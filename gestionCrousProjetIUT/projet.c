#include "projet.h"

//recherche dichotomique d'un etudiant d'un tableau de pointeur d'etudiant.
//On cherche a partir de l'id.
//retourne sa position dans le tableau ou -1 si inexistant
int rechercheIdEtudiant(Etudiant **tEtudiant,char *id, int nEtudiant)
{
	int min=0,max=nEtudiant,moy=-1;
	char *string;
	while(moy!=(min+max)/2)
	{
		moy=(min+max)/2;
		string=tEtudiant[moy]->idEtudiant;
		if(strcmp(string,id)==0)
			return moy;
		else if(strcmp(string,id)<0)
			min=moy;
		else if(strcmp(string,id)>0)
			max=moy;
	}
	return -1;
}

//recher un etudiant par son nom et retourne sa position dans le tableau
int rechercheNomEtudiant(Etudiant **tEtudiant, char *nom, int nEtudiant)
{
	int i;
	for(i=0;i<nEtudiant;i++)
		if(strcmp(tEtudiant[i]->nom,nom)==0)
			return i;
	return -1;
}

//Affiche un etudiant
void affEtudiant(Etudiant a)
{
	char oui[]="Oui", non[]="Non", mr[]="Mr", mme[]="Mme";
	printf("%s ",a.idEtudiant);
	if(a.civ==Mr)
		printf("%s ", mr);
	else printf("%s ", mme);
	printf("%s %s ",a.nom, a.prenom);
	if(a.bourse)
		printf("%s %d ", oui,a.echelon);
	else printf("%s   ", non);
	if(a.handicap)
		printf("%s ", oui);
	else printf("%s ", non);
	printf("\n");
}

//affiche tout les etudiants d'un tableau de pointeur d'etudiant
void affTabEtudiant(Etudiant **tEtudiant, int nEtudiant)
{
	printf("Id  Civilité Nom Prenom Boursier (Bourse) Handicap\n");
	printf("--------------------------------------------------\n");
	for(int i=0;i<nEtudiant;i++)
		affEtudiant(*tEtudiant[i]);
	printf("--------------------------------------------------\n");
}

//Permet de lire un etudiant a partir d'un fichier
Etudiant LireEtudiant(FILE *flot)
{
	char string[50];
	Etudiant a;
	fscanf(flot,"%s%s%*c",&a.idEtudiant,string);
	if(strcmp(string,"Mr")==0)
		a.civ=Mr;
	else a.civ=Mme;
	fgets(a.nom,20,flot);
	a.nom[strlen(a.nom)-1]='\0';
	fgets(a.prenom,20,flot);
	a.prenom[strlen(a.prenom)-1]='\0';
	fscanf(flot,"%s%*c",string);
	if(strcmp(string,"vrai")==0)
	{
		a.bourse=Vrai;
		fscanf(flot,"%d%*c",&a.echelon);
	}
	else{
		a.bourse=Faux;
		a.echelon = 0;
	} 
	fgets(string,5,flot);
	string[strlen(string)] = '\0';
	if(strcmp(string,"vrai")==0)
		a.handicap=Vrai;
	else a.handicap=Faux;
	return a;
}

//insert un etudiant dans la tableau entré en parametre
Etudiant** insertionEtudiant(Etudiant **tEtudiant, int *nEtudiant, int *maxEtudiant)
{
	Etudiant **aux;
	char id[7];
	int num;
	for(int i=0;i<7;i++)
		id[i]='0';
	id[0]='E';
	id[6]='\0';
	num=*nEtudiant+1;
		for(int i=5;i>0;i--)
	{
		id[i]=num%10+48;
		num=num/10;
	}

	if(nEtudiant == maxEtudiant)
	{
		aux = (Etudiant**)realloc(tEtudiant, 5 * (sizeof(Etudiant*)));
		if(aux == NULL)
			erreur(3);

		tEtudiant = aux;
		*maxEtudiant = *maxEtudiant + 5;
	}	

	tEtudiant[*nEtudiant] = (Etudiant *)malloc(sizeof(Etudiant));

	*tEtudiant[*nEtudiant] = ecrireEtudiant(id);
	*nEtudiant = *nEtudiant +1;

	return tEtudiant;
}

