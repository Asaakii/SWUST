VERSION 5.00
Begin VB.Form frmCiFa 
   BackColor       =   &H00C0E0FF&
   Caption         =   "词法分析"
   ClientHeight    =   6555
   ClientLeft      =   75
   ClientTop       =   645
   ClientWidth     =   8880
   FillColor       =   &H008080FF&
   LinkTopic       =   "Form1"
   ScaleHeight     =   6555
   ScaleWidth      =   8880
   StartUpPosition =   2  '屏幕中心
   WindowState     =   2  'Maximized
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   2520
      Top             =   120
   End
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
      Height          =   4140
      ItemData        =   "frmCiFa.frx":0000
      Left            =   360
      List            =   "frmCiFa.frx":0002
      TabIndex        =   71
      Top             =   3960
      Width           =   2055
   End
   Begin VB.TextBox Source 
      BackColor       =   &H80000001&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   3015
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   0
      Text            =   "frmCiFa.frx":0004
      Top             =   360
      Width           =   2055
   End
   Begin VB.TextBox txtCurrentStr 
      BackColor       =   &H00808000&
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   375
      Left            =   5640
      TabIndex        =   25
      Top             =   480
      Width           =   2655
   End
   Begin VB.ListBox lstKeyWord 
      BackColor       =   &H0080FF80&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1260
      ItemData        =   "frmCiFa.frx":0078
      Left            =   9120
      List            =   "frmCiFa.frx":007A
      TabIndex        =   23
      Top             =   120
      Width           =   2415
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   255
      LargeChange     =   6
      Left            =   3120
      Max             =   2000
      SmallChange     =   3
      TabIndex        =   6
      Top             =   7920
      Width           =   2535
   End
   Begin VB.CommandButton comCiFaBegin 
      BackColor       =   &H000000FF&
      Caption         =   "开始"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   3120
      Style           =   1  'Graphical
      TabIndex        =   2
      Top             =   0
      Width           =   975
   End
   Begin VB.Label Label5 
      BackColor       =   &H0080C0FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "保留字"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   1335
      Left            =   8760
      TabIndex        =   72
      Top             =   120
      Width           =   375
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H0080C0FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "词法分析输出："
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
      Index           =   1
      Left            =   240
      TabIndex        =   70
      Top             =   3600
      Width           =   2175
   End
   Begin VB.Line Line53 
      X1              =   4800
      X2              =   3600
      Y1              =   600
      Y2              =   600
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "A"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   405
      Index           =   3
      Left            =   4800
      TabIndex        =   69
      Top             =   480
      Width           =   660
   End
   Begin VB.Label Label3 
      Alignment       =   2  'Center
      BorderStyle     =   1  'Fixed Single
      Caption         =   "A"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   345
      Index           =   2
      Left            =   11040
      TabIndex        =   68
      Top             =   7920
      Width           =   600
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "慢"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   1
      Left            =   5760
      TabIndex        =   67
      Top             =   7920
      Width           =   315
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      Caption         =   "快"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   285
      Index           =   0
      Left            =   2760
      TabIndex        =   66
      Top             =   7920
      Width           =   315
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   0
      Left            =   3240
      TabIndex        =   65
      Top             =   120
      Width           =   765
   End
   Begin VB.Line Line52 
      X1              =   3600
      X2              =   11400
      Y1              =   7680
      Y2              =   7680
   End
   Begin VB.Line Line51 
      X1              =   3600
      X2              =   3600
      Y1              =   7200
      Y2              =   7680
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "非法符号"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   28
      Left            =   3180
      TabIndex        =   64
      Top             =   7080
      Width           =   1005
   End
   Begin VB.Line Line50 
      X1              =   3600
      X2              =   3600
      Y1              =   6000
      Y2              =   7200
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   23
      Left            =   7200
      TabIndex        =   63
      Top             =   5280
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   22
      Left            =   9480
      TabIndex        =   62
      Top             =   6480
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   21
      Left            =   8880
      TabIndex        =   61
      Top             =   6960
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   20
      Left            =   6600
      TabIndex        =   60
      Top             =   6240
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   19
      Left            =   7080
      TabIndex        =   59
      Top             =   5760
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   18
      Left            =   4200
      TabIndex        =   58
      Top             =   5760
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   17
      Left            =   3720
      TabIndex        =   57
      Top             =   6240
      Width           =   135
   End
   Begin VB.Line Line49 
      X1              =   7560
      X2              =   7560
      Y1              =   7320
      Y2              =   6720
   End
   Begin VB.Line Line48 
      X1              =   8760
      X2              =   7560
      Y1              =   7320
      Y2              =   7320
   End
   Begin VB.Line Line47 
      X1              =   8760
      X2              =   8760
      Y1              =   6720
      Y2              =   7320
   End
   Begin VB.Line Line46 
      X1              =   8880
      X2              =   11400
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Line Line45 
      X1              =   7680
      X2              =   8880
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Line Line44 
      X1              =   6480
      X2              =   7680
      Y1              =   6720
      Y2              =   6720
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "删除注释"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   32
      Left            =   9840
      TabIndex        =   56
      Top             =   6600
      Width           =   1005
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "前字符=后字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   31
      Left            =   7920
      TabIndex        =   55
      Top             =   7200
      Width           =   1575
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "注释尾？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   30
      Left            =   8400
      TabIndex        =   54
      Top             =   6600
      Width           =   1005
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读后字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   29
      Left            =   7200
      TabIndex        =   53
      Top             =   6600
      Width           =   1005
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读前字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   27
      Left            =   6000
      TabIndex        =   52
      Top             =   6600
      Width           =   1005
   End
   Begin VB.Line Line43 
      X1              =   6480
      X2              =   6480
      Y1              =   6000
      Y2              =   6720
   End
   Begin VB.Line Line42 
      X1              =   6480
      X2              =   11400
      Y1              =   6000
      Y2              =   6000
   End
   Begin VB.Line Line41 
      X1              =   5040
      X2              =   6480
      Y1              =   6000
      Y2              =   6000
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出单分界符/"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   26
      Left            =   7680
      TabIndex        =   51
      Top             =   5880
      Width           =   1575
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是*吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   25
      Left            =   6120
      TabIndex        =   50
      Top             =   5880
      Width           =   885
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   24
      Left            =   4680
      TabIndex        =   49
      Top             =   5880
      Width           =   765
   End
   Begin VB.Line Line40 
      X1              =   3600
      X2              =   5160
      Y1              =   6000
      Y2              =   6000
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是/吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   20
      Left            =   3225
      TabIndex        =   48
      Top             =   5880
      Width           =   885
   End
   Begin VB.Line Line39 
      X1              =   3600
      X2              =   3600
      Y1              =   5040
      Y2              =   6000
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是字母吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   3
      Left            =   3000
      TabIndex        =   47
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是=吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   22
      Left            =   6600
      TabIndex        =   46
      Top             =   4920
      Width           =   885
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   21
      Left            =   5160
      TabIndex        =   45
      Top             =   4920
      Width           =   765
   End
   Begin VB.Line Line38 
      X1              =   5640
      X2              =   7080
      Y1              =   5040
      Y2              =   5040
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   16
      Left            =   7560
      TabIndex        =   44
      Top             =   4800
      Width           =   135
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "纯单分界符吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   16
      Left            =   2880
      TabIndex        =   43
      Top             =   4320
      Width           =   1665
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出双分界符== >= <= !="
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   18
      Left            =   7680
      TabIndex        =   42
      Top             =   5400
      Width           =   2775
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出单分界符= > < !"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   23
      Left            =   8520
      TabIndex        =   41
      Top             =   4920
      Width           =   2295
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   15
      Left            =   3720
      TabIndex        =   40
      Top             =   5280
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   14
      Left            =   4800
      TabIndex        =   39
      Top             =   4800
      Width           =   135
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "双分界符首= > < !"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   19
      Left            =   2580
      TabIndex        =   38
      Top             =   4920
      Width           =   2055
   End
   Begin VB.Line Line37 
      X1              =   7080
      X2              =   11400
      Y1              =   5520
      Y2              =   5520
   End
   Begin VB.Line Line36 
      X1              =   7080
      X2              =   7080
      Y1              =   5040
      Y2              =   5520
   End
   Begin VB.Line Line35 
      X1              =   7080
      X2              =   11400
      Y1              =   5040
      Y2              =   5040
   End
   Begin VB.Line Line34 
      X1              =   3600
      X2              =   5640
      Y1              =   5040
      Y2              =   5040
   End
   Begin VB.Line Line33 
      X1              =   3600
      X2              =   3600
      Y1              =   4440
      Y2              =   5040
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   13
      Left            =   3720
      TabIndex        =   37
      Top             =   4680
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   12
      Left            =   4560
      TabIndex        =   36
      Top             =   4200
      Width           =   135
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出单分界符 + - * ( ) { } ; : ,"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   17
      Left            =   6180
      TabIndex        =   35
      Top             =   4320
      Width           =   3855
   End
   Begin VB.Line Line32 
      X1              =   3600
      X2              =   11400
      Y1              =   4440
      Y2              =   4440
   End
   Begin VB.Line Line31 
      X1              =   3600
      X2              =   3600
      Y1              =   3600
      Y2              =   4440
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是数字吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   13
      Left            =   6360
      TabIndex        =   34
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出整数"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   15
      Left            =   8745
      TabIndex        =   33
      Top             =   3480
      Width           =   1005
   End
   Begin VB.Line Line30 
      X1              =   7080
      X2              =   11400
      Y1              =   3600
      Y2              =   3600
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   11
      Left            =   4440
      TabIndex        =   32
      Top             =   3360
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   10
      Left            =   7200
      TabIndex        =   31
      Top             =   3840
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   9
      Left            =   3720
      TabIndex        =   30
      Top             =   3840
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   8
      Left            =   7800
      TabIndex        =   29
      Top             =   3360
      Width           =   135
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   14
      Left            =   5880
      TabIndex        =   28
      Top             =   2760
      Width           =   765
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "组合整数"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   12
      Left            =   4920
      TabIndex        =   27
      Top             =   3480
      Width           =   1005
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是数字吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   11
      Left            =   3120
      TabIndex        =   26
      Top             =   3480
      Width           =   1215
   End
   Begin VB.Line Line29 
      X1              =   5400
      X2              =   5400
      Y1              =   3960
      Y2              =   3600
   End
   Begin VB.Line Line28 
      X1              =   7080
      X2              =   5400
      Y1              =   3960
      Y2              =   3960
   End
   Begin VB.Line Line27 
      X1              =   7080
      X2              =   7080
      Y1              =   3600
      Y2              =   3960
   End
   Begin VB.Line Line26 
      X1              =   7080
      X2              =   7080
      Y1              =   2880
      Y2              =   3600
   End
   Begin VB.Line Line25 
      X1              =   6120
      X2              =   7080
      Y1              =   2880
      Y2              =   2880
   End
   Begin VB.Line Line24 
      X1              =   5400
      X2              =   6120
      Y1              =   2880
      Y2              =   2880
   End
   Begin VB.Line Line23 
      X1              =   5400
      X2              =   5400
      Y1              =   3600
      Y2              =   2880
   End
   Begin VB.Line Line22 
      X1              =   3600
      X2              =   5400
      Y1              =   3600
      Y2              =   3600
   End
   Begin VB.Line Line21 
      X1              =   3600
      X2              =   3600
      Y1              =   2160
      Y2              =   3600
   End
   Begin VB.Line Line3 
      X1              =   5280
      X2              =   6000
      Y1              =   1560
      Y2              =   1560
   End
   Begin VB.Label LabelStr 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H0080C0FF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   12
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   300
      Left            =   8070
      TabIndex        =   24
      Top             =   1680
      Visible         =   0   'False
      Width           =   225
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   7
      Left            =   2880
      TabIndex        =   22
      Top             =   1320
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   6
      Left            =   3720
      TabIndex        =   21
      Top             =   1800
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   5
      Left            =   10320
      TabIndex        =   20
      Top             =   1800
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   4
      Left            =   7200
      TabIndex        =   19
      Top             =   2400
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   3
      Left            =   10320
      TabIndex        =   18
      Top             =   2400
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   2
      Left            =   8040
      TabIndex        =   17
      Top             =   1920
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "N"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   1
      Left            =   3720
      TabIndex        =   16
      Top             =   2400
      Width           =   135
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      Caption         =   "Y"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   210
      Index           =   0
      Left            =   4440
      TabIndex        =   15
      Top             =   1920
      Width           =   135
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出保留字"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   9
      Left            =   9480
      TabIndex        =   14
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输出标识符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   10
      Left            =   9480
      TabIndex        =   13
      Top             =   2640
      Width           =   1215
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是保留字"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   8
      Left            =   9720
      TabIndex        =   12
      Top             =   2040
      Width           =   1005
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "查保留字表"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   7
      Left            =   8280
      TabIndex        =   11
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   5
      Left            =   5760
      TabIndex        =   10
      Top             =   1440
      Width           =   765
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是字母数字吗？"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   6
      Left            =   6360
      TabIndex        =   9
      Top             =   2040
      Width           =   1635
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "组合标识符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   4
      Left            =   4920
      TabIndex        =   8
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Line Line20 
      X1              =   11400
      X2              =   11400
      Y1              =   1560
      Y2              =   7920
   End
   Begin VB.Line Line19 
      X1              =   10200
      X2              =   11400
      Y1              =   2760
      Y2              =   2760
   End
   Begin VB.Line Line18 
      X1              =   10200
      X2              =   11400
      Y1              =   1560
      Y2              =   1560
   End
   Begin VB.Line Line17 
      X1              =   10200
      X2              =   10200
      Y1              =   2160
      Y2              =   2760
   End
   Begin VB.Line Line16 
      X1              =   10200
      X2              =   10200
      Y1              =   2160
      Y2              =   1680
   End
   Begin VB.Line Line15 
      X1              =   7080
      X2              =   10080
      Y1              =   2160
      Y2              =   2160
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackColor       =   &H0080C0FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "当前字符串："
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
      Left            =   5640
      TabIndex        =   7
      Top             =   120
      Width           =   1875
   End
   Begin VB.Line Line14 
      X1              =   5280
      X2              =   5280
      Y1              =   2520
      Y2              =   2160
   End
   Begin VB.Line Line13 
      X1              =   7080
      X2              =   5280
      Y1              =   2520
      Y2              =   2520
   End
   Begin VB.Line Line12 
      X1              =   7080
      X2              =   7080
      Y1              =   2160
      Y2              =   2520
   End
   Begin VB.Line Line11 
      X1              =   7080
      X2              =   7080
      Y1              =   1560
      Y2              =   2160
   End
   Begin VB.Line Line10 
      X1              =   6120
      X2              =   7080
      Y1              =   1560
      Y2              =   1560
   End
   Begin VB.Line Line9 
      X1              =   5280
      X2              =   5280
      Y1              =   2160
      Y2              =   1560
   End
   Begin VB.Line Line8 
      X1              =   3600
      X2              =   5520
      Y1              =   2160
      Y2              =   2160
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "读字符"
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   1
      Left            =   3240
      TabIndex        =   5
      Top             =   840
      Width           =   765
   End
   Begin VB.Label Label 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFFC0&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "是空字符？ "
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   10.5
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   270
      Index           =   2
      Left            =   3090
      TabIndex        =   4
      Top             =   1440
      Width           =   1215
   End
   Begin VB.Label LabelChar 
      Alignment       =   2  'Center
      AutoSize        =   -1  'True
      BackColor       =   &H0000FFFF&
      BorderStyle     =   1  'Fixed Single
      BeginProperty Font 
         Name            =   "宋体"
         Size            =   14.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   345
      Left            =   5955
      TabIndex        =   3
      Top             =   0
      Visible         =   0   'False
      Width           =   255
   End
   Begin VB.Line Line7 
      X1              =   3600
      X2              =   3600
      Y1              =   1440
      Y2              =   2160
   End
   Begin VB.Line Line6 
      X1              =   2520
      X2              =   3600
      Y1              =   600
      Y2              =   600
   End
   Begin VB.Line Line5 
      X1              =   2520
      X2              =   2520
      Y1              =   1560
      Y2              =   600
   End
   Begin VB.Line Line4 
      X1              =   3600
      X2              =   2520
      Y1              =   1560
      Y2              =   1560
   End
   Begin VB.Line Line2 
      X1              =   3600
      X2              =   3600
      Y1              =   840
      Y2              =   1440
   End
   Begin VB.Line Line1 
      X1              =   3600
      X2              =   3600
      Y1              =   480
      Y2              =   840
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H0080C0FF&
      BorderStyle     =   1  'Fixed Single
      Caption         =   "输入TEST程序："
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
      Index           =   0
      Left            =   240
      TabIndex        =   1
      Top             =   0
      Width           =   2235
   End
   Begin VB.Menu mmnu0 
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
   Begin VB.Menu mnuYuFa 
      Caption         =   "语法分析"
   End
   Begin VB.Menu mnuYuYi 
      Caption         =   "语义分析"
   End
   Begin VB.Menu mnuEnd 
      Caption         =   "结束"
   End
