/*//
//  yarp.cpp
//  yarp
//
//  Created by Christian John on 2017-11-28.
//  Copyright © 2017 Christian John. All rights reserved.
//

#include "yarp.h"
yarp_sim::yarp_sim()
{
    for (int i = 0; i < 8; i++)
    {
        R[i] = 0;
    }
    status = 1;        // default status state 'AOK'
}

void yarp_sim::fetch(int &icode, int &ifun, int &rA, int &rB , int &valC, int &valP, int &PC, unsigned char data[])
{
    icode = data[PC] >> 4;                  // retrive first four bits
    ifun = data[PC] & 0xF;                  // retrive second four bits
    
    if ((icode == 0) && (ifun == 0))
    {
        status = 2;
        valP = PC + 1;
    }
    else if ((icode == 1) && (ifun == 0))
    {
        valP = PC + 1;
    }
    else if ((icode == 2) && (ifun == 0))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if ((icode == 3) && (ifun == 0))
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        byte1 = i + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 6;
    }
    else if ((icode == 4) && (ifun == 0))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if ((icode == 4) && (ifun == 1))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if ((icode == 5) && (ifun == 0))
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        byte1 = i + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 6;
    }
    else if ((icode == 5) && (ifun == 1))
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        byte1 = i + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 6;
    }
    else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        byte1 = PC + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 5;
    }
    else if ((icode == 8) && (ifun == 0))
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        byte1 = PC + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 5;
    }
    else if ((icode == 9) && (ifun == 0))
    {
        valP = PC + 1;
    }
    else if ((icode == 10) && (ifun == 0))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if ((icode == 11) && (ifun == 0))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else
        status = 4;                          // update value to the status of 4 which stands for 'INS'
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::decode(int &icode, int &ifun, int &rA, int &rB , int &valA, int &valB)
{
    if ((icode == 0) && (ifun == 0))
    {
    }
    else if ((icode == 1) && (ifun == 0))
    {
    }
    else if ((icode == 2) && (ifun == 0))
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if ((icode == 3) && (ifun == 0))
    {
        
    }
    else if ((icode == 4) && (ifun == 0))
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if ((icode == 4) && (ifun == 1))
    {
        rA = (rA==15) ? 7 : rA;
        rB = (rB==15) ? 7 : rB;
        valA = R[rA];
        valB = R[rB];
    }
    else if ((icode == 5) && (ifun == 0))
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if ((icode == 5) && (ifun == 1))
    {
        rA = (rA==15) ? 7 : rA;
        rB = (rB==15) ? 7 : rB;
        valA = R[rA];
        valB = R[rB];
    }
    else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
    {
        rA = (rA==15) ? 7 : rA;
        rB = (rB==15) ? 7 : rB;
        valA = R[rA];
        valB = R[rB];
    }
    else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
    {
        
    }
    else if ((icode == 8) && (ifun == 0))
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if ((icode == 9) && (ifun == 0))
    {
        valA = R[7];
        valB = R[7];
    }
    else if ((icode == 10) && (ifun == 0))
    {
        rA = (rA==15) ? 7 : rA;
        valA = R[rA];
        valB = R[7];
    }
    else if ((icode == 11) && (ifun == 0))
    {
        valA = R[7];
        valB = R[7];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::execute(int &icode, int &ifun, int &valA, int &valB, int &valE, int &valC, bool &cnd)
{
    
    if ((icode == 0) && (ifun == 0))
    {
    }
    else if ((icode == 1) && (ifun == 0))
    {
    }
    else if ((icode == 2) && (ifun == 0))
    {
        valE = 0 + valB;
    }
    else if ((icode == 3) && (ifun == 0))
    {
        valE = 0 + valC;
    }
    else if ((icode == 4) && (ifun == 0))
    {
        valE = valB;
    }
    else if ((icode == 4) && (ifun == 1))
    {
        valE = valB;
    }
    else if ((icode == 5) && (ifun == 0))
    {
        valE = valB + valC;
    }
    else if ((icode == 5) && (ifun == 1))
    {
        valE = valB + valC;
    }
    else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
    {
        switch(ifun) {
            case 0 :
                valE = valA + valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            case 1 :
                valE = valA - valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            case 2 :
                valE = valA & valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            case 3 :
                valE = valA ^ valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            default :
                cout << setw(28) << "INVALID OPERATION";
        }
    }
    else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
    {
        cnd = yarp_sim::cond(ifun);                                 // getting boolean value for validity of operation
    }
    else if ((icode == 8) && (ifun == 0))
    {
        valE = valB + (-4);
    }
    else if ((icode == 9) && (ifun == 0))
    {
        valE = valB + 4;
    }
    else if ((icode == 10) && (ifun == 0))
    {
        valE = valB + (-4);
    }
    else if ((icode == 11) && (ifun == 0))
    {
        valE = valB + 4;
    }
}

void yarp_sim::setflag(int &ifun, int &valA, int &valB, int &valE)
{
    if (ifun == 1)
        valB = -valB;
    
    //Overflow Flag. The most recent operation caused a two’s-complement overflow—either negative or positive.
    flag.V = ((valA < 0) == (valB < 0)) && ((valE < 0) != (valA < 0));
    flag.Z = (valE == 0); //Zero Flag. The most recent operation yielded zero.
    flag.N = (valE < 0); //Negative Flag. The most recent operation yielded a negative value.
    //Carry Flag. The most recent operation generated a carry out of the most significant bit. Used to detect overflow for unsigned operations.
    flag.C = (unsigned) valE < (unsigned) valA;
    
    if (ifun == 1)
        valB = -valB;
}

bool yarp_sim::cond(int &ifun)
{
    switch(ifun) {
        case 0 :
            if (flag.Z) return true;
            else return false;
            break;
        case 1 :
            if (!flag.Z) return true;
            else return false;
            break;
        case 2 :
            if (flag.C) return true;
            else return false;
            break;
        case 3 :
            if (!flag.C) return true;
            else return false;
            break;
        case 4 :
            if (flag.N) return true;
            else return false;
            break;
        case 5 :
            if (!flag.N) return true;
            else return false;
            break;
        case 6 :
            if (flag.V) return true;
            else return false;
            break;
        case 7 :
            if (!flag.V) return true;
            else return false;
            break;
        case 8 :
            if (flag.C && !flag.Z) return true;
            else return false;
            break;
        case 9 :
            if (!flag.C || flag.Z) return true;
            else return false;
            break;
        case 10 :
            if (flag.N == flag.V) return true;
            else return false;
            break;
        case 11 :
            if (flag.N != flag.V) return true;
            else return false;
            break;
        case 12 :
            if (!flag.Z && (flag.N == flag.V)) return true;
            else return false;
            break;
        case 13 :
            if (!flag.Z && (flag.N != flag.V)) return true;
            else return false;
            break;
        case 14 :
            return true;
            break;
        default :
            return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::memory(int &icode, int &ifun, int &valA, int &valE, int &valC, int &valM, int &valP, unsigned char data[])
{
    if ((icode == 0) && (ifun == 0))
    {
    }
    else if ((icode == 1) && (ifun == 0))
    {
    }
    else if ((icode == 2) && (ifun == 0))
    {
    }
    else if ((icode == 3) && (ifun == 0))
    {
    }
    else if ((icode == 4) && (ifun == 0))
    {
        if (valE < 0 || valE > 1020) status = 3;
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
    else if ((icode == 4) && (ifun == 1))
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valA & 0x000000FF);
            data[byte2] = (valA & 0x0000FF00);
            data[byte3] = (valA & 0x00FF0000);
            data[byte4] = (valA & 0xFF000000);
        }
    }
    else if ((icode == 5) && (ifun == 0))
    {
        if (valE < 0 || valE > 1020) status = 3;         // check to see if the memory can be accessed
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
    else if ((icode == 5) && (ifun == 1))
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valA & 0x000000FF);
            data[byte2] = (valA & 0x0000FF00);
            data[byte3] = (valA & 0x00FF0000);
            data[byte4] = (valA & 0xFF000000);
        }
    }
    else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
    {
    }
    else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
    {
    }
    else if ((icode == 8) && (ifun == 0))
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valP & 0x000000FF);
            data[byte2] = (valP & 0x0000FF00);
            data[byte3] = (valP & 0x00FF0000);
            data[byte4] = (valP & 0xFF000000);
        }
    }
    else if ((icode == 9) && (ifun == 0))
    {
        if (valA < 0 || valA > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valA;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
    else if ((icode == 10) && (ifun == 0))
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valA & 0x000000FF);
            data[byte2] = (valA & 0x0000FF00);
            data[byte3] = (valA & 0x00FF0000);
            data[byte4] = (valA & 0xFF000000);
        }
    }
    else if ((icode == 11) && (ifun == 0))
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valA;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::write_back(int &icode, int &ifun, int &rA, int &valE, int &valM, unsigned char data[])
{
    if ((icode == 0) && (ifun == 0))
    {
    }
    else if ((icode == 1) && (ifun == 0))
    {
    }
    else if ((icode == 2) && (ifun == 0))
    {
        R[rA] = valE;
    }
    else if ((icode == 3) && (ifun == 0))
    {
        R[rA] = valE;
    }
    else if ((icode == 4) && (ifun == 0))
    {
        if (status != 3) R[rA] = valM;
    }
    else if ((icode == 4) && (ifun == 1))
    {
    }
    else if ((icode == 5) && (ifun == 0))
    {
        if (status != 3) R[rA] = valM;
    }
    else if ((icode == 5) && (ifun == 1))
    {
    }
    else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
    {
        R[rA] = valE;
    }
    else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
    {
        
    }
    else if ((icode == 8) && (ifun == 0))
    {
        R[7] = valE;
    }
    else if ((icode == 9) && (ifun == 0))
    {
        R[7] = valE;
    }
    else if ((icode == 10) && (ifun == 0))
    {
        R[7] = valE;
    }
    else if ((icode == 11) && (ifun == 0))
    {
        if (status != 3)
        {
            R[7] = valE;
            R[rA] = valM;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::PCupdate(int &icode, int &ifun, int &valC, int &valM, int &valP, int &PC, bool &cnd)
{
    if (status == 1)
    {
        if ((icode == 0) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 1) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 2) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 3) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 4) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 4) && (ifun == 1))
        {
            PC = valP;
        }
        else if ((icode == 5) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 5) && (ifun == 1))
        {
            PC = valP;
        }
        else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
        {
            PC = valP;
        }
        else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
        {
            if (valC < 0 || valC > 1020) status = 3;                // if out_of_bounds update status to 3 'ADR' read/write of illegal address
            else
                PC = cnd ? valC : valP;                             // else updates condition depending on cnd: if true PC = valC else PC = valP
        }
        else if ((icode == 8) && (ifun == 0))
        {
            PC = valC;
        }
        else if ((icode == 9) && (ifun == 0))
        {
            if (status != 3) PC = valM;
        }
        else if ((icode == 10) && (ifun == 0))
        {
            PC = valP;
        }
        else if ((icode == 11) && (ifun == 0))
        {
            PC = valP;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::print(int &icode, int &ifun, int &PCprint, int &PC, int &count, unsigned char data[])
{
    printf("pc=%03X", PCprint );
    cout << ": step " <<  hex << count << ": ";
    if ((icode == 0) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(33) << "| HALT";
    }
    else if ((icode == 1) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(32) << "| NOP";
    }
    else if ((icode == 2) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| MOV";
    }
    else if ((icode == 3) && (ifun == 0))
    {
        int i = 0;
        while (i < 6) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(10) << "| MOV";
    }
    else if ((icode == 4) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| LDR";
    }
    else if ((icode == 4) && (ifun == 1))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| STR";
    }
    else if ((icode == 5) && (ifun == 0))
    {
        int i = 0;
        while (i < 6) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(10) << "| LDR";
    }
    else if ((icode == 5) && (ifun == 1))
    {
        int i = 0;
        while (i < 6) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(10) << "| STR";
    }
    else if ((icode == 6) && ((ifun >= 0) && (ifun <= 3))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        
        switch(ifun) {
            case 0 : cout << setw(28) << "| ADD";
                break;
            case 1 : cout << setw(28) << "| SUB";
                break;
            case 2 : cout << setw(28) << "| AND";
                break;
            case 3 : cout << setw(28) << "| EOR";
                break;
            default: cout << "INVALID OPERATION";
        }
    }
    else if ((icode == 7) && ((ifun >= 0) && (ifun <= 14))
    {
        int i = 0;
        while (i < 5) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        
        switch(ifun) {
            case 0 : cout << setw(14) << "| BEQ";
                break;
            case 1 : cout << setw(14) << "| BNE";
                break;
            case 2 : cout << setw(14) << "| BCS";
                break;
            case 3 : cout << setw(14) << "| BCC";
                break;
            case 4 : cout << setw(14) << "| BMI";
                break;
            case 5 : cout << setw(14) << "| BPL";
                break;
            case 6 : cout << setw(14) << "| BVS";
                break;
            case 7 : cout << setw(14) << "| BVC";
                break;
            case 8 : cout << setw(14) << "| BHI";
                break;
            case 9 : cout << setw(14) << "| BLS";
                break;
            case 10 : cout << setw(14) << "| BGE";
                break;
            case 11 : cout << setw(14) << "| BLT";
                break;
            case 12 : cout << setw(14) << "| BGT";
                break;
            case 13 : cout << setw(14) << "| BLE";
                break;
            case 14 : cout << setw(12) << "| B";
                break;
            default : cout << "INVALID OPERATION";
        }
    }
    else if ((icode == 8) && (ifun == 0))
    {
        int i = 0;
        while (i < 5) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(15) << "| CALL";
    }
    else if ((icode == 9) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(32) << "| RET";
    }
    else if ((icode == 10) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(29) << "| PUSH";
    }
    else if ((icode == 11) && (ifun == 0))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| POP";
    }
    else
    {
        cout << "INVALID INSTRUCTION: ";
        printf("0x%02X", data[PCprint]);
        PCprint = PCprint + 1;
    }
    count++;
    PCprint = PC;
    cout << endl;
}

void yarp_sim::print_change(int &PC, int &count, unsigned char data[], unsigned char datacopy[])
{
    cout << "Stopped in " << --count << " steps at PC=";
    printf("0x%03X", PC);
    cout << ". Status ";
    if (status == 1)cout << "'AOK'";
    else if (status == 2)cout << "'HLT'";
    else if (status == 3)cout << "'ADR'";
    else if (status == 4)cout << "'INS'";
    cout << ", CC: N=" << flag.N << " Z=" << flag.Z << " C=" << flag.C << " V=" << flag.V << "." << endl;
    cout << "Changes to registers:" << endl;
    for (int i = 0; i < 8; i++)
    {
        if (R[i] != 0)
        {
            // if changes exist betweeen register and starting state of the register (that is 0) print change
            cout << "r" << i << ": ";
            printf("%08X", 0);
            printf(" -> %08X", R[i]);
            cout << endl;
        }
    }
    cout << "\n\n";
    cout << "Changes to memory:" << endl;
    for (int j = 0; j < 1024; j++)
    {
        if (data[j] != datacopy[j])
        {
            // if change exist between data at end of run and origin copy of data (datacopy) print change.
            printf("0x%03X", j);
            cout << ": ";
            printf("0x%08X", datacopy[j]);
            printf(" -> 0x%08X", data[j]);
            cout << endl;
        }
    }
}

*/


