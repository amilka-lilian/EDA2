#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DataHora.h"

int valida_data(Data data){
    return data.dia >= 1 && data.dia <=31 && data.mes >= 1 && data.mes <=12 &&data.ano > 0;
}

int valida_hora(Hora hora){
    return hora.hora >= 0 && hora.hora < 24 && hora.minuto >= 0 && hora.minuto < 60;
}

int compara_data(Data d1, Data d2){
    if (d1.ano < d2.ano) return -1;
    if (d1.ano > d2.ano) return 1;
    if (d1.mes < d2.mes) return -1;
    if (d1.mes > d2.mes) return 1;
    if (d1.dia < d2.dia) return -1;
    if (d1.dia > d2.dia) return 1;
    return 0; // as datas são iguais
}

int compara_hora(Hora h1, Hora h2){
    if (h1.hora < h2.hora) return -1;
    if (h1.hora > h2.hora) return 1;
    if (h1.minuto < h2.minuto) return -1;
    if (h1.minuto > h2.minuto) return 1;
    return 0; // as horas são iguais
}
