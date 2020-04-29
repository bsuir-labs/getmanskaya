#define _CRT_SECURE_NO_WARNINGS 1

// Дефайн выше для того, чтобы под виндой работали функции scanf вместо scanf_s и т.д.

#include <iostream>
#include <cstring>
#include <climits>
#include <assert.h>
#include <stdio.h>

using namespace std;

// Константами зададим максимальную длину для фамилии и инициалов (с запасом)
const unsigned int SURNAME_LEN = 50;
const unsigned int INITIALS_LEN = 5;

// А также имена файлов для ввода и вывода
const char DATABASE_FILENAME[] = "students.dat";
const char OUTPUT_FILENAME[] = "output.txt";

// Описание структуры с информацией о студенте
struct Student
{
    /// Фамилия
    char surname[SURNAME_LEN];
    /// Инициалы
    char initials[INITIALS_LEN];

    /// Год рождения
    unsigned short birth_year;

    /// Оценки по предметам
    unsigned short mark_physics;
    unsigned short mark_maths;
    unsigned short mark_informatics;
    unsigned short mark_chemistry;

    /// Средняя оценка
    double average_mark;
};

// Функции для работы со структурой

/// \brief Функция для чтения структуры
/// \param student - ссылка на структуру, в которую запишутся данные
void readStudent(Student& student);

/// \brief Функция для вывода структуры в консоль
void printStudent(Student student);

/// \brief Функция для вывода структуры в произвольный поток вывода
/// (например, в файл)
void fprintStudent(Student student, FILE* stream);

/// \brief Функция для нахождения максимального числа
int max(int a, int b);


// Дальше идут функции для безопасного ввода данных
// Они также используются и в последующих лабах, подробное описание будет тут,
// а в остальных лабах буду ссылаться на этот код

/// Функция для безопасного чтения числа с заданным диапазоном
/// \param minimal - Минимальное число, которое будет принято
/// \param maximal - Максимальное число, которое будет принято
/// \param prompt  - Строка с предложением о вводе, будет выводится в консоли
/// перед чтением числа
///
/// Например, нужно прочитать оценку по какому-то предмету
/// Оценка может быть в диапазоне от 0 до 10.
/// Тогда можно вызвать эту функцию вот так:
/// 
/// int mark = rangeReadInt(0, 10, "Please, input mark: ");
int rangeReadInt(int minimal, int maximal, const char* prompt);

/// Функция для чтения строки определённого размера
/// В неё передаётся буфер, куда читать строку, и размер этого буфера
/// Возвращает размер прочитанной строки.
int safeReadString(char* buffer, unsigned maxLength);

/// Функция для чтения одного символа
/// Читает из консоли один символ и очищает буфер ввода
char safeGetChar();

/// Вспомогательная функция для очистки буфера ввода
/// Т.е., если нам нужно прочитать один символ, а пользователь ввёл 10,
/// то после чтения в буфере ввода останется ещё 9 символов (и перенос строки,
/// скорее всего)
void flush_stdin();


// Дальше идут функции по этой лабе

/// Функция, которая выводит меню и возвращает номер выбранной опции
/// Аналогичная используется и в остальных лабах
int getMainMenuChoice();


/// Функции для опций меню
void createNewRecord(); // 1 - Создание новой записи
void showAllRecords();  // 2 - Показать все записи
void correctRecord();   // 3 - Исправление существующей записи
void individualTask();  // 4 - Индивидуальное задание
void goodbyeMessage();  // 5 - Выход



// Функции для работы с файлами


/// Функция для создания файла
/// В качестве параметра принимает имя нового файла
void createFile(const char filename[]);

/// Функция для удаления файла
void removeFile(const char filename[]);

/// Функция для добавления информации в конец файла
/// \param filename - строка с именем файла, куда нужно дописать данные
/// \param data     - указатель на данные, которые нужно дописать
/// \param size     - размер данных в байтах
///
/// Например, если нужно дописать в файл одну структуру про студента, это 
/// можно сделать так:
///
/// Student info;   // структура, которую будем дописывать
///
/// appendToFile("filename", (char*) &info, sizeof(info));
///
/// Функция универсальна и записывает любые данные, поэтому перед записью нужно
/// указатель на данные привести к указателю на char.
void appendToFile(const char filename[], const char* data, unsigned size);

/// Функция для записи информации в файл (если там уже что-то есть, то оно
/// заменяется на новые данные)
/// Параметры аналогичны тем, что в функции appendToFile
void writeToFile(const char filename[], const char* data, unsigned size);

