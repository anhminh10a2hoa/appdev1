#include "comm.h"
#include <math.h>
#include <curl/curl.h>

// function definition for sendDATA(), this function will calculate 16000
// sample for 8 pieces of Faster decibel values and send them using
// curl library function to an URL. The format of POST data is
// db=num1;num2;num3;...;num8
void sendDATA(short s[])
{
	int i, j;
	float db[8];
	char postdata[128];

	for (i=0; i<8; i++){
		double sum = 0;
		for(j=0; j<2000; j++){
			sum += s[i*2000+j] * s[i*2000+j];
		}
		double rms = sqrt(sum/2000);
		db[i] = 20*log10(rms);
#ifdef DEBUG
		printf("Fast db[%d] = %.2f\n", db[i]);
#endif
	}
	// create post string
	sprintf(postdata, "db=%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f",
		db[0], db[1], db[2], db[3], db[4], db[5], db[6], db[7]);

	curl_global_init(CURL_GLOBAL_ALL);
	CURL *c = curl_easy_init();
	if(c){
		curl_easy_setopt(c, CURLOPT_URL, URL);
		curl_easy_setopt(c, CURLOPT_POSTFIELDS, postdata);
		CURLcode res = curl_easy_perform(c);
		if(res != CURLE_OK)
			printf("Communication is NOT okay!\n");
        curl_easy_cleanup(c);
	}
	curl_global_cleanup();
}
