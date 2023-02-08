#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paro.h"









int main(int argc, char const *argv[])
{
	FILE *dico;

	dico=fopen("french","r");
	if(dico==NULL){
		printf("Erreur d'ouverture du fichier");
		exit(1);
	}

	unsigned char mot[50];
	unsigned char car[500];
	int nbCar = 0;
	Booleen vu;

	for(int i=0;i<500;i++){
		car[i] = '0';
	}

	do{
		fscanf(dico,"%s",mot);
		for(int i=0;mot[i]!='\0';i++){
			vu=Faux;
			for(int j=0;j<500;j++){
				if(mot[i] == car[j]){
					vu = Vrai;
				}
			}
			if(!vu){
				car[nbCar] = mot[i];
				nbCar++;
				printf("%c\n",mot[i] );
			}
		}

	}while(!feof(dico));

	printf("%d\n",nbCar );



	return 0;
}

/*

b d f k l m n p s t v z g ɲ(gn) r ʃ(ch) ʒ(je) 

a e i o u ø(eu) é ɑ(en) ɔ(on) ɛ(un)

*/