
SELECT * 
FROM spitale_ama;

SELECT *
FROM adrese_ama;

SELECT *
FROM sectii_ama;

SELECT * 
FROM persoane_ama;

SELECT *
FROM doctori_ama;

SELECT *
FROM pacienti_ama;

SELECT *
FROM retete_ama;

SELECT * 
FROM medicamente_ama;

SELECT *
FROM dozaje_ama
order by 2;

-- 1) Sa se afiseze date(cnp, nume, prenume, spital, sectie, salariu, numarul de retete) despre cei mai bine platiti 2 doctori 
-- care au cel putin 2 retete prescrise
SELECT *
FROM (SELECT DISTINCT p.cnp, nume, prenume, id_spital, nume_sectie, salariu, COUNT(*) "Numar retete"
      FROM persoane_ama p
      JOIN doctori_ama d ON(p.cnp = d.cnp)
      JOIN retete_ama r ON(r.cnp_doctor = p.cnp)
      GROUP BY p.cnp, p.nume, p.prenume, salariu, id_spital, nume_sectie
      HAVING(COUNT(*)) >= 2
      ORDER BY salariu DESC
     )
WHERE ROWNUM <= 2;   


-- 2) Sa se afiseze date despre doctorii care castiga mai putin decat media salariilor pentru sectia respectiva, aplicandu-le
-- o marire de salariu astfel: 25 % Chirurgie, 15 % Psihiatrie, 10% Endocrine, 5% Restul. Rezultatele vor fi afisate
-- descrescator dupa marire, respectiv crescator dupa nume

SELECT p.cnp, nume_sectie, nume,  prenume, salariu,
CASE LOWER(nume_sectie)
        WHEN 'chirurgie' THEN salariu * 1.25
        WHEN 'psihiatrie' THEN salariu * 1.15
        WHEN 'endocrine' THEN salariu * 1.10
        ELSE salariu * 1.05
END "DUPA MARIRE"
FROM persoane_ama p
JOIN doctori_ama d ON(p.cnp = d.cnp)
WHERE salariu <= (SELECT AVG(salariu)
                  FROM persoane_ama p1
                  JOIN doctori_ama d ON(p1.cnp = d.cnp)
                  WHERE p1.nume_sectie = p.nume_sectie
                  )
ORDER BY 6 DESC, 3;                  

-- 3) Pentru fiecare sptial, sa se afiseze date (id-ul si numele spitalului, numele sectiei, numele si prenumele fiecarei persoane,
-- alaturi de numarul de doctori din sectia respectiva. Daca sectia nu are doctori, atunci se va afisa 0.Se vor lua in considerare
-- si sectiile fara persoane, dar care sa faca parte dintr-un spital!

SELECT s.id_spital, spit.nume_spital, s.nume_sectie, nume, prenume, NVL(numar_doctori, 0) "Nr doctori"
FROM spitale_ama spit
RIGHT JOIN sectie_spital_ama s ON(spit.id_spital = s.id_spital)
LEFT JOIN persoane_ama p ON(p.id_spital = s.id_spital AND p.nume_sectie = s.nume_sectie)
LEFT JOIN (SELECT nume_sectie, id_spital, COUNT(d1.cnp) numar_doctori
           FROM persoane_ama p1 
           JOIN doctori_ama  d1 ON(p1.cnp = d1.cnp)
           GROUP BY nume_sectie, id_spital
          )aux1 ON (p.id_spital = aux1.id_spital AND p.nume_sectie = aux1.nume_sectie)
ORDER BY 1, 3, 4;
           
-- ex 4) Sa se afiseze detalii despre doctorii care au scris retete in ziua in care au fost scrise cele mai multe retete, precum
-- si ziua si numarul lor (Se va lua in considerare ziua din saptamana: luni, marti etc)

SELECT DISTINCT d.cnp, nume, prenume, (SELECT COUNT(TO_CHAR(data, 'DAY'))
                                       FROM retete_ama
                                       WHERE cnp_doctor = p.cnp AND TO_CHAR(data, 'DAY' ) = TO_CHAR(r.data , 'DAY')
                                       ) "Numar retete", TO_CHAR(data, 'DAY') "Ziua"