/// Функция для чтения информации з файла в буфер
/// \param filename - имя файла, откуда будем читать
/// \param buffer   - указатель на указатель на буфер, куда будем читать.
/// Указатель на указатель нужен для того, чтобы выделить память под данные
/// \param maxSize  - максимальное количество байт, которые можно прочитать
/// Если этот параметр равен нулю, то читается без ограничений. По умолчанию 
/// имеет значение 0.
/// \return unsigned количество байт, которе было прочитано из файла
unsigned readFile(const char filename[], char** buffer, unsigned maxSize = 0);

/// Функция, возвращающая размер файла в байтах
unsigned filelength(FILE* file);


/// Главная функция
int main()
{
    // Переменная для красивого завершения программы
    // Главный цикл будет выполнятся, пока эта переменная
    // равна "false", то есть "пока не было запроса на остановку"
    bool stopRequested = false;

    // Создаём файл для вывода
    createFile(OUTPUT_FILENAME);

    // Главный цикл
    while (!stopRequested)
    {
        // Запрашиваем у пользователя выбор
        switch (getMainMenuChoice())
        {
            case 1: createNewRecord(); break;       // и вызываем функции согласно его выбору
            case 2: showAllRecords(); break;
            case 3: correctRecord(); break;
            case 4: individualTask(); break;
            case 5:
                stopRequested = true;               // Если пользователь захотел выйти, то помечаем в переменной его желание
                goodbyeMessage();                   // И выводим прощальное сообщение
                break;
            default: printf("Undefined behavior. Something wrong happened.\n");
        }

        getc(stdin);                                // Функция задержки обновления экрана, 
                                                    // после выполнения действий нужно будет подтвердить
                                                    // продолжение нажатием кнопки Enter
    }
    return 0;
}

// Функция для чтения числа
int rangeReadInt(int minimal, int maximal, const char* prompt)
{
    bool ok = false;        // Если эта переменная станет "тру", значит мы прочитали всё хорошо
    int result;
    do
    {
        printf("%s", prompt);       // Выводим пригласительное сообщение
        ok = scanf("%d", &result) == 1;     // Читаем число
        // сканф возвращает количество переменных, которые он смог прочитать.
        // Если нам ввели не число, то он не сможет его прочесть и вернёт 0.
        // Тогда выражение scanf("%d", &result) == 1 будет равно `false`, что мы и положим 
        // в переменную ok. Если введут всё верно, то выражение будет равно "тру" и ок тоже будет равно тру
        
        // Теперь проверяем, что число находится в нужном диапазоне
        // и кладём результат проверки в тот же "ок"
        ok = ok && result >= minimal && result <= maximal; 

        flush_stdin();  // Очищаем то, что осталось в буфере ввода (там по-любому остался как минимум символ '\n')
        if (!ok)        // Если мы в итоге ничего не прочитали, то выводим сообщение об ошибке
            printf("Please, input a value between %d and %d (inclusive)\n", minimal, maximal);
    } while (!ok);      // Делаем так до тех пор, пока наконец не прочитаем что-нибудь
    return result;      // И возвращаем число
}

// Чтение строки
int safeReadString(char* buffer, unsigned maxLength)
{
    fgets(buffer, maxLength, stdin);        // Читаем строку обычным fgets'ом
    
    // Но fgets читает также и перенос строки на конце, который нам не нужен
    int size = strlen(buffer);

    // Поэтому пока у нас в конце строки находится символ переноса, мы будем его
    // заменять на "нуль-терминатор", т.е. на символ окончания строки
    while (size > 1 && buffer[size - 1] == '\n') buffer[size-- - 1] = '\0';
    return size;    // Вернём получившийся размер строки
}

// Чтение одного символа
// По большой части, аналогична функции чтения числа,
// только без проверок на диапазон
char safeGetChar()
{
    char c;
    bool ok;
    do {
        ok = scanf("%c", &c) == 1;
        flush_stdin();
    } while (!ok);
    return c;
}

