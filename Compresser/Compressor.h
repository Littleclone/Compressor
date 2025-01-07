/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#ifndef Compressor_h
#define Compressor_h
#include "Dictionary.h"
#include <stdbool.h>

bool IsCharOrDigit(unsigned char input);

bool IsDigit(unsigned char input);

int Compress(unsigned char input[], struct entry** ptr_to_ptr);

unsigned char* GetCompressString(unsigned char input[], int newLenght);

void verifyRefferences(unsigned char input[], struct entry** ptr_to_ptr, bool showChangingPosition);

#endif
