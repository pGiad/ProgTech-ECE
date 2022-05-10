#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph
{
public:
    Graph(int V) : array(new list<int>[V]), vertices(V) {}
    ~Graph() { delete[] array; }

    void addedge(int u, int v)
    {
        array[u].push_back(v);
        array[v].push_back(u);
    }

    int Eulerian()
    {
        int odd = 0;
        for (int i = 0; i < vertices; ++i)
            if (array[i].size() % 2 == 1)
            {
                path.push_back(i);
                odd++;
            }
        if (odd > 2)
            return 0;
        return (odd) ? 1 : 2;
    }

    void printPath()
    {
        for (unsigned int i = 0; i < path.size() / 2; ++i)
            cout << " " << path[i];
    }

private:
    int vertices;
    list<int> *array;
    vector<int> path;
};

int main()
{
    int N, M, u, v;
    cin >> N >> M;
    Graph g(N);
    for (int i = 0; i < M; ++i)
    {
        cin >> u >> v;
        g.addedge(u, v);
    }
    if (g.Eulerian() == 0)
        cout << "IMPOSSIBLE" << endl;
    else if (g.Eulerian() == 1)
    {
        cout << "PATH";
        g.printPath();
        cout << endl;
    }
    else
        cout << "CYCLE" << endl;
}