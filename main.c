#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONSULTAS 10
#define ARQUIVO_PACIENTES "pacientes.csv"
#define ARQUIVO_MEDICOS "medicos.csv"
#define ARQUIVO_CONSULTAS "consultas.csv"

typedef struct {
    char data[11]; // formato: "dd/mm/yyyy"
    char cpfPaciente[15];
    char crmMedico[15];
    char diagnostico[100];
} Consulta;

typedef struct {
    char nome[50];
    char dataNascimento[11]; // data de nascimento no formato dd/mm/yyyy
    char cpf[15]; // identificador único para paciente
    char sintomas[100];
    Consulta historico[MAX_CONSULTAS];
    int numConsultas;
} Paciente;

typedef struct {
    char nome[50];
    char especializacao[50];
    char crm[15]; // identificador único para médico
    int disponibilidade; // 1 para disponível, 0 para indisponível
} Medico;

void salvarPacientes(Paciente *pacientes, int numPacientes) {
    FILE *file = fopen(ARQUIVO_PACIENTES, "w");
    if (!file) {
        printf("Erro ao abrir arquivo de pacientes!\n");
        return;
    }
    
    fprintf(file, "Nome,DataNascimento,CPF,Sintomas\n");
    for (int i = 0; i < numPacientes; i++) {
        fprintf(file, "%s,%s,%s,%s\n", pacientes[i].nome, pacientes[i].dataNascimento, pacientes[i].cpf, pacientes[i].sintomas);
    }
    fclose(file);
}

void salvarMedicos(Medico *medicos, int numMedicos) {
    FILE *file = fopen(ARQUIVO_MEDICOS, "w");
    if (!file) {
        printf("Erro ao abrir arquivo de médicos!\n");
        return;
    }
    
    fprintf(file, "Nome,Especializacao,CRM,Disponibilidade\n");
    for (int i = 0; i < numMedicos; i++) {
        fprintf(file, "%s,%s,%s,%d\n", medicos[i].nome, medicos[i].especializacao, medicos[i].crm, medicos[i].disponibilidade);
    }
    fclose(file);
}

void salvarConsultas(Consulta *consultas, int numConsultas) {
    FILE *file = fopen(ARQUIVO_CONSULTAS, "w");
    if (!file) {
        printf("Erro ao abrir arquivo de consultas!\n");
        return;
    }
    
    fprintf(file, "Data,CPFPaciente,CRM,Diagnostico\n");
    for (int i = 0; i < numConsultas; i++) {
        fprintf(file, "%s,%s,%s,%s\n", consultas[i].data, consultas[i].cpfPaciente, consultas[i].crmMedico, consultas[i].diagnostico);
    }
    fclose(file);
}

void cadastrarPaciente(Paciente *paciente) {
    printf("Digite o nome do paciente: ");
    scanf(" %49[^\n]", paciente->nome);
    printf("Digite a data de nascimento (dd/mm/yyyy): ");
    scanf(" %10[^\n]", paciente->dataNascimento);
    printf("Digite o CPF do paciente: ");
    scanf(" %14[^\n]", paciente->cpf);
    printf("Digite os sintomas: ");
    scanf(" %[^\n]", paciente->sintomas);
    paciente->numConsultas = 0;
}

void cadastrarMedico(Medico *medico) {
    printf("Digite o nome do médico: ");
    scanf(" %49[^\n]", medico->nome);
    printf("Digite a especialização do médico: ");
    scanf(" %49[^\n]", medico->especializacao);
    printf("Digite o CRM do médico: ");
    scanf(" %14[^\n]", medico->crm);
    printf("Disponibilidade (1 para disponível, 0 para indisponível): ");
    scanf("%d", &medico->disponibilidade);
}

void registrarConsulta(Consulta *consultas, int *numConsultas, const char *cpfPaciente, const char *crmMedico) {
    if (*numConsultas >= MAX_CONSULTAS) {
        printf("Máximo de consultas atingido!\n");
        return;
    }
    
    printf("Data da consulta (dd/mm/yyyy): ");
    scanf(" %10[^\n]", consultas[*numConsultas].data);
    strcpy(consultas[*numConsultas].cpfPaciente, cpfPaciente);
    strcpy(consultas[*numConsultas].crmMedico, crmMedico);
    printf("Digite o diagnóstico: ");
    scanf(" %[^\n]", consultas[*numConsultas].diagnostico);
    
    (*numConsultas)++;
}

void listarConsultasPaciente(Consulta *consultas, int numConsultas, const char *cpfPaciente) {
    printf("Consultas do paciente %s:\n", cpfPaciente);
    for (int i = 0; i < numConsultas; i++) {
        if (strcmp(consultas[i].cpfPaciente, cpfPaciente) == 0) {
            printf("Data: %s, CRM do Médico: %s, Diagnóstico: %s\n", consultas[i].data, consultas[i].crmMedico, consultas[i].diagnostico);
        }
    }
}

