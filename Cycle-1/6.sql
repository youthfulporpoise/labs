DROP DATABASE IF EXISTS `23cs031-6`;
CREATE DATABASE IF NOT EXISTS `23cs031-6`;

USE `23cs031-6`;

DROP TABLE IF EXISTS
  booking,
  food_order,
  companion,
  room,
  resident,
  room,
  food,
  employee;


CREATE TABLE IF NOT EXISTS `employee` (
  employee_id           INTEGER           PRIMARY KEY,
  name                  VARCHAR(64),
  address               VARCHAR(64),
  aadhar                BIGINT            UNIQUE,
  mobile_no             BIGINT            UNIQUE,
  email_id              VARCHAR(64)       UNIQUE,
  joining_date          DATE,
  salary                FLOAT
);

CREATE TABLE IF NOT EXISTS `resident` (
  resident_id           INTEGER           PRIMARY KEY,
  name                  VARCHAR(64),
  address               VARCHAR(64),
  aadhar                BIGINT            UNIQUE,
  gender                VARCHAR(1),
  age                   INTEGER,
  mobile_no             BIGINT            UNIQUE,
  email_id              VARCHAR(64)       UNIQUE
);

CREATE TABLE IF NOT EXISTS `companion` (
  companion_id          INTEGER           PRIMARY KEY,
  name                  VARCHAR(64),
  gender                VARCHAR(1),
  mobile_no             BIGINT            UNIQUE,
  resident_id           INTEGER,
  FOREIGN KEY (resident_id) REFERENCES resident(resident_id)
);

CREATE TABLE IF NOT EXISTS `room` (
  room_no               INTEGER           PRIMARY KEY,
  room_type             VARCHAR(24),
  capacity              VARCHAR(24)
);

CREATE TABLE IF NOT EXISTS `booking` (
  booking_id            INTEGER,
  resident_id           INTEGER,
  room_no               INTEGER,
  booking_date          DATE,
  PRIMARY KEY (booking_id, room_no, booking_date),
  FOREIGN KEY (resident_id) REFERENCES resident(resident_id),
  FOREIGN KEY (room_no)     REFERENCES room(room_no)
);

CREATE TABLE IF NOT EXISTS `food` (
  item_id               INTEGER           PRIMARY KEY,
  name                  VARCHAR(64),
  food_type             VARCHAR(24),
  price                 FLOAT
);

CREATE TABLE IF NOT EXISTS `food_order` (
  order_id              INTEGER           PRIMARY KEY,
  resident_id           INTEGER,
  item_id               INTEGER,
  order_time            DATETIME,
  FOREIGN KEY (resident_id) REFERENCES resident(resident_id),
  FOREIGN KEY (item_id)     REFERENCES food(item_id)
);


