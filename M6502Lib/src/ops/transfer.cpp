#include "M6502/cpu.h"

void CPU::TAX(){
  X = A;
  Cycles--;
  SetZN(X);
}

void CPU::TAY(){
  Y = A;
  Cycles--;
  SetZN(Y);
}

void CPU::TSX(){
  X = StackPointer;
  Cycles--;
  SetZN(X);
}

void CPU::TXA(){
  A = X;
  Cycles--;
  SetZN(A);
}

void CPU::TXS(){
  StackPointer = X;
  Cycles--;
}

void CPU::TYA(){
  A = Y;
  Cycles--;
  SetZN(A);
}

