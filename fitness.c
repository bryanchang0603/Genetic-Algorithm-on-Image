#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "a4.h"

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size)
{
	int i = 0, j = image_size/5 , z = 0;
	double sumDistancer = 0, sumDistanceg = 0, sumDistanceb = 0, sumDistance = 0, returnDistance = 0, 
	colorDistance1r = 0, colorDistance2r = 0, colorDistance3r = 0, colorDistance4r = 0, colorDistancer = 0,
	colorDistance1g = 0, colorDistance2g = 0, colorDistance3g = 0, colorDistance4g = 0, colorDistanceg = 0,
	colorDistance1b = 0, colorDistance2b = 0, colorDistance3b = 0, colorDistance4b = 0, colorDistanceb = 0,
	colorDistance;	
	//double a, b;

	//compute total distance
	for (i ; z < j; i+=5 , z++)
	{
		//compute rDistance and add into sumDistance
		colorDistancer = (A + i)->r - (B + i)->r;
		colorDistancer *= colorDistancer;
		colorDistance1r = (A + i + 1)->r - (B + i + 1)->r;
		colorDistance1r *= colorDistance1r;
		colorDistance2r = (A + i + 2)->r - (B + i + 2)->r;
		colorDistance2r *= colorDistance2r;
		colorDistance3r = (A + i + 3)->r - (B + i + 3)->r;
		colorDistance3r *= colorDistance3r;
		colorDistance4r = (A + i + 4)->r - (B + i + 4)->r;
		colorDistance4r *= colorDistance4r;
		sumDistancer = sumDistancer + colorDistancer + colorDistance1r + colorDistance2r + colorDistance3r + colorDistance4r;

		//compute gDistance and add into sumDistance
		colorDistanceg = (A + i)->g - (B + i)->g;
		colorDistanceg *= colorDistanceg;
		colorDistance1g = (A + i + 1)->g - (B + i + 1)->g;
		colorDistance1g *= colorDistance1g;
		colorDistance2g = (A + i + 2)->g - (B + i + 2)->g;
		colorDistance2g *= colorDistance2g;
		colorDistance3g = (A + i + 3)->g - (B + i + 3)->g;
		colorDistance3g *= colorDistance3g;
		colorDistance4g = (A + i + 4)->g - (B + i + 4)->g;
		colorDistance4g *= colorDistance4g;
		sumDistanceg = sumDistanceg + colorDistanceg + colorDistance1g + colorDistance2g + colorDistance3g + colorDistance4g;

		//compute bDistance and add into sumDistance
		colorDistanceb = (A + i)->b - (B + i)->b;
		colorDistanceb *= colorDistanceb;
		colorDistance1b = (A + i + 1)->b - (B + i + 1)->b;
		colorDistance1b *= colorDistance1b;
		colorDistance2b = (A + i + 2)->b - (B + i + 2)->b;
		colorDistance2b *= colorDistance2b;
		colorDistance3b = (A + i + 3)->b - (B + i + 3)->b;
		colorDistance3b *= colorDistance3b;
		colorDistance4b = (A + i + 4)->b - (B + i + 4)->b;
		colorDistance4b *= colorDistance4b;
		sumDistanceb = sumDistanceb + colorDistanceb + colorDistance1b + colorDistance2b + colorDistance3b + colorDistance4b;
	}
	sumDistance = sumDistancer + sumDistanceg + sumDistanceb;
	for (i; i < image_size; i++)
	{
		colorDistance = (A + i)->r - (B + i)->r;
		colorDistance *= colorDistance;
		sumDistance += colorDistance;

		colorDistance =(A + i)->g - (B + i)->g;
		colorDistance *= colorDistance;
		sumDistance += colorDistance;

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
