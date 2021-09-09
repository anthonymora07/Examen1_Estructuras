#include<iostream>
#include<time.h>
using namespace std;

class Pila{
	
	public:
	int *cont;
	Pila *sig;
	Pila *ant;
	Pila *tope;
	Pila *datoPila;
	
	Pila(){
		
		cont=NULL;
		sig=NULL;
		ant=NULL;
		tope=NULL;
		datoPila=NULL;
	}
		
	void push(int ingresos, int gastos, int total, int porc){
			
		int *aux;
		aux = new int[4];
			
		aux[0] = ingresos;
		aux[1] = gastos;
		aux[2] = total;
		aux[3] = porc;
			
		if(tope==NULL){
				
			datoPila = new Pila;
			datoPila->cont=aux;
			datoPila->ant=NULL;
			tope=datoPila;
				
		}else{
				
			datoPila = new Pila;
			datoPila->cont=aux;
			datoPila->ant=tope;
			tope->sig=datoPila;
			datoPila->sig=NULL;
			tope=datoPila;
		}
	}
			
	int *pop(){
			
		int *num;
		num = new int[4];
		num=tope->cont;
		if(tope->ant==NULL){
			tope = NULL;
		}else{
			tope=tope->ant;
			tope->sig=NULL;
		}
		return num;
	}
		
	int *mostrarPila(){
		int *num;
		num = new int[4];
		num=tope->cont;
	    
		return num;
	}
		
};


struct Provincia{
	
	string nombre;
	int ganancias;
	Provincia* sig;
	Provincia* ant;
	int **matrizMontos;
	Pila *pila;
};

Provincia* datoPro = NULL, *auxPro = NULL, *iniPro = NULL;

class Pais{
	
	public:
		string pais;
		int ganancia;
		Pais* sig;
		Provincia* provincia;
};

Pais* datoPais = NULL, *auxPais = NULL, *iniPais = NULL;


void insertarPais(Pais *&n, string pais){
	auxPais=n;
	datoPais = new class Pais;
	if (auxPais==NULL){
		datoPais->pais=pais;
		datoPais->ganancia=0;
		datoPais->sig=NULL;
		datoPais->provincia=NULL;
		n=datoPais;
	}
	else{
		while(auxPais->sig!=NULL){
			auxPais=auxPais->sig;
		}
		datoPais->pais=pais;
		datoPais->ganancia=0;
		auxPais->sig=datoPais;
		datoPais->sig=NULL;
		datoPais->provincia=NULL;
		auxPais->sig=datoPais;
	}
}
	
	
void insertarProvincia(Pais *&n, string pais, string nombre){
	
	int **matriz;
	int random;
	int total;
	datoPro = new struct Provincia;
	auxPais=n;
	bool bandera=false;
	
	
	matriz = new int*[3];
	for(int i=0; i<3; i++){
		matriz[i] = new int[3];
	}
	
	
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			
			if(j==0){
				random = 500 + rand() % 499 + 1;
				*(*(matriz+i)+j)=random;
			}
			if(j==1){
				random = 100 + rand() % 399 + 1;
				*(*(matriz+i)+j)=random;
			}
			if(j==2){
				total = *(*(matriz+i)+0) - *(*(matriz+i)+1);
				*(*(matriz+i)+2)=total;
			}
		}
	}

	if (auxPais==NULL){
		insertarPais(auxPais, pais);
	}
	else{
		while(auxPais!=NULL && !bandera){
			if(auxPais->pais==pais){
				bandera=true;
			}
			else{
				auxPais=auxPais->sig;
			}
		}
		if(bandera){
			auxPro=auxPais->provincia;
			if (auxPro==NULL){
				datoPro->nombre=nombre;
				datoPro->ganancias=0;
				datoPro->matrizMontos=matriz;
				datoPro->sig=NULL;
				datoPro->ant=NULL;
				auxPais->provincia=datoPro;
			}
			else{
				while(auxPro->sig!=NULL){
					auxPro=auxPro->sig;
				}
				datoPro->nombre=nombre;
				datoPro->ganancias=0;
				datoPro->matrizMontos=matriz;
				datoPro->sig=NULL;
				datoPro->ant=NULL;
				auxPro->sig=datoPro;
			}
		}
		else{
			cout<<"PAIS "<<pais<<" NO ENCONTRADO!"<<endl;
		}
	}
}
	
