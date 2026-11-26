#pragma once
#include <stdio.h>
#include "menu.hpp"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// This should work in both windows and unix systems. (hopefully)

void parseFromFile(const char* filePath) {
	FILE* path = NULL;
	fopen_s(&path , filePath, "rb"); // the mode "rb" reads the file in binary //
	if (path) {
		
		size_t size = 0;
		fseek(path, 0, SEEK_END);
		size = ftell(path);
		rewind(path);

		char* fileContent = (char*)malloc(size);

		if (fread(fileContent, size, 1 ,path) == 1) {
			fileContent[size] = '\0'; // null terminator so the code knows when to stop reading
		}
		free(fileContent);

		fclose(path);
	}
}

void iniSave(int W, int H, int AUD, int DIFF, int FULL, int HIGH) {
	FILE* path = NULL;
	char numBuffer[16];
	fopen_s(&path, "./config.ini" , "wb"); // the mode "wb" write the file in binary //

	if (path) {
		char fileBuffer[256];
			* fileBuffer = '\0';
			strcat_s(fileBuffer, 256, "WIDTH=");
			strcat_s(fileBuffer, 256, itoa(W, numBuffer, 10));
			strcat_s(fileBuffer, 256, "\n");

			strcat_s(fileBuffer, 256, "HEIGHT=");
			strcat_s(fileBuffer, 256, itoa(H, numBuffer, 10));
			strcat_s(fileBuffer, 256, "\n");

			strcat_s(fileBuffer, 256, "AUDIO=");
			strcat_s(fileBuffer, 256, itoa(AUD, numBuffer, 10));
			strcat_s(fileBuffer, 256, "\n");

			strcat_s(fileBuffer, 256, "DIFFICULTY=");
			strcat_s(fileBuffer, 256, itoa(DIFF, numBuffer, 10));
			strcat_s(fileBuffer, 256, "\n");

			strcat_s(fileBuffer, 256, "FULLSCREEN=");
			strcat_s(fileBuffer, 256, itoa(FULL, numBuffer, 10));
			strcat_s(fileBuffer, 256, "\n");

			strcat_s(fileBuffer, 256, "HIGHLIGHT=");
			strcat_s(fileBuffer, 256, itoa(HIGH, numBuffer, 10));
			strcat_s(fileBuffer, 256, "\n");

			size_t fileLength = strlen(fileBuffer);
			fwrite(fileBuffer, fileLength, 1, path);

		fclose(path);
	}
}

void appendBuffer(char* buffer, char c) {
	if (!iscntrl(c)) {
		char str[2] = {c, '\0'};
		strcat_s(buffer, 256, str);
	}
}