## Proiectul 1

**Tema 7. Clasa "Lista_dublu_inlantuita"**

Se consideră **Class Nod{ int info; Nod* prev, next;}*
- constructori de inițializare și parametrizati pentru clasa Nod;
- destructor pentru clasa Nod;

Clasa Lista_dublu_inlantuita are:
- doi membri privați "Nod*" reprezentând primul și ultimul element;
- metoda publică de adăugare a unui element pe o poziție;
- supraîncărcarea operatorului >>, realizată prin utilizarea succesivă a metodei declarată anterior;
- supraîncărcarea operatorului << pentru afișarea listei în ambele sensuri, în aceeasi funcție;
- metoda publică de ștergere a unui element de pe o poziție;
- supraîncărcarea operatorului +, care să efectueze concatenarea a două liste dublu inlănțuite, 
rezultând într-o nouă listă dublu înlănțuită.

## Proiectul 2

**Tema 7.**

Se dau clasele:
-Locuință (string numeClient, int suprafataUtila, float discount)
-Apartament (int etaj) : Locuinta
-Casa (int suprafataCurte) : Locuinta
La clasa Locuinta se va adăuga metoda virtuală pură CalculChirie (X,Y) cu X = valoare standard
chirie/mp(intreg), Y=1 dacă se ia în considerare discountul și 0 dacă nu se ia în considerare.
Metoda va fi adăugata în clasa Apartament după formula X*suprafataUtila*(1-Y*discount/100.0),
respectiv in clasa Casa dupa formula X*(suprafataUtila + 0.2*suprafataCurte) * (1-Y*discount/100.0).
Metodele vor fi testate prin parcurgerea unui vector de pointeri la Locuinta *, încărcat cu obiecte de
tip Apartament și Casa.
Se definește clasa AgentieImobiliara conținând un vector de pointeri la obiecte de tip Locuinta alocat
dinamic. Se va supraîncărca operatorul >> pentru a citi locuințele agenției și operatorul << pentru
afișarea lor.

## Proiectul 3

**Tema 11**

A) Să se proiecteze și implementeze obiectual o aplicație de gestiune a resurselor umane pentru un grup de **Companii**. Gestionarea se va realiza prin intermediul unui gestionar numit **HRManager**. Se vor avea în vedere următoarele caracteristici :
- Companiile dețin o serie de departamente de lucru (ex: "derulare proiecte", "financiar", "IT", ...) 
- Companiile au o serie de angajați, distribuiți pe departamente, unii dintre aceștia având funcția de manageri pentru alți angajați. Fiecare angajat poate avea cel mult un manager. 
- Aplicația trebuie să poată gestiona pe lângă numele angajaților și informații cum ar fi data de angajare în companie și salariul lunar brut al fiecărui angajat. 
- Se vor realiza interfețe prin care să se poată adăuga/șterge departamente sau angajați din companie precum și companii din gestionarul de companii. 
- Aplicația trebuie să poată furniza următoarele rapoarte:
  - Numărul de angajați ai unui companie/departament dat 
  - Cheltuielile salariale lunare totale existente la nivelul unei companii
  - Numele, data de angajare și salariul angajaților care au funcția de manageri precum și lista de angajați care le sunt subordonați, la nivelul unei companii
  - Lista departamentelor care au minim n angajați (n transmis că parametru). 
- Trebuie să existe posibilitatea de fuzionare a două companii (se va defini un operator + care realizează acest lucru, precum și o metodă la nivelul gestionarului). Departamentele comune vor fuziona într-unul singur. La fuzionare toți managerii își păstrează funcția. 
- La adăugarea unei companii în gestionar trebuie să se verifice dacă acea companie nu există deja acolo. O companie este identică cu altă dacă are același nume și aceeași schemă de deparatamente și angajați. 

B) Pornind de la modelul proiectat mai sus, să se adauge posibilitatea de lucru cu companii care beneficiază de scutire de impozit (dețin departamente cu scutire de impozit (16%)). Acolo cheltuielile salariale sunt diminuate.

C) Toate problemele și situațiile deosebite se vor trata prin intermediul mecanismului de excepții. Exemple de probleme: încercarea de adăugare a unei companii în gestionar, în condițiile în care ea deja există acolo, încercarea de ștergere a unei entități (companie, departament, angajat) care nu există, alocări nereușite de memorie, etc. Obs: se vor folosi cât se poate de mult mecanismele ce țin de tehnicile de programare obiectuală : incapsularea, derivarea și polimorfismul bazat pe supraincarare de operatori și funcții virtuale


