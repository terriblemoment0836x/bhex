# bhex (Beyond Hex) (Work in progress)
bhex is a simple console hex (also other bases) dumping utility with color support.
## Screenshot:
![Example hex dump of an jpg image](https://i.imgur.com/33ot5DO.png)

## Features:
  - Support for dumping a file in hexadecimal, binary or octal format.
  - Color support to match strings in the dump with the ASCII representation.
  - Choice of the columns count and size.
  - Ability to search for strings in a file.
  - Supports Windows and Linux (Currently Windows only).
## Build
cmake and a ucrt64 toolchain are needed to build the program.
```cmd
mkdir bin build
cd build
cmake ..
make (or ming32-make)
```
## Installation: (WIP)
## Usage:
```
hex_dump [-lbf] [-s n] [-c n] [-n hex|oct|bin] FILENAME
        -l: Don't show the address column.
        -b: Disable colors.
        -f: Disable ASCII column.
        -s n: Set the column size of n number.
        -c n: Set the column number to n.
        -n hex|oct|bin: Specify the dump type.
        -e string: try to find string in the file, you can use \\xAB to specify a hex byte.
        FILENAME: a readable file.
```
