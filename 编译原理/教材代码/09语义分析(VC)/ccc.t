        IN   
        STI   0
        LOAD 0
        OUT
        LOAD 0
        LOADI 10
        EQ
        BRF LABEL0
        LOADI 1
        STO 1
        BR LABEL1
LABEL0:
        LOADI 2
        STO 1
LABEL1:
        LOAD 1
        OUT
LABEL2:
        LOAD 0
        LOADI 6
        LE
        BRF LABEL3
        LOADI 3
        STO 1
        BR LABEL2
LABEL3:
        LOAD 1
        OUT
        LOADI 0
        STO 1
        LOADI 0
        STO 0
LABEL4:
        LOAD 0
        LOADI 5
        LES
        BRF LABEL5
        BR LABEL6
LABEL7:
        LOAD 0
        LOADI 1
        ADD
        STO 0
        BR LABEL4
LABEL6:
        LOADI 4
        STO 1
        BR LABEL7
LABEL5:
        LOAD 1
        OUT
        STOP
