#include "stdio.h"
#include "locale.h"
#include "malloc.h"

int findDayOfWeek(int day, int month, int year);

 int main(void) 
{
    int dayOfWeek;
    dayOfWeek = -1;

    dayOfWeek = findDayOfWeek(23, 3, 2028);

    printf("Day of week: %d\n", dayOfWeek);

    return 0;
}

int findMaxDay(int month, int year)
{
    int maxDayInEachMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // »ндекс = мес€ц - 1; значение = max количество дней
    int maxDay;

    maxDay = maxDayInEachMonth[month - 1];

    if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
        maxDay++;

    return maxDay;
}

int findDayOfWeek(int day, int month, int year)
{
    int totalDays, yearCounter, monthCounter, startDay2026, dayOfWeek;

    totalDays = 0;
    startDay2026 = 3;

    for (yearCounter = 2026; yearCounter < year; yearCounter++)
        if ((yearCounter % 4 == 0 && yearCounter % 100 != 0) || (yearCounter % 400 == 0))
            totalDays = totalDays + 366;
        else
            totalDays = totalDays + 365;


    for (monthCounter = 1; monthCounter < month; monthCounter++) 
        totalDays = totalDays + findMaxDay(monthCounter, year);

    totalDays = totalDays + day;

    dayOfWeek = (startDay2026 + totalDays - 1) % 7;

    return dayOfWeek;
}