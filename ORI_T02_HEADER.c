/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Organização de Recuperação da Informação
 * Prof. Tiago A. Almeida
 *
 * Trabalho 02 - Árvore-B
 *
 * ========================================================================== *
 *   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
 * ========================================================================== */

/* Bibliotecas */
#include "ORI_T02_HEADER.h"

/* ===========================================================================
 * ================================= FUNÇÕES ================================= */
/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */


/* Compara a chave (key) com cada elemento do índice (elem).
 * Funções auxiliares para o buscar e inserir chaves em Árvores-B.
 * Note que, desta vez, as funções comparam chaves no formato string, e não struct.
 * "key" é a chave do tipo string que está sendo buscada ou inserida. 
 * "elem" é uma chave do tipo string da struct btree_node.
 *
 * Dica: consulte sobre as funções strncmp() e strnlen(). Muito provavelmente, você vai querer utilizá-las no código.
 * */

/* Função de comparação entre chaves do índice jogadores_idx */
int order_jogadores_idx(const void *key, const void *elem) {
	return strncmp(key, elem, TAM_ID_JOGADOR-1);
}

/* Função de comparação entre chaves do índice kits_idx */
int order_kits_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strncmp(key, elem, TAM_ID_KIT - 1);
}

/* Função de comparação entre chaves do índice partidas_idx */
int order_partidas_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strncmp(key, elem, TAM_ID_PARTIDA - 1);
}

/* Função de comparação entre chaves do índice resultados_idx */
int order_resultados_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strncmp(key, elem, TAM_ID_JOGADOR + TAM_ID_PARTIDA - 2);
}

/* Função de comparação entre chaves do índice preco_kit_idx */
int order_preco_kit_idx(const void *key, const void *elem){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strncmp(key, elem, TAM_FLOAT_NUMBER - 1);
}

/* Função de comparação entre chaves do índice data_partida_idx */
int order_data_partida_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strncmp(key, elem, TAM_DATETIME - 1);
}

/* Função de comparação entre chaves do índice jogador_kits_idx */
int order_jogador_kit_idx(const void *key, const void *elem) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return strncmp(key, elem, TAM_MAX_NOME_KIT - 1);
}

/* Função de comparação entre vitórias, eliminacoes e tempo de sobrevivencia dos jogadores
 * Usada na função recompensar_vencedores_periodo; */
int qsort_info_jogador(const void *a, const void *b) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(((Info_Jogador*)a)->vitorias != ((Info_Jogador*)b)->vitorias) return ((Info_Jogador*)b)->vitorias - ((Info_Jogador*)a)->vitorias;
	else if(((Info_Jogador*)a)->eliminacoes != ((Info_Jogador*)b)->eliminacoes) return ((Info_Jogador*)b)->eliminacoes - ((Info_Jogador*)a)->eliminacoes;
	else if(strcmp(((Info_Jogador*)a)->sobrevivencia, ((Info_Jogador*)b)->sobrevivencia) != 0) return strcmp(((Info_Jogador*)b)->sobrevivencia, ((Info_Jogador*)a)->sobrevivencia);
	else return strcmp(((Info_Jogador*)a)->id_jogador, ((Info_Jogador*)b)->id_jogador);
}


/* Cria o índice respectivo */
void criar_jogadores_idx() {
	char str[TAM_CHAVE_JOGADORES_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_jogadores; ++i) {
		Jogador z = recuperar_registro_jogador(i);

		sprintf(str, "%s%04d", z.id_jogador, i);
		btree_insert(str, &jogadores_idx);
	}
	printf(INDICE_CRIADO, "jogadores_idx");
}


void criar_kits_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_KITS_IDX + 1];
	for (unsigned i = 0; i < qtd_registros_kits; ++i) {
		Kit k = recuperar_registro_kit(i);

		sprintf(str, "%s%04d", k.id_kit, i);
		btree_insert(str, &kits_idx);
	}
	printf(INDICE_CRIADO, "kits_idx");
}


void criar_partidas_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_PARTIDAS_IDX + 1];
	for(unsigned i = 0; i < qtd_registros_partidas; ++i) {
		Partida p = recuperar_registro_partida(i);

		sprintf(str, "%s%04d", p.id_partida, i);
		btree_insert(str, &partidas_idx);
	}
	printf(INDICE_CRIADO, "partidas_idx");
}


void criar_resultados_idx(){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_RESULTADOS_IDX + 1];
	for(unsigned i = 0; i < qtd_registros_resultados; ++i) {
		Resultado r = recuperar_registro_resultado(i);

		sprintf(str, "%s%s%04d", r.id_jogador, r.id_partida, i);
		btree_insert(str, &resultados_idx);
	}
	printf(INDICE_CRIADO, "resultados_idx");
}


void criar_preco_kit_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_PRECO_KIT_IDX + 1];
	for(unsigned i = 0; i < qtd_registros_kits; ++i) {
		Kit k = recuperar_registro_kit(i);

		sprintf(str, "%013.2lf%s", k.preco, k.id_kit);
		btree_insert(str, &preco_kit_idx);
	}
	printf(INDICE_CRIADO, "preco_kit_idx");
}


void criar_data_partida_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_DATA_PARTIDA_IDX + 1];
	for(unsigned i = 0; i < qtd_registros_partidas; ++i) {
		Partida p = recuperar_registro_partida(i);

		sprintf(str, "%s%s", p.inicio, p.id_partida);
		btree_insert(str, &data_partida_idx);
	}
	printf(INDICE_CRIADO, "data_partida_idx");
}


void criar_jogador_kits_idx() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	
	for(unsigned i = 0; i < qtd_registros_jogadores; ++i) {
		Jogador j = recuperar_registro_jogador(i);
		
		for(int k = 0; k < QTD_MAX_KITS; ++k) {
			if(strlen(j.kits[k]) > 0) {
				Kit kit = recuperar_registro_kit(atoi(j.kits[k]));
				inverted_list_insert(strupr(kit.nome), j.id_jogador, &jogador_kits_idx);
			}
		}
	}
	printf(INDICE_CRIADO, "jogador_kits_idx");
}


/* Recupera do arquivo o registro com o RRN informado
 * e retorna os dados nas structs */
Jogador recuperar_registro_jogador(int rrn) {
	Jogador j;
	char data[TAM_REGISTRO_JOGADOR + 1], *p;

	strncpy(data, ARQUIVO_JOGADORES + (rrn * TAM_REGISTRO_JOGADOR), TAM_REGISTRO_JOGADOR);
	data[TAM_REGISTRO_JOGADOR] = '\0';

	p = strtok(data, ";");
	strcpy(j.id_jogador, p);

	p = strtok(NULL, ";");
	strcpy(j.apelido, p);

	p = strtok(NULL, ";");
	strcpy(j.cadastro, p);

	p = strtok(NULL, ";");
	strcpy(j.premio, p);

	p = strtok(NULL, ";");
	j.saldo = atof(p);

	p = strtok(NULL, ";");

	for (int i = 0; i < QTD_MAX_KITS; ++i) {
		memset (j.kits[i], 0, TAM_ID_KIT);
	}

	if (p[0] != '#') {
		p = strtok(p, "|");
		for (int i = 0; p; p = strtok(NULL, "|"), ++i) {
			strncpy(j.kits[i], p, TAM_ID_KIT-1);
		}
	}
	
	return j;
}


Kit recuperar_registro_kit(int rrn) {
	Kit k;
	
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char data[TAM_REGISTRO_KIT + 1], *p;
	strncpy(data, ARQUIVO_KITS + (rrn * TAM_REGISTRO_KIT), TAM_REGISTRO_KIT);
	data[TAM_REGISTRO_KIT] = '\0';

	p = strtok(data, ";");
	strcpy(k.id_kit, p);

	p = strtok(NULL, ";");
	strcpy(k.nome, p);

	p = strtok(NULL, ";");
	strcpy(k.poder, p);

	p = strtok(NULL, ";");
	k.preco = atof(p);

	return k;
}


Partida recuperar_registro_partida(int rrn) {
	Partida p;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char data[TAM_REGISTRO_PARTIDA + 1];
	strncpy(data, ARQUIVO_PARTIDAS + (rrn * TAM_REGISTRO_PARTIDA), TAM_REGISTRO_PARTIDA);
	data[TAM_REGISTRO_PARTIDA] = '\0';

	int desloc = 0;
	strncpy(p.id_partida, data + desloc, TAM_ID_PARTIDA - 1);
	p.id_partida[TAM_ID_PARTIDA-1] = '\0';
	desloc += TAM_ID_PARTIDA - 1;

	strncpy(p.inicio, data + desloc, TAM_DATETIME - 1);
	p.inicio[TAM_DATETIME - 1] = '\0';
	desloc += TAM_DATETIME - 1;

	strncpy(p.duracao, data + desloc, TAM_TIME - 1);
	p.duracao[TAM_TIME - 1] = '\0';
	desloc += TAM_TIME - 1;

	strncpy(p.cenario, data + desloc, TAM_CENARIO - 1);
	p.cenario[TAM_CENARIO - 1] = '\0';
	desloc += TAM_CENARIO - 1;
	
	strncpy(p.id_jogadores, data + desloc, TAM_ID_JOGADORES - 1);
	p.id_jogadores[TAM_ID_JOGADORES - 1] = '\0';

	return p;
}


Resultado recuperar_registro_resultado(int rrn) {
	Resultado r;

	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char data[TAM_REGISTRO_RESULTADO + 1];
	strncpy(data, ARQUIVO_RESULTADOS + (rrn * TAM_REGISTRO_RESULTADO), TAM_REGISTRO_RESULTADO);
	data[TAM_REGISTRO_RESULTADO] = '\0';

	int desloc = 0;
	strncpy(r.id_jogador, data + desloc, TAM_ID_JOGADOR - 1);
	r.id_jogador[TAM_ID_JOGADOR - 1] = '\0';
	desloc += TAM_ID_JOGADOR - 1;

	strncpy(r.id_partida, data + desloc, TAM_ID_PARTIDA-1);
	r.id_partida[TAM_ID_PARTIDA - 1] = '\0';
	desloc += TAM_ID_PARTIDA - 1;

	strncpy(r.id_kit, data + desloc, TAM_ID_KIT-1);
	r.id_kit[TAM_ID_KIT - 1] = '\0';
	desloc += TAM_ID_KIT - 1;

	char number[5];
	strncpy(number, data + desloc, 4);
	number[4] = '\0';
	r.colocacao = atoi(number);
	desloc += 4;

	strncpy(r.sobrevivencia, data + desloc, TAM_TIME - 1);
	r.sobrevivencia[TAM_TIME - 1] = '\0';
	desloc += TAM_TIME - 1;

	strncpy(number, data + desloc, 4);
	number[4] = '\0';
	r.eliminacoes = atoi(number);

	return r;
}


