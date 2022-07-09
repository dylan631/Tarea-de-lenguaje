#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void Scanner(int &verificador, int &pos, char token[], char linFuente[], char &tipo);
void S(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void A(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void B(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void C(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void V(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &cont);
void J(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &cont);
void D(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &cont);
void mostrarTokens(char token[10], char tipo);

// FUNCIONES AGREGADAS : Lectura y Escritura
void F(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int lect);
void G(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect);
void H(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect);
void R(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int escr);
void T(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr);
void U(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr);

// FUNCIONES AGREGADAS: COMENTARIOS
void M(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &v);
void N(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &v);
void P(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &v);

char palabraReservada[4][15] = { 
	"entero", "real", "lee", "escribe"};

char operadorSimple[15][5] = { 
	"+", "-", "*", "/", ";", ",", "[", "]", "{", "}", "=", ">", "<", "(", ")"};

//Verificar si es una letra
int esLetra(char ch){
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
	{
		return 1;
	}
	return 0;
}

//Verificar si es un n?mero
int esDigito(char ch){
	if ((ch >= '0' && ch <= '9'))
	{
		return 1;
	}
	return 0;
}

//Verificar si es un operador simple
int esOperadorSimple(char ch){
	int i;
	for (i = 0; i < sizeof(operadorSimple) / 5; i++)
	{
		if (ch == operadorSimple[i][0])
		{
			return i;
		}
	}
	return -1; 
}

//Verificar si la palabra es reservada
int esPalabraReservada(char token[]){
	int i;
	for (i = 0; i < sizeof(palabraReservada) / 15; i++)
	{
		if (strcmp(token, palabraReservada[i]) == 0)
		{
			return i;
		}
	}
	return -1; 
}

//Limpia el TOKEN
void limpiaChar(char token[]){
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		token[i] = '\0'; // Limpia los espacios
	}
}

int main(){
	int pos = 0; 
	int verificador = -1;
	char token[10];
	char linFuente[1000]; 
	FILE *fp;			  
	int lin = 0;
	char tipo = ' ';
	int sec = 0;
	
	fp = fopen("./TESTSCANNER.txt", "rb");
	cout << "\n\t ---------------------------------------------------------------";
	cout << "\n\t|               RECONOCEDOR DE LENGUAJE BASICO                  |";
	cout << "\n\t ---------------------------------------------------------------";
	cout << "\n"<< endl;
	fgets(linFuente, sizeof(linFuente), fp); 

	while (!feof(fp))
	{
		lin++;
		cout << "\n\tFila " << lin << ": " << linFuente << endl;
		pos = 0;
		int q = 0;
		int e = 0; // Si e=1 lanza ERROR, si e=0 es CORRECTO

		Scanner(verificador, pos, token, linFuente, tipo);
		S(verificador, pos, token, linFuente, tipo, e);

		if (e == 1)
		{
			cout << "\t -> !ERROR! en la fila " << lin << " en el caracter [" << pos << "]\n\n";
		}
		else
		{
			cout << "\t -> Fila correcta\n\n";
		}
		fgets(linFuente, sizeof(linFuente), fp); 
	}
	return 0;
}

//Scanner de tokens
void Scanner(int &verificador, int &pos, char token[], char linFuente[], char &tipo){
	
	char ch;
	int ptoken = 0, i = 0;
	tipo = ' ';
	verificador = 0;

	ch = linFuente[pos];
	while (ch == ' ')
	{
		ch = linFuente[++pos];
	}

	limpiaChar(token); 

	if (esLetra(ch))
	{
		while (esLetra(ch) || esDigito(ch))
		{
			token[ptoken++] = ch;
			ch = linFuente[++pos]; //
		}
		verificador = esPalabraReservada(token);
		if (verificador < 0)
		{
			tipo = 'I'; // Identificador 
			return;
		}
		else if (verificador == 0 || verificador == 1)
		{
			tipo = 'N'; // Palabra Reservada Numeros 
			return;
		}
		else if (verificador == 2)
		{
			tipo = 'L'; // Palabra Reservada Lectura 
			return;
		}
		else if (verificador == 3)
		{
			tipo = 'S'; // Palabra Reservada Escritura 
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
		if (ch == '.') 
		{
			token[ptoken++] = ch;
			ch = linFuente[++pos];

			while (esDigito(ch))
			{
				token[ptoken++] = ch;
				ch = linFuente[++pos];
			}
			tipo = 'D'; // Numero Real 
			return;
		}
		tipo = 'E'; // Numero Entero 
		return;
	}
	else if ((verificador = esOperadorSimple(ch)) != -1)
	{
		token[ptoken++] = ch;
		tipo = 'O'; // Operadores 
		pos++;
		return;
	}
}

void S(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if (strcmp(token, "/") == 0) 
	{
		int v = 1;
		Scanner(verificador, pos, token, lin, tipo);
		M(verificador, pos, token, lin, tipo, e, v);
		if (v == 0)
		{
			S(verificador, pos, token, lin, tipo, e);
		}
	}
	else if (strcmp(token, "") == 0)
	{
		e = 0;
	}
	else
	{
		A(verificador, pos, token, lin, tipo, e); // si empieza con palabra reservada: entero, real, lee o escribe
		if (e != 0)
			B(verificador, pos, token, lin, tipo, e); // si empieza con un identificador
	}
}

void M(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &v){
	if (strcmp(token, "/") == 0)
	{
		e = 0;
	}
	else if (strcmp(token, "*") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e, v);
	}
	else
	{
		e = 1;
	}
}

void N(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &v){
	if (strcmp(token, "*") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e, v);
	}
	else
	{
		e = 1;
	}
}

void P(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &v){
	if (strcmp(token, "*") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			v = 0;
			Scanner(verificador, pos, token, lin, tipo);
		}
		else
		{
			P(verificador, pos, token, lin, tipo, e, v);
		}
	}
	else if (tipo != ' ')
	{
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e, v);
	}
	else
	{
		e = 1;
	}
}

