/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __ESCENA_H
#define __ESCENA_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>


#include "circunferencia.h"
#include "triangulosCapa.h"
#include <GL/freeglut.h>

#include <iostream>
#include "obstaculos.h"
using namespace std;
/**
 Implementación del TAD Escena.

 Las operaciones son:

 - Escena: -> Escena. Generadora. 

 Getters:
 - getWidth: -> int. Observadora.
 - getHeight: -> int. Observadora.
 - getXLeft: -> GLdouble. Observadora.
 - getXRight: -> GLdouble. Observadora.
 - getYBot: -> GLdouble. Observadora.
 - getYTop: -> GLdouble. Observadora.

 Setters:
 - setWidth: int -> void. Modificadora.
 - setHeight: int -> void. Modificadora.
 - setXLeft: GLdouble -> void. Modificadora.
 - setXRight: GLdouble -> void. Modificadora.
 - setYBot: GLdouble -> void. Modificadora.
 - setYTop: GLdouble -> void. Modificadora.

 Metodos:
		Publicos.
 - inicializar: int, char[] -> Escena. Modificadora.
 - step: -> void. Modificadora.
 - zoom: GLdouble -> Escena. Modificadora.
 - traslacion: char -> Escena. Modificadora.
 - pinta: -> Escena. Modificadora.
		Privados.
 - añadirPelota: -> void. Modificadora.
 - dibujaObstaculos: -> void. Modificadora.
 - pedirRadio: -> GLdouble. 
 - pedirDireccion: GLdouble -> Punto. 
 - pedirPunto: -> Punto. 
 - pintaCentral: -> Escena. Modificadora.

 */
class Escena {

public:
	//Constructura:

	static const int NUMOBSTACULOS = 10;
	/**
		0,1,2,3 triangulos frontera
		4,5.6 triangulos en el area visible de la escena
		7,8,9 circunferencias en el area visible de la escena
	*/

	Escena(){}

	Escena(int w,int h,GLdouble xl,GLdouble xr,GLdouble yb,GLdouble yt){
		_WIDTH = w;
		_HEIGHT = h;
		_xLeft = xl;
		_xRight = xr;
		_yBot = yb;
		_yTop = yt;
		_central=Punto ((_xRight+_xLeft)/2.0,(_yTop+_yBot)/2.0);
		_obs = new Obstaculos*[NUMOBSTACULOS];
		añadirPelota();
		dibujaObstaculos();
	}

	//Getters:
	/**
		Devuelve el ancho de la escena.
	*/
	int getWidth(){
		return _WIDTH;
	}

	/**
		Devuelve el altp de la escena.
	*/
	int getHeight(){
		return _HEIGHT;
	}

	/**
		Devuelve la coordenada X izquierda.
	*/
	GLdouble getXLeft(){
		return _xLeft;
	}

	/**
		Devuelve la coordenada X derecha.
	*/
	GLdouble getXRight(){
		return _xRight;
	}

	/**
		Devuelve la coordenada Y inferior.
	*/
	GLdouble getYBot(){
		return _yBot;
	}

	/**
		Devuelve la coordenada Y superior.
	*/
	GLdouble getYTop(){
		return _yTop;
	}

	//Setters:
	/**
		Establece un nuevo ancho de la escena.
	*/
	void setWidth(int a){
		_WIDTH = a;
	}

	/**
		Establece un nuevo alto de la escena.
	*/
	void setHeight(int a){
		_HEIGHT = a;
	}

	/**
		Establece un nueva coordenada X izquierda.
	*/
	void setXLeft(GLdouble a){
		_xLeft = a;
	}

	/**
		Establece un nueva coordenada X derecha.
	*/
	void setXRight(GLdouble a){
		_xRight = a;
	}

	/**
		Establece un nueva coordenada Y inferior.
	*/
	void setYBot(GLdouble a){
		_yBot = a;
	}

	/**
		Establece un nueva coordenada Y superior.
	*/
	void setYTop(GLdouble a){
		_yTop = a;
	}

