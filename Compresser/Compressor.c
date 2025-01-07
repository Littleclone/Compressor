/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#include "Compressor.h"
#include "Dictionary.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool IsCharOrDigit(unsigned char input) {
	if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || (input >= '0' && input <= '9')) {
		return true;
	}
	return false;
}

bool IsDigit(unsigned char input) {
	if ((input >= '0' && input <= '9')) {
		return true;
	}
	return false;
}

// The Function to Compress the String
int Compress(unsigned char input[], struct entry** ptr_to_ptr) { 
	struct entry* ptr;
	bool hasWord = false;
	int i = 0, foundChar = 0, counter = 0;
	int toSmallCounter = 0; // Counters who will displaced on the end of the Compression (More Soon)
	while (*(input + i) != '\0') {
		if (IsCharOrDigit(*(input + i))) {
			++counter;
			++foundChar;
			hasWord = true;
		}
		// TODO: Alles was ein Wort beendet soll hier am ende sein. (Bessere lösung finden) (Vielleicht einfach nur ein else?)
		else if ((*(input + i) == ' ' || *(input + i) == '\n' || *(input + i) == ',' || *(input + i) == '.' || *(input + i) == '(' || *(input + i) == ')'
			|| *(input + i) == '[' || *(input + i) == ']' || *(input + i) == '{' || *(input + i) == '}' || *(input + i) == '?' || *(input + i) == '!'
			|| *(input + i) == ';' || *(input + i) == ':') && hasWord) {
			++counter;
			hasWord = false;
			unsigned char* word = (unsigned char*)malloc(foundChar + 1);
			if (word == NULL) {
				printf("No memory could be reserved!");
				return;
			} 
			int w = 0;
			for (int j = i - foundChar; j < i; ++j) {
				*(word + w) = *(input + j);
				++w;
			}
			word[foundChar] = '\0';
			ptr = Find(*ptr_to_ptr, word);
			if (ptr == NULL) {

				Add(ptr_to_ptr, word, i - foundChar, 0);
			}
			else { // If the word already was found it will replaced with a Refference to the word.
				int j = i - foundChar, rightDigit, num = ptr->position, lenght = 0, temp = num;
				while (temp != 0) { // Counts how many Numbers the Position has
					temp /= 10;
					++lenght;
				}
				if (lenght + 2 <= foundChar) { // If the word is equal larger then the refference then its make sense to replace it with a refference
					int* chars = (int*)malloc((lenght + 1) * sizeof(int));
					// Under here the Refference number will be placed in the String:
					input[j] = '[';
					do { // Extract the Numbers from the Position
						rightDigit = num % 10;
						num = num / 10;
						chars[temp] = rightDigit;
						++temp;
					} while (num != 0);
					if (lenght != 0) { // Places the Numbers in the right order.
						for (int c = lenght - 1; c >= 0; --c) {
							++j;
							input[j] = chars[c] + '0';
						}
					}
					else {
						++j;
						input[j] = chars[temp - 1] + '0';
					}
					free(chars);
					chars = NULL;
					++j;
					input[j] = ']';
					++j;
					while (IsCharOrDigit(*(input + j))) { // Remove this line and you will see for yourself what will happen :O
						++j;
					}
					i = j - 1;
				}
				else {
					++toSmallCounter;
				}
			}
			free(word);
			word = NULL;
			foundChar = 0;
		}
		else {
			++counter;
		}
		++i;
	}
	printf("Follow things Happend while the Compression:\nTo small for a Refference: %i\n\n", toSmallCounter);
	return counter;
}

unsigned char* GetCompressString(unsigned char input[], int newLenght) {
	int i = 0, j = 0;
	bool miss = false; // If we want to miss Characters from the Original string. (This line Works with Line 94)
	unsigned char* newInput = (unsigned char*)malloc(newLenght + 100);
	if (newInput == NULL) {
		return NULL;
	}
	while (*(input + i) != '\0') {
		if (*(input + i) == ']') {
			miss = true;
			*(newInput + j) = *(input + i);
			++i;
			++j;
		}
		else if (IsCharOrDigit(*(input + i)) && miss) {
			++i;
		}
		else {
			miss = false;
			*(newInput + j) = *(input + i);
			++i;
			++j;
		}
	}
	*(newInput + j) = '\0';
	return newInput;
}

void verifyRefferences(unsigned char input[], struct entry** ptr_to_ptr, bool showChangingPosition) {
	struct entry* ptr;
	bool hasWord = false;
	int i = 0, foundChar = 0;
	int oldRefference = 0, sameRefference = 0, changedRefferenzes = 0;
	while (*(input + i) != '\0') {
		if (IsCharOrDigit(*(input + i))) {
			++foundChar;
			hasWord = true;
		}
		else if (*(input + i) == '[' && IsDigit(*(input + (i + 1)))) {
			int j = i + 1, pos = 0, counter = 0;
			while (*(input + j) != ']') {
				pos *= 10;
				pos += *(input + j) - '0';
				++j;
				++counter;
			}
			ptr = FindPos(*ptr_to_ptr, pos);
			if (ptr != NULL) {
				if (pos != ptr->newPosition) {
					j = i + 1;
					int rightDigit = 0, counterNewPos = 0, temp = ptr->newPosition, num = ptr->newPosition;
					int* chars = (int*)malloc((counter + 1) * sizeof(int));
					while (temp != 0) {
						temp /= 10;
						++counterNewPos;
					}
					do {
						rightDigit = num % 10;
						num = num / 10;
						chars[temp] = rightDigit;
						++temp;
					} while (num != 0);
					if (counter != counterNewPos) {
						for (int c = counterNewPos; c <= counter; ++c) {
							chars[c] = 0;
						}
					}
					for (int c = counter - 1; c >= 0; --c, ++j) {
						input[j] = chars[c] + '0';
					}
					++changedRefferenzes;
				}
			}
		}
		// TODO: Alles was ein Wort beendet soll hier am ende sein. (Bessere lösung finden) (Vielleicht einfach nur ein else?)
		else if ((*(input + i) == ' ' || *(input + i) == '\n' || *(input + i) == ',' || *(input + i) == '.' || *(input + i) == '(' || *(input + i) == ')'
			|| *(input + i) == '[' || *(input + i) == ']' || *(input + i) == '{' || *(input + i) == '}' || *(input + i) == '?' || *(input + i) == '!'
			|| *(input + i) == ';' || *(input + i) == ':') && hasWord) {
			hasWord = false;
			unsigned char* word = (unsigned char*)malloc(foundChar + 1);
			if (word == NULL) {
				printf("No memory could be reserved!");
				return;
			}
			int w = 0;
			for (int j = i - foundChar; j < i; ++j) {
				*(word + w) = *(input + j);
				++w;
			}
			word[foundChar] = '\0';
			ptr = Find(*ptr_to_ptr, word);
			if (ptr != NULL) { 
				if (i - foundChar != ptr->position && ptr->newPosition == NULL) {
					ptr->newPosition = i - foundChar;
					if (showChangingPosition) {
						printf("Position Changed from %s: %i -> %i\n", ptr->Word, ptr->position, ptr->newPosition);
					}
					++oldRefference;
				}
				else if (i - foundChar == ptr->position && ptr->newPosition == NULL) {
					ptr->newPosition = ptr->position;
					++sameRefference;
				}
			}
			free(word);
			word = NULL;
			foundChar = 0; 
		}
		++i;
	}
	printf("References that had to be reset: %i\nReferences that could remain as they are: %i\nReferences who get the new position: %i\n", oldRefference, sameRefference, changedRefferenzes);
}
