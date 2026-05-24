#include "M6502/cpu.h"

Byte CPU::FetchByte() {
  Byte Data = (*Memory)[ProgramCounter];
  ProgramCounter++;
  Cycles--;
  return Data;
}

Word CPU::FetchWord() {
  Byte lowByte = FetchByte();
  Byte highByte = FetchByte();

  return lowByte | (highByte << 8);
}

Byte CPU::ReadByte(Word address) {
  Byte Data = (*Memory)[address];
  Cycles--;
  return Data;
}

Word CPU::ReadWord(Word address) {
  Byte lowByte = ReadByte(address);
  Byte highByte = ReadByte(address + 1);
  return lowByte | (highByte << 8);
}

Word CPU::ReadWordFromZeroPage(Word address) {
  Byte lowByteAddress = address;
  Byte highByteAddress = address + 1;
  Byte lowByte = ReadByte(lowByteAddress);
  Byte highByte = ReadByte(highByteAddress);
  return lowByte | (highByte << 8);
}

void CPU::WriteByte(Word address, Byte value) {
  (*Memory)[address] = value;
  Cycles--;
}

void CPU::WriteWord(Word address, Word value) {
  Word lowByteAddress = address;
  Word highByteAddress = address + 1;
  WriteByte(lowByteAddress, value);
  WriteByte(highByteAddress, value >> 8);
}

void CPU::WriteWordToZeroPage(Byte address, Word value) {
  Byte lowByteAddress = address;
  Byte highByteAddress = address + 1;
  WriteByte(lowByteAddress, value);
  WriteByte(highByteAddress, value >> 8);
}
