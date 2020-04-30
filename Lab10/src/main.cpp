#include <fstream>
#include <vector>
#include <string>

using namespace std;

const unsigned int kTestCasesNumber = 6;

enum class GraphType
{
    Common,
    Functional,
    CounterFunctional
};

GraphType getType(const vector<vector<int>> &graph);

int main()
{
    ifstream fin;
    ofstream fout;

    for (unsigned test = 1; test <= kTestCasesNumber; ++test)
    {
        fin.open("test-in-" + std::to_string(test) + ".txt");
        fout.open("test-out-" + std::to_string(test) + ".txt");

        int nodesCnt, edgesCnt;
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

        switch (getType(graph)) {
            case GraphType::Common: output = "common"; break;
            case GraphType::Functional: output = "functional"; break;
            case GraphType::CounterFunctional: output = "counter-functional"; break;
            default: output = "undefined";
        }

        fout << output << endl;

        fout.close();
        fin.close();
    }
    return 0;
}

GraphType getType(const vector<vector<int>> &graph)
{
    unsigned functionalNodes = 0;

    for (size_t i = 0; i < graph.size(); ++i)
        functionalNodes += graph[i].size() == 1;

    if (functionalNodes == graph.size())
        return GraphType::Functional;
    if (functionalNodes == 0)
        return GraphType::CounterFunctional;
    return GraphType::Common;
}
