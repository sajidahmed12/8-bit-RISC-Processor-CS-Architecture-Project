# 8-bit-RISC-Processor Computer Architecture-Project. 
This a project designed by a group of undergraduate students for the Computer Architecture Course Project. 

The task was to design an 8 bit single-cycle CPU that has separate Data Memory and Instruction Memory. 
There is a total of three parts to this Project.

## 1. ISA (Instruction Set Architecture) 
## 2. Assembler 
## 3. Single Cycle Processor

The Processor can run these types of programs. 

a) Simple arithmetic & logic operations
b) Programs that require checking conditions
c) Loop type of programs

# ISA
ISA Instruction Set Architecture. The First part of the project was to build our own ISA based on MIPS 32 bit ISA. Since we had only 8 bits, we had to allocate out bits very carefully, and we had to select the number of instructions as well. We have designed the ISA format as follows.  

## (R-Type) ISA Format
                          opcode	rd      rs	   Shift Amount
                          3 bits	2 bits	2 bits	1 bits

## (I-Type) ISA Format
                          opcode  rd	  Immediate
                          3 bits	2 bits	3 bits
## (J-Type) ISA Format
                          opcode  Target
                          3 bits	5 bits


# Assembler:
Assemblers can automatically generate a machine code from an assembly file written code in C++. In this project, According to the ISA, The assembler reads a program written using assembly language in a text file, then translates it into binary code and generates an output file(.txt) containing machine code. The generated output files will later be useful to run a program in the actual 8-bit Processor.

# ISA(Assembler):

The input codes are written in a text file in assembly format following the ISA. There will be one instruction per line. The output will be generated in Hexadecimal format instead of binary. This will help us later transfer this code into the Instruction Memory block of the logisim circuit.

# Single Cycle Processor: Datapath (Logisim)                                                
In this part of the project, we have designed the complete Single Cycle processor on Logisim. Based on our ISA (can be found on .doc folder), we have designed the Arithmetic Logic Unit, The Register file, and finally, connected them all in the Datapath. Circ file and completed the Project. 

# Processor Testing                                                 
In this section, we have tested our CPU with multiple numbers of Instructions as suggested. We have given input to all the instructions to solve a problem—for instance, a loop. 
All the instructions are then converted into a Hexadecimal format. Then we saved the text file and loaded it on our processor's Instruction memory to run the instructions one after another. 

## A demo instruction file can be found on the Assembler folder named demo_I.txt. 
In logisim datapath. Circ file just loads the file as an image in ROM/Instruction memory and then gives the clock to execute the instructions.
