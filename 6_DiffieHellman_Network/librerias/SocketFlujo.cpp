#include "SocketFlujo.hpp"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

SocketFlujo::SocketFlujo() {
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd==-1){
		std::cerr << "Error al crear el socket: "<<strerror(errno) << std::endl;
		exit(0);
	}
	return;	
}

SocketFlujo::SocketFlujo(int s){
	socket_fd=s;
	}

void SocketFlujo::conectar(std::string host, uint16_t puerto){
	memset(&direccionForeanea,0,sizeof (direccionForeanea));
	direccionForeanea.sin_family = AF_INET;
	direccionForeanea.sin_addr.s_addr = inet_addr(host.c_str());
	direccionForeanea.sin_port = htons(puerto);	
	if(connect(socket_fd,(struct sockaddr*) &direccionForeanea,sizeof (direccionForeanea)) == -1){
			std::cerr << "Error al conectarse: "<<strerror(errno) << std::endl;
			exit(0);
	}
	return;	
}

SocketFlujo::~SocketFlujo(void) { 
	if (close(socket_fd) == -1){
		std::cerr << "Error al cerrar el socket: "<<strerror(errno) << std::endl;
		exit(0);
	}
	return;	 
}
	
void SocketFlujo::cerrarConexion() { 
	if( (close(socket_fd) == -1) ){
		std::cerr << "Error al cerrar el socket: "<<strerror(errno) << std::endl;
		exit(0);
	}
	return;	
}

int SocketFlujo::recibe(Paquete &p) {
	ssize_t tam;	
	if( (tam=read(socket_fd, p.obtieneDatos(), p.obtieneLongitud() ))== -1){
		std::cerr << "Error al recibir: "<<strerror(errno) << std::endl;
		exit(0);
	}	
	return tam;	
}

int SocketFlujo::envia(Paquete &p) {
	ssize_t tam;	
	if( (tam=write(socket_fd, p.obtieneDatos(), p.obtieneLongitud()))== -1){
		std::cerr << "Error al enviar: "<<strerror(errno) << std::endl;
		exit(0);
	}
	return tam;
}

void SocketFlujo::enlazar(uint16_t puerto){
	memset(&direccionLocal,0,sizeof direccionLocal);
	direccionLocal.sin_family = AF_INET;
	direccionLocal.sin_addr.s_addr = htonl(INADDR_ANY);
	direccionLocal.sin_port = htons(puerto);	
	if (bind(socket_fd, (struct sockaddr *)&direccionLocal, sizeof direccionLocal)==-1){
		std::cerr << "Error al hacer el bind: "<<strerror(errno) << std::endl;
		exit(0);
	}
	return;
}

void SocketFlujo::escucha(){
	if (listen(socket_fd, 1)==-1){
		std::cerr << "Error en el listen: "<<strerror(errno) << std::endl;
		exit(0);
	}
	return;
}

SocketFlujo SocketFlujo::aceptar(){
	struct sockaddr_in dest;
	socklen_t socksize = sizeof(struct sockaddr_in);
	int sock=accept(socket_fd, (struct sockaddr *)&dest, &socksize);
	if(sock==-1){
		std::cerr << "Error en el accept: "<<strerror(errno) << std::endl;
		exit(0);
	}
	SocketFlujo socket_aceptado(sock);
	socket_aceptado.inicializaDireccForanea(dest);	
	return socket_aceptado;
}

void SocketFlujo::inicializaDireccForanea(struct sockaddr_in dest){
	memcpy(&direccionForeanea,&dest,sizeof(struct sockaddr_in));
	return;
}




