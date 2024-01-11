Delimit Application
===================

Delimit is an application that will read each record containing fields from a text file and insert delimiters between each field. 

Delimit can reformat each field using filter actions defined in a format file where each line in the format file must contain the size, filter action and name for each field in the input text file.

Delimit format file must contain the following for each field in the input file:

`<field size> <field filter action> <field name>`

Format Field | Description
------------ | -----------
`<field size>` | field size
`<field filter action>` | field filter action (see below)
`<field name>` | field name

`<field filter action>`

Filter Action Field Options | Description
--------------------------- | -----------
`-` | no action
`alphabetic` | allow alphabetic characters only
`alphanumeric` | allow either alphabetic characters or digits (0-9) only
`numeric` | allow digits (0-9) only
`printable` | allow printable characters only
`remove` | remove field
`spaces` | replace field with space characters
`"string"` | replace field with this string
`null` | null field (no text data)

`<field name>`

Name Field Options | Description
------------------ | -----------
`-` | no name
`"field name"` | descriptive name for field

The application is written in the C language for both Windows and Linux operating systems.
