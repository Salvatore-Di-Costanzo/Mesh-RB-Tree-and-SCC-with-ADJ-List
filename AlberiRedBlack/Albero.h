#ifndef ALBERO_H_INCLUDED
#define ALBERO_H_INCLUDED
#include "Nodo.h"
#include "Trunk.h"
#include <vector>
#include <math.h>
class Albero{
private:
    Nodo *radice;
    Nodo *nil;
    std::vector<int> Scaricato;
    void RotateDx               (Nodo *);
    void RotateSx               (Nodo *);
    void TreeInsert             (Nodo *);
    void FixUp                  (Nodo *);
    void FixColore              (Nodo *);
    int profondita = 0;
    int altezza = 0;
public:
    Albero                      (void);
    Albero                      (std::vector<int> &);
    void inOrder                (Nodo *);
    std::vector <int> Scarica   (Nodo *);
    void Pulisci                ();
    void Inserimento            (int );
    void showTrunks             (Trunk* );
    void printTree              (Nodo *,Trunk* ,bool);
    Nodo *getRad                ();
    void setRad                 (Nodo *);
    Nodo *Costruisci            (int, int ,std::vector<int> &,Nodo* ,int);
    ~Albero()                   { delete this->radice; delete this->nil; }
};
///Costruttore di default per l'Albero
Albero::Albero ()
{
    this->nil = new Nodo(-1,nullptr,nullptr,nullptr,nero);
    radice = nil;
    nil->setParent(radice);
}
///Costruttore di Albero usato per andare a costruire la struttura a partire dai
///dati presenti all'interno del vettore e lanciare la prodecura di correzione
///dell'informazione sul colore
Albero::Albero(std::vector<int> &vettore)
{
    this->nil = new Nodo();
    float dec = log2(vettore.size());
    ((dec - log2(vettore.size())) == 0) ? this->altezza = floor(log2(vettore.size()-1)) + 1 : this->altezza = floor(log2(vettore.size()-1));
    this->setRad(Costruisci(0,vettore.size() - 1,vettore,this->nil,this->altezza));
    std::cout<<std::endl<<std::endl;
    this->FixColore(this->getRad());
}
///Metodo per settare la radice
void Albero::setRad(Nodo *nodo)
{
    radice = nodo;
}
///Metodo di supporto per la stampa dell'ASCII Tree
void Albero::showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;
    showTrunks(p->prev);
    std::cout << p->str;
}
///Metodo di stampa ASCII Tree
void Albero::printTree(Nodo *root,Trunk *prev, bool isLeft)
{
    const char *col;
    if (root == nullptr)
        return;

    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getSx(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    col = (root->confronta(rosso)) ? "Rosso" : "Nero";
    (root->getKey() != -1) ? std::cout << root->getKey() << " " << col << std::endl : std::cout << "NIL" << std::endl ;
    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getDx(), trunk, false);
}
///Metodo per costruire le relazioni tra i nodi dell'Albero
Nodo* Albero::Costruisci( int i, int j, std::vector<int> &vettore, Nodo* predecessore, int altezza_max)
{
    if( i > j )
        return this->nil;
    int mediano = ( i + j ) / 2;
    Nodo* nuovo = new Nodo(vettore.at(mediano),nullptr,nullptr,nullptr,nero);
    nuovo->setParent(predecessore);
    nuovo->setSx(Costruisci(i,mediano-1,vettore,nuovo,altezza_max));
    nuovo->setDx(Costruisci(mediano+1,j,vettore,nuovo,altezza_max));
    return nuovo;
}
///Metodo per effettuare la Rotazione Sinistra di un nodo
void Albero::RotateSx(Nodo *nodo)
{
    Nodo *app = nodo->getDx();
    nodo->setDx(app->getSx());
    if(app->getSx() != this->nil)
        app->getSx()->setParent(nodo);
    app->setParent(nodo->getParent());
    if(nodo->getParent() == this->nil)
        this->radice = app;
    else if (nodo == nodo->getParent()->getSx())
        nodo->getParent()->setSx(app);
         else
            nodo->getParent()->setDx(app);
    app->setSx(nodo);
    nodo->setParent(app);
}
///Metodo per effettuare la Rotazione Destra di un nodo
void Albero::RotateDx(Nodo *nodo)
{
    Nodo *app = nodo->getSx();
    nodo->setSx(app->getDx());
    if(app->getDx() != this->nil)
        app->getDx()->setParent(nodo);
    app->setParent(nodo->getParent());
    if(nodo->getParent() == this->nil)
        this->radice = app;
    else if (nodo == nodo->getParent()->getSx())
        nodo->getParent()->setSx(app);
         else
            nodo->getParent()->setDx(app);
    app->setDx(nodo);
    nodo->setParent(app);
}
///Metodo per la stampa in-Order dell'Albero
void Albero::inOrder(Nodo *nodo)
{
    if( nodo != this->nil )
    {
        inOrder( nodo->getSx() );
        (nodo->confronta(nero)) ? (std::cout << "Nodo: " << nodo->getKey() << " Colore: Nero, Padre: " << nodo->getParent()->getKey() << std::endl) : (std::cout << "Nodo: " << nodo->getKey() << " Colore: Rosso, Padre: " << nodo->getParent()->getKey() << std::endl);
        inOrder( nodo->getDx() );
    }
}
///Metodo utile per scaricare all'interno del vettore 'Scaricato' il contenuto dell'albero
std::vector<int> Albero::Scarica(Nodo *nodo)
{
    if( nodo != this->nil )
    {
        Scarica( nodo->getSx() );
        Scaricato.push_back(nodo->getKey());
        Scarica( nodo->getDx() );
    }
    return Scaricato;
}
///Metodo per il reset del vettore
void Albero::Pulisci()
{
    Scaricato.clear();
}
///Metodo di inserimento nodo all'interno dell'albero
void Albero::TreeInsert(Nodo *nodo)
{
    Nodo *y = this->nil;
    Nodo *x = this->radice;
    while(x != nil)
    {
        y = x;
        if(nodo->getKey() < x->getKey())
            x = x->getSx();
        else
            x = x->getDx();
    }
    nodo->setParent(y);
    if (y == this->nil)
        this->radice = nodo;
    else if ( nodo->getKey() < y->getKey())
        y->setSx(nodo);
         else
            y->setDx(nodo);


}
///Metodo Fix Up per garantire che le proprieta' degli Alberi Red-Black siano preservate effettuando la ricolorazione dei nodi e le rotazioni per bilanciarlo
void Albero::FixUp(Nodo *nodo)
{
    while( (nodo != this->radice) && (nodo->getParent()->confronta(rosso)) )
    {
        if(nodo->getParent() == nodo->getParent()->getParent()->getSx())
        {
            Nodo* app = nodo->getParent()->getParent()->getDx();
            if(app->confronta(rosso))
            {
                nodo->getParent()->setColore(nero);
                app->setColore(nero);
                nodo->getParent()->getParent()->setColore(rosso);
                nodo = nodo->getParent()->getParent();
            }
            else
            {
                if(nodo == nodo->getParent()->getDx())
                {
                    nodo = nodo->getParent();
                    this->RotateSx(nodo);
                }
                nodo->getParent()->setColore(nero);
                nodo->getParent()->getParent()->setColore(rosso);
                this->RotateDx(nodo->getParent()->getParent());
            }
        }
        else
        {
            Nodo* app = nodo->getParent()->getParent()->getSx();
            if(app->confronta(rosso))
            {
                nodo->getParent()->setColore(nero);
                app->setColore(nero);
                nodo->getParent()->getParent()->setColore(rosso);
                nodo = nodo->getParent()->getParent();
            }
            else
            {
                if(nodo == nodo->getParent()->getSx())
                {
                    nodo = nodo->getParent();
                    this->RotateDx(nodo);
                }
                nodo->getParent()->setColore(nero);
                nodo->getParent()->getParent()->setColore(rosso);
                this->RotateSx(nodo->getParent()->getParent());
            }
        }
    }
    this->radice->setColore(nero);
}
///Metodo di inserimento che a partire da una chiave va ad inserire un nodo
///con la stessa chiave all'interno dell'Albero
void Albero::Inserimento(int key)
{
    Nodo* app = new Nodo(key, this->nil, this->nil, this->nil,rosso);
    this->TreeInsert(app);
    this->FixUp(app);
}
///Metodo per la ricolorazione dell'Albero costruito con il vector fuso
void Albero::FixColore (Nodo *nodo)
{
    ///Effettuaiamo la ricolorazione poiche' dopo la fusione dei due alberi le proprieta' RB del nuovo albero sono errate essendo tutte le foglie nere
    ///procediamo quindi col colorare i nodi nel modo corretto e mantenendo il padre nero
    ///per i nodi diversi dal padre effettuiamo una verifica semplice, se il nodo, i due figli e il Parent
    ///sono neri allora possiamo colorare il nodo in analisi di rosso
    if( nodo != this->nil  )
    {
        if (nodo != this->radice)
        {
            if(nodo->getDx() == this->nil && nodo->getSx() == this->nil )
            {
                if(nodo->getParent()->getSx()->getDx() == this->nil && nodo->getParent()->getSx()->getSx() == this->nil && nodo->getParent()->getDx()->getSx() == this->nil && nodo->getParent()->getDx()->getDx() == this->nil && this->profondita == this->altezza)
                {
                    nodo->setColore(rosso);
                    nodo->getParent()->setColore(nero);
                }
                else if(nodo->getParent()->getDx() == nodo)
                {
                    if(nodo->getParent()->getSx() == this->nil && nodo->getSx() == this->nil && this->profondita == this->altezza)
                    {
                        nodo->setColore(rosso);
                        nodo->getParent()->setColore(nero);
                    }
                }
                else if(nodo->getParent()->getDx() == this->nil && nodo->getDx() == this->nil && this->profondita == this->altezza)
                {
                    nodo->setColore(rosso);
                    nodo->getParent()->setColore(nero);
                }
            }
            else if((nodo->getDx()->confronta(nero) && nodo->getSx()->confronta(nero)) && nodo->getParent()->confronta(nero))
                nodo->setColore(rosso);
        }
        this->profondita++;
        FixColore(nodo->getSx());
        this->profondita--;
        this->profondita++;
        FixColore(nodo->getDx());
        this->profondita--;
    }
}
///Metodo che restituisce la radice
Nodo* Albero::getRad()
{
    return this->radice;
}



#endif // ALBERO_H_INCLUDED
