{% import 'macros.jinja2' as utils %}
{% import 'python.jinja2' as py %}
{% set template = namespace(enum=false, sign=false, math=false, struct=false) %}
{{ utils.pad_string('# ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) -}}
#
# Auto-generated file for {{ info.title }} v{{ info.version }}.
# Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
"""
Class for {{ info.title }}
"""
{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{% if step[key] is mapping and 'rawRead' in step[key] %}
        {% set bytes = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
        {{key}} = 0
        {% for n in range(bytes) %}
        {# Read each byte one at a time from device #}
        _datum = self.bus.read_byte(self.device_address)
        {{key}} = {{key}} << 8 | _datum
        {% endfor %}
        {% break %}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
        {% if 'value' in step[key] %}
        self.set_{{step[key].register[12:].lower()}}({{step[key].value}})
        {% else %}
        self.set_{{step[key].register[12:].lower()}}()
        {% endif %}
        {% break %}
{%- endif %}
{# Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
        {{key | camel_to_snake}} {{step[key]}}
{%- endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
        self.set_{{function.register[12:].lower()}}({{step[key]}})
{%- endif %}
{# Check if assignment is register read op #}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
        {{key | camel_to_snake}} = self.get_{{step[key][12:].lower()}}()
{%- endif %}
{# Check if assignment is function call op #}
{% if step[key] is string and step[key][:12] == '#/functions/' %}
        {{key | camel_to_snake}} = self.{{step[key].lower() | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>_\\g<compute>')}}()
{%- endif %}
{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
        {{key | camel_to_snake}} = {{py.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}}
{%- endif %}

{% endfor %}
{%- endfor %}
{%- endmacro %}

{{ py.importStdLibs(fields, functions, i2c, template) -}}
import smbus

{# Create enums for fields #}
{% if fields %}
{% for key,field in fields|dictsort %}
{% if field.enum %}
{# Create enum class #}
class {{key[0].upper()}}{{key[1:]}}Values(Enum):
    """
{{utils.pad_string("    ", "Valid values for " + field.title)}}
    """
    {% for ekey,enum in field.enum|dictsort %}
    {{ekey.upper()}} = {{enum.value}} # {{enum.title}}
    {% endfor %}
{% endif %}
{% endfor %}
{% endif %}
{% if imports %}
{% for key,data in imports|dictsort %}
{% for structKey,struct in data.structs.items() %}
{% if struct.is_enum %}
{# Create enum class from emb #}
class {{structKey[0].upper()}}{{structKey[1:]}}Values(Enum):
    """
{{utils.pad_string("    ", "Valid values for " + structKey)}}
    """
    {% for ekey,enum in struct.fields.items() %}
    {% if enum.value is not mapping %}
    {% set val = enum.value.split(".")[0]+"Values."+enum.value.split(".")[1].upper() if "." in enum.value else enum.value %}
    {{ekey.upper()}} = {{val}} 
    {% else %}
    {% set symbol = enum.value.symbol %}
    {% set arg0 = enum.value.arg[0] %}
    {% set arg1 = enum.value.arg[1] %}
    {% set val0 = arg0.split(".")[0]+"Values."+arg0.split(".")[1].upper() if "." in arg0 else arg0 %}
    {% set val1 = arg1.split(".")[0]+"Values."+arg1.split(".")[1].upper() if "." in arg1 else arg1 %}
    {{ekey.upper()}} = {{"{} {} {}".format(val0, symbol, val1)}} 
    {% endif %}
    {% endfor %}
{% endif %}
{% endfor %}
{% endfor %}
{% endif %}
{% if i2c.address is iterable and i2c.address is not string %}
class DeviceAddressValues(Enum):
    """
    Valid device addresses
    """
    {% for address in i2c.address %}
    I2C_ADDRESS_{{address}} = {{address}}
    {% endfor %}
{% endif %}

{{ py.importLittleEndian(i2c) }}
{{ py.importSign(registers, template) }}
class {{ info.title }}:
    """
{{utils.pad_string("    ", info.description)}}
    """
    {% if i2c.address is number %}
    device_address = {{i2c.address}}
    {% endif %}
    {% for key,register in registers|dictsort %}
    REGISTER_{{key.upper()}} = {{register.address}}
    {% endfor %}

    {% if i2c.address is iterable and i2c.address is not string %}
    def __init__(self, address):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)
        self.device_address = address
    {% else %}
    def __init__(self):
        # Initialize connection to peripheral
        self.bus = smbus.SMBus(1)
    {% endif %}
        {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
        self._lifecycle_begin()
        {% endif %}

    {% if imports %}
    {% for key,data in imports|dictsort %}
    {% for structKey,struct in data.structs|dictsort|reverse %}
    {% if not struct.is_enum %}
    def msg_{{key.lower()}}_{{structKey.lower()}}(
        self,
    {% for param_name, param_info in struct.fields|dictsort|reverse %}
        {{param_name}},
    {% endfor %}
    ): # Put params here
        msg = 0
        {% for param_name, param_info in struct.fields|dictsort|reverse %}
        msg |= {{param_name}} {{"<< {}".format(param_info.offset_in_bit) if param_info.offset_in_bit != 0}} 
        {% endfor %}
        return msg # Return the message data structure here
   
    def decode_{{key.lower()}}_{{structKey.lower()}}(self, msg): # Put params here
        res = []
        {% for param_name, param_info in struct.fields|dictsort|reverse %}
        {{param_name}} = msg {{">> {}".format(param_info.offset_in_bit) if param_info.offset_in_bit != 0}} 
        {{param_name}} &= 1 << {{param_info.size_in_byte}} - 1
        res.append({{param_name}})

        {% endfor %}
        return  res # Return the decoded msg

    {% endif %}
    {% endfor %}
    {% endfor %}
    {% endif -%}

    {% for key,register in registers|dictsort %}
    {% set bytes = (register.length / 8) | round(1, 'ceil') | int %}
    {% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", register.description)}}
        """
        {% if register.length <= 8 %}
        val = self.bus.read_byte_data(
            self.device_address,
            self.REGISTER_{{key.upper()}}
        )
        {% elif register.length <= 16 %}
        val = self.bus.read_word_data(
            self.device_address,
            self.REGISTER_{{key.upper()}}
        )
        {% elif register.length <= 32 %}
        byte_list = self.bus.read_i2c_block_data(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            {{bytes}}
        )
        val = 0
        {% for n in range(bytes) %}
        val = val << 8 | byte_list[{{n}}]
        {% endfor %}
        {% endif %}
        {% if i2c.endian == 'little' %}
        val = _swap_endian(val, {{register.length}})
        {% endif %}
        {% if register.signed %}
        # Unsigned > Signed integer
        val = _sign(val, {{register.length}})
        {% endif %}
        return val
    {% endif %}

    {% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
    def set_{{key.lower()}}(self{% if register.length > 0 %}, data{% endif %}):
        """
{{utils.pad_string("        ", register.description)}}
        """
        {% if i2c.endian == 'little' %}
        data = _swap_endian(data, {{register.length}})
        {% endif %}
        {% if register.length == 0 %}
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            []
        )
        {% elif register.length <= 8 %}
        self.bus.write_byte_data(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            data
        )
        {% elif register.length <= 16 %}
        self.bus.write_word_data(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            data
        )
        {% elif register.length <= 32 %}
        buffer = []
        {% for n in range(bytes) %}
        buffer[{{n}}] = (data >> {{8 * (bytes - n - 1)}}) & 0xFF
        {% endfor %}
        self.bus.write_i2c_block_data(
            self.device_address,
            self.REGISTER_{{key.upper()}},
            buffer
        )
        {% endif %}
    {% endif %}
    {% endfor %}

    {% if fields %}
    {% for key,field in fields|dictsort %}
    {% if 'R' is in(field.readWrite) %}
    {# Getter #}

    def get_{{key.lower()}}(self):
        """
{{utils.pad_string("        ", field.description)}}
        """
        # Read register data
        # '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
        val = self.get_{{field.register[12:].lower()}}()
        # Mask register value
        val = val & {{utils.mask(field.bitStart, field.bitEnd)}}
        {% if field.bitEnd %}
        # Bitshift value
        val = val >> {{field.bitEnd}}
        {% endif %}
        return val
    {% endif -%}

    {%- if 'W' is in(field.readWrite) %}
    {# Setter #}

    def set_{{key.lower()}}(self, data):
        """
{{utils.pad_string("        ", field.description)}}
        """
        {% if field.bitEnd %}
        # Bitshift value
        data = data << {{field.bitEnd}}
        {% endif %}
        # Read current register data
        # '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
        register_data = self.get_{{field.register[12:].lower()}}()
        register_data = register_data | data
        self.set_{{field.register[12:].lower()}}(register_data)
    {% endif %}
    {% endfor %}
    {% endif %}
    {% if functions %}
    {% for key,function in functions|dictsort %}
    {% for ckey,compute in function.computed|dictsort %}
    {% if compute.input %}
    def {{key.lower()}}_{{ckey.lower()}}(self, {{py.params(compute.input)}}):
    {% else %}
    def {{key.lower()}}_{{ckey.lower()}}(self):
    {% endif %}
        """
{{utils.pad_string("        ", function.description)}}
        """
        {# Declare our variables #}
{{ py.variables(compute.variables) }}
        {# Read `value` if applicable #}
        {% if 'input' in compute %}
        {%- for vkey,variable in compute.input|dictsort %}
        {% if vkey == 'value' %}
        # Read value of register into a variable
        value = self.get_{{function.register[12:].lower()}}()
        {% endif %}
        {% endfor -%}
        {% endif %}
        {# Handle the logic #}
{{ logic(compute.logic, function) -}}
        {# Return if applicable #}
        {# Return a tuple #}
        {% if 'return' in compute and compute.return is not string %}
        return [{% for returnValue in compute.return %}{{ returnValue | camel_to_snake }}{{ ", " if not loop.last }}{% endfor %}]
        {# Return a plain value #}
        {% elif compute.return is string %}
            {# See if we need to massage the data type #}
            {% if compute.output == 'int16' %}
        # Convert from a unsigned short to a signed short
        {{compute.return}} = struct.unpack("h", struct.pack("H", {{compute.return}}))[0]
            {% endif %}
        return {{compute.return}}
        {% endif %}
    {% endfor %}
    {% endfor %}
    {% endif %}