End
Attribute VB_Name = "frmCiFa"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim currentpos As Long
Dim CurrentChar As String
Dim currentStr As String
Dim s As Long
Public Function GetNextChar(currentpos As Long) As String '获取当前位置的字符
currentpos = currentpos + 1
Source.SelStart = currentpos
Source.SelLength = 1
GetNextChar = LCase$(Source.SelText)
End Function

Public Sub MoveChar(Line As Line)  '获取当前位置的字符
Dim l As Integer

LabelChar.Left = Line.X1 - LabelChar.Width / 2
LabelChar.Top = Line.Y1 - 200
If Line.X2 >= Line.X1 Then
    For l = Line.X1 To Line.X2 Step 2
        LabelChar.Left = l - LabelChar.Width / 2
        Sleep
    Next l
Else
    For l = Line.X1 To Line.X2 Step -2
        LabelChar.Left = l - LabelChar.Width / 2
        Sleep
    Next l

End If
If Line.Y2 >= Line.Y1 Then
    For l = Line.Y1 To Line.Y2 Step 2
        LabelChar.Top = l - 200
        Sleep
    Next l
Else
    For l = Line.Y1 To Line.Y2 Step -2
        LabelChar.Top = l - 200
        Sleep
    Next l
End If
End Sub

Private Sub comCiFaBegin_Click()
mnuYuFa.Enabled = False
mnuYuYi.Enabled = False
mnuEnd.Enabled = False
comCiFaBegin.Enabled = False

