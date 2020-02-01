#include <iostream>
#include "Albero.h"
#include "Nodo.h"
#include "Merge.h"
using namespace std;

int main()
{
    ///Dichiariamo i due alberi T1 e T2
    Albero T1,T2;
    int elemT1,elemT2;
    int app;
    ///Chiediamo quanti elementi vogliamo inserire nei due alberi
    cout<<"Quanti elementi vuoi inserire in T1?"<<endl;
    cin>>elemT1;
    cout<<"Quanti elementi vuoi inserire in T2?"<<endl;
    cin>>elemT2;
    ///Effetuiamo il caricamento dei dati in T1 e T2
    for(int i = 0;i < elemT1; i++)
    {
        cout<<"Inserire numero per T1: ";
        cin>>app;
        T1.Inserimento(app);
    }
    cout<<endl;
    for(int i = 0;i < elemT2; i++)
    {
        cout<<"Inserire numero per T2: ";
        cin>>app;
        T2.Inserimento(app);
    }
    ///Istanziamo un oggetto Fondi della classe Merge e passiamo gli alberi T1 e T2
    Merge Fondi (T1,T2);
    ///Ricaviamo in vettore fuso a partire dai due alberi passati precedentemente
    vector<int> VettoreFuso = Fondi.AFUS();
    ///Andiamo a creare un nuovo albero a partire dal vettore fuso
    Albero T3 (VettoreFuso);
    ///Effettuiamone la stampa
    cout<<"Stampo Albero RB T3: "<<endl;
    cout<<"Radice: "<<T3.getRad()->getKey()<<endl;
    T3.printTree(T3.getRad(),nullptr,false);
    return 0;
}
