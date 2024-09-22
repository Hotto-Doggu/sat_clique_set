#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;

// Função para verificar se uma atribuição satisfaz as cláusulas
bool is_satisfied(const vector<int> &assignment,
                  const vector<vector<int>> &clauses) {
  for (const auto &clause : clauses) {
    bool clause_satisfied = false;
    for (int literal : clause) {
      int var_index = abs(literal) - 1;
      if ((literal > 0 &&
           assignment[var_index] == 1) || // Literal positivo e variável é True
          (literal < 0 &&
           assignment[var_index] == 0)) { // Literal negativo e variável é False
        clause_satisfied = true;
        break;
      }
    }
    if (!clause_satisfied)
      return false; // Se uma cláusula não é satisfeita, retorna false
  }
  return true; // Todas as cláusulas foram satisfeitas
}

// Função de backtracking para satisfabilidade
bool backtrack(vector<int> &assignment, const vector<vector<int>> &clauses,
               int var_idx) {
  if (static_cast<size_t>(var_idx) == assignment.size()) {
    return is_satisfied(assignment, clauses);
  }

  for (int value : {0, 1}) {
    assignment[var_idx] = value;
    if (backtrack(assignment, clauses, var_idx + 1)) {
      return true;
    }
  }
  return false;
}

// Função principal para verificar satisfatibilidade
bool satisfability(int num_vars, const vector<vector<int>> &clauses,
                   vector<int> &assignment) {
  return backtrack(assignment, clauses, 0);
}

// Função para ler o arquivo de entrada
bool read_input(const string &filename, int &num_vars,
                vector<vector<int>> &clauses) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "\nErro ao abrir o arquivo.\n" << endl;
    return false;
  }

  string line;
  if (getline(file, line)) {
    istringstream iss(line);
    iss >> num_vars;
  }

  while (getline(file, line)) {
    istringstream iss(line);
    vector<int> clause;
    int val;
    while (iss >> val) {
      clause.push_back(val);
    }
    clauses.push_back(clause);
  }

  file.close();
  return true;
}

// Função para executar o SAT e salvar o benchmark
void run_benchmark(const string &input_filename,
                   const string &output_filename) {
  int num_vars;
  vector<vector<int>> clauses;

  if (!read_input(input_filename, num_vars, clauses)) {
    cerr << "Erro ao ler o arquivo de entrada: " << input_filename << endl;
    return;
  }

  vector<int> assignment(num_vars, -1);

  auto start_time = chrono::high_resolution_clock::now();
  bool satisfied = satisfability(num_vars, clauses, assignment);
  auto end_time = chrono::high_resolution_clock::now();
  chrono::duration<double> exec_time = end_time - start_time;

  fs::create_directories(
      "outputs/sat"); // Criar diretório de saída se não existir
  ofstream outfile(output_filename);

  if (outfile.is_open()) {
    outfile << "Arquivo de entrada: " << input_filename << endl;
    outfile << "Número de variáveis: " << num_vars << endl;
    outfile << "Número de cláusulas: " << clauses.size() << endl;
    outfile << "Tempo de execução: " << exec_time.count() << " segundos\n";

    if (satisfied) {
      outfile << "Atribuição satisfatória encontrada:\n";
      for (size_t i = 0; i < assignment.size(); ++i) {
        outfile << "x" << i + 1 << " = "
                << (assignment[i] == 1 ? "True" : "False") << endl;
      }
    } else {
      outfile << "Não há solução que satisfaça a fórmula.\n";
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
