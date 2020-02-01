#ifndef TRUNK_H_INCLUDED
#define TRUNK_H_INCLUDED
class Trunk
{
private:
    Trunk       ();
public:
    Trunk       (Trunk *, std::string );
    Trunk *prev;
    std::string str;
};
///Costruttore della classe Trunk
Trunk :: Trunk(Trunk *prev, std::string str)
{
    this->prev = prev;
    this->str = str;
}


#endif // TRUNK_H_INCLUDED
