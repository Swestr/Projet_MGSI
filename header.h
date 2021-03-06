#ifndef HEADER_H
#define HEADER_H

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif

#define NC 10
#define NP 100

#include "Class/Particule.h"
#include "Class/Particules.h"
#include "Class/Vent.h"
#include "Class/Perlin.h"
#include "Class/Obstacle.h"
#include "Class/Sphere.h"
#include "Class/Parallelepipede.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <vector>
#include <cstdlib>
#include <string>
#include <iostream>

#endif
