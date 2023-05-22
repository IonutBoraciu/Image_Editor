# PCLP3_tema1
Varianta finala contine intreg programul in varianta cea mai stabila a acestuia. Restul contin functiile din program.
Celelalte 2 branch-uri sunt DOAR pentru testing, ele contin cod care ARE erori. Singura varianta fara erori se afla pe main branch.

Inainte de a explica functionalitatea fiecarei functii in parte, voi explica cum trebuie apelate si cu ce parametrii:
Exista urmatoarele comenezi : 
  - LOAD
  - SELECT
  - HISTOGRAM
  - EQUALIZE
  - CROP
  - SAVE
  - ROTATE
  - APPLY
  - EXIT

Acestea trebuie apelate in urmatorul fel : 
  - LOAD : asteapta sa primeasca ca parametru o imagine ppm sau pgm stocata in ascii sau in binar
    Exemplu apelare: LOAD imagine1.ppm
  - SELECT : selecteaza o zona VALIDA din imaginea incarcata asupra careia va EFECTUA urmatoarele operatii
 pana cand se apeleaza SELECT ALL care readuce focus-ul asupra intregii matrici, daca este selectata o zona
 invalida va fi afisat un mesaj corespunzator.
    Exemplu apelare: SELECT SELECT 0 0 300 300
  - HISTOGRAM : nu are nevoie de un parametru, va calcula histograma matricei din memorie. Atentie!!
functia functioneaza strict pe imaginele pgm, daca se apeleaza asupra unei imagine ppm atunci se va afisa
un mesaj de eroare corespuznator
  - EQUALIZE : similara cu HISTOGRAM, are nevoie de o imagine alb negru si nu asteapta alt parametru, va egaliza
imagine, pentru a nu mai exista zone foarte negre si zone foarte albe
  - CROP : Taie imagine incarcata in memorie pe zona selectata, nu necesita parametru
  - SAVE : salveaza imaginea in formatul primit ca input in felul urmator : daca este dat ca parametru in plus
 ascii, atunci va salva imaginea in format ascii altfel o salveaza automat in format binar.
   Exemplu apelare: SAVE test1.ppm sau SAVE test2.ppm ASCII
  - ROTATE : roteste ori intreaga imagine cu un numar de grade divizibil cu 90 (pozitiv sau negativ), ori zona selectat DOAR daca este
  patratica
   Exemplu apelare: ROTATE 90
  - APPLY : aplica unul din cele 4 filtre de imagine (SHARPEN, EDGE, BLUR, GAUSSIAN_BLUR) : filtrele functioneaza pe acelasi princpiu doar
  ca matricea aplicata asupra imaginii difera.
   Exemplu apelare: APPLY BLUR

Explicarea functiilor: 

LOAD:
Verific daca fisierul cu numele citit de la tastatura exista, in caz afirmativ verific
daca am deja un fisier incarcat in memorie, daca am, il eliberez, dupa care incarc in
memorie fisierul nou in functie de magic number-ul acestuia.

SELECT:
Verific daca am primit 4 parametrii de tip int. In caz afirmativ, verific daca parametrii
sunt valizi sau nu. Daca parametrii sunt valizi ii salvez altfel pastrez parametrii vechi(daca exista).

SELECT ALL:
Resetez variabilele de selectie la toata imaginea.

HISTOGRAM:
Verific ca parametrii primiti sunt valizi. Apoi creez un vector de frecventa pentru
valoriile din matricea pixelilor. Apoi restrictionez acest vector de frecventa la numarul
de bin-uri primite ca parametru. Afisez histograma conform cerintei.

EQUALIZE:
Creez un vector de frecventa pentru valoriile din matriea pixelilor. Apoi aplic formula
primita in cerinta, pe care o salvez intr-un vector auxiliar. Atribuii valoriile din vecotrului auxiliar matricei pentru a o egaliza.

ROTATE:
Verific ca daca am selectat o anumita zona aceasta este patratica si ca unghiul primit ca
parametru este divizibil cu 90. In cazul in care datele primite sunt valide, apelez una dintre
cele 4 functii de rotire in functie de magic number-ul fisierului. Algoritmul de
functionarea al celor 4 functii este similar: aloc dinamic o matrice in care salvez rotirea
cu inaltimea si latima inversate. Apoi calculez in aceasta matricea rotita la 90 de grade spre
dreapta. Daca am selectat toata imaginea, atunci realoc matricea de pixeli inversand
numarul de linii si de coloane. Apoi copiez raspunsul din matricea rotate in matricea initiala.
( pentru a rotii cu mai mult de 90 de grade functie este apeleta de mai multe ori, iar pentru a o rotii spre stanga este apeleta cu 360-unghiul primit).

CROP:
Creez o matrice copie in care sa stochez temperor valoriile din zona la care vreau sa restrictionez. Apoi eliberez matricea initiala si o realoc cu dimensiunile specifice
zonei selectate. In final, copiez inapoi in matricea initiala valoriile salvate in matricea copie.

APPLY:
Verific ca valoriile care stocheaza pozitia zonei primite sa nu sa afle pe marginea intregii imaginii,
in caz negativ le schimb valoarea. Creez o matrice copie in care sa
stochez rezultatul dupa aplicarea kernel-ului. Apoi aplic kernel-ul primit pe zona selectata 
sau intreaga imagine astfel: calculez suma valorilor din jurul fiecarui pixel pe rand (inclusiv pixelul)si o atribui matricei copie.

SAVE:
Daca imaginea trebuie salvata in ascii, dupa ce scriu in fisier magic number-ul, dimensiunile si valoarea maxima voi scrie in int 
valoriile din matricea pixelilor. Altfel daca trebuie salvata in binar, daca initial matricea era salvata in int voi creea mai intai
o matrice copie in care voi transforma elementele matricei initiale in unsigned char, apoi
voi scrie matricea copie in fisier.

EXIT:
Eliberez matricea curenta daca am un fisier deschis si se opreste executia.

Alta comanda:
Afisez: Invalid command.

