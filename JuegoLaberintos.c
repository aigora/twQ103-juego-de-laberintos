#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int juego (int, int, int, int,char laberinto [6][40][60]);
void estadisticas ();
void intestadisticas (int, int);

void main ()
{
	int seleccion, correcto,i,n,j[6],k[6],l, resultado,w, movimientos;
	char laberinto [6][40][60];
	do
	{
		FILE *pf;
		pf =fopen ("laberintos.txt", "r");
		if (pf == NULL)
		{
			printf ("Problema al abrir el archivo\n");
			system ("pause");
		}
		else
		{
			for (i=0; i<5;i++)// recorre los 5 laberintos
			{
				fscanf (pf, "%d %d", &j[i], &k[i]);// dimension. 
				for (n=0;n<k[i];n++)
				{
					fscanf ( pf, "%s", laberinto[i][n]);//dimension
					for (l=0;l<j[i];l++)
					{
						if (laberinto [i][n][l] == 122 ||laberinto [i][n][l] == 90 )// 122='Z' y 90= 'z'
							laberinto [i][n][l] = 32;// 32= espacio
					}
				}
			}
			fclose (pf);
		}
		
		do
		{
			printf ("Bienvenido al juego de los laberintos;\nselecciona un nivel:\n\t1- Laberinto nivel 1\n\t2- Laberinto nivel 2\n\t3- Laberinto nivel 3\n\t4- Laberinto nivel 4\n\t5- Laberinto nivel 5\n\t6- Salir del juego\n\t7- Cargar laberinto\n\t8-Estadisticas Labaerintos\nDespues de hacer su seleccion pulse intro:");
			scanf ("%d", &seleccion);
			seleccion = seleccion-1;
		}
		while(seleccion < 0 || seleccion > 7);
		if (seleccion < 5)
		{
			resultado = juego (seleccion, j[seleccion], k[seleccion], 0, laberinto);// j y k guardan las dimensiones del laberinto que se ha elegido
		}
		else if (seleccion == 5)
			return;
		else if (seleccion == 7)
			estadisticas();
			//for (w=0;w<150;w++)
			//printf ("\n");
		if (seleccion == 6)
		{
			FILE *pf2;
			pf2 = fopen ("glaberintos.txt", "r");
			if (pf2 == NULL)
			{
				printf ("No hay ninguna partida guardada\n");
			}
			else
			{
				fscanf (pf2, "%d %d", &j[5], &k[5]);
				for (n=0;n<k[5];n++)
				{
					fscanf ( pf2, "%s", laberinto[5][n]);
				}
				fscanf ( pf2, "%d", &movimientos);
				fclose (pf2);
				resultado = juego (seleccion-1, j[5], k[5], movimientos, laberinto);
			}
		}
	}while (1);
} 

