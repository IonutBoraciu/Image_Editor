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

