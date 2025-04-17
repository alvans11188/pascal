/*
Emplear variables compartidas
 class repositorio_tareas {
 // colocar funcion
 };
 std::thread my_hilo(repositorio_tareas());

*/
#include<iostream>
#include<thread>
#include<string>
#include<chrono>
using namespace std;
//parte de especificacion: variables  y funciones de los objetos de esta clase
class saludador
{
	public:
		saludador(string mens,//constructor suministrando datos
				int retardo,
				int veces);
		saludador();
		void run();
		//mas funciones , si las hubiera
		string mens;
		int retardo, veces;
};
//implementacion (las funciones de los objetos de la clase)
saludador::saludador(string mens, int retardo, int veces)
{
	this->mens = mens; //mens: parametro  de la funcion
//this -> mens : variable del objeto
	this->retardo = retardo;
	this->veces=veces;
};

saludador::saludador()
{
	mens=""; //mens:parametro de la funcion
//this -> mens : variable propia
	retardo=0;
	veces=0;
};
void saludador :: run()
{
	for(int i=1;i<=veces;i++)
	{
		cout<<mens+"\n";
		this_thread::sleep_for(chrono::milliseconds(retardo));	
	}	
};

int main()
{
	//creacion de los objetos : constructor con datos
	saludador s1("Mensaje 1",100,10),
			  s2("\tMensaje 2",150,15),
			  s3("\t\tMensaje 3",10,40);
	//creacion de los objetos : constructor por defecto
	saludador s4;
	s4 ={"\t\t\tMensaje 4 ", 2, 12};
	cout << " veces : "<<s4.veces << "\n";
	
	thread th_1 = thread (&saludador :: run , s1);
	thread th_2 = thread (&saludador :: run , s2);
	thread th_3 = thread (&saludador :: run , s3);
	thread th_4 = thread (&saludador :: run , s4);
	//esperar a que vayan acabando
	th_1.join ();
	th_2.join ();
	th_3.join ();
	th_4.join ();
	
	return 0;
}
