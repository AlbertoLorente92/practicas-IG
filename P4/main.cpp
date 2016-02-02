/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;
#include <stdlib.h>
#include "Camara.h"

#include "MuñecoDeNieve.h"
// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight=40, xLeft=-xRight, yTop=40, yBot=-yTop, N=1, F=1000;

// Camera parameters
GLdouble eyeX=100.0, eyeY=100.0, eyeZ=100.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

GLUquadric* esferaCentral = gluNewQuadric();
GLdouble radioEsferaCentral = 4.0;
GLint paralelosCentral = 15, meridianosCentral = 15;

GLUquadric* esferaDerecha = gluNewQuadric();
GLUquadric* esferaSuperior = gluNewQuadric();
GLUquadric* esferaIzquierda = gluNewQuadric();
GLdouble radioEsferasPequeñas = 2;
GLint paralelosPequeñas = 5, meridianosPequeñas = 5;

Sombrero s;

Camara* c;

bool modo, focoPEncendido, ojosMuñeco, ambiental, colocaEsferaDelante = false,narizSeleccionada = false,nieblaActivada = false;

GLdouble angU = 0.0,angV = 0.0, angN = 0.0;

PuntoVector3D* POS = new PuntoVector3D(0,0,0,1);

MuñecoDeNieve frosty;

GLfloat ambApagada[]={0.0f,0.0f,0.0f,1.0f};
GLfloat ambEncendida[]={0.2f,0.2f,0.2f,1.0f};

GLuint texturas[6];


void menu();
void initGL();
void display(void);
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void dibujaEscenaPrimeraParte();
void eliminaPunterosPrimeraParte();
void eliminaPunterosSegundaParte();
void dibujaEscenaSegundaParte();
void muestraConsola1();
void muestraConsola2();
void cambiarModo();

void enciendeApagaP();
void enciendeApagaOjos();
void enciendeApagaAmbiental();

void colocaEsfera();

void niebla();

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	gluQuadricDrawStyle(esferaCentral,GLU_FILL);//GLU_FILL completo - GLU_LINE por lineas
	gluQuadricDrawStyle(esferaDerecha,GLU_FILL);
	gluQuadricDrawStyle(esferaSuperior,GLU_FILL);
	gluQuadricDrawStyle(esferaIzquierda,GLU_FILL);

	menu();

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	if(modo){
		system("cls");
		muestraConsola1();
	}else{
		system("cls");
		muestraConsola2();
	}

	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	eliminaPunterosPrimeraParte();
	eliminaPunterosSegundaParte();

	return 0;
}

void menu(){
	int opcion;

	cout << "Modo de ejecucion:" << endl;
	cout << "1.- Parte 1. Esferas." << endl;
	cout << "2.- Parte 2. Muneco Nieve." << endl;

	do{
		cout << "Modo: \t";
		cin >> opcion;
		cout << endl;
	}while(opcion<=0 || opcion>=3);

	if(opcion==1)
		modo = true;
	else 
		modo = false;
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
    glEnable(GL_LIGHTING);    

	// Camera set up
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);


    // Light0									DIRECCIONAL PRINCIPAL
	focoPEncendido = true;
	GLfloat d[]={1.0,1.0,1.0,0.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    GLfloat a[]={0.3f,0.3f,0.3f,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat p[]={20.0, 20.0, 20.0, 0.0};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);
	GLfloat Q[]={-1.0f, -1.0f, -1.0f};			
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Q);
	glEnable(GL_LIGHT0);

	// Ambiental	
	ambiental = false;
	glEnable(GL_LIGHT_MODEL_AMBIENT);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambApagada);

	// Ojos del muñeco	Light1	Light2
	ojosMuñeco = false; 

	//Niebla
	GLfloat fogColor[4]= {Gray.getF1(),Gray.getF2(),Gray.getF3(), 1.0f};		// Fog Color
	glFogi(GL_FOG_MODE, GL_EXP);												// Fog Mode
	glFogfv(GL_FOG_COLOR, fogColor);											// Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.0035f);											// How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);											// Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);													// Fog Start Depth
	glFogf(GL_FOG_END, 5.0f);													// Fog End Depth


	//Parte del esqueleto...
	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.1f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	// Frustum set up
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();     
	glOrtho(xLeft, xRight, yBot, yTop, N, F);

	c  = new Camara(new PuntoVector3D(eyeX,eyeY,eyeZ,1), new PuntoVector3D(lookX,lookY,lookZ,1), new PuntoVector3D(upX,upY,upZ,1));

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
		dibujaEscenaPrimeraParte();
	else
		dibujaEscenaSegundaParte();

	if(colocaEsferaDelante)
		colocaEsfera();


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

		/////////////////////////lateral, frontal, cenital y esquina.	 
		case '4': 
			c->lateral();//Comprobado
			break;
		case '5': 
			c->frontal();//Comprobado
			break;
		case '6': 
			c->cenital();//Comprobado
			break;
		case '7': 
			c->esquina();//Comprobado
			break;
		/////////////////////////Recorrido Eje OK
		case 'r': 
			c->recorridoEje(1,0,0);//Comprobado
			break;
		case 't': 
			c->recorridoEje(-1,0,0);//Comprobado
			break;
		case 'f': 
			c->recorridoEje(0,1,0);//Comprobado
			break;
		case 'g': 
			c->recorridoEje(0,-1,0);//Comprobado
			break;
		case 'v': 
			c->recorridoEje(0,0,1);//Comprobado
			break;
		case 'b': 
			c->recorridoEje(0,0,-1);//Comprobado
			break;
		/////////////////////////roll, yaw y pitch OK
		case 'n':
			angU++;
			c->rotacionPitch(angU);//Comprobado
			break;
		case 'm':
			angU--;
			c->rotacionPitch(angU);//Comprobado
			break;
		case 'j':
			angV++;
			c->rotacionYaw(angV);//Comprobado
			break;
		case 'k':
			angV--;
			c->rotacionYaw(angV);//Comprobado
			break;
		case 'u':
			angN ++;
			c->rotacionRoll(angN);//Comprobado
			break;
		case 'i':
			angN --;
			c->rotacionRoll(angN);//Comprobado
			break;
		/////////////////////////Ortogonal y perspectiva
		case 'o':
			c->aplicaPerspectiva(true);//Comprobado
			break;
		case 'p':
			c->aplicaPerspectiva(false);//Comprobado
			break;
		/////////////////////////Gira OK
		case '1':
			c->giraX();//Comprobado
			break;
		case '2':
			c->giraY();//Comprobado
			break;
		case '3':
			c->giraZ();//Comprobado
			break;

		case '-':			
			if(!modo){
				colocaEsferaDelante = !colocaEsferaDelante;
				if(colocaEsferaDelante)
					colocaEsfera();
			}
			break;


		case '0':
			enciendeApagaP();
			break;
		case '9':
			if(!modo)
				enciendeApagaOjos();
			break;
		case '8':
			enciendeApagaAmbiental();
			break;

		case 8:
			cambiarModo();
			break;

		
		case '*'://Derecha
			POS->setX(POS->getX()+1);
			POS->setZ(POS->getZ()-1);

			break;

		case '/'://Izquierda
			POS->setX(POS->getX()-1);
			POS->setZ(POS->getZ()+1);
			break;



		case '<'://Niebla
			niebla();
			break;

		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

