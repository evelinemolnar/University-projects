CREATE OR ALTER PROCEDURE TestDatabase
AS
BEGIN
	SET NOCOUNT ON

	DECLARE @NoOfRows INT,  @testRunId INT
	DECLARE @IDTest INT, @TestName NVARCHAR(50)
	DECLARE @IDTable INT, @TableName NVARCHAR(50)
	DECLARE @IDView INT, @ViewName NVARCHAR(50)
	DECLARE @testStartTime DATETIME, @testFinishTime DATETIME
	DECLARE @auxStartTime DATETIME, @auxFinishTime DATETIME

	DECLARE CursorTeste cursor forward_only
	for select * from Tests
		open CursorTeste
		fetch next from CursorTeste into @IDTest,@TestName

		DELETE FROM TestRuns;
		DELETE FROM TestRunTables;
		DELETE FROM TestRunViews;

		while @@FETCH_STATUS = 0 begin
			-- DELETE_URI
			declare CursorDelete cursor forward_only
			for select T.Name, TT.NoOfRows, TT.TableID
				from Tables T inner join dbo.TestTables TT on T.TableID = TT.TableID
				where TestID = @IDTest
				order by Position

			open CursorDelete
			fetch next from CursorDelete into @TableName, @NoOfRows, @IDTable
			while @@FETCH_STATUS = 0 begin
				exec('delete from ' + @TableName)
				fetch next from CursorDelete into @TableName, @NoOfRows, @IDTable
			end
			close CursorDelete
			deallocate CursorDelete

			set @testStartTime = getdate()
			INSERT INTO TestRuns (Description, StartAt) VALUES (@TestName, @testStartTime)
			set @testRunId = @@IDENTITY;

			--INSERT_URI
			declare CursorInsert cursor forward_only
			for select T.Name, TT.NoOfRows, TT.TableID
				from Tables T inner join dbo.TestTables TT on T.TableID = TT.TableID
				where TestID = @IDTest
				order by Position desc
			open CursorInsert
			fetch next from CursorInsert into @TableName, @NoOfRows, @IDTable
			while @@FETCH_STATUS = 0 begin
				set @auxStartTime = getdate()
				exec Insert_Rows @NoOfRows, @TableName
				set @auxFinishTime = getdate()
				INSERT INTO TestRunTables (TestRunID, TableID, StartAt, EndAt) VALUES (@testRunId, @IDTable, @auxStartTime, @auxFinishTime)
				fetch next from CursorInsert into @TableName, @NoOfRows, @IDTable
			end
			close CursorInsert
			deallocate CursorInsert

			--VIEW_URI
			declare CursorView CURSOR FORWARD_ONLY
			for select TV.ViewID, V.Name
				from TestViews TV INNER JOIN Views V on TV.ViewID = V.ViewID
				where TV.TestID = @IDTest;
			open CursorView
			fetch next from CursorView INTO @IDView, @ViewName;
			while @@FETCH_STATUS = 0 BEGIN
				set @auxStartTime = getdate()
				exec ('SELECT * FROM ' + @ViewName)
				set @auxFinishTime = getdate()
				INSERT INTO TestRunViews(TestRunID, ViewID, StartAt, EndAt) VALUES (@testRunId, @IDView, @auxStartTime, @auxFinishTime)
				fetch next from CursorView INTO @IDView, @ViewName;
			end
			close CursorView
			deallocate CursorView

			set @testFinishTime = getdate()
			UPDATE TestRuns SET EndAt=@testFinishTime where TestRunID=@TestRunId;

			fetch next from CursorTeste INTO @IDTest, @TestName
		END
		CLOSE CursorTeste
		DEALLOCATE CursorTeste
END
GO

DBCC CHECKIDENT ( TestRuns,RESEED ,0)

EXEC TestDatabase;

select * from TestRuns
select * from TestRunTables
select * from TestRunViews

create view View_Clienti
as
    select *
from Clienti

--view pentru testul 2

create view View_Rezervari
as
SELECT C.nume_c, C.prenume_c, R.check_in
FROM Clienti C
INNER JOIN Rezervari R
ON C.client_id=R.client_id;


--view pentru testul 3
create or alter view View_CamereRezervate
as
SELECT C.nume_c,C.prenume_c,R.check_in,R.check_out,CA.nr_camera
FROM CamereRezervate CR
	INNER JOIN Rezervari R ON CR.rez_id=R.rez_id
    INNER JOIN Clienti C ON R.client_id=C.client_id
    INNER JOIN Camere CA ON CR.camera_id = CA.camera_id

alter table Rezervari
add constraint fk_Rezervari foreign key(client_id) references Clienti(client_id) on update cascade on delete cascade