void A(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if (tipo == 'N')
	{
		int v = 1;
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				B(verificador, pos, token, lin, tipo, e);
			}
		}
		else
		{
			B(verificador, pos, token, lin, tipo, e);
		}
	}
	else if (tipo == 'L')
	{
		int rep = 1, lect = 1, v = 1;
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				G(verificador, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			G(verificador, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (tipo == 'S')
	{
		int rep = 1, escr = 1, v = 1;
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				T(verificador, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			T(verificador, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else
	{
		e = 1;
	}
}
void B(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if (tipo == 'I')
	{
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			int v = 1;
			Scanner(verificador, pos, token, lin, tipo);
			M(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				C(verificador, pos, token, lin, tipo, e);
			}
		}
		else
		{
			C(verificador, pos, token, lin, tipo, e);
		}
	}
	else
	{
		e = 1;
	}
}

void C(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if (strcmp(token, ",") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		B(verificador, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "/") == 0)
	{
		int v = 1;
		Scanner(verificador, pos, token, lin, tipo);
		M(verificador, pos, token, lin, tipo, e, v);
		if (v == 0)
		{
			C(verificador, pos, token, lin, tipo, e);
		}
	}
	else if (strcmp(token, "=") == 0)
	{
		int parentesis=0;
		Scanner(verificador, pos, token, lin, tipo);
		V(verificador, pos, token, lin, tipo, e, parentesis);
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

void V(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &cont){
	if ((tipo == 'D' || tipo == 'E' || tipo == 'I') )
	{
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "+") == 0 || strcmp(token, "-") == 0 || strcmp(token, "*") == 0 || strcmp(token, "/") == 0)
	{
		J(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "(") == 0)
	{
		cont++;
		Scanner(verificador, pos, token, lin, tipo);
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, ")") == 0)
	{
		cont--;
		if (cont > 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			J(verificador, pos, token, lin, tipo, e, cont);
		}
		else if (cont == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			if(strcmp(token, ",") == 0)
			{
				D(verificador, pos, token, lin, tipo, e, cont);
			}
			else
			{
				V(verificador, pos, token, lin, tipo, e, cont);
			}
		}
		else
		{
			e = 1;
		}
	}
	else if (strcmp(token, "") == 0)
	{
		if (cont == 0)
		{
			e = 0;
		}
		else
		{
			e = 1;
		}
	}
	else
	{
		e = 1;
	}
}

void J(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &cont){
	if (strcmp(token, "+") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "-") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "*") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "(") == 0)
	{
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, ")") == 0)
	{
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, ",") == 0)
	{
		D(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "") == 0)
	{
		V(verificador, pos, token, lin, tipo, e, cont);
	}
	else if (strcmp(token, "/") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			e = 0;
		}
		else if (strcmp(token, "*") == 0)
		{
			int v = 1;
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				J(verificador, pos, token, lin, tipo, e, cont);
			}
		}
		else
		{
			V(verificador, pos, token, lin, tipo, e, cont);
		}
	}
	else
	{
		e = 1;
	}
}

