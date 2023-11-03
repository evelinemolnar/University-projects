Use S12023

CREATE TABLE Logs
(
  id INT IDENTITY,
  operationType VARCHAR(20),
  tableName VARCHAR(20),
  executionTime DATETIME,
  CONSTRAINT pk_Logs PRIMARY KEY(id)
)

go
CREATE or alter PROCEDURE Dirty_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED	-- !!!!!!!!!!!
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Autori
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Autori', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Autori
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Autori', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T2;

-- Solution:
go
CREATE or alter PROCEDURE Dirty_Reads_T2_Solution AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Autori
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Autori', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Autori
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Autori', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T2_Solution;
