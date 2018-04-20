#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

struct Voos{
    int numDoVoo;
    int combustivel;
    struct Voos* prox;
};

typedef struct Voos voos;

int tam;

void inicia(voos *FILA)
{
	FILA->prox = NULL;
	tam = 0;
}

int vazia(voos *FILA)
{
	if(FILA->prox == NULL)
		return 1;
	else
		return 0;
}

 void gerarVoos(int* NVoos, int* NAproximacoes, int* NDecolagens)
 {
    *NVoos = geraRand(0,42);

    printf("\nNumero de Voos = %d     |", *NVoos);


    if(*NVoos == 0)
    {
        printf("\nNumero de Aproximacoes = 0 \nNumero de Decolagens = 0");
    }

    else
    {
          *NAproximacoes = geraRand(0,28);

        do
        {

            *NAproximacoes = geraRand(0,28);

        }

        while(*NAproximacoes > *NVoos);

            printf("     Numero de Aproximacoes = %d     |", *NAproximacoes);

            *NDecolagens = *NVoos - *NAproximacoes;

            printf("     Numero de Decolagens = %d     |", *NDecolagens);

    }
}

voos *aloca(int* NAproximacoes, int* i)
{
	voos *novo = (voos *) malloc(sizeof(voos));
	//voos *aux =
	if(!novo)
    {
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else
    {
        novo->numDoVoo = *i + 1;
        novo->combustivel = combustivel();
		//printf ("\n%d ", novo->combustivel);

		return novo;

	}
}

int geraRand(int min, int max)
{
    int r;

    srand(time(NULL));

    r = min + rand()%(max - min -1);

    return r;
}

 int combustivel()
{
    int combustivel;

    combustivel = rand() % 14;

    do{
        combustivel = rand() % 14;

    }   while(combustivel == 0);

    return combustivel;

}


void insere(voos* FILA, int* NAproximacoes)
{
    int i;

    for(i = 0; i < *NAproximacoes; i++)
    {
        voos *novo = aloca(&NAproximacoes, &i);
        novo->prox = NULL;


        if(vazia(FILA))
            FILA->prox = novo;

        else
        {
            voos *tmp = FILA->prox;

            while(tmp->prox != NULL)
                tmp = tmp->prox;

            tmp->prox = novo;
        }
        tam++;
   }
}

void exibe(voos *FILA)
{
	printf ("\n\n -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n");
    printf ("                                                   RELATORIO DE APROXIMACOES");
    printf ("\n -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n");

	if(vazia(FILA))
    {
		printf("Nenhum pouso no momento!\n\n");
		return;
	}

	voos *tmp = FILA->prox;

	while(tmp != NULL){

		if(tmp->numDoVoo <= 9)
        {
            printf("-> Aeronave 0%d chegando. ", tmp->numDoVoo);
        }

		else
        {
            printf("-> Aeronave %d chegando. ", tmp->numDoVoo);
		}

		if(tmp->combustivel == 1)
        {
            printf("Nivel de combustivel: 0%d (POUSO DE EMERGENCIA!!!)\n", tmp->combustivel);
        }
		else
        {
            if(tmp->combustivel <= 9)
            {
                printf("Nivel de combustivel: 0%d\n", tmp->combustivel);
            }
            else
            {
                printf("Nivel de combustivel: %d\n", tmp->combustivel);
            }
        }

		tmp = tmp->prox;
	}

}

void ordenarVetor(voos* FILA, int* NAproximacoes, int comb[], int num[])
{
    int i, j;

    voos* tmp = FILA->prox;

    for(i = 0; i <*NAproximacoes; i++)
    {
        if(tmp != NULL)
        {
            comb[i] = tmp->combustivel;
            num[i] = tmp->numDoVoo;
            tmp = tmp->prox;
        }
         else
                break;


    }
/*printf ("vetor desordenado: \n");
    for(int f = 0; f < tam; f++)
    {
        printf ("%d ", comb[f]);
    }
*/
   int a, b, continua, aux, aux2;


    for(a = 0; a < tam; a++)
    {
        for(b = 0; b < tam - 1; b++)
        {
            if(comb[b] > comb[b+1])
            {
                aux = comb[b];
                aux2 = num[b];
                comb[b] = comb[b+1];
                num[b] = num[b+1];
                comb[b+1] = aux;
                num[b+1] = aux2;
            }
        }
    }
   /* printf ("\n\nvetor ordenado : ");
    int l;
    for(l = 0; l < *NAproximacoes; l++)
    {
        printf ("%d ", comb[l]);
    }
*/


}

void ordenarFila(voos* FILA, int* comb, int* num, int* NAproximacoes)
{
    int i;

    voos* tmp = FILA->prox;

    for(i = 0; i <*NAproximacoes; i++)
    {
        if(tmp != NULL)
        {
            tmp->combustivel = comb[i];
            tmp->numDoVoo = num[i];
            tmp = tmp->prox;
        }
         else
                break;

    }

    voos* aux = FILA->prox;

    printf ("\nLISTA DE POUSO DE ACORDO COM A PRIORIDADE:\n");
    //printf (" ");

    while(aux != NULL)
    {
        if(aux->numDoVoo <= 9)
            printf ("-> Aeronave 0%d chegando. ", aux->numDoVoo);

        else
            printf ("-> Aeronave %d chegando. ", aux->numDoVoo);

        if(aux->combustivel <= 9)
            printf("Nivel de combustivel: 0%d\n", aux->combustivel);

        else
            printf("Nivel de combustivel: %d\n", aux->combustivel);



        aux = aux->prox;
    }

}

voos *retira(voos *FILA)
{
	if(FILA->prox == NULL){
		printf("Fila ja esta vazia\n");
		return NULL;
	}else{
		voos *tmp = FILA->prox;
		FILA->prox = tmp->prox;
		tam--;
		free(tmp);
		return tmp->prox;
	}

}
void Pista1(voos* FILA)
{
    voos* aux = FILA->prox;
    printf ("\n\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- --");
    printf ("\n           PISTA 1\n");
    printf ("-- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n");

    if(aux->numDoVoo <= 9)
    {
        printf ("-> Aeronave 0%d acaba de pousar\n\n", aux->numDoVoo);
    }
    else
         printf ("-> Aeronave %d acaba de pousar\n\n", aux->numDoVoo);



}




void Desinfileirar(voos* FILA)
{
    voos* aux = retira(FILA);
    printf ("\n\nLISTA DE APROXIMACOES:\n");
   // printf (" ");
    while(aux != NULL)
    {
        if(aux->numDoVoo <= 9)
            printf ("-> Aeronave 0%d chegando. ", aux->numDoVoo);

        else
            printf ("-> Aeronave %d chegando. ", aux->numDoVoo);

        if(aux->combustivel <= 9)
            printf("Nivel de combustivel: 0%d\n", aux->combustivel);

        else
            printf("Nivel de combustivel: %d\n", aux->combustivel);

        aux = aux->prox;
    }
}



int  main(void){

    int NVoos, NAproximacoes, NDecolagens, a;

    voos* FILA = (voos *) malloc(sizeof(voos));

    if(!FILA)
    {
        printf("Sem memoria disponivel!\n");
		exit(1);
    }
    else
    {
        inicia(FILA);
    }

    printf("Aeroporto Internacional de Paraisos\n");
    printf("\nHora Atual: ");
    system("time/t");


    gerarVoos(&NVoos, &NAproximacoes, &NDecolagens);
    int comb[NAproximacoes];
    int num[NAproximacoes];
    insere(FILA, &NAproximacoes);
    exibe(FILA);
    ordenarVetor(FILA, &NAproximacoes, comb, num);
    ordenarFila(FILA, comb, num, &NAproximacoes);
    Pista1(FILA);
    Desinfileirar(FILA);


    printf("\n");
    //printf("tamanho: %d\n", tam);

    return 0;
}
