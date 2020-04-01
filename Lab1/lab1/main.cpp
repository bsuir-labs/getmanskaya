#include <iostream>
#include <cstring>
#include <climits>
#include <assert.h>

using namespace std;

const unsigned int SURNAME_LEN = 50;
const unsigned int INITIALS_LEN = 3;

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

int safeReadInt(bool *ok = nullptr);
int getChoice(int minimal, int maximal);

// Menu choice functions
int getMainMenuChoice();

// Main menu choices
void createNewRecord(); // 1 - create new record
void showAllRecords();  // 2 - show all records
void correctRecord();   // 3 - correct record
void individualTask();  // 4 - individual task
void loadFile();        // 5 - load data from file
void saveToFile();      // 6 - save data to file
void goodbyeMessage();  // 7 - Quit

// Temp debug functions
void unimplemented();

int main()
{
    bool stopRequested = false;
    while (!stopRequested)
    {
        switch (getMainMenuChoice())
        {
        case 1: createNewRecord(); break;
        case 2: showAllRecords(); break;
        case 3: correctRecord(); break;
        case 4: individualTask(); break;
        case 5: loadFile(); break;
        case 6: saveToFile(); break;
        case 7:
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
    printf("%6d | Load file\n", ++point);
    printf("%6d | Save to file\n", ++point);
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
    unimplemented();
}

void showAllRecords()
{
    unimplemented();
}

void correctRecord()
{
    unimplemented();
}

void individualTask()
{
    unimplemented();
}

void loadFile()
{
    unimplemented();
}

void saveToFile()
{
    unimplemented();
}

void goodbyeMessage()
{
    printf("Goodbye! Have a nice day!\n");
    printf("Press Enter key to continue.\n");
}
