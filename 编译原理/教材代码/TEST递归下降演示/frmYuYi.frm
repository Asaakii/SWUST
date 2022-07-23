VERSION 5.00
Begin VB.Form frmYuYI 
   AutoRedraw      =   -1  'True
   BackColor       =   &H0080FF80&
   Caption         =   "语 义 分 析 "
   ClientHeight    =   8310
   ClientLeft      =   165
   ClientTop       =   855
   ClientWidth     =   8880
   LinkTopic       =   "Form3"
   ScaleHeight     =   8310
   ScaleWidth      =   8880
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.ListBox lstToken 
      BackColor       =   &H000080FF&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   2220
      ItemData        =   "frmYuYi.frx":0000
      Left            =   120
      List            =   "frmYuYi.frx":001F
      TabIndex        =   16
      Top             =   600
      Width           =   2175
   End
   Begin VB.CommandButton parse 
      BackColor       =   &H000000FF&
      Caption         =   "开始"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2640
      Style           =   1  'Graphical
      TabIndex        =   15
      Top             =   120
      Width           =   855
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   255
      Left            =   120
      Max             =   2000
      TabIndex        =   14
      Top             =   3000
      Value           =   100
      Width           =   2055
   End
   Begin VB.CommandButton decllist 
      BackColor       =   &H00FF0000&
      Caption         =   "声明语句序列"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4080
      Style           =   1  'Graphical
      TabIndex        =   13
      Top             =   120
      Width           =   1455
   End
   Begin VB.CommandButton exprstat 
      BackColor       =   &H00FF0000&
      Caption         =   "表达式语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   120
      Style           =   1  'Graphical
      TabIndex        =   12
      Top             =   5640
      Width           =   1575
   End
   Begin VB.CommandButton expr 
      BackColor       =   &H00FF0000&
      Caption         =   "表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   2400
      Style           =   1  'Graphical
      TabIndex        =   11
      Top             =   5640
      Width           =   1335
   End
   Begin VB.CommandButton boolexpr 
      BackColor       =   &H00FF0000&
      Caption         =   "布尔表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   3960
      Style           =   1  'Graphical
      TabIndex        =   10
      Top             =   5640
      Width           =   1215
   End
   Begin VB.CommandButton addexpr 
      BackColor       =   &H00FF0000&
      Caption         =   "算术表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   5760
      Style           =   1  'Graphical
      TabIndex        =   9
      Top             =   5640
      Width           =   1215
   End
   Begin VB.CommandButton term 
      BackColor       =   &H00FF0000&
      Caption         =   "项表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   7560
      Style           =   1  'Graphical
      TabIndex        =   8
      Top             =   5640
      Width           =   975
   End
   Begin VB.CommandButton factor 
      BackColor       =   &H00FF0000&
      Caption         =   "因子表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   8880
      Style           =   1  'Graphical
      TabIndex        =   7
      Top             =   5640
      Width           =   1215
   End
   Begin VB.CommandButton if 
      BackColor       =   &H00FF0000&
      Caption         =   "IF语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   8160
      Style           =   1  'Graphical
      TabIndex        =   6
      Top             =   120
      Width           =   735
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   2040
      Top             =   0
   End
   Begin VB.CommandButton statlist 
      BackColor       =   &H00FF0000&
      Caption         =   "语句序列"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   6360
      Style           =   1  'Graphical
      TabIndex        =   5
      Top             =   120
      Width           =   1095
   End
   Begin VB.CommandButton stat 
      BackColor       =   &H00FF0000&
      Caption         =   "语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   6240
      Style           =   1  'Graphical
      TabIndex        =   4
      Top             =   1320
      Width           =   1215
   End
   Begin VB.CommandButton while 
      BackColor       =   &H00FF0000&
      Caption         =   "WHILE语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   9720
      Style           =   1  'Graphical
      TabIndex        =   3
      Top             =   120
      Width           =   1215
   End
   Begin VB.CommandButton compound 
      BackColor       =   &H000000FF&
      Caption         =   "复合语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   255
      Left            =   4320
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   3240
      Width           =   975
   End
   Begin VB.CommandButton read 
      BackColor       =   &H00C00000&
      Caption         =   "READ语句"
      Height          =   255
      Left            =   360
      Style           =   1  'Graphical
      TabIndex        =   1
      Top             =   3360
      Width           =   975
   End
   Begin VB.CommandButton write 
      BackColor       =   &H00C00000&
      Caption         =   "WRITE语句"
      Height          =   255
      Left            =   2520
      Style           =   1  'Graphical
      TabIndex        =   0
      Top             =   3720
      Width           =   1095
   End
   Begin VB.Label Label0 
      AutoSize        =   -1  'True
      BackColor       =   &H0080C0FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语法分析输入："
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   345
      Left            =   0
      TabIndex        =   171
      Top             =   120
      Width           =   2175
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   2760
      TabIndex        =   170
      Top             =   480
      Width           =   660
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是{？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   2760
      TabIndex        =   169
      Top             =   840
      Width           =   570
   End
   Begin VB.Label LabelStr 
      AutoSize        =   -1  'True
      BackColor       =   &H0000FFFF&
      Caption         =   " "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Left            =   1680
      TabIndex        =   168
      Top             =   0
      Visible         =   0   'False
      Width           =   150
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   2640
      TabIndex        =   167
      Top             =   1200
      Width           =   660
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是}？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   2640
      TabIndex        =   166
      Top             =   2280
      Width           =   570
   End
   Begin VB.Line Line1 
      Index           =   0
      X1              =   3000
      X2              =   3000
      Y1              =   240
      Y2              =   600
   End
   Begin VB.Line Line1 
      Index           =   1
      X1              =   3000
      X2              =   3000
      Y1              =   600
      Y2              =   840
   End
   Begin VB.Line Line1 
      Index           =   2
      X1              =   3000
      X2              =   3000
      Y1              =   960
      Y2              =   1320
   End
   Begin VB.Line Line1 
      Index           =   3
      X1              =   3000
      X2              =   3000
      Y1              =   1320
      Y2              =   1680
   End
   Begin VB.Line Line1 
      Index           =   7
      X1              =   3000
      X2              =   3840
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Line Line1 
      Index           =   9
      X1              =   3000
      X2              =   3840
      Y1              =   2400
      Y2              =   2400
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   7
      Left            =   3600
      TabIndex        =   165
      Top             =   1320
      Width           =   465
   End
   Begin VB.Line Line1 
      Index           =   10
      X1              =   3840
      X2              =   3840
      Y1              =   2400
      Y2              =   1440
   End
   Begin VB.Line Line1 
      Index           =   8
      X1              =   3840
      X2              =   3840
      Y1              =   960
      Y2              =   1440
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "结束"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   6
      Left            =   2760
      TabIndex        =   164
      Top             =   2760
      Width           =   465
   End
   Begin VB.Line Line1 
      Index           =   5
      X1              =   3000
      X2              =   3000
      Y1              =   2040
      Y2              =   2400
   End
   Begin VB.Line Line1 
      Index           =   4
      X1              =   3000
      X2              =   3000
      Y1              =   1680
      Y2              =   2040
   End
   Begin VB.Label N1 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   0
      Left            =   3360
      TabIndex        =   163
      Top             =   960
      Width           =   90
   End
   Begin VB.Label N1 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   1
      Left            =   3240
      TabIndex        =   162
      Top             =   2280
      Width           =   90
   End
   Begin VB.Label Y1 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   0
      Left            =   3120
      TabIndex        =   161
      Top             =   1080
      Width           =   90
   End
   Begin VB.Label Y1 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   1
      Left            =   3000
      TabIndex        =   160
      Top             =   2520
      Width           =   90
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "声明语句序列"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   2400
      TabIndex        =   159
      Top             =   1560
      Width           =   1245
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是int？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   4440
      TabIndex        =   158
      Top             =   480
      Width           =   780
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   4560
      TabIndex        =   157
      Top             =   960
      Width           =   660
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是标识符？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   4320
      TabIndex        =   156
      Top             =   1320
      Width           =   1050
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   4560
      TabIndex        =   155
      Top             =   1800
      Width           =   660
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是；？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   4560
      TabIndex        =   154
      Top             =   2160
      Width           =   660
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   9120
      TabIndex        =   153
      Top             =   6480
      Width           =   660
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   7
      Left            =   5520
      TabIndex        =   152
      Top             =   1320
      Width           =   465
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   6
      Left            =   5520
      TabIndex        =   151
      Top             =   480
      Width           =   465
   End
   Begin VB.Line Line2 
      Index           =   0
      X1              =   4800
      X2              =   4800
      Y1              =   240
      Y2              =   720
   End
   Begin VB.Line Line2 
      Index           =   1
      X1              =   4800
      X2              =   4800
      Y1              =   720
      Y2              =   1080
   End
   Begin VB.Line Line2 
      Index           =   2
      X1              =   4800
      X2              =   4800
      Y1              =   1080
      Y2              =   1320
   End
   Begin VB.Line Line2 
      Index           =   3
      X1              =   4800
      X2              =   4800
      Y1              =   1440
      Y2              =   1920
   End
   Begin VB.Line Line2 
      Index           =   4
      X1              =   4800
      X2              =   4800
      Y1              =   1920
      Y2              =   2280
   End
   Begin VB.Line Line2 
      Index           =   5
      X1              =   4800
      X2              =   4800
      Y1              =   2280
      Y2              =   2760
   End
   Begin VB.Line Line2 
      Index           =   11
      X1              =   4800
      X2              =   5760
      Y1              =   600
      Y2              =   600
   End
   Begin VB.Line Line2 
      Index           =   8
      X1              =   4800
      X2              =   5760
      Y1              =   1440
      Y2              =   1440
   End
   Begin VB.Line Line2 
      Index           =   10
      X1              =   4200
      X2              =   4800
      Y1              =   600
      Y2              =   600
   End
   Begin VB.Label N2 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   0
      Left            =   5280
      TabIndex        =   150
      Top             =   360
      Width           =   90
   End
   Begin VB.Label N2 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   1
      Left            =   5400
      TabIndex        =   149
      Top             =   1200
      Width           =   90
   End
   Begin VB.Label N2 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   2
      Left            =   5400
      TabIndex        =   148
      Top             =   2040
      Width           =   90
   End
   Begin VB.Label Y2 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   2
      Left            =   4920
      TabIndex        =   147
      Top             =   2400
      Width           =   90
   End
   Begin VB.Label Y2 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   1
      Left            =   4920
      TabIndex        =   146
      Top             =   1560
      Width           =   90
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   480
      TabIndex        =   145
      Top             =   6480
      Width           =   660
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是；？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   360
      TabIndex        =   144
      Top             =   6840
      Width           =   660
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   480
      TabIndex        =   143
      Top             =   7800
      Width           =   465
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   360
      TabIndex        =   142
      Top             =   7320
      Width           =   660
   End
   Begin VB.Line Line6 
      Index           =   0
      X1              =   840
      X2              =   840
      Y1              =   6480
      Y2              =   6240
   End
   Begin VB.Line Line6 
      Index           =   1
      X1              =   840
      X2              =   840
      Y1              =   6600
      Y2              =   6960
   End
   Begin VB.Line Line6 
      Index           =   2
      X1              =   840
      X2              =   840
      Y1              =   6960
      Y2              =   7440
   End
   Begin VB.Line Line6 
      Index           =   3
      X1              =   840
      X2              =   840
      Y1              =   7440
      Y2              =   7920
   End
   Begin VB.Line Line6 
      Index           =   4
      X1              =   840
      X2              =   1440
      Y1              =   6960
      Y2              =   6960
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   1200
      TabIndex        =   141
      Top             =   6840
      Width           =   465
   End
   Begin VB.Label Y6 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   1
      Left            =   960
      TabIndex        =   140
      Top             =   7080
      Width           =   90
   End
   Begin VB.Label N6 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   1
      Left            =   1200
      TabIndex        =   139
      Top             =   6720
      Width           =   90
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "看下一个符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   2400
      TabIndex        =   138
      Top             =   6000
      Width           =   1245
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "下一个是=？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   2400
      TabIndex        =   137
      Top             =   6360
      Width           =   1155
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "布尔表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   2520
      TabIndex        =   136
      Top             =   7800
      Width           =   1050
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "标识符？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   2520
      TabIndex        =   135
      Top             =   6840
      Width           =   855
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读2个符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   2520
      TabIndex        =   134
      Top             =   7320
      Width           =   960
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   42
      Left            =   1800
      TabIndex        =   133
      Top             =   6840
      Width           =   465
   End
   Begin VB.Label Label7 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   2760
      TabIndex        =   132
      Top             =   8160
      Width           =   465
   End
   Begin VB.Line Line7 
      Index           =   0
      X1              =   3000
      X2              =   3000
      Y1              =   5760
      Y2              =   6120
   End
   Begin VB.Line Line7 
      Index           =   1
      X1              =   3000
      X2              =   3000
      Y1              =   6120
      Y2              =   6480
   End
   Begin VB.Line Line7 
      Index           =   2
      X1              =   3000
      X2              =   3000
      Y1              =   6480
      Y2              =   6960
   End
   Begin VB.Line Line7 
      Index           =   3
      X1              =   3000
      X2              =   3000
      Y1              =   6960
      Y2              =   7440
   End
   Begin VB.Line Line7 
      Index           =   4
      X1              =   3000
      X2              =   3000
      Y1              =   7440
      Y2              =   7920
   End
   Begin VB.Line Line7 
      Index           =   5
      X1              =   3000
      X2              =   3000
      Y1              =   7920
      Y2              =   8280
   End
   Begin VB.Line Line7 
      Index           =   9
      X1              =   3000
      X2              =   2280
      Y1              =   6960
      Y2              =   6960
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "算术表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   4080
      TabIndex        =   131
      Top             =   6120
      Width           =   1050
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是比较符？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   3960
      TabIndex        =   130
      Top             =   6600
      Width           =   1050
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   4200
      TabIndex        =   129
      Top             =   7080
      Width           =   660
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "算术表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   4080
      TabIndex        =   128
      Top             =   7560
      Width           =   1050
   End
   Begin VB.Label Label8 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   4320
      TabIndex        =   127
      Top             =   8040
      Width           =   465
   End
   Begin VB.Line Line8 
      Index           =   0
      X1              =   4560
      X2              =   4560
      Y1              =   5760
      Y2              =   6240
   End
   Begin VB.Line Line8 
      Index           =   1
      X1              =   4560
      X2              =   4560
      Y1              =   6240
      Y2              =   6720
   End
   Begin VB.Line Line8 
      Index           =   2
      X1              =   4560
      X2              =   4560
      Y1              =   6720
      Y2              =   7200
   End
   Begin VB.Line Line8 
      Index           =   3
      X1              =   4560
      X2              =   4560
      Y1              =   7200
      Y2              =   7680
   End
   Begin VB.Line Line8 
      Index           =   4
      X1              =   4560
      X2              =   4560
      Y1              =   7680
      Y2              =   8160
   End
   Begin VB.Line Line8 
      Index           =   5
      X1              =   4560
      X2              =   5400
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Line Line8 
      Index           =   6
      X1              =   5400
      X2              =   5400
      Y1              =   6720
      Y2              =   8160
   End
   Begin VB.Line Line8 
      Index           =   7
      X1              =   5400
      X2              =   4560
      Y1              =   8160
      Y2              =   8160
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "项表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   5880
      TabIndex        =   126
      Top             =   6120
      Width           =   855
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是+、-？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   5760
      TabIndex        =   125
      Top             =   6600
      Width           =   870
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   6000
      TabIndex        =   124
      Top             =   7080
      Width           =   660
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "项表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   5880
      TabIndex        =   123
      Top             =   7560
      Width           =   855
   End
   Begin VB.Label Label9 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   6120
      TabIndex        =   122
      Top             =   8040
      Width           =   465
   End
   Begin VB.Line Line9 
      Index           =   0
      X1              =   6360
      X2              =   6360
      Y1              =   5640
      Y2              =   6240
   End
   Begin VB.Line Line9 
      Index           =   1
      X1              =   6360
      X2              =   6360
      Y1              =   6240
      Y2              =   6720
   End
   Begin VB.Line Line9 
      Index           =   2
      X1              =   6360
      X2              =   6360
      Y1              =   6720
      Y2              =   7200
   End
   Begin VB.Line Line9 
      Index           =   9
      X1              =   6360
      X2              =   6360
      Y1              =   7200
      Y2              =   7680
   End
   Begin VB.Line Line9 
      Index           =   3
      X1              =   6360
      X2              =   5640
      Y1              =   7680
      Y2              =   7680
   End
   Begin VB.Line Line9 
      Index           =   6
      X1              =   6360
      X2              =   7080
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Line Line9 
      Index           =   7
      X1              =   7080
      X2              =   7080
      Y1              =   6720
      Y2              =   8160
   End
   Begin VB.Line Line9 
      Index           =   8
      X1              =   7080
      X2              =   6360
      Y1              =   8160
      Y2              =   8160
   End
   Begin VB.Line Line9 
      Index           =   4
      X1              =   5640
      X2              =   5640
      Y1              =   7680
      Y2              =   6720
   End
   Begin VB.Line Line9 
      Index           =   5
      X1              =   5640
      X2              =   6360
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "因子表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   7440
      TabIndex        =   121
      Top             =   6120
      Width           =   1050
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是*、/？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   7440
      TabIndex        =   120
      Top             =   6600
      Width           =   870
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   7680
      TabIndex        =   119
      Top             =   7080
      Width           =   660
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "因子表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   7440
      TabIndex        =   118
      Top             =   7560
      Width           =   1050
   End
   Begin VB.Label Label10 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   7800
      TabIndex        =   117
      Top             =   8040
      Width           =   465
   End
   Begin VB.Line Line10 
      Index           =   0
      X1              =   8040
      X2              =   8040
      Y1              =   5760
      Y2              =   6240
   End
   Begin VB.Line Line10 
      Index           =   1
      X1              =   8040
      X2              =   8040
      Y1              =   6240
      Y2              =   6720
   End
   Begin VB.Line Line10 
      Index           =   2
      X1              =   8040
      X2              =   8040
      Y1              =   6720
      Y2              =   7200
   End
   Begin VB.Line Line10 
      Index           =   9
      X1              =   8040
      X2              =   8040
      Y1              =   7200
      Y2              =   7680
   End
   Begin VB.Line Line10 
      Index           =   3
      X1              =   8040
      X2              =   7320
      Y1              =   7680
      Y2              =   7680
   End
   Begin VB.Line Line10 
      Index           =   6
      X1              =   8040
      X2              =   8760
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Line Line10 
      Index           =   7
      X1              =   8760
      X2              =   8760
      Y1              =   6720
      Y2              =   8160
   End
   Begin VB.Line Line10 
      Index           =   8
      X1              =   8760
      X2              =   8040
      Y1              =   8160
      Y2              =   8160
   End
   Begin VB.Line Line10 
      Index           =   4
      X1              =   7320
      X2              =   7320
      Y1              =   7680
      Y2              =   6720
   End
   Begin VB.Line Line10 
      Index           =   5
      X1              =   7320
      X2              =   8040
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是（？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   9120
      TabIndex        =   116
      Top             =   6000
      Width           =   660
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   9120
      TabIndex        =   115
      Top             =   6840
      Width           =   660
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   9120
      TabIndex        =   114
      Top             =   7680
      Width           =   660
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是）？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   9120
      TabIndex        =   113
      Top             =   7200
      Width           =   660
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   9240
      TabIndex        =   112
      Top             =   8040
      Width           =   465
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是整数？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   7
      Left            =   10080
      TabIndex        =   111
      Top             =   6600
      Width           =   855
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是标识符？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   6
      Left            =   10080
      TabIndex        =   110
      Top             =   6000
      Width           =   1050
   End
   Begin VB.Line Line11 
      Index           =   0
      X1              =   9480
      X2              =   9480
      Y1              =   5760
      Y2              =   6120
   End
   Begin VB.Line Line11 
      Index           =   1
      X1              =   9480
      X2              =   9480
      Y1              =   6120
      Y2              =   6600
   End
   Begin VB.Line Line11 
      Index           =   2
      X1              =   9480
      X2              =   9480
      Y1              =   6600
      Y2              =   6960
   End
   Begin VB.Line Line11 
      Index           =   3
      X1              =   9480
      X2              =   9480
      Y1              =   6960
      Y2              =   7320
   End
   Begin VB.Line Line11 
      Index           =   4
      X1              =   9480
      X2              =   9480
      Y1              =   7320
      Y2              =   7800
   End
   Begin VB.Line Line11 
      Index           =   5
      X1              =   9480
      X2              =   9480
      Y1              =   7800
      Y2              =   8160
   End
   Begin VB.Line Line11 
      Index           =   6
      X1              =   9480
      X2              =   10680
      Y1              =   6120
      Y2              =   6120
   End
   Begin VB.Line Line11 
      Index           =   7
      X1              =   10560
      X2              =   10560
      Y1              =   6120
      Y2              =   6720
   End
   Begin VB.Line Line11 
      Index           =   10
      X1              =   10560
      X2              =   11280
      Y1              =   6120
      Y2              =   6120
   End
   Begin VB.Line Line11 
      Index           =   11
      X1              =   11280
      X2              =   11280
      Y1              =   6120
      Y2              =   6720
   End
   Begin VB.Line Line11 
      Index           =   13
      X1              =   11280
      X2              =   11280
      Y1              =   6720
      Y2              =   7800
   End
   Begin VB.Line Line11 
      Index           =   14
      X1              =   11280
      X2              =   9480
      Y1              =   7800
      Y2              =   7800
   End
   Begin VB.Line Line11 
      Index           =   12
      X1              =   10560
      X2              =   11280
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Label Label11 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   8
      Left            =   10320
      TabIndex        =   109
      Top             =   7200
      Width           =   465
   End
   Begin VB.Line Line11 
      Index           =   9
      X1              =   9600
      X2              =   10680
      Y1              =   7320
      Y2              =   7320
   End
   Begin VB.Line Line11 
      Index           =   8
      X1              =   10560
      X2              =   10560
      Y1              =   7200
      Y2              =   6720
   End
   Begin VB.Label N8 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   17
      Left            =   5280
      TabIndex        =   108
      Top             =   6480
      Width           =   90
   End
   Begin VB.Label N7 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   1
      Left            =   2280
      TabIndex        =   107
      Top             =   6720
      Width           =   90
   End
   Begin VB.Label N11 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   19
      Left            =   9960
      TabIndex        =   106
      Top             =   6000
      Width           =   90
   End
   Begin VB.Label N9 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   20
      Left            =   6960
      TabIndex        =   105
      Top             =   6480
      Width           =   90
   End
   Begin VB.Label Y7 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   0
      Left            =   3120
      TabIndex        =   104
      Top             =   6720
      Width           =   90
   End
   Begin VB.Label N11 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   22
      Left            =   10680
      TabIndex        =   103
      Top             =   6840
      Width           =   90
   End
   Begin VB.Label N11 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   23
      Left            =   9960
      TabIndex        =   102
      Top             =   7080
      Width           =   90
   End
   Begin VB.Label N7 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   0
      Left            =   3720
      TabIndex        =   101
      Top             =   6240
      Width           =   90
   End
   Begin VB.Label N11 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   25
      Left            =   10680
      TabIndex        =   100
      Top             =   6360
      Width           =   90
   End
   Begin VB.Label N10 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   26
      Left            =   8520
      TabIndex        =   99
      Top             =   6480
      Width           =   90
   End
   Begin VB.Line Line7 
      Index           =   8
      X1              =   3000
      X2              =   3840
      Y1              =   6480
      Y2              =   6480
   End
   Begin VB.Line Line7 
      Index           =   7
      X1              =   3840
      X2              =   3840
      Y1              =   6480
      Y2              =   7920
   End
   Begin VB.Line Line7 
      Index           =   6
      X1              =   3840
      X2              =   3000
      Y1              =   7920
      Y2              =   7920
   End
   Begin VB.Label Y7 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   1
      Left            =   3120
      TabIndex        =   98
      Top             =   7200
      Width           =   90
   End
   Begin VB.Label Y8 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   28
      Left            =   4680
      TabIndex        =   97
      Top             =   6840
      Width           =   90
   End
   Begin VB.Label Y9 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   29
      Left            =   6480
      TabIndex        =   96
      Top             =   6840
      Width           =   90
   End
   Begin VB.Label Y10 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   30
      Left            =   8160
      TabIndex        =   95
      Top             =   6840
      Width           =   90
   End
   Begin VB.Label Y11 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   31
      Left            =   10920
      TabIndex        =   94
      Top             =   6600
      Width           =   90
   End
   Begin VB.Label Y11 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   33
      Left            =   9600
      TabIndex        =   93
      Top             =   7440
      Width           =   90
   End
   Begin VB.Label Y11 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   34
      Left            =   9480
      TabIndex        =   92
      Top             =   6240
      Width           =   90
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是(？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   8280
      TabIndex        =   91
      Top             =   840
      Width           =   570
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   8160
      TabIndex        =   90
      Top             =   480
      Width           =   660
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   8160
      TabIndex        =   89
      Top             =   1320
      Width           =   660
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   8160
      TabIndex        =   88
      Top             =   1680
      Width           =   660
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是)？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   8160
      TabIndex        =   87
      Top             =   2040
      Width           =   570
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   8160
      TabIndex        =   86
      Top             =   2520
      Width           =   660
   End
   Begin VB.Line Line4 
      Index           =   0
      X1              =   8520
      X2              =   8520
      Y1              =   240
      Y2              =   600
   End
   Begin VB.Line Line4 
      Index           =   5
      X1              =   8520
      X2              =   8520
      Y1              =   2160
      Y2              =   2640
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是else？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   7
      Left            =   8040
      TabIndex        =   85
      Top             =   3240
      Width           =   885
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   6
      Left            =   8280
      TabIndex        =   84
      Top             =   2880
      Width           =   465
   End
   Begin VB.Line Line4 
      Index           =   7
      X1              =   8520
      X2              =   8520
      Y1              =   3000
      Y2              =   3360
   End
   Begin VB.Line Line4 
      Index           =   8
      X1              =   8520
      X2              =   8520
      Y1              =   3360
      Y2              =   3720
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   9
      Left            =   8280
      TabIndex        =   83
      Top             =   4080
      Width           =   465
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   10
      Left            =   8280
      TabIndex        =   82
      Top             =   4440
      Width           =   465
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   8
      Left            =   8160
      TabIndex        =   81
      Top             =   3720
      Width           =   660
   End
   Begin VB.Label N4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   2
      Left            =   9120
      TabIndex        =   80
      Top             =   3120
      Width           =   90
   End
   Begin VB.Label Y4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   2
      Left            =   8640
      TabIndex        =   79
      Top             =   3480
      Width           =   90
   End
   Begin VB.Label Y4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   1
      Left            =   8400
      TabIndex        =   78
      Top             =   2280
      Width           =   90
   End
   Begin VB.Label Y4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   0
      Left            =   8400
      TabIndex        =   77
      Top             =   1080
      Width           =   90
   End
   Begin VB.Line Line4 
      Index           =   11
      X1              =   8640
      X2              =   9360
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   11
      Left            =   9120
      TabIndex        =   76
      Top             =   2040
      Width           =   465
   End
   Begin VB.Line Line4 
      Index           =   12
      X1              =   9360
      X2              =   9360
      Y1              =   960
      Y2              =   2160
   End
   Begin VB.Line Line4 
      Index           =   13
      X1              =   8640
      X2              =   9360
      Y1              =   2160
      Y2              =   2160
   End
   Begin VB.Label N4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   0
      Left            =   9000
      TabIndex        =   75
      Top             =   720
      Width           =   90
   End
   Begin VB.Label N4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   1
      Left            =   8880
      TabIndex        =   74
      Top             =   2040
      Width           =   90
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   4560
      TabIndex        =   73
      Top             =   2640
      Width           =   660
   End
   Begin VB.Line Line2 
      Index           =   6
      X1              =   4800
      X2              =   4200
      Y1              =   2760
      Y2              =   2760
   End
   Begin VB.Line Line2 
      Index           =   7
      X1              =   4200
      X2              =   4200
      Y1              =   2760
      Y2              =   600
   End
   Begin VB.Line Line2 
      Index           =   9
      X1              =   4800
      X2              =   5760
      Y1              =   2280
      Y2              =   2280
   End
   Begin VB.Line Line2 
      Index           =   12
      X1              =   5760
      X2              =   5760
      Y1              =   2280
      Y2              =   1440
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "表达式语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   6435
      TabIndex        =   72
      Top             =   1680
      Width           =   1065
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "IF语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   6480
      TabIndex        =   71
      Top             =   2040
      Width           =   705
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "WHILE语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   6435
      TabIndex        =   70
      Top             =   2400
      Width           =   1005
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "FOR语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   6420
      TabIndex        =   69
      Top             =   2760
      Width           =   795
   End
   Begin VB.Line Line1 
      Index           =   11
      X1              =   0
      X2              =   0
      Y1              =   0
      Y2              =   480
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句序列"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   2640
      TabIndex        =   68
      Top             =   1920
      Width           =   855
   End
   Begin VB.Line Line1 
      Index           =   6
      X1              =   3000
      X2              =   3000
      Y1              =   2400
      Y2              =   2760
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "READ语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   6420
      TabIndex        =   67
      Top             =   3480
      Width           =   915
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "WRITE语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   6435
      TabIndex        =   66
      Top             =   3120
      Width           =   1005
   End
   Begin VB.Line Line3 
      Index           =   0
      X1              =   6240
      X2              =   6240
      Y1              =   1440
      Y2              =   1800
   End
   Begin VB.Line Line3 
      Index           =   8
      X1              =   6240
      X2              =   6480
      Y1              =   1800
      Y2              =   1800
   End
   Begin VB.Line Line3 
      Index           =   9
      X1              =   6240
      X2              =   6480
      Y1              =   2160
      Y2              =   2160
   End
   Begin VB.Line Line3 
      Index           =   10
      X1              =   6240
      X2              =   6480
      Y1              =   2520
      Y2              =   2520
   End
   Begin VB.Line Line3 
      Index           =   11
      X1              =   6240
      X2              =   6480
      Y1              =   2880
      Y2              =   2880
   End
   Begin VB.Line Line3 
      Index           =   12
      X1              =   6240
      X2              =   6480
      Y1              =   3240
      Y2              =   3240
   End
   Begin VB.Line Line3 
      Index           =   13
      X1              =   6240
      X2              =   6480
      Y1              =   3600
      Y2              =   3600
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   6
      Left            =   6390
      TabIndex        =   65
      Top             =   4200
      Width           =   495
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "复合语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   7
      Left            =   6420
      TabIndex        =   64
      Top             =   3840
      Width           =   885
   End
   Begin VB.Line Line3 
      Index           =   14
      X1              =   6240
      X2              =   6480
      Y1              =   3960
      Y2              =   3960
   End
   Begin VB.Line Line3 
      Index           =   15
      X1              =   6240
      X2              =   6480
      Y1              =   4320
      Y2              =   4320
   End
   Begin VB.Line Line3 
      Index           =   16
      X1              =   7440
      X2              =   7680
      Y1              =   1800
      Y2              =   1800
   End
   Begin VB.Line Line3 
      Index           =   17
      X1              =   6960
      X2              =   7680
      Y1              =   2160
      Y2              =   2160
   End
   Begin VB.Line Line3 
      Index           =   18
      X1              =   7440
      X2              =   7680
      Y1              =   2520
      Y2              =   2520
   End
   Begin VB.Line Line3 
      Index           =   19
      X1              =   7080
      X2              =   7680
      Y1              =   2880
      Y2              =   2880
   End
   Begin VB.Line Line3 
      Index           =   20
      X1              =   7440
      X2              =   7680
      Y1              =   3240
      Y2              =   3240
   End
   Begin VB.Line Line3 
      Index           =   21
      X1              =   7320
      X2              =   7680
      Y1              =   3600
      Y2              =   3600
   End
   Begin VB.Line Line3 
      Index           =   22
      X1              =   7200
      X2              =   7680
      Y1              =   3960
      Y2              =   3960
   End
   Begin VB.Line Line3 
      Index           =   23
      X1              =   7680
      X2              =   7680
      Y1              =   3600
      Y2              =   3960
   End
   Begin VB.Line Line3 
      Index           =   24
      X1              =   7680
      X2              =   7680
      Y1              =   3240
      Y2              =   3600
   End
   Begin VB.Line Line3 
      Index           =   25
      X1              =   7680
      X2              =   7680
      Y1              =   2880
      Y2              =   3240
   End
   Begin VB.Line Line3 
      Index           =   26
      X1              =   7680
      X2              =   7680
      Y1              =   2520
      Y2              =   2880
   End
   Begin VB.Line Line3 
      Index           =   27
      X1              =   7680
      X2              =   7680
      Y1              =   2160
      Y2              =   2520
   End
   Begin VB.Line Line3 
      Index           =   28
      X1              =   7680
      X2              =   7680
      Y1              =   1800
      Y2              =   2160
   End
   Begin VB.Line Line3 
      Index           =   1
      X1              =   6240
      X2              =   6240
      Y1              =   1800
      Y2              =   2160
   End
   Begin VB.Line Line3 
      Index           =   2
      X1              =   6240
      X2              =   6240
      Y1              =   2160
      Y2              =   2520
   End
   Begin VB.Line Line3 
      Index           =   3
      X1              =   6240
      X2              =   6240
      Y1              =   2520
      Y2              =   2880
   End
   Begin VB.Line Line3 
      Index           =   4
      X1              =   6240
      X2              =   6240
      Y1              =   2880
      Y2              =   3240
   End
   Begin VB.Line Line3 
      Index           =   5
      X1              =   6240
      X2              =   6240
      Y1              =   3240
      Y2              =   3600
   End
   Begin VB.Line Line3 
      Index           =   6
      X1              =   6240
      X2              =   6240
      Y1              =   3600
      Y2              =   3960
   End
   Begin VB.Line Line3 
      Index           =   7
      X1              =   6240
      X2              =   6240
      Y1              =   3960
      Y2              =   4320
   End
   Begin VB.Label Y2 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   0
      Left            =   4920
      TabIndex        =   63
      Top             =   720
      Width           =   90
   End
   Begin VB.Line Line4 
      Index           =   15
      X1              =   8520
      X2              =   9480
      Y1              =   3360
      Y2              =   3360
   End
   Begin VB.Line Line4 
      Index           =   16
      X1              =   9480
      X2              =   9480
      Y1              =   3360
      Y2              =   4560
   End
   Begin VB.Line Line4 
      Index           =   14
      X1              =   9480
      X2              =   8520
      Y1              =   4560
      Y2              =   4560
   End
   Begin VB.Line Line4 
      Index           =   9
      X1              =   8520
      X2              =   8520
      Y1              =   3840
      Y2              =   4200
   End
   Begin VB.Line Line4 
      Index           =   10
      X1              =   8520
      X2              =   8520
      Y1              =   4200
      Y2              =   4560
   End
   Begin VB.Line Line4 
      Index           =   1
      X1              =   8520
      X2              =   8520
      Y1              =   600
      Y2              =   960
   End
   Begin VB.Line Line4 
      Index           =   2
      X1              =   8520
      X2              =   8520
      Y1              =   960
      Y2              =   1440
   End
   Begin VB.Line Line4 
      Index           =   3
      X1              =   8520
      X2              =   8520
      Y1              =   1440
      Y2              =   1800
   End
   Begin VB.Line Line4 
      Index           =   4
      X1              =   8520
      X2              =   8520
      Y1              =   1800
      Y2              =   2160
   End
   Begin VB.Line Line4 
      Index           =   6
      X1              =   8520
      X2              =   8520
      Y1              =   2640
      Y2              =   3000
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句？"
      Height          =   240
      Index           =   0
      Left            =   6480
      TabIndex        =   62
      Top             =   480
      Width           =   600
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句"
      Height          =   240
      Index           =   1
      Left            =   6600
      TabIndex        =   61
      Top             =   840
      Width           =   420
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      Height          =   240
      Index           =   2
      Left            =   7320
      TabIndex        =   60
      Top             =   480
      Width           =   420
   End
   Begin VB.Line Line5 
      Index           =   0
      X1              =   6840
      X2              =   6840
      Y1              =   240
      Y2              =   600
   End
   Begin VB.Line Line5 
      Index           =   1
      X1              =   6840
      X2              =   6840
      Y1              =   600
      Y2              =   960
   End
   Begin VB.Line Line5 
      Index           =   2
      X1              =   6840
      X2              =   6240
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Line Line5 
      Index           =   3
      X1              =   6240
      X2              =   6240
      Y1              =   960
      Y2              =   600
   End
   Begin VB.Line Line5 
      Index           =   4
      X1              =   6240
      X2              =   6840
      Y1              =   600
      Y2              =   600
   End
   Begin VB.Line Line5 
      Index           =   5
      X1              =   6840
      X2              =   7560
      Y1              =   600
      Y2              =   600
   End
   Begin VB.Label N5 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Left            =   7080
      TabIndex        =   59
      Top             =   480
      Width           =   90
   End
   Begin VB.Label Y5 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Left            =   6600
      TabIndex        =   58
      Top             =   720
      Width           =   90
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   8
      Left            =   7350
      TabIndex        =   57
      Top             =   4200
      Width           =   495
   End
   Begin VB.Line Line3 
      Index           =   29
      X1              =   7680
      X2              =   7680
      Y1              =   3960
      Y2              =   4320
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是；？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   480
      TabIndex        =   56
      Top             =   6120
      Width           =   660
   End
   Begin VB.Line Line6 
      Index           =   5
      X1              =   840
      X2              =   240
      Y1              =   6240
      Y2              =   6240
   End
   Begin VB.Line Line6 
      Index           =   6
      X1              =   240
      X2              =   240
      Y1              =   6240
      Y2              =   7440
   End
   Begin VB.Line Line6 
      Index           =   7
      X1              =   240
      X2              =   840
      Y1              =   7440
      Y2              =   7440
   End
   Begin VB.Line Line6 
      Index           =   8
      X1              =   840
      X2              =   840
      Y1              =   5760
      Y2              =   6240
   End
   Begin VB.Label N6 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   0
      Left            =   840
      TabIndex        =   55
      Top             =   6360
      Width           =   90
   End
   Begin VB.Label Y6 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   0
      Left            =   360
      TabIndex        =   54
      Top             =   6120
      Width           =   90
   End
   Begin VB.Label Y11 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   0
      Left            =   11160
      TabIndex        =   53
      Top             =   5880
      Width           =   90
   End
   Begin VB.Line Line12 
      Index           =   6
      X1              =   10320
      X2              =   10320
      Y1              =   2640
      Y2              =   3000
   End
   Begin VB.Line Line12 
      Index           =   4
      X1              =   10320
      X2              =   10320
      Y1              =   1800
      Y2              =   2160
   End
   Begin VB.Line Line12 
      Index           =   3
      X1              =   10320
      X2              =   10320
      Y1              =   1440
      Y2              =   1800
   End
   Begin VB.Line Line12 
      Index           =   2
      X1              =   10320
      X2              =   10320
      Y1              =   960
      Y2              =   1440
   End
   Begin VB.Line Line12 
      Index           =   1
      X1              =   10320
      X2              =   10320
      Y1              =   600
      Y2              =   960
   End
   Begin VB.Label N12 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   3
      Left            =   10680
      TabIndex        =   52
      Top             =   2040
      Width           =   90
   End
   Begin VB.Label N12 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   4
      Left            =   10800
      TabIndex        =   51
      Top             =   720
      Width           =   90
   End
   Begin VB.Line Line12 
      Index           =   10
      X1              =   10440
      X2              =   11160
      Y1              =   2160
      Y2              =   2160
   End
   Begin VB.Line Line12 
      Index           =   9
      X1              =   11160
      X2              =   11160
      Y1              =   960
      Y2              =   2160
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   8
      Left            =   10920
      TabIndex        =   50
      Top             =   2040
      Width           =   465
   End
   Begin VB.Line Line12 
      Index           =   8
      X1              =   10440
      X2              =   11160
      Y1              =   960
      Y2              =   960
   End
   Begin VB.Label Y12 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   3
      Left            =   10200
      TabIndex        =   49
      Top             =   1080
      Width           =   90
   End
   Begin VB.Label Y12 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   4
      Left            =   10200
      TabIndex        =   48
      Top             =   2280
      Width           =   90
   End
   Begin VB.Line Line12 
      Index           =   7
      X1              =   10320
      X2              =   10320
      Y1              =   3000
      Y2              =   3360
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   6
      Left            =   10080
      TabIndex        =   47
      Top             =   2880
      Width           =   465
   End
   Begin VB.Line Line12 
      Index           =   5
      X1              =   10320
      X2              =   10320
      Y1              =   2160
      Y2              =   2640
   End
   Begin VB.Line Line12 
      Index           =   0
      X1              =   10320
      X2              =   10320
      Y1              =   240
      Y2              =   600
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   9960
      TabIndex        =   46
      Top             =   2520
      Width           =   660
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是)？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   9960
      TabIndex        =   45
      Top             =   2040
      Width           =   570
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   9960
      TabIndex        =   44
      Top             =   1680
      Width           =   660
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   9960
      TabIndex        =   43
      Top             =   1320
      Width           =   660
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   9960
      TabIndex        =   42
      Top             =   480
      Width           =   660
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是(？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   10080
      TabIndex        =   41
      Top             =   840
      Width           =   570
   End
   Begin VB.Label Label12 
      AutoSize        =   -1  'True
      BackColor       =   &H000080FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   7
      Left            =   10080
      TabIndex        =   40
      Top             =   3240
      Width           =   465
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "语句序列"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   4320
      TabIndex        =   39
      Top             =   3960
      Width           =   855
   End
   Begin VB.Label Y13 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   2
      Left            =   4920
      TabIndex        =   38
      Top             =   4560
      Width           =   90
   End
   Begin VB.Label N13 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   2
      Left            =   5040
      TabIndex        =   37
      Top             =   4200
      Width           =   90
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "结束"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   4560
      TabIndex        =   36
      Top             =   5160
      Width           =   465
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   5400
      TabIndex        =   35
      Top             =   4320
      Width           =   465
   End
   Begin VB.Line Line13 
      Index           =   4
      X1              =   4800
      X2              =   5640
      Y1              =   4440
      Y2              =   4440
   End
   Begin VB.Line Line13 
      Index           =   3
      X1              =   4800
      X2              =   4800
      Y1              =   4440
      Y2              =   4920
   End
   Begin VB.Line Line13 
      Index           =   2
      X1              =   4800
      X2              =   4800
      Y1              =   4080
      Y2              =   4440
   End
   Begin VB.Line Line13 
      Index           =   1
      X1              =   4800
      X2              =   4800
      Y1              =   3720
      Y2              =   4080
   End
   Begin VB.Line Line13 
      Index           =   0
      X1              =   4800
      X2              =   4800
      Y1              =   3360
      Y2              =   3720
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是}？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   4440
      TabIndex        =   34
      Top             =   4320
      Width           =   570
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   4440
      TabIndex        =   33
      Top             =   3600
      Width           =   660
   End
   Begin VB.Label Label13 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   4440
      TabIndex        =   32
      Top             =   4800
      Width           =   660
   End
   Begin VB.Line Line13 
      Index           =   5
      X1              =   4800
      X2              =   4800
      Y1              =   4920
      Y2              =   5280
   End
   Begin VB.Line Line14 
      Index           =   7
      X1              =   2040
      X2              =   2040
      Y1              =   4920
      Y2              =   4320
   End
   Begin VB.Line Line14 
      Index           =   6
      X1              =   720
      X2              =   2040
      Y1              =   4920
      Y2              =   4920
   End
   Begin VB.Label Y14 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      Height          =   180
      Index           =   3
      Left            =   960
      TabIndex        =   31
      Top             =   4320
      Width           =   90
   End
   Begin VB.Label N14 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   3
      Left            =   1320
      TabIndex        =   30
      Top             =   4680
      Width           =   90
   End
   Begin VB.Label N14 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   4
      Left            =   1320
      TabIndex        =   29
      Top             =   3960
      Width           =   90
   End
   Begin VB.Line Line14 
      Index           =   5
      X1              =   720
      X2              =   1800
      Y1              =   4200
      Y2              =   4200
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   5
      Left            =   1680
      TabIndex        =   28
      Top             =   4080
      Width           =   465
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是；？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   480
      TabIndex        =   27
      Top             =   4800
      Width           =   660
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   480
      TabIndex        =   26
      Top             =   4440
      Width           =   660
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是标识符？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   240
      TabIndex        =   25
      Top             =   4080
      Width           =   1050
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   480
      TabIndex        =   24
      Top             =   3720
      Width           =   660
   End
   Begin VB.Label Label14 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   600
      TabIndex        =   23
      Top             =   5160
      Width           =   465
   End
   Begin VB.Line Line14 
      Index           =   0
      X1              =   840
      X2              =   840
      Y1              =   3480
      Y2              =   3840
   End
   Begin VB.Line Line14 
      Index           =   1
      X1              =   840
      X2              =   840
      Y1              =   3840
      Y2              =   4200
   End
   Begin VB.Line Line14 
      Index           =   2
      X1              =   840
      X2              =   840
      Y1              =   4200
      Y2              =   4560
   End
   Begin VB.Line Line14 
      Index           =   3
      X1              =   840
      X2              =   840
      Y1              =   4560
      Y2              =   4920
   End
   Begin VB.Line Line14 
      Index           =   4
      X1              =   840
      X2              =   840
      Y1              =   4920
      Y2              =   5280
   End
   Begin VB.Line Line15 
      Index           =   4
      X1              =   2880
      X2              =   3840
      Y1              =   4920
      Y2              =   4920
   End
   Begin VB.Label N14 
      AutoSize        =   -1  'True
      Caption         =   "N"
      Height          =   180
      Index           =   0
      Left            =   3480
      TabIndex        =   22
      Top             =   4680
      Width           =   90
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      BackColor       =   &H00C000C0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "错误"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   4
      Left            =   3600
      TabIndex        =   21
      Top             =   4800
      Width           =   465
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是；？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   2
      Left            =   2640
      TabIndex        =   20
      Top             =   4800
      Width           =   660
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "表达式"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   1
      Left            =   2640
      TabIndex        =   19
      Top             =   4440
      Width           =   660
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   0
      Left            =   2640
      TabIndex        =   18
      Top             =   4080
      Width           =   660
   End
   Begin VB.Label Label15 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF00&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "返回"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   9
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   240
      Index           =   3
      Left            =   2760
      TabIndex        =   17
      Top             =   5160
      Width           =   465
   End
   Begin VB.Line Line15 
      Index           =   0
      X1              =   3000
      X2              =   3000
      Y1              =   3840
      Y2              =   4200
   End
   Begin VB.Line Line15 
      Index           =   1
      X1              =   3000
      X2              =   3000
      Y1              =   4200
      Y2              =   4560
   End
   Begin VB.Line Line15 
      Index           =   2
      X1              =   3000
      X2              =   3000
      Y1              =   4560
      Y2              =   4920
   End
   Begin VB.Line Line15 
      Index           =   3
      X1              =   3000
      X2              =   3000
      Y1              =   4920
      Y2              =   5280
   End
   Begin VB.Menu mnu0 
      Caption         =   "词法规则"
   End
   Begin VB.Menu mnu1 
      Caption         =   "语法规则"
   End
   Begin VB.Menu mnu3 
      Caption         =   "语义规则"
   End
   Begin VB.Menu mnu2 
      Caption         =   "抽象机指令"
   End
   Begin VB.Menu mnu4 
      Caption         =   "代码输出"
   End
   Begin VB.Menu mnuCiFa 
      Caption         =   "词法分析"
   End
   Begin VB.Menu mnuYuFa 
      Caption         =   "语法分析"
   End
   Begin VB.Menu mnuEnd 
      Caption         =   "结束"
   End
