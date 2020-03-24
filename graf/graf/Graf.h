#ifndef _GRAF_H
#define _GRAF_H

#include "List.h"

class Graf
{
	int nodeCount;
	int edgeCount;
	List** graf;								//pointer catre un pointre de tip lista
	static const int infinit = (int)1e9;		//infinit
	void dfs(int, bool*, int*, int&) const;		//functie de ajutor ptr dfs-ul public
	void dfs(int, bool*) const;					//functie de ajutor ptr cntConexe
	bool existsEdge(int, int);					//verifica daca o muchie se afla in graf
public:
	Graf();													//constrcutor fara parametri
	Graf(int);												//constructor cu un parametru
	Graf(const Graf&);										//copyconstructor
	~Graf();												//destructor
	int* dfs(int) const;									//parcurgere in adancime
	int* bfs(int) const;									//parcurgere in latime
	int distance(int, int) const;							//returneaza distanta dintre 2 noduri
	int cntConexe() const;									//returneaza nr de componente conexe
	bool isTree() const;									//returneaza True daca graful este arbore, False altfel
	List** getGraf() const;									//returneaza graful
	int getNodeCount() const;								//returneaza numarul de noduri
	int getEdgeCount() const;								//returneaza numarul de muchii
	bool operator<(Graf&) const;							//supraincarcarea operatorului <
	bool operator>(Graf&) const;							//supraincarcarea operatorului >
	void addEdge(int, int);									//adauga o muchie la graf
	int* operator[](int) const;								//supraincarcarea operatorului []
	Graf& operator=(const Graf&);							//supraincarcarea operatorului =
	friend std::istream& operator>>(std::istream&, Graf&);				//supraincarcarea operatorului >>
	friend std::ostream& operator<<(std::ostream&, Graf&);				//supraincarcarea operatorului <<
};

#endif