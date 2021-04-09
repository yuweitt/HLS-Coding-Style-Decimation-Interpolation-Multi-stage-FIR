
#include <math.h>
#include <iostream>
#include "fir_filter.h"
using namespace std;
# define NUM_SAMPLES 600

int main(int argc, char *argv[])
{
	FILE         *fp;

	streamIn_t strmInput;
	streamOut_t strmOut;
	fixIn_t h[TAP] = {0.25, 0.25, 0.25, 0.25};
	fixIn_t input[NUM_SAMPLES];
	fixOut_t output[NUM_SAMPLES * SAMPLE_RATE];
	fixIn_t data;
	fixIn_t signal;
	const double pi = 3.14;

	cout << ">> Start test!" << endl;


    fp = fopen("out.dat", "w");
	// Execute the function with latest input
	for (int i = 0; i < NUM_SAMPLES ; i++) {
        signal = 0.98 * sin(2 * pi * i / 64);
        input[i] = signal;
        strmInput.write(signal);
        if(i%SAMPLE_RATE==(SAMPLE_RATE-1))
        	fir_filter(&strmInput, h, &strmOut);
	}

	// Save the results.
	for (int i = 0; i < NUM_SAMPLES / SAMPLE_RATE; i++) {
		output[i] = strmOut.read();
		fprintf(fp,"%i %.7f %.14f\n", i, input[i*SAMPLE_RATE].to_float(), output[i].to_float());
	}

	fclose(fp);


    cout << ">> Comparing against output data..." << endl;

    if (system("fc .\\out.dat ..\\..\\..\\out_gold.dat")) {
		cout << ">> Test failed!" << endl;
		return 1;
	}

    cout << ">> Test passed!" << endl;
	cout << "------------------------" << endl;
    return 0;

	printf("Finish!");

}
