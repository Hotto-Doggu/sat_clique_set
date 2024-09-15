#include <iostream>
#include <vector>
#include <fstream>  
#include <sstream>  
using namespace std;

// Função para verificar se uma atribuição satisfaz as cláusulas
bool is_satisfied(const vector<int>& assignment, const vector<vector<int>>& clauses) {
    for (const auto& clause : clauses) {
        bool clause_satisfied = false;
        for (size_t i = 0; i < assignment.size(); ++i) {
            if ((clause[i] == 1 && assignment[i] == 1) || (clause[i] == 0 && assignment[i] == 0)) {
                clause_satisfied = true;
                break;
            }
        }
        if (!clause_satisfied) return false;
    }
    return true;
}

// Função de backtracking para satisfabilidade
bool backtrack(vector<int>& assignment, const vector<vector<int>>& clauses, int var_idx) {
    if (static_cast<size_t>(var_idx) == assignment.size()) {
        return is_satisfied(assignment, clauses);
    }

    // Tenta atribuir verdadeiro (1) e falso (0) para a variável atual
    for (int value : {0, 1}) {
        assignment[var_idx] = value;
        if (backtrack(assignment, clauses, var_idx + 1)) {
            return true;
        }
    }
    return false;
}

void satisfability(int num_vars, const vector<vector<int>>& clauses) {
    vector<int> assignment(num_vars, -1);

    if (backtrack(assignment, clauses, 0)) {
        cout << "Atribuições satisfatórias: ";
        for (size_t i = 0; i < assignment.size(); ++i) {
            cout << "x" << i + 1 << " = " << (assignment[i] == 1 ? "True" : "False") << " ";
        }
        cout << endl;
    } else {
        cout << "Não há solução que satisfaça a fórmula." << endl;
    }
}
// Função para ler o arquivo de entrada
bool read_input(const string& filename, int& num_vars, vector<vector<int>>& clauses) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return false;
    }

    string line;
    // Ler o número de variáveis da primeira linha
    if (getline(file, line)) {
        istringstream iss(line);
        iss >> num_vars;
    }

    // Ler as cláusulas restantes
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

int main() {
    string filename;
    cout << "Digite o nome do arquivo de entrada (ex: entrada.txt): ";
    cin >> filename;

    int num_vars;
    vector<vector<int>> clauses;

    // Ler o arquivo de entrada
    if (!read_input(filename, num_vars, clauses)) {
        return 1;
    }

    // Executar o algoritmo de satisfabilidade
    satisfability(num_vars, clauses);

    return 0;
}