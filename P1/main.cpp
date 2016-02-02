/*	Práctica 1 - Informática Gráfica (IG)
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
#include "lapiz.h"
#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;

GLdouble ancho;
bool embaldosado;
int numColumnas;
bool primerMouse;	//Impedimos que el usuario pueda dibujar varios arboles
bool anguloPrimeraVez;
GLdouble anguloDelUsuario;

Escena *e = new Escena(500,250,0.0,500.0,0.0,250.0);	//Iniciamos la escena

void intitGL();
void embaldosar();
void display(void);
int pedirColumnas();
void embaldosadoAux();
GLdouble pedirAngulo();
void anidarAux();
void key(unsigned char key, int x, int y);
void resize(int newWidth, int newHeight);
void mouse(int button, int state, int x, int y);
void pedirAncho();
void zoomProgresivo(GLdouble factor, int nIter);

int main(int argc, char *argv[]){
	anguloPrimeraVez = true;
	cout<< "Starting console..." << endl;

	pedirAncho();

	cout << "Comandos:" << endl;
	cout << "\t+ \t->\t Zoom positivo (nos acercamos)" << endl;
	cout << "\t- \t->\t Zoom negativo (nos alejamos)" << endl;
	cout << "\tz \t->\t Zoom progresivo positivo (nos acercamos)" << endl;
	cout << "\tx \t->\t Zoom progresivo negativo (nos alejamos)" << endl;
	cout << "\te \t->\t Embaldosado o Desembaldosar" << endl;
	cout << "\t8 \t->\t Desplazamiento hacia arriba" << endl;
	cout << "\t6 \t->\t Desplazamiento hacia la derecha" << endl;
	cout << "\t2 \t->\t Desplazamiento hacia abajo" << endl;
	cout << "\t4 \t->\t Desplazamiento hacia la izquierda" << endl;
	cout << "'Espacio' \t->\t Anidar" << endl;
	cout << "'Retroceso' \t->\t Desanidar" << endl;

	embaldosado = false;
	primerMouse = true;

	e->inicializar(argc,argv);

	glutReshapeFunc(resize);

	glutMouseFunc(mouse);
	
	glutKeyboardFunc(key);
  
	glutDisplayFunc(display);

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

void embaldosar(){
	GLdouble SVAratio = (e->getXRight() - e->getXLeft()) / (e->getYTop() - e->getYBot());
	GLdouble w = (GLdouble)e->getWidth() / (GLdouble)numColumnas;
	//La altura de cada puerto se calcula proporcionalmente
	GLdouble h = w / SVAratio;
	for(GLint c = 0; c<numColumnas; c++){
		GLdouble currentH = 0;
			while((currentH + h) < e->getHeight()){
				glViewport((GLint)(c*w), (GLint) currentH, (GLint)w , (GLint) h);
				e->pinta();
				currentH += h;
			}//while
	}//for
}


void display(void){
	glClear( GL_COLOR_BUFFER_BIT );//limpia pantalla
	if(embaldosado){
		embaldosar();
	}else{
		glViewport(0, 0,  e->getWidth(), e->getHeight());			
		e->pinta();		//Pintamos la Escena.
	}
	glFlush();
	glutSwapBuffers();
}

int pedirColumnas(){
	int numCol;

	cout << "Introduzca un numero de columnas: " << endl;
	do{
		cin >> numCol;
	}while(numCol<=0);

	return numCol;
}

void embaldosadoAux(){
	if(!embaldosado){
		numColumnas = pedirColumnas();
		embaldosado = true;
	}else{
		embaldosado = false;
	}
}

GLdouble pedirAngulo(){
	GLdouble ang;
	cout << "Introduzca el angulo para anidar: ";

	do{
		cin >> ang;
	}while(ang<=0 && ang>=90);

	cout << endl;

	return ang;
}

void anidarAux(){
	if(anguloPrimeraVez){
		anguloDelUsuario = pedirAngulo();
		anguloPrimeraVez = false;
	}
	e->anidar(anguloDelUsuario);
	display();
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

		case 'z' :				//Nos acercamos de manera progresiva
			zoomProgresivo(0.5,50);
		break ;

		case 'x' :				//Nos alejamos de manera progresiva
			zoomProgresivo(-1.5,50);
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

		case ' ' :				//Ampliamos el arbol
			anidarAux();
		break ;

		case 8:					//Retrocedemos un nivel en el arbol
			e->desAnidar();
			display();
		break ;

		case 'e' :				//Embaldosamos
			embaldosadoAux();
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

void mouse(int button, int state, int x, int y){

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		glClear( GL_COLOR_BUFFER_BIT );//limpia pantalla

		// Obtenemos l as proporciones de la ventana (las ys crecen de hacia abajo pero en escena hacia arriba).
		GLdouble propX = x / (GLdouble)e->getWidth();
		GLdouble propY = 1 - (y / (GLdouble)e->getHeight());
		// Multiplicamos la proporcion del area visible de la escena por si esta ha sido modificada previamente.
		GLdouble posX = (propX * (e->getXRight() - e->getXLeft()) + e->getXLeft()); 
		GLdouble posY = (propY * (e->getYTop() - e->getYBot()) + e->getYBot());

		//Crear punto
		Punto p1(posX,posY);// <--CHAPUZA

		if(primerMouse){	//Si es la primera vez que el usuario hace click en la ventana gráfica

			GLdouble hipotenusa = sqrt(2) * ( ancho / 2.0);	//El cuadrado a dibujar estara centrado sobre el punto que eligio el usuario
			
			//Dibujamos con la clase lapiz el primer cuadrado
			Lapiz lapiz(p1,225);
			lapiz.forward(hipotenusa,true);
			p1 = lapiz.getPos();
			lapiz.turnTo(0);
			lapiz.forward(ancho,true);
			Punto p2(lapiz.getPos());
			lapiz.turn(90);
			lapiz.forward(ancho,true);
			Punto p3(lapiz.getPos());
			lapiz.turn(90);
			lapiz.forward(ancho,true);
			Punto p4(lapiz.getPos());
			Cuadrado c(p1,p2,p3,p4);
			e->añadirPrimerCuadrado(c);
			primerMouse = false;
		}else{								//Si previamente ya se ha empezado la construccion de un arbol de pitagoras 
			e->seleccionar(p1);				//Buscamos el cuadrado seleccionado por el usuario
			display();
		}
			
	}
}

void pedirAncho(){
	cout << "Introduzca ancho del cuadrado: ";
	do{
		cin >> ancho;
	}while(ancho<=0);
	cout << endl << endl;
}

/**
	Realiza un zoom positivo o negativo centrado y progresivo sobre el area visible de la escena dependiendo del parametro 'factor' y de 'nIter'.
*/
void zoomProgresivo(GLdouble factor, int nIter){

	GLdouble fIncr = (1+factor)/nIter; 
	GLdouble centroX = (e->getXRight()+e->getXLeft())/2.0; //Calculamos el centro antiguo del eje de las x
	GLdouble centroY = (e->getYTop() +e->getYBot())/2.0; //Calculamos el centro antiguo del eje de las y 
	GLdouble anchoNew, altoNew;
	GLdouble ancho = e->getXRight()-e->getXLeft(); //Ancho antiguo
	GLdouble alto = e->getYTop()-e->getYBot(); //Alto antiguo
	//Bucle progresivo
	for(int i=0;i<=nIter;i++){
		GLdouble fAux= 1 + fIncr*i;
		anchoNew= ancho/fAux; //Nuevo ancho
		altoNew = alto/fAux; //Nuevo alto

		//Nueva area visible de la escena
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(centroX-anchoNew/2.0,centroX+anchoNew/2.0,centroY-altoNew/2.0,centroY+altoNew/2.0);
			
		/*glClear( GL_COLOR_BUFFER_BIT );//limpia pantalla
		pinta();
		glFlush();
		glutSwapBuffers();*/

		display();

		Sleep(50);
			
	}

	//Actualizamos xLeft,xRight,yBot,yTop
	e->setXRight(centroX + anchoNew/2.0);
	e->setXLeft(centroX - anchoNew/2.0);
	e->setYTop(centroY + altoNew/2.0);
	e->setYBot(centroY - altoNew/2.0);		
}
