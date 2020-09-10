
#include "Lambda.h"
#include <iostream>
#include <math.h>
#include "Utils.h"
#include <algorithm>
#include <vector>

using namespace std;
/*
VIEW: Gestisce un vettore come una min heap
*/
class MinHeap {
public:
    //Atributi
    int* vet;
    int size;
    int length;
    //Min Heap
    //  UTILITY
    int static left(int i) { return (2 * i) + 1; }

    int static right(int i) { return (2 * i) + 2; }

    int static parent(int i) { return (i == 0 ? 0 : (int)floor((i - 1) / 2)); }
    //  END UTILITY
    //  GETTER
    int MinLength() { return size; }

    int MinElem() { return (size == 0 ? throw "Min Heap Vuota" : vet[0]); }
    //  END GETTER
    //  SETTER
    void MinInsert(int key) {
        //Precondizioni
        if (size >= length)
            throw "MaxHeap Piena non è possibile aggiungere elementi";

        vet[size++] = key;
        int i = size - 1;

        while (i > 0 && vet[i] < vet[parent(i)]) {
            Utils::swap(vet, i, parent(i));
            i = parent(i);
        }
    }
    //  END SETTER
    //  OTHER
    void MinHeapify(int i) {
        int le = MinHeap::left(i), rh = MinHeap::right(i), m = 0;

        if (le < size && vet[le] < vet[i]) {
            m = le;
        }
        else {
            m = i;
        }
        if (rh < size && vet[rh] < vet[m]) {
            m = rh;
        }
        if (m != i) {
            Utils::swap(vet, i, m);
            MinHeapify(m);
        }
    }

    MinHeap(int* vet, int length, int size) {
        this->vet = vet;
        this->length = length;
        this->size = size;
        for (int i = (int)floor((size - 1) / 2); i >= 0; i--) {
            MinHeapify(i);
        }
    }

    int MinEstract() {
        //Precondizione
        if (size == 0) throw "MaxHeap vuota";

        Utils::swap(vet, 0, size - 1);
        size--;
        MinHeapify(0);
        return vet[size];
    }
    //  END OTHER
};


class MinHeapPOINTER {
public:
    //Atributi
    int** vet;
    int size;
    int length;
    //Min Heap
    //  UTILITY
    int static left(int i) { return (2 * i) + 1; }

    int static right(int i) { return (2 * i) + 2; }

    int static parent(int i) { return (i == 0 ? 0 : (int)floor((i - 1) / 2)); }
    //  END UTILITY
    //  GETTER
    int MinLength() { return size; }

    int* MinElem() { return (size == 0 ? throw "Min Heap Vuota" : vet[0]); }
    //  END GETTER
    //  SETTER
    void MinInsert(int* key) {
        //Precondizioni
        if (size >= length)
            throw "MaxHeap Piena non è possibile aggiungere elementi";

        vet[size++] = key;
        int i = size - 1;

        while (i > 0 && *vet[i] < *vet[parent(i)]) {
            Utils::swap(vet, i, parent(i));
            i = parent(i);
        }
    }
    //  END SETTER
    //  OTHER
    void MinHeapify(int i) {
        int le = MinHeap::left(i), rh = MinHeap::right(i), m = 0;

        if (le < size && *vet[le] < *vet[i]) {
            m = le;
        }
        else {
            m = i;
        }
        if (rh < size && *vet[rh] < *vet[m]) {
            m = rh;
        }
        if (m != i) {
            Utils::swap(vet, i, m);
            MinHeapify(m);
        }
    }

    MinHeapPOINTER(int** vet, int length, int size) {
        this->vet = vet;
        this->length = length;
        this->size = size;
        for (int i = (int)floor((size - 1) / 2); i >= 0; i--) {
            MinHeapify(i);
        }
    }

    int* MinEstract() {
        //Precondizione
        if (size == 0) throw "MaxHeap vuota";

        Utils::swap(vet, 0, size - 1);
        size--;
        MinHeapify(0);
        return vet[size];
    }
    //  END OTHER
};


class HeapSelect : public Lambda {
public:
    int** vettoreH2;
    HeapSelect(int size) { vettoreH2 = new int* [size] {}; }

    int heapSelect(int* vettore, int start, int finish, int k) {
        //La prima heap H1 é costruita a partire dal vettore fornito in 
        //input in tempo lineare e non viene modificata.
        MinHeap* H1 = new MinHeap(vettore, finish, finish);
        //Utils::printArray(vettore, finish); cout << endl;

        //La seconda heap H2 contiene inizialmente un solo nodo,
        //corrispondente alla radice di H1.
        MinHeapPOINTER* H2 = new MinHeapPOINTER(vettoreH2, finish, 0);
        H2->MinInsert(&vettore[0]);

        //All'i-esima iterazione, per i che va da 1 a k−1
        for (int i = 1; i <= k - 1; i++) {
            //l'algoritmo estrae la radice di H2
            int* radiceH2 = H2->MinEstract();

            //cout << vettore<<"   "<<radiceH2;
            //Calcolo la posizione nel vettore
            int indexOFValue = (int)(radiceH2 - vettore);
            int left = MinHeap::left(indexOFValue);
            int right = MinHeap::right(indexOFValue);

            //cout << "Index :" << indexOFValue << " left:" << left << " right:" << right<<endl;
            //reinserisce in H2 i nodi successori(figli sinistro e destro) di xi nella heap H1.
            if (left < finish)
                H2->MinInsert(&vettore[left]);
            if (right < finish)
                H2->MinInsert(&vettore[right]);
        }
        return *(H2->MinEstract());

    }

    int execute(int* vettore, int start, int finish, int k) { 
        return heapSelect(vettore, start, finish, k); 
    };

};



