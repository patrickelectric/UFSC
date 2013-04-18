#include "../lib/lib.h"

int main ()
{
	unsigned int entrada=0xaf;											// adiciona os valores de interrupção

	Registrador8b.add8Bit(entrada);										// salva os valores da interrupção no registrador

	while(0!=CPU(Decodificador8x4(Registrador8b.memoria)));				// roda a cpu

	return 0;
}