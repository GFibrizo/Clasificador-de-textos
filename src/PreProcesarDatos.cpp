/*
 * PreProcesarDatos.cpp
 *
 *  Created on: 03/11/2013
 *      Author: agu
 */

#include "PreProcesarDatos.h"
typedef map<string,int> hash;
typedef map<string,float> hash2;

void PreProcesarDatos::relative_dir_base_split(const string& path, string& dir)
{
	std::string::size_type slash_pos = path.rfind("/"); //Encuentra la barra
	
	if (slash_pos != std::string::npos) { //Si hay una barra
		slash_pos++;
		dir = path.substr(0, slash_pos); //Directorio esta antes de la barra
		
	} else { //Sino, no hay directorio
		dir.clear();
	}
}

/**********************************************************************/
/**********************************************************************/


PreProcesarDatos::PreProcesarDatos(const char* ruta) {
	this->invalidos= "¡!#$%&'(	 )*+,‘’”“-.:;<=>¿?@[]^_`{|}~/\\\"\n´~ÑÞ`1234567890\0";//[CANT_DE_SEPARADORES]
	LectorDirectorios * lecDirectorio= new LectorDirectorios(); //no olvidar delete.
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

/**********************************************************************/
/**********************************************************************/


PreProcesarDatos::~PreProcesarDatos() {

	delete this->verifStopWord;
	//delete this->manejador;
	archivoHashSecundario.close();
}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::pasarAminusculas(string& str){
     transform(str.begin(), str.end(), str.begin(), ::tolower);
}

/**********************************************************************/
/**********************************************************************/

//Si la clave no esta en el hash, la agrega asociada a un valor 0.
//Si la clave esta en el hash, aumenta en 1 el valor asociado.
void PreProcesarDatos::agregarElementoAHash(hash& hash, string clave){

	if (hash.count(clave) > 0){
		 hash[clave]=hash[clave]+ 1;
		 return;
	}
	hash[clave] = 1;
}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::agregarElementoAHashPrincipal(hash& hash,string clave, bool cambio_doc){
	
	if (hash.count(clave) == 0) hash[clave] = 1;
	
	if (cambio_doc){
		hash[clave]=hash[clave]+ 1;	//aumento cant de docs
		return;
	}
}

/**********************************************************************/
/**********************************************************************/


string PreProcesarDatos::numberToString(int number){
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}

string PreProcesarDatos::numberToString(float number){
	stringstream ss;
	ss << number;
	string str = ss.str();
	return str;
}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::escribirArchivoDeHash(hash hash){
	string aux;
	for (hash::iterator it= hash.begin(); it != hash.end(); it++){
		aux.operator =(it->first);
		aux.append(",");
		aux.append(this->numberToString(it->second));
		aux.append(" ");
		this->archivoHashSecundario << aux;
	}

	this->archivoHashSecundario << ",//,";

}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::escribirArchivoIndice(hash2 hash, ofstream& archivoIndice){

	string aux;
	archivoIndice.setf( ios::fixed, ios::floatfield );
	archivoIndice.precision(5);
	for (hash2::iterator it= hash.begin(); it != hash.end(); it++){
		archivoIndice << it->second <<",";
	}
	archivoIndice << endl;

}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::preProcesarDatos(){
	string auxLinea;
	string palabra;
	unsigned int i;
	unsigned int ant_i = -1;

	for (i = 0; i < this->vector_archivos.size(); i++){
		
		if (this->vector_archivos[i].compare(".svn") == 0) continue;
		//COUT prueba para ver que archivos se recupero en el directorio
		cout<<"Archivo: "<<this->vector_archivos[i]<<endl;
		this->manejador = new ManejadorArchivos() ;
		this->manejador->abrirLectura(this->directorio+this->vector_archivos[i]);
		
		while ( this->manejador->leerUnaLinea(auxLinea)){

			char *linea = new char[512];
			strcpy(linea, auxLinea.c_str()); //
			//auxPalabra va a ir conteniendo cada palabra sacando los tokens
			char* auxPalabra = strtok(linea,this->invalidos);

			while ( auxPalabra != NULL ) {
					palabra = auxPalabra;
					pasarAminusculas(palabra);
					
					//veo si es un stopword y sino lo agrego a hashes:
					if(!this->verifStopWord->verificarPalabra(palabra)){
						palabra = stem_palabra(palabra);
						//COUT
						cout<<palabra<<endl;
						agregarElementoAHashPrincipal(this->hashPrincipal, palabra, i != ant_i);
						agregarElementoAHash(this->hashSecundario, palabra);
					}
					auxPalabra = strtok (NULL, this->invalidos);
					ant_i = i;
			}
			delete []linea;
			delete auxPalabra;
		} //termina de trabajar con ese archivo
		
		delete this->manejador;		
		escribirArchivoDeHash(this->hashSecundario);
		//referencio la variable hash_secundario a un nuevo hash de un nuevo archivo
		hash nuevoHash;
		this->hashSecundario = nuevoHash;
	}
	this->archivoHashSecundario << "!,";
	this->archivoHashSecundario.close();
	generarIndiceDocumentos();
	
	//CERRAR ARCHIVO DE HASH SECUNDARIO

}

/**********************************************************************/
/**********************************************************************/


const char* PreProcesarDatos::getInvalidos(){
	return this->invalidos;
}

/**********************************************************************/
/**********************************************************************/


void PreProcesarDatos::generarIndiceDocumentos(){
	
	string auxLinea;
	this->manejador = new ManejadorArchivos(); //posible perdida de memoria.
	this->manejador->abrirLectura(DIR_FILE_HASH_2);
	ofstream indiceDocumentos;
	indiceDocumentos.open(DIR_FILE_INDICE_FINAL, ios_base::out | ios_base::app);
	hash2 hashDocsEnMemoria = generarHashMemoria();//posible perdida de memoria
	string clave;
	char* aux;
	float frecuencia = 0;
	int largo;
	string fin = "!";
	const char* fin1 = fin.c_str();
	bool flag = false;

	while ( this->manejador->leerUnaLinea(auxLinea)){
	
		char *linea = new char[512];
		strcpy(linea, auxLinea.c_str());
		largo = strlen(linea);
		aux = strtok(linea, ", ");

		while ((aux != NULL) and (strcmp(aux,fin1) != 0)) {
			
			clave = aux;
			
			if (clave.compare("//") == 0){
				escribirArchivoIndice(hashDocsEnMemoria, indiceDocumentos);
				hash2 nuevoHash = generarHashMemoria();//posible perdida de memoria.
				hashDocsEnMemoria = nuevoHash;//hay que borrar el anterior primero.
				aux = strtok(NULL, ", ");
				continue;
			}
			
			frecuencia = atof(strtok(NULL, ", "));
			hashDocsEnMemoria[clave] = calcular_TF_IDF(clave, frecuencia);
			aux = strtok(NULL, ", ");
		}
		//delete []linea; //SEGURO FALTA ESTO
	}
	indiceDocumentos.close();
}

/**********************************************************************/
/**********************************************************************/


hash2 PreProcesarDatos::generarHashMemoria() {
	
	hash2 hashDocsEnMemoria;
	
	for (hash::iterator it= hashPrincipal.begin(); it != hashPrincipal.end(); it++){
		hashDocsEnMemoria[it->first] = 0;
	}
	return hashDocsEnMemoria;
}

/**********************************************************************/
/**********************************************************************/


float PreProcesarDatos::calcular_TF_IDF(string clave, float frecuencia){
	
	return (frecuencia * log10f( (vector_archivos.size()-1)) / (hashPrincipal[clave]));
	
}

/**********************************************************************/
/**********************************************************************/


string PreProcesarDatos::stem_palabra(string palabra){
	
	char *palabra_c = new char[palabra.length() + 1];
	strcpy(palabra_c, palabra.c_str());

	int final = stem(palabra_c, 0, strlen(palabra_c)-1);
	delete [] palabra_c;
	
	return palabra.substr(0,final);
		
}
