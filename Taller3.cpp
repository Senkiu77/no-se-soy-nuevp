#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

void TITULO(){
	system("cls");
	system("color F1");
	gotoxy(28,6); cout << "RESTAURANTE DONDE SIEMPRE";
	gotoxy(26,7); cout << "Universidad Popular del Cesar";	
	
}


struct Nodo {

    int dato;
    Nodo* izquierda;
    Nodo* derecha;
    int altura;

};

Nodo* raiz = NULL;

Nodo* crearNodo(int dato) {

    Nodo* nuevo = new Nodo();

    nuevo->dato = dato;
    nuevo->izquierda = NULL;
    nuevo->derecha = NULL;
    nuevo->altura = 1;

    return nuevo;
}

int altura(Nodo* nodo){
    if(nodo == NULL){
        return 0;
    }

    return nodo->altura;

}

int obtenerBalance(Nodo* nodo){

    if(nodo == NULL)
        return 0;

    return altura(nodo->izquierda) - altura(nodo->derecha);

}

Nodo* rotarDerecha(Nodo* y){
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    y->altura = max(altura(y->izquierda), altura(y->derecha)) +1;

    x->altura = max(altura(x->izquierda), altura(x->derecha)) +1;

    return x;

}


Nodo* rotarIzquierda(Nodo* x) {

    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    x->altura = max(altura(x->izquierda),
                    altura(x->derecha)) + 1;

    y->altura = max(altura(y->izquierda),
                    altura(y->derecha)) + 1;

    return y;
}


Nodo* insertar(Nodo* nodo, int dato){

if(nodo == NULL){
        return crearNodo(dato);
}
if(dato < nodo->dato){
    nodo->izquierda = insertar(nodo->izquierda, dato);
}
else if(dato > nodo->dato){
    nodo->derecha = insertar(nodo->derecha, dato);
}
else{
    return nodo;
}

    nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha));

    int balance = obtenerBalance(nodo);

    if(balance > 1 && dato < nodo->izquierda->dato){
        return rotarDerecha(nodo);
    }

    if(balance < -1 && dato > nodo->derecha->dato){
        return rotarIzquierda(nodo);
    }

    if(balance > 1 && dato > nodo->izquierda->dato){
        nodo->izquierda = rotarIzquierda(nodo->izquierda);

        return rotarDerecha(nodo);


    }


    if(balance < -1 && dato < nodo->derecha->dato) {

        nodo->derecha = rotarDerecha(nodo->derecha);

        return rotarIzquierda(nodo);
    }

    return nodo;





}



Nodo* buscar(Nodo* raiz, int dato){

    if(raiz == NULL || raiz->dato == dato){
        return raiz;
    }

    if(dato < raiz->dato)
        return buscar(raiz->izquierda, dato);

    return buscar(raiz->derecha, dato);
}

void inOrden(Nodo* raiz){

    if(raiz != NULL){
        inOrden(raiz->izquierda);

        cout << raiz->dato << " ";

        inOrden(raiz->derecha);
    }
}

void preOrden(Nodo* raiz) {

    if(raiz != NULL) {

        cout << raiz->dato << " ";

        preOrden(raiz->izquierda);

        preOrden(raiz->derecha);
    }
}


void postOrden(Nodo* raiz) {

    if(raiz != NULL) {

        postOrden(raiz->izquierda);

        postOrden(raiz->derecha);

        cout << raiz->dato << " ";
    }
}

void mostrarAVL(Nodo* raiz, int x, int y, int separacion){

    if(raiz == NULL){
            return;
    }

    if(separacion < 2)
        separacion = 2;

    gotoxy(x,y); cout << raiz->dato;

    mostrarAVL(raiz->izquierda, x-separacion, y+3, separacion/2);

    mostrarAVL(raiz->derecha, x+separacion, y+3, separacion/2);

if(raiz->izquierda != NULL){
    gotoxy(x-separacion/2, y+1);
    cout<<"/";
}

if(raiz->derecha != NULL){
    gotoxy(x+separacion/2, y+1);
    cout<<"\\";
}

}

Nodo* nodoMinimo(Nodo* nodo){
    Nodo* actual = nodo;

    while(actual->izquierda != NULL){
        actual = actual->izquierda;
    }

    return actual;
}

Nodo* eliminar(Nodo* raiz, int dato)
{

    if(raiz == NULL)
        return raiz;

    if(dato < raiz->dato)
    {
        raiz->izquierda = eliminar(raiz->izquierda, dato);
    }
    else if(dato > raiz->dato)
    {
        raiz->derecha = eliminar(raiz->derecha, dato);
    }
    else
    {

        if(raiz->izquierda == NULL || raiz->derecha == NULL)
        {
            Nodo* temp;

            if(raiz->izquierda != NULL){
                temp = raiz->izquierda;
            }
            else{
                temp = raiz->derecha;
            }
            if(temp == NULL)
            {
                temp = raiz;
                raiz = NULL;
            }
            else
            {
                *raiz = *temp;
            }

            delete temp;
        }
        else
        {

            Nodo* temp = nodoMinimo(raiz->derecha);

            raiz->dato = temp->dato;

            raiz->derecha = eliminar(raiz->derecha,temp->dato);
        }
    }

    if(raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->izquierda),altura(raiz->derecha));

    int balance = obtenerBalance(raiz);

    if(balance > 1 && obtenerBalance(raiz->izquierda) >= 0)
    {
        return rotarDerecha(raiz);
    }

    if(balance > 1 && obtenerBalance(raiz->izquierda) < 0)
    {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);

        return rotarDerecha(raiz);
    }

    if(balance < -1 && obtenerBalance(raiz->derecha) <= 0)
    {
        return rotarIzquierda(raiz);
    }

    if(balance < -1 &&
       obtenerBalance(raiz->derecha) > 0)
    {
        raiz->derecha = rotarDerecha(raiz->derecha);

        return rotarIzquierda(raiz);
    }

    return raiz;
}

