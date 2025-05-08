#include<iostream>
using namespace std;
struct Nodo {
	int info;
	Nodo* liga;
};
class Pila {
	private:
		Nodo* tope; // apunta al nodo superior de la pila
	public:
		Pila() {
			tope=NULL;
		}
		//mtodo para agregr un elemento a la pila
		void agregarPila(int dato) {
			Nodo* q = new Nodo;
			q->info = dato;
			q->liga = tope;
			tope = q;
		}
		
		//Meotdo para eliminar sacar) el elemento superior de la pila
		void sacarPila() {
			if(tope != NULL) {
				Nodo* q =tope;
				tope = q->liga;
				delete q;
			}
			else
			{
				cout << "Pila vacia, no se puede sacar elemento."<<endl;
				return ;
			}
		}
		//metodo para mostrar todos los elementos de la pila
		void mostrarPila() {
			if(tope!=NULL) {
				Nodo* q = tope;
				cout<<"Los elementos de la pila son: "<<endl;
				while(q!=NULL) {
					cout<<q->info<< " ";
					q=q->liga;
				}
				cout<<endl;
			}
			else
			{
				cout<<"Pila vacias."<<endl;
			}
		}
		
		int contarElementosPila(){
			Nodo *q;
			int i;
			q=tope;
			i=0;
			while(q!=NULL){
				i++;
				q=q->liga;
			}
			cout<<i<<endl;
		}
		
		bool buscarElementoPila( int dato){
			Nodo *q;
			int bandera;
			bandera=0;
			q=tope;
			if(q==NULL){
				cout<<"Pila vacia"<<endl;
			}
			else
			{
				while(q!=NULL){
					bandera=1;
				}
				q=q->liga;
				if(bandera==1)
				{
					cout<<"Se encontro el dato "<<endl;
				}
				else
				{
					cout<<"No se encontro el dato "<<endl;
				}
			}
		}
		bool compararCon(Nodo* tope2){
			Nodo *q,*s;
			int b1;
			q=tope;
			s=tope2;
			b1=0;
			while(q!=NULL && s!=NULL)
			{
				if(q->info==s->info)
				{
					b1=1;
				}
				q=q->liga;
				s=s->liga;
			}
			if(b1==1)
			{
				return true;
			}
		}
		
		~Pila(){
			while(tope!=NULL){
				sacarPila();
			}
		}
};

//menu interactivo
void menu(){
	Pila pila;
	Pila pila2;
	int opcion, dato;
	
	do{
		cout<<"\n---MENU PILA---"<<endl;
		cout<<"1. Aplicar en Pila1"<<endl;
		cout<<"2. Desapilar en Pila 1"<<endl;
		cout<<"3. Mostrar Pila 1"<<endl;
		cout<<"4. Conar elementos de Pila 1"<<endl;
		cout<<"5. Buscar un elementoen Pila 1"<<endl;
		cout<<"6. Apilcar en Pila 2"<<endl;
		cout<<"7. Mostar Pila 2"<<endl;
		cout<<"8- Coparar Pila 1 con Pila 2"<<endl;
		cout<<"0. Salir"<<endl;
		cout<<"Opcion: "<<endl;
		cin>>opcion;
		
		switch(opcion){
			case 1:
				cout <<"Ingrese dato a apilar en Pila 1: ";
				cin>>dato;
				pila.agregarPila(dato);
				break;
			case 2:
				pila.sacarPila();
				break;
			case 3:
				pila.mostrarPila();
				break;
			
			case 4:
				cout<<"Cantidad de elementos en Pila 1: "<< pila.contarElementosPila();
				break;
			case 5:
				cout<<"Ingrese el elemento a buscar en Pila 1: ";
				cin>>dato;
				pila.buscarElementoPila(dato);
				cout<<"¿Esa el "<<dato<<"?: "<<(pila.buscarElementoPila(dato)?"Si" : "No")? <<endl;
				break;
			case 6:
				cout<<"Ingrese el elemento a buscar en Pila 1: ";
				cin>>dato;
				pila.agregarPila(dato);
				break;
			case 7:
				pila.mostrarPila();
				break;
			case 8:
				if(pila.compararCon(pila2)) {
					cout<< "Las pilas son iguales. "<<endl;
				}
				else
				{
					cout<<"Las pilas son diferentes. "<<endl;
				}
				break;
			
			case 0:
				cout<<"Programa finalizado. "<<endl;
				break;
			default:
				cout<<"Opcion invalida."<<endl;
		}
	} while (opcion!=0);
}
int main() {
	setlocale(LC_ALL," ");
	
	menu();
	return 0;
}