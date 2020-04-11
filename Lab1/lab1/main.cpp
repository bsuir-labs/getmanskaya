#include <iostream>
#include <cstring>
#include <climits>
#include <assert.h>
#include <stdio.h>
#include <sys/io.h>     // TODO: pay attention! This is for *nix only

using namespace std;

const unsigned int SURNAME_LEN = 50;
const unsigned int INITIALS_LEN = 5;

const char DATABASE_FILENAME[] = "students.dat";
const char OUTPUT_FILENAME[] = "output.txt";

// Struct of student and functions for work with this structure
struct Student
{
    char surname[SURNAME_LEN];
    char initials[INITIALS_LEN];   // format as in Microsoft Office products (for example, Kanstancin Dzmitryjevic Novikau => Novikau KD)

    unsigned short mark_physics;
    unsigned short mark_maths;
    unsigned short mark_informatics;
    unsigned short mark_chemistry;

    double average_mark;

    static void updateAverage(Student& student)
    {
        double sum = student.mark_maths + student.mark_physics + student.mark_chemistry + student.mark_informatics;
        student.average_mark = sum / 4;
    }
};
void readStudent(Student &student);
void printStudent(Student student);
void fprintStudent(Student student, FILE* stream);

int safeReadInt(bool *ok = nullptr);
int safeReadString(char* buffer, unsigned maxLength);
char safeGetChar();
void clearInputBuffer();
int getChoice(int minimal, int maximal);

// Menu choice functions
int getMainMenuChoice();

// Main menu choices
void createNewRecord(); // 1 - create new record
void showAllRecords();  // 2 - show all records
void correctRecord();   // 3 - correct record
void individualTask();  // 4 - individual task
void goodbyeMessage();  // 5 - Quit

// Functions for files
void createFile(const char filename[]);
void removeFile(const char filename[]);
void appendToFile(const char filename[], const char* data, unsigned size);
void writeToFile(const char filename[], const char* data, unsigned size);
unsigned readFile(const char filename[], char** buffer, unsigned maxSize = 0);
unsigned filelength(FILE* file);

// Temp debug functions
void unimplemented();

int main()
{
    bool stopRequested = false;

    createFile(OUTPUT_FILENAME);    // reset output file

    while (!stopRequested)
    {
        switch (getMainMenuChoice())
        {
        case 1: createNewRecord(); break;
        case 2: showAllRecords(); break;
        case 3: correctRecord(); break;
        case 4: individualTask(); break;
        case 5:
            stopRequested = true;
            goodbyeMessage();
            break;
        default: printf("Undefined behavior. Something wrong happened.\n");
        }

        getc(stdin);
    }
    return 0;
}

void unimplemented()
{
    printf("Sorry, this function is not implemented yet!\n");
}

void clearInputBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
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

int safeReadString(char* buffer, unsigned maxLength)
{
    fgets(buffer, maxLength, stdin);
    // sanitize
    int size = strlen(buffer);
    while (size > 1 && buffer[size - 1] == '\n') buffer[size-- -1] = '\0';
    return size;
}

char safeGetChar()
{
    char buffer[255];
    fgets(buffer, 254, stdin);
    if (strlen(buffer) > 1) return buffer[0];
    return '\0';
}

int getChoice(int minimal, int maximal)
{
    bool ok;
    int res = safeReadInt(&ok);
    ok = ok && (res >= minimal && res <= maximal);
    return ok ? res : minimal - 1;
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
    printf("%6d | Correct record\n", ++point);
    printf("%6d | Individual task\n", ++point);
    printf("%6d | Quit\n", ++point);

    bool ok = false;

    while (!ok)
    {
        printf("\nYour choice > ");
        choice = safeReadInt(&ok);

        if (!ok)
        {
            printf("[ERROR] Please, check your input. It should contain only digits.\n");
            continue;
        }

        if (choice < 1 || choice > point)
        {
            ok = false;
            printf("[ERROR] No such index in menu. Please, correct your input.\n");
        }
    }
    return choice;
}

void createNewRecord()
{
    printf("*** Creating new record ***\n");

    Student record;
    readStudent(record);

    appendToFile(DATABASE_FILENAME, (char*)&record, sizeof(record));
}

void showAllRecords()
{
    Student* students = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&students);
    unsigned size = bytes / sizeof(Student);

    FILE* output = fopen(OUTPUT_FILENAME, "a");
    if (output)
    {
        for (unsigned i = 0; i < size; ++i)
            fprintStudent(students[i], output);
        fclose(output);
    }
    else
    {
        printf("Couldn't open %s file for writing (appending)\n", OUTPUT_FILENAME);
    }

    for (unsigned i = 0; i < size; ++i)
        printStudent(students[i]);

    delete[] students;
}

