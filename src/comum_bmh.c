#include "comum_bmh.h"

BmhStatus atribuir_dado_byte_a_byte(
    BmhPonteiroQualquer *destino, //Local Que Irá Ser Copiado O Dado 
    BmhPonteiroQualquer copiado, //Dado Que Irá Ser Copiado
    size_t t_dado //Tamanho Do Dado Que Irá Ser Copiado Em Bytes
) //Copia Dado De Um Ponteiro Para O Outro
{
    BmhByte *ptr_destino = NULL, *ptr_copiado = NULL; //Conversão Para Ponteiro Em Bytes

    if (destino == NULL) { //Verifica Se Ponteiro Do Destino Existe
        bmh_log_fracasso("Atribuir Dado Byte a Byte: O Ponteiro Do Destino Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (*destino == NULL) { //Verifica Se Existe Espaço Alocada No Destino
        bmh_log_fracasso("Atribuir Dado Byte a Byte: O Destino Não Há Memória Alocada!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (copiado == NULL) { //Verifica Se Existe Dado No Copiado
        bmh_log_fracasso("Atribuir Dado Byte a Byte: O Dado Que Será Copiado Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    ptr_destino = (BmhByte *)*destino; //Converte Dado
    ptr_copiado = (BmhByte *)copiado; //Converte Dado

    for (size_t i = 0; i < t_dado; i++) {
        ptr_destino[i] = ptr_copiado[i]; //Realiza Passagem Dos Dados
    }

    bmh_log_fracasso("Atribuir Dado Byte a Byte: A Passagem Dos Dados Foi Feito Corretamente!");
    return BMH_OK;
}