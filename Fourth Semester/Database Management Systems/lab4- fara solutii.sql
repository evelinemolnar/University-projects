USE Hotels;

/*
CREATE TABLE Logs
(
  id INT IDENTITY,
  operationType VARCHAR(20),
  tableName VARCHAR(20),
  executionTime DATETIME,
  CONSTRAINT pk_Logs PRIMARY KEY(id)
)
*/

-- Dirty Reads Transaction 1: update + delay + rollback
go
CREATE or alter PROCEDURE Dirty_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		UPDATE Clienti set nrtel_c = 1000 WHERE nume_c = 'Pop'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked - good!' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked - bad!' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T1;
-- Non-Repeatable Reads Transaction 1: delay + update + commit
go
CREATE or alter PROCEDURE Non_Repeatable_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Clienti', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Clienti', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Non_Repeatable_Reads_T1;
update Clienti set nrtel_c=10000 where nume_c='Popa'

-- Solution
go
CREATE or alter PROCEDURE Non_Repeatable_Reads_T2_Solution AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Clienti', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Clienti', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Non_Repeatable_Reads_T2_Solution;

-- Deadlock Transaction 1: update on clienti + delay + update on Admin
go
CREATE or alter PROCEDURE Deadlock_T1 AS
BEGIN
	--set DEADLOCK_PRIORITY HIGH
	BEGIN TRAN
	BEGIN TRY
		UPDATE Admini SET admin_nume = 'DEADLOCK2222' WHERE admin_id=2
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Admini', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET nrtel_c = 888 where nume_c = 'Pop'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		if ERROR_NUMBER() = 1205
		begin
			ROLLBACK TRAN
			SELECT 'Transaction rollbacked' AS [Message]
		end
	END CATCH
END

EXECUTE Deadlock_T1;


-- Phantom Reads Transaction 1: delay + insert + commit
go
CREATE or alter PROCEDURE Phantom_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		WAITFOR DELAY '00:00:05'
		INSERT INTO Clienti(nume_c,prenume_c,nrtel_c) VALUES ('ssss','sss', 669996)
		INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('INSERT', 'Clienti', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH

		ROLLBACK TRAN
		print ERROR_NUMBER()
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Phantom_Reads_T1;



SELECT * FROM sys.sysprocesses WHERE open_tran = 1
