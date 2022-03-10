SET SERVEROUTPUT ON;
SET VERIFY OFF;

CREATE OR REPLACE TYPE tip_orase IS TABLE OF VARCHAR2(100);
/

CREATE TABLE excursie(
    cod_excursie NUMBER(4),
    denumire VARCHAR2(20),
    orase tip_orase,
    status VARCHAR2(15))
    NESTED TABLE orase STORE AS tabel_orase;

--a
INSERT INTO excursie VALUES (1,'Excursia 1',tip_orase('Bucuresti','Pitesti','Iasi'),'disponibila');
INSERT INTO excursie VALUES (2,'Excursia 2',tip_orase('Bucuresti','Ploiesti','Iasi'),'disponibila');
INSERT INTO excursie VALUES (3,'Excursia 3',tip_orase('Brasov','Iasi'),'anulata');
INSERT INTO excursie VALUES (4,'Excursia 4',NULL,'disponibila');
INSERT INTO excursie VALUES (5,'Excursia 5',tip_orase('Ploiesti'),'disponibila');
COMMIT;
SELECT * FROM excursie;


-- c
DECLARE
    v_cod excursie.cod_excursie % TYPE := &p_cod;
    v_orase excursie.orase % TYPE;
BEGIN 
    SELECT orase INTO v_orase
    FROM excursie
    WHERE cod_excursie = v_cod;
    
--    DBMS_OUTPUT.PUT_LINE('Numarul de orase vizitate pt excursie cu codul ' || v_cod || ' este ' || v_orase.COUNT);
    for contor in v_orase.FIRST .. v_orase.LAST LOOP
        DBMS_OUTPUT.PUT_LINE(v_orase(contor));
    END LOOP;
END;
/

-- d DE LUAT DIN FISIER
select * from excursie;
DECLARE 
    TYPE t_ind IS TABLE OF excursie.cod_excursie 