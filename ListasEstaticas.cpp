#include<iostream>

using namespace std;

const int MAX = 20;

class Empleado{
	private:
		int ClaveEmpleado;
		string Nombre;
		string Domicilio;
		float Sueldo;
		string ReportaA;
	public:
		Empleado(){};
		Empleado(int C, string N, string D, float S, string R): ClaveEmpleado(C), Nombre(N), Domicilio(D), Sueldo(S), ReportaA(R){}
		
	friend Empleado operator +(Empleado& e1, Empleado& e2){
    	return Empleado(e1.ClaveEmpleado+e2.ClaveEmpleado, e1.Nombre+e2.Nombre, e1.Domicilio+e2.Domicilio, e1.Sueldo+e2.Sueldo, e1.ReportaA+e2.ReportaA);
    }
    	
    friend bool operator ==(Empleado& e1, Empleado& e2){
        return (e1.ClaveEmpleado == e2.ClaveEmpleado &&
            e1.Nombre == e2.Nombre &&
            e1.Domicilio == e2.Domicilio &&
            e1.Sueldo == e2.Sueldo &&
            e1.ReportaA == e2.ReportaA);
    }

    friend bool operator !=(Empleado& e1, Empleado& e2){
        return !(e1 == e2);
    }

    friend istream& operator >>(istream& input, Empleado& e){
	    cout << "\nIngrese la clave del empleado: ";
	    input >> e.ClaveEmpleado;
	    cout << "\nIngrese el nombre del empleado: ";
	    input >> e.Nombre;
	    cout << "\nIngrese el domicilio del empleado: ";
	    input >> e.Domicilio;
	    cout << "\nIngrese el sueldo del empleado: ";
	    input >> e.Sueldo;
	    cout << "\nIngrese a quien reporta el empleado: ";
	    input >> e.ReportaA;
	    return input;
	}

    friend ostream& operator <<(ostream& out, Empleado& e){
        out<<"Clave: "<<e.ClaveEmpleado<<"\n";
        out<<"Nombre: "<<e.Nombre<<"\n";
        out<<"Domicilio: "<<e.Domicilio<<"\n";
        out<<"Sueldo: "<<e.Sueldo<<"\n";
        out<<"Reporta a: "<<e.ReportaA<<"\n";
        return out;
    }

    friend bool operator <(Empleado& e1, Empleado& e2) {
        return e1.ClaveEmpleado < e2.ClaveEmpleado;
    }
    
    friend bool operator >(Empleado& e1, Empleado& e2) {
        return e1.ClaveEmpleado > e2.ClaveEmpleado;
    }
};

class ListaEstatica{
	private:
		int Tam;
		Empleado Datos[MAX];
	public:
		ListaEstatica(): Tam(-1){};
		
		int Vacia(){
			if(Tam==-1)
				return 1;
			return 0;
		}
		
		int Llena(){
			if(Tam==MAX-1)
				return 1;
			return 0;
		}
		
		int Inserta(Empleado& T, int p){
			if(Llena())
				return 400;
			if(p < 0 || p > MAX)
				return 405;
			Tam++;
			for(int i = Tam; i > p; i--){
				Datos[i] = Datos[i-1];
			}
			Datos[p] = T;
			return 201;
		}
		
		int Agregar(Empleado& T){
			if(Llena())
				return 400;
			Tam++;
			Datos[Tam] = T;
			return 201;
		}
		
		int Buscar(Empleado& T){
			if(Vacia())
				return 400;
			for(int i = 0; i<=Tam; i++){
				if(Datos[i] == T)
					return i;
			}
			return 404;
		}
		
		int Elimina(int p){
			if(Vacia())
				return 400;
			if(p < 0 || p > Tam)
				return 404;
			for(int i = p; i<=Tam-1; i++){
				Datos[i] = Datos[i+1];
			}
			Tam--;
			return 200;
		}
		
		int Muestra(){
			if(Vacia())
				return 400;
			cout<<"Lista de Empleados"<<endl;
			for(int i = 0; i<=Tam; i++){
				cout<<"***************"<<endl;
				cout<<Datos[i];
				cout<<"***************"<<endl;
			}
			return 1;
		}
};

int main(){
	ListaEstatica L;
	Empleado T;
	int opcion = 0, busqueda, posicion, status;
	
	while(opcion != 6){
		cout<<"*****Listas Estaticas*****"<<endl;
		cout<<"1- Agrega"<<endl;
		cout<<"2- Buscar"<<endl;
		cout<<"3- Elimina"<<endl;
		cout<<"4- Inserta"<<endl;
		cout<<"5- Muestra"<<endl;
		cout<<"6- Salir"<<endl;
		cout<<"Tu opcion: ";
		cin>>opcion;
		
		switch(opcion){
			case 1:
				cout<<"Agrega Empleado a la lista"<<endl;
				cin>>T;
				if(L.Agregar(T) == 400)
					cout<<"La lista esta llena"<<endl;
				break;
			case 2:
				cout<<"Buscar un Empleado en la lista"<<endl;
				cout<<"Ingresa los datos del Empleado que quieres buscar: "<<endl;
				cin>>T;
				busqueda = L.Buscar(T);
				if(busqueda == 400){
					cout<<"La lista esta vacia"<<endl;
				}else if(busqueda == 404){
					cout<<"Empleado no encontrado"<<endl;
				}else
					cout<<"Posicion del empleadoen la lista: "<<busqueda<<endl;
				break;
			case 3:
				cout<<"Dame la posicion del Empleado a Eliminar: ";
				cin>>busqueda;
				status = L.Elimina(busqueda);
				if(status == 400)
					cout<<"Lista Vacia"<<endl;
				if(status == 404)
					cout<<"No se encontro el Empleado a eliminar"<<endl;	
				break;
			case 4:
				cout<<"Dame el Empleado a insertar"<<endl;
				cin>>T;
				cout<<"Dame la posicion donde se deba insertar el Empleado; ";
				cin>>posicion;
				status = L.Inserta(T, posicion);
				if(status == 400)
					cout<<"La lista esta llena"<<endl;
				if(status == 405)
					cout<<"No se puede insertar el empleado en dicha posicion"<<endl;
				break;
			case 5:
				status = L.Muestra();
				break;
			case 6:
				cout<<"Saliendo...";
				break;
			default:
				cout<<"Escoja una opcion valida"<<endl;
		}
	}
	return 0;
}