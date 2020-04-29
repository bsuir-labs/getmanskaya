#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <cstring>

// Структура одного элемента в стэке
struct Stack
{
    int value   = 0;
    Stack* next = nullptr;
};

/// \brief Функция для добавления элемента в стэк
/// \param parent - Указатель на вершину стэка, куда будет добавляться элемент
/// \param value  - Значение, которе добавляется в стэк
/// \return Указатель на новую вершину стэка
Stack* push(Stack* parent, int value)
{
    Stack* st = new Stack;  // создаём новый элемент
    st->value = value;      // кладём туда значение
    st->next = parent;      // указываем на старую вершину
    return st;              // и возвращаем этот элемент
}

/// \brief Вывод стэка
/// \param top - указатель на вершину
void print(Stack* top)
{
    if (!top)           // если вершина это нулевой указатель
    {
        printf("Stack is empty.\n");    // то стэк пуст
        return;                         // уходим
    }

    printf("*** stack ***\n");
    while (top)                         // иначе, пока мы не спустились до конца
    {
        printf("%d\n", top->value);     // выводим значение в текущем элементе
        top = top->next;                // сдвигаемся на следующий
    }
}

/// \brief Удаление стэка
/// \param top - указатель на указатель на вершину стэка
void deleteStack(Stack **top)
{
    while (*top)                // пока не дошли до конца
    {
        Stack *tmp = *top;      // запоминаем адрес текущего элемента
        *top = (*top)->next;    // сдвигаемся дальше
        delete tmp;             // удаляем элемент по адресу, что запомнили
    }
}

/// \brief Функция, которая достаёт из стэка верхний элемент
/// \param top - указатель на вершину стэка
/// \param value - указатель на переменную, куда нужно положить значение верхнего элемента в стэке
/// \return Указатель на новую вершину стэка
Stack* pop(Stack* top, int *value)
{
    if (!top)   // если стэк уже пустой, то нечего доставать
    {
        printf("Error. Stack is already empty.\n");
        return nullptr;
    }

    *value = top->value;    // Иначе - достаём значение из вершины

    Stack *tmp = top;       // И удаляем вершину (как в ф-ции deleteStack)
    top = top->next;
    delete tmp;

    return top;             // возвращаем новую вершину
}

int getMainMenuChoice();

void menu_GenerateNewStack(Stack** stack);      // Генерация стэка
void menu_PrintStack(Stack* stack);             // Вывод стэка
void menu_AppendElement(Stack** stack);         // Добавить элемент в стэк
void menu_PopElement(Stack** stack);            // Удалить элемент из стэка
void menu_SortMethod_1(Stack** stack);          // Сортировка первым методом (метода)
void menu_SortMethod_2(Stack** stack);          // Сортировка вторым методом
void menu_IndividualTask(Stack** stack);        // Индивидуальное задание

// Функции защищённого ввода (см первую лабу)
int rangeReadInt(int minimal, int maximal, const char* prompt);
void flush_stdin();

int main()
{
    Stack* stack = nullptr;
    bool stopRequested = false;

    while (!stopRequested)
    {
        switch (getMainMenuChoice())
        {
        case 1: menu_GenerateNewStack(&stack);  break;
        case 2: menu_PrintStack(stack);         break;
        case 3: menu_AppendElement(&stack);     break;
        case 4: menu_PopElement(&stack);        break;
        case 5: menu_SortMethod_1(&stack);      break;
        case 6: menu_SortMethod_2(&stack);      break;
        case 7: menu_IndividualTask(&stack);    break;
        case 8:
            stopRequested = true;
            printf("GoodBye! Have a nice day!\n");
            break;
        default: printf("Something bad happened...\n");
        }

        getc(stdin);
    }

    return 0;
}

