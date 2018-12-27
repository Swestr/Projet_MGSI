#include "header.h"

Particules::Particules(int n)
{
  srand(time(NULL));
  v.clear();
  for (size_t i = 0; i < n; i++)
  {
    v.push_back(new Particule());
  }
}
void Particules::reinitialize(int n)
{
  v.clear();
  srand(time(NULL));

  for (size_t i = 0; i < n; i++)
  {
    v.push_back(new Particule());
  }
}
//a appeler avec un tableau de GLfloat de la taille v.size()*8*3
//(nb de particules * sommets par particules * coordonnées par sommets)
void Particules::getVBOS(GLfloat *sommets, GLuint *faces, GLfloat *normales, GLuint *texture)
{
  float diametre = 0.05;
  int cptSommets = 0;
  int cptFaces = 0;
  int cptNormales = 0;
  int sommet = 0;
  int cptTexture = 0;
  for (size_t i = 0; i < v.size(); i++) {
    sommets[cptSommets++] = v[i]->position[0] + diametre;
    sommets[cptSommets++] = v[i]->position[1] + diametre;
    sommets[cptSommets++] = v[i]->position[2] - diametre;

    sommets[cptSommets++] = v[i]->position[0] - diametre;
    sommets[cptSommets++] = v[i]->position[1] + diametre;
    sommets[cptSommets++] = v[i]->position[2] - diametre;

    sommets[cptSommets++] = v[i]->position[0] - diametre;
    sommets[cptSommets++] = v[i]->position[1] - diametre;
    sommets[cptSommets++] = v[i]->position[2] - diametre;

    sommets[cptSommets++] = v[i]->position[0] + diametre;
    sommets[cptSommets++] = v[i]->position[1] - diametre;
    sommets[cptSommets++] = v[i]->position[2] - diametre;

    sommets[cptSommets++] = v[i]->position[0] + diametre;
    sommets[cptSommets++] = v[i]->position[1] + diametre;
    sommets[cptSommets++] = v[i]->position[0] + diametre;

    sommets[cptSommets++] = v[i]->position[0] + diametre;
    sommets[cptSommets++] = v[i]->position[1] - diametre;
    sommets[cptSommets++] = v[i]->position[2] + diametre;

    sommets[cptSommets++] = v[i]->position[0] - diametre;
    sommets[cptSommets++] = v[i]->position[1] - diametre;
    sommets[cptSommets++] = v[i]->position[2] + diametre;

    sommets[cptSommets++] = v[i]->position[0] - diametre;
    sommets[cptSommets++] = v[i]->position[1] + diametre;
    sommets[cptSommets++] = v[i]->position[2] + diametre;

    faces[cptFaces++] = sommet;
    faces[cptFaces++] = sommet+1;
    faces[cptFaces++] = sommet+2;
    faces[cptFaces++] = sommet+3;

    faces[cptFaces++] = sommet+4;
    faces[cptFaces++] = sommet+5;
    faces[cptFaces++] = sommet+6;
    faces[cptFaces++] = sommet+7;

    faces[cptFaces++] = sommet;
    faces[cptFaces++] = sommet+4;
    faces[cptFaces++] = sommet+5;
    faces[cptFaces++] = sommet+3;

    faces[cptFaces++] = sommet;
    faces[cptFaces++] = sommet+1;
    faces[cptFaces++] = sommet+7;
    faces[cptFaces++] = sommet+4;

    faces[cptFaces++] = sommet+2;
    faces[cptFaces++] = sommet+1;
    faces[cptFaces++] = sommet+7;
    faces[cptFaces++] = sommet+6;

    faces[cptFaces++] = sommet+2;
    faces[cptFaces++] = sommet+3;
    faces[cptFaces++] = sommet+5;
    faces[cptFaces++] = sommet+7;

    normales[cptNormales++] = 0;
    normales[cptNormales++] = 0;
    normales[cptNormales++] = -1;

    normales[cptNormales++] = 0;
    normales[cptNormales++] = 0;
    normales[cptNormales++] = 1;

    normales[cptNormales++] = 1;
    normales[cptNormales++] = 0;
    normales[cptNormales++] = 0;

    normales[cptNormales++] = 0;
    normales[cptNormales++] = 1;
    normales[cptNormales++] = 0;

    normales[cptNormales++] = -1;
    normales[cptNormales++] = 0;
    normales[cptNormales++] = 0;

    normales[cptNormales++] = 0;
    normales[cptNormales++] = -1;
    normales[cptNormales++] = 0;

    for (size_t i = 0; i < 6; i++) {
      texture[cptTexture++] = 0;
      texture[cptTexture++] = 0;
      texture[cptTexture++] = 1;
      texture[cptTexture++] = 1;
    }

    sommet += 8;
  }
}
