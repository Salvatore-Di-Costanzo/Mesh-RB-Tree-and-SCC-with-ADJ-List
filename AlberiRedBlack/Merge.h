#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED
#include "Albero.h"
class Merge{
private:
    std::vector <int> vetT1,vetT2,vetT3;
public:
    Merge                   (Albero &, Albero &);
    void Stampa             ();
    std::vector<int> AFUS   ();
    ~Merge()                {;}
};
///Costruttore classe Merge
Merge::Merge (Albero &T1,Albero &T2)
{
    T1.Pulisci();
    this->vetT1 = T1.Scarica(T1.getRad());
    T2.Pulisci();
    this->vetT2 = T2.Scarica(T2.getRad());
}
///Permette di stampare il contenuto scaricato dai due vettori
void Merge::Stampa()
{
    std::cout<<"Vettore T1 in Merge: ";
    for(unsigned i=0;i<vetT1.size();i++)
        std::cout<<vetT1.at(i)<<" ";
    std::cout<<"Vettore T2 in Merge: ";
    for(unsigned i=0;i<vetT2.size();i++)
        std::cout<<vetT2.at(i)<<" ";
}
///Esegue il Merge dei due vettori
std::vector<int> Merge::AFUS()
{
    unsigned i = 0,j = 0;
    while( i < vetT1.size() &&  j < vetT2.size() )
    {
        if(vetT1.at(i) < vetT2.at(j))
            vetT3.push_back(vetT1.at(i++));
        else
            vetT3.push_back(vetT2.at(j++));
    }
    while(i < vetT1.size())
        vetT3.push_back(vetT1.at(i++));
    while(j < vetT2.size())
        vetT3.push_back(vetT2.at(j++));
    return vetT3;
}




#endif // MERGE_H_INCLUDED
