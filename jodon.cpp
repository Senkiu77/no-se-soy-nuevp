#include <windows.h>                     
#include <iostream>                      
#include <conio.h>                      

using namespace std;    

int gotoxy(USHORT x,USHORT y){                                  
COORD cp={x,y};                                                 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cp);   
}

struct CAMPOS {
	
	int CEDULA ;
        char NOMBRE[20];
		char SEXO;
} 	EMPLEADO[50];
int NRO = 0;

long double VALNUMERO(int X, int Y, int T )
  {
  long NUMERO ;
  char CADENA[30] ;
  int  SW, K, LONGITUD;
  do { 
     SW = 0 ;
     gotoxy(X,Y) ; cout << "                                                              " ;
     gotoxy(X,Y); NUMERO = atof(gets(CADENA));
     LONGITUD = strlen(CADENA) ;
     if ( LONGITUD == 0 )
        {
        gotoxy(20,22); cout << "ERROR.. no ha escrito nada, max = " << T;
        getch();
        SW = 1;
        }
      else
        if ( LONGITUD > T)
	       {
	       gotoxy(20,22); cout << "ERROR.. demasiados digitos, Max = " << T;
	       getch();
	       SW = 1;
	       }
	     else
	       for ( K = 0 ; K < LONGITUD ; K++ )
	           if ( !isdigit(CADENA[K]) )
	              {
		  	      gotoxy(20,22); cout << "ERROR.. No Digite Letras";
		          getch();
		          SW = 1;
		          }
   gotoxy(20,22) ;cout << "                                                                ";
   }  while ( SW == 1 ) ;
   return  NUMERO ;
  }
  
  char *VALCADENA(int X, int Y, int T )
   {
   static char CADENA[40];
   int  SW, K, LONGITUD ;
   do {
      SW = 0 ;
      gotoxy(X,Y) ; cout << "                                                           " ;
      gotoxy(X,Y);  gets(CADENA);
      LONGITUD = strlen(CADENA) ;
      if ( LONGITUD == 0 )
	     {
	     gotoxy(20,22); cout << "ERROR.. no ha escrito nada, max = " << T;
	     getch();
	     SW = 1;
	     }
       else
	     if ( LONGITUD > T)
	        {
	        gotoxy(20,22); cout << "ERROR.. demasiados LETRAS, Max = " << T;
	        getch();
	        SW = 1;
	        } 
	      else
	        for ( K = 0 ; K < LONGITUD ; K++ )
	            if (( !isalpha( CADENA[K])) && (CADENA[K]  != ' ') && (CADENA[K]  != '.')
		           && (CADENA[K]  != '-') && (CADENA[K]  != '?') && (CADENA[K]  != '?'))
		           {
		           gotoxy(20,22); cout << "ERROR.. Digite solo Letras";
		           getch();
		           SW = 1;
		           }
	
     gotoxy(10,22) ;cout << "                                                             ";
     } while ( SW == 1 ) ;
     return CADENA ;
   }

void TITULO(){

system("cls");
system("color F1");

gotoxy(25,4); cout << "TITULO ORDINARIO";
gotoxy(23,6); cout << "VECTOR DE REGISTRO";
}

int MENU(){
	
	int TIPO;
	TITULO(); 
	gotoxy(23,7); cout << "MENU DEL PROGRAMA";
	gotoxy(20,9); cout << "1. CAPTURA DE DATOS"; 
	gotoxy(20,10); cout << "2. CONSULTA TOTAL"; 
	gotoxy(20,11); cout << "3. CONSULRTA SELECTIVA"; 
	gotoxy(20,12); cout << "4. SALIR DEL PROGRAMA";
	
	
	do{
		gotoxy(20,20); cout << "Seleccione una Opcion:";
		gotoxy(42,20); cout << "          ";
		gotoxy(42,20); TIPO = VALNUMERO(42,20,1); 
	}while((TIPO > 4)||(TIPO < 1));
	return TIPO;
}

