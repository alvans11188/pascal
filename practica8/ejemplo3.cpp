#include <iostream>
#include <thread>
#include <semaphore.h>
using namespace std;
sem_t s;

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
		cout<<"D"<<endl;
	}
}
int main(){
	sem_init(&s,0,0);
	thread P1(proceso1);
	thread P2(proceso2);
	 
	 P1.join();
	 P2.join();
	 return 0;
}