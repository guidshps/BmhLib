#include "bmh_array.h"

BmhStatus criar_bmh_array( 
    BmhArray **ptr_array, //Ponteiro Para O Array Destino
    size_t t_dados //Tamanho dos Dados Armazenados No Array
) //Cria Bmh Array 
{ 
    if (ptr_array == NULL) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Criar Bmh Array: Este Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }
    
    else if (*ptr_array != NULL) { //Verifica Se Array Exsite
        bmh_log_fracasso("Criar Bmh Array: Este Array Já Existe!");
        return BMH_USO_INCORRETO;
    }
    
    else if (t_dados <= 0) { //Verifica Se Tamanho Dos Dados É Válido
        bmh_log_fracasso("Criar Bmh Array: Tamanho De Dado Inválido!");
        return BMH_USO_INCORRETO;
    }

    *ptr_array = bmh_calloc (1, sizeof(BmhArray)); //Tenta Alocar Memória

    if (*ptr_array == NULL) { //Verifica Se Conseguiu Alocar Espaço
        bmh_log_avisar("Criar Bmh Array: Erro Ao Alocar Memória!");
        return BMH_ERRO_AO_ALOCAR;
    }

    (*ptr_array)->t_dados = t_dados; //Atribui Tamanho Em Bytes De Cada Dado
    bmh_log_sucesso("Criar Bmh Array: Sucesso Ao Criar Bmh Array!"); 
    return BMH_OK;
}

