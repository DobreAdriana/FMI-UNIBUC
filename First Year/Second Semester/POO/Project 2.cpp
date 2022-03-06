#include <iostream>
#include <stdlib.h>
#include <typeinfo>
using namespace std;
class locuinta{
protected:
   string numeClient; ///variabila pentru numele clientului
   int suprafataUtila; ///variabila pentru suprafata utila
   float discount; ///variabila pentru discount
public:
   locuinta(string, int, float);///constructor pentru clasa locuinta
   locuinta(const locuinta&);///contructor de copiere pentru clasa locuinta
   virtual ~locuinta();///destructor virtual pentru clasa locuinta-late binding
   virtual void citire(istream &in); ///metoda virtuala de citire pt clasa locuinta-late binding
   virtual void afisare(ostream &out);///metoda virtuala de afisare pt clasa locuinta-late binding
   friend istream& operator>>(istream&, locuinta&);///supraincarcarea operatorului >>
   friend ostream& operator<<(ostream&, locuinta&);///supraincarcarea operatorului <<
   locuinta& operator=(const locuinta& loc);///supraincarcarea operatorului =
   virtual float CalculChirie(int X, bool Y)=0;///metoda virtuala pura pt calculul chiriei
};

///constructorul de initializare pt clasa locuinta
locuinta::locuinta(string numeClient="",int suprafataUtila=0, float discount=0){
    this->numeClient=numeClient;
    this->suprafataUtila=suprafataUtila;
    this->discount=discount;
}

///constructorul de copiere pt clasa locuinta
locuinta::locuinta(const locuinta &cpy){
    this->numeClient=numeClient;
    this->suprafataUtila=suprafataUtila;
    this->discount=discount;
}

///destructorul pt clasa locuinta
locuinta::~locuinta(){
    numeClient="";
    suprafataUtila=0;
    discount=0;
}

///metoda virtuala de citire
void locuinta::citire(istream &in){
    cout<<"Introduceti numele clientului: ";
    in.get();
    getline(in,numeClient);
    cout<<"Introduceti suprafata utila: ";
    in>>suprafataUtila;
    cout<<"Introduceti discountul: ";
    in>>discount;

}

///metoda virtuala de afisare
void locuinta::afisare(ostream &out){
    out<<"Nume client: "<<numeClient<<"\n";
    out<<"Suprafata utila: "<<suprafataUtila<<"\n";
    out<<"Discout: "<<discount<<"\n";
}

///supraincarcarea operatorului >>
istream& operator>>(istream& in,locuinta& loc){
    loc.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, locuinta& loc){
    loc.afisare(out);
    return out;
}

///supraincarcarea operatorului =
locuinta& locuinta::operator=(const locuinta& loc){
    numeClient=loc.numeClient;
    suprafataUtila=loc.suprafataUtila;
    discount=loc.discount;
}

///------------------------------------------------------------------------
class apartament: public locuinta{///mostenire publica
    private:
        int etaj; ///variabila pentru numarul etajului la care se afla apartamentul
        static int chirieAp;///variabila statica pentru chiria apartamentului
    public:
        apartament(string, int, float, int);///constructorul de initializare pt clasa apartament
        apartament(const apartament&);///contructorul de copiere pentru clasa apartament
        ~apartament();///destructorul pentru clasa apartament
        static int get_chirieAp();///getter pt chirieAp
        void set_etaj(int etaj);///setter pt etaj
        int get_etaj();///getter pentru etaj - metoda statica
        void citire(istream &in);///metoda de citire pt clasa apartament
        void afisare(ostream &out);///metoda de afisare pt clasa apartament
        friend istream& operator>>(istream&, apartament&);///supraincarcarea operatorului >>
        friend ostream& operator<<(ostream&, apartament&);///supraincarcarea operatorului <<
        apartament& operator=(const apartament& ap);///supraincarcarea operatorului =
        float CalculChirie(int X, bool Y);///metoda pt calculul chiriei unui apartament
};
int apartament::chirieAp=150; ///declaram variabila statica chirieAp;

