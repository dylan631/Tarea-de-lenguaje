#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

using namespace std;

void S(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void T(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void A(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void B(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void C(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void D(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void E(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void F(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void G(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void H(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void I(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
// void J(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
// void K(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
// void L(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void M(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void N(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void mostrarTokens(char token[10], char tipo);

// FUNCIONES AGREGADAS : Operaci�n Binaria
// void AZ(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
// void BZ(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
// void NZ(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);

// FUNCIONES AGREGADAS : Lectura y Escritura
void lectura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int lect);
void opLectura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect);
void lectOper(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect);
void escritura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int escr);
void opEscritura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr);
void escrOper(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr);

// FUNCIONES AGREGADAS: COMENTARIOS
void ComentarioTipo1(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int &v);
void ComentarioTipo2(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int &v);
void ComentarioComplejo(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int &v);

char palabraReservada[4][15] = { // Palabra reservadas
	"entero", "real", "lee", "escribe"};

char operadorSimple[13][5] = { // Operadores simples
	"+", "-", "*", "/", ";", ",", "[", "]", "{", "}", "=", ">", "<"};

int esLetra(char ch) // Identifica si es una letra
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return 1;
	}
	return 0;
}

int esDigito(char ch) // Identifica si es un numero
{
	if ((ch >= '0' && ch <= '9'))
	{
		return 1;
	}
	return 0;
}

int esOperadorSimple(char ch) // Identifica si es un operador simple
{
	int i;
	for (i = 0; i < sizeof(operadorSimple) / 5; i++)
	{
		if (ch == operadorSimple[i][0])
		{
			return i;
		}
	}
	return -1; // caso contrario
}

int esPalabraReservada(char token[]) // Identifica si es una palabra reservada
{
	int i;
	for (i = 0; i < sizeof(palabraReservada) / 15; i++)
	{
		if (strcmp(token, palabraReservada[i]) == 0)
		{
			return i;
		}
	}
	return -1; // caso contrario
}

void limpiaChar(char token[]) // limpia token
{
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		token[i] = '\0'; // espacio
	}
}

// Scanner de tokens
void Scanner(int &syn, int &pos, char token[], char linFuente[], char &tipo)
{
	char ch;
	int ptoken = 0, i = 0;
	tipo = ' ';
	syn = 0;

	ch = linFuente[pos];
	while (ch == ' ')
	{
		ch = linFuente[++pos];
	}

	limpiaChar(token); // limpia el espacio en blanco

	if (esLetra(ch))
	{
		while (esLetra(ch) || esDigito(ch))
		{
			token[ptoken++] = ch;
			ch = linFuente[++pos]; //
		}
		syn = esPalabraReservada(token);
		if (syn < 0)
		{
			tipo = 'I'; // Identificador (I)
			return;
		}
		else if (syn == 0 || syn == 1)
		{
			tipo = 'N'; // Palabra Reservada Numeros (N)
			return;
		}
		else if (syn == 2)
		{
			tipo = 'L'; // Palabra Reservada Lectura (L)
			return;
		}
		else if (syn == 3)
		{
			tipo = 'S'; // Palabra Reservada Escritura (S)
			return;
		}
	}
	else if (esDigito(ch))
	{
		while (esDigito(ch))
		{
			token[ptoken++] = ch;
			ch = linFuente[++pos];
		}
		if (ch == '.') // si contiene .
		{
			token[ptoken++] = ch;
			ch = linFuente[++pos];

			while (esDigito(ch))
			{
				token[ptoken++] = ch;
				ch = linFuente[++pos];
			}
			tipo = 'D'; // Numero Real (D)
			return;
		}
		tipo = 'E'; // Numero Entero (E)
		return;
	}
	else if ((syn = esOperadorSimple(ch)) != -1)
	{
		token[ptoken++] = ch;
		tipo = 'O'; // Operadores (O)
		pos++;
		return;
	}
}

int main()
{
	int pos = 0; // Posicion inicial en la linea
	int syn = -1;
	char token[10];
	char linFuente[1100]; // Linea del archivo fuente
	FILE *fp;			  // Archivo
	int lin = 0;
	char tipo = ' ';
	int sec = 0;

	fp = fopen("./testParser.txt", "rb");
	cout << "\n\t************************************************************";
	cout << "\n\t*                RECONOCEDOR DE LENGUAJE                   *";
	cout << "\n\t************************************************************" << endl;
	cout << "\n\tCodigo del archivo de texto:\n";
	fgets(linFuente, sizeof(linFuente), fp); // Leer una linea del archivo

	while (!feof(fp))
	{
		lin++;
		cout << "\n\tLinea " << lin << ": " << linFuente << endl;
		pos = 0;
		int q = 0;
		int e = 0; // Error = 1 , Correcto = 0

		Scanner(syn, pos, token, linFuente, tipo);
		S(syn, pos, token, linFuente, tipo, e);

		if (e == 1)
		{
			cout << "\t - Error encontrado en la linea " << lin << " columna " << pos << " -\n";
		}
		else
		{
			cout << "\t - Linea correcta -\n";
		}
		fgets(linFuente, sizeof(linFuente), fp); // Vuelve a leer la linea del archivo texto
	}
	return 0;
}

void S(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "/") == 0) //
	{
		int v = 1;
		Scanner(syn, pos, token, lin, tipo);
		ComentarioTipo1(syn, pos, token, lin, tipo, e, v);
		if (v == 0)
		{
			S(syn, pos, token, lin, tipo, e);
		}
	}
	else
	{
		T(syn, pos, token, lin, tipo, e); // si empieza con palabra reservada: entero, real, lee o escribe
		if (e != 0)
			A(syn, pos, token, lin, tipo, e); // si empieza con un identificador
	}
}

void ComentarioTipo1(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int &v)
{
	if (strcmp(token, "/") == 0)
	{
		e = 0;
	}
	else if (strcmp(token, "*") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		ComentarioComplejo(syn, pos, token, lin, tipo, e, v);
	}
	else
	{
		e = 1;
	}
}

void ComentarioTipo2(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int &v)
{
	if (strcmp(token, "*") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		ComentarioComplejo(syn, pos, token, lin, tipo, e, v);
	}
	else
	{
		e = 1;
	}
}

void ComentarioComplejo(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int &v)
{
	if (strcmp(token, "*") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			v = 0;
			Scanner(syn, pos, token, lin, tipo);
		}
		else
		{
			ComentarioComplejo(syn, pos, token, lin, tipo, e, v);
		}
	}
	else if (tipo != ' ')
	{
		Scanner(syn, pos, token, lin, tipo);
		ComentarioComplejo(syn, pos, token, lin, tipo, e, v);
	}
	else
	{
		e = 1;
	}
}

void T(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'N')
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
	}
	else if (tipo == 'L')
	{
		int rep = 1, lect = 1, v = 1;
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				opLectura(syn, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			opLectura(syn, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (tipo == 'S')
	{
		int rep = 1, escr = 1, v = 1;
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				opEscritura(syn, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			opEscritura(syn, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else
	{
		e = 1;
	}
}
void A(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'I')
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			int v = 1;
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo1(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				B(syn, pos, token, lin, tipo, e);
			}
		}
		else
		{
			B(syn, pos, token, lin, tipo, e);
		}
	}
	else
	{
		e = 1;
	}
}
void B(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, ",") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "/") == 0) //
	{
		int v = 1;
		Scanner(syn, pos, token, lin, tipo);
		ComentarioTipo1(syn, pos, token, lin, tipo, e, v);
		if (v == 0)
		{
			B(syn, pos, token, lin, tipo, e);
		}
	}
	else if (strcmp(token, "[") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		C(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "=") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		M(syn, pos, token, lin, tipo, e);
		// aquiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
	}
	else if (strcmp(token, "") == 0)
	{
		e = 0;
	}
	else
	{
		e = 1;
	}
}
void C(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'D' || tipo == 'E')
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		D(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void D(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "]") == 0)
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		E(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void E(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "=") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		F(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "/") == 0) //
	{
		int v = 1;
		Scanner(syn, pos, token, lin, tipo);
		ComentarioTipo1(syn, pos, token, lin, tipo, e, v);
		if (v == 0)
		{
			E(syn, pos, token, lin, tipo, e);
		}
	}
	else if (strcmp(token, ",") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void F(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "{") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		G(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void G(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'D' || tipo == 'E')
	{
		Scanner(syn, pos, token, lin, tipo);
		H(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void H(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "}") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		I(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, ",") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		G(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void I(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "") == 0)
	{
		e = 0;
	}
	else if (strcmp(token, "/") == 0) //
	{
		int v = 1;
		Scanner(syn, pos, token, lin, tipo);
		ComentarioTipo1(syn, pos, token, lin, tipo, e, v);
		if (v == 0)
		{
			I(syn, pos, token, lin, tipo, e);
		}
	}
	else if (strcmp(token, ",") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
/*
void J(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "=") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		K(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}

void K(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'D' || tipo == 'E')
	{
		Scanner(syn, pos, token, lin, tipo);
		L(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}

void L(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "") == 0)
	{
		e = 0;
	}
	else
	{
		e = 1;
	}
}
*/

void M(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'D' || tipo == 'E' || tipo == 'I')
	{
		Scanner(syn, pos, token, lin, tipo);
		N(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void N(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "") == 0)
	{
		e = 0;
	}
	else if (strcmp(token, ",") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "+") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		M(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "-") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		M(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "*") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		M(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "/") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			e = 0;
		}
		else if (strcmp(token, "*") == 0)
		{
			int v = 1;
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				N(syn, pos, token, lin, tipo, e);
			}
		}
		else
		{
			M(syn, pos, token, lin, tipo, e);
		}
	}
	else
	{
		e = 1;
	}
}
/*
void AZ(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'I' || tipo == 'E' || tipo == 'D')
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		BZ(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}

void BZ(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, "+") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		AZ(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "-") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		AZ(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "*") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		AZ(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "/") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			e = 0;
		}
		else
		{
			AZ(syn, pos, token, lin, tipo, e);
		}
	}
	else if (strcmp(token, "") == 0)
	{
		e = 0;
	}
	else
	{
		e = 1;
	}
}
*/
void lectura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int lect)
{
	if (tipo == 'I')
	{
		int rep = 1;
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		opLectura(syn, pos, token, lin, tipo, e, rep, lect);
	}
	else
	{
		e = 1;
	}
}
void opLectura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect)
{
	if (strcmp(token, ">") == 0)
	{
		e = 0;
		rep++;
		Scanner(syn, pos, token, lin, tipo);
		if (rep <= 2)
		{
			opLectura(syn, pos, token, lin, tipo, e, rep, lect);
		}
		else
		{
			lect++;
			int v = 1;
			if (strcmp(token, "/") == 0)
			{
				Scanner(syn, pos, token, lin, tipo);
				ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
				if (v == 0)
				{
					lectura(syn, pos, token, lin, tipo, e, lect);
				}
			}
			else
			{
				lectura(syn, pos, token, lin, tipo, e, lect);
			}
		}
	}
	else if (strcmp(token, "+") == 0 && lect > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				lectOper(syn, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			lectOper(syn, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "-") == 0 && lect > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				lectOper(syn, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			lectOper(syn, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "*") == 0 && lect > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				lectOper(syn, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			lectOper(syn, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "/") == 0 && lect > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				lectOper(syn, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			lectOper(syn, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "") == 0 && lect > 1)
	{
		e = 0;
	}
	else
	{
		e = 1;
	}
}
void lectOper(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect)
{
	if (tipo == 'I' || tipo == 'E' || tipo == 'D')
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				opLectura(syn, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			opLectura(syn, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else
	{
		e = 1;
	}
}
void escritura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int escr)
{
	if (tipo == 'I')
	{
		int rep = 1;
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		opEscritura(syn, pos, token, lin, tipo, e, rep, escr);
	}
	else
	{
		e = 1;
	}
}
void opEscritura(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr)
{
	if (strcmp(token, "<") == 0)
	{
		e = 0;
		rep++;
		Scanner(syn, pos, token, lin, tipo);
		if (rep <= 2)
		{
			opEscritura(syn, pos, token, lin, tipo, e, rep, escr);
		}
		else
		{
			escr++;
			int v = 1;
			if (strcmp(token, "/") == 0)
			{
				Scanner(syn, pos, token, lin, tipo);
				ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
				if (v == 0)
				{
					escritura(syn, pos, token, lin, tipo, e, escr);
				}
			}
			else
			{
				escritura(syn, pos, token, lin, tipo, e, escr);
			}
		}
	}
	else if (strcmp(token, "+") == 0 && escr > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				escrOper(syn, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			escrOper(syn, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "-") == 0 && escr > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				escrOper(syn, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			escrOper(syn, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "*") == 0 && escr > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				escrOper(syn, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			escrOper(syn, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "/") == 0 && escr > 1)
	{
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				escrOper(syn, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			escrOper(syn, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "") == 0 && escr > 1)
	{
		e = 0;
	}
	else
	{
		e = 1;
	}
}
void escrOper(int &syn, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr)
{
	if (tipo == 'I' || tipo == 'E' || tipo == 'D')
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		int v = 1;
		if (strcmp(token, "/") == 0)
		{
			Scanner(syn, pos, token, lin, tipo);
			ComentarioTipo2(syn, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				opEscritura(syn, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			opEscritura(syn, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else
	{
		e = 1;
	}
}
