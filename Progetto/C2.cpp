#include <iostream>
#include <chrono>
#include <algorithm>
#include <fstream>
#include "Lambda.h"
#include "Utils.h"
#include "Prepara.cpp"
#include "QuickSelect.cpp"
#include "MOMSelectInPlace.cpp"
#include "HeapSelect.cpp"


#define MAX_VAL 3000000
#define DEBUG_CODE true

using namespace std;
using namespace std::chrono;
typedef duration<long, nanoseconds::period> nanosecondi;

//FUNZIONI:
long getDuration(steady_clock::time_point start, steady_clock::time_point end) {
	return duration_cast<nanosecondi>(end - start).count();
}

long getResolution() {
	steady_clock::time_point start = steady_clock::now(), end;
	do {
		end = steady_clock::now();
	} while (start == end);
	return getDuration(start, end);
}

long getRobustResolution() {
	vector<long> res(1000);
	for (int i = 0; i < 1000; i++)
		res[i] = getResolution();
	std::sort(res.begin(), res.end());
	return res[res.size() / 2];
}

/*
EFFETTO: nanosecondi
*/
long nanosec() { return duration_cast<nanosecondi>(steady_clock::now().time_since_epoch()).count(); }


/*
EFFETTO: Calcola le volte che si deve ricalcolare la Tara e Lordo
*/
long calcolaRipTara(Lambda* Prepara, int* vettore, int lenVettore, int k, long tMin);
long calcolaRipLordo(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore, int k, long tMin);

/*
DA NON USARE
EFFETTO: Calcola il tempo di esecuzione
*/
void calcoloDeiTempi(Lambda* P, int* vettore, int lenVettore, int k, long rip);

/*
EFFETTO: calca il tempo medio netto
*/
double tempoMedioNetto(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore, int k, long tMin);

/*
EFFETTO: permette di prendere le misurazione utilizzando gli algoritmi sopra definiti
*/
double* misurazione(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore, int k, long cicles, double za, long tMin, double triangolino);



int main() {

	//Calcolo la granularità
	long risoluzione = getRobustResolution();
	double erroreMassimo = 0.01;					//1%
	double tMin = risoluzione / erroreMassimo + risoluzione;

	//Vettore
	int* vettore = new int[MAX_VAL] {};

	//Lambda
	Prepara* prepara = new Prepara(MAX_VAL);
	prepara->execute(vettore, 0, MAX_VAL, 0);

	//Select
	QuickSelect* quickSelect = new QuickSelect();
	MOMSelectInPlace* momSelect = new MOMSelectInPlace();
	HeapSelect* heapSelect = new HeapSelect(MAX_VAL / 2 + 1);

	//Campionamento
	long minSize = 100;
	long maxSize = MAX_VAL;
	long samples = 100;
	int numeroElementi = 0, prevNumeroElementi = 0;
	int numeroIterazioni = 10;

	//Calcolo dei tempi
	for (int i = 0; i < samples; i++) {
		//Calcolo il numero di elementi
		double base = exp((log(maxSize) - log(minSize)) / (samples - 1));
		double coefficiente = minSize;
		prevNumeroElementi = numeroElementi;
		numeroElementi = round(coefficiente * pow(base, i));

		//QUICK
		double tringQUICK = 0.1f * tempoMedioNetto(prepara, quickSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, tMin);
		prepara->execute(vettore, 0, MAX_VAL, 0);
		double* risultatoQUICK = misurazione(prepara, quickSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, numeroIterazioni, 2.33, tMin, tringQUICK);

		//HEAP
		double tringHEAP = 0.1f * tempoMedioNetto(prepara, heapSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, tMin);
		prepara->execute(vettore, 0, MAX_VAL, 0);
		double* risultatoHEAP = misurazione(prepara, heapSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, numeroIterazioni, 2.33, tMin, tringHEAP);

		//MOM
		double tringMOM = 0.1f * tempoMedioNetto(prepara, momSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, tMin);
		prepara->execute(vettore, 0, MAX_VAL, 0);
		double* risultatoMOM = misurazione(prepara, momSelect, vettore, (int)numeroElementi - 1, (int)numeroElementi / 2, numeroIterazioni, 2.33, tMin, tringMOM);

		prepara->riprepara(MAX_VAL);
		prepara->execute(vettore, 0, MAX_VAL, 0);

		//Stampa
		cout << (int)numeroElementi << " " << (int)numeroElementi / 2 << " " << risultatoQUICK[0] << " " << risultatoQUICK[1] << " " << risultatoHEAP[0] << " " << risultatoHEAP[1] << " " << risultatoMOM[0] << " " << risultatoMOM[1] << endl;

	}

	return 0;
}



