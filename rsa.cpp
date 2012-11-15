#include "rsa.h"

RSA::RSA()
{
    alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890“”¿?¡!áéíóúÁÉÍÓÚ´,;:-_<>@*+";
    //alfabeto = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890“”¿?¡!";
}

RSA::RSA(short b)
{
    alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890“”¿?¡!áéíóúÁÉÍÓÚ´,;:-_<>@*+";

	vecInt claves = random_keys(b);
	p = 46807;// claves[0];
	q = 57269;//claves[1];
	e = 59197;//claves[2];
	n = 2680590083;//claves[3];
	phi = 2680486008;//claves[4];
	d = 2120453389;//claves[5];
	//bool x = f.save_keys(claves);

	cout << "p:" << p << endl;
	cout << "q:" << q << endl;
	cout << "e:" << e << endl;
	cout << "n:" << n << endl;
	cout << "phi:" << phi << endl;
	cout << "d:" << d << endl;

}

RSA::RSA(string txt)
{
    alfabeto = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz 1234567890“”¿?¡!áéíóúÁÉÍÓÚ´,;:-_<>@*+";
	ofstream myfile (txt.c_str());
    if (myfile.is_open())
    {
        myfile << alfabeto << "\n";
        myfile.close();
    }
    else cout << "Archivo no disponible";
}

RSA::~RSA()
{
    //dtor
}

vecInt RSA::encriptar(string txt)
{
    vecInt result;
    nInt tam = txt.size();
    vecInt e_bi = dec_to_binary(e);
    for(nInt i=0; i < tam; i++)
    {
        nInt v = alfabeto.find(txt[i]);
        nInt exp = exponenciacion_rap(v,e_bi,n);
        result.push_back(exp);
    }
    vecInt keys;
    keys.push_back(this->p);
    keys.push_back(this->q);
    keys.push_back(this->e);
    keys.push_back(this->n);
    keys.push_back(this->phi);
    keys.push_back(this->d);
    save_keys(keys);
    return result;
}

string RSA::desencriptar(vecInt v)
{
    string result;
    nInt tam = v.size();
    vecInt d_bi = dec_to_binary(d);
    for(nInt i=0; i < tam; i++)
    {
        nInt val = exponenciacion_rap(v[i], d_bi, n);
        result.push_back(alfabeto[val]);
    }

    return result;
}

string RSA::decript(vecInt v)
{
    string result;
    nInt tam = v.size();

    vecInt fac_primos;
    fac_primos.push_back(this->p);
    fac_primos.push_back(this->q);

    for(nInt i=0; i < tam; i++)
    {
        nInt val = aplicar_rc(v[i], d, n, fac_primos);
        result.push_back(alfabeto[val]);
    }

    return result;


}


string RSA::encript(string m)
{
    vecInt r = to_block(m, this->n, alfabeto);
    nInt tam = r.size();
    string resulta;
    nInt t_n = long_dig(this->n);
    stringstream xs;
    nInt qs;
    vecInt e_bi = dec_to_binary(this->e);
    for(nInt i=0; i < tam; i++)
    {
        qs = exponenciacion_rap(r[i], e_bi, this->n);
        nInt t_r = long_dig(qs);
        while(t_r < t_n)
        {
            xs << '0';
            t_r++;
        }
        xs << r[i];
        resulta += xs.str();
    }

    return resulta;

}

string RSA::decript_b(vecInt v)
{
    stringstream a;
    nInt tam = v.size();
    nInt x, y, z;
    string msj;

    v = app_exp_rap(v, this->p, this->q, this->d, this->n);
    x = long_dig(this->n) - 1;

    for(nInt i=0; i < tam; i++)
    {
        y = long_dig(v[i]);
        z = x-y;
        while(z > 0)
        {
            a << 0;
            z--;
        }
        a << v[i];
    }
    msj = a.str();
    nInt tx = msj.size()/2;
    msj = separa_grupos(msj, 2, alfabeto);

    vecInt r = str_to_vect(msj, tx);
    string result;
    nInt tams = r.size();

    vecInt fac_primos;
    fac_primos.push_back(this->p);
    fac_primos.push_back(this->q);
    vecInt d_bi = dec_to_binary(this->d);
    for(nInt i=0; i < tams; i++)
    {
        nInt val = exponenciacion_rap(r[i], d_bi, this->n);
        result.push_back(alfabeto[r[i]]);
    }

    return result;
}


string RSA::encriptx(string m, nInt ex, nInt nx, string dest)
{
    this->e = ex;
    this->n = nx;
    string r = encript(m);

    string file = dest + "_msj.txt";
    ofstream myfile (file.c_str());

    if (myfile.is_open())
    {
        myfile << r << "#" << dest;
        myfile.close();
    }
    return r;
}

string RSA::desencript(string m, nInt dx, nInt nx)
{
    vecInt q;
    this-> n = nx;
    this-> d = dx;
    nInt tam = m.size();
    nInt xs = long_dig(this->n)-1;
    nInt t = tam/xs;

    m = separa_grupos(m, t, alfabeto);
    q = str_to_vect(m, t);
    string res = decript_b(q);
    return res;
}


string RSA::encripta(string msj, nInt ex, nInt nx, string destino)
{
    this->e = ex;
    this->n = nx;

    nInt s_n = long_dig(this->n);
    nInt size_n = s_n-1;
    nInt chr = this->alfabeto.find('x');
    vecInt e_bi = dec_to_binary(this->e);

    string dig = msj_to_dig(msj, this->alfabeto);
    dig = complete(dig, size_n, chr);
    nInt s_men = dig.size();

    dig = to_groups(dig, size_n);

    nInt t = total_groups(s_men, size_n);

    vecInt val = str_to_vect(dig, t);

    vecInt exp = calc_exp_rap(val, e_bi, this->n);
    string cifrado = complete_vec(exp, s_n);

    save_encript(cifrado, destino);

    return cifrado;
}

string RSA::desencripta(string msj, nInt dx, nInt px, nInt qx)
{
    this-> d = dx;
    this-> p = px;
    this-> q = qx;
    this-> n = px*qx;
    nInt s_mens = msj.size();
    nInt s_n = long_dig(this->n);
    nInt s_a = long_dig(alfabeto.size());
    nInt tx = total_groups(s_mens, s_n);

    msj = to_groups(msj, s_n);

    vecInt vec = str_to_vect(msj, tx);

    vecInt rc = calc_rc(vec, this->d, this->p, this->q);
    string d = complete_vec(rc, s_n-1);

    nInt s_men = d.size();

    nInt t = total_groups(s_men, s_a);

    d = to_groups(d, s_a);

    vecInt r = str_to_vect(d, t);

    string desencritado = vec_to_text(r, this->alfabeto);

    return desencritado;
}
