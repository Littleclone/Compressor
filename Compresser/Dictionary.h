/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#ifndef Dictionary_h
#define Dictionary_h
struct entry {
	unsigned char* Word;
	unsigned int position;
	unsigned int newPosition;
	unsigned int charCount;
	struct entry* next;
};

int Add(struct entry** ptr_To_Begin, unsigned char const Word[], unsigned int const position, unsigned int const count);

struct entry* Find(struct entry* listPtr, unsigned char const match[]);

struct entry* FindPos(struct entry* listPtr, unsigned int const pos);

void FreeDictionary(struct entry** listPtr);

// Debug Funktionen:
void PrintList(struct entry* listPtr);

#endif