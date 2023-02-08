#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{Faux, Vrai} Booleen;
typedef enum{Mr, Mme} Civilite;
typedef enum{studio, chambre, T1, T2} typeLog;

typedef struct {
	char idEtudiant[7]; 
	Civilite civ; 
	char nom[20];
	char prenom[20];
	Booleen bourse; 
	int echelon;
	Booleen handicap;
} Etudiant;

typedef struct {
	char idLogement[7];
	char nomCite[20];
	typeLog type;
	Booleen dispo;
	Booleen handicap;
	Etudiant *occupant;
} Logement;

typedef struct {
	char idDemande[7];
	char nomCite[20];
	Etudiant *etudiant;
	typeLog type;
} Demande;

typedef struct maillon{
	struct maillon *prec;	
	Demande *demande;
	struct maillon *suiv;	
}Maillon,*Liste;

int menu(void);
void global(void);
void affEtudiant(Etudiant a);
void erreur(int e);
Etudiant ** chargementEtudiant(int *nEtudiant, int *maxEtudiant);
Etudiant LireEtudiant(FILE *flot);
void affTabEtudiant(Etudiant **tEtudiant, int nEtudiant);
int rechercheIdEtudiant(Etudiant **tEtudiant,char *id, int nEtudiant);
int rechercheNomEtudiant(Etudiant **tEtudiant, char *nom, int nEtudiant);
void affLogement(Logement a);
Logement lireLogement(FILE *flot,Etudiant **tEtudiant, int nEtudiant);
Logement ** chargementLogement(int *nLogement, int *maxLogement, Etudiant **tEtudiant, int nEtudiant);
void affTabLogement(Logement **tLogement, int nLogement, Booleen affOccupe);
Demande affDemande(Demande a);
Demande lireDemande(FILE *flot, Etudiant **tEtudiant, int nEtudiant);
Liste chargementDemande(int *nDemande, Etudiant** tEtudiant,int nEtudiant, Maillon **tEchelon);
void affListeDemande(Liste l);
Etudiant ecrireEtudiant(char *id);
Etudiant** insertionEtudiant(Etudiant **tEtudiant, int *nEtudiant, int *maxEtudiant);
Demande ecrireDemande(char *id, Etudiant **tEtudiant, int *nEtudiant, int *maxEtudiant);
Liste insertionDemande(Liste lDemande,Maillon **tEchelon,int *nDemande,Etudiant **tEtudiant, int *nEtudiant, int *maxEtudiant);
Liste suppressionDemande(Liste lDemande,char *id,int *nDemande);
Liste traitementDemande(Liste lDemande, Logement **tLogement,int *nDemande, int nLogement);
void liberationLogement(Logement **tLogement,char *id,int nLogement);
void sauvegardeEtudiant(Etudiant **tEtudiant, int nEtudiant);
void sauvegardeLogement(Logement **tLogement, int nLogement);
void sauvegardeDemande(Liste lDemande);