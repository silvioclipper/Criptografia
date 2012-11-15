#include "functions.h"

nInt mcd(nInt a, nInt b)
{
    nInt r = a % b;
    while(r)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}

vecInt ext_mcd(nInt a, nInt b)
{
    nInt q, r1, r2, r, s1, s2, s, t1, t2, t;
    bool f = true;

	if( a > b )
	{

		r1 = a;
		r2 = b;
	}else
	{
	    f = false;
		r1 = b;
		r2 = a;
	}

    s1 = 1;
    t1 = 0;

    s2 = 0;
    t2 = 1;

    while(r2 > 0)
    {
        q = r1 / r2;

        r = r1 - (q*r2);
        r1 = r2;
        r2 = r;

        s = s1 - (q * s2);
        s1 = s2;
        s2 = s;

        t = t1 - (q * t2);
        t1 = t2;
        t2 = t;
    }

    vecInt respuesta;
    respuesta.push_back(r1);
    if(f)
    {
        respuesta.push_back(s1);
        respuesta.push_back(t1);

    }else{
        respuesta.push_back(t1);
        respuesta.push_back(s1);
    }
    return respuesta;
}

vecInt criba(nInt n)
{
    vecInt primos;
    for(nInt i=2; i < n; i++)
        primos.push_back(i);

	vecInt::iterator it;

    for(it = primos.begin(); it < primos.end(); it++)
    {
        vecInt::iterator k;
        for(k=it+1; k < primos.end(); k++)
        {
            if(*k % *it == 0)
                primos.erase(k);
        }
    }

    return primos;
}

vecInt criba_nm(nInt m, nInt n)
{
    vecInt primos;
    nInt pot = sqrt(n);
    vecInt min_pr = criba(pot);
	vecInt::iterator iter;

    for(nInt i=m; i < n; i++)
        primos.push_back(i);


    for(nInt j=0; j< min_pr.size();j++)
    {
		for(nInt k=0 ; k < primos.size(); k++)
        {
			if(primos[k] % min_pr[j] == 0)
                primos[k] = 0;
        }
    }
	vecInt res;
	for(nInt r=0; r < primos.size(); r++)
	{
		if(primos[r] != 0)
			res.push_back(primos[r]);
	}

    return res;
}

nInt inversa_mult(nInt a, nInt n)
{
    nInt x = a;
	if(a < 0)
		x += n;
	else
	{
		vecInt e = ext_mcd(a, n);
		if(e[0] == 1)
		{
			x = e[1];
			if(x < 0)
				x += n;
		}else{
			x = -1;
		}
		x = nInt(x);
	}

	return x;
}

vecInt numeros_long_bits(int16_t t)
{
	vecInt res;
	nInt mini = pow(2,t-1);
    nInt maxi = 0;
	for(int i = 0; i <= t-1; i++)
		maxi += pow(2,i);

	res = criba_nm(mini,maxi);
	return res;
}

vecInt random_keys(int16_t t)
{
	vecInt primos = numeros_long_bits(t);
	nInt tam = primos.size();
	srand(time(NULL));

    nInt a = rand() % tam;
    nInt b = rand() % tam;

	while(a == b)
	{
		a = rand() % tam;
		b = rand() % tam;
	}

	nInt n = primos[a]*primos[b];
	nInt c = rand() % tam;
	nInt e = mcd(primos[c], n);
	nInt phi = (primos[a]-1)*(primos[b]-1);

	while(e != 1 || c == a || c == b)
	{
		c = rand() % tam;
		e = mcd(primos[c], n);
	}

	nInt inv = inversa_mult(primos[c], phi);


	vecInt result;
	result.push_back(primos[a]);
	result.push_back(primos[b]);
	result.push_back(primos[c]);
	result.push_back(n);
	result.push_back(phi);
	result.push_back(inv);

	return result;
}

nInt exponenciacion(nInt m, nInt e, nInt n)
{
	nInt r = 1;
	for(nInt i = 1; i <= e; i++)
	{
		r = (r*m)%n;
	}
	return r;
}


nInt resto_chino(matInt m)
{
    nInt tam = m.size();
    nInt _p = 1;
    nInt ext = 0;

    nInt mcde;
    bool c_pr = true;

    for(nInt i=0; i < tam-1; i++)
    {
        mcde = mcd(m[i][2],m[i+1][2]);
        if(mcde!=1)
            c_pr = false;
    }

    if(c_pr)
    {

        for(nInt j=0; j < tam; j++)
        {
            _p *= m[j][2];
        }


        for(nInt i=0; i < tam; i++)
        {
            if(m[i][0] > 1)
            {
                m[i][1] =  (m[i][1] * inversa_mult(m[i][0],m[i][2])) % m[i][2];
                m[i][0] = 1;
            }

            nInt _pi = _p/m[i][2];
            nInt _qi = inversa_mult(_pi,m[i][2]);
            ext += ((m[i][1]%_p)* (_pi%_p) * (_qi%_p)) % _p;
        }

        nInt resul = ext % _p;
        return resul;
    }
    return -1;

}

