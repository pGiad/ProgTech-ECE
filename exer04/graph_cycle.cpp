#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
    public:
    Graph(int V) : array(new list<int>[V]), vertices(V) {}
    
    ~Graph() {
        vertices=0;
        array=nullptr;
        delete array;
    }
    
    void addEdge(int u, int v) { array[u].push_back(v); }

    enum state { unvisited, seen, visited };
  
    bool cycle(vector<int> &path) const {
        vector<state> status(vertices);
        vector<int> assistant;
        for(int i=0; i<vertices; ++i) status[i]=unvisited;
        for(int i=0; i<vertices; ++i)
            if(cycle_help(i, status, assistant, path)) return true;
        return false;
    }

    private:
    list<int> *array;
    int vertices;

    bool cycle_help(int v, vector<state> &status, vector<int> &assistant, vector<int> &path) const {
        status[v]=seen;
        assistant.push_back(v);
        list<int>::iterator i;
        for(i=array[v].begin(); i!=array[v].end(); ++i) {
            if(status[*i]==seen) {
                int x=0;
                while(assistant[x]!=*i) { assistant[x]=0; ++x; }
                while(x<assistant.size()) { path.push_back(assistant[x]); ++x; }
                return true;
            }
            if(status[*i]==unvisited && cycle_help(*i, status, assistant, path)) return true;
        }
        status[v]=visited;
        if(!assistant.empty()) assistant.pop_back();
        return false;
    }
};
/*
int main() {
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for(int i=0; i<E; ++i) { int u, v; cin >> u >> v; g.addEdge(u, v); }
    vector<int> path;
    bool c=g.cycle(path);
    if(c) {
        cout << "CYCLE: ";
        for(int i=0; i<path.size(); ++i) cout << path[i] << (i==path.size()-1 ? "\n" : " ");
    }
    else cout << "NO CYCLE" << endl;
}*/