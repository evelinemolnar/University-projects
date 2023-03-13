
--PROCEDURI STOCATE

CREATE TABLE VersiuneaCurenta( versiune SMALLINT );
INSERT INTO VersiuneaCurenta(versiune ) VALUES(0);
GO

--procedura 1 modificare tip coloana
CREATE OR ALTER PROCEDURE UpdateVersiune1
AS
BEGIN
	ALTER TABLE Plati
	ALTER COLUMN valoare MONEY

END;
GO

CREATE OR ALTER PROCEDURE DownVersiune1
AS
BEGIN
	SET NOCOUNT ON;

	ALTER TABLE Plati
	ALTER COLUMN valoare INT;

END;
GO


--P2--adauga o constrangere de valoare implicita pentru un camp
GO
CREATE OR ALTER PROCEDURE UpdateVersiune2
AS
BEGIN
    IF (EXISTS (SELECT * FROM sys.default_constraints WHERE name='constrangere'))
		RAISERROR ('Constrangerea este deja setata default!',10,1);
	ELSE
		BEGIN
			ALTER TABLE Camere
			ADD CONSTRAINT constrangere DEFAULT 1 FOR tip_id
		END;

END;
GO

CREATE OR ALTER PROCEDURE DownVersiune2
AS
    IF NOT EXISTS(SELECT * FROM sys.default_constraints WHERE NAME = 'constrangere')
	    RAISERROR ('Nu exista o constrangere de tip default!',10,1);
	ELSE
        BEGIN
            SET NOCOUNT ON;

            ALTER TABLE Camere
            DROP CONSTRAINT constrangere;

        END
GO


--P3--creeaza/sterge o tabela

CREATE OR ALTER PROCEDURE UpdateVersiune3
AS
BEGIN

    IF (NOT EXISTS (SELECT * FROM sys.tables WHERE name='Facilitati'))
		BEGIN
			CREATE TABLE Facilitati(
				id_facilitate INT PRIMARY KEY IDENTITY,
				nume_facilitate NVARCHAR(30) NOT NULL
			)

		END;
	ELSE
		RAISERROR ('Tabelul Facilitati a fost deja creat!',10,1);

END;
GO

CREATE OR ALTER PROCEDURE DownVersiune3
AS

	IF NOT EXISTS(SELECT * FROM sys.tables WHERE NAME = 'Facilitati')
	BEGIN
		PRINT 'Nu exista o tabela Angajati in baza de date.'
	END
	ELSE
	BEGIN
		SET NOCOUNT ON;

		DROP TABLE Facilitati;

	END
GO

--P4--adaunga un camp nou

CREATE OR ALTER PROCEDURE UpdateVersiune4
AS
	IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Admini')
	BEGIN
		PRINT 'Nu exista tabela Admini.'
	END
	ELSE IF EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Admini' AND COLUMN_NAME = 'admin_telefon')
	BEGIN
		PRINT 'Exista campul admin_telefon in tabela Admini'
	END
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE Admini
			ADD admin_telefon INT;

		END
GO

CREATE OR ALTER PROCEDURE DownVersiune4
AS
IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'Admini')
	BEGIN
		PRINT 'Nu exista tabela Admini.'
	END
	ELSE IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME = 'Admini' AND COLUMN_NAME = 'admin_telefon')
	BEGIN
		PRINT 'Nu exista campul admin_telefon in tabela Admini'
	END
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE Admini
			DROP COLUMN admin_telefon;

		END
GO

--P5--creeaza/sterge o constangere cheie straina
GO
CREATE OR ALTER PROCEDURE UpdateVersiune5
AS
IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'TipCamera')
	BEGIN
		PRINT 'Nu exista tabela TipCamera.'
	END
	ELSE IF EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_TipCamera')
	BEGIN
		PRINT 'Exista constrangerea de cheie straina pe tabela TipCamera';
	END
	ELSE
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE TipCamera
            ADD status_id INT
			ALTER TABLE TipCamera
			ADD CONSTRAINT FK_TipCamera FOREIGN KEY (status_id) REFERENCES StatusRezervare(status_id);

		END
GO

CREATE OR ALTER PROCEDURE DownVersiune5
AS
IF NOT EXISTS(SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'TipCamera')
	BEGIN
		PRINT 'Nu exista tabela TipCamera.'
	END
	ELSE IF NOT EXISTS(SELECT * FROM sys.foreign_keys WHERE NAME = 'FK_TipCamera')
	BEGIN
		PRINT 'Nu xista constrangerea de cheie straina pe tabela Admini';
	END
		BEGIN
			SET NOCOUNT ON;

			ALTER TABLE TipCamera
			DROP CONSTRAINT FK_TipCamera
			ALTER TABLE TipCamera
            DROP COLUMN status_id

		END
GO


CREATE OR ALTER PROCEDURE Transforma
@VersiuneDorita SMALLINT
AS
BEGIN
	DECLARE @VersiuneCurenta SMALLINT;
	DECLARE @procedure VARCHAR(50);
	SET @VersiuneCurenta =(SELECT versiune FROM VersiuneaCurenta);

        IF @VersiuneDorita = @VersiuneCurenta OR @VersiuneDorita > 5 OR @VersiuneDorita < 0
		RETURN;

	IF @VersiuneDorita > @VersiuneCurenta
	BEGIN
		WHILE @VersiuneDorita > @VersiuneCurenta
		BEGIN
			SET @VersiuneCurenta = @VersiuneCurenta + 1
			SET @procedure = 'UpdateVersiune' + CAST(@VersiuneCurenta AS VARCHAR);
			PRINT @procedure;
			EXEC @procedure
		END;
	END;
	ELSE
	BEGIN
		WHILE @VersiuneDorita < @VersiuneCurenta
		BEGIN
			SET @procedure = 'DownVersiune' + CAST(@VersiuneCurenta AS VARCHAR);
			SET @VersiuneCurenta = @VersiuneCurenta - 1
			PRINT @procedure;
			EXEC @procedure
		END;
	END;

	UPDATE VersiuneaCurenta SET versiune=@VersiuneDorita;
END
GO

UPDATE VersiuneaCurenta SET versiune=0

EXEC Transforma @VersiuneDorita=5

