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

        if (!fin.is_open() || !fout.is_open())
        {
            std::cout << "Can't open files for test #" << test << std::endl;
            continue;
        }

        vector<vector<int>> graph;
        bool broken = false;

        int a, b;
        fin >> a >> b;
        while (!fin.eof())
        {
            if (a < 1 || b < 1)
            {
                cout << "Test #" << test << " ";
                cout << "Node number should be a positive number" << endl;
                broken = true;
                break;
            }

            if (graph.size() < max(a, b))
                graph.resize(max(a, b));

            --a, --b;
            graph[a].push_back(b);

            fin >> a >> b;
        }

        if (broken)
        {
            fin.close();
            fout.close();
            continue;
        }

        std::string output;

        switch (getType(graph)) {
        case GraphType::Common: output = "common"; break;
        case GraphType::Functional: output = "functional"; break;
        case GraphType::CounterFunctional: output = "counter-functional"; break;
        default: output = "undefined";
        }

        fout << output << endl; // Выводим ответ в файл

        fout.close();
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

    if (functionalNodes == graph.size() && functionalNodes > 0)
        return GraphType::Functional;
    if (functionalNodes == 0)
        return GraphType::CounterFunctional;
    return GraphType::Common;               // А иначе, ни тот, ни другой
}
