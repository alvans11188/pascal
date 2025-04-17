//Usar destructores despues de ejecutar hilo
#include<iostream>
#include<chrono>
#include<thread>
using namespace std;
void independentThread()
{
	std::cout<<"Iniciando hilo concurrente. \n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout<<"Saliendo hilo concurrente. \n";
}
void threadCaller()
{
	std::cout<<"Iniciador de llamada de hilo.\n";
	std::thread t(independentThread);
	t.detach();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout<<"Saliendo de llamada de hilo.\n";
}
int main()
{
	threadCaller();
	std::this_thread::sleep_for(std::chrono::seconds(5));
	return 0;
}