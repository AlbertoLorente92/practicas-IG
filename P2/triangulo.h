/*	Práctica 2 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __TRIANGULO_H
#define __TRIANGULO_H

#include "obstaculos.h"
#include "pelota.h"

#include <math.h>
#include <GL/freeglut.h>
using namespace std;
/**
 Implementación del TAD Triangulo.

 Las operaciones son:

 - Triangulo: Punto, Punto, Punto -> Triangulo. Generadora.

 Metodos:
			Publicos.
 - intersecionConRecta: Pelota, double, Punto -> double, Punto. Modificadora.
 - pinta: -> void. Modificadora.
			Privados.
 - dameSigno: GLdouble -> GLdouble. Observadora.
 - minimo: double[], int -> int. Observadora.

 */
class Triangulo : public Obstaculos {
public:
	
	static const int ELEM = 3;

	//Constructora:
	/**
		Constructora de la clase Triangulo con parametros.
	*/
	Triangulo(Punto p1,Punto p2,Punto p3){
		_baricentro = Punto((p1.x()+p2.x()+p3.x())/3.0,(p1.y()+p2.y()+p3.y())/3.0);

		_vertices[0] = p1;
		_vertices[1] = p2;
		_vertices[2] = p3;

		_vNormalA[0] = _vertices[0].normal(p2).normalizar();
		_vNormalA[1] = _vertices[1].normal(p3).normalizar();
		_vNormalA[2] = _vertices[2].normal(p1).normalizar();

		_vDelCentroA[0] = _baricentro.dameVector(_vertices[0]).normalizar();
		_vDelCentroA[1] = _baricentro.dameVector(_vertices[1]).normalizar();
		_vDelCentroA[2] = _baricentro.dameVector(_vertices[2]).normalizar();

		_color = Color(0.0f,0.0f,0.0f);

	}

	Triangulo(){}

	/**
		Dada una pelota comprueba si tiene intersección con el triangulo.
	*/
	bool intersecionConRecta(Pelota p,double& tIn, Punto& normalIn){
		GLdouble dist[3];
		GLdouble proj[3];
		GLdouble signo[3];

		//paso1:
		Punto vecMovInv = p.getVectorMovimiento();
		vecMovInv = vecMovInv.inversa().normalizar();

		dist[0] = p.getCentro().dameVector(_vertices[0]).productoEscalar(vecMovInv);	
		dist[1] = p.getCentro().dameVector(_vertices[1]).productoEscalar(vecMovInv);
		dist[2] = p.getCentro().dameVector(_vertices[2]).productoEscalar(vecMovInv);
		
		proj[0] = p.getCentro().dameVector(_vertices[0]).productoEscalar(p.getVectorMovimiento().normalizar());
		proj[1] = p.getCentro().dameVector(_vertices[1]).productoEscalar(p.getVectorMovimiento().normalizar());
		proj[2] = p.getCentro().dameVector(_vertices[2]).productoEscalar(p.getVectorMovimiento().normalizar());

		signo[0] = dameSigno(dist[0]);
		signo[1] = dameSigno(dist[1]);
		signo[2] = dameSigno(dist[2]);

		if(abs(signo[0] + signo[1] + signo[2])==3)
			return false;

		//paso2 aristas:		
		int nHits = 0;
		double hit[3];
		Punto n[3];
		for(int i = 0 ; i < 3 ; i++){
			int j = (i+1) % 3;
			if( (signo[i] * signo[j]) < 0 ){
				hit[nHits] = ( (proj[i]*dist[j]) - (dist[i]* proj[j]) ) / ( dist[j] - dist[i] );
				n[nHits] = _vNormalA[i];
				nHits ++ ;
			}
		}

		//paso3 vertices:
		if( nHits < 2 ){
			for( int i = 0; i < 3; i++){
				if(signo[i]==0){
					hit[nHits] = proj[i];
					n[nHits] = _vDelCentroA[i];
					nHits++;
				}
			}
		}

		int m = minimo(hit,nHits);

		tIn = hit[m]/p.getVectorMovimiento().modulo();
		normalIn = n[m];

		return true;
		
	}


	/**
		Pinta el triangulo.
	*/
	void pinta(){
		Punto intermedio;
		Punto avance;

		//glBegin ( GL_POLYGON ) ;													//Pinta el triangulo
		
		glBegin ( GL_LINE_STRIP ) ;	

			glColor3f(_color.getF1(),_color.getF2(),_color.getF3());		
			glVertex2d( _vertices[0].x(), _vertices[0].y());
			glVertex2d( _vertices[1].x(), _vertices[1].y());
			glVertex2d( _vertices[2].x(), _vertices[2].y());
			glVertex2d( _vertices[0].x(), _vertices[0].y());
		glEnd () ;

		glBegin ( GL_POINTS ) ;														//Pinta el baricentro
			glColor3f(_color.getF1()+0.5f,_color.getF2(),_color.getF3());		
			glVertex2d( _baricentro.x(), _baricentro.y());
		glEnd () ;

		for(int i = 0; i < ELEM; i++){												//Pinta las normales de las aristas extendidas del triangulo normalizadas												
			intermedio = (_vertices[i].mitad(_vertices[(i+1)%3]));
			avance = intermedio.suma(_vNormalA[i]);
			glBegin ( GL_LINE_STRIP ) ;
				glColor3f(_color.getF1()+0.5f,_color.getF2(),_color.getF3());		
				glVertex2d( intermedio.x(), intermedio.y());
				glVertex2d( avance.x(), avance.y());
			glEnd () ;
		}

		for(int i = 0; i < ELEM; i++){												//Pinta las normales de los vertices del triangulo normalizadas	
			intermedio = _vertices[i];
			avance = intermedio.suma(_vDelCentroA[i]);
			glBegin ( GL_LINE_STRIP ) ;
				glColor3f(_color.getF1()+0.5f,_color.getF2(),_color.getF3());		
				glVertex2d( intermedio.x(), intermedio.y());
				glVertex2d( avance.x(), avance.y());
			glEnd () ;
		}
	}

private:

	//Metodos:
	/**
		Devuelve: -1 si la distancia al vertice pi es negativa, 0 si la distancia es nula y 1 si la distancia es positiva
	*/
	GLdouble dameSigno(GLdouble dist){
		if(dist<0)
			return -1;
		else if(dist==0)
			return 0;
		else//(dist>0)
			return 1;
	}

	/**
		Dado un array y su tamaño devuelve el indice del elemento menor contenido dicho array
	*/
	int minimo(double vector[],int n){
		int pos=0;
		int i=0;
		double minimo=vector[i];

		while(i+1<n){
			if(vector[i+1]<minimo)
				pos = i+1;

			i++;
		}

		return pos;
	}

	Color _color;

	Punto _vertices[ELEM];

	Punto _vNormalA[ELEM];

	Punto _vDelCentroA[ELEM];

	Punto _baricentro;
};

#endif // __TRIANGULO_H