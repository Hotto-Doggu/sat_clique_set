# Implementação em C++ de Três Problemas Clássicos

Este projeto é um trabalho prático para a disciplina de Projeto e Análise de Algoritmos da Universidade Federal de Ouro Preto e implementa três problemas clássicos em C++:

1. **Satisfatibilidade (SAT)**, utilizando backtracking;
2. **Clique Máximo**, por meio de branch & bound;
3. **Conjunto Independente Máximo**, obtido por redução a partir do Clique em tempo polinomial.

## Estrutura do Projeto

```bash
sat_clique_set/
├── src/
│   ├── clique.cpp           # Implementação do algoritmo Clique Máximo
│   ├── max_set.cpp          # Implementação do algoritmo Conjunto Independente Máximo
│   ├── sat.cpp              # Implementação do algoritmo Satisfatibilidade
│   └── main.cpp             # Código do CLI para selecionar o algoritmo e o arquivo de entrada
├── inputs/
│   ├── clique/              # Arquivos de entrada para o Clique Máximo
│   ├── max_set/             # Arquivos de entrada para o Conjunto Independente Máximo
│   └── sat/                 # Arquivos de entrada para o Satisfatibilidade
├── build/                   # Diretório onde os executáveis são gerados
└── Makefile                 # Arquivo Makefile para compilar o projeto
```

## Compilação

Execute o comando abaixo para compilar todos os algoritmos:

```bash
make

```

## Execução do CLI

Use o comando a seguir para executar a interface de linha de comando e escolher o algoritmo e o arquivo de entrada:

```bash
make run
```

## Limpando Arquivos Compilados

Para limpar os arquivos gerados durante a compilação:

```bash
make clean
```
