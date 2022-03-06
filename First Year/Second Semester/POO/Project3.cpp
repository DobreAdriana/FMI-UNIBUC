#include<iostream>
#include <stdlib.h>
#include <string.h>
#include <list>
using namespace std;
class angajat{
    protected:
        string nume_ang;
        string data_angajarii;
        double salariu;
        bool manager;
    public:
        angajat(string,string,double,bool); ///constructorul de initializare pt clasa angajat
        angajat(const angajat&); ///constructorul de copiere pt clasa angajat
        virtual ~angajat(); ///destructorul virtual pt clasa angajat
        virtual void citire (istream &in); ///metoda virtuala de citire pt clasa angajat
        virtual void afisare(ostream &out); ///metoda virtuala de scriere pt clasa angajat
        friend istream& operator>>(istream&, angajat&); ///supraincarcarea operatorului >>
        friend ostream& operator<<(ostream&, angajat&); ///supraincarcarea operatorului <<
        angajat& operator=(const angajat& ang);///supraincarcarea operatorului =
};

///constructorul de initializare pt clasa angajat
angajat::angajat(string n="",string data="",double s=0,bool m=0){
    nume_ang=n;
    data_angajarii=data;
    salariu=s;
    manager=m;
}

///constructorul de copiere pt clasa angajat
angajat::angajat(const angajat &cpy){
    nume_ang=cpy.nume_ang;
    data_angajarii=cpy.data_angajarii;
    salariu=cpy.salariu;
    manager=cpy.manager;
}

///destructorul virtual pt clasa angajat
angajat::~angajat(){
    nume_ang="";
    data_angajarii="";
    salariu=0;
    manager=0;
}

///supraincarcarea operatorului >>
istream& operator>>(istream& in,angajat& ang){
    ang.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, angajat& ang){
    ang.afisare(out);
    return out;
}

///supraincarcarea operatorului =
angajat& angajat::operator=(const angajat& ang){
    nume_ang=ang.nume_ang;
    data_angajarii=ang.data_angajarii;
    salariu=ang.salariu;
    manager=ang.manager;
}

///metoda virtuala de citire pt clasa angajat
void angajat::citire(istream &in){
    cout<<"Introduceti numele angajatul: ";
    in.get();
    getline(in,nume_ang);
    cout<<"Introduceti data angajarii: ";
    in.get();
    getline(in,data_angajarii);
    cout<<"Introduceti salariu lunar brut: ";
    in>>salariu;
    cout<<"Angajatul este manager? 1/0 :";
    in>>manager;
}

///metoda virtuala de scriere pt clasa angajat
void angajat::afisare(ostream &out){
    out<<"Numele angajatului: "<<nume_ang<<"\n";
    out<<"Data angajarii: "<<data_angajarii<<"\n";
    out<<"Salariu lunar brut: "<<salariu<<"\n";
    if(manager==1)
       out<<"Angajatul este manager"<<"\n";
}

class angajat_avantajat:public angajat{
    private:
        bool scutire_impozit;
        static int impozit;
    public:
       angajat_avantajat(string, string, double, bool, bool); ///constructorul de initializare pt clasa angajat_avantajat
       angajat_avantajat(const angajat_avantajat&); ///constructorul de copiere pt clasa angajat_avantajat
       ~angajat_avantajat(); ///destructorul pt clasa angajat_avantajat
       static int get_impozit();///getter pt impozit
       void set_scutire_impozit(bool scutire_impozit);
       int get_scutire_impozit() const;
       void citire (istream &in); ///metoda de citire pt clasa angajat_avantajat
       void afisare(ostream &out); ///metoda de scriere pt clasa angajat_avantajat
       friend istream& operator>>(istream&, angajat_avantajat&); ///supraincarcarea operatorului >>
       friend ostream& operator<<(ostream&, angajat_avantajat&); ///supraincarcarea operatorului <<
       angajat_avantajat& operator=(const angajat_avantajat& ang);///supraincarcarea operatorului =
       float CalculSalariu();///metoda pt calculul salariului unui angajat

};
int angajat_avantajat::impozit=16; ///declaram variabila statica impozit;

