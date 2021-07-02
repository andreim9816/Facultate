-- MANOLACHE ANDREI 244
SELECT *
FROM rezervare r
JOIN eveniment e ON (e.id = r.id_eveniment)
JOIN spectator s ON (s.id = r.id_spectator)
JOIN abonat ab ON (ab.id_spectator = s.id)
JOIN abonament a ON (a.id = ab.id_abonament)
JOIN sala sa ON (sa.id = e.id_sala);

-- ex 1
--S? se afi?eze pentru fiecare spectator cu un abonament valabil la data 15/09/2021, costul total pe care l-ar
--pl?ti f?r? abonament, pentru toate evenimentele din data 15/09/2021 la care a f?cut rezervare. Pre?urile
--biletelor sunt memorate în coloanele pret_cat1, pret_cat2, pret_cat3, spre exemplu pentru o rezervare
--înregistrat? cu categorie 1 se va achita pret_cat1.

SELECT  s.id, SUM(CASE 
                    WHEN categorie = 1 THEN pret_cat1
                    WHEN categorie = 2 THEN pret_cat1
                    ELSE pret_cat3
                  END) as "Suma totala"
FROM rezervare r
JOIN eveniment e ON (e.id = r.id_eveniment)
JOIN spectator s ON (s.id = r.id_spectator)
JOIN abonat ab ON (ab.id_spectator = s.id)
JOIN abonament a ON (a.id = ab.id_abonament)
WHERE data_validare <= to_date('15-AUG-2021', 'dd-mon-yyyy') AND data_validare + durata_zile - 1 >= to_date('15-AUG-2021', 'dd-mon-yyyy') 
AND data_ev = to_date('15-AUG-2021', 'dd-mon-yyyy')
GROUP BY s.id;

-- ex 2

--S? se afi?eze lista evenimentelor de la Ateneu, cu durata mai mica de 90min, la care a rezervat bilete Ionescu Vlad

SELECT e.id, e.denumire
FROM eveniment e
JOIN rezervare r ON (r.id_eveniment = e.id)
JOIN spectator s ON (s.id = r.id_spectator)
JOIN sala sa ON (sa.id = e.id_sala)
WHERE UPPER(sa.denumire) LIKE ('%ATENEU%') AND durata_min < 90
AND UPPER(nume) = 'IONESCU' AND UPPER(prenume) = 'VLAD';

-- ex 3

--S? se adauge în tabelul eveniment coloana ANULAT având un tip de date adecvat. Nu vor putea fi marcate
--anulate evenimentele care au avut loc înainte de data '01/01/2021'

ALTER TABLE eveniment 
ADD anulat char(1) DEFAULT 'N' CHECK(anulat in ('Y','N'));
 
ALTER TABLE eveniment
ADD CONSTRAINT CK_ev_anulat CHECK(data_ev >= to_date('01-JAN-2021', 'DD-MON-YYYY') OR anulat = 'N');

-- evenimentul cu id-ul 5, care se va desfasura in 2020 nu poate fi marcat ca anulat. Urmatoarea insructiune da eroare
UPDATE eveniment
SET anulat = 'Y' 
WHERE id = 5;

-- evenimentul cu id-ul 1 se va defasura in 2021, deci poate fi anulat. Urmatoarea instructiune va merge
UPDATE eveniment
SET anulat = 'Y'
WHERE id = 1;

SELECT * FROM eveniment;

-- ex 4
--S? se actualizeze coloana ANULAT astfel: evenimentele pentru care nu s-a f?cut nicio rezervare vor fi anulate
UPDATE eveniment e
SET anulat = 'Y'
WHERE e.id NOT IN(SELECT id_eveniment
                  FROM rezervare r
                  JOIN eveniment e2 ON(e2.id = r.id_eveniment)
                 );
                 
SELECT * FROM eveniment;                 