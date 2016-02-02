/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>
#include <math.h>

#include "escena.h"
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;

Escena *e = new Escena(1000,500,0.0,1000.0,0.0,500.0);	//Iniciamos la escena

void timer(int n);
void intitGL();
void display(void);
void key(unsigned char key, int x, int y);
void resize(int newWidth, int newHeight);

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	cout << "Comandos:" << endl;
	cout << "\t+ \t->\t Zoom positivo (nos acercamos)" << endl;
	cout << "\t- \t->\t Zoom negativo (nos alejamos)" << endl;
	cout << "\t8 \t->\t Desplazamiento hacia arriba" << endl;
	cout << "\t6 \t->\t Desplazamiento hacia la derecha" << endl;
	cout << "\t2 \t->\t Desplazamiento hacia abajo" << endl;
	cout << "\t4 \t->\t Desplazamiento hacia la izquierda" << endl;
	cout << "'Espacio' \t->\t Mover Las pelotas" << endl;

	e->inicializar(argc,argv);

	glutReshapeFunc(resize);
	
	glutKeyboardFunc(key);
  
	glutDisplayFunc(display);

	timer(1);

	//OpenGL basic setting

	intitGL();

	// Freeglut's main loop can be stopped executing (**)
	//while ( continue_in_main_loop )
	//  glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}

void timer(int n){
	e->step();

   //Despues de 100ms vuelve a llamar a la función timer
	glutTimerFunc(30,timer,n);
	display();
}

void intitGL(){
	glClearColor(1.0,1.0,1.0,1.0);//color para limpiar la ventana
	glColor3f(1.0,0.0,0.0); //color con el q vamos a pintar
	
	glPointSize(4.0);//tamaño punto
	glLineWidth(2.0);//grosor lineas

	// Viewport
	glViewport(0, 0, e->getWidth(), e->getHeight());//matriz del punto de vista (area cliente de la ventana)
    //puede ternerse varios puertos de vista (esquina inferior izquierda)

	// Model transformation
    glMatrixMode(GL_MODELVIEW);//Inicializa la matriz de modelado y vista (identidad)
    glLoadIdentity();
	
    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);//matriz de proyección
    glLoadIdentity();
	gluOrtho2D(e->getXLeft(),e->getXRight(),e->getYBot(),e->getYTop()); //configura el area visible de la escena
 }

void display(void){
	glClear( GL_COLOR_BUFFER_BIT );//limpia pantalla
		
	e->pinta();		//Pintamos la Escena.

	glFlush();
	glutSwapBuffers();
}

void key(unsigned char key, int x, int y){

	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
		break;

		case '+' :				//Nos acercamos
			e->zoom(0.2);
			display();
		break ;

		case '-' :				//Nos alejamos
			e->zoom(-0.2);
			display();
		break ;

		case '6' :				//Nos movemos hacia la derecha
			e->traslacion(key);
		break ;

		case '2' :				//Nos movemos hacia abajo
			e->traslacion(key);
		break ;

		case '4' :				//Nos movemos hacia la izquierda
			e->traslacion(key);
		break ;

		case '8' :				//Nos movemos hacia arriba
			e->traslacion(key);
		break ;

		case ' ' :				//Avanza la pelota
			e->step();
			display();
		break ;

		default:
		break;
	}
}

void resize(int newWidth, int newHeight){
	//Resize Viewport
	e->setWidth(newWidth);
	e->setHeight(newHeight);
	GLdouble RatioViewPort= (float)e->getWidth()/(float)e->getHeight();
	glViewport ( 0, 0, e->getWidth(), e->getHeight() ) ;
  
	//Resize Scene Visible Area 
	//Se actualiza el área visible de la escena
	//para que su ratio coincida con ratioViewPort
	GLdouble SVAWidth= (e->getXRight())-(e->getXLeft());
	GLdouble SVAHeight= e->getYTop()-e->getYBot();
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {
		// Increase SVAHeight
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( e->getYBot()+e->getYTop() )/2.0;
		e->setYTop(yMiddle + newHeight/2.0);
		e->setYBot(yMiddle - newHeight/2.0);
	}else{
		//Increase SVAWidth
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( e->getXLeft()+e->getXRight())/2.0;
		e->setXRight(xMiddle + newWidth/2.0);
		e->setXLeft(xMiddle - newWidth/2.0);
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(e->getXLeft(), e->getXRight(), e->getYBot(), e->getYTop());
}