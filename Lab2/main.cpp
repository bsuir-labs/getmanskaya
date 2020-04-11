#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <ctype.h>

using namespace std;

int safeReadInt(bool *ok = nullptr);
int rangeReadInt(int minimal, int maximal, const char* prompt);

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

int safeReadString(char* buffer, unsigned maxLength)
{
    fgets(buffer, maxLength, stdin);
    // sanitize
    int size = strlen(buffer);
    while (size > 1 && buffer[size - 1] == '\n') buffer[size-- -1] = '\0';
    return size;
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
