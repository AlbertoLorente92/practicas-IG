/*	Práctica 3 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __SATELITE_H
#define __SATELITE_H

#include "Malla.h"
#include "Lapiz.h"

class Satelite : public Malla{
public:
	//Constructora:
	Satelite(){}

	Satelite(const int np,const int nq,const float alturas[],const float arrayRadios[]){
		//NP--> Es el numero de vertices por el cual se aproxima la circunferencia
		//NQ--> Numero de rodajas que contiene el satelite
		_np = np;
		_nq = nq;

		_numVertices = _np * _nq;
		_numCaras = (_np * (_nq - 1))*2;//4
		_numNormales = _np * _nq;

		_numVertices = _numVertices + 16; //16 nuevos ptos de los paneles
		_numCaras = _numCaras + 12;//12 nuevas caras de los paneles
		_numNormales = _numNormales + 16;

		_vertices = new PuntoVector3D*[_numVertices];
		_caras = new Cara*[_numCaras];
		_normales = new PuntoVector3D*[_numNormales];

		calculaMallaSatelite(alturas,arrayRadios);
	}


	~Satelite(){
		delete _vertices;
		_vertices = NULL;
		delete _normales;
		_normales = NULL;
		delete _caras;
		_caras = NULL;
	}

private:
	void calculaMallaSatelite(const float alturas[],const float arrayRadios[]){
		int indice = 0;
		for(int j = 0; j < _nq; j++){
			Lapiz l;
			PuntoVector3D* aux = new PuntoVector3D(arrayRadios[j],alturas[j],0,1);
			GLdouble alpha = 360.0 / _np;
			GLdouble beta = 180.0 - ((180.0 - alpha) / 2.0);
			GLdouble seno = alpha * M_PI / 180.0;
			GLdouble ancho = 2.0 * arrayRadios[j] * sin(seno/2.0);//radianes

			l.moveTo(aux,true);
			l.turnTo(beta);

			for(int i = 0; i < _np; i++){
				_vertices[indice] = aux;
				l.forward(ancho,true,false);
				aux = l.getPos();
				l.turn(alpha);
				indice++;
			}

			delete aux;
			aux = NULL;
		}	

		/////////////////////////////////////
		int indVert[3];
		int x1 = 0;
		int x2 = 1;
		int x3 = _np;

		int q = 0;
		while(q<(_numCaras-12)){

			if(x2==0 || ((x2%_np)==0)){
				x2 = x2 - _np;
			}

			indVert[0] = x1;
			indVert[1] = x2;
			indVert[2] = x3;
			_caras[q] = new Cara(indVert,3,q);

			if(x2==0 || ((x2%_np)==0)){
				x2 = x2 + _np;
			}

			q++;

			/*indVert[0] = x2;
			indVert[1] = x1;
			indVert[2] = x3+1;
			_caras[q] = new Cara(indVert,3,q);

			q++;*/

			if(x2==0 || ((x2%_np)==0)){
				x2 = x2 - _np;
			}

			indVert[0] = x1;
			indVert[1] = x1+_np;
			indVert[2] = x2+_np;
			_caras[q] = new Cara(indVert,3,q);

			if(x2==0 || ((x2%_np)==0)){
				x2 = x2 + _np;
			}

			/*indVert[0] = x1+_np;
			indVert[1] = x2+_np;
			indVert[2] = x2;
			_caras[q] = new Cara(indVert,3,q);*/

			x1++;
			x2++;
			x3++;

			q++;
		}

		/*int indVert[4];
		int x1 = 0;
		int x2 = 1;
		int x4 = _np;
		int x3 = _np+1;

		for(int q = 0; q < (_numCaras - 12); q++){

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

		//////////////////////////////////////////////////////

		calculaPaneles(arrayRadios,indice);

		calculaNormales();
	}

	void calculaPaneles(const float arrayRadios[],int indice){
		GLdouble alpha = 360.0 / _np;
		GLdouble beta = 180.0 - ((180.0 - alpha) / 2.0);
		GLdouble seno = alpha * M_PI / 180.0;
		GLdouble ancho = 2.0 * arrayRadios[0] * sin(seno/2.0);//radianes

		float largo = arrayRadios[0] * 2;
		float ancho1 = (float) ancho / (float)2.0;
		float ancho2 = (float) ancho;
		int nCaras = _numCaras - 12;
		int posicion = indice;
		int indVert[4];
		int x1, x2, x4, x3;
		PuntoVector3D* p1;
		PuntoVector3D* p2;
		PuntoVector3D* p3;
		PuntoVector3D* p4;
		

		//Primera cara.
		p1 = new PuntoVector3D(largo,0,-ancho1,1);
		p2 = new PuntoVector3D(largo,0,ancho1,1);
		p3 = new PuntoVector3D(largo,-ancho2,ancho1,1);
		p4 = new PuntoVector3D(largo,-ancho2,-ancho1,1);

		_vertices[indice] = p1;
		indice++;
		_vertices[indice] = p2;
		indice++;
		_vertices[indice] = p3;
		indice++;
		_vertices[indice] = p4;
		indice++;

		x1 = posicion;
		x2 = posicion+1;
		x3 = posicion+2;
		x4 = posicion+3;
		indVert[0] = x1;	indVert[1] = x2;	indVert[2] = x3;	indVert[3] = x4;
		_caras[nCaras] = new Cara(indVert,4,nCaras);
		nCaras++;
		posicion = posicion + 4;

		/////////////////////////////////////////////////////////////////////

		//Segunda Cara
		p1 = new PuntoVector3D(-largo,0,-ancho1,1);
		p2 = new PuntoVector3D(-largo,0,ancho1,1);
		p3 = new PuntoVector3D(-largo,-ancho2,ancho1,1);
		p4 = new PuntoVector3D(-largo,-ancho2,-ancho1,1);

		_vertices[indice] = p1;
		indice++;
		_vertices[indice] = p2;
		indice++;
		_vertices[indice] = p3;
		indice++;
		_vertices[indice] = p4;
		indice++;

		x1 = posicion;
		x2 = posicion+1;
		x3 = posicion+2;
		x4 = posicion+3;
		indVert[0] = x1;	indVert[1] = x2;	indVert[2] = x3;	indVert[3] = x4;
		_caras[nCaras] = new Cara(indVert,4,nCaras);
		nCaras++;
		posicion = posicion + 4;

		///4 CARAS DE UNION
		colocaCarasPaneles(indice-1,nCaras);

		/////////////////////////////////////////////////////////////////////

		//Tercera Cara
		p1 = new PuntoVector3D(-ancho1,0,-largo,1);
		p2 = new PuntoVector3D(ancho1,0,-largo,1);
		p3 = new PuntoVector3D(ancho1,-ancho2,-largo,1);
		p4 = new PuntoVector3D(-ancho1,-ancho2,-largo,1);

		_vertices[indice] = p1;
		indice++;
		_vertices[indice] = p2;
		indice++;
		_vertices[indice] = p3;
		indice++;
		_vertices[indice] = p4;
		indice++;

		x1 = posicion;
		x2 = posicion+1;
		x3 = posicion+2;
		x4 = posicion+3;
		indVert[0] = x1;	indVert[1] = x2;	indVert[2] = x3;	indVert[3] = x4;
		_caras[nCaras] = new Cara(indVert,4,nCaras);
		nCaras++;
		posicion = posicion + 4;

		/////////////////////////////////////////////////////////////////////

		//Cuarta Cara
		p1 = new PuntoVector3D(-ancho1,0,largo,1);
		p2 = new PuntoVector3D(ancho1,0,largo,1);
		p3 = new PuntoVector3D(ancho1,-ancho2,largo,1);
		p4 = new PuntoVector3D(-ancho1,-ancho2,largo,1);

		_vertices[indice] = p1;
		indice++;
		_vertices[indice] = p2;
		indice++;
		_vertices[indice] = p3;
		indice++;
		_vertices[indice] = p4;

		x1 = posicion;
		x2 = posicion+1;
		x3 = posicion+2;
		x4 = posicion+3;
		indVert[0] = x1;	indVert[1] = x2;	indVert[2] = x3;	indVert[3] = x4;
		_caras[nCaras] = new Cara(indVert,4,nCaras);
		nCaras++;
		posicion = posicion + 3;

		///4 CARAS DE UNION
		colocaCarasPaneles(posicion,nCaras);

	}

	void colocaCarasPaneles(int posicion,int &nCaras){
		int indVert[4];
		int x1, x2, x4, x3;

		int aux = posicion;



		for(int i = 0; i < 4; i++){
			x1 = aux;
			x2 = aux-1;
			x3 = aux-5;
			x4 = aux-4;
			indVert[0] = x1;	indVert[1] = x2;	indVert[2] = x3;	indVert[3] = x4;
			_caras[nCaras] = new Cara(indVert,4,nCaras);
			nCaras++;
			aux = aux -1;
		}
		/*for(int i = 0; i < 4; i++){
			x1 = aux;
			x2 = aux-1;
			x3 = aux-5;
			x4 = aux-4;
			indVert[0] = x1;	indVert[1] = x2;	indVert[2] = x3;	indVert[3] = x4;
			_caras[nCaras] = new Cara(indVert,4,nCaras);
			nCaras++;
			aux = aux -1;
		}*/
	}

	void calculaNormales(){
		for(int k = 0; k < _numCaras; k++){
			_normales[k] = calculoVectorNormalPorNewell(_caras[k]);
		}
	}

	/*
		Numero de puntos por rodaja
	*/
	int _np;

	/**
		Numero de rodajas
	*/
	int _nq;		

	/*
		 ___			3
		 \_/			2
		/___\			1
		|___|			0
	*/
};

#endif // __SATELITE_H