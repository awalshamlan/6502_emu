#include "test_common.h"

using namespace test6502;

TEST_F(CPUFixture, LDAImmediateSetsAAndFlags) {
  mem[0x8000] = 0xA9;
  mem[0x8001] = 0x84;

  u32 cyclesUsed = Run(2);

  EXPECT_EQ(U(cpu.A), 0x84u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8002u);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(cyclesUsed, 2u);
}

TEST_F(CPUFixture, LDXAndLDYImmediateSetRegistersAndFlags) {
  mem[0x8000] = 0xA2; // LDX #$00
  mem[0x8001] = 0x00;
  mem[0x8002] = 0xA0; // LDY #$80
  mem[0x8003] = 0x80;

  u32 cyclesUsed = Run(4);

  EXPECT_EQ(U(cpu.X), 0x00u);
  EXPECT_EQ(U(cpu.Y), 0x80u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8004u);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(cyclesUsed, 4u);
}

TEST_F(CPUFixture, STAZeroPageStoresAWithoutChangingFlags) {
  cpu.A = 0x42;
  cpu.Status = ZERO_FLAG | UNUSED_FLAG;

  mem[0x8000] = 0x85; // STA $44
  mem[0x8001] = 0x44;

  u32 cyclesUsed = Run(3);

  EXPECT_EQ(U(mem[0x0044]), 0x42u);
  EXPECT_EQ(U(cpu.A), 0x42u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8002u);
  ExpectFlag(ZERO_FLAG, true);
  EXPECT_EQ(cyclesUsed, 3u);
}

TEST_F(CPUFixture, STAAbsoluteXStoresAAndUsesFiveCycles) {
  cpu.A = 0x99;
  cpu.X = 0x05;

  mem[0x8000] = 0x9D; // STA $9000,X
  mem[0x8001] = 0x00;
  mem[0x8002] = 0x90;

  u32 cyclesUsed = Run(5);

  EXPECT_EQ(U(mem[0x9005]), 0x99u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8003u);
  EXPECT_EQ(cyclesUsed, 5u);
}

TEST_F(CPUFixture, STXAndSTYStoreCorrectRegisters) {
  cpu.X = 0x12;
  cpu.Y = 0x34;

  mem[0x8000] = 0x86; // STX $10
  mem[0x8001] = 0x10;
  mem[0x8002] = 0x84; // STY $11
  mem[0x8003] = 0x11;

  u32 cyclesUsed = Run(6);

  EXPECT_EQ(U(mem[0x0010]), 0x12u);
  EXPECT_EQ(U(mem[0x0011]), 0x34u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8004u);
  EXPECT_EQ(cyclesUsed, 6u);
}

TEST_F(CPUFixture, TransferInstructionsMoveValuesAndSetFlags) {
  cpu.A = 0x80;

  mem[0x8000] = 0xAA; // TAX
  mem[0x8001] = 0x8A; // TXA
  mem[0x8002] = 0xA8; // TAY
  mem[0x8003] = 0x98; // TYA

  u32 cyclesUsed = Run(8);

  EXPECT_EQ(U(cpu.X), 0x80u);
  EXPECT_EQ(U(cpu.Y), 0x80u);
  EXPECT_EQ(U(cpu.A), 0x80u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8004u);
  ExpectFlag(NEGATIVE_FLAG, true);
  ExpectFlag(ZERO_FLAG, false);
  EXPECT_EQ(cyclesUsed, 8u);
}

TEST_F(CPUFixture, TXSDoesNotSetFlagsAndTSXDoesSetFlags) {
  cpu.X = 0x00;
  cpu.Status = NEGATIVE_FLAG | UNUSED_FLAG;

  mem[0x8000] = 0x9A; // TXS
  mem[0x8001] = 0xBA; // TSX

  u32 cyclesUsed = Run(4);

  EXPECT_EQ(U(cpu.StackPointer), 0x00u);
  EXPECT_EQ(U(cpu.X), 0x00u);
  ExpectFlag(ZERO_FLAG, true);
  ExpectFlag(NEGATIVE_FLAG, false);
  EXPECT_EQ(cyclesUsed, 4u);
}

TEST_F(CPUFixture, ADCImmediateSetsCarryZeroOverflowNegative) {
  cpu.A = 0x80;

  mem[0x8000] = 0x69; // ADC #$80
  mem[0x8001] = 0x80;

  u32 cyclesUsed = Run(2);

  EXPECT_EQ(U(cpu.A), 0x00u);
  ExpectFlag(CARRY_FLAG, true);
  ExpectFlag(ZERO_FLAG, true);
  ExpectFlag(NEGATIVE_FLAG, false);
  ExpectFlag(OVERFLOW_FLAG, true);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8002u);
  EXPECT_EQ(cyclesUsed, 2u);
}

