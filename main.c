/*****************************************************************************************
 * NOME DO ARQUIVO: main.c 
 * 
 * AUTOR: Gustavo Valadares Castro
 *
 * DESCRIÇÃO:	Programa que verifica quais TADs se comportam conforme entrada
 *
 * OBSERVAÇÕES:
 *				Repositório: https://github.com/GuVCastro/aed2-tad-beecrowd
 *				Compilador: gcc (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0 
 *
 * MUDANÇAS:
 *				DATA		AUTOR	DETALHES
 *				2021/10/29	Gustavo	Esqueleto do código
 *				2021/11/04	Gustavo Código Finalizado
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100
#define LIXO -1

typedef struct Fila {
	int dados[MAX + 1];
	int primeiro;
	int ultimo;
	int n;
} Fila;

typedef struct Pilha {
	int dados[MAX];
	int n;
} Pilha;

void newFila(Fila *f)
{
	f->primeiro = 0;
	f->ultimo = 0;
	f->n = 0;
}

void newPilha(Pilha *p)
{
	p->n = 0;
}

void enqueue(Fila *f, int dados) 
{
	if(((f->ultimo + 1) % MAX) == f->primeiro) 
		printf("FILA CHEIA\n");
	else {
		f->dados[f->ultimo] = dados;
		f->ultimo = (f->ultimo + 1) % MAX;
		f->n++;
	}
}

void push(Pilha *p, int dados) 
{
	if(p->n == MAX) 
		printf("PILHA CHEIA\n");
	else {
		p->dados[p->n] = dados;
		p->n++;
	}
}

void priorityEnqueue(Fila *f, int dados) 
{
	int tmp, i;
	
	if(((f->ultimo + 1) % MAX) == f->primeiro) 
		printf("FILA CHEIA\n");
	else {
		enqueue(f, dados);
	
		if(f->n > 1)
			for(i = (f->ultimo - 1) % MAX; i >= f->primeiro; i = (i - 1) % MAX) {
				if(dados >= f->dados[i]) {
					tmp = f->dados[i];
					f->dados[i] = dados;
					f->dados[(i + 1) % MAX] = tmp;
				}
				else 
					break;
			}
	}
}

int dequeue(Fila *f) 
{
	if(f->primeiro == f->ultimo)
		return LIXO;
	
	int dados = f->dados[f->primeiro];
	
	f->primeiro = (f->primeiro + 1) % MAX;
	f->n--;
	return dados;
}

int pop(Pilha *p) 
{
	if(p->n == 0)
		return LIXO;
	
	p->n--;
	return p->dados[p->n];
}

int main(void) 
{
	int cont, tipo, dado, tmp, i;
	Fila fila, fPrioridade;
	Pilha pilha;
	bool isFila, isPilha, isFilaPrioridade;
	
	
	while(scanf("%d", &cont) != EOF) {
		isFila = true;
		isPilha = true;
		isFilaPrioridade = true;
		
		newFila(&fila);
		newPilha(&pilha);
		newFila(&fPrioridade);	
		
		for(i = 0; i < cont; i++) {
			scanf("%d %d", &tipo, &dado);
		
			switch (tipo) {
				case 1:
					enqueue(&fila, dado);
					push(&pilha, dado);
					priorityEnqueue(&fPrioridade, dado);
					break;
				case 2:
					if(dado != dequeue(&fila))
						isFila = false;
					if(dado != pop(&pilha))
						isPilha = false;
					if(dado != dequeue(&fPrioridade))
						isFilaPrioridade = false;
					break;
				default: printf("ENTRADA INVALIDA\n"); break;
			}
		}

		if ((isFila && isPilha) || (isFila && isFilaPrioridade) || (isFilaPrioridade && isPilha))
			printf("not sure\n");
		else if (isFila && !(isPilha || isFilaPrioridade))
			printf("queue\n");
		else if (isPilha && !(isFila || isFilaPrioridade))
			printf("stack\n");
		else if	(isFilaPrioridade && !(isFila || isPilha))
			printf("priority queue\n");
		else
			printf("impossible\n");
	}

	return 0;
}
