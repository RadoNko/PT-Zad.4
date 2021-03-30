// iLeftChild = 2 * i + 1
// iRightChild = 2 * i + 2
// iParent = (i-2) / 2
// Max-heap = SiftUp
// Min-heap = SiftDown
// Prvý prvok ktorý nieje listom -> (n/2)-1      n - arrayLength

/*
 Meno a priezvisko: Daniel Jankech
 
 POKYNY:
 (1)  Subor premenujte na Priezvisko_Meno_ID_du05.cpp (pouzite vase udaje bez diakritiky).
 (2)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
 (3)  Cela implementacia musi byt v tomto jednom subore.
 (4)  Odovzdajte len tento (spravne premenovany) zdrojovy subor.
 (5)  Program musi byt kompilovatelny.
 (6)  Globalne a staticke premenne su zakazane.
 (7)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
 (nemente nazvy, navratove hodnoty ani typ a pocet parametrov v zadanych funkciach).
 Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii.
 (8)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo struktury.
 (9)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo struktur).
 Testovaci kod ale nebude hodnoteny.
 (10) Funkcia 'main' musi byt v zdrojovom kode posledna.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define ARRAY_SIZE(arr)(sizeof(arr)/sizeof(arr[0]))
#define NUM_TESTS 30
#define ARR_SIZE 18
#define PARRENT (x-2)/2

using namespace std;

// pomocna funkcia, ktora vymeni hodnoty na adresach 'a' a 'b'
void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// pomocna funkcia na generovanie pola
void generateArray(int* data, const int n) {
    for (int i = 0; i < n; i++) {
        data[i] = rand()%100;
    }
}

// pomocna funkcia na vypis pola
void printArray(const int* data, const int n) {
    for (int i = 0; i < n; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}

// pomocna funkcia na overenie, ci je vstupne pole usporiadane vzostupne
bool isArraySortedDescending(const int* data, const int n){
    for (int i = 0; i < n-1; i++) {
        if(data[i]<data[i+1]){
            return false;
        }
    }
    return true;
}


//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
 Prida novy prvok do heapu.
 Verzia heap-u je Min-heap (hodnota kazdeho uzla je mensia alebo rovna ako hodnoty vsetkych jeho nasledovnikov).
 Pouzije algoritmus sift up.
 
 PARAMETRE:
 [in, out] data - heap, do ktoreho prida novy prvok
 [in] addIndex - index prvku, ktory prida do heap-u (preusporiadanim prvkov)
 
 VSTUPNE PODMIENKY:
 Prvky data[0]...data[addIndex-1] (vratane) tvoria heap
 'data' ukazuje na platne pole
 'addIndex' moze mat lubovolnu hodnotu
 
 VYSTUPNE PODMIENKY:
 Prvky data[0]...data[addIndex] (vratane) tvoria heap
 Preusporiada prvky data[0]...data[addIndex] tak, aby tvorili heap
 
 PRIKLADY:
 vstup:  data = {2, 4, 10, 7, 1, 2, 5, 0, 3, -1, 11, 12, 1}, addIndex = 4
 vystup: data = {1, 2, 10, 7, 4, 2, 5, 0, 3, -1, 11, 12, 1}
 
 vstup:  data = {3, 4, 10, 5, 5, 11, 15, 7, 8, 9, 10, 14,  8, 1, 2}, addIndex = 12
 vystup: data = {3, 4,  8, 5, 5, 10, 15, 7, 8, 9, 10, 14, 11, 1, 2}
 :SUCCESS*/
void siftUp(int data[], const size_t addIndex)
{
    int iParent = (addIndex-1)/2;
    if (addIndex < 0) {
        return;
    }
    if (data[addIndex] < data[iParent]) {
        swap(data+addIndex,data+iParent);
        siftUp(data, iParent);
    }
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
 Vytvori heap na poli 'data' preusporiadanim prvkov.
 Verzia heap-u je Min-heap (hodnota kazdeho uzla je mensia alebo rovna ako hodnoty vsetkych jeho nasledovnikov).
 Pouzije algoritmus sift up.
 
 PARAMETRE:
 [in, out] data - pole, ktore funkcia preusporiada, aby bolo heap-om
 [in] length - pocet prvkov pola
 
 VSTUPNE PODMIENKY:
 'data' ukazuje na platne pole, ak 'length' > 0
 'length' moze mat lubovolnu hodnotu
 
 VYSTUPNE PODMIENKY:
 'data' je heap-om
 
 PRIKLAD:
 vstup:  data = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6}, length = 11
 vystup: data = {1, 2, 2, 2, 2, 5, 3, 7, 4, 8, 6}
 SUCCESS */
