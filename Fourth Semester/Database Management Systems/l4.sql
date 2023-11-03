use Hotels

-- Transaction A
BEGIN TRANSACTION
SELECT * FROM Clienti WITH (READUNCOMMITTED)
-- Read uncommitted data modified by Transaction B
COMMIT TRANSACTION

-- Transaction B
BEGIN TRANSACTION
UPDATE Clienti SET adresa_c = 'New Address' WHERE id = 1
COMMIT TRANSACTION

--solution read commited

--2
-- Transaction A
CREATE procedure Transaction1
AS
BEGIN
    SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
    BEGIN TRANSACTION
    
    -- Read a row
    SELECT * FROM Rezervari WHERE id = 1
    
    -- Wait for a short while to simulate Transaction B
    WAITFOR DELAY '00:00:02'
    
    -- Read the same row again
    SELECT * FROM Rezervari WHERE id = 1
    
    COMMIT TRANSACTION
END

-- Transaction B
CREATE PROCEDURE Transaction2
AS
BEGIN
    BEGIN TRANSACTION
    
    -- Modify the row
    UPDATE Rezervari SET status_id = 3 WHERE id = 1
    
    COMMIT TRANSACTION
END

--Use a higher isolation level, such as "SERIALIZABLE," which guarantees consistent reads by placing shared locks on the accessed data until the transaction completes.

--3
-- Transaction A
BEGIN TRANSACTION
SELECT * FROM Rezervari WHERE check_in = '2023-05-23'
-- Read a set of rows based on a condition

-- Wait for a short while to simulate Transaction B
WAITFOR DELAY '00:00:02'

-- Read the same set of rows again
SELECT * FROM Rezervari WHERE check_in = '2023-05-23'
COMMIT TRANSACTION

-- Transaction B
BEGIN TRANSACTION
INSERT INTO Rezervari(client_id, admin_id, check_in, check_out, status_id)
VALUES (1,1, '2023-05-23', '2023-05-25', 1)
-- Insert new rows that meet the condition
COMMIT TRANSACTION

--Use a higher isolation level, such as "SERIALIZABLE," which prevents phantom reads by placing range locks on the accessed data until the transaction completes.
-- Transaction A
CREATE PROCEDURE Transaction4
AS
BEGIN
    BEGIN TRANSACTION
    
    -- Acquire Resource A
    SELECT * FROM Camere WITH (UPDLOCK, HOLDLOCK) WHERE camera_id = 1
    
    -- Wait for a short while to simulate Transaction B
    WAITFOR DELAY '00:00:02'
    
    -- Acquire Resource B
    SELECT * FROM CamereRezervate WITH (UPDLOCK, HOLDLOCK) WHERE camera_id = 1
    
    COMMIT TRANSACTION
END

-- Transaction B
CREATE PROCEDURE TransactionB
AS
BEGIN
    BEGIN TRANSACTION
    
    -- Acquire Resource B
    SELECT * FROM CamereRezervate WITH (UPDLOCK, HOLDLOCK) WHERE camera_id = 1
    
    -- Wait for a short while to simulate Transaction A
    WAITFOR DELAY '00:00:02'
    
    -- Acquire Resource A
    SELECT * FROM Camere WITH (UPDLOCK, HOLDLOCK) WHERE camera_id = 1
    
    COMMIT TRANSACTION
END

--Implement a mechanism to detect and resolve deadlocks automatically, such as using a deadlock detection algorithm and a timeout mechanism.
--Ensure that transactions always acquire resources in a consistent order to avoid circular dependencies.
