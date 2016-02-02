/*	Práctica 4 - Informática Gráfica (IG)
Componentes del grupo:
Juan Deltell Mendicute.
Alberto Lorente Sánchez.
*/

#ifndef __COLOR_H
#define __COLOR_H

#define Black	Color(0.0f,0.0f,0.0f)
#define Red		Color(1.0f,0.0f,0.0f)
#define Blue	Color(0.0f,0.0f,1.0f)
#define Green	Color(0.0f,0.1f,0.0f)
#define Yellow	Color(1.0f,1.0f,0.0f)
#define Cyan	Color(0.0f,1.0f,1.0f)
#define Magenta Color(1.0f,0.0f,1.0f)
#define White	Color(1.0f,1.0f,1.0f)
#define Gray	Color(0.5f,0.5f,0.5f)
#define Orange	Color(1.0f,0.5f,0.0f)
#define Brown	Color(0.647059f,0.164706f,0.164706f)
/**
 Implementación del TAD Color.

 Las operaciones son:

 - Color: float, float, float -> Color. Generadora.

 Getters:
 - getF1: -> float. Observadora.
 - getF2: -> float. Observadora.
 - getF3: -> float. Observadora.

 Setters:
 - setF1: float -> void. Modificadora.
 - setF2: float -> void. Modificadora.
 - setF3: float -> void. Modificadora.

 Metodos:
 - difuminar: int -> Color. Modificadora.
 - esNegro: -> bool. Observadora.

 */
class Color {
public:
	//Constructora:
	/**
		Constructora de la clase color con 3 parametros.
	*/
	Color(float a,float b,float c){
		_A=a;
		_B=b;
		_C=c;
	}

	Color(){}

	//Getters:
	/**
		Devuelve el primer parametro del color.
	*/
	float getF1() const{
		return _A;
	}

	/**
		Devuelve el segundo parametro del color.
	*/
	float getF2() const{
		return _B;
	}

	/**
		Devuelve el tercer parametro del color.
	*/
	float getF3() const{
		return _C;
	}

	//Setters:
	/**
		Establece un nuevo primer parametro del color.
	*/
	void setF1(float f){
		_A =f;
	}

	/**
		Establece un nuevo segundo parametro del color.
	*/
	void setF2(float f){
		_B =f;
	}

	/**
		Establece un nuevo tercer parametro del color.
	*/
	void setF3(float f){
		_C =f;
	}

	//Metodos:
	void Color::operator= (const Color& c){
		_A = c.getF1();
		_B = c.getF2();
		_C = c.getF3();
	}

private:
	float _A;
	float _B;
	float _C;
};

#endif // __COLOR_H