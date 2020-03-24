#include "Graf.h"
#include <iostream>

Graf::Graf() : nodeCount(0), edgeCount(0), graf(NULL) {			//constructor fara parametri
}

Graf::Graf(int n) : nodeCount(n), edgeCount(0)					//constructor cu un parametru
{
	graf = new List*[n];
	for (int i = 0; i < n; i++)
		graf[i] = new List();
}

List** Graf::getGraf() const									
{
	return graf;												//returneaza graful
}

Graf::Graf(const Graf& gr) : nodeCount(gr.nodeCount), edgeCount(gr.edgeCount)		//copyconstructor
{
	graf = new List*[nodeCount];
	for (int i = 0; i < nodeCount; i++)
		*graf[i] = *gr.getGraf()[i];
}

int Graf::getNodeCount() const
{
	return nodeCount;								//returneaza nr de noduri
}

int Graf::getEdgeCount() const
{
	return edgeCount;								//returneaza nr de muchii
}

void Graf::dfs(int node, bool* viz, int* vector, int& index) const					//parcurgerea in adancime - functie auxiliara 
{
	viz[node] = true;																//nodul curent a fost vizitat
	vector[index++] = node;															//fiind vizitat, il adaugam in array-ul care va fi returnat la final
	for (Node* p = graf[node]->getStart(); p != NULL; p = p->getNext())				//parcurgerea vecinilor nodului
	{
		if (viz[p->getInfo()] == false)												//daca gasim un nod nevizitat, atunci se reia procesul pentru el
			dfs(p->getInfo(), viz, vector, index);
	}
}

int* Graf::dfs(int node) const								//parcurgerea in adancime
{
	int* vector = new int[nodeCount + 1];					//retinem elementele in ordinea parcurgerii; la final adaugam -1 ca sa marcam capatul
	bool* viz = new bool[nodeCount];						//vector unde vor fi marcate nodurile vizitate
	for (int i = 0; i < nodeCount; i++)
		viz[i] = false;										//vectorul de vizitati ia initial valoarea False (niciun element nu a fost inca vizitat)
	int index = 0;
	dfs(node, viz, vector, index);							//am creat o functie separata pentru a o putea apela recursiv
	vector[index] = -1;										//finalul il marcam cu -1 ca indicator 
	delete[]viz;											//dezalocam memoria
	index = 0;													
	return vector;											//returnam array-ul ce contine nodurile parcurse in adancime
}


int* Graf::bfs(int node) const								//parcurgerea in latime
{
	int* vector = new int[nodeCount + 1];					//retinem elementele in ordinea parcurgerii; la final adaugam -1 ca sa marcam capatul
	bool* viz = new bool[nodeCount];						//vector unde vor fi marcate elementele vizitate
	for (int i = 0; i < nodeCount; i++)							
		viz[i] = false;										//niciun element nu a fost inca vizitat

	int first, last;										//operam pe o coada, retinem primul si ultimul element din coada
	first = 0;
	last = -1;
	vector[++last] = node;									//primul si ultimul element din coada este nodul curent
	viz[node] = true;										//nodul curent a fost vizitat

	while (first <= last)									//cat inca mai sunt elemente in coada ai caror vecini nu au fost vizitati
	{
		for (Node* p = graf[vector[first]]->getStart(); p != NULL; p = p->getNext())	//parcurgerea nodurilor adiacente
			if (viz[p->getInfo()] == false)												//daca nodul adiacent nu a fost vizitat, atunci este adaugat in coada si marcat drept vizitat
			{
				viz[p->getInfo()] = true;													
				vector[++last] = p->getInfo();
			}
		first++;
	}

	vector[++last] = -1;												//marcam finalul
	delete[]viz;														//dezalocam memoria
	return vector;													
}

int Graf::distance(int node1, int node2) const			//se bazeza pe bfs
{
	int* queue = new int[nodeCount];
	int* dist = new int[nodeCount];												
	for (int i = 0; i < nodeCount; i++)					//distanta dintre oricare doua noduri se considera initial infinit
		dist[i] = infinit;
	
	int first, last;
	first = 0;
	last = -1;
	queue[++last] = node1;
	dist[node1] = 0;

	while (first <= last)
	{
		for (Node* p = graf[queue[first]]->getStart(); p != NULL; p = p->getNext())
			if (dist[queue[first]] + 1 < dist[p->getInfo()])							//daca distanta nodul curent si nodul adiacent este mai mica decat distanta presupusa anterior, distanta este reactualizata
			{
				queue[++last] = p->getInfo();
				dist[p->getInfo()] = dist[queue[first]] + 1;						//distanta este reactualizata
			}
		first++;
	}
	delete[]queue;																	//dezalocam memoria
	int distance = dist[node2];
	delete[]dist;
	return distance;
}

