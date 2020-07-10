#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "a4.h"

void freePOP (Individual *population_free, int population_size )
{
	int i;
	for (i = 1; i < population_size; i++)
	{
		free((population_free + i)->image.data); //not sure why, but the following free cannot free this
	}
	//free(population_free);//this will free population and the images
}

int cmp(const void *a, const void *b) { 
	return (*(Individual *)a).fitness > (*(Individual *)b).fitness? 1 : -1; 
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate){
	int i = 0 , j;
	Individual *rand_population;
	srand(time(NULL));
	// generate a random population
	rand_population = generate_population(population_size  , image->width, image->height, image->max_color);
	// compute the fitness of each individual
	comp_fitness_population(image->data, rand_population, population_size);  
	// sort the individuals in non-decreasing order

	qsort(rand_population, population_size, sizeof(*rand_population), cmp);	
	// For generation1 to number_generations
	// crossover on the population
	for(i = 0; i < num_generations; i++)
	{
		crossover(rand_population, population_size);
		// mute individuals
		mutate_population(rand_population, population_size, rate);
		// compute the fitness
		comp_fitness_population(image->data, rand_population, population_size);
		// sort
		qsort(rand_population, population_size, sizeof(*rand_population), cmp);
	}
	freePOP(rand_population, population_size);

	return &((rand_population)->image);
}

void free_image(PPM_IMAGE *p)
{
	free(p->data);
	free(p);
}


