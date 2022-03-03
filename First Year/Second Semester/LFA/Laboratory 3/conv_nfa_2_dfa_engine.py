"""Dobre Adriana Lia, Guțu Ștefania Alexandra, Pirlogea Luciana Elena, grupa 141
Implement a library/program in a programming language of your
choosing that creates a NFA and convert it to a DFA. Use your library from lab
1 to generate the NFA based on input file. Allow command line arguments to
your program in the form:
c o n v n f a 2 d f a e n g i n e . py   n f a c o n f i g f i l e    c o n v e r t e d d f a c o n f i g f i l e"""

import sys


def get_section(name, l_s):
    mark_1 = False  # initial plecam cu fals pana identificam sectiunea
    l_ret = []  # lista solutie returnata
    for line in l_s:
        if name + ":" == line:  # identifica elementele dfa-ului
            mark_1 = True  # marcam cu true
            continue
        if line == "end":  # capat de sectiune => marcam cu fals
            mark_1 = False
        if mark_1 == True:  # mark_1 = true => ne aflam in interiorul sectiunii si adaugam fiecare element al ei in lista solutie
            l_ret.append(line)
    return l_ret


def get_nfa_from_file(file_name):
    l_sigma = []  # lista pentru alfabet
    l_state_ex = []  # lista pentru stari(+daca este finala si de inceput)
    l_trans = []  # lista pentru tranzitii
    l_s = []  # lista pentru citirea fisierului
    try:
        f = open(file_name)
        for s in f:
            s = s.strip().lower()  # eliminam spatiile si convertim toate literele in litere mici
            if "#" not in s:
                l_s.append(s)  # adaugam linia in lista daca nu este comentariu
        l_sigma = get_section("sigma", l_s)  # se apeleaza pentru a se obtine lista pentru alfabet
        l_state = get_section("states", l_s)  # se apeleaza pentru a se obtine lista pentru stari
        l_trans = get_section("transitions", l_s)  # se apeleaza pentru a se obtine lista pentru tranzitii

        for s in l_state:
            is_final_state = 0
            is_start_state = 0

            tmp1 = s.split(",")

            for entry in tmp1[1:]:  # pentru fiecare stare verificam daca e stare de start sau stare finala
                if entry == "s":  # este stare de start
                    is_start_state = 1
                if entry == "f":  # este stare de final
                    is_final_state = 1
            l_state_ex.append([tmp1[0], is_start_state,
                               is_final_state])  # l_state_ex va reprezenta lista starilor alaturi de proprietatea de stare de start sau de final

        l_state = []  # punem in l_state doar starile dfa-ului(fara proprietati)
        for s in l_state_ex:
            l_state.append(s[0])

        # validare tranzitii
        c = 0  # c = nr de tranzitii

        for t in l_trans:
            t = t.split(",")
            if t[0] in l_state and t[1] in l_sigma and t[
                2] in l_state:  # verificam pentru fiecare element din tranzitia curenta daca se afla in multimea de stari sau in alfabet
                c = c + 1
        message = "Unknown error"
        if len(l_sigma) > 0 and len(l_state) > 0 and len(l_trans) > 0 and c == len(
                l_trans):  # daca numarul tranzitiilor valide este egal cu numarul initial de tranzitii => fisierul de intrare este valid
            message = "Valid config file"
        else:
            if len(l_sigma) == 0 and len(l_state) == 0 and len(l_trans) == 0:  # daca lipsesc mai multe sectiuni
                message = "All sections are missing"
            else:
                if len(l_sigma) == 0 or len(l_state) == 0 or len(l_trans) == 0:  # daca o sectiune este vida
                    message = "One section is missing"
                else:
                    if len(l_trans) != c:  # daca contine tranzitii nevalide
                        message = "The transitions contain errors"
        f.close()
        return l_sigma, l_state_ex, l_trans, message
    except FileNotFoundError:
        message = "The file does not exist"  # daca fisierul dat nu exista
        return l_sigma, l_state_ex, l_trans, message


def nfa_to_dfa(l_sigma, l_state, l_trans):
    l_states_dfa = [[l_state[0][0]]]  # starile dfa-ului
    l_trans_dfa = []  # tranzitiile dfa-ului
    start_state = l_state[0][0]  # starea de start a dfa-ului
    final_states = []  # starile de final ale dfa-ului
    for state in l_states_dfa:  # pentru fiecare stare noua a dfa-ului
        for c in l_sigma:  # pentru fiecare simbol din alfabet
            l_new_trans = []  # luam o lista auxiliara in care punem starile in care ajungem plecand din toate starile din state(care este o lista de stari)
            for l in state:  # pentru fiecare stare din starea noua a dfa-ului
                for t in l_trans:  # pentru fiecare tranzitie a nfa-ului care verifica conditiile de mai jos
                    t = t.split(",")
                    if t[1] == c and l == t[0]:
                        l_new_trans.append(t[2])  # punem in lista auxiliara starea urmatoare
            l_trans_dfa.append([state, c, l_new_trans])  # punem tranzitiile dfa-ului
            if l_new_trans not in l_states_dfa:  # daca noua stare nu a mai fost gasita pana acum, se adauga in lista de stari a dfa-ului
                l_states_dfa.append(l_new_trans)
    for state in l_states_dfa:  # identificam starile de final ale dfa-ului
        for l in state:
            for state2 in l_state:
                if l == state2[0] and state2[2] == 1:
                    final_states.append(state)  # si le adaugam in final_states
    f = sys.argv[2]
    file2 = open(f, "w")
    file2.write("Sigma: \n")
    for character in l_sigma:
        file2.write("\t")
        file2.write(character)  # afisam alfabetul dfa-ului
        file2.write("\n")
    file2.write("End \n")
    file2.write("States: \n")
    for state in l_states_dfa:  # afisam starile dfa-ului
        state_aux = "q"
        for s in state:
            state_aux = state_aux + s[1]
        if state_aux == start_state:
            state_aux = state_aux + ",s"
        if state in final_states:
            state_aux = state_aux + ",f"
        file2.write("\t")
        file2.write(state_aux)
        file2.write("\n")
    file2.write("End \n")
    file2.write("Transitions: \n")
    for transition in l_trans_dfa:  # afisam tranzitiile dfa-ului
        file2.write("\t")
        state_aux = "q"
        for s in transition[0]:
            state_aux = state_aux + s[1]
        file2.write(state_aux)
        file2.write(",")
        file2.write(transition[1])
        file2.write(",")
        state_aux = "q"
        for s in transition[2]:
            state_aux = state_aux + s[1]
        file2.write(state_aux)
        file2.write("\n")
    file2.write("End \n")


file = sys.argv[1]
l_sigma, l_state, l_trans, validation_message = get_nfa_from_file(file)
if validation_message != "Valid config file":  # se afiseaza eroarea gasita
    print("Status:", validation_message)
else:
    print("Status:", validation_message)
    print(l_sigma)
    print(l_state)
    print(l_trans)
    nfa_to_dfa(l_sigma, l_state, l_trans)
