#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "a4.h"

PPM_IMAGE *read_ppm(const char *file_name)
{
	PPM_IMAGE* test;
	FILE *file;
	char buffer[5];
	file = fopen(file_name , "r");
	test = malloc (sizeof(PPM_IMAGE));//don't worry in free_POP. It's input, not population

	//ignore P3 and reading width, height, and max_color
	fscanf(file, "%s %d %d %d", buffer, &test->width, &test->height , &test->max_color);

	//read each pixel into the data array
	int totalSize_r = (test->height * test->width);
	test->data = malloc(sizeof(PIXEL) * totalSize_r + 1);
	for (int i = 0; i < totalSize_r ; i++)
		fscanf(file, "%hhd %hhd %hhd", &(test->data + i)->r, &(test->data + i)->g, &(test->data + i)->b);
	
	fclose(file);
	return test;
}
void write_ppm(const char *file_name, const PPM_IMAGE *image)
{
	FILE *file = fopen (file_name , "w");
	int totalSize_w = image->width * image->height, i = 0, j;

	//write the info about the image
	fprintf(file , "P3\n%d %d\n%d\n" , image->width, image->height, image->max_color );

	//write each pixel
	while(i < totalSize_w)
	{
		for (j = 0; j < image->width; j++, ++i)
		{
			fprintf(file , "%d %d %d ", (image->data + i)->r, (image->data + i)->g, (image->data + i)->b);
		}
		fprintf(file , "\n");
	}
	fclose(file);
}

PIXEL *generate_random_image(int width, int height, int max_color)
{
	PIXEL *genImage;
	int totalSize_gen = width * height, i;
	genImage = malloc(sizeof(PIXEL) * totalSize_gen + 3); //free this in free_POP
	//randomly create each pixel
	for (i = 0; i < totalSize_gen ; i++)
	{
		(genImage + i)->r = rand()%(max_color + 1);
		(genImage + i)->g = rand()%(max_color + 1);
		(genImage + i)->b = rand()%(max_color + 1);		
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

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size)
{
	int i;
	double sumDistance = 0, returnDistance = 0, colorDistance = 0;

	//compute total distance
	for (i = 0; i < image_size; i++)
	{
		//compute rDistance and add into sumDistance
		colorDistance = (A + i)->r - (B + i)->r;
		colorDistance *= colorDistance;
		sumDistance += colorDistance;

		//compute gDistance and add into sumDistance
		colorDistance = (A + i)->g - (B + i)->g;
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

void mutate(Individual *individual, double rate){
	int i, pixel_mutate;
	int n = individual->image.width * individual->image.height;
	int number_mutate = (int)(rate / 100 * n);
	int max_color = individual->image.max_color;
	PIXEL *pixel = individual->image.data;
	for (i = 0; i < number_mutate; i++){
		pixel_mutate = rand()%n;
		(pixel + pixel_mutate)->r = rand()%(max_color + 1);
		(pixel + pixel_mutate)->g = rand()%(max_color + 1);
		(pixel + pixel_mutate)->b = rand()%(max_color + 1);
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

void freePOP (Individual *population_free, int population_size )
{
	int i;
	for (i = 0; i < population_size; i++)
	{
		//free((population_free + i)->image.data); //not sure why, but the following free cannot free this
		free_image(&(population_free + i)->image);
	}
	//free(population_free);//this will free population and the images
}

int cmp(const void *a, const void *b) { 
	return (*(Individual *)a).fitness > (*(Individual *)b).fitness? 1 : -1; 
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate){
	int i = 0;
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
		//printf("%d %f\n", i, rand_population->fitness);
		
	}
	PPM_IMAGE *ret;
	printf("1");
	ret = malloc(sizeof(PPM_IMAGE));
	ret->data = malloc(sizeof(PIXEL) * (ret->width * ret->height));
	ret->data = rand_population->image.data;
	printf("1");
	*ret = rand_population->image;
	printf("1");
	freePOP(rand_population, population_size);
	printf("1");
	printf("\n%d,%d,%d " , ret->width , ret->height, ret->max_color);
	//printf("%d\n" , ret->data->r);
	return ret;
}

void recombine(Individual *parent1, Individual *parent2, Individual *child1, Individual *child2) {
  // Generate a random number between 0 and image size-1
  int image_size = parent1->image.width * parent1->image.height;
  int crossover = rand() % image_size;
  int i;

  // Up to crossover child1 "inherits" from parent1 and child2 inherits
  // from parent2
  for (i = 0; i < crossover; i++) {
    child1->image.data[i] = parent1->image.data[i];
    child2->image.data[i] = parent2->image.data[i];
  }
  // After that child1 "inherits" from parent2 and child2 inherits
  // from parent1
  for (i = crossover; i < image_size; i++) {
    child1->image.data[i] = parent2->image.data[i];
    child2->image.data[i] = parent1->image.data[i];
  }
}



void crossover(Individual *population, int population_size) {
  
  for (int i = 0; i < population_size / 2; i += 2)
    // parent i and i+1 produce children population_size/2+i and
    // population_size/2+i+1.
    recombine(population + i, population + i + 1,
              population + population_size / 2 + i,
              population + population_size / 2 + i + 1);
}

void free_image(PPM_IMAGE *p)
{	
	free(p->data);
	free(p);


}

int main(int argc, char **argv) {
  // Process input parameters
  const char *input_file = "me.ppm";
  const char *output_file = "me2.ppm";

  int num_generations = 1;
  int population_size = 4;

  double mutation_rate = 3e-2;
  
  // Read image.
  PPM_IMAGE *goal = read_ppm(input_file);
  printf("\nFile %s:\n %dx%d, max color %d, pixels to mutate %d\n",
	 input_file, goal->width, goal->height, goal->max_color, (int)(mutation_rate/100*goal->width*goal->height));

  // Compute image
  PPM_IMAGE *new_image =
    evolve_image(goal, num_generations, population_size, mutation_rate);

  // Write image
  //write_ppm(output_file, new_image);
  // Free memory
  free_image(goal);
  //free_image(new_image);

  return (0);
}
