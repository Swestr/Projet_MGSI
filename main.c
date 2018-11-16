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
  for (size_t i = 0; i < N; i++)
  {
    std::vector<double> vec_dir;
    vec_dir.push_back(0);
    vec_dir.push_back(0.001);
    vec_dir.push_back(0);
    p.v[i]->move(vec_dir);
  }
  glutPostRedisplay();
}
void affichage()
{
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);


  glLoadIdentity();
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
  gluLookAt(0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f);

  //glBegin(GL_POINTS);
  for (size_t i = 0; i < N; i++)
  {
    p.v[i]->draw();
  }
  //axes
 glBegin(GL_LINES);
     glColor3f(1.0,0.0,0.0);
     glVertex3f(0, 0,0.0);
     glVertex3f(1, 0,0.0);
 glEnd();
 //axe des y en vert
 glBegin(GL_LINES);
     glColor3f(0.0,1.0,0.0);
     glVertex3f(0, 0,0.0);
     glVertex3f(0, 1,0.0);
 glEnd();
 //axe des z en bleu
 glBegin(GL_LINES);
     glColor3f(0.0,0.0,1.0);
     glVertex3f(0, 0,0.0);
     glVertex3f(0, 0,1);
 glEnd();
  //On echange les buffers
  glFlush();
  glutSwapBuffers();
}
void clavier(unsigned char touche,int x,int y)
{
  float fraction = 0.1f;

  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
  	}
}
void processSpecialKeys(int key, int xx, int yy) {


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
