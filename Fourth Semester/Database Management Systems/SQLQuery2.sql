Use Problema2;

CREATE INDEX idx_year ON Melodii(an_lansare);

select * from melodii where an_lansare>2007


USE Problema1
 
SELECT nume_briosa , pret FROM Briose WHERE pret = 10
 
CREATE INDEX ix_pret_nume2 ON Briose (pret ASC , nume_briosa ASC)