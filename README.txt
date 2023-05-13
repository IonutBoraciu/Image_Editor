Voi explica functionalitatiile functiilor de citire si a LOAD-ului:

Citire :
Exista 4 functii de citire corespunzatoare cu tipul de imagine citita PPM_P3 sau PPM_P6 sunt imagini
color ori stocate in ascii ( ppm_p3) ori stocate binar (ppm_p6), PGM_P2, PGM_P5 sunt imagini alb-negru
stocate ori in binar ori respectiv in ascii. 

LOAD:
Verific daca fisierul cu numele citit de la tastatura exista, in caz afirmativ verific
daca am deja un fisier incarcat in memorie, daca am, il eliberez, dupa care incarc in
memorie fisierul nou in functie de magic number-ul acestuia.

DOCUMENTATIE PENTRU PPM PGM:
http://paulbourke.net/dataformats/ppm/
