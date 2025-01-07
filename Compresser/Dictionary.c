/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int Add(struct entry** ptr_To_Begin, unsigned char const _word[], unsigned int const _position, unsigned int const _count) {
	// TODO: Noch hinzufügen bei Compressor und Decompressor was passiert wenn Add NULL ausgibt. (Für die Zukunft)
	int i = 0;
	struct entry* head = (struct entry*)malloc(sizeof(struct entry)); // Creates a pointer to a new struct in the heap
	if (head == NULL) {
		return -1;
	}
	unsigned char* chars = (unsigned char*)malloc(strlen(_word) + 1); // Creates a pointer for the string to be stored in "word".
	if (chars == NULL) {
		free(head); // Because we already alloceted "head" we need to free it if the Add function fails.
		return -1;
	}
	while (*(_word + i) != '\0') { // Copies one string to another string or simply "strcpy" (Performs the same function)
		*(chars + i) = *(_word + i);
		++i;
	}
	chars[i] = '\0';
	head->Word = chars;
	head->position = _position;
	head->newPosition = NULL;
	head->charCount = _count;
	head->next = NULL;
	if (*ptr_To_Begin != NULL) {
		struct entry* listPtr = *ptr_To_Begin;
		while (listPtr->next != NULL) {
			listPtr = listPtr->next;
		}
		listPtr->next = head;
	}
	else { // If there is no element in the linked list yet. (It makes this the first element of the Linked list)
		*ptr_To_Begin = head; // ptr_To_Begin = Pointer To Pointer to the Beginn of the Linked List.
	}
	return 1;
}

// Looks to find a Entry with a Matching word
struct entry* Find(struct entry* listPtr, unsigned char const match[]) {
	while (listPtr != NULL) {
		if (strcmp(listPtr->Word, match) == 0) {
			return (listPtr);
		}
		else {
			listPtr = listPtr->next;
		}
	}
	return NULL;
}

// Try to find a Entry with Pos.
struct entry* FindPos(struct entry* listPtr, unsigned int const pos) {
	while (listPtr != NULL) {
		if (listPtr->position == pos) {
			return (listPtr);
		}
		else {
			listPtr = listPtr->next;
		}
	}
	return NULL;
}

// Free the entire Dictonary with the Entrys
void FreeDictionary(struct entry** listPtr) {
	struct entry* ptr = *listPtr, *freePtr;
	while (ptr != NULL) {
		freePtr = ptr;
		ptr = ptr->next;
		free(freePtr->Word); // Because the Word is also an Pointer we need to free it too.
		free(freePtr);
	}
	*listPtr = NULL;
}

// Debug Function [Only Using for Debug Needs]

void PrintList(struct entry* listPtr) {
	printf("-------DEBUG Output-------\n");
	while (listPtr != NULL) {
		printf("%s, %i, %i, %p\n", listPtr->Word, listPtr->position, listPtr->charCount, listPtr->next);
		listPtr = listPtr->next;
	}
	printf("-------DEBUG Output-------\n\n");
}