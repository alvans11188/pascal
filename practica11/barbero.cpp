#include <iostream>
#include <thread>
#include <semaphore.h>

using namespace std;

const int NUM_SILLAS = 5;

sem_t mutex,wrt;

sem_t sem_sillas;
sem_t sem_barbero;
sem_t sem_cliente;
sem_t sem_corteTerminado;
int n=5;
int enespera=0;
void barbero(){
	while(true){
		do{
			sem_wait(&sem_cliente);
			sem_wait(&mutex);
			enespera=enespera-1;
			sem_post(&sem_barbero);
			sem_post(&mutex);
			cout<<"Barbero cortando el cabello"<<endl;
		}while(enespera!=0);
	}
}
/*
void barbero(){
	while(true){
		while(enespera!=0){
			sem_wait(&sem_cliente);
			sem_wait(&mutex);
			enespera=enespera-1;
			sem_post(&sem_barbero);
			sem_post(&mutex);
			cout<<"Barbero cortando el cabello"<<endl;
		}
	}
}
*/
void clientela(){
	while(true){
		sem_wait(&mutex);
		if(enespera<n){
			enespera=enespera+1;
			cout<<"Esperando"<<endl;
			sem_post(&sem_cliente);
			sem_post(&mutex);
			sem_wait(&sem_barbero);
		}else{
			sem_post(&mutex);
		}
	}	
}
int main(){
	sem_init(&mutex,0,1);
	sem_init(&sem_cliente,0,0);
	sem_init(&sem_barbero,0,0);

	thread Cliente1(clientela);
	thread Cliente2(clientela);
	thread Cliente3(clientela);
	thread Cliente4(clientela);
	thread Barbero(barbero);
	Barbero.join();
	Cliente1.join();
	Cliente2.join();
	Cliente3.join();
	
	Cliente4.join();
	
	
	return 0;
}