INSERT INTO employee (employee_id, name, address, aadhar, mobile_no, email_id, joining_date, salary)
VALUES
    (1,  'Arjun Nair',         'Thiruvananthapuram, Kerala',  789001534567, 9847015345, 'arjun.nair@example.com',         '2020-01-15', 35000.00),
    (2,  'Meera Pillai',       'Kochi, Kerala',               789001534568, 9847153456, 'meera.pillai@example.com',       '2019-08-20', 32000.00),
    (3,  'Sudeep Kumar',       'Alappuzha, Kerala',           789001534569, 9847234567, 'sudeep.kumar@example.com',       '2021-03-10', 28000.00),
    (4,  'Neha Ramesh',        'Kollam, Kerala',              789001534570, 9847345678, 'neha.ramesh@example.com',        '2022-07-01', 26000.00),
    (5,  'Vishnu Das',         'Kozhikode, Kerala',           789001534571, 9847456789, 'vishnu.das@example.com',         '2021-11-05', 30000.00),
    (6,  'Parvathy Raj',       'Thrissur, Kerala',            789001534572, 9847567890, 'parvathy.raj@example.com',       '2020-02-22', 34000.00),
    (7,  'Rohit Menon',        'Kannur, Kerala',              789001534573, 9847678901, 'rohit.menon@example.com',        '2023-01-15', 27000.00),
    (8,  'Deepa Krishnan',     'Palakkad, Kerala',            789001534574, 9847789015, 'deepa.krishnan@example.com',     '2018-12-05', 36000.00),
    (9,  'Anjali Varma',       'Idukki, Kerala',              789001534575, 9847890153, 'anjali.varma@example.com',       '2021-05-25', 29500.00),
    (10, 'Mohan Chandran',     'Malappuram, Kerala',          789001534576, 9847901534, 'mohan.chandran@example.com',     '2019-03-19', 31000.00),
    (11, 'Rina Joseph',        'Ernakulam, Kerala',           789001534577, 9847011152, 'rina.joseph@example.com',        '2020-08-10', 28000.00),
    (12, 'Shyam S Pillai',     'Pathanamthitta, Kerala',      789001534578, 9847022233, 'shyam.pillai@example.com',       '2021-04-07', 33000.00),
    (13, 'Kiran Madhav',       'Chennai, Tamil Nadu',         789001534579, 9447011523, 'kiran.madhav@example.com',       '2018-06-15', 35000.00),
    (14, 'Sneha Radhakrishnan','Bangalore, Karnataka',        789001534580, 9447022334, 'sneha.radha@example.com',        '2020-09-23', 37000.00),
    (15, 'Rahul Iyer',         'Mumbai, Maharashtra',         789001534581, 9447033445, 'rahul.iyer@example.com',         '2022-05-30', 31000.00),
    (16, 'Divya S Nair',       'New Delhi, India',            789001534582, 9447044556, 'divya.s.nair@example.com',       '2021-07-17', 33000.00),
    (17, 'Anand Krishnan',     'Hyderabad, Telangana',        789001534583, 9447055667, 'anand.krishnan@example.com',     '2022-11-19', 34500.00),
    (18, 'Maria Gonzalez',     'Madrid, Spain',               789001534587, 6661534567, 'maria.gonzalez@example.es',      '2019-12-01', 37500.00),
    (19, 'John Smith',         'London, UK',                  789001534588, 7701152334, 'john.smith@example.co.uk',       '2020-06-22', 39000.00),
    (20, 'Akira Tanaka',       'Tokyo, Japan',                789001534589, 8134455667, 'akira.tanaka@example.jp',        '2021-10-18', 41000.00);

