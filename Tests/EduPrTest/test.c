#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>

// ===================== СТРУКТУРЫ =====================

typedef struct date
{
    int day;
    int month;
    int year;
} date;

typedef struct appt_time
{
    int minute;
    int hour;
} appt_time;

typedef struct appointment
{
    date appointmentDate;
    appt_time appointmentTime;
    int queuePlace;
    char name[30];
    char surname[30];
    char patronymic[30];
    int cabinet;
    int doctorID;
    struct appointment *next;
} appointment;

typedef struct doctorSchedule
{
    int doctorID;
    char specialization[50];
    char name[30];
    char surname[30];
    char patronymic[30];
    int schedule[6][2];        // [день недели 0-5][0=начало, 1=конец] в минутах
} doctorSchedule;

typedef struct NodeDoctor
{
    doctorSchedule data;
    struct NodeDoctor* next;
} NodeDoctor;

// ===================== ГЛОБАЛЬНЫЕ СПИСКИ =====================
appointment* list_appointments = NULL;
NodeDoctor* list_doctors = NULL;

// ===================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ =====================

void clear_input() {
    while (getchar() != '\n');
}

// Добавление врача
void add_doctor(NodeDoctor** head, doctorSchedule d) {
    NodeDoctor* new_node = (NodeDoctor*)malloc(sizeof(NodeDoctor));
    if (new_node == NULL) return;
    new_node->data = d;
    new_node->next = *head;
    *head = new_node;
}

// Добавление талона
void add_appointment(appointment** head, appointment app) {
    appointment* new_node = (appointment*)malloc(sizeof(appointment));
    if (new_node == NULL) return;
    *new_node = app;
    new_node->next = *head;
    *head = new_node;
}

// ===================== РАБОТА С ФАЙЛАМИ =====================

void save_appointments() {
    FILE* f = fopen("appointments.dat", "wb");
    if (!f) return;
    appointment* cur = list_appointments;
    while (cur) {
        fwrite(cur, sizeof(appointment), 1, f);   // Записываем без указателя next
        cur = cur->next;
    }
    fclose(f);
}

void save_doctors() {
    FILE* f = fopen("doctors.dat", "wb");
    if (!f) return;
    NodeDoctor* cur = list_doctors;
    while (cur) {
        fwrite(&cur->data, sizeof(doctorSchedule), 1, f);
        cur = cur->next;
    }
    fclose(f);
}

void load_appointments() {
    FILE* f = fopen("appointments.dat", "rb");
    if (!f) return;
    appointment temp;
    while (fread(&temp, sizeof(appointment), 1, f)) {
        temp.next = NULL;
        add_appointment(&list_appointments, temp);
    }
    fclose(f);
}

void load_doctors() {
    FILE* f = fopen("doctors.dat", "rb");
    if (!f) return;
    doctorSchedule d;
    while (fread(&d, sizeof(doctorSchedule), 1, f)) {
        add_doctor(&list_doctors, d);
    }
    fclose(f);
}

