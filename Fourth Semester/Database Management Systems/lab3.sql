use Hotels
go

select * from Camere;
select * from CamereRezervate;
select * from Rezervari;

/*
create table Logs
(
  id int identity,
  operationType varchar(20),
  tableName varchar(20),
  executionTime datetime,
  constraint pk_Logs primary key(id)
)*/

go
create or alter function validate_name (@name varchar(51))
returns bit
as 
begin
	declare @isValid bit=0

	if @name is not null and @name<> ''
		and len(@name) <=50
		set @isValid = 1

	return @isValid
end
go


create or alter function validate_rating (@rating varchar(51))
returns bit 
as 
begin
	declare @isValid bit=0

	if @rating is not null and @rating<> ''
		and len(@rating) <=2
		set @isValid = 1

	return @isValid
end
go

SELECT  dbo.validate_name('John Doe') -- Returns 1
SELECT  dbo.validate_name('aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa') -- Returns 0
SELECT  dbo.validate_name(NULL) -- Returns 0
go



CREATE OR ALTER FUNCTION validate_date(@date datetime)
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 0
  
  IF @date IS NOT NULL AND @date <> ''
    SET @isValid = 1

  RETURN @isValid
END
go

CREATE OR ALTER FUNCTION validate_nrcamera(@nrcamera int)
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 0
  
  IF @nrcamera IS NOT NULL AND @nrcamera <1000 
	AND @nrcamera >0
    SET @isValid = 1

  RETURN @isValid
END
go

CREATE OR ALTER FUNCTION validate_etaj(@etaj int)
RETURNS BIT
AS
BEGIN
  DECLARE @isValid BIT = 0
  
  IF @etaj IS NOT NULL AND @etaj <10
	AND @etaj >0
    SET @isValid = 1

  RETURN @isValid
END
go


create or alter function validate_detalii (@detalii varchar(51))
returns bit
as 
begin
	declare @isValid bit=0

	if @detalii is not null and @detalii<> ''
		and len(@detalii) <=50
		set @isValid = 1

	return @isValid
end
go

create or alter function validate_parameters_camera(
@nr_camera int,
@etaj int,
@detalii varchar(50)
)
returns varchar(200)
as
begin
	declare @error_message varchar(200)
	set @error_message = ''

	if(dbo.validate_nrcamera(@nr_camera) = 0)
			set @error_message = @error_message + 'numarul camerei invalid, nu trebuie sa fie null, gol sau depaseasca 1000.'
	if(dbo.validate_etaj(@etaj) = 0)
			set @error_message = @error_message + 'numarul etajului invalid, nu trebuie sa fie null, gol sau depaseasca 10.'
	if(dbo.validate_detalii(@detalii) = 0)
			set @error_message = @error_message + 'campul detalii null, gol sau prea lung (>200).'
	return @error_message
end 
go

select dbo.validate_parameters_camera(null, 0 , '')
go

create or alter function validate_parameters_rezervare(
@client_id int,
@admin_id int,
@checkin date, 
@checkout date, 
@status_id int
)
returns varchar(200)
as
begin
	declare @error_message varchar(200)
	set @error_message = ''
	if (not (exists(select id from dbo.Clienti where id = @client_id)))
		set @error_message = @error_message + 'clientul cu id-ul dat nu exista.'
	if (not (exists(select admin_id from dbo.Admini where admin_id = @admin_id)))
		set @error_message = @error_message +'adminul cu id-ul dat nu exista.'
	if (not (exists(select status_id from dbo.StatusRezervare where status_id = @status_id)))
		set @error_message = @error_message +'statusul cu id-ul dat nu exista.'
	if (dbo.validate_date(@checkin) = 0 or dbo.validate_date(@checkout) = 0)
		set @error_message = @error_message + 'cel putin una dintre date (tip date) sunt nulle.'
	if (@checkin > @checkout)
		set @error_message = @error_message +'datele de checkin si checkout sunt invalide.'
	return @error_message
end
go

select dbo.validate_parameters_rezervare(null,1000, null, null,9999)
go

create or alter function validate_parameters_camererezervate(
@rez_id int,
@camera_id int,
@rating varchar(100)
)
returns varchar(200)
as
begin
	declare @error_message varchar(200)
	set @error_message = ''
	if (not (exists(select id from dbo.Rezervari where id = @rez_id)))
		set @error_message = @error_message + 'rezervarea cu id-ul dat nu exista.'
	if (not (exists(select camera_id from dbo.Camere where camera_id = @camera_id)))
		set @error_message = @error_message +'camera cu id-ul dat nu exista.'
	if (dbo.validate_rating(@rating) =0 )
		set @error_message = @error_message + 'rating invalid sau null, ratingul se reprezinta in procente de pana la 100%.'
	return @error_message
end
go

select dbo.validate_parameters_camererezervate(100,2000,null)


go

