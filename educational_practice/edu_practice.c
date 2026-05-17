#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
 (СФ) Организовать выдачу талонов к врачу

 •Осуществлять поиск всех записей к врачу на конкретную дату
    (ФИО врача ввести с клавиатуры);

 •Осуществлять поиск записей о больном по ФИО;

 •Предусмотреть возможность добавлять, удалять и
    корректировать записи из списков, а также просматривать списки полностью.

*/

/*
Каждая запись списка содержит:
    дату,
    время,
    № очереди,
    ФИО больного (изначально поле пустое),
    номер кабинета,
    код врача.
 */

/*
 График работ содержит:
    код врача,
    специализацию врача,
    ФИО врача,
    временной диапазон работы на каждый день с понедельника по субботу.
 */

// TODO Перед удалением спрашивать подтверждение

typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct time
{
    int minute;
    int hour;
} time;

typedef struct appointment
{
    date appointmentDate;
    time appointmentTime;

    int queuePlace;

    char name[30];       // Имя
    char surname[30];    // Фамилия
    char patronymic[30]; // Отчество

    int cabinet;
    int doctorID;

    struct appointment *next;

} appointment;

typedef struct doctorSchedule
{
    int doctorID;
    char specialization[50];

    char name[30];       // Имя
    char surname[30];    // Фамилия
    char patronymic[30]; // Отчество

    int schedule[6][2]; // Индексы от 0 до 5 это дни от понедельника до субботы
                        // Первое число - старт (в минутах), второе число конец (в минутах)

    struct doctorSchedule *next;

} doctorSchedule;

void showMenu();
void showPurpose();
void writeMenuOptionHeader(int option);

int getOption();
void processUserChoice(appointment *appointmentsHead, doctorSchedule *schedulesHead);