void angajat_avantajat::set_scutire_impozit(bool scutire_impozit){
    this->scutire_impozit=scutire_impozit;
}

int angajat_avantajat::get_scutire_impozit() const{
    return scutire_impozit;
}

///getter pt impozit;
int angajat_avantajat::get_impozit(){
    return impozit;
}

///metoda pt calculul salariului unui angajat
float angajat_avantajat::CalculSalariu(){
    return salariu-salariu*impozit*scutire_impozit/100;
}

///constructorul de initializare pt clasa angajat_avantajat
angajat_avantajat::angajat_avantajat(string nume_ang="", string data_angajarii="", double salariu=0, bool manager=0, bool scutire=0):angajat(nume_ang,data_angajarii, salariu, manager){///apelam constructorul din clasa de baza, adica angajat
    scutire_impozit=scutire;
}

///constructorul de copiere pt clasa angajat_avantajat
angajat_avantajat::angajat_avantajat(const angajat_avantajat &cpy):angajat(cpy){///apelam constructorul de copiere din clasa de baza, adica angajat
    scutire_impozit=cpy.scutire_impozit;
}

///destructorul pt clasa angajat_avantajat
angajat_avantajat::~angajat_avantajat(){
    scutire_impozit=0;
}

///supraincarcarea operatorului >>
istream& operator>>(istream& in,angajat_avantajat& ang){
    ang.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, angajat_avantajat& ang){
    ang.afisare(out);
    return out;
}

///supraincarcarea operatorului =
angajat_avantajat& angajat_avantajat::operator=(const angajat_avantajat& ang){
    angajat::operator=(ang);
    scutire_impozit=ang.scutire_impozit;
}

///metoda de citire pt clasa angajat_avantajat
void angajat_avantajat::citire(istream &in){
    angajat::citire(in);
    cout<<"Este angajatul scutit de impozit? 1/0 :";
    in>>scutire_impozit;
}

///metoda de scriere pt clasa angajat_avantajat
void angajat_avantajat::afisare(ostream &out){
    angajat::afisare(out);
    if(scutire_impozit==1)
        out<<"Angajatul este scutit de impozit.";
    else
        out<<"Angajatul nu este scutit de impozit.";

}

class departament{
    private:
         angajat_avantajat *ang;
         string nume_dep;
         int nra;
         double SalariiDep;
    public:
        departament();
        departament(angajat_avantajat *, string, int ,double); ///constructorul de initializare pt clasa departament
        departament(const departament&); ///constructorul de copiere pt clasa departament
        ~departament(); ///destructorul pt clasa departament
        void set_SalariiDep(double SalariiDep);
        int get_SalariiDep();
        void set_nra(int nra);///setter pt nra
        int get_nra();///getter pt nra
        void adaugare_angajat(angajat_avantajat a);
        void citire (istream &in); ///metoda de citire pt clasa departament
        void afisare(ostream &out); ///metoda de scriere pt clasa departament
        friend istream& operator>>(istream&, departament&); ///supraincarcarea operatorului >>
        friend ostream& operator<<(ostream&, departament&); ///supraincarcarea operatorului <<
        departament& operator=(const departament& dep);///supraincarcarea operatorului =
};
void departament::adaugare_angajat(angajat_avantajat a){
    ///nra=nra+1;
    ///a = new angajat_avantajat;
    ///ang[nra]=a;
}
///setter pt SalariiDep
void departament::set_SalariiDep(double SalariiDep){
   this->SalariiDep=SalariiDep;
}

///getter pt SalariiDep
int departament::get_SalariiDep(){
    return SalariiDep;
}

///setter pt nra
void departament::set_nra(int nra){
    this->nra=nra;
}

///getter pt nra
int departament::get_nra(){
    return nra;
}

