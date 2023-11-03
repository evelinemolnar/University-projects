USE Hotels;

go
CREATE or alter PROCEDURE Deadlock_T1_C# AS
BEGIN
	BEGIN TRAN
	UPDATE Clienti SET nrtel_c = 777 where nume_c = 'Pop'
		INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
	WAITFOR DELAY '00:00:05'
	UPDATE Admini SET admin_nume = 'DEADLOCK' WHERE admin_id=2
		INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Admini', CURRENT_TIMESTAMP)
	COMMIT TRAN
END