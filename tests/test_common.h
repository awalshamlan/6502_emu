#pragma once

#include "M6502/cpu.h"
#include "M6502/mem.h"
#include "M6502/types.h"

#include <gtest/gtest.h>

namespace test6502 {

static constexpr Byte CARRY_FLAG = 0x01;
static constexpr Byte ZERO_FLAG = 0x02;
static constexpr Byte INTERRUPT_FLAG = 0x04;
static constexpr Byte DECIMAL_FLAG = 0x08;
static constexpr Byte BREAK_FLAG = 0x10;
static constexpr Byte UNUSED_FLAG = 0x20;
static constexpr Byte OVERFLOW_FLAG = 0x40;
static constexpr Byte NEGATIVE_FLAG = 0x80;

inline unsigned U(Byte value) { return static_cast<unsigned>(value); }
inline unsigned U(Word value) { return static_cast<unsigned>(value); }

inline void WriteWord(MEM &mem, Word address, Word value) {
  mem[address] = static_cast<Byte>(value & 0xFF);
  mem[address + 1] = static_cast<Byte>((value >> 8) & 0xFF);
}

class CPUFixture : public ::testing::Test {
protected:
  CPU cpu;
  MEM mem;

  void SetUp() override {
    cpu.Connect(mem);
    cpu.Reset();
    cpu.ProgramCounter = 0x8000;
  }

  u32 Run(u32 cycles) { return cpu.Exec(cycles); }

  bool Flag(Byte flag) const { return (cpu.Status & flag) != 0; }

  void ExpectFlag(Byte flag, bool expected) const {
    EXPECT_EQ(Flag(flag), expected);
  }
};

} // namespace test6502