#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avalam.h>
#define TAILLE 80
#define TAILLE_DESCRIPTION 255
#define MAXLECTUREDESC 1024

// checker si c'est un nombre
#include <ctype.h>

void Json(char formatnb[],char formatcolor[],int trait,char description[],int numfen);
char *formater(char * ch);
char *diag_interpret(char * fen,char * description,int numfen);

int main(int listparams, char *params[]) {

	printfdbg("\n------------------- MODE DEBUG ACTIVE -------------------\n");

	char fen[TAILLE];
	char numdiag[20];
    int numfen=0;
    fen[0]='\0';
    char lecturedescription[MAXLECTUREDESC]="";
	char description[TAILLE_DESCRIPTION];

	if(listparams>3){
		printf("\nVous ne devez pas indiquer plus de 3 paramètres ! (exemple: ./diag.exe \"1\" \"fen\")\n\n");
		return 0;
	}

	if (params[1]==NULL)
    	{
    	printf("\nErreur : Veuillez entrer un numéro pour le fen en paramètre ! (exemple: ./diag.exe \"1\" \"fen\")\n\n");
    	return 0;
    	}

	if (params[2]==NULL)
   	{
    	printf("\nErreur : Veuillez entrer un type fen en paramètre ! (exemple: ./diag.exe \"1\" \"fen\")\n\n");
    	return 0;
    	}

    	strcpy(fen,params[2]);

    int tailletest=strlen(fen);
    int checkzero=0;
    for (int i = 0; i < tailletest; ++i) // gerer le cas d'une chaine de 0
    {
    	if(fen[i]=='0'){
    		checkzero++;
    	}
    }
    if (tailletest==checkzero)
    {
    	strcpy(fen,"v j");
    }

    strcpy(numdiag,params[1]);
    numfen=atoi(numdiag);

    //description
    description[0]='\0';

    while(fgets(lecturedescription, MAXLECTUREDESC, stdin) != NULL)
    {
    	printfdbg("Debug : Chaine lu : %s\n", lecturedescription);
    	printfdbg("Debug : Chaine description : %s\n", description);
    	printfdbg("Debug : Taille de la description : %d\n", (int) strlen(description));
    	strncat(description,lecturedescription, TAILLE_DESCRIPTION - strlen(description) -1); // on retire la taille de la description et 1 pour ne passer dépasser la tailel de l'espace mémoire et pour garder un caractère pour le caractère de fin
    }

    int j=0;
    int i=0;
    int tailledescription=(int) strlen(description);
    //printf("%d\n", tailledescription);
    for (i = 0; i <= tailledescription; ++i){
    	//printf("%d\n", i);
    		if (description[i]=='\n'){
    			printfdbg("Debug : Saut de ligne détecté %d\n", i);
    			//strcpy(lecturedescription[i],"<br>");
    			//char aux[TAILLE_DESCRIPTION];
    			char savedesc[MAXLECTUREDESC];
    			strcpy(savedesc,description);
    			printfdbg("Debug : s\n", savedesc);
    			description[i]='<'; 
    			description[i+1]='b'; 
    			description[i+2]='r'; 
    			description[i+3]='>'; 
    			tailledescription = tailledescription + 3;  //on a agrandi la chaine il ne faut pas oublier de le spécifier
    			for (j = i; j <= tailledescription; ++j){
    				//printf("%d\n", j);
    				//printf("%s\n", description);
    				description[j+4]=savedesc[j+1];
    				description[j+5]='\0';
    			}
    			//description[tailledescription-1] = '\0';  //on supprime le <br> en trop
    			printfdbg("Debug : %s\n", description);
    		}

    }
    if(description[tailledescription-1] == '>')
    {
    	description[tailledescription-4] = '\0';  //on supprime le <br> en trop
    }

    printf("\nChaine description : %s\n", description);

	//printf("\nVeuillez entrer la description de ce FEN (taille maximum de 255 caractères) : ");
	//fgets(description,TAILLE_DESCRIPTION,stdin);

    diag_interpret(fen,description,numfen);

}


