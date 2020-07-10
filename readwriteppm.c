#include <stdio.h>
#include <stdlib.h>

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