CREATE TABLE adrese_ama(
                        id_adresa NUMBER(4) PRIMARY KEY,
                        strada VARCHAR2(20),
                        nr NUMBER(3),
                        oras VARCHAR2(20) NOT NULL,
                        regiune VARCHAR2(20)
                      );
INSERT INTO adrese_ama
VALUES(1, 'Tineretului', 3, 'Roman', 'Moldova');
INSERT INTO adrese_ama
VALUES(2, 'Nicolae Balcescu', 53, 'Bucuresti', 'Muntenia');
INSERT INTO adrese_ama
VALUES(3, 'Carol', 2, 'Bucuresti', 'Muntenia');
INSERT INTO adrese_ama
VALUES(4, 'Splaiul Independetei', 78, 'Bucuresti', 'Muntenia');
INSERT INTO adrese_ama
VALUES(5, 'Dobrogeanu Gherea', 22, 'Bacau', 'Moldova');


CREATE TABLE spitale_ama(
                        id_spital NUMBER(4) PRIMARY KEY,
                        id_adresa NUMBER(4) REFERENCES adrese_ama (id_adresa) ON DELETE CASCADE,
                        nume_spital VARCHAR2(30)
                        );
INSERT INTO spitale_ama
VALUES(1, 1, 'Sf. Pantelimon');
INSERT INTO spitale_ama
VALUES(2, 2, 'SMU Roman');
INSERT INTO spitale_ama
VALUES(3, 3, 'Sf. Maria');
INSERT INTO spitale_ama
VALUES(4, 4, 'Universitar');
INSERT INTO spitale_ama
VALUES(5, 5, 'Sf. Spiridon');




CREATE TABLE sectii_ama(
                        nume_sectie VARCHAR2(25) PRIMARY KEY
                      );
INSERT INTO sectii_ama
VALUES('Cardiologie');
INSERT INTO sectii_ama
VALUES('Neurologie');
INSERT INTO sectii_ama
VALUES('Chirurgie');
INSERT INTO sectii_ama
VALUES('Psihiatrie');
INSERT INTO sectii_ama
VALUES('Endocrine');
INSERT INTO sectii_ama
VALUES('ORL');

CREATE TABLE sectie_spital_ama(
                        id_spital NUMBER(4) REFERENCES spitale_ama (id_spital) ON DELETE CASCADE,
                        nume_sectie VARCHAR2(25) REFERENCES sectii_ama (nume_sectie) ON DELETE CASCADE,
                        nr_paturi NUMBER(2) CHECK (nr_paturi >= 0),
                        CONSTRAINT sectii_ama_pk PRIMARY KEY(id_spital, nume_sectie)
                        );
INSERT INTO sectie_spital_ama VALUES(1, 'Cardiologie', 20);
INSERT INTO sectie_spital_ama VALUES(1, 'Neurologie', 15);
INSERT INTO sectie_spital_ama VALUES(1, 'Chirurgie', 25);
INSERT INTO sectie_spital_ama VALUES(2, 'Psihiatrie', 30);
INSERT INTO sectie_spital_ama VALUES(2, 'Endocrine', 15);
INSERT INTO sectie_spital_ama VALUES(3, 'Chirurgie', 15);
INSERT INTO sectie_spital_ama VALUES(4, 'ORL', 25);
INSERT INTO sectie_spital_ama VALUES(4, 'Cardiologie', 5);
INSERT INTO sectie_spital_ama VALUES(5, 'Cardiologie', 50);
INSERT INTO sectie_spital_ama VALUES(5, 'Endocrine', 10);

CREATE TABLE persoane_ama(
                         cnp VARCHAR2(13) PRIMARY KEY,
                         nume VARCHAR2(20),
                         prenume VARCHAR2(20),
                         id_spital NUMBER(4),
                         nume_sectie VARCHAR2(25),
                         CONSTRAINT doctori_ama_fk FOREIGN KEY (id_spital, nume_sectie) REFERENCES sectie_spital_ama(id_spital, nume_sectie) ON DELETE CASCADE
                         );
