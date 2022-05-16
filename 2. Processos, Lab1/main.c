#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//O programa apresenta um somatorio de um numero passado
//na hora da execução

int sum;

//função que raliza o somatorio
//sendo uma void *, passando um numero como parametro
void *runner (void *param)
{
	int i, upper = atoi (param);

	sum = 0;
	for (i = 1; i <= upper; i++)
		sum += i;

	//Essa função recebe como argumento um endereço que é
	// utilizado para armazenar o valor de retorno do thread
	pthread_exit (0);
}

//função principal
//
int main (int argc, char *argv [])
{
	//um valor que permite identificar o thread
	pthread_t tid;
	pthread_attr_t attr;

	if (argc != 2)
	{
		fprintf (stderr, "usage: ./main <integer value>\n");
		return -1;
	}

	if (atoi (argv [1]) < 0)
	{
		fprintf (stderr, "%d must be >= 0\n", atoi (argv [1]));
		return -1;
	}

	//Atributos para configuração de thread.
	pthread_attr_init (&attr);
	//inicializar um thread
	pthread_create (&tid, &attr, runner, argv[1]);
	//recebe como argumentos a estrutura de controle do thread,
	//do tipo pthread_t, que será finalizado e o endereço de um
	//ponteiro (void **) para o valor de retorno do thread
	pthread_join (tid, NULL);

	printf ("sum = %d\n", sum);
	return 0;
}

