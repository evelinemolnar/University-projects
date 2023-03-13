select * from Tests
select * from Tables
select * from TestTables

declare @a int = 1
while @a<4 begin
    select Name, NoOfRows, Position
    from Tables T inner join dbo.TestTables TT on T.TableID = TT.TableID
    where TestID = @a
    set @a+=1
end

--var1
/*
declare @a int
set @a = (select TestID from Tests where TestID = 1)
print @a
*/

--var2

declare @a int, @b nvarchar(50)
select @a = TestID, @b = Name from Tests where TestID = 2
print @a
print @b

--var3 cursoare (trebuie sa fie stocat intr o procedura)
declare @IDTest int, @TestName nvarchar(50)
declare @TableName nvarchar(50), @NoOfRows int
declare CursorTeste cursor forward_only

for select * from Tests
    open CursorTeste
    fetch next from CursorTeste into @IDTest,@TestName
    while @@FETCH_STATUS = 0 begin
        -- DELETE_URI
        declare CursorDelete cursor forward_only   -- sau se poate folosi un cursor de tip scroll pe care sa il parcurgem inainte pt delete uri si inapoi pt insert
        for select Name
            from Tables T inner join dbo.TestTables TT on T.TableID = TT.TableID
            where TestID = @IDTest
            order by Position

        open CursorDelete
        fetch next from CursorDelete into @TableName
        while @@FETCH_STATUS = 0 begin
            exec('delete from ' + @TableName)
            fetch next from CursorDelete into @TableName
        end
        close CursorDelete
        deallocate CursorDelete
        --INSERT-uri
        --declare CursorInsert cursor
        --for select

        --VIEW-uri


        fetch next from CursorTeste into @IDTest,@TestName
end
close CursorTeste
deallocate CursorTeste


--procedura insert
create or alter procedure InsertINTO
@table_name nvarchar(25), @number_of_items INT
as
begin
	declare @sqlstatement nvarchar(200);
	declare @index int
	set @index=0
	set @sqlstatement = N'INSERT INTO '
	declare @item_name nvarchar(20)


	if @table_name = 'Clienti'
	begin
		while @index < @number_of_items
		begin
			set @item_name = 'nume'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Clienti(nume_c,prenume_c,adresa_c,oras_c,tara_c,nrtel_c,email_c) VALUES '+N'('''+@item_name+N''','','','','',0,'')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;

		end;
	end;

	else if @table_name='TipCamera'
	begin
		while @index < @number_of_items
		begin
			set @item_name = 'Tip'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO TipCamera(tip) VALUES '+N'('''+@item_name+N''')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;
		end;
	end;

	else if @table_name='Camere'
	begin
	    if not exists(select * from TipCamera where tip='Tip')
			insert into  TipCamera(tip) values ('Tip')

		declare @id_tip int
		select top(1) @id_tip=tip_id from TipCamera
		while @index < @number_of_items
		begin
			set @item_name = 'NrCamera'+CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Camere(nr_camera) VALUES '+N'('''+@item_name+N''')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;
		end;
	end;

	else if @table_name='Rezervari'
	begin
	    if not exists(select * from Clienti where nume_c='nume')
			insert into  Clienti(nume_c, prenume_c, adresa_c, oras_c, tara_c, nrtel_c, email_c) values ('Tip', '','','','',0,'')

	    declare @id_clientt int
		select top(1) @id_clientt=client_id from Clienti

		while @index < @number_of_items
		begin
			set @item_name='checkin' + CAST (@index as NVARCHAR)
			set @sqlstatement = N'INSERT INTO Rezervari(client_id,check_in,check_out) VALUES '+N'(''CAST(@id_clientt as nvarchar)+N'', '','')'
			exec sp_executesql @sqlstatement
			set @index = @index + 1;
		end;
	end;

	else if @table_name='CamereRezervate'
	begin
		--adaugam date in celalalte tabele sa facem conexiunea
		declare @id_clienttt int
		declare @id_rezz int
		declare @id_tipp int
		declare @id_camm int

		delete from Clienti where nume_c='nume'
		delete from TipCamera where tip='Tip'
		delete from Camere where nr_camera='NrCamera'
		delete from Rezervari where check_in='checkin'

		insert into Clienti(nume_c, prenume_c, adresa_c, oras_c, tara_c, nrtel_c, email_c) values ('Nume','','','','',0,'')

		set @id_clienttt = (select top(1) client_id from Clienti)

		insert into Rezervari(client_id, check_in, check_out) values (@id_clienttt,'checkin','')
		select top(1) @id_rezz=rez_id from Rezervari

		insert into TipCamera(tip) values('Tip')
		select top(1) @id_tipp=tip_id from TipCamera

		insert into Camere(nr_camera, tip_id) values ('NrCamera',@id_tipp)
		select top(1) @id_camm=camera_id from Camere

		while @index < @number_of_items
		begin
			set @item_name='CamereRezervate' + CAST (@index as nvarchar)
			set @sqlstatement = 'INSERT INTO CamereRezervate(rez_id,camera_id,rating) VALUES ('+N''+CAST(@id_rezz as nvarchar)+N','+CAST(@id_camm as nvarchar)+N','')'
			exec sp_executesql @sqlstatement
			set @index = @index+1
		end;

	end;


end;


