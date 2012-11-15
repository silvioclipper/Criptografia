#include <iostream>
#include "rsa.h"

using namespace std;

int main()
{

    RSA a;
    nInt e = 59197;
    nInt n = 2680590083;
    nInt p = 46807;
    nInt q = 57269;
    nInt d = 2120453389;
    string msj = "hola esto es un Mensaje de PRUEBA! veamos, que tal resulta";
    string destino = "jjhc@sectorj.net";
    string cifrado = a.encripta(msj, e, n, destino);
    cout << cifrado << endl;
    string enc = "22471057250848153696170412120625864195291708376211029827167510586292092077493327037557524501633959252626245367129487618222834632420330223553109597846006299359502269644956119499569207631882601365018009";
    string decifrado = a.desencripta(enc, d, p, q);
    cout << decifrado << endl;
    return 0;
}