departament::departament(){
    nume_dep="";
    nra=0;
    SalariiDep=0;
}
///constructorul de initializare pt clasa departament
departament::departament(angajat_avantajat *a,string nume="", int nr=0,double s=0){
        nra=nr;
        SalariiDep=s;
        if(nra!=0) ///am pus acest test pentru a evita alocarea memoriei de doua ori
             ang=new angajat_avantajat[nra];
        nume_dep=nume;
}

///constructorul de copiere pt clasa departament
departament::departament(const departament &cpy){
    nume_dep=cpy.nume_dep;
    nra=cpy.nra;
    SalariiDep=cpy.SalariiDep;
    ang=new angajat_avantajat[nra];
    for (int i=0;i<nra;i++)
       ang[i]=cpy.ang[i];
}

///destructorul pt clasa departament
departament::~departament(){
    nume_dep="";
    SalariiDep=0;
    nra=0;
    if (ang!=NULL)
         delete[] ang;
}

///supraincarcarea operatorului >>
istream& operator>>(istream& in,departament& dep){
    dep.citire(in);
    return in;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, departament& dep){
    dep.afisare(out);
    return out;
}

///supraincarcarea operatorului =
departament& departament::operator=(const departament& dep){
    nume_dep=dep.nume_dep;
    nra=dep.nra;
    ang=dep.ang;
    SalariiDep=dep.SalariiDep;
}

///metoda de citire pt clasa departament
void departament::citire(istream &in){
    int i;
    cout<<"Introduceti numele departamentului: ";
    in.get();
    getline(in,nume_dep);
    cout<<"Introduceti numarul de angajati din departament: ";
    in>>nra;
    if (nra>0)
    {
        ang=new angajat_avantajat[nra];
        for (i=0;i<nra;)
            {
                cout<<"Cititi angajatul "<<i+1<<"\n";
                in>>ang[i];
                SalariiDep=SalariiDep+ang[i].CalculSalariu();
                i++;
                cout<<"\n";
            }

    }
}

///metoda de afisare pt clasa departament
void departament::afisare(ostream &out){
    out<<"Numele departamentului: "<<nume_dep<<"\n";
    if(nra>0)
    {
        out<<"Angajatii departamentului sunt: "<<"\n";
        for(int i=0;i<nra;i++)
    {
        out<<"\n"<<ang[i]; ///afisez angajatul de pe pozitia i
        out<<"\n-------------------------------\n";
    }
    out<<"Salariile "<<SalariiDep<<"\n";
    }
}

class companie{
    private:
        int id_comp;
        departament *dep;
        string nume_comp;
        int nrd;
        int contor;
        double cost;
    public:
        companie();/// ///constructor de initializare fara parametrii pt clasa companie
        companie(int, departament *, string, int,int,double); ///constructorul de initializare cu parametrii pt clasa companie
        companie(const companie&); ///constructorul de copiere pt clasa companie
        ~companie(); ///destructorul pt clasa companie
        void set_contor(int contor);///setter pt contor;
        int get_contor();///getter pt contor;
        void set_cost(double cost);///setter pt cost
        int get_cost();///getter pt cost
        void citire (istream &in); ///metoda virtuala de citire pt clasa companie
        void afisare(ostream &out); ///metoda virtuala de scriere pt clasa companie
        friend istream& operator>>(istream&, companie&); ///supraincarcarea operatorului >>
        friend ostream& operator<<(ostream&, companie&); ///supraincarcarea operatorului <<
        companie& operator=(const companie& comp);///supraincarcarea operatorului =
        void Nangajati(int n);///lista departamentelor care au minim n angajati
        void concat(const companie& c1,const companie& c2);
        friend companie& operator+(const companie& c1, const companie& c2);
};
void companie::Nangajati(int n){
  if(nrd!=0)
    for(int i=0;i<nrd;i++)
    {
        if(n<=dep[i].get_nra())
           cout<<"Departamentul "<<i<<"\n";
           cout<<dep[i]<<"\n";
    }
}
///setter pt contor
void companie::set_contor(int contor){
    this->contor=contor;
}

///getter pt contor
int companie::get_contor(){
    return contor;
}

