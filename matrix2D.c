/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix2D.h"

ts_matrix2D * matrix2D_create(const unsigned char number_of_row, const unsigned char number_of_column)
{
	ts_matrix2D * p_matrix = (ts_matrix2D *) calloc (2, sizeof (ts_matrix2D));
	if (p_matrix)
	{
		p_matrix->data = (int **) malloc (number_of_row * sizeof (int*));
		if (p_matrix->data)
		{
            unsigned char row;
			for (row = 0; row < number_of_row; row++)
			{
				p_matrix->data [row] = (int *) calloc (number_of_column, sizeof (int));
				if (!p_matrix->data [row])
				{
                    do
                        free (p_matrix->data [--row]);
                    while (row);
					free (p_matrix->data);
					free (p_matrix);
					return NULL;
				}
			}
			p_matrix->header.number_of_row = number_of_row;
			p_matrix->header.number_of_column = number_of_column;
			p_matrix->header.size = number_of_row * number_of_column;
			return p_matrix;
		}
	}
	return NULL;
}

int matrix2D_get (const ts_matrix2D matrix, unsigned char row, unsigned char column)
{
	 return matrix.data [row][column];
}

void matrix2D_set (const ts_matrix2D matrix, unsigned char row, unsigned char column, int value)
{
	 matrix.data [row][column] = value;
}

void matrix2D_print (const ts_matrix2D matrix)
{
    unsigned char row, column;
	for (row = 0; row < matrix.header.number_of_row; row++)
	{
		printf("| ");
		for (column = 0; column < matrix.header.number_of_column; column++)
			printf ("%d ", matrix.data [row][column]);
		printf ("|\n");
	}
}

ts_matrix2D * matrix2D_ascii_load(tp_file_name file_name)
{
	if (file_name)
	{
		FILE *file_in;
		file_in = fopen (file_name, "r");
		if (file_in)
		{
			int row, column;
			ts_matrix2D * p_matrix;
			fscanf (file_in, "%d", &row);
			fscanf (file_in, "%d", &column);
			p_matrix = m2d_create((char) row, (char) column);
			fscanf (file_in, "%d", &p_matrix->header.size);
			if (p_matrix)
			{
				for (row = 0; row < p_matrix->header.number_of_row; row++)
					for (column = 0; column < p_matrix->header.number_of_column; column++)
						fscanf (file_in, "%d", p_matrix->data [row] + column);
				fclose (file_in);
				return p_matrix;
			}
		}
	}
	return NULL;
}

int matrix2D_ascii_save(tp_file_name file_name, const ts_matrix2D matrix)
{
	if (file_name)
	{
		FILE *file_out;
		file_out = fopen (file_name, "w");
		if (file_out)
		{
            unsigned char row, column;
			fprintf (file_out, "%d ", matrix.header.number_of_row);
			fprintf (file_out, "%d ", matrix.header.number_of_column);
			fprintf (file_out, "%d ", matrix.header.size);
			for (row = 0; row < matrix.header.number_of_row; row++)
				for (column = 0; column < matrix.header.number_of_column; column++)
					fprintf (file_out, "%d ", matrix.data [row][column]);
			fclose (file_out);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

ts_matrix2D * matrix2D_binary_load(tp_file_name file_name)
{
	if (file_name)
	{
		FILE *file_in;
		file_in = fopen (file_name, "rb");
		if (file_in)
	{
            unsigned char row, column;
			ts_matrix2D * p_matrix;
			fread (&row, sizeof (char), 1, file_in);
			fread (&column, sizeof (char), 1, file_in);
			p_matrix = m2d_create(row, column);
			fread (&p_matrix->header.size, sizeof (int), 1, file_in);
			if (p_matrix)
			{
				for (row = 0; row < p_matrix->header.number_of_row; row++)
					for (column = 0; column < p_matrix->header.number_of_column; column++)
						fread (p_matrix->data [row] + column, sizeof (int), 1, file_in);
				fclose (file_in);
				return p_matrix;
			}
		}
	}
	return NULL;
}

int matrix2D_binary_save(tp_file_name file_name, const ts_matrix2D matrix)
{
	if (file_name)
	{
		FILE *file_out;
		file_out = fopen (file_name, "wb");
		if (file_out)
		{
            unsigned char row, column;
			fwrite (&matrix.header.number_of_row, sizeof (char), 1, file_out);
			fwrite (&matrix.header.number_of_column, sizeof (char), 1, file_out);
			fwrite (&matrix.header.size, sizeof (int), 1, file_out);
			for (row = 0; row < matrix.header.number_of_row; row++)
				for (column = 0; column < matrix.header.number_of_column; column++)
					fwrite (matrix.data [row] + column, sizeof (int), 1, file_out);
			fclose (file_out);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

ts_matrix2D* matrix2D_binary_block_load (tp_file_name file_name)
{
	if (file_name)
	{
		FILE *file_in;
		file_in = fopen (file_name, "rb");
		if (file_in)
		{
			struct matrixHeader header;
			ts_matrix2D * p_matrix;
			fread (&header, sizeof (header), 1, file_in);
			p_matrix = m2d_create(header.number_of_row, header.number_of_column);
			if (p_matrix)
			{
                unsigned char row;
				for (row = 0; row < p_matrix->header.number_of_row; row++)
					fread (p_matrix->data [row], sizeof (int), p_matrix->header.number_of_column, file_in);
				fclose (file_in);
				return p_matrix;
			}
			fclose (file_in);
		}
	}
	return NULL;
}

int matrix2D_binary_block_save (tp_file_name file_name, const ts_matrix2D matrix)
{
	if (file_name)
	{
		FILE *file_out;
		file_out = fopen (file_name, "wb");
		if (file_out)
		{
            unsigned char row;
			fwrite (&matrix.header, sizeof (matrix.header), 1, file_out);
			for (row = 0; row < matrix.header.number_of_row; row++)
                fwrite (matrix.data [row], sizeof (int), matrix.header.number_of_column, file_out);
			fclose (file_out);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

void matrix2D_free (ts_matrix2D * p_matrix)
{
    unsigned char row;
	for (row = 0; row < p_matrix->header.number_of_row; row++)
		free (p_matrix->data [row]);
	free(p_matrix->data);
	free(p_matrix);
}
*/