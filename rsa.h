#ifndef RSA_H
#define RSA_H
#include "functions.h"

class RSA
{
    public:
        RSA();
        RSA(short);
		virtual ~RSA(void);
		RSA(string);
		vecInt encriptar(string);
		string encript(string);
		string encriptx(string, nInt, nInt, string);
		string desencriptar(vecInt);
		string decript(vecInt);
		string decript_b(vecInt);
		string desencript(string, nInt, nInt);
		string encripta(string, nInt, nInt, string);
		string desencripta(string, nInt, nInt, nInt);
    protected:
    private:
        nInt d;
		nInt e;
		nInt n;
		nInt p;
		nInt q;
		nInt phi;
		string alfabeto;
};

#endif // RSA_H

