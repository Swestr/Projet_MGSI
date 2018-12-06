/********************************************************/
/*                     hyperboloide.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un hyperboloide en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#include "header.h"

char presse;
int anglex,angley,x,y,xold,yold;
Particules p(NP);

float coordY = 0.5;
float sca = 1;

bool obstacle = true;
bool pause = false;
bool pas = false;

/* Création des vents */
/* (Je ne peut pas passer le vent en paramètre de animation donc les paramètres doivent être globaux) */

std::vector<double> p1V1{-10, 0.5, -10};
std::vector<double> p2V1{20, 0.7, 20};
std::vector<double> vecDirV1{1, 1, 0};
Vent *v1 = new Vent(p1V1, p2V1, vecDirV1, 1.4);
//
std::vector<double> p1V2{-10, 1, -10};
std::vector<double> p2V2{20, 1.5, 20};
std::vector<double> vecDirV2{-1, 1, 0};
Vent *v2 = new Vent(p1V2, p2V2, vecDirV2, 1.5);

Vent *vents[] = {v1, v2};
int nbVents = 0;

/* Création obstacle */


std::vector<double> translation{0.5, 0.5, 0.5};
std::vector<double> rotation{0., 0., 45.};
std::vector<double> scale{0.75, 0.25, 1};
Obstacle *s1 = new Parallelepipede(translation, rotation, scale);
Obstacle *obstacles[] = {s1};
int nbObstaces = 0;

// std::vector<double> centre{0.5,1,0.5};
// float rayon = 0.5;
// Obstacle *s1 = new Sphere(centre, rayon);
// Obstacle *obstacles[] = {s1};
// int nbObstaces = 1;

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
  initGrid();
  glutMainLoop();
  return 0;
}
void animation()
{
  if(!pause){
    for (int i = 0; i < NP; i++)
    {
      if(p.v[i]->vie <= 0){
        p.v[i] = new Particule();
      }
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

      //Recherche des obstacles
      bool leave = false;
      for(int obs = 0; obs < nbObstaces; obs++){
        Obstacle *obst = obstacles[obs];
        std::vector<double> nextPosition = p.v[i]->nextPosition(vec_dir, speedCoeff);
        if(obst->dedans(nextPosition[0], nextPosition[1], nextPosition[2])){
          vec_dir = obst->getTangente(p.v[i]->position, p.v[i]->direction);
          p.v[i]->r = 0;
          p.v[i]->g = 0;
          p.v[i]->force_move(vec_dir);
          leave = true;
          continue;
        }
      }
      if(leave) continue;

      p.v[i]->r = 1;
      p.v[i]->g = 1;
      //Recherche des vents
      for(int vox = 0; vox < nbVents; vox++) {
        if(vents[vox]->dedans(coordX, coordY, coordZ)){
          vec_dir = vents[vox]->getVec();
          speedCoeff = vents[vox]->getVitesse();
        }
      }

      //Déplacement de la particule
      p.v[i]->move(vec_dir, speedCoeff);
    }

    glutPostRedisplay();
    if(pas){
      pas = false;
      pause = true;
    }
  }
}
void affichagePerlin()
{
  double **d;
  double w = ceil((double)NP / NC);
  double v = (double)NC / (NP * 2);

  double di = v;
  double dj = v;
  d = (double**)malloc(sizeof(double*) * NP);
  for (size_t i = 0; i < NP - w; i++)
  {
     dj = v;
     d[i] = (double*)malloc(sizeof(double) * NP);
     for (size_t j = 0; j < NP - w; j++)
     {
       printf("%.2f %.2f %li %li\n", (double)di, (double)dj, i, j);
       d[i][j] = perlin((double)di, (double)dj);
       dj += v * 2;
     }
     di += v * 2;
  }
  double vmin = min(d, NP - w);
  double vmax = max(d, NP - w);
  di = v;
  dj = v;
  glBegin(GL_POINTS);
  glColor3f(1, 1, 1);
  for (size_t i = 0; i < NP - w; i++)
  {
    dj = v;
    for (size_t j = 0; j < NP - w; j++)
    {
      d[i][j] = range(d[i][j], vmin, vmax);
      glVertex3f(di / NC, d[i][j], dj / NC);
      dj += v * 2;
    }
    di += v * 2;
  }
  glEnd();
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


  //Affichage de(s) l'obstacle
  if(!obstacle){
    for(int obs = 0; obs < nbObstaces; obs++){
      obstacles[obs]->draw(0,0,1);
    }
  }
  glColor3f(1, 0, 0);
  glutSolidSphere(0.01, 10, 10);
  glColor3f(1, 1, 1);

  //Affichage des zones de vents
  // for (size_t i = 0; i < nbVents; i++) {
  //   vents[i]->draw(i, 0, 1);
  // }

  // affichagePerlin();
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

  for (size_t i = 0; i < NP; i++)
   p.v[i]->draw();

  // glBegin(GL_QUADS);
  // for (size_t i = 0; i < NC - 1; i++)
  // {
  //   for (size_t j = 0; j < NC - 1; j++)
  //   {
  //     glColor3f(perlin(i + 0.5, j + 0.5), perlin(i + 0.5, j + 0.5), perlin(i + 0.5, j + 0.5));
  //     glVertex3f((double)i / 10, (double)j / 10, 0);
  //     glVertex3f(((double)i / 10) + 0.1, (double)j / 10, 0);
  //     glVertex3f(((double)i / 10) + 0.1, ((double)j / 10) + 0.1 , 0);
  //     glVertex3f((double)i / 10, ((double)j / 10) + 0.1, 0);
  //   }
  // }
  // glEnd();
  //On echange les buffers
  glFlush();
  glutSwapBuffers();
}
void clavier(unsigned char touche,int x,int y)
{

  switch (touche)
    {
    case 'C' : /* Pas à pas */
      pas = true;
      pause = false;
      glutPostRedisplay();
      break;
    case 'O' : /* Afficher ou non les obstacless */
      obstacle = !obstacle;
      glutPostRedisplay();
      break;
    case 'R' : /* Réinitialisation */
      // pause = false;
      p.reinitialize(NP);
      glutPostRedisplay();
      break;
    case 'P' : /* Pause */
      pause = !pause;
      break;
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
