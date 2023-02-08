typedef enum{Faux, Vrai} Booleen;
typedef enum{Vide, Mur} Type;
typedef enum{Debut, Fin, Vierge, Visite} Spec;

typedef struct {
	int i;
	int j;
} Point;

typedef struct {
	Type type;
	Spec spec;
	int numero;
} Case;

typedef struct {
	int taille;
	int nbNum;
	Case ***matrice;
} Laby;



void initLaby(Laby *laby, int taille);
void afficherLaby(Laby *laby);
void testCote(Laby *laby, Point *point, Booleen *tab);
Booleen testCase(Laby *laby, Point point);
void genLaby(Laby *laby, Point point);
void debug(int num);