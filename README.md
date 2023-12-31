<div align="center">
  <img width="120" src="https://github.com/terriblemoment0836x/bhex/blob/main/icon/icon.jpg?raw=true" >
  <h1>bhex</h1>

[![Linux build](https://github.com/terriblemoment0836x/bhex/actions/workflows/linux_build.yml/badge.svg)](https://github.com/terriblemoment0836x/bhex/actions/workflows/linux_build.yml)
[![Windows build](https://github.com/terriblemoment0836x/bhex/actions/workflows/windows_build.yml/badge.svg)](https://github.com/terriblemoment0836x/bhex/actions/workflows/windows_build.yml)
  
  bhex (beyound hex) is a simple console hex (also other bases) dumping utility with color support.
  </div>
  <br>
  


## Screenshot:
![Example hex dump of an jpg image](https://i.imgur.com/33ot5DO.png)

## Features:
  - Support for dumping a file in hexadecimal, binary or octal format.
  - Color support to match strings in the dump with the ASCII representation.
  - Choice of the columns count and size.
  - Ability to search for strings in a file.
  - Supports Windows and Linux.
## Building
CMake and C toolchain are needed to build the program.
```cmd
mkdir bin build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . 
```
### Running
```cmd
cd bin
./bhex (or .\bhex.exe)
```
### Usage:
```
hex_dump [-lbf] [-s n] [-c n] [-n hex|oct|bin] FILENAME
        -l: Don't show the address column.
        -b: Disable colors.
        -f: Disable ASCII column.
        -s n: Set the column size to n.
        -c n: Set the column number to n.
        -n hex|oct|bin: Specify the dump type.
        -e string: try to find string in the file, you can use \\xAB to specify a hex byte.
        FILENAME: a readable file.
```
