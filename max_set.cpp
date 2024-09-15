#include <iostream>
#include <vector>
using namespace std;

vector<int> best_clique;
int max_size = 0;

// Gera o grafo complementar
vector<vector<int>> complement_graph(const vector<vector<int>>& graph, int num_vertices) {
    vector<vector<int>> complement(num_vertices, vector<int>(num_vertices, 0));
    for (int i = 0; i < num_vertices; ++i) {
        for (int j = 0; j < num_vertices; ++j) {
            if (i != j) {
                complement[i][j] = 1 - graph[i][j];
            }
        }
    }
    return complement;
}

// Reutilizando a função de branch and bound
void branch_and_bound(const vector<vector<int>>& graph, vector<int>& clique, vector<int>& candidates) {
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

// Função para encontrar o conjunto independente máximo usando redução ao clique
void max_independent_set(const vector<vector<int>>& graph, int num_vertices) {
    vector<vector<int>> complement = complement_graph(graph, num_vertices);
    vector<int> clique;
    vector<int> candidates;
    for (int i = 0; i < num_vertices; ++i) {
        candidates.push_back(i);
    }

    branch_and_bound(complement, clique, candidates);
    vector<int> best_independent_set = best_clique;  // O conjunto independente corresponde ao clique máximo no complemento

    cout << "Conjunto Independente Máximo: ";
    for (int v : best_independent_set) {
        cout << v + 1 << " ";  // Para exibir o número correto dos vértices (iniciando em 1)
    }
    cout << endl;
}

int main() {
    int num_vertices = 9;
    vector<vector<int>> graph = {
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 0, 0, 0, 1, 1, 0}
    };

    max_independent_set(graph, num_vertices);
    return 0;
}
