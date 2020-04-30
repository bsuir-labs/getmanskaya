#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

/// Количество тестовых заданий
const unsigned int kTestCasesNumber = 7;

// Возможные варианты графа
// (надеюсь, я правильно понял всё)
enum class GraphType
{
    Common,                 // Обычный
    Functional,             // Функциональный
    CounterFunctional       // Контрфункциональный
};

/// \brief Функция для получения типа графа
/// \param graph - список смежности для графа
/// \return Тип графа
GraphType getType(const vector<vector<int>> &graph);

int main()
{
    ifstream fin;   // ввод и вывод из файлов
    ofstream fout;

    for (unsigned test = 1; test <= kTestCasesNumber; ++test)
    {
        fin.open("test-in-" + std::to_string(test) + ".txt");
        fout.open("test-out-" + std::to_string(test) + ".txt");

        if (!fin.is_open() || !fout.is_open())  // Защита от ошибок на случай, если вдруг файл не смогли открыть
        {
            std::cout << "Can't open files for test #" << test << std::endl;
            continue;
        }

        vector<vector<int>> graph;      // Тут будет хранится граф
        bool broken = false;            // Это флаг о том, что текущий тестовый файл с ошибкой
                                        // Нужен, т.к. мы можем узнать про ошибку в процессе чтения файла
                                        // и если так, то нам придётся пропустить весь тест.

        int a, b;
        fin >> a >> b;                  // Пробуем прочесть первое ребро из файла
        while (!fin.eof())              // И будем это делать до тех пор, пока не дойдём до конца файла (eof - End of file)
        {
            if (a < 1 || b < 1)         // Если ребро неверное, то придётся тест пропустить
            {
                cout << "Test #" << test << " ";    // Сообщаем об этом в консоль
                cout << "Node number should be a positive number" << endl;
                broken = true;      // И поднимаем флаг, что тест ошибочный
                break;              // И выходим из этого цикла, дальше тест читать смысла нету
            }

            if (graph.size() < max(a, b))   // Поправляем размер графа на ходу, т.е. если вдруг нам впервые встретилась
                graph.resize(max(a, b));    // вершина с номером 9, то мы считаем, что тут как минимум 9 вершин есть

            --a, --b;
            graph[a].push_back(b);          // Сохраняем прочитанную информацию

            fin >> a >> b;                  // И пытаемся прочесть следующее ребро
        }

        if (broken)                     // Если вдруг наткнулись на ошибку
        {
            fin.close();                // Закрываем файлы
            fout.close();
            continue;                   // И пропускаем этот тест
        }

        std::string output;             // Сюда запишем ответ

        switch (getType(graph)) {       // Спрашиваем у функции тип графа
        case GraphType::Common:             output = "common"; break;               // и в зависимости от полученного значения
        case GraphType::Functional:         output = "functional"; break;           // записываем ответ в переменную
        case GraphType::CounterFunctional:  output = "counter-functional"; break;
        default: output = "undefined";
        }

        fout << output << endl; // Выводим ответ в файл

        fout.close();   // закрываем файлы
        fin.close();
    }
    return 0;
}

// Находим тип графа
GraphType getType(const vector<vector<int>> &graph)
{
    unsigned functionalNodes = 0;   // Считаем, сколько вершин имеют только одно исходящее ребро

    for (size_t i = 0; i < graph.size(); ++i)
        functionalNodes += graph[i].size() == 1;

    if (functionalNodes == graph.size() && functionalNodes > 0) // Если граф не пустой и у него все вершины имеют только 1 исходящее ребро
        return GraphType::Functional;                           // то и граф у нас функциональный
    if (functionalNodes == 0)                                   // А если нету ни одной такой вершины
        return GraphType::CounterFunctional;                    // то контрфункциональный
    return GraphType::Common;               // А иначе, ни тот, ни другой
}
