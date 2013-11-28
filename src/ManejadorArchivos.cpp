/*
 * ManejadorArchivos.cpp
 */

#include "ManejadorArchivos.h"

using namespace std;

/**********************************************************************/
/**********************************************************************/


ManejadorArchivos::ManejadorArchivos(){}

/**********************************************************************/
/**********************************************************************/

//Destructor del ManejadorArchivos:
//Cierra el archivo unicamente, no lo destruye
ManejadorArchivos::~ManejadorArchivos() {
  if (miarchivo != NULL) miarchivo.close();
}

<<<<<<< .mine
/**********************************************************************/
/**********************************************************************/


//ojo: usar solo si hay que abrir y cerrar muchos archivos, sino el destructor cierra el archivo.
//se usa en LevantarListaDePuntos.
void ManejadorArchivos::cerrarArchivo(){
	miarchivo.close();
}	

//Abre el archivo pasado por parametro
//en modo LECTURA
void ManejadorArchivos::abrirLectura(const string &nombre){


	//intenta abrir el archivo en modo lectura
	  miarchivo.open(nombre.c_str(), fstream::in); //in = read.

	  if (!miarchivo.is_open())
	          // si no se puede abrir
	          throw ios_base::failure("El archivo "+nombre+" no se abre");

	}

/**********************************************************************/
/**********************************************************************/


//void ManejadorArchivos::abrirEscritura(const std::string& miruta){

//	miarchivo.open(miruta.c_str(), std::fstream::in);
//}

/**********************************************************************/
/**********************************************************************/


// Lo que lee lo guardo en micadena
// Retorna true si pudo leer una linea, o false en caso contrario
bool ManejadorArchivos::leerUnaLinea(string &micadena){

	
	char linea[102400];

	  // lee del archivo a la linea, hasta haber leido
	  // MAX_LENGTH caracteres(en este caso 100 kbytes
	  miarchivo.getline( (char*)&linea , 102400);
	  micadena = linea;

	  if (miarchivo.fail() ) {
	    //chequea si se ha producido un error, se devuelve false
	    miarchivo.clear();
	    return false;
	  }
	  return true;

}

/**********************************************************************/
/**********************************************************************/


// Lo que lee lo guardo en micadena
// Retorna true si pudo leer una linea, o false en caso contrario
bool ManejadorArchivos::leerUnaLineaIndice(string &micadena){

	
	char linea[102400];

	  // lee del archivo a la linea, hasta haber leido
	  // MAX_LENGTH caracteres(en este caso 100 kbytes
	  miarchivo.getline( (char*)&linea , 102400, '/');
	  micadena = linea;

	  if (miarchivo.fail() ) {
	    //chequea si se ha producido un error, se devuelve false
	    miarchivo.clear();
	    return false;
	  }
	  return true;
}

/**********************************************************************/
/**********************************************************************/



//Posiciona el cursor en una nueva linea debajo de la actual
void ManejadorArchivos::terminarLinea() {
	
  //intenta escribir en el archivo
  miarchivo << endl;

  if (miarchivo.fail())
    //si se produjo un error, arroja una excepcion
    throw ios_base::failure("No se pudo terminar la linea");
}

/**********************************************************************/
/**********************************************************************/


bool ManejadorArchivos::estaAlFinal(){
	
	return miarchivo.eof();
	
}

/**********************************************************************/
/**********************************************************************/


char* ManejadorArchivos::leerArchivo(){
	
    miarchivo.seekg (0, miarchivo.end);
    int largo = miarchivo.tellg();
    miarchivo.seekg (0, miarchivo.beg);

	char * buffer = new char [2*largo];
	//char* buffer = (char*) malloc((largo+1)*sizeof(char));
	
    miarchivo.read (buffer,largo);
    
    miarchivo.close();

	return buffer;
	
}

/**********************************************************************/
/**********************************************************************/


/*Recibe un vector con numeros de docs, lee el archivo del hash secundario 
 *Crea y devuelve la lista de puntos correspondiente. */

//Recibe una lista de numeros de docs NO ORDENADA
vector<Punto> ManejadorArchivos::LevantarListaDePuntos(vector<int> numero_doc, vector<string> vectorArchivos){
	
	//ordena la lista:
	
	std::sort (numero_doc.begin(), numero_doc.end());
	string auxLinea;
	Punto punto;
	vector<Punto> lista_de_puntos;
	/*cout<<"En Manejador:\n";
	for (unsigned int u = 0; u < numero_doc.size(); u++){
		cout<<"numero: "<<numero_doc[u]<<endl;  }*/
	
	this->abrirLectura(DIR_FILE_INDICE_FINAL);//

	int indice = 0;
	unsigned int j = 0;
	char *linea = new char[512];

	while ( (this->leerUnaLinea(auxLinea) == true) && (j<numero_doc.size())){
		int doc = numero_doc[j];
			
		if (indice != doc) { //no es el doc que busco:
			indice++;
			continue;
			//cout<<"INDICES NOT DOC\n";
		}else { //para un doc que busco:
			//cout<<"ELSE\n";
			vector<float> vector_frec;
			strcpy(linea, auxLinea.c_str()); 
			//auxPalabra va a ir conteniendo cada palabra sacando los tokens
			char* auxPalabra = strtok(linea," ,  ");

			while(auxPalabra != NULL){
				//cout<<"WHILE NOT NULL\n";
				//std::string::size_type sz;     // alias of size_t
				float frec = atof(auxPalabra);
				//long float frec = std::stold (auxPalabra,&sz);
				vector_frec.push_back(frec);	
				auxPalabra = strtok(NULL," ,  ");
			}
			//termina la linea:	
			//cout<<"PUSH: "<<j<<"\n";
			punto =  Punto(vector_frec, doc, vectorArchivos[j]);
			lista_de_puntos.push_back(punto);
			//cout<<"&punto = "<<&punto<<endl;
			indice++;
			j++; //pasa al siguiente doc
			
			
		}
	}		
	delete []linea;
	this->cerrarArchivo();
	cout<<"MANEJADOR LISTA DE PUNTOS SIZE: "<<lista_de_puntos.size()<<endl;
	return lista_de_puntos;
}
