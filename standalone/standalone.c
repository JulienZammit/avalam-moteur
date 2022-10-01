#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#include <topologie.h>
void Json(char file[],const T_Position p,T_Score score);

int main(void) {
	T_Position p; 
	T_ListeCoups l;
	T_Coup coup;
	T_ListeCoups valid;
	T_Score score;

	char file[100]="../web/exemples/refresh-data.js";

	printfdbg("\n------------------- MODE DEBUG ACTIVE -------------------\n");

	printf("Veuillez indiquer le chemin du fichier (tapez entrer pour laisser par défaut, la taille maximal est 100 caractères): ");
	fgets(file,100,stdin);
	int taillefile=strlen(file);
	int compteurcheck=0;
	int chgt=0;
	for (int i = 0; i < taillefile; ++i)
	{
		if(file[0]=='\n'){
			strcpy(file,"../web/exemples/refresh-data.js");
			chgt=1;
		}else if(file[i]==' '){
			compteurcheck++;
		}
	}
	//printf("%d\n",compteurcheck );
	//printf("%d\n", taillefile);
	if (compteurcheck==taillefile-1)
	{
		strcpy(file,"../web/exemples/refresh-data.js");
		chgt=1;
	}if(chgt=1){
		printf("\nUtilisation du repertoire par défaut\n");
	}
	printf("\nChemin du fichier : %s\n", file);
	
	printf0("DEBUG : Création de la position initiale ...\n"); 
	p = getPositionInitiale(); //on stock dans "p" la position initial de tout les pions
	
	printf0("DEBUG : Récupération des coups légaux de la position initiale ...\n"); 
 	l = getCoupsLegaux(p);	//on stock dans "l" la liste des differents coups possibles pour l'utilisateur	

	printf("Aux %ss de jouer !\n", COLNAME(p.trait)); //la fonction COLNAME permet d'alterner la possession


	printf0("DEBUG : Affichage des positions initiales\n");
	afficherPositiondbg(p); //on affiche la position de tout les pions (ici c'est la position initiale)
	
	do
	{
		printf("Veuillez indiquer le point d'origine: "); 
		scanf("%hhd",&coup.origine); //recuperation de la position du pion que l'on veut deplacer (origine)
		
		printf("\nVeuillez indiquer le point de destination: ");
		scanf("%hhd",&coup.destination); //recuperation de la position a laquelle on va deplacer le pion (destination)

		printf0("DEBUG : Execution de la fonction JouerCoup ...\n"); 
		p=jouerCoup(p, coup.origine, coup.destination); //on joue le coup (p prend donc une autre valeur car les pions ce sont déplacés)
		
		afficherPosition(p); //on affiche la position de tout les pions
		
		valid=getCoupsLegaux(p); //on stock dans valid le nombre de coups possibles
		printf("\nIl y a désormais %d coups valides disponibles\n", valid.nb);
		
		score=evaluerScore(p); //on stock dans s le score de la partie
		printf("Score : ");
		afficherScore(score); //puis on l'affiche
		
		if(valid.nb != 0)
		{
			printf("Aux %ss de jouer !\n", COLNAME(p.trait));
		}
		else
		{
			if(score.nbJ<score.nbR)
				printf(" Les ROUGES ont gagné !");
			else if(score.nbJ==score.nbR)
			{
				if(score.nbJ5<score.nbR5)
					printf(" Les ROUGES ont gagné !");
				else if (score.nbJ5==score.nbR5)
					printf(" EGALITE ");
				else
					printf(" Les JAUNES ont gagné !");
			}
			else
				printf(" Les JAUNES ont gagné !");
		}

		//Appel de Json
		printf0("DEBUG : Appel à la fonction json ...\n"); 
		Json(file,p,score);
		
		printf0("DEBUG : Aux %ss de jouer !\n", COLNAME(p.trait));
	}while(valid.nb != 0);
	printf(" PARTIE TERMINE \n");
	return 0;
}

//integration de la fonction json qui créé un fichier json
void Json(char file[],const T_Position p,T_Score score){
	printf0("\nDEBUG : Appel réussi...\n");
	FILE* json=NULL; // pour éviter qu'il pointe n'importe ou au cas ou on arrive pas à ouvrir le fichier
	json=fopen(file, "w+"); // on ouvre le fichier avec w+ pour supprimer le contenu au préalable et récrire à chaque fois, utile car on veut générer un fichier à chaque coup
	if(json != NULL){
		// tous les STR_.. sont dans avalam.h je n'ai fais que suivre ce que le prof a déjà écrit pour la structure json, ca évite d'écrire par exemple \"nb\" on met juste STR_NB avec un %s dans le fprintf et c'est réglé
		fprintf(json,"traiterJson({\n%s:%d,",STR_TURN,p.trait);
		fprintf(json,"\n%s:%d,",STR_SCORE_J,score.nbJ);
		fprintf(json,"\n%s:%d,",STR_SCORE_J5,score.nbJ5);
		fprintf(json,"\n%s:%d,",STR_SCORE_R,score.nbR);
		fprintf(json,"\n%s:%d,\n%s:[",STR_SCORE_R5,score.nbR5,STR_COLS);
		for (int i = 0; i < NBCASES; ++i)
		{
			fprintf(json,"\n\t{%s:%d, %s:%d},",STR_NB,p.cols[i].nb,STR_COULEUR,p.cols[i].couleur);//boucle des positions
		}
		fprintf(json,"]\n});");
	    fclose(json); // on close le fichier à chaque fin d'édition pour libérer la mémoire
	    printf0("\nDEBUG : Création du fichier Json réussi...\n");
	}
	else{
		printf("erreur d'ouverture\n");
	}
}
