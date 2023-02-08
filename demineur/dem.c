#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <dirent.h> 
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>

const int largeur = 30 + 1;
const int longueur = 16 + 1;

void init(void);
int random1(int min, int max);
char scan(int nb, char car[nb]);
char gen(int pers[2], char tab[longueur][largeur]);
void aff(int pers[2], char tab[longueur][largeur]);
void jeu(int pers[2], char tab[longueur][largeur]);
int testFin(char tab[longueur][largeur]);
void maj(char tab[longueur][largeur]);
int testCase(int Case, int lo, int la, char car, char tab[longueur][largeur]);
void perdu(void);
void debut(int pers[2], char tab[longueur][largeur]);
int verifCase(char car, char tab[longueur][largeur]);
void gagne(void);

int main(void)
{
	int pers[2];
	char tab[longueur][largeur];
	init();
	debut(pers, tab);	
	printf("\n");
	return 0;
}

//0,1,2,3 ect nombre de bombes a cote
//b=bombe v=vide(0 decouvert) t=bombe trouvée r=mauvais drapeau
// c/x = cotés   i=nombre invisible
//fin si plus de b et de r (toutes les bombes trouvées)

void jeu(int pers[2], char tab[longueur][largeur])
{
	while(!testFin(tab))
	{
		char choixTouche[6] = {'z','q','s','d','e','a'};
		int i=0;

		maj(tab);
		aff(pers, tab);
		switch(scan(6,choixTouche))
		{
			case 'z':
				if(pers[0] != 1)
					pers[0]-= 1;
			break;
			case 'q':
				if(pers[1] != 1)
					pers[1]-= 1;
			break;
			case 's':
				if(pers[0] != longueur-2)
					pers[0]+= 1;
			break;
			case 'd':
				if(pers[1] != largeur-2)
					pers[1]+= 1;
			break;
			case 'e':
				if(tab[pers[0]][pers[1]] == 'b')
					perdu();
				if(tab[pers[0]][pers[1]] == 'i')
				{
					tab[pers[0]][pers[1]] = 'a';
					maj(tab);
					if(tab[pers[0]][pers[1]] == '0')
						tab[pers[0]][pers[1]] = 'v';
					maj(tab);
				}
			break;
			case 'a':
				if(tab[pers[0]][pers[1]] == 'b')
					tab[pers[0]][pers[1]] = 't';
				else if(tab[pers[0]][pers[1]] == 't')
					tab[pers[0]][pers[1]] = 'b';
				else if(tab[pers[0]][pers[1]] == 'r')
					tab[pers[0]][pers[1]] = 'i';
				else if(tab[pers[0]][pers[1]] != 'v')
					tab[pers[0]][pers[1]] = 'r';
			break;
		}		
	}
	gagne();
}

// 0:-- 1:-0 2:-+
// 3:0- 	 4:0+
// 5:+- 6:+0 7:++

int testCase(int Case, int lo, int la, char car, char tab[longueur][largeur])
{
	switch(Case)
	{ 
		case 0:
			if(tab[lo-1][la-1] == car)
				return 1;
		break;
		case 1:
			if(tab[lo-1][la] == car)
				return 1;
		break;
		case 2:
			if(tab[lo-1][la+1] == car)
				return 1;
		break;
		case 3:
			if(tab[lo][la-1] == car)
				return 1;
		break;
		case 4:
			if(tab[lo][la+1] == car)
				return 1;
		break;
		case 5:
			if(tab[lo+1][la-1] == car)
				return 1;
		break;
		case 6:
			if(tab[lo+1][la] == car)
				return 1;
		break;
		case 7:
		if(tab[lo+1][la+1] == car)
				return 1;
		break;
	}
	return 0;
}

int testFin(char tab[longueur][largeur])
{
	for(int lo=0;lo<longueur;lo++)
		for(int la=0;la<largeur;la++)
			if(tab[lo][la] == 'b' || tab[lo][la] == 'r' || tab[lo][la] == 'i')
				return 0;
	return 1;
}

void debut(int pers[2], char tab[longueur][largeur])
{
	char choixTouche2[5] = {'z','q','s','d','e'};
	pers[0] = 1;
	pers[1] = 1;

	for(int lo=0;lo<longueur;lo++)
		for(int la=0;la<largeur ;la++)
			if(lo==0 || lo==longueur-1 )
				tab[lo][la] = 'c';
			else if(la==0 || la==largeur-1)
				tab[lo][la] = 'x';
			else tab[lo][la] = '0';
	
	while(1)
	{
		aff(pers,tab);
		switch(scan(5,choixTouche2))
		{
			case 'z':
				if(pers[0] != 1)
					pers[0]-= 1;
			break;
			case 'q':
				if(pers[1] != 1)
					pers[1]-= 1;
			break;
			case 's':
				if(pers[0] != longueur-2)
					pers[0]+= 1;
			break;
			case 'd':
				if(pers[1] != largeur-2)
					pers[1]+= 1;
			break;
			case 'e':
				gen(pers,tab);
			break;
		}
	}
}