End
Attribute VB_Name = "frmYuYI"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim i As Integer
Dim err As Integer
Dim s As Long
Dim varTablep As Integer
Dim datap As Integer
Dim codep As Integer
Dim labelp As Integer
Dim labelValue As String









Private Sub comEnd_Click()
End
End Sub




Private Sub mnu0_Click()
frmCiFaRules.Show
End Sub

Private Sub mnuCiFa_Click()
Unload Me
frmCiFa.Show
End Sub

Private Sub mnuEnd_Click()
End
End Sub

Private Sub mnuYuFa_Click()
Unload Me
frmYuFa.Show
End Sub

Private Sub read_Click()
Dim address As Integer
MoveStr Line14(0)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line14(1)
If LabelStr <> "ID" Then
    MoveStr Line14(5)
    err = 8
    MsgBox "缺少标识符"
    Exit Sub
End If
'查符号表
labelValue = Trim$(Right$(lstToken.List(i), Len(lstToken.List(i)) - 4))
address = LookvarTable(labelValue)
If address < 0 Then
    err = 22
    MsgBox "变量" & labelValue & "没有声明"
    Exit Sub
End If
frmOutput.lstCode.AddItem "        IN     "  '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
frmOutput.lstCode.AddItem "        STI    " & address '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line14(2)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line14(3)
If LabelStr <> ";" Then
    MoveStr Line14(6)
    MoveStr Line14(7)
    err = 3
    MsgBox "缺少分号——；"
    Exit Sub
