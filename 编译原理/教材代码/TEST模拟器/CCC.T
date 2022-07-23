        LOADI 0
        STO 1
        LOADI 0
        STO 0
LABEL0:
        LOAD 0
        LOADI 5
        LES
        BRF LABEL1
        BR LABEL2
LABEL3:
        LOAD 0
        LOADI 1
        ADD
        STO 0
        BR LABEL0
LABEL2:
        LOAD 1
        LOADI 2
        ADD
        STO 1
        BR LABEL3
LABEL1:
        LOAD 0
        OUT
        LOAD 1
        OUT
        STOP