TEST_F(CPUFixture, AND_EOR_ORAImmediate) {
  cpu.A = 0xF0;

  mem[0x8000] = 0x29; // AND #$CC => C0
  mem[0x8001] = 0xCC;
  mem[0x8002] = 0x49; // EOR #$FF => 3F
  mem[0x8003] = 0xFF;
  mem[0x8004] = 0x09; // ORA #$80 => BF
  mem[0x8005] = 0x80;

  u32 cyclesUsed = Run(6);

  EXPECT_EQ(U(cpu.A), 0xBFu);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8006u);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(cyclesUsed, 6u);
}

TEST_F(CPUFixture, BITZeroPageSetsZFromAAndOperandAndCopiesVAndN) {
  cpu.A = 0x0F;

  mem[0x8000] = 0x24; // BIT $20
  mem[0x8001] = 0x20;
  mem[0x0020] = 0xC0;

  u32 cyclesUsed = Run(3);

  EXPECT_EQ(U(cpu.A), 0x0Fu);
  ExpectFlag(ZERO_FLAG, true);
  ExpectFlag(OVERFLOW_FLAG, true);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x8002u);
  EXPECT_EQ(cyclesUsed, 3u);
}

TEST_F(CPUFixture, LSRAccumulatorShiftsRightAndMovesBitZeroToCarry) {
  cpu.A = 0x03;

  mem[0x8000] = 0x4A; // LSR A

  u32 cyclesUsed = Run(2);

  EXPECT_EQ(U(cpu.A), 0x01u);
  ExpectFlag(CARRY_FLAG, true);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, false);
  EXPECT_EQ(cyclesUsed, 2u);
}

TEST_F(CPUFixture, LSRZeroPageModifiesMemory) {
  mem[0x8000] = 0x46; // LSR $44
  mem[0x8001] = 0x44;
  mem[0x0044] = 0x80;

  u32 cyclesUsed = Run(5);

  EXPECT_EQ(U(mem[0x0044]), 0x40u);
  ExpectFlag(CARRY_FLAG, false);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, false);
  EXPECT_EQ(cyclesUsed, 5u);
}

TEST_F(CPUFixture, CMPImmediateSetsFlagsWithoutChangingA) {
  cpu.A = 0x10;

  mem[0x8000] = 0xC9; // CMP #$20
  mem[0x8001] = 0x20;

  u32 cyclesUsed = Run(2);

  EXPECT_EQ(U(cpu.A), 0x10u);
  ExpectFlag(CARRY_FLAG, false);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(cyclesUsed, 2u);
}

TEST_F(CPUFixture, CPXAndCPYImmediateUseXAndY) {
  cpu.X = 0x20;
  cpu.Y = 0x10;

  mem[0x8000] = 0xE0; // CPX #$10 => C=1,Z=0,N=0
  mem[0x8001] = 0x10;
  mem[0x8002] = 0xC0; // CPY #$20 => C=0,Z=0,N=1
  mem[0x8003] = 0x20;

  u32 cyclesUsed = Run(4);

  EXPECT_EQ(U(cpu.X), 0x20u);
  EXPECT_EQ(U(cpu.Y), 0x10u);
  ExpectFlag(CARRY_FLAG, false);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(cyclesUsed, 4u);
}

TEST_F(CPUFixture, DECAndINCZeroPageModifyMemoryAndSetFlags) {
  mem[0x8000] = 0xC6; // DEC $10: 01 -> 00
  mem[0x8001] = 0x10;
  mem[0x8002] = 0xE6; // INC $11: 7F -> 80
  mem[0x8003] = 0x11;

  mem[0x0010] = 0x01;
  mem[0x0011] = 0x7F;

  u32 cyclesUsed = Run(10);

  EXPECT_EQ(U(mem[0x0010]), 0x00u);
  EXPECT_EQ(U(mem[0x0011]), 0x80u);
  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, true);
  EXPECT_EQ(cyclesUsed, 10u);
}

TEST_F(CPUFixture, BranchTakenForwardAndNotTaken) {
  mem[0x8000] = 0x90; // BCC +2
  mem[0x8001] = 0x02;
  mem[0x8004] = 0xB0; // BCS +2, not taken because C clear
  mem[0x8005] = 0x02;
  mem[0x8006] = 0xEA; // NOP

  cpu.Status &= ~CARRY_FLAG;

  u32 cyclesUsed = Run(5);

  EXPECT_EQ(U(cpu.ProgramCounter), 0x8006u);
  EXPECT_EQ(cyclesUsed, 5u);
}

