#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

/*
 (˜˜) ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜

 ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
    (˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜);

 ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ ˜˜ ˜˜˜;

 ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜, ˜˜˜˜˜˜˜ ˜
    ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜, ˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜.

*/

/*
˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜:
    ˜˜˜˜,
    ˜˜˜˜˜,
    ˜ ˜˜˜˜˜˜˜,
    ˜˜˜ ˜˜˜˜˜˜˜˜ (˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜),
    ˜˜˜˜˜ ˜˜˜˜˜˜˜˜,
    ˜˜˜ ˜˜˜˜˜.
 */

/*
 ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜:
    ˜˜˜ ˜˜˜˜˜,
    ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜,
    ˜˜˜ ˜˜˜˜˜,
    ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ ˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜.
 */

// TODO ˜˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜ 

typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct apptTime
{
    int minute;
    int hour;
} apptTime;

typedef struct appointment
{
    date appointmentDate;
    apptTime appointmentTime;

    int queuePlace;

    char name[17];       // ˜˜˜
    char surname[17];    // ˜˜˜˜˜˜˜
    char patronymic[17]; // ˜˜˜˜˜˜˜˜

    int cabinet;
    int doctorID;

    struct appointment *next;

} appointment;

typedef struct doctorSchedule
{
    int doctorID;
    char specialization[36];

    char name[17];       // ˜˜˜
    char surname[17];    // ˜˜˜˜˜˜˜
    char patronymic[17]; // ˜˜˜˜˜˜˜˜

    int schedule[6][2]; // ˜˜˜˜˜˜˜ ˜˜ 0 ˜˜ 5 ˜˜˜ ˜˜˜ ˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜
                        // ˜˜˜˜˜˜ ˜˜˜˜˜ - ˜˜˜˜˜ (˜ ˜˜˜˜˜˜˜), ˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜ (˜ ˜˜˜˜˜˜˜)

    struct doctorSchedule *next;

} doctorSchedule;

void showMenu();
void showPurpose();

int getOption();
void processUserChoice(appointment *appointmentsHead, doctorSchedule *schedulesHead);

// ! Menu function
void readDataFormFiles(appointment **appointmentsHead, doctorSchedule **schedulesHead);
void readAppointmentsFromFile(appointment *head);
void readSchedulesFromFile(doctorSchedule *head);

