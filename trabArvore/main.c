#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matriz.h"
#include "Fila.h"
#include "arvore_n_aria.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	Matriz matriz;
	int qtd_no, a, i, x;
	
	carrega_arquivo("entrada.txt", &matriz);
	
	 qtd_no = matriz.lin;
	
	mostra_matriz(matriz);
	
	printf("Digite o valor do vertice(A):");
	scanf("%d", &a);
	
	if( a < 1 || a > qtd_no ){
		printf("Vertice invalido.\n");
	}
	
	int vs[a]; 
	memset(vs, 0, qtd_no * sizeof(int));
	
	Fila f;
	inicializa_fila(&f, qtd_no);
	
	Arvore t;
	inicializa_Arvore(&t, a);
	
	vs[a] = 1;
	inserir(&f, a);
	
	while(!fila_vazia(f)){
		remover(&f, &x);
		
		for( i = 0; i < qtd_no; i++){
			if( vs[i] == 0){
				vs[i] = 1;
				insere_filho(&t, x, i);
				inserir(&f, i);
			}
		}
	}
	
	gera_xml(t);
	
	desaloca_fila(&f);
	desaloca_matriz(&matriz);
	desaloca_arvore(&t);
	
	return 0;
}