INSERT INTO persoane_ama VALUES('1981182622282', 'Manolache', 'Andrei', 1, 'Cardiologie');
INSERT INTO persoane_ama VALUES('5156681112069', 'Firastrau', 'Victor', 2, 'Psihiatrie');
INSERT INTO persoane_ama VALUES('1526188822770', 'Tubucanu', 'Alina', 4, 'Cardiologie');
INSERT INTO persoane_ama VALUES('2201294741365', 'Butiurca', 'Victor', 3, 'Chirurgie');
INSERT INTO persoane_ama VALUES('1981414456682', 'Piturca', 'Victor', 5, 'Cardiologie');
INSERT INTO persoane_ama VALUES('100000331452', 'Birjovanu', 'Marius', 4, 'ORL');
INSERT INTO persoane_ama VALUES('238100000082', 'David', 'Mihaela', 4, 'ORL');
INSERT INTO persoane_ama VALUES('123123546446', 'Duncea', 'Vlad', 4, 'ORL');
INSERT INTO persoane_ama VALUES('6125328135721', 'Geangu', 'Eliza', 1, 'Cardiologie');
INSERT INTO persoane_ama VALUES('1102302368591', 'Acasandrei', 'Dedilia', 3, 'Chirurgie');
INSERT INTO persoane_ama VALUES('1231231551252', 'Anca', 'Alina', 3, 'Chirurgie');
INSERT INTO persoane_ama VALUES('2501413364055', 'Tura', 'Andrei', 3, 'Chirurgie');
INSERT INTO persoane_ama VALUES('1278321783181', 'Mocanu', 'Geta', 2, 'Endocrine');
INSERT INTO persoane_ama VALUES('6772728912312', 'Maftei', 'Ion', 3, 'Chirurgie');
                        
CREATE TABLE doctori_ama(
                         cnp VARCHAR2(13) PRIMARY KEY REFERENCES persoane_ama (cnp) ON DELETE CASCADE,
                         cnp_sef VARCHAR2(13),
                         salariu NUMBER(7,2) CHECK(salariu > 0)
                        );               
INSERT INTO doctori_ama VALUES('1981182622282', null,8500);
INSERT INTO doctori_ama VALUES('1526188822770', null, 6500);
INSERT INTO doctori_ama VALUES('2201294741365', '1231231551252', 9000);
INSERT INTO doctori_ama VALUES('100000331452', null, 5500.50);
INSERT INTO doctori_ama VALUES('123123546446', '100000331452', 500);
INSERT INTO doctori_ama VALUES('1231231551252', NULL, 7880);
INSERT INTO doctori_ama VALUES('2501413364055', '1231231551252', 7000);
INSERT INTO doctori_ama VALUES('1278321783181', null, 9000);

CREATE TABLE pacienti_ama(
                          cnp VARCHAR2(13) PRIMARY KEY REFERENCES persoane_ama (cnp) ON DELETE CASCADE,
                          data DATE DEFAULT SYSDATE
                         );                     
INSERT INTO pacienti_ama VALUES('238100000082', TO_DATE('20-06-2020', 'DD-MM-YYYY'));
INSERT INTO pacienti_ama VALUES('1981414456682', TO_DATE('2-04-2020', 'DD-MM-YYYY'));
INSERT INTO pacienti_ama VALUES('5156681112069', TO_DATE('1-05-2020', 'DD-MM-YYYY'));
INSERT INTO pacienti_ama VALUES('6125328135721', TO_DATE('20-05-2020', 'DD-MM-YYYY'));
INSERT INTO pacienti_ama VALUES('1102302368591', TO_DATE('16-05-2020', 'DD-MM-YYYY'));
INSERT INTO pacienti_ama VALUES('6772728912312', TO_DATE('5-03-2020', 'DD-MM-YYYY'));
                  
