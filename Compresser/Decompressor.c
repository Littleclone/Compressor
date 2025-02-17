/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#include "Compressor.h"
#include "Decompressor.h"
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int decompress(unsigned char* input, struct entry** ptr_to_ptr) {
	struct entry* ptr;
	int i = 0, foundChar = 0, counter = 0;
	bool hasWord = false;
	while (*(input + i) != '\0') {
		if (IsCharOrDigit(*(input + i))) {
			++foundChar;
			hasWord = true;
		}
		else if (*(input + i) == '[') {
			int j = i + 1;
			if (*(input + j) != ';' && IsDigit(*(input + j))) { // There is also a Condition for something in the Future.
				int position = 0;
				while (*(input + j) != ']') {
					position *= 10;
					position += *(input + j) - '0';
					++j;
				}
				int temp = position, count = 0; 
				// Was mach ich hier? Bzw. Wieso ist das so? [Vielleicht um sicherzugehen das es der anfang des wortes ist]
				while (IsCharOrDigit(*(input + temp))) {
					--temp;
					--position;
				}
				++temp;
				++position;
				// Größe des Strings erhalten
				while (IsCharOrDigit(*(input + temp))) {
					++temp;
					++count;
				}
				unsigned char* word = (unsigned char*)malloc(count + 1);
				if (word == NULL) {
					printf("Error");
					return 0;
				}
				count = 0; 
				// String übertragen
				while (IsCharOrDigit(*(input + position))) {
					*(word + count) = *(input + position);
					++position;
					++count;
				}
				*(word + count) = '\0';
				ptr = Find(*ptr_to_ptr, word);
				if (ptr != NULL) {
					counter += ptr->charCount;
					++j;
					i = j;
				}
				free(word);
				word = NULL;
			}
		}
		else if (hasWord){
			hasWord = false;
			unsigned char* word = (unsigned char*)malloc(foundChar + 1);
			if (word == NULL) {
				printf("No memory could be reserved!");
				return 0;
			}
			int w = 0;
			for (int j = i - foundChar; j < i; ++j) {
				*(word + w) = *(input + j);
				++w;
			}
			word[foundChar] = '\0';
			ptr = Find(*ptr_to_ptr, word);
			if (ptr == NULL) { // If nothing is found (and therefore NULL) it means that there is no entry with this word yet, this word will then be entered.
				Add(ptr_to_ptr, word, i - foundChar, foundChar);
			}
			free(word);
			word = NULL;
			foundChar = 0;
		}
		++counter;
		++i;
	}
	return counter;
}

unsigned char* GetDecompressString(unsigned char* input, unsigned int lenght, struct entry* startList) {
	struct entry* ptr;
	int i = 0, j = 0;
	unsigned char* newInput = (unsigned char*)malloc(lenght + 100);
	if (newInput == NULL) {
		return NULL;
	}
	while (*(input + i) != '\0') {
		if (*(input + i) == '[' && *(input + (i + 1)) != ';') {
			int pos = 0, x = i + 1;
			while (*(input + x) != ']') {
				pos *= 10;
				pos += *(input + x) - '0';
				++x;
				++i;
			}
			i += 2;
			ptr = FindPos(startList, pos);
			if (ptr == NULL) {
				while (IsCharOrDigit(*(input + pos))) {
					*(newInput + j) = *(input + pos);
					++pos;
					++j;
				}
			}
			else {
				int temp = 0;
				while (*(ptr->Word + temp) != '\0') {
					*(newInput + j) = *(ptr->Word + temp);
					++temp;
					++j;
				}
			}
			

		}
		else if (*(input + i) == ';') {
			++i;
		}
		else {
			*(newInput + j) = *(input + i);
			++i;
			++j;
		}
	}
	*(newInput + j) = '\0';
	return newInput;
}