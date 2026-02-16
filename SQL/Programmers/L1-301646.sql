-- https://school.programmers.co.kr/learn/courses/30/lessons/301646

SELECT COUNT(ID) AS COUNT
FROM ECOLI_DATA
WHERE (GENOTYPE & 2 = 0)
    AND ((GENOTYPE & 1 > 0) OR (GENOTYPE & 4 > 0));