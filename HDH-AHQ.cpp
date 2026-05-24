#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctype.h>
#include <limits>
#include <iomanip>
#include <algorithm>


using namespace std;





void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}


struct Producto{
	int id;
	string nombre;
	string categoria;
	int anio;
	string tipo;
	bool activo;
	
	
};

struct Investigador {
	int id;
	string nombre;
	vector<Producto> productos;
	bool activo;
	int idGrupo;
	
};

struct Grupo {
	
	int id;
	string nombre;
	string area;
	string lider;
	vector<string> Profesores;
	vector<Producto> productos;
	bool activo;
	
	
};




int buscarGrupo(vector<Grupo> &grupo, int id){
	
	for(int i = 0; i < grupo.size(); i++){
		
		if(grupo[i].id == id && grupo[i].activo){
			return i;
		}
		
		
	}
	return -1;
	
}

int buscarProducto(vector<Producto> &productos, int id){
	
	for(int i = 0; i < productos.size(); i++){
		if(productos[i].id == id && productos[i].activo)
		{
			return i;
		}
	}
	return -1;
	
}

int buscarInvestigador(vector<Investigador> & inv, int id ){
	for(int i = 0; i < inv.size(); i++){
		if(inv[i].id == id && inv[i].activo)
		{
			return i;
		}
	}
	return -1;
	
}

void TITULO(){
	system("cls");
	system("color F1");
	gotoxy(26,7); cout << "Universidad Popular del Cesar";	
	gotoxy(25,8); cout << "Programa Estadistico de Analisis";
	
}

void crearGrupo(vector<Grupo> &grupo){
	TITULO();
	Grupo g;
	
	
	gotoxy(23,10); cout << "Id del Grupo :";
	gotoxy(37,10); cin >> g.id;
	
	gotoxy(23,11); cout << "Nombre :";
	gotoxy(31,11); cin >> g.nombre;
	
	gotoxy(23,12); cout << "Area :";
	gotoxy(29,12); cin >> g.area;
	
	g.activo = true;
	
	grupo.push_back(g);
	
	gotoxy(20,20); cout << "GRUPO CREADO";
	getche();
	
	
}

void mostrarGrupo(vector<Grupo> grupo){
    TITULO();
    int y = 11;

    gotoxy(5,10);
    cout << left << setw(10) << "ID"
         << setw(20) << "NOMBRE"
         << setw(20) << "AREA";

    for(auto g : grupo){
        if(g.activo){
            gotoxy(5,y);
            cout << left << setw(10) << g.id
                 << setw(20) << g.nombre
                 << setw(20) << g.area;
            y++;
        }
    }

    getche();
}

void modificarGrupo(vector<Grupo> &grupo){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "ID del grupo :";
	gotoxy(37,10); cin >> id;
	
	int gr = buscarGrupo(grupo, id);
	
	if(gr == -1){
		gotoxy(20,20); cout << "//GRUPO NO EXISTE//";
		getche();
		return;
	}
	
	Grupo &g = grupo[gr];
	
	int OP;
	
	do{
		gotoxy(20,20); cout << "Que desea Modificar?:";
		gotoxy(20,21); cout << "1.Nombre - 2.Area - 3.ID - 4.Estado(Desactivar)";
		
		gotoxy(41,20); cin >> OP;
	}while((OP > 4)||(OP < 1));
	
	switch(OP){
		case 1: gotoxy(23,14); cout << "Nuevo Nombre :";
    			cin.ignore(numeric_limits<streamsize>::max(), '\n');
    			gotoxy(37,14); getline(cin, g.nombre);
    			break; 
		case 2: gotoxy(23,14); cout << "Nuevo Area :";
				gotoxy(35,14); cin >> g.area;
				break;
		case 3: gotoxy(23,14); cout << "Nuevo ID :";
				gotoxy(33,14); cin >> g.id;
				break;
		case 4: g.activo = false;
				break;
	}
	

	
}

void eliminarGrupo(vector<Grupo> &grupo){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "ID del Grupo :";
	gotoxy(37,10); cin >> id;
	
	int gr = buscarGrupo(grupo, id);
	
	if(gr == -1){
		gotoxy(20,20); cout << "//GRUPO NO EXISTE//";
		getche();
		return;
	}
	
	grupo.erase(grupo.begin() + gr);
	
	gotoxy(20,20); cout << "//GRUPO ELIMINADO//";
	
	
}

