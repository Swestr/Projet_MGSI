#include "header.h"

Particules::Particules(int n)
{
  srand(time(NULL));

  for (size_t i = 0; i < n; i++)
  {
    v.push_back(new Particule());
  }
}
