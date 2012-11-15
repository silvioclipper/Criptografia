#include "funciones.h"

Funciones::Funciones()
{
    //ctor
}

Funciones::~Funciones()
{

}

kobra Funciones::euclides(kobra a, kobra b)
{
    kobra r = a % b ;
    while ( r ) {
        a = b ;
        b = r ;
        r = a % b ;
    }
    return  b ;
}

vkobra Funciones::euclides_ext(kobra a, kobra b)
{
    kobra q, r1, r2, r, s1, s2, s, t1, t2, t;
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

    vkobra respuesta;
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

vkobra Funciones::divi(kobra dv, kobra ds)
{
    vkobra res(2);
    res[0] = dv;
    res[1] = ds;

    for(int i=0; res[0] > res[1]; i++)
        res[0] = dv - ds;

    return res;
}

vkobra Funciones::criba(kobra n)
{

	vector<kobra> primos;
    for(kobra i=2; i < n; i++)
        primos.push_back(i);

	vector<kobra>::iterator it;

    for(it = primos.begin(); it < primos.end(); it++)
    {
        vector<kobra>::iterator k;
        for(k=it+1; k < primos.end(); k++)
        {
            if(*k % *it == 0)
                primos.erase(k);
        }
    }

    return primos;

/*
	vkobra primos;
	for(kobra i=2; i <= n; i++)
		primos.push_back(i);

	for(kobra j=0; j < primos.size(); j++)
	{
		for(kobra k=j+1; k < primos.size(); k++)
		{
			if(primos[j] != 0)
				if(primos[k] % primos[j] == 0)
					primos[k] = 0;
		}
	}

	vkobra res;
	for(kobra r=0; r < primos.size(); r++)
	{
		if(primos[r] != 0)
			res.push_back(primos[r]);
	}
	return res;
*/
}

vkobra Funciones::cribi(kobra n)
{
    kobra max = (n - 3) / 2;
    vector<bool> esPrimo(max, true);
    vkobra resl;

    kobra i,k;
    i = 0;
	resl.push_back(2);
	kobra ist = (2*i+3)*(2*i+3);
    while( ist <= n )
    {
        k = i + 1 ;
        if(esPrimo[i])
        {
			kobra kst = (2*k+1)*(2*i+3);
            while( kst <= n)
            {
                kobra v = ((2*k + 1) * (2*i + 3) - 3) / 2;
				if(v < esPrimo.size())
					//esPrimo[v] = false;
                k++;
				kst = (2*k+1)*(2*i+3);
            }
        }
        i++;
		ist = (2*i+3)*(2*i+3);
    }

    for(kobra j = 0; j < max; j++)
    {
        if(esPrimo[j])
        {
            resl.push_back(2*j+3);
        }
    }


    return resl;

}

vkobra Funciones::criba_dos(kobra m, kobra n)
{
	vkobra primos;
    kobra pot = sqrt(n);
    vkobra min_pr = criba(pot);
	vkobra::iterator iter;

    for(kobra i=m; i < n; i++)
        primos.push_back(i);


    for(kobra j=0; j< min_pr.size();j++)
    {
		for(kobra k=0 ; k < primos.size(); k++)
        {
			if(primos[k] % min_pr[j] == 0)
                primos[k] = 0;
        }
    }
	vkobra res;
	for(int r=0; r < primos.size(); r++)
	{
		if(primos[r] != 0)
			res.push_back(primos[r]);
	}

    return res;
}

vkobra Funciones::criba_mn(kobra m, kobra n)
{
	vkobra salida;
    kobra k,mip,p,q,q2;

    kobra min = (m+1-3)/2;
    kobra max = (n-3)/2;
    kobra total = max-min+1;
    kobra qrt = sqrt(n);

    vector<bool> esPrimo(max+1);
    vkobra primos;
    primos = cribi(qrt);

    if(0<= m && m < 3)
        return cribi(n);

    for(kobra i = 0; i < total; i++)
        esPrimo[i]=true;

    for(kobra i = 1; i< primos.size() ; i++)
    {
        p = primos[i];

        if(p*p<m)
        {
            q = (m - 1) / p;
            q2 = q%2;
            k = q2;
            mip = (2*k+1-q2+q)*p;
            while(mip <= n)
            {
                esPrimo[(mip-3)/2-min] = false;
                k= k+1;
                mip=(2*k+1-q2+q) * p;
            }
        }
        if(m <= p*p)
        {
            k = (p -1) / 2;
            while((2*k+1)*p <= n)
            {
                esPrimo[((2*k+1)*p - 3)/2] = false;
                k++;
            }
        }
    }

    for(int i = 0; i < total; i++)
    {
        if(esPrimo[i])
            salida.push_back(2*(i+min)+3);
    }

    return salida;
}

kobra Funciones::inversa(kobra a, kobra n)
{
	kobra x = a;
	if(a < 0)
		x += n;
	else
	{
		vkobra e = euclides_ext(a, n);
		//cout << "mcd: " << e[0] << "\t = " << a << "*" << e[1] << " + " << n << "*" << e[2] << endl;

		if(e[0] == 1)
		{
			x = e[1];
			if(x < 0)
				x += n;
            //cout << "inversa de " << a << " es: " << x << endl;
		}else{
			x = -1;
		}
		x = kobra(x);
	}

	return x;
}

vkobra Funciones::borrado(vkobra vec, kobra val)
{
	kobra tam = vec.size();

	vkobra temp;

	for(kobra i = 0; i < tam; i++)
	{
		if(vec[i] != val)
			temp.push_back(vec[i]);
	}

	return temp;
}

vkobra Funciones::numeros_long_bits(short t)
{
	vkobra res;
	kobra min = pow(2,t-1);
	kobra max = 0;
	for(short i = 0; i <= t-1; i++)
		max += pow(2,i);

	res = criba_dos(min,max);
	return res;
}

vkobra Funciones::random_keys(short t)
{
	vkobra primos = numeros_long_bits(t);
	kobra tam = primos.size();
	srand(time(NULL));

    kobra a = rand() % tam;
    kobra b = rand() % tam;

	while(a == b)
	{
		a = rand() % tam;
		b = rand() % tam;
	}

	kobra n = primos[a]*primos[b];
	kobra c = rand() % tam;
	kobra e = euclides(primos[c], n);
	kobra phi = (primos[a]-1)*(primos[b]-1);

	while(e != 1 || c == a || c == b)
	{
		c = rand() % tam;
		e = euclides(primos[c], n);
	}

	kobra inv = inversa(primos[c], phi);


	vkobra result;
	result.push_back(primos[a]);
	result.push_back(primos[b]);
	result.push_back(primos[c]);
	result.push_back(n);
	result.push_back(phi);
	result.push_back(inv);

	return result;
}

kobra Funciones::exponenciacion(kobra m, kobra e, kobra n)
{
	kobra r = 1;
	for(kobra i = 1; i <= e; i++)
	{
		r = (r*m)%n;
	}
	return r;
}

kobra Funciones::resto_chino(mkobra m)
{
    kobra tam = m.size();
    kobra _p = 1;
    kobra ext = 0;

    kobra mcd;
    bool c_pr = true;

    for(kobra i=0; i < tam-1; i++)
    {
        mcd = euclides(m[i][2],m[i+1][2]);
        if(mcd!=1)
            c_pr = false;
    }

    if(c_pr)
    {

        for(kobra j=0; j < tam; j++)
        {
            _p *= m[j][2];
            //cout <<"a " << m[j][1] << endl;
        }


        for(kobra i=0; i < tam; i++)
        {
            if(m[i][0] > 1)
            {
                m[i][1] =  (m[i][1] * inversa(m[i][0],m[i][2])) % m[i][2];
                m[i][0] = 1;
            }

            kobra _pi = _p/m[i][2];
            //cout << "p[" << i << "]" << _pi << endl;
            kobra _qi = inversa(_pi,m[i][2]);//_pi%m[i][2];
            //cout << "q[" << i << "]" << _qi << endl;
            ext += ((m[i][1]%_p)* (_pi%_p) * (_qi%_p)) % _p;
           // cout << m[i][1] << " x " << _pi << " x " << _qi << " = " << (m[i][1]* _pi * _qi) << " mod " << _p << " = " << (m[i][1]* _pi * _qi)%_p << endl;
        }

        kobra resul = ext % _p;
        //cout << "Resto: " << ext << " mod " << _p << endl;

        return resul;
    }

    return -1;

}

short Funciones::get_long_bits(kobra ne)
{
    int i=0;
    while(true)
    {
        kobra var = pow(2,i);
        //cout << var << endl;
        if( ne < var)
            break;
        i++;
    }
    //cout << "Long b(" << ne << "): " << i-1 << endl;
    return i-1;
}

vkobra Funciones::dec_to_binary(kobra n)
{
    int t;
    vkobra r;
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

    kobra x = r.size();
    vkobra rs;
    int ii = 1;
    for(int i=x; i > 0; i--,ii++)
        rs.push_back(r[x-ii]);

    return rs;
}

kobra Funciones::exponenciacion_rap(kobra a, kobra k, kobra n)
{
    vkobra kb = dec_to_binary(k);
    kobra t = kb.size();
    kobra b = 1;
    kobra aa;
    if(k==0)
        return b;
    aa = a;
    if(kb[0] == 1)
        b = a;

    for(kobra i=1; i < t; i++)
    {
        aa = (aa*aa) % n;
        if(kb[i] == 1)
            b = (aa*b) % n;
    }

    return b;
}

kobra Funciones::mcdMenorResto(kobra a, kobra b)
{
    //cout << a << " ... " << b << endl;
    if(a < b)
    {
        kobra t = a;
        a = b;
        b = t;
    }
    kobra r;
    r = a - (b * (a/b * 1/2));
    //cout << r << endl;
    while(r != 0)
    {
        a = b;
        b = r;
        //cout << a << " . " << b << endl;
        r = a - (b * (a/b * 1/2));
        //cout << r << endl;
    }
    return b;
}

vkobra Funciones::factores_primos(kobra n)
{
    vkobra r;
    vkobra primos = criba(sqrt(n));
    //cout << "menores a: " << sqrt(n) << endl;
    kobra tam = primos.size()-1;
    //cout << "cantidad de primos: " << tam << endl;
    kobra first = 0, second = 0;
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
        //cout << "Factores primos" << first << endl;
        //cout << "Factores primos" << second << endl;
        r.push_back(second);
    }

    return r;
}

