# The Ether Programming Language

Ether is a general-purpose low-level
strict procedural programming language that
strives to improve on C. 

## License
YOU ARE FREE TO USE AND DISTRIBUTE
THIS SOFTWARE NON-COMMERCIALLY AND
COMMERCIALLY. HOWEVER, IT IS 
PREFERABLE TO INCLUDE A CREDIT 
WHERE YOU WISH TO USE THE SOURCE
CODE OF THIS PROJECT.

## Building
To build the compiler, simply
use the Makefile provided in
the root folder of this project.
```sh
	$ make
```	

Additionally, if you want
the executable to be stored
in a folder named _bin_, 
simply create a _bin_ folder,
change to the _bin_ directory,
and run make with the parent 
directory as a command line option.
```sh
	$ cd bin/
	$ make ../
```

NOTE: The project dependencies
are listed in the _Dependencies_ 
section of this file.

## Platform Support
As of now, Ether is written with
an assembly backend, so the
platform support are limited 
to x86 (32 and 64-bit) architecture 
only. However, we do plan to
support other architectures
(ARM and RISC-V) in the future.

## Dependencies
Ether's source code is written
in C99, so other that the runtime
C library, no other dependency 
is needed.
