#ifndef PATRICULES_H
#define PATRICULES_H

#include <vector>

class Particules
{
  public:
    std::vector<Particule*> v;
    Particules(int);
    void reinitialize(int);
    void getVBOS(GLfloat*, GLuint*, GLuint*);
};

#endif
