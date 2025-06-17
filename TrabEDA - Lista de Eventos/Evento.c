#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "DataHora.h"
#include "Evento.h"

int cadastrar_evento(Lista *evento, Evento *novo_evento) {
    if (lista_vazia(*evento))
        return insere_inicio(evento, (void*)novo_evento);

    Elemento *atual = evento->cabeca;
    Elemento *anterior = NULL;

    printf("Nova Data: Data %d/%d/%d\n", novo_evento->data.dia, novo_evento->data.mes, novo_evento->data.ano);

    while (atual != NULL) {
        Evento *evento_atual = (Evento *)atual->info;

        printf("Evento atual: Data %d/%d/%d\n", evento_atual->data.dia, evento_atual->data.mes, evento_atual->data.ano);

        if (compara_data(novo_evento->data, evento_atual->data) < 0 ||
            (compara_data(novo_evento->data, evento_atual->data) == 0 &&
             compara_hora(novo_evento->inicio, evento_atual->inicio) < 0))
            break;

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Inserindo novo evento aqui.\n");

    if (atual != NULL) {
        Elemento *novo = aloca_elemento(novo_evento, evento->tamInfo);
        if (novo == NULL) {
            printf("Erro: Falha na alocação de memória\n");
            return 0; // Falha na alocação de memória
        }

        novo->proximo = atual;
        if (anterior == NULL) {
            evento->cabeca = novo;
        } else {
            anterior->proximo = novo;
        }
        evento->qtd++;
        return 1; // Successo
    }

    return 0;
}

void mostra_evento(void *info){
    Evento *evento = (Evento *)info;
    printf("Data %d/%d/%d\n", evento->data.dia, evento->data.mes, evento->data.ano);
    printf("Inicio: %d:%d\n", evento->inicio.hora, evento->inicio.minuto);
    printf("Fim: %d:%d\n", evento->fim.hora, evento->fim.minuto);
    printf("Descricao: %s\n", evento->descricao);
    printf("Local: %s\n", evento->local);
}

void mostra_evento_data(Lista *evento, Data data){
   Elemento *atual = evento->cabeca;
   while(atual != NULL){
        Evento *evento_atual = (Evento *)atual->info;
        if(compara_data(data, evento_atual->data) == 0)
            mostra_evento(evento_atual);
        atual = atual->proximo;
    }
}

void mostra_evento_descricao(Lista *evento, const char *descricao) {
    Elemento *atual = evento->cabeca;
    while (atual != NULL) {
        Evento *evento_atual = (Evento *)atual->info;
        if (strcmp(descricao, evento_atual->descricao) == 0) {
            mostra_evento(evento_atual);
        }
        atual = atual->proximo;
    }
}

int remove_evento_data(Lista *evento, Data data) {
    int removidos = 0;
    Elemento *atual = evento->cabeca;
    Elemento *anterior = NULL;
    while (atual != NULL) {
        if (compara_data(data, ((Evento *)atual->info)->data) == 0) {
            Elemento *proximo = atual->proximo;
            free(atual->info);
            free(atual);
            if (anterior == NULL) {
                evento->cabeca = proximo;
            } else {
                anterior->proximo = proximo;
            }
            atual = proximo;
            evento->qtd--;
            removidos++;
        } else {
            anterior = atual;
            atual = atual->proximo;
        }
    }

    return removidos;
}

int remove_evento(Lista *evento, Data data, Hora hora_inicio) {
    Elemento *atual = evento->cabeca;
    Elemento *anterior = NULL;

    while (atual != NULL) {
        Evento *evento_atual = (Evento *)atual->info;

        if (compara_data(data, evento_atual->data) == 0 &&
            compara_hora(hora_inicio, evento_atual->inicio) == 0) {
            // Encontrou o evento, remova-o
            Elemento *proximo = atual->proximo;
            free(atual->info);
            free(atual);

            if (anterior == NULL) {
                // Se é o primeiro elemento
                evento->cabeca = proximo;
            } else {
                anterior->proximo = proximo;
            }

            evento->qtd--;
            return 1; // Evento removido com sucesso
        }

        anterior = atual;
        atual = atual->proximo;
    }

    return 0; // Evento não encontrado
}

void salva_lista(Lista *eventos, char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return;
    }
    Elemento *atual = eventos->cabeca;
    while(atual != NULL){
        Evento *evento_atual =  (Evento *)atual->info;
        fprintf(arquivo, "Data: %d/%d/%d\n", evento_atual->data.dia, evento_atual->data.mes, evento_atual->data.ano);
        fprintf(arquivo, "Inicio: %d:%d\n", evento_atual->inicio.hora, evento_atual->inicio.minuto);
        fprintf(arquivo, "Fim: %d:%d\n", evento_atual->fim.hora, evento_atual->fim.minuto);
        fprintf(arquivo, "Descricao: %s\n", evento_atual->descricao);
        fprintf(arquivo, "Local: %s\n", evento_atual->local);
        fprintf(arquivo, "\n");
        atual = atual->proximo;
    }
    fclose(arquivo);
}
    

