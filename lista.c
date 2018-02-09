#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMPATELA();system("cls");
#define LIMPABUFFER();fflush(stdin);

typedef struct lista {
	char NOME [30], TEL [15];
	struct lista *prox, *ant;
} LISTA;

LISTA *inicio, *final;

LISTA* inicia (void);
LISTA* aloca (void);
FILE* abrir_modo_leitura(void);
void ler (FILE *arq);
void fechar (FILE *arq);
void adiciona (char *xNome, char *xTel);
void imprime (void);
int vazia (LISTA* list);
int menu (void);

int main (void)
{
	inicio = final = inicia();

	for ( ; ; ) {
		switch (menu())
		{
			case 0:
				return 0;
			break;
			case 1:
				LIMPATELA();
				ler(abrir_modo_leitura());
				imprime();
				getch();
			break;
			default:
				puts ("Opcao invalida"); getch();
			break;
		}
	} 
	
	getch();
	return 0;
}

int menu (void)
{
	int op = 0;
	LIMPATELA();
	printf ("\t\t*******************************************\n");
	printf ("\t\t**    Manipulando arquivos de texto      **\n");
	printf ("\t\t*******************************************\n");
	printf ("\t\t**    Modo de Leitura                    **\n");
	printf ("\t\t*******************************************\n");
	printf ("0- Sair\n1- Ler e Mostrar dados na tela\n\n\nSua escolha: "); scanf ("%d", &op);

	return op;
}
	
LISTA* inicia (void)
{
	return NULL;
}

LISTA* aloca (void)
{
	return (LISTA *) malloc ( sizeof (LISTA));
}

void adiciona (char *xNome, char *xTel)
{	
	LISTA *novo;
	
	novo = aloca();
	if (!novo)
	{
		puts ("MEMORIA CHEIA");
		exit (1);
	}
	
	strcpy (novo->NOME, xNome);
	strcpy (novo->TEL, xTel);
	
	if ( vazia(inicio) < 0 )
	{
		novo->prox = NULL;
		novo->ant = NULL;
		final = novo;
		inicio = novo;
	}
	
	novo->ant = final;
	novo->prox = NULL;
	final->prox = novo;
	final = novo;
}

int vazia (LISTA* list)
{
	if (list == NULL) return -1;
	return 1;
}

void imprime(void)
{
	LISTA *p;
	p = inicio;
	
	if ( vazia(p) < 0)
	{
		puts ("\n...LISTA VAZIA ...");
	} else {
		puts ("Apresentando dados da lista\n");
		do {
			printf ("NOME: %s\tTELEFONE: %s\n", p->NOME, p->TEL);
			p = p->prox;
		} while (p != final->prox);
		puts ("\n...ENTER PARA VOLTAR AO MENU...");
	}
	
}

FILE* abrir_modo_leitura(void)
{	
	FILE *arq;
	
	arq = fopen ("contatos.txt", "r");
	return arq;
}

void ler (FILE *arq)
{
	if ( arq == NULL )
	{
		puts ("Arquivo nao encontrado");
		exit (1);
	} else {
		while (!feof(arq) )
		{
			char xNome [30], xTel [15];
			fscanf (arq, "%s %s\n", xNome, xTel);
			adiciona (xNome, xTel);
		}
		fechar(arq);
	}
}
void fechar (FILE *arq)
{	
	fclose(arq);
}