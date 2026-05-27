#include "search.h"

/* ================================================================
   writePurpose
   ================================================================ */
void writePurpose(void)
{
    printf("Программа демонстрирует поиск уникальных записей в массиве.\n");
    printf("Реализованы:\n");
    printf("  заполнение массива\n");
    printf("  сортировка по полю id\n");
    printf("  линейный поиск уникальных записей (несортированный массив)\n");
    printf("  двоичный поиск дубликатов с последующим отбором уникальных (отсортированный массив)\n");
    printf("  подсчёт сравнений и анализ.\n");
    printf("Рекомендуется вводить имена на латинице\n");
}

/* ================================================================
   scanInt
   ================================================================ */
static _Bool isCharValid(char ch)
{
    _Bool isValid;
    isValid = isspace(ch) || ch == EOF;
    return isValid;
}

static _Bool isRangeValid(int number, int minVal, int maxVal)
{
    _Bool isValid;
    isValid = number >= minVal && number <= maxVal;
    return isValid;
}

static void printRangeError(int minVal, int maxVal)
{
    printf("Число должно входить в диапазон [%d, %d]\n", minVal, maxVal);
}

static void clearBuffer(void)
{
    while (getchar() != '\n')
        ;
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
            printf("Некорректный ввод, повторите попытку\n");
            while (getchar() != '\n')
                ;
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = 1;
            printf("Число должно входить в диапазон [%d,%d]\n", MIN_NUMBER, MAX_NUMBER);
        }

    } while (isIncorrect);

    return number;
}

static void stripNewline(char buf[])
{
    buf[strcspn(buf, "\n")] = '\0';
}

static _Bool isNameValid(const char buf[], int maxLen)
{
    int len;
    _Bool isValid;
    len = (int)strlen(buf);
    isValid = len > 0 && len < maxLen;

    return isValid;
}

static void scanName(char dest[], int maxLen)
{
    char buf[60];
    _Bool notOk;

    notOk = 1;

    do
    {
        printf("> ");

        if (fgets(buf, (int)sizeof(buf), stdin) == NULL)
        {
            printf("Ошибка чтения, повторите попытку\n");
        }
        else
        {
            stripNewline(buf);

            if (!isNameValid(buf, maxLen))
                printf("Имя должно быть от 1 до %d символов\n", maxLen - 1);
            else
                notOk = 0;
        }

    } while (notOk);

    strncpy(dest, buf, maxLen - 1);
    dest[maxLen - 1] = '\0';
}

/* ================================================================
   fillOneRecord
   ================================================================ */
static void fillOneRecord(Record *rec, int index)
{
    const int MAX_NUM = 999999;
    const int MIN_NUM = -999999;
    const int MAX_BUFFER = 50;

    printf("--- Запись [%d] ---\n", index);

    printf("Введите id\n");
    rec->id = scanInt(MIN_NUM, MAX_NUM, "> "); // используем ->, а не (*rec[index])

    printf("Введите name\n");
    scanName(rec->name, MAX_BUFFER);

    printf("Введите value\n");
    rec->value = scanInt(MIN_NUM, MAX_NUM, "> ");

    printf("\n");
}

void fillRecords(Record **records, int *len)
{
    const int MAX_COUNT = 100;
    int i;

    printf("Введите количество записей\n");
    *len = scanInt(1, MAX_COUNT, "> ");

    *records = (Record *)malloc(*len * sizeof(Record));
    if (*records == NULL)
    {
        printf("Ошибка выделения памяти\n");
        *len = 0;
        return;
    }

    printf("\n");

    for (i = 0; i < *len; ++i)
        fillOneRecord(&(*records)[i], i + 1); // передаём адрес i-го элемента
}

static void showRecord(const Record *r)
{
    printf("{id=%d, name=\"%s\", value=%d}\n", r->id, r->name, r->value);
}

void writeTextSorted()
{
    printf("\n====== ОТСОРТИРОВАННЫЙ МАССИВ (по id) ======\n");
}

void writeTextUnsorted()
{
    printf("\n====== ИСХОДНЫЙ МАССИВ ======\n");
}

