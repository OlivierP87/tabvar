#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	FILE *fid;
	char var[20];
	char func[20];
	char remar[256];
	char *remap[128];
	char signe[256];
	char *signep[128];
	int NB=0,NBs=0;
	int NB1;
	int i,n,k;
	int jj,jj0;
	printf("*** ATTENTION: SEPARER CHAQUE ELEMENTS DES LISTES PAR UNE VIRGULE,\nLES NOMS PEUVENT ETRES DONNES EN LaTeX\n");

	printf("Nom de la variable (moins de 20 caractères)\n");
	fgets(var,20,stdin);
	printf("%ld, %s\n",strlen(var),var);

	printf("Nom de la fonction (moins de 20 caractères)\n");
	fgets(func,20,stdin);

	printf("Liste de valeurs remarquables \n");
	fgets(remar,245,stdin);


	// calcul du nombres de valeurs remarquables
	n=strlen(remar);
	k=0;
	remap[k++]=remar;
	for (i=0;i<n;i++)
	{
		if (remar[i]==',')
		{
			NB++;
			remar[i] = '\0';
			remap[k++] = remar+i+1;
			//REMA[i]
		}
	}

	// nombre de signes
	NB++;
	NB1= NB+1;

	printf("NB = %d\n",NB);

	printf("Liste de signe de la dérivée, %d valeurs \n", NB1);
	fgets(signe,245,stdin);
	
	// calcul du nombres de signes
	n=strlen(signe);
	k=0;
	signep[k++]=signe;
	for (i=0;i<n;i++)
	{
		if (signe[i]==',')
		{
			NBs++;
			signe[i] = '\0';
			signep[k++] = signe+i+1;
		}
	}
	NBs++;

	printf("NBs = %d\n",NBs);

	// sauvegarde du tableau dans un fichier ASYMPTOTE (~metapost)
	fid = fopen("tableau.asy","w");

	if (fid == NULL)
	{
		printf("problème avec l'ouverture du fichier tableau.asy\n");
		return 1;
	}
	else
	{
	fprintf(fid,"real u=1cm;\n");
	fprintf(fid,"pair h;\n");
	fprintf(fid,"pair l;\n");
	fprintf(fid,"pair k;\n");
	fprintf(fid,"pair d;\n");
	fprintf(fid,"pair e;\n");
	fprintf(fid,"pair ee;\n");
	fprintf(fid,"h=(0,6)*u;\n");
	fprintf(fid,"l=(9,0)*u;\n");
	fprintf(fid,"k=(1,0)*u;\n");
	fprintf(fid,"e=(1/2,1/2)*u;\n");
	fprintf(fid,"ee=(1/2,-1/2)*u;\n");
	//# gap entre les nombres
	//N=n+1
	fprintf(fid,"d=(l-3*k)/%d;\n",NB1);
	//# Dessin du cadre
	fprintf(fid,"draw((0,0) -- l -- l+h -- h -- cycle,linewidth(1bp));\n");
	//
	//# Dessin de la première ligne
	fprintf(fid,"draw(3/4*h -- 3/4*h+l);\n");
	//# Dessin de la première colonne
	fprintf(fid,"draw(k -- k+h);\n");
	//# Dessin de la seconde ligne
	fprintf(fid,"draw(h/2 -- h/2+l);\n");
	//

	// remplissage de la première ligne
	fprintf(fid,"//-----------------------\n");
	fprintf(fid,"// Ligne 1 \n");
	fprintf(fid,"label(\"$%s$\",7/8*h+k/2);\n",var);
	fprintf(fid,"label(\"$-\\infty$\",7/8*h+3*k/2);\n");
	fprintf(fid,"label(\"$+\\infty$\",7/8*h+l-k/2);\n");
	for (i=0;i<NB;i++)
	{
    	fprintf(fid,"label(\"$%s$\",7/8*h+2*k+%d*d);\n", remap[i], i+1 );
	}		

	// remplissage de la seconde ligne
	// texte et ligne à finir
	fprintf(fid,"//-----------------------\n");
	fprintf(fid,"// Ligne 2 \n");
	fprintf(fid,"label(\"$%s'(%s)$\",5/8*h+k/2);\n",func,var);
	for (i=0;i<NB;i++)
	{
        fprintf(fid,"draw(3/4*h+2*k+%d*d -- 1/2*h+2*k+%d*d);\n",i+1,i+1);
        fprintf(fid,"// draw 3/4*h+1.9*k+%d*d -- 1/2*h+1.9*k+%d*d;\n",i+1,i+1);
        fprintf(fid,"// label(\"$*$\",5/8*h+2*k+%d*d);\n",i+1);
	}
	// les signes
	for (i=0; i<NBs; i++)
	{
    	fprintf(fid,"label(\"$%s$\",5/8*h+2*k+%d*d+d/2);\n", signep[i], i);
	}

	// remplissage de la dernière ligne
	fprintf(fid,"//-----------------------\n");
	fprintf(fid,"// Ligne 3 \n");
	fprintf(fid,"label(\"$%s(%s)$\",1/4*h+k/2);\n",func,var);
	jj=0;
	for (i=0; i<NBs; i++)
	{
    	//ii=2*i;
    	//j=ii+1;
    	jj+=1;
    	jj0=jj-1;

    	if (signep[i][0]=='+')
		{
        	fprintf(fid,"draw(2*k+%d*d+e -- h/2+2*k+%d*d-e,Arrow);\n",jj0,jj);
        	fprintf(fid,"label(\"$%d$\",2*k+%d*d+e/2);\n",i,jj0);
        	fprintf(fid,"label(\"$%d$\",h/2+2*k+%d*d-e/2);\n",i,jj);
        	fprintf(fid,"//draw(1.9*k+%d*d -- h/2+1.9*k+%d*d);\n",jj,jj);

        	if (i<NBs-1) 
            	fprintf(fid,"draw(2*k+%d*d -- h/2+2*k+%d*d);\n",jj,jj);
    	}       
    	else
		{
        	fprintf(fid,"draw(h/2+2*k+%d*d+ee -- 2*k+%d*d-ee,Arrow);\n",jj0,jj);
        	fprintf(fid,"label(\"$%d$\",h/2+2*k+%d*d+ee/2);\n",i,jj0);
        	fprintf(fid,"label(\"$%d$\",2*k+%d*d-ee/2);\n",i,jj);
        	fprintf(fid,"//draw(1.9*k+%d*d -- h/2+1.9*k+%d*d);\n",jj,jj);

        	if (i<NBs-1)
            	fprintf(fid,"draw(2*k+%d*d -- h/2+2*k+%d*d);\n",jj,jj);
		}
	}

	fclose(fid);

	}

	return 0;
}
