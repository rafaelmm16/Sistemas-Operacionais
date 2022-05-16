#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM_THREADS 1
int cont;
struct thread_data{
   int  id;
   int  inicio;
   int  fim;
};
struct thread_data thread_data_array[NUM_THREADS];

void *primo(void *threadarg)
{
  int id, inicio,fim;
  struct thread_data *my_data;
  my_data = (struct thread_data *) threadarg;

  id     = my_data->id;
  inicio = my_data->inicio;
  fim    = my_data->fim;

  int i,j;
  int limite;
  int flag;
  int cont;

  cont =0;

  printf("Thread %d Numeros de primos %d -> %d\n",id, inicio, fim);

  for(j=my_data->inicio+1;j<my_data->fim;j=j+2){

    if(j==1) continue;
    limite = (int)sqrt(j);
    flag=1;
    for(int i=3;i<=limite;i=i+2){
      if(j%i==0){
        flag=0;
        break;
      }
    }
    if(flag) cont++;
  }

  pthread_exit((void*) cont);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS];
   pthread_attr_t attr;
   int rc;
   long t;
   int i;
   void* status;
   int cont;
   int tam;
   int st;

   cont=1;

   clock_t start, stop;
   double tm = 0.0;
   start = clock();

   /* Initialize and set thread detached attribute */
   pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


   tam = 1000/NUM_THREADS;
   st = 0;

   for(t=0; t<NUM_THREADS; t++){
      printf("Criando a Thread %ld\n",t);
      thread_data_array[t].id     = t;
      thread_data_array[t].inicio = st;
      thread_data_array[t].fim    = st+tam;
      st = st + tam;
      rc = pthread_create(&threads[t], &attr, primo, (void *)&thread_data_array[t]);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   for(t=0; t<NUM_THREADS; t++) {
    rc = pthread_join(threads[t], &status);
    if (rc) {
       printf("ERROR; return code from pthread_join() is %d\n", rc);
       exit(-1);
       }

       printf("Main: completed join with thread %ld having a status of %ld\n",t,(long)status);
       cont = cont + (long) status;
    }
   printf("cont: %d\n",cont);
   stop = clock();
   tm = (double) (stop-start)/CLOCKS_PER_SEC;
   printf("Tempo de Execucao: %lf s\n", tm);
}