USE S12023

CREATE TABLE Logs
(
  id INT IDENTITY,
  operationType VARCHAR(20),
  tableName VARCHAR(20),
  executionTime DATETIME,
  CONSTRAINT pk_Logs PRIMARY KEY(id)
)

go
CREATE or alter PROCEDURE Dirty_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		UPDATE Autori set email_autor = 'emaildirty' WHERE nume_autor = 'Autor1'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Autori', CURRENT_TIMESTAMP)
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