INSERT INTO resident (resident_id, name, address, aadhar, gender, age, mobile_no, email_id)
VALUES
  (1,  'Manoj Kumar',         'Kochi, Kerala',              789101111111,   'M', 35, 9847111111,    'manoj.kumar@example.com'),
  (2,  'Latha Menon',         'Thrissur, Kerala',           789101111112,   'F', 42, 9847222222,    'latha.menon@example.com'),
  (3,  'Arun Gopal',          'Chennai, Tamil Nadu',        789101111113,   'M', 29, 9847333333,    'arun.gopal@example.com'),
  (4,  'Nisha Varghese',      'Kozhikode, Kerala',          789101111114,   'F', 24, 9847444444,    'nisha.varghese@example.com'),
  (5,  'Deepak R',            'Kollam, Kerala',             789101111115,   'M', 31, 9847555555,    'deepak.r@example.com'),
  (6,  'Reshma P',            'Bangalore, Karnataka',       789101111116,   'F', 26, 9847666666,    'reshma.p@example.com'),
  (7,  'Vivek S',             'Alappuzha, Kerala',          789101111117,   'M', 40, 9847777777,    'vivek.s@example.com'),
  (8,  'Anju Thomas',         'New Delhi, India',           789101111118,   'F', 22, 9847888888,    'anju.thomas@example.com'),
  (9,  'Jose Mathew',         'Kottayam, Kerala',           789101111119,   'M', 37, 9847999999,    'jose.mathew@example.com'),
  (10, 'Emma Brown',          'London, UK',                 789101111141,   'F', 28, 7448000001,    'emma.brown@example.co.uk'),
  (11, 'Ramesh Babu',         'Palakkad, Kerala',           789101111121,   'M', 33, 9847000002,    'ramesh.babu@example.com'),
  (12, 'Kavya Radhakrishnan', 'Ernakulam, Kerala',          789101111122,   'F', 21, 9847000003,    'kavya.radha@example.com'),
  (13, 'Ajay Das',            'New Delhi, India',           789101111123,   'M', 28, 9847000004,    'ajay.das@example.com'),
  (14, 'Swathi S',            'Chennai, Tamil Nadu',        789101111124,   'F', 32, 9847000005,    'swathi.s@example.com'),
  (15, 'Harish Kumar',        'Pune, Maharashtra',          789101111125,   'M', 34, 9847000006,    'harish.kumar@example.com'),
  (16, 'Priya Menon',         'Kozhikode, Kerala',          789101111126,   'F', 30, 9847000007,    'priya.menon@example.com'),
  (17, 'Alok Varma',          'Idukki, Kerala',             789101111127,   'M', 41, 9847000008,    'alok.varma@example.com'),
  (18, 'Sheela M',            'Bangalore, Karnataka',       789101111128,   'F', 39, 9847000009,    'sheela.m@example.com'),
  (19, 'Sanjay Joseph',       'Kottayam, Kerala',           789101111129,   'M', 36, 9847000010,    'sanjay.joseph@example.com'),
  (20, 'Bindu K',             'Alappuzha, Kerala',          789101111130,   'F', 26, 9847000011,    'bindu.k@example.com'),
  (21, 'Rohit Eswar',         'Thiruvananthapuram, Kerala', 789101111131,   'M', 38, 9847000012,    'rohit.eswar@example.com'),
  (22, 'Anitha Raj',          'Kannur, Kerala',             789101111132,   'F', 25, 9847000013,    'anitha.raj@example.com'),
  (23, 'Oliver Smith',        'New York, USA',              789101111142,   'M', 31, 1774000001,    'oliver.smith@example.com'),
  (24, 'Lekha S',             'Malappuram, Kerala',         789101111134,   'F', 40, 9847000015,    'lekha.s@example.com'),
  (25, 'Sunil John',          'New Delhi, India',           789101111135,   'M', 43, 9847000016,    'sunil.john@example.com'),
  (26, 'Geetha G',            'Chennai, Tamil Nadu',        789101111136,   'F', 33, 9847000017,    'geetha.g@example.com'),
  (27, 'Sophie Müller',       'Berlin, Germany',            789101111143,   'F', 35, 4915123456,    'sophie.muller@example.de'),
  (28, 'Yuki Nakamura',       'Osaka, Japan',               789101111144,   'F', 27, 8135522334,    'yuki.nakamura@example.jp'),
  (29, 'Carlos Silva',        'Lisbon, Portugal',           789101111145,   'M', 39, 3519112233,    'carlos.silva@example.pt'),
  (30, 'Abhijith P',          'Trivandrum, Kerala',         789101111140,   'M', 36, 9847000021,    'abhijith.p@example.com');

