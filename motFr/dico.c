#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void travailDico(FILE* dico,FILE* nDico){
	int nMot = 0, nFaux = 0, non[50];
	char faux[14] = {133,131,132,140,139,147,148,150,129,130,138,136,137,135}, c;
	char vrai[14] = {'a','a','a','i','i','o','o','u','u','e','e','e','e','c'};

	

	do{
		c= fgetc(dico);
		if(!(c>=97&&c<=122)){
			if(c='\n'){
				nMot++;
			}
			for(int i=0;i<nFaux;i++){
				if(c==non[i]){
					c=0;
				}
			}
			if(c!=0){
				non[nFaux]=c;
				nFaux++;
			}

		}
	}while(!feof(dico));

	for(int i=0;i<nFaux;i++){
		printf("%d\n",non[i] );
		//fprintf(nDico, "%c\n",non[i] );
	}
	//printf("%d\n",nMot );
}


void tableF(FILE* nDico, long tab[27][27][27]){
	long  nLettre=0;
	char c, C0=26, C1=26, C2=26 ;


	for(int i=0; i<27;i++){
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				tab[i][j][k]=0;
			}
			
		}
	}


	do{
		C0 = fgetc(nDico);
		C0-= 97;
		if(C0 == -87 || C0 == -98){
			C0=26;
		}
		if(C1==26){
			C2=C1;
		}

		else{
			nLettre++;
		}
		tab[C2][C1][C0]++;
		C2=C1;
		C1=C0;
	
	}while(!feof(nDico));
	

	/*for(int i=0; i<27;i++){
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				printf("%c: %c: %c: %d\n",i+97, j+97, k+97,tab[i][j][k]);
			}
			
		}
	}
	printf("Nb lettre: %ld\n",nLettre );*/

	return tab;
}

void analyseTab(long tab[27][27][27], float tabF[27][27][27]){
	long nLettre=0, alphabet[27];
	char c;

	for(int i=0;i<27;i++){
		alphabet[i]=0;
	}

	for(int i=0; i<27;i++){	
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				alphabet[k]+=tab[i][j][k];
				nLettre+=tab[i][j][k];
			}
		}
	}
			
	
	/*nLettre-=alphabet[26];
	
	for(int	i=0;i<27;i++){
		c=i+97;
		printf("%c: %ld\n",c,alphabet[i] );
	}
	printf("%ld\n", nLettre);*/


	
	float addLettre = 0;
	for(int i=0; i<27;i++){
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				tabF[i][j][k]=0;	
			}
		}
	}

	for(int i=0; i<27;i++){
		for(int j=0;j<27;j++){
			addLettre=0;
			for(int a=0;a<27;a++){
				addLettre += tab[i][j][a];
			}
			if(addLettre!=0){
				for(int k=0; k<27;k++){
					tabF[i][j][k]=tab[i][j][k]/addLettre;
				}
			}
			
		}
	
	}

	/*for(int i=0; i<27;i++){
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				printf("%c: %c: %c: %.2f\n",i+97, j+97, k+97,tabF[i][j][k]);
			}
			
		}
	}
	printf("Nb lettre: %ld\n",nLettre );*/ 	
}

void genMots(FILE* fDico, float tabF[27][27][27],int nbMots,int longMin, int longMax){
	srand((unsigned int)time(NULL));

	float x, minP, maxP;
	char C0, C1, C2,  mot[100];
	int len;
	int i=0;

	while(i<nbMots){	
			len=0;
			C1=26;
			C2=26;
			do{
				x = (float)rand()/RAND_MAX;
				minP=0;
				maxP=0;
				for(int i=0;i<27;i++){
					maxP+=tabF[C2][C1][i];
					//printf("%f  %f\n",minP,maxP );
					if(x>=minP&&x<maxP){
						C0=i;
						if(C0!=26 && len<100){
							mot[len] = C0+97;
							len++;
						}												
					}
					minP=maxP;					
				}
				C2=C1;
				C1=C0;

			}while(C0!=26);	
			mot[len]=	'\0';
	
			if(len>=longMin && len<=longMax){
				if(fDico==NULL){
				
					  printf("<div class='row mot'><p>%s</p></div>\n",mot);
				}
				else{
					fprintf(fDico, "%s\n",mot );
				}
				
				i++;
			}			
	}
}

int strToNum(char *str){
	int len,res=0;
	for(len=0;str[len]!='\0';len++);
	for(int i=0;i<len;i++){
		res*=10;
		res+=str[i]-48;
	}
	return res;
}

void ecrireFileF(FILE* file, float tabF[27][27][27]){
	for(int i=0; i<27;i++){
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				fprintf(file,"%f\n",tabF[i][j][k]);
			}
			
		}
	}
}

void lireFileF(FILE* file, float tabF[27][27][27]){
	for(int i=0; i<27;i++){
		for(int j=0; j<27;j++){
			for(int k=0;k<27;k++){
				fscanf(file,"%f",&tabF[i][j][k]);
			}
			
		}
	}
}



int main(int argc, char const *argv[])
{
	int nbMot=10, minLong=0, maxLong=20;

	if(argc>=2){
		nbMot=strToNum(argv[1]);
	}
	if(argc>=4){
		minLong=strToNum(argv[2]);
		maxLong=strToNum(argv[3]);
	}



	system("clear");	

	//FILE* dico=NULL;
	FILE* fDico=NULL;
	FILE* fileF=NULL;
   // dico = fopen("/home/andrea/prog/c/dico/dico", "r");
    if(argc==5){
		fDico = fopen(argv[4],"w");
	}
	fileF = fopen("c/fr.f","r");
    

    //long tab[27][27][27];
    float tabF[27][27][27];
    char c;

    //travailDico(dico,nDico);
   // tableF(dico,tab);
    //analyseTab(tab,tabF);
   // ecrireFileF(fileF,tabF);
    lireFileF(fileF,tabF);
    genMots(fDico,tabF,nbMot,minLong,maxLong);
  		

	//travailDico(dico,nDico);
    
   // fclose(dico);
    fclose(fileF);

    if(fDico!=NULL){
    	fclose(fDico);
    }
	return 0;
}