void Graf::dfs(int node, bool* viz) const											//dfs auxiliar pentru cntConexe()
{
	viz[node] = true;
	for (Node* p = graf[node]->getStart(); p != NULL; p = p->getNext())
		if (viz[p->getInfo()] == false)
			dfs(p->getInfo(), viz);
}

int Graf::cntConexe() const									//se bazeaza pe dfs 
{
	int count = 0;											//in count vor fi numarate componentele conexe
	bool* viz = new bool[nodeCount];
	for (int i = 0; i < nodeCount; i++)
		viz[i] = false;
	for (int i = 0; i < nodeCount; i++)
		if (viz[i] == false)
		{
			dfs(i, viz);
			count++;										//s-a gasit o noua componenta conexa
		}
	delete[]viz;											//dezalocam memoria
	return count;
}

bool Graf::isTree() const
{
	return (cntConexe() == 1 && edgeCount == nodeCount - 1);
}

bool Graf::existsEdge(int x, int y)												//verificam daca o muchie exista deja in graf pentru a nu o mai adauga o data
{
	for (Node* p = graf[x]->getStart(); p != NULL; p = p->getNext())
		if (p->getInfo() == y)
			return true;
	return false;
}

void Graf::addEdge(int x, int y)					
{
	if (x != y && !existsEdge(x, y)) {
		graf[x]->insert(y);							//adauga muchie de la x la y
		graf[y]->insert(x);							//adauga muchie de la y la x
		edgeCount++;								//creste nr de muchii
	}
	else
		if (x == y)																//tratam exceptiile
			throw "Nu exista muchie dintr-un nod in acelasi nod";
		else
			throw "Muchia exista deja";
}

int* Graf::operator[](int node) const											//supraincarcarea operatorului []
{
	int* vector = new int[graf[node]->getLength() + 1];							//alocam cu o componenta in plus pentru ca marcam cu -1 finalul
	int index = 0;
	for (Node* p = graf[node]->getStart(); p != NULL; p = p->getNext())
		vector[index++] = p->getInfo();
	vector[index] = -1;															//marcam cu -1 finalul 
	return vector;
}

bool Graf::operator<(Graf& other) const											//supraincarcarea operatorului <
{
	if (nodeCount == other.getNodeCount())
		return edgeCount < other.getEdgeCount();
	return nodeCount < other.getNodeCount();
}
	
bool Graf::operator>(Graf& other) const											//supraincarcarea operatorului >
{
	if (nodeCount == other.getNodeCount())
		return edgeCount > other.getEdgeCount();
	return nodeCount > other.getNodeCount();
}

Graf& Graf::operator=(const Graf& gr)											//supraincarcarea operatorului =
{
	for (int i = 0; i < nodeCount; i++)
		delete graf[i];
	delete[] graf;
	nodeCount = gr.nodeCount;
	edgeCount = gr.edgeCount;
	graf = new List*[nodeCount];
	for (int i = 0; i < nodeCount; i++)
		graf[i] = new List(*gr.getGraf()[i]);
	return *this;
}

std::istream& operator>>(std::istream& in, Graf& gr)								//supraincarcarea operatorului >>
{
	int n, m, x, y;
	in >> n >> m;
	gr = Graf(n);
	for (int i = 0; i < m; i++)
	{
		in >> x >> y;
		gr.addEdge(x, y);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, Graf& gr)									//supraincarcarea operatorului <<
{
	for (int i = 0; i < gr.getNodeCount(); i++)
		out << i<< " : " << gr.getGraf()[i] << std::endl;
	return out;
}

Graf::~Graf()																				//destructor
{
	for (int i = 0; i < nodeCount; i++)
		delete graf[i];
	delete[] graf;
	nodeCount = 0;
	edgeCount = 0;
}