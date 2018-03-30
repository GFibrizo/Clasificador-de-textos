# Clasificador-de-textos
Trabajo práctico para la materia 7506 Organización de Datos de la facultado de Ingeniería de la UBA. Clasificador de textos basado en grupos formados por una etapa de clustering previa.


## Ejecucion

- Compilar ejecutando el comando `make`
- Correr ejecutando `./main -d PATH_A_ARCHIVOS -c CANT_CLUSTERS`

### Argumentos del programa

- -d Directorio en el cual se encuentran los archivos de texto a agrupar en clusters.
- -c Cantidad de clusters deseados.
- -o 'Y' si se desea que un texto pueda pertenecer a mas de un cluster,, 'N' en caso contrario.
- -l Lista todos los documentos y el cluster al que pertenece cada uno
- -g Lista los clusters existentes y los documentos dentro de cada uno.
