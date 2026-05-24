#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void gotoxy(int x, int y){         
COORD cp={x,y};                                               
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cp);
}


//  Recibir desde el teclado : La CEDULA, el NOMBRE y la EDAD de cualquier
//  Estudiante de la UPC. Se desea conocer el número de personas y el promedio
//  de edad de acuerdo a los siguientes ciclo de vida :
//- Ciclo de vida de la Juventud; Edad entre los 14 a 26 años.
//- Ciclo de vida de la adultez ; Edad entre los 27 a 59 años.
//- Ciclo de vida de la Tercera edad ”; Edad mayor a 60 años

int main()
{
	long cedula; 
	int edad,NpJ = 0, NpA = 0, NpT = 0; 
	float PJ = 0, PA = 0, PT = 0,CPJ = 0, CPA = 0, CPT = 0;
	char nombre[30], op = 'S';
	
	while(op == 'S')
	{
		system("cls");
		system("color F1");
		gotoxy(30,4); cout<< "UNIVERSIDAD POPULAR DEL CESAR";
		gotoxy(32,6); cout<< "CEDULA:";
		gotoxy(32,7); cout<< "NOMBRE:";
		gotoxy(32,8); cout<< "EDAD  :";
		
		do{
			gotoxy(39,6); cout<< "             ";
			gotoxy(39,6); cin>> cedula;
			gotoxy(30,20); cout<< "Error.. Fuera de rango";
		}while(cedula<0);
		gotoxy(30,20); cout<< "                             ";
		cin.sync();
		gotoxy(39,7); cin.getline(nombre, 30);
		do{
			gotoxy(39,8); cout<< "             ";
			gotoxy(39,8); cin>> edad;
			gotoxy(30,20); cout<< "Error.. Fuera de rango";
		}while((edad<14) || (edad>110));
		gotoxy(30,20); cout<< "                             ";
		
		
		if((edad>= 14) && (edad<=26))
		{
			NpJ++;
			CPJ = edad + CPJ;
			PJ = CPJ/NpJ;
		}
		if((edad>= 27) && (edad<=59))
		{
			NpA++;
			CPA = edad + CPA;
			PA = CPA/NpA;
		}
		if(edad>60)
		{
			NpT++;
			CPT = edad + CPT;
			PT = CPT/NpT;
		}
		
		
			do{
			
			gotoxy(30,20); cout<< "DESEA CONTINUAR S/N:";
			gotoxy(50,20); op = getch();
			op = toupper(op);
			
			}while((op != 'S') && (op != 'N'));
		
	}
	
	system("cls");
	gotoxy(45,4); cout<< "ESTADISTICAS";
	gotoxy(25,6); cout<< "Numero de personas con ciclo de vida entre 14 y 26:"; cout<< NpJ;
	gotoxy(25,7); cout<< "Numero de personas con ciclo de vida entre 27 y 59:"; cout << NpA;
	gotoxy(25,8); cout<< "Numeros de personas con ciclo de vida mayor de 60 :"; cout << NpT;
	gotoxy(25,9); cout<< "Promedio de las personas entre 14 y 26 de edad    :"; cout << PJ;
	gotoxy(25,10); cout<< "Promedio de las personas entre 27 y 59 de edad    :"; cout << PA;
	gotoxy(25,11); cout<< "Promedio de las personas mayores de 60 de edad    :"; cout << PT;
	
	gotoxy(40,17); cout<< "GRACIAS POR RESPONDER :)";
	
}