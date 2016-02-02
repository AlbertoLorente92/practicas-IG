/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __CARA_H
#define __CARA_H

#include "VerticeNormal.h"

class Cara {
public:
	//Constructora:
	Cara(int indicesVertices[],int n, int numCara){
		_numVertices = n;
		_arrayVertices = new VerticeNormal*[_numVertices];
		for(int i = 0; i<_numVertices;i++){
			_arrayVertices[i] = new VerticeNormal(indicesVertices[i],numCara);
		}
	}

	~Cara(){};

	int getNumeroVertices(){
		return _numVertices;
	}

	int getIndiceNormalK(int j){
		return _arrayVertices[j]->getIndiceNormal();
	}

	int getIndiceVerticeK(int j){
		return _arrayVertices[j]->getIndiceVertice();
	}

	void borra(){
		delete[] _arrayVertices;
		_arrayVertices = NULL;
	}

private:
	int _numVertices;
	VerticeNormal** _arrayVertices;
};

#endif // __CARA_H