/*#include"defs.h"

//Calucul du carée de la norme entre deux vecteurs u et v de dimension d
double NormeAuCarree(double *u, double *v, long int d)
{
    long int j, x;
    for(j=1, x=0.0; j<=d; j++)
        x+=pow(u[j]-v[j],2);
    return x;
}

void Kmoyennes(Exs, G, mu, CardinalG, eps, T, display)
DATA Exs; //Stucture de données contenant les données
long int **G; //Matrice contenant les indices des exemples dans chaques groupe
double **mu; //Matrice contenant les coordonnées des centroïde
long int *CardinalG; //Vecteur contenant la taille des groupe
double eps; //Précision
long int T; //Nombre maximum d'itération
int display; //Affichage ou non des valeurs intermédiaires de la fonction de SSR
{
    long int i, j, k, IndCls, Epoque=1;
    double minimum, SSRnew=0.0, SSRold=1e3;
    while(Epoque<=T && fabs(SSRnew-SSRold)>eps)
    {
        for(k=1;k<=Exs.K;k++)
            CardinalG [k]=0;
        //Etape de réafectation (étapes E et C de l'algorithme 19)
        for(i=1;i<=Exs.u;i++)
        {
            IndCls=1;
            minimum=NormeAuCarree(Exs.X[i],mu[1]),Exs.d);
            for(k=2; k<=Exs.K;k++)
                if (NormeAuCarree(Exs.X[i],mu[k],Exs.d)<minimum)
                {
                    minimum=NormeAuCarree(Exs.X[i],mu[k],Exs.d);
                    IndCls=k;
                }
            CardinalG[IndCls]++;
            //Les indices des exemples affectés au differents groupe sont stockés dans la matrice G
            G[IndCls][CardinalG[IndCls]]=i;
        }
        //Etape de recalcul des centroïdes, étape C de l'algorithme 19->(Eq. 5.10)
        for(k=1;k<=Exs.K;k++)
        {
            if(CardinalG[k]==0)
            {
                printf("Le nombre de groupe est innaproprié, essayez avec un nombre plus petit");
                exit(0);
            }
            for(j=1;j<=Exs.d;j++)
            {
                mu[k][j]=0.0;
                for(i=1;i<=CardinalG[k];i++)
                    mu[k][j]+=Exs.X[G[k][i]][j];
                mu[k][j]/=((double)CardinalG[k]); //-> mu de k =...
                
            }
        }
        //Somme des carrées des résidus -> (Eq. 5.8)
        SSRold=SSRnew;
        for(k=1,SSRnew=0.0;k<=Exs.K;k++)
            for(i=1;i<=CardinalG[k];i++)
                SSRnew+=NormeAuCarree(Exs.X[G[k][i]],mu[k],Exs.d);
        SSRnew/=2.0;
        if(!(Epoque%5) && display)
            printf("Epoque%d SSR %f\n", Epoque,SSRnew);
        Epoque++;
    }
}
*/