void buildHeapSiftUp(int data[], const size_t length)
{
    // TODO
    for (int i = 1; i < length;i++) {
        siftUp(data, i);
    }
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
 Opravi cast heap-u (podstrom ktoreho koren ma index 'topIndex')
 Verzia heap-u je Min-heap (hodnota kazdeho uzla je mensia alebo rovna ako hodnoty vsetkych jeho nasledovnikov).
 Pouzite algoritmus sift down.
 
 PARAMETRE:
 [in, out] data - pole, v ktorom funkcia opravi cast heapu preusporiadanim prvkov
 [in] topIndex - index korena podstromu (casti heapu), ktory sa ma opravit
 [in] length - pocet prvkov pola
 
 VSTUPNE PODMIENKY:
 Podstromy prvku s indexom 'topIndex' splnaju podmienky heap (podstromy, ktorych korene su priamy nasledovnici uzla s indexom 'topIndex').
 'data' ukazuje na platne pole
 'topIndex' moze mat lubovolnu hodnotu
 'length' moze mat lubovolnu hodnotu
 
 VYSTUPNE PODMIENKY:
 Podstrom, ktoreho koren ma index 'topIndex' splna podmienku heap.
 
 PRIKLADY:
 vstup:  data = {55, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140}, topIndex = 0, length = 15
 vystup: data = {10, 20, 50, 30, 40, 55, 60, 70, 80, 90, 100, 110, 120, 130, 140}
 
 vstup:  data = {100, 8, 2, 1, 0, 5, 6, 7, 4, 2, 3, 11, 12, 13, 14, 15, 16, 17}, topIndex = 1, length = 18
 vystup: data = {100, 0, 2, 1, 2, 5, 6, 7, 4, 8, 3, 11, 12, 13, 14, 15, 16, 17}
 SUCC*/
void siftDown(int data[], const size_t topIndex, const size_t length)
{
    // TODO
    int tmp = topIndex;
    int iLeftChild = topIndex * 2 + 1;
    int iRightChild = topIndex * 2 + 2;
    
    if (iLeftChild < length && data[iLeftChild] < data[tmp]) {
        tmp = iLeftChild;
    }
    if (iRightChild < length && data[iRightChild] < data[tmp]) {
        tmp = iRightChild;
    }
    if (topIndex != tmp) {
        swap(data+tmp,data+topIndex);
        siftDown(data, tmp, length);
    }
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
 Vytvori heap na poli 'data' preusporiadanim prvkov.
 Verzia heap-u je Min-heap (hodnota kazdeho uzla je mensia alebo rovna ako hodnoty vsetkych jeho nasledovnikov).
 Pouzitej algoritmus sift down.
 
 PARAMETRE:
 [in, out] data - pole, ktore funkcia preusporiada aby bolo heap-om
 [in] length - pocet prvkov pola
 
 VSTUPNE PODMIENKY:
 'data' ukazuje na platne pole, ak 'length' > 0
 'length' moze mat lubovolnu hodnotu
 
 VYSTUPNE PODMIENKY:
 'data' je heap-om
 
 PRIKLAD:
 vstup:  data = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6}, length = 11
 vystup: data = {1, 2, 3, 2, 2, 5, 7, 4, 2, 8, 6}
 SUCCESS*/
void buildHeapSiftDown(int data[], const size_t length)
{
    // TODO
    for (int i = length/2-1; i>=0; i--) {
        siftDown(data, i, length-1);
    }
}

//-------------------------------------------------------------------------------------------------
// ULOHA (0.2 boda)
//-------------------------------------------------------------------------------------------------
/*
 Preusporiada pole 'data' od najvacsieho prvku po najmensi.
 Pouzite algoritmus heap sort.
 
 PARAMETRE:
 [in,out] data - pole, ktore funkcia usporiada
 [in] length - dlzka pola
 
 VSTUPNE PODMIENKY:
 'data' ukazuje na platne pole, ak 'length' > 0
 'length' moze mat lubovolnu hodnotu
 
 VYSTUPNE PODMIENKY:
 Pole 'data' je usporiadane
 
 PRIKLAD:
 vstup:  data = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6}, length = 11
 vystup: data = {8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 1}
 SUCC*/
void heapSort(int data[], const size_t length)
{
    // TODO
    buildHeapSiftUp(data, length);
    int tmp = length;
    while (tmp > 1) {
        swap(data,data+tmp-1);
        tmp--;
        buildHeapSiftUp(data, tmp);
    }
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    
    // tu mozete doplnit testovaci kod
    // inicializacia generatora nahodnych cisiel
//    srand(time(0));
    
    // Heap Sort - testovanie
//    int data[ARR_SIZE];
//    for(int i=0; i<NUM_TESTS;i++){
//        generateArray(data,ARRAY_SIZE(data));
//        heapSort(data,ARRAY_SIZE(data));
//        cout << "Heap Sort [" << (isArraySortedDescending(data,ARRAY_SIZE(data))?"sorted":"unsorted") << "]: ";
//        printArray(data,ARRAY_SIZE(data));
//    }
    
//    generateArray(data,ARR_SIZE);
//    int data[ARR_SIZE]={7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6};
//    printArray(data, ARR_SIZE);
//    siftUp(data, 12);
//    buildHeapSiftUp(data, 11);
//    siftDown(data, 1, 18);
//    buildHeapSiftDown(data, 11)
//    heapSort(data, 11);
//    printArray(data, ARR_SIZE);
//
    cout <<(-1/2)<< endl;
    
    return 0;
}