// Функция очистки буфера ввода
void flush_stdin()
{
    char c;
    // просто читаем символ из буфера, пока не дойдём до конца строки ('\n')
    // или символа конца файла (EOF, End Of File)
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

// Функция получения выбора из меню
int getMainMenuChoice()
{
    int choice = 0;     // Выбор пользователя
    int point = 0;      // Вспомогательная переменная, чтоб можно было быстро
                        // добавлять и убирать пункты из меню

    // Выводим меню
    printf("*** MAIN MENU ***\n\n");
    printf("Number | Action\n");
    printf("---------------\n");
    printf("%6d | Create new record\n", ++point);
    printf("%6d | Show all records\n", ++point);
    printf("%6d | Correct record\n", ++point);
    printf("%6d | Individual task\n", ++point);
    printf("%6d | Quit\n", ++point);

    // И читаем выбор пользователя
    choice = rangeReadInt(1, point, "Your choice > ");
    return choice;
}

// Функция создания новой записи
void createNewRecord()
{
    printf("*** Creating new record ***\n");

    Student record;         // Создаём запись
    readStudent(record);    // Читаем её

    // и записываем в файл
    appendToFile(DATABASE_FILENAME, (char*)&record, sizeof(record));
}

// Функция для просмотра всех записей
void showAllRecords()
{
    Student* students = nullptr;    // Тут будет лежать массив со всеми записями из файла
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&students); // читаем файл в этот массив
    unsigned size = bytes / sizeof(Student);    // Функция чтения нам вернула количество байт, так что
                                                // нужно теперь поделить его на количество байт, которое
                                                // занимает одна структура Student, чтобы узнать, сколько
                                                // таких структур мы прочитали

    // Пробуем открыть файл вывода, чтоб записать вывод туда (логично)
    FILE* output = fopen(OUTPUT_FILENAME, "a");
    if (output)     // Если получилось открыть
    {               // то выводим туда по очереди каждую структуру
        for (unsigned i = 0; i < size; ++i)
            fprintStudent(students[i], output);
        fclose(output); // и закрываем файл
    }
    else    // Иначе, если файл не открылся (мало ли, с диском проблемы), ругнёмся в консоль
    {
        printf("Couldn't open %s file for writing (appending)\n", OUTPUT_FILENAME);
    }

    for (unsigned i = 0; i < size; ++i) // А также выведем каждую структуру в консоль
        printStudent(students[i]);

    delete[] students;  // не забудем удалить массив с записями
}

// Функция для корректировки одной записи
void correctRecord()
{
    // Читаем все записи из файла, как в showAllRecords
    Student* students = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&students);
    unsigned size = bytes / sizeof(Student);

    // Выводим в консоль имена студентов с номерами, чтобы пользователь выбрал,
    // кого будем редактировать
    for (unsigned i = 0; i < size; ++i)
        printf("%3d:\t%s %s\n", i, students[i].surname, students[i].initials);

    // Читаем его выбор
    int numberToCorrect = rangeReadInt(0, size, "Specify number to correct: ");

    // Выводим данные про выбранного студента
    printStudent(students[numberToCorrect]);
    printf("Specify new values:\n");
    // И читаем новые данные
    readStudent(students[numberToCorrect]);

    // Записываем новые данные в базу данных (файлик)
    writeToFile(DATABASE_FILENAME, (char*)students, size * sizeof(Student));

    delete[] students;  // удаляем массив
}

// Индивидуальное задание
void individualTask()
{
    // Пытаемся открыть файл для вывода
    FILE* output = fopen(OUTPUT_FILENAME, "a");
    if (!output) printf("Couldn't open %s for writing\n", OUTPUT_FILENAME); // если не вышло, ругаемся в консоль

    printf("*** INDIVIDUAL TASK ***\n");
    printf("\nSpecify the letter you want to start with: ");

    char letter = safeGetChar();    // читаем букву, на которую должны начинаться фамилии студентов

    printf("Filtering students according to rule:\n");
    printf("Average mark is larger than 8 and the surname starts with %c\n", letter);

    if (output)     // если файлик тогда получилось открыть, то продублируем вывод и в него
    {
        fprintf(output, "*** INDIVIDUAL TASK ***\n");
        fprintf(output, "Filtering students according to rule:\n");
        fprintf(output, "Average mark is larger than 8 and the surname starts with %c\n", letter);
    }

    // Выполняем задание
    // Сначала читаем весь файл, как и раньше
    Student* students = nullptr;
    unsigned bytes = readFile(DATABASE_FILENAME, (char**)&students);
    unsigned size = bytes / sizeof(Student);

    bool found = false; // Флаг, что мы нашли хотя бы одного студента по заданным фильтрам
    for (unsigned i = 0; i < size; ++i)     // проходимся по массиву
        if (students[i].surname[0] == letter && students[i].average_mark > 8)   // если удовлетворяет условиям
        {
            printStudent(students[i]);                      // выводим его в консоль
            if (output) fprintStudent(students[i], output); // и если файлик открыт, то и в файлик
            found = true;                                   // и поднимаем флаг, что как минимум одного мы уже нашли
        }

    if (!found) // Если никого не нашли - сообщаем об этом в консоль и файл
    {
        printf("No users found.\n");
        if (output) fprintf(output, "No users found.\n");
    }

    if (output) fclose(output); // закрываем файл
    delete[] students;  // удаляем массив
}

// прощальное сообщение
void goodbyeMessage()
{
    printf("Goodbye! Have a nice day!\n");
    printf("Press Enter key to continue.\n");
}

