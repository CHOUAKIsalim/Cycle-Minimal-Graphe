//Ce programme s'occupe de trouver le cycle avec le coup le plus minimal dans un graphe non orienté avec deux méthodes : DFS & Vorace
//Chibah Abdelwahab & Chouaki Salim

#include <stdlib.h>
#include <stdio.h>
#define nb_sommet 12

//*************************************************************************************************************************//
//****************************************************Définition du graphe*************************************************//
//*************************************************************************************************************************//


// Un sommet contient uniquement une valeur
typedef struct Sommet {
	int value ;
}Sommet;

// Le graphe est représenté par un tableau de sommet et une matrice d'arretes ou chaque case vaut le poids de l'arrete, car graphe complet
typedef struct Graphe {
	Sommet sommets[nb_sommet];	
	int arretes[nb_sommet][nb_sommet];
}Graphe;

//*************************************************************************************************************************//
//****************************************************Déclaration des variables********************************************//
//*************************************************************************************************************************//


//Le graphe comme variable globale
Graphe graphe;


//Le tableau qui sera utilisé pour tester avec DFS
int tableauTest[nb_sommet] ;

//Un tableau qui contient la configuration optimale pour l'algorithme de DFS
int configurationOptimale[nb_sommet];
//Le cout optimal pour DFS
int coutOptimal = 0;

//Un tableau qui contient la configuration optimale pour l'algorithme vorace
int configurationOptimale2[nb_sommet];
//Le cout optimal pour Vorace
int coutOptimal2 = 0;

//*************************************************************************************************************************//
//****************************************************Les fonctions DFS********************************************//
//*************************************************************************************************************************//

//Retroune 1 si le tableau de test contient déja le sommet numéro j 
int dejaPasse(int j,int tailleTableau)
{
	for (int a=0; a<tailleTableau ; a++) 
	{
		if(tableauTest[a] == j) return 1;
	}
	return 0;
}

//Calcule le cout du cycle généré dans le tableau tableauTest
int coutCycle()
{
	int result=0; 
	for(int i=0; i < nb_sommet-1 ; i++)
	{
		result+=graphe.arretes[tableauTest[i]][tableauTest[i+1]];
	}
	result+=graphe.arretes[tableauTest[nb_sommet-1]][tableauTest[0]];
	return result;
}

//Enregistre le cycle contenu dans tableauTest dans le tableau configurationOptimale
void enregistrerCycle()
{
	for(int i=0; i<nb_sommet; i++)
	{	
		configurationOptimale[i] = tableauTest[i];

	}
}

//Fait le parcours en DFS, pour generer toutes les permutations possibles
void DFSCycle(int tailleTableau)
{
	if(tailleTableau == nb_sommet)
	{
		int res = coutCycle();
		if(coutOptimal==0 || res < coutOptimal)
		{
			coutOptimal = res;
			enregistrerCycle();
		}	
	} 
	else
	{
		for(int j=0; j<nb_sommet; j++)
		{
			if(!dejaPasse(j, tailleTableau))
			{
				tableauTest[tailleTableau] = j;
				DFSCycle(tailleTableau+1);	
			}
		}
	}
}

//*************************************************************************************************************************//
//****************************************************Les fonctions Vorace*************************************************//
//*************************************************************************************************************************//

//Calcule le cout du cycle contenu dans le tableau a
int coutCycleVorace(int* a)
{
	int result=0; 
	for(int i=0; i < nb_sommet-1 ; i++)
	{
		result+=graphe.arretes[a[i]][a[i+1]];
	}
	result+=graphe.arretes[a[nb_sommet-1]][a[0]];
	return result;
}

//Enregistrer le cycle contenu dans le tableau a dans le tableau configurationOptimale2
void enregistrerCycleVorace(int *a)
{
	for(int i=0; i<nb_sommet; i++)
	{	
		configurationOptimale2[i] = a[i];

	}
}



