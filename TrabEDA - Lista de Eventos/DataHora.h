#ifndef DATAHORA_H
#define DATAHORA_H

typedef struct{
    int hora;
    int minuto;
}Hora;

typedef struct{
    int dia;
    int mes;
    int ano;
}Data;

int valida_data(Data data);
int valida_hora(Hora hora);
int compara_data(Data d1, Data d2);
int compara_hora(Hora h1, Hora h2);

#endif // DATAHORA_H