// ===================== СОРТИРОВКА =====================
void sort_appointments_by_date() {
    if (list_appointments == NULL) {
        printf("Список талонов пуст!\n");
        return;
    }

    int swapped;
    appointment *ptr1, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = list_appointments;

        while (ptr1->next != lptr) {
            int need_swap = 0;

            if (ptr1->appointmentDate.year > ptr1->next->appointmentDate.year) need_swap = 1;
            else if (ptr1->appointmentDate.year == ptr1->next->appointmentDate.year) {
                if (ptr1->appointmentDate.month > ptr1->next->appointmentDate.month) need_swap = 1;
                else if (ptr1->appointmentDate.month == ptr1->next->appointmentDate.month) {
                    if (ptr1->appointmentDate.day > ptr1->next->appointmentDate.day) need_swap = 1;
                    else if (ptr1->appointmentDate.day == ptr1->next->appointmentDate.day) {
                        if (ptr1->appointmentTime.hour > ptr1->next->appointmentTime.hour) need_swap = 1;
                        else if (ptr1->appointmentTime.hour == ptr1->next->appointmentTime.hour) {
                            if (ptr1->appointmentTime.minute > ptr1->next->appointmentTime.minute) need_swap = 1;
                        }
                    }
                }
            }

            if (need_swap) {
                appointment temp = *ptr1;
                *ptr1 = *ptr1->next;
                *ptr1->next = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    printf("Талоны успешно отсортированы по дате и времени!\n");
}

// ===================== СПЕЦИАЛЬНАЯ ФУНКЦИЯ - ВЫДАЧА ТАЛОНОВ =====================
void issue_tickets() {
    char doc_surname[30];
    date search_date;

    printf("Введите фамилию врача: ");
    fgets(doc_surname, 30, stdin);
    doc_surname[strcspn(doc_surname, "\n")] = 0;

    printf("Введите дату (день месяц год): ");
    scanf("%d %d %d", &search_date.day, &search_date.month, &search_date.year);
    clear_input();

    FILE* f = fopen("issued_tickets.txt", "w");
    if (f) fprintf(f, "=== ВЫДАЧА ТАЛОНОВ ===\nДата: %02d.%02d.%d\nВрач: %s\n\n", 
                  search_date.day, search_date.month, search_date.year, doc_surname);

    appointment* cur = list_appointments;
    int count = 0;

    while (cur) {
        if (cur->appointmentDate.day == search_date.day &&
            cur->appointmentDate.month == search_date.month &&
            cur->appointmentDate.year == search_date.year) {

            NodeDoctor* doc = list_doctors;
            while (doc) {
                if (doc->data.doctorID == cur->doctorID && 
                    strstr(doc->data.surname, doc_surname) != NULL) {
                    
                    if (strlen(cur->surname) == 0) {  // Талон свободен
                        printf("%02d:%02d  Каб:%d  Очередь:%d\n", 
                               cur->appointmentTime.hour, cur->appointmentTime.minute,
                               cur->cabinet, cur->queuePlace);
                        if (f) fprintf(f, "%02d:%02d  Каб:%d  №%d\n", 
                                     cur->appointmentTime.hour, cur->appointmentTime.minute,
                                     cur->cabinet, cur->queuePlace);
                        count++;
                    }
                    break;
                }
                doc = doc->next;
            }
        }
        cur = cur->next;
    }

    if (count == 0) {
        printf("Свободных талонов не найдено.\n");
        if (f) fprintf(f, "Свободных талонов не найдено.\n");
    }
    if (f) fclose(f);
    printf("Результат сохранён в issued_tickets.txt\n");
}

// ===================== ПОИСК =====================
void search_by_doctor() {
    char doc_surname[30];
    date search_date;
    printf("Фамилия врача: ");
    fgets(doc_surname, 30, stdin);
    doc_surname[strcspn(doc_surname, "\n")] = 0;
    printf("Дата (день месяц год): ");
    scanf("%d %d %d", &search_date.day, &search_date.month, &search_date.year);
    clear_input();

    printf("\nТалоны к врачу %s на %02d.%02d.%d:\n", doc_surname, search_date.day, search_date.month, search_date.year);
    
    appointment* cur = list_appointments;
    while (cur) {
        if (cur->appointmentDate.day == search_date.day && 
            cur->appointmentDate.month == search_date.month && 
            cur->appointmentDate.year == search_date.year) {
            
            NodeDoctor* d = list_doctors;
            while (d) {
                if (d->data.doctorID == cur->doctorID && strstr(d->data.surname, doc_surname)) {
                    printf("%02d:%02d | Каб:%d | Оч:%d | %s %s %s\n",
                           cur->appointmentTime.hour, cur->appointmentTime.minute,
                           cur->cabinet, cur->queuePlace,
                           cur->surname, cur->name, cur->patronymic);
                    break;
                }
                d = d->next;
            }
        }
        cur = cur->next;
    }
}

void search_by_patient() {
    char patient_surname[30];
    printf("Фамилия пациента: ");
    fgets(patient_surname, 30, stdin);
    patient_surname[strcspn(patient_surname, "\n")] = 0;

    printf("\nЗаписи пациента %s:\n", patient_surname);
    appointment* cur = list_appointments;
    while (cur) {
        if (strstr(cur->surname, patient_surname) != NULL) {
            printf("%02d.%02d.%d %02d:%02d | Каб:%d | Врач ID:%d\n",
                   cur->appointmentDate.day, cur->appointmentDate.month, cur->appointmentDate.year,
                   cur->appointmentTime.hour, cur->appointmentTime.minute,
                   cur->cabinet, cur->doctorID);
        }
        cur = cur->next;
    }
}

// ===================== ГЛАВНОЕ МЕНЮ =====================
int main() {
    int choice, sub;

    setlocale(LC_ALL, "Russian");
    
    load_doctors();
    load_appointments();
    printf("Данные загружены из файлов.\n");

    while (1) {
        printf("\n=== ПОЛИКЛИНИКА - МЕНЮ ===\n");
        printf("1. Чтение данных из файлов\n");
        printf("2. Просмотр списков\n");
        printf("3. Сортировка талонов по дате и времени\n");
        printf("4. Поиск данных\n");
        printf("5. Добавление данных\n");
        printf("6. Удаление данных\n");
        printf("7. Редактирование данных\n");
        printf("8. Выдача талонов к врачу\n");
        printf("9. Выход без сохранения\n");
        printf("10. Выход с сохранением\n");
        printf("Выберите пункт: ");

        if (scanf("%d", &choice) != 1) { clear_input(); continue; }
        clear_input();

        if (choice == 1) {
            load_doctors();
            load_appointments();
            printf("Данные успешно перезагружены.\n");
        }
        else if (choice == 2) {
            printf("1 - Врачи\n2 - Талоны\nВыбор: ");
            scanf("%d", &sub); clear_input();
            if (sub == 1) {
                NodeDoctor* cur = list_doctors;
                while (cur) {
                    printf("ID:%d | %s %s %s | %s\n", cur->data.doctorID,
                           cur->data.surname, cur->data.name, cur->data.patronymic,
                           cur->data.specialization);
                    cur = cur->next;
                }
            } else if (sub == 2) {
                appointment* cur = list_appointments;
                while (cur) {
                    printf("%02d.%02d.%d %02d:%02d | Каб:%d | Оч:%d | %s %s %s | Врач:%d\n",
                           cur->appointmentDate.day, cur->appointmentDate.month, cur->appointmentDate.year,
                           cur->appointmentTime.hour, cur->appointmentTime.minute,
                           cur->cabinet, cur->queuePlace, cur->surname, cur->name, cur->patronymic, cur->doctorID);
                    cur = cur->next;
                }
            }
        }
        else if (choice == 3) {
            sort_appointments_by_date();
        }
        else if (choice == 4) {
            printf("1 - Поиск по врачу и дате\n2 - Поиск по пациенту\nВыбор: ");
            scanf("%d", &sub); clear_input();
            if (sub == 1) search_by_doctor();
            else if (sub == 2) search_by_patient();
        }
        else if (choice == 5) {
            printf("1 - Добавить врача\n2 - Добавить талон\nВыбор: ");
            scanf("%d", &sub); clear_input();
            if (sub == 2) {
                appointment app = {0};
                printf("Дата (день месяц год): "); scanf("%d %d %d", &app.appointmentDate.day, &app.appointmentDate.month, &app.appointmentDate.year);
                printf("Время (час минуты): "); scanf("%d %d", &app.appointmentTime.hour, &app.appointmentTime.minute);
                printf("Номер очереди: "); scanf("%d", &app.queuePlace);
                clear_input();
                printf("Имя: "); fgets(app.name, 30, stdin); app.name[strcspn(app.name,"\n")]=0;
                printf("Фамилия: "); fgets(app.surname, 30, stdin); app.surname[strcspn(app.surname,"\n")]=0;
                printf("Отчество: "); fgets(app.patronymic, 30, stdin); app.patronymic[strcspn(app.patronymic,"\n")]=0;
                printf("Кабинет: "); scanf("%d", &app.cabinet);
                printf("ID врача: "); scanf("%d", &app.doctorID);
                add_appointment(&list_appointments, app);
                printf("Талон добавлен!\n");
            }
        }
        else if (choice == 6) {
            printf("Удаление не реализовано в этой версии.\n");
        }
        else if (choice == 7) {
            printf("Редактирование не реализовано в этой версии.\n");
        }
        else if (choice == 8) {
            issue_tickets();
        }
        else if (choice == 9) {
            printf("Выход без сохранения.\n");
            return 0;
        }
        else if (choice == 10) {
            save_doctors();
            save_appointments();
            printf("Данные сохранены. Выход.\n");
            return 0;
        }
        else {
            printf("Неверный пункт!\n");
        }
    }
    return 0;
}