INSERT INTO companion (companion_id, name, gender, mobile_no, resident_id)
VALUES
  (1,  'Rakhi Menon',     'F', 9847000100,     1),
  (2,  'Aditya Kumar',    'M', 9847000101,     2),
  (3,  'Sanjana R',       'F', 9847000102,     3),
  (4,  'Biju K',          'M', 9847000103,     4),
  (5,  'Nandini P',       'F', 9847000104,     5),
  (6,  'Karthik R',       'M', 9847000105,     6),
  (7,  'Anitha L',        'F', 9847000106,     7),
  (8,  'Ravi M',          'M', 9847000107,     8),
  (9,  'Pooja S',         'F', 9847000108,     9),
  (10, 'Suresh N',        'M', 9847000109,    10),
  (11, 'Sneha Varma',     'F', 9847000110,    11),
  (12, 'Sunny Joseph',    'M', 9847000111,    12),
  (13, 'Vinu P',          'M', 9847000112,    13),
  (14, 'Lisha S',         'F', 9847000113,    14),
  (15, 'George K',        'M', 9847000114,    15),
  (16, 'Anju A',          'F', 9847000115,    16),
  (17, 'Mahesh R',        'M', 9847000116,    17),
  (18, 'Dhanya V',        'F', 9847000117,    18),
  (19, 'Ashwin T',        'M', 9847000118,    19),
  (20, 'Emily Davis',     'F', 7447012345,    10),
  (21, 'Anjali Kumar',    'F', 9847000200,     1),
  (22, 'Rajesh Singh',    'M', 9847000201,     2),
  (23, 'Nisha Thomas',    'F', 9847000202,     3),
  (24, 'Vijay Menon',     'M', 9847000203,     4),
  (25, 'Sneha Pillai',    'F', 9847000204,     5),
  (26, 'Deepak Ramesh',   'M', 9847000205,     6),
  (27, 'Asha Nair',       'F', 9847000206,     7),
  (28, 'Kiran Kumar',     'M', 9847000207,     8),
  (29, 'Priya Varma',     'F', 9847000208,     9),
  (30, 'Anil Raj',        'M', 9847000209,    10),
  (31, 'Latha Das',       'F', 9847000210,     1),
  (32, 'Suresh Menon',    'M', 9847000211,     2),
  (33, 'Radha Sharma',    'F', 9847000212,     3),
  (34, 'Ajay Thomas',     'M', 9847000213,     4),
  (35, 'Meena Nair',      'F', 9847000214,     5),
  (36, 'Ravi Kumar',      'M', 9847000215,     6),
  (37, 'Priya Joseph',    'F', 9847000216,     7),
  (38, 'Sanjay Menon',    'M', 9847000217,     8),
  (39, 'Geetha Varma',    'F', 9847000218,     9),
  (40, 'Manoj Raj',       'M', 9847000219,    10);

INSERT INTO room (room_no, room_type, capacity)
VALUES
  (101, 'a/c',     'single'),
  (102, 'a/c',     'double'),
  (103, 'non-a/c', 'single'),
  (104, 'a/c',     'double'),
  (105, 'non-a/c', 'double'),
  (106, 'a/c',     'single'),
  (107, 'non-a/c', 'single'),
  (108, 'a/c',     'double'),
  (109, 'non-a/c', 'single'),
  (110, 'a/c',     'double'),
  (111, 'a/c',     'single'),
  (112, 'a/c',     'double'),
  (113, 'non-a/c', 'single'),
  (114, 'a/c',     'double'),
  (115, 'non-a/c', 'single'),
  (116, 'non-a/c', 'double'),
  (117, 'a/c',     'single'),
  (118, 'a/c',     'double'),
  (119, 'non-a/c', 'single'),
  (120, 'a/c',     'double'),
  (201, 'a/c',     'single'),
  (202, 'a/c',     'double'),
  (203, 'non-a/c', 'double'),
  (204, 'a/c',     'single'),
  (205, 'non-a/c', 'single'),
  (206, 'a/c',     'double'),
  (207, 'non-a/c', 'single'),
  (208, 'non-a/c', 'double'),
  (209, 'a/c',     'single'),
  (210, 'a/c',     'double'),
  (211, 'a/c',     'single'),
  (212, 'a/c',     'double'),
  (213, 'non-a/c', 'double'),
  (214, 'a/c',     'single'),
  (215, 'non-a/c', 'double'),
  (216, 'a/c',     'single'),
  (217, 'a/c',     'double'),
  (218, 'non-a/c', 'single'),
  (219, 'a/c',     'double'),
  (220, 'non-a/c', 'single');