void mostrarPais(Pais *l) {

	if(l == NULL){
		cout<<"No hay pisos por recorrer!"<<endl;
	}else{
		while (l != NULL) {
			cout<<"Pais: "<<l->pais<<"  Ganancias: "<<l->ganancia<<endl;
			l = l->sig;
		}
	}
	cout<<endl;
}

void mostrarProvinciasPorPais(Pais *l, string pais) {
		
	bool bandera = false;
	Provincia *pro = NULL;
	if(l == NULL){
		cout<<"No hay paises por recorrer!"<<endl;
	}else{
		while (bandera == false) {
			if(l->pais == pais){				
				pro = l->provincia;
				bandera = true;
			
			}if(!bandera){
				l = l->sig;
			}
		}
		if (bandera){
			cout<<endl<<endl<<"Pais: "<<l->pais<<endl;
			
			while (pro != NULL) {
				cout<<endl;
				cout<<"Provincia: "<<pro->nombre<<"   Ganancias: "<<pro->ganancias<<endl<<endl;
				cout<<"Ing\tGan\tTot"<<endl;
				for (int i=0; i<3; i++)
				{
					for (int j=0; j<3; j++)
					{
						cout<<*(*(pro->matrizMontos+i)+j)<<"\t";
					}
					cout<<endl;
				}
				pro = pro->sig;
			}
			cout<<endl;
		}
		else
		{
			cout<<"Pais: "<<pais<<" NO ENCONTRADO!"<<endl;
		}
	}
}

void copiarMatrizPila(Pais *&l){
	
	auxPais = l;
	bool bandera = false;
	Provincia *pro = NULL;

	if(auxPais == NULL){
		cout<<"No hay paises por recorrer!"<<endl;
	}else{
		while (bandera == false) {
			if(auxPais != NULL){
				pro = auxPais->provincia;
				while (pro != NULL) {
					int anho = 2019;
					pro->pila = new Pila();
					cout<<"        |Ingresos   |Gastos   |Total"<<endl<<endl;
					for(int i=0;i<3;i++){
						for(int j=0;j<1;j++){
							pro->pila->push(*(*(pro->matrizMontos+i)+j), *(*(pro->matrizMontos+i)+(j+1)), *(*(pro->matrizMontos+i)+(j+2)),0);
							//cout<<"|"<<((pais_a_recorrer->tabla_ingresos+i)+j)<<"     ";
						}
						Pila *auxPila = pro->pila;
						cout<<anho<<" -> "<<"|"<<auxPila->mostrarPila()[0]<<"        |"<<auxPila->mostrarPila()[1]<<"      |"<<auxPila->mostrarPila()[2]<<endl;
						cout<<endl;
						anho++;
					}
					pro = pro->sig;
				}
				cout<<endl;
				auxPais = auxPais->sig;
			}else{
				break;
			}
		}
	}
}
	
