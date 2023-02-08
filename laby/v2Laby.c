#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO

const int largeur = 201;
const int longueur = 35;

void affichage(int tab[longueur][largeur])
{
	
	printf("\n");
	system("clear");
	for(int lo=0;lo<longueur;lo++)
	{
		printf("\n");
		for (int la = 0; la < largeur; la++)
			if(tab[lo][la] == 3 || tab[lo][la] == 5)
				printf(" ");
			else if(tab[lo][la] == 1 || tab[lo][la] == 2 )
				printf("█");
			else if(tab[lo][la] == 7)
				printf("*");
			else if(tab[lo][la] == 8)
				printf("E");

	}
	printf("\n");
	//usleep(20000);
}

void resolution(int tab[longueur][largeur])
{
	int depart, pers[2], fin, i;
	for (i = 0; tab[0][i] != 3; ++i);
	depart = i;
	for (i = 0; tab[longueur-1][i] != 3; ++i);
	fin = i;
	pers[0] = 1;
	pers[1] = depart;
	tab[pers[0]][pers[1]] = 7;

	while(tab[longueur-1][fin] == 3)
	{
		
		if(tab[pers[0]-1][pers[1]] == 3)
		{
			tab[pers[0]][pers[1]] = 7;
			pers[0] -= 1;
			
		}
		else if(tab[pers[0]+1][pers[1]] == 3)
		{
			tab[pers[0]][pers[1]] = 7;
			pers[0] += 1;
		}
		else if(tab[pers[0]][pers[1]-1] == 3)
		{
			tab[pers[0]][pers[1]] = 7;
			pers[1] -= 1;
		}
		else if(tab[pers[0]][pers[1]+1] == 3)
		{
			tab[pers[0]][pers[1]] = 7;
			pers[1] += 1;
		}
		else if(tab[pers[0]-1][pers[1]] == 7)
		{
			tab[pers[0]][pers[1]] = 5;
			pers[0] -= 1;
		}
		else if(tab[pers[0]+1][pers[1]] == 7)
		{
			tab[pers[0]][pers[1]] = 5;
			pers[0] += 1;
		}
		else if(tab[pers[0]][pers[1]-1] == 7)
		{
			tab[pers[0]][pers[1]] = 5;
			pers[1] -= 1;
		}
		else if(tab[pers[0]][pers[1]+1] == 7)
		{
			tab[pers[0]][pers[1]] = 5;
			pers[1] += 1;
		}
		affichage(tab);
	}
	tab[0][depart] = 7;
	tab[longueur-1][fin] = 7;
	affichage(tab);
}

char scan(int nb, char car[nb])
{
	char t;
	while(t=getchar())	
			for(int i = 0; i < nb; i++)
					if (t == car[i])
						return t;
}

void jeu(int tab[longueur][largeur])
{
	int depart, pers[2], fin, i;
	char touche;
	char deplac[4] = {'z','q','s','d'};
	for (i = 0; tab[0][i] != 3; ++i);
	depart = i;
	for (i = 0; tab[longueur-1][i] != 3; ++i);
	fin = i;
	pers[0] = 0;
	pers[1] = depart;
	tab[pers[0]][pers[1]] = 8;


	while(tab[longueur-1][fin] != 8)
	{
		affichage(tab);
		printf("\n");
		touche = 'a';
		
		touche = scan(4, deplac);


		switch(touche)
		{
			case 'z':
				if (tab[pers[0]-1][pers[1]] == 3 && pers[0]!=0)
				{
					tab[pers[0]][pers[1]] = 3;
					pers[0] -= 1;
				}
				break;
			case 's':
				if (tab[pers[0]+1][pers[1]] == 3)
				{
					tab[pers[0]][pers[1]] = 3;
					pers[0] += 1;
				}
				break;
			case 'q':
				if (tab[pers[0]][pers[1]-1] == 3)
				{
					tab[pers[0]][pers[1]] = 3;
					pers[1] -= 1;
				}
				break;
			case 'd':
				if (tab[pers[0]][pers[1]+1] == 3)
				{
					tab[pers[0]][pers[1]] = 3;
					pers[1] += 1;
				}
				break;			
		}
		tab[pers[0]][pers[1]] = 8;
	}

affichage(tab);
	
}