/* Escreve em seu respectivo arquivo na posição informada (RRN) */
void escrever_registro_jogador(Jogador j, int rrn) {

	char data[TAM_REGISTRO_JOGADOR + 1], number[100];
	data[0] = '\0'; number[0] = '\0';

	strcat(data, j.id_jogador);
	strcat(data, ";");
	strcat(data, j.apelido);
	strcat(data, ";");
	strcat(data, j.cadastro);
	strcat(data, ";");
	strcat(data, j.premio);
	strcat(data, ";");
	sprintf(number, "%013.2lf", j.saldo);
	strcat (data, number);
	strcat(data, ";");

	for (int i = 0; i < QTD_MAX_KITS; ++i) {
		if (strlen(j.kits[i]) > 0) {
			if (i != 0)
				strcat (data, "|");
			strcat(data, j.kits[i]);
		}
	}
	strcat(data, ";");


	strpadright(data, '#', TAM_REGISTRO_JOGADOR);

	strncpy(ARQUIVO_JOGADORES + rrn*TAM_REGISTRO_JOGADOR, data, TAM_REGISTRO_JOGADOR);
}

void escrever_registro_kit(Kit k, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char data[TAM_REGISTRO_KIT + 1], number[100];
	data[0] = '\0'; number[0] = '\0';
	strcat(data, k.id_kit);
	strcat(data, ";");
	strcat(data, k.nome);
	strcat(data, ";");
	strcat(data, k.poder);
	strcat(data, ";");
	sprintf(number, "%013.2lf", k.preco);
	strcat(data, number);
	strcat(data, ";");

	strpadright(data, '#', TAM_REGISTRO_KIT);

	strncpy(ARQUIVO_KITS + rrn*TAM_REGISTRO_KIT, data, TAM_REGISTRO_KIT);
}


void escrever_registro_partida(Partida p, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char data[TAM_REGISTRO_PARTIDA + 1];
	data[0] = '\0';

	strcat(data, p.id_partida);
	strcat(data, p.inicio);
	strcat(data, p.duracao);
	strcat(data, p.cenario);
	strcat(data, p.id_jogadores);

	strncpy(ARQUIVO_PARTIDAS + rrn*TAM_REGISTRO_PARTIDA, data, TAM_REGISTRO_PARTIDA);
}

void escrever_registro_resultado (Resultado jp, int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char data[TAM_REGISTRO_RESULTADO + 1];
	data[0] = '\0';
	strcat(data, jp.id_jogador);
	strcat(data, jp.id_partida);
	strcat(data, jp.id_kit);

	char number[5];
	sprintf(number, "%04d", jp.colocacao);

	strcat(data, number);
	strcat(data, jp.sobrevivencia);
	sprintf(number, "%04d", jp.eliminacoes);
	strcat(data, number);

	strncpy(ARQUIVO_RESULTADOS + rrn*TAM_REGISTRO_RESULTADO, data, TAM_REGISTRO_RESULTADO);
}


/* Exibe um registro com base no RRN */
bool exibir_jogador(int rrn) {
	if (rrn < 0)
		return false;

	Jogador j = recuperar_registro_jogador(rrn);

	printf ("%s, %s, %s, %s, %.2lf\n", j.id_jogador, j.apelido, j.cadastro, j.premio, j.saldo);

	return true;
}

bool exibir_kit(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(rrn < 0)
		return false;
	
	Kit k = recuperar_registro_kit(rrn);

	printf("%s, %s, %s, %.2lf\n", k.id_kit, k.nome, k.poder, k.preco);

	return true;
}

bool exibir_partida(int rrn) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(rrn < 0)
		return false;
	
	Partida p = recuperar_registro_partida(rrn);

	printf("%s, %s, %s, %s, %s\n", p.id_partida, p.inicio, p.duracao, p.cenario, p.id_jogadores);

	return true;
}


/* Exibe um registro com base na chave de um btree_node */
bool exibir_btree_jogadores(char *chave) {
	char num [5];
	memset (num, 0, 5);
	memcpy (num, chave + TAM_ID_JOGADOR-1, 4);

	int rrn = strtol(num, NULL, 10);
    return exibir_jogador(rrn);
}

bool exibir_btree_kits(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char num[5];
	memset(num, 0, 5);
	memcpy(num, chave + TAM_ID_KIT-1, 4);

	int rrn = strtol(num, NULL, 10);
	return exibir_kit(rrn);
}

bool exibir_btree_partidas(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char num[5];
	memset(num, 0, 5);
	memcpy(num, chave + TAM_ID_PARTIDA-1, 4);

	int rrn = strtol(num, NULL, 10);
	return exibir_partida(rrn);
}

bool exibir_btree_preco_kit(char *chave) {
	if (!chave) return false;
	
    char id_kit[TAM_ID_KIT];
    char rrn_str[TAM_RRN_REGISTRO + 1];
    int rrn;

    strncpy(id_kit, chave + (TAM_FLOAT_NUMBER - 1), TAM_ID_KIT - 1);
    id_kit[TAM_ID_KIT - 1] = '\0';
	
	char chave_kit[TAM_CHAVE_KITS_IDX];
	bool found = btree_search(chave_kit, false, id_kit, kits_idx.rrn_raiz, &kits_idx);
	if(!found) {
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return false;
	}
	strncpy(rrn_str, chave_kit + TAM_ID_KIT - 1, TAM_RRN_REGISTRO);
    rrn_str[4] = '\0';
    rrn = atoi(rrn_str);
	
    return exibir_kit(rrn);
}

bool exibir_btree_data_partida(char *chave) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if (!chave) return false;

    char data_partida[TAM_DATETIME];
    char id_partida[TAM_ID_PARTIDA];
    char rrn_str[TAM_RRN_REGISTRO + 1];
    int rrn;

    strncpy(data_partida, chave, TAM_DATETIME - 1);
    data_partida[TAM_DATETIME - 1] = '\0';

    strncpy(id_partida, chave + (TAM_DATETIME - 1), TAM_ID_PARTIDA - 1);
    id_partida[TAM_ID_PARTIDA - 1] = '\0';

	char partida_reg[TAM_CHAVE_PARTIDAS_IDX];
	bool found = btree_search(partida_reg, false, id_partida, partidas_idx.rrn_raiz, &partidas_idx);

	if (!found) {
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return false;
	}

	strncpy(rrn_str, partida_reg + TAM_ID_PARTIDA - 1, TAM_RRN_REGISTRO);
	rrn_str[TAM_RRN_REGISTRO] = '\0';
	rrn = atoi(rrn_str);

    return exibir_partida(rrn);
}



/* Funções principais */
void cadastrar_jogador_menu(char *id_jogador, char *apelido) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
    char resultado[TAM_CHAVE_JOGADORES_IDX];
    bool found = btree_search(resultado, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
    if (found) {
        printf(ERRO_PK_REPETIDA, id_jogador);
        return;
    }

    Jogador j;
    strcpy(j.id_jogador, id_jogador);
    strcpy(j.apelido, apelido);
    strcpy(j.premio, "000000000000");
    current_datetime(j.cadastro);
    j.saldo = 0.0;

    for (int i = 0; i < QTD_MAX_KITS; i++)  j.kits[i][0] = '\0';

    escrever_registro_jogador(j, qtd_registros_jogadores);

    char key[TAM_CHAVE_JOGADORES_IDX + 1];
    snprintf(key, sizeof(key), "%s%04d", id_jogador, qtd_registros_jogadores);
    btree_insert(key, &jogadores_idx);

    qtd_registros_jogadores++;

    printf(SUCESSO);
}


void remover_jogador_menu(char *id_jogador) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char resultado[TAM_CHAVE_JOGADORES_IDX];
	bool found = btree_search(resultado, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
	if (!found) {
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}

	char rrn_str[5];
    strncpy(rrn_str, resultado + TAM_ID_JOGADOR - 1, 4);
    rrn_str[4] = '\0';
    int rrn = atoi(rrn_str);

	Jogador j = recuperar_registro_jogador(rrn);
	j.id_jogador[0] = '*';
	j.id_jogador[1] = '|';

	escrever_registro_jogador(j, strtol(resultado + TAM_ID_JOGADOR - 1, NULL, 10));

	btree_delete(resultado, &jogadores_idx);

	printf(SUCESSO);
}


void adicionar_saldo_menu(char *id_jogador, double valor) {
	adicionar_saldo(id_jogador, valor, true);
}


void adicionar_saldo(char *id_jogador, double valor, bool flag){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(valor < 0){
		printf(ERRO_VALOR_INVALIDO);
		return;
	}

	char resultado[TAM_CHAVE_JOGADORES_IDX];
	bool found = btree_search(resultado, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
	if(!found){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}


	char rrn_str[5];
	strncpy(rrn_str, resultado + TAM_ID_JOGADOR - 1, 4);
	rrn_str[4] = '\0';
	int rrn = atoi(rrn_str);

	Jogador j = recuperar_registro_jogador(rrn);
	if(flag) j.saldo += valor;
	else j.saldo -= valor;

	escrever_registro_jogador(j, rrn);

	printf(SUCESSO);
}

void cadastrar_kit_menu(char *nome, char *poder, double preco) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char resultado[TAM_CHAVE_KITS_IDX];
	bool found = btree_search(resultado, false, nome, kits_idx.rrn_raiz, &kits_idx);
	if(found){
		printf(ERRO_PK_REPETIDA, nome);
		return;
	}

	Kit k;
	sprintf(k.id_kit, "%03d", qtd_registros_kits);
	strcpy(k.nome, nome);
	strcpy(k.poder, poder);
	k.preco = preco;

	escrever_registro_kit(k, qtd_registros_kits);

	char key[TAM_CHAVE_KITS_IDX + 1];
	snprintf(key, sizeof(key), "%s%04d", k.id_kit, qtd_registros_kits);
	key[TAM_CHAVE_KITS_IDX] = '\0';
	btree_insert(key, &kits_idx);

	char key_preco[TAM_CHAVE_PRECO_KIT_IDX + 1];
	snprintf(key_preco, sizeof(key_preco), "%013.2lf%s", preco, k.id_kit);
	key_preco[TAM_CHAVE_PRECO_KIT_IDX] = '\0';
	btree_insert(key_preco, &preco_kit_idx);
	
	qtd_registros_kits++;

	printf(SUCESSO);
}


