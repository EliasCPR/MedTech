-- Tabela Médico
CREATE TABLE Medico (
    ID_Medico INTEGER PRIMARY KEY,
    CRM INTEGER NOT NULL,
    Nome CHAR(100) NOT NULL,
    Disponibilidade DATETIME,
    Especializacao CHAR(50)
);

-- Tabela Paciente
CREATE TABLE Paciente (
    ID_Paciente INTEGER PRIMARY KEY,
    Nome CHAR(100) NOT NULL,
    Data_Nascimento DATE NOT NULL,
    Sintomas CHAR(255)
);

-- Tabela Histórico
CREATE TABLE Historico (
    ID_Historico INTEGER PRIMARY KEY,
    DataRegistro DATETIME NOT NULL,
    Procedimento CHAR(100),
    Medicamento CHAR(100),
    ProximoRetorno DATETIME,
    ID_Paciente INTEGER NOT NULL,
    FOREIGN KEY (ID_Paciente) REFERENCES Paciente(ID_Paciente)
);

-- Tabela Consulta
CREATE TABLE Consulta (
    ID_Consulta INTEGER PRIMARY KEY,
    CPF_Paciente VARCHAR(11) NOT NULL,
    CRM INTEGER NOT NULL,
    Diagnostico CHAR(255),
    ID_Paciente INTEGER NOT NULL,
    ID_Medico INTEGER NOT NULL,
    FOREIGN KEY (ID_Paciente) REFERENCES Paciente(ID_Paciente),
    FOREIGN KEY (ID_Medico) REFERENCES Medico(ID_Medico)
);

-- Tabela Procedimento
CREATE TABLE Procedimento (
    ID_Procedimento INTEGER PRIMARY KEY,
    Descricao CHAR(255),
    Nome CHAR(100)
);
