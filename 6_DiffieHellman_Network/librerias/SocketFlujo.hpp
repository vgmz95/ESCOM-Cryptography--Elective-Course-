#ifndef SOCKETD_H
#define SOCKETD_H

#include "Paquete.hpp"
#include <arpa/inet.h>
#include <string>

class SocketFlujo {
	private:
		struct sockaddr_in direccionLocal;
		struct sockaddr_in direccionForeanea;
		int socket_fd;		
		
	public:
		SocketFlujo();
		SocketFlujo(int);
		~SocketFlujo(void);
		void conectar(std::string host, uint16_t puerto);
		void enlazar(uint16_t puerto);
		void escucha();
		SocketFlujo aceptar();
		int recibe(Paquete& p);
		int envia(Paquete& p);
		void inicializaDireccForanea(struct sockaddr_in);
		void cerrarConexion();		
};

#endif
