/* 
 * File:   myHeader.h
 * Author: antoinenouma
 * Created on 10 mars 2016, 15:32
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "matrix.h"

typedef struct entete entete;
struct entete
{
    unsigned char format [3];
    int fileSize; //Taille du fichier
    int reserve;
    int BMP_Off; //Offset du fichier
    int BMP_Width; //Largeur de l'image
    int BMP_Height; //Longueur de l'image
};
    

typedef struct colorPalette colorPalette; //Palette de couleur des pixels
struct colorPalette
{
    unsigned char R; //Pixel rouge
    unsigned char G; //Pixel vert
    unsigned char B; //Pixel bleu
};

entete RecupEntete(FILE *fpin);