void correctRecord()
{
    Student* students = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&students);
    unsigned size = bytes / sizeof(Student);

    // Print names only
    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s %s\n", i, students[i].surname, students[i].initials);

    printf("Specify number to correct: ");
    int numberToCorrect = -1;
    bool ok = false;
    while (!ok || numberToCorrect < 0 || numberToCorrect >= int(size))
        numberToCorrect = safeReadInt(&ok);

    printStudent(students[numberToCorrect]);
    printf("Specify new values:\n");
    readStudent(students[numberToCorrect]);

    writeToFile(DATABASE_FILENAME, (char*)students, size * sizeof(Student));

    delete[] students;
}

void individualTask()
{
    FILE* output = fopen(OUTPUT_FILENAME, "a");
    if (!output) printf("Couldn't open %s for writing\n", OUTPUT_FILENAME);

    printf("*** INDIVIDUAL TASK ***\n");
    printf("\nSpecify the letter you want to start with: ");

    char letter = safeGetChar();

    printf("Filtering students according to rule:\n");
    printf("Average mark is larger than 8 and the surname starts with %c\n", letter);

    if (output)
    {
        fprintf(output, "*** INDIVIDUAL TASK ***\n");
        fprintf(output, "Filtering students according to rule:\n");
        fprintf(output, "Average mark is larger than 8 and the surname starts with %c\n", letter);
    }

    Student* students = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&students);
    unsigned size = bytes / sizeof(Student);

    bool found = false;
    for (unsigned i = 0; i < size; ++i)
        if (students[i].surname[0] == letter && students[i].average_mark > 8)
        {
            printStudent(students[i]);
            if (output) fprintStudent(students[i], output);
            found = true;
        }

    if (!found)
    {
        printf("No users found.\n");
        if (output) fprintf(output, "No users found.\n");
    }

    if (output) fclose(output);
    delete[] students;
}

void goodbyeMessage()
{
    printf("Goodbye! Have a nice day!\n");
    printf("Press Enter key to continue.\n");
}

void readStudent(Student &student)                      // TODO: refactor
{
    printf("*** reading student info ***\n\n");

    printf("Surname: ");
    safeReadString(student.surname, SURNAME_LEN);
    printf("Initials: ");
    safeReadString(student.initials, INITIALS_LEN);

    bool inner_ok = false;
    while (!inner_ok)                   // TODO: maybe move to a separate function???
    {
        printf("Mark for physics: ");
        student.mark_physics = safeReadInt(&inner_ok);
        if (!inner_ok || student.mark_physics < 0 || student.mark_physics > 10)
            printf("Please, input a value between 0 and 10 (inclusive)\n");
    } inner_ok = false;

    while (!inner_ok)
    {
        printf("Mark for maths: ");
        student.mark_maths = safeReadInt(&inner_ok);
        if (!inner_ok || student.mark_maths < 0 || student.mark_maths > 10)
            printf("Please, input a value between 0 and 10 (inclusive)\n");
    } inner_ok = false;

    while (!inner_ok)
    {
        printf("Mark for chemistry: ");
        student.mark_chemistry = safeReadInt(&inner_ok);
        if (!inner_ok || student.mark_chemistry < 0 || student.mark_chemistry > 10)
            printf("Please, input a value between 0 and 10 (inclusive)\n");
    } inner_ok = false;

    while (!inner_ok)
    {
        printf("Mark for informatics: ");
        student.mark_informatics = safeReadInt(&inner_ok);
        if (!inner_ok || student.mark_informatics < 0 || student.mark_informatics > 10)
            printf("Please, input a value between 0 and 10 (inclusive)\n");
    } inner_ok = false;

    Student::updateAverage(student);
}

void printStudent(Student student)
{
    fprintStudent(student, stdout);
}

void fprintStudent(Student student, FILE* stream)
{
    fprintf(stream, "Name: %s %s\n", student.surname, student.initials);
    fprintf(stream, "Marks:\n");
    fprintf(stream, "\tPhysics:     %d\n", student.mark_physics);
    fprintf(stream, "\tMaths:       %d\n", student.mark_maths);
    fprintf(stream, "\tChemistry:   %d\n", student.mark_chemistry);
    fprintf(stream, "\tInformatics: %d\n\n", student.mark_informatics);
    fprintf(stream, "\tAverage:     %f\n", student.average_mark);
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
