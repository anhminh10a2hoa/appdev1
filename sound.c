#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"
int peak;
void showID(char *idname,char *id){
	int i;
	printf("%s : ", idname);
	for(i=0; i<4; i++)
		printf("%c", id[i]);
	puts("");
}

// this function gets one second of samples (16000), and calculates
// 80 pieces of decibel value, we know we need to calculate one decibel
// value from 200 samples, decibel value is calculated by RMS fromula
void displayWAVDATA(short s[]){
	double rms[80];
	int dB[80];			// used to send decibel values to barchart
	short *ptr = s;		// we use a pointer, pointing to the beginning of array
	int i, j;			// for nested loop counters, outer loosarepeats 80 times
						// inner loop repeats 200 times
	for(i=0; i<80; i++){
		double sum = 0;		// accumulate sum of squares

		for(j=0; j<200; j++){
			sum += (*ptr) * (*ptr);
			ptr++;			// pointing to the next sample
		}
		rms[i] = sqrt(sum/200);
#ifdef DEBUG
		printf("rms[%d] = %f\n", i, rms[i]);
#endif
		dB[i] = 20*log10(rms[i]);
	//	if(dB[i]>dB[i+1] && dB[i]>dB[i-1] && dB[i]>80){
			for(peak=0;dB[i]<dB[i+1] && dB[i]>dB[i-1] && dB[i]>80; peak++){
				if(i==79){peak=0;}}
	}
#ifndef DEBUG
	barChart(dB);
#endif
}
void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("ChunkID", h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	showID("Format", h.Format);
	showID("Subchunk1ID", h.Subchunk1ID);
	printf("Subchunk1 size: %d\n", h.Subchunk1Size);
	printf("Audio Format: %d\n", h.AudioFormat);
	printf("Num. of Channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.SampleRate);
	printf("Byte rate: %d\n", h.ByteRate);
	printf("Block Align: %d\n", h.BlockAlign);
	printf("Bits per sample: %d\n", h.BitsPerSample);
	showID("Subchunk2ID", h.Subchunk2ID);
	printf("Subchunk2 size: %d\n", h.Subchunk2Size);
#else
	setColors(WHITE, bg(RED));
	printf("\033[1;1H");
	printf("test.wav");
	setColors(YELLOW, bg(BLUE));
	printf("\033[1;10H");
	printf("sample rate:%d",h.SampleRate);
	setColors(CYAN, bg(MAGENTA));
	printf("\033[1;30H");
	printf("Duration:%.2fsec	",(float)h.Subchunk2Size/h.ByteRate);
	setColors(WHITE, bg(RED));
	printf("\033[1;55H");
	printf("Peaks:%d times",peak);
//	setColors(RED, bg(BLACK));
#endif
}
