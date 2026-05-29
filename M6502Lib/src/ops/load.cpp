#include "M6502/cpu.h"

void CPU::LDA(Byte value) {
  A = value;
  SetZN(A);
}

void CPU::LDX(Byte value) {
  X = value;
  SetZN(X);
}

void CPU::LDY(Byte value) {
  Y = value;
  SetZN(Y);
}

void CPU::STA(Word address){
  WriteByte(address, A);
}

void CPU::STX(Word address){
  WriteByte(address, X);
}

void CPU::STY(Word address){
  WriteByte(address, Y);
}

void CPU::LDA_IM() { LDA(FetchByte()); }
void CPU::LDA_ZP() { LDA(ReadZeroPageOperand()); }
void CPU::LDA_ZPX() { LDA(ReadZeroPageXOperand()); }
void CPU::LDA_ABS() { LDA(ReadAbsoluteOperand()); }
void CPU::LDA_ABSX() { LDA(ReadAbsoluteXOperand()); }
void CPU::LDA_ABSY() { LDA(ReadAbsoluteYOperand()); }
void CPU::LDA_INDX() { LDA(ReadIndexedIndirectOperand()); }
void CPU::LDA_INDY() { LDA(ReadIndirectIndexedOperand()); }

void CPU::LDX_IM() { LDX(FetchByte()); }
void CPU::LDX_ZP() { LDX(ReadZeroPageOperand()); }
void CPU::LDX_ZPY() { LDX(ReadZeroPageYOperand()); }
void CPU::LDX_ABS() { LDX(ReadAbsoluteOperand()); }
void CPU::LDX_ABSY() { LDX(ReadAbsoluteYOperand()); }

void CPU::LDY_IM() { LDY(FetchByte()); }
void CPU::LDY_ZP() { LDY(ReadZeroPageOperand()); }
void CPU::LDY_ZPX() { LDY(ReadZeroPageXOperand()); }
void CPU::LDY_ABS() { LDY(ReadAbsoluteOperand()); }
void CPU::LDY_ABSX() { LDY(ReadAbsoluteXOperand()); }

void CPU::STA_ZP(){STA(FetchByte());}
void CPU::STA_ZPX(){STA(ResolveZeroPageXAddress());}
void CPU::STA_ABS(){
  Word address = FetchWord();
  STA(address);
}
void CPU::STA_ABSX(){
  Word address = ResolveAbsoluteXAddress();
  STA(address);
}
void CPU::STA_ABSY(){
  Word address = ResolveAbsoluteYAddress();
  STA(address);
}
void CPU::STA_INDX(){STA(ResolveIndexedIndirectAddress());}
void CPU::STA_INDY(){STA(ResolveIndirectIndexedAddress());}

void CPU::STX_ZP(){STX(FetchByte());}
void CPU::STX_ZPY(){STX(ResolveZeroPageYAddress());}
void CPU::STX_ABS(){STX(FetchWord());}

void CPU::STY_ZP(){STY(FetchByte());}
void CPU::STY_ZPX(){STY(ResolveZeroPageXAddress());}
void CPU::STY_ABS(){STY(FetchWord());}
