#include <fstream>
#include <vector>

using namespace std;

/// Количество тестовых заданий
const unsigned int kTestCasesNumber = 6;

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

        int nodesCnt, edgesCnt;                 // Читаем тестовые данные из файла
        fin >> nodesCnt >> edgesCnt;
        vector<vector<int>> graph(nodesCnt);

        for (int i = 0; i < edgesCnt; ++i)
        {
            int a, b;
            fin >> a >> b;
            --a, --b;
            graph[a].push_back(b);
        }

        std::string output;

        switch (getType(graph)) {               // Получаем тип графа и в зависимости от него генерируем ответ
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

    if (functionalNodes == graph.size())    // Если все вершины имеют ровно 1 исходящее ребро,
        return GraphType::Functional;       // то граф функциональный
    if (functionalNodes == 0)               // Если ни одной, то контр-функциональный
        return GraphType::CounterFunctional;
    return GraphType::Common;               // А иначе, ни тот, ни другой
}
