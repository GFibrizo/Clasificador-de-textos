#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>

int main1 (int argc, char **argv) {

	bool one_flag = false;
	bool g_flag = false;
	bool a_flag = false;
	char *d_value = NULL;
	char *c_value = NULL;
	char *o_value = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt (argc, argv, "d:c:o:1ga")) != -1) {
		switch (c) {

			case 'd':
				d_value = optarg;
				break;

			case 'c':
				c_value = optarg;
				break;

			case 'o':
				o_value = optarg;
				break;

			case '1':
				one_flag = true;
				break;

			case 'g':
				g_flag = true;
				break;

			case 'a':
				g_flag = true;
				break;

			case '?':
				if (optopt == 'd')			fprintf (stderr, "Option -%d requires an argument.\n", optopt);
				else if (isprint (optopt))	fprintf (stderr, "Unknown option `-%d'.\n", optopt);
				else 						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

				if (optopt == 'c')			fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))	fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else 						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

				if (optopt == 'o')			fprintf (stderr, "Option -%o requires an argument.\n", optopt);
				else if (isprint (optopt))	fprintf (stderr, "Unknown option `-%o'.\n", optopt);
				else 						fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);

				return 1;
			
			default:
				abort ();
		}
	}

	//Este printf es solo para probar que el parseo anda bien imprimiendo las variables en pantalla
	printf ("d_value = %s, c_value = %s, o_value = %s, one_flag = %d, g_flag = %d, a_flag = %d\n", 
																d_value, c_value, o_value, one_flag, g_flag, a_flag);

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);
	return 0;
}
