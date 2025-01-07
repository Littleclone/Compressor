/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#ifndef Decompressor_h
#define Decompressor_h

int decompress(unsigned char* input, struct entry** ptr_to_ptr);

unsigned char* GetDecompressString(unsigned char* input, unsigned int lenght, struct entry* listStart);

#endif

