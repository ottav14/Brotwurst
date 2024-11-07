#include "util.h"

char* readFileToString(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET); 

    char *buffer = malloc(fileSize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0'; 

    fclose(file);
    return buffer;
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

