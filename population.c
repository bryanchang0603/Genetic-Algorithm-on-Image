#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "a4.h"

PIXEL *generate_random_image(int width, int height, int max_color)
{
	PIXEL *genImage;
	int totalSize_gen = width * height, i , max_color_used = max_color + 1;
	genImage = malloc(sizeof(PIXEL) * totalSize_gen); //free this in free_POP
	//randomly create each pixel
	for (i = 0; i < totalSize_gen ; i++)
	{
		(genImage + i)->r = rand()%(max_color_used);
		(genImage + i)->g = rand()%(max_color_used);
		(genImage + i)->b = rand()%(max_color_used);		
	}
	return genImage;
}

Individual *generate_population(int population_size, int width, int height, int max_color)
{
	Individual *population_gen;
	PPM_IMAGE POPImage;
	int i;
	population_gen = malloc(sizeof(Individual) * population_size); //free this in free_POP

	//generate n random image, n is population_size
	for(i = 0; i < population_size; i++)
	{
		//initlizing the image
		POPImage.width = width;
		POPImage.height = height;
		POPImage.max_color = max_color;
		POPImage.data = generate_random_image(width, height, max_color); //free this separetelly;

		//put image into the population
		(population_gen + i)->image = POPImage; 
	}
	return population_gen;

}