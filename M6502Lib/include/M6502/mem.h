#pragma once

#include "types.h"

struct MEM {
  static constexpr u32 MAX_MEM = 1024 * 64;
  Byte Data[MAX_MEM];

  void Init() {
    for (u32 i = 0; i < MAX_MEM; i++) {
      Data[i] = 0;
    }
  }

  Byte operator[](u32 address) const { return Data[address]; }
  Byte &operator[](u32 address) { return Data[address]; }
};
