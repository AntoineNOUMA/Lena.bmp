/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix1D.h"

ts_matrix1D * matrix1D_create(const unsigned char number_of_row, const unsigned char number_of_column)
{
	ts_matrix1D * p_matrix = (ts_matrix1D *) calloc (1, sizeof (ts_matrix1D));
	if (p_matrix)
	{
		p_matrix->header.size = number_of_row * number_of_column;
		p_matrix->data = (int *) calloc (p_matrix->header.size, sizeof (int));
		if (p_matrix->data)
		{
			p_matrix->header.number_of_row = number_of_row;
			p_matrix->header.number_of_column = number_of_column;
			return p_matrix;
		}
	}
	return NULL;
}

int matrix1D_get (const ts_matrix1D matrix, const unsigned char row, const unsigned char column)
{
	 return matrix.data [row * matrix.header.number_of_column + column];
}

void matrix1D_set (const ts_matrix1D matrix, const unsigned char row, const unsigned char column, const int value)
{
	 matrix.data [row * matrix.header.number_of_column + column] = value;
}

void matrix1D_print (const ts_matrix1D matrix)
{
    unsigned char row, column;
	for (row = 0; row < matrix.header.number_of_row; row++)
	{
		printf("| ");
		for (column = 0; column < matrix.header.number_of_column; column++)
			printf ("%d ", matrix.data [row * matrix.header.number_of_column + column]);
		printf ("|\n");
	}
}

ts_matrix1D * matrix1D_ascii_load(tp_file_name file_name)
{
	if (file_name)
	{
		FILE *file_in;
		file_in = fopen (file_name, "r");
		if (file_in)
		{
            unsigned int row, column;
			ts_matrix1D * p_matrix;
			fscanf (file_in, "%d", &row);
			fscanf (file_in, "%d", &column);
            p_matrix = m1d_create((unsigned char) row, (unsigned char) column);
			fscanf (file_in, "%d", &p_matrix->header.size);
			if (p_matrix)
			{
				for (row = 0; row < p_matrix->header.number_of_row; row++)
					for (column = 0; column < p_matrix->header.number_of_column; column++)
						fscanf (file_in, "%d", p_matrix->data  + row * p_matrix->header.number_of_column + column);
				fclose (file_in);
				return p_matrix;
			}
		}
	}
	return NULL;
}

int matrix1D_ascii_save(tp_file_name file_name, const ts_matrix1D matrix)
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
					fprintf (file_out, "%d ", matrix.data [row * matrix.header.number_of_column + column]);
			fclose (file_out);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

ts_matrix1D * matrix1D_binary_load(tp_file_name file_name)
{
	if (file_name)
	{
		FILE *file_in;
		file_in = fopen (file_name, "rb");
		if (file_in)
	{
            unsigned char row, column;
			ts_matrix1D * p_matrix;
            fread (&row, sizeof (unsigned char), 1, file_in);
            fread (&column, sizeof (unsigned char), 1, file_in);
			p_matrix = m1d_create(row, column);
			fread (&p_matrix->header.size, sizeof (int), 1, file_in);
			if (p_matrix)
			{
				for (row = 0; row < p_matrix->header.number_of_row; row++)
					for (column = 0; column < p_matrix->header.number_of_column; column++)
						fread (p_matrix->data  + row * p_matrix->header.number_of_column + column, sizeof (int), 1, file_in);
				fclose (file_in);
				return p_matrix;
			}
		}
	}
	return NULL;
}

int matrix1D_binary_save(tp_file_name file_name, const ts_matrix1D matrix)
{
	if (file_name)
	{
		FILE *file_out;
		file_out = fopen (file_name, "wb");
		if (file_out)
		{
            unsigned char row, column;
            fwrite (&matrix.header.number_of_row, sizeof (unsigned char), 1, file_out);
            fwrite (&matrix.header.number_of_column, sizeof (unsigned char), 1, file_out);
			fwrite (&matrix.header.size, sizeof (int), 1, file_out);
			for (row = 0; row < matrix.header.number_of_row; row++)
				for (column = 0; column < matrix.header.number_of_column; column++)
					fwrite (matrix.data + row * matrix.header.number_of_column + column, sizeof (int), 1, file_out);
			fclose (file_out);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

ts_matrix1D* matrix1D_binary_block_load (tp_file_name file_name)
{
	if (file_name)
	{
		FILE *file_in;
		file_in = fopen (file_name, "rb");
		if (file_in)
		{
			struct matrixHeader header;
			ts_matrix1D * p_matrix;
			fread (&header, sizeof (header), 1, file_in);
			p_matrix = m1d_create(header.number_of_row, header.number_of_column);
			if (p_matrix)
			{
				fread (p_matrix->data, sizeof (int), header.size, file_in);
				fclose (file_in);
				return p_matrix;
			}
			fclose (file_in);
		}
	}
	return NULL;
}

int matrix1D_binary_block_save (tp_file_name file_name, const ts_matrix1D matrix)
{
	if (file_name)
	{
		FILE *file_out;
		file_out = fopen (file_name, "wb");
		if (file_out)
		{
			fwrite (&matrix.header, sizeof (matrix.header), 1, file_out);
			fwrite (matrix.data, sizeof (int), matrix.header.size, file_out);
			fclose (file_out);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}

void matrix1D_free (ts_matrix1D * p_matrix)
{
	free(p_matrix->data);
	free(p_matrix);
}
*/