// Программа должна:
// 1. Сформировать массив записей.
// 2. Выполнить сортировку массива по ключевому полю.
// 3. Реализовать:
//     o линейный поиск;
//     o двоичный поиск.
// 4. Выполнить поиск в соответствии с вариантом.
// 5. Подсчитать количество обращений (сравнений).
// 6. Сравнить эффективность алгоритмов

// Программа должна выводить:
// • исходный массив;
// • отсортированный массив;
// • результат поиска;
// • количество обращений для каждого алгоритма;
// • сравнительный анализ.

// 20 Найти уникальные записи

// ! ================================================================

#include "search.h"
 
int main(void)
{
    Record *original;
    Record *sorted;
    SearchMetrics linearM;
    SearchMetrics binaryM;
    int len;
 
    linearM.comparisons = 0;
    binaryM.comparisons = 0;
    len = 0;
 
    setlocale(LC_ALL, "Russian");
 
    writePurpose();

    fillRecords(&original, &len);
    writeTextUnsorted();
    showRecords(original, len);

    linearSearchStage(original, len, &linearM);
    copyRecords(original, sorted, len);

    sortById(sorted, len);

    writeTextSorted();
    showRecords(sorted, len);

    binarySearchStage(sorted, len, &binaryM);
    analysisStage(linearM.comparisons, binaryM.comparisons, len);

    endingAndFreeArrays(original, sorted);
 
    return 0;
}