Source.SetFocus
LabelChar.Caption = ""
LabelChar.Visible = True
LabelStr.ZOrder
LabelChar.ZOrder
lstToken.Clear
MoveChar Line1
currentpos = -1 '设当前处理的字符位置为-1
Do While currentpos < Len(Source.Text) - 1
    
    txtCurrentStr = ""
    LabelStr.Caption = ""
    currentStr = ""
    CurrentChar = GetNextChar(currentpos) '获取下一个的字符
    LabelChar.Caption = CurrentChar
    MoveChar Line2
    Do While CurrentChar = "" Or CurrentChar = " " Or CurrentChar = Chr$(13) Or CurrentChar = Chr$(10)
        MoveChar Line4
        MoveChar Line5
        MoveChar Line6
        CurrentChar = GetNextChar(currentpos) '获取下一个的字符
        If currentpos = Len(Source.Text) - 1 Then Exit Do
        LabelChar.Caption = CurrentChar
        MoveChar Line2
    Loop
    If currentpos = Len(Source.Text) - 1 Then Exit Do
    
    Select Case CurrentChar
    Case "a" To "z", "A" To "Z" '标识符处理
         MoveChar Line7
         MoveChar Line8
         currentStr = currentStr & CurrentChar '将当前字符接到当前字符串的后面
         txtCurrentStr.Text = currentStr
         MoveChar Line9
         MoveChar Line3
         CurrentChar = GetNextChar(currentpos) '获取下一个的字符
         LabelChar.Caption = CurrentChar
         MoveChar Line10
         MoveChar Line11
         Do While IsNumeric(CurrentChar) Or (CurrentChar >= "a" And UCase$(CurrentChar) <= "z")
            MoveChar Line12
            MoveChar Line13
            MoveChar Line14
            currentStr = currentStr & CurrentChar
            txtCurrentStr.Text = currentStr
            LabelChar.Caption = CurrentChar
            MoveChar Line9
            MoveChar Line3
            CurrentChar = GetNextChar(currentpos) '获取下一个的字符
            LabelChar.Caption = CurrentChar
            MoveChar Line10
            MoveChar Line11
        Loop
        CurrentChar = GetPreChar(currentpos)
        LabelStr.Visible = True
        LabelChar.Visible = False
        LabelStr.Caption = currentStr
        MoveStr Line15
        Dim i As Integer
        Dim isKeyWord As Boolean
        isKeyWord = False
        For i = 0 To lstKeyWord.ListCount - 1
            If currentStr = Trim$(Left$(lstKeyWord.List(i), 10)) Then
                lstKeyWord.ListIndex = i
                lstToken.AddItem currentStr
                lstToken.ListIndex = lstToken.ListCount - 1
                MoveStr Line16
                isKeyWord = True
                Exit For
            End If
        Next i
        If Not isKeyWord Then
            lstToken.AddItem "ID" & Space(10) & currentStr '标识符的记号为ID
            lstToken.ListIndex = lstToken.ListCount - 1
            MoveStr Line17
        End If
        
    Case "0" To "9" '数字处理
        MoveChar Line7
        MoveChar Line21
        MoveChar Line22
        currentStr = currentStr & CurrentChar '将当前字符接到当前字符串的后面
        txtCurrentStr.Text = currentStr
        MoveChar Line23
        MoveChar Line24
        CurrentChar = GetNextChar(currentpos) '获取下一个的字符
        LabelChar.Caption = CurrentChar
        MoveChar Line25
        MoveChar Line26
        Do While IsNumeric(CurrentChar)
           MoveChar Line27
           MoveChar Line28
           MoveChar Line29
           currentStr = currentStr & CurrentChar
           txtCurrentStr.Text = currentStr
           LabelChar.Caption = CurrentChar
           MoveChar Line23
           MoveChar Line24
           CurrentChar = GetNextChar(currentpos) '获取下一个的字符
           LabelChar.Caption = CurrentChar
           MoveChar Line25
           MoveChar Line26
        Loop
        CurrentChar = GetPreChar(currentpos)
        LabelStr.Visible = True
        LabelChar.Visible = False
      '整数的记号为NUM
        lstToken.AddItem "NUM" & Space(5) & currentStr
        lstToken.ListIndex = lstToken.ListCount - 1
            
        LabelStr.Caption = currentStr
        MoveStr Line30
    '纯单分界符
    Case "+", "-", "*", "(", ")", "{", "}", ";", ",", ":"
        MoveSingleWord
    
    Case "=", ">", "<", "!"
        MoveDoubleWord
    
    Case "/"
        MoveChar Line7
        MoveChar Line21
        MoveChar Line31
        MoveChar Line33
        MoveChar Line39
        currentStr = CurrentChar
        LabelStr.Caption = currentStr
        txtCurrentStr.Text = currentStr
        MoveChar Line40
        CurrentChar = GetNextChar(currentpos)
        LabelChar.Caption = CurrentChar
        MoveChar Line41
        If CurrentChar <> "*" Then
            LabelStr.Visible = True
            LabelChar.Visible = False
            CurrentChar = GetPreChar(currentpos)
            LabelStr.Caption = currentStr
         
             lstToken.AddItem currentStr
            lstToken.ListIndex = lstToken.ListCount - 1
            
            MoveStr Line42
        Else '注释处理
            currentStr = currentStr & CurrentChar
            txtCurrentStr.Text = currentStr
            Dim NextChar As String
            MoveChar Line43
            CurrentChar = GetNextChar(currentpos)
            currentStr = currentStr & CurrentChar
            txtCurrentStr.Text = currentStr
            LabelChar.Caption = CurrentChar
            MoveChar Line44
            NextChar = GetNextChar(currentpos)
            currentStr = currentStr & CurrentChar
            txtCurrentStr.Text = currentStr
            LabelChar.Caption = NextChar
            MoveChar Line45
            Do Until (CurrentChar = "*" And NextChar = "/") Or currentpos >= Len(Source.Text)
                CurrentChar = NextChar
                MoveChar Line47
                MoveChar Line48
                MoveChar Line49
                NextChar = GetNextChar(currentpos)
                currentStr = currentStr & CurrentChar
                txtCurrentStr.Text = currentStr
                LabelChar.Caption = NextChar
                MoveChar Line45
            Loop
            LabelStr.Visible = True
            LabelChar.Visible = False
            LabelStr.Caption = currentStr
            MoveStr Line46
        End If
    Case Else
        MoveChar Line7
        MoveChar Line21
        MoveChar Line31
        MoveChar Line33
        MoveChar Line39
        MoveChar Line50
        LabelStr.Visible = True
        LabelChar.Visible = False
        LabelStr.Caption = "非法符号 " & CurrentChar
        currentStr = CurrentChar
        txtCurrentStr.Text = currentStr
        If currentStr <> "" Then
           
              lstToken.AddItem currentStr & Space(10 - Len(currentStr)) & 0
            lstToken.ListIndex = lstToken.ListCount - 1
            
            MoveStr Line51
            MoveStr Line52
        End If
    End Select
    LabelStr.Visible = False
    LabelChar.Visible = True
    LabelChar.Caption = LabelStr
    LabelChar.Left = Line20.X1 - 200
    For i = LabelStr.Top To Line20.Y2
        LabelChar.Top = i
        Sleep
    Next i
    'DoEvents
    Beep
