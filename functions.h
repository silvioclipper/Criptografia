#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

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

typedef long long int nInt;
typedef vector<nInt> vecInt;
typedef vector<vecInt> matInt;

typedef unsigned long long int u_nInt;
typedef vector<u_nInt> vec_uInt;
typedef vector<vec_uInt> mat_uInt;

nInt mcd(nInt a, nInt b);
vecInt ext_mcd(nInt a, nInt b);
vecInt criba(nInt n);
vecInt criba_nm(nInt m, nInt n);
nInt inversa_mult(nInt a, nInt n);
vecInt numeros_long_bits(int16_t t);
vecInt random_keys(int16_t t);
nInt exponenciacion(nInt m, nInt e, nInt n);
nInt resto_chino(matInt m);
int16_t get_long_bits(nInt ne);
vecInt dec_to_binary(nInt n);
nInt exponenciacion_rap(nInt a, vecInt kb, nInt n);
vecInt factores_primos(nInt n);
nInt aplicar_rc(nInt m, nInt d, nInt n, vecInt fact);
void print_vector(vecInt v);
bool save_msje(vecInt msj, string data);
short long_dig(nInt n);
string msj_to_dig(string m, string alf);
string completa(string m, nInt n, string alf);
string separa_grupos(string m, nInt n, string alf);
vecInt str_to_vect(string m, nInt t);
vecInt to_block(string m, nInt n, string alf);
vecInt app_exp_rap(vecInt v, nInt p, nInt q, nInt d, nInt n);
void save_keys(vecInt llaves);
string rellena_ceros(nInt v, nInt t);
string to_groups(string m, nInt n);
string complete(string m, nInt n, nInt val);
nInt total_groups(nInt s_m, nInt s_n);
vecInt calc_exp_rap(vecInt vec, vecInt e_bi, nInt n);
vecInt msj_to_vec(string m, string alf);
string complete_vec(vecInt vec, nInt n);
void save_encript(string msj, string dest);
vecInt calc_rc(vecInt vec, nInt d, nInt p, nInt q);
string vec_to_text(vecInt vec, string alf);

#endif // FUNCTIONS_H_INCLUDED
