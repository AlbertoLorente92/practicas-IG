/*	Práctica 1 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __ESCENA_H
#define __ESCENA_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "lapiz.h"
#include "arbol.h"
#include <GL/freeglut.h>

#include <iostream>
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
 - inicializar: int, char[] -> Escena. Modificadora.
 - zoom: GLdouble -> Escena. Modificadora.
 - desarrollaDerecho: Punto, int, Punto, Color -> Escena. Modificadora.
 - desarrollaIzquierdo: Punto, int, Punto, Color -> Escena. Modificadora.
 - anidar: -> Escena. Modificadora.
 - desAnidar: -> Escena. Modificadora.
 - traslacion: char -> Escena. Modificadora.
 - añadirPrimerCuadrado: Cuadrado -> Escena. Modificadora.
 - pinta: -> Escena. Modificadora.
 - pintaCentral: -> Escena. Modificadora.
 - seleccionar: Punto -> Escena. Modificadora.

 */
class Escena {

public:
	//Constructura:

	Escena(){}

	Escena(int w,int h,GLdouble xl,GLdouble xr,GLdouble yb,GLdouble yt){
		_WIDTH = w;
		_HEIGHT = h;
		_xLeft = xl;
		_xRight = xr;
		_yBot = yb;
		_yTop = yt;
		_central=Punto ((_xRight+_xLeft)/2.0,(_yTop+_yBot)/2.0);
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

		_primero=true;
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
		Anida un nuevo cuadrado sobre el cuadrado anterior en la arista derecha del triangulo.
		Dado un punto de desarrollo del nuevo cuadrado, el punto anterior (en la consecución del cuadrado) y
		el nivel del cuadrado anterior dibuja un nuevo cuadrado con su propio nivel	y color.
	*/
	void desarrollaDerecho(Punto p,int nivel,Punto pAnterior,GLdouble anguloDelUsuario){
		Color color;
		Lapiz l;
		Punto p2,p3,p4;
		GLdouble seno = sin(anguloDelUsuario * M_PI / 180.0);
		GLdouble ancho = (p.distancia(pAnterior)) *  seno;
		l.moveTo(p,true);
		GLdouble result = atan2 (p.y()-pAnterior.y(),p.x()-pAnterior.x()) * 180 / M_PI;
		GLdouble alpha = 90 - anguloDelUsuario;
		l.turnTo(result-alpha);
		l.forward(ancho,true);
		p2 = l.getPos();
		l.turn(90);
		l.forward(ancho,true);
		p3 = l.getPos();
		l.turn(90);
		l.forward(ancho,true);
		p4 = l.getPos();
		Cuadrado nuevo(p4,p,p2,p3);
		color.difuminar(nivel);
		nuevo.setColor(color);
		nuevo.setNivel(nivel);
		_temporal.ponDr(nuevo);
	}

	/**
		Anida un nuevo cuadrado sobre el cuadrado anterior en la arista izquierda del triangulo.
		Dado un punto de desarrollo del nuevo cuadrado, el punto anterior (en la consecución del cuadrado) y
		el nivel del cuadrado anterior dibuja un nuevo cuadrado con su propio nivel y color.
	*/
	void desarrollaIzquierdo(Punto p,int nivel,Punto pAnterior,GLdouble anguloDelUsuario){
		Color color;
		Lapiz l;
		Punto p2,p3,p4;
		GLdouble coseno = cos(anguloDelUsuario * M_PI / 180.0);
		GLdouble ancho = (p.distancia(pAnterior)) * coseno;
 		l.moveTo(p,true);
		GLdouble result = atan2 (p.y()-pAnterior.y(),p.x()-pAnterior.x()) * 180 / M_PI;
		GLdouble alpha = 90 + (90-anguloDelUsuario);
		l.turnTo(result-alpha);
		l.forward(ancho,true);
		p2 = l.getPos();
		l.turn(90);
		l.forward(ancho,true);
		p3 = l.getPos();
		l.turn(90);
		l.forward(ancho,true);
		p4 = l.getPos();
		Cuadrado nuevo(p,p2,p3,p4);
		color.difuminar(nivel);
		nuevo.setColor(color);
		nuevo.setNivel(nivel);
		_temporal.ponDr(nuevo);
	}

	/**
		Metodo general que sobre la frontera establecida del arbol anida una nueva frontera dibujando dos nuevos
		cuadrado por cada uno antiguo.
	*/
	void anidar(GLdouble anguloDelUsuario){
		Lista<Cuadrado> ultimoNivel = a.getFrontera();
		Lista<Cuadrado>::Iterador it = ultimoNivel.principio();

		while(it != ultimoNivel.final()){
			Cuadrado c = it.elem();
			Punto p4 = c.getP4();
			Punto p3 = c.getP3();
			Punto p2 = c.getP2();
			int nivel = c.getNivel();

	
			desarrollaDerecho(p3,nivel+1,p2,anguloDelUsuario);
			desarrollaIzquierdo(p4,nivel+1,p3,anguloDelUsuario);

			it.avanza();
		}

		if(_primero){
			_primero=false;
		}else{
			Lista<Cuadrado> l = a.getArchivados();
			Lista<Cuadrado> listaFront = a.getFrontera();
			it = listaFront.principio();
			Cuadrado c;

			while(it != listaFront.final()){
				c = it.elem();
				l.ponDr(c);
				it.avanza();
			}

			a.setArchivados(l);
		}

		a.setFrontera(_temporal);

		while(_temporal.numElems()>0){
			_temporal.resto();
		}

	}
	
	/**
		Borra la ultima frontera establecida (retrocede en el anidamiento).
		Nunca borrara el primer cuadrado de todos.
	*/
	void desAnidar(){
		Lista<Cuadrado> ultimoNivel = a.getArchivados();
		Lista<Cuadrado> nuevaFrontera;
		Cuadrado c = ultimoNivel.ultimo();
		int nivel = c.getNivel();
		double eliminar = pow(2,nivel);

		while(eliminar>0){
			c=ultimoNivel.ultimo();
			nuevaFrontera.ponDr(c);
			ultimoNivel.inicio();
			eliminar--;
		}

		a.setArchivados(ultimoNivel);
		a.setFrontera(nuevaFrontera);
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
		Añade el primer cuadrado al area visible de la escena (este metodo solo se ejecuta 1 vez).
	*/
	void añadirPrimerCuadrado(Cuadrado c){
		Lista<Cuadrado> l;
		c.setNivel(0);
		c.setColor(Color (0.5f,0.4f,0.05f));
		l.ponDr(c);
		a.setArchivados(l);	
		a.setFrontera(l);
	}

	/**
		Pinta el punto central del area visible de la escena y pinta el arbol.
	*/
	void pinta(){
		pintaCentral();
		a.pinta();
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

	/**
		Metodo que indica que cuadrado ha sido seleccionado en el area visible de la escena por el raton del
		usuario.

		Si el cuadrado estaba previamente seleccionado vuelve a su color original.
	*/
	void seleccionar(Punto p){
		Color negro(0.0,0.0,0.0);
		bool copiaArchivado = false, copiaFrontera = false;
		GLdouble prodEscalar;
		bool estaDentro;
		Punto vAlPuntoP;
		//GLdouble epsilon;
		Cuadrado c;
		Lista<Cuadrado> frontera = a.getFrontera();
		Lista<Cuadrado> archivados = a.getArchivados();
		Lista<Cuadrado>::Iterador it = archivados.principio();
		
		bool recta12;
		bool recta23;
		bool recta34;
		bool recta41;

		//While para recorrer la lista de archivados
		while(it != archivados.final() && !copiaArchivado){
			estaDentro = true;
			c = it.elem();
			Punto p1 = c.getP1();
			Punto p2 = c.getP2();
			Punto p3 = c.getP3();
			Punto p4 = c.getP4();
			recta12 = true;
			recta23 = true;
			recta34 = true;
			recta41 = true;

			/////////////
			
			Punto vNormalALarectaP1P2(p2.y()-p1.y(),(p1.x()-p2.x()));
			vAlPuntoP = Punto (p.x()-p1.x(),p.y()-p1.y());
			prodEscalar = vNormalALarectaP1P2.x() * vAlPuntoP.x() + vNormalALarectaP1P2.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta12 = false;

			Punto vNormalALarectaP2P3(p3.y()-p2.y(),(p2.x()-p3.x()));
			vAlPuntoP = Punto (p.x()-p2.x(),p.y()-p2.y());
			prodEscalar = vNormalALarectaP2P3.x() * vAlPuntoP.x() + vNormalALarectaP2P3.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta23 = false;
			
			Punto vNormalALarectaP3P4(p4.y()-p3.y(),(p3.x()-p4.x()));
			vAlPuntoP = Punto (p.x()-p3.x(),p.y()-p3.y());
			prodEscalar = vNormalALarectaP3P4.x() * vAlPuntoP.x() + vNormalALarectaP3P4.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta34 = false;
			
			Punto vNormalALarectaP4P1(p1.y()-p4.y(),(p4.x()-p1.x()));
			vAlPuntoP = Punto (p.x()-p4.x(),p.y()-p4.y());
			prodEscalar = vNormalALarectaP4P1.x() * vAlPuntoP.x() + vNormalALarectaP4P1.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta41 = false;
			
			estaDentro = recta12 && recta23 && recta34 && recta41;
			
			//////////////////
			if(estaDentro){
				copiaArchivado=true;
				Color caux = c.getColor();
				if(caux.esNegro()){
					caux.difuminar(c.getNivel());
					c.setColor(caux);
					it.pon(c);
				}else{
					c.setColor(negro);
					it.pon(c);				
				}
			}
		
			it.avanza();

		}

		if(copiaArchivado==true)
			a.setArchivados(archivados);

		it = frontera.principio();

		while(it != frontera.final() && !copiaArchivado && !copiaFrontera){
			estaDentro = true;
			c = it.elem();
			Punto p1 = c.getP1();
			Punto p2 = c.getP2();
			Punto p3 = c.getP3();
			Punto p4 = c.getP4();

			recta12 = true;
			recta23 = true;
			recta34 = true;
			recta41 = true;
			/////////////

			Punto vNormalALarectaP1P2(p2.y()-p1.y(),(p1.x()-p2.x()));
			vAlPuntoP = Punto (p.x()-p1.x(),p.y()-p1.y());
			prodEscalar = vNormalALarectaP1P2.x() * vAlPuntoP.x() + vNormalALarectaP1P2.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta12 = false;

			Punto vNormalALarectaP2P3(p3.y()-p2.y(),(p2.x()-p3.x()));
			vAlPuntoP = Punto (p.x()-p2.x(),p.y()-p2.y());
			prodEscalar = vNormalALarectaP2P3.x() * vAlPuntoP.x() + vNormalALarectaP2P3.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta23 = false;
			
			Punto vNormalALarectaP3P4(p4.y()-p3.y(),(p3.x()-p4.x()));
			vAlPuntoP = Punto (p.x()-p3.x(),p.y()-p3.y());
			prodEscalar = vNormalALarectaP3P4.x() * vAlPuntoP.x() + vNormalALarectaP3P4.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta34 = false;
			
			Punto vNormalALarectaP4P1(p1.y()-p4.y(),(p4.x()-p1.x()));
			vAlPuntoP = Punto (p.x()-p4.x(),p.y()-p4.y());
			prodEscalar = vNormalALarectaP4P1.x() * vAlPuntoP.x() + vNormalALarectaP4P1.y() * vAlPuntoP.y();
			if(prodEscalar>0)
				recta41 = false;
			
			estaDentro = recta12 && recta23 && recta34 && recta41;
			//////////////////
			if(estaDentro){
				copiaFrontera=true;
				Color caux = c.getColor();
				if(caux.esNegro()){
					caux.difuminar(c.getNivel());
					c.setColor(caux);
					it.pon(c);
				}else{
					c.setColor(negro);
					it.pon(c);
				}
			}
		
			it.avanza();

		}

		if(copiaFrontera==true)
			a.setFrontera(frontera);
		
	}

private:
	bool _primero;
	Lista<Cuadrado> _temporal;
	Punto _central;
	Arbol a;

	// Viewport size
	int _WIDTH, _HEIGHT;

	// Scene visible area size
	GLdouble _xLeft, _xRight, _yBot, _yTop;

};

#endif // __ESCENA_H