Loop
Source.SetFocus
LabelChar.Caption = ""
LabelChar.Visible = False
LabelStr.Visible = False
txtCurrentStr.Text = ""
comCiFaBegin.Enabled = True
Beep
Beep
mnuYuFa.Enabled = True
mnuYuYi.Enabled = True
mnuEnd.Enabled = True
End Sub

Public Sub MoveStr(Line As Line)  '获取当前位置的字符
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
Public Sub Sleep()
Dim t As Long
For t = 0 To s
Next t
DoEvents
End Sub









Private Sub Form_Load()

lstKeyWord.AddItem "if"
lstKeyWord.AddItem "else"
lstKeyWord.AddItem "for"
lstKeyWord.AddItem "while"
lstKeyWord.AddItem "do"
lstKeyWord.AddItem "int"
lstKeyWord.AddItem "read"
lstKeyWord.AddItem "write"

Dim i As Integer
For i = 1 To 32
    Label(i).ZOrder
Next i
Label3(2).BackColor = vbGreen
Label3(3).BackColor = vbGreen

End Sub

Public Function GetPreChar(currentpos As Long) As String
currentpos = currentpos - 1 '退回一个字符
Source.SelStart = currentpos
Source.SelLength = 1
GetPreChar = LCase$(Source.SelText)
End Function

