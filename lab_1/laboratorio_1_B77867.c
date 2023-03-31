/*Codigo realizado por Diego Valladares Porras, carne: B77867 para el curso de IE-0624 Laboratorio de Microcontroladores
//Laboratorio 1: Introduccion a microcontroladores y manejo de GPIOS

****************************************************************************************************************************/

#include <pic14/pic12f683.h>
typedef unsigned int word; //Se define el word para definir la configuracion del PIC
word __at 0x2007 __CONFIG = (_WDTE_OFF & _WDT_OFF & _MCLRE_OFF ); //Se definen BODEN (o BOREN, segun la TDS), WDTE, WDT OFF para evitar resets
																			//MCLRE=0 porque se utilizara el GP3 como input, entonces GP3=1
void delay (unsigned int tiempo); //Funcion para hacer los delays de los LEDs
	
void main(void) //Funcion principal
{

    TRISIO = 0b00001000; //Poner todos los pines como salidas menos GP3
    GPIO = 0x00; //Poner pines en bajo
	ANSEL = 0;
    CMCON0 = 0x07;
	
	//Variables para inicializar la generacion de numeros aleatorios mediante el metodo de LFSR
    int lfsr=0b111; //Estado inicial del numero aleatorio
    int bit=0b000; //Valor inicial de bit=0, necesario para el cambio del valor de lfsr.
    int decenas = 0;
	int unidades = 0;
	

    //Loop forever
    while ( 1 )
    {

		if (decenas==0) // Si decenas=0
			{	
				GP1 = 0;
				GP2 = 0;
				GP4 = 0;
				GP5 = 0;
			}
			else if ( decenas==1) //  Si  decenas=1
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 0;
				GP5 = 1;
			}
			else if ( decenas==2) //  Si  decenas=2
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 1;
				GP5 = 0;
			}
			else if ( decenas==3) //  Si  decenas=3
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 1;
				GP5 = 1;
			}
			else if ( decenas==4) //  Si  decenas=4
			{
				GP1 = 0;
				GP2 = 1;
				GP4 = 0;
				GP5 = 0;
			}
			else if ( decenas==5) //  Si  decenas=5
			{
				GP1 = 0;
				GP2 = 1;
				GP4 = 0;
				GP5 = 1;
			}
			else if ( decenas==6) //  Si  decenas=6
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 1;
				GP5 = 1;
			}
			else if (decenas==7) //  Si  decenas=7
			{
				GP1 = 0;
				GP2 = 1;
				GP4 = 1;
				GP5 = 1;
			}
			else if ( decenas==8) //  Si  decenas=8
			{
				GP1 = 1;
				GP2 = 0;
				GP4 = 0;
				GP5 = 0;
			}
			else if ( decenas==9) //  Si  decenas=9
			{
				GP1 = 1;
				GP2 = 0;
				GP4 = 0;
				GP5 = 1;
			}

		delay(10);
		GP0=~GP0;

			if (unidades==0) // Si unidades=0
			{	
				GP1 = 0;
				GP2 = 0;
				GP4 = 0;
				GP5 = 0;
			}
			else if ( unidades==1) //  Si  unidades=1
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 0;
				GP5 = 1;
			}
			else if ( unidades==2) //  Si  unidades=2
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 1;
				GP5 = 0;
			}
			else if ( unidades==3) //  Si  unidades=3
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 1;
				GP5 = 1;
			}
			else if ( unidades==4) //  Si  unidades=4
			{
				GP1 = 0;
				GP2 = 1;
				GP4 = 0;
				GP5 = 0;
			}
			else if ( unidades==5) //  Si  unidades=5
			{
				GP1 = 0;
				GP2 = 1;
				GP4 = 0;
				GP5 = 1;
			}
			else if ( unidades==6) //  Si  unidades=6
			{
				GP1 = 0;
				GP2 = 0;
				GP4 = 1;
				GP5 = 1;
			}
			else if ( unidades==7) //  Si  unidades=7
			{
				GP1 = 0;
				GP2 = 1;
				GP4 = 1;
				GP5 = 1;
			}
			else if ( unidades==8) //  Si  unidades=8
			{
				GP1 = 1;
				GP2 = 0;
				GP4 = 0;
				GP5 = 0;
			}
			else if ( unidades==9) //  Si  unidades=9
			{
				GP1 = 1;
				GP2 = 0;
				GP4 = 0;
				GP5 = 1;
			}
			delay(10);
			GP0=~GP0;

		if (GP3==0) //Si GP3=1
		{ 
		//Generacion de numeros aleatorios del 1 al 99 utilizando el metodo "linear-feedback shift register" 
		bit=((lfsr >> 0) ^	 (lfsr >> 2) ^	 (lfsr >> 3) ^	 (lfsr >> 5)) & 1; 
		lfsr= (lfsr >> 1) | (bit << 7); //8 bits cubren hasta 128, sin embargo solo necesitamos hasta 99.
		lfsr % 100;
			decenas = lfsr / 10;
			unidades = lfsr % 10;
		
		//Las salidas seran GP1, GP2, GP4, GP5
		/*
		GP0 = Ground
		GP1 = S1 - A
		GP2 = S2 - B
		GP4 = S3 - C 
		GP5 = S4 - D
		*/
		}
	}
}
void delay(unsigned int tiempo) 
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
