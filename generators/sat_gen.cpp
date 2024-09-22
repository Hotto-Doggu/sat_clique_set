#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

// Função para gerar uma instância SAT
void generate_sat_instance(int num_clauses, int num_vars,
                           const string &filename) {
  // Definir o diretório de saída
  string output_dir = "generators/generated_inputs/sat";

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

  // Primeira linha: número de variáveis
  outfile << num_vars << endl;

  // Gerar cláusulas
  srand(static_cast<unsigned>(time(0)));
  for (int i = 0; i < num_clauses; ++i) {
    for (int j = 0; j < num_vars; ++j) {
      int value = rand() % 3 - 1; // Gera -1, 0 ou 1 aleatoriamente
      outfile << value;
      if (j < num_vars - 1) {
        outfile << " ";
      }
    }
    outfile << endl;
  }

  outfile.close();
  cout << "Instância SAT gerada e salva em " << filepath << endl;
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    cerr << "Uso: " << argv[0]
         << " <num_clauses> <num_vars> <output_filename>\n";
    return 1;
  }

  int num_clauses = atoi(argv[1]);
  int num_vars = atoi(argv[2]);
  string filename = argv[3];

  if (num_clauses <= 0 || num_vars <= 0) {
    cerr << "Número de cláusulas e variáveis devem ser positivos.\n";
    return 1;
  }

  generate_sat_instance(num_clauses, num_vars, filename);

  return 0;
}
