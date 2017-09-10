#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <time.h>

#include "include/polymer.h"

int main(int argc, char ** argv)
{
	srand(time(NULL));

	int size = 10;
	int N = 500, samples = 1;
	int x = 0, y = 0;
	double p = 1/4;
	int periodic = 0;
	int c;
	while ((c = getopt(argc, argv, ":s:S:N:p:x:y:b")) != -1)
	{
		switch(c)
		{
		case 's':
			size = atoi(optarg);
			break;
		case 'S':
			samples = atoi(optarg);
			break;
		case 'N':
			N = atoi(optarg);
			break;
		case 'p':
			p = atof(optarg);
			break;
		case 'b':
			periodic = 1;
			break;
		case 'x':
			x = atoi(optarg);
			break;
		case 'y':
			y = atoi(optarg);
			break;
		case '?':
			if (optopt == 's' || optopt == 'S' || optopt == 'N' || optopt == 'p' || optopt == 'y' || optopt == 'x')
				fprintf(stderr, "Option '-%c' requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unkown option '-%c'.\n", optopt);
			else	
				fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
			return 1;
		default:
			abort();	
		}
	}

	int i;
	for (i = optind; i < argc; i++)
		printf("Non-option argument %s\n", argv[i]);

		
	for (i = 0; i < samples; i++)
	{
		polymer * poly = initialize_polymer(size, N, p, periodic, x, y);
		generate_path(poly, i);
		free(poly);
	}

	return 0;
}