///setter pt cost
void companie::set_cost(double cost){
    this->cost=cost;
}

///getter pt cost
int companie::get_cost(){
    return cost;
}

companie::companie(){
    nrd=0;
    nume_comp="";
    id_comp=0;
    contor=0;
    cost=0;
}
///constructorul de initializare pt clasa companie
companie::companie(int id, departament *dep , string n , int nr,int c,double sal){
    id_comp=id;
    nrd=nr;
    nume_comp=n;
    contor=c;
    cost=sal;
    if(nr!=0) ///am pus acest test pentru a evita alocarea memoriei de doua ori
       dep=new departament[nrd];
}

///constructorul de copiere pt clasa companie
companie::companie(const companie &cpy){
    id_comp=cpy.id_comp;
    nume_comp=cpy.nume_comp;
    nrd=cpy.nrd;
    contor=cpy.contor;
    cost=cpy.cost;
    dep=new departament[nrd];
    for (int i=0;i<nrd;i++)
       dep[i]=cpy.dep[i];
}

///destructorul pt clasa companie
companie::~companie(){
    id_comp=0;
    contor=0;
    nume_comp="";
    nrd=0;
    cost=0;
    if (dep!=NULL)
        delete[]dep;
}
void companie::concat(const companie& c1, const companie &c2){


}
companie& operator+(const companie& c1,const companie& c2){
    companie *c= new companie;
    c->concat(c1,c2);
    return *c;
}
///supraincarcarea operatorului >>
istream& operator>>(istream& in,companie& comp){
    comp.citire(in);
    return in;
}

///supraincarcarea operatorului =
companie& companie::operator=(const companie& comp){
    id_comp=comp.id_comp;
    nume_comp=comp.nume_comp;
    nrd=comp.nrd;
    dep=comp.dep;
    cost=comp.cost;
    contor=comp.contor;
}

///supraincarcarea operatorului <<
ostream& operator<<(ostream& out, companie& comp){
    comp.afisare(out);
    return out;
}

///metoda de citire pt clasa companie
void companie::citire(istream &in){
    cout<<"Introduceti numarul companiei: ";
    in>>id_comp;
    cout<<"Introduceti numele companiei: ";
    in.get();
    getline(in,nume_comp);
    cout<<"Introduceti numarul de departamente din companie: ";
    in>>nrd;
    if(nrd>0)
    {
        dep=new departament[nrd];
        for(int i=0;i<nrd;)
        {
            cout<<"Cititi departamentul "<<i+1<<"\n";
                in>>dep[i];
                contor=contor+dep[i].get_nra();
                i++;
                cost=cost+dep[i].get_SalariiDep();
                cout<<"\n";
            }

    }
}


///metoda de afisare pt clasa companie
void companie::afisare(ostream &out){
    out<<"Compania "<<id_comp<<"\n";
    out<<"Numele companiei: "<<nume_comp<<"\n";
    out<<"Departamentele companiei sunt: "<<"\n";
        for(int i=0;i<nrd;i++)
    {
        out<<"\n"<<dep[i]; ///afisez departamentul de pe pozitia i
        out<<"\n-------------------------------\n";
    }
}


