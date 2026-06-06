#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}


struct Producto{
	
	string nombre;
	float precio;
	int stock;
	bool activo;
	
	Producto* sig;
	
	
	
};

Producto* listaProductos = NULL;


struct Ingrediente{
	string nombreProducto;
	int cantidad;
	
	Ingrediente* sig;
	
	
};

struct Plato{
	string nombre;
	float precio;
	
	Ingrediente* listaIngredientes;
	
	Plato* sig;
	
};

Plato* listaPlatos = NULL;

struct DetallePedido{
	string nombrePlato;
	int cantidad;
	float precio;
	
	DetallePedido* sig;
	
	
};

struct Pedido{
	int mesa;
	int tipo;
	int codigo;
	string direccion, nombreMesero, nombreCliente;
	
	DetallePedido* listaDetalles;
	
	Pedido* sig;
};

Pedido* listaPedidos = NULL;

struct Reserva{
	
	string nombreCliente;
	int personas;
	string fecha;
	string hora;
	string solicitud;
	
	Reserva* sig;
	
};

Reserva* listaReservas = NULL;

struct Mesero{
	string nombre;
	Mesero* sig;
	
	
};

Mesero* listaMeseros = NULL;

struct Empleado{
	int id;
	string nombre;
	string cargo;
	float salarioBase;
	
	float salud;
	float pension;
	float arl;
	float prestaciones;
	float salarioNeto;
	
	Empleado* sig;
	
	
};

struct CuentaFinanciera{
	
	float ingresos;
	float egresos;
	float saldo;
};

CuentaFinanciera cuenta;

struct Estadisticas{
	
	int pedidosTotales;
	int pedidosLocales;
	int pedidosDomicilios;
	float ingresosTotales;
	int platosVendidos;
	
};

Estadisticas stats;


struct Cliente{
    string nombre;
    int pedidos;
    float totalGastado;
    Cliente* sig;
};

Cliente* listaClientes = NULL;

void TITULO(){
	system("cls");
	system("color F1");
	gotoxy(28,6); cout << "RESTAURANTE DONDE SIEMPRE";
	gotoxy(26,7); cout << "Universidad Popular del Cesar";	
	
}

void registrarIngresos(float monto){
	cuenta.ingresos += monto;
	cuenta.saldo += monto;
	
}

void registrarEgresos(float monto){
	cuenta.egresos += monto;
	cuenta.saldo -= monto;
}

void mostrarFinanzas(){
	gotoxy(23,12); cout << "Ingresos:" << cuenta.ingresos;
	gotoxy(23,13); cout << "Gastos:" << cuenta.egresos;
	gotoxy(23,14); cout << "Saldo restante:" << cuenta.saldo;
	
	
}

Empleado* listaEmpleados = NULL;


Producto* buscarProducto(string nombre){
	
	Producto* aux = listaProductos;
	
	while(aux != NULL){
		if(aux->nombre == nombre){
			
			return aux;
			
		}
		
		aux = aux->sig;
	}
	return NULL;
	
}

Plato* buscarPlato(string nombre){
	
	Plato* aux = listaPlatos;
	
	while(aux != NULL){
		if(aux->nombre == nombre){
			
			return aux;
		}
		aux = aux->sig;
	}
	return NULL;
}

Pedido* buscarPedido(int codigo){
	
	Pedido* aux = listaPedidos;
	
	while(aux != NULL){
		if(aux->codigo == codigo){
			return aux;
		}
		aux = aux->sig;
	}
	return NULL;
}

Reserva* buscarReserva(string nombre){
    
    Reserva* aux = listaReservas;
    
    while(aux != NULL){
        
        if(aux->nombreCliente == nombre){
            return aux;
        }
        
        aux = aux->sig;
    }
    
    return NULL;
}

Empleado* buscarEmpleado(int id){
    
    Empleado* aux = listaEmpleados;
    
    while(aux != NULL){
        
        if(aux->id == id){
            return aux;
        }
        
        aux = aux->sig;
    }
    
    return NULL;
    
}

Cliente* buscarCliente(string nombre){
	
	Cliente* aux = listaClientes;
	
	while(aux != NULL){
		
		if(aux->nombre == nombre){
			return aux;
		}
		aux = aux->sig;
	}
	return NULL;
}