void comprar_kit_menu(char *id_jogador, char *id_kit) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char found_player_id[TAM_CHAVE_JOGADORES_IDX];
	bool found = btree_search(found_player_id, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
	
	if(!found){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}
	
	char rrn_str[5];
	strncpy(rrn_str, found_player_id + TAM_ID_JOGADOR - 1, 4);
	rrn_str[4] = '\0';
	int rrn = atoi(rrn_str);

	Jogador j = recuperar_registro_jogador(rrn);

	char resultado_kit[TAM_CHAVE_KITS_IDX];
	found = btree_search(resultado_kit, false, id_kit, kits_idx.rrn_raiz, &kits_idx);
	if(!found){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}

	char rrn_str_kit[5];
	strncpy(rrn_str_kit, resultado_kit + TAM_ID_KIT - 1, 4);
	rrn_str_kit[4] = '\0';
	int rrn_kit = atoi(rrn_str_kit);


	Kit k = recuperar_registro_kit(rrn_kit);
	if(j.saldo < k.preco){
		printf(ERRO_SALDO_NAO_SUFICIENTE);
		return;
	}


	for(unsigned i = 0; i < QTD_MAX_KITS; ++i){
        if(strcmp(j.kits[i], id_kit) == 0) {
            printf(ERRO_KIT_REPETIDO, id_jogador, id_kit);
            return;
        }
		if(strlen(j.kits[i]) == 0){
			strcpy(j.kits[i], id_kit);
			break;
		}
	}

 	escrever_registro_jogador(j, rrn);

	adicionar_saldo(id_jogador, k.preco, false);

	inverted_list_insert(k.nome, id_jogador, &jogador_kits_idx);
}


void executar_partida_menu(char *inicio, char *duracao, char *cenario, char *id_jogadores, char *kits_jogadores, char *duracoes_jogadores, char *eliminacoes_jogadores) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	Partida p;
	sprintf(p.id_partida, "%08u", qtd_registros_partidas);
	strcpy(p.inicio, inicio);
	strcpy(p.duracao, duracao);
	strcpy(p.cenario, cenario);
	strcpy(p.id_jogadores, id_jogadores);

	for(int i = 0; i < 12; ++i){
		char id_jogador[TAM_ID_JOGADOR];
		char kit[TAM_ID_KIT];
		strncpy(id_jogador, id_jogadores + i * (TAM_ID_JOGADOR - 1), TAM_ID_JOGADOR - 1);
		id_jogador[TAM_ID_JOGADOR - 1] = '\0';

		strncpy(kit, kits_jogadores + i * (TAM_ID_KIT - 1), TAM_ID_KIT - 1);
		kit[TAM_ID_KIT - 1] = '\0';

		char chave_jogador[TAM_CHAVE_RESULTADOS_IDX + 1];
		char chave_kit[TAM_CHAVE_RESULTADOS_IDX + 1];

		bool found = btree_search(chave_jogador, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
		if(!found){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		found = btree_search(chave_kit, false, kit, kits_idx.rrn_raiz, &kits_idx);
		if(!found){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		char rrn_kit[5];
		strncpy(rrn_kit, chave_kit + TAM_ID_KIT - 1, 4);
		rrn_kit[4] = '\0';
		int rrn = atoi(rrn_kit);
		
		Kit k = recuperar_registro_kit(rrn);
		char kit_reg[TAM_MAX_NOME_KIT];
		strcpy(kit_reg, strupr(k.nome));

		int prim_indice = -1;
		if(!inverted_list_secondary_search(&prim_indice, false, kit_reg, &jogador_kits_idx)){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}
		if(prim_indice == -1){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		char jogadores_registrados[qtd_registros_jogadores + 1][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX];
		if(!inverted_list_primary_search(jogadores_registrados, false, prim_indice, NULL, &jogador_kits_idx)){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}
		
		bool tem = false;
		for(int j = 0; j < qtd_registros_jogadores; j++){
			if(jogadores_registrados[j][0] == '\0') break;
			if(strncmp(id_jogador, jogadores_registrados[j], TAM_ID_JOGADOR - 1) == 0){
				tem = true;
				break;
			}
		}
		if(!tem){
			printf(ERRO_JOGADOR_KIT, id_jogador, k.nome);
			return;
		}
	}

	escrever_registro_partida(p, qtd_registros_partidas);

	char chave_partida[TAM_CHAVE_PARTIDAS_IDX + 1];
	snprintf(chave_partida, sizeof(chave_partida), "%s%04d", p.id_partida, qtd_registros_partidas);
	chave_partida[TAM_CHAVE_PARTIDAS_IDX] = '\0';
	btree_insert(chave_partida, &partidas_idx);

	qtd_registros_partidas++;
	
	char chave_data[TAM_CHAVE_DATA_PARTIDA_IDX + 1];
	snprintf(chave_data, sizeof(chave_data), "%s%s", p.inicio, p.id_partida);
	chave_data[TAM_CHAVE_DATA_PARTIDA_IDX] = '\0';
	btree_insert(chave_data, &data_partida_idx);

	for(int i = 0; i < 12; ++i){
		Resultado r;
		strncpy(r.id_jogador, id_jogadores + i * (TAM_ID_JOGADOR - 1), TAM_ID_JOGADOR - 1);
        r.id_jogador[TAM_ID_JOGADOR - 1] = '\0';
        strncpy(r.id_kit, kits_jogadores + i * (TAM_ID_KIT - 1), TAM_ID_KIT - 1);
        r.id_kit[TAM_ID_KIT - 1] = '\0';
        strncpy(r.sobrevivencia, duracoes_jogadores + i * (TAM_TIME - 1), TAM_TIME - 1);
        r.sobrevivencia[TAM_TIME - 1] = '\0';

		char elim[5];
		strncpy(elim, eliminacoes_jogadores + i * 4, 4);
		elim[4] = '\0';
		r.eliminacoes = atoi(elim);

		r.colocacao = i + 1;

		strcpy(r.id_partida, p.id_partida);

		escrever_registro_resultado(r, qtd_registros_resultados);

		char chave_resultado[TAM_CHAVE_RESULTADOS_IDX + 1];
		snprintf(chave_resultado, sizeof(chave_resultado), "%s%s%04u", r.id_jogador, r.id_partida, qtd_registros_resultados);
		
		btree_insert(chave_resultado, &resultados_idx);

		qtd_registros_resultados++;
	}

	printf(SUCESSO);
}


void recompensar_vencedor_menu (char *data_inicio, char *data_fim, double premio) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char **datas = malloc(qtd_registros_partidas * sizeof(char*));
	for(int i = 0; i < qtd_registros_partidas; i++) datas[i] = malloc(TAM_CHAVE_DATA_PARTIDA_IDX * sizeof(char));
	
	int qtd = btree_search_in_order(datas, data_inicio, data_fim, 0, data_partida_idx.rrn_raiz, &data_partida_idx);
	if(qtd == 0){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
		return;
	}

	Info_Jogador info_jogadores[qtd_registros_jogadores];
	int num_jogadores = 0;

	for(int i = 0; i < qtd; ++i){
		char id_partida[TAM_ID_PARTIDA];
		strncpy(id_partida, datas[i] + TAM_DATETIME - 1, TAM_ID_PARTIDA - 1);
		id_partida[TAM_ID_PARTIDA - 1] = '\0';

		char chave_partida[TAM_CHAVE_PARTIDAS_IDX];
		bool found = btree_search(chave_partida, false, id_partida, partidas_idx.rrn_raiz, &partidas_idx);
		if(!found){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		char num[5];
		strncpy(num, chave_partida + TAM_ID_PARTIDA - 1, 4);
		num[4] = '\0';
		int rrn_partida = atoi(num);

		Partida p = recuperar_registro_partida(rrn_partida);

		for(int j = 0; j < 12; j++){
			char chave_resultado[TAM_CHAVE_RESULTADOS_IDX];
			snprintf(chave_resultado, TAM_ID_JOGADOR, "%s", p.id_jogadores + j * (TAM_ID_JOGADOR - 1));
			chave_resultado[TAM_ID_JOGADOR] = '\0';
			strcat(chave_resultado, p.id_partida);
			
			char resultado[TAM_CHAVE_RESULTADOS_IDX];
			found = btree_search(resultado, false, chave_resultado, resultados_idx.rrn_raiz, &resultados_idx);
			if(!found) continue;
			

			char num[5];
			strncpy(num, resultado + TAM_ID_JOGADOR + TAM_ID_PARTIDA - 2, 4);
			num[4] = '\0';
			int rrn_resultado = atoi(num);

			Resultado r = recuperar_registro_resultado(rrn_resultado);
			bool exist = false;
			for(unsigned k = 0; k < num_jogadores; k++){
				if(strcmp(info_jogadores[k].id_jogador, r.id_jogador) == 0){
					exist = true;
					if(r.colocacao == 1) info_jogadores[k].vitorias++;
					info_jogadores[k].eliminacoes += r.eliminacoes;
					if(strcmp(info_jogadores[k].sobrevivencia, r.sobrevivencia) < 0){
						strcpy(info_jogadores[k].sobrevivencia, r.sobrevivencia);
					}
					break;
				}
			}
			if(!exist){
				strcpy(info_jogadores[num_jogadores].id_jogador, r.id_jogador);
				if(r.colocacao == 1) info_jogadores[num_jogadores].vitorias = 1;
				else info_jogadores[num_jogadores].vitorias = 0;
				info_jogadores[num_jogadores].eliminacoes = r.eliminacoes;
				strcpy(info_jogadores[num_jogadores].sobrevivencia, r.sobrevivencia);
				num_jogadores++;
			}
		}
	}

	qsort(info_jogadores, num_jogadores, sizeof(Info_Jogador), qsort_info_jogador);

	Jogador j;
	char chave_jogador[TAM_CHAVE_JOGADORES_IDX];
	bool vencedor = btree_search(chave_jogador, false, info_jogadores[0].id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
	if(!vencedor){
		btree_search(chave_jogador, false, info_jogadores[1].id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
		char num[5];
		strncpy(num, chave_jogador + TAM_ID_JOGADOR - 1, 4);
		num[4] = '\0';
		int rrn_jogador = atoi(num);
		j = recuperar_registro_jogador(rrn_jogador);
		printf(ERRO_JOGADOR_REMOVIDO, premio, j.apelido, info_jogadores[1].vitorias, info_jogadores[1].eliminacoes);
		strcpy(j.premio, data_fim);
		j.saldo += premio;
		escrever_registro_jogador(j, rrn_jogador);
	} else{
		char num[5];
		strncpy(num, chave_jogador + TAM_ID_JOGADOR - 1, 4);
		num[4] = '\0';
		int rrn_jogador = atoi(num);
		j = recuperar_registro_jogador(rrn_jogador);
		printf(CONCEDER_PREMIO, j.apelido, info_jogadores[0].vitorias, info_jogadores[0].eliminacoes, premio);
		strcpy(j.premio, data_fim);
		j.saldo += premio;
		escrever_registro_jogador(j, rrn_jogador);
	}
}


/* Busca */
void buscar_jogador_id_menu(char *id_jogador) {
	char str[TAM_CHAVE_JOGADORES_IDX];
	memset (str, 0, TAM_CHAVE_JOGADORES_IDX);
	
	printf (REGS_PERCORRIDOS);
    bool found = btree_search(str, true, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
	printf ("\n");
	
    if (!found)
        printf(ERRO_REGISTRO_NAO_ENCONTRADO);
    else {
		char num[5];
		memset (num, 0, 5);
		memcpy (num, str+TAM_ID_JOGADOR-1, 4);
		
        exibir_jogador(strtol (num, NULL, 10));
	}
}


void buscar_kit_id_menu(char *id_kit) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_KITS_IDX];
	memset(str, 0, TAM_CHAVE_KITS_IDX);

	printf(REGS_PERCORRIDOS);
	bool found = btree_search(str, true, id_kit, kits_idx.rrn_raiz, &kits_idx);
	printf("\n");

	if(!found){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	} else{
		char num[5];
		memset(num, 0, 5);
		memcpy(num, str + TAM_ID_KIT - 1, 4);

		exibir_kit(strtol(num, NULL, 10));
	}
}


void buscar_partida_id_menu(char *id_partida) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char str[TAM_CHAVE_PARTIDAS_IDX];
	memset(str, 0, TAM_CHAVE_PARTIDAS_IDX);

	printf(REGS_PERCORRIDOS);
	bool found = btree_search(str, true, id_partida, partidas_idx.rrn_raiz, &partidas_idx);
	printf("\n");
	
	if(!found){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
	} else{
		char num[5];
		memset(num, 0, 5);
		memcpy(num, str + TAM_ID_PARTIDA - 1, 4);
		
		exibir_partida(strtol(num, NULL, 10));
	}
}


/* Listagem */
void listar_jogadores_id_menu() {
	if (qtd_registros_jogadores == 0)
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	else
		btree_print_in_order(NULL, NULL, exibir_btree_jogadores, jogadores_idx.rrn_raiz, &jogadores_idx);
}


void listar_jogadores_kits_menu(char *kit){
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_jogadores == 0){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	} else{
		char kit_reg[TAM_MAX_NOME_KIT];
		strcpy(kit_reg, strupr(kit));

		int prim_indice = -1;
		if(!inverted_list_secondary_search(&prim_indice, false, kit_reg, &jogador_kits_idx)){
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			return;
		}
		if(prim_indice == -1){
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			return;
		}

		char jogadores_registrados[qtd_registros_jogadores + 1][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX];
		int qtd = inverted_list_primary_search(jogadores_registrados, true, prim_indice, NULL, &jogador_kits_idx);
		if(qtd == 0){
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			return;
		}

		jogadores_registrados[qtd_registros_jogadores][0] = '\0';

		qsort(jogadores_registrados, qtd, TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX, order_jogadores_idx);

		for(int i = 0; i < qtd; ++i){
			char id_jogador[TAM_ID_JOGADOR + 1];
			strncpy(id_jogador, jogadores_registrados[i], TAM_ID_JOGADOR - 1);
			id_jogador[TAM_ID_JOGADOR] = '\0';
			char jogador_reg[TAM_CHAVE_JOGADORES_IDX];
			btree_search(jogador_reg, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
			char num[5];
			memset(num, 0, 5);
			memcpy(num, jogador_reg + TAM_ID_JOGADOR - 1, 4);
			exibir_jogador(strtol(num, NULL, 10));
		}
	}
}


void listar_kits_compra_menu(char *id_jogador) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_kits == 0){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	} else{
		char jogador[TAM_CHAVE_JOGADORES_IDX]; 
		bool found = btree_search(NULL, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);
		if(!found){
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}
		
		char aux[5];
		strncpy(aux, jogador + TAM_ID_JOGADOR - 1, TAM_RRN_REGISTRO);
		aux[5] = '\0';
		int rrn = atoi(aux);

		Jogador j = recuperar_registro_jogador(rrn);

		char preco[TAM_FLOAT_NUMBER];
		snprintf(preco, sizeof(preco), "%013.2lf", j.saldo);
		
		btree_print_in_order(NULL, preco, exibir_btree_preco_kit, preco_kit_idx.rrn_raiz, &preco_kit_idx);
	}
}


void listar_partidas_periodo_menu(char *data_inicio, char *data_fim) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_partidas == 0){
		printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
	} else{
		btree_print_in_order(data_inicio, data_fim, exibir_btree_data_partida, data_partida_idx.rrn_raiz, &data_partida_idx);
	}
}


