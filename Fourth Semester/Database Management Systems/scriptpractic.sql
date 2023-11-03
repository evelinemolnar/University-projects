USE master
GO
IF(EXISTS(SELECT * FROM sys.databases WHERE name='S12023'))
	DROP DATABASE S12023;
GO
CREATE DATABASE S12023;
GO
USE S12023;
GO
CREATE TABLE Tari
(cod_tara INT PRIMARY KEY IDENTITY,
 denumire VARCHAR(100),
 continent VARCHAR(100)
 );
 CREATE TABLE Autori
(cod_autor INT PRIMARY KEY IDENTITY,
 nume_autor VARCHAR(200),
 email_autor VARCHAR(150),
 data_nasterii DATE,
 cod_tara INT FOREIGN KEY REFERENCES Tari(cod_tara)
 ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Proiecte
(cod_proiect INT PRIMARY KEY IDENTITY,
 titlu VARCHAR(200),
 descriere VARCHAR(300),
 data_depunerii DATE,
 buget INT,
 cod_autor INT FOREIGN KEY REFERENCES Autori(cod_autor)
 ON UPDATE CASCADE ON DELETE CASCADE
);
CREATE TABLE Evaluatori
(cod_evaluator INT PRIMARY KEY IDENTITY,
 nume_evaluator VARCHAR(200),
 email_evaluator VARCHAR(200),
 companie VARCHAR(200)
);
CREATE TABLE Note
(cod_evaluator INT FOREIGN KEY REFERENCES Evaluatori(cod_evaluator)
 ON UPDATE CASCADE ON DELETE CASCADE,
 cod_proiect INT FOREIGN KEY REFERENCES Proiecte(cod_proiect)
 ON UPDATE CASCADE ON DELETE CASCADE,
 nota INT CHECK (nota BETWEEN 1 AND 10),
 CONSTRAINT pk_Note PRIMARY KEY (cod_evaluator, cod_proiect)
);
--Tari
INSERT INTO Tari (denumire, continent) VALUES ('Romania','Europa');
INSERT INTO Tari (denumire, continent) VALUES ('Portugalia','Europa');
INSERT INTO Tari (denumire, continent) VALUES ('Italia','Europa');
--Autori
INSERT INTO Autori (nume_autor, email_autor, data_nasterii, cod_tara) VALUES
('Autor1','autor1@gmail.com','1987-10-10',1);
INSERT INTO Autori (nume_autor, email_autor, data_nasterii, cod_tara) VALUES
('Autor2','autor2@gmail.com','1980-11-11',2);
INSERT INTO Autori (nume_autor, email_autor, data_nasterii, cod_tara) VALUES
('Autor3','autor3@gmail.com','1967-10-20',3);
--Proiecte Autor1
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect1 Autor1','Descriere Proiect1 Autor1','2020-03-04',10000,1);
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect2 Autor1','Descriere Proiect2 Autor1','2021-05-07',20000,1);
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect3 Autor1','Descriere Proiect3 Autor1','2022-09-16',100000,1);
--Proiecte Autor2
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect4 Autor2','Descriere Proiect4 Autor2','2020-04-04',100000,2);
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect5 Autor2','Descriere Proiect5 Autor2','2021-07-07',120000,2);
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect6 Autor2','Descriere Proiect6 Autor2','2022-08-26',200000,2);
--Proiecte Autor3
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect7 Autor3','Descriere Proiect7 Autor3','2020-02-24',80000,3);
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect8 Autor3','Descriere Proiect8 Autor3','2021-05-27',60000,3);
INSERT INTO Proiecte (titlu, descriere, data_depunerii, buget, cod_autor) VALUES
('Proiect9 Autor3','Descriere Proiect9 Autor3','2022-09-20',150000,3);
--Evaluatori
INSERT INTO Evaluatori (nume_evaluator, email_evaluator, companie) VALUES
('Evaluator1','evaluator1@companie1.com','Compania1');
INSERT INTO Evaluatori (nume_evaluator, email_evaluator, companie) VALUES
('Evaluator2','evaluator2@companie2.com','Compania2');
INSERT INTO Evaluatori (nume_evaluator, email_evaluator, companie) VALUES
('Evaluator3','evaluator3@companie3.com','Compania3');
--Note
INSERT INTO Note (cod_evaluator, cod_proiect, nota) VALUES (1,1,10);
INSERT INTO Note (cod_evaluator, cod_proiect, nota) VALUES (2,4,7);
INSERT INTO Note (cod_evaluator, cod_proiect, nota) VALUES (3,8,9);