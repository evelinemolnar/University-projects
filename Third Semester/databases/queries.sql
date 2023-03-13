
USE Hotels
Select *
From Clienti

/* clienti ce folosesc yahoo mail */
SELECT DISTINCT nume_c,Clienti.email_c
FROM Clienti
WHERE Clienti.email_c LIKE '_%@yahoo.com'

/* afiseaza toti clientii din Romania*/
SELECT DISTINCT nume_c, tara_c
FROM Clienti
WHERE tara_c LIKE 'Romania'

/* toate rezervarile confirmate */
SELECT nume_c, S.status
FROM Clienti C, Rezervari R, StatusRezervare S
WHERE C.client_id=R.client_id AND R.status_id=S.status_id AND S.status LIKE 'confirmat'


/*toate rezervarile  de astazi si numarul de camera  m-m*/
SELECT nume_c, check_in,nr_camera
FROM Clienti C
    INNER JOIN Rezervari R2 on C.client_id = R2.client_id
    INNER JOIN CamereRezervate CR on R2.rez_id = CR.rez_id
    INNER JOIN Camere C2 on C2.camera_id = CR.camera_id
WHERE R2.check_in=CAST( GETDATE() AS Date )


/* clientii grupati in functie de tara care au oferit cel mai mare rating camerei inchiriate */
SELECT nume_c,tara_c, rating
FROM Clienti C
    INNER JOIN Rezervari R2 on C.client_id = R2.client_id
    INNER JOIN CamereRezervate CR on R2.rez_id = CR.rez_id
    INNER JOIN Camere C2 on C2.camera_id = CR.camera_id
    INNER JOIN TipCamera TC on TC.tip_id = C2.tip_id
GROUP BY tara_c, nume_c, rating
HAVING MAX(rating) = 10

/* camerele identificate prin numar si grupate in functie de tipul lor*/
SELECT nr_camera, tip
FROM Camere C,TipCamera T
WHERE  C.tip_id=T.tip_id
GROUP BY tip,nr_camera

/* camere ocupate de la etajul 2 grupate dupa tip */

SELECT nr_camera, etaj, tip
FROM Camere C
    INNER JOIN CamereRezervate CR on C.camera_id = CR.camera_id
    INNER JOIN Rezervari R2 on R2.rez_id = CR.rez_id
    INNER JOIN TipCamera TC on TC.tip_id = C.tip_id
WHERE etaj=2
GROUP BY tip, etaj, nr_camera

/* facturile achitate cu cardul cu status de efectuat cu max(val)=1500  grupate dupa data */

SELECT F.factura_id, P.data_p, valoare
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN StatusPlata SP on P.statusplata_id = SP.statusplata_id
    INNER JOIN TipPlata TP on P.tipplata_id = TP.tipplata_id
WHERE SP.status LIKE 'efectuata' AND TP.tip LIKE 'card'
GROUP BY P.data_p, F.factura_id, F.factura_id, valoare
HAVING MAX(valoare)=1500

/*  facturile achitate astazi  */

SELECT F.factura_id, P.data_p, valoare
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN TipPlata TP on P.tipplata_id = TP.tipplata_id
WHERE P.data_p = CAST( GETDATE() AS Date )

/* suma facturilor achitate */
SELECT SUM(P.valoare) AS Suma
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN StatusPlata SP on P.statusplata_id = SP.statusplata_id
WHERE SP.status LIKE 'efectuata'

/*  pretul camerelor rezervate*/
SELECT P.valoare, C2.nr_camera
FROM Facturi F
    INNER JOIN Clienti C on C.client_id = F.client_id
    INNER JOIN Plati P on F.factura_id = P.factura_id
    INNER JOIN Rezervari R2 on R2.rez_id = F.rez_id
    INNER JOIN TipPlata TP on P.tipplata_id = TP.tipplata_id
    INNER JOIN CamereRezervate CR on R2.rez_id = CR.rez_id
    INNER JOIN Camere C2 on C2.camera_id = CR.camera_id
    INNER JOIN TipCamera TC on TC.tip_id = C2.tip_id