INSERT INTO booking (booking_id, resident_id, room_no, booking_date)
VALUES
  (  1,  1,  101, '2025-08-01'),
  (  2,  2,  102, '2025-08-02'),
  (  3,  3,  103, '2025-08-03'),
  (  4,  4,  104, '2025-08-04'),
  (  5,  5,  105, '2025-08-05'),
  (  6,  6,  106, '2025-08-06'),
  (  7,  7,  107, '2025-08-07'),
  (  8,  8,  108, '2025-08-08'),
  (  9,  9,  109, '2025-08-09'),
  ( 10, 10,  110, '2025-08-10'),
  ( 11, 11,  111, '2025-08-11'),
  ( 12, 12,  112, '2025-08-12'),
  ( 13, 13,  113, '2025-08-13'),
  ( 14, 14,  114, '2025-08-14'),
  ( 15, 15,  115, '2025-08-15'),
  ( 16, 16,  116, '2025-08-16'),
  ( 17, 17,  117, '2025-08-17'),
  ( 18, 18,  118, '2025-08-18'),
  ( 19, 19,  119, '2025-08-19'),
  ( 20, 20,  120, '2025-08-20'),
  ( 21, 21,  201, '2025-08-21'),
  ( 22, 22,  202, '2025-08-22'),
  ( 23, 23,  203, '2025-08-23'),
  ( 24, 24,  204, '2025-08-24'),
  ( 25, 25,  205, '2025-08-25'),
  ( 26, 26,  206, '2025-08-26'),
  ( 27, 27,  207, '2025-08-27'),
  ( 28, 28,  208, '2025-08-28'),
  ( 29, 29,  209, '2025-08-29'),
  ( 30, 30,  210, '2025-08-30'),
  (  1,  1,  101, '2025-09-01'),
  (  1,  1,  103, '2025-09-01'),
  (  2,  2,  102, '2025-09-02'),
  (  3,  3,  104, '2025-09-03'),
  (  3,  3,  105, '2025-09-04'),
  (  3,  3,  120, '2025-09-05'),
  (  4,  4,  110, '2025-09-06'),
  (  4,  4,  108, '2025-09-07'),
  (  4,  4,  109, '2025-09-08'),
  (  5,  8,  204, '2025-09-09'),
  (  5,  8,  205, '2025-09-10');

INSERT INTO food (item_id, name, food_type, price)
VALUES
  (1,  'Kerala Sadya',          'vegetarian',     250.00),
  (2,  'Fish Curry Rice',       'non-vegetarian', 220.00),
  (3,  'Malabar Biriyani',      'non-vegetarian', 300.00),
  (4,  'Appam with Stew',       'vegetarian',     180.00),
  (5,  'Idiyappam & Egg Curry', 'non-vegetarian', 200.00),
  (6,  'Masala Dosa',           'vegetarian',     150.00),
  (7,  'Paneer Butter Masala',  'vegetarian',     240.00),
  (8,  'Chicken Tikka',         'non-vegetarian', 280.00),
  (9,  'Caesar Salad',          'vegetarian',     350.00),
  (10, 'Pasta Alfredo',         'vegetarian',     320.00),
  (11, 'Beef Steak',            'non-vegetarian', 480.00),
  (12, 'Sushi Platter',         'non-vegetarian', 520.00),
  (13, 'Falafel Wrap',          'vegetarian',     270.00),
  (14, 'Pizza Margherita',      'vegetarian',     400.00),
  (15, 'Grilled Salmon',        'non-vegetarian', 550.00);

