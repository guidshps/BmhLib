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
    
    else if (*ptr_arvore != NULL) { //Verifica Se Já Existe Árvore
        bmh_log_fracasso("Criar Bmh Árvore: Uma Árvore Já Existe!");
        return BMH_ESTRUTURA_EXISTE;
    }

    (*ptr_arvore) = bmh_calloc(1, sizeof(BmhArvore)); //Tenta Criar Árvore

    if (*ptr_arvore == NULL) { //Verifica Se Conseguiu Alocar Memória
        bmh_log_fracasso("Criar Bmh Árvore: Erro Ao Alocar Memória!");
        return BMH_ERRO_AO_ALOCAR;
    }

    (*ptr_arvore)->t_dados = t_dados; //Atribui Tamanho Dos Dados

    bmh_log_sucesso("Criar Bmh Árvore: Sucesso Ao Criar A Árvore!");
    return BMH_OK;
}

void destruir_sub_arvore(
    BmhNoArvore *no //Nó Base Que Será Usado
) //Destói Sub-Árvore Da Árvore 
{
    if (!no) return;


    //Verifica Se Filhos Existem Para Destruílos
    if (no->filho_esq != NULL) destruir_sub_arvore(no->filho_esq);
    if (no->filho_dir != NULL) destruir_sub_arvore(no->filho_dir);

    free(no->dado); //Libera Dado
    free(no); //Libera Nó

    return;
}

