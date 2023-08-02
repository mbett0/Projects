SELECT COUNT(*)
FROM part_nyc P
WHERE on_hand > 70;

SELECT SUM(
(SELECT COUNT(PN.on_hand)
FROM part_nyc PN, color C
WHERE PN.color = C.color_id AND color_name = 'Red')
+
(SELECT COUNT(PS.on_hand)
FROM part_sfo PS, color C
WHERE PS.color = C.color_id AND color_name = 'Red'));

SELECT S.supplier_id, S.supplier_name
FROM supplier S
WHERE
(SELECT SUM(PN.on_hand)
FROM part_nyc PN
WHERE S.supplier_id = PN.supplier)
>
(SELECT SUM(PS.on_hand)
FROM part_sfo PS
WHERE S.supplier_id = PS.supplier)
ORDER BY S.supplier_id;

SELECT DISTINCT S.supplier_id, S.supplier_name
FROM supplier S, part_nyc P
WHERE S.supplier_id = P.supplier AND P.part_number IN
(SELECT PN.part_number
FROM supplier S, part_nyc PN
WHERE S.supplier_id = PN.supplier
EXCEPT
SELECT PS.part_number
FROM supplier S, part_sfo PS
WHERE S.supplier_id = PS.supplier)
ORDER BY S.supplier_id;

UPDATE part_nyc
SET on_hand = on_hand - 10
WHERE on_hand >= 10;

DELETE FROM part_nyc
WHERE on_hand < 30;


