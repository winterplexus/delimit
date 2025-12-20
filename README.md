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

### delimit
```
usage: delimit (options)

options: -f <format file name>
         -i <input file name>
         -o <output file name>
         -c use comma field delimiter
         -t use tab field delimiter
         -x use space field delimiter
         -s use single quote delimiter
         -d use double quote delimiter
         -u <unique delimiter (0x00 hexadecimal number)>
         -r report statistics
         -w enable write over input file as output mode
         -v display version
         -? print this usage
```