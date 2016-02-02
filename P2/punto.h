/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __PUNTO_H
#define __PUNTO_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <GL/freeglut.h>

/**
 Implementación del TAD Punto.

 Las operaciones son:

 - Punto: GLdouble, GLdouble -> Punto. Generadora.

 Getters:
 - x: -> GLdouble. Observadora.
 - y: -> GLdouble. Observadora.

 Metodos:
 - distancia: Punto -> GLdouble. Observadora.
 - productoEscalar: Punto -> GLdouble. Observadora.
 - normal: Punto -> Punto. Observadora.
 - inversa: -> Punto. Observadora.
 - dameVector: Punto -> Punto. Observadora.
 - suma: Punto -> Punto. Observadora.
 - resta: Punto -> Punto. Observadora.
 - mitad: Punto -> Punto. Observadora.
 - normalizar: Punto -> Punto. Observadora.
 - modulo: -> GLdouble. Observadora.
 - anguloEntreV1V2: Punto -> GLdouble. Observadora.
 - multiplicacion: GLdouble -> Punto. Observadora.
 - negatividad: -> Punto. Observadora.
 */
class Punto {
public:
	//Constructora:
	/**
		Constructora de la clase Punto con parametros.
	*/
	Punto(const GLdouble a,const GLdouble b){
		_A=a;
		_B=b;
	}

	Punto(){}

	//Getters:
	/**
		Devuelve la coordenada x del punto.
	*/
	GLdouble x() const{
		return _A;
	}

	/**
		Devuelve la coordenada y del punto.
	*/
	GLdouble y() const{
		return _B;
	}

	//Metodos:
	/**
		Devuelve la distancia entre dos puntos.
	*/
	GLdouble distancia(Punto p){
		return sqrt(pow(p.x()-_A,2) + pow(p.y()-_B,2));
	}

	/**
		Producto escalar de dos vectores.
	*/
	GLdouble productoEscalar(Punto p){
		return (_A * p.x() + _B * p.y());
	}

	/**
		Calcula la normal dados 2 puntos que definen una recta
	*/
	Punto normal(Punto p){
		return Punto(p.y()-_B,-(p.x()-_A));
	}

	/**
		Devuelve el vector inverso a uno dado
	*/
	Punto inversa(){
		return Punto(-_B,_A);
	}

	/**
		Calcula el vector existente de un punto a otro.
	*/
	Punto dameVector(Punto p){
		return Punto(p.x()-_A,p.y()-_B);
	}

	/**
		Suma de Puntos.
	*/
	Punto suma(Punto p){
		return Punto(_A + p.x(),_B + p.y());
	}

	/**
		Resta de Puntos.
	*/
	Punto resta(Punto p){
		return Punto(_A - p.x(),_B - p.y());
	}

	/**
		Punto medio entre 2 puntos dados.
	*/
	Punto mitad(Punto p){
		return Punto((_A+p.x())/2.0,(_B+p.y())/2.0);
	}

	/**
		Normalizar.
	*/
	Punto normalizar(){
		GLdouble m = modulo();
		return Punto(_A/m,_B/m);
	}

	/**
		Modulo.
	*/
	GLdouble modulo(){
		return sqrt(pow(_A,2)+pow(_B,2));
	}

	/**
		Devuelve el angulo entre dos vectores.
	*/
	GLdouble anguloEntreV1V2(Punto v2){
		return acos(productoEscalar(v2) / (modulo() * v2.modulo())) * 180 / M_PI;
	}

	/**
		Producto punto*k.
	*/
	Punto multiplicacion(double k){
		return Punto(_A*k,_B*k);
	}

	/**
		Cambiamos el signo de los dos componentes del Punto.
	*/
	Punto negatividad(){
		return Punto(-_A,-_B);
	}

	Punto ajustaModulo(GLdouble error){
		GLdouble x,y;
		if(_A<0){
			x = _A - error;
		}else{
			x = _A + error;
		}

		if(_B<0){
			y = _B - error;
		}else{
			y = _B + error;
		}

		return Punto(x,y);
	}

	bool esIgual(Punto p){
		return _A==p.x() && _B==p.y();
	}

private:
	GLdouble _A;
	GLdouble _B;
};

#endif // __PUNTO_H