CREATE DATABASE Seminar2SGBD2242023;
GO
USE Seminar2SGBD2242023;
CREATE TABLE Categorii
(cod_c INT PRIMARY KEY IDENTITY,
nume VARCHAR(100)
);
CREATE TABLE Produse
(cod_p INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
pret REAL,
data_fabricatiei DATE,
cod_c INT FOREIGN KEY REFERENCES Categorii(cod_c)
);
INSERT INTO Categorii (nume) VALUES ('haine'), ('jucarii'), ('tastaturi'),
('alimente'), ('mobila'), ('produse cosmetice'),('produse pirotehnice');
INSERT INTO Produse (nume, pret, data_fabricatiei, cod_c) VALUES
('tricou alb',29,'2002-05-03',1), 
('manusi',199,'2016-11-29',1),('Bakugan',93,'2008-12-01',2),
('Beyblade',75,'2012-12-12',2),('Royal Kludge RK61 HotSwap',350,'2020-03-14',
3),('Razer Huntsman Chroma',500,'2018-07-28',3),
('sos teriyaki',10,'2023-03-07',4), ('mar',0.93,'2022-09-20',4),
('birou reglabil ikea culoarea nucului',2000,'2023-01-02',5),
('Eyeliner',230,'2021-04-09',6), ('FP3',12,'2022-09-02',6);
SELECT * FROM Categorii;
SELECT * FROM Produse;
