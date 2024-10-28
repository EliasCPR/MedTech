#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONSULTAS 10
#define ARQUIVO_PACIENTES "pacientes.csv"
#define ARQUIVO_MEDICOS "medicos.csv"

typedef struct {
    char data[11]; // formato: "dd/mm/yyyy"
    char medico[50];
    char diagnostico[100];
} Consulta;

typedef struct {
    char nome[50];
    int idade;
    char sintomas[100];
    Consulta historico[MAX_CONSULTAS];
    int numConsultas;
} Paciente;

typedef struct {
    char nome[50];
    char especializacao[50];
    int disponibilidade;
} Medico;

void salvarPacientes(Paciente *pacientes, int numPacientes) {
    FILE *file = fopen(ARQUIVO_PACIENTES, "w");
    if (!file) {
        printf("Erro ao abrir arquivo de pacientes!\n");
        return;
    }
    
    fprintf(file, "Nome,Idade,Sintomas\n"); // Cabeçalho do CSV
    for (int i = 0; i < numPacientes; i++) {
        fprintf(file, "%s,%d,%s\n", pacientes[i].nome, pacientes[i].idade, pacientes[i].sintomas);
        for (int j = 0; j < pacientes[i].numConsultas; j++) {
            Consulta consulta = pacientes[i].historico[j];
            fprintf(file, "%s,%s,%s\n", consulta.data, consulta.medico, consulta.diagnostico);
        }
    }
    fclose(file);
}

void carregarPacientes(Paciente *pacientes, int *numPacientes) {
    FILE *file = fopen(ARQUIVO_PACIENTES, "r");
    if (!file) {
        printf("Arquivo de pacientes não encontrado.\n");
        *numPacientes = 0;
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), file); // Ignorar cabeçalho
    *numPacientes = 0;

    while (fgets(linha, sizeof(linha), file)) {
        Paciente paciente;
        sscanf(linha, "%49[^,],%d,%99[^\n]", paciente.nome, &paciente.idade, paciente.sintomas);
        paciente.numConsultas = 0;

        // Ler histórico de consultas
        while (fgets(linha, sizeof(linha), file) && linha[0] != '\n') {
            Consulta consulta;
            sscanf(linha, "%10[^,],%49[^,],%99[^\n]", consulta.data, consulta.medico, consulta.diagnostico);
            paciente.historico[paciente.numConsultas++] = consulta;
        }
        pacientes[(*numPacientes)++] = paciente;
    }
    fclose(file);
}

void salvarMedicos(Medico *medicos, int numMedicos) {
    FILE *file = fopen(ARQUIVO_MEDICOS, "w");
    if (!file) {
        printf("Erro ao abrir arquivo de médicos!\n");
        return;
    }
    
    fprintf(file, "Nome,Especializacao,Disponibilidade\n"); // Cabeçalho do CSV
    for (int i = 0; i < numMedicos; i++) {
        fprintf(file, "%s,%s,%d\n", medicos[i].nome, medicos[i].especializacao, medicos[i].disponibilidade);
    }
    fclose(file);
}

void carregarMedicos(Medico *medicos, int *numMedicos) {
    FILE *file = fopen(ARQUIVO_MEDICOS, "r");
    if (!file) {
        printf("Arquivo de médicos não encontrado.\n");
        *numMedicos = 0;
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), file); // Ignorar cabeçalho
    *numMedicos = 0;

    while (fgets(linha, sizeof(linha), file)) {
        Medico medico;
        sscanf(linha, "%49[^,],%49[^,],%d\n", medico.nome, medico.especializacao, &medico.disponibilidade);
        medicos[(*numMedicos)++] = medico;
    }
    fclose(file);
}

void cadastrarPaciente(Paciente *paciente) {
    printf("Digite o nome do paciente: ");
    scanf(" %49[^\n]", paciente->nome);
    printf("Digite a idade do paciente: ");
    scanf("%d", &paciente->idade);
    printf("Digite os sintomas: ");
    scanf(" %[^\n]", paciente->sintomas);
    paciente->numConsultas = 0;
}

