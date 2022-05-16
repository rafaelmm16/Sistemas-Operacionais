#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int primo(int value) {
	int i = 2;
	while (i < value && value%i != 0) i++;
	return i == value;
}

void* thread_a(void * arg){
    int res = 0;

	for(int i = 1; i<=250; i++)
	{
		res = primo(i);
		if(res) {
			printf("Thread 1: O número %d é primo.\n", i);
		} else {
			printf("Thread 1: O número %d não é primo.\n", i);
		}
	}
    return NULL;
}

void* thread_b(void * arg){
    int res = 0;

	for(int i = 251; i<=500; i++)
	{
		res = primo(i);
		if(res) {
			printf("Thread 2: O número %d é primo.\n", i);
		} else {
			printf("Thread 2: O número %d não é primo.\n", i);
		}
	}
}

void* thread_c(void * arg){
    int res = 0;

	for(int i = 501; i<=750; i++)
	{
		res = primo(i);
		if(res) {
			printf("Thread 3: O número %d é primo.\n", i);
		} else {
			printf("Thread 3: O número %d não é primo.\n", i);
		}
	}
}

void* thread_d(void * arg){
    int res = 0;

	for(int i = 751; i<=1000; i++)
	{
		res = primo(i);
		if(res) {
			printf("Thread 4: O número %d é primo.\n", i);
		} else {
			printf("Thread 4: O número %d não é primo.\n", i);
		}
	}
}

int main(){

	pthread_t newthread;

	pthread_create(&newthread, NULL, thread_a, NULL);
	pthread_create(&newthread, NULL, thread_b, NULL);
	pthread_create(&newthread, NULL, thread_c, NULL);
	pthread_create(&newthread, NULL, thread_d, NULL);

	pthread_join(newthread, NULL);
	//pthread_join(newthread, NULL);
	//pthread_join(newthread, NULL);
	//pthread_join(newthread, NULL);

}