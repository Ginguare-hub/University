#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <io.h>
#include <ctype.h>

//* Tests
_Bool checkIsFileText(char fPath[]);
_Bool canRead(const char fPath[]);
_Bool canWrite(const char filePath[]);
_Bool checkIsEmpty(const char filePath[]);
_Bool checkMyFile(char fPath[], _Bool isToRead);
//*

//* Service
void printPurpose();
void showMenu();
int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[]);
void askTheFilePath(char *buffer, int bufferSize);
void assignFile(char *fPath, int pathSize, _Bool isToRead);
void menuStage(int **dataArray, int *arrayLength);
void readingStage(int **dataArray, int *arraySize);

//*

//* Array operations
void fillArray(int **arr, int *len);
void fillArrayFromConsole(int **arr, int *len);
void fillArrayFromFile(int **arr, int *len);

void writeArray(const int arr[], const int n);
void writeArrayIntoConsole(const int arr[], const int n, _Bool isNumbered);
void writeArrayIntoFile(const int arr[], const int n);

//*

void swap(int **dataArray, int i, int j);
int partition(int **dataArray, const int arrayLength, int low, int high);
void quicksort(int **dataArray, const int arrayLength, int low, int high);

void reallocSafe(int **destination, int *destLen, int *newLen);
void freeSafeOneRef(int *data);
void freeSafeTwoRef(int **data);
void freeArray(int **arr, int *len);

int main(void)
{
    int *dataArray, arrayLength;

    dataArray = NULL;
    arrayLength = 0;

    setlocale(LC_ALL, "Russian");

    printPurpose();
    menuStage(&dataArray, &arrayLength);
    freeArray(&dataArray, &arrayLength);

    return 0;
}

void printPurpose()
{
    printf("Задаётся последовательность  чисел а1, а2, ... , аn. Программа реализует рекурсивную процедуру сортировки последовательности методом быстрой сортировки (Хоара)\n");
}

void showMenu()
{
    printf("0 - Выход\n");
    printf("1 - Ввести массив\n");
    printf("2 - Отсортировать массив\n");
    printf("3 - Вывести массив\n");
    printf("4 - Изменить элемент массива\n");
    printf("5 - Помощь\n");
}

void writeHelp()
{
    printf("Программа позволяет вводить массив через консоль либо через файл, выводить его в консоль либо массив, изменить отдельный элемент массива\n");
    printf("- Массив состоит из целочисленных элементов в диапазоне от -1_000_000 до 1_000_000\n");
    printf("- В файле массив должен быть представлен следующим образом: \n");
    printf("- - первый элемент это длина будущей последовательности\n");
    printf("- - с новой строки записываются элементы последовательности\n");
    printf("- Вводить значения нужно используя стандартные символы ASCII\n");
    printf("- Следите за тем, чтобы не оставлять пробелов в конце строки в файле, это может быть причиной ошибки при чтении\n");
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
        printf(myString);
        isIncorrect = 0;

        if (scanf("%d%c", &number, &ch) == 0 || !(isspace(ch) || ch == EOF))
        {
            isIncorrect = 1;
            printf("Некорректный ввод, повторите попытку\n");
            while (getchar() != '\n');
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = 1;
            printf("Число должно сходить в диапазон [%d,%d]\n", MIN_NUMBER, MAX_NUMBER);
        }

    } while (isIncorrect);

    return number;
}

_Bool checkIsFileText(char fPath[])
{
    int len;
    _Bool result;

    len = 0;
    result = 0;

    len = strlen(fPath);
    result = (len > 3 && strcmp(fPath + len - 4, ".txt") == 0);

    return result;
}

_Bool canRead(const char fPath[])
{
    FILE *testFile;
    _Bool isReady;

    isReady = 0;

    testFile = fopen(fPath, "r");

    if (testFile)
    {
        fclose(testFile);
        isReady = 1;
    }

    return isReady;
}

_Bool canWrite(const char fPath[])
{
    FILE *testFile;
    _Bool isReady;

    isReady = 0;

    testFile = fopen(fPath, "a");

    if (testFile != NULL)
    {
        fclose(testFile);
        isReady = 1;
    }

    return isReady;
}

_Bool checkIsEmpty(const char fPath[])
{
    FILE *testFile;
    _Bool isEmpty;

    isEmpty = 0;

    testFile = fopen(fPath, "r");

    isEmpty = fgetc(testFile) == EOF;

    fclose(testFile);

    return isEmpty;
}

_Bool checkMyFile(char fPath[], _Bool isToRead)
{
    const int EXIST_MODE = 0;

    FILE *testFileRead, *testFileWrite;
    _Bool isGood;

    isGood = 0;

    if (_access(fPath, EXIST_MODE) != 0)
    {
        printf("Ошибка, файл по адресу <%s> не существует или не может быть прочитан\n", fPath);
    }
    else
    {
        if (!checkIsFileText(fPath))
            printf("Ошибка, расширение файла не .txt\n");
        else 
            if (isToRead && !canRead(fPath))
                printf("Ошибка, нет доступа к чтению файла\n");
            else 
                if (!isToRead && !canWrite(fPath))
                    printf("Ошибка, нет доступа к записи в файл\n");
                else
                {
                    isGood = 1;
                    printf("Доступ к файлу получен\n");
                }
    }

    return isGood;
}

