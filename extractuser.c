#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

// Number of person close to you
#define number 100

// Number of user analysed (The maxi first user in the FileData)
#define maxi 14500

// Number of manga sugggested 
#define nbres 30

#define nbtest 1

int cmpfunc(const void * a, const void * b)
{
  return -( *(int*)a - *(int*)b );
}
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

int compare_join(const void* a, const void* b)
{
  struct join arg1 = *(struct join*)a;
  struct join arg2 = *(struct join*)b;
  
  return - (arg1.count - arg2.count);
}

int compare_user(const void* a, const void* b)
{
  struct user arg1 = *(struct user*)a;
  struct user arg2 = *(struct user*)b;
  return - (arg1.count - arg2.count);
}

int nbjoin(int nba, int *a, int nbb, int *b){
  int res = 0;
  
  for (int i = 0; i < nba ; i++){
    //int * pItem;
    int key = a[i];int k = 0;
    int *item;
    item = (int*) bsearch (&key, b, nbb, sizeof (int), cmpfunc);
    //while ( a[i] != b[k] && k < nbb ){k++;}
    //if (a[i] == b[k]) res++;
    if (item != NULL) res++;
    
  }
  return res;
}

void find( int nbref, int idref,int *listref ,FILE *f){
  FILE *LISTE1;
  
  int nbuser;
  int val;
  
  /*
   * Cette partie vas lire le fichier en entrée
   * Le format du fichier est
   * nblignes
   * nombremangauser1 user1 [manga1, manga2 ...]
   * nombremangauser2 user2 [manga1, manga2 ...]
   * ...
   * 
   * Erreur le premier n'est pas trillé
   */
  LISTE1=fopen("liste.txt","r");
  
  //fscanf(LISTE1,"%d",&nbuser);
  nbuser = maxi;
  //printf("Etape 0\n");
  
  
  
  struct user receuil[2*number];
  int buffer  = -number;
  for (int i = 0 ; i<maxi-1; i++){
   
    if (buffer>=number){
      qsort(receuil, 2*number, sizeof(struct user), compare_user);
      for (int i = number ; i<number*2; i++){
	free(receuil[i].liste);
      }
      
      buffer =0;
    }
    
    int nbmanga;
    //printf ("Etape -A\n");
    
    fscanf(LISTE1,"%d",&nbmanga);
    //printf ("Etape -S\n");
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
    qsort(list, nbmanga, sizeof(int), cmpfunc);
    receuil[number+buffer].liste = list;
    receuil[number+buffer].count = nbjoin(receuil[number+buffer].nb, receuil[number+buffer].liste, nbref, listref);
    //printf("Etape 1 %d\n",number+buffer);
    buffer++;
     //printf("%d : %d \n",ident,nbmanga);
    
  }
  qsort(receuil, (number+buffer), sizeof(struct user), compare_user);
  int best[number];
  
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
  
  //struct join *tab2= malloc(total*sizeof(struct join)); 
  int val2 = 0;
  for(int i = 0; i<number;i++){
    for(int k = 0; k<receuil[i].nb; k++){
      if (!nbjoin( 1,&receuil[i].liste[k], nbref,listref ))
	tab[val2++]=receuil[i].liste[k];
    }
  }
  
  qsort(tab, total, sizeof(int), cmpfunc);
  /*
  int val5 = tab[0];
  int index = 0;
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
  */
  
  for (int i = 0; i < number+buffer ; i++){
    free(receuil[i].liste);
  }
  struct join tab2[2*nbres];
  buffer  = -nbres;
  tab2[0].a = tab[0];
  tab2[0].count = 0;
  //printf("Total = %d\n", total);
  for (int i = 0 ; i<total; i++){
    //printf("Val = %d\n", i);
    if (buffer>=nbres){
      qsort(tab2, 2*nbres, sizeof(struct join), compare_join);      
      buffer =0;
    }

    //printf("Val buff = %d\n", buffer);
    if (tab[i] == tab2[buffer+nbres].a) {
      tab2[buffer+nbres].count++;
      //printf("Test\n");
      
    }
    else {
      //index++;
      ///printf("Test0\n");
      buffer++;
      tab2[buffer+nbres].a = tab[i];
      tab2[buffer+nbres].count = 1;
    }
    //printf("Val somme = %d\n", i);
  }        

  qsort(tab2, nbres+buffer, sizeof(struct join), compare_join);      

  
  
  /////
  //qsort(tab2, index, sizeof(struct join), compare_join);
  fprintf(f, "%d", idref);
  
  for (int i = 0; i < nbres ; i++){
    fprintf(f, ";%d(%d user)",tab2[i].a,tab2[i].count);
  }
  fprintf(f, "\n");  
  //printf("Val = %d sur %d\n", 1, total);

  
  free(tab);
  //free(tab2);
  fclose(LISTE1);
  
  
}


void main (void) 
{
  FILE *f = fopen("Solution.txt", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }
  
  FILE *LISTE2;
  LISTE2=fopen("listebis.txt","r");
  for (int i=0;i<nbtest;i++){
    int nbref;
    fscanf(LISTE2,"%d",&nbref);	
    int idref;
    int search = 0;
    fscanf(LISTE2,"%d",&idref);
    printf("Etape %d(%d), %d pourcent\n",idref,nbref, (i)*100/(nbtest));
    search = idref;
    int *listref = malloc(sizeof(int) * nbref);
    
    for ( int k = 0 ; k < nbref; k++){
      fscanf(LISTE2,"%d",&listref[k]);
    }
    qsort(listref, nbref, sizeof(int), cmpfunc);
    //printf("Val = bis\n");
    find(nbref,idref,listref, f);
    free(listref);
  }
  fclose(f);
  fclose(LISTE2);
  FILE *f2 = fopen("Enduser20.txt", "w");
  if (f == NULL)
  {
    printf("Error opening file!\n");
    exit(1);
  }
  fclose(f2);
}
