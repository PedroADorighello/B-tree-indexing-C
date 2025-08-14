#!/bin/bash

# Nome do arquivo-fonte em C
SOURCE="ORI_T02.c"
EXECUTABLE="ORI_T02"

# Diretórios para entradas, saídas esperadas e resultados
INPUT_DIR="./in"
OUTPUT_DIR="./out"
RESULTS_DIR="./results"

# Compila o programa
echo "Compilando $SOURCE..."
gcc -o $EXECUTABLE $SOURCE
if [ $? -ne 0 ]; then
    echo "Erro na compilação. Verifique o código."
    exit 1
fi

# Cria o diretório de resultados se não existir
mkdir -p $RESULTS_DIR

# Verifica se índices específicos foram fornecidos como parâmetros
if [ $# -eq 0 ]; then
    echo "Nenhum índice especificado. Por favor, forneça os índices dos arquivos para teste. Exemplo:"
    echo "./test.sh 1 3 6"
    exit 1
fi

# Loop pelos índices fornecidos
for i in "$@"; do
    INPUT_FILE="$INPUT_DIR/input$i.txt"
    EXPECTED_OUTPUT_FILE="$OUTPUT_DIR/output$i.txt"
    GENERATED_OUTPUT_FILE="$RESULTS_DIR/temp_output$i.txt"
    RESULT_FILE="$RESULTS_DIR/resultados$i.txt"

    # Verifica se os arquivos de entrada e saída esperada existem
    if [ ! -f $INPUT_FILE ] || [ ! -f $EXPECTED_OUTPUT_FILE ]; then
        echo "Arquivo $INPUT_FILE ou $EXPECTED_OUTPUT_FILE não encontrado. Pulando teste $i."
        continue
    fi

    # Executa o programa com o arquivo de entrada
    echo "Testando com $INPUT_FILE..."
    ./$EXECUTABLE < $INPUT_FILE > $GENERATED_OUTPUT_FILE

    # Compara a saída gerada com a saída esperada
    if diff -q $GENERATED_OUTPUT_FILE $EXPECTED_OUTPUT_FILE > /dev/null; then
        echo "Input$i: Saída correta!" > $RESULT_FILE
    else
        echo "Input$i: Saída incorreta." > $RESULT_FILE
        # Mostra a saída completa gerada pelo programa
        echo "Saída completa gerada pelo programa:" >> $RESULT_FILE
        echo "" >> $RESULT_FILE
        cat $GENERATED_OUTPUT_FILE >> $RESULT_FILE
        echo "" >> $RESULT_FILE
        echo "Linhas divergentes entre saída esperada e saída gerada:" >> $RESULT_FILE
        diff $EXPECTED_OUTPUT_FILE $GENERATED_OUTPUT_FILE >> $RESULT_FILE
    fi

    # Remove o arquivo temporário
    rm -f $GENERATED_OUTPUT_FILE
done

echo "Testes concluídos. Verifique os arquivos em $RESULTS_DIR."
