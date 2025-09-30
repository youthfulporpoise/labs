-- Given the schema Employee (empid, empname, joining date, relieving date, salary)
--   (a) Find the service (in years) for each relieved employee.
--   (b) Find the Pension amount to be paid to each relieved employee. (Pension is
--     equal to the years of service times salary divided by 100.
-- Use cursors.

CREATE DATABASE IF NOT EXISTS `23cs031-2-6`;
USE `23cs031-2-6`;

DROP TABLE employee, benefits;
DROP PROCEDURE IF EXISTS benefit_compute;

CREATE TABLE IF NOT EXISTS `employee` (
  empid             INTEGER     PRIMARY KEY,
  empname           VARCHAR(64),
  joining_date      DATE,
  relieving_date    DATE,
  salary            FLOAT
);

CREATE TABLE IF NOT EXISTS `benefits` (
  empid             INTEGER       PRIMARY KEY,
  years_of_service  INTEGER,
  pension           FLOAT
--  FOREIGN KEY (empid) REFERENCES employee(empid)
);

INSERT INTO employee (empid, empname, joining_date, relieving_date, salary)
VALUES
  (  1,     'Rajesh Singh',      '2011-06-15',  '2025-04-10',   56100.00 ),
  (  2,     'Neeraj Kumar',      '2013-09-01',  '2024-12-31',   61300.00 ),
  (  3,     'Saurabh Chauhan',   '2015-02-23',  '2025-05-01',   69400.00 ),
  (  4,     'Arvind Nair',       '2010-12-10',  '2020-10-05',  121200.00 ),
  (  5,     'Sunil Menon',       '2018-03-18',  NULL,           29200.00 ),
  (  6,     'Akash Sharma',      '2016-01-28',  '2023-06-30',   25500.00 ),
  (  7,     'Deepak Joshi',      '2014-07-14',  '2022-08-31',   35400.00 ),
  (  8,     'Praveen Mishra',    '2011-11-30',  '2024-06-15',  139600.00 ),
  (  9,     'Harpreet Kaur',     '2012-05-20',  '2023-11-11',  144200.00 ),
  ( 10,     'Manoj Verma',       '2009-06-05',  '2024-03-16',  182200.00 ),
  ( 11,     'Sameer Desai',      '2017-08-12',  NULL,           29200.00 ),
  ( 12,     'Rakesh Rao',        '2014-03-22',  '2025-05-29',   56100.00 ),
  ( 13,     'Vivek Singh',       '2019-10-09',  NULL,           25500.00 ),
  ( 14,     'Arjun Ghosh',       '2016-02-16',  '2024-12-31',  139600.00 ),
  ( 15,     'Nitin Reddy',       '2013-01-04',  '2023-02-20',   69200.00 ),
  ( 16,     'Mohit Chaturvedi',  '2011-07-15',  '2022-10-10',  121200.00 ),
  ( 17,     'Sandeep Roy',       '2008-08-08',  '2023-05-04',  130600.00 ),
  ( 18,     'Abhishek Gupta',    '2018-11-22',  NULL,           35400.00 ),
  ( 19,     'Kiran S. Pillai',   '2015-04-01',  NULL,           25400.00 ),
  ( 20,     'Priya S. Shetty',   '2020-09-25',  NULL,           56100.00 );

DELIMITER @@

CREATE PROCEDURE benefit_compute ()
BEGIN
  DECLARE done INT DEFAULT FALSE;
  DECLARE eid INT;
  DECLARE jd, rd DATE;
  DECLARE sal FLOAT;

  DECLARE service INT;
  DECLARE pension FLOAT;

  DECLARE cur CURSOR FOR
    SELECT empid, joining_date, relieving_date, salary
    FROM employee
    WHERE relieving_date IS NOT NULL;
  DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

  OPEN cur;

  rd_loop: LOOP
    FETCH cur INTO eid, jd, rd, sal;
    IF done THEN
      LEAVE rd_loop;
    END IF;

    SET service = TIMESTAMPDIFF(YEAR, jd, rd);
    SET pension = (service * sal) / 100;

    INSERT INTO benefits
    VALUES
      (eid, service, pension);
  END LOOP;

END @@

DELIMITER ;

CALL benefit_compute();

SELECT e.empid, e.empname, b.years_of_service, b.pension
FROM employee e
JOIN benefits b ON b.empid = e.empid;
