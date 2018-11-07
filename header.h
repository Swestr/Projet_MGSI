#ifndef HEADER_H
#define HEADER_H

#ifdef __APPLE__

#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "Vent.h"
#include "Voxel.h"
#include "Scale.h"
#include "Translation.h"
#endif
