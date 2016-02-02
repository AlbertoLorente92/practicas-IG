/*	Práctica 3 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/
#include <Windows.h>
/*#include <gl/GL.h>
#include <gl/GLU.h>*/

//#include <GL/freeglut.h>
#include <GL/glut.h>

#include "Satelite.h"
#include "CiruloEspiral.h"

/*#include <iostream>
using namespace std;*/

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;

// Camera parameters
GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;
GLdouble angY=0;

bool modo;

GLUquadric* esfera = gluNewQuadric();
GLdouble radioEsfera = 2.0;
GLint paralelos = 10, meridianos = 10;

float arrayAlturas[4] = {0,5,6,9};
float arrayRadios[4] = {3,3,2,3.5};

Satelite satelite(6,4,arrayAlturas,arrayRadios);

CirculoEspiral ciruloEsp(20,200,radioEsfera);


GLdouble t = 0.00000000001;
GLint rotacionPlaneta = 0;
GLint rotacionSatelite = 5;
GLint rotacionPaneles = 0;

void inicio();
void initGL();
void display(void);
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void limpiaPunteros();
void buildSceneObjects();
void datosParte1();
void datosParte2();
void parte1Display();
float* matriz();
void parte2Display();

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	inicio();

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
	
	gluQuadricDrawStyle(esfera,GLU_LINE);//GLU_FILL completo

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);glColor3f(0.0,1.0,0.0); 

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	//limpiaPunteros();

	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}

void inicio(){
	int opcion;
	cout << "Eliga el modo de ejecucion:" << endl;
	cout << "1\t-\tParte 1. Planeta y Satelite" << endl;
	cout << "2\t-\tParte 2. Planeta, Satelite y Espiral" << endl;
	cout << "Eliga opcion: ";
	cin >> opcion;

	if(opcion==1)
		modo = true;
	else
		modo = false;
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

    // Light0
    glEnable(GL_LIGHT0);
    GLfloat d[]={1.0,1.0,1.0,1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[]={25.0, 25.0, 0.0, 1.0};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	buildSceneObjects();

	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);        
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	// Drawing axes
	glBegin( GL_LINES );
		glColor3f(1.0,0.0,0.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(20, 0, 0);	     
	 
		glColor3f(0.0,1.0,0.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);	 
	 
		glColor3f(0.0,0.0,1.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 20);		
	glEnd();

	if(modo)
		parte1Display();
	else
		parte2Display();
	

	glFlush();
	glutSwapBuffers();
}


void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
   
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	glOrtho(xLeft, xRight, yBot, yTop, N, F);
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;	

		case ' ':  /* Space key */
			if(modo)
				datosParte1();
			else
				datosParte2();
			break;	

		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

void limpiaPunteros(){
	satelite.~Satelite();
	gluDeleteQuadric(esfera);
	esfera = NULL;
}

void buildSceneObjects(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0.0,0.0,-(2*radioEsfera));
	glRotated(90,1.0,0.0,0.0);
	glScaled(0.2,0.2,0.2);
	satelite.dibuja();
	glPopMatrix();
}

void datosParte1(){
	int incrementoPlaneta = 5;
	int incrementoSatelite = 5;
	rotacionPlaneta = (rotacionPlaneta+incrementoPlaneta)%360;
	rotacionSatelite = (rotacionSatelite+incrementoSatelite)%360;
	rotacionPaneles = rotacionPaneles + 5;
}

void datosParte2(){
	int incrementoPlaneta = 5;
	int incrementoSatelite = 5;
	rotacionPlaneta = (rotacionPlaneta+incrementoPlaneta)%360;
	rotacionSatelite = (rotacionSatelite+incrementoSatelite)%360;
	t = t + 0.1;
	rotacionPaneles = rotacionPaneles + 5;
}

