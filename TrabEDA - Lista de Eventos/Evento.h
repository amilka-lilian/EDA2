#include "DataHora.h"
#include "Lista.h"

typedef struct {
    Data data;
    Hora inicio;
    Hora fim;
    char descricao[50];
    char local[50];
} Evento;

int cadastrar_evento(Lista *evento, Evento *novo_evento);
void mostra_evento(void *info);
void mostra_evento_data(Lista *evento, Data data);
void mostra_evento_descricao(Lista *evento, const char *descricao);
int remove_evento_data(Lista *evento, Data data);
int remove_evento(Lista *evento, Data data, Hora hora_inicio);
void salva_lista(Lista *evento, char *nome_arquivo);
