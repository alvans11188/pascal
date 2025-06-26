#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;
int i=0;
mutex mtx;

void inc(){
	lock_guard<mutex> lock(mtx);
	i+=2;
}
void valor(){
	lock_guard<mutex> lock(mtx);
	cout<<i<<endl;
}
void proceso_incrementar(){
	while(true){
		inc();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}
void proceso_imprimir(){
	while(true){
		valor();
		this_thread::sleep_for(chrono::milliseconds(500));
	}
}
int main(){
	thread t1(proceso_incrementar);
	thread t2(proceso_imprimir);
	
	t1.join();
	t2.join();
	return 0;
	
}