//l'utilisateur rempli un etudiant dans le but de l'inserer ensuite
Etudiant ecrireEtudiant(char *id)
{
	Etudiant a;
	strcpy(a.idEtudiant,id);
	int b=0;
	char string[50];
	printf("Nom: ");
	fgets(a.nom,20,stdin);
	a.nom[strlen(a.nom)-1]='\0';
	printf("Prenom: ");
	fgets(a.prenom,20,stdin);
	a.prenom[strlen(a.prenom)-1]='\0';
	printf("Civilité (Mr/Mme): ");
	scanf("%s",string);
	if(strcmp(string,"Mr")==0)
		a.civ=Mr;
	else a.civ=Mme;
	printf("Boursier (0/1)" );
	scanf("%d",&b);
	if(b)
		{

			a.bourse=Vrai;
			printf("Echelon: ");
			scanf("%d",&b);
			a.echelon=b;
		}
	else {
		a.bourse=Faux;
		a.echelon=0;
	}
	b=0;
	printf("Handicap (0/1): ");
	scanf("%d%*c",&b);
	if(b)
		a.handicap=Vrai;
	else a.handicap=Faux;
	return a;
}

//Creation du tableau de pointeur d'etudiant a partir d'un fichier
Etudiant ** chargementEtudiant(int *nEtudiant, int *maxEtudiant)
{
	FILE *flotEtudiant;

	*nEtudiant=0;
	Etudiant **tEtudiant,**aux;

	flotEtudiant = fopen("etudiant","r");
	if(flotEtudiant == NULL)
		erreur(1);

	tEtudiant = (Etudiant **)malloc(sizeof(Etudiant)*5);
	*maxEtudiant=5;
	if(tEtudiant==NULL)
		erreur(2);


	tEtudiant[0] = (Etudiant *)malloc(sizeof(Etudiant));
	*tEtudiant[0] = LireEtudiant(flotEtudiant);
	while(!feof(flotEtudiant))
		{
		*nEtudiant=*nEtudiant+1;
		if(*nEtudiant==*maxEtudiant)
		{
			aux=(Etudiant **)realloc(tEtudiant,(*nEtudiant+5)*sizeof(Etudiant *));
			if(aux==NULL)
				erreur(3);
			tEtudiant=aux;
			*maxEtudiant+=5;
		}
		tEtudiant[*nEtudiant] = (Etudiant *)malloc(sizeof(Etudiant));
		*tEtudiant[*nEtudiant] = LireEtudiant(flotEtudiant);
	}
	fclose(flotEtudiant);
	return tEtudiant;
}

//affiche un logement
void affLogement(Logement a)
{

	printf("%s %s",a.idLogement,a.nomCite);
	switch(a.type){
		case studio: printf(" studio");break;
		case chambre: printf(" chambre");break;
		case T1: printf(" T1");break;
		case T2: printf(" T2");break;
	}
	if(a.dispo)
		printf(" Oui");
	else printf(" Non");
	if(a.handicap)
		printf(" Oui");
	else printf(" Non");
	if(!a.dispo)
		printf(" %s",a.occupant->nom);
	printf("\n");
}

//affiche les logement trié par cité.
//Si affOcuppe est vrai alors affiche seulement les logements occupés
//Si faux affiche tout les logements
void affTabLogement(Logement **tLogement, int nLogement, Booleen affOccupe)
{
	char *string;
	Booleen *tab;

	tab = (Booleen *)malloc(sizeof(Booleen)*nLogement);
	for(int i=0;i<nLogement;i++)
		tab[i] = Vrai;

	printf("Id Cité Type Dispo Handicap Occupant\n");
	printf("-------------------------------------\n");
	for(int i=0;i<nLogement;i++)
	{
		string=tLogement[i]->nomCite;
		for(int a=i;a<nLogement;a++)
			if(tab[a] && strcmp(string,tLogement[a]->nomCite)==0)
			{
				if((affOccupe && !tLogement[a]->dispo) || !affOccupe)
				affLogement(*tLogement[a]);
				tab[a]=Faux;
			}
	}
	printf("-------------------------------------\n");
}