//C'est la fonction qui genere toutes les permutation pour l'algorithme vorace
void genererPermVorace(void) 
{
	int a[nb_sommet], poids[nb_sommet];
   	int i, j, tmp;
  
	for(i = 0; i < nb_sommet; i++) 
	{
	      	a[i] = i;
	      	poids[i] = 0;
		configurationOptimale2[i] = i;
	}
	
	coutOptimal2 = coutCycleVorace(a);
	i = 1;
   	while(i < nb_sommet ) 
	{
      		if (poids[i] < i ) 
		{
			j = i % 2 * poids[i];
			tmp = a[j];
			a[j] = a[i];
			a[i] = tmp;
			int res = coutCycleVorace(a); 
			if(res < coutOptimal2 ) 
			{
				coutOptimal2 = res;
				enregistrerCycleVorace(a);
			}
		 	poids[i]++;
			i = 1;
      		} 
		else 
		{
			poids[i] = 0;
			i++;
			if(poids[nb_sommet-1]==nb_sommet-1)i=nb_sommet;
      		}
   	}
}

//*************************************************************************************************************************//
//****************************************************Construction des graphes********************************************//
//*************************************************************************************************************************//


//Construction aléatoire des graphes, utile pour les tests sur des grands graphes
Graphe construireGraphe()
{
	for(int i=0; i<nb_sommet;i++)
	{
		graphe.sommets[i].value = i;
	}
 
	for(int i=0; i<nb_sommet ; i++)
	{
		graphe.arretes[i][i] = 0;
		for(int j=i+1; j<nb_sommet; j++)
		{
			int x = (rand()+j)%10 + 1;
			graphe.arretes[i][j] = x;
			graphe.arretes[j][i] = x;
		}
	}
}


//Construction manuelle des points d'articulations : utile pour tester le bon fonctionnement de l'algorithme sur des exemples connus
Graphe construireGraphePerso()
{
	graphe.sommets[0].value= 0;
	graphe.sommets[1].value= 1;
	graphe.sommets[2].value= 2;
	graphe.sommets[3].value= 3;

	graphe.arretes[0][0] = 0;
	graphe.arretes[0][1] = 1;
	graphe.arretes[0][2] = 10;
	graphe.arretes[0][3] = 4;
	graphe.arretes[1][0] = 1;
	graphe.arretes[1][1] = 0;
	graphe.arretes[1][2] = 100;
	graphe.arretes[1][3] = 12;
	graphe.arretes[2][0] = 10;
	graphe.arretes[2][1] = 100;
	graphe.arretes[2][2] = 0;
	graphe.arretes[2][3] = 3;
	graphe.arretes[3][0] = 4;
	graphe.arretes[3][1] = 12;
	graphe.arretes[3][2] = 3;
	graphe.arretes[3][3] = 0;
}


// Le main : crée un graphe, puis recherche les points d'articulations et les affiche 
int main()
{
	printf("Test de DFS et Vorace pour trouver le cycle hamiltonien optimale pour un graphe de %d sommets\n",nb_sommet);
//	construireGraphePerso(); Si on veut utiliser celle ci, il faudra modifier le nb_sommet a 4 dans ce cas
	construireGraphe();	
	tableauTest[0]=0;
	printf("\nDebut Execution DFS\n");
	DFSCycle(1);
	printf("\nFin Execution DFS\n");
	printf("\nDebut Execution Vorace\n");
	genererPermVorace();
	printf("\nFin Execution Vorace\n");
	if(coutOptimal != coutOptimal2)
	{
		printf("Erreur");
		return 0;
	}
	printf("Le cycle optimal est :");
	for (int i=0; i<nb_sommet ; i++)
	{
		printf("  %d,",configurationOptimale[i]);
	}
	printf("  %d",configurationOptimale[0]);
	printf("\nLe cout de ce cycle est : %d\n",coutOptimal2);
	return 0;
}



