"""Dobre Adriana Lia, Guțu Ștefania Alexandra, Pirlogea Luciana Elena, grupa 141
2. Implement a library/program in a programming language of your choosing to load and validate a configuration
file of a TM with two heads and one tape. Also implement a simulator for this type of TM"""

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


def TM_config_file(file_name):
    f = open(file_name)
    l_m = []
    for line in f:
        line = line.strip()
        l_m.append(line)
    l_states = get_members("states", l_m)
    l_sigma = get_members("sigma", l_m)
    l_gamma = get_members("gamma", l_m)
    l_transitions = get_members("transitions", l_m)
    l_special_states = get_members("special_states", l_m)
    error = 0
    message = "valid config file"
    # verificare incluziune alfabet
    for caracter in l_sigma:
        if caracter not in l_gamma:  # verificam daca sigma este in gamma
            error = 1
            message = "wrong alphabet"
            return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
    # verificare tranzitii
    for transition in l_transitions:
        error = 0
        transition = transition.split(",")
        if len(transition) == 4:  # tranzitia are lungimea 4 => nu punem niciun simbol pe banda
            if transition[0] not in l_states or transition[1] not in l_states:  # verificam existenta starilor din tranzitie
                error = 1
                message = "wrong transition, the introduced states do not exist"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
            heads_symbols = transition[2].split("/")
            if heads_symbols[0] not in l_gamma or heads_symbols[1] not in l_gamma:  # verificam existenta simbolurilor corespunzatoare capetelor in alfabetul benzii
                error = 1
                message = "wrong transition, the introduced symbols does not exist in the tape's alphabet"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
            heads_directions = transition[3].split("/")
            if (heads_directions[0] != 'R' and heads_directions[0] != 'L' and heads_directions[0] != 'N') or\
                    (heads_directions[1] != 'R' and heads_directions[1] != 'L' and heads_directions[1] != 'N'):  # verificam ca directiile sa fie R - dreapta, L - stanga sau N - capatul sta pe loc
                error = 1
                message = "wrong transition : wrong direction"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
        else:
            if len(transition) == 5:  # tranzitia are lungimea 5 => avem 3 cazuri: - adaugam 2 simboluri (pentru ambele capete); - adaugam 1 simbol pe banda pentru primul capat; - adaugam 1 simbol pe banda pentru al doilea capat
                if transition[0] not in l_states or transition[1] not in l_states:  # verificam existenta starilor din tranzitie
                    error = 1
                    message = "wrong transition, the introduced states do not exist"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                heads_symbols = transition[2].split("/")
                if heads_symbols[0] not in l_gamma or heads_symbols[1] not in l_gamma:  # verificam existenta simbolului in sigma (alfabetul inputului)
                    error = 1
                    message = "wrong transition, the introduced symbol does not exist in the input alphabet"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                replacing_symbols = transition[3].split("/")
                if replacing_symbols[0] != "" and replacing_symbols[1] != "":  # daca adaugam 2 simboluri pe banda
                    if replacing_symbols[0] not in l_gamma or replacing_symbols[1] not in l_gamma:  # verificam existenta simbolurilor in alfabetul benzii
                        error = 1
                        message = "wrong transition, the introduced symbols does not exist in the tape's alphabet"
                        return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                else:
                    # daca adaugam un singur simbol
                    if replacing_symbols[0] != "":  # daca simbolul inlocuieste caracterul corespunzator primului capat
                        replacing_symbol = replacing_symbols[0]
                    else:
                        # daca simbolul inlocuieste caracterul corespunzator celui de-al doilea capat
                        replacing_symbol = replacing_symbols[1]
                    if replacing_symbol not in l_gamma:  # verificam existenta simbolului in alfabetul benzii
                        error = 1
                        message = "wrong transition, the introduced symbol does not exist in the tape's alphabet"
                        return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                heads_directions = transition[4].split("/")
                if (heads_directions[0] != 'R' and heads_directions[0] != 'L' and heads_directions[0] != 'N') or \
                        (heads_directions[1] != 'R' and heads_directions[1] != 'L' and heads_directions[1] != 'N'):  # verificam ca directia sa fie R - dreapta sau L - stanga
                    error = 1
                    message = "wrong transition : wrong direction"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
            else:  # lungimea tranzitiei nu este 4 sau 5
                error = 1
                message = "wrong transition"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states


