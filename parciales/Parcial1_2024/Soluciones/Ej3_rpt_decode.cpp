#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct MalformedPattern
{
    MalformedPattern(string s)
    {
        pat=s;
    }
    string what()
    {
        return pat;
    }
    string pat;
};

// retorna verdadero cuando el caracter c corresponed a un digito [0,9]
bool es_digito(char c)
{
    return (c>='0'&&c<='9');
}

bool es_minuscula(char c)
{
    return (c>='a'&&c<='z');
}

// encuentra el corchete que cierra ']' que se corresponde
// con el corchete que abre ubicado en la posición pos del string s.
// puede haber corchetes anidados.
// Argumentos:
//  s: string donde buscar
//  pos: posicion del corchete que abre donde comienza el patron.
// Retorno: un string con el patron contenido entre los corchetes
//   modifica el valor de next_pos para que apunte al siguiente caracter luego del ']'
// Hint: recuerde el ejercicio 6 de la práctica 4, filtro de comentarios...
// Hint2: string tiene un metodo llamado substr que retorna un substring (porción) de s.
string extrae_patron(string s, size_t pos, size_t &next_pos)
{
    //los patrones están contenidos entre [patron]
    if(s[pos]!='[')
        throw MalformedPattern{"Error en extrae_patron:" + s + " => deberia comenzar con ["};
    //contador de corchetes abiertos
    int count = 1;
    for(size_t i=pos+1; i<s.length(); ++i)
    {
        if(s[i]=='[')
        {
            count++;
        }
        else if(s[i]==']')
        {
            count--;
            if(count==0)
            {
                next_pos=i+1;
                return s.substr(pos+1,i-pos-1);
            }
        }else if(!es_digito(s[i]) && !es_minuscula(s[i]))        {
            throw MalformedPattern{"Error en extrae_patron:" + s + " => caracer invalido en la posicion: " + to_string(i) };
        }
    }
    //nunca deberia llegar aquí a menos que el string este mal formado.
    throw MalformedPattern{"Error en extrae_patron:" +s + " => corchetes desbalanceados"};
}

// existe la función stoi que convierte un string formado por digitos en un numero entero
int extrae_numero(string s, size_t pos, size_t &next_pos)
{

    if (!es_digito(s[pos]))
        throw MalformedPattern{"Error en extrae_numero:" +s + " => deberia comenzar con un numero"};

    //una posible solucion
    size_t count=0;
    while (es_digito(s[pos+count]))
        count ++;
    next_pos = pos+count;
    return stoi(s.substr(pos,count));

    //otra solucion
//    int num = stoi(s.substr(pos),&next_pos);
//    next_pos += pos;
//    return num;
}

string rpt_decode(string enc)
{
    string dec;

    size_t i=0;
    while (i<enc.length())
    {
        if (es_digito(enc[i]))
        {
            size_t newi;
            int rep = extrae_numero(enc,i,newi);
            i=newi;
            string pat = rpt_decode(extrae_patron(enc,i,newi));
            for(int j=0; j<rep; j++)
                dec += pat;
            i=newi;
        }
        else if(es_minuscula(enc[i]))
        {
            dec += enc[i++];
        }
        else
        {
            throw MalformedPattern{"Error en rpt_decode:" + enc + " => caracer invalido en la posicion: " + to_string(i)};
        }
    }

    return dec;
}

// para almacenar el string codificado (enc) y su decodificado (dec)
// que se usaran para testear la funcion rpt_decode en el main
struct Test {
    string enc;
    string dec;
};

// función que lee un conjunto de strings codificados y su correspondiente
// decodificación del archvio que recibe como argumento
// retorna un vector de estructuras Test con los datos leidos
// si falla en la lectura del file lanza una excepción de tipo string
vector<Test> lee_tests(string enc_file_name)
{
    vector<Test> tests;
    Test t;
    ifstream tf(enc_file_name);
    if(!tf.is_open())
        throw string("File not found");
    while(tf >> t.enc >> t.dec)
        tests.push_back(t);
    tf.close();
    return tests;
}


int main()
{
    try
    {
        size_t next_pos;
        string s;
        string res;
        int resi;
        int it=1;

        //Test 1
        cout << "Test "<< it++ <<": extrae_patron"<< endl;
        s = "[abc]";
        res=extrae_patron(s,0,next_pos);
        cout << "\tinput: "<< s <<endl;
        cout << "\toutput: " << res <<endl;
        cout << "\t\tnext_pos = "  << next_pos  << endl;
        if (next_pos==5 && res =="abc")
            cout << "PASSED" << endl;
        else
            cout << "FAILED" <<endl;

        //Test 2
        cout << "Test "<< it++ <<": extrae_numero"<< endl;
        s="924[asd]";
        resi=extrae_numero(s,0,next_pos);
        cout << "\tinput: "<< s <<endl;
        cout << "\toutput: " << resi <<endl;
        cout << "\t\tnext_pos = "  << next_pos  << endl;
        if (next_pos==3 && resi == 924)
            cout << "PASSED" << endl;
        else
            cout << "FAILED" <<endl;

        //Test 2
        cout << "Test "<< it++ <<": rpt_decode"<< endl;
        vector<Test> tests = lee_tests("rpt_tests.txt");
        for(auto t: tests)
        {
            res=rpt_decode(t.enc);
            cout << "\tinput: "<< t.enc <<endl;
            cout << "\toutput: " << res <<endl;
            if ( res == t.dec)
                cout << "PASSED" << endl;
            else
                cout << "FAILED. resultado esperado: " << t.dec << ". resultado obtenido: " << res <<endl;
        }

        //Test 4
        try {
            cout << "Test "<< it++ <<": rpt_decode malformed input"<< endl;
            s="ab3[[c4[z]d]fg";
//            s="ae3[sf#]zq";
            cout << "\tinput: "<< s <<endl;
            res = rpt_decode(s);
            cout << "\toutput: " << res <<endl;
            cout << "FAILED" <<endl;
        }
        catch(MalformedPattern &m)
        {
            cout << "\tMalformed Pattern " << m.what() << endl;
            cout << "PASSED" <<endl;
            return 0;
        }
    }
    catch(MalformedPattern &m)
    {
        cout << "Error inesperado. Malformed Pattern " << m.what() << endl;
        return -1;
    }
    catch (const string & e)
    {
        cout << "Otro error inesperado: " << e << endl;
        return -1;
    }
        return 0;
}
