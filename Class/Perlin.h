#ifndef PERLIN_H
#define PERLIN_H

double frand(double, double);
void printGrid();
void printTab(double **, int);
void initGrid();
double dotGrid(int, int, double, double);
double inter(double, double, double);
double fade(int);
double max(double **, const int);
double min(double **, const int);
double perlin(double, double);
double **perlin2D(int);
double range(double, double, double);

#endif