void parte1Display(){

	/*glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	satelite.dibujaXPartes(0,36);
	glRotated(rotacionPaneles,0.0,1.0,0.0);
	satelite.dibujaXPartes(36,41);
	satelite.dibujaXPartes(42,47);
	glPopMatrix();

		/*glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotated(rotacionPaneles,0.0,1.0,0.0);
		satelite.dibujaXPartes(36,41);
		satelite.dibujaXPartes(42,47);
		glPopMatrix();*/

	

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	GLdouble x = (sin(rotacionPlaneta * M_PI / 180.0)*(2*radioEsfera));
	GLdouble z = -(cos(rotacionPlaneta * M_PI / 180.0)*(2*radioEsfera));
	glTranslated(x,0.0,z);	
		//rotamos la tierra
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotated(90,1.0,0.0,0.0);
		glRotated(-rotacionPlaneta,0.0,0.0,1.0);
		glColor3f(0.5,0.0,0.0); 
		gluSphere(esfera,radioEsfera,meridianos,paralelos);
		glPopMatrix();

		//dibujamos satelite

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(x,0.0,z);			//<<<< Trasladarlo	(alejarlo de la tierra)

		glRotated(90,1.0,0.0,0.0);		//<<< Rotarlo para que mire a la tierra
		glRotated(rotacionSatelite,0.0,0.0,1.0);	//<<< Rotarlo para que mire a la tierra

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glScaled(0.1,0.1,0.1);
			glRotated(rotacionPaneles,0.0,1.0,0.0);
			satelite.dibujaXPartes(36,41);//Paneles
			satelite.dibujaXPartes(42,47);
			glPopMatrix();

		glScaled(0.1,0.1,0.1);
		glColor3f(0.5,0.0,0.0); 
		satelite.dibujaXPartes(0,36);//Dibuja el cuerpo del satelite	

		glPopMatrix();
	glPopMatrix();
}

float* matriz(GLfloat t){
	float* m = new float[16];

	PuntoVector3D C( (GLfloat)cos(t) + ((GLfloat)t*((GLfloat)sin(t))), 0, ((GLfloat)sin(t)) - ((GLfloat)t*((GLfloat)cos(t))),	1);
	PuntoVector3D Cp(((GLfloat)t * ((GLfloat)cos(t))),	0,(	( (GLfloat)t * ((GLfloat)sin(t)))),	0);
	PuntoVector3D Cpp((((GLfloat)cos(t)) - ( (GLfloat)t * ((GLfloat)sin(t)))),	0,(((GLfloat)sin(t)) + ((GLfloat)t * ((GLfloat)cos(t)))),	0);

	PuntoVector3D* T = Cp.clona();
	T->normaliza();

	PuntoVector3D* B = Cpp.clona();
	B = B->productoVectorial(&Cp);
	B->normaliza();

	PuntoVector3D N = B->productoVectorial(T);

	m[0]=N.getX();
	m[1]=N.getY();
	m[2]=N.getZ();
	m[3]=0;
	m[4]=B->getX();
	m[5]=B->getY();
	m[6]=B->getZ();
	m[7]=0;
	m[8]=T->getX();
	m[9]=T->getY();
	m[10]=T->getZ();
	m[11]=0;
	m[12]=C.getX();
	m[13]=C.getY();
	m[14]=C.getZ();
	m[15]=1;

	return m;
}

void parte2Display(){

		/**
		x(t) = cos(t) + t*sen(t) 
		y(t) = 0 
		z(t) = sen(t) – t*cos(t)
		*/
	ciruloEsp.dibuja();

	float* m = matriz((float)t);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(m);
		//rotamos la tierra
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotated(90,1.0,0.0,0.0);
		glRotated(-rotacionPlaneta,0.0,0.0,1.0);
		glColor3f(0.5,0.0,0.0); 
		gluSphere(esfera,radioEsfera,meridianos,paralelos);
		glPopMatrix();

		//dibujamos satelite
		GLdouble x = (sin(rotacionPlaneta * M_PI / 180.0)*(2*radioEsfera));
		GLdouble z = -(cos(rotacionPlaneta * M_PI / 180.0)*(2*radioEsfera));
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(x,0.0,z);			//<<<< Trasladarlo	(alejarlo de la tierra)

		glRotated(90,1.0,0.0,0.0);		//<<< Rotarlo para que mire a la tierra
		glRotated(rotacionSatelite,0.0,0.0,1.0);	//<<< Rotarlo para que mire a la tierra

			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glScaled(0.1,0.1,0.1);
			glRotated(rotacionPaneles,0.0,1.0,0.0);
			satelite.dibujaXPartes(36,41);//Paneles
			satelite.dibujaXPartes(42,47);
			glPopMatrix();

		glScaled(0.1,0.1,0.1);
		glColor3f(0.5,0.0,0.0); 
		satelite.dibujaXPartes(0,36);//Dibuja el cuerpo del satelite	
		glPopMatrix();
	glPopMatrix();
}