	//Metodos:
	/**
		Inicializa la Escena y la ventana del Freeglut.
	*/
	void inicializar(int argc, char *argv[]){

		glutInitWindowSize(_WIDTH, _HEIGHT);
		glutInitWindowPosition (140, 140);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
		glutInit(&argc, argv);
		int my_window; //my window's identifier
		//Window construction
		my_window = glutCreateWindow( "Freeglut 2D-project" );
	}

	/**
		Método step encargado de avanzar la pelota segun su vector movimiento y hacerla chocar contra los obstaculos.
	*/
   	void step() {
		double nHit /*= DBL_MAX*/;
		double tMin = 1.5;
		Punto tHit;
		Punto tHitFuc/*(0,0)*/;

		//_vColisionMultiple = new Punto[NUMOBSTACULOS];
		ponerACero();
		int numColisionesMultiples = 0;
		bool colisionMultiple = false;
		bool primeraVez = true;

		double epsilon;
		double epsilonExtremo;
		
		for(int i = 0; i < NUMOBSTACULOS; i++){
			nHit = DBL_MAX;
			tHitFuc = Punto(0,0);
			if(_obs[i]->intersecionConRecta(_pelota,nHit,tHitFuc)){			
				//hay colision
				epsilon = nHit * 0.1;
				epsilonExtremo = nHit * 0.0000000000001; //<--FLIPA!!

				if(nHit>=(-epsilon) && (nHit <= (1+epsilon))){
					if((tMin-epsilonExtremo)<=nHit && nHit<=(tMin+epsilonExtremo)){					
						colisionMultiple=true;
						if(primeraVez){
							_vColisionMultiple[numColisionesMultiples]=tHit;
							numColisionesMultiples++;
							primeraVez=false;
						}
						introducir(tHitFuc,numColisionesMultiples);
					}else{
						if(tMin > nHit){
							colisionMultiple=false;
							numColisionesMultiples=0;
							primeraVez=true;

							tMin = nHit;
							tHit = tHitFuc;
						}
					}
				}
			}
		}

		if(colisionMultiple){
			Punto rebotar = calculaNormal(numColisionesMultiples).normalizar();
			_pelota.rebote(rebotar);
		}else{
			if(0<=tMin && tMin<1.0){	
				_pelota.rebote(tHit);
				_pelota.avanzaPelota(1.0-tMin);
			}else{
				_pelota.avanzaPelota(1.0);
			}
		}

			
	}

	/**
		Realiza un zoom positivo o negativo centrado sobre el area visible de la escena dependiendo del parametro 'factor'.
	*/
	void zoom(GLdouble factor){
		GLdouble centroX = (_xRight+_xLeft)/2.0;	//Calculamos el centro antiguo del eje de las x
		GLdouble centroY = (_yTop+ _yBot )/2.0;		//Calculamos el centro antiguo del eje de las y 
		GLdouble anchoNew, altoNew;
		GLdouble ancho = _xRight-_xLeft;			//Ancho antiguo
		GLdouble alto = _yTop-_yBot;				//Alto antiguo 

		GLdouble fAux= 1 + factor;
		anchoNew= ancho/fAux;						//Nuevo ancho
		altoNew = alto/fAux;						//Nuevo alto

		//Nueva area visible de la escena
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(centroX-anchoNew/2.0,centroX+anchoNew/2.0,centroY-altoNew/2.0,centroY+altoNew/2.0);

		_xRight = centroX + anchoNew/2.0;
		_xLeft = centroX - anchoNew/2.0;
		_yTop = centroY + altoNew/2.0;
		_yBot  = centroY - altoNew/2.0;
	}

	/**
		Mueve el area visible de la escena segun el usuario lo requiera
	*/
	void traslacion(char key){
		switch (key){
			case '6'://DERECHA
				_xLeft += 10;
				_xRight += 10;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(_xLeft, _xRight, _yBot, _yTop);
			break;

			case '2'://ABAJO
				_yTop -= 10;
				_yBot -= 10;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(_xLeft, _xRight, _yBot, _yTop);
			break;

			case '4'://IZQUIERDA
				_xLeft -= 10;
				_xRight -= 10;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(_xLeft, _xRight, _yBot, _yTop);
			break;

			case '8'://ARRIBA
				_yTop += 10;
				_yBot += 10;
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				gluOrtho2D(_xLeft, _xRight, _yBot, _yTop);
			break;

		}
		glutPostRedisplay();
	}


