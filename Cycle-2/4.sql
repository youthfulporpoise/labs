--  Write a PL/SQL program that reads a positive integer n, forms two seperate
--  tables namely PRIME and COMPOSITE containing the first n prime numbers and
--  the first n composite numbers, print the contents of the two tables and then
--  delete the two tables.

CREATE DATABASE IF NOT EXISTS `23cs031-2-4`;
USE `23cs031-2-4`;

DROP PROCEDURE prime_composite;
DROP FUNCTION is_prime;

DELIMITER @@

CREATE FUNCTION is_prime (n INT)
RETURNS INT
DETERMINISTIC
BEGIN
  DECLARE i INT DEFAULT 2;
  DECLARE prime INT DEFAULT 1;
  DECLARE n0 INT;

  SET n0 = n DIV 2;
  IF n <= i THEN
    RETURN 1;
  ELSE
    WHILE (i < n0 AND prime = 1) DO
      IF (n MOD i) = 0 THEN
        SET prime = 0;
      END IF;
      SET i = i + 1;
    END WHILE;
  END IF;
  RETURN prime;
END @@

CREATE PROCEDURE prime_composite (IN n INT)
BEGIN
  DECLARE i INT DEFAULT 2;
  DECLARE ret INT;

  CREATE TABLE prime (
    id    INTEGER     PRIMARY KEY AUTO_INCREMENT,
    val   INTEGER
  );
  CREATE TABLE composite (
    id    INTEGER     PRIMARY KEY AUTO_INCREMENT,
    val   INTEGER
  );

  WHILE i <= n DO
    SET ret = is_prime(i);
    IF ret = 1 THEN
      INSERT INTO prime(val) VALUES (i);
    ELSE
      INSERT INTO composite(val) VALUES (i);
    END IF;
    SET i = i + 1;
  END WHILE;

  SELECT val AS `primes` FROM prime;
  SELECT val AS `composites` FROM composite;

  DROP TABLE prime, composite;
END @@

DELIMITER ;

CALL prime_composite(30);
