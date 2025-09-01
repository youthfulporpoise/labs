CREATE DATABASE IF NOT EXISTS `23cs031-1-4`;
USE `23cs031-1-4`;

DROP TABLE IF EXISTS
  Books_Issue,
  Book,
  Member;

CREATE TABLE IF NOT EXISTS `Book` (
  accession_no            INTEGER       PRIMARY KEY,
  title                   VARCHAR(64),
  publisher               VARCHAR(48),
  year                    INTEGER,
  date_of_purchase        DATE,
  status                  VARCHAR(18)
);

CREATE TABLE IF NOT EXISTS `Member` (
  member_id               INTEGER       PRIMARY KEY,
  name                    VARCHAR(64),
  number_of_books_issued  INTEGER,
  max_limit               INTEGER
);

CREATE TABLE IF NOT EXISTS `Books_Issue` (
  accession_no            INTEGER,
  member_id               INTEGER,
  date_of_issue           DATE,
  FOREIGN KEY (accession_no) REFERENCES Book(accession_no),
  FOREIGN KEY (member_id) REFERENCES Member(member_id)
);

INSERT INTO Book (accession_no, title, publisher, year, date_of_purchase, status)
VALUES
  (   1, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   2, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   3, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   4, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   5, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   6, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   7, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   8, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (   9, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  10, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  11, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  12, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  13, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  14, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  15, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  16, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  17, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  18, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  19, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  20, 'The Discovery of India',      'Oxford University Press',       1946,   '2023-01-12',   'Available'),
  (  21, 'Midnight’s Children',         'Random House India',            1981,   '2023-02-15',   'Issued'),
  (  22, 'The Guide',                   'Penguin India',                 1958,   '2023-03-20',   'Available'),
  (  23, 'The White Tiger',             'HarperCollins',                 2008,   '2023-04-18',   'Available'),
  (  24, 'Train to Pakistan',           'Rupa Publications',             1956,   '2023-05-22',   'Issued'),
  (  25, 'Interpreter of Maladies',     'Houghton Mifflin',              1999,   '2023-06-15',   'Available'),
  (  26, 'The God of Small Things',     'HarperCollins India',           1997,   '2023-07-11',   'Available'),
  (  27, 'A Suitable Boy',              'Vintage',                       1993,   '2023-08-05',   'Issued'),
  (  28, 'Gitanjali',                   'Macmillan',                     1910,   '2023-09-15',   'Available'),
  (  29, 'The Shadow Lines',            'Penguin India',                 1988,   '2023-10-01',   'Available'),
  (  30, 'The Discovery of India',      'Oxford University Press',       1946,   '2024-01-13',   'Available'),
  (  31, 'Midnight’s Children',         'Random House India',            1981,   '2024-02-16',   'Available'),
  (  32, 'The White Tiger',             'HarperCollins',                 2008,   '2024-03-22',   'Issued'),
  (  33, 'Pride and Prejudice',         'Penguin Classics',              1813,   '2023-02-10',   'Available'),
  (  34, 'Jane Eyre',                   'Oxford University Press',       1847,   '2023-04-12',   'Issued'),
  (  35, 'Great Expectations',          'Chapman & Hall',                1861,   '2023-05-20',   'Available'),
  (  36, 'To Kill a Mockingbird',       'J.B. Lippincott & Co.',         1960,   '2023-06-30',   'Issued'),
  (  37, '1984',                        'Secker & Warburg',              1949,   '2023-07-25',   'Available'),
  (  38, 'Animal Farm',                 'Secker & Warburg',              1945,   '2023-08-15',   'Available'),
  (  39, 'Lord of the Flies',           'Faber and Faber',               1954,   '2023-09-10',   'Issued'),
  (  40, 'The Catcher in the Rye',      'Little, Brown and Company',     1951,   '2023-10-20',   'Available'),
  (  41, 'Wuthering Heights',           'Thomas Cautley Newby',          1847,   '2023-11-05',   'Available'),
  (  42, 'The Hobbit',                  'George Allen & Unwin',          1937,   '2023-12-01',   'Issued'),
  (  43, 'The God of Small Things',     'HarperCollins India',           1997,   '2024-01-10',   'Available'),
  (  44, 'The Guide',                   'Penguin India',                 1958,   '2024-02-14',   'Available'),
  (  45, 'Train to Pakistan',           'Rupa Publications',             1956,   '2024-03-18',   'Issued'),
  (  46, 'The English Patient',         'Knopf Canada',                  1992,   '2023-04-12',   'Available'),
  (  47, 'Cloudstreet',                 'Vintage Australia',             1991,   '2023-05-14',   'Issued'),
  (  48, 'The Bone People',             'Penguin New Zealand',           1984,   '2023-06-20',   'Available'),
  (  49, 'The Power of One',            'Faber and Faber',               1989,   '2023-07-19',   'Available'),
  (  50, 'The Discovery of India',      'Oxford University Press',       1946,   '2024-02-12',   'Issued'),
  (  51, 'Midnight’s Children',         'Random House India',            1981,   '2024-03-18',   'Available'),
  (  52, 'The Guide',                   'Penguin India',                 1958,   '2024-04-12',   'Available'),
  (  53, 'Pride and Prejudice',         'Penguin Classics',              1813,   '2024-05-10',   'Available'),
  (  54, 'Great Expectations',          'Chapman & Hall',                1861,   '2024-06-15',   'Issued'),
  (  55, 'Wuthering Heights',           'Thomas Cautley Newby',          1847,   '2024-07-10',   'Available'),
  (  56, 'The Hobbit',                  'George Allen & Unwin',          1937,   '2024-08-18',   'Available'),
  (  57, 'The God of Small Things',     'HarperCollins India',           1997,   '2024-09-25',   'Issued'),
  (  58, 'An Atlas of the Invisible',   'Penguin India',                 2020,   '2024-09-30',   'Available'),
  (  59, 'The Palace of Illusions',     'Westland',                      2008,   '2024-10-15',   'Available'),
  (  60, 'The Inheritance of Loss',     'Granta Books',                  2006,   '2024-11-05',   'Issued'),
  (  61, 'A Passage to India',          'Heinemann',                     1924,   '2024-11-20',   'Available'),
  (  62, 'Kim',                         'Macmillan',                     1901,   '2024-12-10',   'Available'),
  (  63, 'Kim',                         'Macmillan',                     1901,   '2025-01-01',   'Issued'),
  (  64, 'A Passage to India',          'Heinemann',                     1924,   '2025-01-15',   'Available'),
  (  65, 'The English Patient',         'Knopf Canada',                  1992,   '2025-02-05',   'Available'),
  (  66, 'Cloudstreet',                 'Vintage Australia',             1991,   '2025-03-08',   'Issued'),
  (  67, 'Train to Pakistan',           'Rupa Publications',             1956,   '2025-04-06',   'Available'),
  (  68, 'The White Tiger',             'HarperCollins',                 2008,   '2025-04-12',   'Issued'),
  (  69, 'An Atlas of the Invisible',   'Penguin India',                 2020,   '2025-05-20',   'Available'),
  (  70, 'The Power of One',            'Faber and Faber',               1989,   '2025-06-18',   'Available'),
  (  71, 'The Guide',                   'Penguin India',                 1958,   '2025-07-22',   'Issued'),
  (  72, 'Midnight’s Children',         'Random House India',            1981,   '2025-08-12',   'Available'),
  (  73, 'The Shadow Lines',            'Penguin India',                 1988,   '2025-09-15',   'Available'),
  (  74, 'Gitanjali',                   'Macmillan',                     1910,   '2025-10-19',   'Issued'),
  (  75, 'Kim',                         'Macmillan',                     1901,   '2025-11-20',   'Available'),
  (  76, 'The English Patient',         'Knopf Canada',                  1992,   '2025-12-15',   'Available'),
  (  77, 'Cloudstreet',                 'Vintage Australia',             1991,   '2026-01-10',   'Issued'),
  (  78, 'Train to Pakistan',           'Rupa Publications',             1956,   '2026-02-11',   'Available'),
  (  79, 'The God of Small Things',     'HarperCollins India',           1997,   '2026-03-05',   'Issued'),
  (  80, 'An Atlas of the Invisible',   'Penguin India',                 2020,   '2026-04-12',   'Available'),
  (  81, 'The Power of One',            'Faber and Faber',               1989,   '2026-05-22',   'Available'),
  (  82, 'The Guide',                   'Penguin India',                 1958,   '2026-06-15',   'Issued'),
  (  83, 'A Passage to India',          'Heinemann',                     1924,   '2026-07-10',   'Available'),
  (  84, 'Kim',                         'Macmillan',                     1901,   '2026-08-18',   'Available'),
  (  85, 'The Catcher in the Rye',      'Little, Brown and Company',     1951,   '2026-09-23',   'Issued'),
  (  86, '1984',                        'Secker & Warburg',              1949,   '2026-10-14',   'Available'),
  (  87, 'Animal Farm',                 'Secker & Warburg',              1945,   '2026-11-01',   'Available'),
  (  88, 'Lord of the Flies',           'Faber and Faber',               1954,   '2026-12-12',   'Issued'),
  (  89, 'The Hobbit',                  'George Allen & Unwin',          1937,   '2027-01-09',   'Available'),
  (  90, 'Great Expectations',          'Chapman & Hall',                1861,   '2027-02-06',   'Available'),
  (  91, 'Wuthering Heights',           'Thomas Cautley Newby',          1847,   '2027-03-03',   'Available'),
  (  92, 'Midnight’s Children',         'Random House India',            1981,   '2027-04-04',   'Issued'),
  (  93, 'The White Tiger',             'HarperCollins',                 2008,   '2027-05-20',   'Available'),
  (  94, 'The Guide',                   'Penguin India',                 1958,   '2027-06-15',   'Issued');

INSERT INTO Member (member_id, name, number_of_books_issued, max_limit)
VALUES
  (  1, 'Arun Ramesh',              2,     5),
  (  2, 'Meena Nair',               0,     7),
  (  3, 'Vikram Singh',             1,     6),
  (  4, 'Priya Krishnan',           3,     7),
  (  5, 'Anil Patel',               1,     5),
  (  6, 'Kavitha Raj',              0,     6),
  (  7, 'Suresh Kumar',             2,     7),
  (  8, 'Shreya Iyer',              1,     5),
  (  9, 'Naveen Menon',             0,     6),
  ( 10, 'Lakshmi Subramanian',      3,     7),
  ( 11, 'Rachel Smith',             0,     5),
  ( 12, 'Derek Johnson',            1,     6),
  ( 13, 'Fatima Ali',               0,     7),
  ( 14, 'James O’Connor',           2,     6),
  ( 15, 'Zara Qureshi',             1,     5),
  ( 16, 'John Williams',            0,     6),
  ( 17, 'Latha Krishnapillai',      2,     7),
  ( 18, 'Nikhil Varma',             1,     5),
  ( 19, 'Sanjay Reddy',             3,     6),
  ( 20, 'Elizabeth Brown',          0,     5);

INSERT INTO Books_Issue (accession_no, member_id, date_of_issue)
VALUES
-- New entries issued within last 15 days (new unique books to members 1 to 7)
( 21,  1, '2025-08-31'),
( 22,  2, '2025-08-30'),
( 23,  3, '2025-08-29'),
( 24,  4, '2025-08-28'),
( 25,  5, '2025-08-27'),
( 26,  6, '2025-08-26'),
( 27,  7, '2025-08-25'),

-- Book issued to every member: multiple copies, accession_no 1 to 20 issued to members 1 to 20 respectively
(  1,  1, '2025-02-01'),
(  2,  2, '2025-02-02'),
(  3,  3, '2025-02-03'),
(  4,  4, '2025-02-04'),
(  5,  5, '2025-02-05'),
(  6,  6, '2025-02-06'),
(  7,  7, '2025-02-07'),
(  8,  8, '2025-02-08'),
(  9,  9, '2025-02-09'),
( 10, 10, '2025-02-10'),
( 11, 11, '2025-02-11'),
( 12, 12, '2025-02-12'),
( 13, 13, '2025-02-13'),
( 14, 14, '2025-02-14'),
( 15, 15, '2025-08-25'),
( 16, 16, '2025-08-26'),
( 17, 17, '2025-08-27'),
( 18, 18, '2025-08-28'),
( 19, 19, '2025-08-29'),
( 20, 20, '2025-08-30');

UPDATE Book
SET status = 'Issued'
WHERE accession_no IN (SELECT DISTINCT accession_no FROM Books_Issue);

--  (a) List all the books that are due from students.  A book is considered due
--  if it was issued more than 15 days ago and has not been returned yet.
--
--  SELECT b.accession_no, b.title, b.status, bi.date_of_issue
--  FROM Book b
--  JOIN Books_Issue bi ON bi.accession_no = b.accession_no
--  WHERE
--    b.status = 'Issued'
--    AND
--    bi.date_of_issue + INTERVAL 15 DAY >= CURRENT_DATE;
--  
--  OUTPUT.
--  +--------------+-------------------------+--------+---------------+
--  | accession_no | title                   | status | date_of_issue |
--  +--------------+-------------------------+--------+---------------+
--  |           21 | Midnight’s Children     | Issued | 2025-08-31    |
--  |           22 | The Guide               | Issued | 2025-08-30    |
--  |           23 | The White Tiger         | Issued | 2025-08-29    |
--  |           24 | Train to Pakistan       | Issued | 2025-08-28    |
--  |           25 | Interpreter of Maladies | Issued | 2025-08-27    |
--  |           26 | The God of Small Things | Issued | 2025-08-26    |
--  |           27 | A Suitable Boy          | Issued | 2025-08-25    |
--  |           15 | The Discovery of India  | Issued | 2025-08-25    |
--  |           16 | The Discovery of India  | Issued | 2025-08-26    |
--  |           17 | The Discovery of India  | Issued | 2025-08-27    |
--  |           18 | The Discovery of India  | Issued | 2025-08-28    |
--  |           19 | The Discovery of India  | Issued | 2025-08-29    |
--  |           20 | The Discovery of India  | Issued | 2025-08-30    |
--  +--------------+-------------------------+--------+---------------+
--  13 rows in set (0.000 sec)


--  (b) List all members who cannot be issued any more books.
--
--  SELECT m.member_id, m.name
--  FROM Member m
--  WHERE m.number_of_books_issued >= m.max_limit;
--  
--  OUTPUT.
--  Empty set (0.000 sec)

--  (c) List the details of books:
--        - that has been issued to maximum number of member;
--        - that has been issued to minimum number of member.
--
--  DROP VIEW IF EXISTS Issue;
--  CREATE VIEW IF NOT EXISTS Issue
--  AS
--    SELECT b.title, COUNT(b.accession_no) AS issue_count
--    FROM Book b
--    JOIN Books_Issue bi ON bi.accession_no = b.accession_no
--    GROUP BY b.title;
--  
--  SELECT DISTINCT b.title, i.issue_count
--  FROM Book b
--  JOIN Issue i ON i.title = b.title
--  JOIN (
--          SELECT MAX(issue_count) AS max
--          FROM Issue
--       ) AS mi ON mi.max = i.issue_count;
--  
--  SELECT DISTINCT b.title, i.issue_count
--  FROM Book b
--  JOIN Issue i ON i.title = b.title
--  JOIN (
--          SELECT MIN(issue_count) AS min
--          FROM Issue
--       ) AS mi ON mi.min = i.issue_count;
--  
--  OUTPUT.
--  +------------------------+-------------+
--  | title                  | issue_count |
--  +------------------------+-------------+
--  | The Discovery of India |          20 |
--  +------------------------+-------------+
--  1 row in set (0.002 sec)
--  
--  +-------------------------+-------------+
--  | title                   | issue_count |
--  +-------------------------+-------------+
--  | Midnight’s Children     |           1 |
--  | The Guide               |           1 |
--  | The White Tiger         |           1 |
--  | Train to Pakistan       |           1 |
--  | Interpreter of Maladies |           1 |
--  | The God of Small Things |           1 |
--  | A Suitable Boy          |           1 |
--  +-------------------------+-------------+
--  7 rows in set (0.001 sec)

--  (d) List the details of books:
--        - that has been issued to every member;
--        - that has not been issued to any member.
--
--  DROP VIEW IF EXISTS Member_Issue;
--  CREATE VIEW IF NOT EXISTS Member_Issue
--  AS
--    SELECT b.title, COUNT(bi.member_id) AS member_count
--    FROM Books_Issue bi
--    JOIN Book b ON b.accession_no = bi.accession_no
--    GROUP BY b.title;
--  
--  SELECT DISTINCT b.title, b.publisher, b.year
--  FROM Book b
--  JOIN Member_Issue mi ON mi.title = b.title
--  JOIN
--    ( SELECT COUNT(member_id) AS total_members FROM Member )
--    AS tm ON tm.total_members = mi.member_count;
--  
--  SELECT DISTINCT b.title, b.publisher, b.year
--  FROM Book b
--  WHERE b.title NOT IN
--    ( SELECT b.title FROM Book b
--      JOIN Books_Issue bi ON b.accession_no = bi.accession_no
--    );
--  
--  OUTPUT.
--  +------------------------+-------------------------+------+
--  | title                  | publisher               | year |
--  +------------------------+-------------------------+------+
--  | The Discovery of India | Oxford University Press | 1946 |
--  +------------------------+-------------------------+------+
--  1 row in set (0.001 sec)
--  
--  +---------------------------+---------------------------+------+
--  | title                     | publisher                 | year |
--  +---------------------------+---------------------------+------+
--  | Gitanjali                 | Macmillan                 | 1910 |
--  | The Shadow Lines          | Penguin India             | 1988 |
--  | Pride and Prejudice       | Penguin Classics          | 1813 |
--  | Jane Eyre                 | Oxford University Press   | 1847 |
--  | Great Expectations        | Chapman & Hall            | 1861 |
--  | To Kill a Mockingbird     | J.B. Lippincott & Co.     | 1960 |
--  | 1984                      | Secker & Warburg          | 1949 |
--  | Animal Farm               | Secker & Warburg          | 1945 |
--  | Lord of the Flies         | Faber and Faber           | 1954 |
--  | The Catcher in the Rye    | Little, Brown and Company | 1951 |
--  | Wuthering Heights         | Thomas Cautley Newby      | 1847 |
--  | The Hobbit                | George Allen & Unwin      | 1937 |
--  | The English Patient       | Knopf Canada              | 1992 |
--  | Cloudstreet               | Vintage Australia         | 1991 |
--  | The Bone People           | Penguin New Zealand       | 1984 |
--  | The Power of One          | Faber and Faber           | 1989 |
--  | An Atlas of the Invisible | Penguin India             | 2020 |
--  | The Palace of Illusions   | Westland                  | 2008 |
--  | The Inheritance of Loss   | Granta Books              | 2006 |
--  | A Passage to India        | Heinemann                 | 1924 |
--  | Kim                       | Macmillan                 | 1901 |
--  +---------------------------+---------------------------+------+
--  21 rows in set (0.001 sec)
