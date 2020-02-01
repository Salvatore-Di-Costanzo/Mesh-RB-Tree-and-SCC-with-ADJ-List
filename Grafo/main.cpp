#include <iostream>
///Assunzioni
#define Max_Nodi 1000
#define Max_Archi 10000
#include "Grafo.h"
using namespace std;

int main()
{
    ///Istanzio un oggetto 'g' della classe 'Grafo'
    Graph g;
    ///Predispongo due variabili per scaricare le informazioni dal file di input
    int nodi,archi;
    ///Procedo all'apertura del file di input
    std::ifstream File_I("input.txt");
    ///Se fallisce ritorna errore sullo standard error
    if (!File_I.is_open())
    {
        std::cerr << "File non aperto" << std::endl;
        exit(-1);
    }
    ///Altrimenti prendiamo il numero di nodi
    File_I >> nodi;
    ///Controllo se il numero di nodi rienta nel range, in caso negativo esci
    if (nodi > Max_Nodi || nodi < 2)
    {
        std::cout << "Superato Limite Nodi" << std::endl;
        exit(-2);
    }
    ///Altrimenti prendiamo il numero di archi
    File_I >> archi;
    ///Controllo se il numero di archi rienta nel range, in caso negativo esci
    if (archi > Max_Archi || archi < 1)
    {
        std::cout << "Superato Limite Archi" << std::endl;
        exit(-3);
    }
    ///Aggiungo tanti nodi al grafo tanti quanti sono quelli letti dal file + 1 in quanto i nostri nodi partono dalla posizione 1 e non 0
    for(int i = 0; i < nodi + 1 ; i++)
        g.addNode(new Node(i));
    ///Leggo dal file le informazioni dal file e le inserisco nei nodi del grafo
    for(int i = 0; i < archi; i++)
    {
        int piazza;
        File_I >> piazza;
        int adiacenza;
        File_I >> adiacenza;
        g.getNode(piazza)->addEdge(g.getNode(adiacenza));
    }
    ///Chiudo il file
    File_I.close();
    ///Faccio partire la ricerca delle componenti fortemente connesse
    g.DFS();
    return 0;
}
