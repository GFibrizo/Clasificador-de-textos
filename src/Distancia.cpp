#include "Distancia.h"


//Constructor:
Distancia::Distancia(){}
//Destructor:
Distancia::~Distancia(){}


//Recibe dos vectores de frecuencias, devuelve la distancia entre los vectores calculada con el metodo del coseno
double distanciaCoseno(double vector1[CANT_DOCS], double vector2[CANT_DOCS]){
	double suma = 0.0;
	double norma1 = 0.0;
	double norma2 = 0.0;
	double coseno;
	
	for (int i=0; i<CANT_DOCS; i++){
		suma += (vector1[i] * vector2[i]);
		norma1 += (vector1[i] * vector1[i]);
		norma2 += (vector2[i] * vector2[i]);
	}
	
	coseno = suma / (sqrt(norma1) * sqrt(norma2) );
	return coseno;
}	

// Recibe un vector v1 y una lista de vectores.
// Devuelve el vector de la lista de vectores que este mas cerca de v1.
// No estoy segura de "double* lista_de_vectores "
double calcular_mas_cercano(double vector[CANT_DOCS], double* lista_de_vectores){
	double distancia_minima = 100;
	double distancia_coseno;
	double vector_mas_cercano;
	int largo_lista_de_vectores = 10; //CAMBIAR, SOLO PARA PROBAR,depende de como se declare el vector.
	for (int i=0; i < largo_lista_de_vectores; i++){
		distancia_coseno = distanciaCoseno(vector, &lista_de_vectores[i]);
		if (distancia_coseno < distancia_minima){
			distancia_minima = distancia_coseno;
			vector_mas_cercano = lista_de_vectores[i];
		}				
	}
	return vector_mas_cercano;	
}

	
	




/*
#include <vector>
using namespace std;

vector<vector<float>> vv;
vector<float> v1;

v1.push(2.3);
vv.push(v1);

*/

/*
int main (){
	return 0;
}	*/
	
/*	
//PRUEBA
int main(){
	double a = 1.2;
	double b = 10.2;
	double c = 5.9;
	double v1[CANT_DOCS] = {a,a,c};
	double v2[CANT_DOCS] = {b,c,b};
	double v3[CANT_DOCS] = {b,c,a};
	double v4[CANT_DOCS] = {a,b,c};
	double lista[3] = {v2,v3,v4}; // PROBAR CON VECTOR
	//distanciaCoseno(v1,v2);
	std::cout<<calcular_mas_cercano(v1,lista);
	return 0;
}
*/