/* Imprimir arquivos de dados */
void imprimir_arquivo_jogadores_menu() {
	if (qtd_registros_jogadores == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_JOGADORES);
}


void imprimir_arquivo_kits_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_kits == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_KITS);
	}
}


void imprimir_arquivo_partidas_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_partidas == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_PARTIDAS);
	}
}


void imprimir_arquivo_resultados_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_resultados == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_RESULTADOS);
	}
}


/* Imprimir índices primários */
void imprimir_jogadores_idx_menu() {
	if (jogadores_idx.qtd_nos == 0)
		printf(ERRO_ARQUIVO_VAZIO);
	else
		printf("%s\n", ARQUIVO_JOGADORES_IDX);
}


void imprimir_kits_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(kits_idx.qtd_nos == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_KITS_IDX);
	}
}


void imprimir_partidas_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(partidas_idx.qtd_nos == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_PARTIDAS_IDX);
	}
}


void imprimir_resultados_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(resultados_idx.qtd_nos == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_RESULTADOS_IDX);
	}
}


/* Imprimir índices secundários */
void imprimir_preco_kit_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(preco_kit_idx.qtd_nos == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_PRECO_KIT_IDX);
	}
}


void imprimir_data_partida_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(data_partida_idx.qtd_nos == 0){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", ARQUIVO_DATA_PARTIDA_IDX);
	}
}


void imprimir_jogador_kits_secundario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(jogador_kits_idx.qtd_registros_secundario == 0 || jogador_kits_idx.arquivo_secundario == NULL){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", jogador_kits_idx.arquivo_secundario);
	}
}


void imprimir_jogador_kits_primario_idx_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(jogador_kits_idx.qtd_registros_primario == 0 || jogador_kits_idx.arquivo_primario == NULL){
		printf(ERRO_ARQUIVO_VAZIO);
	} else{
		printf("%s\n", jogador_kits_idx.arquivo_primario);
	}
}


/* Liberar espaço */
void liberar_espaco_menu() {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(qtd_registros_jogadores == 0){
		printf(ERRO_ARQUIVO_VAZIO);
		return;
	}

	char temp[qtd_registros_jogadores * TAM_REGISTRO_JOGADOR + 1];
	temp[0] = '\0';
	int nova_qtd = 0;

	jogadores_idx.qtd_nos = 0;
	jogadores_idx.rrn_raiz = -1;

	int tam = btree_register_size(&jogadores_idx);
	int j = strlen(jogadores_idx.arquivo);
	for(;j >= 0; j -= tam) jogadores_idx.arquivo[j] = '\0';
	
	

	for(unsigned i = 0; i < qtd_registros_jogadores; ++i){
		char data[TAM_REGISTRO_JOGADOR + 1];
		strncpy(data, ARQUIVO_JOGADORES + i * TAM_REGISTRO_JOGADOR, TAM_REGISTRO_JOGADOR);
		data[TAM_REGISTRO_JOGADOR] = '\0';

		if(data[0] == '*' && data[1] == '|') continue;
		
		strcat(temp, data);
		nova_qtd++;
	}

	strcpy(ARQUIVO_JOGADORES, temp);

	qtd_registros_jogadores = nova_qtd;

	for(unsigned i = 0; i < qtd_registros_jogadores; ++i){
		char id_jogador[TAM_ID_JOGADOR];
		strncpy(id_jogador, ARQUIVO_JOGADORES + i * TAM_REGISTRO_JOGADOR, TAM_ID_JOGADOR - 1);
		id_jogador[TAM_ID_JOGADOR - 1] = '\0';

		char key[TAM_CHAVE_JOGADORES_IDX + 1];
		snprintf(key, sizeof(key), "%s%04d", id_jogador, i);
		key[TAM_CHAVE_JOGADORES_IDX] = '\0';
		
		btree_insert(key, &jogadores_idx);
	}

	printf(SUCESSO);
}

/* Funções de busca binária */

