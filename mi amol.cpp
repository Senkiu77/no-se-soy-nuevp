#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y){
	COORD cp;
	cp.X = x;
	cp.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}

main(){
	long n, i, contador = 0;
	char op = 'S';
	system("color 75"); 
	while (op == 'S'){
		
		
		do{
			gotoxy(1,2); cout << "*------------------------------------------------------------------------------*";
			gotoxy(1,3); cout << "|"; gotoxy(80,3); cout << "|"; gotoxy(1,4); cout << "|"; gotoxy(80,4); cout << "|";
			gotoxy(22,4); cout << "ES UN NUMERO PRIMO? DESCUBRALO AQUI";
			gotoxy(1,5); cout << "|"; gotoxy(80,5); cout << "|"; gotoxy(1,7); cout << "|"; gotoxy(80,7); cout << "|";
			gotoxy(1,6); cout << "*--------------------------------------*---------------------------------------*";
			gotoxy(1,9); cout << "|"; gotoxy(80,9); cout << "|"; gotoxy(40,8); cout << "|"; 
			gotoxy(40,7); cout << "|"; gotoxy(40,9); cout << "|"; 
			gotoxy(1,8); cout << "|"; gotoxy(80,8); cout << "|";
			gotoxy(8,8); cout << "NUMERO A INVESTIGAR: ";
			gotoxy(1,10); cout << "*--------------------------------------*---------------------------------------*"; 
			gotoxy(29,8); cin >> n; 
			if ( n<=0 ){
				system("cls");
			}                                                                              
		} while (n <= 0);
		
		gotoxy(40,12); cout << "|"; gotoxy(80,12); cout << "|"; gotoxy(40,11); cout << "|"; 
		gotoxy(40,13); cout << "|"; gotoxy(80,13); cout << "|"; gotoxy(80,11); cout << "|"; 
		gotoxy(40,14); cout << "*---------------------------------------*";
		
	 for (i=1; i<=n; i++){
			if (n%i == 0){
				contador += 1;
			}
		}
		if (contador == 2){
			gotoxy(54,8); printf("%i ES PRIMO", n);
		}
		else{
			gotoxy(52,8); printf("%i NO ES PRIMO", n);
		}
		do {
			gotoxy(44,12); cout << "SIGUIENTE NUMERO? S(Si)/ N(No)";
			op = getch();
			op = toupper(op);
		} while ((op != 'S') && (op != 'N'));
		system("cls");
		contador = 0;
		}
}