string selecionarCategoria(){

	int op; 
	 do{
		TITULO();
		 gotoxy(28,10); cout << "=== SELECCIONAR CATEGORIA ===";

        gotoxy(23,12); cout << "1. Nc.Top";
        gotoxy(23,13); cout << "2. Nc.A";
        gotoxy(23,14); cout << "3. Nc.B";
        gotoxy(23,15); cout << "4. AP";
        gotoxy(23,16); cout << "5. DPC";
        gotoxy(23,17); cout << "6. Fr.A";
        gotoxy(23,18); cout << "7. Fr.B";
        gotoxy(23,19); cout << "8. Cohe";
        gotoxy(23,20); cout << "9. Coop";

        gotoxy(20,22); cout << "Seleccione una opcion: ";
        gotoxy(45,22); cin >> op;



	 }while((op > 9)||(op < 1));

	 switch(op) {
        case 1: return "NC_TOP";
        case 2: return "NC_A";
        case 3: return "NC_B";
        case 4: return "AP";
        case 5: return "DPC";
        case 6: return "FR_A";
        case 7: return "FR_B";
        case 8: return "COHE";
        case 9: return "COOP";
    }





}

void agregarProductoaGrupo(vector<Grupo> &grupo){
	TITULO();
	int id, gr;
	
	gotoxy(23,10); cout << "Ingrese el Id del Grupo";
	gotoxy(46,10); cin >> id;
	
	gr = buscarGrupo(grupo, id);
	
	if(gr == -1){
		gotoxy(20,20); cout << "//EL GRUPO NO EXISTE//";
		getche();
		return;
	}
	
	Producto p;
	
	gotoxy(23,12); cout << "Nombre :";
	cin.ignore();
	gotoxy(31,12); getline(cin, p.nombre);
	
	gotoxy(23,13); cout << "Anio :";
	gotoxy(29,13); cin >> p.anio;
	
	gotoxy(23,14); cout << "Id :";
	gotoxy(27,14); cin >> p.id;
	
	gotoxy(23,15); cout << "Categoria :";
	p.categoria = selecionarCategoria();

	TITULO();

	gotoxy(23,16); cout << "Tipo :";
	gotoxy(29,16); cin >> p.tipo;
	
	p.activo = true;
	
	grupo[gr].productos.push_back(p);
	
	
	gotoxy(20,20); cout << "//PRODUCTO AGREGADO//";
	getche();
	
	
	
}


void mostrarProducto(vector<Grupo> &grupo){
    TITULO();
    int id;
    int y = 13;

    gotoxy(23,10); cout << "Ingrese el ID :";
    gotoxy(38,10); cin >> id;

    int gr = buscarGrupo(grupo, id);

    if(gr == -1){
        gotoxy(20,20); cout << "//NO EXISTE EL GRUPO//";
        getche();
        return;
    }

    gotoxy(5,12);
    cout << left << setw(23) << "NOMBRE"
         << setw(10) << "ID"
         << setw(10) << "AÑO"
         << setw(15) << "CATEGORIA"
         << setw(15) << "TIPO";

    for(auto i : grupo[gr].productos){
        if(i.activo){

           
            i.nombre.erase(remove(i.nombre.begin(), i.nombre.end(), '"'), i.nombre.end());
            i.categoria.erase(remove(i.categoria.begin(), i.categoria.end(), '"'), i.categoria.end());
            i.tipo.erase(remove(i.tipo.begin(), i.tipo.end(), '"'), i.tipo.end());

            gotoxy(5,y);
            cout << left << setw(23) << i.nombre
                 << setw(10) << i.id
                 << setw(10) << i.anio
                 << setw(15) << i.categoria
                 << setw(15) << i.tipo;
            y++;
        }
    }

    getche();
}


