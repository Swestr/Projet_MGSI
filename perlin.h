#ifndef PERLIN_H
#define PERLIN_H

#include <header.h>

double frand(double dmin, double dmax);
void printGrid();
void printTab(double **tab, int n);
void initGrid(const int N);
double dotGrid(int i, int j, double x, double y);
double inter(double d1, double d2, double w);
double fade(int x);
double max(double **tab, const int n);
double min(double **tab, const int n);
double perlin(double x, double y);
double **perlin2D(int N);

#endif