// ! Menu function
void readDataFormFiles(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void readAppointmentsFromFile(appointment *head);
void readSchedulesFromFile(doctorSchedule *head);

void showLists(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void showAppointmentsList(appointment *appointmentsHead);
void showSchedulesList(doctorSchedule *schedulesHead);

void sortList(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void sortAppointmentsByDoctorID(appointment *appointmentsHead);
void sortAppointmentsBySurname(appointment *appointmentsHead);    
void sortSchedulesByDoctorID(doctorSchedule *schedulesHead);
void sortSchedulesBySurname(doctorSchedule *schedulesHead);
appointment* insertAppointmentSortedByDoctorID(appointment *sorted, appointment *node);
appointment* insertAppointmentSortedBySurname(appointment *sorted, appointment *node);
_Bool isAppointmentNodeBefore(const appointment *node, const appointment *other);
doctorSchedule* insertScheduleSortedByDoctorID(doctorSchedule *sorted, doctorSchedule *node);
_Bool isScheduleNodeBefore(const doctorSchedule *node, const doctorSchedule *other);
doctorSchedule* insertScheduleSortedBySurname(doctorSchedule *sorted, doctorSchedule *node);

void findData(appointment *appointmentsHead, doctorSchedule *schedulesHead);

void addDataToList(appointment *appointmentsHead, doctorSchedule *schedulesHead);
appointment *fillAppointment();
doctorSchedule *fillSchedule();

void deleteDataFromList(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void changeData(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void manageAppointments(appointment *appointmentsHead, doctorSchedule *schedulesHead);

void quitAndSave(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void saveAppointmentsToFile(appointment *head);
void saveSchedulesToFile(doctorSchedule *head);
// !

int getTimeInMinutes(int hour, int minute);

int findMaxDay(int month, int year);

int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[]);
void getTimeFromOnlyMinutes(int amountOfMinutes, int *hour, int *minute);

void freeLists(appointment *appointmentsHead, doctorSchedule *schedulesHead);

// ? To Test
int isEarlierAppointment(appointment *a, appointment *b);
void resetQueueNumbers(appointment *head);
appointment *findFirstUnassigned(appointment *head, int *cabinet);
appointment *findEarliestUnassignedInCabinet(appointment *head, int cabinet);
void numberCabinet(appointment *head, int cabinet);
void assignQueueNumbers(appointment *head);
// ?

int main(void)
{
    appointment *appointmentsHead;
    doctorSchedule *schedulesHead;

    appointmentsHead = (appointment *)malloc(sizeof(appointment));
    schedulesHead = (doctorSchedule *)malloc(sizeof(doctorSchedule));

    appointmentsHead->next = NULL;
    schedulesHead->next = NULL;

    showPurpose();
    processUserChoice(appointmentsHead, schedulesHead);
    freeLists(appointmentsHead, schedulesHead);

    return 0;
}

void processUserChoice(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option;
    _Bool isContinue;

    option = 0;
    isContinue = 1;

    while (isContinue)
    {
        option = getOption();
        writeMenuOptionHeader(option);

        switch (option)
        {
        case 1:
            readDataFormFiles(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 2:
            showLists(appointmentsHead, schedulesHead);
            break;
        case 3:
            sortList(appointmentsHead, schedulesHead);
            break;
        case 4:
            findData(appointmentsHead, schedulesHead);
            break;
        case 5:
            addDataToList(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 6:
            deleteDataFromList(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 7:
            changeData(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 8:
            manageAppointments(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 9:
            isContinue = 0;
            break;
        case 10:
            quitAndSave(appointmentsHead, schedulesHead);
            isContinue = 0;
            break;
        }
    }
}

void showMenu()
{
    printf("\n====== MENU ======\n");
    printf(" 1 - Read data from files\n");
    printf(" 2 - Show full lists\n");
    printf(" 3 - Sort\n");
    printf(" 4 - Find data\n");
    printf(" 5 - Add data to list\n");
    printf(" 6 - Delete data from list\n");
    printf(" 7 - Change data\n");
    printf(" 8 - Manage appointments\n");
    printf(" 9 - Quit without save\n");
    printf("10 - Quit and save\n");
}

void writeMenuOptionHeader(int option)
{
    printf("\n");

    switch (option)
    {
    case 1:
        printf("====== READING DATA ======");
        break;
    case 2:
        printf("====== SHOWING LISTS ======");
        break;
    case 3:
        printf("====== SORTING ======");
        break;
    case 4:
        printf("====== FINDING DATA ======");
        break;
    case 5:
        printf("====== ADDING DATA ======");
        break;
    case 6:
        printf("====== DELETING DATA ======");
        break;
    case 7:
        printf("====== CHANGING DATA ======");
        break;
    case 8:
        printf("====== MANAGING APPOINTMENTS ======");
        break;
    case 9:
        printf("====== QUITTING WITHOUT SAVE ======");
        break;
    case 10:
        printf("====== QUITTING AND SAVING ======");
        break;
    }

    printf("\n");
}

void showPurpose()
{
    printf("PURPOSE_PURPOSE_PURPOSE_PURPOSE_PURPOSE_PURPOSE_PURPOSE_PURPOSE\n");
}

int getOption()
{
    const int MAX_MENU_OPTION = 10;
    const int MIN_MENU_OPTION = 1;
    int option;
    option = 0;

    showMenu();
    option = scanInt(MIN_MENU_OPTION, MAX_MENU_OPTION, "> ");

    return option;
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
            printf("The number must be within the range [%d,%d]\n", MIN_NUMBER, MAX_NUMBER);
        }

    } while (isIncorrect);

    return number;
}

void addDataToList(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option;
    option = 0;

    appointment *apptCurr;
    doctorSchedule *schdlCurr;

    apptCurr = appointmentsHead;
    schdlCurr = schedulesHead;

    printf("To which list will the data be added?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");

    option = scanInt(1, 2, "> ");

    if (option == 1)
    {
        printf("\nThe data will be added to list of appointments\n");

        while (apptCurr->next != NULL)
            apptCurr = apptCurr->next;

        apptCurr->next = fillAppointment();
    }
    else
    {
        printf("\nThe data will be added to list of schedules\n");

        while (schdlCurr->next != NULL)
            schdlCurr = schdlCurr->next;

        schdlCurr->next = fillSchedule();
    }
}

appointment *fillAppointment()
{
    const int MAX_ID = 1000000;
    const int MAX_CABINET = 1000;
    const int MAX_MONTH = 12;
    const int MAX_YEAR = 2028;
    const int MIN_YEAR = 2026;
    const int MAX_HOUR = 23;
    const int MAX_MINUTE = 59;

    int maxDay;

    appointment *newAppointment;
    newAppointment = (appointment *)malloc(sizeof(appointment));

    if (!newAppointment)
        return NULL;

    printf("Write patient's\n");
    printf("name: ");
    scanf("%29s", newAppointment->name);
    printf("surname: ");
    scanf("%29s", newAppointment->surname);
    printf("patronymic: ");
    scanf("%29s", newAppointment->patronymic);

    printf("Write doctor's ID: ");
    newAppointment->doctorID = scanInt(0, MAX_ID, "");
    printf("Write doctor's cabinet: ");
    newAppointment->cabinet = scanInt(0, MAX_CABINET, "");

    printf("Write appointment date\n");
    printf("year: ");
    newAppointment->appointmentDate.year = scanInt(MIN_YEAR, MAX_YEAR, "");
    printf("month: ");
    newAppointment->appointmentDate.month = scanInt(1, MAX_MONTH, "");
    maxDay = findMaxDay(newAppointment->appointmentDate.month, newAppointment->appointmentDate.year);
    printf("day: ");
    newAppointment->appointmentDate.day = scanInt(1, maxDay, "");

    printf("Write appointment time\n");
    printf("hour: ");
    newAppointment->appointmentTime.hour = scanInt(0, MAX_HOUR, "");
    printf("minute: ");
    newAppointment->appointmentTime.minute = scanInt(0, MAX_MINUTE, "");

    newAppointment->queuePlace = 0;
    newAppointment->next = NULL;
    return newAppointment;
}

doctorSchedule *fillSchedule()
{
    const int MAX_ID = 1000000;
    const int MAX_HOUR = 23;
    const int MAX_MINUTE = 59;
    int counter, hour, minute;
    size_t len;

    counter = 0;
    hour = 0;
    minute = 0;

    doctorSchedule *newSchedule;
    newSchedule = (doctorSchedule *)malloc(sizeof(doctorSchedule));

    if (!newSchedule)
        return NULL;

    printf("Write doctor's\n");
    printf("name: ");
    scanf("%29s", newSchedule->name);
    printf("surname: ");
    scanf("%29s", newSchedule->surname);
    printf("patronymic: ");
    scanf("%29s", newSchedule->patronymic);

    printf("\nWrite doctor's ID: ");
    newSchedule->doctorID = scanInt(0, MAX_ID, "");

    printf("\nWrite doctor's specialization: ");
    fgets(newSchedule->specialization, sizeof(newSchedule->specialization), stdin);
    len = strlen(newSchedule->specialization);
    if (len > 0 && newSchedule->specialization[len - 1] == '\n')
        newSchedule->specialization[len - 1] = '\0';
    printf("%s\n", newSchedule->specialization);

    printf("Write doctor's schedule for each working day (Monday to Saturday):\n");
    char *dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    for (counter = 0; counter < 6; counter++)
    {
        printf("\n%s\n", dayNames[counter]);
        printf("start:\n");
        hour = scanInt(0, MAX_HOUR, "    hour: ");
        minute = scanInt(0, MAX_MINUTE, "    minute: ");
        newSchedule->schedule[counter][0] = getTimeInMinutes(hour, minute);

        printf("end:\n");
        hour = scanInt(0, MAX_HOUR, "    hour: ");
        minute = scanInt(0, MAX_MINUTE, "    minute: ");
        newSchedule->schedule[counter][1] = getTimeInMinutes(hour, minute);
    }

    newSchedule->next = NULL;
    return newSchedule;
}

void readDataFormFiles(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    readAppointmentsFromFile(appointmentsHead);
    readSchedulesFromFile(schedulesHead);
}

void readAppointmentsFromFile(appointment *head)
{
    size_t read;
    FILE *appFile;
    appointment *last, *newNode;
    _Bool isMore;

    isMore = 1;
    read = 0;

    appFile = fopen("appointments.bin", "rb");

    if (appFile == NULL)
    {
        printf("No appointments.bin found, starting with empty list\n");
        return;
    }

    last = head;
    while (last->next != NULL)
        last = last->next;

    while (isMore)
    {
        newNode = (appointment *)malloc(sizeof(appointment));

        if (newNode == NULL)
        {
            printf("Memory allocation error while reading appointments\n");
            isMore = 0;
        }
        else
        {
            read = fread(&newNode->appointmentDate, sizeof(date), 1, appFile);
            read = read + fread(&newNode->appointmentTime, sizeof(time), 1, appFile);
            read = read + fread(&newNode->queuePlace, sizeof(int), 1, appFile);
            read = read + fread(newNode->name, sizeof(newNode->name), 1, appFile);
            read = read + fread(newNode->surname, sizeof(newNode->surname), 1, appFile);
            read = read + fread(newNode->patronymic, sizeof(newNode->patronymic), 1, appFile);
            read = read + fread(&newNode->cabinet, sizeof(int), 1, appFile);
            read = read + fread(&newNode->doctorID, sizeof(int), 1, appFile);

            if (read != 8)
            {
                free(newNode);
                isMore = 0;
            }
            else
            {
                newNode->next = NULL;
                last->next = newNode;
                last = newNode;
            }
        }
    }

    fclose(appFile);
    printf("Appointments loaded from appointments.bin\n");
}

void readSchedulesFromFile(doctorSchedule *head)
{
    FILE *schFile;
    doctorSchedule *last, *newNode;
    _Bool isMore;
    size_t read;

    isMore = 1;
    read = 0;

    schFile = fopen("schedules.bin", "rb");

    if (schFile == NULL)
    {
        printf("No schedules.bin found, starting with empty list\n");
        return;
    }

    last = head;
    while (last->next != NULL)
        last = last->next;

    while (isMore)
    {
        newNode = (doctorSchedule *)malloc(sizeof(doctorSchedule));
        if (newNode == NULL)
        {
            printf("Memory allocation error while reading schedules\n");
            isMore = 0;
        }
        else
        {
            read = fread(&newNode->doctorID, sizeof(int), 1, schFile);
            read = read + fread(newNode->specialization, sizeof(newNode->specialization), 1, schFile);
            read = read + fread(newNode->name, sizeof(newNode->name), 1, schFile);
            read = read + fread(newNode->surname, sizeof(newNode->surname), 1, schFile);
            read = read + fread(newNode->patronymic, sizeof(newNode->patronymic), 1, schFile);
            read = read + fread(newNode->schedule, sizeof(newNode->schedule), 1, schFile);

            if (read != 6)
            {
                free(newNode);
                isMore = 0;
            }
            else
            {
                newNode->next = NULL;
                last->next = newNode;
                last = newNode;
            }
        }
    }

    fclose(schFile);
    printf("Schedules loaded from schedules.bin\n");
}

void showLists(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option;

    printf("\nWhich list do you want to view?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");
    option = scanInt(1, 2, "> ");

    if (option == 1)
    {
        showAppointmentsList(appointmentsHead);
    }
    else
    {
        showSchedulesList(schedulesHead);
    }
}

void showAppointmentsList(appointment *appointmentsHead)
{
    appointment *curr;
    int count;

    curr = appointmentsHead->next; // пропускаем фиктивный головной узел
    count = 1;

    printf("\n========== APPOINTMENTS LIST ==========\n");

    if (curr == NULL)
    {
        printf("No appointments found.\n");
        return;
    }

    while (curr != NULL)
    {
        printf("\n--- Appointment #%d ---\n", count);
        printf("Date: %02d.%02d.%04d\n",
               curr->appointmentDate.day,
               curr->appointmentDate.month,
               curr->appointmentDate.year);
        printf("Time: %02d:%02d\n",
               curr->appointmentTime.hour,
               curr->appointmentTime.minute);
        printf("Queue number: %d\n", curr->queuePlace);
        printf("Patient: %s %s %s\n",
               curr->surname, curr->name, curr->patronymic);
        printf("Cabinet: %d\n", curr->cabinet);
        printf("Doctor ID: %d\n", curr->doctorID);

        curr = curr->next;
        count++;
    }
}

void showSchedulesList(doctorSchedule *schedulesHead)
{
    doctorSchedule *curr;
    int i, count, startHour, startMinute, endHour, endMinute;
    char *dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    curr = schedulesHead->next; // пропускаем фиктивный головной узел
    count = 1;

    printf("\n========== DOCTOR SCHEDULES LIST ==========\n");

    if (curr == NULL)
    {
        printf("No schedules found.\n");
        return;
    }

    while (curr != NULL)
    {
        printf("\n--- Doctor #%d ---\n", count);
        printf("ID: %d\n", curr->doctorID);
        printf("Specialization: %s\n", curr->specialization);
        printf("Full name: %s %s %s\n", curr->surname, curr->name, curr->patronymic);
        printf("Working schedule (Monday to Saturday):\n");

        for (i = 0; i < 6; i++)
        {
            getTimeFromOnlyMinutes(curr->schedule[i][0], &startHour, &startMinute);
            getTimeFromOnlyMinutes(curr->schedule[i][1], &endHour, &endMinute);
            printf("  %-9s: %02d:%02d - %02d:%02d\n", dayNames[i], startHour, startMinute, endHour, endMinute);
        }

        curr = curr->next;
        count++;
    }
}

// Сортировки
void sortList(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int optionList, optionSort;

    printf("\nWhich list do you want to sort?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");
    optionList = scanInt(1, 2, "> ");

    printf("\nHow do you want to sort the list?\n");
    printf(" 1 - Sort by doctorID\n");
    printf(" 2 - Sort by surname\n");
    optionSort = scanInt(1, 2, "> ");
    
    if (optionList == 1)
    {
        if (optionSort == 1)
            sortAppointmentsByDoctorID(appointmentsHead);
        else
            sortAppointmentsBySurname(appointmentsHead);    
    }
    else
    {
        if (optionSort == 1)
            sortSchedulesByDoctorID(schedulesHead);
        else
            sortSchedulesBySurname(schedulesHead); 
    }

}

// Сортировка appointments по doctorID
void sortAppointmentsByDoctorID(appointment *appointmentsHead)
{
    appointment *sorted;
    appointment *current;
    appointment *next;

    sorted = NULL;
    current = appointmentsHead->next;

    if (current == NULL || current->next == NULL)
    {
        return;                     /* нечего сортировать */
    }

    while (current != NULL)
    {
        next = current->next;
        sorted = insertAppointmentSortedByDoctorID(sorted, current);
        current = next;
    }

    appointmentsHead->next = sorted;
}

appointment* insertAppointmentSortedByDoctorID(appointment *sorted, appointment *node)
{
    appointment *prev;
    appointment *curr;
    _Bool isSearching;

    if (sorted == NULL)
    {
        node->next = NULL;
        sorted = node;
    }
    else
    {
        prev = NULL;
        curr = sorted;
        isSearching = 1;

        while (isSearching)
        {
            if (curr == NULL)
            {
                isSearching = 0;
            }
            else
            {
                if (node->doctorID <= curr->doctorID)
                {
                    isSearching = 0;
                }
                else
                {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }

        if (prev == NULL)
        {
            node->next = sorted;
            sorted = node;
        }
        else
        {
            node->next = curr;
            prev->next = node;
        }
    }

    return sorted;
}

// Сортировка appointments по фамилии
void sortAppointmentsBySurname(appointment *appointmentsHead)
{
    appointment *sorted;
    appointment *current;
    appointment *next;

    sorted = NULL;
    current = appointmentsHead->next;

    if (current == NULL || current->next == NULL)
        return;

    while (current != NULL)
    {
        next = current->next;
        sorted = insertAppointmentSortedBySurname(sorted, current);
        current = next;
    }

    appointmentsHead->next = sorted;
}  

appointment* insertAppointmentSortedBySurname(appointment *sorted, appointment *node)
{
    appointment *prev;
    appointment *curr;
    _Bool isSearching;

    if (sorted == NULL)
    {
        node->next = NULL;
        sorted = node;
        return sorted;
    }

    prev = NULL;
    curr = sorted;
    isSearching = 1;

    while (isSearching)
    {
        if (curr == NULL)
        {
            isSearching = 0;
        }
        else
        {
            if (isAppointmentNodeBefore(node, curr))
            {
                isSearching = 0;     
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    if (prev == NULL)
    {
        node->next = sorted;
        sorted = node;
    }
    else
    {
        node->next = curr;
        prev->next = node;
    }

    return sorted;
}

_Bool isAppointmentNodeBefore(const appointment *node, const appointment *other)
{
    int cmpSurname;
    int cmpName;
    int cmpPatronymic;
    _Bool isBefore;

    cmpSurname = strcasecmp(node->surname, other->surname);

    if (cmpSurname < 0)
    {
        isBefore = 1;
    }
    else
    {
        if (cmpSurname > 0)
        {
            isBefore = 0;
        }
        else
        {
            cmpName = strcasecmp(node->name, other->name);
            if (cmpName < 0)
            {
                isBefore = 1;
            }
            else
            {
                if (cmpName > 0)
                {
                    isBefore = 0;
                }
                else
                {
                    cmpPatronymic = strcasecmp(node->patronymic, other->patronymic);
                    if (cmpPatronymic < 0)
                    {
                        isBefore = 1;
                    }
                    else
                    {
                        isBefore = 0;
                    }
                }
            }
        }
    }

    return isBefore;
}

// Сортировка schedules по doctorID
void sortSchedulesByDoctorID(doctorSchedule *schedulesHead)
{
    doctorSchedule *sorted;
    doctorSchedule *current;
    doctorSchedule *next;

    sorted = NULL;
    current = schedulesHead->next;

    if (current == NULL || current->next == NULL)
        return;

    while (current != NULL)
    {
        next = current->next;
        sorted = insertScheduleSortedByDoctorID(sorted, current);
        current = next;
    }

    schedulesHead->next = sorted;
}

doctorSchedule* insertScheduleSortedByDoctorID(doctorSchedule *sorted, doctorSchedule *node)
{
    doctorSchedule *prev;
    doctorSchedule *curr;
    _Bool isSearching;

    if (sorted == NULL)
    {
        node->next = NULL;
        sorted = node;
    }
    else
    {
        prev = NULL;
        curr = sorted;
        isSearching = 1;

        while (isSearching)
        {
            if (curr == NULL)
            {
                isSearching = 0;
            }
            else
            {
                if (node->doctorID <= curr->doctorID)
                {
                    isSearching = 0;
                }
                else
                {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }

        if (prev == NULL)
        {
            node->next = sorted;
            sorted = node;
        }
        else
        {
            node->next = curr;
            prev->next = node;
        }
    }

    return sorted;
}

// Сортировка schedules по фамилии
void sortSchedulesBySurname(doctorSchedule *schedulesHead)
{
    doctorSchedule *sorted;
    doctorSchedule *current;
    doctorSchedule *next;

    sorted = NULL;
    current = schedulesHead->next;

    if (current == NULL || current->next == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        next = current->next;
        sorted = insertScheduleSortedBySurname(sorted, current);
        current = next;
    }

    schedulesHead->next = sorted;
}

doctorSchedule* insertScheduleSortedBySurname(doctorSchedule *sorted, doctorSchedule *node)
{
    doctorSchedule *prev;
    doctorSchedule *curr;
    _Bool isSearching;

    if (sorted == NULL)
    {
        node->next = NULL;
        sorted = node;
        return sorted;
    }

    prev = NULL;
    curr = sorted;
    isSearching = 1;

    while (isSearching)
    {
        if (curr == NULL)
        {
            isSearching = 0;
        }
        else
        {
            if (isScheduleNodeBefore(node, curr))
            {
                isSearching = 0;       /* место перед curr найдено */
            }
            else
            {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    if (prev == NULL)
    {
        node->next = sorted;
        sorted = node;
    }
    else
    {
        node->next = curr;
        prev->next = node;
    }

    return sorted;
}

_Bool isScheduleNodeBefore(const doctorSchedule *node, const doctorSchedule *other)
{
    int cmpSurname;
    int cmpName;
    int cmpPatronymic;
    _Bool isBefore;

    cmpSurname = strcasecmp(node->surname, other->surname);

    if (cmpSurname < 0)
        isBefore = 1;
    else
    {
        if (cmpSurname > 0)
            isBefore = 0;
        else
        {
            cmpName = strcasecmp(node->name, other->name);

            if (cmpName < 0)
                isBefore = 1;
            else
            {
                if (cmpName > 0)
                    isBefore = 0;
                else
                {
                    cmpPatronymic = strcasecmp(node->patronymic, other->patronymic);
                    if (cmpPatronymic < 0)
                        isBefore = 1;
                    else
                        isBefore = 0;
                }
            }
        }
    }

    return isBefore;
}




void findData(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
}

void deleteDataFromList(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
}

void changeData(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
}

void manageAppointments(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
}

void quitAndSave(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    saveAppointmentsToFile(appointmentsHead);
    saveSchedulesToFile(schedulesHead);
    printf("\nData saved successfully\n");
}

void saveAppointmentsToFile(appointment *head)
{
    FILE *file;
    appointment *curr;

    file = fopen("appointments.bin", "wb");

    if (file == NULL)
    {
        printf("Error: cannot create appointments.bin\n");
        return;
    }

    curr = head->next;
    while (curr != NULL)
    {
        // пишем все поля, кроме указателя next
        fwrite(&curr->appointmentDate, sizeof(date), 1, file);
        fwrite(&curr->appointmentTime, sizeof(time), 1, file);
        fwrite(&curr->queuePlace, sizeof(int), 1, file);
        fwrite(curr->name, sizeof(curr->name), 1, file);
        fwrite(curr->surname, sizeof(curr->surname), 1, file);
        fwrite(curr->patronymic, sizeof(curr->patronymic), 1, file);
        fwrite(&curr->cabinet, sizeof(int), 1, file);
        fwrite(&curr->doctorID, sizeof(int), 1, file);

        curr = curr->next;
    }

    fclose(file);
}

void saveSchedulesToFile(doctorSchedule *head)
{
    FILE *file;
    doctorSchedule *curr;

    file = fopen("schedules.bin", "wb");

    if (file == NULL)
    {
        printf("Error: cannot create schedules.bin\n");
        return;
    }

    curr = head->next; // пропускаем фиктивный узел
    while (curr != NULL)
    {
        fwrite(&curr->doctorID, sizeof(int), 1, file);
        fwrite(curr->specialization, sizeof(curr->specialization), 1, file);
        fwrite(curr->name, sizeof(curr->name), 1, file);
        fwrite(curr->surname, sizeof(curr->surname), 1, file);
        fwrite(curr->patronymic, sizeof(curr->patronymic), 1, file);
        fwrite(curr->schedule, sizeof(curr->schedule), 1, file); // массив 6x2 int

        curr = curr->next;
    }

    fclose(file);
}

int findMaxDay(int month, int year)
{
    int maxDayInEachMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Индекс = месяц - 1; значение = max количество дней
    int maxDay;

    maxDay = maxDayInEachMonth[month - 1];

    if (month == 2 && (year % 4 == 0 && year % 100 != 0 || year % 400 == 0))
        maxDay++;

    return maxDay;
}

int getTimeInMinutes(int hour, int minute)
{
    int answer;
    answer = hour * 60 + minute;
    return answer;
}

void getTimeFromOnlyMinutes(int amountOfMinutes, int *hour, int *minute)
{
    *hour = amountOfMinutes / 60;
    *minute = amountOfMinutes % 60;
}

void freeLists(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    appointment *apptCurr, *apptNext;
    doctorSchedule *schCurr, *schNext;

    // Освобождение списка записей
    apptCurr = appointmentsHead;
    while (apptCurr != NULL)
    {
        apptNext = apptCurr->next;
        free(apptCurr);
        apptCurr = apptNext;
    }

    // Освобождение списка расписаний
    schCurr = schedulesHead;
    while (schCurr != NULL)
    {
        schNext = schCurr->next;
        free(schCurr);
        schCurr = schNext;
    }
}

// --------------------------------------------------------------
// Сравнение двух талонов: возвращает 1, если a раньше b, иначе 0
// --------------------------------------------------------------
int isEarlierAppointment(appointment *a, appointment *b)
{
    int aTime;
    int bTime;

    bTime = 0;
    aTime = 0;

    if (a->appointmentDate.year != b->appointmentDate.year)
        return (a->appointmentDate.year < b->appointmentDate.year);

    if (a->appointmentDate.month != b->appointmentDate.month)
        return (a->appointmentDate.month < b->appointmentDate.month);

    if (a->appointmentDate.day != b->appointmentDate.day)
        return (a->appointmentDate.day < b->appointmentDate.day);

    aTime = getTimeInMinutes(a->appointmentTime.hour, a->appointmentTime.minute);
    bTime = getTimeInMinutes(b->appointmentTime.hour, b->appointmentTime.minute);
    return (aTime < bTime);
}

// --------------------------------------------------------------
// Сброс всех номеров очереди (кроме фиктивной головы)
// --------------------------------------------------------------
void resetQueueNumbers(appointment *head)
{
    appointment *curr;

    curr = head->next;

    while (curr != NULL)
    {
        curr->queuePlace = 0;
        curr = curr->next;
    }
}

// --------
// Находит ПЕРВЫЙ непронумерованный талон и возвращает его кабинет
// --------
appointment *findFirstUnassigned(appointment *head, int *cabinet)
{
    appointment *curr = NULL;
    appointment *found = NULL;

    *cabinet = 0;
    curr = head->next;

    while (curr != NULL && found == NULL)
    {
        if (curr->queuePlace == 0)
        {
            *cabinet = curr->cabinet;
            found = curr;
        }
        curr = curr->next;
    }
    return found;
}

// --------------------------------------------------------------
// Находит самый ранний непронумерованный талон в заданном кабинете
// --------------------------------------------------------------
appointment *findEarliestUnassignedInCabinet(appointment *head, int cabinet)
{
    appointment *curr;
    appointment *earliest;

    curr = head->next;
    earliest = NULL;

    while (curr != NULL)
    {
        if (curr->cabinet == cabinet && curr->queuePlace == 0)
        {
            if (earliest == NULL)
                earliest = curr;
            else if (isEarlierAppointment(curr, earliest))
                earliest = curr;
        }
        curr = curr->next;
    }
    return earliest;
}

// --------------------------------------------------------------
// Нумерует все талоны одного кабинета по порядку времени
// --------------------------------------------------------------
void numberCabinet(appointment *head, int cabinet)
{
    int nextNumber;
    appointment *earliest;

    nextNumber = 1;
    earliest = NULL;

    earliest = findEarliestUnassignedInCabinet(head, cabinet);
    while (earliest != NULL)
    {
        earliest->queuePlace = nextNumber;
        nextNumber = nextNumber + 1;
        earliest = findEarliestUnassignedInCabinet(head, cabinet);
    }
}

// --------------------------------------------------------------
// Главная функция: полностью пересчитывает номера очереди для всех талонов
// --------------------------------------------------------------
void assignQueueNumbers(appointment *head)
{
    int cabinet;
    appointment *first;

    cabinet = 0;
    first = NULL;

    resetQueueNumbers(head);

    first = findFirstUnassigned(head, &cabinet);
    while (first != NULL)
    {
        numberCabinet(head, cabinet);
        first = findFirstUnassigned(head, &cabinet);
    }
}
