#include <stdio.h>
#include "screen.h"
#include <stdlib.h>		// for random numbers
#include <time.h>

int main(){
	int dec[COL],i;		// 80-pieces of sound decibels
	srand(time(NULL));
	for(i=0; i<COL; i++) dec[i] = rand()%70+30;
	clearScreen();
	setColors(RED, bg(YELLOW));
	barChart(dec);

	resetColors();
	getchar();
}
