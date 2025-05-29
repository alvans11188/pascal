#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;
sem_t s,t;

void proceso1(){
	while(true){
		cout<<"A"<<endl;
		sem_post(&s);//signal
		cout<<"B"<<endl;
		
	}
}
void proceso2(){
	while(true){
		cout<<"C"<<endl;
		sem_wait(&s);
		sem_wait(&t);
		cout<<"D"<<endl;
	}
}
void proceso3(){
	while(true){
		cout<<"E"<<endl;
		sem_post(&t);
		cout<<"F"<<endl;
	}
}
int main(){
	sem_init(&s,0,0);
	sem_init(&t,0,0);
	
	thread P1(proceso1);
	thread P2(proceso2);
	thread P3(proceso3);
	 
	 P1.join();
	 P2.join();
	 P3.join();
	 return 0;
}