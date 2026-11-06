#ifndef COMUM_BMH_H
#define COMUM_BMH_H
#pragma once

//Cores Para Impressão No Terminal
#define BMH_VERMELHO "\033[31m"
#define BMH_VERDE "\033[32m"
#define BMH_AMARELO "\033[33m"
#define BMH_AZUL "\033[34m"
#define BMH_MAGENTA "\033[35m"
#define BMH_CIANO "\033[36m"
#define BMH_BRANCO "\033[37m"
#define BMH_RESET "\033[0m"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#ifdef BMH_DEBUG
    #define bmh_log_sucesso(msg) \
        fprintf(stderr, BMH_AZUL "[BMH DEBUG] " "%s" BMH_RESET "\n", msg)
    #define bmh_log_fracasso(msg) \
        fprintf(stderr, BMH_VERMELHO "[BMH DEBUG] " "%s" BMH_RESET "\n", msg)
    #define bmh_log_avisar(msg) \
        fprintf(stderr, BMH_AMARELO "[BMH DEBUG: AVISO] " "%s" BMH_RESET "\n", msg)
#else
    #define bmh_log_sucesso(msg) ((void)0)
    #define bmh_log_fracasso(msg) ((void)0)
    #define bmh_log_avisar(msg) ((void)0)
#endif

#define bmh_calloc calloc //Apelido Para A Função Calloc
#define bmh_malloc malloc //Apelido Para A Função Malloc
#define bmh_realloc realloc //Apelido Para A Função Realloc
#define bmh_free free //Apelido Para A Função Free

typedef enum BmhStatus {
    BMH_OK = 0, BMH_ERRO_AO_ALOCAR = 1, BMH_ESTRUTURA_EXISTE = 2, 
    BMH_ESTRUTURA_N_EXISTE = 3, BMH_ERRO = 4, BMH_USO_INCORRETO = 5,
    BMH_FLAG = 6
} BmhStatus; //Retorna Status De Operaçõs Realizadas

typedef void * BmhPonteiroQualquer; //Recebe Qualquer Tipo De Ponteiro
typedef const void * BmhPonteiroQualquerCnst; //Recebe Um Ponteiro Constante
typedef unsigned char BmhByte; //Variável Que Possui Tamanho De 1 Byte

typedef int(BmhComparador)(BmhPonteiroQualquerCnst, BmhPonteiroQualquerCnst);

BmhStatus atribuir_dado_byte_a_byte(
    BmhPonteiroQualquer *destino, //Local Que Irá Ser Copiado O Dado 
    BmhPonteiroQualquer copiado, //Dado Que Irá Ser Copiado
    size_t t_dado //Tamanho Do Dado Que Irá Ser Copiado Em Bytes
); //Copia Dado De Um Ponteiro Para O Outro

#endif