	/**
		Pinta el punto central del area visible de la escena y pinta el arbol.
	*/
	void pinta(){
		pintaCentral();

		_pelota.pinta();

		for(int i = 0; i < NUMOBSTACULOS; i++){
			_obs[i]->pinta();
		}
	}

private:	
	//Metodos privados de la clase escena.
	/**
		Introduce una nueva normal de colision multiple SI Y SOLO SI esa normal es distinta a las que ya estaban en el vector
	*/
	void introducir(Punto p,int& posicion){
		bool b = true;

		for(int i = 0; i < NUMOBSTACULOS && b; i++){
			if(_vColisionMultiple[i].esIgual(p))
				b=false;
		}

		if(b){
			_vColisionMultiple[posicion]=p;
			posicion++;
		}
	}

	/**
		Devuelve el angulo y las normales que lo componen para formar la normal de la colision multiple
	*/
	GLdouble anguloMayor(int numColisionesMultiples,Punto& n1,Punto& n2){
		GLdouble angulo=0;
		n1 = Punto(0,0);
		n2 = Punto(0,0);

		for(int i = 0; i < numColisionesMultiples; i++){
			for(int j = i + 1; j < numColisionesMultiples; j++){
				if(_vColisionMultiple[i].anguloEntreV1V2(_vColisionMultiple[j])>angulo){
					angulo = _vColisionMultiple[i].anguloEntreV1V2(_vColisionMultiple[j]);
					n1 = _vColisionMultiple[i];
					n2 = _vColisionMultiple[j];
				}
			}
		}

		return angulo;
	}

	/**
		Calcula la normal en caso de colision multiple
	*/
	Punto calculaNormal(int numColisionesMultiples){
		Punto n1,n2;
		GLdouble angulo = anguloMayor(numColisionesMultiples,n1,n2);

		Punto normal = n1.suma(n2);

		return normal;
	}

	/**
		Pone Puntos(0,0) en todo el vector 
	*/
	void ponerACero(){
		for(int i = 0; i < NUMOBSTACULOS; i++){
			_vColisionMultiple[i]=Punto(0,0);
		}
	}

	/**
		Añade la pelota al area visible de la escena.
	*/
	void añadirPelota(){
		
		//Podemos pedir los datos al usuario...
		//Punto inicio = pedirPunto();
		//GLdouble radio = pedirRadio(5.0);			
		//Punto direccion = pedirDireccion();		

		float c1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float c2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float c3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		Color color(c1,c2,c3);

		Punto inicio = Punto(975,25);		
		GLdouble radio = 20;
		Punto direccion = Punto(-5,5);
		
		_pelota = Pelota(inicio,radio,direccion,color);	

		/*Punto inicio = Punto(980,480);			// Forzamos una interseccion Triangulo-Triangulo
		GLdouble radio = 20;
		Punto direccion = Punto(5.0,5.0);
		
		_pelota = Pelota(inicio,radio,direccion,color);		*/

		/*Punto inicio = Punto(235,185);			// Forzamos una interseccion Circunferencia-Circunferencia
		GLdouble radio = 20;
		Punto direccion = Punto(-5.0,0);

		_pelota = Pelota(inicio,radio,direccion,color);	   */

		/*Punto inicio = Punto(100,310);			// Forzamos una interseccion Circunferencia-Triangulo
		GLdouble radio = 20;
		Punto direccion = Punto(-5,-5);
		
		_pelota = Pelota(inicio,radio,direccion,color);		 */
	}

