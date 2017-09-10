#ifndef POLYMER
#define POLYMER

typedef enum direction direction;

enum direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

typedef struct polymer polymer;
typedef struct position position;
typedef struct path path;

//Position of head of path
struct position
{
	int x; 
	int y;
};

struct polymer
{
	int size, N;
	int periodic;
	double p;
	position pos;
};

struct path
{
    position pos;
    path * next;
};

/*Functions*/
polymer * initialize_polymer(int size, int N, double p, int periodic, int x, int y);
void generate_path(polymer * poly, int sample);

#endif
