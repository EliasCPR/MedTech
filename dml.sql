-- Inserindo médicos
INSERT INTO Medico (ID_Medico, CRM, Nome, Disponibilidade, Especializacao)
VALUES 
(1, 123456, 'Dr. João Silva', '2024-11-27 09:00:00', 'Cardiologia'),
(2, 789012, 'Dra. Maria Oliveira', '2024-11-27 14:00:00', 'Pediatria');

-- Inserindo pacientes
INSERT INTO Paciente (ID_Paciente, Nome, Data_Nascimento, Sintomas)
VALUES 
(1, 'Ana Paula', '1990-05-15', 'Febre e tosse'),
(2, 'Carlos Eduardo', '1985-08-22', 'Dor abdominal');

-- Inserindo histórico
INSERT INTO Historico (ID_Historico, DataRegistro, Procedimento, Medicamento, ProximoRetorno, ID_Paciente)
VALUES 
(1, '2024-11-20 10:00:00', 'Consulta de rotina', 'Paracetamol', '2024-12-20', 1);

-- Inserindo consultas
INSERT INTO Consulta (ID_Consulta, CPF_Paciente, CRM, Diagnostico, ID_Paciente, ID_Medico)
VALUES 
(1, '12345678901', 123456, 'Gripe', 1, 1),
(2, '98765432100', 789012, 'Gastrite', 2, 2);

-- Inserindo procedimentos
INSERT INTO Procedimento (ID_Procedimento, Descricao, Nome)
VALUES 
(1, 'Aplicação de vacina', 'Vacina contra gripe'),
(2, 'Exame de sangue', 'Hemograma completo');
