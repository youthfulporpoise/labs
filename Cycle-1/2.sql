CREATE DATABASE IF NOT EXISTS `23cs031-1-2`;
USE `23cs031-1-2`;

DROP TABLE IF EXISTS Book;
CREATE TABLE Book (
    accession_no        INTEGER         PRIMARY KEY,
    title               VARCHAR(64),
    publisher           VARCHAR(64),
    author              VARCHAR(64),
    date_of_purchase    DATE,
    date_of_publishing  DATE,
    status              VARCHAR(36)
);

INSERT INTO Book VALUES
(1,     'The God of Small Things',      'Random House',         'Arundhati Roy',                '2025-05-15',        '1997-04-01',        'present in the library'),
(2,     'Midnight''s Children',         'Vintage',              'Salman Rushdie',               '2022-03-20',        '1981-04-01',        'issued'),
(3,     'Randamoozham',                 'D.C. Books',           'M. T. Vasudevan Nair',         '2021-05-10',        '1984-01-01',        'present in the library'),
(4,     'Khasakkinte Ithihasam',        'D.C. Books',           'O. V. Vijayan',                '2020-07-22',        '1969-01-01',        'present in the library'),
(5,     'Indulekha',                    'D.C. Books',           'O. Chandu Menon',              '2019-09-05',        '1889-01-01',        'cannot be issued'),
(6,     'The White Tiger',              'Atlantic Books',       'Aravind Adiga',                '2023-02-18',        '2008-01-01',        'issued'),
(7,     'The Inheritance of Loss',      'Hamish Hamilton',      'Kiran Desai',                  '2022-04-25',        '2006-05-01',        'present in the library'),
(8,     'A Suitable Boy',               'Penguin Books',        'Vikram Seth',                  '2025-06-12',        '1993-01-01',        'present in the library'),
(9,     'The Palace of Illusions',      'Anchor Books',         'Chitra Banerjee Divakaruni',   '2020-08-30',        '2008-02-01',        'present in the library'),
(10,    'Things Fall Apart',            'Heinemann',            'Chinua Achebe',                '2023-03-01',        '1958-01-01',        'issued'),
(11,    'Randamoozham',                 'D.C. Books',           'M. T. Vasudevan Nair',         '2021-05-10',        '1984-01-01',        'reference'),
(12,    'The God of Small Things',      'Random House',         'Arundhati Roy',                '2023-01-15',        '1997-04-01',        'present in the library'),
(13,    'Midnight''s Children',         'Vintage',              'Salman Rushdie',               '2022-03-20',        '1981-04-01',        'issued'),
(14,    'Khasakkinte Ithihasam',        'D.C. Books',           'O. V. Vijayan',                '2020-07-22',        '1969-01-01',        'present in the library'),
(15,    'Indulekha',                    'D.C. Books',           'O. Chandu Menon',              '2023-04-05',        '1889-01-01',        'cannot be issued'),
(16,    'The White Tiger',              'Atlantic Books',       'Aravind Adiga',                '2023-02-18',        '2008-01-01',        'present in the library'),
(17,    'A Suitable Boy',               'Penguin Books',        'Vikram Seth',                  '2023-05-20',        '1993-01-01',        'present in the library'),
(18,    'The Inheritance of Loss',      'Hamish Hamilton',      'Kiran Desai',                  '2022-04-25',        '2006-05-01',        'issued'),
(19,    'The Palace of Illusions',      'Anchor Books',         'Chitra Banerjee Divakaruni',   '2020-08-30',        '2008-02-01',        'present in the library'),
(20,    'Norwegian Wood',               'Kodansha',             'Haruki Murakami',              '2023-06-01',        '1987-09-04',        'present in the library'),
(21,    'The God of Small Things',      'Random House',         'Arundhati Roy',                '2023-07-10',        '1997-04-01',        'present in the library'),
(22,    'Midnight''s Children',         'Vintage',              'Salman Rushdie',               '2022-03-20',        '1981-04-01',        'issued'),
(23,    'Randamoozham',                 'D.C. Books',           'M. T. Vasudevan Nair',         '2021-05-10',        '1984-01-01',        'present in the library'),
(24,    'Khasakkinte Ithihasam',        'D.C. Books',           'O. V. Vijayan',                '2020-07-22',        '1969-01-01',        'present in the library'),
(25,    'Indulekha',                    'D.C. Books',           'O. Chandu Menon',              '2023-04-05',        '1889-01-01',        'cannot be issued'),
(26,    'The White Tiger',              'Atlantic Books',       'Aravind Adiga',                '2025-04-18',        '2008-01-01',        'present in the library'),
(27,    'The Inheritance of Loss',      'Hamish Hamilton',      'Kiran Desai',                  '2022-04-25',        '2006-05-01',        'issued'),
(28,    'A Suitable Boy',               'Penguin Books',        'Vikram Seth',                  '2023-05-20',        '1993-01-01',        'present in the library'),
(29,    'The Palace of Illusions',      'Anchor Books',         'Chitra Banerjee Divakaruni',   '2020-08-30',        '2008-02-01',        'present in the library'),
(30,    'Randamoozham',                 'D.C. Books',           'M. T. Vasudevan Nair',         '2021-05-10',        '1984-01-01',        'present in the library'),
(31,    'The God of Small Things',      'Random House',         'Arundhati Roy',                '2023-07-10',        '1997-04-01',        'present in the library'),
(32,    'Midnight''s Children',         'Vintage',              'Salman Rushdie',               '2022-03-20',        '1981-04-01',        'issued'),
(33,    'The White Tiger',              'Atlantic Books',       'Aravind Adiga',                '2023-02-18',        '2008-01-01',        'present in the library'),
(34,    'Khasakkinte Ithihasam',        'D.C. Books',           'O. V. Vijayan',                '2020-07-22',        '1969-01-01',        'present in the library'),
(35,    'The Inheritance of Loss',      'Hamish Hamilton',      'Kiran Desai',                  '2022-04-25',        '2006-05-01',        'issued'),
(36,    'Indulekha',                    'D.C. Books',           'O. Chandu Menon',              '2023-04-05',        '1889-01-01',        'cannot be issued'),
(37,    'Chemmeen',                     'National Book Stall',  'Thakazhi Sivasankara Pillai',  '2024-01-10',        '1956-01-01',        'present in the library'),
(38,    'Life of Pi',                   'Canongate Books',      'Yann Martel',                  '2024-02-20',        '2001-09-01',        'issued'),
(39,    'Train to Pakistan',            'Chatto & Windus',      'Khushwant Singh',              '2023-03-15',        '1956-01-01',        'present in the library'),
(40,    'Balyakalasakhi',               'D.C. Books',           'Vaikom Muhammad Basheer',      '2022-04-18',        '1944-01-01',        'present in the library'),
(41,    'Goat Days',                    'Penguin Books',        'Benyamin',                     '2023-05-25',        '2008-01-01',        'present in the library'),
(42,    'Randamoozham',                 'D.C. Books',           'M. T. Vasudevan Nair',         '2024-06-05',        '1984-01-01',        'reference'),
(43,    'The God of Small Things',      'Random House',         'Arundhati Roy',                '2023-07-10',        '1997-04-01',        'present in the library'),
(44,    'Midnight''s Children',         'Vintage',              'Salman Rushdie',               '2022-03-20',        '1981-04-01',        'issued'),
(45,    'Khasakkinte Ithihasam',        'D.C. Books',           'O. V. Vijayan',                '2020-07-22',        '1969-01-01',        'present in the library'),
(46,    'The White Tiger',              'Atlantic Books',       'Aravind Adiga',                '2023-02-18',        '2008-01-01',        'present in the library'),
(47,    'The Inheritance of Loss',      'Hamish Hamilton',      'Kiran Desai',                  '2022-04-25',        '2006-05-01',        'issued'),
(48,    'A Suitable Boy',               'Penguin Books',        'Vikram Seth',                  '2023-05-20',        '1993-01-01',        'present in the library'),
(49,    'The Palace of Illusions',      'Anchor Books',         'Chitra Banerjee Divakaruni',   '2020-08-30',        '2008-02-01',        'present in the library'),
(50,    'Randamoozham',                 'D.C. Books',           'M. T. Vasudevan Nair',         '2024-06-05',        '1984-01-01',        'reference');