template <class t> class HRManager{
    private:
         t *v;
         int nr;
    public:
    HRManager(t *p=NULL, int n=0)
    {
        nr=n;
        v=new t[n];
        for(int i=0;i<n;i++)
        {
            v[i]=p[i];
        }
    }
    HRManager(HRManager &a)
    {
        nr=a.nr;
        v=new t[nr];
        for(int i=0;i<nr;i++)
        {
            v[i]=a.v[i];
        }
    }
    ~HRManager()
    {
        delete [] v;
    }

    int get_nr() {return nr;}
    t get_v(int i) {return v[i];}
    friend istream& operator >>(istream &in, HRManager <t> &g)
    {
        cout<<"Introduceti numarul de companii: ";
        in>>g.nr;
        g.v=new t[g.nr];
        cout<<"Introduceti companiile: \n";
        for(int i=0;i<g.nr;i++){
           in>>g.v[i];
           cout<<"\n";
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, HRManager<t> &g)
    {
        out<<"Se gasesc urmatoarele "<<g.nr<<" companii:"<<"\n";
        for(int i=0;i<g.nr;i++)
            {out<<g.v[i]<<"\n";
            out<<"Cheltuielile salariale lunare totale existente la nivelul companiei sunt: "<<g.v[i].get_cost()<<"\n";
            out<<"Numarul total de angajati ai companiei este: "<<g.v[i].get_contor();
            cout<<"\n";
            cout << "---------------------------------------------------------------\n";
            }
        return out;
    }

};

void menu_output()
{
    cout<<"\n Dobre Adriana Lia - Proiect 3- Tema 11 \n";
    cout<<"\n Gestiunea unor companii\n";
    cout<<"\n\t\tMENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste informatii despre companiile implicate. --- UPCAST & LATE-BINDING";
    cout<<"\n";
    cout<<"2. Gestionare --- TEMPLATE (companie).";
    cout<<"\n";
    cout<<"3. Introduceti o lista de angajati si afisarea celor cu scutire de impozit";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}

void menu()
{
    int option;///optiunea aleasa din meniu
    option=0;///optiunea aleasa
    int n=0;
    int na=0;
    companie *v;
    do
    {
        menu_output();
        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>option;
        if (option==1)
        {
            cout<<"Introduceti numarul de companii pe care doriti sa le cititi: ";
            cin>>n;
            v=new companie[n];
            if (n>0)
            {
                for(int i=0;i<n;i++)
                    cin>>v[i];
                cout<<"\nAfisam companiile citite anterior:\n";
                for(int i=0;i<n;i++)
                   {
                        cout<<"\n"<<v[i];
                        cout<<"--------------------------\n";
                   }
            }
            else
                cout<<"Numarul introdus trebuie sa fie pozitiv.\n";
        }
        if (option==2)
        {
            HRManager <companie> x;
            cin>>x;
            cout<<x;
        }
        if(option==3)
        {
            int cimp=0;
            int avant=0;
            list < angajat_avantajat > FaraImpozit; ///folosesc list din stl
            cout<<"Introduceti un numar de angajati:";
            cin>>na;
            for(int i=0;i<na;)
                {
                    string s;
    cout<<"\n";
    cout<<"Introduceti postul personalului "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="angajat")
        {
                angajat *p=new angajat;
                cin>>*p;
                i++;
                cimp++;
        }
        else
            if(s=="angajat_avantajat")
            {
                angajat_avantajat *p=new angajat_avantajat;
                cin>>*p;
                i++;
                angajat *a1=dynamic_cast<angajat*>(p);
                if (a1 && p->get_scutire_impozit()==1)
                   {
                       avant++;
                       FaraImpozit.push_back(*p);
                   }
                else
                   cimp++;
            }
            else
                throw 10;
    }
    catch (bad_alloc var)
    {
        cout << "Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un post valid. Incercati angajat sau angajat_avantajat.\n ";
    }
    }
    cout << "---------------------------------------------------------------\n";
    cout<<"In lista introdusa la punctul 3 se afla: \n";
    cout<<"- "<<cimp<<" angajati fara scutire de impozit \n";
    cout<<"- "<<avant<<" angajati cu scutire de impozit \n";
    cout << "---------------------------------------------------------------\n";
    cout<<"Angajatii cu scuture de impozit sunt: \n";
    list<angajat_avantajat>::iterator i; ///Creez un iterator
	cout << "---------------------------------------------------------------\n";
	for (i = FaraImpozit.begin(); i != FaraImpozit.end(); ++i) { ///De la inceputul listei pana la final, parcurg si afisez continutul iteratorului
		cout << (*i)<<endl;
        cout << "---------------------------------------------------------------\n";

	}
        }
        if (option==0)
        {
            cout<<"\nEXIT\n\n";
        }
        if (option<0||option>4)
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
    menu();
    return 0;
}