void modificarProducto(vector<Grupo> &grupo){
	TITULO();
	int id, id2;
	
	gotoxy(23,10); cout << "ID del Grupo :";
	gotoxy(37,10); cin >> id;
	
	int gr = buscarGrupo(grupo, id);
	
	if(gr == -1){
		gotoxy(20,20); cout << "//GRUPO NO EXISTE//";
		getche();
		return; 
	}
	
	gotoxy(23,12); cout << "ID del Producto :";
	gotoxy(40,12); cin >> id2;
	
	int pr = buscarProducto(grupo[gr].productos, id2);
	
	if(pr == -1){
		gotoxy(20,20); cout << "//PRODUCTO NO ENCONTRADO//";
		getche();
		return;
	}	
	
	Producto &p = grupo[gr].productos[pr];
	
	int OP;
	
	do{
		gotoxy(20,20); cout << "Que desea Modificar?:";
		gotoxy(20,21); cout << "1.Nombre - 2.ID - 3.Años - 4.Categoria - 5.Tipo - 6.Estado(Desactivar)";
		
		gotoxy(41,20); cin >> OP;
	}while((OP > 6)||(OP < 1));
	
	switch(OP){
		case 1: gotoxy(23,14); cout << "Nuevo Nombre :";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				gotoxy(37,14); getline(cin, p.nombre);
				break; 
		case 2: gotoxy(23,14); cout << "Nuevo ID :";
				gotoxy(33,14); cin >> p.id;
				break;                                     
		case 3: gotoxy(23,14); cout << "Nuevo Año :";
				gotoxy(34,14); cin >> p.anio;
				break;
		case 4: gotoxy(23,14); cout << "Nueva Categoria :";
				p.categoria = selecionarCategoria();
				break;
		case 5: gotoxy(23,14); cout << "Nuevo Tipo :";
				gotoxy(35,14); cin >> p.tipo;
				break;
		case 6: p.activo = false;
				break;
		
	}
	

	
	
}


void eliminarProducto(vector<Grupo> &grupo){
	TITULO();
	int id, id2;
	
	
	gotoxy(23,10); cout << "ID del Grupo :";
	gotoxy(37,10); cin >> id;
	
	int gr = buscarGrupo(grupo, id);
	
	if(gr == -1){
		gotoxy(20,20); cout << "//GRUPO NO EXISTE//";
		getche(); 
		return;
	}
	
	gotoxy(23,12); cout << "ID del Producto :";
	gotoxy(40,12); cin >> id2;
	
	int pr = buscarProducto(grupo[gr].productos, id2);
	
	if(pr == -1){
		gotoxy(20,20); cout << "//PRODUCTO NO EXISTE//";
		getche();
		return;
	}
	
	grupo[gr].productos.erase(grupo[gr].productos.begin() + pr);
	
	gotoxy(20,20); cout << "//PRODUCTO ELIMINADO//";
	getche();
	
	
	
}

void filtrarPorAnio(vector<Grupo> &grupo){
	TITULO();
	int anio;
	int y = 13;
	
	gotoxy(23,10); cout << "Desde el Año :";
	gotoxy(37,10); cin >> anio;
	
	gotoxy(18,12); cout << "ID     NOMBRE     AÑO";
	
	for(auto g :grupo){
		for(auto p : g.productos){
			if(p.activo && p.anio >= anio){
				gotoxy(18,y); cout << p.id;
				gotoxy(25,y); cout << p.nombre;
				gotoxy(36,y); cout << p.anio;
				y++;
			}
		}
	}
	
	getche();
	
}

void crearInvestigador(vector<Investigador> &inv, vector<Grupo> &grupo){
	TITULO();
	Investigador i;
	
	gotoxy(23,10); cout << "Nombre del Investigador :";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	gotoxy(48,10); getline(cin, i.nombre);
	
	gotoxy(23,11); cout << "ID del Investigaor :";
	gotoxy(43,11); cin >> i.id;
	
	gotoxy(23,12); cout << "ID del grupo :";
	gotoxy(37,12); cin >> i.idGrupo;
	
	int gr = buscarGrupo(grupo, i.idGrupo);
	
	if(gr == -1){
		gotoxy(20,20); cout << "//GRUPO NO EXISTE//";
		getche();
		return;
	}
	
	i.activo = true;
	
	inv.push_back(i);
	
	gotoxy(20,20); cout << "//INVESTIGADOR CREADO//";
	getche();
	
}

void mostrarInvestigador(vector<Investigador> &inv){
    TITULO();
    int y = 13;

    gotoxy(5,12);
    cout << left << setw(10) << "ID"
         << setw(25) << "NOMBRE"
         << setw(10) << "GRUPO";

    for(auto i: inv){
        if(i.activo){
            gotoxy(5,y);
            cout << left << setw(10) << i.id
                 << setw(25) << i.nombre
                 << setw(10) << i.idGrupo;
            y++;
        }
    }

    getche();
}

