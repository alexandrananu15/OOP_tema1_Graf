#include <iostream>
#include "Graf.h"
#include <cassert>

using namespace std; 

void grafTests()
{
    Graf g(6);              //Graf Test 1
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(2, 4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    cout << g << endl;

    Graf f(5);              //Graf Test 2
    f.addEdge(0, 1);
    f.addEdge(0, 2);
    f.addEdge(1, 3);
    f.addEdge(2, 4);
    cout << f << endl;

    Graf h;                 //Graf Test 3
    h = g;
    h.addEdge(1, 4);
    
    //test assert DFS
    int v[] = { 1, 3, 4, 2, 0 };
    int* a = g.dfs(1);
    int index = 0;
    while (a[index] != -1)
    {
        assert(a[index] == v[index]);
        index++;
    }

    //test assert BFS
    int w[] = { 1, 3, 0, 2, 4 };
    int* b = g.bfs(1);
    index = 0;
    while (b[index] != -1)
    {
        assert(b[index] == w[index]);
        index++;
    }
    
    //test assert distanta dintre 2 noduri
    assert(g.distance(2, 3) == 2);
    assert(g.distance(2, 2) == 0);
    assert(g.distance(2, 5) == (int)1e9);       //initializam cu infinit daca nu exista muchie intre cele 2 noduri

    //test assert operatorul []
    int x[] = { 0, 4, 1 };
    int* c = g[2];
    index = 0;
    while (c[index] != -1)
    {
        assert(c[index] == x[index]);
        index++;
    }

    //test assert operatorul <
    assert(f < g);
    assert(f < h);

    //test assert operatorul >
    assert(g > f);
    assert(h > g);

    //test assert "este arbore?"
    assert(f.isTree());
    assert(!g.isTree());

    //test assert numar de componente conexe
    assert(f.cntConexe() == 1);
    assert(g.cntConexe() == 2);
    assert(h.cntConexe() == 2);

    //test assert numar de noduri 
    assert(g.getNodeCount() == 6);
    assert(h.getNodeCount() == 6);
    assert(f.getNodeCount() == 5);

    //test assert numar de muchii
    assert(g.getEdgeCount() == 6);
    assert(h.getEdgeCount() == 7);
    assert(f.getEdgeCount() == 4);

    //test adaugarea aceleasi muchii
    try
    {
        g.addEdge(1, 2);
        assert(false);
    }
    catch (const char* e)
    {
        if (e == "Muchia exista deja")
            assert(true);
        else
            assert(false);
    }

    //test adaugarea unei muchii dintr-un nod in acelasi nod
    try
    {
        g.addEdge(2, 2);
        assert(false);
    }
    catch (const char* e)
    {
        if (e == "Nu exista muchie dintr-un nod in acelasi nod")
            assert(true);
        else
            assert(false);
    }
}

int main()
{
    grafTests();
    cout << "Toate testele au trecut";
}