int juego (int numero, int xmax, int ymax, int movimientos,char laberinto [6][40][60])
{
	int n,x,y, cordx, cordy,i,j;
	char movimiento;
	while (1)
	{
		fflush (stdin);
		for (x=0;x<xmax;x++)//recorre las filas del laberinto
		{
			for (y=0;y<ymax;y++)//una vez recorrida la fila recorre las columnas del laberinto.
			{
				if (laberinto [numero] [y] [x] == 80 )// 80 = 'P' en ASCII. cuando encuentra 'P' entra en el if y la 'P' pasa a ser un asterisco. Guardamos las coordenadas en una variables auxiliares(cordx y cordy)
				{
					cordx = x;
					cordy = y;
					laberinto [numero] [y] [x] = 42;
				}
				else if (laberinto [numero] [y] [x] == 42)// Comprueba que es un asterisco (42=* EN ASCII)
				{
					cordx = x;
					cordy = y;
				}
			    else if(laberinto [numero] [y] [x] == 122)// Si encuentra en el laberinto 'Z' te lo cambia por asteriscos.
		 	       laberinto [numero] [y] [x] == 32;
			}
		}
		for (n=0;n<ymax;n++)// Una vez leído todo el laberinto, va fila y columna imprimiéndolo por pantalla
		{
			for (i=0; i<xmax; i++)
			{
				printf ("%c", laberinto [numero][n] [i]);
			}
			printf ("\n");
		}
		printf ("Movimientos: %d\tX:%d\tY:%d\nPara guardar, pulse P(borrara cualquier laberinto guardado anteriormente)\nPara salir sin guardar, pulse Q\nSeleccione movimineto con WASD y pulse intro: ", movimientos,cordx+1,ymax-(cordy+1));
		scanf ("%c" , &movimiento);
		fflush (stdin);
		if (movimiento == 97 || movimiento == 65 ) //a cuando pulsas a
		{
			if ( laberinto [numero] [cordy] [cordx-1] == 35)// almohadilla. si tu siguiente movimiento al tecler a hace que te choques con una pared te enviara un mensaje diciendo que te has chocado.
			{
				printf ("Movimiento no valido\n");// esto es porque te has chocado con una pared.
				movimientos++;
				continue;
			}
			else if ( laberinto [numero] [cordy] [cordx-1] == 64)// arroba. si tu siguiente movimiento te lleva hasta el arroba te envia un mensjae de enhorabuena.  
			{
				movimientos++;
				
				printf ("Enhorabuena, laberinto solucionado en %d movimientos\n", movimientos);
				intestadisticas (numero, movimientos);
				system ("pause");
				return movimientos;
					}
			else if ( laberinto [numero] [cordy] [cordx-1] == 32)// espacio
			{
				laberinto [numero] [cordy] [cordx-1] = 42;// si el que viene es un espacio lo cambia por asterisco 
				laberinto [numero] [cordy] [cordx] = 32;// y el siguiente te lo cambia por espacio.
				movimientos++;
				continue;
			}
		}
		
		else if (movimiento == 115 || movimiento == 83 ) //s
		{
			if ( laberinto [numero] [cordy+1] [cordx] == 35)
			{
				printf ("Movimiento no valido\n");//pared
				movimientos++;
				continue;
			}
			else if ( laberinto [numero] [cordy+1] [cordx] == 64)
			{
				movimientos++;
				printf ("Enhorabuena, laberinto solucionado en %d movimientos\n", movimientos);
				intestadisticas (numero, movimientos);
				system ("pause");
				return movimientos;
						}
			else if (laberinto [numero] [cordy+1] [cordx] == 32)
			{
				laberinto [numero] [cordy+1] [cordx] = 42;
				laberinto [numero] [cordy] [cordx] = 32;
				movimientos++;
				continue;
			}
		}
		else if (movimiento == 100 || movimiento == 68 ) //d
		{
			if ( laberinto [numero] [cordy] [cordx+1] == 35)
			{
				printf ("Movimiento no valido\n");
				movimientos++;
				continue;
			}
			else if ( laberinto [numero] [cordy] [cordx+1] == 64)
			{
				movimientos++;
				printf ("Enhorabuena, laberinto solucionado en %d movimientos\n", movimientos);
				intestadisticas (numero, movimientos);
				system ("pause");
				return movimientos;
				 
			}
			else if ( laberinto [numero] [cordy] [cordx+1] == 32)
			{
				laberinto [numero] [cordy] [cordx+1] = 42;
				laberinto [numero] [cordy] [cordx] = 32;
				movimientos++;
				continue;
			}
		}
		else if (movimiento == 119 || movimiento == 87 ) //w
		{
			if ( laberinto [numero] [cordy-1] [cordx] == 35)
			{
				printf ("Movimiento no valido\n");
				movimientos++;
				continue;
			}
			else if ( laberinto [numero] [cordy-1] [cordx] == 64)
			{
				movimientos++;
				printf ("Enhorabuena, laberinto solucionado en %d movimientos\n\n", movimientos);
				intestadisticas (numero, movimientos);
					system ("pause");
				return movimientos;
						}
			else  if ( laberinto [numero] [cordy-1] [cordx] == 32)
			{
				laberinto [numero] [cordy-1] [cordx] = 42;
				laberinto [numero] [cordy] [cordx] = 32;
				movimientos++;
				continue;
			}
		}
		else if (movimiento == 80 || movimiento == 112) //p. si le das a la opcion de guardar.
		{
			FILE *pf2;
			pf2 = fopen ("glaberintos.txt", "w");// 
			fprintf (pf2, "%d %d\n", xmax, ymax);// escribe la longitud del laberinto
			for (i=0; i<ymax; i++)//lee fila 
			{
				for (n=0; n<xmax;n++)//lee columnas
				{
					if (laberinto [numero] [i] [n] == 42)// donde este el asterisco, que es tu posicion guardad, el programa lo cambiara por una 'P', y ese sera tu punto inicial cuando se cargue el laberinto
					{
						laberinto [numero] [i] [n] = 80;
					}
					else if (laberinto [numero] [i] [n] == 32)// donde hay espacios pone una z.
					{
						laberinto [numero] [i] [n] = 122;
					}
				}
				fprintf (pf2, "%s\n", laberinto [numero] [i]); // imprime el laberinto en el fichero glaberintos
			}
			fprintf (pf2, "%d", movimientos);// numero de movimientos
			fclose (pf2);
			printf ("Laberinto guardado correctamente\n");
			intestadisticas (numero, movimientos);
			return movimientos;
		}
		else if (movimiento == 81 || movimiento == 113)// q
		{
			intestadisticas (numero, movimientos);// actualiza las estadisticas
			return movimientos;// devuelve lo movimientos
		}
	}
} 