/**
 * Função Genérica de busca binária, que aceita parâmetros genéricos (assinatura baseada na função bsearch da biblioteca C).
 *
 * @param key Chave de busca genérica.
 * @param base0 Base onde ocorrerá a busca, por exemplo, um ponteiro para um vetor.
 * @param nmemb Número de elementos na base.
 * @param size Tamanho do tipo do elemento na base, dica: utilize a função sizeof().
 * @param compar Ponteiro para a função que será utilizada nas comparações.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso. Se true, imprime as posições avaliadas durante a busca, até que todas sejam visitadas ou o elemento seja encontrado (pela 1a vez).
 *                       Caso o número de elementos seja par (p.ex, 10 elementos), então há 2 (duas) possibilidades para a posição da mediana dos elementos (p.ex., 5a ou 6a posição se o total fosse 10).
 *                       Neste caso, SEMPRE escolha a posição mais à direita (p.ex., a posição 6 caso o total for 10).
 * @param posicao_caso_repetido Caso o elemento seja encontrado, se houver mais do que 1 ocorrência, indica qual deve ser retornada. As opções são:
 *                     -1 = primeira : retorna a PRIMEIRA ocorrência (posição mais à esquerda).
 *                      0 = meio : retorna a ocorrência do MEIO (posição central). [modo padrão]
 *                     +1 = ultima : retorna a ÚLTIMA ocorrência (posição mais à direita).
 * @param retorno_se_nao_encontrado Caso o elemento NÃO seja encontrado, indica qual valor deve ser retornado. As opções são:
 *                     -1 = predecessor : retorna o elemento PREDECESSOR (o que apareceria imediatamente antes do elemento procurado, caso fosse encontrado).
 *                      0 = nulo : retorna NULL. [modo padrão]
 *                     +1 = sucessor : retorna o elemento SUCESSOR (o que apareceria imediatamente depois do elemento procurado, caso fosse encontrado).
 * @return Retorna o elemento encontrado ou NULL se não encontrou.
 */
int busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int inicio = 0, fim = nmemb - 1, meio, cmp;
	if(exibir_caminho) printf(REGS_PERCORRIDOS);
	while(inicio <= fim){
		meio = (inicio + fim + 1)/2;
		cmp = compar(key, base0 + meio * size);
		
		if(exibir_caminho) printf(" %d", meio);
		if(cmp == 0){
			if(exibir_caminho) printf("\n");
			if(posicao_caso_repetido == 0) {
				return meio;
			} else {
				int i = meio;
				if(posicao_caso_repetido > 0) 
					while(i < nmemb - 1 && compar(key, base0 + (i + 1) * size) == 0) i++;
				else 
					while(i > 0 && compar(key, base0 + (i - 1) * size) == 0) i--;

				return i;
			}
		} else if(cmp < 0)
			fim = meio - 1;
		else 
			inicio = meio + 1;
	}
	if(exibir_caminho) printf("\n");
	if(retorno_se_nao_encontrado > 0){
		if(cmp > 0){ 
			if(meio == nmemb - 1) return -1;
			else return meio + 1;
		} else{
			return meio;
		}
	}
	else if(retorno_se_nao_encontrado < 0){
		if(cmp < 0){
			if(meio == 0) return -1;
			else return meio - 1;
		} else{
			return meio;
		}
	}

	return -1;
}


int busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
	return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
}

/* Funções de manipulação de Lista Invertida */

/* Funções de manipulação de Lista Invertida */
/**
 * Responsável por inserir duas chaves (chave_secundaria e chave_primaria) em uma Lista Invertida (t).<br />
 * Atualiza os parâmetros dos índices primário e secundário conforme necessário.<br />
 * As chaves a serem inseridas devem estar no formato correto e com tamanho t->tam_chave_primario e t->tam_chave_secundario.<br />
 * O funcionamento deve ser genérico para qualquer Lista Invertida, adaptando-se para os diferentes parâmetros presentes em seus structs.<br />
 *
 * @param chave_secundaria Chave a ser buscada (caso exista) ou inserida (caso não exista) no registro secundário da Lista Invertida.
 * @param chave_primaria Chave a ser inserida no registro primário da Lista Invertida.
 * @param t Ponteiro para a Lista Invertida na qual serão inseridas as chaves.
 */
void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int indice;
	char aux_kit[t->tam_chave_secundaria];
	strcpy(aux_kit, strupr(chave_secundaria));

	if(!inverted_list_secondary_search(&indice, false, aux_kit, t)){
		strncpy(t->arquivo_secundario + t->qtd_registros_secundario * (t->tam_chave_secundaria + 4), aux_kit, t->tam_chave_secundaria);
		strpadright(t->arquivo_secundario + t->qtd_registros_secundario * (t->tam_chave_secundaria + 4), '#', t->tam_chave_secundaria);
		
		char aux[5];
		sprintf(aux, "%04d", t->qtd_registros_primario);
		strncpy(t->arquivo_secundario + t->qtd_registros_secundario * (t->tam_chave_secundaria + 4) + t->tam_chave_secundaria, aux, 4);
		t->qtd_registros_secundario++;

		sprintf(t->arquivo_primario + t->qtd_registros_primario * (t->tam_chave_primaria + 4), "%s%04d", chave_primaria, -1);
		t->qtd_registros_primario++;

		qsort(t->arquivo_secundario, t->qtd_registros_secundario, t->tam_chave_secundaria + 4, t->compar);

	} else{
		int indice_final;
		inverted_list_primary_search(NULL, false, indice, &indice_final, t);
		
		char aux[5];
		sprintf(aux, "%04u", t->qtd_registros_primario);
		strncpy(t->arquivo_primario + indice_final * (t->tam_chave_primaria + 4) + t->tam_chave_primaria, aux, 4);
		sprintf(t->arquivo_primario + t->qtd_registros_primario * (t->tam_chave_primaria + 4), "%s%04d", chave_primaria, -1);
		
		t->qtd_registros_primario++;
	}
}


/**
 * Responsável por buscar uma chave no índice secundário de uma Lista invertida (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice inicial das chaves no registro primário.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, false, nome, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = inverted_list_secondary_search(NULL, false, nome, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse no caminho feito para encontrar a chave.<br />
 * ...<br />
 * int result;<br />
 * bool found = inverted_list_secondary_search(&result, true, nome, &jogador_kits_idx);<br />
 * </code>
 *
 * @param result Ponteiro para ser escrito o índice inicial (primeira ocorrência) das chaves do registro primário. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave_secundaria Chave a ser buscada.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	return inverted_list_binary_search(result, exibir_caminho, chave_secundaria, t);
}


/**
 * Responsável por percorrer o índice primário de uma Lista invertida (T). O valor de retorno indica a quantidade de chaves encontradas.
 * O ponteiro para o vetor de strings result pode ser fornecido opcionalmente, e será populado com a lista de todas as chaves encontradas.
 * O ponteiro para o inteiro indice_final também pode ser fornecido opcionalmente, e deve conter o índice do último campo da lista encadeada
 * da chave primaria fornecida (isso é útil na inserção de um novo registro).<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. As chaves encontradas deverão ser retornadas e tanto o caminho quanto o indice_final não devem ser informados.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, false, indice, NULL, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse nas chaves encontradas, apenas no indice_final, e o caminho não deve ser informado.<br />
 * ...<br />
 * int indice_final;
 * int qtd = inverted_list_primary_search(NULL, false, indice, &indice_final, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 3. Há interesse nas chaves encontradas e no caminho feito.<br />
 * ...<br />
 * char chaves[TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX][MAX_REGISTROS];<br />
 * int qtd = inverted_list_primary_search(chaves, true, indice, NULL, &jogador_kits_idx);<br />
 * ...<br />
 * <br />
 * </code>
 *
 * @param result Ponteiro para serem escritas as chaves encontradas. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param indice Índice do primeiro registro da lista encadeada a ser procurado.
 * @param indice_final Ponteiro para ser escrito o índice do último registro encontrado (cujo campo indice é -1). É ignorado caso NULL.
 * @param t Ponteiro para o índice do tipo Lista invertida no qual será buscada a chave.
 * @return Indica a quantidade de chaves encontradas.
 */
int inverted_list_primary_search(char result[][TAM_CHAVE_JOGADOR_KIT_PRIMARIO_IDX], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(exibir_caminho) printf(REGS_PERCORRIDOS);
	int qtd = 0;
	while(indice != -1){
		if(exibir_caminho) printf(" %d", indice);
		if(indice_final != NULL) *indice_final = indice;
		if(result != NULL) strncpy(result[qtd], t->arquivo_primario + indice * (t->tam_chave_primaria + 4), t->tam_chave_primaria);
		char aux[5];
		strncpy(aux, t->arquivo_primario + indice * (t->tam_chave_primaria + 4) + t->tam_chave_primaria, 4);
		aux[4] = '\0';
		indice = atoi(aux);
		qtd++;
	}
	if(result != NULL) result[qtd][0] = '\0';
	if(exibir_caminho) printf("\n");
	return qtd;
}


/**
 * Responsável por buscar uma chave (k) dentre os registros secundários de uma Lista Invertida de forma eficiente.<br />
 * O valor de retorno deve indicar se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e conterá o índice no registro secundário da chave encontrada.<br />
 *
 * @param result Ponteiro para ser escrito o índice nos registros secundários da chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Lista Invertida.
 * @param t Ponteiro para o índice da Lista Invertida no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool inverted_list_binary_search(int* result, bool exibir_caminho, char *chave, inverted_list *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	char aux[t->tam_chave_secundaria + 1];
	strncpy(aux, chave, t->tam_chave_secundaria);
	strpadright(aux, '#', t->tam_chave_secundaria);

	if(exibir_caminho) printf(REGS_PERCORRIDOS);
	int indice = busca_binaria(aux, t->arquivo_secundario, t->qtd_registros_secundario, t->tam_chave_secundaria + 4, t->compar, exibir_caminho, 0);
	if(indice == -1) return false;
	
	if(result != NULL){
		char num[5];
		strncpy(num, t->arquivo_secundario + indice * (t->tam_chave_secundaria + 4) + t->tam_chave_secundaria, 4);
		num[4] = '\0';
		*result = atoi(num);
	}

	return true;
}


/* Funções de manipulação de Árvores-B */

