10 READ A, B, D, E
15 LET G = A * E - B * D
20 IF G = 0 THEN GOTO 65
30 READ C, F
37 LET X = (C*F - B*F) / G
42 LET Y = (A*F - C*F) / G
55 PRINT X; Y
60 GOTO 30
65 PRINT "NO UNIQUE SOLUTION"
70 DATA 1, 2, 4
80 DATA 2, 7, 5
85 DATA 1, 3, 4, 7
90 END
