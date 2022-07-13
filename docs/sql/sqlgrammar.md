# SQL Grammar

> Refer: [SQL Tutorial](https://www.tutorialspoint.com/sql/sql-overview.htm)

## Commands

### Data Define

| Command | Description                                                                  |
| ------- | ---------------------------------------------------------------------------- |
| CREATE  | Creates a new table, a view of a table, or other object in the database.     |
| ALTER   | Modifies an existing database object, such as a table.                       |
| DROP    | Deletes an entire table, a view of a table or other objects in the database. |

### Data Maniplation

| Command | Description                                        |
| ------- | -------------------------------------------------- |
| INSERT  | Creates a record or a row.                         |
| DELETE  | Deletes records or a row.                          |
| UPDATE  | Modifies records or a row.                         |
| SELECT  | Retrieves certain records from one or more tables. |

### Data Control

| Command | Description                                                                      |
| ------- | -------------------------------------------------------------------------------- |
| GRANT   | Gives a privilege to user.                                                       |
| REVOKE  | Takes back privileges granted from user.Takes back privileges granted from user. |



## Constrains

| Constrain | Description                                                                          |
| --------- | ------------------------------------------------------------------------------------ |
| NOT NULL  | Ensures that a column cannot have a NULL value.                                      |
| DEFAULT   | Provides a default value for a column when none is specified.                        |
| UNIQUE    | Ensures that all the values in a column are different.                               |
| PRIMARY   | Uniquely identifies each row/record in a database table.                             |
| FOREIGN   | Uniquely identifies a row/record in any another database table.                      |
| CHECK     | The CHECK constraint ensures that all values in a column satisfy certain conditions. |
| INDEX     | Used to create and retrieve data from the database very quickly.                     |


## DataType

### Exact Numeric Data Types

| DATA TYPE  | FROM                       | TO                        |
| ---------- | -------------------------- | ------------------------- |
| bigint     | -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 |
| int        | -2,147,483,648             | 2,147,483,647             |
| smallint   | -32,768                    | 32,767                    |
| tinyint    | 0                          | 255                       |
| bit        | 0                          | 1                         |
| decimal    | -10^38 +1                  | 10^38 -1                  |
| numeric    | -10^38 +1                  | 10^38 -1                  |
| money      | -922,337,203,685,477.5808  | +922,337,203,685,477.5807 |
| smallmoney | -214,748.3648              | +214,748.3647             |


### Approximate Numeric Data Types

| DATA TYPE | FROM         | TO          |
| --------- | ------------ | ----------- |
| float     | -1.79E + 308 | 1.79E + 308 |
| real      | -3.40E + 38  | 3.40E + 38  |


### Date and Time Data Types

| DATA TYPE     | FROM                                 | TO           |
| ------------- | ------------------------------------ | ------------ |
| datetime      | Jan 1, 1753                          | Dec 31, 9999 |
| smalldatetime | Jan 1, 1900                          | Jun 6, 2079  |
| date          | Stores a date like June 30, 1991     |              |
| time          | Stores a time of day like 12:30 P.M. |              |

**Note** − Here, datetime has 3.33 milliseconds accuracy where as smalldatetime has 1 minute accuracy.


### Character Strings Data Types

| DATA TYPE              | Description                                                                                    |
| ---------------------- | ---------------------------------------------------------------------------------------------- |
| **char**Maximum  | length of 8,000 characters.( Fixed length non-Unicode characters)                              |
| varchar                | Maximum of 8,000 characters.(Variable-length non-Unicode data).                                |
| **varchar(max)** | Maximum length of 2E + 31 characters, Variable-length non-Unicode data (SQL Server 2005 only). |
| text                   | Variable-length non-Unicode data with a maximum length of 2,147,483,647 characters.            |


### Unicode Character Strings Data Types

| DATA TYPE               | Description                                                                            |
| ----------------------- | -------------------------------------------------------------------------------------- |
| nchar                   | Maximum length of 4,000 characters.( Fixed length Unicode)                             |
| nvarchar                | Maximum length of 4,000 characters.(Variable length Unicode)                           |
| **nvarchar(max)** | Maximum length of 2E + 31 characters (SQL Server 2005 only).( Variable length Unicode) |
| ntext                   | Maximum length of 1,073,741,823 characters. ( Variable length Unicode )                |


### Binary Data Types

| DATA TYPE                | Description                                                                            |
| ------------------------ | -------------------------------------------------------------------------------------- |
| binary                   | Maximum length of 8,000 bytes(Fixed-length binary data )                               |
| varbinary                | Maximum length of 8,000 bytes.(Variable length binary data)                            |
| **varbinary(max)** | Maximum length of 2E + 31 bytes (SQL Server 2005 only). ( Variable length Binary data) |
| image                    | Maximum length of 2,147,483,647 bytes. ( Variable length Binary Data)                  |


### Misc Data Types

| DATA TYPE        | Description                                                                                    |
| ---------------- | ---------------------------------------------------------------------------------------------- |
| sql_variant      | Stores values of various SQL Server-supported data types, except text, ntext, and timestamp.   |
| timestamp        | Stores a database-wide unique number that gets updated every time a row gets updated           |
| uniqueidentifier | Stores a globally unique identifier (GUID)                                                     |
| xml              | Stores XML data. You can store xml instances in a column or a variable (SQL Server 2005 only). |
| cursor           | Reference to a cursor object                                                                   |
| table            | Stores a result set for later processing                                                       |
