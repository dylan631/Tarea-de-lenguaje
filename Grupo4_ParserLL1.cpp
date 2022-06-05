#include <stdio.h>
#include <string.h>
#include <fstream>
#include <iostream>
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
void J(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void K(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void L(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void M(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void N(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void O(int &syn, int &pos, char token[], char lin[], char &tipo, int &e);
void mostrarTokens(char token[10], char tipo);

char palabraReservada[4][15] = { // Palabra reservadas (tipo)
	"entero", "real","lee","escribe"};

char operadorSimple[13][5] = { // Operadores simples
	"+", "-", "*", "/", ",", "[", "]", "{", "}", "=",">","<"}; //TAREA TWO: Comentario (// /* */)

int esLetra(char ch) // Identifica si una letra
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
	for (i = 0; i < 10; i++) // I - In - Int  
	{
		token[i] = '\0'; // espacio
	}
}
// Scanner de tokens
void Scanner(int &syn, int &pos, char token[], char linFuente[], char &tipo)
{
	char ch;
	int ptoken = 0,i = 0;
	tipo = ' ';
	syn = 0;

	do{
		ch = linFuente[pos];
	}while (ch == ' ');

	limpiaChar(token); // limpia el espacio en blanco

	if (esLetra(ch))
	{
		while (esLetra(ch) || esDigito(ch))
		{
			token[ptoken++] = ch;
			ch = linFuente[++pos];
		}
		syn = esPalabraReservada(token);
		if (syn < 0)
		{
			tipo = 'I'; // identificador (I)
			return;
		}
		tipo = 'R'; // palabra reservada (R)
		return;
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
			tipo = 'D'; // Numero con Decimales (D)
			return;
		}
		tipo = 'E'; // Numro Entero (E)
		return;
	}
	else if ((syn = esOperadorSimple(ch)) != -1) // Reconoce si es un operador Simple
	{
		token[ptoken++] = ch;
		tipo = 'O'; // Operadores (O)
		pos++;
		return;
	}
	return;
}

int main()
{
	int pos = 0; // Posicion inicial en la linea
	int syn = -1;
	char token[10];
	char linFuente[1100]; // linea del archivo fuente
	FILE *fp;			  // archivo
	int lin = 0;
	char tipo = ' ';
	int sec = 0;

	fp = fopen("./testParser.txt", "rb");
	cout << "\n\t************************************************************";
	cout << "\n\t*                      PARSER LL1                          *";
	cout << "\n\t************************************************************" << endl;
	cout << "\tCodigo del archivo texto:\n";
	//fgets(linFuente, sizeof(linFuente), fp); // Leer una linea del archivo

	while (!feof(fp))
	{
		fgets(linFuente, sizeof(linFuente), fp);
		lin++;
		cout << "\tlinea " << lin << ": " << linFuente << endl;
		pos = 0;
		int q = 0;
		int e = 0; // error, 1=error, 0=ok

		/// Llama a la funcion S - Parser LL1
		Scanner(syn, pos, token, linFuente, tipo);
		S(syn, pos, token, linFuente, tipo, e);

		if (e == 1)
		{
			cout << "\n\tError encontrado en la linea " << lin << " columna " << pos << "\n"
				 << endl;
		}
		else
		{
			cout << "\n\tlinea correcta\n"
				 << endl;
		}
		//fgets(linFuente, sizeof(linFuente), fp); // Vuelve a leer la linea del archivo texto
	}
	return 0;
}

void S(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	T(syn, pos, token, lin, tipo, e); // si empieza con palabra reservada: entero, real, lee o escribe
	if (e != 0)
		A(syn, pos, token, lin, tipo, e); // si empieza con un identificador
}
void T(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'R') //TAREA ONE
	{
		e = 0;
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
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
		B(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void B(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token, ",") == 0) //
	{
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
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
	}
	else if (strcmp(token, "") == 0) //ENTERO Anadir  ,agarrar.    
	{
		e=0;
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
	if (strcmp(token, ";") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		O(syn, pos, token, lin, tipo, e);
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
	if (strcmp(token, ";") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		O(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void M(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (tipo == 'D' || tipo == 'E')
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
	if (strcmp(token, ";") == 0)
	{
		Scanner(syn, pos, token, lin, tipo);
		O(syn, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, ",") == 0) //OTRO OPERARDOR (FALTA AGREGAR)
	{
		Scanner(syn, pos, token, lin, tipo);
		A(syn, pos, token, lin, tipo, e);
	}
	else
	{
		e = 1;
	}
}
void O(int &syn, int &pos, char token[], char lin[], char &tipo, int &e)
{
	if (strcmp(token,"") == 0){
		e = 0;
	}
	else
	{
		e = 1;
	}
}