//lecture d'un logement a partir du flot donné
Logement lireLogement(FILE *flot,Etudiant **tEtudiant, int nEtudiant)
{
	int pos;
	Logement a;
	char string[50];
	fscanf(flot,"%s%*c",a.idLogement);
	fgets(a.nomCite,20,flot);
	a.nomCite[strlen(a.nomCite)-1]='\0';
	fscanf(flot,"%s",string);
	if(strcmp(string,"studio")==0)
		a.type=studio;
	else if(strcmp(string,"chambre")==0)
		a.type=chambre;
	else if(strcmp(string,"T1")==0)
		a.type=T1;
	else if(strcmp(string,"T2")==0)
		a.type=T2;
	fscanf(flot,"%s",string);
	if(strcmp(string,"vrai")==0)
		a.dispo=Vrai;
	else a.dispo=Faux;
	fscanf(flot,"%s",string);
	if(strcmp(string,"vrai")==0)
		a.handicap=Vrai;
	else a.handicap=Faux;
	if(a.dispo==Faux)
	{
		fscanf(flot,"%s",string);
		pos=rechercheIdEtudiant(tEtudiant,string,nEtudiant);
		a.occupant=tEtudiant[pos];
	}
	return a;
}

//charge les logements dans la memoire dans un tableau dynamique de pointeur.
Logement ** chargementLogement(int *nLogement, int *maxLogement, Etudiant **tEtudiant, int nEtudiant)
{
	FILE *flotLogement;

	*nLogement=0;
	Logement **tLogement,**aux;

	flotLogement = fopen("logement","r");
	if(flotLogement == NULL)
		erreur(1);

	tLogement = (Logement **)malloc(sizeof(Logement)*5);
	*maxLogement=5;
	if(tLogement==NULL)
		erreur(2);


	tLogement[0] = (Logement *)malloc(sizeof(Logement));
	*tLogement[0] = lireLogement(flotLogement,tEtudiant,nEtudiant);
	while(!feof(flotLogement))
		{
		*nLogement=*nLogement+1;
		if(*nLogement==*maxLogement)
		{
			aux=(Logement **)realloc(tLogement,(*nLogement+5)*sizeof(Logement *));
			if(aux==NULL)
				erreur(3);
			tLogement=aux;
			*maxLogement+=5;
		}
		tLogement[*nLogement] = (Logement *)malloc(sizeof(Logement));
		*tLogement[*nLogement] = lireLogement(flotLogement,tEtudiant,nEtudiant);
	}
	*nLogement=*nLogement+1;
	
	fclose(flotLogement);
	return tLogement;
}

//affiche une demande
Demande affDemande(Demande a)
{
	printf("%s %s ",a.idDemande,a.etudiant->idEtudiant);
	printf("%d ",a.etudiant->echelon );
	printf("%s ",a.nomCite );
	switch(a.type){
		case studio: printf(" studio");break;
		case chambre: printf(" chambre");break;
		case T1: printf(" T1");break;
		case T2: printf(" T2");break;
	}
	printf("\n");
}

//affiche les demandes de la liste
void affListeDemande(Liste l)
{
	printf("IdDemande IdEtudiant Echelon Cité Type\n");
	printf("---------------------------------------\n");
	for(;l != NULL;l = l->suiv)
		affDemande(*(l->demande));
	printf("---------------------------------------\n");
}

//lecture d'une demande a partir d'un flot donné
Demande lireDemande(FILE *flot, Etudiant **tEtudiant, int nEtudiant)
{
	Demande a;
	int pos;
	char string[50];
	fscanf(flot,"%s %s ",a.idDemande,string);
	pos=rechercheIdEtudiant(tEtudiant,string,nEtudiant);
	a.etudiant=tEtudiant[pos];
	fgets(a.nomCite,20,flot);
	a.nomCite[strlen(a.nomCite)-1]='\0';
	fscanf(flot,"%s",string);
	if(strcmp(string,"studio")==0)
		a.type=studio;
	else if(strcmp(string,"chambre")==0)
		a.type=chambre;
	else if(strcmp(string,"T1")==0)
		a.type=T1;
	else if(strcmp(string,"T2")==0)
		a.type=T2;
	return a;
}