void listarConsultasMedico(Consulta *consultas, int numConsultas, const char *crmMedico) {
    printf("Consultas do médico %s:\n", crmMedico);
    for (int i = 0; i < numConsultas; i++) {
        if (strcmp(consultas[i].crmMedico, crmMedico) == 0) {
            printf("Data: %s, CPF do Paciente: %s, Diagnóstico: %s\n", consultas[i].data, consultas[i].cpfPaciente, consultas[i].diagnostico);
        }
    }
}

void listarMedicosDisponiveis(Medico *medicos, int numMedicos, const char *especializacao) {
    printf("Médicos disponíveis:\n");
    int medicosEncontrados = 0;
    
    for (int i = 0; i < numMedicos; i++) {
        if (medicos[i].disponibilidade == 1 && (especializacao == NULL || strcmp(medicos[i].especializacao, especializacao) == 0)) {
            printf("Nome: %s, Especialização: %s, CRM: %s\n", medicos[i].nome, medicos[i].especializacao, medicos[i].crm);
            medicosEncontrados++;
        }
    }
    
    if (medicosEncontrados == 0) {
        printf("Nenhum médico disponível encontrado com esses critérios.\n");
    }
}

void buscarPacientes(Paciente *pacientes, int numPacientes, const char *nomeFiltro, const char *cpfFiltro) {
    printf("Pacientes encontrados:\n");
    int pacientesEncontrados = 0;
    
    for (int i = 0; i < numPacientes; i++) {
        if ((nomeFiltro == NULL || strstr(pacientes[i].nome, nomeFiltro) != NULL) &&
            (cpfFiltro == NULL || strcmp(pacientes[i].cpf, cpfFiltro) == 0)) {
            printf("Nome: %s, Data de Nascimento: %s, CPF: %s, Sintomas: %s\n",
                   pacientes[i].nome, pacientes[i].dataNascimento, pacientes[i].cpf, pacientes[i].sintomas);
            pacientesEncontrados++;
        }
    }
    
    if (pacientesEncontrados == 0) {
        printf("Nenhum paciente encontrado com esses critérios.\n");
    }
}

void exibirMenu() {
    printf("=== Sistema de Triagem ===\n");
    printf("1. Cadastrar paciente\n");
    printf("2. Cadastrar médico\n");
    printf("3. Registrar consulta\n");
    printf("4. Listar consultas de um paciente\n");
    printf("5. Listar consultas de um médico\n");
    printf("6. Listar médicos disponíveis (com filtro)\n");
    printf("7. Buscar pacientes (com filtro)\n");
    printf("8. Sair\n");
    printf("Escolha uma opção: ");
}

int main() {
    Paciente pacientes[100];
    Medico medicos[50];
    Consulta consultas[100];
    int numPacientes = 0, numMedicos = 0, numConsultas = 0;
    int opcao;

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
                char cpfPaciente[15], crmMedico[15];
                printf("Digite o CPF do paciente: ");
                scanf(" %14[^\n]", cpfPaciente);
                printf("Digite o CRM do médico: ");
                scanf(" %14[^\n]", crmMedico);
                registrarConsulta(consultas, &numConsultas, cpfPaciente, crmMedico);
                salvarConsultas(consultas, numConsultas);
                break;
            }
            case 4: {
                char cpfPaciente[15];
                printf("Digite o CPF do paciente: ");
                scanf(" %14[^\n]", cpfPaciente);
                listarConsultasPaciente(consultas, numConsultas, cpfPaciente);
                break;
            }
            case 5: {
                char crmMedico[15];
                printf("Digite o CRM do médico: ");
                scanf(" %14[^\n]", crmMedico);
                listarConsultasMedico(consultas, numConsultas, crmMedico);
                break;
            }
            case 6: {
                char especializacao[50];
                printf("Digite a especialização (ou deixe em branco para listar todos): ");
                scanf(" %49[^\n]", especializacao);
                listarMedicosDisponiveis(medicos, numMedicos, (strlen(especializacao) > 0 ? especializacao : NULL));
                break;
            }
            case 7: {
                char nomeFiltro[50], cpfFiltro[15];
                printf("Digite parte do nome do paciente (ou deixe em branco para ignorar): ");
                scanf(" %49[^\n]", nomeFiltro);
                printf("Digite o CPF do paciente (ou deixe em branco para ignorar): ");
                scanf(" %14[^\n]", cpfFiltro);
                buscarPacientes(pacientes, numPacientes, (strlen(nomeFiltro) > 0 ? nomeFiltro : NULL), (strlen(cpfFiltro) > 0 ? cpfFiltro : NULL));
                break;
            }
            case 8:
                exit(0);
            default:
                printf("Opção inválida!\n");
        }
    }
    return 0;
}