void dibujaEscenaPrimeraParte(){
	GLdouble separacion = 2.0;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glRotated(90,1.0,0.0,0.0);
	glColor3f(1.0,1.0,1.0); 
	gluSphere(esferaCentral,radioEsferaCentral,meridianosCentral,paralelosCentral);						//Pintamos la esfera central.
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(radioEsferaCentral+radioEsferasPequeñas+separacion,0.0,0.0);
	glRotated(90,1.0,0.0,0.0);	
	glColor3f(1.0,0.0,0.0); 
	gluSphere(esferaDerecha,radioEsferasPequeñas,meridianosPequeñas,paralelosPequeñas);					//Pintamos la esfera derecha.
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0.0,radioEsferaCentral+radioEsferasPequeñas+separacion,0.0);
	glRotated(90,1.0,0.0,0.0);	
	glColor3f(0.0,1.0,0.0); 
	gluSphere(esferaSuperior,radioEsferasPequeñas,meridianosPequeñas,paralelosPequeñas);				//Pintamos la esfera superior.
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(0.0,0.0,radioEsferaCentral+radioEsferasPequeñas+separacion);
	glRotated(90,1.0,0.0,0.0);	
	glColor3f(0.0,0.0,1.0); 
	gluSphere(esferaIzquierda,radioEsferasPequeñas,meridianosPequeñas,paralelosPequeñas);				//Pintamos la esfera izquierda.
	glPopMatrix();	
}

void eliminaPunterosPrimeraParte(){
	gluDeleteQuadric(esferaCentral);
	esferaCentral = NULL;

	gluDeleteQuadric(esferaDerecha);
	esferaDerecha = NULL;

	gluDeleteQuadric(esferaSuperior);
	esferaSuperior = NULL;

	gluDeleteQuadric(esferaIzquierda);
	esferaIzquierda = NULL;
}

void eliminaPunterosSegundaParte(){
	frosty.borra();
}

void dibujaEscenaSegundaParte(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(POS->getX(),0.0,POS->getZ());

		frosty.pinta();

	glPopMatrix();	
}

void muestraConsola1(){
	cout << "En ejecucion: Parte 1." << endl;
}

void muestraConsola2(){
	cout << "En ejecucion: Parte 2." << endl;
	cout << "* \t	- \t DERECHA" << endl;
	cout << "/ \t	- \t IZQUIERDA" << endl;
}

void restauraCamara(){
	c  = new Camara(new PuntoVector3D(eyeX,eyeY,eyeZ,1), new PuntoVector3D(lookX,lookY,lookZ,1), new PuntoVector3D(upX,upY,upZ,1));
}

void cambiarModo(){
	modo = !modo;
	system("cls");
	restauraCamara();

	if(modo){
		muestraConsola1();
		colocaEsferaDelante = false;
	}else
		muestraConsola2();
}

void enciendeApagaP(){
	if(focoPEncendido){
		glDisable(GL_LIGHT0);
		focoPEncendido = false;
	}else{
		glEnable(GL_LIGHT0);
		focoPEncendido = true;
	}		
}

void enciendeApagaOjos(){
	if(ojosMuñeco){
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		ojosMuñeco = false;		
	}else{
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		ojosMuñeco = true;		
	}	
}

void enciendeApagaAmbiental(){
	if(ambiental){
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambApagada);
		ambiental = false;
	}else{
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambEncendida);
		ambiental = true;
	}
}

void colocaEsfera(){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glColor3f(Red.getF1(),Red.getF2(),Red.getF3()); 
	glTranslated(POS->getX()+15,25.0,POS->getZ()+15);
	gluSphere(esferaCentral,radioEsferaCentral,meridianosCentral,paralelosCentral);						//Pintamos la esfera central.
	glPopMatrix();
}

void niebla(){
	if(nieblaActivada){
		nieblaActivada = false;
		glEnable(GL_FOG);
	}else{	
		nieblaActivada = true;
		glDisable(GL_FOG);
	}
}