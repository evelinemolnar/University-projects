
use Hotels;
go

CREATE TABLE Clienti
(
    client_id INT PRIMARY KEY IDENTITY,
    nume_c VARCHAR(100) NOT NULL ,
    prenume_c VARCHAR(100) NOT NULL,
    adresa_c VARCHAR(100) ,
    oras_c VARCHAR(100) ,
    tara_c VARCHAR(100),
    nrtel_c INT NOT NULL UNIQUE
);

ALTER TABLE Clienti
ADD email_c VARCHAR(100) UNIQUE;

CREATE TABLE Admini
(
    admin_id INT PRIMARY KEY IDENTITY,
    admin_nume VARCHAR(100)
);

CREATE TABLE StatusRezervare
(
    status_id INT PRIMARY KEY IDENTITY,
    status VARCHAR(100),
    descriere VARCHAR(100),
);

CREATE TABLE Rezervari
(
    rez_id INT PRIMARY KEY IDENTITY,
    client_id INT FOREIGN KEY REFERENCES Clienti(client_id) ON UPDATE NO ACTION ON DELETE NO ACTION,
    admin_id INT FOREIGN KEY REFERENCES Admini(admin_id) ON UPDATE NO ACTION ON DELETE NO ACTION,
    check_in DATETIME,
    check_out DATETIME,
    status_id INT FOREIGN KEY REFERENCES StatusRezervare(status_id) ON UPDATE CASCADE ON DELETE NO ACTION

);

CREATE TABLE CamereRezervate
(
    rez_id INT,
    camera_id INT,
    rating VARCHAR(100),
    CONSTRAINT fk_Rezervari FOREIGN KEY (rez_id) REFERENCES Rezervari(rez_id),
    CONSTRAINT fk_Camere FOREIGN KEY (camera_id) REFERENCES Camere(camera_id),
    CONSTRAINT pk_CamereRezervate PRIMARY KEY (rez_id,camera_id)
);


CREATE TABLE Camere
(
    camera_id  INT PRIMARY KEY IDENTITY,
    nr_camera INT ,
    etaj INT,
    tip_id INT FOREIGN KEY REFERENCES TipCamera(tip_id) ON UPDATE CASCADE ON DELETE CASCADE
);

CREATE TABLE Facturi
(
    factura_id INT PRIMARY KEY IDENTITY,
    rez_id INT FOREIGN KEY REFERENCES Rezervari(rez_id) ON UPDATE no action ON DELETE no action ,
    client_id INT FOREIGN KEY REFERENCES Clienti(client_id) ON UPDATE no action ON DELETE no action ,
    valoare INT NOT NULL
);

CREATE TABLE Plati
(
    plata_id INT PRIMARY KEY IDENTITY,
    factura_id INT FOREIGN KEY REFERENCES Facturi(factura_id) ON UPDATE CASCADE ON DELETE CASCADE ,
    data DATETIME,
    valoare INT,
    statusplata_id INT FOREIGN KEY REFERENCES StatusPlata(statusplata_id) ON UPDATE CASCADE ON DELETE CASCADE,
    tipplata_id INT FOREIGN KEY REFERENCES TipPlata(tipplata_id) ON UPDATE CASCADE ON DELETE CASCADE
);

ALTER TABLE Facturi
DROP COLUMN valoare;

CREATE TABLE StatusPlata
(
    statusplata_id INT PRIMARY KEY IDENTITY,
    status VARCHAR(100),

);

CREATE TABLE TipPlata
(
    tipplata_id INT PRIMARY KEY IDENTITY,
    tip VARCHAR(100)
);


CREATE TABLE TipCamera
(
    tip_id INT PRIMARY KEY IDENTITY,
    tip VARCHAR(100),
    descriere VARCHAR(100)
);






USE Hotels
Select *
From Clienti

/* clienti ce folosesc yahoo mail */
SELECT DISTINCT nume_c,Clienti.email_c
FROM Clienti
WHERE Clienti.email_c LIKE '_%@yahoo.com'

/* afiseaza toti clientii din Romania*/
SELECT DISTINCT nume_c, tara_c
FROM Clienti
WHERE tara_c LIKE 'Romania'

/* toate rezervarile confirmate */
SELECT nume_c, S.status
FROM Clienti C, Rezervari R, StatusRezervare S
WHERE C.client_id=R.client_id AND R.status_id=S.status_id AND S.status LIKE 'confirmat'


/*toate rezervarile  de astazi si numarul de camera  m-m*/
SELECT nume_c, check_in,nr_camera
FROM Clienti C
    INNER JOIN Rezervari R2 on C.client_id = R2.client_id
    INNER JOIN CamereRezervate CR on R2.rez_id = CR.rez_id
    INNER JOIN Camere C2 on C2.camera_id = CR.camera_id
WHERE R2.check_in=CAST( GETDATE() AS Date )


/* clientii grupati in functie de tara care au oferit cel mai mare rating camerei inchiriate */
SELECT nume_c,tara_c, rating
FROM Clienti C
    INNER JOIN Rezervari R2 on C.client_id = R2.client_id
    INNER JOIN CamereRezervate CR on R2.rez_id = CR.rez_id
    INNER JOIN Camere C2 on C2.camera_id = CR.camera_id
    INNER JOIN TipCamera TC on TC.tip_id = C2.tip_id
GROUP BY tara_c, nume_c, rating
HAVING MAX(rating) = 10

/* camerele identificate prin numar si grupate in functie de tipul lor*/
SELECT nr_camera, tip
FROM Camere C,TipCamera T
WHERE  C.tip_id=T.tip_id
GROUP BY tip,nr_camera

/* camere ocupate de la etajul 2 grupate dupa tip */

SELECT nr_camera, etaj, tip
FROM Camere C
    INNER JOIN CamereRezervate CR on C.camera_id = CR.camera_id
    INNER JOIN Rezervari R2 on R2.rez_id = CR.rez_id
    INNER JOIN TipCamera TC on TC.tip_id = C.tip_id
WHERE etaj=2
GROUP BY tip, etaj, nr_camera

/* facturile achitate cu cardul cu status de efectuat cu max(val)=1500  grupate dupa data */

SELECT F.factura_id, P.data_p, valoare
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN StatusPlata SP on P.statusplata_id = SP.statusplata_id
    INNER JOIN TipPlata TP on P.tipplata_id = TP.tipplata_id
WHERE SP.status LIKE 'efectuata' AND TP.tip LIKE 'card'
GROUP BY P.data_p, F.factura_id, F.factura_id, valoare
HAVING MAX(valoare)=1500

/*  facturile achitate astazi  */

SELECT F.factura_id, P.data_p, valoare
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN TipPlata TP on P.tipplata_id = TP.tipplata_id
WHERE P.data_p = CAST( GETDATE() AS Date )

/* suma facturilor achitate */
SELECT SUM(P.valoare) AS Suma
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN StatusPlata SP on P.statusplata_id = SP.statusplata_id
WHERE SP.status LIKE 'efectuata'

/*  pretul camerelor rezervate*/
SELECT P.valoare, C2.nr_camera
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN TipPlata TP on P.tipplata_id = TP.tipplata_id
    INNER JOIN CamereRezervate CR on R2.rez_id = CR.rez_id
    INNER JOIN Camere C2 on C2.camera_id = CR.camera_id
    INNER JOIN TipCamera TC on TC.tip_id = C2.tip_id


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
