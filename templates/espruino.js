{% import 'macros.jinja2' as utils %}
{% import 'javascript.jinja2' as js %}
{% set template = namespace(sign=false) %}
/*
{{ utils.pad_string(' * ', utils.license(info.copyright.name, info.copyright.date, info.license.name)) }}
 *
 * Auto-generated file for {{ info.title }} v{{ info.version }}.
 * Generated from {{ fileName }} using Cyanobyte Codegen v{{ version }}
 */

 /**
{{utils.pad_string("  * ", info.description)}}
  */

{% macro logic(logicalSteps, function) -%}

{% for step in logicalSteps %}
{% for key in step.keys() %}
{% if step[key] is mapping and 'rawRead' in step[key] %}
  {% set bytes = (step[key].rawRead / 8) | round(1, 'ceil') | int %}
  {{key}} = 0
  var _temp = this.i2c.readFrom(this.address, {{bytes}})
  for (var n of _temp) {
    {{key}} = {{key}} << 8 | n
  }
  {% break %}
{% endif %}
{# Check if assignment is a send-op #}
{% if key == 'cmdWrite' %}
  {% if 'value' in step[key] %}
  this.set{{step[key].register[12:]}}({{step[key].value}})
  {% else %}
  this.set{{step[key].register[12:]}}()
  {% endif %}
  {% break %}
{%- endif %}
{# Check if assignment op #}
{% if step[key] is string and step[key][0:1] == "=" %}
  {{key}} {{step[key]}}
{%- endif %}
{# Check if assignment is a send-op #}
{% if key == 'send' %}
  this.set{{function.register[12:]}}({{step[key]}})
{%- endif %}
{# Check if assignment is register read op #}
{% if step[key] is string and step[key][:12] == '#/registers/' %}
  {{key}} = this.get{{step[key][12:]}}()
{%- endif %}
{# Check if assignment is function call op #}
{% if step[key] is string and step[key][:12] == '#/functions/' %}
  {{key}} = this.{{step[key] | regex_replace('#/functions/(?P<function>.+)/(?P<compute>.+)', '\\g<function>\\g<compute>')}}()
{%- endif %}
{# If the value is a list, then this is a logical setter #}
{% if step[key] is iterable and step[key] is not string %}
  {{key}} = {{js.recursiveAssignLogic(step[key][0], step[key][0].keys()) -}}
{%- endif %}

{% endfor %}
{% endfor %}
{% endmacro %}

{# Create enums for fields #}
{% if fields %}
{% for key,field in fields|dictsort %}
{% if field.enum %}
{# Create enum object #}
var {{key[0].upper()}}{{key[1:]}}Values = {
  {% for ekey,enum in field.enum|dictsort %}
  {{ekey.upper()}}: {{enum.value}}, // {{enum.title}}
  {% endfor %}
}
{% endif %}
{% endfor %}
{% endif %}

var DEVICE = {
{% if i2c.address is iterable and i2c.address is not string %}
{% for address in i2c.address %}
  ADDR_{{address}}: {{address}},
{% endfor %}
{% else %}
  ADDR: {{i2c.address}},
{% endif %}
}

var REGISTER = {
{% for key,register in registers|dictsort %}
  {{key.upper()}}: {{register.address}},
{% endfor %}
}

{{ js.importLittleEndian(i2c) }}
{{ js.importSign(registers, template) }}

{% if i2c.address is iterable and i2c.address is not string %}
function {{info.title}}(i2c, address) {
  this.address = address
{% else %}
function {{info.title}}(i2c) {
  this.address = DEVICE.ADDR
{% endif %}
  this.i2c = i2c // Assume i2c is already setup
  {% if '_lifecycle' in functions and 'Begin' in functions._lifecycle.computed %}
  this._lifecycle_begin()
  {% endif %}
}

{% for key,register in registers|dictsort %}
{% set bytes = (register.length / 8) | round(1, 'ceil') | int %}
{% if (not 'readWrite' in register) or ('readWrite' in register and 'R' is in(register.readWrite)) %}
/**
 * Reads the value of register {{key}}
 * {{register.title}}
 * {{register.description}}
 *
 * @return {number} The value read from the register
 */
{{info.title}}.prototype.get{{key}} = function() {
  // Write the register to read from
  this.i2c.writeTo(this.address, REGISTER.{{key.upper()}})
  var read = this.i2c.readFrom(this.address, {{bytes}}) // Uint8Array
  var result = 0
  for (var byte of read) {
    result = result << 8 | byte
  }
  {% if i2c.endian == 'little' %}
  result = _swapEndian(result, {{register.length}})
  {% endif %}
  {% if register.signed %}
  // Unsigned > Signed integer
  result = _sign(result, {{register.length}})
  {% endif %}
  return result
}
{% endif %}

{% if (not 'readWrite' in register) or ('readWrite' in register and 'W' is in(register.readWrite)) %}
/**
 * Sets the value of register {{key}}
 * {{register.title}}
 * {{register.description}}
 *
 * @param {number} data - The value to write to the register
 */
{{info.title}}.prototype.set{{key}} = function({% if register.length > 0 %}data{% endif %}) {
  {% if i2c.endian == 'little' %}
  data = _swapEndian(data, {{register.length}})
  {% endif %}
  this.i2c.writeTo(this.address, REGISTER.{{key.upper()}}{% if register.length > 0 %}, data{% endif %})
}
{% endif %}

{% endfor %}
{% if fields %}
{% for key,field in fields|dictsort %}
{% if 'R' is in(field.readWrite) %}
/**
 * Reads the value of field {{key}}
 * {{field.title}}
 * {{field.description}}
 *
 * @return {number} The value of the field
 */
{{info.title}}.prototype.get{{key}} = function() {
  // Read register data
  // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
  var register = this.get{{field.register[12:]}}()
  // Mask register value
  register = register & {{utils.mask(field.bitStart, field.bitEnd)}}
  {% if field.bitEnd %}
  // Bitshift value
  register = register >> {{field.bitEnd}}
  {% endif %}
  return register
}
{% endif %}

{%- if 'W' is in(field.readWrite) %}
/**
 * Sets the value of field {{key}}
 * {{field.title}}
 * {{field.description}}
 *
 * @param {number} data - The value to write to the field
 */
{{info.title}}.prototype.set{{key}} = function(data) {
  {% if field.bitEnd %}
  // Bitshift value
  data = data << {{field.bitEnd}}
  {% endif %}
  // Read current register data
  // '#/registers/{{field.register[12:]}}' > '{{field.register[12:]}}'
  register = this.get{{field.register[12:]}}()
  register = register | data
  this.set{{field.register[12:]}}(register)
}
{% endif %}

{% endfor %}
{% endif %}
{% if functions %}
{% for key,function in functions|dictsort %}
{% for ckey,compute in function.computed|dictsort %}
/**
 * {{function.title}}
 * {{function.description}}
 */
{% if compute.input %}
{{info.title}}.prototype.{{key}}{{ckey}} = function({{js.params(compute.input)}}) {
{% else %}
{{info.title}}.prototype.{{key}}{{ckey}} = function() {
{% endif %}
{# Declare our variables #}
{{ js.variables(compute.variables) }}
{# Read `value` if applicable #}
{% if 'input' in compute %}
{%- for vkey,variable in compute.input|dictsort %}
{% if vkey == 'value' %}
  // Read value of register into a variable
  var value = this.get{{function.register[12:]}}()
{% endif %}
{% endfor -%}
{% endif %}
{# Handle the logic #}
{{ logic(compute.logic, function) -}}
 {# Return if applicable #}
{# Return a tuple #}
{% if 'return' in compute and compute.return is not string %}
  return [{% for returnValue in compute.return %}{{ returnValue }}{{ ", " if not loop.last }}{% endfor %}]
{# Return a plain value #}
{% elif compute.return is string %}
  return {{compute.return}}
{% endif %}
}

{% endfor %}
{% endfor %}
{% endif %}

{% if i2c.address is iterable and i2c.address is not string %}
exports.connect = function(i2c, address) {
  return new {{info.title}}(i2c, address)
{% else %}
exports.connect = function(i2c) {
  return new {{info.title}}(i2c)
{% endif %}
}