Nodo* modificar(Nodo* raiz, int viejo, int nuevo)
{
    raiz = eliminar(raiz, viejo);
    raiz = insertar(raiz, nuevo);

    return raiz;
}

void guardar(Nodo* raiz, ofstream& archivo)
{
    if(raiz == NULL)
        return;

    archivo << raiz->dato << endl;

    guardar(raiz->izquierda, archivo);
    guardar(raiz->derecha, archivo);
}


void cargar(Nodo*& raiz)
{
    ifstream archivo("avl.txt");

    int dato;

    while(archivo >> dato)
    {
        raiz = insertar(raiz, dato);
    }

    archivo.close();
}

void menuInsertar()
{
    int dato;

    system("cls");

    gotoxy(35,2);
    cout << "INSERTAR DATO";

    gotoxy(25,5);
    cout << "Ingrese el dato: ";
    cin >> dato;

    raiz = insertar(raiz, dato);

    gotoxy(25,8);
    cout << "Dato insertado correctamente.";

    getch();
}

void menuEliminar()
{
    int dato;

    system("cls");

    gotoxy(35,2);
    cout << "ELIMINAR DATO";

    gotoxy(25,5);
    cout << "Ingrese el dato a eliminar: ";
    cin >> dato;

    raiz = eliminar(raiz, dato);

    gotoxy(25,8);
    cout << "Proceso completado.";

    getch();
}

void menuBuscar()
{
    int dato;

    system("cls");

    gotoxy(35,2);
    cout << "BUSCAR DATO";

    gotoxy(25,5);
    cout << "Ingrese el dato a buscar: ";
    cin >> dato;

    if(buscar(raiz, dato))
    {
        gotoxy(25,8);
        cout << "Dato encontrado.";
    }
    else
    {
        gotoxy(25,8);
        cout << "Dato no encontrado.";
    }

    getch();
}

void menuModificar()
{
    int viejo;
    int nuevo;

    system("cls");

    gotoxy(35,2);
    cout << "MODIFICAR DATO";

    gotoxy(25,5);
    cout << "Dato actual: ";
    cin >> viejo;

    if(buscar(raiz, viejo) == NULL)
    {
        gotoxy(25,8);
        cout << "El dato no existe.";

        getch();
        return;
    }

    gotoxy(25,7);
    cout << "Nuevo dato: ";
    cin >> nuevo;

    raiz = eliminar(raiz, viejo);
    raiz = insertar(raiz, nuevo);

    gotoxy(25,10);
    cout << "Dato modificado correctamente.";

    getch();
}

void menuMostrarArbol()
{
    system("cls");

    gotoxy(45,0);
    cout << "ARBOL AVL";

    if(raiz == NULL)
    {
        gotoxy(40,10);
        cout << "ARBOL VACIO";
    }
    else
    {
        mostrarAVL(raiz,40,2,8);
    }

    gotoxy(0,25);
    getch();
}

void menuRecorridos()
{
    system("cls");

    gotoxy(35,2);
    cout << "RECORRIDOS AVL";

    gotoxy(5,6);
    cout << "Preorden: ";
    preOrden(raiz);

    gotoxy(5,8);
    cout << "Inorden: ";
    inOrden(raiz);

    gotoxy(5,10);
    cout << "Postorden: ";
    postOrden(raiz);

    getch();
}

void guardarDatos()
{
    ofstream archivo("avl.txt");

    if(!archivo)
    {
        return;
    }

    guardar(raiz, archivo);

    archivo.close();

    
}

int menuPrincipal(){
	
	TITULO();
	int X;
	
	gotoxy(31,8); cout << "//ARBOL AVL//";
	gotoxy(23,10); cout << "Elija una opcion:";
	gotoxy(23,11); cout << "1. Insertar";
	gotoxy(23,12); cout << "2. Buscar";
	gotoxy(23,13); cout << "3. Modificar";
	gotoxy(23,14); cout << "4. Eliminar";
	gotoxy(23,15); cout << "5. Mostrar Arbol";
	gotoxy(23,16); cout << "6. MostrarRecorrido";
    gotoxy(23,17); cout << "7. Salir Y Guardar";
	
	
	
	do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> X;
		
	}while((X < 0)||(X > 7));
	return X;
}


void menuInicio()
{
    system("color F1");
    int opcion;

    system("cls");

    gotoxy(30,5);
    cout << "ARBOL AVL";

    gotoxy(25,8);
    cout << "1. Cargar datos";

    gotoxy(25,9);
    cout << "2. Iniciar vacio";

    do{
    gotoxy(25,12);
    cout << "Opcion: ";
    cin >> opcion;
    }while(opcion < 1 || opcion > 2);

    switch(opcion)
    {
        case 1:
            cargar(raiz);
            break;

        case 2:
            break;
    }
}


int main(){

    int OPCION = 0;
	string OP = "S";

	menuInicio();


	
        
    do{

        OPCION = menuPrincipal();

	switch(OPCION){
		case 1: menuInsertar();
		break;
		case 2: menuBuscar();
		break;
		case 3: menuModificar();
		break;
		case 4: menuEliminar();
		break;
		case 5: menuMostrarArbol(); 
		break;
		case 6: menuRecorridos();
		break; 
		case 7: guardarDatos();
		break;
		

	}

  
  
  }while(OPCION != 7);



}