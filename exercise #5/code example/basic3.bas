  5 PRINT "What is your name: "
 10 INPUT U$
 20 PRINT "Hello "; U$
 25 PRINT "How many stars do you want: "
 30 INPUT N$
 40 LET S$ = ""
 50 FOR I = 1 TO N
 60 LET S$ = S$ + "*"
 70 NEXT I
 80 PRINT S$
 85 PRINT "Do you want more stars? "
 90 INPUT A$
100 IF LEN(A$) = 0 THEN GOTO 90
110 LET A$ = LEFT$(A$, 1)
120 IF A$ = "Y" OR A$ = "y" THEN GOTO 30
130 PRINT "Goodbye "; U$
140 END
