#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

// Função para gerar uma instância
void generate_graph_instance(int num_vertices, double edge_probability,
                             const string &filename) {
  // Definir o diretório de saída
  string output_dir = "generators/generated_inputs/graph";

  // Cria o diretório se não existir
  if (!fs::exists(output_dir)) {
    fs::create_directories(output_dir);
  }

  // Caminho completo para o arquivo de saída
  string filepath = output_dir + "/" + filename;

  ofstream outfile(filepath);

  if (!outfile.is_open()) {
    cerr << "Erro ao abrir o arquivo de saída: " << filepath << endl;
    return;
  }

  // Primeira linha: número de vértices
  outfile << num_vertices << endl;

  // Gerar a matriz de adjacência
  srand(static_cast<unsigned>(time(0)));
  for (int i = 0; i < num_vertices; ++i) {
    for (int j = 0; j < num_vertices; ++j) {
      if (i == j) {
        outfile << "0"; // Sem laços
      } else {
        // Gera 1 ou 0 com base na probabilidade de uma aresta
        int value =
            (rand() / static_cast<double>(RAND_MAX)) < edge_probability ? 1 : 0;
        outfile << value;
      }
      if (j < num_vertices - 1) {
        outfile << " ";
      }
    }
    outfile << endl;
  }

  outfile.close();
  cout << "Instância gerada e salva em " << filepath << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << "Uso: " << argv[0]
         << " <num_vertices> <edge_probability> <output_filename>\n";
    return 1;
  }

  int num_vertices = atoi(argv[1]);
  double edge_probability = atof(argv[2]);
  string filename = argv[3];

  if (num_vertices <= 0 || edge_probability < 0 || edge_probability > 1) {
    cerr << "Número de vértices deve ser positivo e a probabilidade deve estar "
            "entre 0 e 1.\n";
    return 1;
  }

  generate_graph_instance(num_vertices, edge_probability, filename);

  return 0;
}