// Функция чтения информации про студента
void readStudent(Student& student)
{
    printf("*** reading student info ***\n\n");

    printf("Surname: ");
    safeReadString(student.surname, SURNAME_LEN);
    printf("Initials: ");
    safeReadString(student.initials, INITIALS_LEN);

    student.birth_year = rangeReadInt(1990, 2020, "Birth year: ");
    student.mark_physics = rangeReadInt(0, 10, "Mark for physics: ");
    student.mark_maths = rangeReadInt(0, 10, "Mark for maths: ");
    student.mark_chemistry = rangeReadInt(0, 10, "Mark for chemistry: ");
    student.mark_informatics = rangeReadInt(0, 10, "Mark for informatics: ");

    student.average_mark = (student.mark_maths + student.mark_physics +
        student.mark_chemistry + student.mark_informatics) / 4.0;
}

// Вывод информации про студента в консоль
// Консоль это у нас stdout, а это такой же поток, как и FILE*
// Так что мы вызовем функцию вывода в файл, но передадим ей вместо
// файла нашу консоль
void printStudent(Student student)
{
    fprintStudent(student, stdout);
}

// Функция вывода в произвольный поток
void fprintStudent(Student student, FILE* stream)
{
    fprintf(stream, "Name:      \t%s %s\n", student.surname, student.initials);
    fprintf(stream, "Birth year:\t%d\n", student.birth_year);
    fprintf(stream, "Marks:\n");
    fprintf(stream, "\tPhysics:     %d\n", student.mark_physics);
    fprintf(stream, "\tMaths:       %d\n", student.mark_maths);
    fprintf(stream, "\tChemistry:   %d\n", student.mark_chemistry);
    fprintf(stream, "\tInformatics: %d\n\n", student.mark_informatics);
    fprintf(stream, "\tAverage:     %f\n", student.average_mark);
    fprintf(stream, "\n");
}

// Максимальный элемент
int max(int a, int b)
{
    if (a > b) return a;
    return b;
}

// Функция создания нового файла
void createFile(const char filename[])
{
    FILE* file = fopen(filename, "wb"); // пытаемся открыть
    if (file == nullptr)    // если не получилось, то ругаемся
        fprintf(stderr, "Can't create file %s. Error.\n", filename);
    else
    {
        fclose(file);   // а иначе - закрываем обратно, всё создали
        printf("File %s has been created.\n", filename);
    }
}

// Функция удаления файла
void removeFile(const char filename[])
{
    if (remove(filename) != 0)  // Пытаемся удалить. Если не вышло, ругаемся
        fprintf(stderr, "Can't remove file %s. Error\n", filename);
    else
        printf("Removed file successfully!\n"); // Иначе хвалимся
}

// Функция дописывания в конец файла
void appendToFile(const char filename[], const char* data, unsigned size)
{
    // Открываем файл
    FILE* file = fopen(filename, "ab");
    if (file)   // если открылся
    {
        fwrite(data, 1, size, file);    // записываем туда данные
        fclose(file);                   // закрываем файл
        printf("%d bytes appended to file %s.\n", size, filename);  // сообщаем что всё ок
    }
    else
    {   // Иначе сообщаем об ошибке
        fprintf(stderr, "Can't write to file %s!\n", filename);
    }
}

// Запись в файл
// То же самое, что и дописывание, отличается только
// открытие файла (с опцией "w" вместо "а" (write вместо append))
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

// Чтение данных из файла
unsigned readFile(const char filename[], char** buffer, unsigned maxSize)
{
    // Открываем файл для чтения
    FILE* file = fopen(filename, "rb");
    unsigned read = 0;  // количество прочитанных байт
    if (file)
    {
        unsigned length = filelength(file); // считаем размер файла
        if (maxSize) length = max(length, maxSize); // если нам задали ограничение по размеру прочитанного,
                                                    // то будем следовать ему
        *buffer = new char[length];     // выделяем память под данные, которые будем читать
        read = fread(*buffer, 1, length, file); // читаем данные
        if (ferror(file) != 0)  // если случилась ошибка, сообщим об этом в консоль
            fprintf(stderr, "Some error occurred while reading");
        fclose(file);   // и закроем файл
    }
    else    // а если файл не получилось открыть, то тоже поругаемся в консоль
        fprintf(stderr, "Can't open file %s for reading\n", filename);
    return read;    // возвращаем количество прочитанных байт
}

// считаем длину файла в байтах
unsigned filelength(FILE* file)
{
    unsigned position = ftell(file);    // запоминаем, где стоял курсор в файле сначала
    fseek(file, 0, SEEK_END);           // двигаем его в конец
    unsigned length = ftell(file);      // получаем его смещение в байтах (т.к. он в конце, то это и будет размер)
    fseek(file, position, SEEK_SET);    // двигаем курсор обратно, где стоял сначала
    return length;                      // возвращаем длину
}