void modificarInvestigador(vector<Investigador> &inv){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el ID: ";
	gotoxy(38,10); cin >> id;
	
	int in = buscarInvestigador(inv, id);
	
	if(in == -1){
		gotoxy(20,20); cout << "//INVESTIGADOR NO EXISTE//";
		getche(); 
		return;
	}
	
	Investigador &i = inv[in];
	int op;
	
	do{
		gotoxy(44,12); cout << "             ";
		gotoxy(23,12); cout << "Que desea modificar?: ";
		gotoxy(23,13); cout << "1.Nombre  2.Id  3.Desactivar";
		gotoxy(44,12); cin >> op;
		
	}while((op > 3)||(op < 1));
	
	switch(op){
		case 1: gotoxy(23,15); cout << "Nuevo Nombre: ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				gotoxy(36,15); getline(cin, i.nombre);
				break;
		case 2: gotoxy(23,15); cout << "Nuevo ID: ";
    			gotoxy(33,15); cin >> i.id;
    			break;
		case 3: i.activo = false;
				break;
	}
	gotoxy(20,20); cout << "//MODIFICADO//";
	getche();
	
}

void eliminarInvestigador(vector<Investigador> &inv){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el ID: ";
	gotoxy(38,10); cin >> id;
	
	int in = buscarInvestigador(inv, id);
	
	if(in == -1){
		gotoxy(20,20); cout << "//INVESTIGADOR NO EXISTE//";
		getche(); 
		return;
	}
	
	inv.erase(inv.begin() + in);
	
	gotoxy(20,20); cout << "//INVESTIGADOR ELIMINADO//";
	getche();
	
}



void agregarProductoInvestigador(vector<Investigador> &inv){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el ID del Investigador: ";
	gotoxy(55,10); cin >> id;
	
	int in = buscarInvestigador(inv, id);
	
	if(in == -1){
		gotoxy(20,20); cout << "//INVESTIGADOR NO EXISTE//";
		getche(); 
		return;
	}
	
	Producto p;
	
	gotoxy(23,12); cout << "Nombre: ";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	gotoxy(31,12); getline(cin, p.nombre);
	
	gotoxy(23,13); cout << "ID: ";
	gotoxy(27,13); cin >> p.id;
	
	gotoxy(23,14); cout << "Anio: ";
	gotoxy(29,14); cin >> p.anio;
	
	gotoxy(23,15); cout << "Categoria: ";
	p.categoria = selecionarCategoria();
	TITULO();

	gotoxy(23,16); cout << "Tipo: ";
	gotoxy(29,16); cin >> p.tipo;
	
	p.activo = true;
	
	inv[in].productos.push_back(p);
	
	gotoxy(20,20); cout << "//PRODUCTO AGREGADO//";
	getche();
}

void mostrarProductosInvestigador(vector<Investigador> &inv){
    TITULO();
    int id;
    int y = 13;

    gotoxy(23,10); cout << "Ingrese el ID del investigador: ";
    gotoxy(55,10); cin >> id;

    int in = buscarInvestigador(inv, id);

    if(in == -1){
        gotoxy(20,20); cout << "//INVESTIGADOR NO EXISTE//";
        getche();
        return;
    }

    gotoxy(5,12);
    cout << left << setw(20) << "NOMBRE"
         << setw(10) << "ID"
         << setw(10) << "AÑO"
		 << setw(10) << "CATEGORIA";

    for(auto p: inv[in].productos){
        if(p.activo){

            
            p.nombre.erase(remove(p.nombre.begin(), p.nombre.end(), '"'), p.nombre.end());

            gotoxy(5,y);
            cout << left << setw(20) << p.nombre
                 << setw(10) << p.id
                 << setw(10) << p.anio
				 << setw(10) << p.categoria;
            y++;
        }
    }

    getche();
}

