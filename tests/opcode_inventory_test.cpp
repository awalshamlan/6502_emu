#include "test_common.h"

#include <string>
#include <vector>

using namespace test6502;

struct OpcodeInfo {
  Byte opcode;
  const char *name;
  const char *mode;
  int cycles;
  bool pageCrossPossible;
  bool implemented;
};

static std::vector<OpcodeInfo> OfficialOpcodes() {
  return {
      // ADC
      {0x69, "ADC", "IMM", 2, false, true},
      {0x65, "ADC", "ZP", 3, false, true},
      {0x75, "ADC", "ZPX", 4, false, true},
      {0x6D, "ADC", "ABS", 4, false, true},
      {0x7D, "ADC", "ABSX", 4, true, true},
      {0x79, "ADC", "ABSY", 4, true, true},
      {0x61, "ADC", "INDX", 6, false, true},
      {0x71, "ADC", "INDY", 5, true, true},

      // AND
      {0x29, "AND", "IMM", 2, false, true},
      {0x25, "AND", "ZP", 3, false, true},
      {0x35, "AND", "ZPX", 4, false, true},
      {0x2D, "AND", "ABS", 4, false, true},
      {0x3D, "AND", "ABSX", 4, true, true},
      {0x39, "AND", "ABSY", 4, true, true},
      {0x21, "AND", "INDX", 6, false, true},
      {0x31, "AND", "INDY", 5, true, true},

      // ASL
      {0x0A, "ASL", "ACC", 2, false, false},
      {0x06, "ASL", "ZP", 5, false, false},
      {0x16, "ASL", "ZPX", 6, false, false},
      {0x0E, "ASL", "ABS", 6, false, false},
      {0x1E, "ASL", "ABSX", 7, false, false},

      // Branches
      {0x90, "BCC", "REL", 2, true, true},
      {0xB0, "BCS", "REL", 2, true, true},
      {0xF0, "BEQ", "REL", 2, true, true},
      {0x30, "BMI", "REL", 2, true, true},
      {0xD0, "BNE", "REL", 2, true, true},
      {0x10, "BPL", "REL", 2, true, true},
      {0x50, "BVC", "REL", 2, true, true},
      {0x70, "BVS", "REL", 2, true, true},

      // BIT / BRK
      {0x24, "BIT", "ZP", 3, false, true},
      {0x2C, "BIT", "ABS", 4, false, true},
      {0x00, "BRK", "IMPLIED", 7, false, true},

      // Status flags
      {0x18, "CLC", "IMPLIED", 2, false, false},
      {0xD8, "CLD", "IMPLIED", 2, false, false},
      {0x58, "CLI", "IMPLIED", 2, false, false},
      {0xB8, "CLV", "IMPLIED", 2, false, false},
      {0x38, "SEC", "IMPLIED", 2, false, false},
      {0xF8, "SED", "IMPLIED", 2, false, false},
      {0x78, "SEI", "IMPLIED", 2, false, false},

      // CMP
      {0xC9, "CMP", "IMM", 2, false, true},
      {0xC5, "CMP", "ZP", 3, false, true},
      {0xD5, "CMP", "ZPX", 4, false, true},
      {0xCD, "CMP", "ABS", 4, false, true},
      {0xDD, "CMP", "ABSX", 4, true, true},
      {0xD9, "CMP", "ABSY", 4, true, true},
      {0xC1, "CMP", "INDX", 6, false, true},
      {0xD1, "CMP", "INDY", 5, true, true},

      // CPX
      {0xE0, "CPX", "IMM", 2, false, true},
      {0xE4, "CPX", "ZP", 3, false, true},
      {0xEC, "CPX", "ABS", 4, false, true},

      // CPY
      {0xC0, "CPY", "IMM", 2, false, true},
      {0xC4, "CPY", "ZP", 3, false, true},
      {0xCC, "CPY", "ABS", 4, false, true},

      // DEC / DEX / DEY
      {0xC6, "DEC", "ZP", 5, false, true},
      {0xD6, "DEC", "ZPX", 6, false, true},
      {0xCE, "DEC", "ABS", 6, false, true},
      {0xDE, "DEC", "ABSX", 7, false, true},
      {0xCA, "DEX", "IMPLIED", 2, false, true},
      {0x88, "DEY", "IMPLIED", 2, false, true},

      // EOR
      {0x49, "EOR", "IMM", 2, false, true},
      {0x45, "EOR", "ZP", 3, false, true},
      {0x55, "EOR", "ZPX", 4, false, true},
      {0x4D, "EOR", "ABS", 4, false, true},
      {0x5D, "EOR", "ABSX", 4, true, true},
      {0x59, "EOR", "ABSY", 4, true, true},
      {0x41, "EOR", "INDX", 6, false, true},
      {0x51, "EOR", "INDY", 5, true, true},

      // INC / INX / INY
      {0xE6, "INC", "ZP", 5, false, true},
      {0xF6, "INC", "ZPX", 6, false, true},
      {0xEE, "INC", "ABS", 6, false, true},
      {0xFE, "INC", "ABSX", 7, false, true},
      {0xE8, "INX", "IMPLIED", 2, false, true},
      {0xC8, "INY", "IMPLIED", 2, false, true},

      // JMP / JSR
      {0x4C, "JMP", "ABS", 3, false, true},
      {0x6C, "JMP", "IND", 5, false, true},
      {0x20, "JSR", "ABS", 6, false, true},

      // LDA
      {0xA9, "LDA", "IMM", 2, false, true},
      {0xA5, "LDA", "ZP", 3, false, true},
      {0xB5, "LDA", "ZPX", 4, false, true},
      {0xAD, "LDA", "ABS", 4, false, true},
      {0xBD, "LDA", "ABSX", 4, true, true},
      {0xB9, "LDA", "ABSY", 4, true, true},
      {0xA1, "LDA", "INDX", 6, false, true},
      {0xB1, "LDA", "INDY", 5, true, true},

      // LDX
      {0xA2, "LDX", "IMM", 2, false, true},
      {0xA6, "LDX", "ZP", 3, false, true},
      {0xB6, "LDX", "ZPY", 4, false, true},
      {0xAE, "LDX", "ABS", 4, false, true},
      {0xBE, "LDX", "ABSY", 4, true, true},

      // LDY
      {0xA0, "LDY", "IMM", 2, false, true},
      {0xA4, "LDY", "ZP", 3, false, true},
      {0xB4, "LDY", "ZPX", 4, false, true},
      {0xAC, "LDY", "ABS", 4, false, true},
      {0xBC, "LDY", "ABSX", 4, true, true},

      // LSR
      {0x4A, "LSR", "ACC", 2, false, true},
      {0x46, "LSR", "ZP", 5, false, true},
      {0x56, "LSR", "ZPX", 6, false, true},
      {0x4E, "LSR", "ABS", 6, false, true},
      {0x5E, "LSR", "ABSX", 7, false, true},

      // NOP
      {0xEA, "NOP", "IMPLIED", 2, false, true},

      // ORA
      {0x09, "ORA", "IMM", 2, false, true},
      {0x05, "ORA", "ZP", 3, false, true},
      {0x15, "ORA", "ZPX", 4, false, true},
      {0x0D, "ORA", "ABS", 4, false, true},
      {0x1D, "ORA", "ABSX", 4, true, true},
      {0x19, "ORA", "ABSY", 4, true, true},
      {0x01, "ORA", "INDX", 6, false, true},
      {0x11, "ORA", "INDY", 5, true, true},

      // Stack
      {0x48, "PHA", "IMPLIED", 3, false, false},
      {0x08, "PHP", "IMPLIED", 3, false, false},
      {0x68, "PLA", "IMPLIED", 4, false, false},
      {0x28, "PLP", "IMPLIED", 4, false, false},

      // ROL
      {0x2A, "ROL", "ACC", 2, false, false},
      {0x26, "ROL", "ZP", 5, false, false},
      {0x36, "ROL", "ZPX", 6, false, false},
      {0x2E, "ROL", "ABS", 6, false, false},
      {0x3E, "ROL", "ABSX", 7, false, false},

      // ROR
      {0x6A, "ROR", "ACC", 2, false, false},
      {0x66, "ROR", "ZP", 5, false, false},
      {0x76, "ROR", "ZPX", 6, false, false},
      {0x6E, "ROR", "ABS", 6, false, false},
      {0x7E, "ROR", "ABSX", 7, false, false},

      // RTI / RTS
      {0x40, "RTI", "IMPLIED", 6, false, false},
      {0x60, "RTS", "IMPLIED", 6, false, false},

      // SBC
      {0xE9, "SBC", "IMM", 2, false, false},
      {0xE5, "SBC", "ZP", 3, false, false},
      {0xF5, "SBC", "ZPX", 4, false, false},
      {0xED, "SBC", "ABS", 4, false, false},
      {0xFD, "SBC", "ABSX", 4, true, false},
      {0xF9, "SBC", "ABSY", 4, true, false},
      {0xE1, "SBC", "INDX", 6, false, false},
      {0xF1, "SBC", "INDY", 5, true, false},

      // Store
      {0x85, "STA", "ZP", 3, false, true},
      {0x95, "STA", "ZPX", 4, false, true},
      {0x8D, "STA", "ABS", 4, false, true},
      {0x9D, "STA", "ABSX", 5, false, true},
      {0x99, "STA", "ABSY", 5, false, true},
      {0x81, "STA", "INDX", 6, false, true},
      {0x91, "STA", "INDY", 6, false, true},

      {0x86, "STX", "ZP", 3, false, true},
      {0x96, "STX", "ZPY", 4, false, true},
      {0x8E, "STX", "ABS", 4, false, true},

      {0x84, "STY", "ZP", 3, false, true},
      {0x94, "STY", "ZPX", 4, false, true},
      {0x8C, "STY", "ABS", 4, false, true},

      // Transfer
      {0xAA, "TAX", "IMPLIED", 2, false, true},
      {0xA8, "TAY", "IMPLIED", 2, false, true},
      {0xBA, "TSX", "IMPLIED", 2, false, true},
      {0x8A, "TXA", "IMPLIED", 2, false, true},
      {0x9A, "TXS", "IMPLIED", 2, false, true},
      {0x98, "TYA", "IMPLIED", 2, false, true},
  };
}

class OpcodeInventoryTest : public ::testing::TestWithParam<OpcodeInfo> {};

TEST_P(OpcodeInventoryTest, OfficialOpcodeIsTracked) {
  const OpcodeInfo op = GetParam();

  SCOPED_TRACE(std::string(op.name) + " " + op.mode);

  EXPECT_LE(op.opcode, 0xFF);
  EXPECT_GT(op.cycles, 0);

  if (!op.implemented) {
    GTEST_SKIP() << "Not implemented yet: " << op.name << " " << op.mode
                 << " opcode=0x" << std::hex << U(op.opcode);
  }

  SUCCEED() << "Implemented opcode is tracked: " << op.name << " " << op.mode;
}

INSTANTIATE_TEST_SUITE_P(
    Official6502Opcodes,
    OpcodeInventoryTest,
    ::testing::ValuesIn(OfficialOpcodes()));