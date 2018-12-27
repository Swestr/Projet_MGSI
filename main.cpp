/********************************************************/
/*                     hyperboloide.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un hyperboloide en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#include "header.h"

/*Controles*/
char presse;
int anglex,angley,x,y,xold,yold;
float coordY = 0.5, sca = 1;
bool obstacle = true, pause = false, pas = false;
bool mouseLeftDown;
bool mouseRightDown;
bool mouseMiddleDown;
float mouseX, mouseY;

/*Shader*/
GLuint VBO_sommets, VBO_indices, VBO_UVtext, VBO_normales, VAO;
GLfloat sommets[NP*8*3];
GLuint faces[NP*6*4];
GLuint coordTexture[NP*6*8];
GLuint programID;
glm::mat4 MVP;
glm::mat4 Model, View, Projection;

GLuint MatrixIDMVP,MatrixIDView,MatrixIDModel,MatrixIDPerspective;
GLuint locCameraPosition ;
GLuint locmaterialShininess ;
GLuint locmaterialSpecularColor;
GLuint locLightPosition ;
GLuint locLightIntensities;
GLuint locLightAttenuation;
GLuint locLightAmbientCoefficient;
GLuint locLightDiffuseCoefficient;
GLuint locLightSpecularLightIntensities;
vec3 cameraPosition(0.,0.,3.);
GLuint image ;
GLuint bufTexture;
GLuint locationTexture;

float cameraAngleX;
float cameraAngleY;
float cameraDistance=0.;

/*Création des particules*/
Particules p(NP);

/* Création des vents */
Vent *vents[2];
int nbVents = 0;
/*Vent 1*/
std::vector<double> p1V1{-10, 0.5, -10};
std::vector<double> p2V1{20, 0.7, 20};
std::vector<double> vecDirV1{1, 1, 0};
Vent *v1 = new Vent(p1V1, p2V1, vecDirV1, 1.4);
/*Vent2*/
std::vector<double> p1V2{-10, 1, -10};
std::vector<double> p2V2{20, 1.5, 20};
std::vector<double> vecDirV2{-1, 1, 0};
Vent *v2 = new Vent(p1V2, p2V2, vecDirV2, 1.5);

/* Création obstacle */
Obstacle *obstacles[2] ;
int nbObstaces = 0;
/*Sphère*/
std::vector<double> centre{0.5,1,0.5};
float rayon = 0.5;
Obstacle *sphere = new Sphere(centre, rayon);
/*Parallelepipede*/
std::vector<double> translation{1, 1, 1};
std::vector<double> rotation{0., 0., 45.};
std::vector<double> scalePa{0.75, 0.25, 1};
Obstacle *para = new Parallelepipede(translation, rotation, scalePa);


/* Prototype des fonctions */
void affichage();
void animation();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x, int y);
void processSpecialKeys(int key, int xx, int yy);
void genereVBO ();
void traceObjet();
void deleteVBO();
void traceObjet();
void initOpenGL(void);
void initTexture();
GLubyte* glmReadPPM(char* filename, int* width, int* height);


int main(int argc,char **argv)
{
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("Fumee");
  glEnable(GL_BLEND);
  glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);


  // Initialize GLEW
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

  //info version GLSL
	std::cout << "***** Info GPU *****" << std::endl;
  std::cout << "Fabricant : " << glGetString (GL_VENDOR) << std::endl;
  std::cout << "Carte graphique: " << glGetString (GL_RENDERER) << std::endl;
  std::cout << "Version : " << glGetString (GL_VERSION) << std::endl;
  std::cout << "Version GLSL : " << glGetString (GL_SHADING_LANGUAGE_VERSION) << std::endl << std::endl;

	initOpenGL();

  p.getVBOS(sommets, faces, coordTexture);

  genereVBO();
  initTexture();

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
  glDeleteProgram(programID);
  deleteVBO();
  return 0;
}

void initTexture()
{
  int iwidth  , iheight;
  GLubyte *  image = NULL;
  image = glmReadPPM((char*)"textfumee.ppm", &iwidth, &iheight);
  glGenTextures(1, &bufTexture);
  glBindTexture(GL_TEXTURE_2D, bufTexture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, iwidth,iheight, 0, GL_RGB,GL_UNSIGNED_BYTE,image);
  locationTexture = glGetUniformLocation(programID, "myTextureSampler");
  // glBindAttribLocation(programID, 3, "vertexUV");
}