void maj(char tab[longueur][largeur])
{
	int tab2[longueur][largeur], num;

	for (int nb = 0; nb < longueur+largeur; ++nb)
	{

		for(int lo=0;lo<longueur;lo++)
			for(int la=0;la<largeur;la++)
				tab2[lo][la] = tab[lo][la];

		for (int deux = 0; deux < 2; ++deux)
			for(int lo=0;lo<longueur;lo++)
				for(int la=0;la<largeur;la++)
					if(!(tab[lo][la]=='b'||tab[lo][la]=='v'||tab[lo][la]=='t'||tab[lo][la]=='r'||tab[lo][la]=='c'||tab[lo][la]=='x'))
					{
						num = 0;
						for(int i=0;i<8;i++)
							if(testCase(i,lo,la,'b',tab) || testCase(i,lo,la,'t',tab))
								num++;

						if(tab2[lo][la] != 'a')
							tab2[lo][la] = 'i';

						if(tab2[lo][la] == 'a')
							if(num == 0)
								tab[lo][la] = 'v';

						for(int a=0;a<8;a++)
								if(testCase(a,lo,la,'v',tab))						
									if(tab[lo][la]=='0')
										tab2[lo][la]='v';
									else tab2[lo][la] = num+48;
					}

		for(int lo=0;lo<longueur;lo++)
			for(int la=0;la<largeur;la++)
				tab[lo][la] = tab2[lo][la];

	}					
}

char gen(int pers[2], char tab[longueur][largeur])
{
	int nbBombe;

	for(int lo=0;lo<longueur;lo++)
		for(int la=0;la<largeur ;la++)
			if(lo==0 || lo==longueur-1 )
				tab[lo][la] = 'c';
			else if(la==0 || la==largeur-1)
				tab[lo][la] = 'x';
			else tab[lo][la] = '0';

	nbBombe = ((longueur-1)*(largeur-1))/10;
	for(int i=0;i<nbBombe;i++)
		tab[random1(1,longueur-2)][random1(1,largeur-2)] = 'b';

	maj(tab);
	for(int i=0;i<8;i++)
		if(testCase(i,pers[0],pers[1],'b',tab))
			gen(pers, tab);

	tab[pers[0]][pers[1]] = 'v';
	maj(tab);
	jeu(pers, tab);

}

void aff(int pers[2], char tab[longueur][largeur])
{
	int num;
	printf("\n");
	system("clear");

	printf("ZQSD: Déplacement\n");
	printf("A: Indiquer bombe\n");
	printf("E: Exploser parcelle\n");
	printf("Fin du jeu si toutes les bombes sont indiquées");
	printf(" et si il n'y a plus de carrés blancs.\n");

	for(int lo=0;lo<longueur;lo++)
	{
		printf("\n");
		for(int la=0;la<largeur;la++)
			if(lo == pers[0] && la == pers[1])
					printf("▒");
			 else if(tab[lo][la] == 'v')
				printf(" ");
			else if(tab[lo][la] == 'c')
				printf("'");
			else if(tab[lo][la] == 'x')
				printf("-");
			else if(tab[lo][la] == 'b' || tab[lo][la] == 'i' || tab[lo][la] == '0')
				printf("█");
			else if(tab[lo][la] == 't' || tab[lo][la] == 'r')
				printf("░");
			else if(tab[lo][la] == 'a' )
			{
				num=0;
				for (int i=0;i<8;i++)
					if(testCase(i,lo,la,'b',tab) || testCase(i,lo,la,'t',tab))
							num++;
				printf("%d", num);
			}
			else printf("%c",tab[lo][la]);//printf("█");
	}
	printf("\n");
}

int verifCase(char car, char tab[longueur][largeur])
{
	for(int lo=0;lo<longueur;lo++)
		for(int la=0;la<largeur ;la++)
			if(tab[lo][la] == car)
				return 1;
	return 0;
}

void gagne(void)
{
	system("clear");
	printf("\t---------------\n");
	printf("\t| Tu as gagné |\n");
	printf("\t---------------\n");
	exit(0);
}

void perdu(void)
{
	system("clear");
	printf("\t---------------\n");
	printf("\t| Tu as perdu |\n");
	printf("\t---------------\n");
	exit(0);
}

char scan(int nb, char car[nb])
{
	char t;
	while(t=getchar())	
		for(int i = 0; i < nb; i++)
			if (t == car[i])
				return t;
}

void init(void)
{
	srand(time(NULL));
	static struct termios oldt, newt;
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON);     
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
}

int random1(int min, int max)
{
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}