void showLists(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void showAppointmentsListHead();
void showAppointmentsListRow(int rowNumber, const appointment *curr);
int showAppointmentsList(appointment *appointmentsHead);
void showSchedulesListHead();
void showSchedulesListRow(int rowNumber, const doctorSchedule *curr);
int showSchedulesList(doctorSchedule *schedulesHead);

void sortList(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void sortAppointmentsByDoctorID(appointment *appointmentsHead);
void sortAppointmentsBySurname(appointment *appointmentsHead);
void sortSchedulesByDoctorID(doctorSchedule *schedulesHead);
void sortSchedulesBySurname(doctorSchedule *schedulesHead);
appointment *insertAppointmentSortedByDoctorID(appointment *sorted, appointment *node);
appointment *insertAppointmentSortedBySurname(appointment *sorted, appointment *node);
_Bool isAppointmentNodeBefore(const appointment *node, const appointment *other);
doctorSchedule *insertScheduleSortedByDoctorID(doctorSchedule *sorted, doctorSchedule *node);
_Bool isScheduleNodeBefore(const doctorSchedule *node, const doctorSchedule *other);
doctorSchedule *insertScheduleSortedBySurname(doctorSchedule *sorted, doctorSchedule *node);

void findData(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void findAllAppointmentsByDoctorNameAndDate(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void inputFullName(char *surname, char *name, char *patronymic);
void inputDate(int *day, int *month, int *year);
int findDoctorIDsByFullName(doctorSchedule *head, const char *surname, const char *name, const char *patronymic);
void findAllAppointmentsByPatientName(appointment *appointmentsHead);

void addDataToList(appointment *appointmentsHead, doctorSchedule *schedulesHead);
appointment *fillAppointment();
doctorSchedule *fillSchedule();

void deleteDataFromList(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void deleteFromAppointmentsList(appointment *appointmentsHead, int count);
void deleteFromSchedulesList(doctorSchedule *schedulesHead, int count);
_Bool checkIsClientSureToDelete(int index);

void changeData(appointment *appointmentsHead, doctorSchedule *schedulesHead);
int chooseWhatToChangeAsAppointment();
void changeFromAppointmentsList(appointment *appointmentsHead, int count);
int chooseWhatToChangeAsSchedule();
void changeFromSchedulesList(doctorSchedule *schedulesHead, int count);

void manageAppointments(appointment *appointmentsHead, doctorSchedule *schedulesHead);
appointment *bookAnAppointment(doctorSchedule *selectedDoctor, appointment *appointmentsHead, date startDate);
date chooseDateForBook(doctorSchedule *selectedDoctor, date startDate);
void incrementDate(date *someDate);
int chooseStartTimeOfAppointment(doctorSchedule* selectedDoctor, date chosenDate, appointment* appointmentHead);
_Bool checkIsWorkingDay(doctorSchedule *selectedDoctor, date chosenDate);
_Bool checkIsSlotFree(appointment *appointmentHead, int doctorID, date currDate, int start, int end);


void quitAndSave(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void saveAppointmentsToFile(appointment *head);
void saveSchedulesToFile(doctorSchedule *head);
void saveAppointmentToTextFile(const appointment *appt, const doctorSchedule *doctor);
// !

int findMaxDay(int month, int year);
int findDayOfWeek(int day, int month, int year);
void getTimeFromOnlyMinutes(int amountOfMinutes, int *hour, int *minute);
int getTimeInMinutes(int hour, int minute);
doctorSchedule *getDoctorByIndex(doctorSchedule *head, int index);
appointment *getAppointmentByIndex(appointment *head, int index);
doctorSchedule *getScheduleByIndex(doctorSchedule *head, int index);


int scanInt(const int MIN_NUMBER, const int MAX_NUMBER, const char myString[]);
void freeLists(appointment *appointmentsHead, doctorSchedule *schedulesHead);
void appendAppointment(appointment *head, appointment *appendedAppointment);
void appendSchedule(doctorSchedule *head, doctorSchedule *appendedSchedule);

int checkIsEarlierAppointment(appointment *a, appointment *b);
void resetQueueNumbers(appointment *head);
appointment *findFirstUnassigned(appointment *head, int *cabinet);
appointment *findEarliestUnassignedInCabinet(appointment *head, int cabinet);
void numberCabinet(appointment *head, int cabinet);
void assignQueueNumbers(appointment *head);

int main(void)
{
    srand(time(NULL));

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

        switch (option)
        {
        case 1:
            printf("\n====== READING DATA ======\n");
            readDataFormFiles(&appointmentsHead, &schedulesHead);
            assignQueueNumbers(appointmentsHead);
            showAppointmentsList(appointmentsHead);
            showSchedulesList(schedulesHead);
            break;
        case 2:
            printf("\n====== SHOWING LISTS ======\n");
            showLists(appointmentsHead, schedulesHead);
            break;
        case 3:
            printf("\n====== SORTING ======\n");
            sortList(appointmentsHead, schedulesHead);
            break;
        case 4:
            printf("\n====== FINDING DATA ======\n");
            findData(appointmentsHead, schedulesHead);
            break;
        case 5:
            printf("\n====== ADDING DATA ======\n");
            addDataToList(appointmentsHead, schedulesHead);
            break;
        case 6:
            printf("\n====== DELETING DATA ======\n");
            deleteDataFromList(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 7:
            printf("\n====== CHANGING DATA ======\n");
            changeData(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 8:
            printf("\n====== MANAGING APPOINTMENTS ======\n");
            manageAppointments(appointmentsHead, schedulesHead);
            assignQueueNumbers(appointmentsHead);
            break;
        case 9:
            printf("\n====== QUITTING WITHOUT SAVE ======\n");
            isContinue = 0;
            break;
        case 10:
            printf("\n====== QUITTING AND SAVING ======\n");
            quitAndSave(appointmentsHead, schedulesHead);
            isContinue = 0;
            break;
        }
    }
}

void showMenu()
{
    printf("\n========== MENU ==========\n");
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

void showPurpose()
{
    printf("=============================================================\n");
    printf("   Clinic Appointment Management System\n");
    printf("=============================================================\n");
    printf(" This program automates patient appointment scheduling\n");
    printf(" for a polyclinic.\n");
    printf("\n");
    printf(" Key features:\n");
    printf("  - Book appointments based on doctor work schedules\n");
    printf("  - Search appointments by doctor name and date\n");
    printf("  - Search appointments by patient name\n");
    printf("  - Add, edit and delete records in both lists\n");
    printf("  - Save and load data from binary files\n");
    printf("  - Export issued appointment tickets to a text file\n");
    printf("\n");
    printf(" Data is stored in two linked lists:\n");
    printf("  - Appointments  (appointments.bin)\n");
    printf("  - Doctor schedules (schedules.bin)\n");
    printf("=============================================================\n");
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

//

void addDataToList(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option;
    option = 0;

    appointment *newAppointment;
    doctorSchedule *newSchedule;

    printf("To which list will the data be added?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");

    option = scanInt(1, 2, "> ");

    if (option == 1)
    {
        printf("\nThe data will be added to list of appointments\n");

        newAppointment = fillAppointment();
        appendAppointment(appointmentsHead, newAppointment);
        assignQueueNumbers(appointmentsHead);
        showAppointmentsList(appointmentsHead);
    }
    else
    {
        printf("\nThe data will be added to list of schedules\n");
        newSchedule = fillSchedule();
        appendSchedule(schedulesHead, newSchedule);
        showSchedulesList(schedulesHead);
    }
}

appointment *fillAppointment()
{
    const int MAX_ID = 1000000;
    const int MAX_CABINET = 1000;
    const int MAX_HOUR = 23;
    const int MAX_MINUTE = 59;

    appointment *newAppointment;
    newAppointment = (appointment *)malloc(sizeof(appointment));

    if (!newAppointment)
        return NULL;

    printf("Write patient\n");
    inputFullName(newAppointment->surname, newAppointment->name, newAppointment->patronymic);

    printf("doctorID (1..%d): ", MAX_ID);
    newAppointment->doctorID = scanInt(1, MAX_ID, "");
    printf("cabinet (1..%d): ", MAX_CABINET);
    newAppointment->cabinet = scanInt(1, MAX_CABINET, "");

    printf("Write appointment date\n");
    inputDate(&newAppointment->appointmentDate.day, &newAppointment->appointmentDate.month, &newAppointment->appointmentDate.year);

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
    char *dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    counter = 0;
    hour = 0;
    minute = 0;
    len = 0;

    doctorSchedule *newSchedule;
    newSchedule = (doctorSchedule *)malloc(sizeof(doctorSchedule));

    if (!newSchedule)
        return NULL;

    printf("Write doctor\n");
    inputFullName(newSchedule->surname, newSchedule->name, newSchedule->patronymic);

    printf("doctorID (1..%d): ", MAX_ID);
    newSchedule->doctorID = scanInt(1, MAX_ID, "");

    printf("doctor specialization: ");
    fgets(newSchedule->specialization, sizeof(newSchedule->specialization), stdin);
    len = strlen(newSchedule->specialization);
    if (len > 0 && newSchedule->specialization[len - 1] == '\n')
        newSchedule->specialization[len - 1] = '\0';

    printf("Write doctor schedule for each working day (Monday to Saturday):\n");

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

//

void readDataFormFiles(appointment **appointmentsHead, doctorSchedule **schedulesHead)
{
    freeLists(*appointmentsHead, *schedulesHead);
    *appointmentsHead = (appointment *)malloc(sizeof(appointment));
    (*appointmentsHead)->next = NULL;
    *schedulesHead = (doctorSchedule *)malloc(sizeof(doctorSchedule));
    (*schedulesHead)->next = NULL;

    readAppointmentsFromFile(*appointmentsHead);
    readSchedulesFromFile(*schedulesHead);
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
            read += fread(&newNode->appointmentTime, sizeof(apptTime), 1, appFile);
            read += fread(&newNode->queuePlace, sizeof(int), 1, appFile);
            read += fread(newNode->name, sizeof(newNode->name), 1, appFile);
            read += fread(newNode->surname, sizeof(newNode->surname), 1, appFile);
            read += fread(newNode->patronymic, sizeof(newNode->patronymic), 1, appFile);
            read += fread(&newNode->cabinet, sizeof(int), 1, appFile);
            read += fread(&newNode->doctorID, sizeof(int), 1, appFile);

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

//

void showLists(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option;

    printf("\nWhich list do you want to view?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");
    option = scanInt(1, 2, "> ");

    if (option == 1)
        showAppointmentsList(appointmentsHead);
    else
        showSchedulesList(schedulesHead);
}

void showAppointmentsListHead()
{
    printf("+-----+------------+----------+-------+----------------------------------------------------+------+----------+\n");
    printf("|  #  |    Date    |     Time | Queue | Patient name                                       | Cab. | DoctorID |\n");
    printf("+-----+------------+----------+-------+----------------------------------------------------+------+----------+\n");
}

// (˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜)
int showAppointmentsList(appointment *appointmentsHead)
{
    appointment *curr;
    int count;

    curr = appointmentsHead->next;
    count = 0;

    printf("\n====== APPOINTMENTS LIST ======\n");

    if (curr == NULL)
    {
        printf("No appointments found\n");
        return count;
    }

    showAppointmentsListHead();

    while (curr != NULL)
    {
        count++;
        showAppointmentsListRow(count, curr);
        curr = curr->next;
    }

    printf("+-----+------------+----------+-------+----------------------------------------------------+------+----------+\n");
    return count;
}

void showAppointmentsListRow(int rowNumber, const appointment *curr)
{
    char fullName[51];
    snprintf(fullName, sizeof(fullName), "%s %s %s", curr->surname, curr->name, curr->patronymic);

    printf("| %3d | %02d.%02d.%04d |    %02d:%02d | %5d | %-50.50s | %4d | %8d |\n",
           rowNumber,
           curr->appointmentDate.day,
           curr->appointmentDate.month,
           curr->appointmentDate.year,
           curr->appointmentTime.hour,
           curr->appointmentTime.minute,
           curr->queuePlace,
           fullName,
           curr->cabinet,
           curr->doctorID);
}

void showSchedulesListHead()
{
    printf("+-----+----------+-------------------------------------+----------------------------------------------------+-----------+---------+---------+\n");
    printf("|  #  | DoctorID | Specialization                      | Doctor name                                        | Day       |  Start  |   End   |\n");
    printf("+-----+----------+-------------------------------------+----------------------------------------------------+-----------+---------+---------+\n");
}

// ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
int showSchedulesList(doctorSchedule *schedulesHead)
{
    doctorSchedule *curr;
    int count;

    curr = schedulesHead->next;
    count = 0;

    printf("\n====== DOCTOR SCHEDULES LIST ======\n");

    if (curr == NULL)
    {
        printf("No schedules found\n");
        return count;
    }

    showSchedulesListHead();

    while (curr != NULL)
    {
        count++;
        showSchedulesListRow(count, curr);
        printf("+-----+----------+-------------------------------------+----------------------------------------------------+-----------+---------+---------+\n");
        curr = curr->next;
    }

    return count;
}

void showSchedulesListRow(int rowNumber, const doctorSchedule *curr)
{
    char fullName[51], specialization[36];
    int i, startHour, startMinute, endHour, endMinute, firstForDoctor;
    char *dayNames[6];

    dayNames[0] = "Monday";
    dayNames[1] = "Tuesday";
    dayNames[2] = "Wednesday";
    dayNames[3] = "Thursday";
    dayNames[4] = "Friday";
    dayNames[5] = "Saturday";

    snprintf(fullName, sizeof(fullName), "%s %s %s", curr->surname, curr->name, curr->patronymic);
    snprintf(specialization, sizeof(specialization), "%s", curr->specialization);

    firstForDoctor = 1;

    for (i = 0; i < 6; i++)
    {
        if (curr->schedule[i][0] != 0 || curr->schedule[i][1] != 0)
        {
            getTimeFromOnlyMinutes(curr->schedule[i][0], &startHour, &startMinute);
            getTimeFromOnlyMinutes(curr->schedule[i][1], &endHour, &endMinute);

            if (firstForDoctor)
            {
                printf("| %3d | %8d | %-35.35s | %-50.50s | %-9s |  %02d:%02d  |  %02d:%02d  |\n",
                       rowNumber,
                       curr->doctorID,
                       specialization,
                       fullName,
                       dayNames[i],
                       startHour, startMinute,
                       endHour, endMinute);
            }
            else
            {
                printf("|     |          |                                     |                                                    | %-9s |  %02d:%02d  |  %02d:%02d  |\n",
                       dayNames[i],
                       startHour, startMinute,
                       endHour, endMinute);
            }

            firstForDoctor = 0;
        }
    }
}

//

// ˜˜˜˜˜˜˜˜˜˜
void sortList(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int optionList, optionSort;

    printf("\nWhich list do you want to sort?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");
    optionList = scanInt(1, 2, "> ");

    if (optionList == 1 && appointmentsHead->next == NULL)
    {
        printf("\nThere is no data in list of appointments\n");
        return;
    }

    if (optionList == 2 && schedulesHead->next == NULL)
    {
        printf("\nThere is no data in list of doctor schedules\n");
        return;
    }

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

        showAppointmentsList(appointmentsHead);
    }
    else
    {
        if (optionSort == 1)
            sortSchedulesByDoctorID(schedulesHead);
        else
            sortSchedulesBySurname(schedulesHead);

        showSchedulesList(schedulesHead);
    }

    printf("\nSorted\n");
}

// ˜˜˜˜˜˜˜˜˜˜ appointments ˜˜ doctorID
void sortAppointmentsByDoctorID(appointment *appointmentsHead)
{
    appointment *sorted;
    appointment *current;
    appointment *next;

    sorted = NULL;
    current = appointmentsHead->next;

    if (current == NULL || current->next == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        next = current->next;
        sorted = insertAppointmentSortedByDoctorID(sorted, current);
        current = next;
    }

    appointmentsHead->next = sorted;
}

appointment *insertAppointmentSortedByDoctorID(appointment *sorted, appointment *node)
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

// ˜˜˜˜˜˜˜˜˜˜ appointments ˜˜ ˜˜˜˜˜˜˜
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

appointment *insertAppointmentSortedBySurname(appointment *sorted, appointment *node)
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

// ˜˜˜˜˜˜˜˜˜˜ schedules ˜˜ doctorID
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

doctorSchedule *insertScheduleSortedByDoctorID(doctorSchedule *sorted, doctorSchedule *node)
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

// ˜˜˜˜˜˜˜˜˜˜ schedules ˜˜ ˜˜˜˜˜˜˜
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

doctorSchedule *insertScheduleSortedBySurname(doctorSchedule *sorted, doctorSchedule *node)
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
                isSearching = 0; /* ˜˜˜˜˜ ˜˜˜˜˜ curr ˜˜˜˜˜˜˜ */
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

//

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ findData (˜˜˜˜˜˜˜˜˜˜˜)
void findData(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option;

    printf("What data you need to find?\n");
    printf(" 1 - Find all appointments by doctor full name and date\n");
    printf(" 2 - Find all appointments by patient full name\n");
    option = scanInt(1, 2, "> ");

    if (option == 1)
        findAllAppointmentsByDoctorNameAndDate(appointmentsHead, schedulesHead);
    else
        findAllAppointmentsByPatientName(appointmentsHead);
}

void findAllAppointmentsByDoctorNameAndDate(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    char surname[17], name[17], patronymic[17];
    int day, month, year, count, doctorIDByFullName;
    appointment *curr;
    _Bool isThereNoRightAppointments;

    count = 1;
    day = 0;
    month = 0;
    year = 0;
    isThereNoRightAppointments = 1;
    doctorIDByFullName = -1;

    if (appointmentsHead->next == NULL)
    {
        printf("No appointments found. No data available for search\n");
        return;
    }

    curr = appointmentsHead;

    printf("\nEnter doctor full name to search appointments:\n");

    inputFullName(surname, name, patronymic);
    printf("\nEnter appointment date:\n");
    inputDate(&day, &month, &year);

    doctorIDByFullName = findDoctorIDsByFullName(schedulesHead, surname, name, patronymic);

    if (doctorIDByFullName == -1)
    {
        printf("No doctor with this name found\n");
        return;
    }

    printf("\n====== APPOINTMENTS FOR DOCTOR ======\n");
    printf("Doctor: %s %s %s\n", surname, name, patronymic);
    printf("Date: %02d.%02d.%04d\n", day, month, year);
    printf("\n");

    showAppointmentsListHead();

    while (curr->next != NULL)
    {
        curr = curr->next;
        if (doctorIDByFullName == curr->doctorID && curr->appointmentDate.year == year &&
            curr->appointmentDate.month == month && curr->appointmentDate.day == day)
        {
            isThereNoRightAppointments = 0;
            showAppointmentsListRow(count, curr);

            printf("+-----+------------+----------+-------+----------------------------------------------------+------+----------+\n");
            count++;
        }
    }

    if (isThereNoRightAppointments)
        printf("No appointments found\n");
}

// ˜˜˜˜ ˜˜˜
void inputFullName(char *surname, char *name, char *patronymic)
{
    printf("surname: ");
    scanf("%16s", surname);
    printf("name: ");
    scanf("%16s", name);
    printf("patronymic: ");
    scanf("%16s", patronymic);
}

// ˜˜˜˜ ˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜
void inputDate(int *day, int *month, int *year)
{
    const int MIN_YEAR = 2026;
    const int MAX_YEAR = 2028;
    const int MAX_MONTH = 12;
    int maxDay;

    maxDay = 0;
    
    printf("year (%d..%d): ", MIN_YEAR, MAX_YEAR);
    *year = scanInt(MIN_YEAR, MAX_YEAR, "");
    printf("month (1..12): ");
    *month = scanInt(1, MAX_MONTH, "");
    maxDay = findMaxDay(*month, *year);
    printf("day (1..%d): ", maxDay);
    *day = scanInt(1, maxDay, "");
}

int findDoctorIDsByFullName(doctorSchedule *head, const char *surname, const char *name, const char *patronymic)
{
    doctorSchedule *curr;
    int doctorID;
    
    curr = head;
    doctorID = -1;

    while (curr->next != NULL)
    {
        curr = curr->next;
        if (strcasecmp(curr->surname, surname) == 0 &&
            strcasecmp(curr->name, name) == 0 &&
            strcasecmp(curr->patronymic, patronymic) == 0)
        {
            doctorID = curr->doctorID;
        }
    }
    return doctorID;
}

void findAllAppointmentsByPatientName(appointment *appointmentsHead)
{
    char surname[17], name[17], patronymic[17];
    _Bool isThereNoRightAppointments;
    int count;
    appointment *curr;

    count = 1;
    isThereNoRightAppointments = 1;
    surname[0] = '\0';
    name[0] = '\0';
    patronymic[0] = '\0';
    curr = NULL;
    
    if (appointmentsHead->next == NULL)
    {
        printf("No appointments found. No data available for search\n");
        return;
    }
    
    curr = appointmentsHead;

    printf("\nEnter patient full name to search appointments:\n");

    inputFullName(surname, name, patronymic);

    printf("\n====== APPOINTMENTS BY PATIENT NAME ======\n");
    printf("Patient: %s %s %s\n", surname, name, patronymic);
    printf("\n");

    showAppointmentsListHead();

    while (curr->next != NULL)
    {
        curr = curr->next;
        if (strcasecmp(curr->surname, surname) == 0 &&
            strcasecmp(curr->name, name) == 0 &&
            strcasecmp(curr->patronymic, patronymic) == 0)
        {
            showAppointmentsListRow(count, curr);
            
            printf("+-----+------------+----------+-------+----------------------------------------------------+------+----------+\n");
            isThereNoRightAppointments = 0;
            count++;
        }
    }

    if (isThereNoRightAppointments)
        printf("No appointments found\n");
}

//

void deleteDataFromList(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option, count;

    printf("\nFrom which list do you want to delete?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");
    option = scanInt(1, 2, "> ");

    if (option == 1)
    {
        count = showAppointmentsList(appointmentsHead);
        deleteFromAppointmentsList(appointmentsHead, count);
        showAppointmentsList(appointmentsHead);
    }
    else
    {
        count = showSchedulesList(schedulesHead);
        deleteFromSchedulesList(schedulesHead, count);
        showSchedulesList(schedulesHead);
    }
}

void deleteFromAppointmentsList(appointment *appointmentsHead, int count)
{
    appointment *curr, *prev;
    int indexToDelete;

    if (count == 0)
    {
        printf("There is no data to delete in appointments list\n");
        return;
    }

    prev = appointmentsHead;
    curr = prev->next;

    printf("Write number \"#\" which you need to delete\n");
    indexToDelete = scanInt(1, count, "> ");
    
    if (checkIsClientSureToDelete(indexToDelete))
    {
        indexToDelete--;

        prev = getAppointmentByIndex(appointmentsHead, indexToDelete);
        curr = prev->next;

        prev->next = curr->next;
        free(curr);
        printf("The element was deleted\n");
    }
    else
        printf("The element was NOT deleted by user's choice\n");
}

void deleteFromSchedulesList(doctorSchedule *schedulesHead, int count)
{
    doctorSchedule *curr, *prev;
    int indexToDelete;

    indexToDelete = 0;
    prev = schedulesHead;
    curr = prev->next;

    if (count == 0)
    {
        printf("There is no data to delete in schedules list\n");
        return;
    }


    printf("Write number \"#\" which you need to delete\n");
    indexToDelete = scanInt(1, count, "> ");
    
    if (checkIsClientSureToDelete(indexToDelete + 1))
    {
        indexToDelete--;

        prev = getScheduleByIndex(schedulesHead, indexToDelete);
        curr = prev->next;

        prev->next = curr->next;
        free(curr);
        printf("The element was deleted\n");
    }
    else
        printf("The element was NOT deleted by user's choice\n");
}

_Bool checkIsClientSureToDelete(int index)
{
    int option;
    _Bool isSure;

    printf("\nAre you sure you want to delete element number <%d> ?\n", index);
    printf(" 1 - YES\n");
    printf(" 2 - NO\n");
    option = scanInt(1, 2, "> ");

    if (option == 1)
        isSure = 1;
    else
        isSure = 0;

    return isSure;
}

//

void changeData(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int option, count;

    printf("\nFrom which list do you want to change element?\n");
    printf(" 1 - Appointments list\n");
    printf(" 2 - Schedule list\n");
    option = scanInt(1, 2, "> ");

    if (option == 1)
    {
        if (appointmentsHead->next == NULL)
        {
            printf("\nThere is no data in list of appointments\n");
            return;
        }
        
        count = showAppointmentsList(appointmentsHead);
        changeFromAppointmentsList(appointmentsHead, count);
        showAppointmentsList(appointmentsHead);
    }
    else
    {
        if (schedulesHead->next == NULL)
        {
            printf("\nThere is no data in list of doctor schedules\n");
            return;
        }

        count = showSchedulesList(schedulesHead);
        changeFromSchedulesList(schedulesHead, count);
        showSchedulesList(schedulesHead);
    }
}

int chooseWhatToChangeAsAppointment()
{
    const int MAX_OPTION = 7;
    int option;

    printf("\nWhat should be changed?\n");
    printf(" 1 - Name\n");
    printf(" 2 - Surname\n");
    printf(" 3 - Patronymic\n");
    printf(" 4 - Appointment date\n");
    printf(" 5 - Appointment time\n");
    printf(" 6 - Cabinet\n");
    printf(" 7 - DoctorID\n");
    option = scanInt(1, MAX_OPTION, "> ");   

    return option;
}

void changeFromAppointmentsList(appointment *appointmentsHead, int count)
{   
    const int MAX_ID = 1000000;
    const int MAX_CABINET = 1000;
    const int MAX_HOUR = 23;
    const int MAX_MINUTE = 59;

    int optionChange, indexToChange, hour, minute;
    appointment *changed;

    optionChange = 0;
    changed = appointmentsHead;
    
    printf("\nWrite number \"#\" of patient which you need to change\n");
    indexToChange = scanInt(1, count, "> ");
    
    while (changed->next != NULL && indexToChange != 0)
    {
        changed = changed->next;
        indexToChange--;
    }

    optionChange = chooseWhatToChangeAsAppointment();
    
    if (indexToChange == 0)
    {

        switch (optionChange)
        {
        case 1:
            printf("Old name <%s>\n", changed->name);
            printf("New name: ");
            scanf("%16s", changed->name);
            break;
        case 2:
            printf("Old surname <%s>\n", changed->surname);
            printf("New surname: ");
            scanf("%16s", changed->surname);
            break;
        case 3:
            printf("Old patronymic <%s>\n", changed->patronymic);   
            printf("New patronymic: ");
            scanf("%16s", changed->patronymic);
            break;
        case 4:
            printf("Old date: <%02d.%02d.%d>\n", changed->appointmentDate.day, changed->appointmentDate.month, changed->appointmentDate.year);
            printf("New date\n");
            inputDate(&changed->appointmentDate.day, &changed->appointmentDate.month, &changed->appointmentDate.year);
            break;
        case 5:
            printf("Old time: <%02d:%02d>\n", changed->appointmentTime.hour, changed->appointmentTime.minute);
            printf("New time\n");
            printf("hour: ");
            changed->appointmentTime.hour = scanInt(0, MAX_HOUR, "");
            printf("minute: ");
            changed->appointmentTime.minute = scanInt(0, MAX_MINUTE, "");
            break;
        case 6:
            printf("Old cabinet <%d>\n", changed->cabinet);
            printf("New cabinet (1..%d): ", MAX_CABINET);
            changed->cabinet = scanInt(1, MAX_CABINET, "");
            break;
        case 7:
            printf("Old doctorID <%d>\n", changed->doctorID);
            printf("New doctorID (1..%d): ", MAX_ID);
            changed->doctorID = scanInt(1, MAX_ID, "");
            break;
        }
        
        printf("Element was changed\n");
    }
    else    
        printf("Element was NOT changed because of unexpected error\n");

    changed->queuePlace = 0;
}

int chooseWhatToChangeAsSchedule()
{
    const int MAX_OPTION = 6;
    int option;

    printf("\nWhat should be changed?\n");
    printf(" 1 - Name\n");
    printf(" 2 - Surname\n");
    printf(" 3 - Patronymic\n");
    printf(" 4 - Specialization\n");
    printf(" 5 - DoctorID\n");
    printf(" 6 - Week schedule\n");
    option = scanInt(1, MAX_OPTION, "> ");   

    return option;
}

void changeFromSchedulesList(doctorSchedule *schedulesHead, int count)
{
    const int MAX_ID = 1000000;
    const int MAX_HOUR = 23;
    const int MAX_MINUTE = 59;

    int optionChange, indexToChange, counter, hour, minute;
    doctorSchedule *changed;
    char *dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    counter = 0;
    indexToChange = 0;
    optionChange = 0;
    changed = schedulesHead;

    printf("\nWrite number \"#\" of doctor which you need to change\n");
    indexToChange = scanInt(1, count, "> ");

    counter = indexToChange;

    while (changed->next != NULL && counter != 0)
    {
        changed = changed->next;
        counter--;
    }

    optionChange = chooseWhatToChangeAsSchedule();
    
    if (counter == 0)
    {
        switch (optionChange)
        {
        case 1:
            printf("Old name <%s>\n", changed->name);
            printf("New name: ");
            scanf("%16s", changed->name);
            break;
        case 2:
            printf("Old surname <%s>\n", changed->surname);
            printf("New surname: ");
            scanf("%16s", changed->surname);
            break;
        case 3:
            printf("Old patronymic <%s>\n", changed->patronymic);   
            printf("New patronymic: ");
            scanf("%16s", changed->patronymic);
            break;
        case 4:
            printf("Old specialization <%s>\n", changed->specialization);   
            printf("New specialization: ");
            scanf("%35s", changed->specialization);
            break;
        case 5:
            printf("Old doctorID <%d>\n", changed->doctorID);
            printf("New doctorID (1..%d): ", MAX_ID);
            changed->doctorID = scanInt(1, MAX_ID, "");
            break;
        case 6:
            printf("Old week schedule\n");
            showSchedulesListHead();
            showSchedulesListRow(indexToChange, changed);
            printf("+-----+----------+-------------------------------------+----------------------------------------------------+-----------+---------+---------+\n");
            printf("\nNew week schedule\n");
            for (counter = 0; counter < 6; counter++)
            {
                printf("\n%s\n", dayNames[counter]);
                printf("start:\n");
                hour = scanInt(0, MAX_HOUR, "    hour: ");
                minute = scanInt(0, MAX_MINUTE, "    minute: ");
                changed->schedule[counter][0] = getTimeInMinutes(hour, minute);

                printf("end:\n");
                hour = scanInt(0, MAX_HOUR, "    hour: ");
                minute = scanInt(0, MAX_MINUTE, "    minute: ");
                changed->schedule[counter][1] = getTimeInMinutes(hour, minute);
            }
            break;
        }
        printf("Element was changed\n");
    }
    else
        printf("Element was NOT changed because of unexpected error\n");

}

//

void manageAppointments(appointment *appointmentsHead, doctorSchedule *schedulesHead)
{
    int doctorCount, doctorIndex, option;
    doctorSchedule *selectedDoctor;
    appointment *bookedAppointment, *curr;
    date startDate;

    doctorCount = 0;
    doctorIndex = 0;
    selectedDoctor = NULL;
    bookedAppointment = NULL;
    curr = appointmentsHead;
    option = 0;

    if (schedulesHead->next == NULL)
    {
        printf("There are no doctors to take an appointment with\n");
        return;
    }

    printf("\nEnter the starting date to display the doctor's schedule for the week: \n");
    inputDate(&(startDate.day), &(startDate.month), &(startDate.year));

    doctorCount = showSchedulesList(schedulesHead);
    printf("\nEnter the number of the doctor you want to book: \n");
    doctorIndex = scanInt(1, doctorCount, "> ");
    selectedDoctor = getDoctorByIndex(schedulesHead, doctorIndex);

    bookedAppointment = bookAnAppointment(selectedDoctor, appointmentsHead, startDate);

    if (bookedAppointment == NULL)
    {
        printf("\nAppointment was NOT booked because chosen date was holiday or by user's refuse\n");
    }
    else
    {
        appendAppointment(appointmentsHead, bookedAppointment);
        assignQueueNumbers(appointmentsHead);
        saveAppointmentToTextFile(bookedAppointment, selectedDoctor);
        showAppointmentsList(appointmentsHead);
    }
}

void saveAppointmentToTextFile(const appointment *appt, const doctorSchedule *doctor)
{
    FILE *file;
    char fullNamePatient[51];
    char fullNameDoctor[51];

    file = fopen("appointment_ticket.txt", "a"); // "a" - ˜˜˜˜˜˜˜˜˜˜, ˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜
    if (file == NULL)
    {
        printf("Error: cannot open appointment_ticket.txt\n");
        return;
    }

    snprintf(fullNamePatient, sizeof(fullNamePatient), "%s %s %s",
             appt->surname, appt->name, appt->patronymic);
    snprintf(fullNameDoctor, sizeof(fullNameDoctor), "%s %s %s",
             doctor->surname, doctor->name, doctor->patronymic);

    fprintf(file, "============================================================\n");
    fprintf(file, "                     APPOINTMENT TICKET                    \n");
    fprintf(file, "============================================================\n");
    fprintf(file, "  Patient       : %s\n", fullNamePatient);
    fprintf(file, "  Date          : %02d.%02d.%04d\n",
            appt->appointmentDate.day,
            appt->appointmentDate.month,
            appt->appointmentDate.year);

    fprintf(file, "  Time          : %02d:%02d\n",
            appt->appointmentTime.hour,
            appt->appointmentTime.minute);

    fprintf(file, "  Doctor        : %s\n", fullNameDoctor);
    fprintf(file, "  Specialization: %s\n", doctor->specialization);
    fprintf(file, "  Cabinet       : %d\n", appt->cabinet);
    fprintf(file, "  Queue number  : %d\n", appt->queuePlace);
    fprintf(file, "============================================================\n\n");

    fclose(file);
    printf("\nAppointment ticket saved to appointment_ticket.txt\n");
}

appointment *bookAnAppointment(doctorSchedule *selectedDoctor, appointment *appointmentsHead, date startDate)
{
    const int MAX_CABINET = 1000;

    appointment *bookedAppointment;
    date chosenDate;
    int chosenTimeInMinutes;
    _Bool isContinue, isWorkingDay, isRefusedToBook;

    bookedAppointment = NULL;
    isContinue = 0;
    isRefusedToBook = 0;
    isWorkingDay = 1;

    do
    {
        isContinue = 0;

        chosenDate = chooseDateForBook(selectedDoctor, startDate);
        isWorkingDay = checkIsWorkingDay(selectedDoctor, chosenDate);

        printf("\nChosen date: %02d.%02d.%04d\n", chosenDate.day, chosenDate.month, chosenDate.year);

        if (chosenDate.day == -1)
        {
            printf("\nReturning to the previous menu\n");
            isContinue = 0;
            isRefusedToBook = 1;
        }
        else
            if (isWorkingDay)
            {
                chosenTimeInMinutes = chooseStartTimeOfAppointment(selectedDoctor, chosenDate, appointmentsHead);

                if (chosenTimeInMinutes == -1)
                {
                    isContinue = 1;
                    printf("\nReturning to the previous menu\n");
                }     
            }
            else
            {
                printf("\nThe chosen date is a holiday, returning to the previous menu\n");
                isContinue = 1;  
            }
            
    } while (isContinue);

    if (isRefusedToBook)
        bookedAppointment = NULL;
    else
    {
        bookedAppointment = (appointment *)malloc(sizeof(appointment));
        if (bookedAppointment == NULL)
        {
            printf("Memory allocation error\n");
            return NULL;
        }

        printf("Write patient\n");
        inputFullName(bookedAppointment->surname, bookedAppointment->name, bookedAppointment->patronymic);   

        bookedAppointment->cabinet = rand() % (MAX_CABINET - 1) + 1;

        bookedAppointment->appointmentDate = chosenDate;
        getTimeFromOnlyMinutes(chosenTimeInMinutes, &(bookedAppointment->appointmentTime.hour), &(bookedAppointment->appointmentTime.minute));
        bookedAppointment->doctorID = selectedDoctor->doctorID;

        bookedAppointment->queuePlace = 0;
        bookedAppointment->next = NULL;
    }
        
    return bookedAppointment;
}

date chooseDateForBook(doctorSchedule *selectedDoctor, date startDate)
{
    const int WEEK = 7;
    const int MAX_OPTION = 7;

    char *dayNames[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    date chosenDate, demonstrationDate;
    apptTime start, end;
    int dayOfWeek, i, optionDay;
    _Bool isWorkingDay;

    demonstrationDate = startDate;
    dayOfWeek = 0;
    isWorkingDay = 0;

    printf("\n");
    printf("+-----+------------+-------------+---------------+\n");
    printf("|  #  |    Date    | Day of week | Work schedule |\n");
    printf("+-----+------------+-------------+---------------+\n");

    for (i = 0; i < WEEK; i++)
    {
        dayOfWeek = findDayOfWeek(demonstrationDate.day, demonstrationDate.month, demonstrationDate.year);

        getTimeFromOnlyMinutes(selectedDoctor->schedule[dayOfWeek][0], &start.hour, &start.minute);
        getTimeFromOnlyMinutes(selectedDoctor->schedule[dayOfWeek][1], &end.hour, &end.minute);
        printf("| %3d | %02d.%02d.%04d | %-11s |", 
            i + 1,
            demonstrationDate.day, demonstrationDate.month, demonstrationDate.year,
            dayNames[dayOfWeek]
        );

        isWorkingDay = checkIsWorkingDay(selectedDoctor, demonstrationDate);

        if (isWorkingDay)
            printf(" %02d:%02d - %02d:%02d |\n", start.hour, start.minute, end.hour, end.minute);
        else
            printf(" ------------- |\n");

        incrementDate(&demonstrationDate);
    }

    printf("+-----+------------+-------------+---------------+\n");
    printf("|       0 - Refuse to book an appointment        |\n");
    printf("+------------------------------------------------+\n");

    printf("\nWrite number \"#\" of date (0 to refuse and go back): \n");
    optionDay = scanInt(0, MAX_OPTION, "> ");
    
    if (optionDay == 0)
        chosenDate.day = -1;
    else
    {
        chosenDate = startDate;
        optionDay--;
        for (i = 0; i < optionDay; i++)
            incrementDate(&chosenDate);
    }

    return chosenDate;
}

void incrementDate(date *someDate)
{
    int maxDay;
    maxDay = findMaxDay((*someDate).month, (*someDate).year);

    (*someDate).day++;

    if ((*someDate).day > maxDay)
    {
        (*someDate).day = 1;
        (*someDate).month++;
        if ((*someDate).month > 12)
        {
            (*someDate).month = 1;
            (*someDate).year++;
        }
    }
}

int chooseStartTimeOfAppointment(doctorSchedule* selectedDoctor, date chosenDate, appointment* appointmentHead)
{
    const int DURATION = 30;

    int counter, chosenStartTime, currStart, currEnd, endOfShiftTime, dayOfWeek;
    int *availableStartTime;
    apptTime start, end;
    _Bool isAvailable;

    availableStartTime = NULL;
    chosenStartTime = -1;
    counter = 0;
    dayOfWeek = findDayOfWeek(chosenDate.day, chosenDate.month, chosenDate.year);
    currStart = selectedDoctor->schedule[dayOfWeek][0];
    endOfShiftTime = selectedDoctor->schedule[dayOfWeek][1];
    isAvailable = 0;

    while (currStart < endOfShiftTime)
    {
        currEnd = currStart + DURATION;
        isAvailable = checkIsSlotFree(appointmentHead, selectedDoctor->doctorID, chosenDate, currStart, currEnd);
        if (isAvailable && currEnd <= endOfShiftTime)
        {
            counter++;
            if (availableStartTime == NULL)
            {
                availableStartTime = (int*)malloc(sizeof(int));
                printf("\n");
                printf("+------------------------------------------------+\n");
                printf("|    Available appointment time %02d.%02d.%04d       |\n", chosenDate.day, chosenDate.month, chosenDate.year);
                printf("|    Duration of appointment is %3d minutes      |\n", DURATION);
                printf("+-----+---------------+--------------------------+\n");
                printf("|  #  | Available     |\n");
                printf("+-----+---------------+\n");
            }
            else
            {
                availableStartTime = realloc(availableStartTime, counter * sizeof(int));
            }

            if(availableStartTime != NULL)
            {
                getTimeFromOnlyMinutes(currStart, &start.hour, &start.minute);
                getTimeFromOnlyMinutes(currStart + DURATION, &end.hour, &end.minute);

                availableStartTime[counter - 1] = currStart;
                printf("| %3d | %02d:%02d - %02d:%02d |\n", 
                    counter,
                    start.hour, start.minute, 
                    end.hour, end.minute
                );
            }
        }

        currStart = currStart + DURATION;
    }

    if (availableStartTime == NULL)
    {
        printf("\nNo available time to book, returning to the previous stage\n");
        chosenStartTime = -1;
    }
    else
    {
        printf("+-----+---------------+-----------------+\n");
        printf("| 0 - get back to choose another option |\n");
        printf("+---------------------------------------+\n");
        printf("\nWrite number \"#\" of option that suit to you: \n");
        chosenStartTime = scanInt(0, counter, "> ");

        if (chosenStartTime == 0)
            chosenStartTime = -1;
        else
            chosenStartTime = availableStartTime[chosenStartTime - 1]; 
            
        free(availableStartTime);
        availableStartTime = NULL;
    }


    return chosenStartTime;
}

_Bool checkIsWorkingDay(doctorSchedule *selectedDoctor, date chosenDate)
{
    const int SUNDAY = 6;
    int dayOfWeek;
    _Bool isWorking;

    isWorking = 1;

    dayOfWeek = findDayOfWeek(chosenDate.day, chosenDate.month, chosenDate.year);

    if (dayOfWeek == SUNDAY || selectedDoctor->schedule[dayOfWeek][0] == selectedDoctor->schedule[dayOfWeek][1])
        isWorking = 0;

    return isWorking;
}

_Bool checkIsSlotFree(appointment *appointmentHead, int doctorID, date currDate, int start, int end)
{
    const int DURATION = 30;
    _Bool isFree;
    appointment *curr;
    int currStart, currEnd; 

    isFree = 1;

    if (appointmentHead->next == NULL)
        return isFree;

    curr = appointmentHead;

    while (curr->next != NULL && isFree)
    {
        curr = curr->next;
        currStart = getTimeInMinutes(curr->appointmentTime.hour, curr->appointmentTime.minute);
        currEnd = currStart + DURATION;

        if (curr->appointmentDate.day == currDate.day && 
            curr->appointmentDate.month == currDate.month &&
            curr->appointmentDate.year == currDate.year &&
            curr->doctorID == doctorID && 
            !(start >= currEnd || end <= currStart))
            isFree = 0;

    } 

    return isFree;
}



//

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
        fwrite(&curr->appointmentDate, sizeof(date), 1, file);
        fwrite(&curr->appointmentTime, sizeof(apptTime), 1, file);
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

    curr = head->next; // ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜
    while (curr != NULL)
    {
        fwrite(&curr->doctorID, sizeof(int), 1, file);
        fwrite(curr->specialization, sizeof(curr->specialization), 1, file);
        fwrite(curr->name, sizeof(curr->name), 1, file);
        fwrite(curr->surname, sizeof(curr->surname), 1, file);
        fwrite(curr->patronymic, sizeof(curr->patronymic), 1, file);
        fwrite(curr->schedule, sizeof(curr->schedule), 1, file); // ˜˜˜˜˜˜ 6x2 int

        curr = curr->next;
    }

    fclose(file);
}

//

doctorSchedule *getDoctorByIndex(doctorSchedule *head, int index)
{
    doctorSchedule *curr;
    int i;

    curr = head;
    i = 0;

    while (curr->next != NULL && i < index)
    {
        curr = curr->next;
        i++;
    }

    return curr;
}

appointment *getAppointmentByIndex(appointment *head, int index)
{
    appointment *curr;
    int i;

    curr = head;
    i = 0;

    while (curr->next != NULL && i < index)
    {
        curr = curr->next;
        i++;
    }

    return curr;
}

doctorSchedule *getScheduleByIndex(doctorSchedule *head, int index)
{
    doctorSchedule *curr;
    int i;

    curr = head;
    i = 0;

    while (curr->next != NULL && i < index)
    {
        curr = curr->next;
        i++;
    }

    return curr;
}

int findMaxDay(int month, int year)
{
    int maxDayInEachMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // ˜˜˜˜˜˜ = ˜˜˜˜˜ - 1; ˜˜˜˜˜˜˜˜ = max ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜
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

    // ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜
    apptCurr = appointmentsHead;
    while (apptCurr != NULL)
    {
        apptNext = apptCurr->next;
        free(apptCurr);
        apptCurr = apptNext;
    }

    // ˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
    schCurr = schedulesHead;
    while (schCurr != NULL)
    {
        schNext = schCurr->next;
        free(schCurr);
        schCurr = schNext;
    }

    appointmentsHead = NULL;
    schedulesHead = NULL;
}

// ˜˜˜˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜: ˜˜˜˜˜˜˜˜˜˜ 1, ˜˜˜˜ a ˜˜˜˜˜˜ b, ˜˜˜˜˜ 0
int checkIsEarlierAppointment(appointment *a, appointment *b)
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

// ˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜ (˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜)
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

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜˜
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

// ˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜
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
            else if (checkIsEarlierAppointment(curr, earliest))
                earliest = curr;
        }
        curr = curr->next;
    }
    return earliest;
}

// ˜˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
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

// ˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜: ˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜ ˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜
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

void appendAppointment(appointment *head, appointment *appendedAppointment)
{
    appointment *curr;
    curr = head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = appendedAppointment; 
}

void appendSchedule(doctorSchedule *head, doctorSchedule *appendedSchedule)
{
    doctorSchedule *curr;
    curr = head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = appendedSchedule; 
}