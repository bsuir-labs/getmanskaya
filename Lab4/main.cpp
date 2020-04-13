#include <cstdio>
#include <climits>
#include <algorithm>
#include <ctype.h>
#include <cstring>

struct Stack
{
    int value   = 0;
    Stack* next = nullptr;
};

Stack* push(Stack* parent, int value)
{
    Stack* st = new Stack;
    st->value = value;
    st->next = parent;
    return st;
}

void print(Stack* top)
{
    if (!top)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("*** stack ***\n");
    while (top)
    {
        printf("%d\n", top->value);
        top = top->next;
    }
}

void deleteStack(Stack **top)
{
    while (*top)
    {
        Stack *tmp = *top;
        *top = (*top)->next;
        delete tmp;
    }
}

Stack* pop(Stack* top, int *value)
{
    if (!top)
    {
        printf("Error. Stack is already empty.\n");
        return nullptr;
    }

    *value = top->value;

    Stack *tmp = top;
    top = top->next;
    delete tmp;

    return top;
}

int getMainMenuChoice();

void menu_GenerateNewStack(Stack** stack);
void menu_PrintStack(Stack* stack);
void menu_AppendElement(Stack** stack);
void menu_PopElement(Stack** stack);
void menu_SortMethod_1(Stack** stack);
void menu_SortMethod_2(Stack** stack);
void menu_IndividualTask(Stack** stack);

// safe input functions
int safeReadInt(bool *ok = nullptr);
int rangeReadInt(int minimal, int maximal, const char* prompt);

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

void menu_GenerateNewStack(Stack** stack)
{
    printf("*** Generating new stack ***\n\n");
    int size = rangeReadInt(1, INT_MAX, "Specify stack size: ");

    while (size--)
        *stack = push(*stack, rand() % 50 - 25);
}

void menu_PrintStack(Stack* stack)
{
    print(stack);
}

void menu_AppendElement(Stack** stack)
{
    int element = rangeReadInt(INT_MIN, INT_MAX, "Specify value: ");
    *stack = push(*stack, element);
}

void menu_PopElement(Stack** stack)
{
    int dummy;
    *stack = pop(*stack, &dummy);
}

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

void menu_IndividualTask(Stack** stack)
{
    printf("*** INDIVIDUAL TASK ***\n\n");
    printf("Remove even numbers from stack.\n");

    Stack* prev = nullptr, *cur = *stack;
    while (cur != nullptr) // while (cur) is also a possible option
        if (cur->value % 2 == 0)    // it should be removed
        {
            Stack* tmp = cur->next;
            if (prev != nullptr)    // This is not the first element in stack
                prev->next = tmp;   // Moving pointer from previous element to get current element around
            else                    // This is the first element in stack
                *stack = tmp;       // Then we just should move the beginning of the stack forward

            delete cur;             // Delete unnecessary element
            cur = tmp;              // Move current pointer
        } else {
            prev = cur;             // Nothing should happen
            cur = cur->next;        // Just moving on
        }

    printf("Done!\n");
}

int safeReadInt(bool* ok)
{
    static const unsigned int LINE_SIZE = 255;
    char lineBuffer[LINE_SIZE];
    int result = 0;
    char sign = 1;
    if (ok) *ok = false;

    // get the whole line
    fgets(lineBuffer, LINE_SIZE, stdin);
    int lineSize = strlen(lineBuffer);

    // parse the buffer
    int i;
    for (i = 0; i < lineSize && isspace(lineBuffer[i]); ++i);   // skip spaces
    if (i < lineSize && (lineBuffer[i] == '+' || lineBuffer[i] == '-'))
        if (lineBuffer[i++] == '-')
            sign *= -1;
    for (; i < lineSize && isdigit(lineBuffer[i]); ++i)
    {
        if (ok && !(*ok)) *ok = true;
        result = result * 10 + int(lineBuffer[i] - '0');
    }

    return result * sign;
}


int rangeReadInt(int minimal, int maximal, const char *prompt)
{
    bool ok = false;
    int result = 0;
    while (!ok)
    {
        printf("%s", prompt);
        result = safeReadInt(&ok);
        if (!ok || result < minimal || result > maximal)
        {
            printf("Please, input a value between %d and %d (inclusive)\n", minimal, maximal);
            ok = false;
        }
    }
    return result;
}
