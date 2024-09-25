# Implementação em C++ de Três Problemas Clássicos

Este projeto é um trabalho prático para a disciplina de Projeto e Análise de Algoritmos da Universidade Federal de Ouro Preto e implementa três problemas clássicos em C++:

1. **Satisfatibilidade Booleana (SAT)**, utilizando backtracking;
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
├── generators/
│   ├── graph_gen.cpp        # Código do gerador de instâncias para problemas de grafos
│   ├── sat_gen.cpp          # Código do gerador de instâncias de SAT
│   └── generated_inputs/
│       ├── graph/           # Instâncias geradas pelo algoritmo de geração de grafos
│       └── sat/             # Instâncias geradas pelo algoritmo de geração de SAT
├── inputs/
│   ├── clique/              # Arquivos de entrada para o Clique Máximo
│   ├── max_set/             # Arquivos de entrada para o Conjunto Independente Máximo
│   └── sat/                 # Arquivos de entrada para o Satisfatibilidade
├── outputs/
│   ├── clique/              # Resultados gerados pelas execuções do algoritmo de Clique Máximo
│   ├── max_set/             # Resultados gerados pelas execuções do algoritmo de Conjunto Independente Máximo
│   └── sat/                 # Resultados gerados pelas execuções do algoritmo de SAT
├── data/                    # Diretório contendo os gráficos gerados pela análise
│   ├── clique_analysis.png  # Gráfico de análise do Clique Máximo
│   ├── max_set_analysis.png # Gráfico de análise do Conjunto Independente Máximo
│   └── sat.png              # Gráfico de análise do SAT
├── analysis.py              # Script Python para gerar os gráficos de análise
├── build/                   # Diretório onde os executáveis são gerados
├── Makefile                 # Arquivo Makefile para compilar o projeto
└── README.md                # Este arquivo de documentação
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

## Gerando Instâncias

Para gerar instâncias, você pode usar o gerador de entradas. O gerador permite criar instâncias com um número especificado de cláusulas e variáveis.

### Gerando uma Instância de SAT

Para gerar uma nova instância de SAT com 5 cláusulas e 6 variáveis, por exemplo, use:

```bash
generators/sat_gen 5 6 example.txt
```

Isso criará um arquivo `example.txt` no diretório `generators/generated_inputs/sat`.

### Benchmark e Resultados para SAT

Durante a execução, o algoritmo de SAT salva os resultados (incluindo o tempo de execução, número de variáveis, número de cláusulas, e as atribuições de variáveis) em arquivos no diretório `outputs/sat`.

Por exemplo, se o arquivo de entrada for `entrada1.txt`, o resultado será salvo em `outputs/sat/entrada1.txt.out`.

## Gerando Gráficos com o `analysis.py`

Este projeto inclui um script Python chamado `analysis.py` que gera gráficos de desempenho dos três algoritmos baseados nos resultados das execuções. Os gráficos serão salvos no diretório `data`.

### Como executar o script de análise

Certifique-se de que o ambiente Python esteja configurado corretamente, incluindo a instalação de bibliotecas como `matplotlib` e `pandas`. Para gerar os gráficos, execute:

```bash
python analysis.py
```

## Limpando Arquivos Compilados

Para limpar os arquivos gerados durante a compilação:

```bash
make clean
```
