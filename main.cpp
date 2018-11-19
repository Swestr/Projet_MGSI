/********************************************************/
/*                     hyperboloide.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un hyperboloide en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#include "header.h"

#define N 1000
char presse;
int anglex,angley,x,y,xold,yold;
Particules p(N);

float coordY = 0.5;
float sca = 1;

/* Création des vents */
/* (Je ne peut pas passer le vent en paramètre de animation donc les paramètres doivent être globaux) */

std::vector<double> p1V1{-10, 0.5, -10};
std::vector<double> p2V1{20, 0.7, 20};
std::vector<double> vecDirV1{1, 1, 0};
Voxel *v1 = new Voxel(p1V1, p2V1, vecDirV1, 1.4);
//
std::vector<double> p1V2{-10, 1, -10};
std::vector<double> p2V2{20, 1.5, 20};
std::vector<double> vecDirV2{-1, 1, 0};
Voxel *v2 = new Voxel(p1V2, p2V2, vecDirV2, 1.5);

Voxel *voxels[] = {v1, v2};
int nbVoxels = 2;

/* Prototype des fonctions */
void affichage();
void animation();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void processSpecialKeys(int key, int xx, int yy);

int main(int argc,char **argv)
{
/* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("Figures");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutIdleFunc(animation);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);
  glutSpecialFunc(processSpecialKeys);
  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}


void animation()
{
  for (int i = 0; i < N; i++)
  {
    //Les coordonnés de la particule
    double coordX = p.v[i]->position[0];
    double coordY = p.v[i]->position[1];
    double coordZ = p.v[i]->position[2];

    //Recherche du vecteur directeur (de base : (0,0.001,0)) et de la vitesse du vent
    std::vector<double> vec_dir;
    vec_dir.push_back(0);
    vec_dir.push_back(1);
    vec_dir.push_back(0);
    double speedCoeff = 1;
    for(int vox = 0; vox < nbVoxels; vox++) {
        if(voxels[vox]->dedans(coordX, coordY, coordZ)){
          vec_dir = voxels[vox]->getVec();
          speedCoeff = voxels[vox]->getVitesse();
        }
    }
    //Déplacement de la particule
    p.v[i]->move(vec_dir, speedCoeff);
  }
  glutPostRedisplay();
}
void affichage()
{

  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glLoadIdentity();
  glScalef(sca, sca, sca);
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
  gluLookAt(0.5f, coordY, 0.5f, 0.5f, coordY, 0.0f, 0.0f, 1.0f, 0.0f);

  //Affichage des zones de vents
  // for (size_t i = 0; i < nbVoxels; i++) {
  //   voxels[i]->draw(i, 0, 1);
  // }

  // glBegin(GL_POINTS);
  for (size_t i = 0; i < N; i++)
    p.v[i]->draw();


 //  //axes
 // glBegin(GL_LINES);
 //     glColor3f(1.0,0.0,0.0);
 //     glVertex3f(0, 0,0.0);
 //     glVertex3f(1, 0,0.0);
 // glEnd();
 // //axe des y en vert
 // glBegin(GL_LINES);
 //     glColor3f(0.0,1.0,0.0);
 //     glVertex3f(0, 0,0.0);
 //     glVertex3f(0, 1,0.0);
 // glEnd();
 // //axe des z en bleu
 // glBegin(GL_LINES);
 //     glColor3f(0.0,0.0,1.0);
 //     glVertex3f(0, 0,0.0);
 //     glVertex3f(0, 0,1);
 // glEnd();
  //On echange les buffers
  glFlush();
  glutSwapBuffers();
}
void clavier(unsigned char touche,int x,int y)
{
  float fraction = 0.1f;

  switch (touche)
    {
    // case 'p': /* affichage du carre plein */
    //   glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    //   glutPostRedisplay();
    //   break;
    // case 'f': /* affichage en mode fil de fer */
    //   glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //   glutPostRedisplay();
    //   break;
    // case 's' : /* Affichage en mode sommets seuls */
    //   glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
    //   glutPostRedisplay();
    //   break;
    // case 'd':
    //   glEnable(GL_DEPTH_TEST);
    //   glutPostRedisplay();
    //   break;
    // case 'D':
    //   glDisable(GL_DEPTH_TEST);
    //   glutPostRedisplay();
    //   break;
    case 'Z': /* Dézoom */
      sca -= 0.01;
      glutPostRedisplay();
      break;
    case 'z': /* Zoom */
      sca += 0.01;
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
  	}
}
void processSpecialKeys(int key, int xx, int yy) {
  switch(key){
    case GLUT_KEY_UP : /* la caméra se déplace en haut */
      coordY += 0.05;
      glutPostRedisplay();
      break;
    case GLUT_KEY_DOWN : /* la caméra se déplace en bas */
      coordY -= 0.05;
      glutPostRedisplay();
      break;
    case GLUT_KEY_RIGHT : /* la caméra se déplace autour de la fumée par la droite */
      anglex += 1;
      glutPostRedisplay();
      break;
    case GLUT_KEY_LEFT :  /* la caméra se déplace autour de la fumée par la gauche */
      anglex -= 1;
      glutPostRedisplay();
      break;
  }
}
void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else
    glViewport((x-y)/2,0,y,y);
}
void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    presse=0; /* le booleen presse passe a 0 (faux) */
}
void mousemotion(int x,int y)
{
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }
