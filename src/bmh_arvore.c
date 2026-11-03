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

    (*ptr_arvore) = bmh_calloc(1, sizeof(BmhArvore)); //Tenta Criar Árvore

    if (*ptr_arvore == NULL) { //Verifica Se Conseguiu Alocar Memória
        bmh_log_fracasso("Criar Bmh Árvore: Erro Ao Alocar Memória!");
        return BMH_ERRO_AO_ALOCAR;
    }

    bmh_log_sucesso("Criar Bmh Árvore: Sucesso Ao Criar A Árvore!");
    return BMH_OK;
}

static BmhNoArvore *criar_bmh_no_arvore(
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Copiado Para Nó
    BmhNoArvore *filho_esq, //Filho Que Será Atribuido à Esquerda
    BmhNoArvore *filho_dir, //Filho Que Será Atribuido à Direita
    size_t t_dado //Tamanho Do Dado Que Será Copiado
) //Cria Nó Para Árvore Binária
{
    BmhNoArvore *no_criado = NULL; //Nó Que Irá Ser Criado

    if (dado == NULL) { //Verifica Se Dado Existe
        bmh_log_fracasso("Criar Bmh Nó Árvore: Este Dado Não Existe!");
        return NULL; //Retorna NULL, Pois Não Conseguiu Criar Nó
    }

    no_criado = bmh_calloc(1, sizeof(BmhNoArvore)); //Tenta Criar Dado

    if (no_criado == NULL) { //Verifica Se Conseguiu Alocar Memória
        bmh_log_fracasso("Criar Bmh Nó Árvore: Erro Ao Criar Nó!");
        return NULL; //Retorna NULL, Pois Não Conseguiu Criar Nó
    }

    no_criado->dado = bmh_calloc(1, t_dado); //Tenta Criar Espaço Para Dado

    if (no_criado->dado == NULL) { //Verifica Se Conseguiu Alocar Espaço
        bmh_log_fracasso("Criar Bmh Nó Árvore: Erro Ao Criar Espaço Para Dado!");
        free(no_criado); //Limpa Nó Já Que Não Conseguiu Criar
        return NULL; //Retorna NULL, Pois Não Conseguiu Criar Nó
    }

    atribuir_dado_byte_a_byte(&(no_criado->dado), dado, t_dado); //Passa Dado
    no_criado->filho_esq = filho_esq; //Atribui Filho Esquerdo
    no_criado->filho_dir = filho_dir; //Atribuir Filho Direito

    no_criado->qtd_filhos = 0; //Define Para 0, Para Ter Certeza Que Não Possui Filhos
    if (filho_esq != NULL) no_criado->qtd_filhos++; //Aumenta A Referência De Filhos
    if (filho_dir != NULL) no_criado->qtd_filhos++; //Aumenta A Referência De Filhos

    return no_criado; //Retorna Nó Que Foi Criado
}

BmhStatus insercao_ordedana_balanceada_bmh_arvore(
    BmhArvore **ptr_arvore, //Ponteiro Para Árvore Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Armazenado
    BmhComparador metodo_comparacao //Método Para Comparar Os Dados
) //Insere Dado De Forma Que A Árvore Fique Balanceada
{
    if (ptr_arvore == NULL) { //Verifica Se Ponteiro Passado Existe
        bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Este Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (*ptr_arvore == NULL) { //Verifica Se Árvore Não Existe
        bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Esta Árvore Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (dado == NULL) { //Verifica Se Dado Existe
        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Este Dado Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (metodo_comparacao == NULL) { //Verifica Se Existe Método De Comparação
        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Este Metódo De Comparação Não Existe!");
        return BMH_USO_INCORRETO;
    }

    if ((*ptr_arvore)->no_raiz == NULL && (*ptr_arvore)->qtd_nos == 0) { /*Verifica Se Nenhum
    Nó Foi Criado*/
        (*ptr_arvore)->no_raiz = criar_bmh_no_arvore(dado, NULL, NULL,
        (*ptr_arvore)->t_dados); //Tenta Criar Nó

        if ((*ptr_arvore)->no_raiz == NULL) { //Verifica Se Conseguiu Criar Nó
            bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Erro Ao Criar Nó");
            return BMH_ERRO_AO_ALOCAR;
        }
    }

    bmh_log_sucesso("Inserção Ordenada Balanceada Bmh Árvore: Sucesso Ao Inserir Dado!");
    return BMH_OK;
}