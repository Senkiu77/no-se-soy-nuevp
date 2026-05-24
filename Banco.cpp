#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>


using namespace std;


struct Estudiante{
    string nombre;
    float nota;
    Estudiante* sig;
};



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
	gotoxy(30,6); cout << "VORTAL UNIVERSITARIO";
	gotoxy(26,7); cout << "Universidad Popular del Cesar";	
	
}

int MENU(){
	
	TITULO();
	int X;
	gotoxy(38,8); cout << "MENU";
	gotoxy(23,10); cout << "Elija una opcion:";
	gotoxy(23,11); cout << "1.";
	gotoxy(23,12); cout << "2.";
	gotoxy(23,13); cout << "3.";
	gotoxy(23,14); cout << "4.";
	
	do{
		gotoxy(38,20); cout << "             ";
		gotoxy(20,20); cout << "Ingrese la opcion:";
		gotoxy(38,20); cin >> X;
		
	}while((X < 0)||(X > 4));
	return X;
}

void CONSULTAR(){
	char OP = 'S';
	TITULO();
	while(OP == 'S'){
	   gotoxy(20,10); cout << "SU SALDO RESTANTE:" << Cuenta[usuario].Total_Saldo;
	
	   do{
			gotoxy(20,20), cout << "DESEA CONTINUAR S/N:"; 
			gotoxy(40,20); cout << "         ";
			gotoxy(40,20); OP = getche();
			gotoxy(40,20); OP = toupper(OP);
	    }while((OP != 'S') && (OP != 'N'));
	        
}
	
}

int INGRESAR(){
	
	TITULO();
	int Saldo = 0; 
	char OP = 'S';
	while(OP == 'S'){

	gotoxy(26,10); cout << "Cuanto Dinero Desea Ingresar?:";
	gotoxy(56,10); cout << "       ";
	gotoxy(56,10); cin >> Saldo;
	Cuenta[usuario].Total_Saldo = Cuenta[usuario].Total_Saldo + Saldo;
	
	do{
		
		gotoxy(20,20); cout << "DESEA INGRESAR MAS DINERO S/N?:";
		gotoxy(51,20);
		OP = getche();
		OP = toupper(OP);	
	  }while((OP != 'S') && (OP != 'N'));
	
	
}

}

int RETIRAR(){
	
	TITULO();
	int Retirar = 0;
	char OP = 'S';
	
	while(OP == 'S'){
		
		gotoxy(26,10); cout << "Cuanto Dinero Desea Retirar?:";
		do{
			gotoxy(56,10); cout << "           ";
		    gotoxy(55,10); cin >> Retirar;
			}while((Retirar < 0) || (Retirar > Cuenta[usuario].Total_Saldo));
	  
		Cuenta[usuario].Total_Saldo = Cuenta[usuario].Total_Saldo - Retirar;
		
		do{
			gotoxy(40,20); cout << "          ";
			gotoxy(20,20); cout << "DESEA CONTINUAR?:";
			OP = getche();
			OP = toupper(OP);
			
		}while((OP != 'S') && (OP != 'N'));
	}
	
	
	
	
}

int main() {
  
  int OPCION = 0;
  char OP = 'S';
  
  gotoxy(20,20); cout << "Elija una cuenta (0/10):";
  gotoxy(44,20); cin >> usuario;
    
  while(OP == 'S'){
  	OPCION = MENU();
  	
  switch(OPCION){
  	case 1: CONSULTAR();
  	break;
  	case 2: INGRESAR();
  	break;
  	case 3: RETIRAR();
  	break;
  	case 4: OP = 'N';
  	break;
  	
  }
}
  
  
  
  }