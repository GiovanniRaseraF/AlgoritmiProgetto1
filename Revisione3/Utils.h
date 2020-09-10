#pragma once
//
// Created by giovannirasera on 23/10/2019.
//
/*
AGGIORNAMENTI:
    03/11/2019:
        -Aggiunta di swap per i vector
        -Aggiunta di printArray che permette di scegliere separatore, inizio e fine per VECTOR

    04/1172019:
        -Aggiunta di insertValues per i vettori di interi
        -Aggiunta di printArray che permette di sceglie il separatore inizio e fine per ARRAY
*/

#include <cstdlib>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <ctime>

class Utils {
public:
    /**
    * EFFETTO: Scambia l'elemento alla posizione a con quello alla posizione b
    * MODIFICA: array
    * @param vet
    * @param a
    * @param b
    */
    static void swap(std::vector<int>& vet, int a, int b);

    static void swap(int **vet, int a, int b);

    //Vettori
    /**
     * EFFETTO: Scambia l'elemento alla posizione a con quello alla posizione b
     * MODIFICA: array
     * @param array
     * @param a
     * @param b
     */
    static void swap(int array[], int a, int b);

    /**
     * EFFETTO: Carica numeri a caso all'interno del vettore
     * min compreso, max non compreso
     * @param array
     */
    static void loadArray(int* array, int length, int min, int max);

    /**
     * EFFETTO: Carica numeri a caso all'interno del vettore
     * min compreso, max non compreso
     * @param array
     */
    static void loadArray(std::vector<int>& array, int length, int min, int max);

    /**
     * EFFETTO: Stapa a video l'array
     * @param array
     * @param length
     */
    static void printArray(int* array, int length);

    /**
     * EFFETTO: Ritorna un valore a caso tra min e max(non compreso)
     * @param min
     * @param max
     * @return
     */
    static int randInt(int min, int max);

    /**
     * EFFETTO: Stampa in un qualsiasi output stream il vettore
     * @param ad
     * @param a
     * @return
     */
    friend std::ostream& operator <<(std::ostream& ad, std::vector<int>& a);

    /**
     * EFFETTO: Inserisce in valori che legge da un qualiasi stream di input e li salva in un vettore
     * @param in
     * @param a
     * @return
     */
    friend std::istream& operator >>(std::istream& in, std::vector<int>& a);


    /**
     * EFFETTO: Stampa il vector in uno stream di output
     * @param vet
     */
    static void printArray(std::vector<int>& vet, std::ostream& out);

    /**
     * EFFETTO: Stampa il vector in uno stream di output con primo carattere first
     * ad ogni elemento stampato stampa separator e alla fine stampa last
     * @param vet
     */
    static void printArray(std::string first, std::vector<int>& vet, std::string separator, std::string last, std::ostream& out);

    /**
     * EFFETTO: Stampa L'ARRAY in uno stream di output con primo carattere first
     * ad ogni elemento stampato stampa separator e alla fine stampa last
     * @param vet
     */
    static void printArray(std::string first, int* vet, int vet_length, std::string separator, std::string last, std::ostream& out);

    /**
     * EFFETTO: Inserisce in valori che legge da un qualiasi stream di input e li salva in un vettore
     */
    static void insertValues(std::vector<int>& vet, std::istream& in);

    /**
     * EFFETTO: Inserisce in valori che legge da un qualiasi stream di input e li carica in un vettore
     * grande massimo max_elem
     * Alla fine ritora il numero di elementi inseriti
     */
    static int insertValues(int* vet, int max_len, std::istream& in);

    /**
     * EFFETTO: Legge un intero da tastiera
     * @param frase
     * @return
     */
    static int readInt(std::string frase, std::istream& in);

    /**
     *
     * @tparam T
     * @param vet
     * @param min
     * @param max
     */
     //template <class T> static void insertValues(std::vector<int> &vet, int min, int max);
};
