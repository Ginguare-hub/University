#include <stdio.h>
#include "text.h"

void writeInitial(char *source);
void writeNormalized(char normalized[]);
void writeTokensBySetLength(char **tokens, int len);
void getString(char *buffer, int size);
void writeLetterFrequencies(int freq[], int size);
void writePurpose();

int main(void)
{
    const int BUFFER = 256;
    const int LETTER_COUNT = 26;
    char source[BUFFER];
    char normalized[BUFFER];
    int word_count, len;
    int freq[LETTER_COUNT];
    char **tokens;

    len = 0;
    source[0] = '\0';

    writePurpose();

    getString(source, sizeof(source));

    writeInitial(source);

    normalizeText(source, normalized);
    writeNormalized(normalized);

    analyzeText(normalized);
    writeAnalyze();

    countLetterFrequency(normalized, freq);
    writeLetterFrequencies(freq, LETTER_COUNT);

    tokens = tokenization(normalized, &len);
    writeTokens(tokens, len);

    writeTokensBySetLength(tokens, len);

    return 0;
}

void writePurpose()
{
    printf("\n====== LAB 7: TEXT PROCESSING ======\n");
    printf("This program performs:\n");
    printf(" - text normalization (remove extra spaces, to lower case)\n");
    printf(" - character analysis by using SETS (letters, digits, spaces)\n");
    printf(" - letter frequency count\n");
    printf(" - tokenization (split into words, numbers, punctuation)\n");
    printf(" - search for words of a specified length\n");
    printf("\n");
}

void getString(char *buffer, int size)
{
    printf("\n=== INPUT ===\n");
    while (buffer[0] == '\n' || buffer[0] == '\0')
    {
        printf("Write string (MAX %d symbols): ", size-1);
        fgets(buffer, size, stdin);
    }
}

void writeNormalized(char normalized[])
{
    printf("=== OUTPUT ===\n");
    printf("Normalized text:\n%s\n", normalized);
}

void writeTokensBySetLength(char **tokens, int len)
{
    const int MAX_LENGTH = 100;
    const int MIN_LENGTH = 1;
    int setLength, i, j, wordLength;
    _Bool isNotExist;

    isNotExist = 1;
    setLength = 0;
    printf("\nEnter the length of the words you want to find: \n");
    setLength = scanInt(MIN_LENGTH, MAX_LENGTH, "> ");

    printf("\n=== WORDS WITH LENGTH <%d> ===\n", setLength);

    for (i = 0; i < len && tokens[i] != NULL; i++)
    {
        wordLength = 0;
        while (tokens[i][wordLength] != '\0')
            wordLength++;

        if (wordLength == setLength)
        {
            if (isNotExist)
                printf("+---------------------------+\n");
            isNotExist = 0;
            printf("| %-25s |\n", tokens[i]);
            printf("+---------------------------+\n");
        }
    }

    if (isNotExist)
        printf("There are NO words with length %d\n", setLength);
}

void writeInitial(char *source)
{
    printf("Initial text:\n%s\n", source);
}

void writeLetterFrequencies(int freq[], int size)
{
    printf("\n=== LETTER FREQUENCIES IN SET OF LETTERS ===\n");
    printf("+---------+\n");
    for (int i = 0; i < size; ++i)
    {
        if (freq[i] > 0)
        {
            printf("| %c - %-3d |\n", 'a' + i, freq[i]);
            printf("+---------+\n");
        }
    }
}