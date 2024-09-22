import os
import re
import matplotlib
import matplotlib.pyplot as plt

# Configurar o Matplotlib para usar o backend 'Agg' (sem interface gráfica)
matplotlib.use('Agg')

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

                elif data_type == 'sat':
                    clauses_match = re.search(r'Número de cláusulas:\s+(\d+)', content)
                    execution_time_match = re.search(r'Tempo de execução:\s+([\d\.e-]+)\s+segundos', content)

                    if clauses_match and execution_time_match:
                        num_clauses = int(clauses_match.group(1))
                        execution_time = float(execution_time_match.group(1))
                        data.append((num_clauses, execution_time))

    return data

# Função para gerar e salvar os gráficos
def generate_and_save_plot(data, title, filename):
    if data:
        # Ordenar os dados pelo número de vértices/cláusulas
        data.sort()

        x_values = [d[0] for d in data]
        execution_times = [d[1] for d in data]

        # Criar o gráfico
        plt.figure()
        plt.plot(x_values, execution_times, marker='o', linestyle='-')
        plt.xlabel('Número de Vértices' if 'Clique' in title or 'Max Set' in title else 'Número de Cláusulas')
        plt.ylabel('Tempo de Execução (segundos)')
        plt.title(title)
        plt.grid(True)

        # Ajustar o layout para evitar corte de elementos
        plt.tight_layout()

        # Salvar o gráfico
        plt.savefig(filename, bbox_inches='tight')
        plt.close()
        print(f"Gráfico salvo como: {filename}")

# Caminhos para os diretórios de saída
clique_directory = 'outputs/clique'
max_set_directory = 'outputs/max_set'
sat_directory = 'outputs/sat'

# Ler os dados dos arquivos de saída
clique_data = read_data(clique_directory, 'clique_max_set')
max_set_data = read_data(max_set_directory, 'clique_max_set')
sat_data = read_data(sat_directory, 'sat')

# Gerar e salvar os gráficos
generate_and_save_plot(clique_data, 'Número de Vértices vs Tempo de Execução (Clique)', 'clique_analysis.png')
generate_and_save_plot(max_set_data, 'Número de Vértices vs Tempo de Execução (Max Set)', 'max_set_analysis.png')
generate_and_save_plot(sat_data, 'Número de Cláusulas vs Tempo de Execução (SAT)', 'sat_analysis.png')
