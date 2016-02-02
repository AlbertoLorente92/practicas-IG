/*	Práctica 3 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __MALLA_H
#define __MALLA_H

#include "Cara.h"
#include "PuntoVector3D.h"

class Malla {
public:

	void dibuja(){
		for(int i = 0; i < _numCaras; i++){
			glLineWidth(1.0);
			glBegin(GL_LINE_LOOP);

			//glBegin(GLU_LINE);

			//glBegin(GL_POLYGON);

			//o glBegin(GL_LINE_LOOP);
			for(int j = 0; j < _caras[i]->getNumeroVertices(); j++){
				int iN = _caras[i]->getIndiceNormalK(j);
				int iV = _caras[i]->getIndiceVerticeK(j);
				glNormal3f(_normales[iN]->getX(),_normales[iN]->getY(),_normales[iN]->getZ());
				//Si hubiera coordenadas de textura, aquí se suministrarían
				//las coordenadas de textura del vértice j con glTexCoor2f(…);
				glVertex3f(_vertices[iV]->getX(),_vertices[iV]->getY(),_vertices[iV]->getZ());
			}

			glEnd();
		}	
	}

	void dibujaXPartes(int comienzo,int fin){
		for(int i = comienzo; i < fin; i++){
			glLineWidth(1.0);
			glBegin(GL_LINE_LOOP);

			//glBegin(GLU_LINE);

			//glBegin(GL_POLYGON);

			//o glBegin(GL_LINE_LOOP);
			for(int j = 0; j < _caras[i]->getNumeroVertices(); j++){
				int iN = _caras[i]->getIndiceNormalK(j);
				int iV = _caras[i]->getIndiceVerticeK(j);
				glNormal3f(_normales[iN]->getX(),_normales[iN]->getY(),_normales[iN]->getZ());
				//Si hubiera coordenadas de textura, aquí se suministrarían
				//las coordenadas de textura del vértice j con glTexCoor2f(…);
				glVertex3f(_vertices[iV]->getX(),_vertices[iV]->getY(),_vertices[iV]->getZ());
			}

			glEnd();
		}	
	}

	PuntoVector3D* calculoVectorNormalPorNewell(Cara* c){
		PuntoVector3D* n = new PuntoVector3D(0,0,0,1);

		for(int i = 0; i < c->getNumeroVertices(); i++){
			PuntoVector3D* vertActual = _vertices[c->getIndiceVerticeK(i)];
			PuntoVector3D* vertSiguiente = _vertices[c->getIndiceVerticeK((i+1) % c->getNumeroVertices())];

			n->setX((vertActual->getY() - vertSiguiente->getY()) * (vertActual->getZ() + vertSiguiente->getZ()));

			n->setY((vertActual->getZ() - vertSiguiente->getZ()) * (vertActual->getX() + vertSiguiente->getX()));

			n->setZ((vertActual->getX() - vertSiguiente->getX()) * (vertActual->getY() + vertSiguiente->getY()));

		}	

		n->normaliza();

		return n;
	}

		
protected:
	int _numVertices;
	PuntoVector3D** _vertices;
	int _numNormales;	//=numCaras frecuentemente
	PuntoVector3D** _normales;
	int _numCaras;
	Cara** _caras;
};

#endif // __MALLA_H