///getter pt chirieAp
int apartament::get_chirieAp(){
    return chirieAp;
}
///setter pentru etaj
void apartament::set_etaj(int etaj){
    this->etaj=etaj;
}

///getter pt etaj
int apartament::get_etaj(){
    return etaj;
}

///metoda pt calculul chiriei unui apartament
float apartament::CalculChirie(int X, bool Y){
    return X*suprafataUtila*(1-Y*discount/100.0);
}

///constructorul de initializare pt clasa apartament
apartament::apartament(string numeClient="", int suprafataUtila=0, float discount=0, int etaj=0):locuinta(numeClient,suprafataUtila,discount){///apelam constructorul din baza,adica locuinta
        this->etaj=etaj; ///adaugam ce era de adaugat la clasa apartament
}

///constructorul de copiere pt clasa apartament
apartament::apartament(const apartament &cpy):locuinta(cpy){///apelam constructorul de copiere din baza,adica locuinta
        this->etaj=etaj; ///adaugam ce era de adaugat la clasa apartament
}

///destructorul pt clasa apartament
apartament::~apartament(){
    etaj=0;
}

///metoda de citire pt clasa apartament
void apartament::citire(istream &in){
    locuinta::citire(in);
    cout<<"Dati etajul la care se afla apartamentul: ";
    in>>etaj;
    cout<<"-----------------------------------------\n";
}

///metoda de afisare pt clasa apartament
void apartament::afisare(ostream &out){
    locuinta::afisare(out);
    cout<<"Etajul la care se afla apartamentul este: ";
    out<<etaj;
}

///supraincarcarea operatorului >>
istream& operator>>(istream& in,apartament& ap){
    ap.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, apartament& ap){
    ap.afisare(out);
    return out;
}

///supraincarcarea operatorului =
apartament& apartament::operator=(const apartament& ap){
    locuinta::operator=(ap);
    etaj=ap.etaj;
}

///-------------------------------------------------
class casa: public locuinta{///mostenire publica
    private:
        int suprafataCurte;///variabila pentru suprafata curtii
        static int chirieCasa;///variabila statica pt chiria casei
    public:
        casa(string, int, float, int);///constructorul pentru clasa casa
        casa(const casa&);///contructorul de copiere pentru clasa casa
        ~casa();///destructorul pentru clasa casa
        static int get_chirieCasa(); ///getter pt chirieCasa -metoda statica
        float CalculChirie(int X, bool Y); ///metoda pt calculul chiriei unui case
        void citire(istream &in);///metoda de citire pt clasa casa
        void afisare(ostream &out);///metoda de afisare pt clasa casa
        friend istream& operator>>(istream&, casa&);///supraincarcarea operatorului >>
        friend ostream& operator<<(ostream&, casa&);///supraincarcarea operatorului <<
        casa& operator=(const casa& c);///supraincarcarea operatorului =
};
int casa::chirieCasa=100; ///declaram variabila statica chirieCasa;

///getter pt chirieCasa
int casa::get_chirieCasa(){
    return chirieCasa;
}

///metoda pt calculul chiriei unui case
float casa::CalculChirie(int X, bool Y){
    return X*(suprafataUtila + 0.2*suprafataCurte)*(1-Y*discount/100.0);
}

///constructorul de initializare pt clasa casa
casa::casa(string numeClient="", int suprafataUtila=0, float discount=0, int suprafataCurte=0):locuinta(numeClient,suprafataUtila,discount){///apelam constructorul din baza,adica locuinta
        this->suprafataCurte=suprafataCurte; ///adaugam ce era de adaugat la clasa casa
}

///constructorul de copiere pt clasa casa
casa::casa(const casa &cpy):locuinta(cpy){///apelam constructorul de copiere din baza,adica locuinta
        this->suprafataCurte=suprafataCurte; ///adaugam ce era de adaugat la clasa casa
}

///destructorul pt clasa casa
casa::~casa(){
    suprafataCurte=0;
}

