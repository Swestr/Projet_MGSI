#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <vector>

class Obstacle
{
  public:
    std::vector<double> normer(double x, double y, double z);
    virtual std::vector<double> getTangente(std::vector<double> part, std::vector<double> I)=0;
    virtual bool dedans(float x, float y, float z)=0;
    virtual void draw(int r, int g, int b)=0;
};
#endif
