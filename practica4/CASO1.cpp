//Crear y ejecutar 3 hilos
#include<iostream>
#include<thread>
#include<string>
#include<chrono>
using namespace std;
void saludo (string m, int retardo, int veces)
{
	for(int i=1;i<=veces;i++)
	{
		cout<<m+"\n";
		this_thread :: sleep_for (chrono ::milliseconds (retardo));
	}
}
int main()
{
	thread th_1(&saludo,"Mensaje A",100,10),
		   th_2(&saludo,"Mensaje B",150,15),
		   th_3(&saludo,"Mensaje C",300,5);
		   
	th_1.join();
	th_2.join();
	th_3.join();
	cout<<"FIN!!"<<endl;
	return 0;
}