///metoda de citire pt clasa casa
void casa::citire(istream &in){
    locuinta::citire(in);
    cout<<"Introduceti suprafata curtii: ";
    in>>suprafataCurte;
    cout<<"-----------------------------------------\n";
}

///metoda de afisare pt clasa casa
void casa::afisare(ostream &out){
    locuinta::afisare(out);
    cout<<"Suprafata curtii: ";
    out<<suprafataCurte;
}

///supraincarcarea operatorului >>
istream& operator>>(istream& in,casa& c){
    c.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, casa& c){
    c.afisare(out);
    return out;
}

///supraincarcarea operatorului =
casa& casa::operator=(const casa& c){
    locuinta::operator=(c);
    suprafataCurte=c.suprafataCurte;
}

///----------------------------------------------------------------
class AgentieImobiliara{
    private:
        locuinta **loc;
        int nr;
    public:
        AgentieImobiliara(); ///constructor de initializare fara parametrii pt clasa AgentieImobiliara
        AgentieImobiliara(locuinta**,int); ///constructor de initializare cu paramatrii pt clasa AgentieImobiliara
        AgentieImobiliara(const AgentieImobiliara& a); /// constructor de copiere cu paramatrii pt clasa AgentieImobiliara
        ~AgentieImobiliara(); ///destructor pt clasa AgentieImobiliara
        void citire(istream &in);///metoda de citire pt clasa AgentieImobiliara
        void afisare(ostream &out);///metoda de afisare pt clasa AgentieImobiliara
        friend istream& operator>>(istream& in, AgentieImobiliara& a);///supraincarcarea operatorului >>
        friend ostream& operator<<(ostream& out,AgentieImobiliara& a);///supraincarcarea operatorului <<
        AgentieImobiliara& operator=(const AgentieImobiliara& a);///supraincarcarea operatorului =
};

AgentieImobiliara::AgentieImobiliara(){
    nr=0;
}
AgentieImobiliara::AgentieImobiliara(locuinta **loc,int numar=0){
    nr=numar;
    if (nr!=0)///am pus acest test pentru a evita alocarea memoriei de doua ori (in cazul in care nr este dat ca parametru sa se aloce memorie, iar in cazul in care nr se citeste se aloca in metoda de citire memorie)
        loc=new locuinta*[nr];
}
///constructorul de copiere pt clasa agentie
AgentieImobiliara::AgentieImobiliara(const AgentieImobiliara &cpy){
    nr=cpy.nr;
    loc=new locuinta*[nr];
    for (int i=0;i<nr;i++)
         loc[i]=cpy.loc[i];
}
///destrctorul pt clasa agentie
AgentieImobiliara::~AgentieImobiliara(){
    if(loc!=NULL)
        delete[] loc;
}

void AgentieImobiliara::citire(istream& in){
    int i;
    cout<<"Introduceti numarul de locuinte din agentie: ";
    in>>nr;
    if (nr>0)
    {
        loc=new locuinta*[nr];
        for (i=0;i<nr;)
        {
            string s;
            cout<<"\n";
            cout<<"Introduceti tipul locuintei "<<i+1<<": ";
            in>>s;
            if(s=="apartament"){
                loc[i]=new apartament; ;///upcasting
                in>>*loc[i];
                i++;
                }
            else
               if(s=="casa"){
                   loc[i]=new casa; ;///upcasting
                   in>>*loc[i];
                   i++;
                        }
               else
                   cout<<"Nu ati introdus un tip de locuinta valid. Incercati casa sau apartament.\n ";
    }}
    else
        cout<<"Nu ati introdus un numar valid de locuinte. Incercati din nou introducand un numar mai mare decat 0.";
}
void AgentieImobiliara::afisare(ostream &out){
    if(nr>0)
    {
    out<<"Agentia are urmatoarele locuinte care sunt in numar de: "<<nr<<"\n";
    for(int i=0;i<nr;i++)
    {
        out<<"\n"<<*loc[i]; ///afisez locuinta de pe pozitia i
        out<<"\n-------------------------------\n";
    }
    }

}
///supraincarcarea operatorului >>
istream& operator>>(istream& in,AgentieImobiliara& a){
    a.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, AgentieImobiliara& a){
    a.afisare(out);
    return out;
}
///supraincarcarea operatorului =
AgentieImobiliara& AgentieImobiliara::operator=(const AgentieImobiliara& a){
    loc=a.loc;
    nr=a.nr;
}