void estadisticas ()
{
	FILE *pf;
	int nivel [100], movimientos [100], contador=0 ,n,numLaberinto [5]= {0,0,0,0,0}, mlaberintos [5] = {0,0,0,0,0};
	bool total = 0;
	pf =fopen ("Estadisticas.txt", "r");//abre el fichero estadisticas de manera read
	if (pf==NULL)// no lo encuentra
	{
		printf ("No hay estadisticas anteriores\n");
		fclose (pf);
		pf = fopen ("Estadisticas.txt", "w");
		fclose (pf);
		system ("pause");
		printf ("\n\n");
		return;
	}
	while (fscanf (pf, "%d %d", &nivel[contador], &movimientos[contador]) != EOF)// escanea 
	{
		if (contador >= 99)
		{
			contador = 0;
			total = 1;
		}
		else if(nivel[contador]<6)
		{
			contador ++;	
		}
	}
	if(contador == 0)
	{
		printf ("No hay estadisticas anteriores\n");
		system ("pause");
		printf ("\n\n");
		return;
	}
	if (total == 1)
		contador = 100;
	for (n=0;n<contador;n++)// COMPRUEBA CUANTOA HAY DE CADA LABERINTO
	{
		numLaberinto [nivel[n]]++;// si el nivel deñ primero es 1 suma 1 al primer laberinto
		mlaberintos[nivel[n]]+=movimientos [n];// suma todos los movimientos que ha habido en el laberinto seleccionado
	}
	printf ("Estadisticas mostradas en porcentaje\n");
	for (n=1;n<6;n++)
	{
		if (numLaberinto [n] == 0)
		{
			printf ("Usuarios que eligieron laberinto nivel %d: 0%\n", n);
		}
		else
		{
			printf ("Usuarios que eligieron laberinto nivel %d: %d\n\tMovimientos medios en el laberinto: %d\n",n, 100*numLaberinto [n]/contador, mlaberintos [n]/numLaberinto[n]);
		}
	}
	system ("pause");
}

void intestadisticas ( int nivel, int movimiento)
{
	int bnivel, bmovimiento;
	nivel++;
	FILE *pf1, *pf2;
	pf1 =fopen ("Estadisticas.txt", "r");
	if (pf1 == NULL)
	{
		fclose (pf1);
		pf1 = fopen ("Estadisticas.txt", "w");
		fprintf (pf1, "%d %d", nivel, movimiento);
		fclose (pf1);
		printf ("Estadisticas guardadas\n");
		return;
	}
	else
	{
		pf2 = fopen ("BEstadisticas.txt.","w");
		while (fscanf (pf1, "%d %d", &bnivel, &bmovimiento)!= EOF)
		{
			fprintf ( pf2, "%d %d\n", bnivel, bmovimiento);
		}
	fprintf (pf2, "%d %d", nivel, movimiento);
	fclose (pf1);
	fclose (pf2);
	pf1 = fopen ( "Estadisticas.txt", "w");
	pf2 = fopen ( "BEstadisticas.txt", "r");
	while (fscanf (pf2, "%d %d", &bnivel, &bmovimiento)!= EOF)
	{
		fprintf (pf1, "%d %d\n", bnivel, bmovimiento);
	}
	fclose (pf1);
	fclose (pf2);
	remove("BEstadisticas.txt");
	printf ("Estadisticas guardadas\n");
	}
}
