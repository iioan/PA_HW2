# Tema 2 Proiectarea Algoritmilor

### Teodorescu Ioan, 323CB

Arhiva consta in rezolvarea celor 4 probleme, avand un punctaj total de 107 puncte (cu README si coding style)

### Problema 1 - Supercomputer

La baza problemei sa algoritmul de sortare topologica putin modificat pentru a aflarea numarului minim de context switch-uri. Noi vom primii dependente cum ar fi: task-ul x trebuie sa se termine inainte de task-ul y; iar pentru TopSort, orientarea muchiilor corespunde unei relatie de ordine de la nodul sursa, la nodul destinatie; daca (x, y) este un arc, atunci x trebuie sa fie inaintea lui y.

Incep prin a citi datele din `[supercomputer.in](http://supercomputer.in)`. Memorez ce set de date foloseste task-ul / nodul respectiv; lista de adicenta pentru nodul x si gradul interior pentru nodul y. 

In `topologicalSort`, apare coada `q`, ce contine intotdeauna noduri care au gradul interior egal cu 0 si coada `lost`, care va stoca task-urile care nu au un set de date egal. Pentru inceput, voi cauta nodurile cu gradul interior 0 (mai exact, task-urile care nu au nicio dependenta) si le adaug in coada q. In timp ce se executa algoritmul de sortare, extrag nodul din coada (`node`), iau fiecare nod adiacent cu acesta si le scad gradul interior. Daca ajunge sa fie 0, asta inseamna ca trebuie inserate in coada `q`, insa aici are loc o modificare. Daca set-ul de date folosit de nodul adiacent lui node este acelasi cu setul de date al lui node, acesta poate fi pus in coada `q`. Iar daca nu, nodul va fi pus in `lost`. Daca cumva, coada q va deveni nula si coada lost are elemente in ea, aici ar trebuii sa aiba loc un context switch, unde acesta va fi contorizat (`count++`) iar toatele elementele din lost, sunt puse in q. Tot procesul continua pana cand coada q devine goala, ajungand sa parcurga toate nodurile. Rezultatul se afla in count.

************************Complexitate************************

N - numarul ce noduri; M - numarul de muchii

- Complexitatea temporala: O(N + M)
    - Sortarea topologica: O(N + M)
    - Cititea datelor: O(N + M)
    - Adaugarea elementelor din lost in q: O(N)
- Complexitatea spatiala: O(N + M)
    - Lista de adiacenta: O(N + M)
    - Cozile; O(N)
    - Vectorul pentru gradul interior: O(N)

Resurse folosite: 

