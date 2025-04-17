//Ejecucion por turnos de forma simultanea
#include<iostream>
#include<thread>
#include<string>
#include<chrono>
using namespace std;
void saludo(string m, int retardo, int veces)
{
	for(int i=1;i<=veces;i++)
	{
		cout<<m+"\n";
		this_thread::sleep_for(chrono::milliseconds(retardo));
	}
}
int main()
{
	thread P[3];
	P[0] = thread(&saludo, "Mensaje A", 100, 10);
	P[1] = thread(&saludo, "\tMensaje B", 100, 10);
	P[2] = thread(&saludo, "\t\tMensaje C", 100, 10);
		P[0].join();
		P[1].join();
		P[2].join();
	cout<<"FIN!!"<<endl;
	return 0;
}