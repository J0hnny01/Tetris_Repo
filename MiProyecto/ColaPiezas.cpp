#include "ColaPiezas.h"
#include <cstdlib> 

NodoCola::NodoCola(int tipo) {
	this->tipoPieza = tipo;
	this->siguiente = nullptr;
}


void ColaPiezas::encolar(int tipo) {
	NodoCola* nuevoNodo = new NodoCola(tipo);	
	if (frente == nullptr) { 
		frente = nuevoNodo;
		final = nuevoNodo;
	} else { 
		final->siguiente = nuevoNodo;
		final = nuevoNodo;
	}
	cantidad++;
}

void ColaPiezas::generarBolsa() {
	int bolsa[7] = {0, 1, 2, 3, 4, 5, 6};
	for (int i = 6; i > 0; i--) {
		int j = rand() % (i + 1); 
		int temp = bolsa[i];
		bolsa[i] = bolsa[j];
		bolsa[j] = temp;
	}
	if (final != nullptr) {
		if (bolsa[0] == final->tipoPieza) {
			int temp = bolsa[0];
			bolsa[0] = bolsa[1];
			bolsa[1] = temp;
		}
	}
	for (int i = 0; i < 7; i++) {
		encolar(bolsa[i]);
	}
}
