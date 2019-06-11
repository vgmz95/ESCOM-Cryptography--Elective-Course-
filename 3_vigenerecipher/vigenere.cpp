#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

void encrypt (ifstream &input_file,string key,char *letters_uppercase);
void decrypt (ifstream &input_file,string key,char *letters_lowercase);
int addInverse(int n);

int main(){
	char letters_lowercase[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char letters_uppercase[]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	//Menu
	cout<<"Vigenere cipher\n";
	cout<<"a)Encrypt\n";
	cout<<"b)Decrypt\n";
	cout<<"Select an operation: ";
	char opt;
	cin>>opt;
	cout<<"Insert filename: ";
	char filename[256];
	cin>>filename;
	cout<<"Insert key: ";
	string key;
	cin>>key;
	//Opening input file
	ifstream input_file;
	input_file.open(filename,ios::in|ios::ate);
	
	if(opt=='a'){
		cout<<"Encrypt selected\n";
		cout<<"Key:"<<key<<" File: "<<filename<<" Key lenght: "<<key.length()<<endl;
		encrypt(input_file,key,letters_uppercase);
		cout<<"Done."<<endl;
	}else if(opt=='b'){
		cout<<"Decrypt selected\n";
		cout<<"Key:"<<key<<" File: "<<filename<<" Key lenght: "<<key.length()<<endl;
		decrypt(input_file,key,letters_lowercase);
		cout<<"Done."<<endl;
		
	}else{
		cout<<"Invalid option";		
	}
	return 0;
}


void encrypt(ifstream &input_file,string key,char *letters_uppercase){
	//Creating output file
	ofstream output_file;
	output_file.open ("c_out.txt",ios::out);
	//Buffer
	int filesize;
	filesize = input_file.tellg();
	char *buffer= new char [filesize];
	input_file.seekg (0, ios::beg);
    input_file.read (buffer, filesize);
    input_file.close();
    //Encrypt
	for(int i=0;i<filesize;i++){
		if(islower(buffer[i])){
		output_file<<letters_uppercase[((buffer[i]-97) + (key[i%key.length()]-97))%26];
		}		
	}
	//Closing stream
	output_file.close();
	delete buffer;
	return;	
	}

void decrypt (ifstream &input_file,string key,char *letters_lowercase){
	//Creating output file
	ofstream output_file;
	output_file.open ("m_out.txt",ios::out);
	//Buffer
	int filesize;
	filesize = input_file.tellg();
	char *buffer= new char [filesize];
	input_file.seekg (0, ios::beg);
    input_file.read (buffer, filesize);
    input_file.close();
    //Decrypt
	for(int i=0;i<filesize;i++){
		if(isupper(buffer[i])){
		output_file<<letters_lowercase[((buffer[i]-65) + addInverse(key[i%key.length()]-97))%26];
		}		
	}    
    //Closing stream
	output_file.close();
	delete buffer;	
	return;
	}
	
int addInverse(int n){
	return 26-n;
	
	}
