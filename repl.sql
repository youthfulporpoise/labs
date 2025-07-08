USE `23cs031`;

-- CREATE TABLE `employees` (
--     `id`        INTEGER          PRIMARY KEY,
--     `name`      VARCHAR(48),
--     `phoneno`   INTEGER
-- );
   
-- ALTER TABLE `employees`
--     ADD COLUMN `department_id` VARCHAR(24) UNIQUE NOT NULL;
-- 
   
-- CREATE TABLE `departments` (
--     `department_id`     VARCHAR(24)     PRIMARY KEY,
--     `name`              VARCHAR(40),
--     `hod_id`            INTEGER         UNIQUE NOT NULL,
--     FOREIGN KEY (hod_id) REFERENCES employees(id)
-- );
   
-- INSERT INTO `employees` VALUES
--     (1,     'Tarun Garg',       987654321,      'CSE'),
--     (2,     'Janaki Agarwal',   987654331,      'EEE'),
--     (3,     'Diya Bhatt',       999654331,      'ECE');
   
-- INSERT INTO `departments` VALUES
--     ('CSE',     'Computer Science & Engg.',             1),
--     ('EEE',     'Electrical & Electronics Engg.',       2),
--     ('ECE',     'Electronics & Communication Engg.',    3);
   
-- ALTER TABLE `employees`
--     ADD FOREIGN KEY (department_id)
--     REFERENCES departments(department_id);

-- SELECT * FROM `employees`; 

-- SELECT * FROM `departments`;

-- ALTER TABLE `employees`
--     ADD COLUMN `basic` INTEGER
--     DEFAULT 0;

-- UPDATE `employees`
--     SET basic = 60000;

-- UPDATE `employees`
--     SET basic = 80000
--     WHERE department_id = 'EEE';

ALTER TABLE `employees`
    ADD COLUMN `hra` INTEGER
    DEFAULT 0;
