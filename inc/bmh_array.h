#ifndef BMH_ARRAY_H
#define BMH_ARRAY_H
#pragma once

#include "comum_bmh.h"

#define TAMANHO_INICIAL_BMH_ARRAY 8 //Indica Tamanho Inicial Que Array Irá Possuir
#define FATOR_CRESCIMENTO_BMH_ARRAY 0.5 /*Valor Que Indica Quantos % Vai Crescer 
O Array Ao Aumentar O Array Dos Dados, Ou Seja, 
TAMANHO_ATUAL * (1 + "FATOR_CRESCIMENTO_BMH_ARRAY") */

typedef struct BmhArray {
    BmhPonteiroQualquer dados; //Array Dos Dados
    size_t t_dados; //Tamanho Que Tipo Dado Possui
    size_t q_dados; //Quantidade De Dados
    size_t t_atual; //Tamanho Atual Do Array
} BmhArray; //Estrutura Que Armazena Lista Com Dados Do Mesmo Tipo

//Definição dos Métodos do Bmh Array

BmhStatus criar_bmh_array(
    BmhArray **ptr_array, //Ponteiro Para O Array Destino
    size_t t_dados //Tamanho dos Dados Armazenados No Array
); //Cria Bmh Array 

BmhStatus destruir_bmh_array(
    BmhArray **ptr_array //Ponteiro Para O Array Destino
); //Destroí Bmh Array

BmhStatus adicionar_dado_bmh_array(
    BmhArray **ptr_array, //Ponteiro Para O Array Destino
    BmhPonteiroQualquer dado //Dado Que Irá Ser Adicionado No Array
); //Atribui Dado Para O Array (Último Endereço)

BmhPonteiroQualquer acessar_endereco_bmh_array(
    BmhArray *array, //Array Destino
    size_t indice //Indice Do Dado Que Irá Ser Devolvido
); //Acessa Endereço Enviado Pelo Usuário E Devolve Ele

BmhPonteiroQualquer busca_linear_bmh_array(
    BmhArray *array, //Array Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Buscado No Array
    BmhComparador metodo_comparacao //Método Que Os Dados Serão Comparados
); //Busca Linearmente Por Dado (Devolve Endereço Do Dado)

BmhPonteiroQualquer busca_binaria_bmh_array(
    BmhArray *array, //Array Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Buscado No Array
    BmhComparador metodo_comparacao //Método Que Os Dados Serão Comparados
); //Busca Binareamente Por Dado (Devolve Endereço Do Dado)

BmhStatus ordenacao_rapida_bmh_array(
    BmhArray **ptr_array, //Array Destino
    BmhComparador metodo_comparacao //Método Que Os Dados Serão Comparados
); //Realiza A Quick Sort Na Lista Com O Método Que O Usúario Destinou Para Usar

BmhStatus deletar_dado_bmh_array(
    BmhArray **ptr_array, //Array Destino
    size_t indice //Indice Do Dado Que Será Deletado
); //Deleta Dado Indicado Do Array E Corrige As Posições Dos Dados

#endif