FROM persoane_ama p
JOIN doctori_ama d ON(p.cnp = d.cnp)
JOIN retete_ama r ON (d.cnp = r.cnp_doctor)
WHERE TO_CHAR(data , 'DAY') IN (
                                SELECT TO_CHAR(data, 'DAY')
                                FROM retete_ama
                                GROUP BY TO_CHAR(data, 'DAY')
                                HAVING COUNT(*) = (SELECT MAX(COUNT(*))
                                                   FROM retete_ama
                                                   GROUP BY TO_CHAR(data, 'DAY')
                                                  )
                              );


-- ex 5) Sa se afiseze subalternii sefului de sectie din sectia in care suma salariilor este minima
SELECT  id_spital, nume_sectie, cnp, nume, prenume
FROM persoane_ama 
JOIN doctori_ama USING(cnp)
WHERE level > 1
START WITH cnp = (
                    SELECT cnp
                    FROM persoane_ama 
                    JOIN doctori_ama  USING(cnp)
                    WHERE (id_spital, nume_sectie) IN (SELECT id_spital, nume_sectie
                                                       FROM persoane_ama
                                                       JOIN doctori_ama USING(cnp)
                                                       GROUP BY id_spital, nume_sectie
                                                       HAVING SUM(salariu) = (SELECT MIN(SUM(salariu))
                                                                              FROM persoane_ama
                                                                              JOIN doctori_ama USING(cnp)
                                                                              GROUP BY id_spital, nume_sectie
                                                                             )
                                                       ) AND cnp_sef is NULL
                  )
CONNECT BY PRIOR cnp = cnp_sef;   

-- 6) Sa se afiseze detalii (cnp, nume, prenume) despre pacientii din Bucuresti care sunt internati de cel putin 2 luni, intr-un
-- spital care incepe cu "Sf" ordonati crescator dupa nume, descrescator dupa prenume
SELECT p.cnp, nume, prenume, s1.id_spital, a.oras, s1.nume_spital
FROM adrese_ama a
JOIN spitale_ama s1 ON(a.id_adresa = s1.id_adresa)
JOIN sectie_spital_ama s2 ON(s1.id_spital = s2.id_spital)
JOIN persoane_ama p ON(p.id_spital = s2.id_spital AND p.nume_sectie = s2.nume_sectie)
JOIN pacienti_ama p2 ON(p2.cnp = p.cnp)
WHERE  LOWER(a.oras) = 'bucuresti'  AND SUBSTR(UPPER(s1.nume_spital),1, 2) = 'SF'  AND  ROUND(MONTHS_BETWEEN(SYSDATE, p2.data), 2) > 1
ORDER BY 2, 3 DESC;

-- ex 7) Sa se afiseze medicamentele care au fost prescrise tuturor retetelor din primele 4 luni ale anului
SELECT id_medicament, nume_medicament
FROM medicamente_ama m
WHERE NOT EXISTS ( (
                    SELECT r.id_reteta
                    FROM retete_ama r
                    JOIN dozaje_ama d ON(r.id_reteta = d.id_reteta)
                    WHERE data < ADD_MONTHS(TO_DATE('1-01-2020', 'DD-MM-YYYY'), 4)
                   )
                   
                   MINUS
                   
                   (
                   SELECT r1.id_reteta
                   FROM retete_ama r1, dozaje_ama d1
                   WHERE r1.id_reteta = d1.id_reteta AND d1.id_medicament = m.id_medicament
                   )
                 );
                    
-- ex 8) Sa se afiseze date despre pacientii din sectiile cu cel putin 20 de paturi sau in care au fost prescrise cel putin 2 
-- retete. 

SELECT nume, prenume
FROM sectie_spital_ama s
JOIN persoane_ama p ON (s.id_spital = p.id_spital AND s.nume_sectie = p.nume_sectie)
JOIN pacienti_ama pac ON (pac.cnp = p.cnp)
WHERE nr_paturi >= 20

UNION

SELECT nume, prenume
FROM persoane_ama p
JOIN pacienti_ama pac ON (pac.cnp = p.cnp)
JOIN retete_ama r ON(r.cnp_pacient = pac.cnp)
GROUP BY id_spital, nume_sectie, nume, prenume
HAVING COUNT(id_reteta) >= 2;

