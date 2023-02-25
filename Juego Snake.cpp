#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool GameOver;
const int ancho = 20;
const int altura = 20;
int x, y ,frutaX , frutaY , puntaje;
enum eDireccion {stop=0,derecha,izquierda,abajo,arriba};
eDireccion direc;
int colaX[100], colaY[100];
int numeroColas;

void iniciarVariables();
void mapaSnake();
void tecladoSnake();
void logicaDeMovimientos();

int main(){

	iniciarVariables();
	
	while(!GameOver){
		mapaSnake();
		tecladoSnake();
		logicaDeMovimientos();
	}
	
	getch();
	return 0;
}

void iniciarVariables(){
	GameOver = false;
	direc = stop;
	x = ancho / 2;
	y = altura / 2;
	frutaX = rand() % ancho;
	frutaY = rand() % altura;
	puntaje = 0;
	
}

void mapaSnake(){
	
	system("cls");
	
	for(int i=0; i < ancho;i++){
		cout<<"#";
	}
	
	cout<<endl;
	
	for(int i=0; i < altura;i++){
		for(int j=0; j < ancho;j++){
			if(j == 0)
				cout<<"#";
			if(i == y && j == x)
				cout<<"0";
			else if(i == frutaY && j == frutaX)
				cout<<"F";
			else{
				bool dibujar = false;
				for(int k = 0;k < numeroColas;k++){
					
					if(colaX[k] == j && colaY[k] == i){

						cout<<"o";
						dibujar = true;
					}
				}
				if(!dibujar)
						cout<<" ";
			} 
					
			if(j == ancho - 1)
				cout<<"#";
	}
	cout<<endl;
	}
	
	for(int i=0; i < ancho;i++){
		cout<<"#";
	}
	cout<<endl;
	cout<<"Puntaje: "<<puntaje<<endl;
}

void tecladoSnake(){
	if(_kbhit() ){
		switch(_getch()){
			case 'a':
				direc = derecha;
				break;
			case 'd':
				direc = izquierda;
				break;
			case 'w':
				direc = arriba;
				break;
			case 's':
				direc = abajo;
				break;
			case 'p':
				GameOver = true;
				getch();
				break;
		}
	}
	
}

void logicaDeMovimientos(){
	
	int previoX = colaX[0];
	int previoY = colaY[0];
	int previo2X,previo2Y;
	
	colaX[0] = x;
	colaY[0] = y;
	
	for(int i=1;i<numeroColas;i++){
		
		previo2X = colaX[i];
		previo2Y = colaY[i];
		colaX[i] = previoX;
		colaY[i] = previoY;
		previoX = previo2X;
		previoY = previo2Y;
	}
	switch (direc){
		case derecha:
			x--;
			break;
		case izquierda:
			x++;
			break;
		case arriba:
			y--;
			break;
		case abajo:
			y++;
			break;
	}
	if( x > ancho || x < 0 ||y > altura || y < 0)
		GameOver = true;
	for(int i=0;i < numeroColas;i++){
		if(colaX[i] == x && colaY[i] == y){
			GameOver = true;
		}
	}
	if(x == frutaX && y == frutaY){
		puntaje = puntaje + 10;
		frutaX = rand() % ancho;
		frutaY = rand() % altura;
		numeroColas++;
	}
}