[https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-06](https://ocw.cs.pub.ro/courses/pa/laboratoare/laborator-06)

[https://youtu.be/cIBFEhD77b4](https://youtu.be/cIBFEhD77b4)

### Problema 2 - Cai Ferate

Am decis ca pentru rezolvarea cerintei, trebuie gasite componentele tare conexe ale grafului orientat, ca mai apoi odata gasite, voi numara numarul de componente tare conexe care nu au un grad interior. Astfel, se determina numarul minim de cai ferate care trebuie construite astfel incat nodul S (statia cu depozit) sa aiba un drum catre fiecare dintre nodurile din graf (mai exact, statia principala sa poata livra marfuri catre orice gara). 

Pentru aflarea numarul de componente conexe, am folosit **algoritmul lui Kosaraju**.  Se citesc datele din fisier, se creeaza lista de adiacenta `adj` si lista de adiacenta inversata (inversarea grafului). Pentru inceput, fac parcurgerea in adancime pentru graful normal, tinand cont de timpul de terminare al fiecarul nod, astfel incat la terminarea parcurgerii, nodul parcurs este adaugat in stiva `reordered`.

Dupa care, vom face DFS pentru graful inversat. Aici nu voi folosi un vector de frecventa, ci unul in care memorez in ce componenta conexa se afla nodul respectiv (`component`). Iau cate un nod din stiva, verific daca acesta nu apartine niciunei componente tare conexe si fac DFS pentru nodul respectiv, gasind o noua componenta tare conexa. Fiecarui nod ii se va atribuii un identificator (`component`). Acest lucru se repeta pana cand stiva `reordered` este goala. 

Acum avem numarul de componente tare conexe si pentru fiecare nod, al carei componente ii apartine. Acum, voi lua graful simplu si pentru fiecare nod, voi lua nodurile adiacente cu acesta, si verific daca ambii apartin unor componente conexe diferite. Daca da, inseamna ca nodul adiacent (`adj[i][v]`) are un grad interior ≠ 0, deci si componenta care il contine are un grad interior ≠ 0 si asta va fi contorizata de lista grad_int. 

Acum, voi cauta componentele care sunt diferite de cel care contin nodul `s` si care au gradul interior egal cu 0. Motivul pentru care fac asta este ca daca o componenta nu are grad interior, inseamna ca nu exista nicio modalitate de a ajunge la ea. Adaugand o muchie de la nodul `S` la acea componenta conexa, se creeaza o cale de la statia S la toate statiile din acea componenta. 

************************Complexitate************************

N - numarul ce noduri; M - numarul de muchii

- Complexitatea temporala: O(N + M)
    - Cititea datelor: O(N + M)
    - Algoritmul lui Kosaraju: O(N + M)
- Complexitatea spatiala: O(N + M)
    - Listele de adiacenta: O(N + M)
    - Stiva: O(N)
    - Vectorul pentru gradul interior: O(N)

Resurse folosite: 

[https://www.youtube.com/watch?v=Rs6DXyWpWrI](https://www.youtube.com/watch?v=Rs6DXyWpWrI)

[https://iq.opengenus.org/kosarajus-algorithm-for-strongly-connected-components/](https://iq.opengenus.org/kosarajus-algorithm-for-strongly-connected-components/)

### Problema 3 - nu am facut-o

### Problema 4 - Magazin

Am observat ordinea magazinelor din exemplul dat de enunt si de regula in care X va expedia la x_1, dupa care x_1 va expedia la randul sau spre alte depozite, iar dupa ce x_1 termina, X continua cu x_2. M-am gandit sa folosesc parcurgerea in adancime (DFS) pentru a afla ordinea in care coletele vor fi trimise. 

Se citesc datele din fisier. M-am gandit sa pastrez cele N - 1 numere de pe a doua linie, pentru a-l folosi ca un vector de parinti (`parent`) + lista de adiacenta.

Voi face parcurgerea in adancime iterativa, folosind o stiva, doarece consider ca este mult mai eficient decat DFS-ul recursiv. Algoritmul incepe prin a pune nodul radacina in stiva. In loop, se va lua un element din stiva, care va fi procesat: va fi adaugat in vectorul `reordered`, ce pastreaza ordinea in care coletele vor fi trimise si va fi memorata si pozitia in vector a nodului respectiv. Dupa care, se ia fiecare nod adiacent cu cel curent, si vor si puse in stiva. Aceste operatii se vor repeta, pana cand stiva este goala.

Acum ca avem ordinea in care coletele for fi trimise, voi citi cele m linii, care au un nod de la care pornesc si un numar de expedieri.

- Verific daca nodul / depozitul respectiv nu are cui sa ii trimita colete → afiseaza -1
- Iau pozitia nodului / depozitului din `ordered` si verific daca fac `timer` expedieri, se va depasii dimensiunea vectorului (n == ordered.size()) → afiseaza -1
- Iau nodul / depozitul la care ar trebuii sa se ajunga dupa `timer` expedieri; daca nu exista drum intre nodul `x` si acest nod → afiseaza -1
- Daca toate aceste conditii nu sunt indeplinite, asta inseamna ca am gasit nodul in care se va ajunge de la nodul `x`, dupa `timer` expedieri

Pentru gasirea unui drum posibil, m-am folosit de functia `find_parental`, in care interpretez graful ca un arbore (de aceea pastrez si vectorul parintilor). Se cauta parintele nodului `b` intr-un loop, pana cand il gasim pe `a`, asta inseamna ca exista drum intre cele doua noduri si se va intoarce 1. Daca e este 0, asta inseamna ca s-a ajung la nodul radacina si nu exista drum catre a la b → se returneaza -1. In opinia mea, complexitatea algoritmului ar trebuii sa fie O(log N): daca suntem intr-un arbore si voi lua de fiecare daca parintele nodului, asta ar insemna ca traversez un nivel de fiecare data, iar deobicei, inaltimea unui arbore ar trebuii sa fie k = log N.

Pe vmchecker uneori primesc TLE la anumite teste, insa pe local imi trec toate testele.

C************************omplexitate************************

N - numarul ce noduri; Q - numarul de perechi (D, E); M - numarul de muchii (e N - 1)

- Complexitatea temporala: O(Q*log N)
    - DFS cu stiva: O(N + M)
    - find_parental: O(log N)
- Complexitatea spatiala: O(N + M)
    - Lista de adiacenta: O(N + M)
    - Stiva; Vectorii reordered, position; O(N)

Resurse folosite:

[https://www.geeksforgeeks.org/iterative-depth-first-traversal/](https://www.geeksforgeeks.org/iterative-depth-first-traversal/)

Rezultat checker local:
```
./check 
g++ (Ubuntu 12.2.0-17ubuntu1) 12.2.0
gcc (Ubuntu 12.2.0-17ubuntu1) 12.2.0
javac 17.0.7
Python 3.11.2
timeout (GNU coreutils) 9.1
---------------------- Run public_tests -------------------
------------------------------------------------------------
------------------------------------------------------------
---------------------- Problema 1: supercomputer -----------------
---------------------- timp C++ => 1 s -----------------
Test 0 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 1 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 2 problema 1 .......... 1.0/1.0 - OK  - 0.008 s
Test 3 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 4 problema 1 .......... 1.0/1.0 - OK  - 0.008 s
Test 5 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 6 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 7 problema 1 .......... 0.0/1.0 - WA 3 vs 4 - 0.008 s
Test 8 problema 1 .......... 1.0/1.0 - OK  - 0.008 s
Test 9 problema 1 .......... 1.0/1.0 - OK  - 0.006 s
Test 10 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 11 problema 1 .......... 1.0/1.0 - OK  - 0.006 s
Test 12 problema 1 .......... 1.0/1.0 - OK  - 0.007 s
Test 13 problema 1 .......... 1.0/1.0 - OK  - 0.008 s
Test 14 problema 1 .......... 1.0/1.0 - OK  - 0.006 s
Test 15 problema 1 .......... 1.0/1.0 - OK  - 0.008 s
Test 16 problema 1 .......... 1.0/1.0 - OK  - 0.014 s
Test 17 problema 1 .......... 1.0/1.0 - OK  - 0.009 s
Test 18 problema 1 .......... 1.0/1.0 - OK  - 0.048 s
Test 19 problema 1 .......... 1.0/1.0 - OK  - 0.052 s
Test 20 problema 1 .......... 0.0/1.0 - WA 27 vs 28 - 0.075 s
Test 21 problema 1 .......... 1.0/1.0 - OK  - 0.077 s
Test 22 problema 1 .......... 1.0/1.0 - OK  - 0.074 s
Test 23 problema 1 .......... 1.0/1.0 - OK  - 0.077 s
Test 24 problema 1 .......... 1.0/1.0 - OK  - 0.058 s
Test 25 problema 1 .......... 1.0/1.0 - OK  - 0.080 s
Test 26 problema 1 .......... 1.0/1.0 - OK  - 0.079 s
Test 27 problema 1 .......... 0.0/1.0 - WA 2612 vs 2613 - 0.081 s
Test 28 problema 1 .......... 1.0/1.0 - OK  - 0.094 s
Test 29 problema 1 .......... 1.0/1.0 - OK  - 0.080 s
=============>>>>>> Scor : 27.0/30 <<<<<< =============
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
---------------------- Problema 2: ferate -----------------
---------------------- timp C++ => 0.5 s -----------------
Test 0 problema 2 .......... 1.0/1.0 - OK  - 0.012 s
Test 1 problema 2 .......... 1.0/1.0 - OK  - 0.009 s
Test 2 problema 2 .......... 1.0/1.0 - OK  - 0.009 s
Test 3 problema 2 .......... 1.0/1.0 - OK  - 0.009 s
Test 4 problema 2 .......... 1.0/1.0 - OK  - 0.010 s
Test 5 problema 2 .......... 1.0/1.0 - OK  - 0.009 s
Test 6 problema 2 .......... 1.0/1.0 - OK  - 0.011 s
Test 7 problema 2 .......... 1.0/1.0 - OK  - 0.010 s
Test 8 problema 2 .......... 1.0/1.0 - OK  - 0.011 s
Test 9 problema 2 .......... 1.0/1.0 - OK  - 0.011 s
Test 10 problema 2 .......... 1.0/1.0 - OK  - 0.011 s
Test 11 problema 2 .......... 1.0/1.0 - OK  - 0.010 s
Test 12 problema 2 .......... 1.0/1.0 - OK  - 0.010 s
Test 13 problema 2 .......... 1.0/1.0 - OK  - 0.011 s
Test 14 problema 2 .......... 1.0/1.0 - OK  - 0.010 s
Test 15 problema 2 .......... 1.0/1.0 - OK  - 0.013 s
Test 16 problema 2 .......... 1.0/1.0 - OK  - 0.021 s
Test 17 problema 2 .......... 1.0/1.0 - OK  - 0.036 s
Test 18 problema 2 .......... 1.0/1.0 - OK  - 0.016 s
Test 19 problema 2 .......... 1.0/1.0 - OK  - 0.017 s
Test 20 problema 2 .......... 1.0/1.0 - OK  - 0.031 s
Test 21 problema 2 .......... 1.0/1.0 - OK  - 0.056 s
Test 22 problema 2 .......... 1.0/1.0 - OK  - 0.077 s
Test 23 problema 2 .......... 1.0/1.0 - OK  - 0.152 s
Test 24 problema 2 .......... 1.0/1.0 - OK  - 0.176 s
Test 25 problema 2 .......... 1.0/1.0 - OK  - 0.158 s
Test 26 problema 2 .......... 1.0/1.0 - OK  - 0.109 s
Test 27 problema 2 .......... 1.0/1.0 - OK  - 0.123 s
Test 28 problema 2 .......... 1.0/1.0 - OK  - 0.148 s
Test 29 problema 2 .......... 1.0/1.0 - OK  - 0.125 s
Test 30 problema 2 .......... 1.0/1.0 - OK  - 0.064 s
Test 31 problema 2 .......... 1.0/1.0 - OK  - 0.151 s
Test 32 problema 2 .......... 1.0/1.0 - OK  - 0.118 s
Test 33 problema 2 .......... 1.0/1.0 - OK  - 0.080 s
Test 34 problema 2 .......... 1.0/1.0 - OK  - 0.497 s
=============>>>>>> Scor : 35.0/35 <<<<<< =============
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
---------------------- Problema 3: teleportare -----------------
---------------------- timp C++ => 2.5 s -----------------
Test 0 problema 3 .......... 0.0/1.0 - WA 1 vs 3 - 0.007 s
Test 1 problema 3 .......... 0.0/1.0 - WA 1 vs 4 - 0.007 s
Test 2 problema 3 .......... 0.0/1.0 - WA 1 vs 4 - 0.004 s
Test 3 problema 3 .......... 0.0/1.0 - WA 1 vs 4 - 0.004 s
Test 4 problema 3 .......... 0.0/1.0 - WA 1 vs 4 - 0.012 s
Test 5 problema 3 .......... 0.0/1.0 - WA 1 vs 7 - 0.008 s
Test 6 problema 3 .......... 0.0/1.0 - WA 1 vs 8 - 0.004 s
Test 7 problema 3 .......... 0.0/1.0 - WA 1 vs 15 - 0.005 s
Test 8 problema 3 .......... 0.0/1.0 - WA 1 vs 22 - 0.005 s
Test 9 problema 3 .......... 0.0/1.0 - WA 1 vs 7 - 0.004 s
Test 10 problema 3 .......... 0.0/1.0 - WA 1 vs 14 - 0.005 s
Test 11 problema 3 .......... 0.0/1.0 - WA 1 vs 8 - 0.004 s
Test 12 problema 3 .......... 0.0/1.0 - WA 1 vs 53 - 0.005 s
Test 13 problema 3 .......... 0.0/1.0 - WA 1 vs 22 - 0.005 s
Test 14 problema 3 .......... 0.0/1.0 - WA 1 vs 8 - 0.004 s
Test 15 problema 3 .......... 0.0/1.0 - WA 1 vs 21 - 0.004 s
Test 16 problema 3 .......... 0.0/1.0 - WA 1 vs 17 - 0.004 s
Test 17 problema 3 .......... 0.0/1.0 - WA 1 vs 367 - 0.005 s
Test 18 problema 3 .......... 0.0/1.0 - WA 1 vs 143 - 0.006 s
Test 19 problema 3 .......... 0.0/1.0 - WA 1 vs 239 - 0.005 s
Test 20 problema 3 .......... 0.0/1.0 - WA 1 vs 1698 - 0.004 s
Test 21 problema 3 .......... 0.0/1.0 - WA 1 vs 9959 - 0.005 s
Test 22 problema 3 .......... 0.0/1.0 - WA 1 vs 15166 - 0.007 s
Test 23 problema 3 .......... 0.0/1.0 - WA 1 vs 20403 - 0.005 s
Test 24 problema 3 .......... 0.0/1.0 - WA 1 vs 9254 - 0.005 s
Test 25 problema 3 .......... 0.0/1.0 - WA 1 vs 462418 - 0.006 s
Test 26 problema 3 .......... 0.0/1.0 - WA 1 vs 551020 - 0.004 s
Test 27 problema 3 .......... 0.0/1.0 - WA 1 vs 222030 - 0.004 s
Test 28 problema 3 .......... 0.0/1.0 - WA 1 vs 417096 - 0.005 s
Test 29 problema 3 .......... 0.0/1.0 - WA 1 vs 280187 - 0.004 s
Test 30 problema 3 .......... 0.0/1.0 - WA 1 vs 1750561 - 0.005 s
Test 31 problema 3 .......... 0.0/1.0 - WA 1 vs 1641413694 - 0.005 s
Test 32 problema 3 .......... 0.0/1.0 - WA 1 vs 1722130916 - 0.005 s
Test 33 problema 3 .......... 0.0/1.0 - WA 1 vs 79176387 - 0.005 s
Test 34 problema 3 .......... 0.0/1.0 - WA 1 vs 80532140 - 0.005 s
Test 35 problema 3 .......... 0.0/1.0 - WA 1 vs 592406861 - 0.005 s
Test 36 problema 3 .......... 0.0/1.0 - WA 1 vs 71644697543 - 0.005 s
Test 37 problema 3 .......... 0.0/1.0 - WA 1 vs 516862681 - 0.005 s
Test 38 problema 3 .......... 0.0/1.0 - WA 1 vs 56366494996 - 0.005 s
Test 39 problema 3 .......... 0.0/1.0 - WA 1 vs 2136308637 - 0.005 s
=============>>>>>> Scor : 0/40 <<<<<< =============
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
---------------------- Problema 4: magazin -----------------
---------------------- timp C++ => 0.5 s -----------------
Test 0 problema 4 .......... 1.0/1.0 - OK  - 0.011 s
Test 1 problema 4 .......... 1.0/1.0 - OK  - 0.007 s
Test 2 problema 4 .......... 1.0/1.0 - OK  - 0.007 s
Test 3 problema 4 .......... 1.0/1.0 - OK  - 0.008 s
Test 4 problema 4 .......... 1.0/1.0 - OK  - 0.007 s
Test 5 problema 4 .......... 1.0/1.0 - OK  - 0.007 s
Test 6 problema 4 .......... 1.0/1.0 - OK  - 0.007 s
Test 7 problema 4 .......... 1.0/1.0 - OK  - 0.008 s
Test 8 problema 4 .......... 1.0/1.0 - OK  - 0.009 s
Test 9 problema 4 .......... 1.0/1.0 - OK  - 0.010 s
Test 10 problema 4 .......... 1.0/1.0 - OK  - 0.009 s
Test 11 problema 4 .......... 1.0/1.0 - OK  - 0.012 s
Test 12 problema 4 .......... 1.0/1.0 - OK  - 0.011 s
Test 13 problema 4 .......... 1.0/1.0 - OK  - 0.011 s
Test 14 problema 4 .......... 1.0/1.0 - OK  - 0.010 s
Test 15 problema 4 .......... 1.0/1.0 - OK  - 0.010 s
Test 16 problema 4 .......... 1.0/1.0 - OK  - 0.083 s
Test 17 problema 4 .......... 1.0/1.0 - OK  - 0.099 s
Test 18 problema 4 .......... 1.0/1.0 - OK  - 0.147 s
Test 19 problema 4 .......... 1.0/1.0 - OK  - 0.084 s
Test 20 problema 4 .......... 1.0/1.0 - OK  - 0.203 s
Test 21 problema 4 .......... 1.0/1.0 - OK  - 0.045 s
Test 22 problema 4 .......... 1.0/1.0 - OK  - 0.119 s
Test 23 problema 4 .......... 1.0/1.0 - OK  - 0.216 s
Test 24 problema 4 .......... 1.0/1.0 - OK  - 0.165 s
Test 25 problema 4 .......... 1.0/1.0 - OK  - 0.242 s
Test 26 problema 4 .......... 1.0/1.0 - OK  - 0.294 s
Test 27 problema 4 .......... 1.0/1.0 - OK  - 0.251 s
Test 28 problema 4 .......... 1.0/1.0 - OK  - 0.312 s
Test 29 problema 4 .......... 1.0/1.0 - OK  - 0.285 s


                .--.                  Try not.
        ::\`--._,'.::.`._.--'/::     Do or do not.
        ::::.  ` __::__ '  .::::    There is no try.
        ::::::-:.`'..`'.:-::::::
        ::::::::\ `--' /::::::::        Yoda


=============>>>>>> Scor : 30.0/30 <<<<<< =============
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
------------------------------------------------------------
================>>>>>> Check README <<<<<< ================
README OK. Punctajul final se va acorda la corectare.
===============>>>>>> README: 10/10 <<<<<< ===============
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
===============>>>>>> Check coding style <<<<<< ===============
/home/eone/PA/tema2_finala/_utils/coding_style/check_cpp.py:57: DeprecationWarning: module 'sre_compile' is deprecated
  import sre_compile
Done processing ./_utils/verif.cpp
Done processing ./ferate.cpp
Done processing ./magazin.cpp
Done processing ./supercomputer.cpp
Done processing ./teleportare.cpp

Coding style OK. Punctajul final se poate modifica la corectare.
===============>>>>>> Coding style: 5/5 <<<<<< ===============
-------------------------------------------------------------
-------------------------------------------------------------
Erorile de coding style se gasesc in cpp.errors / java.errors
=============>>>>>> Total: 107.0/150 <<<<<< =============

```