	/**
		Añade los triangulos y circunferencias que formaran los obstaculos contra los que chocará la pelota.
	*/
	void dibujaObstaculos(){
		TrianguloCapa* bordes;
		Circunferencia* c;
		//Triangulo* t;

		//Triangulo derecho
		bordes = new TrianguloCapa(Punto(_xRight,-200),Punto(_xRight+(_xRight/2.0),_yTop/2.0),Punto(_xRight,_yTop+200),_pelota.getRadio());		
		_obs[0]=bordes;

		//Triangulo superior
		bordes = new TrianguloCapa(Punto(-200,_yTop),Punto(_xRight+200,_yTop),Punto(_xRight/2.0,_yTop+(_yTop/2.0)),_pelota.getRadio());	
		_obs[1]=bordes;

		//Triangulo izquierdo
		bordes = new TrianguloCapa(Punto(-(_xRight/2.0),(_yTop/2.0)),Punto(0,-200),Punto(0,_yTop+200),_pelota.getRadio());	
		_obs[2]=bordes;

		//Triangulo inferior
		bordes = new TrianguloCapa(Punto((_xRight/2.0),-(_yTop/2.0)),Punto(_xRight+200,0),Punto(-200,0),_pelota.getRadio());	
		_obs[3]=bordes;

		//////////////Triangulos del area visible de la escena
		bordes = new TrianguloCapa (Punto(520,100),Punto(650,250),Punto(520,400),_pelota.getRadio());
		_obs[4]=bordes;
		bordes = new TrianguloCapa (Punto(470,100),Punto(470,400),Punto(200,400),_pelota.getRadio());
		_obs[5]=bordes;
		bordes = new TrianguloCapa (Punto(800,260),Punto(900,260),Punto(850,350),_pelota.getRadio());
		_obs[6]=bordes;

		//////////////Circunferencias
		c = new Circunferencia (Punto(300,185),20,_pelota.getRadio()+20);
		_obs[7]=c;
		c = new Circunferencia (Punto(100,220),70,_pelota.getRadio()+70);
		_obs[8]=c;
		c = new Circunferencia (Punto(100,150),70,_pelota.getRadio()+70);
		_obs[9]=c;

		//////////////Mas triangulos
		/*t = new Triangulo (Punto(1200,200),Punto(1200,760),Punto(760,760));
		_obs[10]=t;

		t = new Triangulo (Punto(100,280),Punto(100,340),Punto(0,310));
		_obs[11]=t;	  */
	}

	/**
		Pide al usuario el radio de la pelota.
	*/
	GLdouble pedirRadio(){
		GLdouble radio;

		cout << "Introduzca radio del circulo: ";

		do{
			cin >> radio;
		}while(radio<=0);

		cout << endl;

		return radio;
	}

	/**
		Pide una direccion (expresada en angulos) dada una fuerza.
	*/
	Punto pedirDireccion(GLdouble fuerza){
		GLdouble angulo;			//HACER RANDOM
		cout << "Indique la direccion de la pelota (en grados): ";
		cin >> angulo;

		cout << endl;

		angulo = angulo * M_PI / 180;

		GLdouble descomposicionEnX = cos(angulo) * fuerza;
		GLdouble descomposicionEnY = sin(angulo) * fuerza;

		return Punto(descomposicionEnX,descomposicionEnY);
	}

	/**
		Pide al usuario 2 coordenadas x e y para formar el vector direccion de la pelota.
	*/
	Punto pedirPunto(){
		GLdouble x,y;

		do{
			cout << "Indique la coordenada x del punto inicial: ";
			cin >> x;
		}while(x<0 || x>_WIDTH);

		cout << endl;

		do{
			cout << "Indique la coordenada y del punto inicial: ";
			cin >> y;
		}while(y<0 || y>_HEIGHT);

		cout << endl;

		return Punto(x,y);
	}

	/**
		Pinta el punto central del area visible de la escena.
	*/
	void pintaCentral(){
		glBegin ( GL_POINTS ) ;
			glColor3f(1.0,0.0,0.0);
			glVertex2d( _central.x(), _central.y());
		glEnd () ;
	}

	//Atributos privados.

	Punto _central;

	Pelota _pelota;

	Obstaculos** _obs;

	Punto _vColisionMultiple[NUMOBSTACULOS];

	// Viewport size
	int _WIDTH, _HEIGHT;

	// Scene visible area size
	GLdouble _xLeft, _xRight, _yBot, _yTop;

};

#endif // __ESCENA_H