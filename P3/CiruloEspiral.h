/*	Práctica 3 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __CIRCULOESPIRAL_H
#define __CIRCULOESPIRAL_H

#include "Malla.h"
#include "Lapiz.h"
#include "Matriz4x4.h"
#include <math.h>

class CirculoEspiral : public Malla{
public:

	//Constructora:
	CirculoEspiral(){}

	CirculoEspiral(const int np,const int nq,const GLdouble radioEsfera){
		//NP--> Es el numero de vertices por el cual se aproxima la circunferencia
		//NQ--> Numero de rodajas que contiene el satelite
		_np = np;
		_nq = nq;
		_radio = (GLfloat)radioEsfera;

		_numVertices = _np * _nq;
		_numCaras = (_np * (_nq - 1))*2;
		_numNormales = _np * _nq;

		_vertices = new PuntoVector3D*[_numVertices];
		_caras = new Cara*[_numCaras];
		_normales = new PuntoVector3D*[_numNormales];

		calculaMallaCirculoEspiral();
	}

	PuntoVector3D** getVertices(){
		return _vertices;
	}

	~CirculoEspiral(){
		delete _vertices;
		_vertices = NULL;
		delete _normales;
		_normales = NULL;
		delete _caras;
		_caras = NULL;
	}
	
private:
	/*
		Numero de puntos por rodaja
	*/
	int _np;

	/**
		Numero de rodajas
	*/
	int _nq;

	GLfloat _radio;

	void calculaMallaCirculoEspiral(){
		PuntoVector3D* perfil = new PuntoVector3D[_np];
		Lapiz l;
		PuntoVector3D* aux = new PuntoVector3D(_radio,0,0,1);
		GLdouble alpha = 360.0 / _np;
		GLdouble beta = 180.0 - ((180.0 - alpha) / 2.0);
		GLdouble seno = alpha * M_PI / 180.0;
		GLdouble ancho = 2.0 * _radio * sin(seno/2.0);//radianes

		l.moveTo(aux,true);
		l.turnTo(beta);

		for(int i = 0; i < _np; i++){
			perfil[i] = aux;
			l.forward(ancho,true,true);
			aux = l.getPos();
			l.turn(alpha);
		}

		delete aux;

		GLdouble t = 0;
		int indice = 0;
		for(int i = 0; i < _nq; i++){
			Matriz4x4 m(t);

			for(int j = 0; j < _np; j++){
				_vertices[indice] = m.multiplicaPuntoXMatriz(perfil[j]);
				indice++;
			}

			t = t + 0.1;
		}

		/////////////////////////////////////
		
		int indVert[3];
		int x1 = 0;
		int x2 = 1;
		int x3 = _np;

		int q = 0;
		while(q<_numCaras){

			if((q+1)%_np==0){
				x2 = x2 - _np;
				x3 = x3 - _np;
			}

			indVert[0] = x1;
			indVert[1] = x2;
			indVert[2] = x3;
			_caras[q] = new Cara(indVert,3,q);

			if((q+1)%_np==0){
				x2 = x2 + _np;
				x3 = x3 + _np;
			}

			q++;

			if((q+1)%_np==0){
				x2 = x2 - _np;
				x3 = x3 - _np;
			}

			indVert[0] = x1;
			indVert[1] = x2+_np;
			indVert[2] = x3;
			_caras[q] = new Cara(indVert,3,q);

			if((q+1)%_np==0){
				x2 = x2 + _np;
				x3 = x3 + _np;
			}

			x1++;
			x2++;
			x3++;

			q++;
		}

		/*for(int q = 0; q < _numCaras; q++){

			if((q+1)%_np==0){
				x2 = x2 - _np;
				x3 = x3 - _np;
			}


			indVert[0] = x1;
			indVert[1] = x2;
			indVert[2] = x3;
			indVert[3] = x4;

			_caras[q] = new Cara(indVert,3,q);

			if((q+1)%_np==0){
				x2 = x2 + _np;
				x3 = x3 + _np;
			}

			x1++;
			x2++; 
			x3++;
			x4++;
		}

		/*int indVert[4];
		int x1 = 0;
		int x2 = 1;
		int x4 = _np;
		int x3 = _np+1;

		for(int q = 0; q < _numCaras; q++){

			if((q+1)%_np==0){
				x2 = x2 - _np;
				x3 = x3 - _np;
			}


			indVert[0] = x1;
			indVert[1] = x2;
			indVert[2] = x3;
			indVert[3] = x4;

			_caras[q] = new Cara(indVert,4,q);

			if((q+1)%_np==0){
				x2 = x2 + _np;
				x3 = x3 + _np;
			}

			x1++;
			x2++; 
			x3++;
			x4++;
		}*/

		calculaNormales();
	
	}

	void calculaNormales(){
		for(int k = 0; k < _numCaras; k++){
			_normales[k] = calculoVectorNormalPorNewell(_caras[k]);
		}
	}

};

#endif // __CIRCULOESPIRAL_H