void agregarProducto(){
	TITULO();
	Producto* nuevo = new Producto();
	
	gotoxy(23,10); cout << "Ingrese el nombre del producto:";
	gotoxy(54,10); cin >> nuevo->nombre;
	
	gotoxy(23,11); cout << "Ingrese el precio del producto:";
	gotoxy(54,11); cin >> nuevo->precio;
	
	registrarEgresos(nuevo->precio);
	
	gotoxy(23,12); cout << "Ingrese el stock:";
	gotoxy(40,12); cin >> nuevo->stock;
	
	nuevo->activo = true;
	nuevo->sig = NULL;
	
	
	if(listaProductos == NULL){
		
		listaProductos = nuevo;
		
	}
	else{
		
		Producto* aux = listaProductos;
		
		while(aux->sig != NULL){
			aux = aux->sig;
		}
		aux->sig = nuevo;
	}

	
}

void mostrarProducto(){
	TITULO();
	string nombre;
	
	gotoxy(23,10); cout << "Ingrese el nombre del producto:";
	gotoxy(54,10); cin >> nombre;
	
	Producto* prod = buscarProducto(nombre);
	
	if(prod == NULL){
		gotoxy(20,20); cout << "//Producto no existe//";
		getche();
		return;	
	} 
	
	gotoxy(23,12); cout << "Nombre del producto:" << prod->nombre;
	gotoxy(23,13); cout << "Precio del producto:" << prod->precio;
	gotoxy(23,14); cout << "Stock del producto:" << prod->stock;
	gotoxy(23,15); cout << "Estado del producto:" << prod->activo;
	
	getche();
	
	
}

