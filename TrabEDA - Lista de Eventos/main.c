#include "Evento.h"
#include "Lista.h"
#include "DataHora.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (){
   
    Evento novo_evento;
    Data data;
    char descricao[50];
    char nome_arquivo[50];

    // Inicialize a lista de eventos
    Lista eventos;
    inicializa_lista(&eventos, sizeof(Evento));

    // Loop do menu
     int opcao;
    do {
        printf("Menu:\n");
    	printf("--------------------------------\n");
        printf("1. Cadastrar evento:\n");
        printf("2. Mostrar evento por data:\n");
        printf("3. Mostrar evento por descricao:\n");
        printf("4. Mostrar todos os eventos cadastrados:\n");
        printf("5. Remover eventos por data:\n");
        printf("6. Remover eventos por data e hora:\n");
        printf("7. Salvar lista:\n");
        printf("0. Sair:\n");
        printf("--------------------------------\n");
        printf("Escolha uma opcao:");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                // Solicitar dados ao usuário para cadastrar evento
                printf("Informe a data do evento (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &novo_evento.data.dia, &novo_evento.data.mes, &novo_evento.data.ano);

                printf("Informe a hora de inicio do evento (HH:MM): ");
                scanf("%d:%d", &novo_evento.inicio.hora, &novo_evento.inicio.minuto);

                printf("Informe a hora de termino do evento (HH:MM): ");
                scanf("%d:%d", &novo_evento.fim.hora, &novo_evento.fim.minuto);

                printf("Informe a descricao do evento: ");
                scanf(" %[^\n]", novo_evento.descricao);  // [^\n] para ler espacos em branco

                printf("Informe o local do evento: ");
                scanf(" %[^\n]", novo_evento.local);  // [^\n] para ler espacos em branco

                int resultado = cadastrar_evento(&eventos, &novo_evento);
                if (resultado) {
                    printf("Evento cadastrado com sucesso!\n");
                } else {
                    printf("Erro ao cadastrar o evento.\n");
                }
        		printf("\n");
                break;
            }
            case 2: {
                // Solicitar dados ao usuario para mostrar evento por data
                printf("Informe a data para mostrar eventos (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);

                // Chamar a funcao mostra_evento_data
                mostra_evento_data(&eventos, data);
                printf("\n");
                break;
            }
           case 3: {

                printf("Informe a descricao para mostrar eventos: ");
                scanf(" %[^\n]", descricao);

                mostra_evento_descricao(&eventos, descricao);
                printf("\n");
                break;
            }
             case 4: {
                mostra_lista(eventos, mostra_evento);
                break;
            }
            case 5: {
                // Solicitar dados ao usuario para remover eventos por data
                printf("Informe a data para remover eventos (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);

                // Chamar a funcao remove_evento_data
                remove_evento_data(&eventos, data);
                break;
            }
            case 6: {
                // Solicitar dados ao usuario para remover um evento
                printf("Informe a data para remover um evento (DD/MM/AAAA): ");
                scanf("%d/%d/%d", &data.dia, &data.mes, &data.ano);

                printf("Informe a hora de inicio para remover um evento (HH:MM): ");
                scanf("%d:%d", &novo_evento.inicio.hora, &novo_evento.inicio.minuto);

                // Chamar a função remove_evento
                int resultado = remove_evento(&eventos, data, novo_evento.inicio);

                if (resultado) {
                    printf("Evento removido com sucesso!\n");
                } else {
                printf("Evento nao encontrado.\n");
                }
                break;
            }
            case 7: {
              
                salva_lista(&eventos, "Lista_Evento.txt");
                printf("Lista Salvo com sucesso.\n");
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    limpa_lista(&eventos);

    return 0;
}