void D(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int &cont){
	if (strcmp(token, ",") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		B(verificador, pos, token, lin, tipo, e);
	}
	else if (strcmp(token, "/") == 0)
	{
		Scanner(verificador, pos, token, lin, tipo);
		if (strcmp(token, "/") == 0)
		{
			e = 0;
		}
		else if (strcmp(token, "*") == 0)
		{
			int v = 1;
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				D(verificador, pos, token, lin, tipo, e, cont);
			}
		}
		else
		{
			e = 1;
		}
	}
	else
	{
		e = 1;
	}
}

void F(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int lect){
	if (tipo == 'I')
	{
		int rep = 1;
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		G(verificador, pos, token, lin, tipo, e, rep, lect);
	}
	else
	{
		e = 1;
	}
}

void G(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect){
	if (strcmp(token, ">") == 0)
	{
		e = 0;
		rep++;
		Scanner(verificador, pos, token, lin, tipo);
		if (rep <= 2)
		{
			G(verificador, pos, token, lin, tipo, e, rep, lect);
		}
		else
		{
			lect++;
			int v = 1;
			if (strcmp(token, "/") == 0)
			{
				Scanner(verificador, pos, token, lin, tipo);
				N(verificador, pos, token, lin, tipo, e, v);
				if (v == 0)
				{
					F(verificador, pos, token, lin, tipo, e, lect);
				}
			}
			else
			{
				F(verificador, pos, token, lin, tipo, e, lect);
			}
		}
	}
	else if (strcmp(token, "+") == 0 && lect > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				H(verificador, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			H(verificador, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "-") == 0 && lect > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				H(verificador, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			H(verificador, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "*") == 0 && lect > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				H(verificador, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			H(verificador, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else if (strcmp(token, "/") == 0 && lect > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				H(verificador, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			H(verificador, pos, token, lin, tipo, e, rep, lect);
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

void H(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int lect){
	if (tipo == 'I' || tipo == 'E' || tipo == 'D')
	{
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				G(verificador, pos, token, lin, tipo, e, rep, lect);
			}
		}
		else
		{
			G(verificador, pos, token, lin, tipo, e, rep, lect);
		}
	}
	else
	{
		e = 1;
	}
}

void R(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int escr){
	if (tipo == 'I')
	{
		int rep = 1;
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		T(verificador, pos, token, lin, tipo, e, rep, escr);
	}
	else
	{
		e = 1;
	}
}

void T(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr){
	if (strcmp(token, "<") == 0)
	{
		e = 0;
		rep++;
		Scanner(verificador, pos, token, lin, tipo);
		if (rep <= 2)
		{
			T(verificador, pos, token, lin, tipo, e, rep, escr);
		}
		else
		{
			escr++;
			int v = 1;
			if (strcmp(token, "/") == 0)
			{
				Scanner(verificador, pos, token, lin, tipo);
				N(verificador, pos, token, lin, tipo, e, v);
				if (v == 0)
				{
					R(verificador, pos, token, lin, tipo, e, escr);
				}
			}
			else
			{
				R(verificador, pos, token, lin, tipo, e, escr);
			}
		}
	}
	else if (strcmp(token, "+") == 0 && escr > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				U(verificador, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			U(verificador, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "-") == 0 && escr > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				U(verificador, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			U(verificador, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "*") == 0 && escr > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				U(verificador, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			U(verificador, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else if (strcmp(token, "/") == 0 && escr > 1)
	{
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		e = 0;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				U(verificador, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			U(verificador, pos, token, lin, tipo, e, rep, escr);
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

void U(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e, int rep, int escr){
	if (tipo == 'I' || tipo == 'E' || tipo == 'D')
	{
		e = 0;
		Scanner(verificador, pos, token, lin, tipo);
		int v = 1;
		if (strcmp(token, "/") == 0)
		{
			Scanner(verificador, pos, token, lin, tipo);
			N(verificador, pos, token, lin, tipo, e, v);
			if (v == 0)
			{
				T(verificador, pos, token, lin, tipo, e, rep, escr);
			}
		}
		else
		{
			T(verificador, pos, token, lin, tipo, e, rep, escr);
		}
	}
	else
	{
		e = 1;
	}
}

