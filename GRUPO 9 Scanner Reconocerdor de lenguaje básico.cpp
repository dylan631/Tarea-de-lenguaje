#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

void Scanner(int &verificador, int &pos, char token[], char linFuente[], char &tipo);
void mostrarTokens(char token[10], char tipo);
void AFA(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void AF(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void U(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void AE(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void Q(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void AD(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void T(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void R(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void ABA(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void AB(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void H(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void AC(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void K(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void I(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void G(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void F(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void N(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void J(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void L(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void M(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void V(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void D(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void B(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void W(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void Z(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void C(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void X(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void A(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void AH(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void P(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);
void S(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e);


char palabraReservada[4][15] = { 
	"entero", "real", "lee", "escribe"};

char operadorSimple[15][5] = { 
	"+", "-", "*", "/", ";", ",", "[", "]", "{", "}", "=", ">", "<", "(", ")"};

char operadorComplejo[5][5] = {">>", "<<", "/*","*/", "//"};

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
	
	char ch,mutil[1];
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
		token[ptoken++] = ch;//TOKEN[0] = '/' 0
		ch = linFuente[++pos]; 
		token[ptoken++] = ch;
		for (i = 0; i < sizeof(operadorComplejo) / 5; i++)
		{			
			if (strcmp(token,operadorComplejo[i])== 0)
			{				
				tipo = 'C'; // OPERADOR COMPLEJO =
				pos++;
				return;
			}
		}
		token[--ptoken] = '\0'; 
		--pos;
		tipo = 'O'; // Operadores
		pos++;
		return;
	}
}


void S(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token, "//") == 0){
		e=0;
	}
	else if(strcmp(token, "/*") == 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo,e);
		S(verificador, pos, token, lin, tipo,e);
	}
	else if(tipo=='N'||tipo=='L'||tipo=='S'){
		A(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'){
		B(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token, "") == 0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}

void P(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"*/")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else if (tipo != ' ')
	{
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void A(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='N'){
		Scanner(verificador, pos, token, lin, tipo);
		X(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo == 'L'){
		Scanner(verificador, pos, token, lin, tipo);
		Z(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo == 'S'){
		Scanner(verificador, pos, token, lin, tipo);
		W(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void X(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		B(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'){
		B(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void Z(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		G(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,">>")== 0){
		G(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void W(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		T(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"<<")== 0){
		T(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void B(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='I'){
		Scanner(verificador, pos, token, lin, tipo);
		D(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void D(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"//")== 0){
		e=0;
	}
	if(strcmp(token,"")== 0||strcmp(token,",")== 0||strcmp(token,"/*")== 0||strcmp(token,"//")== 0||strcmp(token,"=")== 0){
		C(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void C(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,",")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		B(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"/*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		C(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"//")== 0){
		e=0;
	}
	else if(strcmp(token,"=")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		V(verificador, pos, token, lin, tipo, e);
		AH(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")== 0){
		e=0;
	}
	else{
		e=1;
	}
}

void AH(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,",")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		B(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){
		e=0;
	}
	else{
		e=1;
	}
}

void V(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='D'){
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='E'){
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'){
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"(")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		L(verificador, pos, token, lin, tipo, e);
		Scanner(verificador, pos, token, lin, tipo);
		if(strcmp(token,")")== 0){
			Scanner(verificador, pos, token, lin, tipo);
			M(verificador, pos, token, lin, tipo, e);
		}else{
			e=1;
		}
	}
	else{
		e=1;
	}
}

void M(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,",")== 0){
		B(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")== 0){
		e=0;
	}
	else if(strcmp(token,"//")== 0){
		e=0;
	}
	else if(strcmp(token,"/*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		J(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void L(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='D'){
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='E'){
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'){
		Scanner(verificador, pos, token, lin, tipo);
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		L(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"(")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		L(verificador, pos, token, lin, tipo, e);
		Scanner(verificador, pos, token, lin, tipo);
		if(strcmp(token,")")== 0){
			Scanner(verificador, pos, token, lin, tipo);
			e=0;
		}else{
			e=1;
		}
	}
	else{
		e=1;
	}
}


void J(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"+")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		L(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"-")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		L(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		L(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"/")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		L(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"/*")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		N(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")== 0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}

void N(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")== 0||strcmp(token,"+")== 0||strcmp(token,"-")== 0||strcmp(token,"*")== 0||strcmp(token,"/")== 0||strcmp(token,"")==0){
		J(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}

void F(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='I'){
		Scanner(verificador, pos, token, lin, tipo);
		K(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void G(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,">>")==0){
		Scanner(verificador, pos, token, lin, tipo);
		I(verificador, pos, token, lin, tipo, e);
	}
}

void I(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		F(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'){
		F(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void K(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"+")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AC(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"-")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AC(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AC(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"/")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AC(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,">>")==0){
		G(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else {
		e=1;
	}
}

void AC(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		H(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo == 'I'||tipo=='E'||tipo=='D'){
		H(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void H(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo == 'I'||tipo=='E'||tipo=='D'){
		Scanner(verificador, pos, token, lin, tipo);
		AB(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void AB(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		ABA(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,">>")==0){
		ABA(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}

void ABA(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,">>")==0){
		G(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}

void R(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='I'){
		Scanner(verificador, pos, token, lin, tipo);
		Q(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void T(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"<<")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AD(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void AD(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		R(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'){
		R(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void Q(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"+")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AE(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"-")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AE(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AE(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"/")==0){
		Scanner(verificador, pos, token, lin, tipo);
		AE(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"<<")==0){
		T(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}

void AE(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		U(verificador, pos, token, lin, tipo, e);
	}
	else if(tipo=='I'||tipo=='E'||tipo=='D'){
		U(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void U(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(tipo=='I'||tipo=='E'||tipo=='D'){
		Scanner(verificador, pos, token, lin, tipo);
		AF(verificador, pos, token, lin, tipo, e);
	}
	else{
		e=1;
	}
}

void AF(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"/*")==0){
		Scanner(verificador, pos, token, lin, tipo);
		P(verificador, pos, token, lin, tipo, e);
		AFA(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"<<")==0){		
		AFA(verificador, pos, token, lin, tipo, e);
	}
	else if(strcmp(token,"")==0){	
		Scanner(verificador, pos, token, lin, tipo);	
		e=0;
	}
	else{
		e=1;
	}
}

void AFA(int &verificador, int &pos, char token[], char lin[], char &tipo, int &e){
	if(strcmp(token,"<<")==0){
		T(verificador, pos, token, lin, tipo, e);
	}
	if(strcmp(token,"")==0){
		Scanner(verificador, pos, token, lin, tipo);
		e=0;
	}
	else{
		e=1;
	}
}
