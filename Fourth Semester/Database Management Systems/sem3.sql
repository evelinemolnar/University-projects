USE Seminar2SGBD2242023;
--tranzactie autocommit
SELECT * FROM Categorii;
--tranzactie autocommit
SELECT * FROM Produse;
--verificarea numarului de tranzactii deschise pe conexiunea curenta
SELECT @@TRANCOUNT;
--tranzactie explicita
BEGIN TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;
INSERT INTO Categorii (nume) VALUES ('pantofi');
SELECT * FROM Categorii;
ROLLBACK TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;
--tranzactii implicite
SET IMPLICIT_TRANSACTIONS ON;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;
SELECT @@TRANCOUNT;
INSERT INTO Categorii (nume) VALUES ('pantofi');
SELECT * FROM Categorii;
COMMIT TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;
SELECT @@TRANCOUNT;
ROLLBACK TRAN;
SET IMPLICIT_TRANSACTIONS OFF;
SELECT @@TRANCOUNT;
SELECT * FROM Produse;
SELECT @@TRANCOUNT;
--imbricarea tranzactiilor
BEGIN TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;
INSERT INTO Categorii (nume) VALUES ('medicamente');
BEGIN TRAN;
SELECT * FROM Categorii;
SELECT @@TRANCOUNT;
DELETE FROM Categorii WHERE nume='pantofi';
COMMIT TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;
ROLLBACK TRAN;
SELECT @@TRANCOUNT;
SELECT * FROM Categorii;