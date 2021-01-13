#include "Randomgen.h"


int random_int(int max) {

	return rand() % max;

}


float random_uniform() {

	return (float)(rand() % 10000) / 10000.0;

}