End If
MoveStr Line14(4)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
End Sub

Private Sub compound_Click()
MoveStr Line13(0)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line13(1)
statlist_Click '调语句序列
MoveStr Line13(2)
If LabelStr <> "}" Then
   MoveStr Line13(4)
   err = 2
   MsgBox "缺少右括号——}"
   Exit Sub
End If
MoveStr Line13(3)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line1(5)
End Sub

Private Sub parse_Click() '主程序处理
frmOutput.lstCode.Clear
frmOutput.run.Enabled = False
err = 0
LabelStr.Visible = True
MoveStr Line1(0)
i = 0 '读第一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line1(1)
If LabelStr <> "{" Then
   MoveStr Line1(7)
   MoveStr Line1(8)
   err = 1
   MsgBox "缺少左括号——{"
   Exit Sub
End If
MoveStr Line1(2)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line1(3)
decllist_Click '调声明语句序列
MoveStr Line1(4)
statlist_Click '调语句序列
MoveStr Line1(5)
If err = 0 And LabelStr <> "}" Then
   MoveStr Line1(9)
   MoveStr Line1(10)
   err = 2
   MsgBox "缺少右括号——}"
   Exit Sub
End If
frmOutput.lstCode.AddItem "        STOP   " '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line1(6)
If err = 0 Then MsgBox "语法语义分析成功！"
LabelStr.Visible = False
frmOutput.run.Enabled = True
Beep
End Sub

