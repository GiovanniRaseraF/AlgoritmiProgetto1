#include<iostream> 
#include<algorithm>
#include <cmath>
#include "Utils.h"
#include "Lambda.h"
using namespace std;
class MOMSelectStabile: public Lambda{
public:
#define FIVE 5
	MOMSelectStabile() {};
	
	int static trovaMinimo(int* vettore, int start, int finish, int offset) {
		int posMin = start;
		for (int i = start; i < finish; i += offset)
			if (vettore[i] < vettore[posMin]) posMin = i;
		return posMin;
	}

	int static trovaMediao(int* vettore, int start, int finish, int offset) {
		for (int i = start; i < finish; i += offset) {
			int posMin = trovaMinimo(vettore, start, finish, offset);
			Utils::swap(vettore, i, posMin);
		}
		return start + 2;
	}

	int static momSelect(int* vettore, int start, int finish, int k) {
		do {
			//Se il k che sto cercando è minore del numero di elementi 
			int numero_elementi = finish-start;
			int numero_di_gruppi_interi = floor(numero_elementi / 5);
			int salto = FIVE;
			int inizio_gruppo_non_intero = (numero_di_gruppi_interi * FIVE)+start;
			int numero_elementi_non_interi = numero_elementi - inizio_gruppo_non_intero;

			while (true) {
				//Gruppi con 5 elementi
				for (int i = 0; i <  numero_di_gruppi_interi; i++) {
					int pos_mediano = trovaMediao(vettore, i , i + salto, 1);
					Utils::swap(vettore, floor(i / salto), pos_mediano);
				}
				//Gruppi con meno di 5 elementi
				if (numero_elementi_non_interi != 0) {
					int pos_mediano = inizio_gruppo_non_intero + floor(numero_di_gruppi_interi / 2);
					trovaMediao(vettore, inizio_gruppo_non_intero, inizio_gruppo_non_intero + numero_elementi_non_interi, 1);
					Utils::swap(vettore, numero_di_gruppi_interi, pos_mediano);
				}
				

				//Esco
				if (numero_elementi <= 1) break;

				//Reimposto le variabili
				numero_elementi = numero_di_gruppi_interi + (numero_elementi_non_interi == 0? 0:1);
				numero_di_gruppi_interi = floor(numero_elementi / 5);
				salto = FIVE;
				inizio_gruppo_non_intero = (numero_di_gruppi_interi * FIVE);
				numero_elementi_non_interi = numero_elementi - inizio_gruppo_non_intero;
			}

			
			//Selezione il pivot
			int mom = vettore[start];

		
			cout << "Vettore:" << endl;
			Utils::printArray(&vettore[start], finish);
			cout <<"    start:" << start << "  Finish:" << finish << "  mom:" << mom;
			cin.ignore();
			
			int pos = partition(vettore, start, finish, mom);
			
			cout <<"Vettore:"<< endl;
			Utils::printArray(&vettore[start], pos + 1); 
			cout << "\n      POS:" << pos << "    start:" << start<<"  Finish:"<<finish<<"  mom:"<<mom;
			cin.ignore();
			
			//Trovato la posizione k 
			if (pos == k) return vettore[pos];
			//Vado a sinistra
			else if (pos > k ) finish = pos - 1;
			//Vado a destra
			else {
				vettore = &vettore[pos + 1];
				k = (k - pos) -1;
				finish -= (pos+1);
			}
		} while (true);
	}

	/*
	EFFETTO: Esegue una partizione
	*/
	int static partition(int* vettore, int l, int r, int mom) {
		//cerco il mediano
		int i;
		for (i = l; i < r && vettore[i] != mom; i++);
		Utils::swap(vettore, i, r);

		//Algoritmo di partizione Lomuto
		i = l;
		for (int j = l; j <= r - 1; j++)
			if (vettore[j] <= mom) Utils::swap(vettore, i++, j);

		Utils::swap(vettore, i, r);
		return i;
	}

	int execute(int* vettore, int start, int finish, int k) { return momSelect(vettore, start, finish, k); };

};


#define MAIN_EXE
#ifdef MAIN_EXE
int main() {
	std::vector<int> vet;
	Utils::insertValues(vet, cin);
	int k = Utils::readInt("", cin);
	int* vettore = new int[vet.size()];
	MOMSelectStabile* mom = new MOMSelectStabile();

	//Copia
	for (int i = 0; i < vet.size(); i++)
		vettore[i] = vet[i];

	cout << mom->execute(vettore, 0, vet.size(),  k);

	return 0;
}
#endif