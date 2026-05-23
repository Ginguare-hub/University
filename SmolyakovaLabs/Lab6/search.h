#ifndef SEARCH_H
#define SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

typedef struct Record
{
int id;
char name[50];
int value;
} Record;

typedef struct
{
    long long comparisons;
} SearchMetrics;

int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[]);
void writePurpose(void);

void fillRecords(Record **records, int *len);

void sortArray(Record *records, int len);
void sortById(Record *records, int len);
void sortByName(Record *records, int len);
void sortByValue(Record *records, int len);
void copyRecords(const Record *src, Record *dst, int len);

void showRecords(const Record *records, int len);

int  linearSearchUnique(const Record *records, int len, int *unique, SearchMetrics *m);
int  binarySearchUnique(const Record *records, int len, int *unique, SearchMetrics *m);

void writeTextSorted();
void writeTextUnsorted();

void linearSearchStage(const Record *records, int len, SearchMetrics *m);
void binarySearchStage(const Record *sorted, int len, SearchMetrics *m);
void analysisStage(long long linearCmp, long long binaryCmp, int len);

void endingAndFreeArrays(struct Record *original, struct Record *sorted);

#endif