--cerinta 5 puncte
create or alter procedure insert_camere_rezervari_camrez_v1(
@nr_camera int,
@etaj int,
@detalii varchar(50),
@rating varchar(50),
@client_id int,
@admin_id int,
@check_in datetime,
@check_out datetime,
@status_id int
)
as
begin
	begin tran
	begin try
		declare @error_message varchar(200)
		set @error_message = dbo.validate_parameters_camera(@nr_camera,@etaj,@detalii)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Camere(nr_camera, etaj, detalii) values (@nr_camera, @etaj, @detalii)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'camere', CURRENT_TIMESTAMP)
		set @error_message = dbo.validate_parameters_rezervare(@client_id, @admin_id, @check_in, @check_out, @status_id)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Rezervari(client_id, admin_id, check_in, check_out, status_id ) values (@client_id, @admin_id, @check_in, @check_out, @status_id)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'rezervari', CURRENT_TIMESTAMP)
		declare @rez_id int, @camera_id int
		set @rez_id = (select max(id) from Rezervari)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'rez id', CURRENT_TIMESTAMP)
		set @camera_id = (select max(camera_id) from Camere)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'camera id', CURRENT_TIMESTAMP)

		set @error_message = dbo.validate_parameters_camererezervate(@rez_id, @camera_id, @rating)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end

		insert into CamereRezervate(rez_id, camera_id, rating) values (@rez_id, @camera_id, @rating);
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'camere rezervate', CURRENT_TIMESTAMP)

		commit tran

		select 'Transaction commited'
	end try
	begin catch
		rollback tran
		select 'Transaction rollbacked'
	end catch
end
go

--tests

select * from Rezervari
select * from Camere
select * from CamereRezervate
select * from Logs

--commit
execute dbo.insert_camere_rezervari_camrez_v1
1,
1,
'miaumiau',
'98',
1,
1,
'2023-05-01 12:00:00.000',
'2023-05-03 14:00:00.000',
1

select * from Rezervari
select * from Camere
select * from CamereRezervate
select * from Logs

--roll back
execute dbo.insert_camere_rezervari_camrez_v1
1000,
10000,
'miaumiaumiau',
'9008',
2,
2,
'2023-05-02 12:00:00.000',
'2023-05-08 14:00:00.000',
1

select * from Rezervari
select * from Camere
select * from CamereRezervate
select * from Logs

--cerinta 4 puncte
go
create or alter procedure insert_camere_rezervari_camrez_v2(
@nr_camera int,
@etaj int,
@detalii varchar(50),
@rating varchar(50),
@client_id int,
@admin_id int,
@check_in datetime,
@check_out datetime,
@status_id int
)
as
begin
	declare @error bit
	set @error = 1

	begin tran
	begin try
		declare @error_message varchar(200)
		set @error_message = dbo.validate_parameters_camera(@nr_camera,@etaj,@detalii)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Camere(nr_camera, etaj, detalii) values (@nr_camera, @etaj, @detalii)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'camere', CURRENT_TIMESTAMP)

		commit tran
		select 'Transaction comitted Camere'
	end try
	begin catch
		rollback tran
		select 'Transaction rollbacked for Camere'
		insert into Logs(operationType, tableName, executionTime) values ('rollback', 'camere', CURRENT_TIMESTAMP)
		set @error = 0
	end catch
	
	begin tran
	begin try
		set @error_message = dbo.validate_parameters_rezervare(@client_id, @admin_id, @check_in, @check_out, @status_id)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end
		insert into Rezervari(client_id, admin_id, check_in, check_out, status_id ) values (@client_id, @admin_id, @check_in, @check_out, @status_id)
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'rezervari', CURRENT_TIMESTAMP)
		
		commit tran
		select 'Transaction comitted Rezervari'
	end try
	begin catch
		rollback tran
		select 'Transaction rollbacked for Rezervari'
		insert into Logs(operationType, tableName, executionTime) values ('rollback', 'rezervari', CURRENT_TIMESTAMP)
		set @error = 0
	end catch

	if (@error = 0)
		return;

	begin tran
	begin try
		declare @rez_id int, @camera_id int
		set @rez_id = (select max(id) from Rezervari)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'rez id', CURRENT_TIMESTAMP)
		set @camera_id = (select max(camera_id) from Camere)
		insert into Logs(operationType, tableName, executionTime) values ('select', 'camera id', CURRENT_TIMESTAMP)

		set @error_message = dbo.validate_parameters_camererezervate(@rez_id, @camera_id, @rating)
		if (@error_message != '')
		begin
			print @error_message
			raiserror(@error_message, 14, 1)
		end

		insert into CamereRezervate(rez_id, camera_id, rating) values (@rez_id, @camera_id, @rating);
		insert into Logs(operationType, tableName, executionTime) values ('insert', 'camere rezervate', CURRENT_TIMESTAMP)

		commit tran

		select 'Transaction commited CamereRezervate'
	end try
	begin catch
		rollback tran
		insert into Logs(operationType, tableName, executionTime) values ('rollback', 'camere rezervate', CURRENT_TIMESTAMP)
		select 'Transaction rollbacked CamereRezervate'
	end catch
end
go

--tests

select * from Rezervari
select * from Camere
select * from CamereRezervate
select * from Logs

--commit
execute dbo.insert_camere_rezervari_camrez_v2
205,
2,
'honeymoon',
'95',
2,
2,
'2023-05-01 12:00:00.000',
'2023-05-03 14:00:00.000',
1

select * from Rezervari
select * from Camere
select * from CamereRezervate
select * from Logs

--roll back
execute dbo.insert_camere_rezervari_camrez_v2
99,
9,
'miaumiaumiau',
'9008',
80,
200,
'2023-06-12 12:00:00.000',
'2023-06-18 14:00:00.000',
3

select * from Rezervari
select * from Camere
select * from CamereRezervate
select * from Logs