char *diag_interpret(char * fen,char * description,int numfen){
	for (int u = 0; u < TAILLE_DESCRIPTION; ++u) // correction bug du saut de ligne pour la description
	{
		if (strcmp(&(description[u]),"\n")==0)
		{
			strcpy(&(description[u]),"\0");
		}
	}
	strcpy(fen,formater(fen));
	//printf("Type FEN format : %s\n", fen);

	//char fen[50]="ud3tUDU14DUuuTc1vv r";

	char formatnb[49];
	char formatcolor[49];
	int trait=0;

	printfdbg("Le FEN : %s\n", fen);
	int c=0;//compteur d'ajout dans formatnb et formatcolor pour bien avoir les 48 cases, il est utile pour l'ajout des cases vides pour pouvoir placer 19 cases vides et pas une case vide + 9 cases vide qui était le bug rencontré
	//fin du head
	for (int i = 0; i < 50; ++i)
	{
		if (fen[i]=='u' || fen[i]=='d' || fen[i]=='t' || fen[i]=='q' ||fen[i]=='c')
		{
			if(fen[i]=='u'){
				strcpy(&(formatnb[c]),"1");
				strcpy(&(formatcolor[c]),"1");
				c++;
			}else if(fen[i]=='d'){
				strcpy(&(formatnb[c]),"2");
				strcpy(&(formatcolor[c]),"1");
				c++;
			}else if(fen[i]=='t'){
				strcpy(&(formatnb[c]),"3");
				strcpy(&(formatcolor[c]),"1");
				c++;
			}else if(fen[i]=='q'){
				strcpy(&(formatnb[c]),"4");
				strcpy(&(formatcolor[c]),"1");
				c++;
			}else if(fen[i]=='c'){
				strcpy(&(formatnb[c]),"5");
				strcpy(&(formatcolor[c]),"1");
				c++;
			}
		}else if(fen[i]=='U' || fen[i]=='D' || fen[i]=='T' || fen[i]=='Q' ||fen[i]=='C')
		{
			if(fen[i]=='U'){
				strcpy(&(formatnb[c]),"1");
				strcpy(&(formatcolor[c]),"2");
				c++;
			}else if(fen[i]=='D'){
				strcpy(&(formatnb[c]),"2");
				strcpy(&(formatcolor[c]),"2");
				c++;
			}else if(fen[i]=='T'){
				strcpy(&(formatnb[c]),"3");
				strcpy(&(formatcolor[c]),"2");
				c++;
			}else if(fen[i]=='Q'){
				strcpy(&(formatnb[c]),"4");
				strcpy(&(formatcolor[c]),"2");
				c++;
			}else if(fen[i]=='C'){
				strcpy(&(formatnb[c]),"5");
				strcpy(&(formatcolor[c]),"2");
				c++;
			}
		}else if (isdigit(fen[i])){//is digit verifie si dans la chaine l'élement est un chiffre on aurait pu aussi faire une vérification compris entre 1 et 9

			int size=strlen(fen);//strlen compte le nombre de caractère o, récupère donc la taille de la chaine
			int k=0;
			int j=i;
			char extractnumber[48];
			int aux;
			int stop=0;

			do{
				k++;
				if(aux>k){//l'objectif est de vérifier si le k précédant est plus grand que le k suivant c'est à dire si on a fini de lire le chiffre en entier, par exemple si le chiffre est 195 on va le lire et on a k=195 et à la prochaine occurance on aura k=95 et donc k précédant est supérieur à k suivant donc on a finit de lire le chiffre 
					stop=1; //pour marquer la fin de lecture du chiffre on utilise la variable stop en booleen
				}
				j++;
			}while(isdigit(fen[j])!=0 && j<size);//is digit verifie si dans la chaine l'élement est un chiffre on aurait pu aussi faire une vérification compris entre 1 et 9
			aux=k;
			stop=0;

			//DEBUG
			printfdbg("Debug compteur de chiffre (pour chaque passage de i) : %d\n", k);
			int z=0;
			for (j=i; j < i+k; ++j)
			{
				if(stop!=1){//on extrait pas le nombre car il est terminé
					extractnumber[z]=fen[j];
					z++;
				}
			}
			extractnumber[z]='\0';//on marque bien la fin du chiffre avec le caractère de fin pour éviter d'avoir des soucis

			// DEBUG
			printfdbg("Debug Extract number : %s\n", extractnumber);

			int convert=atoi(extractnumber);// la fonction atoi converti une chaine de caractère en int

			//DEBUG
			printfdbg("Debug Convert : %d\n", convert);

			for (j = i; j < i+convert; ++j)
			{
				strcpy(&(formatnb[c]),"0"); //
				strcpy(&(formatcolor[c]),"0");
				c++;
			}




		}else if (fen[i]=='v'){
			strcpy(&(formatnb[c]),"0"); //
			strcpy(&(formatcolor[c]),"0");
			c++;
		}else if(fen[i]=='j'){
			trait=1;
		}else if(fen[i]=='r'){
			trait=2;
		}
		//DEBUG
		printfdbg("\nDebug : Format nb : %s\n", formatnb);
		printfdbg("Debug : Format color : %s\n", formatcolor);
	}

	printf("\nLa chaine a été formaté pour l'export json !");
	printf("\nFormat nb : %s\n", formatnb);
	printf("Format color : %s\n", formatcolor);
	printf("Le trait est : %d\n", trait);

	//printf("%c\n", formatnb[1]);

	//Appel de Json
	printfdbg("Debug : Appel de la fonction json export\n");
	Json(formatnb,formatcolor,trait,description,numfen);
}





