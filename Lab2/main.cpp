#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>
#include <ctype.h>

using namespace std;

// Эти функции описаны в первой лабе, тут они аналогичные
int rangeReadInt(int minimal, int maximal, const char* prompt);
void flush_stdin();

/// \brief Рекурсивный поиск элемента в массиве
/// \param array - массив, где будем искать
/// \param left  - левая граница рассматриваемого диапазона
/// \param right - правая граница рассматриваемого диапазона
/// \param element - элемент, который мы ищем
///
/// Изначально рассматривается весь диапазон, который будет сужаться в процессе
/// поиска, так что вызывается эта функция как:
///
/// int result = recursiveFind(array, 0, size - 1, elementToFind);
int recursiveFind(const int* array, int left, int right, int element);

/// \brief Нерекурсивный поиск элемента в массиве
/// \param array - массив для поиска
/// \param size  - размер массива
/// \param element - элемент для поиска
int nonrecursiveFind(const int* array, unsigned size, int element);

/// \brief Генерация случайного массива заданного размера
void generateArray(int* array, unsigned size);

/// \brief Вывод массива в консоль
void printArray(int* array, unsigned size);

/// Функция, аналогичная такой же в первой лабе
int getMainMenuChoice();

/// Функции для опций меню
void menu_RecursiveImpl(const int* array, const unsigned size);
void menu_NonRecursiveImpl(const int* array, const unsigned size);

int main()
{
    const unsigned kSize = 20;          // размер массива
    int array[kSize];                   // создаём массив
    generateArray(array, kSize);        // генерируем значения

    bool stopRequested = false;     
    while (!stopRequested)
    {
        switch (getMainMenuChoice()) {
            case 1: generateArray(array, kSize); break;     // генерируем значения заново, если надо
            case 2: menu_RecursiveImpl(array, kSize); break;    // рекурсивно ищем элемент
            case 3: menu_NonRecursiveImpl(array, kSize); break; // нерекурсивно ищем
            case 4:
                stopRequested = true;                           // выходим
                printf("GoodBye! Have a nice day!\n");
                break;
            default: printf("Something went wrong.");
        }
        getc(stdin);
    }

    return 0;
}

// см. лабу 1
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

// см лабу 1
void flush_stdin()
{
    char c;
    while ((c = getc(stdin)) != '\n' && c != EOF);
}

// см. лабу 1
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

// Рекурсивный поиск
// Тот же бинарный поиск, только рекурсивно
int recursiveFind(const int* array, int left, int right, int element)
{
    if (left == right)          // Если границы диапазона сошлись в одном элементе
    {
        if (array[left] == element) // Проверяем, тот ли это элемент.
            return left;            // Если тот, то возвращаем его индекс
        else
            return -1;              // Иначе - минус единицу
    }
                                    // Если границы ещё не схлопнулись
    int mid = (left + right) / 2;   // Берём середину отрезка
    if (element > array[mid])       // Если искомый элемент больше, чем элемент в середине
        return recursiveFind(array, mid + 1, right, element);   // то продолжаем поиск в правой половине отрезка
    else
        return recursiveFind(array, left, mid, element);    // а иначе - в левой
}

// Нерекурсивный поиск
// Тот же бинарный поиск, только без рекурсии
int nonrecursiveFind(const int* array, unsigned size, int element)
{
    int left = 0, right = size - 1; // Задаём начальные границы отрезка
    while (left < right)                // Пока границы не сошлись в одном элементе
    {
        int mid = (left + right) / 2;   // ищем середину отрезка
        if (element > array[mid])       // если искомый элемент больше, чем элемент посередине
            left = mid + 1;             // Изменяем границы, чтобы продолжить поиск в правой части
        else
            right = mid;                // Иначе - в левой части
    }
    if (array[left] == element) return left;    // Если в итоге мы схлопнулись на нужном элементе, возвращаем его
    return -1;                          // Иначе минус единицу
}


// Генерация массива
void generateArray(int* array, unsigned size)
{
    srand(time(nullptr));   // рандомизируем
    for (unsigned i = 0; i < size; ++i) // идём по массиву
        array[i] = rand() % 50 - 20;    // и генерируем случайные числа

    std::sort(array, array + size);     // сортируем массив

    printf("Generated array:\n");
    printArray(array, size);            // Выводим массив на экран для проверки
}


// Вывод массива на экран
void printArray(int* array, unsigned size)
{
    for (unsigned i = 0; i < size; ++i)
        printf("%4d", array[i]);
    printf("\n");
}

// Опция меню для рекурсивного поиска
void menu_RecursiveImpl(const int* array, const unsigned size)
{
    // Запрашиваем элемент, который будем искать
    int elementToFind = rangeReadInt(-100, 100, "Specify element to find: ");
    // Ищем
    int result = recursiveFind(array, 0, size - 1, elementToFind);
    // Выводим ответ
    printf("\t\tRecursive result:     %d\n", result);
}

// Опция меню для нерекурсивного поиска
// То же самое, что и для рекурсивного
void menu_NonRecursiveImpl(const int* array, const unsigned size)
{
    int elementToFind = rangeReadInt(-100, 100, "Specify element to find: ");
    int result = nonrecursiveFind(array, size, elementToFind);
    printf("\t\tNon-recursive result: %d\n", result);
}