Private Sub factor_Click()
MoveStr Line11(0)
If LabelStr = "(" Then
    MoveStr Line11(1)
    i = i + 1: lstToken.ListIndex = i '读下一个符号
    LabelStr = Left$(lstToken.List(i), 2)
    MoveStr Line11(2)
    expr_Click
    If err > 0 Then Exit Sub
    MoveStr Line11(3)
    If LabelStr = ")" Then
        MoveStr Line11(4)
    Else
        MoveStr Line11(9)
        err = 0
        MsgBox "缺少右括号——）"
        Exit Sub
    End If
Else
    MoveStr Line11(6)
    If LabelStr = "ID" Then
        Dim address As Integer
        '查符号表
        labelValue = Trim$(Right$(lstToken.List(i), Len(lstToken.List(i)) - 4))
        address = LookvarTable(labelValue)
        If address < 0 Then
            err = 22
            MsgBox "变量" & labelValue & "没有声明"
            Exit Sub
        End If
        frmOutput.lstCode.AddItem "        LOAD   " & address '输出指令
        frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
        codep = codep + 1
        frmOutput.Label1.Caption = "新增一条指令"
        frmOutput.Show 1
        MoveStr Line11(10)
        MoveStr Line11(11)
        MoveStr Line11(13)
        MoveStr Line11(14)
    ElseIf LabelStr = "NU" Then
        labelValue = Trim$(Right$(lstToken.List(i), Len(lstToken.List(i)) - 4))
        frmOutput.lstCode.AddItem "        LOADI  " & labelValue '输出指令
        frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
        codep = codep + 1
        frmOutput.Label1.Caption = "新增一条指令"
        frmOutput.Show 1
        MoveStr Line11(7)
        MoveStr Line11(12)
        MoveStr Line11(13)
        MoveStr Line11(14)
    Else
        MoveStr Line11(8)
        err = 10
        MsgBox "表达式少标识符或整数"
        Exit Sub
    End If
