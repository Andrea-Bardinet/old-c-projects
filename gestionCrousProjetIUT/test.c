#include "projet.h"

void testAffEtudiant(void){
	Etudiant e={"E00001",Mr,"Bardinet","Andrea",Vrai,7,Faux};
	affEtudiant(e);
}

void testLireEtudiant(void){
	Etudiant a;
	FILE *flot;
	flot=fopen("etudiant","r");
	if(flot==NULL)
		erreur(1);
	a=LireEtudiant(flot);
	affEtudiant(a);
	while(!feof(flot))
	{
		a=LireEtudiant(flot);
		affEtudiant(a);
	}
}

void testChargementEtudiant(void){
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
 	affTabEtudiant(tEtudiant,nEtudiant);
 	printf("%d\n",nEtudiant );
}

void testRechercheIdEtudiant(void){
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant, pos;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	pos = rechercheIdEtudiant(tEtudiant,"E00001",nEtudiant);
	printf("%d\n",pos );
}

void testRechercheNomEtudiant(void){
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant, pos;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	pos = rechercheNomEtudiant(tEtudiant,"Bardinet",nEtudiant);
	printf("%d\n",pos );
}

void testAffLogement(void){
	Etudiant **tEtudiant;
	Logement **tLogement;
	int nEtudiant, maxEtudiant, nLogement, maxLogement;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	tLogement = chargementLogement(&nLogement, &maxLogement,tEtudiant,nEtudiant);
	
	affTabLogement(tLogement,nLogement,Faux);
}

void testLireLogement(void){
	Logement l;
	FILE *flotLogement;
	flotLogement=fopen("logement","r");
	if(flotLogement==NULL)
		erreur(1);
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);

	while(!feof(flotLogement))
	{
	l=lireLogement(flotLogement,tEtudiant,nEtudiant);
	affLogement(l);
	printf("\n");
	}
}

void testChargementLogement(void){
	Logement **tLogement;
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant, nLogement, maxLogement;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	tLogement = chargementLogement(&nLogement,&maxLogement,tEtudiant,nEtudiant);
	affTabLogement(tLogement,nLogement,Faux);
}

void testAffDemande(void){
	Etudiant e={"E00001",Mr,"Bardinet","Andrea",Vrai,7,Faux};
	Demande d={"D00001","Les pins",&e,T1};
	affDemande(d);
}

void testLireDemande(void){
	FILE *flotDemande;
	Demande d;

	flotDemande = fopen("demande","r");
	if(flotDemande == NULL)
		erreur(1);
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);

	while(!feof(flotDemande))
	{
		d=lireDemande(flotDemande,tEtudiant,nEtudiant);
	affDemande(d);
	}
	
}

void testChargementDemande(void){
	Liste l;
	Etudiant **tEtudiant;
	Maillon *tEchelon[8];
	int nDemande, nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	l=chargementDemande(&nDemande,tEtudiant,nEtudiant,tEchelon);
	affListeDemande(l);
}

void testEcrireEtudiant(void){
	Etudiant a;
	a=ecrireEtudiant("E00001");
	affEtudiant(a);
}

void testInsertionEtudiant(void){
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
 	insertionEtudiant(tEtudiant,&nEtudiant,&maxEtudiant);
 	affTabEtudiant(tEtudiant,nEtudiant);
}

void testEcrireDemande(void){
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);

	Demande a;
	a=ecrireDemande("D00001",tEtudiant,&nEtudiant,&maxEtudiant);
	affDemande(a);
	affTabEtudiant(tEtudiant,nEtudiant);
}

void testInsertionDemande(void){
	Liste l;
	Etudiant **tEtudiant;
	Maillon *tEchelon[8];
	int nDemande, nEtudiant, maxEtudiant;

	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	l=chargementDemande(&nDemande,tEtudiant,nEtudiant,tEchelon);
	l=insertionDemande(l,tEchelon,&nDemande,tEtudiant,&nEtudiant,&maxEtudiant);
	affListeDemande(l);
}

void testSuppressionDemande(void){
	Liste l;
	Etudiant **tEtudiant;
	Maillon *tEchelon[8];
	int nDemande, nEtudiant, maxEtudiant;
	char id[7];

	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	l=chargementDemande(&nDemande,tEtudiant,nEtudiant,tEchelon);
	affListeDemande(l);
	printf("ID de la demande a supprimer: ");
	scanf("%s",id);
	l=suppressionDemande(l,id,&nDemande);
	affListeDemande(l);
}

void testTraitementDemande(void){
	Liste l;
	Etudiant **tEtudiant;
	Logement **tLogement;
	Maillon *tEchelon[8];
	int nDemande, nEtudiant, maxEtudiant, nLogement, maxLogement;
	
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	tLogement = chargementLogement(&nLogement,&maxLogement,tEtudiant,nEtudiant);
	l=chargementDemande(&nDemande,tEtudiant,nEtudiant,tEchelon);

	affListeDemande(l);
	l=traitementDemande(l,tLogement,&nDemande,nLogement);
	affListeDemande(l);
}

void testLiberationLogement(void){
	Etudiant **tEtudiant;
	Logement **tLogement;
	int nEtudiant, maxEtudiant, nLogement, maxLogement;
	char id[7];
	
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	tLogement = chargementLogement(&nLogement,&maxLogement,tEtudiant,nEtudiant);

	affTabLogement(tLogement,nLogement,Vrai);
	printf("ID du logement a liberer: ");
	scanf("%s",id);
	liberationLogement(tLogement,id,nLogement);
	affTabLogement(tLogement,nLogement,Vrai);
	affTabLogement(tLogement,nLogement,Faux);
}

void testSauvegardeEtudiant(void){
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant;

	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	sauvegardeEtudiant(tEtudiant,nEtudiant);
}

void testSauvegardeLogement(void){
	Logement **tLogement;
	Etudiant **tEtudiant;
	int nEtudiant, maxEtudiant, nLogement, maxLogement;

	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	tLogement = chargementLogement(&nLogement,&maxLogement,tEtudiant,nEtudiant);

	sauvegardeLogement(tLogement,nLogement);
}

void testSauvegardeDemande(void){
	Liste l;
	Etudiant **tEtudiant;
	Maillon *tEchelon[8];
	int nDemande, nEtudiant, maxEtudiant;
	tEtudiant = chargementEtudiant(&nEtudiant,&maxEtudiant);
	l=chargementDemande(&nDemande,tEtudiant,nEtudiant,tEchelon);
	sauvegardeDemande(l);
}

int main(void)
{
	global();
	//testAffEtudiant();
	//testLireEtudiant();
	//testChargementEtudiant();
	//testRechercheIdEtudiant();
	//testRechercheNomEtudiant();
	//testAffLogement();
	//testLireLogement();
	//testChargementLogement();
	//testAffDemande();
	//testLireDemande();
	//testChargementDemande();
	//testEcrireEtudiant();
	//testInsertionEtudiant();
	//testEcrireDemande();
	//testInsertionDemande();
	//testSuppressionDemande();
	//testTraitementDemande();
	//testLiberationLogement();
	//testSauvegardeEtudiant();
	//testSauvegardeLogement();
	//testSauvegardeDemande();
	return 0;
}