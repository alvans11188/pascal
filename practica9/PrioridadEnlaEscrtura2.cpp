#include<iostream>
#include<thread>
#include <semaphore.h>
using namespace std;
sem_t mutex,wrt;
bool writing;
int lec=0,nee=0;
void lector(){
	while(true){
		sem_wait(&mutex);
		while(writing==true||nee>0){
			sem_wait(&mutex);
			sem_post(&mutex);	
		}
		lec=lec+1;
		sem_post(&mutex);
		cout<<"leer del reuso"<<endl;
		if(lec==1){
			sem_wait(&wrt);
		}
		sem_post(&mutex);
		cout<<"Leer del recurso"<<endl;
		sem_wait(&mutex);
		lec=lec-1;
		if(lec==0){
			sem_post(&wrt);
		}
		sem_post(&mutex);
	}		
}
void escritor(){
	while(true){
		sem_wait(&wrt);
		cout<<"Escribir recurso"<<endl;
		sem_post(&wrt);
	}
}

int main(){
	
	
	sem_init(&mutex,0,1);
	//sem_init(&wrt,0,0);
	thread le1(lector);
	thread le2(lector);
	thread le3(lector);
	
	thread es1(escritor);
	thread es2(escritor);
	thread es3(escritor);
	
	le1.join();
	le1.join();
	le1.join();
	es1.join();
	es2.join();
	es3.join();


	return 0;
}