void askTheFilePath(char *buffer, int bufferSize)
{
    size_t len;

    len = 0;

    printf("Введите адрес существующего файла: ");
    fgets(buffer, bufferSize, stdin);

    len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

void assignFile(char *fPath, int pathSize, _Bool isToRead)
{
    _Bool isIncorrect;

    isIncorrect = 0;

    printf("\n====== Получение доступа к файлу ======\n");

    do
    {
        askTheFilePath(fPath, pathSize);
        isIncorrect = !checkMyFile(fPath, isToRead);
    } while (isIncorrect);
}

void reallocSafe(int **destination, int *destLen, int *newLen)
{
    int *temp = realloc(*destination, *newLen);
    
    if (temp == NULL)
        printf("Ошибка при попытке изменить массив\n");
    else
    {
        *destination = temp;
        *destLen = *newLen;
    }
}

void fillArray(int **arr, int *len)
{
    int inputMethod;

    inputMethod = 0;

    printf("0 - Ввод через консоль\n");
    printf("1 - Ввод через файл\n\n");

    inputMethod = scanInt(0, 1, "> ");

    if (inputMethod == 0)
        fillArrayFromConsole(arr, len);
    else
        fillArrayFromFile(arr, len);
}

void fillArrayFromConsole(int **arr, int *len)
{
    const int MIN_ELEMENT = -1000000;
    const int MAX_ELEMENT = 1000000;

    int testLen, i;

    testLen = 0;

    printf("\nВведите длину массива\n");
    testLen = scanInt(1, 100, "> ");

    if (*arr == NULL || arr == NULL)
    {
        *arr = (int *)malloc(testLen * sizeof(int));
        *len = testLen;
    }
    else
        reallocSafe(arr, len, &testLen);

    for (i = 0; i < *len; i++)
    {
        printf("Элемент [%d]: \n", i + 1);
        (*arr)[i] = scanInt(MIN_ELEMENT, MAX_ELEMENT, "> ");
    }
}

void fillArrayFromFile(int **arr, int *len)
{
    const int MAX_BUFFER = 255;
    const int MIN_ELEMENT = -1000000;
    const int MAX_ELEMENT =  1000000;

    char fPath[MAX_BUFFER];
    _Bool isToRead, isDataCorrect;
    FILE *dataFile;
    int i, testLen;

    isToRead = 1;
    isDataCorrect = 1;
    testLen = 0;

    assignFile(fPath, MAX_BUFFER, isToRead);
    dataFile = fopen(fPath, "r");

    if (feof(dataFile))
        isDataCorrect = 0;

    if (fscanf(dataFile, "%d", &testLen) == 1)
    {
        if (testLen < 1)
            isDataCorrect = 0;
        else
        {
            if (*arr == NULL || arr == NULL)
            {
                *arr = (int *)malloc(testLen * sizeof(int));
                *len = testLen;
            }
            else
                reallocSafe(arr, len, &testLen);
        }
    }

    for (i = 0; (i < *len) && isDataCorrect; ++i)
    {
        fscanf(dataFile, "%d", &(*arr)[i]);

        if ((*arr)[i] < MIN_ELEMENT || (*arr)[i] > MAX_ELEMENT)
            isDataCorrect = 0;

        if (i < *len - 1 && feof(dataFile)) 
            isDataCorrect = 0;
    }

    if (!feof(dataFile))
        isDataCorrect = 0;

    fclose(dataFile);

    if (!isDataCorrect)
    {
        if (arr != NULL && *arr != NULL)
            freeSafeTwoRef(arr);

        *len = 0;
        printf("Некорректные данные в указанном файле\n");
    }
}

void writeArray(const int *arr, const int n)
{
    int outputMethod;
    _Bool isNumbered;

    outputMethod = 0;
    isNumbered = 0;

    if (arr == NULL)
        printf("Массив пуст, сначала введите массив через соответствующий пункт меню\n");
    else
    {
        printf("Выберите метод вывода массива:\n");
        printf("0 - Вывод в консоль\n");
        printf("1 - Вывод в файл\n\n");

        outputMethod = scanInt(0, 1, "> ");

        if (outputMethod == 0)
            writeArrayIntoConsole(arr, n, isNumbered);
        else
            writeArrayIntoFile(arr, n);
    }
}

void writeArrayIntoConsole(const int *arr, const int n, _Bool isNumbered)
{
    int i;
    i = 0;

    printf("\nМассив:\n");

    if (isNumbered)
    {
        if (arr != NULL && n != 0)
        {
            for (i = 0; i < n; i++)
                printf("%d) %d\n", i + 1, arr[i]);

            printf("\n");
        }
        else
            printf("Ошибка состояния массива.\n");
    }
    else
    {
        if (arr != NULL && n != 0)
        {
            for (i = 0; i < n; i++)
                printf("%d ", arr[i]);

            printf("\n");
        }
        else
            printf("Ошибка состояния массива.\n");
    }
}

void writeArrayIntoFile(const int *arr, const int n)
{
    const int MAX_BUFFER = 255;

    char fPath[MAX_BUFFER];
    _Bool isToRead;
    FILE *dataFile;
    int i;

    isToRead = 0;

    assignFile(fPath, MAX_BUFFER, isToRead);
    dataFile = fopen(fPath, "w");

    fprintf(dataFile, "%d\n", n);

    for (i = 0; i < n - 1; ++i)
        fprintf(dataFile, "%d ", arr[i]);

    fprintf(dataFile, "%d", arr[n - 1]);

    fclose(dataFile);
}

void changeElement(int **arr, int *n)
{
    const int MIN_ELEMENT = -1000000;
    const int MAX_ELEMENT = 1000000;

    int newElement, index;
    _Bool isNumbered;

    newElement = 0;
    index = 0;
    isNumbered = 1;

    if (arr == NULL || *arr == NULL)
    {
        printf("Изменение массива невозможно, так как массив пуст. Сначала введите массив через соответствующий пункт меню\n");
    }
    else
    {
        writeArrayIntoConsole(*arr, *n, isNumbered);
        printf("Введите индекс элемента, который хотите изменить в диапазоне [1;%d]:\n", *n);

        index = scanInt(1, *n, "> ");

        printf("Вы хотите заменить элемент под номером %d со значением %d на новое значение:\n", index, (*arr)[index - 1]);
        newElement = scanInt(MIN_ELEMENT, MAX_ELEMENT, "> ");

        (*arr)[index - 1] = newElement;
        printf("Элемент успешно изменён.\n");
    }
}

void swap(int **dataArray, int i, int j)
{
    if (i != j)
    {
        (*dataArray)[i] = (*dataArray)[i] + (*dataArray)[j];
        (*dataArray)[j] = (*dataArray)[i] - (*dataArray)[j];
        (*dataArray)[i] = (*dataArray)[i] - (*dataArray)[j];
    }
}

int partition(int **dataArray, const int arrayLength, int low, int high)
{
    int pivot, randomIndex, i, j;
    _Bool isDoNotStop;

    randomIndex = 0;
    pivot = 0;
    i = low;
    j = high;
    isDoNotStop = 1;

    randomIndex = low + rand() % (high - low);
    pivot = (*dataArray)[randomIndex];

    while (isDoNotStop)
    {
        while ((*dataArray)[i] < pivot)
            i = i + 1;

        while ((*dataArray)[j] > pivot)
            j = j - 1;

        if (i >= j)
            isDoNotStop = 0;
        else
            swap(dataArray, i++, j--);
    }

    return j;
}

void quicksort(int **dataArray, const int arrayLength, int low, int high)
{
    int point;
    point = 0;

    if (*dataArray == NULL || dataArray == NULL)
        printf("Массив пуст, сначала введите массив через соответствующий пункт меню\n");
    else 
        if (low < high)
        {
            point = partition(dataArray, arrayLength, low, high);
            quicksort(&(*dataArray), arrayLength, low, point);
            quicksort(&(*dataArray), arrayLength, point + 1, high);
        }
}

void menuStage(int **dataArray, int *arrayLength)
{
    const int MIN_MENU = 0;
    const int MAX_MENU = 5;

    _Bool isDoNotStop;
    int menuOption;

    isDoNotStop = 1;
    menuOption = 0;

    do
    {
        printf("\n====== Меню =====\n");
        showMenu();

        printf("\n");
        menuOption = scanInt(MIN_MENU, MAX_MENU, "> ");

        if (menuOption == 1)
        {
            printf("\n====== Метод ввода ======\n");
            fillArray(&*dataArray, &*arrayLength);
        }
        else 
            if (menuOption == 2)
            {
                printf("\n====== Сортировка ======\n");
                quicksort(&*dataArray, *arrayLength, 0, *arrayLength - 1);
                if (*dataArray != NULL && dataArray != NULL)
                    printf("Сортировка произведена\n");
            }
            else 
                if (menuOption == 3)
                {
                    printf("\n====== Вывод массива ======\n");
                    writeArray(*dataArray, *arrayLength);
                }
                else 
                    if (menuOption == 4)
                    {
                        printf("\n====== Изменение элемента ======\n");
                        changeElement(&*dataArray, &*arrayLength);
                    }
                    else 
                        if (menuOption == 5)
                        {
                            printf("\n====== Помощь ======\n");
                            writeHelp();
                        }
                        else 
                            if (menuOption == 0)
                            {
                                isDoNotStop = 0;
                                printf("\n====== Выход ======\n");
                            }

    } while (isDoNotStop);
}

void freeArray(int **arr, int *len)
{
    if (!(arr == NULL || *arr == NULL))
    {
        free(*arr);
        *arr = NULL;
        *len = 0;
    }
}

void freeSafeOneRef(int *data)
{
    if (data != NULL)
    {
        free(data);
        data = NULL;    
    }
}

void freeSafeTwoRef(int **data)
{
    if (data != NULL && *data != NULL)
    {
        free(*data);
        *data = NULL;    
    }   
}