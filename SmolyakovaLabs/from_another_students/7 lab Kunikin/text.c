#include <stdio.h>
#include <string.h>
#include "text.h"

static Set letters_set;
static Set digits_set;
static Set spaces_set;

int is_in_set(Set *my_set, char c)
{
    int i, found;

    found = 0;
    i = 0;
    while (i < my_set->size)
    {
        if (my_set->elements[i] == c)
        {
            found = 1;
        }
        i++;
    }
    return found;
}

void init_set(Set *my_set)
{
    my_set->size = 0;
    return;
}

void add_to_set(Set *my_set, char c)
{
    if (is_in_set(my_set, c) == 0)
    {
        my_set->elements[my_set->size] = c;
        my_set->size++;
    }
    return;
}

char my_tolower(char c)
{
    char lower_c;

    lower_c = c;
    if (c >= 'A' && c <= 'Z')
    {
        lower_c = (char)(c + ('a' - 'A'));
    }
    return lower_c;
}

void init_global_sets(void)
{
    int i;

    init_set(&letters_set);
    init_set(&digits_set);
    init_set(&spaces_set);

    i = 'a';
    while (i <= 'z')
    {
        add_to_set(&letters_set, (char)i);
        i++;
    }
    i = 'A';
    while (i <= 'Z')
    {
        add_to_set(&letters_set, (char)i);
        i++;
    }
    i = '0';
    while (i <= '9')
    {
        add_to_set(&digits_set, (char)i);
        i++;
    }

    add_to_set(&spaces_set, ' ');
    add_to_set(&spaces_set, '\t');
    add_to_set(&spaces_set, '\n');
    add_to_set(&spaces_set, '\r');

    return;
}

int is_latin_letter(char c)
{
    return is_in_set(&letters_set, c);
}

int is_digit_char(char c)
{
    return is_in_set(&digits_set, c);
}

int is_space_char(char c)
{
    return is_in_set(&spaces_set, c);
}

void normalizeText(const char *src, char *dst)
{
    int i, j, in_space;
    char c;

    i = 0;
    j = 0;
    in_space = 1;
    while (src[i] != '\0')
    {
        c = src[i];
        if (is_space_char(c))
        {
            if (in_space == 0)
            {
                dst[j] = ' ';
                j++;
                in_space = 1;
            }
        }
        else
        {
            dst[j] = my_tolower(c);
            j++;
            in_space = 0;
        }
        i++;
    }
    if (j > 0)
    {
        if (dst[j - 1] == ' ')
        {
            j--;
        }
    }
    dst[j] = '\0';
    return;
}

void analyzeText(const char *text, int *letters, int *digits, int *spaces)
{
    int i;

    *letters = 0;
    *digits = 0;
    *spaces = 0;
    i = 0;
    while (text[i] != '\0')
    {
        if (is_latin_letter(text[i]))
        {
            (*letters)++;
        }
        else if (is_digit_char(text[i]))
        {
            (*digits)++;
        }
        else if (is_space_char(text[i]))
        {
            (*spaces)++;
        }
        i++;
    }
    return;
}

int tokenizeWords(const char *text, char words[][50], int max_words)
{
    int count, i, j, keep_going_outer;

    count = 0;
    i = 0;
    keep_going_outer = 1;
    while (text[i] != '\0' && count < max_words && keep_going_outer)
    {
        while (text[i] != '\0' && !is_latin_letter(text[i]))
        {
            i++;
        }
        if (text[i] == '\0')
        {
            keep_going_outer = 0;
        }
        else
        {
            j = 0;
            while (text[i] != '\0' && is_latin_letter(text[i]) && j < 49)
            {
                words[count][j] = text[i];
                j++;
                i++;
            }
            words[count][j] = '\0';
            count++;
        }
    }
    return count;
}

void countLetterFrequency(const char *text, int freq[26])
{
    int i;

    for (i = 0; i < 26; i++)
    {
        freq[i] = 0;
    }
    i = 0;
    while (text[i] != '\0')
    {
        if (text[i] >= 'a')
        {
            if (text[i] <= 'z')
            {
                freq[text[i] - 'a']++;
            }
        }
        i++;
    }
    return;
}

void reverse_string(const char *src, char *dst)
{
    int len, i;

    len = 0;
    while (src[len] != '\0')
    {
        len++;
    }
    for (i = 0; i < len; i++)
    {
        dst[i] = src[len - 1 - i];
    }
    dst[len] = '\0';
    return;
}

