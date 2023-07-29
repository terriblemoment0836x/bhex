### Hex_dump
Is a utilities to dump files in hex/oct/bin format with the corresponding ascii characters.

### Features
	- Colored output (to match string with hex values)
	- Ability to search for strings
	- Chose column size and number of columns per line
	- Show the address of each byte.
	- Don't use printf (this feature will be added at the last stage).

### Proof of concept expected output:

0x0000 aa bb cc dd ee [....]
0x0006 ff gg hh 00 99 [...d]

### Project management
	- cmake as the build system
	- git/github for version control

### Project tree
/
|-/bin: the output binary file
|-/src: the .c and .h files
|-cmake

### Deadline 1 week: 2/8/24