void CAPTURA(){
	char OP = 'S'; 
	
	while((OP == 'S') && (NRO < 50))
	{
		TITULO();
		gotoxy(22,7); cout << "CAPTURA DE DATOS"; 
		gotoxy(20,9); cout << "NOMBRE       : ";
		gotoxy(20,10); cout << "CEDULA       : "; 
		gotoxy(20,11); cout << "SEXO(F/M)    : ";
		
		cin.sync(); 
		gotoxy(35,9); strcpy(EMPLEADO[NRO].NOMBRE , VALCADENA(35,9,20));
		gotoxy(35,9); cout << strupr(EMPLEADO[NRO].NOMBRE);
		
		do{
			gotoxy(35,10); EMPLEADO[NRO].CEDULA = VALNUMERO(35,10,10);
		}while(EMPLEADO[NRO].CEDULA < 0 ); 
		
		do {
			gotoxy(35,11); cout << "      ";
			gotoxy(35,11); EMPLEADO[NRO].SEXO = getche();
			gotoxy(35,11); EMPLEADO[NRO].SEXO = toupper(EMPLEADO[NRO].SEXO);
			
		}while((EMPLEADO[NRO].SEXO != 'F') && (EMPLEADO[NRO].SEXO != 'M'));
		NRO = NRO + 1;
		
		do{
			gotoxy(20,20), cout << "DESEA CONTINUAR S/N:"; 
			gotoxy(40,20); cout << "         ";
			gotoxy(40,20); OP = getche();
			gotoxy(40,20); OP = toupper(OP);
		}while((OP != 'S') && (OP != 'N'));
		 
	}
}

void DETALLE()
   {
   	TITULO();
   gotoxy(12,8) ; printf("CEDULA      NOMBRE      SEXO ");
   }

void CONSULTA()
{
	int F,K; 
	if(NRO == 0)
	{
		gotoxy(20,20); cout << "NO HAY DATOS";
		getch();
	}
	else
	{
		DETALLE();
		F = 10;
		
		for(K = 0; K < NRO; K++)
		{
			gotoxy(12,F); cout << EMPLEADO[K].CEDULA;
			gotoxy(24,F); cout << EMPLEADO[K].NOMBRE;
			gotoxy(36,F); cout << EMPLEADO[K].SEXO;
			
			if(F <= 24)
			F++;
			else{
				gotoxy(21,F+=3); cout << "Pulse cualquiere tecla para continuar",
				getch();
				F = 10;
				DETALLE(); 
			}
		}
		gotoxy(21,F+=3); cout << "Pulse cualquier tecla para contiunar";
		getch();
	}
	
}

void CONSULTA_S(){
	char SEX, OP = 'S';
	int SW = 0, K;
	
	if(NRO == 0)
	{
		gotoxy(20,20 ); cout << "NO HAY DATOS EN LOS ARCHIVOS";
	}
	else
	{
		
		TITULO();
		
		do{
			gotoxy(20,12); cout << "SEXO a buscar(F/M):";
			gotoxy(39,12); cout << "           "; 
			gotoxy(39,12); SEX = getche();
			SEX = toupper(SEX); 
		}while((SEX != 'F') && (SEX != 'M'));
		
		for(K = 0;((K < NRO) && (SW == 0));K++)
		{
			if (SEX == EMPLEADO[K].SEXO)
			{
				SW = 1;
				gotoxy(20,14); cout << "NOMBRE:" << EMPLEADO[K].NOMBRE;
				gotoxy(20,15); cout << "CEDULA:" << EMPLEADO[K].CEDULA;
				gotoxy(20,16); cout << "SEXO:" << EMPLEADO[K].SEXO;
			}
			
		}
		if(SW == 0)
		{
			gotoxy(20,20); cout << "NO SE ENCONTRO EL REGISTRO";
		}
		
			gotoxy(20,22); cout << "PULSE CUALQUIER TECLA PARA CONRIUNAR";
			gotoxy(40,22); OP = getche();
			OP = toupper(OP);
		
	}
		
	
}






int main()
{
   char OP = 'S'; 
   int OPCION = 0; 
   
   while(OP == 'S')
   {
   
   	OPCION = MENU(); 
   	
   	switch(OPCION){
   		case 1: CAPTURA();
   		break;
   		case 2: CONSULTA();
   		break;
   		case 3: CONSULTA_S();
   		break;
   		case 4: OP = 'N';
   		break;
	   }
   }
   
   
   
   
   
   
   
   
   
}