void eliminarProducto(){
	TITULO();
	string nombre;
	
	gotoxy(23,10); cout << "Ingrese el nombre del producto:";
	gotoxy(54,10); cin >> nombre;
	
	Producto* prod = buscarProducto(nombre);
	
	if(prod == NULL){
		gotoxy(20,20); cout << "//Producto no existe//";
		getche();
		return;	
	} 
	
	Producto* actual = listaProductos;
	Producto* anterior = NULL;
	
	 while(actual != NULL){

        if(actual->nombre == nombre){

            if(anterior == NULL){
                listaProductos = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            delete actual;

            gotoxy(20,20); cout <<"//Producto eliminado//";
            getche();
            return;
        }

        anterior = actual;
        actual = actual->sig;
    }
	
	
	
	
}

void agregarPlato(){
	TITULO();
	Plato* nuevo = new Plato;
	
	gotoxy(23,10); cout << "Ingrese el nombre del plato:";
	cin.ignore();
	gotoxy(51,10); getline(cin,nuevo->nombre);
	gotoxy(23,11); cout << "Ingrese el precio:";
	gotoxy(41,11); cin >> nuevo->precio;
	
	nuevo->listaIngredientes = NULL;
	nuevo->sig = NULL;
	
	if(listaPlatos == NULL){
		listaPlatos = nuevo;
    }
    else{
    	Plato* aux = listaPlatos;
    	while(aux->sig != NULL){
    		aux = aux->sig;
		}
		aux->sig = nuevo;
	}
	
	
	
}

void agregarIngrediente(){
	TITULO();
	string nombre, nombreIngrediente;
	int cantidad;
	
	gotoxy(23,10); cout << "Ingrese le nombre del plato:";
	cin.ignore();
	gotoxy(51,10); getline(cin,nombre);
	
	Plato* plat = buscarPlato(nombre); 
	
	if(plat == NULL){
		gotoxy(20,20); cout << "//El plato no existe//";
		getche();
		return;
	}
	
	Ingrediente* nuevo = new Ingrediente;
	
	gotoxy(23,12); cout << "Ingrese el nombre del ingrediente:";
	gotoxy(57,12); cin >> nombreIngrediente;
	
	Producto* prod = buscarProducto(nombreIngrediente);
	
	if(prod == NULL){
		gotoxy(20,20); cout << "//El Ingrediente no existe//";
		getche(); 
		return;
	}
	
	nuevo->nombreProducto = nombreIngrediente;
	
	gotoxy(23,13); cout << "Ingrese la cantidad (g):";
	gotoxy(47,13); cin >> nuevo->cantidad;
	
	nuevo->sig = NULL;
	
    if(plat->listaIngredientes == NULL){
        plat->listaIngredientes = nuevo;
    }
	else
	{
        Ingrediente* aux = plat->listaIngredientes;
        
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        
        aux->sig = nuevo;
    }
	
	
}


void mostrarPlato(){
	TITULO();
	string nombre;
	int cont = 0;
	
	gotoxy(23,10); cout << "Ingrese el plato:";
	cin.ignore();
	gotoxy(40,10); getline(cin,nombre); 
	
	Plato* plat = buscarPlato(nombre);
	
	if(plat == NULL){
		gotoxy(20,20); cout << "//Plato no existe//";
		getche(); 
		return;
	}
	
	Ingrediente* ing = plat->listaIngredientes;
	
	gotoxy(23,12); cout << "Plato:" << plat->nombre;
	gotoxy(23,13); cout << "Precio:" << plat->precio;	
	gotoxy(23,14); cout << "Ingredientes:";
	while(ing != NULL){
		
		gotoxy(23,15+cont); cout << ing->nombreProducto;
		gotoxy(23,16+cont); cout << "Cant: " << ing->cantidad << "g";
		
		cont++;
		ing = ing->sig;
	}
	
	getche();
	
}

void eliminarPlato(){
	TITULO();
	string nombre;
	
    gotoxy(23,10); cout << "Ingrese el plato:";
	cin.ignore();
	gotoxy(40,10); getline(cin,nombre); 
	
	Plato* plat = buscarPlato(nombre);
	
	if(plat == NULL){
		gotoxy(20,20); cout << "//Plato no existe//";
		getche(); 
		return;
	}
	
	
	Plato* actual = listaPlatos;
	Plato* anterior = NULL;
	
	 while(actual != NULL){

        if(actual->nombre == nombre){

            if(anterior == NULL){
                listaPlatos = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            delete actual;

            gotoxy(20,20); cout <<"//Plato eliminado//";
            getche();
            return;
        }

        anterior = actual;
        actual = actual->sig;
    }
	
	
	
	
}

void registrarCliente(string nombre, float total){
    
    Cliente* aux = listaClientes;
    
    while(aux != NULL){
        
        if(aux->nombre == nombre){
            aux->pedidos++;
            aux->totalGastado += total;
            return;
        }
        
        aux = aux->sig;
    }
    
    Cliente* nuevo = new Cliente();
    
    nuevo->nombre = nombre;
    nuevo->pedidos = 1;
    nuevo->totalGastado = total;
    nuevo->sig = listaClientes;
    
    listaClientes = nuevo;
}


	
void crearPedido(){
	TITULO();
	
	int codigo;
	Pedido* nuevo = new Pedido;
	
	gotoxy(23,10); cout << "Ingrese el codigo del pedido:";
	gotoxy(52,10); cin >> nuevo->codigo;
	
	gotoxy(23,11); cout << "Nombre cliente:";
    cin.ignore();
    gotoxy(38,11); getline(cin,nuevo->nombreCliente);
	
	gotoxy(23,12); cout << "Que tipo de pedido desea?:";
	gotoxy(23,13); cout << "1.Local";
	gotoxy(23,14); cout << "2.Domicilio";
	
	
	gotoxy(49,12); cin >> nuevo->tipo;
	
	stats.pedidosTotales++;
	if(nuevo->tipo == 2){
		gotoxy(23,16); cout << "Ingrese la direccion:";
		cin.ignore();
		gotoxy(44,16); getline(cin,nuevo->direccion);
		nuevo->mesa = 0;
		stats.pedidosDomicilios++;
		
	}
	else if(nuevo->tipo == 1){
		gotoxy(23,16); cout << "Ingrese el numero de mesa:";
		gotoxy(49,16); cin >> nuevo->mesa;
		stats.pedidosLocales++;
		
	}
	
	gotoxy(23,17); cout << "Ingrese el Nombre del mesero:";
	cin.ignore();
	gotoxy(52,17); getline(cin,nuevo->nombreMesero);
	
	nuevo->listaDetalles = NULL;
	nuevo->sig = NULL;
	
   if(listaPedidos == NULL){
        listaPedidos = nuevo;
    }
	else
	{
        Pedido* aux = listaPedidos;
        
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        
        aux->sig = nuevo;
    }
    
    
	gotoxy(20,20); cout << "//Pedido Creado//";
	getche();

	
}

void agregarPlatoPedido(){
	TITULO();
	int codigo;
	string nombre;
	int cantidad;
	
	gotoxy(23,10); cout << "Codigo pedido:";
	gotoxy(37,10); cin >> codigo;
	
	Pedido* ped = buscarPedido(codigo);
	
	if(ped == NULL){
		gotoxy(20,20); cout << "//Pedido no existe//";
		getche();
		return;
	}
	
	gotoxy(23,12); cout << "Nombre del Plato:";
	cin.ignore();
	gotoxy(40,12); getline(cin,nombre);
	
	Plato* plat = buscarPlato(nombre);
	
	if(plat == NULL){
		gotoxy(20,20); cout << "//Plato no esta en el Menu//";
		getche(); 
		return;
		
	}
	
	gotoxy(23,13); cout << "Cantidad:";
	gotoxy(32,13); cin >> cantidad;
	
	DetallePedido* nuevo = new DetallePedido;
	
	nuevo->nombrePlato = nombre;
	nuevo->cantidad = cantidad;
	nuevo->precio = plat->precio;
	nuevo->sig = NULL;
	
	if(ped->listaDetalles == NULL){
		ped->listaDetalles = nuevo;
	}
	else
	{
		DetallePedido* aux = ped->listaDetalles;
		
		while(aux->sig != NULL){
			aux = aux->sig;
		}
		
		aux->sig = nuevo;
	}
	
	stats.platosVendidos += cantidad;
	
	float total = plat->precio*cantidad;
    
    registrarIngresos(total);
    stats.ingresosTotales += total;
    registrarCliente(ped->nombreCliente, total);
	
	
}

void mostrarPedido(){
	TITULO();
	int codigo; 
	
	gotoxy(23,10); cout << "Ingrese el codigo:";
	gotoxy(41,10); cin >> codigo;
	
	Pedido* ped = buscarPedido(codigo);
	
	if(ped == NULL){
		gotoxy(20,20); cout << "//Pedido no existe//";
		getche();
		return;
	}
	
	if(ped->tipo == 1){
		gotoxy(23,12); cout << "PEDIDO LOCAL";
		gotoxy(23,13); cout << "Mesero:" << ped->nombreMesero;
		gotoxy(23,14); cout << "Mesa: " << ped->mesa;
		
	}
	else{
		gotoxy(23,12); cout << "PEDIDO DOMICILIO";
		gotoxy(23,14); cout << "Domicilio:" << ped->direccion;
	}
	
	
	DetallePedido* det = ped->listaDetalles;
	
	if(det == NULL){
    gotoxy(23,16); cout << "Pedido sin platos";
    getche();
    return;
}

int y = 16;
	while(det != NULL){
	gotoxy(23,y++); cout << "Plato:" << det->nombrePlato;
	gotoxy(23,y++); cout << "Cantidad:" << det->cantidad;
	gotoxy(23,y++); cout << "Total a Pagar:" << det->precio*det->cantidad;
	y++;
	
	det = det->sig;
	}
	
	getche();
	
	
}

void eliminarPedido(){
	TITULO();
	int codigo;
	
    gotoxy(23,10); cout << "Ingrese el codigo";
	gotoxy(40,10); cin >> codigo; 
	
	Pedido* ped = buscarPedido(codigo);
	
	if(ped == NULL){
		gotoxy(20,20); cout << "//Pedido no existe//";
		getche(); 
		return;
	}
	
	
	Pedido* actual = listaPedidos;
	Pedido* anterior = NULL;
	
	 while(actual != NULL){

        if(actual->codigo == codigo){

            if(anterior == NULL){
                listaPedidos = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            delete actual;

            gotoxy(20,20); cout <<"//Pedido eliminado//";
            getche();
            return;
        }

        anterior = actual;
        actual = actual->sig;
    }
}

void agregarReserva(){
	TITULO();
	Reserva* nuevo = new Reserva;
	
	gotoxy(23,10); cout << "Nombre del cliente:";
	cin.ignore();
	gotoxy(42,10); getline(cin,nuevo->nombreCliente);
	
	gotoxy(23,11); cout << "Nro de Personas:";
	gotoxy(39,11); cin >> nuevo->personas;
	
	gotoxy(23,12); cout << "Fecha:";
	cin.ignore();
	gotoxy(29,12); getline(cin,nuevo->fecha);
	
	gotoxy(23,13); cout << "Hora:";
	gotoxy(28,13); getline(cin,nuevo->hora);
	
	gotoxy(23,14); cout << "Solicitud Especial:";
	gotoxy(42,14); getline(cin,nuevo->solicitud);
	
	if(listaReservas == NULL){
        listaReservas = nuevo;
    }
	else
	{
        Reserva* aux = listaReservas;
        
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        
        aux->sig = nuevo;
    }
	
	
	
}

void mostrarReservas(){
	TITULO();
	string nombre;
	
	gotoxy(23,10); cout << "Nombre del Cliente:";
	cin.ignore();
	gotoxy(42,10); getline(cin,nombre);
	
	Reserva* re = buscarReserva(nombre);
	
	if(re == NULL){
		gotoxy(20,20); cout << "//Reserva no existe//";
		getche();
		return;
	}
	
	gotoxy(23,12); cout << "Nombre del cliente: " << re->nombreCliente;
	gotoxy(23,13); cout << "Cantidad de personas: " << re->personas;
	gotoxy(23,14); cout << "Fecha: " << re->fecha;
	gotoxy(23,15); cout << "Hora: " << re->hora;
	gotoxy(23,16); cout << "Solicitud: " << re->solicitud;
	
	getche();
	
	
	
	
}

void eliminarReserva(){
	TITULO();
	string nombre;
	
	gotoxy(23,10); cout << "Nombre del Cliente:";
	cin.ignore();
	gotoxy(42,10); getline(cin,nombre);
	
	Reserva* re = buscarReserva(nombre);
	
	if(re == NULL){
		gotoxy(20,20); cout << "//Reserva no existe//";
		getche();
		return;
	}
	
	Reserva* actual = listaReservas;
	Reserva* anterior = NULL;
	
	while(actual != NULL){

        if(actual->nombreCliente == nombre){

            if(anterior == NULL){
                listaReservas = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            delete actual;

            gotoxy(20,20); cout <<"//Reserva eliminada//";
            getche();
            return;
        }

        anterior = actual;
        actual = actual->sig;
    }
	
}

void agregarEmpleado(){
	TITULO();
	Empleado* nuevo = new Empleado;
	
	gotoxy(23,10); cout << "Ingrese el Id del Empleado:";
	gotoxy(50,10); cin >> nuevo->id;
	
	gotoxy(23,11); cout << "Ingrese el Nombre del Empleado:";
	gotoxy(54,11); cin >> nuevo->nombre;
	
	gotoxy(23,12); cout << "Ingrese el Cargo:";
	gotoxy(23,13); cout << "1.Cocinero";
	gotoxy(23,14); cout << "2.Cajero";
	gotoxy(23,15); cout << "3.Administrador";
	gotoxy(40,12); cin >> nuevo->cargo;
	
	gotoxy(23,16); cout << "Salario del Empleado:";
	gotoxy(44,16); cin >> nuevo->salarioBase;
	
	nuevo->sig = NULL;
	
	
	if(listaEmpleados == NULL){
        listaEmpleados = nuevo;
    }
	else
	{
        Empleado* aux = listaEmpleados;
        
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        
        aux->sig = nuevo;
    }
	
	
	
}


void mostrarEmpleado(){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el Id del Empleado:";
	gotoxy(50,10); cin >> id;
	
	Empleado* emp = buscarEmpleado(id);
	
	if(emp == NULL){
		gotoxy(20,20); cout << "//Empleado no existe//";
		getche();
		return;
		
	}
	
	gotoxy(23,12); cout << "ID:" << emp->id;
	gotoxy(23,13); cout << "Nombre:" << emp->nombre;
	gotoxy(23,14); cout << "Cargo:" << emp->cargo;
	gotoxy(23,15); cout << "Salario:" << emp->salarioBase;
	
	getche();
	
	
}

void eliminarEmpleado(){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el Id del Empleado:";
	gotoxy(50,10); cin >> id;
	
	Empleado* emp = buscarEmpleado(id);
	
	if(emp == NULL){
		gotoxy(20,20); cout << "//Empleado no existe//";
		getche();
		return;
		
	}
	
	Empleado* actual = listaEmpleados;
	Empleado* anterior = NULL;
	
	while(actual != NULL){

        if(actual->id == id){

            if(anterior == NULL){
                listaEmpleados = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            delete actual;

            gotoxy(20,20); cout <<"//Empleado eliminado//";
            getche();
            return;
        }

        anterior = actual;
        actual = actual->sig;
    }
	
}

void calcularNomina(Empleado* emp){
	
	emp->salud = emp->salarioBase*0.04;
	emp->pension = emp->salarioBase*0.04;
	emp->arl = emp->salarioBase*0.00522;
	emp->prestaciones = emp->salarioBase*0.0833;
	
	emp->salarioNeto = emp->salarioBase-(emp->salud+emp->pension+emp->prestaciones);
	
}

void calcularNominaEmpleado(){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el Id del Empleado:";
	gotoxy(50,10); cin >> id;
	
	Empleado* emp = buscarEmpleado(id);
	
	if(emp == NULL){
		gotoxy(20,20); cout << "//Empleado no existe//";
		getche();
		return;
		
	}
	
	calcularNomina(emp);
	
}


void mostrarNomina(){
	TITULO();
	int id;
	
	gotoxy(23,10); cout << "Ingrese el Id del Empleado:";
	gotoxy(50,10); cin >> id;
	
	Empleado* emp = buscarEmpleado(id);
	
	if(emp == NULL){
		gotoxy(20,20); cout << "//Empleado no existe//";
		getche();
		return;
		
	}
	
	gotoxy(23,12); cout << "Nombre del Empleado:" << emp->nombre;
	gotoxy(23,13); cout << "Cargo:" << emp->cargo;
	
	gotoxy(23,14); cout << "Salario Base:" << emp->salarioBase;
	gotoxy(23,15); cout << "Salud:" << emp->salud;
	gotoxy(23,16); cout << "Pension:" << emp->pension;
	gotoxy(23,17); cout << "ARL:" << emp->arl;
	gotoxy(23,18); cout << "Prestaciones:" << emp->prestaciones;
	gotoxy(23,19); cout << "Salario Neto:" << emp->salarioNeto;
	
	getche();
	
	
}



int contarPlatos(){
    TITULO();
    int cont = 0;
    Plato* aux = listaPlatos;
    
    while(aux != NULL){
        cont++;
        aux = aux->sig;
    }
    
    return cont;
}

Plato* obtenerPlatoRandom(){
    
    int total = contarPlatos();
    
    if(total == 0) return NULL;
    
    int pos = rand() % total;
    
    Plato* aux = listaPlatos;
    
    for(int i=0; i<pos; i++){
        aux = aux->sig;
    }
    
    return aux;
}

void simularRestaurante(int cantidadPedidos){
	
	system("cls");
	
    if(listaPlatos == NULL){
        gotoxy(20,20); cout << "No hay platos para simular";
        getche();
        return;
    }
    
    
    for(int i=0; i<cantidadPedidos; i++){
        
        Pedido* nuevo = new Pedido();
        
        nuevo->codigo = rand()%1000 + 1;
        nuevo->tipo = rand()%2 + 1;
        
        if(nuevo->tipo == 1){
            nuevo->mesa = rand()%20 + 1;
            nuevo->direccion = "";
        }
        else{
            nuevo->mesa = 0;
            nuevo->direccion = "Domicilio simulado";
        }
        
        nuevo->nombreMesero = "Mesero sim";
        nuevo->listaDetalles = NULL;
        nuevo->sig = NULL;
        
        int cantPlatos = rand()%3 + 1;
        
        for(int j=0; j<cantPlatos; j++){
            
            Plato* plat = obtenerPlatoRandom();
            
            if(plat == NULL) return;
            
            DetallePedido* det = new DetallePedido();
            
            det->nombrePlato = plat->nombre;
            det->cantidad = rand()%3 + 1;
            det->precio = plat->precio;
            det->sig = NULL;
            
            if(nuevo->listaDetalles == NULL){
                nuevo->listaDetalles = det;
            }
            else{
                DetallePedido* aux = nuevo->listaDetalles;
                
                while(aux->sig != NULL){
                    aux = aux->sig;
                }
                
                aux->sig = det;
            }
            
            float total = det->precio * det->cantidad;

            stats.platosVendidos += det->cantidad;
			stats.ingresosTotales += total;

			registrarIngresos(total);
        }
        
        if(listaPedidos == NULL){
            listaPedidos = nuevo;
        }
        else{
            Pedido* aux = listaPedidos;
            
            while(aux->sig != NULL){
                aux = aux->sig;
            }
            
            aux->sig = nuevo;
        }
        
        stats.pedidosTotales++;

		if(nuevo->tipo == 1){
   		 stats.pedidosLocales++;
   		}
		else
		{
    	stats.pedidosDomicilios++;
    	}
    }
}

void mostrarDashboard(){
	TITULO();
	gotoxy(33,5); cout <<  "----- DASHBOARD -----";
	gotoxy(23,10); cout << "Pedidos Totales:" << stats.pedidosTotales;
	gotoxy(23,11); cout << "Pedidos Locales:" << stats.pedidosLocales;
	gotoxy(23,12); cout << "Pedidos Domicilios:" << stats.pedidosDomicilios;
	gotoxy(23,13); cout << "Platos Vendidos:" << stats.platosVendidos;
	gotoxy(23,14); cout << "Ingresos Totales:" << stats.ingresosTotales;
	
	getche();
	
	
}

void reiniciarEstadisticas(){
    
    stats.pedidosTotales = 0;
    stats.pedidosLocales = 0;
    stats.pedidosDomicilios = 0;
    stats.ingresosTotales = 0;
    stats.platosVendidos = 0;
    
}

void generarPromociones(){
	TITULO();
	string nombre;
	
	gotoxy(23,10); cout << "Nombre Cliente:";
	cin.ignore();
	gotoxy(38,10); getline(cin, nombre);
	
	Cliente* cl = buscarCliente(nombre);
	
	if(cl == NULL){
		gotoxy(20,20); cout << "//Cliente no registrado//";
		getche();
		return;
		
	}
	else
	{
		if(cl->pedidos >= 3){
			gotoxy(23,12); cout << "//Cliente Con Promocion//";
			gotoxy(23,13); cout << "Nombre Cliente:" << cl->nombre;
			gotoxy(23,14); cout << "Pedidos:" << cl->pedidos;
			gotoxy(23,15); cout << "Total Gastado:" << cl->totalGastado;
			gotoxy(23,16); cout << "Promo: 10% de Descuento";
			
		}
		else
		{
			gotoxy(23,12); cout << "//Cliente Sin Promocion//";
			gotoxy(23,13); cout << "Nombre Cliente:" << cl->nombre;
			gotoxy(23,14); cout << "Pedidos:" << cl->pedidos;
			gotoxy(23,15); cout << "Total Gastado:" << cl->totalGastado;
			gotoxy(23,16); cout << "Promo: N/A";
		}
	}
	
	getche();
	
	
}


void guardarPedidos(){

    ofstream file("pedidos.dat");

    Pedido* aux = listaPedidos;

    while(aux != NULL){

        file << aux->codigo << "|"
             << aux->tipo << "|"
             << aux->mesa << "|"
             << aux->direccion << "|"
             << aux->nombreMesero << endl;

        aux = aux->sig;
    }

    file.close();
}


void guardarDetalles(){

    ofstream file("detalles.dat");

    Pedido* ped = listaPedidos;

    while(ped != NULL){

        DetallePedido* det = ped->listaDetalles;

        while(det != NULL){

            file << ped->codigo << "|"
                 << det->nombrePlato << "|"
                 << det->cantidad << "|"
                 << det->precio << endl;

            det = det->sig;
        }

        ped = ped->sig;
    }

    file.close();
}

void cargarPedidos(){

    ifstream file("pedidos.dat");

    if(!file) return;

    string linea;

    while(getline(file,linea)){

        Pedido* nuevo = new Pedido();

        stringstream ss(linea);
        string temp;

        getline(ss,temp,'|');
        nuevo->codigo = stoi(temp);

        getline(ss,temp,'|');
        nuevo->tipo = stoi(temp);

        getline(ss,temp,'|');
        nuevo->mesa = stoi(temp);

        getline(ss,nuevo->direccion,'|');
        getline(ss,nuevo->nombreMesero);

        nuevo->listaDetalles = NULL;
        nuevo->sig = NULL;

        if(listaPedidos == NULL)
            listaPedidos = nuevo;
        else{
            Pedido* aux = listaPedidos;
            while(aux->sig != NULL)
                aux = aux->sig;
            aux->sig = nuevo;
        }
    }

    file.close();
}

void cargarDetalles(){

    ifstream file("detalles.dat");

    if(!file) return;

    string linea;

    while(getline(file,linea)){

        stringstream ss(linea);

        string temp;
        int codPedido;

        getline(ss,temp,'|');
        codPedido = stoi(temp);

        Pedido* ped = buscarPedido(codPedido);

        if(ped == NULL) continue;

        DetallePedido* det = new DetallePedido();

        getline(ss,det->nombrePlato,'|');

        getline(ss,temp,'|');
        det->cantidad = stoi(temp);

        getline(ss,temp);
        det->precio = stof(temp);

        det->sig = NULL;

        if(ped->listaDetalles == NULL)
            ped->listaDetalles = det;
        else{
            DetallePedido* aux = ped->listaDetalles;
            while(aux->sig != NULL)
                aux = aux->sig;
            aux->sig = det;
        }
    }

    file.close();
}


void guardarStats(){
    
    ofstream file("stats.txt");
    
    file << stats.pedidosTotales << endl;
    file << stats.pedidosLocales << endl;
    file << stats.pedidosDomicilios << endl;
    file << stats.platosVendidos << endl;
    file << stats.ingresosTotales << endl;
    
    file.close();
}

void cargarStats(){
    
    ifstream file("stats.txt");
    
    if(!file) return;
    
    file >> stats.pedidosTotales;
    file >> stats.pedidosLocales;
    file >> stats.pedidosDomicilios;
    file >> stats.platosVendidos;
    file >> stats.ingresosTotales;
    
    file.close();
}


void menuProductos(){
    int op;
    do{
        TITULO();
        gotoxy(32,8); cout << "=== Productos ===";
        gotoxy(23,10); cout << "1. Agregar Productos";
        gotoxy(23,12); cout << "2. Mostrar Producto";
        gotoxy(23,14); cout << "3. Eliminar Producto";
        gotoxy(23,16); cout << "4. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 0)||(op > 4));
	    
        switch(op){
            case 1: agregarProducto(); break;
            case 2: mostrarProducto(); break;
            case 3: eliminarProducto(); break;
        }

    }while(op != 4);
}

void menuPlatos(){
    int op;
    do{
        TITULO();
        gotoxy(32,8); cout << "=== Platos ===";
        gotoxy(23,10); cout << "1. Agregar Platos";
        gotoxy(23,12); cout << "2. Agregar Ingredientes";
        gotoxy(23,14); cout << "3. Mostrar Platos";
        gotoxy(23,16); cout << "4. Eliminar Platos";
        gotoxy(23,18); cout << "5. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 0)||(op > 5));
	    
        switch(op){
            case 1: agregarPlato(); break;
			case 2: agregarIngrediente(); break;
			case 3: mostrarPlato(); break;
            case 4: eliminarPlato(); break; 
        }

    }while(op != 5);
}

void menuPedidos(){
    int op;
    do{
        TITULO();
        gotoxy(32,8); cout << "=== Pedidos ===";
        gotoxy(23,10); cout << "1. Crear Pedido";
        gotoxy(23,12); cout << "2. Agregar Plato";
        gotoxy(23,14); cout << "3. Mostrar Pedido";
        gotoxy(23,16); cout << "4. Eliminar Pedido";
        gotoxy(23,17); cout << "5. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 0)||(op > 5));
	    
        switch(op){
            case 1: crearPedido(); break;
            case 2: agregarPlatoPedido(); break;
            case 3: mostrarPedido(); break;
            case 4: eliminarPedido(); break;
        }

    }while(op != 5);
}


void menuReservas(){
    int op;
    do{
        TITULO();
        gotoxy(32,8); cout << "=== Reservas ===";
        gotoxy(23,10); cout << "1. Agregar Reserva";
        gotoxy(23,12); cout << "2. Mostrar Reserva";
        gotoxy(23,14); cout << "3. Eliminar Reserva";
        gotoxy(23,16); cout << "4. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 0)||(op > 4));
	    
        switch(op){
            case 1: agregarReserva(); break;
            case 2: mostrarReservas(); break;
            case 3: eliminarReserva(); break;
        }

    }while(op != 4);
}

void menuEmpleado(){
    int op;
    do{
        TITULO();
        gotoxy(32,8); cout << "=== Empleados ===";
        gotoxy(23,10); cout << "1. Agregar Empleado";
        gotoxy(23,12); cout << "2. Mostrar Empleado";
        gotoxy(23,14); cout << "3. Eliminar Empleado";
        gotoxy(23,16); cout << "4. Calcular Nomina";
        gotoxy(23,18); cout << "5. Mostrar Nomina";
        gotoxy(23,20); cout << "6. Volver";
       do{
		gotoxy(38,22); cout << "             ";
		gotoxy(20,22); cout << "Ingrese la opcion:";
		gotoxy(38,22); cin >> op;
		
	    }while((op < 0)||(op > 6));
	    
        switch(op){
            case 1: agregarEmpleado(); break;
            case 2: mostrarEmpleado(); break;
            case 3: eliminarEmpleado(); break;
            case 4: calcularNominaEmpleado(); break;
            case 5: mostrarNomina(); break;
        }

    }while(op != 6);
}


void menuDashBoard(){
    int op;
    do{
    	TITULO();
        gotoxy(23,10); cout << "1. DashBoard";
        gotoxy(23,12); cout << "2. Reiniciar DashBoard";
        gotoxy(23,14); cout << "3. Volver";
        
       do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> op;
		
	    }while((op < 0)||(op > 3));
	    
        switch(op){
            case 1: mostrarDashboard(); break;
            case 2: reiniciarEstadisticas(); break;
        }

    }while(op != 3);
}








int menuPrincipal(){
	
	TITULO();
	int X;
	
	gotoxy(31,8); cout << "//MENU PRINCIPAL//";
	gotoxy(23,10); cout << "Elija una opcion:";
	gotoxy(23,11); cout << "1. Productos";
	gotoxy(23,12); cout << "2. Platos";
	gotoxy(23,13); cout << "3. Pedidos";
	gotoxy(23,14); cout << "4. Reservas";
	gotoxy(23,15); cout << "5. Empleados";
	gotoxy(23,16); cout << "6. DashBoard";
	gotoxy(23,17); cout << "7. Simular Restaurante";
	gotoxy(23,18); cout << "8. Generar Promociones";
	gotoxy(23,19); cout << "9. Salir";
	
	
	
	do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> X;
		
	}while((X < 0)||(X > 9));
	return X;
}






int main(){
	
	
	cargarPedidos();
	cargarDetalles();
	cargarStats();
	
   srand(time(NULL));
   
   int OPCION = 0;
	
	do{
	
	OPCION = menuPrincipal();
	
	switch(OPCION){
		case 1: menuProductos();
		break;
		case 2: menuPlatos();
		break;
		case 3: menuPedidos();
		break;
		case 4: menuReservas();
		break;
		case 5: menuEmpleado(); 
		break;
		case 6: menuDashBoard();
		break; 
		case 7: simularRestaurante(20);
		break;
		case 8: generarPromociones();
		break;
		case 9: guardarPedidos();
				guardarDetalles();
				guardarStats();
				break;

	}
  
  
  }while(OPCION != 9);
	
}