BmhStatus destruir_bmh_arvore(
    BmhArvore **ptr_arvore //Ponteiro Para Árvore Destino
) //Destrói Árvore Enviada Pelo Usuário
{
    if(!ptr_arvore) { //Verifica Se Ponteiro É Válido
        bmh_log_fracasso("Destruir Bmh Árvore: Este Ponteiro Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_arvore)) { //Verifica Se Existe Árvore
        bmh_log_fracasso("Destruir Bmh Árvore: Esta Árvore Não Existe!");
        return BMH_USO_INCORRETO;
    }

    destruir_sub_arvore((*ptr_arvore)->no_raiz); //Destrói Árvore Em Si
    bmh_free(*ptr_arvore); //Destrói Estruturas De Dados Da Árvore
    (*ptr_arvore) = NULL; //Recebe Como Que Árvore Não Existe 

    bmh_log_sucesso("Destruir Bmh Árvore: Sucesso Ao Destruir Árvore!");
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
    BmhComparador metodo_comparacao //Método Para Comoarar Os Dados
) //Balanceia Nó, Caso Este Possua Dois Elementos Seguidos
{
    BmhNoArvore *prox_no = NULL, *prox_prox_no = NULL; //Nós De Referência A Base
    BmhPonteiroQualquer dado_menor = NULL, dado_medio = NULL, dado_maior = NULL; //Variáveis Auxiliares
    BmhPonteiroQualquer lista_dados[3] = {}; //Lista Com Os Dados Para Ordenar Eles
    int ref = 0; //Referência De Qual Dado É O Maior

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

    lista_dados[0] = (*ptr_no_base)->dado;
    lista_dados[1] = prox_no->dado;
    lista_dados[2] = prox_prox_no->dado;

    dado_maior = lista_dados[0]; //Define Referência

    for (int i = 0; i < 3; i++) {
        if (metodo_comparacao(dado_maior, lista_dados[i]) < 0) { //Compara Dados
            dado_maior = lista_dados[i]; //Novo Dado Maior
            ref = i; //Adota Nova Referência
        }
    }

    //Obtenção Dos Valores Médios e Menor
    if (ref == 0) {
        if (metodo_comparacao(lista_dados[1], lista_dados[2]) > 0) {
            dado_medio = lista_dados[1]; 
            dado_menor = lista_dados[2];
        }

        else {
            dado_medio = lista_dados[2]; 
            dado_menor = lista_dados[1];
        }
    }

    else if (ref == 1) {
        if (metodo_comparacao(lista_dados[0], lista_dados[2]) > 0) {
            dado_medio = lista_dados[0]; 
            dado_menor = lista_dados[2];
        }

        else {
            dado_medio = lista_dados[2]; 
            dado_menor = lista_dados[0];
        }
    }

    else if (ref == 2) {
        if (metodo_comparacao(lista_dados[0], lista_dados[1]) > 0) {
            dado_medio = lista_dados[0]; 
            dado_menor = lista_dados[1];
        }

        else {
            dado_medio = lista_dados[1]; 
            dado_menor = lista_dados[0];
        }
    }

    prox_no->filho_esq = prox_no->filho_dir = NULL; //Limpa Filhos Do Próximo Nó
    prox_prox_no->filho_esq = prox_prox_no->filho_dir = NULL; //Limpa Filhos Do Nó Filho Do Próximo Nó
    prox_no->qtd_filhos = 0; //Zera Quantidade De Filhos
    prox_prox_no->qtd_filhos = 0; //Zera Quantidade De Filhos
    
    (*ptr_no_base)->dado = dado_medio; //Recebe Dado Médio
    prox_no->dado = dado_menor; //Recebe Menor Dado
    prox_prox_no->dado = dado_maior; //Recebe Dado Maior

    //Atribuição De Nova Referência
    (*ptr_no_base)->filho_esq = prox_no;
    (*ptr_no_base)->filho_dir = prox_prox_no;
    (*ptr_no_base)->qtd_filhos = 2; //Atualiza Qtd De Filhos

    bmh_log_sucesso("Balancear Nó: Sucesso Ao Balancear Nó!");
    return BMH_OK;
}

static BmhStatus criar_no_filho_para_no(
    BmhNoArvore **ptr_no, //Ponteiro Para Nó Base
    BmhPonteiroQualquer dado, //Dado Que Será Atribuido No Novo Ponteiro
    size_t t_dado, //Tamanho Do Dado Que Irá Ser Atribuido
    BmhComparador metodo_comparacao //Método De Comparação Dos Dados
) //Cria Nó Filho Para Um Nó Caso Este Não Possua
{
    BmhNoArvore *no_criado = NULL; //Nó Que Será Criado

    if (!ptr_no) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Criar Nós Filhos Para Nó: Este Ponteiro Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_no)) { //Verifica Se Existe Raiz
        bmh_log_fracasso("Criar Nós Filhos Para Nó: A Raiz Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!dado) { //Verifica Se Dado Existe
        bmh_log_fracasso("Criar Nós Filhos Para Nó: Este Dado Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!metodo_comparacao) { //Verifica Se Existe Método De Comparação
        bmh_log_fracasso("Criar Nós Filhos Para Nó: Este Método de Comparação É Inválido!");
        return BMH_USO_INCORRETO;
    }

    else if (t_dado == 0) {
        bmh_log_avisar("Criar Nós Filhos Para Nó: O Tamanho Do Dado Passado Foi 0!");
        return BMH_USO_INCORRETO;
    }

    no_criado = criar_bmh_no_arvore(dado, NULL, NULL, t_dado);

    if (!no_criado) { //Verifica Se Conseguiu Criar Nó
        bmh_log_fracasso("Criar Nós Filhos Para Nó: Erro Ao Criar Novo Nó!");
        return BMH_ERRO_AO_ALOCAR;
    }

    if (metodo_comparacao(dado, (*ptr_no)->dado) > 0 && (*ptr_no)->filho_dir == NULL) {
    //Caso Dado Seja Maior E Não Exista Filho Na Direita
        (*ptr_no)->filho_dir = no_criado; //Nó Filho Direito Recebe Nó Criado
        (*ptr_no)->qtd_filhos++; //Conta Filho Já Que Adicionou Nó
    }
    else if (metodo_comparacao(dado, (*ptr_no)->dado) < 0 && (*ptr_no)->filho_esq == NULL) {
    //Caso Dado Seja Menor E Não Exista Filho Na Esquerda
        (*ptr_no)->filho_esq = no_criado; //Nó Filho Esquerdo Recebe Nó Criado
        (*ptr_no)->qtd_filhos++; //Conta Filho Já Que Adicionou Nó
    }
    else { //Caso Esteja Tentando Sobreescrever Ponteiro
        bmh_log_avisar("Criar Nós Filhos Para Nó: Tentativa De Sobreescrever Filho!");
        return BMH_ERRO;
    }

    bmh_log_sucesso("Criar Nós Filhos Para Nó: Sucesso Ao Criar Nó Filho");
    return BMH_OK;
}

static BmhStatus caso_no_possua_1_filho_insercao_ordenada (
    BmhNoArvore **ptr_no, //Ponteiro Para Nó Base
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Comparado Ou Atribuido
    size_t t_dado, //Tamanho Do Dado Que Irá Ser Atribuido
    BmhComparador metodo_comparacao //Método De Comparação Dos Dados
) //Caso Que Nó Possui Apenas 1 Filho Na Inserção Ordenada 
{
    BmhNoArvore *prox_no = NULL; //Ponteiro Para Próximo Nó Em Relação À Base

    if (!ptr_no) { //Verifica Se Ponteiro É Válido
        bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Ponteiro Passado É Inválido!");
        return BMH_USO_INCORRETO;
    }

    else if (!(*ptr_no)) { //Verifica Se Existe Nó Passado
        bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Este Nó Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!dado) { //Verifica Se Dado Existe
        bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Este Dado Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (!metodo_comparacao) { //Verifica Se Existe Método De Comparação
        bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Este Método De Comparação Não Existe!");
        return BMH_USO_INCORRETO;
    }

    if ((*ptr_no)->filho_dir != NULL) { //Caso Filho Da Direita Exista
        prox_no = (*ptr_no)->filho_dir; //Recebe Filho Da Direita

        if (metodo_comparacao(dado, (*ptr_no)->dado) <= 0) { /*Caso Dado Seja Menor Ou Igual E 
        Exista Apenas Filho Na Direita*/
            if (criar_no_filho_para_no(ptr_no, dado, t_dado, metodo_comparacao) == BMH_OK) {
                bmh_log_sucesso("Caso Nó Possua 1 Filho Inserção Ordenada: Sucesso Ao Inserir Novo Filho!");
                return BMH_FLAG; 
            }

            else {
                bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Fracasso Ao Inserir Novo Filho!");
                return BMH_ERRO;
            }
        }

        else { // Caso Dado Deve Ser Inserido Na Mesma Direção Deve-se Balancear
            if (criar_no_filho_para_no(&prox_no, dado, t_dado, metodo_comparacao) == BMH_OK) {
                if (balancear_no(ptr_no, metodo_comparacao) == BMH_OK) { //Caso Consiga Balancear Nó
                    bmh_log_sucesso("Caso Nó Possua 1 Filho Inserção Ordenada: Sucesso Ao Balancear!");
                    return BMH_FLAG; //Retorna Flag
                }

                else {
                    if (prox_no->filho_dir != NULL) {
                        free(prox_no->filho_dir); //Libera Já Que Não Conseguiu Balancear
                        prox_no->filho_dir = NULL; //Indica Que Está Vázio
                    }
                    else if (prox_no->filho_esq != NULL) {
                        free(prox_no->filho_esq); //Libera Já Que Não Conseguiu Balancear
                        prox_no->filho_esq = NULL; //Indica Que Está Vázio
                    }
                    bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Fracasso Ao Balancear!");
                    return BMH_ERRO;
                }
            }

            else { //Caso Não Consiga Criar Nenhum Nó Filho Para O Próximo Nó
                bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Erro Criar Nó Filho! (Caso Que Dados Estão Em Série)");
                return BMH_ERRO;
            }
        }
    }

    else if ((*ptr_no)->filho_esq != NULL) { //Caso Filho Da Esquerda Exista
        prox_no = (*ptr_no)->filho_esq; //Recebe Filho Da Direita

        if (metodo_comparacao(dado, (*ptr_no)->dado) > 0) { /*Caso Dado Seja Maior E 
        Exista Apenas Filho Na Esquerda*/
            if (criar_no_filho_para_no(ptr_no, dado, t_dado, metodo_comparacao) == BMH_OK) {
                bmh_log_sucesso("Caso Nó Possua 1 Filho Inserção Ordenada: Sucesso Ao Inserir Novo Filho!");
                return BMH_FLAG; 
            }
        }

        else { // Caso Dado Deve Ser Inserido Na Mesma Direção Deve-se Balancear
            if (criar_no_filho_para_no(&prox_no, dado, t_dado, metodo_comparacao) == BMH_OK) {
                if (balancear_no(ptr_no, metodo_comparacao) == BMH_OK) { //Caso Consiga Balancear Nó
                    bmh_log_sucesso("Caso Nó Possua 1 Filho Inserção Ordenada: Sucesso Ao Balancear!");
                    return BMH_FLAG; //Retorna Flag
                }

                else {
                    if (prox_no->filho_dir != NULL) {
                        free(prox_no->filho_dir); //Libera Já Que Não Conseguiu Balancear
                        prox_no->filho_dir = NULL; //Indica Que Está Vázio
                    }
                    else if (prox_no->filho_esq != NULL) {
                        free(prox_no->filho_esq); //Libera Já Que Não Conseguiu Balancear
                        prox_no->filho_esq = NULL; //Indica Que Está Vázio
                    }
                    bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Fracasso Ao Balancear!");
                    return BMH_ERRO;
                }
            }

            else { //Caso Não Consiga Criar Nenhum Nó Filho Para O Próximo Nó
                bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Erro Criar Nó Filho! (Caso Que Dados Estão Em Série)");
                return BMH_ERRO;
            }
        }
    }

    else { //Caso Nenhum Nó Filho Exista
        bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Comportamento Inesperado!");
        return BMH_ERRO;
    }

    bmh_log_fracasso("Caso Nó Possua 1 Filho Inserção Ordenada: Comportamento Inesperado!");
    return BMH_ERRO;
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
        if (no_atual->qtd_filhos == 0) { //Caso Nó Não Possua Filhos
            if (criar_no_filho_para_no(&no_atual, dado, (*ptr_arvore)->t_dados,
            metodo_comparacao) != BMH_OK) { //Tenta Criar Nó Filho E Verifica
                bmh_log_fracasso("Método Inserção Ordenada Balanceada: Erro Em Criar Nó Filho Para Nó!");
                return BMH_ERRO; //Retorna Erro
            }
            (*ptr_arvore)->qtd_nos++; //Incrementa Já Que Conseguiu Adicionar
            break; //Sai Do Loop Caso Consiga Inserir
        }

        else if (no_atual->qtd_filhos == 1) { //Caso Possua Um Filho
            if (caso_no_possua_1_filho_insercao_ordenada(&no_atual,
            dado, (*ptr_arvore)->t_dados, metodo_comparacao) == BMH_FLAG) {
                break; //Sai Do Loop Caso Consiga Inserir
            }

            else {
                bmh_log_fracasso("Método Inserção Ordenada Balanceada: Erro No Caso Nó Atual Possua 1 Filho!");
                return BMH_ERRO;
            }
        }

        else if (no_atual->qtd_filhos == 2) { //Caso Nó Já Esteja Balanceado
            if (metodo_comparacao(dado, no_atual) > 0) //Caso Dado Seja Maior Que Dado Do Nó Atual
                no_atual = no_atual->filho_dir;
            else //Caso Dado Seja Menor Que Dado Do Nó Atual
                no_atual = no_atual->filho_esq; 
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
            return BMH_ERRO;
        }

        bmh_log_sucesso("Inserção Ordenada Balanceada Bmh Árvore: Sucesso Ao Criar Nó Na Raiz!");
        (*ptr_arvore)->qtd_nos++; //Conta Um Nó Criado
    }
    
    else { //Caso Já Tenha Criado
        if (metodo_insercao_ordenada_balanceada(ptr_arvore, dado, metodo_comparacao) != BMH_OK) {
            bmh_log_fracasso("Inserção Ordenada Balanceada Bmh Árvore: Erro Ao Inserir Dado!");
            return BMH_ERRO;
        }

        bmh_log_sucesso("Inserção Ordenada Balanceada Bmh Árvore: Sucesso Ao Inserir Dado Fora Da Raiz!");
        (*ptr_arvore)->qtd_nos++; //Conta Um Nó Criado
    }

    bmh_log_sucesso("Inserção Ordenada Balanceada Bmh Árvore: Sucesso Ao Inserir Dado!");
    return BMH_OK;
}

BmhStatus insercao_ordenada_bmh_arvore(
    BmhArvore **ptr_arvore, //Ponteiro Para Árvore Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Armazenado
    BmhComparador metodo_comparacao //Método Para Comparar Os Dado
) //Insere Dado De Forma Ordenada, Mas Não Balanceia Árvore
{
    BmhNoArvore *no_atual = NULL; //Variável Auxiliar Para Navegar Na Árore

    if (!ptr_arvore) { //Verifica Se Ponteiro É Válido
        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Este Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (!(*ptr_arvore)) { //Verifica Se Existe Árvore
        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Esta Árvore Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (!dado) { //Verifica Se Dado Existe
        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Este Dado Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (!metodo_comparacao) { //Verifica Se Método De Comaparação É Válido
        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Este Método De Comparação Não É Válido!");
        return BMH_ESTRUTURA_N_EXISTE;
    }
    
    //Métodos De Inserção Efetivos Realmente

    //Caso Árvore Não Possua Raiz E Nenhum Nó
    if ((*ptr_arvore)->no_raiz == NULL && (*ptr_arvore)->qtd_nos == 0) {
        //Tenta Criar Nó Para Dado
        (*ptr_arvore)->no_raiz = criar_bmh_no_arvore(dado, NULL, NULL, (*ptr_arvore)->t_dados);

        if ((*ptr_arvore)->no_raiz != NULL) { //Verifica Se Conseguiu Criar Nó
            bmh_log_sucesso("Inserção Ordenada Bmh Árvore: Sucesso Ao Inserir Dado Na Raiz!");
            (*ptr_arvore)->qtd_nos++; //Conta Um Nó, Pois Adicionou
            return BMH_OK; 
        }

        else { //Caso Não Conseguiu Criar Nó
            bmh_log_sucesso("Inserção Ordenada Bmh Árvore: Erro Ao Criar Dado Na Raiz!");
            return BMH_ERRO_AO_ALOCAR;
        }
    }
    
    else if ((*ptr_arvore)->no_raiz != NULL && (*ptr_arvore)->qtd_nos != 0) {
        no_atual = (*ptr_arvore)->no_raiz; //Define Referência Como A Raiz Para Navegar

        while (true) {
            if (metodo_comparacao(dado, no_atual->dado) > 0) { //Se Dado É Maior Que Dado Do Nó
                if (no_atual->filho_dir == NULL) { //Caso Não Exista Filho Que Tenha Dado Maior
                    if (criar_no_filho_para_no(&no_atual, dado, (*ptr_arvore)->t_dados,
                    metodo_comparacao) == BMH_OK) { //Tenta Criar Filho Para Nó Atual
                        bmh_log_sucesso("Inserção Ordenada Bmh Árvore: Sucesso Ao Criar Nó Filho Para Nó Atual!");
                        return BMH_OK;
                    }

                    else { //Caso Não Consiga Criar
                        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Erro Ao Criar Nó Filho Para Nó Atual!");
                        return BMH_ERRO;;
                    }
                }
                else no_atual = no_atual->filho_dir; //Passa Para Lado Direto Caso Exista
            }

            else {
                if (no_atual->filho_esq == NULL) { //Caso Não Exista Filho Que Tenha Dado Menor
                    if (criar_no_filho_para_no(&no_atual, dado, (*ptr_arvore)->t_dados,
                    metodo_comparacao) == BMH_OK) { //Tenta Criar Filho Para Nó Atual
                        bmh_log_sucesso("Inserção Ordenada Bmh Árvore: Sucesso Ao Criar Nó Filho Para Nó Atual!");
                        return BMH_OK;
                    }

                    else { //Caso Não Consiga Criar
                        bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Erro Ao Criar Nó Filho Para Nó Atual!");
                        return BMH_ERRO;
                    }
                }
                else no_atual = no_atual->filho_esq; //Passa Para Lado Direto Caso Exista
            }
        }
    }

    bmh_log_fracasso("Inserção Ordenada Bmh Árvore: Comportamento Inesperado Ou Árvore Foi Corrompida!");
    return BMH_ERRO;
}

BmhNoArvore *buscar_dado_bmh_arvore(
    BmhArvore *arvore, //Árvore Que Irá Ser Procurado Os Dados
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Procurado
    BmhComparador metodo_comparacao //Metódo Para Comparar Dados
) //Busca Dado Na Árvore E Devolve Nó Que Foi Achado
{
    BmhNoArvore *no_atual = NULL; //Nó Usado Para Navegar Na Árvore

    if (!arvore) { //Verifica Se Existe Árvore
        bmh_log_fracasso("Buscar Dado Bmh Árvore: Esta Árvore Não Existe!");
        return NULL; //Retorna Nulo, Pois Não Foi Feito A Operação
    }

    else if (!dado) { //Verifica Se Dado É Válido
        bmh_log_fracasso("Buscar Dado Bmh Árvore: Este Dado Não Existe!");
        return NULL; //Retorna Nulo, Pois Não Foi Feito A Operação
    }

    else if (!metodo_comparacao) { //Verifica Se Existe Método De Comparação
        bmh_log_fracasso("Buscar Dado Bmh Árvore: Este Método De Comparação É Inválido!");
        return NULL; //Retorna Nulo, Pois Não Foi Feito A Operação
    }

    //Busca do Dado Efetiva

    if (arvore->qtd_nos == 0 || !arvore->no_raiz) { //Verifica Se Árvore É Hábil Para Busca
        bmh_log_avisar("Buscar Dado Bmh Árvore: Esta Árvore Não Possui Nós Ou Não Possui Raiz!");
        return NULL; //Retorna Nulo, Pois Não Foi Feito A Operação
    }


    else {
        no_atual = arvore->no_raiz; //Define Nó Raiz Para Começar A Busca

        while (true) {
            if (metodo_comparacao(dado, no_atual->dado) == 0) { //Se Dados São Iguais
                bmh_log_sucesso("Buscar Dado Bmh Árvore: Sucesso Ao Procurar Dado!");
                return no_atual;
            }

            else if (metodo_comparacao(dado, no_atual->dado) > 0) { //Se Dado É Maior Que Dado Do Nó
                if (no_atual->filho_dir == NULL) { //Verifica Se Existe Dados Maiores
                    bmh_log_fracasso("Buscar Dado Bmh Árvore: Não Existe Esse Dado Na Árvore!");
                    return NULL; //Retorna Nulo, Já Que Não Achou Dado
                }
                
                else no_atual = no_atual->filho_dir; //Passa Para Próximo Para Continuar A Busca
            }

            else if (metodo_comparacao(dado, no_atual->dado) <= 0) { //Se Dado É Menor Ou Igual Que Dado Do Nó
                if (no_atual->filho_esq == NULL) { //Verifica Se Existe Dados Maiores
                    bmh_log_fracasso("Buscar Dado Bmh Árvore: Não Existe Esse Dado Na Árvore!");
                    return NULL; //Retorna Nulo, Já Que Não Achou Dado
                }
                
                else no_atual = no_atual->filho_esq; //Passa Para Próximo Para Continuar A Busca
            }
        }
    }

    bmh_log_fracasso("Buscar Dado Bmh Árvore: Comportamento Inesperado!");
    return NULL; //Retorna Nulo, Pois Teve Comportamento Não Esperado
}