void meniu_output()
{
    cout<<"\n Dobre Adriana Lia - Proiect - Nume proiect:Clasa 'Locuinta' (Tema 7) \n";
    cout<<"\n\t\t\t\t MENIU:";
    cout<<"\n-----------------------------------------------------------------------\n";
    cout<<"\n";
    cout<<"1. Actiunea 1 din meniu:citirea si afisarea a n locuinte"; cout<<"\n";
    cout<<"2. Actiunea 2 din meniu:afisarea chiriei pentru fiecare locuinta(cu si fara discount)"; cout<<"\n";
    cout<<"3. Actiunea 3 din meniu:citirea si afisarea locuintelor dintr-o agentie imobiliara "; cout<<"\n";
    cout<<"0. Iesire."; cout<<"\n";
}
void meniu(){
    int option,n,i,val,j;
    option=0;///optiunea aleasa din meniu
    n=0;///numarul de locuinte pe care doriti sa le introduceti
    locuinta **v;///vectorul de locuinte
    AgentieImobiliara ag;

    do
    {
        meniu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {
            cout<<"Introduceti numarul de locuinte: ";
            cin>>n;
            if(n<=0)
               cout<<"Nu exista locuinte. Incercati din nou introducand un numar de locuinte mai mare decat 0.";
            else
                {
                    v=new locuinta*[n];
                    for(int i=0;i<n;)
                       {
                           string s;
                           cout<<"\n";
                           cout<<"Introduceti tipul locuintei "<<i+1<<": ";
                           cin>>s;
                           if(s=="apartament"){
                               v[i]=new apartament;///upcasting
                               cin>>*v[i];
                               i++;}
                           else
                              if(s=="casa"){
                                  v[i]=new casa; ///upcasting
                                  cin>>*v[i];
                                  i++;}
                              else
                                   cout<<"Nu ati introdus un tip de locuinta valid. Incercati casa sau apartament.\n ";
                        }
                    }
                    if(n>0)
                       {
                           cout<<"\nAfisam locuintele citite anterior:\n";
                           for(int i=0;i<n;i++)
                           {
                           cout<<"\n"<<*v[i]; ///afisez locuinta de pe pozitia i
                           cout<<"\n-------------------------------\n";
                           }}
            }

        if (option==2)
        {
            if (n>0)
                {for(int i=0;i<n;i++)
                       if(typeid(*v[i])==typeid(apartament))
                       {
                           apartament a;
                           cout<<"\n"<<*v[i]; ///afisez apartamentul de pe pozitia i
                           cout<<"\nChirie apartament fara discount: "<<v[i]->CalculChirie(a.get_chirieAp(),0);
                           cout<<"\nChirie apartament cu discount: "<<v[i]->CalculChirie(a.get_chirieAp(),1);
                           cout<<"\n--------------------------\n";
                       }
                       else
                          if (typeid(*v[i])==typeid(casa))
                       {
                           casa c;
                           cout<<"\n"<<*v[i]; ///afisez apartamentul de pe pozitia i
                           cout<<"\nChirie casa fara discout: "<<v[i]->CalculChirie(c.get_chirieCasa(),0);
                           cout<<"\nChirie casa cu discout: "<<v[i]->CalculChirie(c.get_chirieCasa(),1);
                           cout<<"\n-------------------------------\n";
                       }


                }
            else
                cout<<"Nu a fost introdusa nicio locuinta. Pentru a introduce locuinte apasati tasta 1.";
        }
        if (option==3)
            {
                cout<<"Se vor citi locuintele unei agentii:\n";
                cin>>ag;
                cout<<ag;
            }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }while(option!=0);
}
int main()
{
    meniu();
    return 0;
}