-- ex 9)Sa se afiseze detalii despre doctorii care nu au prescris retete si pentru care numarul doctorilor din sectia respectiva
-- este mai mare ca cel al pacientilor din sectie
SELECT pers.cnp, pers.nume, pers.prenume
FROM persoane_ama pers
JOIN doctori_ama d ON(pers.cnp = d.cnp)
WHERE NOT EXISTS(SELECT id_reteta
                 FROM retete_ama
                 WHERE cnp_doctor = d.cnp)
INTERSECT
SELECT pers.cnp, pers.nume, pers.prenume
FROM persoane_ama pers
JOIN (  SELECT id_spital, nume_sectie, NVL(COUNT(*), 0) total_doctori
        FROM persoane_ama pers
        JOIN doctori_ama d ON(d.cnp = pers.cnp)
        GROUP BY id_spital, nume_sectie) aux1 ON(pers.id_spital = aux1.id_spital AND pers.nume_sectie = aux1.nume_sectie)
FULL OUTER JOIN (   SELECT id_spital, nume_sectie, NVL(COUNT(*), 0) total_pacienti
                    FROM persoane_ama pers
                    JOIN pacienti_ama p ON(p.cnp = pers.cnp)
                    GROUP BY id_spital, nume_sectie
                ) aux2 ON(aux1.id_spital = aux2.id_spital AND aux1.nume_sectie = aux2.nume_sectie)
WHERE total_pacienti < total_doctori OR total_pacienti is NULL and total_doctori IS NOT NULL;


-- ex 10) Sa se afiseze cel mai prescris medicament de fiecare doctor. Se vor afisa cnp-ul, numele si prenumele doctorului,
-- medicamentul si de cate ori a fost prescris
SELECT pers.cnp, nume, prenume, m.id_medicament, nume_medicament, count(d.id_medicament) Cantitate
FROM persoane_ama pers
JOIN doctori_ama doc ON(pers.cnp = doc.cnp)
JOIN retete_ama r ON(r.cnp_doctor = doc.cnp)
JOIN dozaje_ama d ON(d.id_reteta = r.id_reteta)
JOIN medicamente_ama m ON(m.id_medicament = d.id_medicament)
GROUP BY pers.cnp, m.id_medicament, m.nume_medicament, nume, prenume
HAVING COUNT(d.cantitate) = (SELECT MAX(aux.cant)
                            FROM(SELECT cnp_doctor, id_medicament, count(cantitate) cant
                                 FROM retete_ama r
                                 JOIN dozaje_ama d ON(r.id_reteta = d.id_reteta)
                                 GROUP BY cnp_doctor, id_medicament
                                )aux WHERE aux.cnp_doctor = pers.cnp GROUP BY aux.cnp_doctor
                            )ORDER BY 2, 4;    
                        


-- ex 11) Sa sa afiseze cel ma bine platit doctor din fiecare sectie. Daca o sectie nu contine doctori, se va afisa 0

SELECT spit.nume_spital, s.nume_sectie, nume, prenume, NVL(salariu, 0) Salariu
FROM spitale_ama spit 
JOIN sectie_spital_ama s ON(spit.id_spital = s.id_spital)
LEFT JOIN persoane_ama p ON(s.id_spital = p.id_spital AND s.nume_sectie = p.nume_sectie)
LEFT JOIN doctori_ama d ON(p.cnp = d.cnp)
WHERE (NVL(salariu, 0), s.id_spital, s.nume_sectie) IN (
                                                        SELECT NVL(max(salariu), 0) , s.id_spital, s.nume_sectie
                                                        FROM sectie_spital_ama s
                                                        LEFT JOIN persoane_ama p ON(s.id_spital = p.id_spital AND s.nume_sectie = p.nume_sectie)
                                                        LEFT JOIN doctori_ama d ON(d.cnp = p.cnp)
                                                        GROUP BY s.id_spital, s.nume_sectie
                                                       ) AND (p.cnp NOT IN (SELECT cnp FROM pacienti_ama) or p.cnp is null)