void gen(void)
{

	int tab[longueur][largeur], tete[2], depart[2], cote[4], rdm;
// largeur: --- 	longueur: |
// passage: 0 	mur: 1 		bordure: 2█	queu: 3 

	for(int lo=0;lo<longueur;lo++)
		for (int la = 0; la < largeur; la++)
			if(lo==0 || lo==longueur-1 || la==0 || la==largeur-1)
				tab[lo][la] = 2;
			else tab[lo][la] = 1;

	for(int lo=0;lo<longueur;lo++)
		for (int la = 0; la < largeur; la++)
			if(tab[lo][la] == 1 && la%2 == 1 && lo%2 == 1)
				tab[lo][la] = 0;

	
	tete[0] = rand()%longueur;
	tete[1] = rand()%largeur;
	while(tab[tete[0]][tete[1]]!=0)
	{
		tete[0] = rand()%longueur;
		tete[1] = rand()%largeur;
	}
	depart[0] = tete[0];
	depart[1] = tete[1];
	tab[tete[0]][tete[1]] = 4;


//cote-> 0ha: -1.0 | 1ba: -1.0 | 2ga: 0.-12 | 3dr: 0.+1  

	while(tab[depart[0]][depart[1]] != 3)
	{

		if(tab[tete[0]-1][tete[1]] != 2)
			if(tab[tete[0]-2][tete[1]] == 0)
				cote[0] = 1;
			else cote[0] = 0;
		if(tab[tete[0]+1][tete[1]] != 2)
			if(tab[tete[0]+2][tete[1]] == 0)
				cote[1] = 1;
			else cote[1] = 0;
		if(tab[tete[0]][tete[1]-1] != 2)
			if(tab[tete[0]][tete[1]-2] == 0)
				cote[2] = 1;
			else cote[2] = 0;
		if(tab[tete[0]][tete[1]+1] != 2)
			if(tab[tete[0]][tete[1]+2] == 0)
				cote[3] = 1;
			else cote[3] = 0;


		if(cote[0]+cote[1]+cote[2]+cote[3] != 0)
		{
			rdm = rand()%4;
			while(cote[rdm] != 2)
				if(cote[rdm] == 1)
					cote[rdm] = 2;
				else rdm = rand()%4;
		
			switch(rdm)
			{
				case 0:
					tab[tete[0]-1][tete[1]] = 4;
					tab[tete[0]-2][tete[1]] = 4;
					tete[0] -= 2;
					break;
				case 1:
					tab[tete[0]+1][tete[1]] = 4;
					tab[tete[0]+2][tete[1]] = 4;
					tete[0] += 2;
					break;
				case 2:
					tab[tete[0]][tete[1]-1] = 4;
					tab[tete[0]][tete[1]-2] = 4;
					tete[1] -= 2;
					break;
				case 3:
					tab[tete[0]][tete[1]+1] = 4;
					tab[tete[0]][tete[1]+2] = 4;
					tete[1] += 2;
					break;
			}		
		}
		else for (int i = 0; i < 2; i++)
			{
				tab[tete[0]][tete[1]] = 3;
				if(tab[tete[0]-1][tete[1]] == 4)			
					tete[0]-=1;
				else if(tab[tete[0]+1][tete[1]] == 4)
					tete[0]+=1;
				else if(tab[tete[0]][tete[1]-1] == 4)
					tete[1]-=1;
				else if(tab[tete[0]][tete[1]+1] == 4)
					tete[1]+=1;			
			}

		for (int i = 0; i < 4; ++i)
			cote[i] = 0;	
		affichage(tab);	
	}

	rdm = rand()%largeur;
	while(tab[1][rdm] != 3)
		rdm = rand()%largeur;
	tab[0][rdm] = 3;

	rdm = rand()%largeur;
	while(tab[longueur-2][rdm] != 3)
		rdm = rand()%largeur;
	tab[longueur-1][rdm] = 3;

	//affichage(tab);
	resolution(tab);
	//jeu(tab);
	
}


int main(void)
{


	//system("clear");
	 static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
	srand(time(NULL));
	gen();
	printf("\n");
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}

