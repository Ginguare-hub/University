#include <stdio.h>
#include <windows.h>
#include "ds.h"
#include "processing.h"

void clear_input_buffer(void) {
    int c, keep_going;

    keep_going = 1;
    while (keep_going) {
        c = getchar();
        if (c == '\n') {
            keep_going = 0;
        } 
        else 
            if (c == EOF) {
                keep_going = 0;
            }
    }
}

void print_queue(Queue *q) {
    Queue temp;
    int value, success;
    
    init_queue(&temp);
    
    printf("Элементы очереди: ");
    success = 1;
    while (!is_empty(q) && success) {
        success = dequeue(q, &value);
        if (success) {
            printf("%d ", value);
            enqueue(&temp, value);
        }
    }
    printf("\n");
    
    success = 1;
    while (!is_empty(&temp) && success) {
        success = dequeue(&temp, &value);
        if (success) {
            enqueue(q, value);
        }
    }
}

void run_program(void) {
    Queue q;
    int value, threshold, input_status, keep_going, condition_type;

    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    init_queue(&q);
    printf("--- Лабораторная работа 8. Вариант 16. ---\n");
    printf("Удаление элементов из очереди по условию.\n");
    printf("Введите элементы очереди (введите любой символ, не являющийся числом, для завершения ввода):\n");
    
    keep_going = 1;
    while (keep_going) {
        input_status = scanf("%d", &value);
        if (input_status == 1) {
            if (!enqueue(&q, value)) {
                printf("Ошибка: Очередь переполнена.\n");
                keep_going = 0;
            }
        } 
        else {
            keep_going = 0;
        }
    }
    
    clear_input_buffer();
    
    if (is_empty(&q)) {
        printf("Очередь пуста. Обработка завершена.\n");
    } 
    else {
        print_queue(&q);
        
        printf("\nВыберите условие для удаления элементов:\n");
        printf("1. Строго меньше порога (<)\n");
        printf("2. Строго больше порога (>)\n");
        printf("Ваш выбор: ");
        input_status = scanf("%d", &condition_type);
        if (input_status == 1) {
            if (condition_type == 1 || condition_type == 2) {
                printf("Введите пороговое значение: ");
                input_status = scanf("%d", &threshold);
                if (input_status == 1) {
                    filter_queue(&q, threshold, condition_type);
                    if (condition_type == 1) {
                        printf("Очередь после удаления элементов меньше %d:\n", threshold);
                    } 
                    else {
                        printf("Очередь после удаления элементов больше %d:\n", threshold);
                    }
                    print_queue(&q);
                } 
                else {
                    printf("Ошибка ввода порога.\n");
                }
            } 
            else {
                printf("Ошибка: неверный выбор условия.\n");
            }
        } 
        else {
            printf("Ошибка ввода выбора условия.\n");
        }
    }
}

int main(void) {
    run_program();
    return 0;
}
