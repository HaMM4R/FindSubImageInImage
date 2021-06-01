#pragma once

int countRows(char *fileName); 
int countColumns(char *fileName);

double* read_text(char *fileName, int sizeR, int sizeC);
void write_pgm(char *filename, double *data, int sizeR, int sizeC, int Q);