/**
 * Responsável por inserir uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * A chave a ser inserida deve estar no formato correto e com tamanho t->tam_chave.<br />
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * ...<br />
 * char jogador_str[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * sprintf(jogador_str, "%s%04d", id_jogador, rrn_jogador);<br />
 * btree_insert(jogador_str, &jogadores_idx);<br />
 * ...<br />
 * </code>
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 */
void btree_insert(char *chave, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// A estrutura da função foi baseada no código Algoritmo 4 INSERE (T, k) do pdf fornecido
	if(t->qtd_nos == 0){
		btree_node node = btree_node_malloc(t);
		strcpy(node.chaves[0], chave);
		t->rrn_raiz = node.this_rrn;
		t->qtd_nos++;
		node.qtd_chaves++;
		btree_write(node, t);
	} else{
		promovido_aux p = btree_insert_aux(chave, t->rrn_raiz, t);
		if(p.chave_promovida[0] != '\0'){
			btree_node raiz = btree_node_malloc(t);
			raiz.folha = false;  
			raiz.qtd_chaves = 1;
			strncpy(raiz.chaves[0], p.chave_promovida, t->tam_chave);
			raiz.filhos[0] = t->rrn_raiz;
			raiz.filhos[1] = p.filho_direito;
			t->rrn_raiz = raiz.this_rrn;
			t->qtd_nos++;
			btree_write(raiz, t);
		}
	}
}


/**
 * Função auxiliar de inserção de uma chave (k) em uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.<br />
 *
 * @param chave Chave a ser inserida na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_insert_aux(char *chave, int rrn, btree *t) {
	promovido_aux p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	// A estrutura da função foi baseada no código Algoritmo 3 INSERE_AUX (T, k) do pdf fornecido
	p.chave_promovida[0] = '\0';
	p.filho_direito = -1;
	btree_node node = btree_read(rrn, t);
	int indice_filho = -1;
	bool found = btree_binary_search(&indice_filho, false, chave, &node, t);
	if(found) indice_filho++;

	if(node.folha){
		if(node.qtd_chaves < btree_order - 1){
			int i = node.qtd_chaves;
			while(i > 0 && strcmp(chave, node.chaves[i - 1]) < 0) i--;
			for(int j = node.qtd_chaves; j > i; j--)
				strncpy(node.chaves[j], node.chaves[j - 1], t->tam_chave);
			
			strncpy(node.chaves[i], chave, t->tam_chave);
            node.qtd_chaves++;
			
			btree_write(node, t);
			return p;
		} else{
			strncpy(p.chave_promovida, chave, t->tam_chave);
			return btree_divide(p, &node, indice_filho, t);
		}  
	} else{
		p = btree_insert_aux(chave, node.filhos[indice_filho], t);
		if(p.chave_promovida[0] == '\0') return p;
		if(node.qtd_chaves < btree_order - 1){
			int i = node.qtd_chaves;
			while(i > 0 && strcmp(p.chave_promovida, node.chaves[i - 1]) < 0) i--;
			for (int j = node.qtd_chaves; j > i; --j)
				strncpy(node.chaves[j], node.chaves[j - 1], t->tam_chave);
			
			node.qtd_chaves++;
			for (int j = node.qtd_chaves; j > i + 1; --j)
				node.filhos[j] = node.filhos[j - 1];
			
			
			strncpy(node.chaves[i], p.chave_promovida, t->tam_chave);
			node.filhos[i + 1] = p.filho_direito;
			
			p.chave_promovida[0] = '\0';
			btree_write(node, t);
			return p;
		} else{
			return btree_divide(p, &node, indice_filho, t);
		}
	}
}


/**
 * Função auxiliar para dividir um nó de uma Árvore-B (T). Atualiza os parâmetros conforme necessário.<br />
 *
 * @param promo Uma struct do tipo promovido_aux que contém a chave a ser inserida e o RRN do seu filho direito.
 * @param node Ponteiro para nó que deve ser dividido. 
 * @param i O índice da posição onde a chave a ser inserida deve estar.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Retorna uma struct do tipo promovido_aux que contém a chave promovida e o RRN do filho direito.
 */
promovido_aux btree_divide(promovido_aux promo, btree_node *node, int i, btree *t) {
	promovido_aux p;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	p.chave_promovida[0] = '\0';
	p.filho_direito = -1;
	btree_node novo_no = btree_node_malloc(t);
	novo_no.folha = node->folha;
	novo_no.qtd_chaves = (btree_order - 1) / 2;
	int j = (btree_order - 1) / 2;

	if(i != (btree_order - 1) / 2){
		char aux[t->tam_chave];
		if(i < (btree_order - 1) / 2){
			strncpy(aux, promo.chave_promovida, t->tam_chave);
			for(j = j - 1; j >= i; j--){
				strncpy(promo.chave_promovida, node->chaves[j], t->tam_chave);
				strncpy(node->chaves[j], aux, t->tam_chave);
				strncpy(aux, promo.chave_promovida, t->tam_chave);
			}
			strncpy(promo.chave_promovida, aux, t->tam_chave);
		} else if(i > (btree_order - 1) / 2){
			strncpy(aux, promo.chave_promovida, t->tam_chave);
			for(; j < i; j++){
				strncpy(promo.chave_promovida, node->chaves[j], t->tam_chave);
				strncpy(node->chaves[j], aux, t->tam_chave);
				strncpy(aux, promo.chave_promovida, t->tam_chave);
			}
			strncpy(promo.chave_promovida, aux, t->tam_chave);
		}
	}


	for(int j = 0; j < novo_no.qtd_chaves; j++){
		strncpy(novo_no.chaves[j], node->chaves[j + (btree_order - 1) / 2], t->tam_chave);
		node->chaves[j + (btree_order - 1) / 2][0] = '\0';
	}
	
	if(!node->folha){
		int vetor_filhos[btree_order + 1];
		memset(vetor_filhos, -1, sizeof(vetor_filhos));
		vetor_filhos[i + 1] = promo.filho_direito;
		bool inseriu = false;
		for(int j = 0; j < btree_order; j++){
			if(vetor_filhos[j] != -1 || inseriu){
				vetor_filhos[j + 1] = node->filhos[j];
				inseriu = true;
			} else{
				vetor_filhos[j] = node->filhos[j];
			}
		}
		for(int j = 0; j <= (btree_order - 1) / 2; j++){
			node->filhos[j] = vetor_filhos[j];
		}
		node->filhos[(btree_order - 1) / 2 + 1] = -1;
		for(int j = 0; j <= novo_no.qtd_chaves; j++){
			novo_no.filhos[j] = vetor_filhos[j + (btree_order - 1) / 2 + 1];
		}
	}

	node->qtd_chaves = (btree_order - 1) / 2;

	strncpy(p.chave_promovida, promo.chave_promovida, t->tam_chave);
	p.filho_direito = novo_no.this_rrn;
	
	t->qtd_nos++;
	btree_write(novo_no, t);
	btree_write(*node, t);

	return p;
}


/**
 * Responsável por remover uma chave (k) de uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * A chave a ser removida deve estar no formato correto e com tamanho t->tam_chave.<br />
 * O funcionamento deve ser genérico para qualquer Árvore-B, considerando que os únicos parâmetros que se alteram entre
 * as árvores é o t->tam_chave.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * ...<br />
 * char jogador_str[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * sprintf(jogador_str, "%s%04d", id_jogador, rrn_jogador);<br />
 * btree_delete(jogador_str, &jogadores_idx);<br />
 * ...<br />
 * </code>
 *
 * @param chave Chave a ser removida da Árvore-B.
 * @param t Ponteiro para o índice do tipo Árvore-B do qual será removida a chave.
 */
void btree_delete(char *chave, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(t->rrn_raiz == -1){
		printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		return;
	}

	if(btree_delete_aux(chave, t->rrn_raiz, t)){
		btree_node root = btree_read(t->rrn_raiz, t);

		if(root.qtd_chaves == 0){
			if(root.folha) t->rrn_raiz = -1;
			else t->rrn_raiz = root.filhos[0];
			
			btree_node_free(root);
		}
	}
}


/**
 * Função auxiliar de remoção de uma chave (k) de uma Árvore-B (T). Atualiza os parâmetros da Árvore-B conforme necessário.<br />
 * Esta é uma função recursiva. Ela recebe o RRN do nó a ser trabalhado sobre.<br />
 *
 * @param chave Chave a ser removida da Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B do qual será removida a chave.
 * @return Indica se a remoção deixou o nó que foi processado com menos chaves que o mínimo necessário.
 */
bool btree_delete_aux(char *chave, int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	btree_node node = btree_read(rrn, t);
    int pos;
    bool found = btree_binary_search(&pos, false, chave, &node, t);

    if (found) {	
        if (node.folha) {
            for (int i = pos; i < node.qtd_chaves - 1; i++) {
                strncpy(node.chaves[i], node.chaves[i + 1], t->tam_chave);
            }
            node.qtd_chaves--;
			node.chaves[node.qtd_chaves][0] = '\0';
			
        } else {
            btree_node predecessor = btree_read(node.filhos[pos], t);

			while (!predecessor.folha) 
				predecessor = btree_read(predecessor.filhos[predecessor.qtd_chaves], t);
			
            if (predecessor.qtd_chaves >= (btree_order - 1) / 2) {
                char predecessor_key[t->tam_chave + 1];
                strcpy(predecessor_key, predecessor.chaves[predecessor.qtd_chaves - 1]);
				strncpy(node.chaves[pos], predecessor_key, t->tam_chave);
                if(btree_delete_aux(predecessor_key, node.filhos[pos], t))
					btree_borrow_or_merge(&node, pos, t);
				
            } else {
                btree_node successor = btree_read(node.filhos[pos + 1], t);

				while (!successor.folha) 
					successor = btree_read(successor.filhos[0], t);
				
                if (successor.qtd_chaves >= (btree_order - 1) / 2) {
                    char successor_key[t->tam_chave + 1];
                    strcpy(successor_key, successor.chaves[0]);
					strncpy(node.chaves[pos], successor_key, t->tam_chave); 

                    if(btree_delete_aux(successor_key, node.filhos[pos + 1], t))
						btree_borrow_or_merge(&node, pos + 1, t);
                    
                } else {
                    btree_borrow_or_merge(&node, pos, t);
                    btree_delete_aux(chave, node.filhos[pos], t);
                }
            }
        }
    } else if (!node.folha) {
        if (btree_delete_aux(chave, node.filhos[pos], t))
            return btree_borrow_or_merge(&node, pos, t);
        	
    } else {
        btree_node_free(node);
        return false;
    }

    btree_write(node, t);

	bool underflow = node.qtd_chaves < (btree_order - 1) / 2;

    btree_node_free(node);
    return underflow;
}


