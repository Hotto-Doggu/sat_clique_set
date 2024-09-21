#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main() {
  // Lista de algoritmos
  std::vector<std::string> algoritmos = {"clique", "max_set", "sat"};

  // Exibir opções de algoritmos
  std::cout << "\nEscolha um algoritmo:\n";
  for (size_t i = 0; i < algoritmos.size(); ++i) {
    std::cout << i + 1 << ". " << algoritmos[i] << std::endl;
  }

  int escolha_algo;
  std::cout << "\nDigite o número do algoritmo desejado: ";
  std::cin >> escolha_algo;

  if (escolha_algo < 1 || escolha_algo > static_cast<int>(algoritmos.size())) {
    std::cerr << "\nSeleção inválida.\n" << std::endl;
    return 1;
  }

  std::string algoritmo = algoritmos[escolha_algo - 1];

  // Caminho do diretório correspondente ao algoritmo escolhido
  std::string dir_path = "inputs/" + algoritmo;

  // Verificar se o diretório existe
  if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
    std::cerr << "\nDiretório de entrada não encontrado: " << dir_path << "\n"
              << std::endl;
    return 1;
  }

  // Lista de arquivos de entrada específicos para o algoritmo escolhido
  std::vector<std::string> entradas;
  for (const auto &entry : fs::directory_iterator(dir_path)) {
    if (entry.is_regular_file()) {
      entradas.push_back(entry.path().filename().string());
    }
  }

  // Ordenar os arquivos em ordem lexicográfica
  std::sort(entradas.begin(), entradas.end());

  if (entradas.empty()) {
    std::cerr << "\nNenhum arquivo de entrada encontrado no diretório: "
              << dir_path << "\n"
              << std::endl;
    return 1;
  }

  // Exibir opções de arquivos de entrada
  std::cout << "\nEscolha um arquivo de entrada:\n";
  for (size_t i = 0; i < entradas.size(); ++i) {
    std::cout << i + 1 << ". " << entradas[i] << std::endl;
  }

  int escolha_entrada;
  std::cout << "\nDigite o número do arquivo de entrada desejado: ";
  std::cin >> escolha_entrada;

  if (escolha_entrada < 1 ||
      escolha_entrada > static_cast<int>(entradas.size())) {
    std::cerr << "\nSeleção inválida.\n" << std::endl;
    return 1;
  }

  std::string entrada = entradas[escolha_entrada - 1];

  // Construir o comando para executar o algoritmo selecionado
  std::string comando =
      "./build/" + algoritmo + " inputs/" + algoritmo + "/" + entrada;

  std::cout << "\nExecutando: " << comando << "\n" << std::endl;
  int result = system(comando.c_str());

  return result;
}
