# Definir o compilador e as flags
CXX = g++
CXXFLAGS = -Wall -g

# Nomes dos executáveis
EXEC_SAT = satisfability
EXEC_CLIQUE = clique
EXEC_INDEPENDENT = max_set

# Compilar todos os programas
all: $(EXEC_SAT) $(EXEC_CLIQUE) $(EXEC_INDEPENDENT)

# Regras de compilação para sat.cpp
$(EXEC_SAT): sat.cpp
	$(CXX) $(CXXFLAGS) -o $(EXEC_SAT) sat.cpp

# Regras de compilação para clique.cpp
$(EXEC_CLIQUE): clique.cpp
	$(CXX) $(CXXFLAGS) -o $(EXEC_CLIQUE) clique.cpp

# Regras de compilação para max_set.cpp
$(EXEC_INDEPENDENT): max_set.cpp
	$(CXX) $(CXXFLAGS) -o $(EXEC_INDEPENDENT) max_set.cpp

# Limpeza dos arquivos compilados
clean:
	rm -f $(EXEC_SAT) $(EXEC_CLIQUE) $(EXEC_INDEPENDENT)
