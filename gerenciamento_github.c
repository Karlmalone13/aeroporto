#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//PARA APROXIMACOES
struct Voos
{
	int numDoVoo;
	int combustivel;
	struct Voos* prox;
};
typedef struct Voos voos;

//PARA DECOLAGENS
typedef struct parado{

       int numDoVoo;
       int combustivel;
       struct parado* prox;
}deposito;

int tam;
int UnTempo = 5;//tempo a cada instante

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
	    *NAproximacoes = geraRand(0,0);
	    *NDecolagens = geraRand(0,0);
		printf("\nNumero de Aproximacoes = %d\nNumero de Decolagens = %d\n", *NAproximacoes, *NDecolagens);
        return;
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

//Aloca Aproximacoes
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
//Aloca AVIOES POUSADOS APENAS
deposito *alocaPOUSOS(int* NDecolagens, int* i)
{
	deposito *novo = (deposito *) malloc(sizeof(deposito));

	if(!novo)
	{
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else
	{
		novo->numDoVoo = *i + 1;
		novo->combustivel = 13;//tanque dos avios com nivel maximo de cobustivel
#ifdef TESTANDO
		printf ("\n%d ", novo->combustivel);
#endif

		return novo;
	}
}
//insere na Fila de pouso
void insereNOPOUSO(deposito* POUSOS, int* NDecolagens)
{
	int i;

	for(i = 0; i < *NDecolagens; i++)
	{
		deposito *novo = alocaPOUSOS(&NDecolagens, &i);
		novo->prox = NULL;

		if(vazia(POUSOS))
			POUSOS->prox = novo;//primeiro igual ao proximo
		else
		{
			voos *tmp = POUSOS->prox;//PRIMEIRO TERMO

			while(tmp->prox != NULL)
				tmp = tmp->prox;

			tmp->prox = novo;
		}
		tam++;
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
		novo->prox = NULL;//primeiro termo nulo

		if(vazia(FILA))
			FILA->prox = novo;
		else
		{
			voos *tmp = FILA->prox;//primeiro termo

			while(tmp->prox != NULL)
				tmp = tmp->prox;

			tmp->prox = novo;
		}
		tam++;
    }
}

void exibe(voos *FILA)
{

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
			printf("-> Aeronave 0%d *", tmp->numDoVoo);
		}
		else
		{
			printf("-> Aeronave %d *", tmp->numDoVoo);
		}

		if(tmp->combustivel == 1)
		{
			printf("Nivel de combustivel: 0%d (ATENCAO! POUSO DE EMERGENCIA)\n", tmp->combustivel);
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

void ordenarFila(voos* FILA, int* comb, int* num, int* NAproximacoes, int tempo[])
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
	 printf("---------------------------------------------------------------------\n");
         printf("Hora prevista para chegada | Numero do Voo | Nivel de Combustivel   |\n");
         printf("---------------------------------------------------------------------\n");


	while(aux != NULL)

	{

        HORA(tempo);
		if(aux->numDoVoo <= 9){

			printf("              |-> Aeronave 0%d", aux->numDoVoo);
		}
		else{
			printf("              |-> Aeronave %d", aux->numDoVoo);
		}

		if(aux->combustivel <= 9){
            printf(" |->            0%d        |\n",aux->combustivel);
            printf("----------------------------------------------------------------------\n");
		}
		else{
			printf(" |->            %d         |\n",aux->combustivel);
			printf("----------------------------------------------------------------------\n");
		}
		tempo[1] = tempo[1] + UnTempo;
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
            //SÓ desenfileira o A fila de aproximação se o combustivel for 1
                    voos *tmp = FILA->prox;
                  FILA->prox = tmp->prox;
		         if(tmp-> prox == NULL && NAproximacoes == 1)
			          printf ("NENHUM VOO SE APROXIMANDO\n!");
		                     tam--;
		/* É importante verificar se o ponteiro é nulo antes de liberar a memória */
		if(tmp)
			free(tmp);

		return tmp->prox;//retorna o proximo elemento
            }


}
//Libera pousa na pista 1
void Pista1(voos* FILA)
{
	voos* aux = FILA->prox;

	printf("\n\n");
	desenhar_linha(60);
	printf ("\t\tPISTA 1\n");
	desenhar_linha(60);
	printf("\n");

	//SÓ libera a aterrissagem se o combustivel for 1

	   if(aux->numDoVoo <= 9)
		  printf ("-> Aeronave 0%d LIBERADA A ATERRISSAGEM NA PISTA 1\n", aux->numDoVoo);
	   else
          printf ("-> Aeronave %d LIBERADA A ATERRISSAGEM NA PISTA 1\n", aux->numDoVoo);


}

void Desinfileirar(voos* FILA, int* NAproximacoes)
{
	voos* aux1 = NULL;//QUE ISSO??

	/* Temos que verificar se FILA é um ponteiro válido, antes de utilizá-lo */
	if(FILA == NULL)
	{
		printf( "BUG: o ponteiro FILA no endereco %p é nulo!!!\n", FILA);
		return;
	}

	retira(FILA, &NAproximacoes);
	voos* aux = FILA->prox;

	printf ("\n\n");
	desenhar_linha(60);
	printf ("\t\tNOVA LISTA DE APROXIMACOES\n");
	desenhar_linha(60);
	printf("\n");

	while(aux != NULL)
	{
		if(aux->numDoVoo <= 9)
			printf ("-> Aeronave 0%d", aux->numDoVoo);
		else
			printf ("-> Aeronave %d", aux->numDoVoo);

        aux->combustivel =aux->combustivel -1; //Subtrai 1 do combustivel das aeronaves aproximantes.

		if(aux->combustivel <= 9)
			printf(" *Nivel de combustivel: 0%d\n", aux->combustivel );

		else
			printf(" *Nivel de combustivel: %d\n", aux->combustivel );

		aux = aux->prox;
	}

	//FILA ja vazia?
	if(FILA->prox == NULL){
        printf("\n        SEM APROXIMACOES    \n");
	}

}
//DECOLAR AVIOES
void Decolar(deposito* POUSADOS, int* NDecolagens, int tempo[])
{
	voos* aux1 = NULL;//QUE ISSO??

	/* Temos que verificar se FILA é um ponteiro válido, antes de utilizá-lo */
	if(POUSADOS == NULL)
	{
		printf( "BUG: o ponteiro FILA no endereco %p é nulo!!!\n", POUSADOS);
		return;
	}

	retira(POUSADOS, &NDecolagens);
	deposito* aux = POUSADOS->prox;

	printf ("\n\n");
	desenhar_linha(60);
	printf ("\t\tNOVA LISTA DE AVIOES PARADOS\n");
	desenhar_linha(60);
	printf("\n");
     printf("\n");
	 printf("---------------------------------------------------------------------\n");
         printf("Hora prevista para chegada | Numero do Voo | Nivel de Combustivel   |\n");
         printf("---------------------------------------------------------------------\n");
	while(aux != NULL)
	{
	    HORA(tempo);
		if(aux->numDoVoo <= 9)
			printf("              |-> Aeronave 0%d", aux->numDoVoo);
		else
			printf("              |-> Aeronave %d", aux->numDoVoo);

		if(aux->combustivel <= 9){
			 printf(" |->            0%d        |\n",aux->combustivel);
			printf("----------------------------------------------------------------------\n");
		}
		else{
			printf(" |->            %d         |\n",aux->combustivel);
			printf("----------------------------------------------------------------------\n");
		}
        tempo[1] = tempo[1] + UnTempo;
		aux = aux->prox;
	}

	//FILA ja vazia?
	if(POUSADOS->prox == NULL){
        printf("\n        SEM APROXIMACOES    \n");
	}

}
//função para gerar o horario dos voos
 void HORA(int tempo[]){

   if(tempo[0] > 10 && tempo[1] > 59){
        tempo[0]++;
        tempo[1] = tempo[1] -60;
    printf("        %d:0%d", tempo[0] , tempo[1]);
   }
  else if (tempo[0] < 10 && tempo[1] > 59){
        tempo[0]++;
        tempo[1] = tempo[1] -60;
    printf("        0%d:0%d", tempo[0], tempo[1]);
    }
   else if(tempo[0]<10 && tempo[1]>10){
    printf("       0%d:%d", tempo[0], tempo[1]);
   }
  else if(tempo[0] < 10 && tempo[1] < 10){
     printf("       0%d:0%d", tempo[0], tempo[1]);
   }
   else if (tempo[0] > 10 && tempo[1] <10){
     printf("       %d:0%d", tempo[0], tempo[1]);
    }
   else if(tempo[0] > 10 && tempo[1] > 59){
        tempo[0]++;
        tempo[1] = tempo[1] -60;
    printf("        %d:0%d", tempo[0] , tempo[1]);
   }
   else{
    printf("        %d:%d", tempo[0], tempo[1]);
   }


 }
int main(void)
{
	int NVoos, NAproximacoes, NDecolagens;
	int tempo[2];
	tempo[0] = geraRand(0,24);
	tempo[1] = geraRand(0,59);

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

    printf("                           ");
    desenhar_linha(60);
	printf("                           *           Aeroporto Internacional de Paraisos            *\n");
    printf("                           ");
	desenhar_linha(60);
	printf("\nHora Atual: ");
	HORA(tempo);
    printf("\n");
	gerarVoos(&NVoos, &NAproximacoes, &NDecolagens);
	int comb[NAproximacoes];
	int num[NAproximacoes];

	//Só monta a fila se tiver aproximacoes
	if(NAproximacoes > 0){
	  insere(FILA, &NAproximacoes);
	  printf("\n\n");
	  desenhar_linha(60);
	  printf("\t\tRELATORIO DE APROXIMACOES\n");
	  desenhar_linha(60);

	  exibe(FILA);
	  ordenarVetor(FILA, &NAproximacoes, comb, num);
	  ordenarFila(FILA, comb, num, &NAproximacoes, tempo);

	//verificar antes se precisa decolar alguem!!
	  Pista1(FILA);//Libera pouso na pista 1
	  Desinfileirar(FILA, &NAproximacoes);
	/* É preciso liberar a memória alocada! */
	   if(FILA)
		 free(FILA);
	}
//////////////////////////////////////////////////////////////////////////////////////////

printf("\n\n--------------------------------------------------------------------------------------------------------------------");
//Cria fila de avioes no deposito
    deposito* POUSADOS  = (deposito *)malloc(sizeof(deposito));
    if(!POUSADOS)
	{
		printf("Sem memoria disponivel!\n");
		exit(1);
	}
	else
	{
		inicia(POUSADOS);
	}

	//SÓ CRIA A FILA SE TIVER AVIOS PARA DECOLAR
	if(NDecolagens > 0){
      insereNOPOUSO(POUSADOS, &NDecolagens);
      printf("\n\n");
	  desenhar_linha(60);
	  printf("\t\tRELATORIO DE AVIOES PARADOS\n");
	  desenhar_linha(60);

      exibe(POUSADOS);
	}

	if(NDecolagens > 0 && NAproximacoes == 0){

        Decolar(POUSADOS,NDecolagens, tempo);//ta deoolando apenas 1 aviao, porque??
	}

	printf("\n");

    printf("------------------------------------------SIMULACAO ENCERRADA-----------------------------------------------------\n\n");
    pausar();
	return 0;
}
