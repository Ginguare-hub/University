#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum hierarchyLevel 
{
    lvlTerm,
    lvlSubterm,
    lvlSubsubterm
};

struct library 
{
    struct library *next; 
    struct library *prev;
    struct library *parent;
    struct library *firstChild;

    enum hierarchyLevel hLevel;
    int pageNumber;
    char termData[256];
};     

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
            printf("Invalid input, try again\n");
            while (getchar() != '\n');
        }

        if (!isIncorrect && ((number < MIN_NUMBER) || (number > MAX_NUMBER)))
        {
            isIncorrect = 1;
            printf("Number must be in range [%d,%d]\n", MIN_NUMBER, MAX_NUMBER);
        }

    } while (isIncorrect);

    return number;
}

//* Read string 
void readString(const char* prompt, char* buffer, int bufferSize) 
{
    printf("%s", prompt);
    fgets(buffer, bufferSize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

// Create new item
struct library* createItem(enum hierarchyLevel level, int page, const char* data) 
{
    struct library* item = (struct library*)calloc(1, sizeof(struct library));
    
    if (!item) 
        return NULL;
    
    item->hLevel = level;
    item->pageNumber = page;
    strncpy(item->termData, data, sizeof(item->termData) - 1);
    item->termData[sizeof(item->termData) - 1] = '\0';
    
    return item;
}

// Add child
void addChildToEnd(struct library* parent, struct library* child) 
{
    if (!parent || !child) return;
    
    child->parent = parent;
    
    if (!parent->firstChild) {
        parent->firstChild = child;
        return;
    }
    
    struct library* last = parent->firstChild;
    while (last->next) {
        last = last->next;
    }
    
    last->next = child;
    child->prev = last;
}

// Add term
void addTermToEnd(struct library** termList, struct library* term) 
{
    if (!term) return;
    
    if (!*termList) {
        *termList = term;
        return;
    }
    
    struct library* last = *termList;
    while (last->next) {
        last = last->next;
    }
    
    last->next = term;
    term->prev = last;
}

// Recursive delete
void deleteItemRecursive(struct library** termList, struct library* item) 
{
    if (!item) return;
    
    // First delete all children recursively
    struct library* child = item->firstChild;
    while (child) {
        struct library* nextChild = child->next;
        deleteItemRecursive(termList, child);
        child = nextChild;
    }
    
    // If item has a parent
    if (item->parent) {
        //// Remove item from parent's children list
        // Удаляем элемент item из родителей
        struct library* current = item->parent->firstChild;
        
        // If deleting first child
        if (current == item) {
            item->parent->firstChild = item->next;
            if (item->next) {
                item->next->prev = NULL;
            }
        } 
        else {
            // Find item in the list
            while (current && current->next != item) {
                current = current->next;
            }
            if (current) {
                current->next = item->next;
                if (item->next) {
                    item->next->prev = current;
                }
            }
        }
    } 
    else {
        // This is a root term - remove from global list
        if (item->prev) {
            item->prev->next = item->next;
        }
        if (item->next) {
            item->next->prev = item->prev;
        }
        
        // If this is the first item in global list
        if (*termList == item) {
            *termList = item->next;
        }
    }
    
    free(item);
}

// поисковые функции

// Find term by name
struct library* findTermByName(struct library* termList, const char* name) 
{
    struct library* curr = termList;
    while (curr) {
        if (strcmp(curr->termData, name) == 0) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// вывод всей библиотеки

// Recursive tree printing
void printTree(struct library* item, int indent) 
{
    if (!item) 
        return;
    
    for (int i = 0; i < indent; ++i) 
    {
        printf("  ");
    }
    
    if (item->hLevel == lvlTerm) {
        printf("[Term] %s (page %d)\n", item->termData, item->pageNumber);
    } 
    else 
        if (item->hLevel == lvlSubterm) 
        {
            printf("  [Subterm] %s (page %d)\n", item->termData, item->pageNumber);
        } 
        else 
        {
            printf("    [Subsubterm] %s (page %d)\n", item->termData, item->pageNumber);
        }
    
    printTree(item->firstChild, indent + 1);
    printTree(item->next, indent);
}

void viewAll(struct library* termList) 
{
    printf("\n====== Hierarchy ======\n");
    if (!termList) 
    {
        printf("List is empty\n");
    } 
    else 
    {
        printTree(termList, 0);
    }
    printf("\n");
}

// Recursively collect all items into array with numbers
void collectAllItems(struct library* item, struct library** array, int* index, int* nextNumber, _Bool isPrintNeeded) 
{
    if (!item) return;
    
    // add current item to array
    array[*index] = item;
    (*index)++;
    
    // print it with number
    char* prefix = "";
    if (item->hLevel == lvlTerm) {
        prefix = "TERM";
    } else if (item->hLevel == lvlSubterm) {
        prefix = "  SUBTERM";
    } else {
        prefix = "    SUBSUBTERM";
    }
    
    if (isPrintNeeded)
        printf("%d. %s: %s (p. %d)\n", *nextNumber, prefix, item->termData, item->pageNumber);

    (*nextNumber)++;
    
    // recursively find children
    collectAllItems(item->firstChild, array, index, nextNumber, isPrintNeeded);
    
    // recursively find next item
    collectAllItems(item->next, array, index, nextNumber, isPrintNeeded);
}

void deleteItem(struct library** termList) 
{
    if (!*termList) {
        printf("No items to delete\n");
        return;
    }
    
    // Count total number of items
    int totalCount = 0;
    struct library** tempArray = (struct library**)malloc(1000 * sizeof(struct library*));
    int tempIndex = 0;
    int tempNumber = 1;

    collectAllItems(*termList, tempArray, &tempIndex, &tempNumber, 0);
    totalCount = tempIndex;
    free(tempArray);
    
    if (totalCount == 0) {
        printf("No items to delete\n");
        return;
    }
    
    printf("\n====== Delete item ======\n");
    printf("Available items for deletion:\n");
    
    // Create array of pointers to all items
    struct library** allItems = (struct library**)malloc(totalCount * sizeof(struct library*));
    int index = 0;
    int number = 1;
    
    // Fill array and print numbered list
    collectAllItems(*termList, allItems, &index, &number, 1);   
    printf("\n");

    int choice = scanInt(1, totalCount, "Enter item number to delete: ");
    
    // Get selected item
    struct library* toDelete = allItems[choice - 1];
    
    // Save name for message
    char deletedName[256];
    strcpy(deletedName, toDelete->termData);

    deleteItemRecursive(termList, toDelete);
    
    printf("Item '%s' and all its sub-items deleted\n", deletedName);
    
    free(allItems);
}

// adding element

void addNewTerm(struct library** termList) 
{
    char name[256];
    int page;
    
    readString("Term name: ", name, sizeof(name));
    
    if (strlen(name) == 0) {
        printf("Name cannot be empty!\n");
        return;
    }
    
    if (findTermByName(*termList, name)) {
        printf("Error: term '%s' already exists!\n", name);
        return;
    }
    
    page = scanInt(1, 1000, "Page number: ");
    
    struct library* newTerm = createItem(lvlTerm, page, name);
    addTermToEnd(termList, newTerm);
    printf("Term '%s' added!\n", name);
}

void addNewSubterm(struct library* termList) 
{
    char subName[256];
    int page;
    
    // Show list of terms
    printf("\nAvailable terms:\n");
    struct library* curr = termList;
    int num = 1;
    struct library* termArray[100];
    while (curr) {
        printf("%d. %s (p. %d)\n", num, curr->termData, curr->pageNumber);
        termArray[num-1] = curr;
        curr = curr->next;
        num++;
    }
    
    int termChoice = scanInt(1, num - 1, "Select term number: ");
    struct library* parent = termArray[termChoice - 1];
    
    readString("Subterm name: ", subName, sizeof(subName));
    
    if (strlen(subName) == 0) {
        printf("Name cannot be empty!\n");
        return;
    }
    
    page = scanInt(1, 1000, "Page number: ");
    
    struct library* newSub = createItem(lvlSubterm, page, subName);
    addChildToEnd(parent, newSub);
    printf("Subterm '%s' added to term '%s'!\n", subName, parent->termData);
}

void addNewSubSubterm(struct library* termList) 
{
    char subsubName[256];
    int page;
    
    // Collect all subterms
    printf("\nAvailable subterms:\n");
    struct library* term = termList;
    int globalNum = 1;
    struct library* subtermArray[1000];
    int subtermIndex = 0;
    
    while (term) {
        struct library* sub = term->firstChild;
        while (sub) {
            if (sub->hLevel == lvlSubterm) {
                printf("%d. Term \"%s\" -> Subterm \"%s\" (p. %d)\n", 
                       globalNum, term->termData, sub->termData, sub->pageNumber);
                subtermArray[subtermIndex] = sub;
                subtermIndex++;
                globalNum++;
            }
            sub = sub->next;
        }
        term = term->next;
    }
    
    if (subtermIndex == 0) {
        printf("No subterms to add subsubterms!\n");
        return;
    }
    
    int subChoice = scanInt(1, subtermIndex, "Select subterm number: ");
    struct library* parent = subtermArray[subChoice - 1];
    
    readString("Subsubterm name: ", subsubName, sizeof(subsubName));
    
    if (strlen(subsubName) == 0) {
        printf("Name cannot be empty!\n");
        return;
    }
    
    page = scanInt(1, 1000, "Page number: ");
    
    struct library* newSubSub = createItem(lvlSubsubterm, page, subsubName);
    addChildToEnd(parent, newSubSub);
    printf("Subsubterm '%s' added to subterm '%s'!\n", subsubName, parent->termData);
}

void addItem(struct library** termList) 
{
    int choice = scanInt(1, 3, "\n====== Add ======\n1. Add term\n2. Add subterm\n3. Add subsubterm\n> ");
    
    switch(choice) {
        case 1: addNewTerm(termList); 
            break;
        case 2: addNewSubterm(*termList); 
            break;
        case 3: addNewSubSubterm(*termList); 
            break;
        }
    }

void editItem(struct library* termList) 
{
    if (!termList) {
        printf("No terms to edit!\n");
        return;
    }
    
    // Show list of terms
    printf("\nAvailable terms:\n");
    struct library* curr = termList;
    int num = 1;
    struct library* termArray[100];
    while (curr) {
        printf("%d. %s (p. %d)\n", num, curr->termData, curr->pageNumber);
        termArray[num-1] = curr;
        curr = curr->next;
        num++;
    }
    
    int choice = scanInt(1, num - 1, "Select term number to edit: ");
    struct library* term = termArray[choice - 1];
    
    printf("\nCurrent name: %s\n", term->termData);
    printf("Current page: %d\n", term->pageNumber);
    
    char newName[256];
    printf("New name: ");
    fgets(newName, sizeof(newName), stdin);
    newName[strcspn(newName, "\n")] = '\0';
    if (strlen(newName) > 0) {
        strcpy(term->termData, newName);
    }
    
    int newPage = scanInt(-1, 1000, "New page number (-1 to keep): ");
    if (newPage >= 0) {
        term->pageNumber = newPage;
    }
    
    printf("Term updated!\n");
}

int compareByName(const void* a, const void* b) 
{
    struct library* itemA = *(struct library**)a;
    struct library* itemB = *(struct library**)b;
    return strcmp(itemA->termData, itemB->termData);
}

int compareByPage(const void* a, const void* b) 
{
    struct library* itemA = *(struct library**)a;
    struct library* itemB = *(struct library**)b;
    return itemA->pageNumber - itemB->pageNumber;
}

void sortLevelRecursive(struct library** head, int (*compar)(const void*, const void*)) 
{
    if (!*head) return;
    
    int count = 0;
    struct library* curr = *head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    
    if (count <= 1) {
        sortLevelRecursive(&(*head)->firstChild, compar);
        return;
    }
    
    struct library** arr = (struct library**)malloc(count * sizeof(struct library*));
    curr = *head;
    for (int i = 0; i < count; i++) {
        arr[i] = curr;
        curr = curr->next;
    }
    
    qsort(arr, count, sizeof(struct library*), compar);
    
    *head = arr[0];
    for (int i = 0; i < count; i++) {
        arr[i]->prev = (i > 0) ? arr[i-1] : NULL;
        arr[i]->next = (i < count-1) ? arr[i+1] : NULL;
    }
    
    free(arr);
    
    // Recursively sort children
    curr = *head;
    while (curr) {
        sortLevelRecursive(&curr->firstChild, compar);
        curr = curr->next;
    }
}

void sortItems(struct library** termList) 
{
    if (!*termList) {
        printf("No terms to sort!\n");
        return;
    }
    
    int choice = scanInt(1, 2, "\n====== Sorting ======\n1. By name\n2. By page number\n> ");
    
    if (choice == 1) {
        sortLevelRecursive(termList, compareByName);
        printf("Sorted by name!\n");
    } else {
        sortLevelRecursive(termList, compareByPage);
        printf("Sorted by page number!\n");
    }
    
    viewAll(*termList);
}

void searchSubtermsByTerm(struct library* termList) 
{
    if (!termList) {
        printf("No terms to search!\n");
        return;
    }
    
    // Show list of terms
    printf("\nAvailable terms:\n");
    struct library* curr = termList;
    int num = 1;
    struct library* termArray[100];
    while (curr) {
        printf("%d. %s (p. %d)\n", num, curr->termData, curr->pageNumber);
        termArray[num-1] = curr;
        curr = curr->next;
        num++;
    }
    
    int choice = scanInt(1, num - 1, "Select term number: ");
    struct library* term = termArray[choice - 1];
    
    printf("\nSubterms of term \"%s\":\n", term->termData);
    struct library* child = term->firstChild;
    int found = 0;
    
    while (child) {
        if (child->hLevel == lvlSubterm) {
            printf("  - %s (p. %d)\n", child->termData, child->pageNumber);
            found++;
        }
        child = child->next;
    }

    printf("\n");
    
    if (!found) printf("  (no subterms)\n");
}

void searchTermsBySubterm(struct library* termList) 
{
    char subName[256];
    
    readString("\n====== Search term by subterm ======\nEnter subterm name: ", subName, sizeof(subName));
    
    printf("\nTerms containing subterm \"%s\":\n", subName);
    
    struct library* term = termList;
    int found = 0;
    
    while (term) {
        struct library* child = term->firstChild;
        while (child) {
            if (child->hLevel == lvlSubterm && strcmp(child->termData, subName) == 0) {
                printf("  - Term: \"%s\" (p. %d) -> subterm on p. %d\n", 
                       term->termData, term->pageNumber, child->pageNumber);
                found++;
                break;
            }
            child = child->next;
        }
        term = term->next;
    }
    
    if (!found) printf("  (not found)\n");
}

void showMenu() 
{
    printf("====== Library ======\n");
    printf("1. View full hierarchy\n");
    printf("2. Add item\n");
    printf("3. Delete item\n");
    printf("4. Edit term\n");
    printf("5. Sort\n");
    printf("6. Search subterms by term\n");
    printf("7. Search terms by subterm\n");
    printf("0. Exit\n");
    printf("=======================\n");
}

int main(void) 
{
    //0
    setlocale(LC_ALL, "C");
    
    struct library* termList = NULL;
    
    printf("\nBase library:\n");
    
    // Добавление
    struct library* t1 = createItem(lvlTerm, 10, "Programming");
    struct library* t2 = createItem(lvlTerm, 25, "Databases");
    struct library* t3 = createItem(lvlTerm, 5, "Algorithms");
    struct library* t4 = createItem(lvlTerm, 15, "Networks");
    
    addTermToEnd(&termList, t1); 
    addTermToEnd(&termList, t2); 
    addTermToEnd(&termList, t3);
    addTermToEnd(&termList, t4);
    
    struct library* s1 = createItem(lvlSubterm, 12, "Programming Languages");
    struct library* s2 = createItem(lvlSubterm, 15, "Paradigms");
    struct library* s3 = createItem(lvlSubterm, 8, "Development Tools");
    addChildToEnd(t1, s1); 
    addChildToEnd(t1, s2);
    addChildToEnd(t1, s3);
    
    struct library* ss1 = createItem(lvlSubsubterm, 13, "C");
    struct library* ss2 = createItem(lvlSubsubterm, 14, "Pascal");
    struct library* ss3 = createItem(lvlSubsubterm, 11, "Fortran");
    addChildToEnd(s1, ss1); 
    addChildToEnd(s1, ss2);
    addChildToEnd(s1, ss3);
    
    struct library* ss4 = createItem(lvlSubsubterm, 16, "OOP");
    struct library* ss5 = createItem(lvlSubsubterm, 17, "Functional");
    struct library* ss6 = createItem(lvlSubsubterm, 15, "Procedural");
    addChildToEnd(s2, ss4); 
    addChildToEnd(s2, ss5);
    addChildToEnd(s2, ss6);
    struct library* s4 = createItem(lvlSubterm, 30, "Relational");
    struct library* s5 = createItem(lvlSubterm, 28, "NoSQL");

    struct library* s6 = createItem(lvlSubterm, 30, "Relational");
    addChildToEnd(t2, s4); 
    addChildToEnd(t2, s5);
    addChildToEnd(t2, s6);
    
    struct library* ss7 = createItem(lvlSubsubterm, 31, "MySQL");


    struct library* ss8 = createItem(lvlSubsubterm, 32, "PostgreSQL");
    addChildToEnd(s4, ss7);
    addChildToEnd(s4, ss8);
    struct library* s7 = createItem(lvlSubterm, 6, "Sorting");
    struct library* s8 = createItem(lvlSubterm, 7, "Searching");
    struct library* s9 = createItem(lvlSubterm, 9, "Graphs");
    addChildToEnd(t3, s7);
    addChildToEnd(t3, s8);
    addChildToEnd(t3, s9);
    
    struct library* ss9 = createItem(lvlSubsubterm, 6, "Bubble");
    struct library* ss10 = createItem(lvlSubsubterm, 6, "Quick");
    struct library* ss11 = createItem(lvlSubsubterm, 7, "Merge");
    addChildToEnd(s7, ss9);
    addChildToEnd(s7, ss10);
    addChildToEnd(s7, ss11);
    
    struct library* s10 = createItem(lvlSubterm, 16, "Protocols");
    struct library* s11 = createItem(lvlSubterm, 17, "OSI Model");
    addChildToEnd(t4, s10);



    addChildToEnd(t4, s11);

    struct library* s12 = createItem(lvlSubterm, 150, "Relational");
    addChildToEnd(t4, s12); 
    
    viewAll(termList);
    
    int choice;
    do {
        showMenu();
        choice = scanInt(0, 7, "> ");
        
        switch(choice) {
            case 1: viewAll(termList); break;
            case 2: addItem(&termList); break;
            case 3: deleteItem(&termList); break;
            case 4: editItem(termList); break;
            case 5: sortItems(&termList); break;
            case 6: searchSubtermsByTerm(termList); break;
            case 7: searchTermsBySubterm(termList); break;
            case 0: printf("\n=== Exiting ===\n"); break;
        }

    } while (choice != 0);
    
    while (termList) {
        deleteItemRecursive(&termList, termList);
    }
    
    return 0;
}