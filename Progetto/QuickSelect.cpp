#pragma once
#include "Lambda.h"
#include "Utils.h"
#include <iostream>
using namespace std;

class QuickSelect : public Lambda {
public:
    QuickSelect() {}
    int partition(int* vettore, int low, int high) {
        int x = vettore[high], index = low;

        //Lomuto partition
        for (int j = low; j < high; j++)
            if (vettore[j] <= x) Utils::swap(vettore, index++, j);

        Utils::swap(vettore, index, high);

        //Indice del pivot
        return index;
    }

    int quickselect(int* vettore, int start, int lenVettore, int k) {
        int mediano = partition(vettore, start, lenVettore);

        //Caso base
        if (k - 1 == mediano - start)return vettore[mediano];

        //Chiamate ricorsive
        if (k - 1 < mediano - start)return quickselect(vettore, start, mediano - 1, k);                                     //Cerco a sinistra
        else                        return quickselect(vettore, mediano + 1, lenVettore, k - mediano + start - 1);          //Certo a destra
    }


    int execute(int* vettore, int start, int finish, int k) {
        return quickselect(vettore, start, finish, k);
    }
};
