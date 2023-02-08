#include "laby.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bmp.h"

void initLaby(Laby *laby, int taille){
	if(taille<3){
		taille=3;
	}
	if(taille%2==0){
		taille++;
	}

	laby->taille = taille;
	laby->nbNum = 0;
	laby->matrice =(Case ***)malloc(sizeof(Case **)*taille);

	for(int i=0; i<taille; i++){
		laby->matrice[i] = (Case **)malloc(sizeof(Case *)*taille);
		for(int j=0; j<taille;j++){
			laby->matrice[i][j] = (Case *)malloc(sizeof(Case)*taille);	
			if(i%2==1 && j%2==1){
				laby->matrice[i][j]->type=Vide;
				laby->matrice[i][j]->numero=laby->nbNum;
				laby->nbNum++;	
			}
			else{
				laby->matrice[i][j]->type=Mur;
			}
			laby->matrice[i][j]->spec=Vierge;
		}
	}
}

/*----------------------------------------------
haut = i+2   droite = j+2    bas = i-2    gauche = j-2
------------------------------------------------*/

void genLaby(Laby *laby, Point point){
	Booleen tab[4];
	Point point2;
	int r;

	laby->matrice[point.i][point.j]->spec = Visite;

	testCote(laby,&point,tab);
	while(tab[0]||tab[1]||tab[2]||tab[3]){
		point2 = point;
		for(r=rand()%4;!tab[r];r=rand()%4);
		switch(r){
			case 0: point2.i++; laby->matrice[point2.i][point2.j]->type=Vide; point2.i++; break;
			case 1: point2.j++; laby->matrice[point2.i][point2.j]->type=Vide; point2.j++; break;
			case 2: point2.i--; laby->matrice[point2.i][point2.j]->type=Vide; point2.i--; break;
			case 3: point2.j--; laby->matrice[point2.i][point2.j]->type=Vide; point2.j--; break;
		}
		genLaby(laby,point2);

		testCote(laby,&point,tab);
	}
}

void afficherLaby(Laby *laby){
	for(int i=0; i<laby->taille; i++){
		for(int j=0; j<laby->taille;j++){
			switch(laby->matrice[i][j]->type){
				//case Vide: printf("%d",laby->matrice[i][j]->numero);break;
				case Vide: printf(" ");break;
				case Mur: printf("█");break;
			}
		}
		printf("\n");
	}
}

void testCote(Laby *laby, Point *point, Booleen *tab){
	for(int i=0;i<4;i++){
		tab[i]=Faux;
	}	

	Point point2 = *point;
	
	point2.i+=2;
	if(point2.i < laby->taille)
		tab[0] = testCase(laby,point2);
	point2.i-=2;

	point2.j+=2;
	if(point2.j < laby->taille)
		tab[1] = testCase(laby,point2);
	point2.j-=2;

	point2.i-=2;
	if(point2.i >= 0)
		tab[2] = testCase(laby,point2);
	point2.i+=2;

	point2.j-=2;
	if(point2.j >= 0)
		tab[3] = testCase(laby,point2);
}

Booleen testCase(Laby *laby, Point point){
	//Case fcase = laby->matrice[point.i][point.j];
	if(laby->matrice[point.i][point.j]->spec == Vierge){
		return Vrai;
	}
	return Faux;
}

void labyToBmp(Laby *laby){
	int taille = laby->taille;

    unsigned char image[taille][taille][3];
    char* imageFileName = "laby.bmp";

    int i, j;
    for(i=0; i<taille; i++){
        for(j=0; j<taille; j++){
        	if(laby->matrice[i][j]->spec==Debut){
        		image[i][j][2] = 0; ///red
            	image[i][j][1] = 255; ///green
            	image[i][j][0] = 0; ///blue
        	}
        	else if(laby->matrice[i][j]->spec==Fin){
        		image[i][j][2] = 255; ///red
            	image[i][j][1] = 0; ///green
            	image[i][j][0] = 0; ///blue
        	}
        	else if(laby->matrice[i][j]->type==Vide){
        		image[i][j][2] = 255; ///red
            	image[i][j][1] = 255; ///green
            	image[i][j][0] = 255; ///blue
        	}
        	else{
        		 image[i][j][2] = 150; ///red
           		image[i][j][1] = 50; ///green
            	image[i][j][0] = 50; ///blue
        	}
           
        }
    }

    generateBitmapImage((unsigned char *)image, taille, taille, imageFileName);
}

int main(int argc, char const *argv[])
{
	system("clear");
	if(argc<=1){
		printf("Donnez au minimum une longueur en argument\n");
		exit(1);
	}

	srand(time(NULL));

	Laby labyrinth;
	Laby *laby = &labyrinth;
	

	Point depart = {1,1};

	initLaby(laby,strtol(argv[1],NULL,10));

	laby->matrice[laby->taille-1][1]->spec=Debut;
	laby->matrice[laby->taille-1][1]->type=Vide;
	laby->matrice[0][laby->taille-2]->spec=Fin;
	laby->matrice[0][laby->taille-2]->type=Vide;

	genLaby(laby,depart);
	afficherLaby(laby);
	labyToBmp(laby);

	return 0;
}

void debug(int num){
	printf("-------------------- %d --------------------\n",num);
}
