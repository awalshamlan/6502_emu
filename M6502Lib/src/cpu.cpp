#include "M6502/cpu.h"
#include "stdio.h"

CPU::CPU() {
  InstructionTable.fill(&CPU::OpUnhandled);
#define OPCODE(name, value) InstructionTable[INS_##name] = &CPU::name;
#include "M6502/opcodes.def"
#undef OPCODE
}

void CPU::Connect(MEM &memory) { Memory = &memory; }

u32 CPU::Exec(u32 cycles) {
  Cycles = cycles;
  const u32 cyclesRequested = cycles;
  while (Cycles > 0) {
    Byte opcode = FetchByte();
    Handler handler = InstructionTable[opcode];
    (this->*handler)();
  }
  return cyclesRequested - Cycles;
}

void CPU::Reset() {
  ProgramCounter = 0xFFFC;
  StackPointer = 0xFF;
  Status = UNUSED_FLAG;
  A = X = Y = 0x00;
  Memory->Init();
}

void CPU::OpUnhandled() {
  Word opcodeAddress = ProgramCounter - 1;
  Byte opcode = (*Memory)[opcodeAddress];
  fprintf(stderr, "Instruction not handled: 0x%02X at PC=0x%04X\n", opcode,
          opcodeAddress);
  Cycles = 0;
}

void CPU::SetFlag(Byte flag, bool enabled) {
  if (enabled) {
    Status |= flag;
  } else {
    Status &= ~flag;
  }
}

bool CPU::GetFlag(Byte flag) { return (Status & flag) != 0; }

void CPU::SetZN(Byte result) {
  SetFlag(ZERO_FLAG, result == 0);
  SetFlag(NEGATIVE_FLAG, (result & NEGATIVE_FLAG) > 0);
}
