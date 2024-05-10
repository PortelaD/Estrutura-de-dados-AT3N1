#ifndef HOSPEDES_H
#define HOSPEDES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HOSPEDES 10
#define MAX_NOME 50
#define ARQUIVO "hospedes.txt"

typedef struct {
    char nome[MAX_NOME];
    int quarto;
} Hospede;

extern Hospede hospedes[MAX_HOSPEDES];
extern int total_hospedes;

void carregar_hospedes_do_arquivo();
void salvar_hospedes_no_arquivo();
void criar_arquivo_hospedes();
void inserir_hospede();
void listar_hospedes_por_nome();
void buscar_hospede();
void editar_hospede();
void liberar_quarto();
void mostrar_quartos_vazios();
void exibir_menu();

#endif
