//
// Created by giovannirasera on 23/10/2019.
//
#include "Utils.h"
//Vettore di Int
void Utils::swap(std::vector<int>& vet, int a, int b) {
    int t = vet[a];
    vet[a] = vet[b];
    vet[b] = t;
}

void Utils::swap(int* array, int a, int b) {
    int t = array[a];
    array[a] = array[b];
    array[b] = t;
}

void Utils::loadArray(int* array, int length, int min, int max) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < length; i++) {
        array[i] = (rand() % (max - min)) + min;
    }
}

void Utils::loadArray(std::vector<int>& array, int length, int min, int max) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < length; i++) {
        array.push_back((rand() % (max - min)) + min);
    }
}

void Utils::printArray(int* array, int length) {
    for (int i = 0; i < length; i++) {
        std::cout << array[i] << ", ";
    }
}

int Utils::randInt(int min, int max) {
    return (rand() % (max - min)) + min;
}

std::ostream& operator<<(std::ostream& out,const std::vector<int>& a) {
    for (int i = 0; i < a.size(); i++) {
        out << a[i] << " ";
    }
    out << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, std::vector<int>& a) {
    std::string line = "";
    getline(in, line);
    std::istringstream s(line);
    int value = 0;
    while (s >> value) {
        a.push_back(value);
    }
    return in;
}

void Utils::printArray(std::vector <int>& vet, std::ostream& out) {
    for (int i = 0; i < vet.size(); i++) {
        out << vet[i] << " ";
    }
    out << std::endl;
}

void Utils::swap(int** vet, int a, int b) {
    int *t = vet[a];
    vet[a] = vet[b];
    vet[b] = t;
}

void Utils::printArray(std::string first, std::vector<int>& vet, std::string separator, std::string last, std::ostream& out) {
    if (vet.empty()) {
        out << first << last << std::endl;
        return;
    }
    out << first;
    for (int i = 0; i < vet.size() - 1; i++) {
        out << vet[i] << separator;
    }
    out << vet[vet.size() - 1] << last << std::endl;
}

void Utils::printArray(std::string first, int* vet, int vet_length, std::string separator, std::string last, std::ostream& out) {
    if (vet_length == 0) {
        out << first << last << std::endl;
        return;
    }
    out << first;
    for (int i = 0; i < vet_length - 1; i++) {
        out << vet[i] << separator;
    }
    out << vet[vet_length - 1] << last << std::endl;
}

void Utils::insertValues(std::vector<int>& vet, std::istream& in) {
    std::string line = "";
    getline(in, line);
    std::istringstream s(line);
    int value = 0;
    while (s >> value) {
        vet.push_back(value);
    }
}

int Utils::insertValues(int* vet, int max_len, std::istream& in) {
    std::string line = "";
    getline(in, line);
    std::istringstream s(line);
    int value = 0, ret = 0;
    while (s >> value && ret < max_len) {
        //std::cout<<value<<std::endl;
        vet[ret++] = value;
    }
    return ret;
}

int Utils::readInt(std::string frase, std::istream& in) {
    int valore = 0;
    std::cout << frase; in >> valore;
    return valore;
}