#include "M6502/cpu.h"

void CPU::PHA(){
    PushByte(A);
    Cycles--;
}

void CPU::PHP(){
    PushByte(Status);
    Cycles--;
}

void CPU::PLA(){
    Cycles--;
    Cycles--;
    A = PullByte();
    SetZN(A);
}

void CPU::PLP(){
    Cycles--;
    Cycles--;
    Status = PullByte();
}

