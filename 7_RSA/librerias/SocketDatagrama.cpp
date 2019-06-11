#include "SocketDatagrama.hpp"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

SocketDatagrama::SocketDatagrama(uint16_t puerto) {
	udp_socket = socket(AF_INET, SOCK_DGRAM, 0);	
	if (udp_socket == -1){
		std::cerr << "Error al crear el socket: "<<strerror(errno) << std::endl;
		exit(0);
	}
	memset(&direccionLocal,0,sizeof direccionLocal);
	direccionLocal.sin_family=AF_INET;
	direccionLocal.sin_addr.s_addr=htonl(INADDR_ANY); 
	direccionLocal.sin_port=htons(puerto);
	timeout=false;
	//Reusar direccion
	int yes=1;
	if (setsockopt(udp_socket,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
		std::cerr << "Error en el reuseaddr: "<<strerror(errno) << std::endl;	
		exit(0);
	}
	//Bind
	if (bind(udp_socket,(struct sockaddr *) &direccionLocal,sizeof direccionLocal) == -1) {
		std::cerr << "Error en el bind: "<<strerror(errno) << std::endl;	
		exit(0);
    }
}

SocketDatagrama::~SocketDatagrama(void){ close(udp_socket);}

int SocketDatagrama::recibe(PaqueteDatagrama &p) {
	int tam;
	struct sockaddr_in direccionForeanea;
	socklen_t n = sizeof(direccionForeanea);
	memset(p.obtieneDatos(),'\0',p.obtieneLongitud());	
	//Recibe datos
	if ((tam = recvfrom(udp_socket , p.obtieneDatos(), p.obtieneLongitud(), 0,(struct sockaddr *)&direccionForeanea, &n)) == -1){
		if(errno==EAGAIN||errno==EWOULDBLOCK){//Expiro el socket
			std::cerr << "Socket Timeout. "<< std::endl;
			timeout=true;
		}else{//Otro tipo de error
			std::cerr << "Error al recibir el mensaje: "<<strerror(errno) << std::endl;
			timeout=false;
		}
	}else{//Ningun error
		p.inicializaIP(std::string(inet_ntoa(direccionForeanea.sin_addr)));
		p.inicializaPuerto(htons(direccionForeanea.sin_port));			
		timeout=false;
	}			
	unsetTimeout();
	return tam;	
}

int SocketDatagrama::envia(PaqueteDatagrama &p) {
	//Relleno de los campos destino
	struct sockaddr_in direccionForeanea;
	memset(&direccionForeanea,0,sizeof direccionForeanea);
	direccionForeanea.sin_family=AF_INET;
	direccionForeanea.sin_addr.s_addr=inet_addr(p.obtieneIP().c_str());
	direccionForeanea.sin_port=htons(p.obtienePuerto());
	int tam=0;
	//Envio de datos
	if ((tam = sendto(udp_socket ,p.obtieneDatos(),p.obtieneLongitud(), 0,(struct sockaddr *)&direccionForeanea,sizeof direccionForeanea)) == -1)
		std::cerr << "Error al enviar el mensaje: "<<strerror(errno) << std::endl;		
	//Retorno de la longitud enviada
	return tam;
}

void SocketDatagrama::setTimeout(time_t segundos, suseconds_t microsegundos){	
	struct timeval timeout;      
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;		
    if (setsockopt (udp_socket , SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,sizeof(timeout)) ==-1 ){
        std::cerr << "Error al asignar el timeout: "<<strerror(errno) << std::endl;
    }
}

void SocketDatagrama:: unsetTimeout(void){setTimeout(0,0);}
	
bool SocketDatagrama::haExpirado(void){return timeout;}

void SocketDatagrama::cerrarSocket(void){close(udp_socket);}
