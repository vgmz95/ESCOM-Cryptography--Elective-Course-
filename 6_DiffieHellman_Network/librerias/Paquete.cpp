#include"Paquete.hpp"

Paquete::Paquete(char* data, size_t tamanio) {
	datos = new char[tamanio];
	memcpy(datos,data, tamanio);
	this->tamanio=tamanio;
	return;}
	

Paquete::Paquete(size_t tamanio) {
	datos = new char[tamanio];
	this->tamanio=tamanio;
	return;}

Paquete::~Paquete() { 
	delete[] datos; 
	return;}


size_t Paquete::obtieneLongitud() { return tamanio; }

char* Paquete::obtieneDatos() { return datos; }


void Paquete::inicializaDatos(char* d, size_t t) {
	datos = new char[t];
	memcpy(datos, d, t);
	tamanio = t;
	return;}
