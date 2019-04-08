// this file contains screen functions. They are used to display
// sound levels on a PUTTY screen as a bar chart
#include <stdio.h>
#include "screen.h"

void barChart(int db[]){
	int i,j,peak;

	setColors(RED, bg(BLACK));
	for(i=0; i<COL; i++){	// for 80 columns
		for(j=0; j<db[i]/3; j++){
			if(j*3>60){
				setColors(CYAN, bg(BLACK));}
			else{
				setColors(RED, bg(BLACK));}
			printf("\033[%d;%dH", 35-j, i+1);

#ifdef UNICODE				// conditional compilation
			printf("%s",BAR);
#else
			printf("%c", '*');
#endif
		}
	}
}
void clearScreen(void){
	printf("\033[2J");
	fflush(stdout);		// for remote terminal (such as PUTTY)
}

void setColors(short bg, short fg){
	printf("\033[%d;%d;1m", bg, fg);
	fflush(stdout);
}

void resetColors(void){
	printf("\033[0m");
	fflush(stdout);
}