/**
 * Função auxiliar para redistribuir ou concatenar nós irmãos adjacentes à esquerda e à direita de um nó pai em uma Árvore-B (T). 
 * Atualiza os parâmetros conforme necessário.<br />
 *
 * @param node Ponteiro para nó pai dos nós irmãos adjacentes que deve ser redistribuidos ou concatenados. 
 * @param i O índice da posição no nó pai onde se encontra a chave separadora dos nós irmãos adjacentes.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual serão redistribuídos ou concatenados os nós irmãos adjacentes.
 * @return Indica se a redistribuição ou concatenação deixou o nó pai com menos chaves que o mínimo necessário.
 */
bool btree_borrow_or_merge(btree_node *node, int i, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	btree_node left_sibling, right_sibling, child = btree_read(node->filhos[i], t);

    if (i < node->qtd_chaves) {
        right_sibling = btree_read(node->filhos[i + 1], t);

        if (right_sibling.qtd_chaves > (btree_order - 1) / 2) {
            strncpy(child.chaves[child.qtd_chaves], node->chaves[i], t->tam_chave);
            strncpy(node->chaves[i], right_sibling.chaves[0], t->tam_chave);
            for (int j = 0; j < right_sibling.qtd_chaves - 1; j++)
                strncpy(right_sibling.chaves[j], right_sibling.chaves[j + 1], t->tam_chave);
            
			right_sibling.chaves[right_sibling.qtd_chaves - 1][0] = '\0';
            child.qtd_chaves++;
            right_sibling.qtd_chaves--;

			child.filhos[child.qtd_chaves] = right_sibling.filhos[0];

			for(int j = 0; j < right_sibling.qtd_chaves + 1; j++)
				right_sibling.filhos[j] = right_sibling.filhos[j + 1];
			
			right_sibling.filhos[right_sibling.qtd_chaves + 1] = -1;

            btree_write(right_sibling, t);
            btree_write(child, t);
			btree_write(*node, t);

			btree_node_free(right_sibling);
			btree_node_free(child);
            
            return false;
        }
    }

    if (i > 0) {
        left_sibling = btree_read(node->filhos[i - 1], t);

        if (left_sibling.qtd_chaves > (btree_order - 1) / 2) {
            for (int j = child.qtd_chaves; j > 0; j--)
                strncpy(child.chaves[j], child.chaves[j - 1], t->tam_chave);
            
            strncpy(child.chaves[0], node->chaves[i - 1], t->tam_chave);
            strncpy(node->chaves[i - 1], left_sibling.chaves[left_sibling.qtd_chaves - 1], t->tam_chave);
			left_sibling.chaves[left_sibling.qtd_chaves - 1][0] = '\0';
            child.qtd_chaves++;
            left_sibling.qtd_chaves--;

			child.filhos[child.qtd_chaves] = left_sibling.filhos[left_sibling.qtd_chaves + 1];
			
			for(int j = left_sibling.qtd_chaves; j > 0; j--)
				left_sibling.filhos[j] = left_sibling.filhos[j - 1];
			
			left_sibling.filhos[left_sibling.qtd_chaves + 1] = -1;

            btree_write(left_sibling, t);
            btree_write(child, t);
			btree_write(*node, t);
			
        	btree_node_free(left_sibling);
			btree_node_free(child);

            return false;
        }
    }

    if (i < node->qtd_chaves) {
		right_sibling = btree_read(node->filhos[i + 1], t);

        strncpy(child.chaves[child.qtd_chaves], node->chaves[i], t->tam_chave);
        strncpy(child.chaves[child.qtd_chaves + 1], right_sibling.chaves[0], t->tam_chave);
        child.qtd_chaves += 2;

		for(int j = 0; j < right_sibling.qtd_chaves; j++)
			strncpy(right_sibling.chaves[j], right_sibling.chaves[j + 1], t->tam_chave);
		
		right_sibling.qtd_chaves--;
		right_sibling.chaves[right_sibling.qtd_chaves][0] = '\0';

		for(int j = 0; j < child.qtd_chaves; j++){
			child.filhos[j + 1] = right_sibling.filhos[j];
			right_sibling.filhos[j] = right_sibling.filhos[j + 1];
		}

		right_sibling.filhos[right_sibling.qtd_chaves] = -1;

		for(int j = i; j < node->qtd_chaves - 1; j++){
			node->filhos[j] = node->filhos[j + 1];
			strncpy(node->chaves[j], node->chaves[j + 1], t->tam_chave);
		}

		node->filhos[node->qtd_chaves] = -1;

        node->qtd_chaves--;
		node->chaves[node->qtd_chaves][0] = '\0';

        btree_write(right_sibling, t);
        btree_node_free(right_sibling);

    } else {
        left_sibling = btree_read(node->filhos[i - 1], t);

        strncpy(left_sibling.chaves[left_sibling.qtd_chaves], node->chaves[i - 1], t->tam_chave);
        for(int j = 0; j < child.qtd_chaves; j++) {
            strncpy(left_sibling.chaves[left_sibling.qtd_chaves + 1 + j], child.chaves[j], t->tam_chave);
        }

        left_sibling.qtd_chaves += child.qtd_chaves + 1;

        for(int j = i - 1; j < node->qtd_chaves - 1; j++) {
            strncpy(node->chaves[j], node->chaves[j + 1], t->tam_chave);
            node->filhos[j] = node->filhos[j + 1];
        }

		left_sibling.filhos[left_sibling.qtd_chaves] = child.filhos[child.qtd_chaves];

        node->qtd_chaves--;
		node->chaves[node->qtd_chaves][0] = '\0';
		child.chaves[child.qtd_chaves][0] = '\0';

		for(int j = 0; j <= child.qtd_chaves; j++)
			child.filhos[j] = child.filhos[j + 1];
		
		child.filhos[child.qtd_chaves] = -1;

		for(int j = node->qtd_chaves + 1; j <= i; j++)
			node->filhos[j] = node->filhos[j - 1];
		
		node->filhos[node->qtd_chaves + 1] = -1;

        btree_write(left_sibling, t);
        btree_node_free(left_sibling);
    }

    btree_write(*node, t);
	btree_write(child, t);

    btree_node_free(child);

	bool underflow = node->qtd_chaves < (btree_order - 1) / 2;
    return underflow;
}


/**
 * Responsável por buscar uma chave (k) em uma Árvore-B (T). O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para a string result pode ser fornecido opcionalmente, e conterá o resultado encontrado.<br />
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo fornecido.<br />
 * Comportamento de acordo com as especificações do PDF sobre Árvores-B e suas operações.<br />
 * <br />
 * Exemplos de uso:<br />
 * <code>
 * // Exemplo 1. A chave encontrada deverá ser retornada e o caminho não deve ser informado.<br />
 * ...<br />
 * char result[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * bool found = btree_search(result, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);<br />
 * ...<br />
 * <br />
 * // Exemplo 2. Não há interesse na chave encontrada, apenas se ela existe, e o caminho não deve ser informado.<br />
 * ...<br />
 * bool found = btree_search(NULL, false, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);<br />
 * ...<br />
 * <br />
* // Exemplo 3. Há interesse no caminho feito para encontrar a chave.<br />
  * ...<br />
 * char result[TAM_CHAVE_JOGADORES_IDX + 1];<br />
 * bool found = btree_search(result, true, id_jogador, jogadores_idx.rrn_raiz, &jogadores_idx);<br />
 * printf("\n");<br />
 * </code>
 *
 * @param result Ponteiro para ser escrita a chave encontrada. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param rrn RRN do nó no qual deverá ser processado. É o RRN da raíz da Árvore-B caso seja a primeira chamada.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_search(char *result, bool exibir_caminho, char *chave, int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(rrn == -1) return false;
	btree_node node = btree_read(rrn, t);
	int posicao;
	if(exibir_caminho) printf(" %d (", rrn);
	bool found = btree_binary_search(&posicao, exibir_caminho, chave, &node, t);
	if(exibir_caminho) printf(")");
	if(found){
		if(result != NULL){
			strncpy(result, node.chaves[posicao], t->tam_chave);
			result[t->tam_chave] = '\0';
		}
		return true;
	}
	if(node.folha) return false;
	return btree_search(result, exibir_caminho, chave, node.filhos[posicao], t);
}


/**
 * Responsável por buscar uma chave (k) dentro do nó de uma Árvore-B (T) de forma eficiente. O valor de retorno indica se a chave foi encontrada ou não.
 * O ponteiro para o int result pode ser fornecido opcionalmente, e indica o índice da chave encontrada (caso tenha sido encontrada) 
 * ou o índice do filho onde esta chave deve estar (caso não tenha sido encontrada).<br />
 *
 * @param result Ponteiro para ser escrito o índice da chave encontrada ou do filho onde ela deve estar. É ignorado caso NULL.
 * @param exibir_caminho Indica se o caminho percorrido deve ser impresso.
 * @param chave Chave a ser buscada na Árvore-B.
 * @param node Ponteiro para o nó onde a busca deve ser feita.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será buscada a chave.
 * @return Indica se a chave foi encontrada.
 */
bool btree_binary_search(int *result, bool exibir_caminho, char* chave, btree_node* node, btree* t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int inicio = 0, fim = node->qtd_chaves - 1;
	int meio = (inicio + fim + 1) / 2;
	int cmp;
	
	if(exibir_caminho) printf("%d", meio);

	while(inicio <= fim){
		cmp = t->compar(chave, node->chaves[meio]);

		if(cmp == 0){
			if(result != NULL) *result = meio;
			return true;
		}
		else if(cmp < 0) fim = meio - 1;
		else inicio = meio + 1;

		meio = (inicio + fim + 1) / 2;
		if(exibir_caminho && inicio <= fim) printf(" %d", meio);
	}

	if(result != NULL) *result = inicio;
	return false;
}