kobra Funciones::aplicar_rc(kobra m, kobra d, kobra n, vkobra fact)
{
    if(n > 0)
    {
        kobra temp_1 = d % (fact[0]-1);
        kobra temp_2 = d % (fact[1]-1);
        kobra a_1 = exponenciacion_rap(m,temp_1, n);
        kobra a_2 = exponenciacion_rap(m,temp_2, n);

        mkobra mat(2);
        mat[0].push_back(1);
        mat[0].push_back(a_1);
        mat[0].push_back(fact[0]);
        mat[1].push_back(1);
        mat[1].push_back(a_2);
        mat[1].push_back(fact[1]);

        //cout << mat[0][0] << "\t = \t" << mat[0][1] << " \t mod \t " << mat[0][2] << endl;
        //cout << mat[1][0] << "\t = \t" << mat[1][1] << " \t mod \t " << mat[1][2] << endl;

        kobra res = resto_chino(mat);
        return res;
    }
    else
        return 0;

}

void Funciones::print_vector(vkobra v)
{
    for(kobra i=0; i < v.size(); i++)
        cout << v[i] << "\t";
    cout << endl;
}

vkobra Funciones::strick_keys(kobra ne, kobra ex)
{
    vkobra fact = factores_primos(ne);
    for(kobra i=0; i < fact.size(); i++)
        cout << fact[i] << endl;

    kobra p = fact[0];
    kobra q = fact[1];
    //cout << ".... a" << a << endl << ".....b " << b << endl;

	kobra n = ne;
	kobra e = ex;
	kobra phi = (p-1)*(q-1);

	kobra d = inversa(e, phi);


	vkobra result;
	result.push_back(p);
	result.push_back(q);
	result.push_back(e);
	result.push_back(n);
	result.push_back(phi);
	result.push_back(d);

	return result;
}

bool Funciones::save_keys(vkobra llaves)
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
        return true;
    }
    else cout << "No se puede abrir el archivo.";
    return false;
}

bool Funciones::save_msje(vkobra msj, string data)
{
    string file = data + "_msj.txt";
    ofstream myfile (file.c_str());
    stringstream s;
    for(kobra i=0; i < msj.size(); i++)
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

short Funciones::long_dig(kobra n)
{
    short i;
    for(i=1; n >=10; i++)
        n /= 10;
    return i;
}