Public Sub MoveSingleWord()
    MoveChar Line7
    MoveChar Line21
    MoveChar Line31
    currentStr = CurrentChar
    LabelStr.Visible = True
    LabelChar.Visible = False
    LabelStr.Caption = currentStr
    txtCurrentStr.Text = currentStr
    lstToken.AddItem currentStr
    lstToken.ListIndex = lstToken.ListCount - 1
    MoveStr Line32
End Sub

Public Sub MoveDoubleWord()
    MoveChar Line7
    MoveChar Line21
    MoveChar Line31
    MoveChar Line33
    currentStr = CurrentChar
    txtCurrentStr.Text = currentStr
    MoveChar Line34
    currentStr = CurrentChar
    txtCurrentStr.Text = currentStr
    CurrentChar = GetNextChar(currentpos)
    LabelChar.Caption = CurrentChar
    MoveChar Line38
    LabelStr.Visible = True
    LabelChar.Visible = False
    If CurrentChar <> "=" Then
        CurrentChar = GetPreChar(currentpos)
        LabelStr.Caption = currentStr
        lstToken.AddItem currentStr
        lstToken.ListIndex = lstToken.ListCount - 1
        MoveStr Line35
    Else
        currentStr = currentStr & CurrentChar
        MoveStr Line36
        LabelStr.Caption = currentStr
        txtCurrentStr.Text = currentStr
        lstToken.AddItem currentStr
        lstToken.ListIndex = lstToken.ListCount - 1
        MoveStr Line37
    End If
End Sub





Private Sub mmnu0_Click()
frmCiFaRules.Show
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


Private Sub mnuEnd_Click()
End
End Sub

Private Sub mnuYuFa_Click()
Me.Hide
frmYuFa.Show
End Sub

Private Sub mnuYuYi_Click()
Me.Hide
frmYuYI.Show
End Sub

Private Sub Timer1_Timer()
s = Val(HScroll1.Value) * 1000
End Sub