//insert une demande dans une liste de pointeur sur demande.
Liste insertionDemande(Liste lDemande,Maillon **tEchelon,int *nDemande,Etudiant **tEtudiant, int *nEtudiant, int *maxEtudiant)
{
	Demande *demande;
	Maillon *m, *suiv, *prec;
	int echelon;

	m=(Maillon *)malloc(sizeof(Maillon));
	demande=(Demande *)malloc(sizeof(Demande));

	char id[7];
	int num;
	for(int i=0;i<7;i++)
		id[i]='0';
	id[0]='D';
	id[6]='\0';
	num=*nDemande+1;
	for(int i=5;i>0;i--)
	{
		id[i]=num%10+48;
		num=num/10;
	}

	*demande=ecrireDemande(id,tEtudiant,nEtudiant,maxEtudiant);
	m->demande=demande;

	
	echelon=m->demande->etudiant->echelon;
	for(; tEchelon[echelon]==NULL && echelon>0 ;echelon--);
	suiv=tEchelon[echelon];
	

	if(suiv!=NULL)
	{
		m->suiv=suiv;
		if(m->suiv->prec!=NULL)
		{
			m->prec=m->suiv->prec;
			printf("%d\n",suiv->demande->etudiant->echelon);
			m->prec->suiv=m;
		}
		m->suiv->prec=m;
	}
	else{
		echelon=m->demande->etudiant->echelon;
		for(; tEchelon[echelon]==NULL && echelon<7 ;echelon++);
		m->prec=tEchelon[echelon];
		m->prec->suiv=m;
	}
	tEchelon[m->demande->etudiant->echelon]=m;
	*nDemande=*nDemande+1;
	if(m->prec==NULL)
		return m;
	return lDemande;
}

//supprime une demande de la liste de pointeur sur demande
Liste suppressionDemande(Liste lDemande,char *id,int *nDemande)
{
	Liste sauv=lDemande;
	while(strcmp(lDemande->demande->idDemande,id)!=0)
	{
		if(lDemande->suiv==NULL)
			erreur(4);
		lDemande=lDemande->suiv;
	}

	if(lDemande->prec!=NULL)
		lDemande->prec->suiv=lDemande->suiv;
	else sauv=lDemande->suiv;
	if(lDemande->suiv!=NULL)
	lDemande->suiv->prec=lDemande->prec;
		
	free(lDemande);
	*nDemande=*nDemande-1;
	return sauv;
}

//l'utilisateur ecrit une demande
Demande ecrireDemande(char *id, Etudiant **tEtudiant, int *nEtudiant, int *maxEtudiant)
{
	Demande a;
	int choix;
	char string[50];

	strcpy(a.idDemande,id);
	printf("Etes vous inscrit en tant qu'étudiant (0/1) ?\n");
	scanf("%d%*c",&choix);
	if(choix)
	{
		printf("Saisissez votre numero étudiant: ");
		scanf("%s%*c",string);
		a.etudiant=tEtudiant[rechercheIdEtudiant(tEtudiant,string,*nEtudiant)];
	}
	else {
		insertionEtudiant(tEtudiant,nEtudiant,maxEtudiant);
	a.etudiant=tEtudiant[*nEtudiant-1];
	printf("Votre numero d'étudiant est: %s\n",a.etudiant->idEtudiant );
	}
	printf("Nom de la cité souhaité: ");
	fgets(a.nomCite,20,stdin);
	a.nomCite[strlen(a.nomCite)-1]='\0';
	printf("Type de logement souahité:\n");
	printf("  1- Studio\n  2- Chambre\n  3- T1\n  4- T2\nVotre choix: ");
	scanf("%d",&choix);
	a.type = choix-1;
	return a;
}

