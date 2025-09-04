CREATE DATABASE IF NOT EXISTS `23cs031-1-5`;
USE `23cs031-1-5`;

DROP TABLE IF EXISTS
  Loan,
  Savings,
  Customer,
  Branch;

CREATE TABLE IF NOT EXISTS Branch (
  branch_id           INTEGER           PRIMARY KEY,
  branch_name         VARCHAR(64),
  branch_city         VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS Customer (
  customer_id         INTEGER           PRIMARY KEY,
  customer_name       VARCHAR(64),
  customer_city       VARCHAR(64)
);

CREATE TABLE IF NOT EXISTS Savings (
  customer_id         INTEGER,
  branch_id           INTEGER,
  savings_accno       INTEGER,
  balance             FLOAT,
  FOREIGN KEY (customer_id) REFERENCES Customer(customer_id),
  FOREIGN KEY (branch_id) REFERENCES Branch(branch_id)
);

CREATE TABLE IF NOT EXISTS Loan (
  customer_id         INTEGER,
  branch_id           INTEGER,
  loan_accno          INTEGER,
  balance             FLOAT,
  FOREIGN KEY (customer_id) REFERENCES Customer(customer_id),
  FOREIGN KEY (branch_id) REFERENCES Branch(branch_id)
);

INSERT INTO Branch (branch_id, branch_name, branch_city)
VALUES
  (1  ,  'Citibank Downtown'             , 'New York'     ),
  (2  ,  'Citibank Central'              , 'London'       ),
  (3  ,  'Citibank Main'                 , 'Mumbai'       ),
  (4  ,  'Citibank Westside'             , 'Sydney'       ),
  (5  ,  'Citibank North Branch'         , 'Toronto'      ),
  (6  ,  'Citibank East End'             , 'Dubai'        ),
  (7  ,  'Citibank CBD'                  , 'Singapore'    ),
  (8  ,  'Citibank Financial District'   , 'Hong Kong'    ),
  (9  ,  'Citibank City Center'          , 'Johannesburg' ),
  (10 ,  'Citibank Main Office'          , 'Dubai'        ),
  (11 ,  'Citibank Uptown'               , 'Delhi'        ),
  (12 ,  'Citibank Riverside'            , 'Cape Town'    );

INSERT INTO Customer (customer_id, customer_name, customer_city)
VALUES
  (1    ,  'Arjun Reddy'         , 'Bangalore'    ),
  (2    ,  'Priya Sharma'        , 'Chennai'      ),
  (3    ,  'Fatima Khan'         , 'Dubai'        ),
  (4    ,  'John Smith'          , 'New York'     ),
  (5    ,  'Suresh Kumar'        , 'Coimbatore'   ),
  (6    ,  'Linda Johnson'       , 'London'       ),
  (7    ,  'Rajesh Iyer'         , 'Madurai'      ),
  (8    ,  'Maria Gonzalez'      , 'Toronto'      ),
  (9    ,  'Naveen Patil'        , 'Pune'         ),
  (10   ,  'James Brown'         , 'Hong Kong'    ),
  (11   ,  'Ayesha Siddiqui'     , 'Mumbai'       ),
  (12   ,  'Sunil Menon'         , 'Kochi'        ),
  (13   ,  'Elizabeth Davis'     , 'Sydney'       ),
  (14   ,  'Vikram Singh'        , 'Delhi'        ),
  (15   ,  'Jessica Lee'         , 'Singapore'    ),
  (16   ,  'Kavita Reddy'        , 'Hyderabad'    ),
  (17   ,  'Mohammed Ali'        , 'Johannesburg' ),
  (18   ,  'Ravi Kumar'          , 'Chennai'      ),
  (19   ,  'Sandra Miller'       , 'Cape Town'    ),
  (20   ,  'Lakshmi Narayan'     , 'Bangalore'    ),
  (21   ,  'Emily Wilson'        , 'London'       ),
  (22   ,  'Manish Gupta'        , 'Mumbai'       ),
  (23   ,  'Chitra Subramanian'  , 'Chennai'      ),
  (24   ,  'Tom Harris'          , 'New York'     ),
  (25   ,  'Anil Nair'           , 'Kochi'        );

INSERT INTO Savings (savings_accno, customer_id, branch_id, balance)
VALUES
  (101  ,    1  ,   3   ,     25000.50),
  (102  ,    2  ,   11  ,     30000.75),
  (103  ,    3  ,   6   ,    120000.00),
  (104  ,    4  ,   1   ,     5000.00 ),
  (105  ,    5  ,   3   ,    45000.00 ),
  (106  ,    6  ,   2   ,    67000.25 ),
  (107  ,    7  ,   11  ,    150000.00),
  (108  ,    8  ,   5   ,    38000.10 ),
  (109  ,    9  ,   3   ,    29000.20 ),
  (110  ,   10  ,   8   ,   125000.00 ),
  (111  ,   11  ,   3   ,    64000.00 ),
  (112  ,   12  ,   7   ,    98000.40 ),
  (113  ,   13  ,   4   ,     5600.00 ),
  (114  ,   14  ,   11  ,    39000.65 ),
  (115  ,   15  ,   7   ,    87000.00 ),
  (116  ,   16  ,   3   ,    78000.12 ),
  (117  ,   17  ,   9   ,    35000.00 ),
  (118  ,   18  ,   11  ,    44700.50 ),
  (119  ,   19  ,   12  ,    29000.10 ),
  (120  ,   20  ,   3   ,    41000.00 ),
  (121  ,   21  ,   2   ,    22000.00 ),
  (122  ,   22  ,   3   ,    31000.30 ),
  (123  ,   23  ,   11  ,    54000.00 ),
  (124  ,   24  ,   1   ,    39000.00 ),
  (125  ,   25  ,   7   ,    54000.00 ),

  (126  ,    1  ,   1   ,    15000.25),
  (127  ,    2  ,   2   ,    35000.10),
  (128  ,    3  ,   6   ,    85000.00),
  (129  ,    4  ,   1   ,     6000.00),
  (130  ,    5  ,   11  ,    40000.00),
  (131  ,    6  ,   2   ,    28000.00),
  (132  ,    7  ,   11  ,    77000.00),
  (133  ,   12  ,   7   ,    45000.00),
  (134  ,   14  ,   3   ,    22300.50),
  (135  ,   15  ,   7   ,    18000.00),
  (136  ,   18  ,   11  ,    37600.00),
  (137  ,   20  ,   3   ,    42000.00),
  (138  ,   21  ,   2   ,    29000.00),
  (139  ,   22  ,   3   ,    43000.40),
  (140  ,   23  ,   11  ,   12500.00 );

INSERT INTO Loan (loan_accno , customer_id, branch_id, balance)
VALUES
  (201  ,    1  ,   3   ,    120000.00),
  (202  ,    2  ,   11  ,    85000.50 ),
  (203  ,    3  ,   6   ,    60000.00 ),
  (204  ,    4  ,   1   ,    45000.00 ),
  (205  ,    5  ,   3   ,    75000.00 ),
  (206  ,    6  ,   2   ,    47000.00 ),
  (207  ,    7  ,   11  ,    88000.00 ),
  (208  ,    8  ,   5   ,    30000.00 ),
  (209  ,    9  ,   3   ,    40000.00 ),
  (210  ,   10  ,   8   ,   130000.00 ),
  (211  ,   11  ,   3   ,    39000.00 ),
  (212  ,   12  ,   7   ,   125000.00 ),
  (213  ,   13  ,   4   ,    27000.00 ),
  (214  ,   14  ,   11  ,    57000.00 ),
  (215  ,   15  ,   7   ,    94000.00 ),
  (216  ,   16  ,   3   ,    89000.00 ),
  (217  ,   17  ,   9   ,    44000.00 ),
  (218  ,   18  ,   11  ,    49000.00 ),
  (219  ,   19  ,   12  ,    35000.00 ),
  (220  ,   20  ,   3   ,    47000.00 ),
  (221  ,   21  ,   2   ,    31000.00 ),
  (222  ,   22  ,   3   ,    58000.00 ),
  (223  ,   23  ,   11  ,    53000.00 ),
  (224  ,   24  ,   1   ,    61000.00 ),
  (225  ,   25  ,   7   ,    76000.00 ),

  (226  ,    1  ,   1   ,    39000.00 ),
  (227  ,    2  ,   2   ,    68000.00 ),
  (228  ,    3  ,   6   ,    21000.00 ),
  (229  ,    4  ,   1   ,    15000.00 ),
  (230  ,    5  ,   11  ,    36000.00 ),
  (231  ,    6  ,   2   ,    22000.00 ),
  (232  ,    7  ,   11  ,    49000.00 ),
  (233  ,   12  ,   7   ,    87000.00 ),
  (234  ,   14  ,   3   ,    12000.00 ),
  (235  ,   15  ,   7   ,    18000.00 );

--  (a) List the details of the customers who live the same city where they have
--  an account.
--
SELECT DISTINCT c.customer_id, c.customer_name, c.customer_city, b.branch_city
FROM Customer c
JOIN Savings s ON s.customer_id = c.customer_id
JOIN Branch b ON b.branch_id = s.branch_id
WHERE c.customer_city = b.branch_city
ORDER BY customer_id ASC;
--  
--  OUTPUT.
--  +-------------+-----------------+---------------+--------------+
--  | customer_id | customer_name   | customer_city | branch_city  |
--  +-------------+-----------------+---------------+--------------+
--  |           3 | Fatima Khan     | Dubai         | Dubai        |
--  |           4 | John Smith      | New York      | New York     |
--  |           6 | Linda Johnson   | London        | London       |
--  |           8 | Maria Gonzalez  | Toronto       | Toronto      |
--  |          10 | James Brown     | Hong Kong     | Hong Kong    |
--  |          11 | Ayesha Siddiqui | Mumbai        | Mumbai       |
--  |          13 | Elizabeth Davis | Sydney        | Sydney       |
--  |          14 | Vikram Singh    | Delhi         | Delhi        |
--  |          15 | Jessica Lee     | Singapore     | Singapore    |
--  |          17 | Mohammed Ali    | Johannesburg  | Johannesburg |
--  |          19 | Sandra Miller   | Cape Town     | Cape Town    |
--  |          21 | Emily Wilson    | London        | London       |
--  |          22 | Manish Gupta    | Mumbai        | Mumbai       |
--  |          24 | Tom Harris      | New York      | New York     |
--  +-------------+-----------------+---------------+--------------+
--  14 rows in set (0.001 sec)

--  (b) List the customers who have an account in a given branch city.
--  
SELECT DISTINCT c.customer_name, c.customer_city
FROM Customer c
JOIN Savings s ON s.customer_id = c.customer_id
JOIN Branch b ON b.branch_id = s.branch_id
WHERE b.branch_city = "Singapore";
--  
--  OUTPUT.
--  +---------------+---------------+
--  | customer_name | customer_city |
--  +---------------+---------------+
--  | Sunil Menon   | Kochi         |
--  | Jessica Lee   | Singapore     |
--  | Anil Nair     | Kochi         |
--  +---------------+---------------+
--  3 rows in set (0.001 sec)

--  (c) List the customers who have accounts in more than one branch.
--  
SELECT c.customer_name, b.branch_name, COUNT(s.savings_accno) AS acc_count
FROM Customer c
JOIN Savings s ON c.customer_id = s.customer_id
JOIN Branch b ON b.branch_id = s.branch_id
GROUP BY c.customer_name, b.branch_name
HAVING acc_count > 1;
--  
--  OUTPUT.
--  +--------------------+-------------------+-----------+
--  | customer_name      | branch_name       | acc_count |
--  +--------------------+-------------------+-----------+
--  | Chitra Subramanian | Citibank Uptown   |         2 |
--  | Emily Wilson       | Citibank Central  |         2 |
--  | Fatima Khan        | Citibank East End |         2 |
--  | Jessica Lee        | Citibank CBD      |         2 |
--  | John Smith         | Citibank Downtown |         2 |
--  | Lakshmi Narayan    | Citibank Main     |         2 |
--  | Linda Johnson      | Citibank Central  |         2 |
--  | Manish Gupta       | Citibank Main     |         2 |
--  | Rajesh Iyer        | Citibank Uptown   |         2 |
--  | Ravi Kumar         | Citibank Uptown   |         2 |
--  | Sunil Menon        | Citibank CBD      |         2 |
--  +--------------------+-------------------+-----------+
--  11 rows in set (0.001 sec)

--  (d) List the details of customers who:
--        - do not have a savings account but have a loan;
--        - do not have a loan but have a savings account;
--        - have both a savings account and loan.
--  
SELECT c.customer_id, c.customer_name, c.customer_city
FROM Customer c
WHERE
  c.customer_id IN (SELECT customer_id FROM Savings)
  AND
  c.customer_id NOT IN (SELECT customer_id FROM Loan);

SELECT c.customer_id, c.customer_name, c.customer_city
FROM Customer c
WHERE
  c.customer_id NOT IN (SELECT customer_id FROM Savings)
  AND
  c.customer_id IN (SELECT customer_id FROM Loan);

SELECT c.customer_id, c.customer_name, c.customer_city
FROM Customer c
WHERE
  c.customer_id IN (SELECT customer_id FROM Savings)
  AND
  c.customer_id IN (SELECT customer_id FROM Loan);
--  
--  OUTPUT.
--  Empty set (0.000 sec)
--  
--  Empty set (0.000 sec)
--  
--  +-------------+--------------------+---------------+
--  | customer_id | customer_name      | customer_city |
--  +-------------+--------------------+---------------+
--  |           1 | Arjun Reddy        | Bangalore     |
--  |           2 | Priya Sharma       | Chennai       |
--  |           3 | Fatima Khan        | Dubai         |
--  |           4 | John Smith         | New York      |
--  |           5 | Suresh Kumar       | Coimbatore    |
--  |           6 | Linda Johnson      | London        |
--  |           7 | Rajesh Iyer        | Madurai       |
--  |           8 | Maria Gonzalez     | Toronto       |
--  |           9 | Naveen Patil       | Pune          |
--  |          10 | James Brown        | Hong Kong     |
--  |          11 | Ayesha Siddiqui    | Mumbai        |
--  |          12 | Sunil Menon        | Kochi         |
--  |          13 | Elizabeth Davis    | Sydney        |
--  |          14 | Vikram Singh       | Delhi         |
--  |          15 | Jessica Lee        | Singapore     |
--  |          16 | Kavita Reddy       | Hyderabad     |
--  |          17 | Mohammed Ali       | Johannesburg  |
--  |          18 | Ravi Kumar         | Chennai       |
--  |          19 | Sandra Miller      | Cape Town     |
--  |          20 | Lakshmi Narayan    | Bangalore     |
--  |          21 | Emily Wilson       | London        |
--  |          22 | Manish Gupta       | Mumbai        |
--  |          23 | Chitra Subramanian | Chennai       |
--  |          24 | Tom Harris         | New York      |
--  |          25 | Anil Nair          | Kochi         |
--  +-------------+--------------------+---------------+
--  25 rows in set (0.000 sec)

--  (f) For each branch, produce a list showing:
--        - total number of customers;
--        - total number of customers with only a loan;
--        - total number of customers with only a savings account;
--        - total number of customers with both a loan and a savings account.
--
SELECT
  b.branch_id, b.branch_name, b.branch_city, COUNT(c.customer_id) AS cust_cnt
FROM Branch b
JOIN Savings s ON s.branch_id = b.branch_id
JOIN Loan l ON l.branch_id = b.branch_id
JOIN Customer c ON
  c.customer_id = s.customer_id
  AND
  c.customer_id = l.customer_id
GROUP BY b.branch_id;

SELECT
  b.branch_id, b.branch_name, b.branch_city, COUNT(c.customer_id) AS cust_cnt
FROM Branch b
JOIN Savings s ON s.branch_id = b.branch_id
JOIN Loan l ON l.branch_id = b.branch_id
JOIN Customer c ON
  c.customer_id = s.customer_id
  AND
  c.customer_id = l.customer_id
WHERE
  c.customer_id IN (SELECT customer_id FROM Savings)
  AND
  c.customer_id NOT IN (SELECT customer_id FROM Loan)
GROUP BY b.branch_id;

SELECT
  b.branch_id, b.branch_name, b.branch_city, COUNT(c.customer_id) AS cust_cnt
FROM Branch b
JOIN Savings s ON s.branch_id = b.branch_id
JOIN Loan l ON l.branch_id = b.branch_id
JOIN Customer c ON
  c.customer_id = s.customer_id
  AND
  c.customer_id = l.customer_id
WHERE
  c.customer_id NOT IN (SELECT customer_id FROM Savings)
  AND
  c.customer_id IN (SELECT customer_id FROM Loan)
GROUP BY b.branch_id;

SELECT
  b.branch_id, b.branch_name, b.branch_city, COUNT(c.customer_id) AS cust_cnt
FROM Branch b
JOIN Savings s ON s.branch_id = b.branch_id
JOIN Loan l ON l.branch_id = b.branch_id
JOIN Customer c ON
  c.customer_id = s.customer_id
  AND
  c.customer_id = l.customer_id
WHERE
  c.customer_id IN (SELECT customer_id FROM Savings)
  AND
  c.customer_id IN (SELECT customer_id FROM Loan)
GROUP BY b.branch_id;
--  
--  OUTPUT.
--  +-----------+-----------------------------+--------------+----------+
--  | branch_id | branch_name                 | branch_city  | cust_cnt |
--  +-----------+-----------------------------+--------------+----------+
--  |         1 | Citibank Downtown           | New York     |        6 |
--  |         2 | Citibank Central            | London       |        7 |
--  |         3 | Citibank Main               | Mumbai       |       10 |
--  |         4 | Citibank Westside           | Sydney       |        1 |
--  |         5 | Citibank North Branch       | Toronto      |        1 |
--  |         6 | Citibank East End           | Dubai        |        4 |
--  |         7 | Citibank CBD                | Singapore    |        9 |
--  |         8 | Citibank Financial District | Hong Kong    |        1 |
--  |         9 | Citibank City Center        | Johannesburg |        1 |
--  |        11 | Citibank Uptown             | Delhi        |       11 |
--  |        12 | Citibank Riverside          | Cape Town    |        1 |
--  +-----------+-----------------------------+--------------+----------+
--  11 rows in set (0.001 sec)
--  
--  Empty set (0.001 sec)
--  
--  Empty set (0.001 sec)
--  
--  +-----------+-----------------------------+--------------+----------+
--  | branch_id | branch_name                 | branch_city  | cust_cnt |
--  +-----------+-----------------------------+--------------+----------+
--  |         1 | Citibank Downtown           | New York     |        6 |
--  |         2 | Citibank Central            | London       |        7 |
--  |         3 | Citibank Main               | Mumbai       |       10 |
--  |         4 | Citibank Westside           | Sydney       |        1 |
--  |         5 | Citibank North Branch       | Toronto      |        1 |
--  |         6 | Citibank East End           | Dubai        |        4 |
--  |         7 | Citibank CBD                | Singapore    |        9 |
--  |         8 | Citibank Financial District | Hong Kong    |        1 |
--  |         9 | Citibank City Center        | Johannesburg |        1 |
--  |        11 | Citibank Uptown             | Delhi        |       11 |
--  |        12 | Citibank Riverside          | Cape Town    |        1 |
--  +-----------+-----------------------------+--------------+----------+
--  11 rows in set (0.001 sec)

--  (g) Find the details of the branch that has issued the maximum total amount
--  of loan.
--
DROP VIEW IF EXISTS LoanCount;
CREATE VIEW IF NOT EXISTS LoanCount
AS
  SELECT b.branch_id, COUNT(l.loan_accno) AS loan_cnt
  FROM Branch b
  JOIN Loan l ON b.branch_id = l.branch_id
  GROUP BY b.branch_id
  ORDER BY loan_cnt DESC;

SELECT b.branch_id, b.branch_name, lc.loan_cnt
FROM Branch b
JOIN LoanCount lc ON b.branch_id = lc.branch_id
WHERE lc.loan_cnt = (SELECT MAX(loan_cnt) FROM LoanCount);
--  
--  OUTPUT.
--  +-----------+---------------+----------+
--  | branch_id | branch_name   | loan_cnt |
--  +-----------+---------------+----------+
--  |         3 | Citibank Main |        8 |
--  +-----------+---------------+----------+
--  1 row in set (0.003 sec)

--  (h) Find the details of the bank that has not issued any loans at all.
--
SELECT b.branch_id, b.branch_name, b.branch_city
FROM Branch b
WHERE b.branch_id NOT IN (SELECT branch_id FROM Loan);
--  
--  OUTPUT.
--  +-----------+----------------------+-------------+
--  | branch_id | branch_name          | branch_city |
--  +-----------+----------------------+-------------+
--  |        10 | Citibank Main Office | Dubai       |
--  +-----------+----------------------+-------------+
--  1 row in set (0.000 sec)

--  (i) For each customer, produce a list showing the total savings balance and
--  and loan balance for all branches where they have either a loan and/or a
--  savings account.
--
SELECT
  c.customer_id, c.customer_name,
  SUM(l.balance) AS loan_balance,
  SUM(s.balance) AS savings_balance
FROM Customer c
JOIN Loan l ON l.customer_id = c.customer_id
JOIN Savings s ON s.customer_id = c.customer_id
GROUP BY c.customer_id, c.customer_name;
--  
--  OUTPUT.
--  +-------------+--------------------+--------------+-----------------+
--  | customer_id | customer_name      | loan_balance | savings_balance |
--  +-------------+--------------------+--------------+-----------------+
--  |           1 | Arjun Reddy        |       318000 |         80001.5 |
--  |           2 | Priya Sharma       |       306001 |   130001.703125 |
--  |           3 | Fatima Khan        |       162000 |          410000 |
--  |           4 | John Smith         |       120000 |           22000 |
--  |           5 | Suresh Kumar       |       222000 |          170000 |
--  |           6 | Linda Johnson      |       138000 |        190000.5 |
--  |           7 | Rajesh Iyer        |       274000 |          454000 |
--  |           8 | Maria Gonzalez     |        30000 |   38000.1015625 |
--  |           9 | Naveen Patil       |        40000 |  29000.19921875 |
--  |          10 | James Brown        |       130000 |          125000 |
--  |          11 | Ayesha Siddiqui    |        39000 |           64000 |
--  |          12 | Sunil Menon        |       424000 |   286000.796875 |
--  |          13 | Elizabeth Davis    |        27000 |            5600 |
--  |          14 | Vikram Singh       |       138000 |   122602.296875 |
--  |          15 | Jessica Lee        |       224000 |          210000 |
--  |          16 | Kavita Reddy       |        89000 |   78000.1171875 |
--  |          17 | Mohammed Ali       |        44000 |           35000 |
--  |          18 | Ravi Kumar         |        98000 |         82300.5 |
--  |          19 | Sandra Miller      |        35000 | 29000.099609375 |
--  |          20 | Lakshmi Narayan    |        94000 |           83000 |
--  |          21 | Emily Wilson       |        62000 |           51000 |
--  |          22 | Manish Gupta       |       116000 |  74000.69921875 |
--  |          23 | Chitra Subramanian |       106000 |           66500 |
--  |          24 | Tom Harris         |        61000 |           39000 |
--  |          25 | Anil Nair          |        76000 |           54000 |
--  +-------------+--------------------+--------------+-----------------+
--  25 rows in set (0.001 sec)