//integration de la fonction json qui créé un fichier json

// on réutilise la fonction Json de standalone.c en l'ayant adapté avec nos nouvelles variables

void Json(char formatnb[],char formatcolor[],int trait,char description[],int numfen){
	printfdbg("Debug : Appel de la fonction json export réussi ! \n");
	FILE* json=NULL; // pour éviter qu'il pointe n'importe ou au cas ou on arrive pas à ouvrir le fichier
	json=fopen("../web/exemples/diag_initial.js", "w+"); // on ouvre le fichier avec w+ pour supprimer le contenu au préalable et récrire à chaque fois, utile car on veut générer un fichier à chaque coup
	if(json != NULL){
		// tous les STR_.. sont dans avalam.h je n'ai fais que suivre ce que le prof a déjà écrit pour la structure json, ca évite d'écrire par exemple \"nb\" on met juste STR_NB avec un %s dans le fprintf et c'est réglé
		fprintf(json,"traiterJson({\n%s:%d,",STR_TURN,trait);
		fprintf(json,"\n\"numDiag\":%d,",numfen);
		fprintf(json,"\n\"notes\":\"%s\",",description);
		fprintf(json,"\n%s:[",STR_COLS);
		for (int i = 0; i < NBCASES; ++i)
		{
			fprintf(json,"\n\t{%s:%c, %s:%c},",STR_NB,formatnb[i],STR_COULEUR,formatcolor[i]);//boucle des positions
			//printf("\n%c\n%c", formatnb[i],formatcolor[i]);
		}
		fprintf(json,"\n]\n});");
	    fclose(json); // on close le fichier à chaque fin d'édition pour libérer la mémoire
	    printf("\n => Export Json terminé (chemin de fichier : ../web/exemples/diag_initial.js) ! \n");
	}
	else{}
}


