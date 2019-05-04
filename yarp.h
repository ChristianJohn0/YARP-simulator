//
//  yarp.h
//  yarp
//
//  Created by Christian John on 2017-11-28.
//  Copyright © 2017 Christian John. All rights reserved.
//

#ifndef yarp_h
#define yarp_h

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
using namespace std;

class yarp_sim
{
public:
    struct flags
    {
        bool C;
        bool N;
        bool V;
        bool Z;
    }flag;

    uint32_t R[8];                  // registers 
    unsigned int status;
    
    yarp_sim();
    //
    // fetch
    //
    // Purpose: fetches instruction from memory, extracts icode:ifun. May extract rA:rB, may extract a 4 byte constant, valC. Computes valP = PC + size of instruction depending on the values of icode:ifun.
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> rA: integral value of rA (passed by reference).
    //  <4> rB: integral value of rB (passed by reference).
    //  <5> valC: integral value of valC (passed by reference).
    //  <6> valP: integral value of valP (passed by reference).
    //  <7> PC: integral value of PC (passed by reference).
    //  <8> data[]: unsigned char array for data[] which stores our yarp memory.
    // Precondition(s): N/A
    // Postcondition(s):
    //  <1> retrieved values of icode:ifun. May extract rA:rB, may extract a 4 byte constant, valC. Computes valP = PC + size of instruction depending on the values of icode:ifun.
    // Return: N/A
    // Side Effect:
    void fetch(int &icode, int &ifun, int &rA, int &rB , int &valC, int &valP, int &PC, unsigned char data[]);
    
    //
    // decode
    //
    // Purpose:  reads up to 2 operands from the register file, specific registers selected by the instruction fields rA and rB, giving valA and valB.
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> rA: integral value of rA (passed by reference).
    //  <4> rB: integral value of rB (passed by reference).
    //  <5> valA: integral value of valA (passed by reference).
    //  <6> valB: integral value of valB (passed by reference).
    // Precondition(s): extracted values for icode and ifun in order to identify instructions.
    // Postcondition(s):
    //  <1> updates using specific registers selected by the instruction fields rA and rB, giving valA and valB.
    // Return: N/A
    // Side Effect:
    void decode(int &icode, int &ifun, int &rA, int &rB, int &valA, int &valB);
    
    //
    // execute
    //
    // Purpose:  the ALU either (1) performs the operation specified in the ifun field, (2) computes the effective address of a memory reference, or (3) increments/decrements the sp by 4.  The resulting value is valE.  The condition codes are set if an operation was executed.  For a branch instruction, this stage testes the condition codes and the branch condition (given in ifun) to see whether the branch should be taken or not.
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> valA: integral value of valA (passed by reference).
    //  <4> valB: integral value of valB (passed by reference).
    //  <5> valE: integral value of valE (passed by reference).
    //  <6> valC: integral value of valC (passed by reference).
    //  <7> cnd: boolean value of cnd (passed by reference).
    // Precondition(s): extracted values for icode and ifun in order to identify instructions. Decoded values of valA, valB or fetched value for valC.
    // Postcondition(s):
    //  <1> returns the calculated values to valE using ALU which either (1) performs the operation specified in the ifun field, (2) computes the effective address of a memory reference, or (3) increments/decrements the sp by 4.  The resulting value stored in valE. The condition codes are set if an operation was executed (operations: ADD, SUB, AND, XOR). Function for setting of this coditional codes: setflag(int &ifun, int &valA, int &valB, int &valE). For a branch instruction, this stage testes the condition codes and the branch condition (given in ifun) to see whether the branch should be taken or not (function: cond(ifun)).
    // Return: N/A
    // Side Effect:
    void execute(int &icode, int &ifun, int &valA, int &valB, int &valE, int &valC, bool &cnd);
    
    //
    // memory
    //
    // Purpose: may write data to memory or read data from memory. Any value read is designated valM. Any value to be written to data is either from valA or valP.
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> valA: integral value of valA (passed by reference).
    //  <4> valE: integral value of valE (passed by reference).
    //  <5> valC: integral value of valC (passed by reference).
    //  <6> valM: integral value of valM (passed by reference).
    //  <7> valP: integral value of valP (passed by reference).
    //  <8> data[]: unsigned char array for data[] which stores our yarp memory.
    // Precondition(s):
    //  <1> extracted values for icode and ifun in order to identify instructions. Decoded values of valA, valB or fetched value for valC.
    // Postcondition(s):
    //  <1> either memory(data array) updated by being written to or data is read from memory and value read is designated valM.
    // Return: N/A
    // Side Effect:
    void memory(int &icode, int &ifun, int &valA, int &valE, int &valC, int &valM, int &valP, unsigned char data[]);
    