GLubyte* glmReadPPM(char* filename, int* width, int* height)
{
    FILE* fp;
    int i, w, h, d;
    unsigned char* image;
    char head[70];

    fp = fopen(filename, "rb");
    if (!fp) {
        perror(filename);
        return NULL;
    }
    fgets(head, 70, fp);
    if (strncmp(head, "P6", 2)) {
        fprintf(stderr, "%s: Not a raw PPM file\n", filename);
        return NULL;
    }
    i = 0;
    while(i < 3) {
        fgets(head, 70, fp);
        if (head[0] == '#')
            continue;
        if (i == 0)
            i += sscanf(head, "%d %d %d", &w, &h, &d);
        else if (i == 1)
            i += sscanf(head, "%d %d", &h, &d);
        else if (i == 2)
            i += sscanf(head, "%d", &d);
    }
    image = new unsigned char[w*h*3];
    fread(image, sizeof(unsigned char), w*h*3, fp);
    fclose(fp);

    *width = w;
    *height = h;
    return image;
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
          p.v[i]->force_move(vec_dir);
          leave = true;
          continue;
        }
      }
      if(leave) continue;
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
    traceObjet();

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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glShadeModel(GL_SMOOTH);

  glLoadIdentity();
  glScalef(sca, sca, sca);
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
  gluLookAt(0.5f, coordY, 0.5f, 0.5f, coordY, 0.0f, 0.0f, 1.0f, 0.0f);

  p.getVBOS(sommets, faces, coordTexture);

  //Affichage de(s) l'obstacle
  if(obstacle){
    for(int obs = 0; obs < nbObstaces; obs++){
      obstacles[obs]->draw(0,0,1);
    }
  }

  View       = glm::lookAt(   cameraPosition, // Camera is at (0,0,3), in World Space
                                       glm::vec3(0,0,0), // and looks at the origin
                                       glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
                          );
  Model = glm::mat4(1.0f);
  Model = glm::translate(Model,glm::vec3(0,0,cameraDistance));
  Model = glm::rotate(Model,glm::radians(cameraAngleX),glm::vec3(1, 0, 0) );
  Model = glm::rotate(Model,glm::radians(cameraAngleY),glm::vec3(0, 1, 0) );
  Model = glm::scale(Model,glm::vec3(.8, .8, .8));
  MVP = Projection * View * Model;

  traceObjet();
  //Affichage des zones de vents
  // for (size_t i = 0; i < nbVents; i++) {
  //   vents[i]->draw(i, 0, 1);
  // }


  // for (size_t i = 0; i < NP; i++)
  //   p.v[i]->draw();
  glFlush();
  glutSwapBuffers();
}

void genereVBO ()
{
    glGenBuffers(1, &VAO);
    glBindVertexArray(VAO);


    if(glIsBuffer(VBO_sommets) == GL_TRUE) glDeleteBuffers(1, &VBO_sommets);
    glGenBuffers(1, &VBO_sommets);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sommets);
    glBufferData(GL_ARRAY_BUFFER, sizeof(sommets),sommets , GL_STATIC_DRAW);
    glVertexAttribPointer ( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

    if(glIsBuffer(VBO_indices) == GL_TRUE) glDeleteBuffers(1, &VBO_indices);
    glGenBuffers(1, &VBO_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces),faces , GL_STATIC_DRAW);

    if(glIsBuffer(VBO_UVtext) == GL_TRUE) glDeleteBuffers(1, &VBO_UVtext);
    glGenBuffers(1, &VBO_UVtext);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_UVtext);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coordTexture),coordTexture , GL_STATIC_DRAW);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, 0,  (void*)0  );

   glEnableVertexAttribArray(0); //Sommets
   glEnableVertexAttribArray(1); //Textures

   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
 }

void deleteVBO()
{
   glDeleteBuffers(1, &VBO_sommets);
   glDeleteBuffers(1, &VBO_indices);
   glDeleteBuffers(1, &VBO_UVtext);
   glDeleteBuffers(1, &VAO);
}