char *formater(char * ch)
{

	int i=0, j=0, k=0, etat=1;
	int multiplicator;
	int minicompteur;
	int compteur;
	int nbchara;
	char newfen[TAILLE];
	char newfen2[TAILLE];
	char rajout[TAILLE];
	int taillechaine = 0;
	int difference;
	char aux[3];
	char nb[3];
	int test;

	// ETAPE 1 //


	do			//boucle faites par MrKubiak lors du tp 4 -> remplace les tabs par des espaces et supprime les espaces en trop
	{
  		switch (etat)
  		{
    			case 1:
    			if (ch[j]!=' ' && ch[j]!='\t')  //si le charactere est different d'un espace ou d'une tabulation
    			{
    				etat=2; 
    				ch[i++]=ch[j++];
    			}
    			else if (ch[j]==' ' || ch[j]=='\t')  //si le charactere est egal a une tabulation ou a un espace
    			{
    				j++;
    				etat=1;
    			}
    			else if (ch[j]=='\0')
     			{
      	  			if (i>0 && ch[i-1]==' ') ch[i-1]=ch[j];
        			else {ch[i]=ch[j]; etat=3;}
      			}
      		break;

    			case 2:
    			if (ch[j]!=' ' && ch[j]!='\t')  
    			{
    				ch[i++]=ch[j++];
    			}
    			if (ch[j]==' ' || ch[j]=='\t') 
    			{
    				j++;
    				etat=1;
    				ch[i++]=' ';
    			}
    			if (ch[j]=='\0') 
    			{
    				etat=3; ch[i]=ch[j];
    			}
    			break;
  		}
	}while(etat!=3);  //fin de ce qu'a fait kubkub, a partir d'ici on a recuperé la chaine sans espaces avant et apres, sasn plusieurs espaces de suite et sans tabs

	i=0;
	do	//on recupere juste la taille de la chaine
	{
		i++;
		taillechaine++;
	}while(ch[i]!='\0');


	// ETAPE 2 //  On supprime tout les caracteres inutiles

	char tab_char[26] = {'u','d','t','q','c','U','D','T','Q','C','r','j','R','J',' ','0','1','2','3','4','5','6','7','8','9'};  //liste des caracteres possibles pour fen

	for(i=0; i<taillechaine+1; i++)
	{
		j=0;
		do
		{	
			if(ch[i] == tab_char[j])  //si le caractere fait parti des carcteres valides
			{
				newfen[k]=ch[i]; //alors on le copie dans une nouvelle chaine
				k++;
			}
			j++;
		}while(tab_char[j]!='\0');
	}

	printfdbg("DEBUG : NEW FEN : %s\n",newfen);

	strcpy(ch, newfen);  //on recopie la nouvelle chaine dans celle de base pour ne pas avoir a changer de nom dans les etapes suivantes(certaines sont plus recentes)





	i=0;  //reinitialisation des variables pour ne pas en creer d'autres inutilement
	j=0;


	// ETAPE 3 //

	do 	//ici on supprime les espaces qui ne sont pas present avant un r ou un j, pour que le seul espace restant soit avant le trait (r ou j)
	{
		if (ch[i]==' ' && ch[i+1]!='r' && ch[i+1]!='j')
		{
			j = i;
			do  //on decale tout les caracteres a partir de l'espace en trop ce qui le supprime.
			{
				ch[j] = ch[j+1];
				j++;
			}while(ch[j]!='\0');
		}
	i++;
	}while(ch[i]!='\0');

	taillechaine=0;

	i=0;
	j=0;	
	k=0;
	do{
		i++;
		taillechaine++;
	}while(ch[i]!='\0');



	char tab_trait[24] = {'u','d','t','q','c','U','D','T','Q','C',' ','0','1','2','3','4','5','6','7','8','9'};  //on supprime les 'j' et 'r' avant le trait

	for(i=0; i<taillechaine+1; i++)
	{
		j=0;
		do
		{	
			if(ch[i] == tab_trait[j] || ch[i-1]==' ')  //les 'j' et 'r' avant un espace ne sont pas supprimés (trait)
			{
				newfen2[k]=ch[i]; 
				k++;
				if(ch[i-1]==' ')
				{
					i++;
				}
			}	
			j++;	
		}while(tab_trait[j]!='\0');
	}

	strcpy(ch, newfen2);

	i=0;  //parfois, il reste un ou plusieurs caracteres apres le trait, cette boucle permet de le supprimer
	do
	{
		if(ch[i]=='j' || ch[i]=='r')
		{
			ch[i+1]='\0';
		}
		i++;
	}while(ch[i]!='\0');

	printfdbg("DEBUG : SANS TRAIT : %s\n",ch);



	taillechaine=0;
	i=0;
	do	
	{
		i++;
		taillechaine++;
	}while(ch[i]!='\0');


	etat=0;

	for(i=0;i<taillechaine+1;i++)   //on regarde si l'utilisateur a bien rentré un espace avant le trait comme demandé
	{	
		if(ch[i]==' ')
		{
			etat=1;
		}
	}

	if(etat==0)
	{
		printf("\nErreur : Merci de rentrer un trait separé par un ESPACE\n");
		return 0;
	}



	i=0;
	j=0;
	etat = 2;
	compteur = 0;  //compteur de places utilisés sur le plateau
	minicompteur = 0; //permet de calculer le un nombre a l'intrerieur du fen
	multiplicator = 1;

	// ETAPE 4 //

	do  //mtn on va compter le nombre de cases que le fen rentré prend pour pouvoir l'adapter si il en prend trop ou pas assez sachant que le plateau compte 48 cases (l'etape est assez chiante a comprendre je vous expliquerai quand on se verra).
	{
		switch (etat)
		{	
			case 1: //cas ou on a un nombre
			if (ch[i]>='0' && ch[i]<='9')	//si le caractere est un chiffre
			{
				minicompteur = minicompteur*multiplicator;  //de base a 1, le multiplicator est utile lorsqu'on a un nombre a plus d'un caractere (si par exemple on voit un chiffre apres un 4, cela veut dire que c'est plutot 40 et ainsi de suite pour les centaines, les milliers, etc).
				//printf("minicompteur : %d\n", minicompteur);
				minicompteur = minicompteur + (ch[i]-'0'); 
				//printf("minicompteur : %d\n", minicompteur);
				i++;
				multiplicator = 10; //application du multiplicator (il sera effectif si le nombre comporte 2 caracteres ou +).		
			}
			else
			{
				etat = 2;
			}
			break;

			case 2: //cas de test
			compteur = compteur + minicompteur; //on applique au compteur le nombre final obtenu seulement a la sortie du cas 1
			minicompteur = 0;
			multiplicator = 1;
			if (ch[i]>='0' && ch[i]<='9') 
			{
				//printf("on passe cas 1\n");
				etat = 1;
			}
			else if (ch[i]==' ') //si on arrive a l'espace
			{
				//printf("on passe fin du prog\n");
				etat = 3;
			}
			else //cas par defaut, ni un espace ni un chiffre, c'est donc un pion et on ajoute 1 au compteur.
			{
				//printf("on reste cas 2\n");
				i++;
				compteur++;
			}
			break;
		}
	}while(etat!=3); 
	nbchara = i;

	printfdbg("\nNombre de cases utilisés sur le plateau de jeu: %d\n", compteur);
	printfdbg("Nombre de caracteres avant le trait : %d\n", nbchara);

	//aux[0]=ch[nbchara-1];
	//printf("DERNIER CARA : %s\n", aux);


	//ETAPE 5// derniere etape, on va maintenant ramener le nombre de cases utilisés sur le plateau a 48

	j=0;
	etat=1;
	do
	{
		switch (etat)
		{
			case 1: //cas de test
			if(compteur < NBCASES)	 //si l'on ne prend pas assez de cases sur le plateau
			{
				etat = 2;
			}
			else if(compteur > NBCASES)	 //si l'on prend trop de cases sur le plateau
			{
				etat = 3;
			}
			else if(compteur == NBCASES) //on prend parfaitement le bon nombre de cases
			{
				etat = 4;
			}
			break;

			case 2: 
			difference = NBCASES-compteur-1;  //nb de cases a completer

			aux[0]=ch[nbchara];
			aux[1]=ch[nbchara+1];	//on stock le trait dans une autre chaine

			for(i=0; i<difference+1; i++)		
			{
				ch[nbchara+i]='v';	//on rajoute le nombre de 1 pour le nombre de cases manquantes
			}

			ch[nbchara+i]=aux[0];
			ch[nbchara+i+1]=aux[1];  //on remet le trait dans la chaine de base
			ch[nbchara+i+2]='\0';	

			etat = 4;
			break;

			case 3:

			if(ch[nbchara-1]>='0' && ch[nbchara-1]<='9')	//si le dernier caractere avant le trait est un chiffre
			{
				nb[0]=ch[nbchara-1];
				if(ch[nbchara-2]>='0' && ch[nbchara-2]<='9')
				{
					aux[0]=nb[0];
					nb[0]=ch[nbchara-2];
					nb[1]=aux[0];
					j=0;

					do
					{
						ch[nbchara-1+j] = ch[nbchara+j];
						j++;
					}while(ch[nbchara+j]!='\0');

				}
				nbchara--;
				test = atoi(nb);
				printfdbg("Debug ATOI : %d\n",test);

				j=0;
				do
				{
					ch[nbchara-1+j] = ch[nbchara+j];
					j++;
				}while(ch[nbchara+j]!='\0');

				nbchara--;
				compteur = compteur - test;

				ch[nbchara+2]='\0';
				etat = 1;
				break;
			}
			else		//sinon cela veut dire que c'est une lettre
			{	
				j=0;
				do
				{
					ch[nbchara-1+j] = ch[nbchara+j];
					j++;
				}while(ch[nbchara+j]!='\0');

				nbchara--;
				compteur--;	

				ch[nbchara+2]='\0';

				etat = 1;
				break;
			}

		}
	}while(etat!=4);


return ch;
}
