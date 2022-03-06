#include <iostream>
#include <stdlib.h>
using namespace std;
///clas Nod=clasa unui nod
class Nod{
private:
    int info;
    Nod *prev;
    Nod *next;
public:
    Nod(int, Nod*, Nod*);///constructor de initializare cu parametrii
    ~Nod();///destructor
    Nod(Nod&);///constructor de copiere
    void set_info(int);///setter pentru info
    void set_prev(Nod*);///setter pentru next
    void set_next(Nod*);///setter pentru prev
    int get_info();///getter pentru info
    Nod* get_prev();///getter pentru prev
    Nod* get_next();///getter pentru next
    friend class List;///friend class pentru a avea acces la membrele private ale clasei nod
};
///constructor de initializare cu parametrii
Nod::Nod(int info=0, Nod* prev=NULL, Nod* next=NULL){
    this->info=info;
    this->prev=prev;
    this->next=next;
}
///constructor de copiere
Nod::Nod(Nod &cpy){
    this->info=cpy.info;
    this->prev=cpy.prev;
    this->next=cpy.next;
}
///destructor pentru clasa Nod
Nod::~Nod(){
    this->info=0;
    this->prev=0;
    this->next=0;
}
///setter pentru info
void Nod::set_info(int info){
    this->info=info;
}
///setter pentru prev
void Nod::set_prev(Nod* prev){
    this->prev=prev;
}
///setter pentru next
void Nod::set_next(Nod* next){
    this->next=next;
}
///getter pentru info
int Nod::get_info(){
    return info;
}
///getter pentru prev
Nod* Nod::get_prev(){
    return prev;
}
///getter pentru next
Nod* Nod::get_next(){
    return next;
}
///friend class pentru a avea acces la membrele private ale clasei Nod
class List{
    Nod *first; ///adresa primului nod din lista
    Nod *last;  ///adresa ultimului nod din lista
public:
    List(); ///constructor de initializare fara parametrii
    List(Nod*, Nod*); ///constructor de initializare cu parametrii
    ~List(); ///destructor
    List(List &); ///constructor de copiere
    void set_first(Nod*);///setter pentru first
    void set_last(Nod*);///setter pentru last
    Nod* get_first();///getter pentru first
    Nod* get_last();///getter pentru last
    void add_elem(int); ///metoda publica de adaugare element la sfarsitului listei
    void add_poz(int, int); ///metoda publica de adaugare a unui element pe o pozitie data
    void print_list(ostream &out); ///metoda publica de afisare a unei liste in ambele sensuri
    void read_list(istream &in); ///metoda publica de citire a elementelor unei liste
    void delete_elem(int); ///metoda publica de stergere a unui element de pe o pozitie data
    void concat(List& l1, List& l2); ///metoda publica de concatenare a doua liste
    Nod* find_val(Nod*,int); ///metoda publica de cautare a adresei unui element de pe o pozitie data
    friend ostream& operator<<(ostream &out, List& l); ///supraincarcarea operatorului <<
    friend istream& operator>>(istream &in, List& l); ///supraincaracrea operatorului >>
    friend List& operator+(List& l1, List& l2); ///supraincarcarea operatorului +
    void info_obs(int);///metoda pentru afisarea a n obiecte
};
///constructor de initializare fara parametrii
List::List(){
    first=0;
    last=0;
}
///constructor de initializare cu parametrii
List::List(Nod* first, Nod* last){
    this->first=first;
    this->last=last;
}
///destructor
List::~List(){
    Nod *p=first;
    Nod *q;
    while (p!=0)
    {
        q=p;
        p=p->next;
        delete q;
    }
    first=0;
}
///constructor de copiere
List::List(List &initial){
    if (initial.first==0){
        this->first=0;
    }
    else{
        first=new Nod(*initial.first);
        Nod *p=initial.first->next;
        Nod *q=first;
        while (p){
            q->next=new Nod(*p);
            p->prev=p;
            p=p->next;
            q->prev=q;
            q=q->next;
        }
    }}
