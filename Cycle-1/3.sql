CREATE DATABASE IF NOT EXISTS `23cs031-1-3`;
USE `23cs031-1-3`;

DROP TABLE IF EXISTS
    Enrollment,
    Student,
    Course;

CREATE TABLE IF NOT EXISTS `Student` (
    roll_no         INTEGER         PRIMARY KEY,
    name            VARCHAR(64),
    date_of_birth   DATE
);

CREATE TABLE IF NOT EXISTS `Course` (
    course_id       INTEGER         PRIMARY KEY,
    name            VARCHAR(48),
    fee             FLOAT,
    duration        INTEGER
);

CREATE TABLE IF NOT EXISTS `Enrollment` (
    enrollment_id       INTEGER     PRIMARY KEY,
    roll_no             INTEGER,
    course_id           INTEGER,
    FOREIGN KEY (roll_no) REFERENCES Student(roll_no),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

INSERT INTO Student (roll_no, name, date_of_birth) VALUES
    (1,     'Aarav Sharma',     '2002-03-15'),
    (2,     'Meera Iyer',       '2001-11-22'),
    (3,     'Rohan Patel',      '2003-01-19'),
    (4,     'Fatima Khan',      '2002-07-28'),
    (5,     'Siddharth Nair',   '2000-12-05'),
    (6,     'Leela Thomas',     '2001-05-17'),
    (7,     'Ananya Gupta',     '2003-09-13'),
    (8,     'Vikram Desai',     '2002-06-03'),
    (9,     'Priya Menon',      '2001-02-14'),
    (10,    'Kabir Chandra',    '2000-08-09'),
    (11,    'Aditya Reddy',     '2002-10-01'),
    (12,    'Clara Johansson',  '2001-04-12'),
    (13,    'Liam O’Connor',    '2002-03-21'),
    (14,    'Sophia Martinez',  '2000-11-09'),
    (15,    'William Smith',    '2001-07-25'),
    (16,    'Akira Tanaka',     '2003-01-05'),
    (17,    'Jinwoo Park',      '2002-08-18'),
    (18,    'Nina Petrova',     '2001-09-30'),
    (19,    'Ahmed Hassan',     '2000-06-10'),
    (20,    'David Cohen',      '2001-12-22'),
    (21,    'Omar Al-Sayed',    '2002-03-04'),
    (22,    'Elena Rossi',      '2001-05-28'),
    (23,    'Carlos Silva',     '2000-02-09'),
    (24,    'Lucas Müller',     '2001-10-14'),
    (25,    'Emma Dupont',      '2002-07-01'),
    (26,    'Isabella Costa',   '2000-03-26'),
    (27,    'Noah Johnson',     '2001-01-15'),
    (28,    'Yuki Nakamura',    '2002-09-07'),
    (29,    'Rajiv Bansal',     '2000-05-11'),
    (30,    'Divya Pillai',     '2003-02-16'),
    (31,    'Zara Qureshi',     '2001-04-07'),
    (32,    'Krishna Kulkarni', '2002-12-19');

INSERT INTO Course (course_id, name, fee, duration)
VALUES
    (101,   'B.Tech. Computer Science',              85000.00,  48),
    (102,   'B.Tech. Mechanical Engineering',        82000.00,  48),
    (103,   'B.Tech. Civil Engineering',             80000.00,  48),
    (104,   'B.Tech. Electrical Engineering',        83000.00,  48),
    (105,   'B.Tech. Electronics & Communication',   84000.00,  48),
    (106,   'B.Tech. Information Technology',        86000.00,  48),
    (107,   'B.Sc. Mathematics',                     40000.00,  36),
    (108,   'B.Sc. Physics',                         42000.00,  36),
    (109,   'B.Sc. Chemistry',                       42000.00,  36),
    (110,   'B.Sc. Biology',                         41000.00,  36),
    (111,   'B.Sc. Computer Science',                45000.00,  36),
    (112,   'B.Sc. Statistics',                      43000.00,  36),
    (113,   'B.Com. General',                        38000.00,  36),
    (114,   'B.Com. Accounting & Finance',           40000.00,  36),
    (115,   'B.Com. Banking & Insurance',            39000.00,  36),
    (116,   'B.Com. Business Analytics',             42000.00,  36),
    (117,   'B.FSc. Fisheries Science',              45000.00,  36),
    (118,   'B.Pharm. Pharmacy',                     60000.00,  48),
    (119,   'BBA Management',                        48000.00,  36),
    (120,   'LLB Law',                               65000.00,  36),
    (121,   'M.Tech. Computer Science',              95000.00,  24),
    (122,   'M.Tech. Data Science',                 100000.00,  24),
    (123,   'M.Tech. Structural Engineering',        92000.00,  24),
    (124,   'M.Tech. VLSI Design',                   94000.00,  24),
    (125,   'M.Sc. Mathematics',                     50000.00,  24),
    (126,   'M.Sc. Physics',                         52000.00,  24),
    (127,   'M.Sc. Chemistry',                       52000.00,  24),
    (128,   'M.Sc. Computer Science',                60000.00,  24),
    (129,   'MBA Finance',                           98000.00,  24),
    (130,   'MBA Marketing',                         97000.00,  24),
    (131,   'MBA Human Resources',                   96000.00,  24),
    (132,   'MBA International Business',           105000.00,  24);

INSERT INTO Enrollment (enrollment_id, roll_no, course_id)
VALUES
    (1,     1,      101),
    (2,     2,      107),
    (3,     3,      113),
    (4,     4,      119),
    (5,     5,      102),
    (6,     6,      108),
    (7,     7,      114),
    (8,     8,      120),
    (9,     9,      109),
    (10,    10,     103),
    (11,    11,     118),
    (12,    12,     119),
    (13,    13,     115),
    (14,    14,     110),
    (15,    15,     104),
    (16,    16,     111),
    (17,    17,     119),
    (18,    18,     120),
    (19,    19,     112),
    (20,    20,     116),
    (21,    21,     117),
    (22,    22,     105),
    (23,    23,     106),
    (24,    24,     110),
    (25,     1,     121),
    (26,     2,     125),
    (27,     3,     129),
    (28,    10,     122),
    (29,    12,     132),
    (30,    16,     128),
    (31,    29,     130),
    (32,    32,     129);

INSERT INTO Student (roll_no, name, date_of_birth)
VALUES
    (33,    'Alex Global',  '2001-01-01');

INSERT INTO Enrollment (enrollment_id, roll_no, course_id)
VALUES
    (57,    33,     101),
    (58,    33,     102),
    (59,    33,     103),
    (60,    33,     104),
    (61,    33,     105),
    (62,    33,     106),
    (63,    33,     107),
    (64,    33,     108),
    (65,    33,     109),
    (66,    33,     110),
    (67,    33,     111),
    (68,    33,     112),
    (69,    33,     113),
    (70,    33,     114),
    (71,    33,     115),
    (72,    33,     116),
    (73,    33,     117),
    (74,    33,     118),
    (75,    33,     119),
    (76,    33,     120),
    (77,    33,     121),
    (78,    33,     122),
    (79,    33,     123),
    (80,    33,     124),
    (81,    33,     125),
    (82,    33,     126),
    (83,    33,     127),
    (84,    33,     128),
    (85,    33,     129),
    (86,    33,     130),
    (87,    33,     131),
    (88,    33,     132);

--  (a) List the names of all students are greater than 18 years of age and have
--  opted for a B.Tech. course.
SELECT s.name, s.date_of_birth, c.name
FROM Student s
JOIN Enrollment e ON s.roll_no = e.roll_no
JOIN Course c ON c.course_id = e.course_id
WHERE
    s.date_of_birth + INTERVAL 18 YEAR <= CURRENT_DATE
    AND
    c.name LIKE 'B.Tech.%';
--  
--  OUTPUT.
--  +----------------+---------------+-------------------------------------+
--  | name           | date_of_birth | name                                |
--  +----------------+---------------+-------------------------------------+
--  | Aarav Sharma   | 2002-03-15    | B.Tech. Computer Science            |
--  | Meera Iyer     | 2001-11-22    | B.Tech. Mechanical Engineering      |
--  | Rohan Patel    | 2003-01-19    | B.Tech. Civil Engineering           |
--  | Fatima Khan    | 2002-07-28    | B.Tech. Electrical Engineering      |
--  | Siddharth Nair | 2000-12-05    | B.Tech. Electronics & Communication |
--  | Leela Thomas   | 2001-05-17    | B.Tech. Information Technology      |
--  +----------------+---------------+-------------------------------------+
--  6 rows in set (0.001 sec)

--  (b) List the details of those courses the fee whereof is greater than that
--  of a B.Tech. course.
SELECT c.course_id, c.name, c.fee
FROM Course c
JOIN (
       SELECT MAX(fee) AS btech_fee
       FROM Course
       WHERE name LIKE 'B.Tech.%'
     ) AS b
WHERE c.fee > b.btech_fee;
--  
--  OUTPUT.
--  +-----------+--------------------------------+--------+
--  | course_id | name                           | fee    |
--  +-----------+--------------------------------+--------+
--  |       121 | M.Tech. Computer Science       |  95000 |
--  |       122 | M.Tech. Data Science           | 100000 |
--  |       123 | M.Tech. Structural Engineering |  92000 |
--  |       124 | M.Tech. VLSI Design            |  94000 |
--  |       129 | MBA Finance                    |  98000 |
--  |       130 | MBA Marketing                  |  97000 |
--  |       131 | MBA Human Resources            |  96000 |
--  |       132 | MBA International Business     | 105000 |
--  +-----------+--------------------------------+--------+
--  8 rows in set (0.001 sec)

--  (c) List the details of the students who have opted for more than 2 courses.
SELECT s.roll_no, s.name, COUNT(e.enrollment_id) AS enrollments
FROM Student s
JOIN Enrollment e ON s.roll_no = e.roll_no
JOIN Course c ON c.course_id = e.course_id
GROUP BY e.roll_no
HAVING enrollments > 1;
--  
--  OUTPUT.
--  +---------+-----------------+-------------+
--  | roll_no | name            | enrollments |
--  +---------+-----------------+-------------+
--  |       1 | Aarav Sharma    |           2 |
--  |       2 | Meera Iyer      |           2 |
--  |       3 | Rohan Patel     |           2 |
--  |      10 | Kabir Chandra   |           2 |
--  |      12 | Clara Johansson |           2 |
--  |      16 | Akira Tanaka    |           2 |
--  +---------+-----------------+-------------+
--  6 rows in set (0.002 sec)

-- (d) List the details (viz. name; fee; duration) of:
--      - the courses that have been opted by maximum number of students;
--      - the courses that have been opted by minimum number of students.
DROP VIEW IF EXISTS StudentsEnrolled;
CREATE VIEW IF NOT EXISTS StudentsEnrolled AS
    SELECT course_id, COUNT(enrollment_id) AS enroll_count
    FROM Enrollment
    GROUP BY course_id;

SELECT c.name, c.fee, c.duration, se.enroll_count
FROM Course c
JOIN StudentsEnrolled se ON se.course_id = c.course_id
JOIN (
        SELECT MAX(enroll_count) AS max
        FROM StudentsEnrolled
     ) mse ON mse.max = se.enroll_count;
--  
--  OUTPUT.
--  +----------------+-------+----------+--------------+
--  | name           | fee   | duration | enroll_count |
--  +----------------+-------+----------+--------------+
--  | BBA Management | 48000 |       36 |            3 |
--  +----------------+-------+----------+--------------+
--  1 row in set (0.002 sec)

--  (e) List the details of the student(s) who have opted every course.
--  DROP VIEW IF EXISTS CoursesEnrolled;
CREATE VIEW IF NOT EXISTS CoursesEnrolled AS
    SELECT roll_no, COUNT(DISTINCT course_id) AS enroll_count
    FROM Enrollment
    GROUP BY roll_no;

SELECT s.roll_no, s.name
FROM Student s
JOIN CoursesEnrolled ce ON ce.roll_no = s.roll_no
JOIN (
        SELECT COUNT(course_id) AS total_course_count
        FROM Course
     ) AS tcc ON ce.enroll_count = tcc.total_course_count;
--  
--  OUTPUT.
--  +---------+-------------+
--  | roll_no | name        |
--  +---------+-------------+
--  |      33 | Alex Global |
--  +---------+-------------+
--  1 row in set (0.001 sec)
