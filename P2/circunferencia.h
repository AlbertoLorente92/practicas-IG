/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __CIRCUNFERENCIA_H
#define __CIRCUNFERENCIA_H

#include "obstaculos.h"

#include <math.h>
#include <GL/freeglut.h>
using namespace std;
/**
 Implementación del TAD Circunferencia.

 Las operaciones son:

 - Circunferencia: Punto, GLdouble -> Circunferencia. Generadora.

 Metodos:
			Publicos.
 - intersecionConRecta: Pelota, double, Punto -> double, Punto. Modificadora.
 - pinta: -> void. Modificadora.
			Privados.
 - dameSigno: GLdouble -> GLdouble. Observadora.
 - calculaContorno: -> void. Observadora.
 */

class Circunferencia: public Obstaculos {
public:

	static const int NUMLADOS = 50;

	//Constructora:
	/**
		Constructora de la clase Punto con parametros.
	*/
	Circunferencia(const Punto centro,const GLdouble radio,GLdouble radioChoque){
		_centro = centro;
		_radio = radio;
		_color = Color(0.0f,0.0f,0.0f);
		_radioChoque = radioChoque;
		calculaContorno();
	}

	Circunferencia(){}

	/**
		Pinta la pelota.
	*/
	void Obstaculos::pinta(){
		Color c = _color;

		glBegin ( GL_LINE_STRIP ) ;
			glColor3f(_color.getF1(),_color.getF2(),_color.getF3());
			
			for(int i = 0; i < NUMLADOS; i++){
				glVertex2d( _contorno[i].x(), _contorno[i].y());
			}
			glVertex2d( _contorno[0].x(), _contorno[0].y());	
		glEnd () ;

		glBegin ( GL_LINE_STRIP ) ;
			glColor3f(_color.getF1(),_color.getF2(),_color.getF3());
			
			for(int i = 0; i < NUMLADOS; i++){
				glVertex2d( _contornoChoque[i].x(), _contornoChoque[i].y());
			}
			glVertex2d( _contornoChoque[0].x(), _contornoChoque[0].y());	
		glEnd () ;

		glBegin ( GL_POINTS ) ;
			glColor3f(_color.getF1()+0.5f,_color.getF2(),_color.getF3());			
			glVertex2d( _centro.x(), _centro.y());				
		glEnd () ;
	}

	bool Obstaculos::intersecionConRecta(Pelota p,double& tIn, Punto& normalIn){
		bool interseccion = false;
		GLdouble a = p.getVectorMovimiento().productoEscalar(p.getVectorMovimiento());
		GLdouble b = _centro.dameVector(p.getCentro()).productoEscalar(p.getVectorMovimiento()) * 2;
		GLdouble c = _centro.dameVector(p.getCentro()).productoEscalar(_centro.dameVector(p.getCentro())) - pow(_radioChoque,2);
		GLdouble varianza = pow(b,2) - 4 * (a*c);
		
		GLdouble numInterseciones = dameSigno(varianza);

		if(numInterseciones<0){						//No hay interseccion
			interseccion = false;
		} else if(numInterseciones==0){				//Hay 1 interseccion
			interseccion = true;
			tIn = (- (b) / (2 * a));
			Punto newVecMov = p.getVectorMovimiento().multiplicacion(tIn);
			Punto centroPelotaMasVector = p.getCentro().suma(newVecMov);
			Punto vCentroCirInterseccion = _centro.dameVector(centroPelotaMasVector).normalizar();
			normalIn = vCentroCirInterseccion;
		}else{										//Hay 2 intersecciones
			interseccion = true;
			GLdouble tIn1 = (-b-sqrt(varianza))/(2*a);
			GLdouble tIn2 = (-b+sqrt(varianza))/(2*a);
			tIn = (min(tIn1,tIn2));
			Punto newVecMov = p.getVectorMovimiento().multiplicacion(tIn);
			Punto centroPelotaMasVector = p.getCentro().suma(newVecMov);
			Punto vCentroCirInterseccion = _centro.dameVector(centroPelotaMasVector).normalizar();
			normalIn = vCentroCirInterseccion;
		}

		return interseccion;
	}

private:
	//Metodos:
	/**
		Pinta la pelota.
	*/
	GLdouble dameSigno(GLdouble dist){
		if(dist<0) 
			return -1;
		else if(dist==0)
			return 0;
		else//(dist>0)
			return 1;
	}

	void calculaContorno(){
		Lapiz l,l2;

		Punto aux(_centro.x()+_radio,_centro.y());
		Punto aux2(_centro.x()+_radioChoque,_centro.y());

		GLdouble alpha = 360 / NUMLADOS;
		GLdouble beta = 180 - ((180 - alpha) / 2);
		GLdouble seno = alpha * M_PI /180;

		GLdouble ancho = 2.0 * _radio * sin(seno/2.0);//radianes
		GLdouble anchoChoque = 2.0 * _radioChoque * sin(seno/2.0);//radianes

		l.moveTo(aux,true);
		l.turnTo(beta);

		l2.moveTo(aux2,true);
		l2.turnTo(beta);

		for(int i = 0; i < NUMLADOS; i++){
			_contorno[i]=aux;
			_contornoChoque[i]=aux2;

			l.forward(ancho,true);
			l2.forward(anchoChoque,true);

			aux = l.getPos();
			aux2 = l2.getPos();

			l.turn(alpha);
			l2.turn(alpha);
		}
	}

	Color _color;

	Punto _centro;

	GLdouble _radio;

	GLdouble _radioChoque;

	Punto _contorno[NUMLADOS];

	Punto _contornoChoque[NUMLADOS];
};

#endif // __CIRCUNFERENCIA_H