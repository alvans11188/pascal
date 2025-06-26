#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

int i=0;
bool listo_para_imprimir = false;
int contador=0;
mutex mtx;
condition_variable cv;

void incrementar(){
	while(true&&contador<19){
		unique_lock<mutex> lock(mtx);
		i+=2;
		cout<<"Incrementado a: "<<i<<endl;
		
		listo_para_imprimir = true;
		cv.notify_one();
		lock.unlock();
		
		this_thread::sleep_for(chrono::milliseconds(500));
		contador++;
	}
}
void imprimir(){
	while(true&&contador<19){
		unique_lock<mutex> lock(mtx);
		
		cv.wait(lock, []{return listo_para_imprimir; });
		
		cout<<"Imprimiendo: "<<i<<endl;
		
		listo_para_imprimir = false;
		lock.unlock();
		
		this_thread::sleep_for(chrono::milliseconds(500));
		contador++;
	}
}
int main(){
	thread t1(incrementar);
	thread t2(imprimir);
	
	t1.join();
	t2.join();
	return 0;
}