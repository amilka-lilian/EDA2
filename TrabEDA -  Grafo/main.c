#include "Fila.h"
#include "Matriz.h"
#include "PilhaGenerica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  int qtd_grafo, a, b, i;
  Matriz matriz;
  
  carrega_arquivo("entrada.txt", &matriz);
  
  qtd_grafo = matriz.lin;
  
  mostra_matriz(matriz);
  
  printf("Insira o vertice de inicio(a): ");
  scanf("%d", &a);
  printf("Insira o vertice de destino(b): ");
  scanf("%d", &b);
  
  if( a < 1 || a > qtd_grafo || b < 1 || b > qtd_grafo ){
  	printf("Vertices de inicio e/ou destino invalidos.\n");	
  	return EXIT_FAILURE;
  }
   	
  int vs[qtd_grafo], va[qtd_grafo];
  memset(vs, 0, qtd_grafo * sizeof(int));
  memset(va, 0, qtd_grafo * sizeof(int));
  
  
  
  Fila f;
  inicializa_fila(&f, qtd_grafo);
  
  vs[ a - 1 ] = 1;
  inserir( &f, a );
  int achou = 0;
  int x;
  
  while (!fila_vazia(f) && !achou){
  	remover( &f, &x );
  	
  	if( x == b ){
  		achou = 1;
  		printf("Achou!\n");
  		
	}else{
		for( i = 0; i < qtd_grafo; i++){
			int valor;
			get_valor (&matriz, x - 1, i, &valor);
			
			if(valor == 1 && vs[i] == 0){
				vs[i] = 1;
				va[i] = x;
				
				inserir(&f, i + 1 );
			}
		}
	}
  }
  if ( achou ){
  	PilhaGenerica pilha;
  	inicializa_pilha(&pilha, 8, sizeof(int));
  	
  	while( x != 0 ){
  		empilha( &pilha, &x);
  		x = va[ x - 1 ];
	  }
	  
	  while (pilha.topo > -1){
	  	int temp;
	  	desempilha(&pilha, &temp);
	  	printf("%d\n", temp);
	  }
  }
  return EXIT_SUCCESS;
}
