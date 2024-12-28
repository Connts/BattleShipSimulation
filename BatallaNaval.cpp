#include <iostream>
#include <stdio.h>
#include <windows.h> //PERMITE POSCIONAR LOS CARACTERES, CAMBIARLES EL COLOR
#include <conio.h>
#include <stdlib.h>
#include<time.h> 
#include<pthread.h>


int corazones=5;

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hCon,dwPos);

}
void OcultaCursor() {
 CONSOLE_CURSOR_INFO cci = {100, FALSE};
 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}
void setColor(int color) {
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon, color);
}


class Bala{
    int x,y;
public:
	
    Bala(int xInicial, int yInicial)
    {
        x = xInicial;
        y = yInicial;
    }
    int X()
    {
        return x;
    }
    int Y()
    {
        return y;
    }
    void mover();
    void moverR();
    void enemiga();
    void enemigaR();
};
void Bala::enemiga(){
    gotoxy(x, y); printf(" "); // Borras la bala de su posición actual
    if (x > 3) {  // Solo si x es mayor que 2 (límite izquierdo)
        x--; // Decrementas x
        setColor(4);
        gotoxy(x, y); printf("*"); // Pintas la bala en la nueva posición
    }
}
void Bala::enemigaR(){
    gotoxy(x, y);
    printf(" "); // Borras la bala de su posición actual
    if (x < 79) { // Solo si x es menor que 79 (límite derecho)
        x++; // Incrementas x
    }
    // Pintas la bala en la nueva posición si x es menor que 79
    // Si x es igual a 79, en cambio imprimes un espacio, lo que hace que la bala desaparezca
    gotoxy(x, y);
    setColor(4);
    printf(x < 79 ? "*" : " ");
}

void Bala::mover(){
    gotoxy(x, y); printf(" "); // Borras la bala de su posición actual
    if (x > 3) {  // Solo si x es mayor que 2 (límite izquierdo)
        x--; // Decrementas x
        gotoxy(x, y); printf("*"); // Pintas la bala en la nueva posición
    }
}	

void Bala::moverR() {
    gotoxy(x, y);
    printf(" "); // Borras la bala de su posición actual
    if (x < 79) { // Solo si x es menor que 79 (límite derecho)
        x++; // Incrementas x
    }
    // Pintas la bala en la nueva posición si x es menor que 79
    // Si x es igual a 79, en cambio imprimes un espacio, lo que hace que la bala desaparezca
    gotoxy(x, y);
    printf(x < 79 ? "*" : " ");
}

// Clase Barco principal
class SHIP{
    int corazones;
    int x;
    int y;
public:
    
    void Pintar();
    void Borrar();
    void Morir();
    int X() { return x; }  // Getter para obtener la coordenada X
    int Y() { return y; }  // Getter para obtener la coordenada Y
    SHIP(int _corazones);
};

SHIP::SHIP(int _corazones)
{
    corazones = _corazones;
    x = 35;  // Coordenada X inicial del barco principal
    y = 15;  // Coordenada Y inicial del barco principal
}


void SHIP::Pintar(){
	gotoxy (35,13);
 	printf("  %c\n",178);
 	gotoxy (35,14);
	printf(" %c%c%c\n",178,178,178);
	gotoxy (35,15);
	printf("%c%c%c%c%c\n",205,178,178,178,205);
	gotoxy (35,16);
	printf("%c%c%c%c%c\n",205,178,178,178,205);
	gotoxy (35,17);
	printf("%c%c%c%c%c\n",205,178,178,178,205);
	gotoxy (35,18);
	printf("%c%c%c%c%c\n",205,178,178,178,205);
	gotoxy (35,19);
	printf(" %c%c%c\n",178,178,178);
	gotoxy (35,20);
	printf("  %c",178,178,178);
}

void Borrar(){
		gotoxy (35,13);
 	printf("          ");
 	gotoxy (35,14);
	printf("          ");
	gotoxy (35,15);
	printf("          ");
	gotoxy (35,16);
	printf("          ");
	gotoxy (35,17);
	printf("          ");
	gotoxy (35,18);
	printf("          ");
	gotoxy (35,19);
	printf("          ");
	gotoxy (35,20);
	printf("          ");
}

void SHIP::Morir(){
	gotoxy (35,13);
 	printf(" *   *");
 	gotoxy (35,14);
	printf("**    **");
	gotoxy (35,15);
	printf("**    **");
	gotoxy (35,16);
	printf("**    **");
	gotoxy (35,17);
	printf("**    **");
	gotoxy (35,18);
	printf("**    **");
	gotoxy (35,19);
	printf("**    **");
	gotoxy (35,20);
	printf(" *   *");
	
}
 


 void* PintarEnemL(void*){
	printf("%c%c\n",178,205);
 }
 
 void* PintarEnemR(void*){
	printf("%c%c\n",205,178);

 }
 void BorrarEnem(int x, int y)
{
    gotoxy(x, y);
    printf("   ");
    gotoxy(x, y + 1);
    printf("    ");
    gotoxy(x, y + 2);
    printf("   ");
}
 
 
 
 

void paint(){
	// Lineas horizontales
	for (int i = 3; i < 80; i++)
	{
		gotoxy(i,3);
		printf("%c",205);
		gotoxy(i,30);
		printf("%c",205);
	}

	// Lineas verticales
	for (int i = 4; i < 30; i++)
	{
		gotoxy(2,i);
		printf("%c",186);
		gotoxy(80,i);
		printf("%c",186);
	}

	// Esquinas
	gotoxy(2,3);
	printf("%c",201);
	gotoxy(2,30);
	printf("%c",200);
	gotoxy(80,3);
	printf("%c",187);
	gotoxy(80,30);
	printf("%c",188);

}