CREATE TABLE retete_ama(
                        id_reteta NUMERIC(5) PRIMARY KEY,
                        cnp_doctor VARCHAR2(13) REFERENCES doctori_ama (cnp) ON DELETE CASCADE,
                        cnp_pacient VARCHAR2(13) REFERENCES pacienti_ama (cnp) ON DELETE CASCADE,
                        data DATE DEFAULT SYSDATE
                        );
INSERT INTO retete_ama VALUES(1, '1981182622282', '1981414456682', TO_DATE('5-04-2020', 'DD-MM-YYYY'));
INSERT INTO retete_ama VALUES(2, '1981182622282', '1981414456682', TO_DATE('20-04-2020', 'DD-MM-YYYY'));
INSERT INTO retete_ama VALUES(3, '1231231551252', '1102302368591', TO_DATE('1-05-2020', 'DD-MM-YYYY'));
INSERT INTO retete_ama VALUES(4, '100000331452', '238100000082', TO_DATE('16-06-2020', 'DD-MM-YYYY'));
INSERT INTO retete_ama VALUES(5, '1981182622282', '1981414456682', TO_DATE('27-04-2020', 'DD-MM-YYYY'));
INSERT INTO retete_ama VALUES(6, '1231231551252', '1102302368591', TO_DATE('9-05-2020', 'DD-MM-YYYY'));
INSERT INTO retete_ama VALUES(7, '100000331452', '238100000082', TO_DATE('20-06-2020', 'DD-MM-YYYY'));   

CREATE TABLE medicamente_ama(
                            id_medicament NUMERIC(5) PRIMARY KEY,
                            nume_medicament varchar2(30) NOT NULL,
                            cantitate numeric(4) CHECK(cantitate > 0)
                            );
INSERT INTO medicamente_ama VALUES(1, 'Agocalmin', 600);
INSERT INTO medicamente_ama VALUES(2, 'Cipralex', 300);
INSERT INTO medicamente_ama VALUES(3, 'Nidoflor', 500);
INSERT INTO medicamente_ama VALUES(4, 'Controloc', 500);
INSERT INTO medicamente_ama VALUES(5, 'Paracetamol', 1000);
INSERT INTO medicamente_ama VALUES(6, 'Cordarone', 100);
INSERT INTO medicamente_ama VALUES(7, 'Ibuprofen', 300);
INSERT INTO medicamente_ama VALUES(8, 'Ibuprofen', 800);
INSERT INTO medicamente_ama VALUES(9, 'Paracetamol', 600);
INSERT INTO medicamente_ama VALUES(10, 'Cordarone', 200);
INSERT INTO medicamente_ama VALUES(11, 'Cordarone', 400);





CREATE TABLE dozaje_ama(
                   id_medicament NUMERIC(5) REFERENCES medicamente_ama (id_medicament) ON DELETE CASCADE,
                   id_reteta NUMERIC(5) REFERENCES retete_ama (id_reteta) ON DELETE CASCADE,
                   cantitate NUMERIC(3),
                   CONSTRAINT dozaje_ama_pk PRIMARY KEY(id_medicament, id_reteta)                   
                  );
INSERT INTO dozaje_ama VALUES(1, 1, 2);
INSERT INTO dozaje_ama VALUES(2, 1, 2);
INSERT INTO dozaje_ama VALUES(3, 1, 1);
INSERT INTO dozaje_ama VALUES(1, 2, 3);
INSERT INTO dozaje_ama VALUES(3, 2, 1);
INSERT INTO dozaje_ama VALUES(2, 3, 1);
INSERT INTO dozaje_ama VALUES(4, 3, 1);
INSERT INTO dozaje_ama VALUES(2, 4, 2);
INSERT INTO dozaje_ama VALUES(5, 4, 1);
INSERT INTO dozaje_ama VALUES(6, 4, 2);
INSERT INTO dozaje_ama VALUES(1, 5, 2);
INSERT INTO dozaje_ama VALUES(2, 5, 1);
INSERT INTO dozaje_ama VALUES(3, 5, 3);