/**
 * Função para percorrer uma Árvore-B (T) em ordem e armazenar as chaves, em result, que estiverem dentro do intervalo fornecido.<br />
 * Os parâmetros chave_inicio e chave_fim podem ser fornecidos opcionalmente, e contém o intervalo do percurso.
 * Caso chave_inicio e chave_fim sejam NULL, o índice inteiro é percorrido.
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo de percursão em ordem.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * // Exemplo 1. Intervalo não especificado.
 * ...<br />
 * bool imprimiu = btree_search_in_order(result, NULL, NULL, 0, jogadores_idx.rrn_raiz, &jogadores_idx);
 * ...<br />
 * <br />
 * // Exemplo 2. Imprime as transações contidas no intervalo especificado.
 * ...<br />
 * bool imprimiu = btree_search_in_order(result, data_inicio, data_fim, 0, data_partida_idx.rrn_raiz, &data_partida_idx);
 * ...<br />
 * </code>
 *
 * @param result Vetor de strings onde serão armazenadas as chaves dos registros válidos.
 * @param chave_inicio Começo do intervalo. É ignorado caso NULL.
 * @param chave_fim Fim do intervalo. É ignorado caso NULL.
 * @param qtd Recebe a quantidade atual de chaves válidas (valor usado para retornar a quantidade com a recursão).
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Indica a quantidade de chaves válidas.
 */
int btree_search_in_order(char **result, char *chave_inicio, char *chave_fim, int qtd, int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(rrn == -1) return qtd;

	btree_node node = btree_read(rrn, t);

	int i;
	if(node.folha){
		for(i = 0; i < node.qtd_chaves; i++){
			if((chave_inicio == NULL || t->compar(node.chaves[i], chave_inicio) >= 0) && (chave_fim == NULL || t->compar(node.chaves[i], chave_fim) <= 0)){
				strncpy(result[qtd], node.chaves[i], t->tam_chave);
				qtd++;
			}
		}
	} else{
		for(i = 0; i < node.qtd_chaves; i++){
			qtd = btree_search_in_order(result, chave_inicio, chave_fim, qtd, node.filhos[i], t);
			if((chave_inicio == NULL || t->compar(node.chaves[i], chave_inicio) >= 0) && (chave_fim == NULL || t->compar(node.chaves[i], chave_fim) <= 0)){
				strncpy(result[qtd], node.chaves[i], t->tam_chave);
				qtd++;
			}
		}
		qtd = btree_search_in_order(result, chave_inicio, chave_fim, qtd, node.filhos[i], t);
	}

	return qtd;
}


/**
 * Função para percorrer uma Árvore-B (T) em ordem.<br />
 * Os parâmetros chave_inicio e chave_fim podem ser fornecidos opcionalmente, e contém o intervalo do percurso.
 * Caso chave_inicio e chave_fim sejam NULL, o índice inteiro é percorrido.
 * Esta é uma função recursiva. O parâmetro rrn recebe a raíz da Árvore-B na primeira chamada, e nas chamadas
 * subsequentes é o RRN do filho de acordo com o algoritmo de percursão em ordem.<br />
 * <br />
 * Exemplo de uso:<br />
 * <code>
 * // Exemplo 1. Intervalo não especificado.
 * ...<br />
 * bool imprimiu = btree_print_in_order(NULL, NULL, exibir_btree_jogadores, jogadores_idx.rrn_raiz, &jogadores_idx);
 * ...<br />
 * <br />
 * // Exemplo 2. Imprime as transações contidas no intervalo especificado.
 * ...<br />
 * bool imprimiu = btree_print_in_order(data_inicio, data_fim, exibir_btree_data_partida, data_partida_idx.rrn_raiz, &data_partida_idx);
 * ...<br />
 * </code>
 *
 * @param chave_inicio Começo do intervalo. É ignorado caso NULL.
 * @param chave_fim Fim do intervalo. É ignorado caso NULL.
 * @param exibir Função utilizada para imprimir uma chave no índice. É informada a chave para a função.
 * @param rrn RRN do nó no qual deverá ser processado.
 * @param t Ponteiro para o índice do tipo Árvore-B no qual será inserida a chave.
 * @return Indica se alguma chave foi impressa.
 */
bool btree_print_in_order(char *chave_inicio, char *chave_fim, bool (*exibir)(char *chave), int rrn, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	if(rrn == -1) return false;

	btree_node node = btree_read(rrn, t);
	bool imprimiu = false;
	
	int i;
	if(node.folha){
		for(i = 0; i < node.qtd_chaves; i++){
			if((chave_inicio == NULL || t->compar(node.chaves[i], chave_inicio) >= 0) && (chave_fim == NULL || t->compar(node.chaves[i], chave_fim) <= 0)){
				imprimiu = true;
				if(!exibir(node.chaves[i])) return false;
			}
		}
	} else{
		for(i = 0; i < node.qtd_chaves; i++){
			btree_print_in_order(chave_inicio, chave_fim, exibir, node.filhos[i], t);
			if((chave_inicio == NULL || t->compar(node.chaves[i], chave_inicio) >= 0) && (chave_fim == NULL || t->compar(node.chaves[i], chave_fim) <= 0)){
				imprimiu = true;
				if(!exibir(node.chaves[i])) return false;
			}
		}
		btree_print_in_order(chave_inicio, chave_fim, exibir, node.filhos[i], t);
	}
	
	return imprimiu;
}


/**
 * Função interna para ler um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser lido da Árvore-B.
 * @param t Árvore-B na qual será feita a leitura do nó.
 */
btree_node btree_read(int rrn, btree *t) {
	btree_node no;
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int offset = btree_register_size(t) * rrn;
	no = btree_node_malloc(t);	
	no.this_rrn = rrn;
	char aux[4];
	strncpy(aux, t->arquivo + offset, 3);
	aux[3] = '\0';
	no.qtd_chaves = atoi(aux);
	offset += 3;
	int i = 0;
	for(; i < no.qtd_chaves; i++){
		strncpy(no.chaves[i], t->arquivo + offset, t->tam_chave);
		offset += t->tam_chave;
	}
	
	if(i < btree_order-1){
		while(i < btree_order-1){
			offset += t->tam_chave;
			i++;
		}
	}

	no.folha = t->arquivo[offset] == 'T' ? true : false;
	offset += 1;	

	if(!no.folha){
		int j = 0;
		for(; j < no.qtd_chaves + 1; j++){
			if(t->arquivo[offset] == '*') break;
			char aux[4];
			strncpy(aux, t->arquivo + offset, 3);
			aux[3] = '\0';
			no.filhos[j] = atoi(aux);
			offset += 3;
		}
	}
	
	return no;
}


/**
 * Função interna para escrever um nó em uma Árvore-B (T).<br />
 *
 * @param no No a ser escrito na Árvore-B.
 * @param t Árvore-B na qual será feita a escrita do nó.
 */
void btree_write(btree_node no, btree *t) {
	/*IMPLEMENTE A FUNÇÃO AQUI*/
	int offset = btree_register_size(t) * no.this_rrn;
	sprintf(t->arquivo + offset, "%03d", no.qtd_chaves);
	offset += 3;
	int i = 0;
	for(; i < no.qtd_chaves; i++){
		strcpy(t->arquivo + offset, no.chaves[i]);
		offset += t->tam_chave;
	}
	if(i < btree_order-1){
		strpadright(t->arquivo + offset, '#', t->tam_chave * (btree_order-1-i));
		offset += (btree_order-1-i) * t->tam_chave;
	}

	if(no.folha) sprintf(t->arquivo + offset, "T");
	else sprintf(t->arquivo + offset, "F");
	offset += 1;

	if(no.folha){
		memset(t->arquivo + offset, '*', 3 * btree_order);
	} else{
		int j = 0;
		for(; j <= no.qtd_chaves; j++){
			if(no.filhos[j] == -1) break;
			char aux[4];
			sprintf(aux, "%03d", no.filhos[j]);
			strncpy(t->arquivo + offset, aux, 3);
			offset += 3;
		}
		memset(t->arquivo + offset, '*', 3 * (btree_order - j));
	}
}

/**
 * Função interna para alocar o espaço necessário dos campos chaves (vetor de strings) e filhos (vetor de inteiros) da struct btree_node.<br />
 *
 * @param t Árvore-B base para o qual será alocado um struct btree_node.
 */
btree_node btree_node_malloc(btree *t) {
	btree_node no;

	no.this_rrn = t->qtd_nos;

	no.qtd_chaves = 0;

	char *aux = malloc (sizeof (char) * (btree_order-1) * (t->tam_chave)); //vetor contíguo para permitir uso de algumas funções da stdlib
	memset (aux, 0, (btree_order-1) * (t->tam_chave));
	no.chaves = malloc (sizeof (void*) * (btree_order-1));
	for (int i = 0; i < btree_order-1; i++) {
		no.chaves[i] = (aux + i * (t->tam_chave));
	}

	no.folha = true;
	no.filhos = malloc (sizeof(int) * btree_order);
	memset (no.filhos, -1, sizeof(int) * btree_order);

	return no;
}


/**
 * Função interna para liberar o espaço alocado pelo btree_node_malloc.<br />
 *
 * @param no Nó para o qual o espaço alocado deverá ser librerado;
 */
void btree_node_free (btree_node no) {
	if (*no.chaves)
		free (*no.chaves);
	if (no.chaves)
		free (no.chaves);
	if (no.filhos)
		free (no.filhos);
}


/**
 * Função interna para calcular o tamanho em bytes de uma Árvore-B.<br />
 *
 * @param t Árvore-B base para o qual será calculado o tamanho.
 */
int btree_register_size(btree *t) {
	int chaves_ordenadas = (btree_order-1)*t->tam_chave;
	return 3 + chaves_ordenadas + 1 + (btree_order*3);
}


/* Funções Auxiliares */

char *strpadright(char *str, char pad, unsigned size){
	for (unsigned i = strlen(str); i < size; ++i)
		str[i] = pad;
	str[size] = '\0';
	return str;
}

char *strupr(char *str){
	for (char *p = str; *p; ++p)
		*p = toupper(*p);
	return str;
}

char *strlower(char *str){
	for (char *p = str; *p; ++p)
		*p = tolower(*p);
	return str;
}