void traceObjet()
{
 glUseProgram(programID);


 glUniformMatrix4fv(MatrixIDMVP, 1, GL_FALSE, &MVP[0][0]);
 glUniformMatrix4fv(MatrixIDModel, 1, GL_FALSE, &Model[0][0]);
 glUniformMatrix4fv(MatrixIDView, 1, GL_FALSE,&View[0][0]);
 glUniformMatrix4fv(MatrixIDPerspective, 1, GL_FALSE, &Projection[0][0]);

  //pour l'affichage
	glBindVertexArray(VAO);
  glDrawElements(GL_QUADS,  sizeof(faces), GL_UNSIGNED_INT, 0);

}

void initOpenGL(void)
{
  glCullFace (GL_BACK); // on spécifie queil faut éliminer les face arriere
  glEnable(GL_CULL_FACE); // on active l'élimination des faces qui par défaut n'est pas active
  glEnable(GL_DEPTH_TEST);
	// le shader
  programID = LoadShaders( "PhongShader.vert", "PhongShader.frag" );
  MatrixIDMVP = glGetUniformLocation(programID, "MVP");
  MatrixIDView = glGetUniformLocation(programID, "VIEW");
  MatrixIDModel = glGetUniformLocation(programID, "MODEL");
  MatrixIDPerspective = glGetUniformLocation(programID, "PERSPECTIVE");
  Projection = glm::perspective( glm::radians(60.f), 1.0f, 1.0f, 1000.0f);
	locCameraPosition = glGetUniformLocation(programID, "cameraPosition");
	locLightAmbientCoefficient = glGetUniformLocation(programID, "light.ambientCoefficient");
	locLightDiffuseCoefficient = glGetUniformLocation(programID, "light.diffuseCoefficient");
	locLightIntensities = glGetUniformLocation(programID, "light.intensities");//a.k.a the color of the light
	locLightPosition = glGetUniformLocation(programID, "light.position");
	locmaterialSpecularColor = glGetUniformLocation(programID, "materialSpecularColor");
	locmaterialShininess = glGetUniformLocation(programID, "materialShininess");
	locLightAttenuation = glGetUniformLocation(programID, "light.attenuation");
}

void clavier(unsigned char touche,int x,int y)
{

  switch (touche)
    {

      case 'L' : /* Réinitialise la grille et ajoute le Parallelepipede */
        obstacles[0] = para;
        nbObstaces = 1;
        p.reinitialize(NP);
        glutPostRedisplay();
        break;

      case 'M' : /* Réinitialise la grille et ajoute la sphere */
        obstacles[0] = sphere;
        nbObstaces = 1;
        p.reinitialize(NP);
        glutPostRedisplay();
        break;

      case 'l' : /* Supprime l'objet */

      case 'm' : /* idem */
        nbObstaces = 0;
        glutPostRedisplay();
        break;

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

void processSpecialKeys(int key, int xx, int yy)
{
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

void reshape(int w,int h)
{
  // if (w<h)
  //   glViewport(0,(w-h)/2,w,w);
  // else
  //   glViewport((w-h)/2,0,h,h);

  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  float aspectRatio = (float)w / h;
  Projection = glm::perspective(glm::radians(60.0f),(float)(w)/(float)h, 1.0f, 1000.0f);

}

void mouse(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
        }
        else if(state == GLUT_UP)
            mouseRightDown = false;
    }

    else if(button == GLUT_MIDDLE_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseMiddleDown = true;
        }
        else if(state == GLUT_UP)
            mouseMiddleDown = false;
    }
}


void mousemotion(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance += (y - mouseY) * 0.2f;
        mouseY = y;
    }

    glutPostRedisplay();
}

// void mouse(int button, int state,int x,int y)
// {
//   /* si on appuie sur le bouton gauche */
//   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
//   {
//     presse = 1; /* le booleen presse passe a 1 (vrai) */
//     xold = x; /* on sauvegarde la position de la souris */
//     yold=y;
//   }
//   /* si on relache le bouton gauche */
//   if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
//     presse=0; /* le booleen presse passe a 0 (faux) */
// }
//
// void mousemotion(int x,int y)
// {
//     if (presse) /* si le bouton gauche est presse */
//     {
//       /* on modifie les angles de rotation de l'objet
// 	 en fonction de la position actuelle de la souris et de la derniere
// 	 position sauvegardee */
//       anglex=anglex+(x-xold);
//       angley=angley+(y-yold);
//       glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
//     }
//
//     xold=x; /* sauvegarde des valeurs courante de le position de la souris */
//     yold=y;
//   }
