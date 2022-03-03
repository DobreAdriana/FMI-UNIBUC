"""Dobre Adriana Lia, Guțu Ștefania Alexandra, Pirlogea Luciana Elena, grupa 141
~ Lab 4.2 ~
Implement a library/program in a programming language of your choosing to load and validate a CFG configuration file.
Implement a library/program that creates a CFG given an input config file.
Create and test configuration file using the above engine for CFGs presented in 2.4(Sipser - Chapter 2)
"""
import sys


def get_members(name, l_m):
    ok = 0
    list_sol = []
    for line in l_m:  # identificam sectiunea
        if name + ":" == line:  # verificam numele sectiunii
            ok = 1
            continue
        if line == "End":  # final de sectiune
            ok = 0
        if ok == 1:  # adaugam elementele dintr-o sectiune
            list_sol.append(line)
    return list_sol


def cfg_config_file(file_name):
    f = open(file_name)
    l_m = []
    for line in f:
        line = line.strip()
        l_m.append(line)
    l_variables = get_members("Variables", l_m)  # lista de variabile
    l_terminals = get_members("Terminals", l_m)  # lista de terminale
    l_rules = get_members("Rules", l_m)  # lista de reguli
    start_state = l_rules[0][0]  # varibila de start
    error = 0;
    for rule in l_rules:  # validare reguli
        if error == 0:
            aux = rule.split(",")
            for letter in range(len(aux)):
                if letter == 0 and aux[letter] not in l_variables:
                    error = 1
                    print("Status: The file contains a wrong variable")
                    break
                if (letter > 0 and aux[letter] not in l_variables) and (letter > 0 and aux[letter] not in l_terminals):
                    error = 1
                    print("Status: The file contains wrong terminal or variable")
                    break
    if error == 0:
        print("Status: Valid config file")
    return error, l_variables, l_terminals, l_rules, start_state


file = sys.argv[1]
error, l_variables, l_terminals, l_rules, start_state = cfg_config_file(file)

words = []  # lista de cuvinte
productions = {}  # dictionarul de productii(reguli)
for rule in l_rules:
    rule = rule.split(",")
    if rule[0] not in productions.keys():
        productions[rule[0]] = ["".join(rule[1:])]
    else:
        productions[rule[0]].append("".join(rule[1:]))


# verifica daca un simbol este terminal sau neterminal
def is_terminal(symbol):
    global l_terminals

    for i in range(0, len(l_terminals)):
        if l_terminals[i] == symbol: return 1

    return 0


# verifica daca un cuvant a mai fost generat in trecut
def old_word(symbols):
    for i in range(0, len(words)):
        if symbols == words[i]: return 1

    return 0


# verifica daca un cuvant contine doar terminale
def is_word(symbols):
    for i in range(0, len(symbols)):
        if not is_terminal(symbols[i]): return 0
    return 1


# max_length = numarul maxim de simboluri dintr-un cuvant
def generate(symbols, max_length):
    global productions
    global words

    # daca depaseste numarul maxim de simboluri, se opreste generarea
    if len(symbols) > max_length: return

    # se adauga noi cuvinte
    if is_word(symbols) and not old_word(symbols):
        symbols = symbols.replace("l", "")  # inlocuim l(lambda) cu sirul vid
        words.append(symbols)

    for i in range(0, len(symbols)):

        # trece peste simbol daca este terminal (din moment ce nu este nimic de inlocuit)
        if is_terminal(symbols[i]): continue

        for j in productions:

            if symbols[i] == j:
                for k in range(0, len(productions[j])):
                    temp = symbols[0:i] + productions[j][k] + symbols[i + 1: len(symbols)]
                    generate(temp, max_length)  # concatenam pentru a obtine noul cuvant


if error == 0:  # daca fisierul de configurare este valid
    print("Starea de start este: ", start_state)
    print("Variabilele sunt: ", l_variables)
    print("Terminalele sunt: ", l_terminals)
    print("Regulile sunt: ", productions)
    generate(start_state, 8)  # generam cuvinte de lungime maxim 8
    for i in range(len(words) - 1, -1, -1):  # afisare in ordine inversa
        print(words[i])
    print(len(words))  # afisam numarul de cuvinte generate