//IMPLEMENTAZIONE:
long granularita() {
	long t0 = nanosec();
	long t1 = nanosec();
	while (t0 == t1) {
		t1 = nanosec();
	}
	return (t1 - t0);
}

/*
EFFETTO: Calcola quante volte deve essere eseguita la tara affinchè venga scomputata correttamente.
PARAMETRI:
	- Prepara		: Lambda		-> funzione da eseguire per caricare il vettore
	- vettore		: int *			-> il vettore da caricare
	- lenVettore	: int			-> lunghezza del vettore
	- k				: int			-> non utile in questo caso
	- tMin			: long			-> risoluzione del sistema
*/
long calcolaRipTara(Lambda* Prepara, int* vettore, int lenVettore, int k, long tMin) {
	long t0 = nanosec(), t1 = nanosec(), rip = 1;

	//Calcolo delle ripetizioni massime
	while (t1 - t0 <= tMin) {
		//stima di rip con crescita esponenziale
		rip += 2;
		t0 = nanosec();
		for (int i = 0; i < rip; i++) {
			int n = Prepara->execute(vettore, 0, lenVettore, 0);
		}
		t1 = nanosec();
	}


	long max = rip, min = rip / 2, cicliErrati = 5;
	//Ricerca esatta del numero di ripetizioni per bisezione
	while (max - min >= cicliErrati) {
		rip = (max + min) / 2;
		t0 = nanosec();
		for (int i = 0; i < rip; i++) {
			int n = Prepara->execute(vettore, 0, lenVettore, 0);
		}
		t1 = nanosec();
		if (t1 - t0 <= tMin)
			min = rip;
		else
			max = rip;
	}
	return max;
}

/*
EFFETTO: Calcola quante volte deve essere eseguita il lordo affichè il tempo di esecuzione sia maggiore della risoluzione.
PARAMETRI:
	- Prepara		: Lambda		-> funzione da eseguire per caricare il vettore
	- Algoritmo		: Lambda		-> funzione da eseguire per la SELEZIONE (QUICK, HEAP, MOM)
	- vettore		: int *			-> il vettore da caricare
	- lenVettore	: int			-> lunghezza del vettore
	- k				: int			-> il k - esimo elemento da trovare
	- tMin			: long			-> risoluzione del sistema
*/
long calcolaRipLordo(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore, int k, long tMin) {
	long t0 = nanosec(), t1 = nanosec();
	long rip = 1;
	//Calcolo delle ripetizioni massime
	while (t1 - t0 <= tMin) {
		//stima di rip con crescita esponenziale
		rip += 2;
		t0 = nanosec();
		for (int i = 0; i < rip; i++) {
			Prepara->execute(vettore, 0, lenVettore, 0);
			Algoritmo->execute(vettore, 0, lenVettore, k);
		}
		t1 = nanosec();
	}

	//Ricerca esatta del numero di ripetizioni per bisezione
	long max = rip, min = rip / 2;
	long cicliErrati = 5;

	while (max - min >= cicliErrati) {
		rip = (max + min) / 2;
		t0 = nanosec();
		for (int i = 0; i < rip; i++) {
			int n = Prepara->execute(vettore, 0, lenVettore, 0);
			n = Algoritmo->execute(vettore, 0, lenVettore, k);
		}
		t1 = nanosec();
		if (t1 - t0 <= tMin)
			min = rip;
		else
			max = rip;
	}

	return max;
}