--  (a) List the total number of copies of each book in the library.
SELECT title, COUNT(accession_no) AS copies
FROM Book
GROUP BY title;
--  
--  OUTPUT.
--  +-------------------------+--------+
--  | title                   | copies |
--  +-------------------------+--------+
--  | A Suitable Boy          |      4 |
--  | Balyakalasakhi          |      1 |
--  | Chemmeen                |      1 |
--  | Goat Days               |      1 |
--  | Indulekha               |      4 |
--  | Khasakkinte Ithihasam   |      5 |
--  | Life of Pi              |      1 |
--  | Midnight's Children     |      5 |
--  | Norwegian Wood          |      1 |
--  | Randamoozham            |      6 |
--  | The God of Small Things |      5 |
--  | The Inheritance of Loss |      5 |
--  | The Palace of Illusions |      4 |
--  | The White Tiger         |      5 |
--  | Things Fall Apart       |      1 |
--  | Train to Pakistan       |      1 |
--  +-------------------------+--------+
--  16 rows in set (0.001 sec)

--  (b) List the total number of reference copies for each book in the library.
SELECT title, COUNT(accession_no) AS copies, status
FROM Book
WHERE status = "reference"
GROUP BY title;
--  
--  OUTPUT.
--  +--------------+--------+-----------+
--  | title        | copies | status    |
--  +--------------+--------+-----------+
--  | Randamoozham |      3 | reference |
--  +--------------+--------+-----------+
--  1 row in set (0.001 sec)

