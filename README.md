Delimit Application
===================

Delimit is an application that will read each record containing fields from a text file and insert delimiters between each field. 

Delimit can reformat each field using filter actions defined in a format file where each line in the format file must contain the size, filter action and name for each field in the input text file.

Delimit format file must contain the following for each field in the input file:

 `<field size> <field filter action> <field name>`

Format Field | Description
------------ | -----------
`<field size>` | size of the field
`<field filter action>` | filter action to be performed on the field
`<field name>` | name of the field

`<field filter action>`

Filter Action Field Options | Description
--------------------------- | -----------
`-` | no action
`alphabetic` | allow only alphabetic characters
`alphanumeric` | allow only either alphabetic characters or digits (0-9)
`numeric` | allow only digits (0-9)
`null` | null field (zero length)
`remove` | remove field
`spaces` | replace field with space characters
`"string"` | replace field with this string

`<field name>`

Name Field Options | Description
------------------ | -----------
`-` | no field name
`"field name"` | given field name

The applications are written in the C language for both Windows and Linux operating systems.