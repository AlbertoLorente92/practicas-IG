/*	Pr�ctica 3 - Inform�tica Gr�fica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente S�nchez.
*/

#ifndef __VERTICENORMAL_H
#define __VERTICENORMAL_H

class VerticeNormal {
public:
	//Constructora:
	VerticeNormal(int inVertice, int inNormal){     
		_indiceVertice = inVertice;
		_indiceNormal = inNormal;
   }

	~VerticeNormal(){};

   int getIndiceVertice(){
		return _indiceVertice;
   }

   int getIndiceNormal(){
	return _indiceNormal;
   }


private:
	int _indiceVertice,_indiceNormal;
};

#endif // __VERTICENORMAL_H