def TM_simulator(l_transitions, l_special_states):
    # input_ex3 = "010011#010"
    # input_ex4 = "00+00000="
    input = sys.argv[2]  # inputul dat de la terminal
    current_state = l_special_states[0]  # starea curenta
    l_sol = []  # lista cu continutul benzii
    # punem in aceasta lista unde se afla capetele benzii si caracterele inputului pentru a prelucra mai usor continutul benzii la fiecare stare
    head1 = "(h1)"
    head2 = "(h2)"
    l_sol.append(head1)
    l_sol.append(head2)
    for character in input:
        l_sol.append(character)
    first_head_pos = 0  # pozitia capatului 1
    second_head_pos = 0  # pozitia capatului 2
    while current_state != 'qaccept' and current_state != "qreject":
        input_sol = "".join(l_sol)
        input_sol = input_sol.replace("s", "_")  # s = space/blank
        print( input_sol + " (" + current_state + ")")  # afisam continutul benzii dupa fiecare tranzitie + (starea curenta)
        for transition in l_transitions:
            transition = transition.split(",")
            heads_symbols_trans = transition[2].split("/")
            aux = 1  # numarul de pozitii pe care le adunam la pozitia capetelor in cazul in care capetele se afla pe aceeasi pozitie pe banda
            if l_sol[first_head_pos + 1] == "(h2)" or l_sol[second_head_pos + 1] == "(h1)":  # capetele se afla pe aceeasi pozitie pe banda
                aux += 1
            if transition[0] == current_state and l_sol[first_head_pos + aux] == heads_symbols_trans[0] and l_sol[second_head_pos + aux] == heads_symbols_trans[1]:
                # daca starea de inceput a tranzitiei coincide cu starea curenta si daca simbolurile de la capetele benzii coincid cu simbolurile de pe banda ale tranzitiei
                current_state = transition[1]  # starea curenta devine starea urmatoare din tranzitie
                if len(transition) == 4:  # nu adaugam nimic pe banda
                    heads_directions = transition[3].split("/")
                    if heads_directions[0] == 'R':  # in cazul in care directia este dreapta pentru primul capat
                        l_sol[first_head_pos], l_sol[first_head_pos + 1] = l_sol[first_head_pos + 1], l_sol[first_head_pos]  # interschimbam capatul 1 cu simbolul de pe pozitia urmatoare
                        first_head_pos = first_head_pos + 1  # crestem pozitia primului capat
                        if (first_head_pos == len(l_sol) - 1):
                            l_sol.append("s")  # daca ne aflam pe ultima pozitie din lista cu continutul benzii, adaugam un space pentru a simula infinitatea din partea dreapta a benzii
                        l_sol[first_head_pos] = head1  # schimbam pozitia lui h1 pe banda
                    if heads_directions[0] == 'L' and first_head_pos > 0:  # in cazul in care directia este stanga pentru primul capat si capatul nu se afla pe prima pozitie
                        l_sol[first_head_pos], l_sol[first_head_pos - 1] = l_sol[first_head_pos - 1], l_sol[first_head_pos]  # interschimbam capatul 1 cu simbolul de pe pozitia anterioara
                        first_head_pos = first_head_pos - 1  # scadem pozitia primului capat
                        l_sol[first_head_pos] = head1  # schimbam pozitia lui h1 pe banda
                    if heads_directions[1] == 'R':  # in cazul in care directia este dreapta pentru al doilea capat
                        l_sol[second_head_pos], l_sol[second_head_pos + 1] = l_sol[second_head_pos + 1], l_sol[second_head_pos]  # interschimbam capatul 2 cu simbolul de pe pozitia urmatoare
                        second_head_pos = second_head_pos + 1  # crestem pozitia celui de-al doilea capat
                        if (second_head_pos == len(l_sol) - 1):
                            l_sol.append("s")  # daca ne aflam pe ultima pozitie din lista cu continutul benzii, adaugam un space pentru a simula infinitatea din partea dreapta a benzii
                        l_sol[second_head_pos] = head2  # schimbam pozitia lui h2 pe banda
                    if heads_directions[1] == 'L' and second_head_pos > 0:  # in cazul in care directia este stanga pentru al doilea capat si capatul nu se afla pe prima pozitie
                        l_sol[second_head_pos], l_sol[second_head_pos - 1] = l_sol[second_head_pos - 1], l_sol[second_head_pos]  # interschimbam capatul 2 cu simbolul de pe pozitia anterioara
                        second_head_pos = second_head_pos - 1  # scadem pozitia celui de-al doilea capat
                        l_sol[second_head_pos] = head2  # schimbam pozitia lui h2 pe banda
                    break
                if len(transition) == 5:  # adaugam simboluri pe banda
                    replacing_symbols = transition[3].split("/")
                    if replacing_symbols[0] != "" and replacing_symbols[1] != "":  # daca adaugam 2 simboluri pe banda (inlocuim simbolurile spre care arata h1 si h2, adica cele aflate la pozitia capetelor+1)
                        l_sol[first_head_pos + 1] = replacing_symbols[0]
                        l_sol[second_head_pos + 1] = replacing_symbols[1]
                    else:
                        # daca adaugam un simbol pe banda (inlocuim simbolul spre care arata h1, respectiv h2, adica cele aflate la pozitia capetelor+1)
                        if replacing_symbols[0] == "":
                            l_sol[second_head_pos + 1] = replacing_symbols[1]
                        else:
                            l_sol[first_head_pos + 1] = replacing_symbols[0]

                    heads_directions = transition[4].split("/")
                    if heads_directions[0] == 'R':  # in cazul in care directia este dreapta pentru primul capat
                        l_sol[first_head_pos], l_sol[first_head_pos + 1] = l_sol[first_head_pos + 1], l_sol[first_head_pos]  # interschimbam capatul 1 cu simbolul de pe pozitia urmatoare
                        first_head_pos = first_head_pos + 1  # crestem pozitia primului capat
                        if (first_head_pos == len(l_sol) - 1):
                            l_sol.append("s")  # daca ne aflam pe ultima pozitie din lista cu continutul benzii, adaugam un space pentru a simula infinitatea din partea dreapta a benzii
                        l_sol[first_head_pos] = head1  # schimbam pozitia lui h1 pe banda
                    if heads_directions[0] == 'L' and first_head_pos>0:  # in cazul in care directia este stanga pentru primul capat si capatul nu se afla pe prima pozitie
                        l_sol[first_head_pos], l_sol[first_head_pos - 1] = l_sol[first_head_pos - 1], l_sol[first_head_pos]  # interschimbam capatul 1 cu simbolul de pe pozitia anterioara
                        first_head_pos = first_head_pos - 1  # scadem pozitia primului capat
                        l_sol[first_head_pos] = head1  # schimbam pozitia lui h1 pe banda
                    if heads_directions[1] == 'R':  # in cazul in care directia este dreapta pentru al doilea capat
                        l_sol[second_head_pos], l_sol[second_head_pos + 1] = l_sol[second_head_pos + 1], l_sol[second_head_pos]  # interschimbam capatul 2 cu simbolul de pe pozitia urmatoare
                        second_head_pos = second_head_pos + 1  # crestem pozitia celui de-al doilea capat
                        if (second_head_pos == len(l_sol) - 1):
                            l_sol.append("s")  # daca ne aflam pe ultima pozitie din lista cu continutul benzii, adaugam un space pentru a simula infinitatea din partea dreapta a benzii
                        l_sol[second_head_pos] = head2  # schimbam pozitia lui h2 pe banda
                    if heads_directions[1] == 'L' and second_head_pos>0:  # in cazul in care directia este stanga pentru al doilea capat si capatul nu se afla pe prima pozitie
                        l_sol[second_head_pos], l_sol[second_head_pos - 1] = l_sol[second_head_pos - 1], l_sol[second_head_pos]  # interschimbam capatul 2 cu simbolul de pe pozitia anterioara
                        second_head_pos = second_head_pos - 1  # scadem pozitia celui de-al doilea capat
                        l_sol[second_head_pos] = head2  # schimbam pozitia lui h2 pe banda
                    break
        # ne asiguram ca h1 si h2 se afla pe pozitiile corespunzatoare in cazul in care amandoua s-au aflat pe aceeasi pozitie la un moment dat
        l_sol[first_head_pos] = head1
        l_sol[second_head_pos] = head2
    input_sol = "".join(l_sol)
    input_sol = input_sol.replace("s", "_")
    print(input_sol + " (" + current_state + ")")  # afisam ultima configuratie a benzii + (starea finala - qaccept sau qreject)
    if current_state == 'qaccept':
        print("Accepted input")
    else:
        print("Rejected input")


file = sys.argv[1]
error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states = TM_config_file(file)
if error == 1:
    print(message)
else:
    print("Status: ", message)
    print("The states are: ", l_states)
    print("The input alphabet is: ", l_sigma)
    print("The tape's alphabet is: ", l_gamma)
    print("The transitions are:", l_transitions)
    print("The special states are:", l_special_states)
    TM_simulator(l_transitions, l_special_states)
