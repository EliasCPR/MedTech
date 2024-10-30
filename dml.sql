-- Inserindo dados na tabela de pacientes
INSERT INTO Pacientes (cpf, nome, data_nascimento, sintomas) VALUES
('12345678901', 'João Silva', TO_DATE('1985-05-10', 'YYYY-MM-DD'), 'Dor de cabeça, febre'),
('23456789012', 'Maria Oliveira', TO_DATE('1990-07-20', 'YYYY-MM-DD'), 'Tosse seca, dor de garganta'),
('34567890123', 'Carlos Pereira', TO_DATE('1975-03-15', 'YYYY-MM-DD'), 'Dor abdominal, náusea');

-- Inserindo dados na tabela de médicos
INSERT INTO Medicos (crm, nome, especializacao, disponibilidade) VALUES
('123456', 'Dr. Fernando Almeida', 'Pediatria', 'Y'),
('234567', 'Dra. Ana Costa', 'Clínica Geral', 'Y'),
('345678', 'Dr. Roberto Santos', 'Cardiologia', 'N');

-- Inserindo dados na tabela de consultas
INSERT INTO Consultas (data, cpf_paciente, crm_medico, diagnostico) VALUES
(TO_DATE('2024-10-01', 'YYYY-MM-DD'), '12345678901', '123456', 'Migraine'),
(TO_DATE('2024-10-02', 'YYYY-MM-DD'), '23456789012', '234567', 'Faringite'),
(TO_DATE('2024-10-03', 'YYYY-MM-DD'), '34567890123', '345678', 'Infarto do miocárdio');