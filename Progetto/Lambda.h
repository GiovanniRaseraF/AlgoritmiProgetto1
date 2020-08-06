#pragma once
class Lambda
{
public:
	/*
	EFFETTO: Permette di generalizzare l'esecuzione
	*/
	virtual int execute(int* vettore, int start, int finish, int k) { return 0; };
};