INSERT INTO food_order (order_id, resident_id, item_id, order_time)
VALUES
  (1,  1,  1,  '2025-09-01 12:30:00'),
  (2,  2,  2,  '2025-09-01 13:00:00'),
  (3,  3,  3,  '2025-09-01 19:15:00'),
  (4,  4,  4,  '2025-09-02 08:45:00'),
  (5,  5,  5,  '2025-09-02 09:00:00'),
  (6,  6,  6,  '2025-09-02 10:15:00'),
  (7,  7,  7,  '2025-09-02 20:10:00'),
  (8,  8,  8,  '2025-09-02 21:00:00'),
  (9,  9,  9,  '2025-09-03 12:00:00'),
  (10, 10, 10, '2025-09-03 12:45:00'),
  (11, 11,  3, '2025-09-03 19:30:00'),
  (12, 12,  3, '2025-09-03 19:45:00'),
  (13, 13, 13, '2025-09-03 14:00:00'),
  (14, 14, 11, '2025-09-03 21:30:00'),
  (15, 15, 15, '2025-09-03 20:45:00'),
  (16, 16,  1, '2025-09-04 12:20:00'),
  (17, 17,  2, '2025-09-04 13:15:00'),
  (18, 18,  3, '2025-09-04 19:05:00'),
  (19, 19,  4, '2025-09-04 08:50:00'),
  (20, 20,  5, '2025-09-04 09:10:00'),
  (21, 21,  6, '2025-09-04 10:30:00'),
  (22, 22,  7, '2025-09-04 20:00:00'),
  (23, 23,  8, '2025-09-04 21:10:00'),
  (24, 24,  9, '2025-09-05 12:15:00'),
  (25, 25, 10, '2025-09-05 13:05:00'),
  (26, 26, 11, '2025-09-05 19:25:00'),
  (27, 27, 12, '2025-09-05 19:50:00'),
  (28, 28, 13, '2025-09-05 14:20:00'),
  (29, 29, 14, '2025-09-05 21:40:00'),
  (30, 30, 15, '2025-09-05 20:50:00'),
  (31,  1,  3, '2025-09-06 19:10:00'),
  (32,  2,  7, '2025-09-06 20:20:00'),
  (33,  3,  8, '2025-09-06 21:15:00'),
  (34,  4,  6, '2025-09-06 09:30:00'),
  (35,  5,  2, '2025-09-06 12:45:00'),
  (36,  6, 15, '2025-09-06 21:00:00'),
  (37,  7, 12, '2025-09-06 19:40:00'),
  (38,  8, 13, '2025-09-06 14:25:00'),
  (39,  9, 14, '2025-09-06 21:35:00'),
  (40, 10, 11, '2025-09-06 20:55:00'),
  (41, 11,  1, '2025-09-07 12:40:00'),
  (42, 12,  5, '2025-09-07 09:05:00'),
  (43, 13,  4, '2025-09-07 08:55:00'),
  (44, 14,  9, '2025-09-07 12:25:00'),
  (45, 15, 10, '2025-09-07 13:20:00'),
  (46, 16,  7, '2025-09-07 20:05:00'),
  (47, 17,  8, '2025-09-07 21:05:00'),
  (48, 18, 14, '2025-09-07 21:45:00'),
  (49, 19,  2, '2025-09-07 12:50:00'),
  (50, 20,  6, '2025-09-07 10:25:00');

--  (a) Print the details of the residents who has more than one companions in a
--  single booking.
--
SELECT r.resident_id, r.name, ccnt.companion_count
FROM resident r
JOIN (
  SELECT resident_id, COUNT(companion_id) AS companion_count
  FROM companion
  GROUP BY resident_id
) AS ccnt ON ccnt.resident_id = r.resident_id
WHERE ccnt.companion_count > 1;
--  
--  OUTPUT.
--  +-------------+------------+-----------------+
--  | resident_id | name       | companion_count |
--  +-------------+------------+-----------------+
--  |          10 | Emma Brown |               2 |
--  +-------------+------------+-----------------+
--  1 row in set (0.001 sec)

--  (b) Print the details of the residents along with the number of companions
--  for a specified period.
--
DROP VIEW IF EXISTS `companion_count`;
CREATE VIEW `companion_count`
AS
  SELECT c.resident_id, COUNT(c.companion_id) AS count
  FROM companion c
  GROUP BY c.resident_id;

SELECT DISTINCT r.resident_id, r.name, r.address, cc.count
FROM resident r
JOIN companion_count cc ON cc.resident_id = r.resident_id
JOIN booking b ON b.resident_id = r.resident_id
WHERE b.booking_date BETWEEN '2025-09-01' AND '2025-09-30';
--  
--  OUTPUT.
--  +-------------+----------------+---------------------+-------+
--  | resident_id | name           | address             | count |
--  +-------------+----------------+---------------------+-------+
--  |           1 | Manoj Kumar    | Kochi, Kerala       |     3 |
--  |           2 | Latha Menon    | Thrissur, Kerala    |     3 |
--  |           3 | Arun Gopal     | Chennai, Tamil Nadu |     3 |
--  |           4 | Nisha Varghese | Kozhikode, Kerala   |     3 |
--  |           8 | Anju Thomas    | New Delhi, India    |     3 |
--  +-------------+----------------+---------------------+-------+
--  11 rows in set (0.00 sec)

--  (c) Print the details of the residents who reserved more than two a/c rooms
--  in at least two different bookings.
--
DROP VIEW IF EXISTS ac_rooms_booked;
CREATE VIEW ac_rooms_booked
AS
  SELECT b.resident_id, b.booking_id, COUNT(o.room_no) AS ac_rooms
  FROM booking b
  JOIN room o ON b.room_no = o.room_no
  WHERE o.room_type = 'a/c'
  GROUP BY b.resident_id, b.booking_id
  HAVING ac_rooms > 2;

