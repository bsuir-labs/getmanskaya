#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <ctime>

struct Queue
{
    int value = 0;
    Queue* prev = nullptr;
    Queue* next = nullptr;
};

void push_front(Queue **first, Queue **last, int value)
{
    Queue *temp = new Queue;
    temp->value = value;
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*first)->prev = temp;
        temp->next = *first;
        *first = temp;
    }
}

void push_back(Queue **first, Queue **last, int value)
{
    Queue *temp = new Queue;
    temp->value = value;
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*last)->next = temp;
        temp->prev = *last;
        *last = temp;
    }
}


void deleteQueue(Queue **p)
{
    Queue *t;
    while (*p != NULL)
    {
        t = *p;
        *p = (*p)->next;
        delete t;
    }
    *p = nullptr;
}

void printQueue(int code, Queue *begin, Queue *end)
{
    Queue *t = nullptr;
    if (code == 0) t = begin;
    else t = end;
    while (t != NULL)
    {
        printf("%d, ", t->value);
        if (code == 0) t = t->next;
        else
            t = t->prev;
    }
    printf("\n");
}


void pop_back(Queue **first, Queue **last)
{
    if (*first == *last)
    {
        delete *first;
        *last = nullptr;
        *first = nullptr;
        return;
    }

    Queue *tmp = (*last)->prev;
    delete *last;
    *last = tmp;
    (*last)->next = NULL;
}

void pop_front(Queue **first, Queue **last)
{
    if (*first == *last)
    {
        delete *first;
        *last = nullptr;
        *first = nullptr;
        return;
    }

    Queue *tmp = (*first)->next;
    delete *first;
    *first = tmp;
    (*first)->prev = NULL;
}


int getMainMenuChoice();

void menu_GenerateNewQueue(Queue** qbegin, Queue** qend);
void menu_PrintQueue(Queue* qbegin, Queue *qend);
void menu_AppendElement(Queue** qbegin, Queue** qend);
void menu_PopElement(Queue** qbegin, Queue** qend);
void menu_IndividualTask(Queue** qbegin, Queue** qend);

// safe input functions
int rangeReadInt(int minimal, int maximal, const char* prompt);
void flush_stdin();

int main()
{
    srand(time(nullptr));

    Queue *qbegin, *qend;
    qbegin = qend = nullptr;

    bool stopRequested = false;
    while (!stopRequested)
    {
        switch (getMainMenuChoice())
        {
            case 1: menu_GenerateNewQueue(&qbegin, &qend);      break;
            case 2: menu_PrintQueue(qbegin, qend);              break;
            case 3: menu_AppendElement(&qbegin, &qend);         break;
            case 4: menu_PopElement(&qbegin, &qend);            break;
            case 5: menu_IndividualTask(&qbegin, &qend);        break;
            case 6:
                stopRequested = true;
                printf("Goodbye! Have a nice day!\n");
                break;
            default: printf("Something went wrong\n");
        }

        getc(stdin);
    }
    return 0;
}

void menu_GenerateNewQueue(Queue** qbegin, Queue** qend)
{
    if (*qbegin != nullptr) { deleteQueue(qbegin); *qend = nullptr; }

    printf("*** Generating new queue ***\n\n");
    int size = rangeReadInt(1, INT_MAX, "Specify queue size: ");

    while (size--)
        push_front(qbegin, qend, rand() % 50 - 20);

    printf("Generated!\n");
}

void menu_PrintQueue(Queue* qbegin, Queue *qend)
{
    if (qbegin == nullptr)
    {
        printf("Can't print empty queue.\n");
        return;
    }

    int dir = rangeReadInt(0, 1, "Specify direction (0 - regular, 1 - backwards): ");
    printf("*** QUEUE ***\n");
    printQueue(dir, qbegin, qend);
}

void menu_AppendElement(Queue** qbegin, Queue** qend)
{
    int element = rangeReadInt(INT_MIN, INT_MAX, "Specify value: ");
    int dir = rangeReadInt(0, 1, "Specify where to push (0 - front, 1 - back): ");
    if (dir == 0)
        push_front(qbegin, qend, element);
    else
        push_back(qbegin, qend, element);
}

void menu_PopElement(Queue** qbegin, Queue** qend)
{
    if (*qbegin == nullptr)
    {
        printf("Can't pop from empty queue.\n");
        return;
    }

    int dir = rangeReadInt(0, 1, "Specify from where to pop (0 - front, 1 - back): ");
    if (dir == 0)
        pop_front(qbegin, qend);
    else
        pop_back(qbegin, qend);
}

void menu_IndividualTask(Queue** qbegin, Queue** qend)
{
    printf("*** INDIVIDUAL TASK ***\n\n");
    printf("Remove even numbers from queue.\n");

    Queue *cur = *qbegin;
    while (cur != nullptr)
        if (cur->value % 2 == 0)
        {
            Queue* nxt = cur->next;
            Queue* prv = cur->prev;

            if (prv != nullptr) prv->next = nxt;
            else *qbegin = nxt;
            if (nxt != nullptr) nxt->prev = prv;
            else *qend = prv;

            delete cur;
            cur = nxt;
        }
        else
        {
            cur = cur->next;
        }
    printf("Done!\n");
}

int getMainMenuChoice()
{
    int choice = 0;
    int point = 0;

    printf("*** MAIN MENU ***\n\n");
    printf("Number | Action\n");
    printf("---------------\n");
    printf("%6d | Generate new queue\n", ++point);
    printf("%6d | Print queue\n", ++point);
    printf("%6d | Append new element\n", ++point);
    printf("%6d | Pop element\n", ++point);
    printf("%6d | Individual task\n", ++point);
    printf("%6d | Quit\n", ++point);

    choice = rangeReadInt(1, point, "Your choice > ");
    return choice;
}

int rangeReadInt(int minimal, int maximal, const char *prompt)
{
    bool ok = false;
    int result;
    do
    {
        printf("%s", prompt);
        ok = scanf("%d", &result) == 1;
        ok &= result >= minimal && result <= maximal;
        flush_stdin();
        if (!ok)
            printf("Please, input a value between %d and %d (inclusive)\n", minimal, maximal);
    } while (!ok);
    return result;
}

void flush_stdin()
{
    char c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}