//
//  yarp_sim.cpp
//  yarp-dump
//
//  Created by Christian John on 2017-11-28.
//  Copyright © 2017 Christian John. All rights reserved.
//

#include "yarp.h"
yarp_sim::yarp_sim()
{
    for (int i = 0; i < 8; i++)
    {
        R[i] = 0;
    }
    status = 1;        // default status state 'AOK'
}

void yarp_sim::fetch(int &icode, int &ifun, int &rA, int &rB , int &valC, int &valP, int &PC, unsigned char data[])
{
    icode = data[PC] >> 4;                  // retrive first four bits
    ifun = data[PC] & 0xF;                  // retrive second four bits
    
    if (icode == 0 & ifun == 0)
    {
        status = 2;
        valP = PC + 1;
    }
    else if (icode == 1 & ifun == 0)
    {
        valP = PC + 1;
    }
    else if (icode == 2 & ifun == 0)
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if (icode == 3 & ifun == 0)
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        byte1 = i + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 6;
    }
    else if (icode == 4 & ifun == 0)
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if (icode == 4 & ifun == 1)
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if (icode == 5 & ifun == 0)
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        byte1 = i + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 6;
    }
    else if (icode == 5 & ifun == 1)
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        byte1 = i + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 6;
    }
    else if ((icode == 6) & (ifun >= 0 & ifun <= 14))
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        byte1 = PC + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 5;
    }
    else if (icode == 8 & ifun == 0)
    {
        // converting little endian to big endian
        int byte1, byte2, byte3, byte4;
        byte1 = PC + 1;
        byte2 = byte1 + 1;
        byte3 = byte2 + 1;
        byte4 = byte3 + 1;
        valC = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        valP = PC + 5;
    }
    else if (icode == 9 & ifun == 0)
    {
        valP = PC + 1;
    }
    else if (icode == 10 & ifun == 0)
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else if (icode == 11 & ifun == 0)
    {
        int i = PC + 1;
        rA = data[i] >> 4;                   // retrive first four bits
        rB = data[i] & 0xF;                  // retrive second four bits
        valP = PC + 2;
    }
    else
        status = 4;                          // update value to the status of 4 which stands for 'INS'
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::decode(int &icode, int &ifun, int &rA, int &rB , int &valA, int &valB)
{
    if (icode == 0 & ifun == 0)
    {
    }
    else if (icode == 1 & ifun == 0)
    {
    }
    else if (icode == 2 & ifun == 0)
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if (icode == 3 & ifun == 0)
    {
        
    }
    else if (icode == 4 & ifun == 0)
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if (icode == 4 & ifun == 1)
    {
        rA = (rA==15) ? 7 : rA;
        rB = (rB==15) ? 7 : rB;
        valA = R[rA];
        valB = R[rB];
    }
    else if (icode == 5 & ifun == 0)
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if (icode == 5 & ifun == 1)
    {
        rA = (rA==15) ? 7 : rA;
        rB = (rB==15) ? 7 : rB;
        valA = R[rA];
        valB = R[rB];
    }
    else if ((icode == 6) & (ifun >= 0 & ifun <= 14))
    {
        rA = (rA==15) ? 7 : rA;
        rB = (rB==15) ? 7 : rB;
        valA = R[rA];
        valB = R[rB];
    }
    else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
    {
        
    }
    else if (icode == 8 & ifun == 0)
    {
        rB = (rB==15) ? 7 : rB;
        valB = R[rB];
    }
    else if (icode == 9 & ifun == 0)
    {
        valA = R[7];
        valB = R[7];
    }
    else if (icode == 10 & ifun == 0)
    {
        rA = (rA==15) ? 7 : rA;
        valA = R[rA];
        valB = R[7];
    }
    else if (icode == 11 & ifun == 0)
    {
        valA = R[7];
        valB = R[7];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::execute(int &icode, int &ifun, int &valA, int &valB, int &valE, int &valC, bool &cnd)
{
    
    if (icode == 0 & ifun == 0)
    {
    }
    else if (icode == 1 & ifun == 0)
    {
    }
    else if (icode == 2 & ifun == 0)
    {
        valE = 0 + valB;
    }
    else if (icode == 3 & ifun == 0)
    {
        valE = 0 + valC;
    }
    else if (icode == 4 & ifun == 0)
    {
        valE = valB;
    }
    else if (icode == 4 & ifun == 1)
    {
        valE = valB;
    }
    else if (icode == 5 & ifun == 0)
    {
        valE = valB + valC;
    }
    else if (icode == 5 & ifun == 1)
    {
        valE = valB + valC;
    }
    else if ((icode == 6) & (ifun >= 0 & ifun <= 14))
    {
        switch(ifun) {
            case 0 :
                valE = valA + valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            case 1 :
                valE = valA - valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            case 2 :
                valE = valA & valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            case 3 :
                valE = valA ^ valB;
                yarp_sim::setflag(ifun, valA, valB, valE);          //setting conditional codes
                break;
            default :
                cout << setw(28) << "INVALID OPERATION";
        }
    }
    else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
    {
        cnd = yarp_sim::cond(ifun);                                 // getting boolean value for validity of operation
    }
    else if (icode == 8 & ifun == 0)
    {
        valE = valB + (-4);
    }
    else if (icode == 9 & ifun == 0)
    {
        valE = valB + 4;
    }
    else if (icode == 10 & ifun == 0)
    {
        valE = valB + (-4);
    }
    else if (icode == 11 & ifun == 0)
    {
        valE = valB + 4;
    }
}

void yarp_sim::setflag(int &ifun, int &valA, int &valB, int &valE)
{
    if (ifun == 1)
        valB = -valB;
    
    //Overflow Flag. The most recent operation caused a two’s-complement overflow—either negative or positive.
    flag.V = (valA < 0 == valB < 0) && (valE < 0 != valA < 0);
    flag.Z = (valE == 0); //Zero Flag. The most recent operation yielded zero.
    flag.N = (valE < 0); //Negative Flag. The most recent operation yielded a negative value.
    //Carry Flag. The most recent operation generated a carry out of the most significant bit. Used to detect overflow for unsigned operations.
    flag.C = (unsigned) valE < (unsigned) valA;
    
    if (ifun == 1)
        valB = -valB;
}

bool yarp_sim::cond(int &ifun)
{
    switch(ifun) {
        case 0 :
            if (flag.Z) return true;
            else return false;
            break;
        case 1 :
            if (!flag.Z) return true;
            else return false;
            break;
        case 2 :
            if (flag.C) return true;
            else return false;
            break;
        case 3 :
            if (!flag.C) return true;
            else return false;
            break;
        case 4 :
            if (flag.N) return true;
            else return false;
            break;
        case 5 :
            if (!flag.N) return true;
            else return false;
            break;
        case 6 :
            if (flag.V) return true;
            else return false;
            break;
        case 7 :
            if (!flag.V) return true;
            else return false;
            break;
        case 8 :
            if (flag.C && !flag.Z) return true;
            else return false;
            break;
        case 9 :
            if (!flag.C || flag.Z) return true;
            else return false;
            break;
        case 10 :
            if (flag.N == flag.V) return true;
            else return false;
            break;
        case 11 :
            if (flag.N != flag.V) return true;
            else return false;
            break;
        case 12 :
            if (!flag.Z && (flag.N == flag.V)) return true;
            else return false;
            break;
        case 13 :
            if (!flag.Z && (flag.N != flag.V)) return true;
            else return false;
            break;
        case 14 :
            return true;
            break;
        default :
            return false;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::memory(int &icode, int &ifun, int &valA, int &valE, int &valC, int &valM, int &valP, unsigned char data[])
{
    if (icode == 0 & ifun == 0)
    {
    }
    else if (icode == 1 & ifun == 0)
    {
    }
    else if (icode == 2 & ifun == 0)
    {
    }
    else if (icode == 3 & ifun == 0)
    {
    }
    else if (icode == 4 & ifun == 0)
    {
        if (valE < 0 || valE > 1020) status = 3;
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
    else if (icode == 4 & ifun == 1)
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valA & 0x000000FF);
            data[byte2] = (valA & 0x0000FF00);
            data[byte3] = (valA & 0x00FF0000);
            data[byte4] = (valA & 0xFF000000);
        }
    }
    else if (icode == 5 & ifun == 0)
    {
        if (valE < 0 || valE > 1020) status = 3;         // check to see if the memory can be accessed
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
    else if (icode == 5 & ifun == 1)
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valA & 0x000000FF);
            data[byte2] = (valA & 0x0000FF00);
            data[byte3] = (valA & 0x00FF0000);
            data[byte4] = (valA & 0xFF000000);
        }
    }
    else if ((icode == 6) & (ifun >= 0 & ifun <= 14))
    {
    }
    else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
    {
    }
    else if (icode == 8 & ifun == 0)
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valP & 0x000000FF);
            data[byte2] = (valP & 0x0000FF00);
            data[byte3] = (valP & 0x00FF0000);
            data[byte4] = (valP & 0xFF000000);
        }
    }
    else if (icode == 9 & ifun == 0)
    {
        if (valA < 0 || valA > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valA;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
    else if (icode == 10 & ifun == 0)
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting big endian to little endian
            int byte1, byte2, byte3, byte4;
            byte1 = valE;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            
            data[byte1] = (valA & 0x000000FF);
            data[byte2] = (valA & 0x0000FF00);
            data[byte3] = (valA & 0x00FF0000);
            data[byte4] = (valA & 0xFF000000);
        }
    }
    else if (icode == 11 & ifun == 0)
    {
        if (valE < 0 || valE > 1020) status = 3;        // check to see if the memory can be accessed
        else
        {
            // converting little endian to big endian
            int byte1, byte2, byte3, byte4;
            byte1 = valA;
            byte2 = byte1 + 1;
            byte3 = byte2 + 1;
            byte4 = byte3 + 1;
            valM = (data[byte1] | (data[byte2] << 8) | (data[byte3] << 16) | (data[byte4] << 24));
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::write_back(int &icode, int &ifun, int &rA, int &valE, int &valM, unsigned char data[])
{
    if (icode == 0 & ifun == 0)
    {
    }
    else if (icode == 1 & ifun == 0)
    {
    }
    else if (icode == 2 & ifun == 0)
    {
        R[rA] = valE;
    }
    else if (icode == 3 & ifun == 0)
    {
        R[rA] = valE;
    }
    else if (icode == 4 & ifun == 0)
    {
        if (status != 3) R[rA] = valM;
    }
    else if (icode == 4 & ifun == 1)
    {
    }
    else if (icode == 5 & ifun == 0)
    {
        if (status != 3) R[rA] = valM;
    }
    else if (icode == 5 & ifun == 1)
    {
    }
    else if ((icode == 6) & (ifun >= 0 & ifun <= 14))
    {
        R[rA] = valE;
    }
    else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
    {
        
    }
    else if (icode == 8 & ifun == 0)
    {
        R[7] = valE;
    }
    else if (icode == 9 & ifun == 0)
    {
        R[7] = valE;
    }
    else if (icode == 10 & ifun == 0)
    {
        R[7] = valE;
    }
    else if (icode == 11 & ifun == 0)
    {
        if (status != 3)
        {
            R[7] = valE;
            R[rA] = valM;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::PCupdate(int &icode, int &ifun, int &valC, int &valM, int &valP, int &PC, bool &cnd)
{
    if (status == 1)
    {
        if (icode == 0 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 1 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 2 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 3 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 4 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 4 & ifun == 1)
        {
            PC = valP;
        }
        else if (icode == 5 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 5 & ifun == 1)
        {
            PC = valP;
        }
        else if ((icode == 6) & (ifun >= 0 & ifun <= 14))
        {
            PC = valP;
        }
        else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
        {
            if (valC < 0 || valC > 1020) status = 3;                // if out_of_bounds update status to 3 'ADR' read/write of illegal address
            else
                PC = cnd ? valC : valP;                             // else updates condition depending on cnd: if true PC = valC else PC = valP
        }
        else if (icode == 8 & ifun == 0)
        {
            PC = valC;
        }
        else if (icode == 9 & ifun == 0)
        {
            if (status != 3) PC = valM;
        }
        else if (icode == 10 & ifun == 0)
        {
            PC = valP;
        }
        else if (icode == 11 & ifun == 0)
        {
            PC = valP;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
void yarp_sim::print(int &icode, int &ifun, int &PCprint, int &PC, int &count, unsigned char data[])
{
    printf("pc=%03X", PCprint );
    cout << ": step " <<  hex << count << ": ";
    if (icode == 0 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(33) << "| HALT";
    }
    else if (icode == 1 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(32) << "| NOP";
    }
    else if (icode == 2 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| MOV";
    }
    else if (icode == 3 & ifun == 0)
    {
        int i = 0;
        while (i < 6) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(10) << "| MOV";
    }
    else if (icode == 4 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| LDR";
    }
    else if (icode == 4 & ifun == 1)
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| STR";
    }
    else if (icode == 5 & ifun == 0)
    {
        int i = 0;
        while (i < 6) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(10) << "| LDR";
    }
    else if (icode == 5 & ifun == 1)
    {
        int i = 0;
        while (i < 6) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(10) << "| STR";
    }
    else if ((icode == 6) & (ifun >= 0 & ifun <= 3))
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        
        switch(ifun) {
            case 0 : cout << setw(28) << "| ADD";
                break;
            case 1 : cout << setw(28) << "| SUB";
                break;
            case 2 : cout << setw(28) << "| AND";
                break;
            case 3 : cout << setw(28) << "| EOR";
                break;
            default: cout << "INVALID OPERATION";
        }
    }
    else if ((icode == 7) & (ifun >= 0 & ifun <= 14))
    {
        int i = 0;
        while (i < 5) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        
        switch(ifun) {
            case 0 : cout << setw(14) << "| BEQ";
                break;
            case 1 : cout << setw(14) << "| BNE";
                break;
            case 2 : cout << setw(14) << "| BCS";
                break;
            case 3 : cout << setw(14) << "| BCC";
                break;
            case 4 : cout << setw(14) << "| BMI";
                break;
            case 5 : cout << setw(14) << "| BPL";
                break;
            case 6 : cout << setw(14) << "| BVS";
                break;
            case 7 : cout << setw(14) << "| BVC";
                break;
            case 8 : cout << setw(14) << "| BHI";
                break;
            case 9 : cout << setw(14) << "| BLS";
                break;
            case 10 : cout << setw(14) << "| BGE";
                break;
            case 11 : cout << setw(14) << "| BLT";
                break;
            case 12 : cout << setw(14) << "| BGT";
                break;
            case 13 : cout << setw(14) << "| BLE";
                break;
            case 14 : cout << setw(12) << "| B";
                break;
            default : cout << "INVALID OPERATION";
        }
    }
    else if (icode == 8 & ifun == 0)
    {
        int i = 0;
        while (i < 5) {
            printf("%02X", data[PCprint]);
            printf("  ");
            PCprint++; i++;
        }
        cout << setw(15) << "| CALL";
    }
    else if (icode == 9 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(32) << "| RET";
    }
    else if (icode == 10 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(29) << "| PUSH";
    }
    else if (icode == 11 & ifun == 0)
    {
        printf("%02X", data[PCprint]);
        printf("  ");
        PCprint++;
        printf("%02X", data[PCprint]);
        PCprint = PCprint + 1;
        cout << setw(28) << "| POP";
    }
    else
    {
        cout << "INVALID INSTRUCTION: ";
        printf("0x%02X", data[PCprint]);
        PCprint = PCprint + 1;
    }
    count++;
    PCprint = PC;
    cout << endl;
}

void yarp_sim::print_change(int &PC, int &count, unsigned char data[], unsigned char datacopy[])
{
    cout << "Stopped in " << --count << " steps at PC=";
    printf("0x%03X", PC);
    cout << ". Status ";
    if (status == 1)cout << "'AOK'";
    else if (status == 2)cout << "'HLT'";
    else if (status == 3)cout << "'ADR'";
    else if (status == 4)cout << "'INS'";
    cout << ", CC: N=" << flag.N << " Z=" << flag.Z << " C=" << flag.C << " V=" << flag.V << "." << endl;
    cout << "Changes to registers:" << endl;
    for (int i = 0; i < 8; i++)
    {
        if (R[i] != 0)
        {
            // if changes exist betweeen register and starting state of the register (that is 0) print change
            cout << "r" << i << ": ";
            printf("%08X", 0);
            printf(" -> %08X", R[i]);
            cout << endl;
        }
    }
    cout << "\n\n";
    cout << "Changes to memory:" << endl;
    for (int j = 0; j < 1024; j++)
    {
        if (data[j] != datacopy[j])
        {
            // if change exist between data at end of run and origin copy of data (datacopy) print change.
            printf("0x%03X", j);
            cout << ": ";
            printf("0x%08X", datacopy[j]);
            printf(" -> 0x%08X", data[j]);
            cout << endl;
        }
    }
}


