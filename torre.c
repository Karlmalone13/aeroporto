#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct Voos
{
	int numDoVoo;
	int combustivel;
	struct Voos* prox;
};

typedef struct Voos voos;

int tam;

void pausar()
{
	printf( "Aperte alguma tecla ...");
	getchar();
}

/* Desenha uma linha com um tamanho especificado */
void desenhar_linha(int tamanho)
{
	for(int i = 0; i < tamanho; i++)
		printf( "\xC4");
	
	printf("\n");
}

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

	printf("\nNumero de Voos = %d\n", *NVoos);
	
	if(*NVoos == 0)
	{
		printf("\nNumero de Aproximacoes = 0\nNumero de Decolagens = 0\n");
	}
	else
	{
		*NAproximacoes = geraRand(0,28);
		do
		{
			*NAproximacoes = geraRand(0,28);
		} while(*NAproximacoes > *NVoos);

		printf("Numero de Aproximacoes = %d\n", *NAproximacoes);

		*NDecolagens = *NVoos - *NAproximacoes;
		printf("Numero de Decolagens = %d\n\n", *NDecolagens);
	}
}

voos *aloca(int* NAproximacoes, int* i)
{
	voos *novo = (voos *) malloc(sizeof(voos));
	
	if(!novo)
	{
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else
	{
		novo->numDoVoo = *i + 1;
		novo->combustivel = combustivel();
#ifdef TESTANDO
		printf ("\n%d ", novo->combustivel);
#endif

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

	do
	{
		combustivel = rand() % 14;
	} while(combustivel == 0);

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
	printf("\n\n");
	desenhar_linha(60);
	printf("\t\tRELATORIO DE APROXIMACOES\n");
	desenhar_linha(60);

	if(vazia(FILA))
	{
		printf("Nenhum pouso no momento!\n\n");
		return;
	}

	voos *tmp = FILA->prox;

	while(tmp != NULL)
	{
		if(tmp->numDoVoo <= 9)
		{
			printf("-> Aeronave %2d *", tmp->numDoVoo);
		}
		else
		{
			printf("-> Aeronave %d *", tmp->numDoVoo);
		}

		if(tmp->combustivel == 1)
		{
			printf("Nivel de combustivel: %2d (ATENCAO! POUSO DE EMERGENCIA)\n", tmp->combustivel);
		}
		else
		{
			if(tmp->combustivel <= 9)
			{
				printf("Nivel de combustivel: %2d\n", tmp->combustivel);
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
	
#ifdef TESTANDO
	printf ("vetor desordenado:\n");
	for(int f = 0; f < tam; f++)
	{
		printf ("%d ", comb[f]);
	}
#endif

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
	
#ifdef TESTANDO
	printf ("\n\nvetor ordenado : ");
	int l;
	for(l = 0; l < *NAproximacoes; l++)
	{
		printf ("%d ", comb[l]);
	}
#endif
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
	
	printf("\n");
	desenhar_linha(60);
	printf ("\t\tLISTA DE POUSO DE ACORDO COM A PRIORIDADE:\n");
	desenhar_linha(60);
	printf("\n");
	
	while(aux != NULL)
	{
		if(aux->numDoVoo <= 9)
			printf ("-> Aeronave %2d *", aux->numDoVoo);

		else
			printf ("-> Aeronave %d *", aux->numDoVoo);

		if(aux->combustivel <= 9)
			printf("Nivel de combustivel: %2d\n", aux->combustivel);

		else
			printf("Nivel de combustivel: %d\n", aux->combustivel);
		
		aux = aux->prox;
	}

}

voos *retira(voos *FILA, int NAproximacoes)
{
	if(FILA->prox == NULL) {
		printf("FILA JA ESTA VAZIA!\n");
		return NULL;
	}
	else {
		voos *tmp = FILA->prox;
		FILA->prox = tmp->prox;
		if(tmp-> prox == NULL && NAproximacoes == 1)
			printf ("NENHUM VOO SE APROXIMANDO\n!");
		tam--;
		
		/* É importante verificar se o ponteiro é nulo antes de liberar a memória */
		if(tmp)
			free(tmp);
		
		return tmp->prox;
	}

}
void Pista1(voos* FILA)
{
	voos* aux = FILA->prox;
	
	printf("\n\n");
	desenhar_linha(60);
	printf ("\t\tPISTA 1\n");
	desenhar_linha(60);
	printf("\n");
	
	if(aux->numDoVoo <= 9)
		printf ("-> Aeronave 0%d LIBERADA A ATERRISSAGEM NA PISTA 1\n", aux->numDoVoo);
	else
		 printf ("-> Aeronave %d LIBERADA A ATERRISSAGEM NA PISTA 1\n", aux->numDoVoo);
}

void Desinfileirar(voos* FILA, int* NAproximacoes)
{
	voos* aux = NULL;
	
	/* Temos que verificar se FILA é um ponteiro válido, antes de utilizá-lo */
	if(FILA == NULL)
	{
		printf( "BUG: o ponteiro FILA no endereco %p é nulo!!!\n", FILA);
		return;
	}
	
	retira(FILA, &NAproximacoes);
	
	printf ("\n\n");
	desenhar_linha(60);
	printf ("\t\tNOVA LISTA DE APROXIMACOES\n");
	desenhar_linha(60);
	printf("\n");

	while(aux != NULL)
	{
		if(aux->numDoVoo <= 9)
			printf ("-> Aeronave %2d AGUARDANDO A ORDEM DE ATERRISSAGEM.", aux->numDoVoo);
		else
			printf ("-> Aeronave %d AGUARDANDO A ORDEM DE ATERRISSAGEM.", aux->numDoVoo);

		if(aux->combustivel <= 9)
			printf("Nivel de combustivel: 0%d\n", aux->combustivel);

		else
			printf("Nivel de combustivel: %d\n", aux->combustivel);

		aux = aux->prox;
	}
}

int main(void)
{
	int NVoos, NAproximacoes, NDecolagens;
	
	voos* FILA = (voos *)malloc(sizeof(voos));

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
	Desinfileirar(FILA, &NAproximacoes);

	/* É preciso liberar a memória alocada! */
	if(FILA)
		free(FILA);
	
	printf("\n");
	pausar();

	return 0;
}
