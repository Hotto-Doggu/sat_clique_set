#include <iostream>
#include <vector>
using namespace std;

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

void max_clique(const vector<vector<int>> &graph, int num_vertices) {
  vector<int> clique;
  vector<int> candidates;
  for (int i = 0; i < num_vertices; ++i) {
    candidates.push_back(i);
  }

  branch_and_bound(graph, clique, candidates);

  cout << "Clique Máximo: ";
  for (int v : best_clique) {
    cout << v + 1 << " ";
  }
  cout << endl;
}

int main() {
  int num_vertices = 9;
  vector<vector<int>> graph = {
      {0, 0, 1, 0, 0, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 0},
      {1, 1, 0, 1, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0, 1, 0, 1, 0}, {0, 0, 0, 0, 1, 0, 0, 0, 0},
      {0, 0, 0, 1, 0, 0, 0, 1, 1}, {0, 0, 0, 0, 1, 0, 1, 0, 1},
      {0, 0, 0, 0, 0, 0, 1, 1, 0}};

  max_clique(graph, num_vertices);
  return 0;
}
