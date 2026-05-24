#include <stdio.h>
#include "ds.h"
#include "processing.h"

void filter_queue(Queue *q, int threshold, int condition_type) {
    Queue temp;
    int value, success, should_remove;
    
    init_queue(&temp);
    
    printf("\n--- Процесс фильтрации очереди ---\n");
    success = 1;
    while (!is_empty(q) && success) {
        success = dequeue(q, &value);
        if (success) {
            should_remove = 0;
            if (condition_type == 1) {
                if (value < threshold) {
                    should_remove = 1;
                }
            } 
            else 
                if (condition_type == 2) {
                    if (value > threshold) {
                        should_remove = 1;
                    }
                }
            
            if (should_remove) {
                printf("Элемент %d удален.\n", value);
            } 
            else {
                printf("Элемент %d оставлен.\n", value);
                enqueue(&temp, value);
            }
        }
    }
    printf("--- Завершение фильтрации ---\n\n");
    
    success = 1;
    while (!is_empty(&temp) && success) {
        success = dequeue(&temp, &value);
        if (success) {
            enqueue(q, value);
        }
    }
}
