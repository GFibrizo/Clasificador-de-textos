/*
 * PreProcesarDatos.cpp
 *
 *  Created on: 03/11/2013
 *      Author: agu
 */

#include "PreProcesarDatos.h"


PreProcesarDatos::PreProcesarDatos(const char* ruta) {
	this->invalidos= "¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890";//[CANT_DE_SEPARADORES]
	LectorDirectorios * lecDirectorio= new LectorDirectorios();
	//levanta archivos del directorio:
	this->vector_archivos = lecDirectorio->leerDir (ruta);
	this->verifStopWord= new VerificadorStopWords(DIR_STOP_WORDS);

	this->archivoHashSecundario.open(DIR_FILE_HASH_2, fstream::app); //modo append
		//si no se puede abrir:
		if (!this->archivoHashSecundario.is_open()){
			throw std::ios_base::failure("El archivo no se abre");
		}

}

PreProcesarDatos::~PreProcesarDatos() {

	delete this->verifStopWord;
	//delete this->manejador;
	archivoHashSecundario.close();
}
void PreProcesarDatos::pasarAminusculas(string& str){
     transform(str.begin(), str.end(), str.begin(), ::tolower);
}

//Si la clave no esta en el hash, la agrega asociada a un valor 0.
//Si la clave esta en el hash, aumenta en 1 el valor asociado.
void PreProcesarDatos::agregarElementoAHash(hash& hash, string clave){

	if (hash.count(clave) > 0){
		 hash[clave]=hash[clave]+ 1;
		 return;
	}
	hash[clave] = 1;

}

string PreProcesarDatos::numberToString(int number){
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}
void PreProcesarDatos::escribirArchivoDeHash(hash hash){
	string aux;

	for (hash::iterator it= hash.begin(); it != hash.end(); it++){
		aux.operator =(it->first);
		aux.append(this->numberToString(it->second));
		//aux=it->first;

		//tam=std::tuple_size<decltype(it->pair)>::value;
		this->archivoHashSecundario.write(aux.c_str(),aux.length());

	}
}

void PreProcesarDatos::preProcesarDatos(){
	string auxLinea;
	string palabra;
	//trabaja con cada archivo:
	unsigned int i;

	for (i = 0; i <= this->vector_archivos.size(); i++){
		//COUT prueba para ver que archivos se recupero en el directorio
		cout<<"Archivo: "<<this->vector_archivos[i]<<endl;
		//TODO ver repositorio donde estaran los archivos
		this->manejador = new ManejadorArchivos() ;
		this->manejador->abrirLectura("files/"+this->vector_archivos[i]);
			while ( this->manejador->leerUnaLinea(auxLinea)){
			/* ¿Que deberia hacer con la linea? le tiene que sacar los
			 * simbolos, numeros y espacios e ir devolviendo por palabra.
			 * Luego comprueba si la palabra es un stopword. Si lo es, la
			 * descarta, sino la agrega a los hashes correspondientes.
			 */
			char *linea = new char[256];
			strcpy(linea, auxLinea.c_str()); //
			//auxPalabra va a tener una lista de palabras sacando los tokens
			char* auxPalabra = strtok(linea,this->invalidos);

			while ( auxPalabra != NULL ){
					palabra = auxPalabra;
					pasarAminusculas(palabra);
					//veo si es un stopword y sino lo agrego a hashes:
					if(!this->verifStopWord->verificarPalabra(palabra)){
						//COUT
						//cout<<palabra<<endl;
						agregarElementoAHash(this->hashPrincipal, palabra);
						agregarElementoAHash(this->hashSecundario, palabra);
					}
					auxPalabra = strtok (NULL, this->invalidos);// "siguiente"
			}
			delete []linea;
			delete auxPalabra;

		} //termina de trabajar con ese archivo
		//CERRAR ESE ARCHIVO
		delete this->manejador;
		//guardo la referencia al hash secundario viejo en una cola de hashes
		this->colaHashesSecundarios.push(this->hashSecundario);
		//referencio la variable hash_secundario a un nuevo hash de un nuevo archivo
		hash nuevoHash;
		this->hashSecundario = nuevoHash;

		/* Una vez que se llega a la cantidad maxima de hashes secundarios soportados
		 * en memoria, estos se guardan en un archivo. */
		if (this->colaHashesSecundarios.size() >= CANT_MAX){
			while (this->colaHashesSecundarios.size() > 0){
				//TODO esto es muy dudoso

				this->hashAux  = this->colaHashesSecundarios.front();
				this->colaHashesSecundarios.pop();
				escribirArchivoDeHash(this->hashAux);
			}
		}


	}
	//CERRAR ARCHIVO DE HASH SECUNDARIO

}

const char* PreProcesarDatos::getInvalidos(){
	return this->invalidos;
}