int getMainMenuChoice()
{
    int choice = 0;
    int point = 0;

    printf("*** MAIN MENU ***\n\n");
    printf("Number | Action\n");
    printf("---------------\n");
    printf("%6d | Generate new stack\n", ++point);
    printf("%6d | Print stack\n", ++point);
    printf("%6d | Append new element\n", ++point);
    printf("%6d | Pop last element\n", ++point);
    printf("%6d | Sort with method 1\n", ++point);
    printf("%6d | Sort with method 2\n", ++point);
    printf("%6d | Individual task\n", ++point);
    printf("%6d | Quit\n", ++point);

    choice = rangeReadInt(1, point, "Your choice > ");
    return choice;
}

// Генерация стэка
void menu_GenerateNewStack(Stack** stack)
{
    printf("*** Generating new stack ***\n\n");
    int size = rangeReadInt(1, INT_MAX, "Specify stack size: ");    // Спрашиваем размер

    while (size--)
        *stack = push(*stack, rand() % 50 - 25);    // генерируем стэк
}

// Вывод стэка
void menu_PrintStack(Stack* stack)
{
    print(stack);
}

// Добавление нового элемента
void menu_AppendElement(Stack** stack)
{
    int element = rangeReadInt(INT_MIN, INT_MAX, "Specify value: ");    // спрашиваем элемент
    *stack = push(*stack, element); // добавляем
}

// Удаление элемента
void menu_PopElement(Stack** stack)
{
    int dummy;  // Временная переменная (нам обязательно надо куда-то положить значение из верхнего элемента стэка)
    *stack = pop(*stack, &dummy);   // Удаляем
}

// Сортировка первым методом из методы
void menu_SortMethod_1(Stack** stack)
{
    if (!*stack)
    {
        printf("Can't sort empty stack.\n");
        return;
    }

    int dummy = 0;
    *stack = push(*stack, dummy);   // push dummy
    if ((*stack)->next->next != nullptr)
    {
        Stack* last_checked = nullptr, *current;
        do {
            for (current = *stack; current->next->next != last_checked; current = current->next)
                if (current->next->value > current->next->next->value)
                {
                    Stack* tmp = current->next->next;
                    current->next->next = tmp->next;
                    tmp->next = current->next;
                    current->next = tmp;
                }
            last_checked = current->next;
        } while ((*stack)->next->next != last_checked);
    }
    *stack = pop(*stack, &dummy);

    printf("Stack sorted using method 1.\n");
}

// Сортировка вторым методом из методы
void menu_SortMethod_2(Stack** stack)
{
    if (!*stack)
    {
        printf("Can't sort empty stack.\n");
        return;
    }

    Stack* last_checked = nullptr, *cur;
    do {
        for (cur = *stack; cur->next != last_checked; cur = cur->next)
            if (cur->value > cur->next->value)
            {
                int tmp = cur->value;
                cur->value = cur->next->value;
                cur->next->value = tmp;
            }
        last_checked = cur;
    } while ((*stack)->next != last_checked);

    printf("Stack sorted using method 2.\n");
}

// Индивидуальное задание
void menu_IndividualTask(Stack** stack)
{
    printf("*** INDIVIDUAL TASK ***\n\n");
    printf("Remove even numbers from stack.\n");

    Stack* prev = nullptr, *cur = *stack;
    while (cur != nullptr) // Пока мы не дошли до конца стэка
        if (cur->value % 2 == 0)    // Если текущий элемент чётный, его надо удалить
        {
            Stack* tmp = cur->next; // Запоминаем адрес следующего элемента
            if (prev != nullptr)    // Если у нас есть адрес предыдущего элемента
                prev->next = tmp;   // То нужно связать предыдущий элемент с элементом следующим за текущим
            else                    // Если адреса нету, то мы сейчас на вершине стэка
                *stack = tmp;       // Значит, нам просто нужно опустить вершину пониже

            delete cur;             // Удаляем текущий элемент
            cur = tmp;              // И двигаемся дальше по стэку
        } else {                    // Ну а если элемент был нечётным
            prev = cur;             // То ничего не должно случиться
            cur = cur->next;        // Просто двигаемся дальше
        }

    printf("Done!\n");
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