void calcoloDeiTempi(Lambda* P, int* vettore, int lenVettore, int k, long rip) {
	long t0 = nanosec();
	for (int i = 0; i < rip; i++) {
		P->execute(vettore, 0, lenVettore, k);
	}
	long t1 = nanosec();
	long tTot = t1 - t0;
	long tSing = tTot / rip;
	cout << "T_Tot: " << tTot << endl << "R_Sing: " << tSing << endl;
}


/*
EFFETTO: Dopo aver calcolato le ripetizioni per la tara e per il lordo, esegue il calcolo vero e propio
del tempo di esecuzione della tara e in seguito quello del lordo.
RITORNA: il tempo di esecuzione del lordo - tempo di esecuzione della tara,   ovvero il tempo medio netto.
*/
double tempoMedioNetto(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore, int k, long tMin) {
	double ripTara = calcolaRipTara(Prepara, vettore, lenVettore, k, tMin);
	double ripLordo = calcolaRipLordo(Prepara, Algoritmo, vettore, lenVettore, k, tMin);

	long t0 = nanosec();
	//Calcola il tempo di esecuzione della preparazione del vettore, ripTara volte
	for (int i = 0; i < ripTara; i++) {
		Prepara->execute(vettore, 0, lenVettore, k);
	}
	long t1 = nanosec();
	//Tempo totale di esecuzione della tara
	long tTara = t1 - t0;

	//Calcola il tempo di esecuzione della preparazione che dell'algoritmo, ripLordo volte
	for (int i = 0; i < ripLordo; i++) {
		Prepara->execute(vettore, 0, lenVettore, k);
		Algoritmo->execute(vettore, 0, lenVettore, k);
	}
	t1 = nanosec();
	//Tempo lordo
	long tLordo = t1 - t0;

	//Tempo medio netto
	double tMedio = ((tLordo / ripLordo) - (tTara / ripTara));
	return tMedio;
}

/*
EFFETTO: Effettua una media di tutto il calcolo dei tempi
PARAMETRI:
	- Prepara		: Lambda		-> funzione da eseguire per caricare il vettore
	- Algoritmo		: Lambda		-> funzione da eseguire per la SELEZIONE (QUICK, HEAP, MOM)
	- vettore		: int *			-> il vettore da caricare
	- lenVettore	: int			-> lunghezza del vettore
	- k				: int			-> il k - esimo elemento da trovare
	- cicles		: int			-> numero di volte che viene eseguita la misurazione del tempo medio netto
	- za			: double		-> il parametro che descrive la funzione di distribuzione normale
	- tMin			: long			-> risoluzione
	- triangolino	: double		-> errore massimo tollerato ( 1% )
RITORNA:
	- vettore[0]	: double		-> tempo di esecuzione
	- vettore[1]	: double		-> deviazione standard
*/
double* misurazione(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore,
	int k, long cicles, double za, long tMin, double triangolino) {
	double t = 0, m = 0, sum2 = 0, delta = 0, e = 0, s = 0;
	long cn = 0;

	do {
		for (int i = 0; i < cicles; i++) {
			m = tempoMedioNetto(Prepara, Algoritmo, vettore, lenVettore, k, tMin);
			t += m;
			sum2 += (m * m);
		}

		cn += cicles;
		e = t / cn;
		s = sqrt(sum2 / cn - (e * e));
		delta = ((1 / sqrt(cn))) * za * s;

		//Eseguo il calcolo fino a quando ho un errore < dell'1%
	} while (delta >= triangolino);

	return new double[2]{ e, delta };
}