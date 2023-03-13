
CREATE OR ALTER PROCEDURE Insert_Rows
	@nb_of_rows varchar(30),
	@table_name varchar(30)
AS
BEGIN
	SET NOCOUNT ON;

	declare @table varchar(100)
	set @table = ('[' + @table_name + ']')

    if @table_name = 'Clienti' or @table_name = 'Rezervari' or @table_name = 'Camere'
	begin
		DBCC CHECKIDENT (@table, RESEED, 0);
	end

	if ISNUMERIC(@nb_of_rows) != 1
	BEGIN
		print('Not a number')
		return 1
	END

	SET @nb_of_rows = cast(@nb_of_rows as INT)

	declare @contor int
	set @contor = 1

    declare @nume_c varchar(50)
	declare @prenume_c varchar(50)
	declare @adresa_c varchar(50)
	declare @oras_c varchar(50)
	set @oras_c= 'Cluj-Napoca'
	declare @tara_c varchar(50)
	set @tara_c= 'Romania'
	declare @nrtel_c int
	set @nrtel_c= 0748165858

    declare @nr_camera int
	set @nr_camera = 1

    declare @client_id int
	set @client_id=1
	declare @check_in DATETIME
	set @check_in = GETDATE()
	declare @check_out DATETIME
	set @check_out = GETDATE()


	declare @camera_idd int
	declare @rez_id int

    while @contor <= @nb_of_rows
	begin
		if @table_name = 'Clienti'
		begin
			set @nume_c = 'nume' + convert(varchar(7), @contor)
			set @prenume_c = 'prenume' + convert(varchar(7), @contor)
			set @adresa_c= 'adresa' + convert(varchar(7), @contor)
			insert into Clienti(nume_c,prenume_c,adresa_c,oras_c,tara_c,nrtel_c) values (@nume_c, @prenume_c, @adresa_c, @oras_c, @tara_c, @nrtel_c)
		end
		if @table_name = 'Camere'
		begin
			insert into Camere(nr_camera) values (@nr_camera)
		end

		if @table_name = 'Rezervari'
		begin
			insert into Rezervari (client_id,check_in,check_out) values (@client_id,@check_in,@check_out)
		end

		if @table_name = 'CamereRezervate'
		begin
			set @rez_id=@contor
			set @camera_idd=@contor
			insert into CamereRezervate(rez_id, camera_id) values (@rez_id, @camera_idd)
		end

		set @contor = @contor + 1
	end

END


