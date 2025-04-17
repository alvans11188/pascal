/*
Usar constructores para la ejecución de hilos.
 void comenzar_trabajo(p);
 std::thread my_hilo(comenzar_trabajo,p);
*/
#include<iostream>
#include<thread>
using namespace std;
void function_1(string msg)
{
	cout<<"Mensaje del hilo : "<<msg<<"\n";
}
int main()
{
	std::thread t1(function_1,string("1"));
	
	try
	{
		for(int i=0;i<100;i++)
			cout<<t1.get_id() << "Del menu principal"<<i<<"\n";
	}
	catch(...)
	{
		t1.join();
		throw;
	}
	t1.join();
	return 0;
}