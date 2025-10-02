--  The following table shows the details of the books available in a library.
--  Book(Accno, Title, Author, Publisher, Eition, Number of copies) Write a trigger
--  that displays the total number of tuples in the table on each insertion,
--  deletion and updation.

CREATE DATABASE IF NOT EXISTS `23cs031-2-7`;
USE `23cs031-2-7`;

DROP TABLE IF EXISTS
  book,
  book_tuple_count;

CREATE TABLE `book` (
  accno             INTEGER       PRIMARY KEY,
  title             VARCHAR(64),
  author            VARCHAR(64),
  edition           INTEGER,
  number_of_copies  INTEGER
);

CREATE TABLE `book_tuple_count` (
  count             INTEGER
);

INSERT INTO book_tuple_count
VALUES (0);

DELIMITER @@

CREATE TRIGGER `tuple_insert`
AFTER INSERT ON `book`
FOR EACH ROW
BEGIN
  UPDATE book_tuple_count
  SET count = count + 1;
END @@

CREATE TRIGGER `tuple_delete`
AFTER DELETE ON `book`
FOR EACH ROW
BEGIN
  UPDATE book_tuple_count
  SET count = count - 1;
END @@

DELIMITER ;
