import os
import re
import matplotlib
import matplotlib.pyplot as plt

# Configurar o Matplotlib para usar o backend 'Agg' (sem interface gráfica)
matplotlib.use('Agg')

# Criar o diretório "data" se ele não existir
output_directory = "data"
os.makedirs(output_directory, exist_ok=True)

# Função para ler os dados dos arquivos
def read_data(directory, data_type='clique_max_set'):
    data = []

    # Iterar sobre todos os arquivos no diretório
    for filename in sorted(os.listdir(directory)):
        if filename.endswith(".out"):
            file_path = os.path.join(directory, filename)

            with open(file_path, 'r') as file:
                content = file.read()

                # Usar expressões regulares para extrair os valores desejados
                if data_type == 'clique_max_set':
                    vertices_match = re.search(r'Número de vértices:\s+(\d+)', content)
                    execution_time_match = re.search(r'Tempo de execução:\s+([\d\.e-]+)\s+segundos', content)

                    if vertices_match and execution_time_match:
                        num_vertices = int(vertices_match.group(1))
                        execution_time = float(execution_time_match.group(1))
                        data.append((num_vertices, execution_time))

                elif data_type == 'sat_fixed_variables':  # Aqui, analisar "Número de Cláusulas"
                    clauses_match = re.search(r'Número de cláusulas:\s+(\d+)', content)
                    execution_time_match = re.search(r'Tempo de execução:\s+([\d\.e-]+)\s+segundos', content)

                    if clauses_match and execution_time_match:
                        num_clauses = int(clauses_match.group(1))
                        execution_time = float(execution_time_match.group(1))
                        data.append((num_clauses, execution_time))

                elif data_type == 'sat_fixed_clauses':  # Aqui, analisar "Número de Variáveis"
                    variables_match = re.search(r'Número de variáveis:\s+(\d+)', content)
                    execution_time_match = re.search(r'Tempo de execução:\s+([\d\.e-]+)\s+segundos', content)

                    if variables_match and execution_time_match:
                        num_variables = int(variables_match.group(1))
                        execution_time = float(execution_time_match.group(1))
                        data.append((num_variables, execution_time))

    return data

# Função para gerar e salvar os gráficos
def generate_and_save_plot(data, title, filename, x_label):
    if data:
        # Ordenar os dados pelo número de vértices/cláusulas/variáveis
        data.sort()

        x_values = [d[0] for d in data]
        execution_times = [d[1] for d in data]

        # Criar o gráfico
        plt.figure()
        plt.plot(x_values, execution_times, marker='o', linestyle='-')
        plt.xlabel(x_label)
        plt.ylabel('Tempo de Execução (segundos)')
        plt.title(title)
        plt.grid(True)

        # Ajustar o layout para evitar corte de elementos
        plt.tight_layout()

        # Salvar o gráfico no diretório "data"
        full_path = os.path.join(output_directory, filename)
        plt.savefig(full_path, bbox_inches='tight')
        plt.close()
        print(f"Gráfico salvo como: {full_path}")

# Caminhos para os diretórios de saída
clique_directory = 'outputs/clique'
max_set_directory = 'outputs/max_set'
sat_fixed_clauses_directory = 'outputs/sat_fixed_clauses'
sat_fixed_variables_directory = 'outputs/sat_fixed_variables'

# Ler os dados dos arquivos de saída
clique_data = read_data(clique_directory, 'clique_max_set')
max_set_data = read_data(max_set_directory, 'clique_max_set')
sat_fixed_variables_data = read_data(sat_fixed_variables_directory, 'sat_fixed_variables')
sat_fixed_clauses_data = read_data(sat_fixed_clauses_directory, 'sat_fixed_clauses')

# Gerar e salvar os gráficos
generate_and_save_plot(clique_data, 'Número de Vértices vs Tempo de Execução (Clique)', 'clique_analysis.png', 'Número de Vértices')
generate_and_save_plot(max_set_data, 'Número de Vértices vs Tempo de Execução (Max Set)', 'max_set_analysis.png', 'Número de Vértices')
generate_and_save_plot(sat_fixed_variables_data, 'Número de Cláusulas vs Tempo de Execução (SAT - Variáveis Fixas)', 'sat_fixed_variables_analysis.png', 'Número de Cláusulas')
generate_and_save_plot(sat_fixed_clauses_data, 'Número de Variáveis vs Tempo de Execução (SAT - Cláusulas Fixas)', 'sat_fixed_clauses_analysis.png', 'Número de Variáveis')
