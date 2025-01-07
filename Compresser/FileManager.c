/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#define _CRT_SECURE_NO_WARNINGS
#include "FileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

FILE* FileStart(unsigned char* path) {
	printf("Hello, please enter the full path to the .txt file you want to compress.\n");
	scanf_s("%s", path, 261);
	int i = 0;
	if (*(path + i) == '\0') {
		printf("Please a valid Path.");
		return NULL;
	}
	bool valid = false; // Right now where i write this Comment, i notice that this while loop is more or less completely useless... Will be changed in the future.
	while (*(path + i) != '\0') {
		if (*(path + i) == '.') {
			if (*(path + (i + 1)) == 't') {
				if (*(path + (i + 2)) == 'x') {
					if (*(path + (i + 3)) == 't') {
						if (*(path + (i + 4)) == '\0') {
							valid = true;
							break;
						}
					}
				}
			}
		}
		++i;
	}
	if (valid == false) {
		return NULL;
	}
	return fopen(path, "r");
}

int countCharsInFile(FILE* file) {
	int counter = 0;
	char character;
	while ((character = fgetc(file)) != EOF) {
		++counter;
	}
	rewind(file);
	return counter;
}

unsigned char* getText(int chars, FILE* file) {
	char* text = (char*)malloc(chars + 1);
	if (text == NULL) {
		return NULL;
	}
	int counter = 0;
	char character;
	while ((character = fgetc(file)) != EOF) {
		*(text + counter) = character;
		++counter;
	}
	*(text + counter) = '\0';
	return text;
}

void WriteInNewFile(unsigned char* text, unsigned char* path) {
	FILE* currentFile = fopen(path, "w");
	fputs(text, currentFile);
	fclose(currentFile);
}