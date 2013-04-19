#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

/*+---------------------------------------------------------------+*/
int Decodificador8x4(unsigned int entrada);				// declaro o decodificador8x4

class Registrador8b										// declaro o registrador de 8 bits
{
	public:
	unsigned int memoria;
	void reset(unsigned int ireset);
	unsigned int add8Bit(unsigned int ibit);
};

Registrador8b Registrador8b;							// crio registrador

int CPU(unsigned int i4bits);							// declaro a CPU
/*+---------------------------------------------------------------+*/


/*+---------------------------------------------------------------+*/
int Decodificador8x4(unsigned int entrada) 				// entrada pode ter o valor de 0 a 255, 0b00000000 a 0b11111111
{
	unsigned int i=0;  									// inicia a variavel para guardar os valores da divisão
	if(entrada!=0)
		for(i ; 1 != entrada >> i; i++);				// divide o valor da entrada ate descobrir o BMS(Bit Mais Significativo)
			//printf("%x,%x\n",i+1,entrada >> i );			
	else
		return 0;										// caso não tenha nada na entrada não fazer nada
	unsigned int valor=i+1;								// para não retornar a interrupção como zero e maxima como 7 add 1
	return valor;										// retorna o valor da prioridade
}
/*+---------------------------------------------------------------+*/


/*+---------------------------------------------------------------+*/
void Registrador8b::reset(unsigned int ireset)			
{
	printf("memoria= %d\n",memoria);					// mostra a memoria atual
	printf("deleta memoria : %d - %.0f\n",memoria,pow(2,ireset-1) );					// reseta a variavel do registrador 8º interrup = 2^7, assim por diante	
	memoria=memoria-pow(2,ireset-1);
	printf("memoria = %d\n", memoria);					// mostra nova memoria do registrador
}

unsigned int Registrador8b::add8Bit(unsigned int ibit)	
{
	memoria=ibit;										// salva os valores no registrador
	return memoria;										// retorna valor da memoria caso precise 
}
/*+---------------------------------------------------------------+*/


/*+---------------------------------------------------------------+*/
int CPU(unsigned int i4bits)
{
	printf("+---------------------------------------------------------------+\n");
	printf("i4bits = %d\n", i4bits);					// mostra o valor da interrupcao
	if(i4bits <= 0)										// caso receber nada, esperar o proximo
	{
		printf("sem interacao !!!\n\n");
		return 0;										// retorna que não tem nada para fazer
	}
	else
	{
		Registrador8b.reset(i4bits);					// limpa o registrador da interrupcao
		usleep(200000);									// faz alguma coisa
		printf("faz interrupcao numero %d !!!\n",i4bits);				
		printf("pronto para proxima interacao\n\n");
		return 1;										// retorna que a operacao foi realizada e esta pronto para a proxima
	}
	printf("+---------------------------------------------------------------+\n");
}
/*+---------------------------------------------------------------+*/