void porcentajeCrecimiento(Pais *&l, bool mostrar){
	
	//(Total-TotalAnt)*100/TotalAnt

	auxPais = l;
	bool bandera = false;
	Provincia *pro = NULL;

	if(auxPais== NULL){
		cout<<"No hay paises por recorrer!"<<endl;
	}else{
		while (bandera == false) {

		if(auxPais != NULL){
			pro = auxPais->provincia;
				while (pro != NULL) {
					int anho = 2019;
				 
					pro->pila = new Pila();
					Pila *auxPila = pro->pila;
					cout<<"Pais: "<<auxPais->pais<<endl;
					cout<<"Provincia: "<<pro->nombre<<endl<<endl;
					cout<<"        |Ingresos   |Gastos   |Total    |Porcentaje"<<endl<<endl;
					for(int i=0;i<3;i++){
						for(int j=0;j<1;j++){
							if(i==0){
								pro->pila->push(*(*(pro->matrizMontos+i)+j), *(*(pro->matrizMontos+i)+(j+1)), *(*(pro->matrizMontos+i)+(j+2)),0);	
							
							}else{
							    pro->pila->push(*(*(pro->matrizMontos+i)+j), *(*(pro->matrizMontos+i)+(j+1)), *(*(pro->matrizMontos+i)+(j+2)), ((*(*(pro->matrizMontos+i)+(j+2))-*(*(pro->matrizMontos+(i-1))+(j+2)))*100)/(*(*(pro->matrizMontos+(i-1))+(j+2))));	        
							}
						}
						if(mostrar==true){
						
							cout<<anho<<" -> "<<"|"<<auxPila->mostrarPila()[0]<<"        |"<<auxPila->mostrarPila()[1]<<"      |"<<auxPila->mostrarPila()[2]<<"      |"<<auxPila->mostrarPila()[3]<<endl;
							cout<<endl<<endl;
							anho++;
					
						}else{
		
							cout<<anho<<" -> "<<"|"<<auxPila->mostrarPila()[0]<<"        |"<<auxPila->mostrarPila()[1]<<"      |"<<auxPila->mostrarPila()[2]<<endl;
							cout<<endl<<endl;
							anho++;
						}
					}
					pro->ganancias = auxPila->mostrarPila()[3];
					pro = pro->sig;
				}
				cout<<"-----------------------------------------------------"<<endl;
				auxPais = auxPais->sig;
		}else{
			
			break;
		}
		}
	}
}
	
void promedioPais(Pais *&l){
	
	auxPais = l;
	bool bandera = false;
	Provincia *pro = NULL;
	
	if(auxPais == NULL){
		cout<<"No hay paises por recorrer!"<<endl;
	}else{

		while (bandera == false) {

			if(auxPais != NULL){
				int suma = 0;
				pro = auxPais->provincia;
				int cont = 0;
				while (pro != NULL) {
					pro->pila = new Pila();
					Pila *auxPila = pro->pila;
					for(int i=0;i<3;i++){
						for(int j=0;j<1;j++){
							if(i==0){
								pro->pila->push(*(*(pro->matrizMontos+i)+j), *(*(pro->matrizMontos+i)+(j+1)), *(*(pro->matrizMontos+i)+(j+2)),0);	
								
							}else{
								pro->pila->push(*(*(pro->matrizMontos+i)+j), *(*(pro->matrizMontos+i)+(j+1)), *(*(pro->matrizMontos+i)+(j+2)), ((*(*(pro->matrizMontos+i)+(j+2))-*(*(pro->matrizMontos+(i-1))+(j+2)))*100)/(*(*(pro->matrizMontos+(i-1))+(j+2))));	        
							}
							suma = suma + auxPila->mostrarPila()[3];
						}
						cont++;
					}
					auxPais->ganancia = suma/cont;
					pro = pro->sig;
				}
				auxPais = auxPais->sig;
			}else{
				
				break;
			}
		}
	}
}
	
void paisesSinGanancias(Pais *&l){
	
	Provincia *pro = NULL;
	auxPais = l;
	
	if(auxPais == NULL){
		cout<<"No hay pisos por recorrer!"<<endl;
	}else{
		
		while(auxPais != NULL){
			if(auxPais != NULL && auxPais->ganancia <= 0){
				pro = auxPais->provincia;
				cout<<"Pais: "<<auxPais->pais<<"  Ganancias: "<<auxPais->ganancia<<endl;
				while(pro != NULL){
					if(pro->ganancias <= 0){
						cout<<"\tProvincia: "<<pro->nombre<<"  Ganancia: "<<pro->ganancias<<endl;
					}
					pro = pro->sig;
				}
			}
			cout<<endl;
			auxPais = auxPais->sig;
		}
	}
}
	
