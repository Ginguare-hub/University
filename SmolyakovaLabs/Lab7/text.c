#include <ctype.h>
#include <string.h>
#include "text.h"

static Set setOfLetters;
static Set setOfDigits;
static Set setOfSpaces;

void normalizeText(const char *src, char *dst)
{
    int i = 0;
    int j = 0;
    int in_space = 1;
    char c = '\0';

    while (src[i] != '\0')
    {
        c = src[i];
        if (isspace((unsigned char)c))
        {
            if (!in_space)
            {
                dst[j++] = ' ';
                in_space = 1;
            }
        }
        else
        {
            dst[j++] = (char)tolower((unsigned char)c);
            in_space = 0;
        }
        i++;
    }

    if (j > 0 && dst[j - 1] == ' ')
        j--;

    dst[j] = '\0';
}

void analyzeText(const char *text)
{
    setOfLetters.size = 0;
    setOfDigits.size = 0;
    setOfSpaces.size = 0;

    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (isalpha((unsigned char)text[i]))
            setOfLetters.size++;
        else 
            if (isdigit((unsigned char)text[i]))
                setOfDigits.size++;
            else    
                if (isspace((unsigned char)text[i]))
                    setOfSpaces.size++;
    }
}

int tokenizeWords(const char *text, char words[][50], int max_words)
{
    int count = 0;
    int i = 0;
    int j;
    _Bool isSkip = 0;

    while (text[i] != '\0' && count < max_words && !isSkip)
    {
        isSkip = 0;
        while (text[i] != '\0' && !isalpha((unsigned char)text[i]))
            i++;
        if (text[i] == '\0')
            isSkip = 1;

        if (!isSkip)
        {
            j = 0;
            while (text[i] != '\0' && isalpha((unsigned char)text[i]) && j < 49)
            {
                words[count][j++] = text[i++];
            }
            words[count][j] = '\0';
            count++;
        }
    }

    return count;
}

void countLetterFrequency(const char *text, int freq[26])
{
    const int LETTERS_COUNT = 26;
    for (int i = 0; i < LETTERS_COUNT; ++i)
        freq[i] = 0;

    for (int i = 0; text[i] != '\0'; ++i)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
            freq[text[i] - 'a']++;
    }
}

char **tokenization(char *text, int *n)
{
    char **tokens;
    int capacity = 10;
    int idx = 0;
    int i = 0;
    int start, len;
    char *token;

    *n = 0;
    tokens = (char **)malloc(capacity * sizeof(char *));
    if (tokens == NULL)
        return NULL;

    while (text[i] != '\0')
    {
        if (isspace((unsigned char)text[i]))
        {
            i++;
        }
        else
        {
            if (isalpha((unsigned char)text[i]))
            {
                start = i;
                while (text[i] != '\0' && isalpha((unsigned char)text[i]))
                    i++;
                len = i - start;
            }
            else if (isdigit((unsigned char)text[i]))
            {
                start = i;
                while (text[i] != '\0' && isdigit((unsigned char)text[i]))
                    i++;
                len = i - start;
            }
            else
            {
                start = i;
                i++;
                len = 1;
            }

            token = (char *)malloc((len + 1) * sizeof(char));
            if (token == NULL)
            {
                for (int j = 0; j < idx; j++)
                    free(tokens[j]);
                free(tokens);
                return NULL;
            }
            strncpy(token, text + start, len);
            token[len] = '\0';
            tokens[idx++] = token;

            if (idx >= capacity)
            {
                capacity *= 2;
                char **tmp = (char **)realloc(tokens, capacity * sizeof(char *));
                if (tmp == NULL)
                {
                    for (int j = 0; j < idx; j++)
                        free(tokens[j]);
                    free(tokens);
                    return NULL;
                }
                tokens = tmp;
            }
        }
    }

    char **tmp = (char **)realloc(tokens, (idx + 1) * sizeof(char *));
    if (tmp == NULL && idx > 0)
    {
        tokens = (char **)realloc(tokens, (idx + 1) * sizeof(char *));
    }
    else if (tmp != NULL)
        tokens = tmp;
    tokens[idx] = NULL;
    *n = idx;
    return tokens;
}

void writeTokens(char **tokens, int len)
{
    int i;
    printf("\n=== TOKENS ===\n");
    printf("+--------------------------------+\n");

    for (i = 0; i < len && tokens[i] != NULL; i++)
    {
        printf("| %2d - %-25s |\n", i + 1, tokens[i]);
        printf("+--------------------------------+\n");
    }
}

int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[])
{
    _Bool isIncorrect;
    int number;
    char ch;

    isIncorrect = 0;
    number = 0;
    ch = 0;

    do
    {
        printf("%s", myString);
        isIncorrect = 0;

        if (scanf("%d%c", &number, &ch) == 0 || !(isspace(ch) || ch == EOF))
        {
            isIncorrect = 1;
            printf("Incorrect input, try again\n");
            while (getchar() != '\n')
                ;
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = 1;
            printf("Number must fit the [%d,%d] diapason\n", MIN_NUMBER, MAX_NUMBER);
        }

    } while (isIncorrect);

    return number;
}

void writeAnalyze()
{
    printf("\n=== ANALYSIS ===\n");
    printf("| Letters:  %-3d |\n", setOfLetters.size);
    printf("| Digits:   %-3d |\n", setOfDigits.size);
    printf("| Spaces:   %-3d |\n", setOfSpaces.size);
}