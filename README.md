# EE/CS120B Introduction to Embedded Systems
> Summer 2019 We will be using C code in order to program our ATMEGA1284 microcontrollers. We will be developing on the Linux machines provided by the school so that we can execute necessary commands to synthesize the programs. 

# Team
* Daniel Kwong
* Bhrayan Escobar
* Akshay Gulabrao
* Ramiro Carrillo

# Notes
Below are some notes for personal use
* `ssh [username]@bolt.cs.ucr.edu` - to connect to UCR server
* `ssh wch136-0x` - where x is equal to 02-30, for direction connection to lab machines, need to be inside a UCR server initially before you can do this.
* `make test` - to generate and run tests for the program
* `/usr/csshare/pkgs/cs120b-avrtools/createProject.sh` - runs project creation bash script
* `avr-gcc -mmcu=atmega1284 -I/usr/csshare/pkgs/simavr/ -Iheader/ -D_SIMULATE_ -Wall -Wl,--undefined=_mmcu,--section-start=.mmcu=910000 -o build/objects/main.elf source/main.c` - compiles the source into main.elf file
* `simavr -v -v -v -v -m atmega1284 -f 8000000 build/objects/main.elf` runs simulation
* `gtkwave build/results/Lab2_introToAVR_trace.vcd` - runs waveform simulation

# Tools Required
* AVR-GCC compiler
* AVR-GDB debugger
* AVRDUDE programmer
* SimAVR simulator
