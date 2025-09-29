--  Write a PL/SQL program that reads a positive integer n, forms two seperate
--  tables namely SQUARE and CUBE containing the perfect squares upto
--  (including) n and the perfect cubes (including) n, print the contents of the
--  two tables and then delete the two tables.

CREATE DATABASE IF NOT EXISTS `23cs031-5-1`;
USE `23cs031-5-1`;

DROP PROCEDURE IF EXISTS square_cube;

DELIMITER @@

CREATE PROCEDURE square_cube (IN n INT)
BEGIN
  DECLARE i INT DEFAULT 0;
  DECLARE s, c INT;

  CREATE TABLE squares (
    id    INT     PRIMARY KEY AUTO_INCREMENT,
    val   INT
  );
  CREATE TABLE cubes (
    id    INT     PRIMARY KEY AUTO_INCREMENT,
    val   INT
  );

  WHILE i < n DO
    SET s = POW(i, 2);
    SET c = POW(i, 3);

    IF s < n THEN
      INSERT INTO squares(val) VALUES (s);
    END IF;

    IF c < n THEN
      INSERT INTO cubes(val) VALUES (c);
    END IF;

    IF (s >= n AND c >= n) THEN
      SET i = n;
    ELSE
      SET i = i + 1;
    END IF;
  END WHILE;

  SELECT val AS `squares` FROM squares;
  SELECT val AS `cubes` FROM cubes;

  DROP TABLE squares, cubes;
END @@

DELIMITER ;

CALL square_cube(100);
