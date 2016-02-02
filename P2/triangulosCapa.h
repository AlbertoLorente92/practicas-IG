/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __TRIANGULOCAPA_H
#define __TRIANGULOCAPA_H

#include "obstaculos.h"

#include "triangulo.h"
#include "circunferencia.h"

#include <math.h>
#include <GL/freeglut.h>
using namespace std;
/**
 Implementación del TAD TriangulosCapa.

 Las operaciones son:

 - TriangulosCapa: Punto, Punto, Punto, GLdouble -> TriangulosCapa. Generadora.

 Metodos:
			Publicos.
 - intersecionConRecta: Pelota, double, Punto -> double, Punto. Modificadora.
 - pinta: -> void. Modificadora.
			Privados.
 - construirFrontera: GLdouble -> void. Modificadora.

 */
class TrianguloCapa : public Obstaculos {
public:
	
	static const int ELEM = 3;

	//Constructora:
	/**
		Constructora de la clase Triangulo con parametros.
	*/
	TrianguloCapa(Punto p1,Punto p2,Punto p3,GLdouble radio){
		Triangulo t(p1,p2,p3);
		_tri[0] = t;

		Punto centro((p1.x()+p2.x()+p3.x())/3.0,(p1.y()+p2.y()+p3.y())/3.0);

		_vertices[0] = p1;
		_vertices[1] = p2;
		_vertices[2] = p3;

		_vNormalA[0] = _vertices[0].normal(p2).normalizar();
		_vNormalA[1] = _vertices[1].normal(p3).normalizar();
		_vNormalA[2] = _vertices[2].normal(p1).normalizar();

		_vDelCentroA[0] = centro.dameVector(_vertices[0]).normalizar();
		_vDelCentroA[1] = centro.dameVector(_vertices[1]).normalizar();
		_vDelCentroA[2] = centro.dameVector(_vertices[2]).normalizar();

		construirFrontera(radio);
	}

	TrianguloCapa(){}

	/**
		Dada una pelota comprueba si tiene intersección con el triangulo.
	*/
	bool Obstaculos::intersecionConRecta(Pelota p,double& tIn, Punto& normalIn){
		bool interseccionGeneral = false;

		double tInAux;
		Punto normalInAux;
		double epsilon;

		for(int i = 1; i < ELEM+1; i++){

			if(_tri[i].intersecionConRecta(p,tInAux,normalInAux)){

				if(!interseccionGeneral)
					interseccionGeneral = true;

				epsilon = tInAux * 0.1;
				if(tInAux>=(-epsilon) && (tInAux <= (1+epsilon))){
					if(tIn >= tInAux){
						tIn = tInAux;
						normalIn = normalInAux;
					}
				}
			}
		}

		for(int i = 0; i < ELEM; i++){
			if(_cir[i].intersecionConRecta(p,tInAux,normalInAux)){

				if(!interseccionGeneral)
					interseccionGeneral = true;

				epsilon = tInAux * 0.1;
				if(tInAux>=(-epsilon) && (tInAux <= (1+epsilon))){
					if(tIn >= tInAux){
						tIn = tInAux;
						normalIn = normalInAux;
					}
				}
			}
		}

		return interseccionGeneral;
	}


	/**
		Pinta el triangulo compuesto.
	*/
	void Obstaculos::pinta(){
		_tri[0].pinta();
		for(int i = 1; i < 4; i++){
			_tri[i].pinta();
		}
		for(int i = 0; i < ELEM; i++){
			_cir[i].pinta();
		}
	}

private:
	void construirFrontera(GLdouble radio){
		Triangulo t;

		Circunferencia c1(_vertices[0],radio,radio);
		Circunferencia c2(_vertices[1],radio,radio);
		Circunferencia c3(_vertices[2],radio,radio);
		_cir[0]=c1;
		_cir[1]=c2;
		_cir[2]=c3;

		Punto aux1 = _vertices[0].suma(_vNormalA[0].multiplicacion(radio));
		Punto aux2 = _vertices[1].suma(_vNormalA[0].multiplicacion(radio));
		t = Triangulo(aux1,aux2,_vertices[0]);

		_tri[1] = t;

		aux1 = _vertices[1].suma(_vNormalA[1].multiplicacion(radio));
		aux2 = _vertices[2].suma(_vNormalA[1].multiplicacion(radio));
		t = Triangulo(aux1,aux2,_vertices[1]);

		_tri[2] = t;

		aux1 = _vertices[2].suma(_vNormalA[2].multiplicacion(radio));
		aux2 = _vertices[0].suma(_vNormalA[2].multiplicacion(radio));
		t = Triangulo(aux1,aux2,_vertices[2]);

		_tri[3] = t;
	}

	Circunferencia _cir[ELEM];

	Triangulo _tri[ELEM+1];

	Punto _vertices[ELEM];

	Punto _vNormalA[ELEM];

	Punto _vDelCentroA[ELEM];
};

#endif // __TRIANGULO_H