    //
    // write_back
    //
    // Purpose: 0 up to 2 results are written back to the register file.
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> rA: integral value of rA (passed by reference).
    //  <4> valE: integral value of valE (passed by reference).
    //  <5> valM: integral value of valM (passed by reference).
    //  <6> data[]: unsigned char array for data[] which stores our yarp memory.
    // Precondition(s):
    //  <1> extracted values for icode and ifun in order to identify instructions. Executed return value of valE and valM from the memory function.
    // Postcondition(s):
    //  <1> updates to the registers depending on the instruction. The updates can be made to 0-2 registers.
    // Return: N/A
    // Side Effect:
    void write_back(int &icode, int &ifun, int &rA, int &valE, int &valM, unsigned char data[]);
    
    //
    // PCupdate
    //
    // Purpose: the PC is set to the address of the next instruction.
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> valC: integral value of valC (passed by reference).
    //  <4> valM: integral value of valM (passed by reference).
    //  <5> valP: integral value of valP (passed by reference).
    //  <6> PC: integral value of PC (passed by reference).
    //  <7> cnd: boolean value of cnd (passed by reference).
    // Precondition(s):
    //  <1> extracted values for icode and ifun in order to identify instructions. Fetched value of valC, valP, valM from the memory function, executed value of cnd.
    // Postcondition(s):
    //  <1> the PC is set to the address of the next instruction depending on the instruction.
    // Return: N/A
    // Side Effect:
    void PCupdate(int &icode, int &ifun, int &valC, int &valM, int &valP, int &PC, bool &cnd);
    
    //
    // setflag
    //
    // Purpose: setting of the conditional codes (flags CNZV).
    // Parameter(s):
    //  <1> ifun: integral value of ifun for identifying the kind of instruction (passed by reference).
    //  <2> valA: integral value of valA (passed by reference).
    //  <3> valB: integral value of valB (passed by reference).
    //  <4> valE: integral value of valE (passed by reference).
    // Precondition(s):
    //  <1> extracted value of ifun in order to identify instructions. Executed values of valE and decoded value of valA and valB.
    // Postcondition(s):
    //  <1> set conditional codes (flags CNZV) depending on the kind of operation which is identified by the value of ifun.
    // Return: N/A
    // Side Effect: returns -valB if the operation is SUB (that is ifun == 1). Updates the flags following my algorithm for the various flags.
    void setflag(int &ifun, int &valA, int &valB, int &valE);
    
    //
    // cond
    //
    // Purpose: conditional return controlling the branching or not of a function.
    // Parameter(s):
    //  <1> ifun: integral value of ifun for identifying the kind of instruction (passed by reference).
    // Precondition(s):
    //  <1> extracted value of ifun in order to identify instructions.
    // Postcondition(s):
    //  <1> returns true if condition is valid and false otherwise.
    // Return: cond: Boolean value.
    // Side Effect: returns true of false depending on if the condition(s) are valid and the condition(s) changes depending on the value of ifun.
    bool cond(int &ifun);
    
    //
    // print
    //
    // Purpose: printing of the individual instuctions
    // Parameter(s):
    //  <1> icode: integral value of icode for identifying the kind of instruction (passed by reference).
    //  <2> ifun: integral value of ifun also for identifying the kind of instruction (passed by reference).
    //  <3> PCprint: integral value of PCprint (passed by reference).
    //  <4> PC: integral value of PC (passed by reference).
    //  <5> count: integral value of count (passed by reference).
    //  <6> data[]: unsigned char array for data[] which stores our yarp memory.
    // Precondition(s):
    //  <1> extracted values for icode and ifun in order to identify instructions. PCupdate value of PC
    // Postcondition(s):
    //  <1> printed pc value, step, bytes used in instruction and the assembly-language opcode, discovered by examining the first byte. example: pc=000: step 1: 30  2F  09  00  00  00       | MOV
    // Return: N/A
    // Side Effect:
    void print(int &icode, int &ifun, int &PCprint, int &PC, int &count, unsigned char data[]);
    
    //
    // print
    //
    // Purpose: printing ending status after run and changes to both registers and memory
    // Parameter(s):
    //  <1> PC: integral value of PC (passed by reference).
    //  <2> count: integral value of count (passed by reference).
    //  <3> data[]: unsigned char array for data[] which stores our yarp memory.
    //  <4> datacopy[]: unsigned char array for datacopy[] which is the original copy of the array data
    // Precondition(s):
    //  <1> copy of data in datacopy
    //  <2> values for count and PC
    // Postcondition(s):
    //  <1> outputs end state after run in the form Stopped in count steps at PC=value(3-digit hex number). Status 'status', conditional codes. Example: Stopped in 4 steps at PC=0x014. Status 'AOK', CC: N=0 Z=0 C=1 V=0.
    //  <2> compares the register changes to the registers in the form register: 00000000 -> change. example: r2: 00000000 -> 00000009
    //  <3> compares the memory changes to the memory in the form memory(3-digit hex number): 00000000 -> change. example: 0x00c: 0x00000000 -> 0x0000002d
    // Return: N/A
    // Side Effect:
    void print_change(int &PC, int &count, unsigned char data[], unsigned char datacopy[]);

};
#endif /* yarp_h */
