#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include <fstream>
#include <stack>
#include <queue>
#include <vector>
#include <limits>
#include "Nodo.h"
class Graph
{
private:
    int V;
    std::vector<Node *> *adj;
public:
    Graph                   ();
    void addNode            (Node *);
    Node *getNode           (int );
    void printAdj           ();
    Graph getTranspose      ();
    void DFS_Visit1         (Node *,std::stack<Node *> &);
    void DFS_Visit2         (Node *,Graph &);
    void DFS                ();
    ~Graph()                {delete adj;};
};
///Costruttore grafo
Graph::Graph ()
{
    V=0;
    this->adj = new std::vector<Node *>;
}
///Metodo per aggiungere in nodo
void Graph::addNode (Node *s)
{
    this->adj->push_back(s);
    this->V++;
}
///Metodo per ottenere un node della lista in posizione v
Node* Graph::getNode(int v)
{
    return this->adj->at(v);
}
///Metodo per la stampa della lista di adiacenza
void Graph::printAdj(){
    for(auto v:*adj){
        std::cout<<"Adj("<<v->getData()<<"):";
        for(auto vv:*v->getAdj())
            std::cout<<" "<<vv->getData();
        std::cout<<std::endl;
    }
}
///DFS per la visita sul grafo di partenza
void Graph::DFS_Visit1(Node *s,std::stack<Node *> &L)
{
    s->setColor(Grigio);
    s->setD(s->getD()+1);
    for(auto v : *s->getAdj())
        {
            if (v->getColor() == 0)
            {
                v->setP(s);
                DFS_Visit1(v,L);
            }
        }
    s->setColor(Nero);
    s->setF(s->getD()+1);
    L.push(s);
}
///DFS per la visita sul grafo trasposto
void Graph::DFS_Visit2(Node *s,Graph &g)
{
    s->setColor(Grigio);
    s->setD(s->getD()+1);
    int index = 0;
    for(int i = 0;i < V ;i++)
    {
        if(g.getNode(i)->getData() == s->getData())
        {
            index = i;
            i = V;
        }
    }
    for(auto x : *g.adj->at(index)->getAdj())
    {
        if (x->getColor() == Bianco)
        {
            std::cout<<" -> "<<x->getData();
            x->setP(s);
            DFS_Visit2(x,g);
        }
    }
    s->setColor(Nero);
    s->setF(s->getD()+1);
}

///Metodo per ottenere il grafo trasposto
Graph Graph::getTranspose()
{
    Graph g ;
    for(int i = 0; i<V ;i++)
        g.addNode(new Node(this->getNode(i)->getData()));

    for(auto x : *adj)
        for(auto y : *x->getAdj())
        {
            for(int i = 0;i < V ;i++)
            {
                if(adj->at(i) == y)
                {
                    g.getNode(i)->addEdge(x);
                    i = V;
                }
            }
        }
    return g;
}

///Metodo per la ricerca delle componenti fortemente connesse
void Graph::DFS ()
{
    ///Dichiaro lo stack
    std::stack<Node *> L;
    ///Coloro tutti i nodi di bianco
    for(unsigned i = 0; i < adj->size(); i++)
    {
        adj->at(i)->setColor(Bianco);
        adj->at(i)->setP(nullptr);
        adj->at(i)->setD(Bianco);
    }

    ///Eseguo una visita DFS passando anche lo stack per riempirlo
    for(unsigned i = 0; i < adj->size(); i++)
        if (adj->at(i)->getColor() == 0)
            DFS_Visit1(adj->at(i),L);

    ///Calcolo il trasposto
    Graph g = getTranspose();
    ///Dichiaro il grafo SCC
    Graph SCC;
    ///Settiamo i nodi del grafo di partenza di colore Bianco
    for(unsigned i = 0; i < adj->size(); i++)
        adj->at(i)->setColor(Bianco);
    ///Dichiaro un vettore per collezionare gli elementi non collegati
    std::vector<int> Non_Coll;
    ///Tengo un contatore per contare le compotenti fortemente connesse
    int control_elem = 0;
    ///Avvia la procedura per la ricerca degli elementi fortementi connessi
    while (!L.empty())
    {
        ///Scarica l'elemento testa dallo stack
        Node * v = L.top();
        ///Rimuovi la testa dallo stack
        L.pop();
        ///Procedi a verificare il nodo
        if (v->getColor() == 0)
        {
            if (v->getData() != 0)
            {
                std::cout<<std::endl<<"Elementi Fortemente Connessi: "<<v->getData() ;
                Non_Coll.push_back(v->getData());
                control_elem++;
            }
            DFS_Visit2(v,g);
        }
        ///Aggiungiamo il nodo che è fortemente connesso al grafo SCC
        SCC.addNode(v);
    }
    ///Apriamo il file di output
    std::ofstream File_O("output.txt");
    if (!File_O.is_open())
    {
        std::cerr << "File Output non aperto" << std::endl;
        exit(-1);
    }
    ///Se esistono piu' elementi fortemente connessi allora stampali sul file
    if(control_elem != 1)
    {
        for(unsigned i = 0;i < Non_Coll.size() - 1 ;i++)
            for(unsigned j = i+1;j < Non_Coll.size() ;j++)
                File_O<<Non_Coll.at(j)<<" "<<Non_Coll.at(i)<<std::endl;
        File_O.close();
    } else ///Altrimenti setta il valore come 0 0
        File_O<<0<<" "<<0<<std::endl;

    File_O.close();
}

#endif // GRAFO_H_INCLUDED