DROP VIEW IF EXISTS gt_two_rooms_booked;
CREATE VIEW gt_two_rooms_booked AS
  SELECT resident_id, COUNT(DISTINCT booking_id) AS times_booked
  FROM ac_rooms_booked
  GROUP BY resident_id
  HAVING times_booked > 2;

SELECT r.resident_id, r.name
FROM resident r
JOIN gt_two_rooms_booked gt ON gt.resident_id = r.resident_id;
--  
--  OUTPUT.
--  Empty set (0.01 sec)

--  (d) Print the details of the food item(s) ordered by maximum number of
--  residents and the details of the food item(s) ordered b the minimum number
--  of residents.
--
DROP VIEW IF EXISTS `order_count`;
CREATE VIEW `order_count`
AS
  SELECT fo.item_id, COUNT(fo.order_id) AS order_count
  FROM food_order fo
  GROUP BY fo.item_id
  ORDER BY order_count DESC;

SELECT f.item_id, f.name, oc.order_count
FROM food f
JOIN order_count oc ON oc.item_id = f.item_id
JOIN ( SELECT MAX(order_count) AS max FROM order_count ) AS max
  ON oc.order_count = max.max;

SELECT f.item_id, f.name, oc.order_count
FROM food f
JOIN order_count oc ON oc.item_id = f.item_id
JOIN ( SELECT MIN(order_count) AS min FROM order_count ) AS min
  ON oc.order_count = min.min;
--  
--  OUTPUT.
--  +---------+------------------+-------------+
--  | item_id | name             | order_count |
--  +---------+------------------+-------------+
--  |       3 | Malabar Biriyani |           5 |
--  +---------+------------------+-------------+
--  1 row in set (0.001 sec)
--  
--  +---------+---------------+-------------+
--  | item_id | name          | order_count |
--  +---------+---------------+-------------+
--  |      12 | Sushi Platter |           2 |
--  +---------+---------------+-------------+
--  1 row in set (0.000 sec)

--  (e) Print the details of the food item(s) in the non-decreasing order of
--  preference in a specific period. The preference is to be computed on the
--  basis of two factors- the number of orders for that item in the period an
--  the price for the item. The item with the highest number of orders and least
--  price is considered to have most preference.
--
DROP VIEW IF EXISTS `order_count`;
CREATE VIEW `order_count`
AS
  SELECT fo.item_id, COUNT(fo.order_id) AS order_count
  FROM food_order fo
  WHERE fo.order_time BETWEEN '2025-09-02' AND '2025-09-05'
  GROUP BY fo.item_id
  ORDER BY order_count DESC;

SELECT f.item_id, f.name, oc.order_count, f.price
FROM food f
JOIN order_count oc ON oc.item_id = f.item_id
ORDER BY oc.order_count DESC, f.price ASC;
--  
--  OUTPUT.
--  +---------+-----------------------+-------------+-------+
--  | item_id | name                  | order_count | price |
--  +---------+-----------------------+-------------+-------+
--  |       3 | Malabar Biriyani      |           3 |   300 |
--  |       6 | Masala Dosa           |           2 |   150 |
--  |       4 | Appam with Stew       |           2 |   180 |
--  |       5 | Idiyappam & Egg Curry |           2 |   200 |
--  |       7 | Paneer Butter Masala  |           2 |   240 |
--  |       8 | Chicken Tikka         |           2 |   280 |
--  |       2 | Fish Curry Rice       |           1 |   220 |
--  |       1 | Kerala Sadya          |           1 |   250 |
--  |      13 | Falafel Wrap          |           1 |   270 |
--  |      10 | Pasta Alfredo         |           1 |   320 |
--  |       9 | Caesar Salad          |           1 |   350 |
--  |      11 | Beef Steak            |           1 |   480 |
--  |      15 | Grilled Salmon        |           1 |   550 |
--  +---------+-----------------------+-------------+-------+
--  13 rows in set (0.001 sec)
