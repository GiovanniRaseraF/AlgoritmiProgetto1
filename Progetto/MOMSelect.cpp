#include<iostream> 
#include<algorithm> 
#include<climits> 
#include "Utils.h"
#include "Lambda.h"
using namespace std;

class MOMSelect : public Lambda {
public:
	MOMSelect() {};
	/*
	EFFETTO: Trova l'elemente modiano dell'array
	*/
	int trovaMediao(int *vettore, int n){
		sort(vettore, vettore + n); 
		return vettore[n / 2]; 
	}
 
	int momSelect(int *vettore, int start, int finish, int k){
		//Se il k che sto cercando è minore del numero di elementi 
		int numero_elementi = finish - start + 1; 

		//Divido il vettore in 5 elementi 
		int i;
		//Allocazione del nuovo vettore
		int *median = new int[(int)((numero_elementi + 4) / 5)]; 
		for (i = 0; i < numero_elementi / 5; i++)
			median[i] = trovaMediao(vettore + start + i * 5, 5);
		if (i * 5 < numero_elementi){
			median[i] = trovaMediao(vettore + start + i * 5, numero_elementi % 5);
			i++;
		}

		//Caso base
		int mom = 0;
		if (i == 1) mom = median[i - 1];

		//Caso riorsivo
		else		mom = momSelect(median, 0, i - 1, i / 2);
		//delete(median);

		//Partizionamento dell'array attorno al mom selezionato
		int pos = partition(vettore, start, finish, mom);

		//Trovato la posizione k 
		if (pos - start == k - 1)		return vettore[pos];
		//Vado a sinistra
		else if (pos - start > k - 1)   return momSelect(vettore, start, pos - 1, k);
		//Vado a destra
		else							return momSelect(vettore, pos + 1, finish, k - pos + start - 1);
	}

	/*
	EFFETTO: Esegue una partizione
	*/
	int partition(int *vettore, int l, int r, int mom){
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

	int execute(int* vettore, int start, int finish, int k) {
		return momSelect(vettore, start, finish, k);
	}

};

#define DA_CONSEGNA_

#ifdef DA_CONSEGNA
int main(){
	std::vector<int> vet;
	Utils::insertValues(vet, cin);
	int k = Utils::readInt("", cin);
	int *vettore = new int[vet.size()];
	MOMSelect* mom = new MOMSelect_1();

	//Copia
	for (int i = 0; i < vet.size(); i++)
		vettore[i] = vet[i];

	cout << mom->execute(vettore, 0, vet.size()-1, k);

	return 0;
}
#endif