TEST_F(CPUFixture, BranchTakenBackward) {
  // BNE -2 loops to itself. Run exactly one branch.
  mem[0x8000] = 0xD0;
  mem[0x8001] = 0xFE;

  cpu.Status &= ~ZERO_FLAG;

  u32 cyclesUsed = Run(3);

  EXPECT_EQ(U(cpu.ProgramCounter), 0x8000u);
  EXPECT_EQ(cyclesUsed, 3u);
}

TEST_F(CPUFixture, JMPAbsoluteSetsProgramCounter) {
  mem[0x8000] = 0x4C; // JMP $9000
  mem[0x8001] = 0x00;
  mem[0x8002] = 0x90;

  u32 cyclesUsed = Run(3);

  EXPECT_EQ(U(cpu.ProgramCounter), 0x9000u);
  EXPECT_EQ(cyclesUsed, 3u);
}

TEST_F(CPUFixture, JSRPushesReturnAddressAndJumps) {
  mem[0x8000] = 0x20; // JSR $9000
  mem[0x8001] = 0x00;
  mem[0x8002] = 0x90;

  u32 cyclesUsed = Run(6);

  EXPECT_EQ(U(cpu.ProgramCounter), 0x9000u);
  EXPECT_EQ(U(cpu.StackPointer), 0xFDu);
  EXPECT_EQ(U(mem[0x01FF]), 0x80u);
  EXPECT_EQ(U(mem[0x01FE]), 0x02u);
  EXPECT_EQ(cyclesUsed, 6u);
}

TEST_F(CPUFixture, BRKPushesStatusAndLoadsInterruptVector) {
  cpu.Status = CARRY_FLAG | UNUSED_FLAG;
  WriteWord(mem, 0xFFFE, 0x9000);

  mem[0x8000] = 0x00; // BRK
  mem[0x8001] = 0xEA; // padding byte

  u32 cyclesUsed = Run(7);

  EXPECT_EQ(U(cpu.ProgramCounter), 0x9000u);
  EXPECT_EQ(U(cpu.StackPointer), 0xFCu);

  EXPECT_EQ(U(mem[0x01FF]), 0x80u);
  EXPECT_EQ(U(mem[0x01FE]), 0x02u);

  Byte pushedStatus = mem[0x01FD];
  EXPECT_TRUE((pushedStatus & CARRY_FLAG) != 0);
  EXPECT_TRUE((pushedStatus & UNUSED_FLAG) != 0);
  EXPECT_TRUE((pushedStatus & BREAK_FLAG) != 0);

  ExpectFlag(INTERRUPT_FLAG, true);
  EXPECT_EQ(cyclesUsed, 7u);
}

TEST_F(CPUFixture, NOPOnlyConsumesCycleAndAdvancesPCByOpcodeFetch) {
  mem[0x8000] = 0xEA;

  u32 cyclesUsed = Run(2);

  EXPECT_EQ(U(cpu.ProgramCounter), 0x8001u);
  EXPECT_EQ(cyclesUsed, 2u);
}

TEST_F(CPUFixture, WholeProgramUsesImplementedInstructions) {
  cpu.X = 0x01;
  cpu.Y = 0x02;

  mem[0x8000] = 0x20; // JSR $8100
  mem[0x8001] = 0x00;
  mem[0x8002] = 0x81;

  mem[0x8100] = 0xA9; // LDA #$F0
  mem[0x8101] = 0xF0;

  mem[0x8102] = 0x29; // AND #$CC => C0
  mem[0x8103] = 0xCC;

  mem[0x8104] = 0x69; // ADC #$20 => E0
  mem[0x8105] = 0x20;

  mem[0x8106] = 0x8D; // STA $9000
  mem[0x8107] = 0x00;
  mem[0x8108] = 0x90;

  mem[0x8109] = 0x4A; // LSR A => 70
  mem[0x810A] = 0x09; // ORA #$01 => 71
  mem[0x810B] = 0x01;

  // cycles:
  // JSR abs  6
  // LDA #    2
  // AND #    2
  // ADC #    2
  // STA abs  4
  // LSR A    2
  // ORA #    2
  // total   20
  u32 cyclesUsed = Run(20);

  EXPECT_EQ(U(cpu.A), 0x71u);
  EXPECT_EQ(U(mem[0x9000]), 0xE0u);
  EXPECT_EQ(U(cpu.ProgramCounter), 0x810Cu);
  EXPECT_EQ(U(cpu.StackPointer), 0xFDu);
  EXPECT_EQ(cyclesUsed, 20u);

  ExpectFlag(ZERO_FLAG, false);
  ExpectFlag(NEGATIVE_FLAG, false);
}