exec InsertINTO 'CamereRezervate',100
select * from CamereRezervate





create procedure DeleteFromTable
@table_name VARCHAR(25)
as
begin
	declare @sqlstatement nvarchar(100)
	set @sqlstatement = N'DELETE FROM '+@table_name
	exec sp_executesql @sqlstatement

end



select * from tests




--procedura view
create or alter procedure ExecuteView
@view_name varchar(30)
as
begin

	declare @sqlstatement nvarchar(150)
	if exists(select name from sys.views where name=@view_name)
		begin
			set @sqlstatement = N'select * from '+@view_name
			exec sp_executesql @sqlstatement
		end;
end


exec TestDatabase

select * from TestRuns
select * from TestRunTables
select * from TestRunViews

create or alter procedure TestDatabase
as
begin



	set nocount on


	delete from TestRuns
	delete from TestRunViews
	delete from TestRunTables
	DBCC CHECKIDENT (TestRuns, RESEED, 0);
	-- delete all from the tables

		declare cursorPreDelete cursor forward_only
		for
		select T.name from TestTables TT
			inner join Tables T on T.TableID=TT.TableID
			where TT.TestID = 3
			order by Position
		declare @tableTempDeleteName varchar(25)
		open cursorPreDelete
			fetch next from cursorPreDelete into @tableTempDeleteName
			while @@FETCH_STATUS=0
			begin
				exec DeleteFromTable @tableTempDeleteName
				fetch next from cursorPreDelete into @tableTempDeleteName
			end;

		close cursorPreDelete
		deallocate cursorPreDelete

	declare @currentTestId int
	declare @tableId int
	declare @tableName varchar(25)
	declare @noOfRows int

	declare @startGlobal datetime




	declare @startTime datetime, @endTime datetime
	declare @endGlobal datetime
	declare @description nvarchar(50)
	declare @TestRunId int
	----- here starts
	declare cursorTest cursor forward_only for
	select TestID, Name from Tests

	open cursorTest

	fetch next from cursorTest into @currentTestId, @description
	while @@FETCH_STATUS=0
	begin
		insert into TestRuns(Description,StartAt) values (@description,getdate())


		set @TestRunId = @@IDENTITY;

		declare cursorForDelete cursor forward_only for
		select T.name, T.TableID from TestTables TT
		inner join Tables T on T.TableID=TT.TableID
		where TT.TestID = @currentTestId
		order by Position

		declare @testStart datetime
		set @testStart = getdate()

		open cursorForDelete
			fetch next from cursorForDelete into @tableName, @tableId
			while @@FETCH_STATUS=0
			begin
				--aici masor timpul de executie pentru delete al fiecarui tabel si il stochez in TestRunTables

				exec DeleteFromTable @tableName

				fetch next from cursorForDelete into @tableName, @tableId
			end

		close cursorForDelete
		deallocate cursorForDelete


		declare cursorForInsert cursor forward_only for
		select T.name, TT.NoOfRows, T.TableID from TestTables TT
		inner join Tables T on T.TableID=TT.TableID
		where TT.TestID = @currentTestId
		order by Position desc

		open cursorForInsert
			fetch next from cursorForInsert into @tableName, @noOfRows, @tableId
			while @@FETCH_STATUS=0
			begin
				--aici masor timpul de executie pentru insert al fiecarui tabel si il stochez in TestRunTables



				set @startTime=GETDATE()
				exec InsertINTO @tableName, @noOfRows
				set @endTime=GETDATE()
				insert into TestRunTables(TestRunID,TableID,StartAt,EndAt) values (@TestRunId,@tableId,@startTime,@endTime);

				fetch next from cursorForInsert into @tableName, @noOfRows, @tableId
			end

		close cursorForInsert
		deallocate cursorForInsert


		declare @viewName nvarchar(100);
		declare @viewIDFrom int;

		declare cursorViews cursor forward_only
		for
		select V.name, V.ViewID from TestViews TV
		inner join Views V on V.ViewID=TV.ViewID
		where TV.TestID = @currentTestId

		open cursorViews
			fetch next from cursorViews into @viewName,@viewIDFrom
			while @@FETCH_STATUS = 0
			begin
				set @startTime=GETDATE();
				--exec ExecuteView @viewName
				EXEC('SELECT * FROM '+ @viewName)
				set @endTime=GETDATE();

				insert into TestRunViews(TestRunID,ViewID,StartAt,EndAt) values (@TestRunId,@viewIDFrom,@startTime,@endTime)

				fetch next from cursorViews into @viewName,@viewIDFrom
			end;
		close cursorViews
		deallocate cursorViews

		set @endGlobal = GETDATE()
		UPDATE TestRuns SET EndAt=@endGlobal where TestRunID=@TestRunId;

		fetch next from cursorTest into @currentTestId, @description

	end;
	close cursorTest
	deallocate cursorTest

end;



CREATE TABLE CamereRezervate
(rez_id INT FOREIGN KEY REFERENCES Rezervari(rez_id) ON UPDATE CASCADE ON DELETE CASCADE,
 camera_id INT FOREIGN KEY REFERENCES Camere(camera_id) ON UPDATE CASCADE ON DELETE CASCADE,
 CONSTRAINT pk_CamereRezervate PRIMARY KEY(rez_id, camera_id)
);
 GO