End If
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line11(5)
End Sub







Private Sub if_Click() 'if语句
Dim Label1 As Integer, Label2 As Integer
MoveStr Line4(0)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line4(1)
If LabelStr <> "(" Then
    MoveStr Line4(11)
    MoveStr Line4(12)
    err = 5
    MsgBox "缺少左括号——（"
    Exit Sub
End If
MoveStr Line4(2)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line4(3)
expr_Click '表达式
If err > 0 Then Exit Sub
MoveStr Line4(4)
If LabelStr <> ")" Then
    MoveStr Line4(13)
    err = 6
    MsgBox "缺少右括号——）"
    Exit Sub
End If
'输出转移指令
labelp = labelp + 1
Label1 = labelp
frmOutput.lstCode.AddItem "        BRF    " & "Label" & Label1 '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line4(5)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line4(6)
stat_Click
If err > 0 Then Exit Sub
'输出转移指令
labelp = labelp + 1
Label2 = labelp
frmOutput.lstCode.AddItem "        BR     " & "Label" & Label2 '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line4(7)
'设置LABEL1
frmOutput.lstCode.AddItem "Label" & Label1 & "："  '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
If LabelStr = "el" Then 'else处理
    MoveStr Line4(8)
    i = i + 1: lstToken.ListIndex = i '读下一个符号
    LabelStr = Left$(lstToken.List(i), 2)
    MoveStr Line4(9)
    stat_Click
    MoveStr Line4(10)
