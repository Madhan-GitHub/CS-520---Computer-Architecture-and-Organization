MOVC,R0,#46
MOVC,R1,#1
MOVC,R4,#0
MOVC,R5,#1
SUB,R2,R0,R1
BZ,R2,#0028
HALT
ADD,R3,R4,R5
ADD,R4,R5,#0
ADD,R5,R3,#0
ADD,R1,R1,#1
MOVC,R6,#0
BNZ,R6,#0016