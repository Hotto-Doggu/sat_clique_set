#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

vector<int> assignment;
bool satisfiable = false;

// Função para verificar se a fórmula é satisfeita
bool isSatisfied(const vector<vector<int>> &clauses) {
  for (const auto &clause : clauses) {
    bool clauseSatisfied = false;

    for (size_t i = 0; i < clause.size(); ++i) {
      int literal = clause[i];

      if (literal != -1) {
        bool value = assignment[i] == 1;

        if (literal == 0) {
          value = !value;
        }

        if (value) {
          clauseSatisfied = true;
          break;
        }
      }
    }

    if (!clauseSatisfied) {
      return false;
    }
  }

  return true;
}

// Função de backtracking para encontrar a solução
void solveSAT(vector<vector<int>> &clauses, int index, int num_variables) {
  if (index == num_variables) {
    if (isSatisfied(clauses)) {
      satisfiable = true;
    }
    return;
  }

  assignment[index] = 0;
  solveSAT(clauses, index + 1, num_variables);

  if (satisfiable)
    return;

  assignment[index] = 1;
  solveSAT(clauses, index + 1, num_variables);
}

// Função principal para resolver o problema SAT
void solveSATProblem(vector<vector<int>> &clauses, int num_variables) {
  assignment.resize(num_variables, 0);
  solveSAT(clauses, 0, num_variables);
}

// Função para ler o arquivo de entrada
bool read_input(const string &filename, int &num_variables,
                vector<vector<int>> &clauses) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "\nErro ao abrir o arquivo.\n" << endl;
    return false;
  }

  string line;
  // Ler o número de variáveis e o número de cláusulas
  if (getline(file, line)) {
    istringstream iss(line);
    int num_clauses;
    iss >> num_variables >> num_clauses;

    // Ler as cláusulas
    clauses.resize(num_clauses);
    for (int i = 0; i < num_clauses; ++i) {
      if (getline(file, line)) {
        istringstream iss(line);
        int literal;
        while (iss >> literal) {
          clauses[i].push_back(literal);
        }
      }
    }
  }

  file.close();
  return true;
}

// Função para executar o SAT e salvar o benchmark
void run_benchmark(const string &input_filename,
                   const string &output_filename) {
  int num_variables;
  vector<vector<int>> clauses;

  if (!read_input(input_filename, num_variables, clauses)) {
    cerr << "Erro ao ler o arquivo de entrada: " << input_filename << endl;
    return;
  }

  auto start_time = chrono::high_resolution_clock::now();
  solveSATProblem(clauses, num_variables);
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double> exec_time = end_time - start_time;

  // Criar diretório de saída se não existir
  fs::create_directories("outputs/sat");

  // Salvar os resultados no arquivo de saída
  ofstream outfile(output_filename);

  if (outfile.is_open()) {
    outfile << "Arquivo de entrada: " << input_filename << endl;
    outfile << "Número de variáveis: " << num_variables << endl;
    outfile << "Satisfatibilidade: "
            << (satisfiable ? "Satisfiável" : "Insatisfiável") << endl;
    outfile << "Tempo de execução: " << exec_time.count() << " segundos\n";

    if (satisfiable) {
      outfile << "Atribuição satisfatória: ";
      for (int i = 0; i < num_variables; ++i) {
        outfile << "x" << (i + 1) << "=" << (assignment[i] == 1 ? "1" : "0")
                << " ";
      }
      outfile << endl;
    }

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
      "outputs/sat/" + fs::path(input_filename).filename().string() + ".out";

  run_benchmark(input_filename, output_filename);

  return 0;
}
