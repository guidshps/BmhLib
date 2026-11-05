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

static BmhStatus criar_no_raiz_bmh_arvore(
    BmhArvore **ptr_arvore, //Ponteiro Para Árvore Destino
    BmhPonteiroQualquer dado //Dado Que Será Atribuido
) //Cria Nó Raiz Da Árvore 
{
    if (!ptr_arvore) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Criar Nó Raiz Bmh Árvore: Este Ponteiro Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_arvore)) { //Verifica Se Arrau Existe
        bmh_log_fracasso("Criar Nó Raiz Bmh Árvore: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }

    (*ptr_arvore)->no_raiz = criar_bmh_no_arvore(dado, NULL, NULL, (*ptr_arvore)->t_dados); //Tenta Passar Dado

    if (!(*ptr_arvore)->no_raiz) { //Verifica Se Conseguiu Alocar Memória
        bmh_log_fracasso("Criar Nó Raiz Bmh Árvore: Erro Ao Alocar Memória");
        return BMH_ERRO_AO_ALOCAR;
    }

    bmh_log_sucesso("Criar Nó Raiz Bmh Árvore: Sucesso Ao Criar Nó Raiz");
    return BMH_OK;
}

static BmhStatus balancear_no(
    BmhNoArvore **ptr_no_base, //Ponteiro Que Aponta Para O Nó Base Que Será Balanceada
    BmhComparador metodo_comparacao, //Método Para Comoarar Os Dados
) //Balanceia Nó, Caso Este Possua Dois Elementos Seguidos
{
    BmhNoArvore *prox_no = NULL, *prox_prox_no = NULL; //Nós De Referência A Base

    if (!ptr_no_base) { //Verifica Se Ponteiro É Válido
        bmh_log_fracasso("Balancear Nó: Este Ponteiro Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_no_base)) { //Verifica Se Existe Nó Base
        bmh_log_fracasso("Balancear Nó: Este Nó Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!metodo_comparacao) { //Verifica Se Método De Comparação Existe
        bmh_log_fracasso("Balancear Nó: Não Existe Método De Comparação");
        return BMH_USO_INCORRETO;
    }

    if ((*ptr_no_base)->filho_dir != NULL) 
        prox_no = (*ptr_no_base)->filho_dir;
    else if ((*ptr_no_base)->filho_esq != NULL)
        prox_no = (*ptr_no_base)->filho_esq;
    else {
        bmh_log_fracasso("Balancear Nó: Erro Com Os Nós!");
        return BMH_ERRO;
    }

    if (prox_no->filho_dir != NULL) 
        prox_prox_no = prox_no->filho_dir;
    else if (prox_no->filho_esq != NULL)
        prox_prox_no = prox_no->filho_esq;
    else {
        bmh_log_fracasso("Balancear Nó: Erro Com Os Nós!");
        return BMH_ERRO;
    }
}

static BmhStatus metodo_insercao_ordenada_balanceada(
    BmhArvore **ptr_arvore, //Ponteiro Para Árvore Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Armazenado
    BmhComparador metodo_comparacao //Método Para Comparar Os Dados
) //Compara Dados 
{
    BmhNoArvore *no_atual = NULL; //Nó Usado Para Referência Ao Navegar Na Árvore
    BmhNoArvore *prox_no = NULL; //Nó Que É O Próximo Do Nó Atual
    BmhNoArvore *no_criado = NULL; //Nó Que Foi Criado

    if (!ptr_arvore) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Este Ponteiro Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_arvore)) { //Verifica Se Árvore Existe
        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Esta Árvore Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!metodo_comparacao) {
        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Este Método De Comparação Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!dado) {
        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Este Dado Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_arvore)->no_raiz) { //Verifica Se Nó Raiz Existe
        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Esta Árvore Não Existe!");
        return BMH_USO_INCORRETO;
    }

    no_atual = (*ptr_arvore)->no_raiz; //Adota Referência Como Atual

    while (true) {
        if (metodo_comparacao(no_atual->dado, dado) < 0) { //Se Dado É Maior, Então
            if (no_atual->qtd_filhos == 0) {
                no_atual->filho_dir = criar_bmh_no_arvore(dado, NULL, NULL, (*ptr_arvore)->t_dados); //Tenta Criar Nó
                if (no_atual->filho_dir == NULL) { //Verifica Se Consegui Alocar Memória
                    bmh_log_fracasso("Método Inserção Ordenad Balanceada: Erro Ao Alocar Memória");
                    return BMH_ERRO_AO_ALOCAR; 
                }
                no_atual->qtd_filhos++; //Conta Um Filho Para Nó
                break;
            }

            else if (no_atual->qtd_filhos == 1) {
                if (no_atual->filho_dir == NULL) { //Se Nó Direito Não Existe
                    no_atual->filho_dir = criar_bmh_no_arvore(dado, NULL, NULL, (*ptr_arvore)->t_dados); //Tenta Criar Nó
                    if (no_atual->filho_dir == NULL) { //Verifica Se Consegui Alocar Memória
                        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Erro Ao Alocar Memória");
                        return BMH_ERRO_AO_ALOCAR; 
                    }
                    no_atual->qtd_filhos++; //Conta Um Filho Para Nó
                    break;
                }

                else {
                    prox_no = no_atual->filho_dir; //Adota Referência Do Próximo
                    no_criado = criar_bmh_no_arvore(dado, NULL, NULL, (*ptr_arvore)->t_dados);

                    if (no_criado == NULL) { //Verifica Se Conseguiu Criar Nó
                        bmh_log_fracasso("Método Inserção Ordenada Balanceada: Erro Ao Alocar Memória!");
                        return BMH_ERRO_AO_ALOCAR;
                    }

                    if (metodo_comparacao(prox_no->dado, no_criado->dado) < 0) 
                        prox_no->filho_dir = no_criado;
                    else 
                        prox_no->filho_esq = no_criado; 

                    (*ptr_arvore)->qtd_nos++; //Incrementa Nó, Já Que Adicionou
                }
            }

            else {
                no_atual = no_atual->filho_dir; //Atribui Nova Referência
            }
        }

        else { //Se Dado É Menor, Então
            if (no_atual->qtd_filhos == 0) {
                no_atual->filho_esq = criar_bmh_no_arvore(dado, NULL, NULL, (*ptr_arvore)->t_dados); //Tenta Criar Nó
                if (no_atual->filho_esq == NULL) { //Verifica Se Consegui Alocar Memória
                    bmh_log_fracasso("Método Inserção Ordenada Balanceada: Erro Ao Alocar Memória");
                    return BMH_ERRO_AO_ALOCAR; 
                }
                no_atual->qtd_filhos++; //Conta Um Filho Para Nó
                break;
            }

            else if (no_atual->qtd_filhos == 1) {
            }

            else {
                no_atual = no_atual->filho_esq;
            }
        }
    }

    bmh_log_sucesso("Método Inserção Ordenada: Sucesso Ao Inserir Dado!");
    return BMH_OK;
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
        bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Este Dado Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (metodo_comparacao == NULL) { //Verifica Se Existe Método De Comparação
        bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Este Metódo De Comparação Não Existe!");
        return BMH_USO_INCORRETO;
    }

    if ((*ptr_arvore)->no_raiz == NULL && (*ptr_arvore)->qtd_nos == 0) { /*Verifica Se Nenhum 
    Nó Foi Criado Ainda*/
        if (criar_no_raiz_bmh_arvore(ptr_arvore, dado) != BMH_OK) { //Verifica Se Operação Ocorreu Corretamente
            bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Erro Ao Criar Nó Raiz");
        }

        (*ptr_arvore)->qtd_nos++; //Conta Um Nó Criado
    }
    
    else { //Caso Já Tenha Criado

    }

    bmh_log_sucesso("Inserção Ordenada Balanceada Bmh Árvore: Sucesso Ao Inserir Dado!");
    return BMH_OK;
}