USE `23cs031`;

-- CREATE TABLE employee (
--     employee_id         INTEGER,
--     employee_name       VARCHAR(36),
--     street              VARCHAR(24),
--     city                VARCHAR(24),
--     PRIMARY KEY (employee_id)
-- );
-- 
-- CREATE TABLE bank (
--     bank_id             INTEGER,
--     bank_name           VARCHAR(36),
--     city                VARCHAR(24),
--     PRIMARY KEY (bank_id)
-- );
-- 
-- CREATE TABLE works (
--     employee_id         INTEGER,
--     bank_id             INTEGER,
--     salary              FLOAT,
--     FOREIGN KEY (employee_id) REFERENCES employee(employee_id),
--     FOREIGN KEY (bank_id) REFERENCES bank(bank_id)
-- );
-- 
-- CREATE TABLE manages (
--     employee_id       INTEGER,
--     manager_id        INTEGER,
--     FOREIGN KEY (manager_id) REFERENCES employee(employee_id),
--     FOREIGN KEY (employee_id) REFERENCES employee(employee_id)
-- );


-- INSERT INTO employee VALUES
--     ( 1,     "M. Harshvardhan",         "Breach Candy",         "Mumbai"),
--     ( 2,     "Mohammed Shah",           "Kamal Marg",           "Noida"),
--     ( 3,     "Aisha Fathima",           "Edapally Jn",          "Edapally"),
--     ( 4,     "G. H. Nair",              "Mangattu Rd",          "Ernakulam"),
--     ( 5,     "Christina Jose",          "Theatre Rd",           "Kodungallur"),
--     ( 6,     "Aliya Rahseed",           "Nethaji Rd",           "Pollachi"),
--     ( 7,     "Selvi Ramakrishnan",      "Aruthra Nagar",        "Pondicherry"),
--     ( 8,     "Sitara Jayakumar",        "English Church Rd",    "Palakkad"),
--     ( 9,     "Jennifer Thottathil",     "Double Cutting",       "Idukki"),
--     (10,     "Aparna John",             "Anna Salai",           "Chennai");
-- 
-- 
-- INSERT INTO bank VALUES
--     (1,     "State Bank of India",         "Mumbai"),
--     (2,     "Bank of Oman",                "Muscat"),
--     (3,     "Indian Bank",                 "Chennai"),
--     (4,     "HDFC Bank",                   "Mumbai"),
--     (5,     "Federal Bank",                "Aluva");

-- INSERT INTO works VALUES
--     (1,      2,      200000),
--     (2,      4,      300000),
--     (3,      5,       80000),
--     (4,      3,       60000),
--     (5,      4,      120000),
--     (6,      2,      140000),
--     (7,      1,       70000),
--     (8,      3,       80000),
--     (9,      1,       80000),
--     (10,     5,       90000);
-- 
-- INSERT INTO manages VALUES
--     (1,     6),
--     (2,     5),
--     (3,     10),
--     (4,     8),
--     (5,     5),
--     (6,     6),
--     (7,     9),
--     (8,     8),
--     (9,     9),
--     (10,    10);

-- (a) Find the names and cities of residence of all employees who work for Bank
-- of Oman.
-- SELECT e.employee_name, e.street, e.city, b.bank_name
-- FROM employee e
-- JOIN works w ON e.employee_id = w.employee_id
-- JOIN bank b ON b.bank_id = w.bank_id
-- WHERE b.bank_name = "Bank of Oman";

-- (b) Find the names, street, addresses, and cities of residence of all
-- employees who work for Indian Bank and earn more than INR 41,000.
-- SELECT e.employee_name, e.street, e.city, b.bank_name
-- FROM employee e
-- JOIN works w ON e.employee_id = w.employee_id
-- JOIN bank b ON b.bank_id = w.bank_id
-- WHERE b.bank_name = "Indian Bank" AND
--       w.salary > 41000;

-- (c) Find all employees in the database who live in the sames cities as the
-- banks for which they work.
-- SELECT e.employee_name, b.bank_name, e.city, b.city
-- FROM employee e
-- JOIN works w ON e.employee_id = w.employee_id
-- JOIN bank b ON b.bank_id = w.bank_id
-- WHERE e.city = b.city;

-- (d) Find all employees in the database that does not work in State Bank of
-- India.
-- SELECT e.employee_name, b.bank_name
-- FROM employee e
-- JOIN works w ON e.employee_id = w.employee_id
-- JOIN bank b ON b.bank_id = w.bank_id
-- WHERE b.bank_name <> "State Bank of India";

-- (e) Find all employees in the database that earn more than every employee of
-- Indian Bank.
-- CREATE VIEW max_ib AS
-- SELECT MAX(w.salary) AS max
-- FROM works w
-- JOIN bank b ON w.bank_id = b.bank_id
-- WHERE bank_name = "Indian Bank"
-- GROUP BY bank_name;
-- 
-- SELECT e.employee_name, w.salary, b.bank_name
-- FROM employee e
-- JOIN works w ON e.employee_id = w.employee_id
-- JOIN bank b ON b.bank_id = w.bank_id
-- JOIN max_ib m
-- WHERE b.bank_name <> "Indian Bank" AND w.salary > m.max;

-- (f) Find the number of employees working in each bank.
SELECT b.bank_name, COUNT(b.bank_name) AS strength
FROM bank b
JOIN works w on b.bank_id = w.bank_id
JOIN employee e ON e.employee_id = w.employee_id
GROUP BY b.bank_name;