Else
    MoveStr Line4(15)
    MoveStr Line4(16)
    MoveStr Line4(14)
End If
'设置LABEL2
frmOutput.lstCode.AddItem "Label" & Label2 & "："  '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
End Sub
Public Function LookvarTable(str As String) As Integer
Dim i As Integer
LookvarTable = -1
frmOutput.varTable.Col = 1
For i = frmOutput.varTable.Rows - 1 To 1 Step -1
    frmOutput.varTable.Row = i
    Sleep
    frmOutput.varTable.RowSel = i
    Sleep
    If frmOutput.varTable.Text = str Then
        frmOutput.varTable.Col = 3
        LookvarTable = Val(frmOutput.varTable.Text)
        frmOutput.Hide
        Exit For
    End If
Next i

frmOutput.Hide
End Function
Private Sub decllist_Click() '声明语句序列处理
MoveStr Line2(0)
While LabelStr = "in"
MoveStr Line2(1)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line2(2)
If Left$(LabelStr, 2) <> "ID" Then
    MoveStr Line2(8)
    err = 3
    MsgBox "缺少标识符"
    Exit Sub
End If
'查符号表
labelValue = Trim$(Right$(lstToken.List(i), Len(lstToken.List(i)) - 4))
If LookvarTable(labelValue) >= 0 Then
    err = 21
    MsgBox "变量" & labelValue & "重复声明"
    Exit Sub
