#pragma once
#include "Lambda.h"
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <random>

class Prepara : public Lambda {
public:
	int* vettoreOriginale;
	int len;

	Prepara(int lenVettore) {
		this->vettoreOriginale = new int[lenVettore];
		len = lenVettore;
		std::mt19937 generator;

		// Once per programme, before first use of generator
		generator.seed((unsigned int)std::time(0));

		std::uniform_int_distribution<uint32_t> dice(1, 100000);

		//int random = dice(generator);

		for (int i = 0; i < lenVettore; i++) {
			long seed = dice(generator);
			//std::cout << seed << " ";
			this->vettoreOriginale[i] = seed;
			
		}
	}

	int execute(int* vettore, int start, int finish, int k) {
		for (int i = 0; i < finish + 1; i++) {
			vettore[i] = this->vettoreOriginale[i];
		}
		return 0;
	}

	void riprepara(int lenVettore) {
		len = lenVettore;
		for (int i = 0; i < lenVettore; i++) {
			long seed = std::rand();
			//std::cout << seed << " ";
			this->vettoreOriginale[i] = seed;

		}
	}
};