void simulacion() {
	
    DWORD tiempoInicio = GetTickCount();
    OcultaCursor();
    SHIP B(5);
    pthread_t EI1;
    pthread_create(&EI1,NULL,PintarEnemL, NULL);
    gotoxy(22,13);
    pthread_join (EI1,NULL);
    
    pthread_t EI2;
    pthread_create(&EI2,NULL,PintarEnemL, NULL);
    gotoxy(12,18);
    pthread_join (EI2,NULL);
    
    pthread_t EI3;
    pthread_create(&EI3,NULL,PintarEnemL, NULL);
    gotoxy(7,15);
    pthread_join (EI3,NULL);
    
    pthread_t EI4;
    pthread_create(&EI4,NULL,PintarEnemL, NULL);
    gotoxy(28,10);
    pthread_join (EI4,NULL);
    
    pthread_t EI5;
    pthread_create(&EI5,NULL,PintarEnemL, NULL);
    gotoxy(15,20);
    pthread_join (EI5,NULL);
    
    pthread_t EI6;
    pthread_create(&EI6,NULL,PintarEnemL, NULL);
    gotoxy(18,16);
    pthread_join (EI6,NULL);
    
    pthread_t ER1;
    pthread_create(&ER1,NULL,PintarEnemR, NULL);
    gotoxy(43,14);
    pthread_join (ER1,NULL);
    
    pthread_t ER2;
    pthread_create(&ER2,NULL,PintarEnemR, NULL);
    gotoxy(70,17);
    pthread_join (ER2,NULL);
    
    pthread_t ER3;
    pthread_create(&ER3,NULL,PintarEnemR, NULL);
    gotoxy(52,12);
    pthread_join (ER3,NULL);
    
    pthread_t ER4;
    pthread_create(&ER4,NULL,PintarEnemR, NULL);
    gotoxy(56,15);
    pthread_join (ER4,NULL);
    
    pthread_t ER5;
    pthread_create(&ER5,NULL,PintarEnemR, NULL);
    gotoxy(61,22);
    pthread_join (ER5,NULL);
    
    pthread_t ER6;
    pthread_create(&ER6,NULL,PintarEnemR, NULL);
    gotoxy(47,18);
    pthread_join (ER6,NULL);
    
    B.Pintar();
    const int nBalasEnemigo = 3;

// Balas para cada enemigo
	Bala* balasEnemigoI[nBalasEnemigo] = {
    new Bala(42,14), 
	new Bala(68,18),
	};

	Bala* balasEnemigoD[nBalasEnemigo] = {
    new Bala(26,13), 
    new Bala(16,18),
	};

    	
	const int nBalas = 3;
 	Bala* bDerecha[nBalas] = { 
        new Bala(41,14), 
        new Bala(66,15),
        new Bala(76,17),
    };

 	Bala* bIzquierda[nBalas] = { 
        new Bala(24,13), 
        new Bala(9,15),
        new Bala(14,18),
    };

    const int numBalas = 4;
    Bala* balasIzquierda[numBalas] = { 
        new Bala(34,15), 
        new Bala(34,16),
        new Bala(34,17),
        new Bala(34,18)
    };

    Bala* balasDerecha[numBalas] = { 
        new Bala(40,15), 
        new Bala(40,16),
        new Bala(40,17),
        new Bala(40,18)
    };

    int indiceBalaActual = 0;
    bool turnoIzquierdo = true;
	int tiroEnemigo = 0;
	int indiceBalaEnemigo = 0;
	bool turnoEnemigoD = true;
	bool turnoEnemigoI = true;
    while (TRUE) {
    if (turnoIzquierdo) {
        // Movimiento de las balas izquierdas
        if (balasIzquierda[indiceBalaActual]->X() > 3) {
            balasIzquierda[indiceBalaActual]->mover();
        } else {
            gotoxy(balasIzquierda[indiceBalaActual]->X(), balasIzquierda[indiceBalaActual]->Y());
            printf(" ");
            turnoIzquierdo = false;
        }
    } else {
        // Movimiento de las balas derechas
        if (balasDerecha[indiceBalaActual]->X() < 79) {
            balasDerecha[indiceBalaActual]->moverR();
        } else {
            turnoIzquierdo = true;
            indiceBalaActual = (indiceBalaActual + 1) % numBalas;
        }
    }
    if (turnoEnemigoD) {
    if (balasEnemigoD[indiceBalaEnemigo]->X() < 79) {
        balasEnemigoD[indiceBalaEnemigo]->enemigaR();
    } else {
        gotoxy(balasEnemigoD[indiceBalaEnemigo]->X(), balasEnemigoD[indiceBalaEnemigo]->Y());
        printf(" ");
        turnoEnemigoD = false;
    }
} else {
        // Movimiento de las balas derechas
        if (balasEnemigoI[indiceBalaEnemigo]->X() < 79) {
            balasEnemigoI[indiceBalaEnemigo]->enemiga();
        } else {
            turnoEnemigoD= true;
            indiceBalaEnemigo = (indiceBalaEnemigo + 1) % nBalasEnemigo;
        }
    }
    paint();

    Sleep(40);

    DWORD tiempoActual = GetTickCount();
    DWORD tiempoTranscurrido = tiempoActual - tiempoInicio;
    if (tiempoTranscurrido >= 12000) {
        break;
    }
}
}
int main() {
    simulacion();
    return 0;
}


