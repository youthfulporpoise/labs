--  Write a PL/SQL to check whether a number is narcissistic or not.  A number
--  N = D1D2D3...Dn of n digits is narcissistic if N = D1^n + D2^n + ... +
--  Dn^n.

CREATE DATABASE IF NOT EXISTS `23cs031-2-1`;
USE `23cs031-2-1`;

DELIMITER $$
DROP PROCEDURE narcissistic;
CREATE PROCEDURE narcissistic (IN number INT)
BEGIN
  DECLARE d, n, n_0 INT;
  SET n_0 = number;
  SET d = 0;
  SET n = CEIL(LOG10(number));

  WHILE n_0 > 0 DO
    SET d = d + POWER((n_0  % 10), n);
    SET n_0 = n_0 DIV 10;
  END WHILE;

  IF d = number THEN
    SELECT number, 'yes' AS `is narcissistic?`;
  ELSE
    SELECT number, 'no' AS `is narcissistic?`;
  END IF;
END $$
DELIMITER ;

CALL narcissistic(153);   -- narcissistic
CALL narcissistic(764);   -- not narcissistic
CALL narcissistic(1634);  -- narcissistic
