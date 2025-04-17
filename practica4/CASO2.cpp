// Crear y ejecutar un bucle de comunicación entre mensajes para un determinado hilo

#include<iostream>
#include<thread>
#include<algorithm>
#include<vector>
#include<functional>
using namespace std;

void hacer_trabajo(unsigned id)
{
	cout<<id<<"\n";
}
void captura(int variable)
{
	vector<thread> hilos;
	for (unsigned i = 0; i < variable;i++)
	{
		hilos.push_back(thread(hacer_trabajo,1));
	}
	for_each(hilos.begin(), hilos.end(),mem_fn(&thread::join));
}
int main()
{
	int val;
	cout<<"Introduce un numero"	;
	cin>>val;
	captura(val);
	return 0;
}