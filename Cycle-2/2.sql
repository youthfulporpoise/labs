--  Write a PL/SQL script to check whether a string (read from the user) is a
--  palindrome or not.
DROP DATABASE `23cs031-2-2`;
CREATE DATABASE IF NOT EXISTS `23cs031-2-2`;
USE `23cs031-2-2`;

DELIMITER |

CREATE PROCEDURE `ispalindrome` (IN word VARCHAR(255))
proc: BEGIN
  DECLARE i INT DEFAULT 1;
  DECLARE palindrome INT DEFAULT 1;
  DECLARE len, j INT;

  SET len = CHAR_LENGTH(word);
  SET j = len;

  WHILE (i <= len AND j > 0) DO
    SET @cs_1 = SUBSTRING(word, i, 1);
    SET @cs_2 = SUBSTRING(word, j, 1);

    IF @cs_1 <> @cs_2 THEN
      SELECT word AS `input`,
             'no' AS `is a palindrome?`;
      LEAVE proc;
    END IF;

    SET i = i + 1;
    SET j = j - 1;
  END WHILE;

  SELECT word AS `input`,
         'yes' AS `is a palindrome?`;
END |

DELIMITER ;

CALL ispalindrome('malayalam');
CALL ispalindrome('kerala');
CALL ispalindrome('arora');
CALL ispalindrome('mohabbet');