//chargement les demandes dans une liste de pointeurs vers des demandes.
Liste chargementDemande(int *nDemande, Etudiant** tEtudiant,int nEtudiant, Maillon **tEchelon)
{
	FILE *flotDemande;
	Liste l,r;

	flotDemande = fopen("demande","r");
	if(flotDemande == NULL)
		erreur(1);

	l = (Maillon *)malloc(sizeof(Maillon));
	if(l == NULL)
		erreur(2);
	r = l;
	l->demande=(Demande *)malloc(sizeof(Demande));
	*(l->demande) = lireDemande(flotDemande,tEtudiant, nEtudiant);
	l->prec = NULL;
	if(l->demande->etudiant->echelon!=0)
		tEchelon[(l->demande->etudiant->echelon)+1] = l;
	else tEchelon[0] = l;


		
	while(!feof(flotDemande))
	{
		*nDemande=*nDemande+1;
		l->suiv = (Maillon *)malloc(sizeof(Maillon));
		l->suiv->prec = l;
		l = l->suiv;
		l->demande=(Demande *)malloc(sizeof(Demande));
		*(l->demande) = lireDemande(flotDemande,tEtudiant, nEtudiant);
		if(l->demande->etudiant->echelon!=0)
			tEchelon[(l->demande->etudiant->echelon)+1] = l;
		else tEchelon[0] = l;
	}
	*nDemande=*nDemande+1;


	fclose(flotDemande);
	return r;
}

//attribut les logements libres et correspondant aux demandes des etudiants
Liste traitementDemande(Liste lDemande, Logement **tLogement,int *nDemande, int nLogement)
{
	Liste sauv=lDemande;
	char id[7];
	while(lDemande != NULL)
	{
		for(int i=0;i<nLogement;i++)
			if(strcmp(lDemande->demande->nomCite,tLogement[i]->nomCite)==0)
				if(tLogement[i]->dispo)
					if(tLogement[i]->type == lDemande->demande->type)
					{
						tLogement[i]->dispo=Faux;
						tLogement[i]->occupant=lDemande->demande->etudiant;
						sauv=suppressionDemande(sauv,lDemande->demande->idDemande,nDemande);
						printf("Logement %s attribué à l'étudiant %s.\n",tLogement[i]->idLogement,tLogement[i]->occupant->idEtudiant);
					}
		lDemande=lDemande->suiv;
	}
	return sauv;
}

//libere un logement d'un etudiant
void liberationLogement(Logement **tLogement,char *id,int nLogement)
{
	for(int i=0;i<nLogement;i++)
		if(strcmp(id,tLogement[i]->idLogement)==0)
		{
			tLogement[i]->dispo=Vrai;
			tLogement[i]->occupant=NULL;
		}
}

//sauvegarde les etudiants dans le ficher "etudiant"
void sauvegardeEtudiant(Etudiant **tEtudiant, int nEtudiant)
{
	FILE *flotEtudiant;
	flotEtudiant=fopen("etudiant","w+");
	if(flotEtudiant==NULL)
		erreur(1);
	Etudiant a;

	for(int i=0;i<nEtudiant;i++)
	{
		a=*tEtudiant[i];
		char oui[]="vrai", non[]="faux", mr[]="Mr", mme[]="Mme";
		
		fprintf(flotEtudiant,"\n%s\n",a.idEtudiant);
		if(a.civ==Mr)
			fprintf(flotEtudiant,"%s\n", mr);
		else fprintf(flotEtudiant,"%s\n", mme);
		fprintf(flotEtudiant,"%s\n%s\n",a.nom, a.prenom);
		if(a.bourse)
			fprintf(flotEtudiant,"%s\n%d\n", oui,a.echelon);
		else fprintf(flotEtudiant,"%s\n", non);
		if(a.handicap)
			fprintf(flotEtudiant,"%s", oui);
		else fprintf(flotEtudiant,"%s", non);
	}	
}

//sauvegarde les logements dans le fichier "logement"
void sauvegardeLogement(Logement **tLogement, int nLogement)
{
	FILE *flotLogement;
	flotLogement=fopen("logement","w+");
	if(flotLogement==NULL)
		erreur(1);
	Logement a;

	for(int i=0;i<nLogement;i++)
	{
		a=*tLogement[i];
		fprintf(flotLogement,"\n%s\n%s\n",a.idLogement,a.nomCite);
		switch(a.type){
			case studio: fprintf(flotLogement,"studio\n");break;
			case chambre: fprintf(flotLogement,"chambre\n");break;
			case T1: fprintf(flotLogement,"T1\n");break;
			case T2: fprintf(flotLogement,"T2\n");break;
		}
		if(a.dispo)
			fprintf(flotLogement,"vrai\n");
		else fprintf(flotLogement,"faux\n");
		if(a.handicap)
			fprintf(flotLogement,"vrai");
		else fprintf(flotLogement,"faux");
		if(!a.dispo)
			fprintf(flotLogement,"\n%s",a.occupant->idEtudiant);
	}
}

