"""Dobre Adriana Lia, Guțu Ștefania Alexandra, Pirlogea Luciana Elena, grupa 141
~ Lab 5 ~
1. Implement a library/program in a programming language of your
choosing to load and validate a TM configuration file
2. Implement a library/program that creates a TM given an input
config file.
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
            if transition[0] not in l_states or transition[
                1] not in l_states:  # verificam existenta starilor din tranzitie
                error = 1
                message = "wrong transition, the introduced states do not exist"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
            if transition[2] not in l_gamma:  # verificam existenta simbolului in alfabetul benzii
                error = 1
                message = "wrong transition, the introduced symbol does not exist in the tape's alphabet"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
            if transition[3] != 'R' and transition[3] != 'L':  # verificam ca directia sa fie R - dreapta sau L - stanga
                error = 1
                message = "wrong transition : wrong direction"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
        else:
            if len(transition) == 5:  # tranzitia are lungimea 5 => adaugam un simbol pe banda
                if transition[0] not in l_states or transition[
                    1] not in l_states:  # verificam existenta starilor din tranzitie
                    error = 1
                    message = "wrong transition, the introduced states do not exist"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                if transition[2] not in l_sigma:  # verificam existenta simbolului in sigma (alfabetul inputului)
                    error = 1
                    message = "wrong transition, the introduced symbol does not exist in the input alphabet"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                if transition[3] not in l_gamma:  # verificam existenta simbolului in alfabetul benzii
                    error = 1
                    message = "wrong transition, the introduced symbol does not exist in the tape's alphabet"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
                if transition[4] != 'R' and transition[
                    4] != 'L':  # verificam ca directia sa fie R - dreapta sau L - stanga
                    error = 1
                    message = "wrong transition : wrong direction"
                    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
            else:  # lungimea tranzitiei nu este 4 sau 5
                error = 1
                message = "wrong transition"
                return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states
    return error, message, l_states, l_sigma, l_gamma, l_transitions, l_special_states


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
    input = sys.argv[2]  # inputul dat de la terminal
    current_state = l_special_states[0]  # starea curenta
    l_sol = []  # lista cu continutul benzii
    # punem in aceasta lista starea curenta si caracterele inputului pentru a prelucra mai usor continutul benzii la fiecare stare
    l_sol.append(current_state)
    for character in input:
        l_sol.append(character)
    current_state_pos = 0  # pozitia starii curente in lista cu continutul benzii; retinem aceasta pozitie pentru a afla locatia capului benzii (pozitia starii curente + 1)
    while current_state != 'qaccept' and current_state != "qreject":
        input_sol = "".join(l_sol)
        input_sol = input_sol.replace("s", "_")  # s = space/blank
        print(input_sol)  # afisam continutul benzii dupa fiecare tranzitie
        for transition in l_transitions:
            transition = transition.split(",")
            if transition[0] == current_state and l_sol[current_state_pos + 1] == transition[
                2]:  # daca starea de inceput a tranzitiei coincide cu starea curenta si daca capul benzii coincide cu simbolul de pe banda al tranzitiei
                current_state = transition[1]  # starea curenta devine starea urmatoare din tranzitie
                if len(transition) == 4:
                    if transition[3] == 'R':  # in cazul in care directia este dreapta
                        l_sol[current_state_pos], l_sol[current_state_pos + 1] = l_sol[current_state_pos + 1], l_sol[
                            current_state_pos]  # interschimbam starea curenta cu simbolul de pe pozitia urmatoare
                        current_state_pos = current_state_pos + 1
                        if (current_state_pos == len(l_sol) - 1):
                            l_sol.append(
                                "s")  # daca ne aflam pe ultima pozitie din lista cu continutul benzii, adaugam un space pentru a simula infinitatea din partea dreapta a benzii
                        l_sol[current_state_pos] = current_state
                    if transition[3] == 'L':  # in cazul in care directia este stanga
                        l_sol[current_state_pos], l_sol[current_state_pos - 1] = l_sol[current_state_pos - 1], l_sol[
                            current_state_pos]  # interschimbam starea curenta cu simbolul de pe pozitia anterioara
                        current_state_pos = current_state_pos - 1
                        l_sol[current_state_pos] = current_state
                    break
                if len(transition) == 5:
                    l_sol[current_state_pos + 1] = transition[
                        3]  # inlocuim simbolul unde se afla capul benzii in acest moment cu simbolul tranzitiei
                    if transition[4] == 'R':  # in cazul in care directia este dreapta
                        l_sol[current_state_pos], l_sol[current_state_pos + 1] = l_sol[current_state_pos + 1], l_sol[
                            current_state_pos]  # interschimbam starea curenta cu simbolul de pe pozitia urmatoare
                        current_state_pos = current_state_pos + 1
                        if (current_state_pos == len(l_sol) - 1):
                            l_sol.append(
                                "s")  # daca ne aflam pe ultima pozitie din lista cu continutul benzii, adaugam un space pentru a simula infinitatea din partea dreapta a benzii
                        l_sol[current_state_pos] = current_state
                    if transition[4] == 'L':  # in cazul in care directia este stanga
                        l_sol[current_state_pos], l_sol[current_state_pos - 1] = l_sol[current_state_pos - 1], l_sol[
                            current_state_pos]  # interschimbam starea curenta cu simbolul de pe pozitia anterioara
                        current_state_pos = current_state_pos - 1
                        l_sol[current_state_pos] = current_state
                    break
    input_sol = "".join(l_sol)
    input_sol = input_sol.replace("s", "_")
    print(input_sol)
    if current_state == 'qaccept':
        print("Accepted input")
    else:
        print("Rejected input")
