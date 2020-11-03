
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h> 
#include <windows.h>


typedef struct _t{
	char nome[15];
	char sigla[3];
	int P, V, E, D, gM, gS;
	struct _t *pai;
	struct _t *esq;
	struct _t *dir;
} TIME;


void inicializar (TIME **tree) {
    *tree = NULL;
}


int estaVazia (TIME *tree) {
    
    if (tree == NULL)
        return 1;

    return 0;
}

TIME* achaMaior (TIME* arvore) {

    TIME* atual = arvore;

    if (!estaVazia(arvore))
        while (atual->dir != NULL)
            atual = atual->dir;

    return atual;

}

void inserir (TIME **tree, char *s, char *n) {
    
    TIME* aux;
    TIME* papai;

    TIME *novo = (TIME*) malloc(sizeof(TIME));   
    strcpy(novo->sigla, s);
    strcpy(novo->nome, n);
    //printf("%s\n", novo->sigla);
    novo->P = 0;
    novo->V = 0;
    novo->E = 0;
    novo->D = 0;
    novo->gM = 0;
    novo->gS = 0;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
   
    if (estaVazia(*tree)) {
        *tree = novo;
        return;
    }
    
    aux = *tree;
    while (aux != NULL) {

        papai = aux;
        
        if (strcmp(s, aux->sigla) < 0){
            aux = aux->esq;
    	}
		
        else if (strcmp(s, aux->sigla) > 0){
            aux = aux->dir;
    	}

        else {
            return;
        }
    
    } 
    
    if (strcmp(s, papai->sigla) < 0)
        papai->esq = novo;
    else
        papai->dir = novo;
	
	novo->pai = papai;
    
} 

int remover(TIME **arvore, char *s) {

    TIME* atual = *arvore;
    TIME* maior;
    char valor[3];

    if (estaVazia(*arvore))
        return 1;
	
    while (atual != NULL) {
        if (strcmp(s, atual->sigla) == 0){	
            break;
    	}
        
        else if (strcmp(s, atual->sigla) < 0){
            atual = atual->esq;
    	}
        else{
            atual = atual->dir;
    	}
    }

    if (atual == NULL)
        return 0;

    /* ================================================================ */
    /* CASO 1: NOH A SER REMOVIDO EH NOH FOLHA                          */
    /* ================================================================ */
    if ((atual->esq == NULL) && (atual->dir == NULL)) {

        /* noh a ser removido eh noh raiz */
        if (atual->pai == NULL) {
            inicializar(arvore);
            free(atual);
            return 1;
        }
       
        /* noh a ser removido nao eh o noh raiz */
        if (strcmp(s, atual->pai->sigla) < 0)
            atual->pai->esq = NULL;
        else
            atual->pai->dir = NULL;

        free(atual);
        return 1;

    } 


    /* ================================================================ */
    /* CASO 2: NOH A SER REMOVIDO TEM APENAS UM FILHO                   */
    /* ================================================================ */
    if (((atual->esq != NULL) && (atual->dir == NULL)) ||
        ((atual->esq == NULL) && (atual->dir != NULL))) {

        /* caso o noh 'atual' for o noh raiz */
        if (atual->pai == NULL) {

            /* se filho do noh atual for o filho da esquerda */
            if (atual->esq != NULL)
                *arvore = atual->esq;

            /* se filho do noh atual for o filho da direita */
            else
                *arvore = atual->dir;
        }

        /* caso o noh 'atual' nao for o noh raiz */
        else {

            /* caso do noh 'atual' ser o filho da esquerda */
            if (atual == atual->pai->esq) {
                
                /* caso do filho do noh 'atual' ser o filho da esquerda */
                if (atual->esq != NULL) {
                    atual->pai->esq = atual->esq;
                    atual->esq->pai = atual->pai;
                }

                /* caso do filho do noh 'atual' ser o filho da direita */
                else {
                    atual->pai->esq = atual->dir;
                    atual->dir->pai = atual->pai;
                }

            } /* fim do if (atual == filho da esquerda) */


            /* caso noh 'atual ser o filho da direita */
            else if (atual == atual->pai->dir) {

                /* caso do filho do noh 'atual' ser o filho da esquerda */
                if (atual->esq != NULL) {
                    atual->pai->dir = atual->esq;
                    atual->esq->pai = atual->pai;
                }

                /* caso do filho do noh 'atual' ser o filho da direita */
                else {
                    atual->pai->dir = atual->dir;
                    atual->dir->pai = atual->pai;
                }
            }
        } 

        free(atual);
        return 1;
    } 

    /* ================================================================ */
    /* CASO 3: NOH A SER REMOVIDO TEM AMBOS OS FILHOS                   */
    /* ================================================================ */
    if ((atual->esq != NULL) && (atual->dir != NULL)) {

        /* acha o noh de maior valor da sub-arvore da esquerda */
        maior = achaMaior(atual->esq);
        
        /* guarda valor do noh encontrado */
        strcpy(valor, maior->sigla);

        /* remove o noh econtrado */
        remover(arvore, maior->sigla);

        /* substitui 'atual' pelo noh encontrado */
        strcpy(atual->sigla, valor);

    } /* fim do CASO 3 */

}


