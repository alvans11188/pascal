//Exportar valores luego de ejecución de hilos
#include<iostream>
#include<fstream>
#include<thread>
using namespace std;

void generaarchivo(){
	std::ofstream outfile("NombreArchivo.txt");
	outfile<<"este es el nombre del archivo \n";
	outfile.close();
}
int main()
{
	std::thread nombre(generaarchivo);
	nombre.join();
	return 0;
}