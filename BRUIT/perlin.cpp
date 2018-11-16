#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

using namespace std;

#define N 10
vector<double> grid[N][N];

double frand(double dmin, double dmax)
{
  double f = (double)rand() / RAND_MAX;
  return dmin + f * (dmax - dmin);
}
void printGrid()
{
  for (size_t i = 0; i < N; i++)
  {
    for (size_t j = 0; j < N; j++)
      printf("[%f, %f] ", grid[i][j][0], grid[i][j][1]);
  }
  printf("\n");
}
void initGrid()
{
  double alpha;
  for (size_t i = 0; i < N; i++)
  {
    for (size_t j = 0; j < N; j++)
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
double max(double tab[N][N], const int n)
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

double min(double tab[N][N], const int n)
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
  // printf("s: %.2f, %.2f\n", sx, sy);
  // printf("n: %.2f, %.2f\n", n[0], n[1]);
  // printf("ix: %.2f, %.2f\n", ix[0], ix[1]);

  n[0] = dotGrid(i[0], j[1], x, y);
  n[1] = dotGrid(i[1], j[1], x, y);
  ix[1] = inter(n[0], n[1], sx);

  // printf("s: %.2f, %.2f\n", sx, sy);
  // printf("n: %.2f, %.2f\n", n[0], n[1]);
  // printf("ix: %.2f, %.2f\n", ix[0], ix[1]);
  return inter(ix[0], ix[1], sy);
}
int main(int argc, char const *argv[])
{
  srand(time(NULL));
  initGrid();
  printGrid();
  double tab[N][N];
  for (size_t i = 1; i <= 10; i++)
  {
    for (size_t j = 1; j <= 10; j++)
    {
      tab[i - 1][j - 1] = perlin((double)i / 10, (double)j / 10);
      printf("%f ", tab[i - 1][j - 1]);
    }
    printf("\n");
  }
  double vmax = max(tab, N);
  double vmin = min(tab, N);
  printf("\n");

  for (size_t i = 1; i <= 10; i++)
  {
    for (size_t j = 1; j <= 10; j++)
    {
      tab[i - 1][j - 1] = (tab[i - 1][j - 1] - vmin)/(vmax - vmin);
      printf("%f ", tab[i - 1][j - 1]);
    }
    printf("\n");
  }
  return 0;
}

// 3.4, 7.6
// x' = [3, 4]
// y' = [7, 8]
// sx = 3.4 - 3 = 0.4
// sy = 7.6 - 7 = 0.6
//n0 = dotGrad(3, 4, 3.4, 7.6) = (3.4 - 3 * )
// 0.4 * grid[7][3].x + 0.6 * grid[7][3].y;
// -0.6 * grid[7][4].x - 0.4 * grid[7][4].y;
// -0.6 * grid[7][4].x - 0.4 * grid[7][4].y;
// 0.4 * grid[7][4].x + 0.6 * grid[7][4].y;
