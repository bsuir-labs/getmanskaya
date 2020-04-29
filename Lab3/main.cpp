#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <ctype.h>
#include <ctime>
#include <climits>

using namespace std;

const int TITLE_LEN = 50;
const char DATABASE_FILENAME[] = "database.dat";

struct Date
{
    unsigned year;
    unsigned month;
    unsigned day;
};
Date currentDate()
{
    time_t t = time(nullptr);
    tm time = *localtime(&t);
    Date date;
    date.day = time.tm_mday;
    date.month = time.tm_mon;
    date.year = time.tm_year;
    return date;
}

struct Cargo
{
    char title[TITLE_LEN];
    unsigned quantity;
    unsigned cost;
    Date income_date;
};


int getMainMenuChoice();

void menu_CreateNewRecord();
void menu_ShowAllRecords();
void menu_CorrectRecord();
void menu_LinearSearch();
void menu_SelectionSort();
void menu_QuickSort();
void menu_BinarySearch();
void menu_IndividualTask();

void selectionSort(Cargo* array, unsigned size);
void quickSort(Cargo* array, int left, int right);
int binarySearch(Cargo* array, unsigned size, const char title[]);

void readCargo(Cargo& cargo);
void printCargo(Cargo cargo);


// Functions for files
void createFile(const char filename[]);
void removeFile(const char filename[]);
void appendToFile(const char filename[], const char* data, unsigned size);
void writeToFile(const char filename[], const char* data, unsigned size);
unsigned readFile(const char filename[], char** buffer, unsigned maxSize = 0);
unsigned filelength(FILE* file);

// Functions for safe input
int rangeReadInt(int minimal, int maximal, const char* prompt);
int safeReadString(char* buffer, unsigned maxLength);
void flush_stdin();

Date promptDate(const char* prompt);

