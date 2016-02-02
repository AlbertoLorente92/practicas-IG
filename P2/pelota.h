/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __PELOTA_H
#define __PELOTA_H

#include "color.h"
#include "lapiz.h"
#include <math.h>
#include <GL/freeglut.h>

/**
 Implementación del TAD Pelota.

 Las operaciones son:

 - Pelota: Punto,GLdouble,Punto,Color -> Pelota. Generadora.

 Getters:
 - getCentro: -> Punto. Observadora.
 - getVectorMovimiento: -> Punto. Observadora.
 - getRadio: -> GLdouble. Observadora.
 - getColor: -> Color. Observadora.

 Setters:
 - setCentro: Punto -> void. Modificadora.
 - setVectorMovimiento: Punto -> void. Modificadora.
 - setRadio: GLdouble -> void. Modificadora.
 - setColor: Color -> void. Modificadora.

 Metodos:
			Publicos.
 - pinta: -> void. Observadora
 - avanzaPelota: GLdouble -> void. Modificadora.
 - rebote: Punto -> void: Modificadora.
			Privados.
 - calculaLados: GLdouble -> int. Modificadora.
 */
class Pelota {
public:

	static const int NUMLADOS = 50;

	//Constructora:
	/**
		Constructora de la clase Punto con parametros.
	*/
	Pelota(const Punto centro,const GLdouble radio,const Punto vectorMov,const Color color){
		_centro = centro;
		_radio = radio;
		_vectorMov = vectorMov;
		_color = color;
		calculaContorno();		
	}

	Pelota(){}

	//Getters:
	/**
		Devuelve el centro de la pelota.
	*/
	Punto getCentro() const{
		return _centro;
	}

	/**
		Devuelve el vector de movimiento de la pelota.
	*/
	Punto getVectorMovimiento() const{
		return _vectorMov;
	}

	/**
		Devuelve el radio de la pelota.
	*/
	GLdouble getRadio() const{
		return _radio;
	}

	/**
		Devuelve el color de la pelota.
	*/
	Color getColor() const{
		return _color;
	}

	//Setters:
	/**
		Cambia el centro de la pelota.
	*/
	void setCentro(Punto centro){
		_centro = centro;
	}

	/**
		Cambia el vector de movimiento de la pelota.
	*/
	void setVectorMovimiento(Punto vector){
		_vectorMov = vector;
	}

	/**
		Cambia el radio de la pelota.
	*/
	void setRadio(GLdouble radio){
		_radio = radio;
	}

	/**
		Cambia el color de la pelota.
	*/
	void setColor(Color color){
		_color = color;
	}

	//Metodos:
	/**
		Pinta la pelota.
	*/
	void pinta(){
		glBegin ( GL_POLYGON ) ;
			glColor3f(_color.getF1(),_color.getF2(),_color.getF3());
			
			for(int i = 0; i < NUMLADOS; i++){
				glVertex2d( _contorno[i].x(), _contorno[i].y());				
			}

		glEnd () ;

		glBegin ( GL_POINTS ) ;
			glColor3f(0.0f,0.0f,0.0f);
			
			glVertex2d( _centro.x(), _centro.y());				
		glEnd () ;
	}

	/**
		Avanza la pelota segun su vector de movimiento
	*/
	void avanzaPelota(double tMin){
		if(tMin!=0){
			_centro = _centro.suma(_vectorMov.multiplicacion(tMin));

			for(int i = 0 ; i < NUMLADOS ; i++ ){
				_contorno[i] = _contorno[i].suma(_vectorMov.multiplicacion(tMin));
			}
		}
	}

	/**
		Modifica el vector direccion segun el vector de la normal de la recta con la que choca
	*/
 	void rebote(Punto Normal){
		Punto aux = Normal;
		
		// producto escalar de la trayectoria con la normal
		GLdouble pe = abs(aux.productoEscalar(_vectorMov));

		aux = aux.multiplicacion(pe);
		aux = aux.multiplicacion(2);

		//sumamos el aux a la direccion actual

		if(_vectorMov.suma(aux).modulo()!=_vectorMov.modulo()){
			GLdouble error = _vectorMov.modulo() - (_vectorMov.suma(aux).modulo());
			aux = aux.ajustaModulo(error);
			_vectorMov = _vectorMov.suma(aux);
			//_vectorMov = _vectorMov.normalizar();
		}else{
			_vectorMov = _vectorMov.suma(aux);
		}
	}
	
private:
	//Metodos privados:
	/**
		Rellena el array de puntos del contorno.	
	*/
	void calculaContorno(){
		Lapiz l;
		Punto aux(_centro.x()+_radio,_centro.y());
		GLdouble alpha = 360 / NUMLADOS;
		GLdouble beta = 180 - ((180 - alpha) / 2);
		GLdouble seno = alpha * M_PI /180;
		GLdouble ancho = 2.0 * _radio * sin(seno/2.0);//radianes

		l.moveTo(aux,true);
		l.turnTo(beta);

		for(int i = 0; i < NUMLADOS; i++){
			_contorno[i] = aux;
			l.forward(ancho,true);
			aux = l.getPos();
			l.turn(alpha);
		}
	}

	Color _color;

	Punto _centro;

	GLdouble _radio;

	Punto _vectorMov;

	Punto _contorno[NUMLADOS];

};

#endif // __PELOTA_H