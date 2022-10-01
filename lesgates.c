while (1) 
	{
		printf("\t---------------------------- Strat 10 en cours :\n");
		printf(" Tirer au sort  :  \n");
		a = rand()%listeCoups.nb;
		o = listeCoups.coups[a].origine; 
		d = listeCoups.coups[a].destination;  
 
		if ( (currentPosition.cols[o].couleur != myColor)
		&& ((currentPosition.cols[o].nb+currentPosition.cols[d].nb) != 5) ) 
		{
			printf("On choisit ce coup ! -Strategie 10----------------------------\n"); 
			ecrireIndexCoup(a);
			return; // on quitte la fonction 
		}
	}