void resumenDatos(vector<Grupo> &grupo, vector<Investigador> &inv){
	TITULO();
	int totalGrupos = 0;
	int totalInvestigadores = 0;
	int totalProductos = 0;
	
	for(auto g: grupo){
		if(g.activo){
			totalGrupos++;
			for(auto p : g.productos){
    			if(p.activo) {
    				totalProductos++;
				}
			}
		}
	}
	
	for(auto i: inv ){
		if(i.activo){
			totalInvestigadores++;
			for(auto p : i.productos){
    			if(p.activo) {
    				totalProductos++;
				}
			}
		}
	}
	
	gotoxy(33,9); cout << "--RESUMEN DE DATOS--";
	
	gotoxy(25,10); cout << "Grupos: " << totalGrupos;
	gotoxy(25,11); cout << "Investigadores: " << totalInvestigadores;
	gotoxy(25,12); cout << "Productos: " << totalProductos;
	
	getche();
	
}

void cargarGrupos(vector<Grupo> &grupo){
	
	ifstream archivo("grupos.csv");
	
	if(!archivo){
		gotoxy(20,22); cout << "Error al abrir el Archivo";
		getche();
		return;
	}
	
	string linea;
	
	while(getline(archivo, linea)){
		stringstream ss(linea);
		string dato;
		
		Grupo g;
		
		getline(ss, dato, ',');
		
		g.id = stoi(dato);
		
		getline(ss, g.nombre, ',');
		getline(ss, g.area, ',');
		
		g.activo = true;
		grupo.push_back(g);
	}
	
	archivo.close();
}

void cargarInvestigadores(vector<Investigador> &inv){
	
	ifstream archivo("investigadores.csv");
	
	if(!archivo){
		gotoxy(20,22); cout << "Error al abrir el Archivo";
		getche();
		return;
	}
	
	string linea;
	
	while(getline(archivo, linea)){
		stringstream ss(linea);
		string dato;
		
		Investigador i;
		
		getline(ss,dato, ',');
		i.id = stoi(dato);
		
		getline(ss,i.nombre, ',');
		
		getline(ss,dato, ',');
		i.idGrupo = stoi(dato);
		
		i.activo = true;
		
		inv.push_back(i);
	}
	archivo.close();
}

void cargarProductos(vector<Grupo> &grupo, vector<Investigador> &inv){
	
	ifstream archivo("productos.csv");
	
	if(!archivo){
		gotoxy(20,22); cout << "Error al abrir el Archivo";
		getche();
		return;
	}
	
	string linea;
	
	while(getline(archivo, linea)){
		stringstream ss(linea);
		string dato;
		
		Producto p;
		int idRef, tipo;
		
		getline(ss,dato, ',');
		p.id = stoi(dato);
		
		getline(ss, p.nombre,',');
		
		getline(ss, dato,',');
		p.anio = stoi(dato);
		
		getline(ss, p.categoria, ',');
		
		getline(ss, p.tipo, ',');
		
		getline(ss, dato, ',');
		idRef = stoi(dato);
		
		getline(ss, dato, ',');
		tipo = stoi(dato);
		
		p.activo = true;
		
		if(tipo == 0){
			int gr = buscarGrupo(grupo, idRef);
			if(gr != -1){
				grupo[gr].productos.push_back(p);
			}
		}
		else
		{
			if(tipo == 1){
				int in = buscarInvestigador(inv, idRef);
					if(in != -1){
						inv[in].productos.push_back(p);
					}
				
			}
		}
		
		
	}
	
	archivo.close();
}

void guardarGrupos(vector<Grupo> &grupo){
	
	
	ofstream archivo("grupos.csv");
	
	for(auto g: grupo){
		if(g.activo){
			archivo << g.id << ","
					<< g.nombre << ","
					<< g.area << "\n";
		}
	}
	archivo.close();
}


void guardarInvestigadores(vector<Investigador> &inv){
	
	ofstream archivo("investigadores.csv");
	
	for(auto i: inv){
		if(i.activo){
			archivo << i.id << ","
					<< i.nombre << ","
					<< i.idGrupo << "\n";
		}
	}
	archivo.close();
}

void guardarProductos(vector<Grupo> &grupo, vector<Investigador> &inv){
	
	ofstream archivo("productos.csv");
	
	for(auto g: grupo){
		if(g.activo){
			for(auto p: g.productos){
				if(p.activo){
					archivo << p.id << ","
                            << p.nombre << ","
                            << p.anio << ","
                            << p.categoria << ","
                            << p.tipo << ","
                            << g.id << ","
                            << 0 << "\n"; 
				}
			}
		}
	}
	
	for(auto i: inv){
		if(i.activo){
			for(auto p: i.productos){
				if(p.activo){
					archivo << p.id << ","
                            << p.nombre << ","
                            << p.anio << ","
                            << p.categoria << ","
                            << p.tipo << ","
                            << i.id << ","
                            << 1 << "\n";
				}
			}
		}
	}
	archivo.close();
}

