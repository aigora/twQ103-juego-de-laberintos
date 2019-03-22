//El trabajo que se ha planteado realizar es un juego de laberintos en el cual el usuario pueda registrarse con su nombre y apellidos y elegir entre diversos niveles de dificultad: 
//fácil, medio y experto. El usuario tendrá la posibilidad de realizar el laberinto cuantas veces quiera y comparar resultados en una tabla de valores con sus mejores puntuaciones. 
//Para el movimiento del jugador por el laberinto se usará el sistema asdw y el objetivo final se pondrá con un asterisco impreso en pantalla.

// ESTE ES UN MENÚ DE PRUEBA EN EL QUE PRÓXIMAMENTE REALIZAREMOS CAMBIOS.

#include <stdio.h>

#define N 100
#define M 100

int main () {
	
		char nombre[N], apellido[M];
		int dif, s;
		printf("Bienvenidos al Juego de Laberintos \n");
		
	
	do{
		
		
		
		printf("Introduzca su nombre: \n");
		gets(nombre);
		printf("Introduzca su apellido: \n");
		gets(apellido);
		
		printf("Elija la dificultad del juego: \n");
		
		printf("Si pulsa 1 , la dificultad será fácil \n ");
		printf("Si pulsa 2 , la dificultad será normal \n ");
		printf("Si pulsa 3 , la dificultad será difícil \n ");
		scanf("%d",&dif);
		
		switch (dif){
			case 1: printf("La dificultad  elegida es la fácil \n");
					break;
			case 2: printf("La dificultad  elegida es la normal \n");
					break;
			case 3: printf("La dificultad  elegida es la dificil \n");
					break;
			default: printf("Opcion incorrecta \n");
					break;
			
			
		}
		printf("Quiere salir del juego?\n");
		printf("Si pulsa 0 , fin del programa \n");
		printf("Si pulsa 1 , continua el programa \n");
		
	
		scanf("%d",&s);
		
		
			
		}while(s != 0);
		
		return 0;
		

	}
	

