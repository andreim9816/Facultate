-- lab 2

-- ex 1

SET SERVEROUTPUT ON

COMMIT;

DECLARE
    TYPE tip_colectie IS
        TABLE OF employees_vst%rowtype;
    t tip_colectie;
BEGIN
    SELECT
        *
    BULK COLLECT
    INTO t
    FROM
        (
            SELECT
                *
            FROM
                employees_vst
            WHERE
                commission_pct IS NULL
            ORDER BY
                salary
        )
    WHERE
        ROWNUM <= 5;

    FOR i IN 1..t.count LOOP
        dbms_output.put_line('Old: ' || t(i).employee_id || ' ' || t(i).salary);

        UPDATE employees_vst
        SET
            salary = 1.05 * salary
        WHERE
            employee_id = t(i).employee_id
        RETURNING salary INTO t(i).salary;
        
        dbms_output.put_line('New: ' || t(i).employee_id || ' ' || t(i).salary);
    END LOOP;

END;
/

ROLLBACK;

-- ex 2
CREATE OR REPLACE TYPE tip_orase IS TABLE OF VARCHAR2(100);
/

CREATE TABLE excursie (cod_excursie NUMBER(4),
                       denumire VARCHAR2(20),
                       oras tip_orase,
                       status VARCHAR2(15))
                       NESTED TABLE orase STORE AS tabel_orase;
                      
--a
INSERT INTO excursie
VALUES ('1', 'Excursia 1', tip_orase('Bucuresti', 'Pitesti', 'Iasi'), 'disponibila');

INSERT INTO excursie
VALUES ('2', 'Excursia 2', tip_orase('Bucuresti', 'Ploiesti', 'Iasi'), 'disponibila');

INSERT INTO excursie
VALUES ('3', 'Excursia 3', tip_orase('Brasov', 'Iasi', 'Roman'), 'anulata');

INSERT INTO excursie
VALUES ('4', 'Excursia 4', NULL, 'disponibila');

-- b
DECLARE 
    v_oras_nou VARCHAR2(100) := '&p_oras_nou';
    v_cod_excursie excursie.cod_excursie % TYPE := &p_cod;
    v_lista tip_orase;
BEGIN
    SELECT orase INTO v_lista
    FROM excursie
    where cod_excursie = v_cod_excursie;
    v_lista.EXTEND();
    v_lista.
    
    FOR i IN 1..v_lista.COUNT LOOP
        v(i)
    END LOOP;    
    