void borrarSinGanancias(Pais *&l){
	
	Provincia *pro = NULL;
	auxPais = l;
	
	if(auxPais == NULL){
		cout<<"No hay pisos por recorrer!"<<endl;
	}else{
		
		while(auxPais != NULL){
			if(auxPais != NULL && auxPais->ganancia <= 0){
				pro = auxPais->provincia;
				cout<<"Pais: "<<auxPais->pais<<"  Ganancias: "<<auxPais->ganancia<<endl;
				while(pro != NULL){
					cout<<"\tProvincia: "<<pro->nombre<<endl;
					pro = pro->sig;
				}
			}
		}
	}	
}
	

	


int main (int argc, char *argv[]) {
	
	bool salir = true;
	
	insertarPais(iniPais, "Panama");
	insertarPais(iniPais, "Cuba");
	insertarPais(iniPais, "USA");
	insertarPais(iniPais, "Mexico");
	insertarPais(iniPais, "Costa Rica");
	insertarProvincia(iniPais, "USA", "NY");
	insertarProvincia(iniPais, "USA", "Ohio");
	insertarProvincia(iniPais, "Costa Rica", "SJ");
	insertarProvincia(iniPais, "Costa Rica", "Alajuela");
	insertarProvincia(iniPais, "Costa Rica", "Guanacaste");
	
	srand(time(NULL));
	
	
	do{
		
		int op;
	
		
		system("cls");
		cout<<endl<<"\t----- BIENVENIDO AL MENU -----"<<endl<<endl;
		cout<<"\t1) Mostrar Paises."<<endl;
		cout<<"\t2) Mostrar Provincias por Pais."<<endl;
		cout<<"\t3) Llenar Matrices en Pila."<<endl;
		cout<<"\t4) Ver Porcentajes de Crecimiento."<<endl;
		cout<<"\t5) Mostrar Paises y Estados que no Generan Ganancias."<<endl;
		cout<<"\t6) Salir."<<endl;
		cout<<endl<<"\tOpcion: ";
		cin>>op;
		
		if(op == 1){
			
			system("cls");
			mostrarPais(iniPais);
			cout<<endl<<endl;
			system("pause");
		}
		
		if(op == 2){
			
			system("cls");
			string pais;
			cout<<"Digite el nombre del pais a consultar: ";
			cin>>pais;
			mostrarProvinciasPorPais(iniPais,pais);
			cout<<endl<<endl;
			system("pause");
		}
		
		if(op == 3){
			
			system("cls");
			porcentajeCrecimiento(iniPais, false);
			cout<<endl<<endl;
			system("pause");
		}
		
		if(op == 4){
			
			system("cls");
			porcentajeCrecimiento(iniPais, true);
			promedioPais(iniPais);
			cout<<endl<<endl;
			system("pause");
		}
		
		if(op == 5){
			
			system("cls");
			porcentajeCrecimiento(iniPais, true);
			paisesSinGanancias(iniPais);
			cout<<endl<<endl;
			system("pause");
		}
		
		if(op == 6){
			
			salir = false;
		}
		
	} while(salir == true);
	
	


	/*insertarPais(iniPais, "Jamaica");
	insertarProvincia(iniPais, "Jamaica", "Perez");
	insertarProvincia(iniPais, "Jamaica", "Limon");
	mostrarPais(iniPais);
	promedioPais(iniPais);
	mostrarPais(iniPais);
	//mostrarPais(iniPais);
	cout<<endl;
	//paisesSinGanancias(iniPais);	
	//insertarPais(iniPais, "Panana");
	//copiarMatrizPila(iniPais);

	
	//mostrarProvinciasPorPais(iniPais, "Jamaica");

	

	



	//mostrarProvinciasPorPais(iniPais, "Limon");

	
	//mostrarProvinciasPorPais(iniPais, "Peru");
	//mostrarProvinciasPorPais(iniPais, "Mexico");*/

	return 0;
}

