#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <ctype.h>

using namespace std;

int rangeReadInt(int minimal, int maximal, const char* prompt);
void flush_stdin();

int recursiveFind(const int* array, int left, int right, int element);
int nonrecursiveFind(const int* array, unsigned size, int element);
void generateArray(int* array, unsigned size);
void printArray(int* array, unsigned size);

// Menu choice function
int getMainMenuChoice();

// Main menu options
void menu_RecursiveImpl(const int* array, const unsigned size);
void menu_NonRecursiveImpl(const int* array, const unsigned size);

int main()
{
    const unsigned kSize = 20;
    int array[kSize];
    generateArray(array, kSize);

    bool stopRequested = false;
    while (!stopRequested)
    {
        switch (getMainMenuChoice()) {
            case 1: generateArray(array, kSize); break;
            case 2: menu_RecursiveImpl(array, kSize); break;
            case 3: menu_NonRecursiveImpl(array, kSize); break;
            case 4:
                stopRequested = true;
                printf("GoodBye! Have a nice day!\n");
                break;
            default: printf("Something went wrong.");
        }
        getc(stdin);
    }

    return 0;
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

int getMainMenuChoice()
{
    int choice = 0;
    int point = 0;

    printf("*** MAIN MENU ***\n\n");
    printf("Number | Action\n");
    printf("---------------\n");
    printf("%6d | Regenerate array\n", ++point);
    printf("%6d | Recursive binary search\n", ++point);
    printf("%6d | Non-recursive binary search\n", ++point);
    printf("%6d | Quit\n", ++point);

    choice = rangeReadInt(1, point, "Your choice > ");
    return choice;
}

int recursiveFind(const int* array, int left, int right, int element)
{
    if (left == right)
    {
        if (array[left] == element)
            return left;
        else
            return -1;
    }

    int mid = (left + right) / 2;
    if (element > array[mid])
        return recursiveFind(array, mid + 1, right, element);
    else
        return recursiveFind(array, left, mid, element);
}

int nonrecursiveFind(const int* array, unsigned size, int element)
{
    int left = 0, right = size - 1;
    while (left < right)
    {
        int mid = (left + right) / 2;
        if (element > array[mid])
            left = mid + 1;
        else
            right = mid;
    }
    if (array[left] == element) return left;
    return -1;
}

void generateArray(int* array, unsigned size)
{
    srand(time(nullptr));
    for (unsigned i = 0; i < size; ++i)
        array[i] = rand() % 50 - 20;

    std::sort(array, array + size);

    printf("Generated array:\n");
    printArray(array, size);
}

void printArray(int* array, unsigned size)
{
    for (unsigned i = 0; i < size; ++i)
        printf("%4d", array[i]);
    printf("\n");
}

void menu_RecursiveImpl(const int* array, const unsigned size)
{
    int elementToFind = rangeReadInt(-100, 100, "Specify element to find: ");
    int result = recursiveFind(array, 0, size - 1, elementToFind);
    printf("\t\tRecursive result:     %d\n", result);
}

void menu_NonRecursiveImpl(const int* array, const unsigned size)
{
    int elementToFind = rangeReadInt(-100, 100, "Specify element to find: ");
    int result = nonrecursiveFind(array, size, elementToFind);
    printf("\t\tNon-recursive result: %d\n", result);
}
