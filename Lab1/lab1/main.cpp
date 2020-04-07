#include <iostream>
#include <cstring>
#include <climits>
#include <assert.h>

using namespace std;

const unsigned int SURNAME_LEN = 50;
const unsigned int INITIALS_LEN = 3;

// Struct of student and functions for work with this structure
struct Student;
void readStudent(Student &student);
void printStudent(Student student);

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

void readStudent(Student &student)                      // TODO: refactor
{
    printf("*** reading student info ***\n\n");

    printf("Surname: "); scanf("%s", student.surname);  // TODO: maybe change to safe scanfs
    printf("Initials: "); scanf("%s", student.initials);

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
    printf("Name: %s %s\n", student.surname, student.initials);
    printf("Marks:\n");
    printf("\tPhysics:     %d\n", student.mark_physics);
    printf("\tMaths:       %d\n", student.mark_maths);
    printf("\tChemistry:   %d\n", student.mark_chemistry);
    printf("\tInformatics: %d\n\n", student.mark_informatics);
    printf("\tAverage:     %f\n", student.average_mark);
}
