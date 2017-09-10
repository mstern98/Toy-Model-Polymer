#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "../include/polymer.h"

/*Functions*/
void trace_polymer(polymer * poly, path * poly_path, path * head, int index);
void print_path(path * head, int sample);
int exists(path * head, position p);

/** Initializes polymer
 * Generates from top right corner.
**/
polymer * initialize_polymer(int size, int N, double p, int periodic, int x, int y)
{
	polymer * poly = (polymer *) malloc(sizeof(polymer));
	poly->size = size;
	poly->N = N;
	poly->p = p;
	poly->pos = (position) {x, y};
	poly->periodic = periodic;
	return poly;
}

void generate_path(polymer * poly, int sample)
{
	
	if (poly == NULL)
	{
		perror("Polymer not initialized\n");
		exit(0);
	}

        path * poly_path = (path *) malloc(sizeof(path));
        path * head = (path *) malloc(sizeof(path));

        poly_path = head;

        trace_polymer(poly, poly_path, head, 1);

        if (head != NULL && head->next != NULL)
		print_path(head, sample);
	free(head);
}

 /**Generates random set of polymers
*/
void trace_polymer(polymer * poly, path * poly_path, path * head, int index)
{
	poly_path->pos = poly->pos;
    	poly_path->next = NULL;

	if (poly->periodic == 0 && (poly->pos.x == 0 || poly->pos.x == poly->size - 1 || poly->pos.y == 0 || poly->pos.y == poly->size - 1))
		return;

	if (index == poly->N)
		return;
	
	position up = (position) {poly->pos.x, (poly->pos.y + 1)%poly->size};
	position down = (position) {poly->pos.x, (poly->pos.y - 1)%poly->size};
	position right = (position) {(poly->pos.x + 1)%poly->size, poly->pos.y};
	position left = (position) {(poly->pos.x - 1)%poly->size, poly->pos.y};	

	int visited = -1;
	direction v_dir[4];
	int new = -1; 
	direction n_dir[4];
	if (exists(head, up))
	{
		visited++;
		v_dir[visited] = UP;
	}
	else
	{
		new++;
		n_dir[new] = UP;
	}
		
	if (exists(head, down))
	{
		visited++;
		v_dir[visited] = DOWN;
	}
	else
	{
		new++;
		n_dir[new] = DOWN;
	}
	if (exists(head, right))
	{
		visited++;
		v_dir[visited] = RIGHT;
	}
	else
	{
		new++;
		n_dir[new] = RIGHT;
	}
	if (exists(head, left))
	{
		visited++;
		v_dir[visited] = LEFT;
	}
	else
	{
		new++;
		n_dir[new] = LEFT;
	}


	double result = (double) rand() / (double) (RAND_MAX + 0);
	direction choice = NONE;

	double upper, lower;	
	if (visited == 1 || visited == 3)
	{
		upper =.25 - (4 - visited) * poly->p;
		lower = .25 + visited * poly->p;

		if (result <= lower)
			choice = v_dir[0];
		else if (result <= lower + upper)
			choice = n_dir[0];
		else if (result <= lower + 2 * upper)
			choice = n_dir[1];
		else
			choice = n_dir[2];
	}
	else if (visited == 2)
	{
		upper = .25 - poly->p;
		lower = .25 + poly->p;
		
		if (result <= lower)
			choice = v_dir[0];
		else if (result <= 2 * lower)
			choice = v_dir[1];
		else if (result <= 2 * lower + upper)
			choice = n_dir[0];
		else
			choice = n_dir[1];
	}	
	else
	{
		direction * temp;
		temp = (visited == 0)? v_dir: n_dir;
		upper = .25;
		lower = .25;
		
		if (result <= upper)
			choice = temp[0];
		else if (result <= 2 * upper)
			choice = temp[1];
		else if (result <= 3 * upper)
			choice = temp[2];
		else 
			choice = temp[3]; 
	}

        poly_path->next = (path *) malloc(sizeof(path));
        position temp = poly->pos;
	poly_path = poly_path->next;

	switch(choice)
	{
	case UP:
		poly->pos = (position) {temp.x, (temp.y + 1)%poly->size};
		break;
	case DOWN:
		poly->pos = (position) {temp.x, (temp.y - 1)%poly->size};
		break;
	case LEFT:
		poly->pos = (position) {(temp.x - 1)%poly->size, temp.y};
		break;
	case RIGHT:
		poly->pos = (position) {(temp.x + 1)%poly->size, temp.y};
		break;
	default:
		break;
	}

	index++;
	trace_polymer(poly, poly_path, head, index);
}

/**Prints path of polymer
 */
void print_path(path * head, int sample)
{
	if (head == NULL)
    	{
        	perror("No path");
        	exit(0);
    	}

    	if (head->next == NULL)
        	return;
	
	char file[50];
    	strcpy(file, "polymer_");
    	sprintf(file + strlen(file), "%d", sample);
    	strcat(file, ".dat");

    FILE * f = fopen(file, "w");

    while(head != NULL)
    { 
        fprintf(f, "%d %d\n", head->pos.x, head->pos.y);
        head = head->next;
    }

    fclose(f);
}

int exists(path * head, position p)
{
	path * temp = (path *) malloc(sizeof(path));
	temp = head;
	while (temp != NULL)
	{
		if (temp->pos.x == p.x && temp->pos.y == p.y)
			return 1;
		temp = temp->next;
	}
	return 0;
}
