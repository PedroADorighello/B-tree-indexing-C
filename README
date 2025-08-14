# Sistema de Indexação com Árvore-B em C

## Descrição do Projeto
Este projeto implementa um **sistema de indexação utilizando Árvore-B** para otimizar o gerenciamento de grandes volumes de dados em um **suposto** jogo chamado **UFSCraft**.

O UFSCraft tornou-se extremamente popular, resultando em um aumento massivo no número de:
- Jogadores
- Kits
- Partidas
- Resultados

Com esse crescimento, os **índices simples** (listas ordenadas) utilizados anteriormente passaram a apresentar problemas de desempenho:
- Lentidão na manutenção dos índices
- Buscas demoradas por kits
- Listagens excessivamente lentas
- Alto número de acessos ao disco

Para resolver esses problemas, foi adotada a **Árvore-B** como estrutura de dados principal para indexação, garantindo maior eficiência, principalmente para dados que **não cabem inteiramente na memória RAM**.

---

## Objetivo
O objetivo do projeto é substituir os índices simples por uma implementação de **Árvore-B** em C, garantindo:
- **Menor tempo de busca**
- **Menor número de acessos ao disco**
- **Melhor escalabilidade** para grandes volumes de dados

---

## Funcionalidades
- Inserção de registros (jogadores, kits, partidas, resultados)
- Busca eficiente por chave
- Remoção de registros
- Listagem ordenada de elementos
- Armazenamento otimizado para acesso em disco

---

## Estrutura da Árvore-B
A **Árvore-B** é uma estrutura de dados balanceada projetada para **minimizar leituras/escritas em disco**.  
Características principais:
- Cada nó pode ter múltiplas chaves
- Os dados são mantidos ordenados
- Operações de inserção, remoção e busca têm complexidade **O(log n)**
- Reduz a profundidade da árvore, diminuindo acessos ao disco

## Como Compilar e Executar
### 1. Compilar o projeto:
```bash
make
```

### 2. Executar:
```bash
./ufscraft_index
```

## 🧑‍💻 Autor
Desenvolvido como parte do projeto de **Organização e Recuperação da Informação (ORI)**.

=== DESCRIÇÃO DOS ARQUIVOS FORNECIDOS ===

- ORI_T02_HEADER.c: este arquivo deve conter a implementação de todas as funções/operações. *** ESTE É O ÚNICO ARQUIVO QUE DEVE SER EDITADO ***

- ORI_T02_HEADER.h: arquivo de cabeçalho, com constantes, registros, tipos definidos, protótipos e algumas funções. *** ESTE ARQUIVO NÃO DEVE SER ALTERADO ***

- ORI_T02.c: arquivo com a função principal. *** ESTE ARQUIVO NÃO DEVE SER ALTERADO ***

- makefile: script de compilação e geração do executável
