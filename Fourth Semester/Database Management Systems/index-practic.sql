Use S12023;

select titlu, buget from Proiecte where buget>9999

CREATE INDEX ix_proiecte on Proiecte(buget ASC, titlu ASC)