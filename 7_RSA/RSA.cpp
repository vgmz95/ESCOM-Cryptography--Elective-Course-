//Sockets & RSA & MD5
#include "./librerias/SocketDatagrama.hpp"
#include "./librerias/myRSA.cpp"

//C++
#include <iostream>
#include <cstring>
#include <fstream>
//POSIX
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

std::string getFileData(string filename);

int main(int argc, char *argv[]){
	// Uso: ./RSA local_port name
	if(argc!=3){
		cout<<"Usage: ./RSA local_port your_name"<<endl;
		exit(0);
	}
	string name=string(argv[2]);
	SocketDatagrama socket(atoi(argv[1]));
	string filename="";
	cout<<"Insert filename of your private key: ";
	getline(cin,filename);	
	string myprivateKey=getFileData(filename);
	cout<<"Insert filename of the public foreign key: ";
	getline(cin,filename);
	string foreignpublicKey=getFileData(filename);
	cout<<"Insert the ip you want to comunicate: ";
	string ip;
	getline(cin,ip);
	cout<<"Insert port: ";
	string port;
	getline(cin,port);
	
	pid_t pid;
	pid=fork();
	if(pid>0){//Main process, sender
		cout<<"Type your messages: "<<endl;
		string out_message="";
		struct RSAmessage out_c;
		int encrypted_length=0;
		unsigned char digest[SHA_DIGEST_LENGTH];
		PaqueteDatagrama *pack;
		
		while(true){
			getline(cin,out_message);			
			//Encrypt message
			if((encrypted_length=public_encrypt((unsigned char *)out_message.c_str(),out_message.size(),(unsigned char *)foreignpublicKey.c_str(),out_c.data))== -1){
				printLastError("Public Encrypt failed");
				exit(0);
			}
			//Hash function			
			SHA((unsigned char *)out_message.c_str(), out_message.size(),digest);
			//Sing Hash
			if((encrypted_length=private_encrypt(digest,strlen((const char *)digest),(unsigned char *)myprivateKey.c_str(),out_c.sign)) == -1){
				printLastError("Private Encrypt failed");
				exit(0);
			}
			//Send message to peer
			strcpy(out_c.name,name.c_str());
			out_c.bytes=out_message.size();
			pack=new PaqueteDatagrama((char*)&out_c, sizeof out_c, ip,stoi(port));
			socket.envia(*pack);
			delete pack;
			cout<<"Message sent!"<<endl;
		}
	
	}else if(pid==0){//Child process, receiver
		struct RSAmessage in_c;
		PaqueteDatagrama pack=PaqueteDatagrama(sizeof in_c);
		unsigned char decrypted[2048/8];
		unsigned char decrypted_hash[2048/8];
		char plain_text[2048/8];
		unsigned char digest[SHA_DIGEST_LENGTH];
		while(true){
			socket.recibe(pack);
			memcpy(&in_c,pack.obtieneDatos(),sizeof in_c);
			//Message
			int decrypted_length = private_decrypt(in_c.data,2048/8,(unsigned char *)myprivateKey.c_str(), decrypted);
			if(decrypted_length == -1){
				//printLastError("Private Decrypt failed ");
			}
			memset(plain_text,'\0',2048/8);
			memcpy(plain_text,decrypted,in_c.bytes);
			cout<<"Message from "<<in_c.name<<" : "<<plain_text<<endl;
			
			//Sign
			SHA((const unsigned char*)plain_text,in_c.bytes,digest);
			decrypted_length = public_decrypt(in_c.sign,2048/8,(unsigned char* )foreignpublicKey.c_str(), decrypted_hash);
			if(decrypted_length == -1){
				//printLastError("Public Decrypt failed");
			}
			memset(decrypted_hash+SHA_DIGEST_LENGTH,'\0',2048/8 -SHA_DIGEST_LENGTH);
			//Comparing hashes
			if(strcmp((const char*)decrypted_hash,(const char*)digest)!= 0){				
				cout<<"Hash don't match!!!!"<<endl;
			}else{				
				cout<<"The hashes are equal"<<endl;
			}
		}
		
	}else{//Error
		cerr << "Error in fork: "<<strerror(errno) << endl;
		exit(0);
	}
	
	wait(0);	
	return 0;
	
}


std::string getFileData(string filename){
	string data="";
	streampos size;
	ifstream file (filename, ios::in|ios::binary|ios::ate);
	size = file.tellg();
	char *buffer=new char [size];
    file.seekg (0, ios::beg);
    file.read (buffer, size);
    file.close();
    data=string(buffer);
    delete[] buffer;	
	return data;
}
