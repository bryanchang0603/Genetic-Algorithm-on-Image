#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a4.h"

void mutate(Individual *individual, double rate){
	int i, pixel_mutate;
	int n = individual->image.width * individual->image.height;
	int number_mutate = (int)(rate / 100 * n);
	int max_color = individual->image.max_color + 1;
	PIXEL *pixel = individual->image.data;
	for (i = 0; i < number_mutate; i++){
		pixel_mutate = rand()%n;
		(pixel + pixel_mutate)->r = rand()%(max_color );
		(pixel + pixel_mutate)->g = rand()%(max_color );
		(pixel + pixel_mutate)->b = rand()%(max_color );
	}
}

void mutate_population(Individual *individual, int population_size, double rate)
{
	int i, n;
	n = population_size / 4;
	for(i = n; i < population_size; i++){
		mutate(individual+i, rate);
	}
}