//sauvegarde les demandes dans le fichier "demande"
void sauvegardeDemande(Liste lDemande)
{
	FILE *flotDemande;
	flotDemande=fopen("demande","w+");
	if(flotDemande==NULL)
		erreur(1);
	Demande a;

	for(;lDemande!=NULL;lDemande=lDemande->suiv)
	{
		a=*(lDemande->demande);
		fprintf(flotDemande,"\n%s\n%s\n",a.idDemande,a.etudiant->idEtudiant);
		fprintf(flotDemande,"%s\n",a.nomCite );
		switch(a.type){
			case studio: fprintf(flotDemande,"studio");break;
			case chambre: fprintf(flotDemande,"chambre");break;
			case T1: fprintf(flotDemande,"T1");break;
			case T2: fprintf(flotDemande,"T2");break;
		}
	}
}

//Fonction global stockant les differents tableau et liste. S'occupe de la redirection
void global(void){

	int choix=0, nEtudiant, maxEtudiant, nLogement, maxLogement,nDemande;
	char id[7];
	Maillon *tEchelon[8];
	for(int i=0;i<8;i++)
		tEchelon[i]=NULL;

	Etudiant **tEtudiant;
	Logement **tLogement;
	Liste lDemande;

	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	tLogement = chargementLogement(&nLogement,&maxLogement,tEtudiant,nEtudiant);
    lDemande = chargementDemande(&nDemande,tEtudiant,nEtudiant,tEchelon);

	while(choix != 8)
	{
		choix=menu();
		switch(choix){
			case 1: affTabLogement(tLogement,nLogement,Faux); break;
			case 2: affTabLogement(tLogement,nLogement,Vrai); break;
			case 3: affListeDemande(lDemande); break;
			case 4: lDemande=traitementDemande(lDemande,tLogement,&nDemande,nLogement); break;
			case 5: lDemande=insertionDemande(lDemande,tEchelon,&nDemande,tEtudiant,&nEtudiant,&maxEtudiant); break;
			case 6: printf("ID de la demande a supprimer: ");
					scanf("%s",id);
					lDemande=suppressionDemande(lDemande,id,&nDemande); break;
			case 7:	printf("ID du logement à liberer: ");
					scanf("%s",id);
					liberationLogement(tLogement,id,nLogement); 
					lDemande=traitementDemande(lDemande,tLogement,&nDemande,nLogement); break;
			case 8: printf("Au revoir\n"); break;
			default: printf("Ce choix n'existe pas\n"); break;
			}
	}

	printf("Voulez vous sauvegarder les modification (0/1): ");
	scanf("%d",&choix);
	if(choix==1)
	{
		sauvegardeEtudiant(tEtudiant,nEtudiant);
		sauvegardeLogement(tLogement,nLogement);
		sauvegardeDemande(lDemande);
	}
}

//Affiche un message d'erreur suivant le code en parametre
void erreur(int e)
{
	switch(e){
		case 1: printf("Erreur d'ouverture d'un fichier\n"); exit(1); break;
		case 2: printf("Erreur d'allocation memoire\n"); exit(1); break;
		case 3: printf("Erreur d'agrandissement de tableau\n"); exit(1); break;
		case 4: printf("Erreur, cette demande n'existe pas\n"); exit(1); break;
		case 5: printf("Erreur, ce logement n'existe pas\n"); exit(1); break;
	}
}

//Affiche les choix de menu et retourne le choix de l'utilisateur
int menu(void){
	int choix;
	printf("\n\n\n===== LOGEMENT CROUS =====\n");
	printf("1- Affichage des logements \n");
	printf("2- Affichage des logements occupes \n");
	printf("3- Affichage des demandes \n");
	printf("4- Traitement des demandes \n");
	printf("5- Saisir une demande \n");
	printf("6- Annulation d'une demande\n");
	printf("7- Liberation d'un logement \n");
	printf("8- Quitter\n");
	printf("==========================\n");
	printf("\nChoisissez votre destination: ");
	scanf("%d",&choix);
	return choix;
}