End If
'添符号表、分配内存
varTablep = varTablep + 1
frmOutput.varTable.Rows = frmOutput.varTable.Rows + 1
frmOutput.varTable.Row = varTablep
frmOutput.varTable.Col = 0
frmOutput.varTable.Text = varTablep
frmOutput.varTable.Col = 1
frmOutput.varTable.Text = labelValue
frmOutput.varTable.Col = 2
frmOutput.varTable.Text = 1
frmOutput.varTable.Col = 3
frmOutput.varTable.Text = datap
frmOutput.data.Rows = frmOutput.data.Rows + 1
frmOutput.data.Row = datap
frmOutput.data.Col = 0
frmOutput.data.Text = datap
datap = datap + 1
frmOutput.Label1.Caption = "符号表新增一个记录"
frmOutput.Show 1

MoveStr Line2(3)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line2(4)
If Left$(LabelStr, 2) <> ";" Then
    MoveStr Line2(9)
    MoveStr Line2(12)
    err = 4
    MsgBox "缺少分号——；"
    Exit Sub
End If
MoveStr Line2(5)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line2(6)
MoveStr Line2(7)
MoveStr Line2(10)
Wend
MoveStr Line2(11)
End Sub

Private Sub stat_Click() '语句处理
    MoveStr Line3(0)
    Select Case LabelStr
           
    Case "if"
        MoveStr Line3(1)
        MoveStr Line3(9)
        if_Click 'if语句
        If err > 0 Then Exit Sub
        MoveStr Line3(27)
        MoveStr Line3(26)
        MoveStr Line3(25)
        MoveStr Line3(24)
        MoveStr Line3(23)
       
    Case "wh"
        MoveStr Line3(1)
        MoveStr Line3(2)
        MoveStr Line3(10)
        while_Click 'if语句
        If err > 0 Then Exit Sub
        MoveStr Line3(26)
        MoveStr Line3(25)
        MoveStr Line3(24)
        MoveStr Line3(23)
        
    Case "fo"
        MoveStr Line3(1)
        MoveStr Line3(2)
        MoveStr Line3(3)
        MoveStr Line3(11)
       'for_Click 'if语句
        If err > 0 Then Exit Sub
        MoveStr Line3(25)
        MoveStr Line3(24)
        MoveStr Line3(23)
        
    Case "wr"
        MoveStr Line3(1)
        MoveStr Line3(2)
        MoveStr Line3(3)
        MoveStr Line3(4)
        MoveStr Line3(12)
        write_Click '输出语句
        If err > 0 Then Exit Sub
        MoveStr Line3(24)
        MoveStr Line3(23)
        
    Case "re"
        MoveStr Line3(1)
        MoveStr Line3(2)
        MoveStr Line3(3)
        MoveStr Line3(5)
        MoveStr Line3(13)
        read_Click '输入语句
        If err > 0 Then Exit Sub
        MoveStr Line3(23)
        
    Case "{"
        MoveStr Line3(1)
        MoveStr Line3(2)
        MoveStr Line3(3)
        MoveStr Line3(5)
        MoveStr Line3(6)
        MoveStr Line3(14)
        compound_Click '复合语句
        If err > 0 Then Exit Sub
        MoveStr Line3(22)
    Case "ID", "NU", "(", ";"
        MoveStr Line3(8)
        exprstat_Click '表达式语句
        If err > 0 Then Exit Sub
        MoveStr Line3(28)
        MoveStr Line3(27)
        MoveStr Line3(26)
        MoveStr Line3(25)
        MoveStr Line3(24)
        MoveStr Line3(23)
    Case Else
        MoveStr Line3(1)
        MoveStr Line3(2)
        MoveStr Line3(3)
        MoveStr Line3(5)
        MoveStr Line3(6)
        MoveStr Line3(7)
        MoveStr Line3(15)
        err = 7
        MsgBox "非法语句"
        Exit Sub
    End Select
    MoveStr Line3(29)
End Sub



Private Sub exprstat_Click() '表达式语句
MoveStr Line6(8)
If LabelStr = ";" Then
    MoveStr Line6(5)
    MoveStr Line6(6)
    MoveStr Line6(7)
    i = i + 1: lstToken.ListIndex = i '读下一个符号
    LabelStr = Left$(lstToken.List(i), 2)
    MoveStr Line6(3)
    Exit Sub
End If
MoveStr Line6(0)
If LabelStr <> ";" Then
    expr_Click
    If err > 0 Then Exit Sub
    MoveStr Line6(1)
    If LabelStr <> ";" Then
        MoveStr Line6(4)
        err = 7
        MsgBox "缺少分号——；"""
        Exit Sub
    End If
    MoveStr Line6(2)
End If
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line6(3)
End Sub

Private Sub expr_Click() '赋值表达式处理
Dim address As Integer
Dim boolFuZhi As Boolean
MoveStr Line7(0)
MoveStr Line7(1)
If lstToken.List(i + 1) = "=" Then '赋值表达式处理
    MoveStr Line7(2)
    boolFuZhi = True
    If LabelStr = "ID" Then
        '查符号表
        labelValue = Trim$(Right$(lstToken.List(i), Len(lstToken.List(i)) - 4))
        address = LookvarTable(labelValue)
        If address < 0 Then
            err = 22
            MsgBox "变量" & labelValue & "没有声明"
            Exit Sub
        End If
        MoveStr Line7(3)
        i = i + 2 '读下2个符号
        LabelStr = Left$(lstToken.List(i), 2)
        MoveStr Line7(4)
    Else
        err = 8
        MoveStr Line7(9)
        MsgBox "赋值表达式左边少标识符"
        Exit Sub
    End If
Else
    MoveStr Line7(8)
    MoveStr Line7(7)
    MoveStr Line7(6)
End If
boolexpr_Click '布尔表达式处理
If err > 0 Then Exit Sub
MoveStr Line7(5)
If boolFuZhi Then
    frmOutput.lstCode.AddItem "        STO    " & address '输出指令
    frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
    codep = codep + 1
    frmOutput.Label1.Caption = "新增一条指令"
    frmOutput.Show 1
