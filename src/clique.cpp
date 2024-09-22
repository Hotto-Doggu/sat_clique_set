#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

vector<int> best_clique;
size_t max_size = 0;

// Verifica se o subconjunto atual de vértices forma um clique
bool is_clique(const vector<vector<int>> &graph, const vector<int> &clique) {
  for (size_t i = 0; i < clique.size(); ++i) {
    for (size_t j = i + 1; j < clique.size(); ++j) {
      if (graph[clique[i]][clique[j]] == 0) {
        return false;
      }
    }
  }
  return true;
}

// Função de branch and bound para encontrar o clique máximo
void branch_and_bound(const vector<vector<int>> &graph, vector<int> &clique,
                      vector<int> &candidates) {
  if (clique.size() > max_size) {
    max_size = clique.size();
    best_clique = clique;
  }

  for (size_t i = 0; i < candidates.size(); ++i) {
    int v = candidates[i];
    vector<int> new_candidates;

    for (size_t j = i + 1; j < candidates.size(); ++j) {
      if (graph[v][candidates[j]] == 1) {
        new_candidates.push_back(candidates[j]);
      }
    }

    clique.push_back(v);
    branch_and_bound(graph, clique, new_candidates);
    clique.pop_back();
  }
}

// Função principal para encontrar o clique máximo
void max_clique(const vector<vector<int>> &graph, int num_vertices) {
  vector<int> clique;
  vector<int> candidates(num_vertices);
  for (int i = 0; i < num_vertices; ++i) {
    candidates[i] = i;
  }

  branch_and_bound(graph, clique, candidates);
}

// Função para ler o arquivo de entrada
bool read_input(const string &filename, int &num_vertices,
                vector<vector<int>> &graph) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "\nErro ao abrir o arquivo.\n" << endl;
    return false;
  }

  string line;
  // Ler o número de vértices da primeira linha
  if (getline(file, line)) {
    istringstream iss(line);
    iss >> num_vertices;
  }

  // Inicializar a matriz de adjacência
  graph.resize(num_vertices, vector<int>(num_vertices, 0));

  // Ler a matriz de adjacência
  for (int i = 0; i < num_vertices; ++i) {
    if (getline(file, line)) {
      istringstream iss(line);
      for (int j = 0; j < num_vertices; ++j) {
        iss >> graph[i][j];
      }
    }
  }

  file.close();
  return true;
}

// Função para executar o Clique Máximo e salvar o benchmark
void run_benchmark(const string &input_filename,
                   const string &output_filename) {
  int num_vertices;
  vector<vector<int>> graph;

  if (!read_input(input_filename, num_vertices, graph)) {
    cerr << "Erro ao ler o arquivo de entrada: " << input_filename << endl;
    return;
  }

  auto start_time = chrono::high_resolution_clock::now();
  max_clique(graph, num_vertices);
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double> exec_time = end_time - start_time;

  // Criar diretório de saída se não existir
  fs::create_directories("outputs/clique");

  // Salvar os resultados no arquivo de saída
  ofstream outfile(output_filename);

  if (outfile.is_open()) {
    outfile << "Arquivo de entrada: " << input_filename << endl;
    outfile << "Número de vértices: " << num_vertices << endl;
    outfile << "Tamanho do clique máximo: " << max_size << endl;
    outfile << "Tempo de execução: " << exec_time.count() << " segundos\n";

    outfile << "Vértices do clique máximo: ";
    for (int v : best_clique) {
      outfile << v + 1 << " "; // Imprimir os vértices com índice baseado em 1
    }
    outfile << endl;

    outfile.close();
    cout << "Resultados salvos em " << output_filename << endl;
  } else {
    cerr << "Erro ao criar arquivo de saída: " << output_filename << endl;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "\nUso: " << argv[0] << " <arquivo de entrada>\n" << endl;
    return 1;
  }

  string input_filename = argv[1];
  string output_filename =
      "outputs/clique/" + fs::path(input_filename).filename().string() + ".out";

  run_benchmark(input_filename, output_filename);

  return 0;
}