float calcularIndiceGrupo(Grupo &g){


	int NcTop = 0, NcA = 0, NcB = 0;
    int AP = 0, DPC = 0;
    int FrA = 0, FrB = 0;
    int Cohe = 0, Coop = 0;
	float indice;


	for(auto p : g.productos){
        if(!p.activo) continue;

        if(p.categoria == "NC_TOP") 
			NcTop++;
        else if(p.categoria == "NC_A") 
			NcA++;
        else if(p.categoria == "NC_B") 
			NcB++;
        else if(p.categoria == "AP") 
			AP++;
        else if(p.categoria == "DPC") 
			DPC++;
        else if(p.categoria == "FR_A") 
			FrA++;
        else if(p.categoria == "FR_B") 
			FrB++;
        else if(p.categoria == "COHE") 
			Cohe++;
        else if(p.categoria == "COOP") 
			Coop++;
	}


	indice = (3.7 * NcTop + 2.3 * NcA + 0.4 * NcB + 1.5 * AP + 0.5 * DPC + 1.0 * FrA + 0.2 * FrB + 0.1 * Cohe + 0.3 * Coop);

	return indice;


}


float calcularIndiceInvestigador(Investigador &inv){

int NcTop = 0, NcA = 0, NcB = 0;
    int AP = 0, DPC = 0;
    int FrA = 0, FrB = 0;
    int Cohe = 0, Coop = 0;
	float indice;


	
		for(auto p: inv.productos){
         if(!p.activo) continue;

        if(p.categoria == "NC_TOP") 
			NcTop++;
        else if(p.categoria == "NC_A") 
			NcA++;
        else if(p.categoria == "NC_B") 
			NcB++;
        else if(p.categoria == "AP") 
			AP++;
        else if(p.categoria == "DPC") 
			DPC++;
        else if(p.categoria == "FR_A") 
			FrA++;
        else if(p.categoria == "FR_B") 
			FrB++;
        else if(p.categoria == "COHE") 
			Cohe++;
        else if(p.categoria == "COOP") 
			Coop++;
	}


	indice = (3.7 * NcTop + 2.3 * NcA + 0.4 * NcB + 1.5 * AP + 0.5 * DPC + 1.0 * FrA + 0.2 * FrB + 0.1 * Cohe + 0.3 * Coop);

	return indice;

}

void mostrarIndiceGrupo(vector<Grupo> &grupo){

	TITULO();

	int id;

	gotoxy(23,10); cout << "Ingrese el ID del Grupo: ";
	gotoxy(48,10); cin >> id;

	int gr = buscarGrupo(grupo, id);

	if(gr == -1){
		gotoxy(20,20); cout << "//EL GRUPO NO EXISTE//";
		getche();
		return;
	}

	float indice = calcularIndiceGrupo(grupo[gr]);

	gotoxy(25,12); cout << "Indice de Grupo: " << indice;


	getche();


}

void mostrarIndiceInvestigador(vector<Investigador> &inv){

TITULO();

	int id;

	gotoxy(23,10); cout << "Ingrese el ID del Investigador: ";
	gotoxy(55,10); cin >> id;

	int in = buscarInvestigador(inv, id);

	if(in == -1){
		gotoxy(20,20); cout << "//EL INVESTIGADOR NO EXISTE//";
		getche();
		return;
	}

	float indice = calcularIndiceInvestigador(inv[in]);

	gotoxy(25,12); cout << "Indice del Investigador: " << indice;


	getche();


}



void guardarTodo(vector<Grupo> &grupo, vector<Investigador> &inv){

    guardarGrupos(grupo);
    guardarInvestigadores(inv);
    guardarProductos(grupo, inv);

    
    getche();
}
void cargarTodo(vector<Grupo> &grupo, vector<Investigador> &inv){

    cargarGrupos(grupo);
    cargarInvestigadores(inv);
    cargarProductos(grupo, inv);

    
    
}

