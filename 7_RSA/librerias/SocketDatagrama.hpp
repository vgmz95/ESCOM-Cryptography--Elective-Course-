#ifndef SOCKETD_H
#define SOCKETD_H
#include <netinet/in.h>
#include "PaqueteDatagrama.hpp"
class SocketDatagrama {
	private:
		struct sockaddr_in direccionLocal;		
		int udp_socket;
		bool timeout;
		
	public:
		SocketDatagrama(uint16_t puerto);
		~SocketDatagrama(void);
		
		int recibe(PaqueteDatagrama& p);
		int envia(PaqueteDatagrama& p);
		
		void setTimeout(time_t segundos, suseconds_t microsegundos);
		void unsetTimeout(void);			
		
		bool haExpirado(void);		
		void cerrarSocket(void);		
};

#endif
