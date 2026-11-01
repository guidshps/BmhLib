#include "bmh_arvore.h"

BmhStatus criar_bmh_arvore(
    BmhArvore **ptr_arvore, //Ponteiro Para Árvore Destino
    size_t t_dados //Tamanho Dos Dados Que Os Nós Irão Guardar
) //Cria Árvore Que Possui Dados Com Tamanho De Dados Especificado
{
    if (ptr_arvore == NULL) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Criar Bmh Árvore: Este Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    } 
    
    else if (*ptr_arvore == NULL) { //Verifica Se Já Existe Árvore
        bmh_log_fracasso("Criar Bmh Árvore: Uma Árvore Já Existe!");
        return BMH_ESTRUTURA_EXISTE;
    }

    (*ptr_arvore) = calloc(1, sizeof(BmhArvore)); //Tenta Criar Árvore

    if (*ptr_arvore == NULL) { //Verifica Se Conseguiu Alocar Memória
        bmh_log_fracasso("Criar Bmh Árvore: Erro Ao Alocar Memória!");
        return BMH_ERRO_AO_ALOCAR;
    }

    return BMH_OK;
}