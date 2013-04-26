#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

unsigned int entrada=0x00;											// adiciona os valores de interrupção
unsigned int mascara=0x00;											// adiciona valores de mascara

/*+---------------------------------------------------------------+*/

int Decodificador8x4(unsigned int);						// declaro o decodificador8x4

class Registrador8b										// declaro o registrador de 8 bits
{
	public:
	unsigned int memoria;
	void reset(unsigned int);
	unsigned int add8Bit(unsigned int);
};

Registrador8b Registrador8b;							// crio registrador

bool Mascara(unsigned int, unsigned int);
void addInterrupt(int, unsigned int );					// declaro a funcao que adiciona uma nova interrupcao 
void NewInterrupt();									// ajuda o addInterrupt a adicionar uma interrupcao
void NewMascara();										// ajuda a adicionar um novo valor na mascara pelo usuario
int controlador(unsigned int);							// declaro a controlador
void printMemoria();									// funcao de debug que mostra o valor em binario

/*+---------------------------------------------------------------+*/

void printMemoria(unsigned int mem)										
{
	printf("0b");
	for(int i=8;i>0;i--)
	{
		if((mem & (unsigned int)pow(2,i-1))!=0) printf("1");
		else
			printf("0");
	}
	printf("\n");
}

/*+---------------------------------------------------------------+*/

bool Mascara(unsigned int i, unsigned int mascara)
{
	if((unsigned int)pow(2,i-1) & mascara)
		return false;
	else
		return true;
}

/*+---------------------------------------------------------------+*/

int Decodificador8x4(unsigned int entrada) 				// entrada pode ter o valor de 0 a 255, 0b00000000 a 0b11111111
{
	unsigned int i=0;  									// inicia a variavel para guardar os valores da divisão
	if(entrada!=0)
		for(i ; 1 != entrada >> i; i++);				// divide o valor da entrada ate descobrir o BMS(Bit Mais Significativo)
			//printf("%x,%x\n",i+1,entrada >> i );			
	else
		return 0;										// caso não tenha nada na entrada não fazer nad)
	unsigned int valor=i+1;								// para não retornar a interrupção como zero e maxima como 7 add 1
	return valor;										// retorna o valor da prioridade
}

/*+---------------------------------------------------------------+*/

void Registrador8b::reset(unsigned int ireset)			
{
	printf("memoria= "); printMemoria(memoria );							// mostra a memoria atual
	printf("deleta memoria : %d - %.0f\n",memoria,pow(2,ireset-1) );		// reseta a variavel do registrador 8º interrup = 2^7, assim por diante	
	memoria=memoria-pow(2,ireset-1);
	printf("memoria = "); printMemoria( memoria );							// mostra nova memoria do registrador
}

/*+---------------------------------------------------------------+*/

unsigned int Registrador8b::add8Bit(unsigned int ibit)	
{
	memoria=ibit;										// salva os valores no registrador
	return memoria;										// retorna valor da memoria caso precise 
}


/*+---------------------------------------------------------------+*/

void addInterrupt(int op,unsigned int mascara)
{
	int memoriaTemp;
	if((op)>= 9 || (op)<= 0)
		printf("fora do valor !!\n");
	else
	{
		if (Mascara(op,mascara))
		{
			printf("valor não ativado pela mascara!\n");
			return;
		}
		if ((Registrador8b.memoria & (unsigned int)pow(2,op-1))==0) 				// se o bit estiver livre add interrupcao
		{
			Registrador8b.memoria=Registrador8b.memoria+pow(2,op-1);				// salva o valor na memoria
			printf("memoria : "); printMemoria(Registrador8b.memoria );									// mostra memoria
			/*
			printf("start\n");
			for(int i=0;i<=8;i++)
				printf("%d\n",Registrador8b.memoria >> i );
			*/
		}
	}
}

/*+---------------------------------------------------------------+*/

void NewMascara()
{
	char op[2];
	RETORNO:
	printf("mascara = "); printMemoria(mascara);
	memset (&op, 0, sizeof (op) );												// simula a acionamento de um bit na mascara
	printf("voce gostaria de modificar um bit na mascara ?\n");
	printf("(8,7,6,5,4,3,2,1) ADD / (N) NAO / (-8,-7,-6,-5,-4,-3,-2,-1) REM\n");
	scanf ("%s",op);
	sleep(1);
	if(op[0] == 'n' || op[0] == 'N')
		printf("ok !\n");
	else
		{
			if(op[0]!='-')
				mascara=mascara+(unsigned int)pow(2,(int)atoi(&op[0])-1);
			else
				mascara=mascara-(unsigned int)pow(2,(int)atoi(&op[1])-1);
			goto RETORNO;
		}
}

/*+---------------------------------------------------------------+*/

void NewInterrupt()
{
	char op;
	RETORNO:
	memset (&op, 0, sizeof (op) );												// simula a acionamento de uma interrupcao
	printf("voce gostaria de adicionar uma nova interrupcao ?\n");
	printf("(8,7,6,5,4,3,2,1) SIM / (N) NAO\n");
	scanf ("%s",&op);
	sleep(1);
	if(op == 'n' || op == 'N')
		printf("ok !\n");
	else
		{
			addInterrupt(atoi(&op),mascara);
			goto RETORNO;
		}
}

/*+---------------------------------------------------------------+*/

int controlador(unsigned int i4bits)
{
	printf("+---------------------------------------------------------------+\n");
	printf("i4bits = %d\n", i4bits);					// mostra o valor da interrupcao
	if(i4bits <= 0)										// caso receber nada, esperar o proximo
	{
		printf("sem interacao !!!\n\n");
		printf("+---------------------------------------------------------------+\n");
		return 0;										// retorna que não tem nada para fazer
	}
	else
	{
		Registrador8b.reset(i4bits);					// limpa o registrador da interrupcao
		usleep(200000);									// faz alguma coisa
		printf("faz interrupcao numero %d !!!\n",i4bits);				
		printf("pronto para proxima interacao\n\n");
		printf("+---------------------------------------------------------------+\n");
		return 1;										// retorna que a operacao foi realizada e esta pronto para a proxima
	}
}

/*+---------------------------------------------------------------+*/