--  (c) For each book in the library, obtain:
--      - the total number of issued copies;
--      - the number of copies currently available in the libray;
--      - the number of reference copies.
SELECT title, status, COUNT(accession_no) AS copies
FROM Book
GROUP BY status, title
ORDER BY title ASC, status ASC;
--
--  OUTPUT.
--  +-------------------------+------------------------+--------+
--  | title                   | status                 | copies |
--  +-------------------------+------------------------+--------+
--  | A Suitable Boy          | present in the library |      4 |
--  | Balyakalasakhi          | present in the library |      1 |
--  | Chemmeen                | present in the library |      1 |
--  | Goat Days               | present in the library |      1 |
--  | Indulekha               | cannot be issued       |      4 |
--  | Khasakkinte Ithihasam   | present in the library |      5 |
--  | Life of Pi              | issued                 |      1 |
--  | Midnight's Children     | issued                 |      5 |
--  | Norwegian Wood          | present in the library |      1 |
--  | Randamoozham            | present in the library |      3 |
--  | Randamoozham            | reference              |      3 |
--  | The God of Small Things | present in the library |      5 |
--  | The Inheritance of Loss | issued                 |      4 |
--  | The Inheritance of Loss | present in the library |      1 |
--  | The Palace of Illusions | present in the library |      4 |
--  | The White Tiger         | issued                 |      1 |
--  | The White Tiger         | present in the library |      4 |
--  | Things Fall Apart       | issued                 |      1 |
--  | Train to Pakistan       | present in the library |      1 |
--  +-------------------------+------------------------+--------+
--  19 rows in set (0.004 sec)

--  (d) List the details of all books whose status is "cannot be issued"
--  publisherwise.
SELECT accession_no, title, publisher, status
FROM Book
WHERE status = "cannot be issued"
ORDER BY publisher ASC;
--  
--  OUTPUT.
--  +--------------+-----------+------------+------------------+
--  | accession_no | title     | publisher  | status           |
--  +--------------+-----------+------------+------------------+
--  |            5 | Indulekha | D.C. Books | cannot be issued |
--  |           15 | Indulekha | D.C. Books | cannot be issued |
--  |           25 | Indulekha | D.C. Books | cannot be issued |
--  |           36 | Indulekha | D.C. Books | cannot be issued |
--  +--------------+-----------+------------+------------------+
--  4 rows in set (0.004 sec)

--  (e) List the details of all books that are categorized as *new arrivals*
--  (i.e. books purchased within the last 6 months).
SELECT accession_no, title, author, date_of_purchase
FROM Book
WHERE date_of_purchase + INTERVAL 6 MONTH > CURRENT_DATE;
--  
--  OUTPUT.
--  +--------------+-------------------------+---------------+------------------+
--  | accession_no | title                   | author        | date_of_purchase |
--  +--------------+-------------------------+---------------+------------------+
--  |            1 | The God of Small Things | Arundhati Roy | 2025-05-15       |
--  |            8 | A Suitable Boy          | Vikram Seth   | 2025-06-12       |
--  |           26 | The White Tiger         | Aravind Adiga | 2025-04-18       |
--  +--------------+-------------------------+---------------+------------------+
--  3 rows in set (0.001 sec)

--  (f) List the details of each *famous book*.  A book is considered famous if:
--          (i) it was purchased within 20 year of its publishing;
--          (ii) it has more than 4 total copies in the library.
DROP VIEW IF EXISTS Copies;
CREATE VIEW Copies AS
    SELECT title, COUNT(accession_no) AS copies
    FROM Book
    GROUP BY title;

SELECT DISTINCT b.title, b.author, b.date_of_publishing, c.copies
FROM Book b
JOIN Copies c ON b.title = c.title
WHERE
    b.date_of_publishing + INTERVAL 20 YEAR > CURRENT_DATE 
    AND
    c.copies >= 4;
--  
--  OUTPUT.
--  +-------------------------+----------------------------+--------------------+--------+
--  | title                   | author                     | date_of_publishing | copies |
--  +-------------------------+----------------------------+--------------------+--------+
--  | The White Tiger         | Aravind Adiga              | 2008-01-01         |      5 |
--  | The Inheritance of Loss | Kiran Desai                | 2006-05-01         |      5 |
--  | The Palace of Illusions | Chitra Banerjee Divakaruni | 2008-02-01         |      4 |
--  +-------------------------+----------------------------+--------------------+--------+
--  3 rows in set (0.001 sec)
