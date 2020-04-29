#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <ctime>

// Описание структуры для очереди (двусвязного списка)
struct Queue
{
    int value = 0;
    Queue* prev = nullptr;
    Queue* next = nullptr;
};

/// \brief Добавление элемента в начало очереди
/// \param first - указатель на указатель на первый элемент в очереди
/// \param last  - указатель на указатель на последний элемент в очереди
/// \param value - число, которое мы хотим добавить
void push_front(Queue **first, Queue **last, int value)
{
    Queue *temp = new Queue;        // Создаём новый элемент
    temp->value = value;            // Задаём ему значение
    if (*first == NULL) {           // Если очередь была пуста
        *first = *last = temp;      // То этот элемент станет и первым, и последним
    }
    else {                          // иначе
        (*first)->prev = temp;      // соединяем его с первым элементом
        temp->next = *first;
        *first = temp;              // и говорим, что теперь это новый первый элемент
    }
}

/// \brief Добавление элемента в конец очереди
/// \param first - указатель на указатель на первый элемент в очереди
/// \param last  - указатель на указатель на последний элемент в очереди
/// \param value - число, которое мы хотим добавить
void push_back(Queue **first, Queue **last, int value)
{
    Queue *temp = new Queue;        // По сути, то же самое, что и в push_front,
    temp->value = value;            // только цепляем, соответственно, к последнему элементу
    if (*first == NULL) {
        *first = *last = temp;
    }
    else {
        (*last)->next = temp;
        temp->prev = *last;
        *last = temp;
    }
}

/// \brief Удаление всей очереди
/// \param p - указатель на начало очереди
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

/// \brief Вывод очереди на экран
/// \param code - код, показывающий, с какой стороны выводить очередь
/// Если равен 0, то выводим с начала, иначе - с конца
/// \param begin - указатель на начало очереди
/// \param end   - указатель на конец очереди
void printQueue(int code, Queue *begin, Queue *end)
{
    Queue *t = nullptr;
    if (code == 0) t = begin;       // в зависимости от кода, выбираем первый элемент
    else t = end;                   // (начало или конец)
    while (t != NULL)                   // и пока не прошли всю очередь
    {
        printf("%d, ", t->value);       // выводим элемент
        if (code == 0) t = t->next;     // и сдвигаемся в зависимости от направления
        else
            t = t->prev;
    }
    printf("\n");
}

/// \brief Удаление элемента из конца очереди
/// \param first - указатель на указатель на первый элемент очереди
/// \param last  - указатель на указатель на последний элемент
void pop_back(Queue **first, Queue **last)
{
    if (*first == *last)        // если в очереди всего один элемент
    {
        delete *first;          // то удаляем его
        *last = nullptr;        // и всё
        *first = nullptr;
        return;
    }

    Queue *tmp = (*last)->prev; // Иначе, запоминаем адрес предпоследнего элемента
    delete *last;               // удаляем последний
    *last = tmp;                // Говорим, что теперь предпоследний стал последним
    (*last)->next = NULL;       // И помечаем, что дальше за ним ничего нету
}

/// \brief Удаление элемента из начала очереди
/// \param first - указатель на указатель на первый элемент очереди
/// \param last  - указатель на указатель на последний элемент
void pop_front(Queue **first, Queue **last)
{                               // Всё тут аналогично pop_back
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

void menu_GenerateNewQueue(Queue** qbegin, Queue** qend);   // генерация очереди
void menu_PrintQueue(Queue* qbegin, Queue *qend);           // вывод на экран
void menu_AppendElement(Queue** qbegin, Queue** qend);      // добавление элемента
void menu_PopElement(Queue** qbegin, Queue** qend);         // удаление элемента
void menu_IndividualTask(Queue** qbegin, Queue** qend);     // индивидуальное задание

// safe input functions (см лабу 1)
int rangeReadInt(int minimal, int maximal, const char* prompt);
void flush_stdin();

int main()
{
    srand(time(nullptr));

    Queue *qbegin, *qend;
    qbegin = qend = nullptr;    // пока что очередь пуста

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

// Генерация очереди
// Аналогично, как для стэка, см. лабу 4
void menu_GenerateNewQueue(Queue** qbegin, Queue** qend)
{
    if (*qbegin != nullptr) { deleteQueue(qbegin); *qend = nullptr; }

    printf("*** Generating new queue ***\n\n");
    int size = rangeReadInt(1, INT_MAX, "Specify queue size: ");

    while (size--)
        push_front(qbegin, qend, rand() % 50 - 20);

    printf("Generated!\n");
}

// Вывод очереди на экран
void menu_PrintQueue(Queue* qbegin, Queue *qend)
{
    if (qbegin == nullptr)
    {
        printf("Can't print empty queue.\n");
        return;
    }
    // спрашиваем направление
    int dir = rangeReadInt(0, 1, "Specify direction (0 - regular, 1 - backwards): ");
    printf("*** QUEUE ***\n");
    printQueue(dir, qbegin, qend);  // выводим очередь
}

// Добавление элемента
void menu_AppendElement(Queue** qbegin, Queue** qend)
{
    int element = rangeReadInt(INT_MIN, INT_MAX, "Specify value: ");                // спрашиваем значение
    int dir = rangeReadInt(0, 1, "Specify where to push (0 - front, 1 - back): ");  // спрашиваем, куда пихать
    if (dir == 0)
        push_front(qbegin, qend, element);      // и добавляем
    else
        push_back(qbegin, qend, element);
}

// Удаление элемента
void menu_PopElement(Queue** qbegin, Queue** qend)
{
    if (*qbegin == nullptr)
    {
        printf("Can't pop from empty queue.\n");
        return;
    }
        // Поступаем аналогично добавлению элемента
    int dir = rangeReadInt(0, 1, "Specify from where to pop (0 - front, 1 - back): ");
    if (dir == 0)
        pop_front(qbegin, qend);
    else
        pop_back(qbegin, qend);
}

// Индивидуальное задание
void menu_IndividualTask(Queue** qbegin, Queue** qend)
{
    printf("*** INDIVIDUAL TASK ***\n\n");
    printf("Remove even numbers from queue.\n");

    Queue *cur = *qbegin;
    while (cur != nullptr)                          // Пока не прошли очередь до конца
        if (cur->value % 2 == 0)                    // Если текущий элемент чётный
        {                                           // надо его удалить
            Queue* nxt = cur->next;                 // Запоминаем адрес следующего элемента
            Queue* prv = cur->prev;                 // И адрес предыдущего

            if (prv != nullptr) prv->next = nxt;    // Если предыдущий элемент был (т.е. текущий - не первый)
                                                    // то соединяем предыдущий со следующим
            else *qbegin = nxt;                     // иначе просто сдвигаем начало очереди дальше
            if (nxt != nullptr) nxt->prev = prv;    // То же самое проверяем для следующего элемента
            else *qend = prv;

            delete cur;                             // Удаляем текущий
            cur = nxt;                              // Двигаемся дальше
        }
        else                                        // А если элемент был нечётный
        {
            cur = cur->next;                        // То ничего не делаем, просто двигаемся
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
