#ifndef DATAGRAM_H_
#define DATAGRAM_H_

#include <cstring>

class Paquete{
	private:
		char *datos;		
		size_t tamanio;
	public:
		Paquete(char *datos, size_t tamanio);
		Paquete(size_t);
		~Paquete();
		size_t obtieneLongitud();
		char *obtieneDatos();
		void inicializaDatos(char*, size_t l);
};

#endif