int16_t get_long_bits(nInt ne)
{
    int16_t i=0;
    while(true)
    {
        nInt var = pow(2,i);
        if( ne < var)
            break;
        i++;
    }
    return i-1;
}

vecInt dec_to_binary(nInt n)
{
    int t;
    vecInt r;
    bool f = false;
    t = get_long_bits(n);

    for(int i=t; i >=0; i--)
    {

        if(!f && n>>i == 1)
            f = true;
        if(f)
           r.push_back(n>>i);
        if(n>>i != 0)
            n -= pow(2,i);
    }

    nInt x = r.size();
    vecInt rs;
    int ii = 1;
    for(int i=x; i > 0; i--,ii++)
        rs.push_back(r[x-ii]);

    return rs;
}

nInt exponenciacion_rap(nInt a, vecInt kb, nInt n)
{
    nInt t = kb.size();
    nInt b = 1;
    nInt aa;
    /*if(k==0)
        return b;*/
    aa = a;
    if(kb[0] == 1)
        b = a;

    for(nInt i=1; i < t; i++)
    {
        aa = (aa*aa) % n;
        if(kb[i] == 1)
            b = (aa*b) % n;
    }

    return b;
}

vecInt factores_primos(nInt n)
{
    vecInt r;
    vecInt primos = criba(sqrt(n));
    nInt tam = primos.size()-1;
    nInt first = 0, second = 0;
    while(tam >=0)
    {
        if(n%primos[tam] == 0)
        {
            first = primos[tam];
            r.push_back(first);
            break;
        }
        tam--;
    }
    if(first == 0)
    {
        r.push_back(0);
    }else
    {
        second = n/first;
        r.push_back(second);
    }

    return r;
}

nInt aplicar_rc(nInt m, nInt d, nInt n, vecInt fact)
{
    if(n > 0)
    {
        nInt temp_1 = d % (fact[0]-1);
        nInt temp_2 = d % (fact[1]-1);
        vecInt t_1 = dec_to_binary(temp_1);
        vecInt t_2 = dec_to_binary(temp_2);
        nInt a_1 = exponenciacion_rap(m,t_1, n);
        nInt a_2 = exponenciacion_rap(m,t_2, n);

        matInt mat(2);
        mat[0].push_back(1);
        mat[0].push_back(a_1);
        mat[0].push_back(fact[0]);
        mat[1].push_back(1);
        mat[1].push_back(a_2);
        mat[1].push_back(fact[1]);

        nInt res = resto_chino(mat);
        return res;
    }
    else
        return 0;

}

void print_vector(vecInt v)
{
    for(nInt i=0; i < v.size(); i++)
        cout << v[i] << "\t";
    cout << endl;
}

bool save_msje(vecInt msj, string data)
{
    string file = data + "_msj.txt";
    ofstream myfile (file.c_str());
    stringstream s;
    for(nInt i=0; i < msj.size(); i++)
        s << msj[i];
    string mensaje = s.str();
    if (myfile.is_open())
    {
        myfile << mensaje << "#" << data;
        myfile.close();
        return true;
    }
    else cout << "No se puede abrir el archivo.";
    return false;
}

short long_dig(nInt n)
{
    stringstream t;
    t << n;
    string st = t.str();
    short tam = st.size();
    return tam;
}

string msj_to_dig(string m, string alf)
{
    nInt tam = m.size();
    string r;
    nInt tam_alf = alf.size();
    nInt lon_alf = long_dig(tam_alf);

    for(nInt i=0; i < tam; i++)
    {
        nInt t = alf.find(m[i]);
        r += rellena_ceros(t, lon_alf);
    }

    return r;
}

string completa(string m, nInt n, string alf)
{
    nInt tam = m.size();
    nInt modulo = tam % n;
    nInt t = alf.find('x');
    while(modulo > 0)
    {
        stringstream a;
        a << t;
        m += a.str();
        tam = m.size();
        modulo = tam % n;
    }

    return m;
}

string separa_grupos(string m, nInt n, string alf)
{
    m = completa(m, n, alf);
    nInt tam = m.size();

    stringstream a;

    nInt div = tam / n;
    nInt i=0;
    nInt t = n;
    while(i < div)
    {

        m.insert(t,1, ' ');
        t +=n+1;
        i++;
    }

    return m;

}

