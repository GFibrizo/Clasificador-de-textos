#include "Distancia.h"


//Constructor:
Distancia::Distancia(){}
//Destructor:
Distancia::~Distancia(){}


//Recibe dos vectores de frecuencias, devuelve la distancia entre los vectores calculada con el metodo del coseno
double distanciaCoseno(Punto punto1, Punto punto2){
	double suma = 0.0;
	double norma1 = 0.0;
	double norma2 = 0.0;
	double coseno;
	vector <double> vector1 = punto1.vectorDeFrecuencias();
	vector <double> vector2 = punto2.vectorDeFrecuencias();
	for (int i=0; i<vector1.size(); i++){ 
		suma += (vector1[i] * vector2[i]);
		norma1 += (vector1[i] * vector1[i]);
		norma2 += (vector2[i] * vector2[i]);
	}
	
	coseno = suma / (sqrt(norma1) * sqrt(norma2) );
	return coseno;
}	

// Recibe un punto v1 y una lista de puntos.
// Devuelve el punto de la lista de puntos que este mas cerca de v1.
Punto calcular_mas_cercano(Punto v1, vector<Punto> lista_de_puntos){
	double distancia_maxima = 0;
	double distancia_coseno;
	Punto punto_mas_cercano;
	for (unsigned int i=0; i < lista_de_puntos.size(); i++){
		distancia_coseno = distanciaCoseno(v1, lista_de_puntos[i]);
		if (distancia_coseno > distancia_maxima){
			distancia_maxima = distancia_coseno;
			punto_mas_cercano = lista_de_puntos[i];
		}				
	}
	return punto_mas_cercano;	
}

	
	




/*
 * 
#include <vector>
using namespace std;

vector<vector<float>> vv;
vector<float> v1;

v1.push_back(2.3);
vv.push_back(v1);

*/

/*
int main (){
	return 0;
}*/
	
/*
//PRUEBA
#include <string>
int main(){
	double a = 1.2;
	double b = 10.2;
	double c = 5.9;
	double v1[CANT_DOCS] = {a,a,c};
	double v2[CANT_DOCS] = {b,c,b};
	double v3[CANT_DOCS] = {b,c,a};
	double v4[CANT_DOCS] = {a,b,c};
	double *lista[] = {v2,v3,v4}; // PROBAR CON VECTOR
	//distanciaCoseno(v1,v2);
	double* resultado = calcular_mas_cercano(v1,lista);
	std::cout<<resultado[0]<<","<< resultado[1]<<","<<resultado[2]<<"\n";

	return 0;
}

*/
