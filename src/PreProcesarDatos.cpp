/*
 * PreProcesarDatos.cpp
 *
 *  Created on: 03/11/2013
 *      Author: agu
 */

#include "PreProcesarDatos.h"

void PreProcesarDatos::relative_dir_base_split(const string& path, string& dir)
{
  std::string::size_type slash_pos = path.rfind("/"); //Find the last slash
  if (slash_pos != std::string::npos) //If there is a slash
  {
    slash_pos++;
    dir = path.substr(0, slash_pos); //Directory is before slash

  }
  else //Otherwise, there is no directory present
  {
    dir.clear();

  }
}
PreProcesarDatos::PreProcesarDatos(const char* ruta) {
	this->invalidos= "¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890";//[CANT_DE_SEPARADORES]
	LectorDirectorios * lecDirectorio= new LectorDirectorios();
	//levanta archivos del directorio:
	this->vector_archivos = lecDirectorio->leerDir (ruta);
	this->verifStopWord= new VerificadorStopWords(DIR_STOP_WORDS);
	this->archivoHashSecundario.open(DIR_FILE_HASH_2, ios_base::out | ios_base::app); //modo append
	this->verifDocDiferentes=0;
		//si no se puede abrir:
		if (!this->archivoHashSecundario.is_open()){
			throw std::ios_base::failure("El archivo no se abre");
		}
	this->relative_dir_base_split(ruta,this->directorio);
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

void PreProcesarDatos::agregarElementoAHashPrincipal(t_hashPrincipal& hash,string clave,int numDoc){
	//Si encuentra la clave en el hash

	if (hash.count(clave) > 0){

		//si el documento actual es diferente al documento anterior
		if(this->verifDocDiferentes!=numDoc){

			hash[clave].documentos=hash[clave].documentos+1;
			this->verifDocDiferentes=numDoc;

		}
		hash[clave].frecuencia=hash[clave].frecuencia+1;

		return;
	}
	hash[clave].documentos=1;
	hash[clave].frecuencia=1;
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
		aux.append(",");
		aux.append(this->numberToString(it->second));
		aux.append(" ");
		this->archivoHashSecundario << aux.c_str();
	}
	this->archivoHashSecundario <<  endl;

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
		this->manejador->abrirLectura(this->directorio+this->vector_archivos[i]);
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
						palabra = stem_palabra(palabra);
						//COUT
						cout<<palabra<<endl;
                  //TODO Ver que estamos agregando al hash principal, no coincide con lo que esta en el informe
						agregarElementoAHashPrincipal(this->hashPrincipal, palabra,i);
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


void PreProcesarDatos::generarArchivoConDatosPonderados(){
	
	//TO BE IMPLEMENTED
	
	
}


string PreProcesarDatos::stem_palabra(string palabra){
	
	char *palabra_c = new char[palabra.length() + 1];
	strcpy(palabra_c, palabra.c_str());

	int final = stem(palabra_c, 0, strlen(palabra_c)-1);
	delete [] palabra_c;
	
	return palabra.substr(0,final);
	
	
}
