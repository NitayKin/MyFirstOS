## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)
* [Setup](#setup)
* [Run](#Run)

## General info
This project is a simple Operation System for x86 architecture.  
there are task scheduling, mutex, system calls and virtual memory implementations.
	
## Technologies
The project is written in C and assembly.  
it was compiled on Ubuntu 22.04.1 LTS , and tested using QEMU emulator.
	
## Setup
To compile this project, you will need:  
1.gcc ( was tested on version 11.3.0 )  
2.nasm  ( was tested on version 2.15.05)  
to emulate this project, you will need:  
1.Qemu emulating X86 machine ( was tested on qemu-system-x86_64 version 6.2.0. )
	
## Run
  
In the root directory, there is a ./run shell file, which can be executed in order to compile the project: 

```
./run.sh
```  
After the execution, an image file named "os-image" will be created, which is the final binary file of the operation system.  

then, the project can be run with Qemu using the command:  
```
qemu-system-x86_64 -monitor stdio -D ./log.txt -d int -m 4000 os-image
```  
This command will run the operation system on the emulator, and will also emit a log file named log.txt.  
The log file can be viewed after the emulation, for debugging purposes.
