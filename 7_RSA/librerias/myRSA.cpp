#include <iostream>

//OPENSSL
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/sha.h>

int padding = RSA_PKCS1_PADDING;

RSA * createRSA(unsigned char * key,int publick){
    RSA *rsa= NULL;
    BIO *keybio ;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio==NULL)    {
        std::cerr<<"Failed to create key BIO"<<std::endl;
        return 0;
    }
    if(publick){
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa,NULL, NULL);
    }
    else{
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL);
    }
    if(rsa == NULL){
        std::cerr<<"Failed to create RSA"<<std::endl;
    }
 
    return rsa;
}
 
int public_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted){
    RSA * rsa = createRSA(key,1);
    int result = RSA_public_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}

int private_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted){
    RSA * rsa = createRSA(key,0);
    int  result = RSA_private_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}
 
 
int private_encrypt(unsigned char * data,int data_len,unsigned char * key, unsigned char *encrypted){
    RSA * rsa = createRSA(key,0);
    int result = RSA_private_encrypt(data_len,data,encrypted,rsa,padding);
    return result;
}
int public_decrypt(unsigned char * enc_data,int data_len,unsigned char * key, unsigned char *decrypted){
    RSA * rsa = createRSA(key,1);
    int  result = RSA_public_decrypt(data_len,enc_data,decrypted,rsa,padding);
    return result;
}
 
void printLastError(const char *msg){
    char * err = new char [130];;
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    std::cerr<<msg<<" ERROR: "<<err<<std::endl; 
    delete [] err;
}

struct RSAmessage{
	int bytes;
	char name[50] ;
	unsigned char data[256];
	unsigned char sign[256];	
};
