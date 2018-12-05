#include "header.h"

using namespace std;
vector <double> grid[NC][NC];

double frand(double dmin, double dmax)
{
  double f = (double)rand() / RAND_MAX;
  return dmin + f * (dmax - dmin);
}
void printGrid()
{
  for (size_t i = 0; i < NC; i++)
  {
    for (size_t j = 0; j < NC; j++)
      printf("[%f, %f] ", grid[i][j][0], grid[i][j][1]);
  }
  printf("\n");
}
void printTab(double **tab, const int n)
{
  for (size_t i = 0; i < n; i++)
  {
    for (size_t j = 0; j < n; j++)
      printf("%.3f ", tab[i][j]);
  }
  printf("\n");
}
void initGrid()
{
  double alpha;
  for (size_t i = 0; i < NC; i++)
  {
    for (size_t j = 0; j < NC; j++)
    {
      alpha = frand(0, 2 * M_PI);
      grid[i][j].push_back(cos(alpha));
      grid[i][j].push_back(sin(alpha));
    }
  }
}
double dotGrid(int i, int j, double x, double y)
{
  double dx = x - i;
  double dy = y - j;

  return dx * grid[j][i].at(0) + dy * grid[j][i].at(1);
}
double inter(double d1, double d2, double w)
{
  return d1 + w * (d2 - d1);
}
double fade(int x)
{
  return 6 * pow(x, 5) - 15 * pow(x, 4) + 10 * pow(x, 3);
}
double max(double **tab, const int n)
{
  double m = -100000;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      m = tab[i][j] > m? tab[i][j] : m;
    }
  }
  return m;
}

double min(double **tab, const int n)
{
  double m = 100000;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      m = tab[i][j] < m? tab[i][j] : m;
    }
  }
  return m;
}
double range(double x, double vmin, double vmax)
{
  return (x - vmin)/(vmax - vmin);
}
double perlin(double x, double y)
{
  int i[2] = {int(x), int(x + 1)};
  int j[2] = {int(y), int(y + 1)};

  double sx = x - i[0];
  double sy = y - j[0];

  double n[2];
  double ix[2];

  n[0] = dotGrid(i[0], j[0], x, y);
  n[1] = dotGrid(i[1], j[0], x, y);
  ix[0] = inter(n[0], n[1], sx);

  n[0] = dotGrid(i[0], j[1], x, y);
  n[1] = dotGrid(i[1], j[1], x, y);
  ix[1] = inter(n[0], n[1], sx);

  return inter(ix[0], ix[1], sy);
}
