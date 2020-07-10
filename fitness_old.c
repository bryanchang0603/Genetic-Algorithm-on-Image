#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "a4.h"

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size)
{
	int i;
	double sumDistance = 0, returnDistance = 0, colorDistance = 0;
	//double a, b;

	//compute total distance
	for (i = 0; i < image_size; i++)
	{
		//compute rDistance and add into sumDistance
		colorDistance = (A + i)->r - (B + i)->r;
		colorDistance *= colorDistance;
		sumDistance += colorDistance;

		//compute gDistance and add into sumDistance
		colorDistance =(A + i)->g - (B + i)->g;
		colorDistance *= colorDistance;
		sumDistance += colorDistance;

		//compute bDistance and add into sumDistance
		colorDistance = (A + i)->b - (B + i)->b;
		colorDistance *= colorDistance;
		sumDistance += colorDistance;		
	}

	//compute and return the true distance
	returnDistance = sqrt(sumDistance);
	return returnDistance;
}

void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size){
	int i;
	int image_size = individual->image.width * individual->image.height;
    for (i = 0; i < population_size; i++){
        double graph_fitness = comp_distance(image, (individual + i)->image.data , image_size);
        (individual + i)->fitness = graph_fitness;
    }
}	