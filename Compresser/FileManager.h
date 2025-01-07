/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#ifndef FileManager_h
#define FileManager_h
#include <stdio.h>

FILE* FileStart(unsigned char* path);

int countCharsInFile(FILE* file);

unsigned char* getText(int chars, FILE* file);

void WriteInNewFile(unsigned char* text, unsigned char* path);

#endif