#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
#include <list>
#include <limits>
typedef enum colore {Bianco,Grigio,Nero} Colore;
class Node{
    Colore colore;
    Node *p;
    int d;
    int f;
    int data;
    std::list<Node *> *adj;
public:
    Node                        (int);
    void addEdge                (Node *);
    std::list<Node *> *getAdj   ();
    int getData                ();
    void setColor               (Colore );
    int getColor                ();
    void setP                   (Node *);
    Node *getP                  ();
    void setD                   (int );
    int getD                    ();
    void setF                   (int );
    int getF                    ();
    ~Node()                     {delete adj;}
};
///Costruttore nodo
Node::Node (int data)
{
    this->data=data;
    this->colore = Bianco;
    p=nullptr;
    d=std::numeric_limits<int>::max();
    f=std::numeric_limits<int>::max();
    adj=new std::list<Node *>;
}
///Metodo per aggiungere un elemento alla lista di adiacenza del nodo
void Node::addEdge(Node *w)
{
    adj->push_back(w);
}
///Metodo utilizzato per restituire la lista di adiacenza del nodo
std::list<Node *> * Node::getAdj()
{
    return adj;
}
///Metodo utilizzato per restituire il campo data del nodo
int Node::getData()
{
    return this->data;
}
///Metodo utilizzato per settare il campo colore del nodo
void Node::setColor(Colore colore)
{
    this->colore = colore;
}
///Metodo utilizzato per restituire il colore del nodo
int Node::getColor()
{
    return this->colore;
}
///Metodo utilizzato per settare il parent del nodo
void Node::setP (Node *p)
{
    this->p = p;
}
///Metodo utilizzato per restituire il parent del nodo
Node * Node::getP()
{
    return this->p;
}
///Metodo utilizzato per settare il campo d
void Node::setD(int d)
{
    this->d = d;
}
///Metodo utilizzato per restituire il campo d
int Node::getD()
{
    return this->d;
}
///Metodo utilizzato per settare il campo f
void Node::setF(int f)
{
    this->f = f;
}
///Metodo utilizzato per restituire il campo f
int Node::getF()
{
    return this->f;
}

#endif // NODO_H_INCLUDED
