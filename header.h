#ifndef HEADER_H
#define HEADER_H

#ifdef __APPLE__

#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif

#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include "Particules/Particule.h"
#include "Particules/Particules.h"
#include "Voxels/Voxel.h"


#endif
