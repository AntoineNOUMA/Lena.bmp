/* 
 * File:   main.c
 * Author: antoinenouma
 * Created on 10 mars 2016, 15:23
 */

#include "myHeader.h"
    
int main ()
{
    unsigned char memoryManagement[]=""; //Variable de la gestion de la mémoire
    unsigned char fileName[]=""; //Variable des noms des images.bmp stockées dans le projet. Exemple : lena1, lena2...
    int i=0,j=0; //Itérateurs utilisés s dans les boucles 
    FILE* f;
    FILE* newFile;
    entete E;
    colorPalette *colors=NULL;
    colorPalette *newColors=NULL;
    printf("Souhaitez vous une gestion 1D ou 2D de la mémoire pour représenter l’image? Taper 1D ou 2D");
    scanf("%s",memoryManagement);
    printf("Entrez le nom de l'image (lena1 est en couleur / lena2 est en noir et blanc:  ");
    scanf("%s",fileName); //Le nom de l'image entrée au clavier est stocké dans fileName Exemple : Filename=lena1
    strcat(fileName,".bmp"); //On ajoute l'extension .bmp au nom de l'image entrée au clavier Exemple : fileName=lena1.bmp
    printf("%s\n",fileName);
    f=fopen(fileName,"rb"); //Le programme va chercher l'image demandée
    if (f==NULL)
        printf ("Erreur");
    else //récupération de l'entête jusqu'à la longueur en pixels
    {
        E=RecupEntete(f);
        // comme je ne charge pas toute l'entete, je fait un fseek pour commencer au debut de l'image
        fseek(f, E.BMP_Off, SEEK_SET);
        i=0;
        // allocation dynamique
        colors=malloc (E.BMP_Height*E.BMP_Width*sizeof(colorPalette));
        while (!feof(f))
        {
                            // ici ca foire
            fread(&colors[i], sizeof(colorPalette),1,f);
                               //les 10 premieres valeurs sont negatives !
            if(i>=0&&i<11)
                printf("%d\n",colors[i].B );
            i++;
        }
     }
    fclose(f);  
    newColors=malloc (E.fileSize *sizeof(colorPalette));
            //modification des pixels
            // elle sert a rien mais c'est just pour tester
    while (j<i)
    {
        newColors[j].R=255-colors[j].R;
        newColors[j].G=255-colors[j].G;
        newColors[j].B=255-colors[j].B;
        j++;
    }
    
    newFile=fopen("result.bmp", "wb"); //je crée mon nouveau fichier
    if (newFile==NULL)
        printf ("Erreur");
    else
    {
        fwrite(&E, sizeof(entete),1,newFile);
        //dois je metre la pallette ??
        j=0;
        while(j<i)
        {
            fwrite(&newColors[j], (sizeof(colorPalette)),1,newFile);
            j++;
        }  
     }
    fclose(newFile); // ajoute EOF au fichier et ferme le fichier 
    // affichage de l'entete
    printf("Format: %c%c\n",E.format[0],E.format[1]);
    printf("fileSize: %d octets\n",E.fileSize);
    printf("BMP_Off: %d octets \n",E.BMP_Off);
    printf("BMP_Width: %d pixels\n",E.BMP_Width);
    printf("BMP_Height: %d pixels\n",E.BMP_Height);
    printf("appuyez sur la touche entrée");
    getchar();
    getchar();
    return EXIT_SUCCESS;
}

entete RecupEntete(FILE *fpin)
{
    entete E1;
    fread(&E1.format,2,1,fpin);
    fread(&E1.fileSize,4,1,fpin);
    fread(&E1.reserve,4,1,fpin);
    fread(&E1.BMP_Off,4,1,fpin);
    fread(&E1.reserve,4,1,fpin);
    fread(&E1.BMP_Width,4,1,fpin);
    fread(&E1.BMP_Height,4,1,fpin);
    return E1;  
}




//PITCH

/*I=f(BMP_Width.BMP_Height.taille);
	pitch = corrpitch[(3*BMP_Width.BMP_Height.taille)%4];
	for(j=0;j<I->h;j++)
	{
		for(i=0;i<I->w;i++)
		{
			fread(&bgrpix,1,3,F);
			p.r = bgrpix[2];
			p.g = bgrpix[1];
			p.b = bgrpix[0];
			SetPixel(I,i,I->h-j-1,p);
		}
		fread(&bgrpix,1,pitch,F);
	}
	fclose(F);
	return I;
}*/