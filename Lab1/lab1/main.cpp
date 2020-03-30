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

int safeReadInt(bool* ok = nullptr)
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

    printf("*** MAIN MENU ***\n\n");
    printf("Number | Action\n");
    printf("---------------\n");
    printf("%6d | Hello!\n", 1);
    printf("%6d | World!\n", 2);

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

        if (choice < 1 || choice > 2)
        {
            ok = false;
            printf("[ERROR] No such index in menu. Please, correct your input.\n");
        }
    }
    return choice;
}

int main()
{
    getMainMenuChoice();
    return 0;
}