void menuGrupos(vector<Grupo> &grupo ){
    int op;
    do{
        TITULO();
        gotoxy(32,9); cout << "=== GRUPOS ===";
        gotoxy(23,10); cout << "1. Agregar Grupo";
        gotoxy(23,11); cout << "2. Mostrar Grupo";
        gotoxy(23,12); cout << "3. Modificar Grupo";
        gotoxy(23,13); cout << "4. Eliminar Grupo";
        gotoxy(23,14); cout << "5. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 1)||(op > 5));
	    
        switch(op){
            case 1: crearGrupo(grupo); break;
            case 2: mostrarGrupo(grupo); break;
            case 3: modificarGrupo(grupo); break;
            case 4: eliminarGrupo(grupo); break;
        }

    }while(op != 5);
}

void menuInvestigadores(vector<Grupo> &grupo, vector<Investigador> &inv){
    int op;
    do{
        TITULO();
        gotoxy(32,9); cout << "=== INVESTIGADORES ===";
        gotoxy(23,10); cout << "1. Crear Investigador";
        gotoxy(23,11); cout << "2. Mostrar Investigadores";
        gotoxy(23,12); cout << "3. Modificar Investigador";
        gotoxy(23,13); cout << "4. Eliminar Investigador";
        gotoxy(23,14); cout << "5. Volver";
        
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 1)||(op > 5));
	    
        switch(op){
            case 1: crearInvestigador(inv, grupo); break;
            case 2: mostrarInvestigador(inv); break;
            case 3: modificarInvestigador(inv); break;
            case 4: eliminarInvestigador(inv); break;
           
        }

    }while(op != 5);
}

void menuProductos(vector<Grupo> &grupo, vector<Investigador> &inv){
    int op;
    do{
        TITULO();
        gotoxy(32,9); cout << "=== PRODUCTOS ===";
        gotoxy(23,10); cout << "1. Agregar Productos a Grupo";
        gotoxy(23,11); cout << "2. Agregar Productos a Investigador";
        gotoxy(23,12); cout << "3. Mostrar Productos de Grupo";
        gotoxy(23,13); cout << "4. Mostrar Productos de Investigador";
        gotoxy(23,14); cout << "5. Modificar Producto";
        gotoxy(23,15); cout << "6. Eliminar Producto";
        gotoxy(23,16); cout << "7. Filtro Por Año";
        gotoxy(23,17); cout << "8. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 1)||(op > 8));
	    
        switch(op){
            case 1: agregarProductoaGrupo(grupo); break;
            case 2: agregarProductoInvestigador(inv); break;
            case 3: mostrarProducto(grupo); break;
            case 4: mostrarProductosInvestigador(inv); break;
            case 5: modificarProducto(grupo); break;
            case 6: eliminarProducto(grupo); break;
            case 7: filtrarPorAnio(grupo); break;
        }

    }while(op != 8);
}
int main(){
	
	char OP;
	


    vector<Grupo> grupo;
    vector<Investigador> inv;
	TITULO();
   do{
   		gotoxy(20,23); cout << "Desea Abrir un Archivo ya existente (S/N):";
   		OP = getch();
		OP = toupper(OP);
   }while((OP != 'S')&&(OP != 'N'));
   
   if(OP == 'S'){ 
   		
   	 cargarTodo(grupo,inv);
   }
   
   

    int op;

    do{
        TITULO();
        gotoxy(30,9); cout << "=== MENU PRINCIPAL ===";
        gotoxy(23,10); cout << "1. Grupos";
        gotoxy(23,11); cout << "2. Investigadores";
        gotoxy(23,12); cout << "3. Productos";
        gotoxy(23,13); cout << "4. Guardar";
        gotoxy(23,14); cout << "5. Resumen de Datos";
		gotoxy(23,15); cout << "6. Indice de Grupo";
		gotoxy(23,16); cout << "7. Indice de Investigador";
        gotoxy(23,17); cout << "8. Salir";

        do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 1)||(op > 8));

        switch(op){
            case 1: menuGrupos(grupo); break;
            case 2: menuInvestigadores(grupo, inv); break;
            case 3: menuProductos(grupo, inv); break;
            case 4: guardarTodo(grupo, inv); break;
            case 5: resumenDatos(grupo,inv); break;
			case 6: mostrarIndiceGrupo(grupo); break;
			case 7: mostrarIndiceInvestigador(inv); break;
        }

    }while(op != 8);


	
	
}