void adicionarConsulta(Paciente *paciente, const char *medico, const char *diagnostico, const char *data) {
    if (paciente->numConsultas < MAX_CONSULTAS) {
        Consulta *novaConsulta = &paciente->historico[paciente->numConsultas++];
        strncpy(novaConsulta->medico, medico, sizeof(novaConsulta->medico) - 1);
        strncpy(novaConsulta->diagnostico, diagnostico, sizeof(novaConsulta->diagnostico) - 1);
        strncpy(novaConsulta->data, data, sizeof(novaConsulta->data) - 1);
    } else {
        printf("Histórico cheio para o paciente %s.\n", paciente->nome);
    }
}

void cadastrarMedico(Medico *medico) {
    printf("Digite o nome do médico: ");
    scanf(" %49[^\n]", medico->nome);
    printf("Digite a especialização do médico: ");
    scanf(" %49[^\n]", medico->especializacao);
    printf("Disponibilidade (1 para disponível, 0 para indisponível): ");
    scanf("%d", &medico->disponibilidade);
}

void buscarPaciente(Paciente *pacientes, int numPacientes, const char *nome) {
    for (int i = 0; i < numPacientes; i++) {
        if (strcmp(pacientes[i].nome, nome) == 0) {
            printf("Paciente: %s\nIdade: %d\nSintomas: %s\n", pacientes[i].nome, pacientes[i].idade, pacientes[i].sintomas);
            printf("Histórico de consultas:\n");
            for (int j = 0; j < pacientes[i].numConsultas; j++) {
                Consulta consulta = pacientes[i].historico[j];
                printf("Data: %s, Médico: %s, Diagnóstico: %s\n", consulta.data, consulta.medico, consulta.diagnostico);
            }
            return;
        }
    }
    printf("Paciente %s não encontrado.\n", nome);
}

void listarPacientes(Paciente *pacientes, int numPacientes) {
    printf("=== Lista de Pacientes ===\n");
    for (int i = 0; i < numPacientes; i++) {
        printf("%d. %s, Idade: %d\n", i + 1, pacientes[i].nome, pacientes[i].idade);
    }
}

void exibirMenu() {
    printf("=== Sistema de Triagem ===\n");
    printf("1. Cadastrar paciente\n");
    printf("2. Cadastrar médico\n");
    printf("3. Adicionar consulta ao paciente\n");
    printf("4. Buscar paciente\n");
    printf("5. Listar pacientes\n");
    printf("6. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Paciente pacientes[100];
    Medico medicos[50];
    int numPacientes = 0, numMedicos = 0;
    int opcao;

    carregarPacientes(pacientes, &numPacientes);
    carregarMedicos(medicos, &numMedicos);

    while (1) {
        exibirMenu();
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                cadastrarPaciente(&pacientes[numPacientes++]);
                salvarPacientes(pacientes, numPacientes);
                break;
            case 2:
                cadastrarMedico(&medicos[numMedicos++]);
                salvarMedicos(medicos, numMedicos);
                break;
            case 3: {
                char nome[50], medico[50], diagnostico[100], data[11];
                printf("Digite o nome do paciente para adicionar consulta: ");
                scanf(" %49[^\n]", nome);
                printf("Digite o nome do médico: ");
                scanf(" %49[^\n]", medico);
                printf("Digite o diagnóstico: ");
                scanf(" %[^\n]", diagnostico);
                printf("Digite a data (dd/mm/yyyy): ");
                scanf("%10s", data);

                for (int i = 0; i < numPacientes; i++) {
                    if (strcmp(pacientes[i].nome, nome) == 0) {
                        adicionarConsulta(&pacientes[i], medico, diagnostico, data);
                        salvarPacientes(pacientes, numPacientes);
                        break;
                    }
                }
                break;
            }
            case 4: {
                char nome[50];
                printf("Digite o nome do paciente para busca: ");
                scanf(" %49[^\n]", nome);
                buscarPaciente(pacientes, numPacientes, nome);
                break;
            }
            case 5:
                listarPacientes(pacientes, numPacientes);
                break;
            case 6:
                printf("Saindo...\n");
                return 0;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    }

    return 0;
}