ORDER BY 1, 2, 5;                                                       

-- ex 12) Sa se afiseze cate pastile de Cipralex are de luat fiecare pacient internat dupa 15 mai
SELECT pers.cnp, nume, prenume, SUM(DECODE('Cipralex', INITCAP(nume_medicament), d.cantitate, 0)) Cantitate, pac.data
FROM persoane_ama pers
JOIN pacienti_ama pac ON(pers.cnp = pac.cnp)
LEFT JOIN retete_ama r ON(r.cnp_pacient = pac.cnp)
LEFT JOIN dozaje_ama d ON(d.id_reteta = r.id_reteta)
LEFT JOIN medicamente_ama m ON(m.id_medicament = d.id_medicament)
WHERE pac.data > TO_DATE('15-05-2020' , 'DD-MM-YYYY')
GROUP BY pers.cnp, nume, prenume, pac.data;


-- ex 13) Sa se afiseze sectia cu numarul maxim de paturi care nu are doctori
SELECT sect.id_spital, sect.nume_sectie, nr_paturi "Numar paturi"
FROM sectie_spital_ama sect
JOIN persoane_ama pers ON(sect.id_spital = pers.id_spital AND sect.nume_sectie = pers.nume_sectie)
WHERE NOT EXISTS(SELECT cnp
                 FROM doctori_ama
                 WHERE cnp = pers.cnp
                 ) AND nr_paturi = (SELECT MAX(nr_paturi)
                                    FROM sectie_spital_ama sect
                                    JOIN persoane_ama pers ON(sect.id_spital = pers.id_spital AND sect.nume_sectie = pers.nume_sectie)
                                    WHERE NOT EXISTS(SELECT cnp
                                                     FROM doctori_ama
                                                     WHERE cnp = pers.cnp
                                                     )
                                    );                          
-- ex 14) Sa se afiseze doctorii care au scris cel putin 2 retete si au salariul mai mare decat media salarillor doctorilor
-- de la Cardiologie
SELECT cnp, nume, prenume, salariu
FROM persoane_ama
JOIN doctori_ama USING(cnp)
WHERE (SELECT COUNT(*)
       FROM retete_ama
       WHERE cnp_doctor = cnp
       GROUP BY cnp_doctor
       ) >= 2 AND salariu > (SELECT AVG(salariu)
                             FROM persoane_ama 
                             JOIN doctori_ama USING(cnp)
                             WHERE INITCAP(nume_sectie) = 'Cardiologie'
                             );
                
-- ex 15) Sa se afiseze medicamentele prescrise de doctorul cu cei mai multi subalterni
SELECT DISTINCT m.id_medicament, nume_medicament
FROM persoane_ama pers
JOIN doctori_ama doc ON(doc.cnp = pers.cnp)
JOIN retete_ama ret ON (ret.cnp_doctor = doc.cnp)
JOIN dozaje_ama d ON (d.id_reteta = ret.id_reteta)
JOIN medicamente_ama m ON(m.id_medicament = d.id_medicament)
WHERE pers.cnp IN (SELECT cnp_sef
                   FROM (
                           SELECT  cnp_sef 
                           FROM doctori_ama
                           GROUP by cnp_sef
                           HAVING COUNT(cnp_sef) = (SELECT MAX(COUNT(cnp_sef))
                                                    FROM doctori_ama
                                                    GROUP by cnp_sef
                                                    )
                          ) 
                );

--------------- date despre pacienti
SELECT p1.cnp, p1.nume, p1.prenume,  p1.id_spital, p1.nume_sectie, data
FROM persoane_ama p1
JOIN pacienti_ama p2 ON(p1.cnp = p2.cnp);

-- date despre doctori
SELECT p1.cnp, p1.nume, p1.prenume, p1.id_spital, p1.nume_sectie, p2.cnp_sef, salariu
FROM persoane_ama p1
JOIN doctori_ama p2 ON(p1.cnp = p2.cnp)
order by 4, 5;

SELECT *
FROM persoane_ama p1
JOIN persoane_ama p2 ON(p1.id_spital = p2.id_spital AND p1.nume_sectie = p2.nume_sectie AND p1.cnp != p2.cnp);