void run_laboratory(void)
{
    char source[256], normalized[256], reversed[256];
    int letters, digits, spaces, word_count, i, choice, keep_going, should_execute;
    int freq[26];
    char words[50][50];
    Set letter_set, digit_set;

    init_global_sets();

    keep_going = 1;
    should_execute = 0;
    while (keep_going)
    {
        printf("\n======================================================================================\n");
        printf("=== МЕНЮ ВЫБОРА ИСХОДНЫХ ДАННЫХ ===\n");
        printf("1. Использовать текст по умолчанию: \"  Hello,   WORLD 123   hello  \"\n");
        printf("2. Ввести свою строку вручную\n");
        printf("0. Выход из программы\n");
        printf("======================================================================================\n");
        printf("Выберите вариант: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\n[ОШИБКА] Пожалуйста, введите число (0, 1 или 2).\n");
            while (getchar() != '\n')
                ;
        }
        else
        {
            getchar();
            if (choice == 1)
            {
                strcpy(source, "  Hello,   WORLD 123   hello  ");
                should_execute = 1;
                keep_going = 0;
            }
            else if (choice == 2)
            {
                printf("Введите ваш текст (макс. 255 символов): ");
                if (fgets(source, sizeof(source), stdin) != NULL)
                {
                    if (strlen(source) > 1)
                    {
                        source[strcspn(source, "\n")] = '\0';
                        should_execute = 1;
                        keep_going = 0;
                    }
                    else
                    {
                        printf("\n[ОШИБКА] Введена пустая строка. Попробуйте еще раз.\n");
                    }
                }
            }
            else if (choice == 0)
            {
                printf("\nЗавершение работы программы...\n");
                keep_going = 0;
            }
            else
            {
                printf("\n[ОШИБКА] Неверный пункт меню. Выберите 0, 1 или 2.\n");
            }
        }
    }

    if (should_execute)
    {
        normalizeText(source, normalized);

        init_set(&letter_set);
        init_set(&digit_set);

        i = 0;
        while (normalized[i] != '\0')
        {
            if (is_latin_letter(normalized[i]))
            {
                add_to_set(&letter_set, normalized[i]);
            }
            else if (is_digit_char(normalized[i]))
            {
                add_to_set(&digit_set, normalized[i]);
            }
            i++;
        }

        printf("\n======================================================================================\n");
        printf("=== ЛАБОРАТОРНАЯ РАБОТА 7: РЕЗУЛЬТАТЫ ОБРАБОТКИ ===\n");
        printf("======================================================================================\n\n");

        printf("--- ИСХОДНЫЕ ДАННЫЕ ---\n");
        printf("Текст: \"%s\"\n\n", source);

        printf("--- НОРМАЛИЗАЦИЯ ---\n");
        printf("Текст: \"%s\"\n\n", normalized);

        printf("--- МНОЖЕСТВА СИМВОЛОВ В ТЕКСТЕ ---\n");
        printf("• буквы: ");
        for (i = 0; i < letter_set.size; i++)
        {
            printf("%c%s", letter_set.elements[i], (i == letter_set.size - 1) ? "" : ", ");
        }
        printf("\n• цифры: ");
        for (i = 0; i < digit_set.size; i++)
        {
            printf("%c%s", digit_set.elements[i], (i == digit_set.size - 1) ? "" : ", ");
        }
        printf("\n\n");

        analyzeText(normalized, &letters, &digits, &spaces);
        printf("--- АНАЛИЗ СИМВОЛОВ ---\n");
        printf("Буквы:   %d\n", letters);
        printf("Цифры:   %d\n", digits);
        printf("Пробелы: %d\n\n", spaces);

        word_count = tokenizeWords(normalized, words, 50);
        printf("--- ТОКЕНИЗАЦИЯ (СЛОВА) ---\n");
        printf("Найдено слов: %d\n", word_count);
        for (i = 0; i < word_count; i++)
        {
            printf("  %d: %s\n", i + 1, words[i]);
        }
        printf("\n");

        countLetterFrequency(normalized, freq);
        printf("--- ЧАСТОТА ЛАТИНСКИХ БУКВ ---\n");
        for (i = 0; i < 26; i++)
        {
            if (freq[i] > 0)
            {
                printf("  '%c': %d\n", 'a' + i, freq[i]);
            }
        }
        printf("\n");

        reverse_string(normalized, reversed);
        printf("--- ВАРИАНТ 16: РАЗВЕРНУТАЯ СТРОКА ---\n");
        printf("Текст: \"%s\"\n\n", reversed);
        printf("======================================================================================\n\n");
    }

    return;
}
