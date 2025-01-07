#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <Windows.h>
#include "Dictionary.h"
#include "FileManager.h"
#include "Compressor.h"
#include "Decompressor.h"

#define DEBUG 1 // Change here to '0' if you don't want to see the Debug Informations.
#define ShowChangedPosition 1 // Change here to '0' if you don't want to see how the Position from a Words Changed by the Compression
/*
 * MIT License
 * Copyright (c) 2025 Littleclone
 * Permission is granted to use, copy, modify, and distribute this software,
 * provided that the copyright notice and this permission notice are included.
 * The software is provided "as is", without warranty of any kind.
 */

struct entry* listStart, ** ptr_to_ptr = &listStart;
int main() {
	SetConsoleOutputCP(CP_UTF8);
	unsigned char* path[261], *newInput; // Max Lenght of File Paths.
	FILE* currentFile = FileStart(path); // The Current File we will use.
	if (currentFile == NULL) {
		printf("Error: File is NULL");
		return -1;
	}
	int chars = countCharsInFile(currentFile); // Here we want to know how many Chars are in the File to know how many Memory we have to allocated.
	if (chars == 0) {
		printf("File has no content");
		return -1;
	}
	unsigned char* text = getText(chars, currentFile); // With the amount of Chars we allocet memory on the Heap and want the Content from the File as a Char Pointer.
	if (text == NULL) {
		printf("Text couldn't extracted from the File or the Pointer is not working.");
		return -1;
	}
	fclose(currentFile); // We don't need the File anymore so we can close it.
	while (true) {
		char choice;
		printf("\nDo you want to compress or decompress the file?\nCompress [1]\nDecompress [2]\n");
		scanf_s(" %c", &choice);
		if (choice == '1') { // Compression
			int counter = Compress(text, ptr_to_ptr); // Here we Compress the text and we get the Number of Chars for a new String we want to make.
			if (DEBUG) {
				PrintList(listStart); // Debug Function
			}
			newInput = GetCompressString(text, counter); // The new string with the compressed sentence is created and the pointer to it is returned.
			if (newInput == NULL) {
				printf("Error: Pointer is NULL");
				return -1;
			}
			printf("Verify Check started.\n");
			// Here we Verify that every Refference fit still to the refferenced word because the string is now shorter
			// if thats not the case the Old Position will changed with the new Position.
			verifyRefferences(newInput, ptr_to_ptr, ShowChangedPosition); 
			printf("\n");
			break;
		}
		else if (choice == '2') { // Decompression
			int counter = decompress(text, ptr_to_ptr); // We analyze the Compressed file and give the Chars we need for the larger string back as int.
			if (DEBUG) {
				PrintList(listStart); // Debug Function
			}
			newInput = GetDecompressString(text, counter, listStart); // Here we Decompress the String and get the New String back as a Pointer.
			if (newInput == NULL) {
				printf("Error: Pointer is NULL");
				return -1;
			}
			break;
		}
		else {
			printf("\nThats not a Valid Option.");
			continue;
		}
	}
	printf("Finish");
	WriteInNewFile(newInput, path); // We write the next Text in the File
	FreeDictionary(ptr_to_ptr); // We clear the Dictionary used for the Compression/Decompression
	return 0;
}