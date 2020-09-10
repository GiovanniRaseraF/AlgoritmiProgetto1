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
/*
EFFETTO: nanosecondi
*/
long nanosec() { return duration_cast<nanosecondi>(steady_clock::now().time_since_epoch()).count(); }
long getDuration(steady_clock::time_point start, steady_clock::time_point end);
long getResolution();
long getRobustResolution();
/*
EFFETTO: calca il tempo medio netto
*/
double tempoAlgoritmo(Lambda* Prepara, Lambda* Algoritmo, int* vettore, int lenVettore, int k, long tMin);
/*
EFFETTO: permette di prendere le misurazione utilizzando gli algoritmi sopra definiti
*/
double* misurazione(Lambda* prepara, Lambda* algoritmo, int* vettore, int lenVettore, int k, long tMin, int ripetizioni);




int main() {

	//Calcolo la granularità
	long risoluzione = getRobustResolution();
	double erroreMassimo = 0.01;					//1%
	double tMin = risoluzione / erroreMassimo + risoluzione;

	//Vettore
	int* vettore = new int[MAX_VAL] {};

	//Lambda
	Prepara* prepara			= new Prepara(MAX_VAL);
	prepara->execute(vettore, 0, MAX_VAL, 0);

	//Select
	QuickSelect* quickSelect	= new QuickSelect();
	MOMSelectInPlace* momSelect = new MOMSelectInPlace();
	HeapSelect* heapSelect		= new HeapSelect(MAX_VAL / 2 + 1);

	//Campionamento
	long minSize			= 100;
	long maxSize			= MAX_VAL;
	long samples			= 100;
	int numeroElementi		= 0, prevNumeroElementi = 0;
	int numeroIterazioni	= 10;
	int ripetizioni			= 50;

	//Calcolo dei tempi
	for (int i = 0; i < samples; i++) {
		//Calcolo il numero di elementi
		double base = exp((log(maxSize) - log(minSize)) / (samples - 1));
		double coefficiente = minSize;
		prevNumeroElementi = numeroElementi;
		numeroElementi = round(coefficiente * pow(base, i));

		//QUICK
		prepara->execute(vettore, 0, MAX_VAL, 0);
		double* risultatoQUICK = misurazione(prepara, quickSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, tMin, ripetizioni);

		//HEAP
		prepara->execute(vettore, 0, MAX_VAL, 0);
		double* risultatoHEAP = misurazione(prepara, heapSelect, vettore, (int)numeroElementi, (int)numeroElementi / 2, tMin, ripetizioni);

		//MOM
		prepara->execute(vettore, 0, MAX_VAL, 0);
		double* risultatoMOM = misurazione(prepara, momSelect, vettore, (int)numeroElementi - 1, (int)numeroElementi / 2, tMin, ripetizioni);

		prepara->riprepara(MAX_VAL);
		prepara->execute(vettore, 0, MAX_VAL, 0);

		//Stampa
		cout << (int)numeroElementi << " " << (int)numeroElementi / 2 << " " << risultatoQUICK[0] << " " << risultatoQUICK[1] << " " << risultatoHEAP[0] << " " << risultatoHEAP[1] << " " << risultatoMOM[0] << " " << risultatoMOM[1] << endl;

	}

	return 0;
}



//IMPLEMENTAZIONE:
double calcolaDeviazione(vector<double> tempi, double median, int ripetizioni) {
	double deviazione = 0;
	for (double time : tempi) deviazione += pow(time - median, 2);
	return (sqrt(deviazione / ripetizioni));
}

double* misurazione(Lambda* prepara, Lambda* algoritmo, int* vettore, int lenVettore, int k, long tMin, int ripetizioni) {
	double deviazione = 0, median = 0, currenttime = 0;
	vector<double> mem_deviazione{};
	for (int i = 0; i < ripetizioni; i++) {
		currenttime = tempoAlgoritmo(prepara, algoritmo, vettore, lenVettore, k, tMin);
		median += currenttime;
		//Salvo il valore per calcolare la deviazione standard
		mem_deviazione.push_back(currenttime);
	}
	//Calcolo la mediana
	median = median / ripetizioni;
	deviazione = calcolaDeviazione(mem_deviazione, median, ripetizioni);
	//Ritorno il risultato
	return new double[2]{median, deviazione};
}

double tempoAlgoritmo(Lambda* prepara, Lambda* algoritmo, int* vettore, int lenVettore, int k, long tMin) {
	long timeS, timeE;
	int c = 0;
	timeS = nanosec();
	do {
		prepara->execute(vettore, 0, MAX_VAL, 0);
		algoritmo->execute(vettore, 0, lenVettore, k);

		timeE = nanosec();
		c++;
	} while (timeE - timeS <= tMin);

	double value =  ((timeE - timeS) / c);
	return value;
}

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