void inserePontos(TIME **tree, char s[], int qtd, int vit, int emp, int der, int gmc, int gsf) {
    TIME* aux = *tree;

    while (aux != NULL) {
        
        if (strcmp(s, aux->sigla) == 0)
            break;
        
        else if (strcmp(s, aux->sigla) < 0)
            aux = aux->esq;
        
        else
            aux = aux->dir;

    } 
    aux->P += qtd;
    aux->V += vit;
    aux->E += emp;
    aux->D += der;
    aux->gM += gmc;
    aux->gS += gsf; 
}

void pesquisaSigla(TIME *tree, char s[]) {
    TIME* aux = tree;

    while (aux != NULL) {
        
        if (strcmp(s, aux->sigla) == 0)
            break;
        
        else if (strcmp(s, aux->sigla) < 0)
            aux = aux->esq;
        
        else
            aux = aux->dir;
    } 

	
    printf("Time: %s - %s \n Pontos: %d \n Vitorias: %d \n Empates: %d \n Derrotas: %d \n Gols Marcados : %d \n Gols Sofridos: %d \n\n", aux->sigla, aux->nome, aux->P, aux->V, aux->E, aux->D, aux->gM, aux->gS);
	
}


TIME* auxiliar(TIME *tree, int p, TIME *aux){
	int pts = p;
	if (tree != NULL) {
        if(pts < tree->P)
        	aux = tree;
    	auxiliar(tree->esq, pts, aux);	
        auxiliar(tree->dir, pts, aux);	
    }
	return aux;
}

void campeao(TIME *tree){
	TIME* aux = tree;
	aux = auxiliar(tree, 0, aux);
	printf("\n\nTime Campeão com %d pontos:\n ****** %s ****** \n",aux->P, aux->nome);
}



void preOrdem (TIME *tree) {

    if (tree != NULL) {
        printf("%s ", tree->sigla);
        preOrdem(tree->esq);
        preOrdem(tree->dir);
    }

}

void posOrdem (TIME *tree) {

    if (!estaVazia(tree)) {
        posOrdem(tree->esq);
        posOrdem(tree->dir);
        printf("%s ", tree->sigla);
    }

} 

void emOrdem (TIME *tree) {

    if (!estaVazia(tree)) {
        emOrdem(tree->esq);
        printf("%s ", tree->sigla);
        emOrdem(tree->dir);
    }

}


int main(void){
  	
	FILE *arq;
	char sigla[3];
	char siglab[3];
	char nome[15];
	int g1, g2, i;
	
	
	TIME *arvore;
    TIME *aux;
	int ret;
	
    inicializar(&arvore);

    	
	arq = fopen("A05Times.txt", "r");
	
	for(i=0; i<20; i++){
		fscanf(arq, "%s  %s \n",
				&sigla,
				&nome);	
				//printf("%s -", sigla);
	inserir(&arvore, sigla, nome);
	}
	
	arq = fopen("A05Partidas.txt", "r");
	
	for(i=0; i<380; i++){
		fscanf(arq, "%s %d %*s %d %s",
				&sigla,
				&g1,
				&g2,
				&siglab);
		//printf("%s %d x %d %s\n", sigla, g1, g2, siglab);
		
		if(g1 == g2){
			inserePontos(&arvore, sigla, 1, 0, 1, 0, g1, g2);
			inserePontos(&arvore, siglab, 1, 0, 1, 0, g2, g1);
		}
		else if(g1 > g2){
			inserePontos(&arvore, sigla, 3, 1, 0, 0, g1, g2);
			inserePontos(&arvore, siglab, 0, 0, 0, 1, g2, g1);
		}
		else{
			inserePontos(&arvore, siglab, 3, 1, 0, 0, g2, g1);
			inserePontos(&arvore, sigla, 0, 0, 0, 1, g1, g2);
		}
	}
	
	
	printf("-Arvore atual-\n\n");
	printf("PRE: ");
    preOrdem(arvore);
    printf("\n");

    printf("POS: ");
    posOrdem(arvore);
    printf("\n");
    
    printf(" EM: ");
    emOrdem(arvore);
    printf("\n");
    
    printf("\n\nDigite o time que deseja saber os detalhes: ");
	gets(sigla);
	pesquisaSigla(arvore, sigla);
    
    printf("\n\n Qual time deseja excluir da arvore? ");
    gets(sigla);
    remover(&arvore, sigla);
    printf("-Arvore apos remocao-\n\n");
    
    printf("PRE: ");
    preOrdem(arvore);
    printf("\n");

    printf("POS: ");
    posOrdem(arvore);
    printf("\n");
    
    printf(" EM: ");
    emOrdem(arvore);
    printf("\n");
    
    campeao(arvore);   
    
	return 0;
}

