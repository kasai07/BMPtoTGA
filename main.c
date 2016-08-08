#include <stdio.h>
#include <string.h>


void main()
{
//preparation des variables
char *tab;
char *tab2;
FILE *fichier;
FILE *fichier2;

//Ouverture du fichier d'entrée en mode lecture
if((fichier = fopen("in.bmp","rb")) == NULL){printf("impossible d'ouvrir le fichier\n"); goto fin;}

int taille;
//calcule de la taille de fichier
fseek(fichier, 0, SEEK_END);
taille = ftell(fichier);
fseek(fichier,0,SEEK_SET);

//Allocation de la memoire de la taille de fichier
//au cas ou mais celle la    tab = (int*)malloc(taille * sizeof(int));
int taille2;
char *header[19] = {0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
                     0x00, 0x00, 0x00, 0x00, 0x40, 0x01, 0xF0, 0x00,
                     0x18, 0x00};
taille2 = (taille - 54 + 18);


tab = malloc(taille);


tab2 = malloc(taille * 3);
//lecture en memoire des données d'entrée
fread(tab, taille, 1, fichier);

header[12] = tab[18];
header[13] = tab[19];
header[14] = tab[22];
header[15] = tab[23];
header[18] = tab[28];
int j;
int debut = 54;
int depart = 18;
for(j = 0; j < 18; j++)
{
    tab2[j] = header[j];
}

int i;
for(i = 0; i < taille; i++)
{
    tab2[depart++] = tab[debut++];
}

//ouve rture du fichier de sortie en mode ecriture
if((fichier2 = fopen("out.tga","wb")) == NULL){printf("impossible d'ouvrir le fichier a ecrire\n"); goto fin;}
//ecriture ddes données dans le fichier
fwrite(tab2, taille2, 1, fichier2);

//fermeture des fichier
fclose(fichier2);
fclose(fichier);
printf("Conversion Fini !!!\n");
fin : system("pause");

}
