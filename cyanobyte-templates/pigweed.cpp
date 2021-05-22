{% import 'macros.jinja2' as utils %}
{% import 'base.c.jinja2' as cpp %}
{% set template = namespace(enum=false, sign=false, math=false, struct=false) %}
/*
{{ utils.pad_string('* ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
*
* Auto-generated file for {{ info.title }} v{{ info.version }}.
* Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
* Class for {{ info.title }}
{{utils.pad_string("* ", info.description)}}
*/

{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{# // Check if a raw read-op #}
{% if step[key] is mapping and 'rawRead' in step[key] %}
    {% set bytes = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
    ByteBuffer<sizeof(bytes)> byte_buffer;

    // can i even call this?
    PutRegisterAddressInByteBuffer(
      byte_buffer, DEVICE_ADDRESS, order_, register_address_size_
    )
    
    if (!byte_buffer.ok()) {
      return pw::Status::Internal()
    }

    ByteSpan return_data;

    WriteReadFor(byte_buffer.data(), byte_buffer.size(),
      return_data.data(), return_data.size(), std::chrono::seconds(1));

    uint8_t _datum;
    _datum = return_data.data();
    {{key}} = _datum; // Post-process?
    {% break %}
{% endif %}
{# // Check if assignment is a send-op #}
{% if key == '$cmdWrite' %}
    {% if 'value' in step[key] %}
    write{{step[key].register[12:]}}({{step[key].value}});
    {% else %}
    write{{step[key].register[12:]}}();
    {% endif %}
    {% break %}
{% endif %}
{% if key == "$delay" %}
    {# Blocking impl #}
    _time_pt = TimePointAfterAtLeast({{step[key].for}});
    while (SystemClock::now() < _time_pt) {}
{{ logic(step[key].after, function) }}
    {% break %}
{% endif %}
{# // Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
    {{key}} {{step[key]}};
{% endif %}
{# // Check if assignment is a send-op #}
{% if key == 'send' %}
    write{{function.register[12:]}}({{step[key]}});
{% endif %}
{# // Check if assignment is register read op #}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
    {{key}} = read{{step[key][12:]}}();
{% endif %}
{# // Check if assignment is function call op #}
{% if step[key] is string and step[key][:12] == '#/functions/' %}
    {{key}} = {{step[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>\\g<compute>')}}();
{% endif %}
{# // If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
    {{key}} = {{cpp.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}};
{% endif %}
{% endfor %}
{% endfor %}
{%- endmacro %}

{% if i2c.endian == 'little' %}
static short _swap_endian(short val) {
    // Swap the endianness of a short only
    return (val & 0xFF00) >> 8 | (val & 0xFF) << 8;
}
{% endif %}

{# Add signing function if needed #}
{% for key,register in registers|dictsort %}
{% if register.signed %}
{% if template.sign is sameas false %}
static short _sign(short val, char length) {
    // Convert unsigned integer to signed integer
    if (val & (1 << (length - 1))) {
        return val - (1 << length);
    }
    return val;
}
{% set template.sign = true %}
{% endif %}
{% endif %}
{% endfor %}

{% if i2c.address is number %}
#define DEVICE_ADDRESS {{i2c.address}}
{% endif %}

{% for key,register in registers|dictsort %}
#define REGISTER_{{key.upper()}} {{register.address}}
{% endfor %}

{{info.title}}::{{info.title}}(Initiator& initiator,
                            {% if i2c.address is iterable and i2c.address is not string %}Address address{% endif %}
    ): RegisterDevice(initiator, {% if i2c.address is iterable and i2c.address is not string %}Address address{% else %}Address({{i2c.address}}){% endif %}),
{% if i2c.endian == 'little' %}          std::endian::little{% else %}          std::endian::big{% endif %},
          {# FIXME #}register_address_size_(RegisterAddressSize::k1Byte)
      ) {
        {% if i2c.address is iterable and i2c.address is not string %}
        DEVICE_ADDRESS ( address )
        {% endif %}
      }

{% for key,register in registers|dictsort -%}
{% set length = register.length %}
{% set bytes = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
Result<{{cpp.numtype(length)}}> {{info.title}}::read{{key}}() {
  // Hard-coded timeout of 1s.
  {% if length == 0 %}
  return ReadRegister8(REGISTER_{{key.upper()}}, std::chrono::seconds(1));
  {% else %}
  return ReadRegister{{length}}(REGISTER_{{key.upper()}}, std::chrono::seconds(1));
  {% endif %}
}
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
Status {{info.title}}::write{{key}}({% if length > 0 %}{{cpp.numtype(length)}} data{% endif %}) {
  // Hard-coded timeout of 1s.
  {% if length == 0 %}
  return WriteRegister8(REGISTER_{{key.upper()}}, 0, std::chrono::seconds(1))
  {% else %}
  return WriteRegister{{length}}(REGISTER_{{key.upper()}}, data, std::chrono::seconds(1))
  {% endif %}
}
{% endif %}

{% endfor %}

{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
{# Getter #}
Result<{{cpp.registerSize(registers, field.register[12:])}}> {{info.title}}::get{{key}}() {
    // Read register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    Result<{{cpp.registerSize(registers, field.register[12:])}}> res = read{{field.register[12:]}}();
    {# Assume it is good #}
    {{cpp.registerSize(registers, field.register[12:])}} val = res.value();
    // Mask register value
    val = val & {{utils.mask(field.bitStart, field.bitEnd)}};
    {% if field.bitEnd %}
    // Bitshift value
    val = val >> {{field.bitEnd}};
    {% endif %}
    // Rewrap in a Result
    Result<{{cpp.registerSize(registers, field.register[12:])}}> result = new Result(val);
    return result;
}
{% endif -%}

{%- if 'W' is in(field.readWrite) %}
{# Setter #}

Status {{info.title}}::set{{key}}(uint8_t data) {
    {% if field.bitEnd %}
    // Bitshift value
    data = data << {{field.bitEnd}};
    {% endif %}
    // Read current register data
    // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
    Result<{{cpp.registerSize(registers, field.register[12:])}}> res = read{{field.register[12:]}}();
    {{cpp.registerSize(registers, field.register[12:])}} register_data = res.value()
    register_data = register_data | data;
    return write{{field.register[12:]}}(register_data);
}
{% endif %}
{% endfor %}
{% endif %}

{% if functions %}
{% for key,function in functions|dictsort %}
{% for ckey,compute in function.computed|dictsort %}
{% if 'input' in compute %}
{{cpp.returnType(compute)}} {{info.title}}::{{key}}{{ckey}}({{cpp.params(compute)}}) {
{% else %}
{{cpp.returnType(compute)}} {{info.title}}::{{key}}{{ckey}}({{cpp.params(compute)}}) {
{% endif %}
    {# Declare our variables #}
{{ cpp.variables(compute.variables) }}

    {# Read `value` if applicable #}
    {% if 'input' in compute %}
    {%- for vkey,variable in compute.input|dictsort %}
    {% if vkey == 'value' %}
    // Read value of register into a variable
    {{cpp.numconv(variable)}} value = read{{function.register[12:]}}();
    {% endif %}
    {% endfor %}
    {% endif %}
    {# Handle the logic #}
{{ logic(compute.logic, function) }}

    {# Return if applicable #}
    {# Return a tuple #}
    {% if 'return' in compute and compute.return is not string %}
    {# In C languages, the array is a parameter `returnArray` you fill #}
    {% for variable in compute.return %}
    returnArray[{{loop.index - 1}}] = {{variable}};
    {% endfor %}
    {% endif %}
    {# Return a plain value #}
    {% if compute.return is string %}
    return {{compute.return}};
    {% endif %}
}

{% endfor %}
{% endfor %}
{% endif %}
