#pragma once

#include "mem.h"
#include "types.h"

#include <array>

struct CPU {
  using Handler = void (CPU::*)();

  CPU();

  Word ProgramCounter;
  Byte StackPointer;
  Byte A, X, Y, Status; // Byte registers
  MEM *Memory = nullptr;
  u32 Cycles = 0;

  void Connect(MEM &memory);
  u32 Exec(u32 cycles);
  void Reset();

// OP CODES
#define OPCODE(name, value) static constexpr Byte INS_##name = value;
#include "opcodes.def"
#undef OPCODE
private:
  // Constants
  static constexpr Word STACK_BASE = 0x0100;
  static constexpr Word INTERRUPT_VECTOR = 0xFFFE;

  static constexpr Byte CARRY_FLAG = 0x01;
  static constexpr Byte ZERO_FLAG = 0x02;
  static constexpr Byte INTERRUPT_FLAG = 0x04;
  static constexpr Byte DECIMAL_FLAG = 0x08;
  static constexpr Byte BREAK_FLAG = 0x10;
  static constexpr Byte UNUSED_FLAG = 0x20;
  static constexpr Byte OVERFLOW_FLAG = 0x40;
  static constexpr Byte NEGATIVE_FLAG = 0x80;

  // Addressing helpers
  Byte ReadZeroPageOperand();
  Byte ReadZeroPageXOperand();
  Byte ReadAbsoluteOperand();
  Byte ReadAbsoluteXOperand(bool pageCrossPenalty = true);
  Byte ReadAbsoluteYOperand(bool pageCrossPenalty = true);
  Byte ReadIndexedIndirectOperand();
  Byte ReadIndirectIndexedOperand(bool pageCrossPenalty = true);

  // Instruction Handlers
  std::array<Handler, 256> InstructionTable{};
  void OpUnhandled();
#define OPCODE(name, value) void name();
#include "opcodes.def"
#undef OPCODE

  // Instruction Helpers
  void ADC(Byte operand);
  void AND(Byte operand);
  void LDA(Byte operand);
  void CMP(Byte reg, Byte operand);

  void Branch(bool branchFlag);

  // OP Status Setters
  void ADCSetFlags(Byte oldA, Byte operand, Word result);
  void ANDSetFlags();
  void LDASetFlags();

  // Stack Helpers
  void PushByte(Byte value);
  void PushWord(Word value);

  // Memory Helpers
  // Fetch
  Byte FetchByte();
  Word FetchWord();
  // Read
  Byte ReadByte(Word address);
  Word ReadWord(Word address);
  Word ReadWordFromZeroPage(Word address);

  // Write
  void WriteByte(Word address, Byte value);
  void WriteWord(Word address, Word value);

  // Status Flag Helpers
  void SetFlag(Byte flag, bool value);
  bool GetFlag(Byte flag);
};