void showRecords(const Record *records, int len)
{
    int i;
    i = 0;

    if (len == 0)
    {
        printf("Массив пуст\n");
        return;
    }

    for (i = 0; i < len; ++i)
    {
        printf("[%3d] ", i + 1);
        showRecord(&records[i]);
    }
}

/* ================================================================
   copyRecords
   ================================================================ */
void copyRecords(const Record *src, Record *dst, int len)
{
    int i;
    i = 0;

    for (i = 0; i < len; ++i)
        dst[i] = src[i];
}

/* ================================================================
   swapRecords / findMinIdx / sortById
   ================================================================ */
static void swapRecords(Record *a, Record *b)
{
    Record tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

static int findMinIdIdx(const Record *records, int from, int len)
{
    int minIdx, j;
    minIdx = from;
    j = from + 1;

    for (j = from + 1; j < len; ++j)
    {
        if (records[j].id < records[minIdx].id)
            minIdx = j;
    }

    return minIdx;
}

static int findMinValueIdx(const Record *records, int from, int len)
{
    int minIdx, j;
    minIdx = from;
    j = from + 1;

    for (j = from + 1; j < len; ++j)
    {
        if (records[j].value < records[minIdx].value)
            minIdx = j;
    }

    return minIdx;
}

/* ================================================================
   findMinNameIdx — поиск индекса минимального по name
   ================================================================ */
static int findMinNameIdx(const Record *records, int from, int len)
{
    int minIdx, j;
    minIdx = from;

    for (j = from + 1; j < len; ++j)
    {
        if (strcasecmp(records[j].name, records[minIdx].name) < 0)
            minIdx = j;
    }
    return minIdx;
}

/* ================================================================
   sortByName — сортировка массива по полю name (лексикографически)
   ================================================================ */
void sortByName(Record *records, int len)
{
    int i, minIdx;

    for (i = 0; i < len; ++i)
    {
        minIdx = findMinNameIdx(records, i, len);
        if (minIdx != i)
            swapRecords(&records[i], &records[minIdx]);
    }
}

void sortById(Record *records, int len)
{
    int i, minIdx;
    i = 0;
    minIdx = 0;

    for (i = 0; i < len; ++i)
    {
        minIdx = findMinIdIdx(records, i, len);
        if (minIdx != i)
            swapRecords(&records[i], &records[minIdx]);
    }
}

void sortByValue(Record *records, int len)
{
    int i, minIdx;
    i = 0;
    minIdx = 0;

    for (i = 0; i < len; ++i)
    {
        minIdx = findMinValueIdx(records, i, len);
        if (minIdx != i)
            swapRecords(&records[i], &records[minIdx]);
    }
}

// Выбор метода сортировки и сама сортировка
void sortArray(Record *records, int len)
{
    int option = 0;
    printf("\nВыбирите метод сортировки:\n");
    printf(" 1 - по ID\n");
    printf(" 2 - по полю name\n");
    printf(" 3 - по value\n");
    option = scanInt(1, 3, "> ");

    switch (option)
    {
    case 1:
        sortById(records, len);
        break;
    case 2:
        sortByName(records, len);
        break;
    case 3:
        sortByValue(records, len);
        break;
    }
}

/* ================================================================
   isRecordEqual — сравнение двух записей по всем полям
   ================================================================ */
static _Bool isRecordEqual(const Record *a, const Record *b)
{
    _Bool isEqual;
    isEqual = a->id == b->id && strcasecmp(a->name, b->name) == 0 && a->value == b->value;
    return isEqual;
}

/* ================================================================
   linearSearchUnique
   Линейный поиск уникальных записей в несортированном массиве.
   Запись считается уникальной, если среди всех остальных нет
   ни одной записи с совпадением по ВСЕМ трём полям.
   Индексы уникальных кладёт в *unique, возвращает их количество.
   ================================================================ */
static _Bool hasDuplicateLinear(const Record *records, int len, int idx, SearchMetrics *m)
{
    int i;
    _Bool found;

    i = 0;
    found = 0;

    for (i = 0; i < len; ++i)
    {
        if (i != idx)
        {
            m->comparisons++;

            if (isRecordEqual(&records[i], &records[idx]))
                found = 1;
        }
    }

    return found;
}

int linearSearchUnique(const Record *records, int len, int *unique, SearchMetrics *m)
{
    int count, i;
    count = 0;
    i = 0;

    for (i = 0; i < len; i = i + 1)
    {
        if (!hasDuplicateLinear(records, len, i, m))
        {
            unique[count] = i;
            count = count + 1;
        }
    }
    return count;
}

//    binaryFindDuplicate
//    Двоичный поиск: проверяет, есть ли в отсортированном по id
//    массиве запись с тем же id (потенциальный дубликат).
//    Возвращает индекс найденного соседа или -1.
static int binaryFindById(const Record *records, int len, int targetId, int excludeIdx, SearchMetrics *m)
{
    int left, right, mid, result;

    left = 0;
    right = len - 1;
    mid = 0;
    result = -1;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        m->comparisons++;

        if (records[mid].id == targetId && mid != excludeIdx)
        {
            result = mid;
            left = right + 1;
        }
        else if (records[mid].id < targetId)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return result;
}

/* ================================================================
   binarySearchUnique
   Для каждой записи в отсортированном массиве двоичным поиском
   ищет другую запись с тем же id. Если такой нет — запись точно
   уникальна. Если id совпал — дополнительно сравниваем все поля.
   Индексы уникальных кладёт в *unique, возвращает их количество.
   ================================================================ */
/* ================================================================
findRangeById — находит левую и правую границу блока с targetId
================================================================ */
static void findRangeById(const Record records[], int len, int targetId, int *first, int *last, SearchMetrics *m)
{
    int left, right, mid;

    *first = -1;
    *last = -1;

    /* Поиск левой границы */
    left = 0;
    right = len - 1;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        m->comparisons = m->comparisons + 1;
        if (records[mid].id == targetId)
        {
            *first = mid;
            right = mid - 1;
        }
        else if (records[mid].id < targetId)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    if (*first == -1)
        return;

    /* Поиск правой границы */
    left = *first;
    right = len - 1;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        m->comparisons = m->comparisons + 1;
        if (records[mid].id == targetId)
        {
            *last = mid;
            left = mid + 1;
        }
        else if (records[mid].id < targetId)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
}

/* ================================================================
   hasFullDuplicate — проверяет, есть ли в диапазоне [first, last]
   запись, полностью равная records[idx] (кроме самой себя)
   ================================================================ */
static int hasFullDuplicate(const Record records[], int idx, int first, int last, SearchMetrics *m)
{
    int j;
    for (j = first; j <= last; j = j + 1)
    {
        if (j == idx)
        {
            /* пропускаем самого себя */
        }
        else
        {
            m->comparisons = m->comparisons + 1;
            if (isRecordEqual(&records[idx], &records[j]))
            {
                return 1;
            }
        }
    }
    return 0;
}

/* ================================================================
   binarySearchUnique — исправленная версия
   ================================================================ */
int binarySearchUnique(const Record records[], int len, int unique[], SearchMetrics *m)
{
    int i, count, first, last;
    int hasDup;

    i = 0;
    count = 0;
    first = -1;
    last = -1;
    hasDup = 0;

    for (i = 0; i < len; i = i + 1)
    {
        findRangeById(records, len, records[i].id, &first, &last, m);
        if (first == -1)
        {
            /* не должно случиться, но на всякий случай считаем уникальным */
            unique[count] = i;
            count = count + 1;
        }
        else
        {
            hasDup = hasFullDuplicate(records, i, first, last, m);
            if (hasDup == 0)
            {
                unique[count] = i;
                count = count + 1;
            }
        }
    }

    return count;
}

/* ================================================================
   showUniqueFound — вывод уникальных записей
   ================================================================ */
static void showUniqueFound(const Record *records, const int *unique, int count)
{
    int i;
    i = 0;

    if (count == 0)
    {
        printf("Уникальных записей не найдено\n");
        return;
    }

    printf("Найдено уникальных записей: %d\n", count);

    for (i = 0; i < count; ++i)
    {
        printf("  [позиция %d] ", unique[i] + 1);
        showRecord(&records[unique[i]]);
    }
}

void linearSearchStage(const Record *records, int len, SearchMetrics *m)
{
    int *unique;
    int count;

    unique = (int *)malloc(len * sizeof(int));
    if (unique == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return;
    }

    m->comparisons = 0;

    printf("\n====== ЛИНЕЙНЫЙ ПОИСК ======\n");
    printf("Поиск уникальных записей в несортированном массиве\n");
    printf("(запись уникальна, если нет другой с совпадением по всем полям)\n\n");

    count = linearSearchUnique(records, len, unique, m);

    showUniqueFound(records, unique, count);

    printf("Количество сравнений: %lld\n", m->comparisons);

    free(unique);
}
/* ================================================================
   binarySearchStage
   ================================================================ */
void binarySearchStage(const Record *sorted, int len, SearchMetrics *m)
{
    int *unique;
    int count;

    unique = (int *)malloc(len * sizeof(int));
    if (unique == NULL)
    {
        printf("Ошибка выделения памяти\n");
        return;
    }

    m->comparisons = 0;

    printf("\n====== ДВОИЧНЫЙ ПОИСК ======\n");
    printf("Поиск уникальных записей в отсортированном по id массиве\n");
    printf("(двоичным поиском ищем дубликат по id, затем сверяем все поля)\n\n");

    count = binarySearchUnique(sorted, len, unique, m);

    showUniqueFound(sorted, unique, count);

    printf("Количество сравнений: %lld\n", m->comparisons);

    free(unique);
}

static void showComparisonTable(long long linearCmp, long long binaryCmp, int len)
{
    printf("+------------------------------------+------------+\n");
    printf("| Алгоритм                           | Сравнений  |\n");
    printf("+------------------------------------+------------+\n");
    printf("| Линейный поиск  (уникальные)       | %10lld |\n", linearCmp);
    printf("| Двоичный поиск  (уникальные)       | %10lld |\n", binaryCmp);
    printf("| Размер массива                     | %10d |\n", len);
    printf("+------------------------------------+------------+\n");
}

static void showConclusion(long long linearCmp, long long binaryCmp)
{
    if (linearCmp < binaryCmp)
    {
        printf("Линейный поиск выполнил МЕНЬШЕ сравнений (%lld < %lld).\n", linearCmp, binaryCmp);
        printf("На малых массивах накладные расходы двоичного поиска\n");
        printf("(сортировка + два прохода) могут превышать выигрыш.\n");
    }
    else if (binaryCmp < linearCmp)
    {
        printf("Двоичный поиск выполнил МЕНЬШЕ сравнений (%lld < %lld).\n", binaryCmp, linearCmp);
        printf("На больших массивах преимущество O(n log n) перед O(n^2)\n");
        printf("будет возрастать кратно размеру массива.\n");
    }
    else
    {
        printf("Оба алгоритма выполнили одинаковое число сравнений (%lld).\n", linearCmp);
        printf("Совпадение характерно для малых массивов.\n");
    }

    printf("\nСложность:\n");
    printf("  Линейный поиск уникальных — O(n^2): для каждого элемента проверяются все остальные.\n");
    printf("  Двоичный поиск уникальных — O(n log n): для каждого элемента двоичный поиск дубликата по id.\n");
}

void analysisStage(long long linearCmp, long long binaryCmp, int len)
{
    printf("\n====== СРАВНИТЕЛЬНЫЙ АНАЛИЗ ======\n");
    showComparisonTable(linearCmp, binaryCmp, len);
    printf("\n");
    showConclusion(linearCmp, binaryCmp);
}

void endingAndFreeArrays(Record *original, Record *sorted)
{
    printf("\n====== ЗАВЕРШЕНИЕ ======\n");
    free(original);
    free(sorted);
}