int main()
{
    bool stopRequested = false;

    while (!stopRequested)
    {
        switch (getMainMenuChoice())
        {
            case 1: menu_CreateNewRecord(); break;
            case 2: menu_ShowAllRecords(); break;
            case 3: menu_CorrectRecord(); break;
            case 4: menu_LinearSearch(); break;
            case 5: menu_SelectionSort(); break;
            case 6: menu_QuickSort(); break;
            case 7: menu_BinarySearch(); break;
            case 8: menu_IndividualTask(); break;
            case 9:
                stopRequested = true;
                printf("Goodbye! have a nice day!\n");
                break;
            default: printf("Something went wrong...\n");
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
    printf("%6d | Create new record\n", ++point);
    printf("%6d | Show all records\n", ++point);
    printf("%6d | Edit record\n", ++point);
    printf("%6d | Linear search\n", ++point);
    printf("%6d | Selection sort\n", ++point);
    printf("%6d | Quick sort\n", ++point);
    printf("%6d | Binary search\n", ++point);
    printf("%6d | Individual task\n", ++point);
    printf("%6d | Quit\n", ++point);

    choice = rangeReadInt(1, point, "Your choice > ");
    return choice;
}

void menu_CreateNewRecord()
{
    printf("*** Creating new record ***\n");
    Cargo cargo;
    readCargo(cargo);
    appendToFile(DATABASE_FILENAME, (char*)&cargo, sizeof(cargo));
}

void menu_ShowAllRecords()
{
    Cargo* cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    for (unsigned i = 0; i < size; ++i)
        printCargo(cargos[i]);

    delete[] cargos;
}

void menu_CorrectRecord()
{
    Cargo* cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s\n", i, cargos[i].title);

    int numberToCorrect = rangeReadInt(0, size, "Specify number to correct: ");

    printCargo(cargos[numberToCorrect]);
    printf("Specify new values:\n");
    readCargo(cargos[numberToCorrect]);

    writeToFile(DATABASE_FILENAME, (char*)cargos, size * sizeof(Cargo));

    delete[] cargos;
}

void menu_LinearSearch()
{
    Cargo* cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    printf("Specify title to search for: ");
    char title[50];
    safeReadString(title, 49);

    printf("Searching for items with title: %s\n", title);

    bool found = false;
    for (unsigned i = 0; i < size; ++i)
        if (strcmp(title, cargos[i].title) == 0)
        {
            printCargo(cargos[i]);
            found = true;
        }
    if (!found) printf("No items found.\n");

    delete[] cargos;
}

void menu_SelectionSort()
{
    Cargo* cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    printf("File state before Selection sort:\n");
    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s\n", i, cargos[i].title);
    printf("\n");

    selectionSort(cargos, size);

    printf("File state after Selection sort:\n");
    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s\n", i, cargos[i].title);
    printf("\n");

    writeToFile(DATABASE_FILENAME, (char*)cargos, size * sizeof(Cargo));
    delete[] cargos;
}

void menu_QuickSort()
{
    Cargo* cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    printf("File state before Quick sort:\n");
    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s\n", i, cargos[i].title);

    quickSort(cargos, 0, size - 1);

    printf("File state after Quick sort:\n");
    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s\n", i, cargos[i].title);

    writeToFile(DATABASE_FILENAME, (char*)cargos, size * sizeof(Cargo));
    delete[] cargos;
}

void menu_BinarySearch()
{
    Cargo* cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    printf("Specify title to search for: ");
    char title[50];
    safeReadString(title, 49);

    int index = binarySearch(cargos, size, title);
    if (index != -1)
        printCargo(cargos[index]);
    else
        printf("No items found.\n");

    delete[] cargos;
}

void menu_IndividualTask()
{
    Cargo *cargos = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&cargos);
    unsigned size = bytes / sizeof(Cargo);

    printf("Alphabetical order of cargos with the cost larger than 100 000.\n");

    quickSort(cargos, 0, size - 1);

    bool found = false;

    for (unsigned i = 0; i < size; ++i)
        if (cargos[i].cost * cargos[i].quantity > 100000)
        {
            printCargo(cargos[i]);
            found = true;
        }

    if (!found)
        printf("No cargos found.\n");

    delete[] cargos;
}

void selectionSort(Cargo* array, unsigned size)
{
    for (unsigned i = 0; i < size - 1; ++i)
    {
        unsigned min_index = i;
        for (unsigned j = i + 1; j < size; ++j)
            if (strcmp(array[min_index].title, array[j].title) > 0)
                min_index = j;
        if (min_index != i)
        {
            Cargo tmp = array[min_index];
            array[min_index] = array[i];
            array[i] = tmp;
        }
    }
}

void quickSort(Cargo* array, int left, int right)
{
    char buffer[TITLE_LEN + 1]; // buffer for comparison
    int l = left, r = right;
    strcpy(buffer, array[(l + r) / 2].title);
    do {
        while (strcmp(array[l].title, buffer) < 0) ++l;
        while (strcmp(array[r].title, buffer) > 0) --r;
        if (l <= r)
        {
            Cargo tmp = array[l];
            array[l] = array[r];
            array[r] = tmp;
            ++l;
            --r;
        }
    } while (l <= r);
    if (left < r) quickSort(array, left, r);
    if (l < right) quickSort(array, l, right);
}

int binarySearch(Cargo* array, unsigned size, const char title[])
{
    int result = -1;    // -1 means "nothing was found"
    int l = 0, r = size - 1, mid;
    while (l < r)
    {
        mid = (l + r) / 2;
        if (strcmp(title, array[mid].title) > 0)
            l = mid + 1;
        else
            r = mid;
    }
    if (strcmp(title, array[l].title) == 0) result = l;
    return result;
}

void readCargo(Cargo& cargo)
{
    printf("*** reading cargo info ***\n\n");

    printf("Title: ");  safeReadString(cargo.title, TITLE_LEN);
    cargo.quantity = rangeReadInt(1, INT_MAX, "Quantity: ");
    cargo.cost = rangeReadInt(0, INT_MAX, "Cost: ");
    cargo.income_date = promptDate("Income date (YYYY.MM.DD): ");
}

void printCargo(Cargo cargo)
{
    printf("Title:       %s\n", cargo.title);
    printf("Quantity:    %d\n", cargo.quantity);
    printf("Cost:        %d\n", cargo.cost);
    printf("Income date: %d.%02d.%02d\n", cargo.income_date.year,
        cargo.income_date.month,
        cargo.income_date.day);
    printf("\n");
}

void createFile(const char filename[])
{
    FILE* file = fopen(filename, "wb");
    if (file == nullptr)
        fprintf(stderr, "Can't create file %s. Error.\n", filename);
    else
    {
        fclose(file);
        printf("File %s has been created.\n", filename);
    }
}

void removeFile(const char filename[])
{
    if (remove(filename) != 0)
        fprintf(stderr, "Can't remove file %s. Error\n", filename);
    else
        printf("Removed file successfully!\n");
}

void appendToFile(const char filename[], const char* data, unsigned size)   // TODO: refactor (look at writeToFile)
{
    FILE* file = fopen(filename, "ab");
    if (file)
    {
        fwrite(data, 1, size, file);
        fclose(file);
        printf("%d bytes appended to file %s.\n", size, filename);
    }
    else
    {
        fprintf(stderr, "Can't write to file %s!\n", filename);
    }
}

void writeToFile(const char filename[], const char* data, unsigned size)
{
    FILE* file = fopen(filename, "wb");
    if (file)
    {
        fwrite(data, 1, size, file);
        fclose(file);
        printf("%d bytes appended to file %s.\n", size, filename);
    }
    else
    {
        fprintf(stderr, "Can't write to file %s!\n", filename);
    }
}

unsigned readFile(const char filename[], char** buffer, unsigned maxSize)
{
    FILE* file = fopen(filename, "rb");
    unsigned read = 0;
    if (file)
    {
        unsigned length = filelength(file);
        if (maxSize) length = max(length, maxSize);
        *buffer = new char[length];
        read = fread(*buffer, 1, length, file);
        if (ferror(file) != 0)
            fprintf(stderr, "Some error occurred while reading");
        fclose(file);
    }
    else
        fprintf(stderr, "Can't open file %s for reading\n", filename);
    return read;
}

unsigned filelength(FILE* file)
{
    unsigned position = ftell(file);
    fseek(file, 0, SEEK_END);
    unsigned length = ftell(file);
    fseek(file, position, SEEK_SET);
    return length;
}

int rangeReadInt(int minimal, int maximal, const char* prompt)
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

int safeReadString(char* buffer, unsigned maxLength)
{
    fgets(buffer, maxLength, stdin);
    // sanitize
    int size = strlen(buffer);
    while (size > 1 && buffer[size - 1] == '\n') buffer[size-- - 1] = '\0';
    return size;
}

void flush_stdin()
{
    char c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

Date promptDate(const char* prompt)
{
    bool ok = false;
    Date result;
    do {
        printf("%s", prompt);
        ok = scanf("%d.%d.%d", &result.day, &result.month, &result.year);
        flush_stdin();
        ok &= result.day > 0 && result.day < 32;
        ok &= result.month > 0 && result.month < 13;
        ok &= result.year > 1970 && result.year < 2021;
        if (!ok)
            printf("Please, input a valid date in format DD.MM.YYYY\n");
    } while (!ok);
    return result;
}
