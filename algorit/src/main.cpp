#include "../lib/lib.h"

int main ()
{
	unsigned int entrada=0x00;											// adiciona os valores de interrupção

	Registrador8b.add8Bit(entrada);
	while(1)															// salva os valores da interrupção no registrador
	{										
		NewInterrupt();
		sleep(1);
		controlador(Decodificador8x4(Registrador8b.memoria));         	// roda a controlador
	}

	return 0;
}