vecInt str_to_vect(string m, nInt t)
{
    vecInt r;
    stringstream a;
    a << m;
    nInt v;

    for(nInt i=0; i < t; i++)
    {
        a >> v;
        r.push_back(v);
    }
    return r;
}

vecInt to_block(string m, nInt n, string alf)
{

    vecInt r;
    nInt tam = m.size();
    nInt x = long_dig(n)-1;
    nInt mod = (tam*2) % x;
    nInt div = (tam*2) / x;
    nInt t = mod+div;
    string s = msj_to_dig(m, alf);
    s = separa_grupos(s, x, alf);
    r = str_to_vect(s, t);
    return r;
}

vecInt app_exp_rap(vecInt v, nInt p, nInt q, nInt d, nInt n)
{
    nInt tam = v.size();

    vecInt fac_primos;
    fac_primos.push_back(p);
    fac_primos.push_back(q);
    for(nInt i=0; i < tam; i++)
        v[i] = aplicar_rc(v[i], d, n, fac_primos);

    return v;
}

void save_keys(vecInt llaves)
{
    string file = "q_keys.txt";
    ofstream myfile (file.c_str());
    string keys;
    stringstream s;
    s << "p: " << llaves[0] << "\n";
    s << "q: " << llaves[1] << "\n";
    s << "e: " << llaves[2] << "\n";
    s << "n: " << llaves[3] << "\n";
    s << "phi: " << llaves[4] << "\n";
    s << "d: " << llaves[5] << "\n";
    keys = s.str();

    if (myfile.is_open())
    {
        myfile << keys;
        myfile.close();
    }
    else cout << "No se puede abrir el archivo.";
}

string rellena_ceros(nInt v, nInt t)
{
    nInt t_v = long_dig(v);
    stringstream s;
    string r;
    nInt y = t-t_v;
    string temp(y, '0');
    s << temp;
    s << v;
    r = s.str();
    return r;
}

string to_groups(string m, nInt n)
{
    nInt tam = m.size();
    stringstream a;
    nInt div = tam / n;
    nInt i=0;
    nInt t = n;
    while(i < div)
    {
        m.insert(t,1, ' ');
        t +=n+1;
        i++;
    }

    return m;

}

string complete(string m, nInt n, nInt val)
{

    nInt tam = m.size();
    nInt modulo = tam % n;
    while(modulo > 0)
    {
        stringstream a;
        a << val;
        m += a.str();
        tam = m.size();
        modulo = tam % n;
    }

    return m;
    /*
    stringstream s;
    s << val;
    m += s.str();
    return m;*/
}

nInt total_groups(nInt s_m, nInt s_n)
{
    nInt mod = (s_m) % s_n;
    nInt div = (s_m) / s_n;
    nInt t = mod+div;
    return t;
}

vecInt calc_exp_rap(vecInt vec, vecInt e_bi, nInt n)
{
    nInt tam = vec.size();
    vecInt res;
    for(nInt i=0; i < tam; i++)
    {
        nInt temp = exponenciacion_rap(vec[i], e_bi, n);
        res.push_back(temp);
    }
    return res;
}

vecInt msj_to_vec(string m, string alf)
{
    nInt tam = m.size();
    vecInt res;
    for(nInt i=0; i < tam; i++)
    {
        nInt temp = alf.find(m[i]);
        res.push_back(temp);
    }
    return res;
}

string complete_vec(vecInt vec, nInt n)
{
    nInt tam = vec.size();
    string res;
    for(nInt i=0; i < tam; i++)
    {
        res += rellena_ceros(vec[i], n);
    }
    return res;
}

void save_encript(string msj, string dest)
{
    string file = dest + "_msj.txt";
    ofstream myfile (file.c_str());
    if (myfile.is_open())
    {
        myfile << msj << "#" << dest;
        myfile.close();
        cout << "El mensaje se ha guardado en el archivo: " << file << endl;
    }
    else
        cout << "No se puede abrir el archivo." << endl;

}

vecInt calc_rc(vecInt vec, nInt d, nInt p, nInt q)
{
    nInt n = p*q;
    nInt tam = vec.size();
    vecInt fac_primos;
    fac_primos.push_back(p);
    fac_primos.push_back(q);
    vecInt res;
    for(nInt i=0; i < tam; i++)
    {
        nInt temp = aplicar_rc(vec[i], d, n, fac_primos);
        res.push_back(temp);
    }


    return res;
}

string vec_to_text(vecInt vec, string alf)
{
    nInt tam = vec.size();
    string res;
    for(nInt i=0; i < tam; i++)
    {
        res += alf[vec[i]];
    }
    return res;
}
