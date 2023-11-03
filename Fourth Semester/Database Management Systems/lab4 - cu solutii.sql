Use Hotels;
-- Dirty Reads Transaction 2: select + delay + select
-- Order of the operations: update - select - rollback - select
go
CREATE or alter PROCEDURE Dirty_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED	-- !!!!!!!!!!!
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

EXECUTE Dirty_Reads_T2;

-- Solution:
go
CREATE or alter PROCEDURE Dirty_Reads_T2_Solution AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Rezervari', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Rezervari', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Dirty_Reads_T2_Solution;


-- Non-Repeatable Reads Transaction 2: select + delay + select
-- Order of the operations: select - update - select
go
CREATE or alter PROCEDURE Non_Repeatable_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED	-- !!!!!!!!!
	BEGIN TRAN
	BEGIN TRY
		WAITFOR DELAY '00:00:05'
		UPDATE Clienti SET nrtel_c = 9999 WHERE nume_c = 'Popa'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Non_Repeatable_Reads_T2;


-- Deadlock Transaction 2 : update on MANAGER + delay + update on MAGAZIN
go
CREATE or alter PROCEDURE Deadlock_T2 AS
BEGIN
	SET DEADLOCK_PRIORITY HIGH
	--SET DEADLOCK_PRIORITY LOW
	BEGIN TRAN
	BEGIN TRY
		UPDATE Clienti SET nrtel_c = 777 where nume_c = 'Pop'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		UPDATE Admini SET admin_nume = 'DEADLOCK' WHERE admin_id=2
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Admini', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Deadlock_T2;

--solution
go
CREATE or alter PROCEDURE Deadlock_T2_Solution AS
BEGIN
	--SET DEADLOCK_PRIORITY HIGH
	SET DEADLOCK_PRIORITY LOW
	BEGIN TRAN
	BEGIN TRY
		UPDATE Clienti SET nrtel_c = 777 where nume_c = 'Pop'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:05'
		UPDATE Admini SET admin_nume = 'DEADLOCK' WHERE admin_id=2
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Admini', CURRENT_TIMESTAMP)
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		if ERROR_NUMBER() = 1205
		begin 
		rollback;
		BEGIN TRAN
			UPDATE Clienti SET nrtel_c = 777 where nume_c = 'Pop'
				INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Clienti', CURRENT_TIMESTAMP)
			WAITFOR DELAY '00:00:05'
			UPDATE Admini SET admin_nume = 'DEADLOCK' WHERE admin_id=2
				INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('UPDATE', 'Admini', CURRENT_TIMESTAMP)
			COMMIT TRAN
			SELECT 'Transaction committed after deadlock' AS [Message]
		end
	END CATCH
END

EXECUTE Deadlock_T2_solution;

select * from Clienti;
select * from Admini;
UPDATE Admini SET admin_nume = 'kkk' WHERE admin_id=2
UPDATE Clienti SET nrtel_c = 11111 where nume_c = 'Pop'

-- Phantom Reads Transaction 2: select + delay + select
-- Order of the operations: select - insert - select
go
CREATE or alter PROCEDURE Phantom_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ		-- !!!!!!!!
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

EXECUTE Phantom_Reads_T2;

-- Solution:
go
CREATE or alter PROCEDURE Phantom_Reads_T2_Solution AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRAN
	BEGIN TRY
		SELECT * FROM Clienti
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Clienti', CURRENT_TIMESTAMP)
		WAITFOR DELAY '00:00:10'
			INSERT INTO Logs(operationType, tableName, executionTime) VALUES ('SELECT', 'Clienti', CURRENT_TIMESTAMP)
		SELECT * FROM Clienti
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

EXECUTE Phantom_Reads_T2_Solution;

select * from Clienti