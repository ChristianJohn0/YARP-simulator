//
//  main.cpp
//  yarp_sim
//
//  Created by Christian John on 2017-11-16.
//  Copyright © 2017 Christian John. All rights reserved.
//
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "yarp.h"
using namespace std;

int main(int argc, char *argv[])
{
    const int SIZE = 1024;
    unsigned char data[SIZE] = {'0'};
    unsigned char datacopy[SIZE];
    yarp_sim yarp;
    
    int len = 0;
    
    if (argc < 2 or argc > 3)
    {
        printf("Failure usage: <filename> <length>\n");
        return 1;
    }
    
    ifstream is(argv[1]);                   // open file
    if (is.fail())                          // error check: set failbit or badbit error state flags
    {
        cout << argv[1] << ": File is not available or cannot be opened" << endl;
        exit(1);
    }
    
    if (argc == 3)                          // if number is arguments equal 3 then third argument is the
        len = atoi(argv[2]);
    else
        len = 200;
    
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    char c;
    int i = 0;
    while (is.get(c) && !is.eof())      // loop getting single characters
    {
        if (i > /* DISABLES CODE */  (1023))
        {
            cout << "Instruction overflow" << endl;
            exception();
        }
        data[i] = c;
        i++;
    }
    is.close();                         // close file
    
    for (int i = 0; i < 1024; i++)
    {
        datacopy[i] = data[i];
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    int icode, ifun, rA, rB, valA, valB, valM, valC, valP, valE, PC, count, PCprint, temp; bool cnd;
    icode = 0; ifun = 0; rA = 0; rB = 0; valA = 0; valB = 0; valM = 0; valC = 0; valP = 0; valE = 0; PC = 0;
    temp = 0; count = 1; PCprint = 0;
    unsigned int fileSize = i;
    do {
        yarp.fetch(icode, ifun, rA, rB, valC, valP, PC, data);
        yarp.decode(icode, ifun, rA, rB, valA, valB);
        yarp.execute(icode, ifun, valA, valB, valE, valC, cnd);
        yarp.memory(icode, ifun, valA, valE, valC, valM, valP, data);
        yarp.write_back(icode, ifun, rA, valE, valM, data);
        yarp.PCupdate(icode, ifun, valC, valM, valP, PC, cnd);
        yarp.print(icode, ifun, PCprint, PC, count, data);
        
        temp++;
    } while (temp < len && PC < fileSize && (yarp.status == 1));
    yarp.print_change(PC, count, data, datacopy);
    
    return 0;
}