BmhStatus destruir_bmh_array(
    BmhArray **ptr_array //Ponteiro Para O Array Destino
) //Destroí Bmh Array
{
    if (ptr_array == NULL) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Destruir Bmh Array: Este Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (*ptr_array == NULL) { //Verifica Se Array Existe
        bmh_log_fracasso("Destruir Bmh Array: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }

    if ((*ptr_array)->dados != NULL) { //Verifica Se Existem Dados
        bmh_free((*ptr_array)->dados); //Libera Lista De Dados
    }

    bmh_free(*ptr_array); //Libera Memória
    *ptr_array = NULL; //Define Como Valor Não Existente

    bmh_log_sucesso("Destruir Bmh Array: Array Destruido Com Sucesso!");
    return BMH_OK;
}

static BmhStatus talvez_aumente_bmh_array(
    BmhArray **ptr_array //Ponteiro Para O Array Destino
) //Aumenta O Tamanho Do Espaço Que O Ponteiro Dos Dados Aponta, Caso Necessário 
{ 
    BmhPonteiroQualquer ptr_auxiliar = NULL; /*Variável Auxiliar Para
    Realizar Alocação De Memória E Transferência De Dados.*/

    if (ptr_array == NULL) {
        bmh_log_fracasso("Aumentar Bmh Array: Este Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (*ptr_array == NULL) {
        bmh_log_fracasso("Aumentar Bmh Array: Este Array Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    if ((*ptr_array)->t_atual == 0 && (*ptr_array)->q_dados == 0 && 
    (*ptr_array)->dados == NULL) {
        bmh_log_avisar("Talvez Aumente Bmh Array: Iniciando Espaço...");
        ptr_auxiliar = calloc(TAMANHO_INICIAL_BMH_ARRAY, (*ptr_array)->t_dados); //Aloca Espaço Inicial

        if (ptr_auxiliar == NULL) { //Verifica Se Conseguiu Alocar
            bmh_log_avisar("Talvez Aumente Bmh Array: Falha Ao Inciar Espaço!");
            return BMH_ERRO_AO_ALOCAR;
        }

        (*ptr_array)->dados = ptr_auxiliar; //Recebe Espaço Inicial
        (*ptr_array)->t_atual = TAMANHO_INICIAL_BMH_ARRAY; //Define Tamanho Inciail
        bmh_log_sucesso("Talvez Aumente Bmh Array: Sucesso Ao Alocar Espaço Inicial!");
    }

    else if ((*ptr_array)->q_dados + 1 > (*ptr_array)->t_atual && 
    (*ptr_array)->dados != NULL) { //Verifica Se Lista Conforta Dado
        bmh_log_avisar("Talvez Aumente Bmh Array: Tentando Aumentar Array...");
        unsigned int tamanho_antigo = (*ptr_array)->t_atual; //Tamanho Antigo Do Array
        unsigned int novo_tamanho = ceil(tamanho_antigo * (1 + FATOR_CRESCIMENTO_BMH_ARRAY)); /*Aumenta 
        Array Conforme A Funçaõ*/

        ptr_auxiliar = calloc(novo_tamanho, (*ptr_array)->t_dados); //Tenta Criar Novo Array

        if (ptr_auxiliar == NULL) {
            bmh_log_avisar("Talvez Aumente Bmh Array: Falha Ao Alocar Ponteiro Auxiliar!");
            return BMH_ERRO_AO_ALOCAR;
        }

        BmhByte *ptr_auxiliar_convertido = (BmhByte *)ptr_auxiliar;
        BmhByte *ptr_array_convertido = (BmhByte *)(*ptr_array)->dados;

        for (int i = 0; i < tamanho_antigo * (*ptr_array)->t_dados; i++) {
            ptr_auxiliar_convertido[i] = ptr_array_convertido[i]; //Transfere Dados
        }

        free(ptr_array_convertido); //Limpa Lista Antiga De Dados
        (*ptr_array)->dados = ptr_auxiliar_convertido; //Recebe Lista Com Dados Novos
        (*ptr_array)->t_atual = novo_tamanho; //Atualiza Novo Tamanho Da Lista
        bmh_log_sucesso("Talvez Aumente Bmh Array: Sucesso Ao Extender Ponteiro!");
    }

    else if ((*ptr_array)->dados == NULL) {
        bmh_log_avisar("Talvez Aumente Bmh Array: Lista Foi Corrompida!");
        return BMH_ERRO;
    }

    return BMH_OK;
}

static BmhStatus atribuir_dado_byte_a_byte_bmh_array(
    BmhArray **ptr_array, //Ponteiro Para O Array Destino
    BmhPonteiroQualquer dado //Dado Que Irá Ser Copiado
) //Passa Byte A Byte Para O Local Do Novo Dado
{
    size_t endereco_acessado;
    BmhByte *array_base = NULL, *local_destino = NULL, *dado_convertido = NULL; /*Váriavel
    Auxiliar Para Salvar Dados */

    if (ptr_array == NULL) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Atribuir Dado Byte A Byte Bmh Array: Este Ponteiro Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (*ptr_array == NULL) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Atribuir Dado Byte A Byte Bmh Array: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (dado == NULL) { //Verifica Se Dado Existe
        bmh_log_fracasso("Atribuir Dado Byte A Byte Bmh Array: Este Dado Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if ((*ptr_array)->dados == NULL || (*ptr_array)->t_atual < (*ptr_array)->q_dados) {
        bmh_log_avisar("Adicionar Dado Bmh Array: Este Array Não Conforta O Dado!");
        return BMH_USO_INCORRETO;
    }

    endereco_acessado = (*ptr_array)->q_dados - 1; //Realiza Cálculo Do Endereço

    //Realiza Conversão Dos Dados
    array_base = (BmhByte *) (*ptr_array)->dados;
    local_destino = array_base + endereco_acessado * (*ptr_array)->t_dados;
    dado_convertido = (BmhByte *) dado;

    for (size_t i = 0; i < (*ptr_array)->t_dados; i++) {
        local_destino[i] = dado_convertido[i]; //Realiza Passagem De Dados
    }

    bmh_log_sucesso("Atribuir Dado Byte A Byte Bmh Array: Foi Atribuido O Dado!");
    return BMH_OK;
}

BmhStatus adicionar_dado_bmh_array(
    BmhArray **ptr_array, //Ponteiro Para O Array Destino
    BmhPonteiroQualquer dado //Dado Que Irá Ser Adicionado No Array
) //Atribui Dado Para O Array (Último Endereço) 
{ 
    if (*ptr_array == NULL) { //Verifica Se Array Existe
        bmh_log_fracasso("Atribuir Dado Bmh Array: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (dado == NULL) { //Verifica Se Dado Existe
        bmh_log_fracasso("Atribuir Dado Bmh Array: Este Dado Não Existe!");
        return BMH_USO_INCORRETO;
    }

    if (talvez_aumente_bmh_array(ptr_array) != BMH_OK) { /*Verifica Se Conseguiu Aumentar 
    Tamanho Do Array Ou Se Está Tudo Certo*/
        bmh_log_fracasso("Atribuir Dado Bmh Array: Algo Aconteceu Errado Ao Aumentar O Array!\n");
        return BMH_ERRO; //Retorna Erro Para O Usuário
    }

    if (atribuir_dado_byte_a_byte_bmh_array(ptr_array, dado) == BMH_OK) { //Verifica Se Atribuição Ocorreu Corretamente
        bmh_log_sucesso("Atribuir Dado Bmh Array: O Dado Foi Atribuido Corretamente!");
        (*ptr_array)->q_dados++; //Incrementa Quantidade De Dados Para Se Referenciar
        return BMH_OK;
    }

    else {
        bmh_log_fracasso("Atribuir Dado Bmh Array: O Dado Não Foi Atribuido!");
        return BMH_ERRO;
    }
}

BmhPonteiroQualquer acessar_endereco_bmh_array(
    BmhArray *array, //Array Destino
    size_t indice //Indice Do Dado Que Irá Ser Devolvido 
) //Acessa Endereço Enviado Pelo Usuário E Devolve Ele 
{
    if (array == NULL) { //Verifica Se Array Existe
        bmh_log_fracasso("Acessar Endereço Bmh Array: Este Array Não Existe!");
        return NULL; //Devolve Endereço Nulo, Já Que Não Conseguiu Acessar Elemento
    }
    
    else if (indice < 0 || indice >= array->q_dados) { // Verifica Se Endereço É Válido
        bmh_log_fracasso("Acessar Endereço Bmh Array: Este Endereço É Inválido!");
        bmh_log_avisar("Acessar Endereco Bmh Array: Vale Ressaltar Que O Conjunto De Endereços É De (0 a N)!");
        return NULL; //Devolve Endereço Nulo, Já Que Não Conseguiu Acessar Elemento
    }

    else if (array->dados == NULL) { //Verifica Se Existe Dados
        bmh_log_fracasso("Acessar Endereço Bmh Array: Não Existe Dados!\n");
        return NULL; //Devolve Endereço Nulo, Já Que Não Conseguiu Acessar Elemento
    }

    BmhByte *ptr_base = array->dados; //Ptr Base Para Acessar Dados
    return ptr_base + indice * array->t_dados; //Retorna Endereço Enviado
}

BmhPonteiroQualquer busca_linear_bmh_array(
    BmhArray *array, //Array Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Buscado No Array
    BmhComparador metodo_comparacao //Método Que Os Dados Serão Comparados
) //Busca Linearmente Por Dado (Devolve Endereço Do Dado) 
{ //Busca Linearmente Por Dado (Devolve Endereço Do Dado)
    if (array == NULL) { //Verifica Se Array Existe
        bmh_log_fracasso("Busca Linear Bmh Array: Este Array Não Existe!");
        return NULL; //Retorna Nulo, Já Que Não Foi Possível Efetuar Operação
    }

    else if (dado == NULL) { //Verifica Se Dado Existe
        bmh_log_fracasso("Busca Linear Bmh Array: Este Dado Não Existe!");
        return NULL; //Retorna Nulo, Já Que Não Foi Possível Efetuar Operação
    }

    else if (array->dados == NULL || array->t_atual == 0 || array->q_dados == 0) {
        bmh_log_fracasso("Busca Linear Bmh Array: Não Existe Um Conjunto De Dados!");
        return NULL; //Retorna Nulo, Já Que Não Foi Possível Efetuar Operação
    }

    else if (metodo_comparacao == NULL) {
        bmh_log_fracasso("Busca Linear Bmh Array: Método de Comparação Inválido!");
        return NULL; //Retorna Nulo, Já Que Não Foi Possível Efetuar Operação
    }

    BmhByte *ptr_base = array->dados; //Passa Ponteiro Base Como Referência

    for (int i = 0; i < array->q_dados; i++) {
        if (metodo_comparacao(ptr_base + i * array->t_dados, dado) == 0) {
            bmh_log_sucesso("Busca Linear Bmh Array: O Dado Foi Achado!");
            return ptr_base + i * array->t_dados; //Devolve Endereço Do Dado Achado
        }
    }

    bmh_log_fracasso("Busca Linear Bmh Array: O Dado Não Foi Achado!");
    return NULL; //Retorna Nulo, Já Que Não Foi Possível Efetuar Operação
}

BmhPonteiroQualquer busca_binaria_bmh_array(
    BmhArray *array, //Array Destino
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Buscado No Array 
    BmhComparador metodo_comparacao //Método Que Os Dados Serão Comparados
) //Busca Linearmente Por Dado (Devolve Endereço Do Dado)
{ 
    size_t end_min, end_ref, end_max, t_dados; //Variáveis Para Controle Da Posição
    BmhByte *array_base = NULL; //Endereço Inicial Do Dado

    if (array == NULL) { //Verifica Se Existe Array
        bmh_log_fracasso("Busca Binária Bmh Array: Este Array Não Existe!");
        return NULL; //Retorna Ponteiro Nulo, Pois Não Efetuou Operação
    }

    else if (array->dados == NULL) { //Verifica Se Existem Dados
        bmh_log_fracasso("Busca Binária Bmh Array: Não Existe Uma Lista Dos Dados!");
        return NULL; //Retorna Ponteiro Nulo, Pois Não Efetuou Operação
    }

    else if (metodo_comparacao == NULL) {
        bmh_log_fracasso("Busca Binária Bmh Array: Este Método De Comparação Não Existe!");
        return NULL;
    }

    array_base = array->dados; //Pega Endereço Inicial Dos Dados
    t_dados = array->t_dados; //Tamanho Dos Dados Para Controle
    end_min = 0;; //Define Endereço Mínimo Inicial
    end_max = array->q_dados - 1; //Define Endereço Máximo Inicial
    end_ref = ceil((end_max - end_min) / 2); //Define Endereço De Referência Inicial

    while (true) {
        if (metodo_comparacao(array_base + end_ref * t_dados, dado) == 0) { //Verifica Se Dados São Iguais
            bmh_log_sucesso("Busca Binária Bmh Array: O Elemento Foi Achado!");
            return array_base + end_ref * t_dados; //Devolve Endereço
        }

        else if (end_max - end_min == 0) {
            break; //Sai Do Loop Caso Dado Não Seja Achado
        }

        else if (metodo_comparacao(dado, array_base + end_ref * t_dados) > 0) { //Verifica Se Dado É Maior
            end_min = end_ref; //Adota Endreço De Refêrencia Mínimo Como O Atual
            end_ref = ceil(end_ref + (float)(end_max - end_min) / 2); //Adota Novo Endereço Mediano
        }

        else if (metodo_comparacao(dado, array_base + end_ref * t_dados) < 0) { //Verifica Se Dado É Maior
            end_max = end_ref; //Adota Endreço De Refêrencia Máxima Como O Atual
            end_ref = ceil(end_ref + (float)(end_max - end_min) / 2); //Adota Novo Endereço Mediano
        }
    }

    bmh_log_fracasso("Busca Binária Bmh Array: O Elemento Não Foi Achado!");
    return NULL;
}

BmhStatus ordenacao_rapida_bmh_array(
    BmhArray **ptr_array, //Array Destino
    BmhComparador metodo_comparacao //Método Que Os Dados Serão Comparados
) //Realiza A Quick Sort Na Lista Com O Método Que O Usúario Destinou Para Usar
{ /*Realiza A Quick Sort Na Lista Com O Método Que O 
Usúario Destinou Para Usar*/
    if (ptr_array == NULL) { //Verifica Se Array Existe
        bmh_log_fracasso("Ordenação Rápida Bmh Array: Ponteiro Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (*ptr_array == NULL) {
        bmh_log_fracasso("Ordenação Rápida Bmh Array: Este Array Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (metodo_comparacao == NULL) { //Vê Se Existe Método De Comparação
        bmh_log_fracasso("Ordenação Rápida Bmh Array: Este Método De Comparação Não Existe!");
        return BMH_USO_INCORRETO;
    }

    qsort((*ptr_array)->dados, (*ptr_array)->q_dados, 
    (*ptr_array)->t_dados, metodo_comparacao); //Realiza Ordenação Dos Dados

    bmh_log_sucesso("Ordenação Rápida Bmh Array: O Array Foi Ordenado!");
    return BMH_OK;
}

BmhStatus deletar_dado_bmh_array(
    BmhArray **ptr_array, //Array Destino
    size_t indice //Indice Do Dado Que Será Deletado
)  //Deleta Dado Indicado Do Array E Corrige As Posições Dos Dados 
{ 
    BmhPonteiroQualquer ptr_dado_destino = NULL; //Ponteiro Do Destino
    BmhByte *ptr_convertido = NULL; //Ponteiro Destino Convertido
    size_t tamanho_dado, qtd_dados; //Tamanho do Tipo Do Dado

    if (ptr_array == NULL) { //Verifica Se Existe Ponteiro
        bmh_log_fracasso("Deletar Dado Bmh Array: Este Array Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (*ptr_array == NULL) { //Verifica Se Ponteiro Existe
        bmh_log_fracasso("Deletar Dado Bmh Array: Este Array Não Existe!");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (indice >= (*ptr_array)->q_dados) { //Verifica Se Endereço É Válido
        bmh_log_fracasso("Deletar Dado Bmh Array: Este Endereço Está Fora Do Alcance!");
        return BMH_USO_INCORRETO; 
    }

    ptr_dado_destino = acessar_endereco_bmh_array(*ptr_array, indice); //Acessa Endereço
    ptr_convertido = (BmhByte *) ptr_dado_destino; //Converte Endereço
    qtd_dados = (*ptr_array)->q_dados; //Atribui Quantidade De Dados
    tamanho_dado = (*ptr_array)->t_dados; //Atribui Tamanho Do Dano

    for (int i = 0; i < tamanho_dado * (qtd_dados - indice - 1); i++) {
        ptr_convertido[i] = ptr_convertido[i + tamanho_dado]; //Passa Dados
    }

    (*ptr_array)->q_dados--; //Diminui Quantidade De Dados

    bmh_log_sucesso("Deletar Dado Bmh Array: O Dado Foi Deletado Sucessivamente!");
    return BMH_OK;
}