#include <iostream>
#include <thread>

using namespace std;

bool s1=false;
bool s2=false;
int turno=1;
int dinero=1;

int maximo=10;
void pausa(){
	for ( int j=0;j<10000;j++){
		
	}
}


void p1(){
	int i=0;
	while (i<=maximo){
		cout<<"proceso 1 - ingresando"<<endl;
		s1=true;
		turno=2;
		
		while(s2==true&&turno==2){
			cout<<"Proceso 1 - espera activa"<<endl;
			pausa();
		}
		cout<<"proceso 1 - se esta realizando un deposito"<<endl;
		dinero++;
		s1=false;
		i++;	
		pausa();
	}
	
}

void p2(){
	int m=0;;
	while (m <= maximo){	
		cout<<"proceso 2 - ingresando"<<endl;
		s2=true;
		turno=1;
		
		while(s1==true&&turno==1){
			cout<<"Proceso 2 - espera activa"<<endl;
			pausa();
		}
		cout<<"proceso 2 - El dinero deposito es de "<<dinero<< " bebacoins "<<endl;
		
		s2=false;
		m++;
		pausa();
	}

}

int main(){
	thread hilo1(p1);
	thread hilo2(p2);
	
	hilo1.join();
	hilo2.join();
	
	
	return 0;
}