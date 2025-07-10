/*
Ejemplo 1:
Si tenemos una variable compartida “mensaje”, diseñe un programa que gestione el paso de
dicha variable de forma síncrona entre un proceso emisor y receptor, asegure una correcta
comunicación (debe existir un mensaje para que el receptor confirme recepción).
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

mutex mtx;
condition_variable cv;
string mensaje;
bool listo=false;
void receptor() {
	unique_lock<mutex> lock (mtx);
	cout<<"------No hay mensaje, el receptor-----"<<endl;
	cv.wait(lock, []{return listo; });
	cout<<"Receptor recibio el mensaje: "<<mensaje<<endl;
	cout<<"-----El receptor proceso el mensaje..."<<endl;
	listo=false;
	lock.unlock();
	cv.notify_one();
}

void emisor(){
	unique_lock<mutex> lock(mtx);
	mensaje="Hola soy el emisor";
	cout<<"Emisor envia mensaje: "<<mensaje<<endl;
	listo=true;
	lock.unlock();
	cv.notify_one();
	unique_lock<mutex> wait_lock(mtx);
	cout<<"-----El emisor espera a que el receptor procese el mensaje..."<<endl;
	cv.wait(wait_lock,[]{return !listo;	});
	cout<<"Emisor continua su proceso"<<endl;
}

int main(){
	thread t1(receptor);
	thread t2(emisor);
	t1.join();
	t2.join();
	return 0;
}