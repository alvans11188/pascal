/*
Ejemplo 2:
Para el segundo caso, se creará una cola, el emisor irá emitiendo mensajes y el receptor
recibe y confirma recepción.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;
mutex mtx;
condition_variable cv;
queue<int>mensajes;
bool listo=false;
const int N=3;

void receptor(){
	for(int i=0;i<N;i++){
		unique_lock<mutex>lock(mtx);
		cout<<"-----No hay mensaje el receptor espera..."<<endl;
		cv.wait(lock,[]{return listo;	});
		int msg=mensajes.back();
		cout<<"Receptor recibio el mensaje: "<<msg<<endl;
		cout<<"-----El receptor proceso el mensaje..."<<endl;
		listo=false;
		lock.unlock();
		cv.notify_one();
	}
}
void emisor(){
	for(int i=0;i<N;i++){
		unique_lock<mutex>lock(mtx);
		mensajes.push(i);
		cout<<"Emisor envia mensaje: "<<i<<endl;
		listo=true;
		lock.unlock();
		cv.notify_one();
		
		unique_lock<mutex> wait_lock(mtx);
		cout<<"------El emisor espera a que el receptor procese el mensaje ..."<<endl;
		cv.wait(wait_lock,[]{return !listo;	});
		cout<<"Emisor puede continuar con el siguiente mensaje o finalizar. "<<endl;
		
	}
}

int main(){
	thread hilo1(receptor);
	thread hilo2(emisor);
	hilo1.join();
	hilo2.join();
	return 0;
}