End If
End Sub

Private Sub boolexpr_Click()
MoveStr Line8(0)
addexpr_Click
If err > 0 Then Exit Sub
MoveStr Line8(1)
Select Case LabelStr
Case ">", "<", ">=", "<=", "==", "!="
    MoveStr Line8(2)
    Dim LabelStr1 As String
    LabelStr1 = LabelStr
    i = i + 1: lstToken.ListIndex = i '读下1个符号
    LabelStr = Left$(lstToken.List(i), 2)
    MoveStr Line8(3)
    addexpr_Click
    If err > 0 Then Exit Sub
    Select Case LabelStr1
    Case ">"
        frmOutput.lstCode.AddItem "        GT     "
    Case "<"
        frmOutput.lstCode.AddItem "        LES    "
    Case ">="
        frmOutput.lstCode.AddItem "        GE     "
    Case "<="
        frmOutput.lstCode.AddItem "        LE     "
    Case "=="
        frmOutput.lstCode.AddItem "        EQ     "
    Case "!="
        frmOutput.lstCode.AddItem "        NOTEQ  "
    End Select
    frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
    codep = codep + 1
    frmOutput.Label1.Caption = "新增一条指令"
    frmOutput.Show 1
    MoveStr Line8(4)
Case Else
    MoveStr Line8(5)
    MoveStr Line8(6)
    MoveStr Line8(7)
    Exit Sub
End Select
End Sub

Private Sub addexpr_Click()
MoveStr Line9(0)
term_Click '调项表达式
If err > 0 Then Exit Sub
MoveStr Line9(1)
Do While LabelStr = "+" Or LabelStr = "-"
    MoveStr Line9(2)
    Dim LabelStr1 As String
    LabelStr1 = LabelStr
    i = i + 1: lstToken.ListIndex = i '读下1个符号
    LabelStr = Left$(lstToken.List(i), 2)
    MoveStr Line9(9)
    term_Click '调项表达式
    If err > 0 Then Exit Sub
    Select Case LabelStr1
        Case "+"
            frmOutput.lstCode.AddItem "        ADD    "
        Case "-"
            frmOutput.lstCode.AddItem "        SUB    "
    End Select
    frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
    codep = codep + 1
    frmOutput.Label1.Caption = "新增一条指令"
    frmOutput.Show 1
    MoveStr Line9(3)
    MoveStr Line9(4)
    MoveStr Line9(5)
Loop
MoveStr Line9(6)
MoveStr Line9(7)
MoveStr Line9(8)
End Sub



Private Sub term_Click()
MoveStr Line10(0)
factor_Click '调因子表达式
If err > 0 Then Exit Sub
MoveStr Line10(1)
Do While LabelStr = "*" Or LabelStr = "/"
    MoveStr Line10(2)
    Dim LabelStr1 As String
    LabelStr1 = LabelStr
    i = i + 1: lstToken.ListIndex = i '读下1个符号
    LabelStr = Left$(lstToken.List(i), 2)
    MoveStr Line10(9)
    factor_Click '调因子表达式
    If err > 0 Then Exit Sub
    Select Case LabelStr1
        Case "*"
            frmOutput.lstCode.AddItem "        MULT   "
        Case "/"
            frmOutput.lstCode.AddItem "        DIV    "
    End Select
    frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
    codep = codep + 1
    frmOutput.Label1.Caption = "新增一条指令"
    frmOutput.Show 1
    MoveStr Line10(3)
    MoveStr Line10(4)
    MoveStr Line10(6)
Loop
MoveStr Line10(6)
MoveStr Line10(7)
MoveStr Line10(8)
End Sub







Private Sub Form_Load()
Me.lstToken.Clear
Dim i As Integer
For i = 0 To frmCiFa.lstToken.ListCount - 1
Me.lstToken.AddItem frmCiFa.lstToken.List(i)
Next i

For i = 0 To 7
Label1(i).ZOrder
Next i
For i = 0 To 7
Label2(i).ZOrder
Next i

For i = 0 To 8
Label3(i).ZOrder
Next i
For i = 0 To 11
Label4(i).ZOrder
Next i
For i = 0 To 2
Label5(i).ZOrder
Next i
For i = 0 To 5
Label6(i).ZOrder
Next i
For i = 0 To 5
Label7(i).ZOrder
Next i
For i = 0 To 4
Label8(i).ZOrder
Next i
For i = 0 To 4
Label9(i).ZOrder
Next i
For i = 0 To 4
Label10(i).ZOrder
Next i
For i = 0 To 8
Label11(i).ZOrder
Next i
For i = 0 To 8
Label12(i).ZOrder
Next i
For i = 0 To 5
Label13(i).ZOrder
Next i
For i = 0 To 5
Label14(i).ZOrder
Next i
For i = 0 To 4
Label15(i).ZOrder
Next i
LabelStr.ZOrder

End Sub

Public Sub MoveStr(Line As Line)  '移动字符串
Dim l As Integer
LabelStr.Left = Line.X1 - LabelStr.Width / 2
LabelStr.Top = Line.Y1 - 200
If Line.X2 >= Line.X1 Then
    For l = Line.X1 To Line.X2 Step 2
        LabelStr.Left = l - LabelStr.Width / 2
        Sleep
    Next l
Else
    For l = Line.X1 To Line.X2 Step -2
        LabelStr.Left = l - LabelStr.Width / 2
        Sleep
    Next l

End If
If Line.Y2 >= Line.Y1 Then
    For l = Line.Y1 To Line.Y2 Step 2
        LabelStr.Top = l - 200
        Sleep
    Next l
Else
    For l = Line.Y1 To Line.Y2 Step -2
        LabelStr.Top = l - 200
        Sleep
    Next l
End If
End Sub


Private Sub lstToken_KeyDown(KeyCode As Integer, Shift As Integer)
If KeyCode = vbKeyDelete And lstToken.ListIndex >= 0 Then
    lstToken.RemoveItem (lstToken.ListIndex)
End If
End Sub

Private Sub mnu2_Click()
frmCode.Show

End Sub

Private Sub mnu3_Click()
frmYuYiRules.Show
End Sub

Private Sub mnu4_Click()
frmOutput.Show
End Sub

Private Sub mnu1_Click()
frmYuFaRules.Show
End Sub


Private Sub statlist_Click()
While 1
MoveStr Line5(0)
Select Case LabelStr
Case "ID", "NU", "(", "if", "wh", "fo", "wr", "re", "{"
        MoveStr Line5(1)
        stat_Click
        MoveStr Line5(2)
        MoveStr Line5(3)
        MoveStr Line5(4)
Case Else
        MoveStr Line5(5)
        Exit Sub
End Select
Wend
End Sub

Private Sub Timer1_Timer()

s = Val(HScroll1.Value) * 1000
End Sub

Private Sub while_Click()
Dim Label1 As Integer, Label2 As Integer
MoveStr Line12(0)
'设置LABEL1
labelp = labelp + 1
Label1 = labelp
frmOutput.lstCode.AddItem "Label" & Label1 & "："  '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
i = i + 1: lstToken.ListIndex = i:  '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line12(1)
If LabelStr <> "(" Then
    MoveStr Line12(8)
    MoveStr Line12(9)
    err = 5
    MsgBox "缺少左括号——（"
    Exit Sub
End If
MoveStr Line12(2)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line12(3)
expr_Click '表达式
If err > 0 Then Exit Sub
MoveStr Line12(4)
If LabelStr <> ")" Then
    MoveStr Line12(10)
    err = 6
    MsgBox "缺少右括号——）"
    Exit Sub
End If
'输出转移指令
labelp = labelp + 1
Label2 = labelp
frmOutput.lstCode.AddItem "        BRF    " & "Label" & Label2 '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line12(5)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line12(6)
stat_Click
If err > 0 Then Exit Sub
'输出转移指令
frmOutput.lstCode.AddItem "        BR     " & "Label" & Label1 '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line12(7)
'设置LABEL2
frmOutput.lstCode.AddItem "Label" & Label2 & "："  '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
End Sub

Private Sub write_Click()
MoveStr Line15(0)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
MoveStr Line15(1)
expr_Click
If err > 0 Then Exit Sub
MoveStr Line15(2)
If LabelStr <> ";" Then
    MoveStr Line15(4)
    err = 3
    MsgBox "缺少分号——；"
    Exit Sub
End If
'输出OUT指令
frmOutput.lstCode.AddItem "        OUT    " '输出指令
frmOutput.lstCode.ListIndex = frmOutput.lstCode.ListCount - 1
codep = codep + 1
frmOutput.Label1.Caption = "新增一条指令"
frmOutput.Show 1
MoveStr Line15(3)
i = i + 1: lstToken.ListIndex = i '读下一个符号
LabelStr = Left$(lstToken.List(i), 2)
End Sub

