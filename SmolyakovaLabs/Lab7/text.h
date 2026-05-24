#ifndef TEXT
#define TEXT

#include <stdio.h>
#include <stdlib.h>

typedef struct Set
{
    char elements[256];
    int size;
} Set;

void writeAnalyze();
void normalizeText(const char *src, char *dst);
void analyzeText(const char *text);
int tokenizeWords(const char *text, char words[][50], int max_words);
void countLetterFrequency(const char *text, int freq[26]);
char **tokenization(char *text, int *n);
void writeTokens(char **tokens, int len);
void writeTokensBySetLength(char **tokens, int len);
int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[]);

#endif