#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256   // For all ASCII characters

// Node structure for Huffman Tree
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode *left, *right;
};

// Function to read frequencies from a file
void calculateFrequency(const char *filePath, int freq[]) {
    FILE *fp = fopen(filePath, "r");
    if (!fp) {
        printf("Error: Cannot open file %s\n", filePath);
        return;
    }

    char ch;
    while ((ch = fgetc(fp)) != EOF) {
        freq[(unsigned char)ch]++;  // Count each character
    }

    fclose(fp);
}

// Example function to start Huffman compression
void huffmanCompress(const char *filePath) {
    int freq[MAX_CHAR] = {0};

    // Step 1: Count frequency of each character
    calculateFrequency(filePath, freq);

    printf("Character frequencies in file:\n");
    for (int i = 0; i < MAX_CHAR; i++) {
        if (freq[i] > 0)
            printf("%c : %d\n", i, freq[i]);
    }

    // Step 2: Build Huffman tree (you can implement heap + tree building here)
    // Step 3: Generate Huffman codes
    // Step 4: Encode file content into compressed form
    // (To be implemented)
}
// #include<stdio.h>
// #include<string.h>

// char* encryption(char str[])
// {

// }

// int main()
// {
// 	char str[30];

// 	printf("Enter the string to encrypt:- ");
// 	scanf("%s" str);

// 	printf("%s",str);

// 
int main() {
    const char *filePath = "test.c";   // Path to your C file
    huffmanCompress(filePath);
    return 0;
}