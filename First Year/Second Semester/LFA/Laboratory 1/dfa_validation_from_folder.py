"""Dobre Adriana Lia, Guțu Ștefania Alexandra, Pirlogea Luciana Elena, grupa 141
~ Lab 1 - ex 2 - validation files from folder~
Implement a library/program in a programming language of your choosing to load and validate an input file.
Sections can be in any order. By validation we ask to check that transition section has valid states (first and third word)
and valid words (word two). Note that states can be succeeded by ”F”, ”S”, both or nothing. ”S” symbol can succeed only one state.
-scrieți un alt script care primește ca parametru un folder enumeră toate fișierele din folderul respectiv și pentru fiecare nume
de fișier apelează metoda de la puctul 1. Scriptul să afișeze ceva de genul: c:\docume....\file1.txt -> ok, c:\docume....\file1.txt -> ko, etc... -"""

import glob
import sys
import os.path
from os import path


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


def get_dfa_from_file(file_name):
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


# functie care enumera si valideaza fisierele dintr-un folder dat
def folder_files(path):
    for file in glob.glob(os.path.join(path, '*')):
        print(os.path.join(os.getcwd(), file), end=" -> ")
        l_sigma, l_state, l_trans, validation_message = get_dfa_from_file(file)
        if validation_message != "Valid config file":  # se afiseaza eroarea gasita
            print("Status:", validation_message)
        else:
            print("Status:", validation_message)


folder_files(sys.argv[1])
