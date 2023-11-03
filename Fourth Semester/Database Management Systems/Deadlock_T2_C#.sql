USE Hotels;

go
CREATE or alter PROCEDURE Deadlock_T2_C# AS
BEGIN
	SET DEADLOCK_PRIORITY HIGH
	-- SET DEADLOCK_PRIORITY LOW
	BEGIN TRAN
	UPDATE Admini SET admin_nume = 'AdminD' WHERE admin_id=2
		INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Admini', CURRENT_TIMESTAMP)
	WAITFOR DELAY '00:00:05'
	UPDATE Clienti SET nrtel_c = 777 where nume_c = 'Pop'
		INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
	COMMIT TRAN
END

SELECT * FROM Clienti
insert into Clienti(nume_c,prenume_c,nrtel_c) values ('DeadlockNume', 'DadlockPrenume', 999999)