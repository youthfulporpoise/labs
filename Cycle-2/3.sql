--  Write a PL/SQL script that prints the first n Fibonacci numbers.
CREATE DATABASE IF NOT EXISTS `23cs031-2-3`;
USE `23cs031-2-3`;

DROP TABLE IF EXISTS `fibonacci`;
CREATE TABLE IF NOT EXISTS `fibonacci` (
  seq_id    INTEGER   PRIMARY KEY   AUTO_INCREMENT,
  seq_val   INTEGER
);

DROP PROCEDURE fibonacci;

INSERT INTO fibonacci (seq_val)
VALUES (0), (1);

DELIMITER @@

CREATE PROCEDURE fibonacci (IN n INT)
BEGIN
  DECLARE a INT DEFAULT 0;
  DECLARE b INT DEFAULT 1;
  DECLARE tmp INT;

  WHILE b <= n DO
    SET tmp = a + b;
    SET a = b;
    SET b = tmp;

    INSERT INTO fibonacci (seq_val)
    VALUES (b);
  END WHILE;

  SELECT seq_id AS term, seq_val AS member FROM fibonacci;
END @@

DELIMITER ;

CALL fibonacci(50);
