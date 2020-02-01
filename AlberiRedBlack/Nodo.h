#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED
typedef enum colore {nero,rosso} Colore;
class Nodo{
private:
    int Key;
    Nodo    *Parent;
    Nodo    *Sx;
    Nodo    *Dx;
    Colore  colore;
public:
    Nodo            (void);
    Nodo            (int );
    Nodo            (int ,Colore );
    Nodo            (int ,Nodo *, Nodo *,Nodo *,Colore );
    int getKey      ();
    void setKey     (int );
    void setParent  (Nodo *);
    Nodo *getParent ();
    void setSx      (Nodo *);
    Nodo *getSx     ();
    void setDx      (Nodo *);
    Nodo *getDx     ();
    void setColore  (Colore );
    bool confronta  (Colore );
    ~Nodo()         {;}

};
///Costruttore di default
Nodo::Nodo ()
{
    this->Key = -1;
    this->Parent = nullptr;
    this->Sx = nullptr;
    this->Dx = nullptr;
}
///Costruttore con Key
Nodo::Nodo (int Key)
{
    this->Parent = nullptr;
    this->Sx = nullptr;
    this->Dx = nullptr;
    this->Key = Key;
}
///Costruttore con Key e Colore
Nodo::Nodo (int Key,Colore colore)
{
    this->Parent = nullptr;
    this->Sx = nullptr;
    this->Dx = nullptr;
    this->Key = Key;
    this->colore = colore;
}
///Contruttore completo con tutti gli attrivuti
Nodo::Nodo (int Key,Nodo *Parent,Nodo *Sx,Nodo *Dx,Colore colore)
{
    this->Parent = Parent;
    this->Sx = Sx;
    this->Dx = Dx;
    this->Key = Key;
    this->colore = colore;
}
///Restituisce il valore della Key del Nodo
int Nodo::getKey()
{
    return this->Key;
}
///Setta il valore Key del Nodo
void Nodo::setKey(int Key)
{
    this->Key = Key;
}
///Setta il Parent del Nodo
void Nodo::setParent (Nodo *nodo)
{
    this->Parent = nodo;
}
///Restituisce il Parent del Nodo
Nodo* Nodo::getParent ()
{
    return this->Parent;
}
///Restituisce il Figlio Sx
Nodo* Nodo::getSx ()
{
    return this->Sx;
}
///Setta il Figlio Sx
void Nodo::setSx (Nodo *nodo)
{
    this->Sx = nodo;
}
///Restituisce il Figlio Dx
Nodo* Nodo::getDx ()
{
    return this->Dx;
}
///Setta il Figlio Dx
void Nodo::setDx (Nodo *nodo)
{
    this->Dx = nodo;
}
///Setta il Colore del Nodo
void Nodo::setColore (Colore colore)
{
    this->colore = colore;
}
///Questo metodo permette, dato in input un colore, di verificare se il Nodo su cui è chiamato è di quel colore o meno
bool Nodo::confronta (Colore colore)
{
    bool result;
    (this->colore == colore) ? result = true : result = false;
    return result;
}

#endif // NODO_H_INCLUDED
