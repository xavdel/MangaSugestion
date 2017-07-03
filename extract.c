#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

#define number 50
#define maxi 1000
#define nbres 100
typedef struct join {
	int a;
	int b;
	int count;
} *join;

typedef struct user {
	int id;
	int nb;
	int * liste;
	int count;
} *user;

int compare_ints2(const void* a, const void* b)
{
    struct join arg1 = *(struct join*)a;
    struct join arg2 = *(struct join*)b;
 
    if (arg1.count < arg2.count) return -1;
    if (arg1.count > arg2.count) return 1;
    return 0;
 
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

int compare_ints3(const void* a, const void* b)
{
    struct user arg1 = *(struct user*)a;
    struct user arg2 = *(struct user*)b;
 
    if (arg1.count < arg2.count) return 1;
    if (arg1.count > arg2.count) return -1;
    return 0;
 
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
 
    // return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    // return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
}

int compare(const void* a, const void* b){return -compare_ints(a,b);}

int compareints (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int nbjoin(int nba, int *a, int nbb, int *b){
	int res = 0;

	for (int i = 0; i < nba ; i++){
		//int * pItem;
		int key = a[i];int k = 0;
			while ( a[i] != b[k] && k < nbb ){k++;}
			if (a[i] == b[k]) res++;
			
	}
	return res;
}

void main (void) 
{
	FILE *LISTE1;
	int nbuser;
	int val;
	int search = 0;
/*
Cette partie vas lire le fichier en entrée
Le format du fichier est
nblignes
nombremangauser1 user1 [manga1, manga2 ...]
nombremangauser2 user2 [manga1, manga2 ...]
...

Erreur le premier n'est pas trillé
*/
	LISTE1=fopen("liste.txt","r");
	//fscanf(LISTE1,"%d",&nbuser);
	nbuser = maxi;
printf("Etape 0\n");

		int nbref;
		fscanf(LISTE1,"%d",&nbref);
		int idref;
		fscanf(LISTE1,"%d",&idref);
		search = idref;
		int *listref = malloc(sizeof(int) * nbref);
		for ( int k = 0 ; k < nbref; k++){
			fscanf(LISTE1,"%d",&listref[k]);
		}
		//receuil[i].id = ident;
		//receuil[i].nb = nbmanga;
		//int size = sizeof receuil[i].liste / sizeof *receuil[i].liste;
		qsort(listref, nbref, sizeof(int), compare);
		//receuil[i].liste = list;
	
		
	struct user receuil[2*number];
	int buffer  = -number;
	for (int i = 0 ; i<nbuser-1; i++){
	printf("Etape 0, %d poucent\n", (i)*100/(nbuser-1));
		if (buffer>=number){
			qsort(receuil, 2*number, sizeof(struct user), compare_ints3);
			for (int i = number ; i<number*2; i++){
				//printf("i = %d\n", i);
				free(receuil[i].liste);
				//free(receuil[i]);
			}
			
			buffer =0;
		}

		int nbmanga;
		fscanf(LISTE1,"%d",&nbmanga);
		int ident;
		fscanf(LISTE1,"%d",&ident);
		//if (ident == searchid) search = i;
		int *list = malloc(sizeof(int) * nbmanga);
		for ( int k = 0 ; k < nbmanga; k++){
			fscanf(LISTE1,"%d",&list[k]);
		}

		receuil[number+buffer].id = ident;
		receuil[number+buffer].nb = nbmanga;

		//int size = sizeof receuil[i].liste / sizeof *receuil[i].liste;
		qsort(list, nbmanga, sizeof(int), compare_ints);
		receuil[number+buffer].liste = list;
		receuil[number+buffer].count = nbjoin(receuil[number+buffer].nb, receuil[number+buffer].liste, nbref, listref);
		printf("Etape 1 %d\n",number+buffer);
		buffer++;
		

	}
printf("place = %d\n", search);
/*
Cette partie vas faire la matrice entre users
de chaque manga en commun


*/
//alloue la matrice
/*
struct join **matrice = malloc (nbuser*sizeof(void *));
for (int i = 0 ; i<nbuser; i++){
	matrice[i]=malloc(sizeof(struct join)*nbuser);
}
*/
/*
struct join *matrice2 = malloc(sizeof(struct join)*nbuser);
//matrice[i]=malloc(sizeof(struct join)*nbuser);
//remplie la matrice
printf ("Bonjour 1\n");
for (int i = 0 ; i<nbuser; i++){
	printf("Etape 2 %d pourcent\n", i*100/nbuser);
	//matrice[i][i].count = 0;
	//for (int k = 0 ; k<i; k++)
	int save = 0;
	{
		int pourc = i/nbuser;
		if (save<pourc) {
			//printf ("%d Pourcent\n", pourc);
			save = pourc;
		}
		int k = search;
		struct join *valeur = malloc(sizeof(struct join));
		valeur->a = receuil[i].id ;
		valeur->b = receuil[k].id ;
		valeur->count = nbjoin(receuil[i].nb, receuil[i].liste, receuil[k].nb, receuil[k].liste);
		//printf("nbjoin %d\n",valeur->count);

		//matrice[i][k] = *valeur;
		//matrice[k][i] = *valeur;

		matrice2[i] = *valeur;
		free(valeur);
	}
}




qsort(matrice2, nbuser, sizeof(struct join), compare_ints2);

*/
printf ("Bonjour 2\n");
//for (int i = 0; i < nbuser ; i++){
/*
	for (int k = 0; k < nbuser ; k++){
		printf ("%d ", matrice[i][k].count);
	}
*/
	//printf ("\n");
	//printf ("%d ", matrice2[i].count);
//}

int best[number];
//int worst[number];


//for (int i = 0; i<number; i++){
/*
	if (matrice2[i].a == search){
		worst[i] = matrice2[i].b;
	}
	else
	{
		worst[i] = matrice2[i].a;
	}
	*/
/*	if (matrice2[i].a == search){
		best[i] = matrice2[nbuser-1-i].b;
	}
	else
	{
		best[i] = matrice2[nbuser-1-i].a;
	}
*/
//}

int bestplace[number];
int bestnb[number];
int total = 0;
for(int i = 0; i<number;i++){
	int m =-1;
	//while (receuil[++m].id != best[i]);
	//bestplace[i]=m;
	//bestnb[i]=receuil[m].nb;
	total += receuil[i].nb;

}

int *tab= malloc(total*sizeof(int)); 
struct join *tab2= malloc(total*sizeof(struct join)); 
int val2 = 0;
for(int i = 0; i<number;i++){
	for(int k = 0; k<receuil[i].nb; k++){
		if (!nbjoin( 1,&receuil[i].liste[k], nbref,listref ))
			tab[val2++]=receuil[i].liste[k];
	}
}
printf ("Etape x\n");
qsort(tab, total, sizeof(int), compare_ints);
int index = 0;
int val5 = tab[0];
tab2[index].a = val5;
tab2[index].count = 0;
	for (int i = 0; i < total ; i++){
		
		if (tab[i] == val5) tab2[index].count++;
		else {
			index++;
			val5 = tab[i];
			tab2[index].a = val5;
			tab2[index].count = 0;
		}

	}
qsort(tab2, index, sizeof(struct join), compare_ints2);

	for (int i = index-nbres; i < index ; i++){
		printf (" %d(%d user)",tab2[i].a,tab2[i].count);
	}
printf ("\n--%d !! %d--\n",index, total);
	//sprintf ("Bonjour le monde !\n");
	for (int i = 0; i < number+buffer ; i++){
		//printf ("id = %d, nb = %d, premier =  %d, 2e = %d \n",receuil[i].id,receuil[i].nb,receuil[i].liste[0], receuil[i].liste[1]  );
		free(receuil[i].liste);
	}
	//free (receuil);

/*	
	for (int i = 0 ; i<nbuser; i++){
		free(matrice[i]);
	}
	free(matrice);
*/
	//free(matrice2);
	//printf ("%d\n",val );
	free(listref);
	free(tab);
	free(tab2);
	fclose(LISTE1);
}
