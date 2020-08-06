#include<iostream> 
#include<algorithm>
#include <cmath>
#include "Utils.h"
#include "Lambda.h"
using namespace std;
#define FIVE 5
class MOMSelectInPlace : public Lambda {
public:
	int static momSelect(int* vettore, int inizio, int lunghezza, int k) {
		
		while (true) {
			int numero_gruppi_completi = floor(lunghezza / FIVE);
			int numero_elemnti_non_completi = lunghezza - (numero_gruppi_completi * FIVE);
			int* ultimiElementi = &vettore[(numero_gruppi_completi * FIVE)];


			while (true) {
				for (int gruppo_completo = 0; gruppo_completo < numero_gruppi_completi; gruppo_completo++) {
					std::sort(&vettore[gruppo_completo * FIVE], &vettore[(gruppo_completo * FIVE) + FIVE]);
					int posizione_mediano_del_gruppo = (gruppo_completo * FIVE) + 2;
					Utils::swap(vettore, gruppo_completo, posizione_mediano_del_gruppo);
				}

				//Elementi non completi
				if (numero_elemnti_non_completi != 0) {
					std::sort(ultimiElementi, &ultimiElementi[numero_elemnti_non_completi]);
					int posizione_mediano_del_gruppo = floor((numero_elemnti_non_completi-1) / 2) + (numero_gruppi_completi * FIVE);
					Utils::swap(vettore, numero_gruppi_completi, posizione_mediano_del_gruppo);
				}

				//Esco siccome ho finito
				if (numero_gruppi_completi == 0) break;

				int lun = numero_elemnti_non_completi;
				numero_gruppi_completi = floor(lun / FIVE);
				numero_elemnti_non_completi = lun - (numero_gruppi_completi * FIVE);
				ultimiElementi = &vettore[(numero_gruppi_completi * FIVE)];
			}

			int mom = *vettore;
			
			//Chiamata a partition
			int pivot = partition(vettore, lunghezza-1, mom);

			

			if (pivot == k) return vettore[pivot];

			if (pivot < k) {
				k = k - pivot - 1;
				vettore = &vettore[pivot + 1];
				lunghezza = lunghezza - (pivot + 1);
			}
			else if (pivot > k) {
				lunghezza = pivot;
			}
		}
	}

	/*
	EFFETTO: Esegue una partizione
	*/
	int static partition(int* vettore, int lunghezza, int mom) {
		//cerco il mediano
		int i;
		for (i = 0; i < lunghezza && vettore[i] != mom; i++);
		Utils::swap(vettore, i, lunghezza);

		//Algoritmo di partizione Lomuto
		i = 0;
		for (int j = 0; j <= lunghezza - 1; j++)
			if (vettore[j] <= mom) Utils::swap(vettore, i++, j);

		Utils::swap(vettore, i, lunghezza);
		return i;
	}

	int execute(int* vettore, int start, int finish, int k) {
		return momSelect(vettore, start, finish, k-1); 
	};
};

#define MAIN_EXE_
#ifdef MAIN_EXE
int main() {
	std::vector<int> vet;
	Utils::insertValues(vet, cin);
	int k = Utils::readInt("", cin);
	int* vettore = new int[vet.size()];
	MOMSelectInPlace* mom = new MOMSelectInPlace();

	//Copia
	for (int i = 0; i < vet.size(); i++)
		vettore[i] = vet[i];

	int res = mom->momSelect(vettore, 0, vet.size(), k-1);
	cout << res;

	return 0;
}
#endif