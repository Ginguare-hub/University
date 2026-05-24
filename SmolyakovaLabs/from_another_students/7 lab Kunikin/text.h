#ifndef TEXT_H
#define TEXT_H

typedef struct
{
    char elements[256];
    int size;
} Set;

void init_set(Set *my_set);
void add_to_set(Set *my_set, char c);
int is_in_set(Set *my_set, char c);
void init_global_sets(void);

int is_latin_letter(char c);
int is_digit_char(char c);
int is_space_char(char c);

void normalizeText(const char *src, char *dst);
void analyzeText(const char *text, int *letters, int *digits, int *spaces);
int tokenizeWords(const char *text, char words[][50], int max_words);
void countLetterFrequency(const char *text, int freq[26]);
void reverse_string(const char *src, char *dst);
void run_laboratory(void);

#endif