///setter pentru first
void List::set_first(Nod* first){
    this->first=first;
}
///setter pentru last
void List::set_last(Nod* last){
    this->last=last;
}
///getter pentru first
Nod* List::get_first(){
    return first;
}
///getter pentru last
Nod* List::get_last(){
    return last;
}
///metoda publica de gasire a adresei unui element de pe o pozitie data
Nod*::List::find_val(Nod* first,int poz){
    int i=0;
    while (first!= NULL && i< poz)
            {
                first=first->next;
                i++;
            }
    if (i==poz)
       return first;
    else
       return NULL;

}
///metoda publica de adaugare element la sfarsitul listei
void List::add_elem(int value){
    Nod *newNod = new Nod(value,NULL);
    if (first==0){///daca lista e goala, primul si ultimul nod sunt cel nou
        first=newNod;
    }
    else{
        ///altfel parcurg si leg la final
        Nod *last=first;
        while (last->next != NULL){
            last=last->next;
        }
        last->next=newNod;
        last->next->prev=last;
    }
}
///metoda publica de inserare a unui element pe o pozitie data
void List::add_poz(int value,int poz=0){
    Nod *n = new Nod(value,NULL);
    if (first==0)///daca lista e goala, primul si ultimul nod sunt cel nou
          first=n;
    else
        if (poz==0)
            {
                n->next=first;
                first->prev=n;
                first=n;
            }
        else
        {
             Nod *p=find_val(first, poz);
             if (p!=NULL)
             {
                  n->next=p;
                  n->prev=p->prev;
                  p->prev->next=n;
                  p->prev=n;
             }
             else
                 add_elem(value);///daca pozitia depaseste numarul listei se adauga la sfarsit
        }
}
///metoda publica de citire a unei liste
void List::read_list(istream &in){
    int n,i,val;
    cout<<"Introduceti numarul de elemente al listei:";
    in>>n;
    cout<<"Introduceti elementele listei:";
    for (i=0;i<n;i++)
    {
        in>>val;
        add_poz(val,i);
    }
}
///metoda publica de afisare a unei liste
void List::print_list(ostream &out){
    Nod *p=first;
    out<<endl<<"Afisare de la inceput: ";
    ///parcurg lista de la inceput
    while (p != NULL){
        out<<p->info<<" ";
        if(p->next==NULL)
            last=p; ///retin adresa ultimului element
        p=p->next;
    }
    ///parcurg lista de la sfarsit
    out<<endl<<"Afisare de la sfarsit: ";
    while(last!=first)
    {
        out<<last->info<<" ";
        last=last->prev;
    }
    out<<last->info;
}
///supraincarcarea operatorului >>
istream& operator>>(istream& in, List& l)
{
    l.read_list(in);
    return in;
}
///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, List& l){
    l.print_list(out);
    return out;
}
///metoda publica de concatenare a doua liste
void List::concat(List& l1, List& l2){
    Nod *p=l1.get_first();
    ///adaug elementele din prima lista
    while(p!=NULL)
    {
        add_elem(p->info);
        p=p->next;
    }
    ///adaug elementele din a doua lista
    p=l2.get_first();
    while(p!=NULL)
    {
        add_elem(p->info);
        p=p->next;
    }
}
///supraincarcarea operatorului +
inline List& operator+(List& l1, List& l2){
    List *l = new List;
    l->concat(l1,l2);
    return *l;
}
///metoda publica de stergere a unui element de pe o pozitie data
void List::delete_elem(int poz){
    if (poz==0)
        {
            Nod *p=first;
            first=first->next;
            first->prev=NULL;
            delete p;
        }
    else
       {
           Nod *p=find_val(first, poz);
           p->next->prev=p->prev;
           p->prev->next=p->next;
           delete p;}
}
void List::info_obs(int n){
    int i;
    cout<<"Numarul de liste care urmeaza a fi introduse este: "<<n<<endl;
    for (i=0;i<n;i++)
    {
        cout<<"Cititi lista "<<i+1<<": "<<endl;
        cin>>this[i];
    }
    for(i=0;i<n;i++)
       cout<<"Lista "<<i+1<<": "<<this[i]<<endl;
}
void meniu_output()
{
    cout<<"\n Dobre Adriana Lia - Proiect - Nume proiect:Clasa 'Lista dublu inlantuita' (Tema 7) \n";
    cout<<"\n\t\t\t\t MENIU:";
    cout<<"\n-----------------------------------------------------------------------\n";
    cout<<"\n";
    cout<<"1. Actiunea 1 din meniu:citirea si afisarea a n liste dublu inlantuite"; cout<<"\n";
    cout<<"2. Actiunea 2 din meniu:adaugarea unui element"; cout<<"\n";
    cout<<"3. Actiunea 3 din meniu:adaugarea unui element pe o pozitie data"; cout<<"\n";
    cout<<"4. Actiunea 4 din meniu:stergerea unui element de pe o pozitie data"; cout<<"\n";
    cout<<"5. Actiunea 5 din meniu:afisarea listei in ambele sensuri"; cout<<"\n";
    cout<<"6. Actiunea 6 din meniu:concatenarea a doua liste";cout<<"\n";
    cout<<"0. Iesire."; cout<<"\n";
}
void meniu(){
    int option,n,i,val,j;
    option=0;///optiunea aleasa din meniu
    i=0;///indicele listei pe care doriti sa o modificati
    n=0;///numarul de liste care vor fi introduse
    j=0;///pozitia pe care se vor face modificarile
    List *l;
    do
    {
        meniu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {
            cout<<"Introduceti numarul de liste duble inlantuite: ";
            cin>>n;
            if(n<0)
               cout<<"Valoare invalida";
            else
                {
                    l= new List[n];
                    l->info_obs(n);
                }
        }
        if (option==2)
        {
            if (n>0)
                {
                    cout<<"Introduceti numarul listei pe care doriti sa o modicati: ";
                    cin>>i;
                    cout<<"Introduceti valoarea pe care doriti sa o inserati in lista: ";
                    cin>>val;
                    if(i-1<=n)
                        {l[i-1].add_elem(val);
                         cout<<l[i-1];}
                    else
                        cout<<"Nu exista lista";
                }
            else
                cout<<"Nu a fost introdusa nicio lista. Pentru a introduce liste apasati tasta 1.";
        }
        if (option==3)
        {
            if (n>0)
                {
                    cout<<"Introduceti numarul listei pe care doriti sa o modicati: ";
                    cin>>i;
                    cout<<"Introduceti valoarea pe care doriti sa o inserati in lista: ";
                    cin>>val;
                    cout<<"Introduceti pozitia pe care doriti sa inserati valoarea introdusa: ";
                    cin>>j;
                    if (i-1<=n)
                         {l[i-1].add_poz(val,j-1);
                          cout<<l[i-1];}
                    else
                        cout<<"Nu exista lista";
                }
            else
                cout<<"Nu a fost introdusa nicio lista. Pentru a introduce liste apasati tasta 1.";
        }
        if (option==4)
        {
           if (n>0)
                {
                    cout<<"Introduceti numarul listei pe care doriti sa o modicati: ";
                    cin>>i;
                    cout<<"Introduceti pozitia elementului pe care doriti sa il stergeti: ";
                    cin>>j;
                    if (i-1<=n)
                         {l[i-1].delete_elem(j-1);
                          cout<<l[i-1];}
                    else
                        cout<<"Nu exista lista";
                }
            else
                cout<<"Nu a fost introdusa nicio lista. Pentru a introduce liste apasati tasta 1.";
        }
        if (option==5)
        {
            if (n>0)
                {
                    cout<<"Introduceti numarul listei pe care doriti sa o afisati: ";
                    cin>>i;
                    if(i-1<=n)
                        cout<<l[i-1];
                    else
                        cout<<"Nu exista lista";

                }
            else
                cout<<"Nu a fost introdusa nicio lista.Pentru a introduce liste apasati tasta 1.";
        }
        if (option==6)
        {
           if (n>0)
                {
                    cout<<"Introduceti cele doua liste pe care doriti sa le concatenati: ";
                    cin>>i>>j;
                    if (i-1<=n && j-1<=n)
                          cout<<l[i-1]+l[j-1];
                    else
                        cout<<"Nu exista una dintre liste sau ambele";
                }
            else
                cout<<"Nu a fost introdusa nicio lista.Pentru a introduce liste apasati tasta 1.";
        }
        if (option==0)
        {
            cout<<"\nEXIT!\n";
        }
        if (option<0||option>6)
        {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}
int main()
{
    meniu();
    return 0;
}

