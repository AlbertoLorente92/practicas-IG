/*	Pr�ctica 2 - Inform�tica Gr�fica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente S�nchez.
*/

#ifndef __OBSTACULOS_H
#define __OBSTACULOS_H

#include "pelota.h"
#include <GL/freeglut.h>

/**
 Implementaci�n de la interfaz Obstaculos.
*/
class Obstaculos {
public:
	
	//Metodos:	
	virtual bool intersecionConRecta(Pelota p,double& tIn, Punto& normalIn) = 0;

	virtual void pinta() = 0;

};

#endif // __OBSTACULOS_H