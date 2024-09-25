#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

int main() {
  std::vector<std::string> algoritmos = {"clique", "max_set", "sat"};

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
  std::string dir_path = "inputs/" + algoritmo;

  if (!fs::exists(dir_path) || !fs::is_directory(dir_path)) {
    std::cerr << "\nDiretório de entrada não encontrado: " << dir_path << "\n"
              << std::endl;
    return 1;
  }

  std::vector<std::string> entradas;
  for (const auto &entry : fs::directory_iterator(dir_path)) {
    if (entry.is_regular_file()) {
      entradas.push_back(entry.path().filename().string());
    }
  }

  std::sort(entradas.begin(), entradas.end());

  if (entradas.empty()) {
    std::cerr << "\nNenhum arquivo de entrada encontrado no diretório: "
              << dir_path << "\n"
              << std::endl;
    return 1;
  }

  std::cout << "\nDeseja executar em:\n";
  std::cout << "1. Uma única instância\n";
  std::cout << "2. Todas as instâncias\n";
  int escolha_exec;
  std::cin >> escolha_exec;

  std::string output_dir = "outputs/" + algoritmo;

  if (escolha_exec == 1) {
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
    std::string comando =
        "./build/sat inputs/" + algoritmo + "/" + entrada + " " + output_dir;

    std::cout << "\nExecutando: " << comando << "\n" << std::endl;
    int result = system(comando.c_str());
    return result;

  } else if (escolha_exec == 2) {
    for (const auto &entrada : entradas) {
      std::string comando = "./build/" + algoritmo + " inputs/" + algoritmo +
                            "/" + entrada + " " + output_dir;
      std::cout << "\nExecutando: " << comando << "\n";
      int result = system(comando.c_str());
      if (result != 0) {
        std::cerr << "Erro ao executar o arquivo: " << entrada << "\n";
      }
    }
  }

  return 0;
}
