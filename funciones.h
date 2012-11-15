#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

typedef int64_t kobra; //Entero de 64 bits
typedef vector<kobra> vkobra; // Vector de Enteros de 64 bits
typedef vector<vkobra> mkobra; // Matriz de Enteros de 64 bits

class Funciones
{
    public:
        Funciones();
        virtual ~Funciones();
        kobra euclides(kobra, kobra); // Funciones Euclides, devuelve el mcd de dos numeros.
		vkobra euclides_ext(kobra, kobra); // Funcion Euclides Extendido, devuelve el mcd y la inversa de dos numeros.
		vkobra criba(kobra); // Funcion criba simple, trabajo con vectores de interos.
		vkobra cribi(kobra); // Funcion criba simple, trabajo con vector de booleanos
		vkobra criba_dos(kobra, kobra); // Funcion criba entre dos numeros, trabaja con vector de enteros
		vkobra criba_mn(kobra, kobra); // Funcion criba entre dos numeros, trabaja con vector de bool
        vkobra divi(kobra, kobra); // Funcion para hallar la division entre dos enteros, devuelve resultado y modulo
		kobra inversa(kobra, kobra); // Funcion para hallar la inversa de un valor a-1 mod n. Ej (19^-1 mod 143 -> inversa(19,143) -> Result: 19).
		vkobra borrado(vkobra, kobra); // Funcion que elimina todas las ocurrencias de un vector.

		vkobra numeros_long_bits(short); // Funcion que halla el valor maximo y minimo de una determinada longitud de bits. (Ej: numero_long_bits(5); halla el mínimo y máximo valor con 5 bits: min=32, max=63)
		vkobra random_keys(short); // Generacion aleatoria de clases de acuerdo a una cantidad dada de bits.
		kobra exponenciacion(kobra, kobra, kobra); // Funcion para hallar la exponenciación modular.
		kobra resto_chino(mkobra); //Funcion que realiza el teorema del resto chino
		vkobra dec_to_binary(kobra); // Funcion que convierte un numero decimal a un vector binario
		short get_long_bits(kobra); // Funcion que halla el tamaño de bits de un numero dado.
		kobra exponenciacion_rap(kobra, kobra, kobra);
		kobra mcdMenorResto(kobra, kobra);
		vkobra factores_primos(kobra);
		kobra aplicar_rc(kobra, kobra, kobra, vkobra);
		void print_vector(vkobra);
		vkobra strick_keys(kobra, kobra);
		bool save_keys(vkobra);
		bool save_msje(vkobra, string);
		short long_dig(kobra);

    protected:
    private:
};

#endif // FUNCIONES_H
