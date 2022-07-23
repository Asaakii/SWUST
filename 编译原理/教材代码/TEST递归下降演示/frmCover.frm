VERSION 5.00
Begin VB.Form frmCover 
   BorderStyle     =   1  'Fixed Single
   ClientHeight    =   8625
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   11910
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   Picture         =   "frmCover.frx":0000
   ScaleHeight     =   8625
   ScaleWidth      =   11910
   StartUpPosition =   3  '窗口缺省
   WindowState     =   2  'Maximized
   Begin VB.PictureBox Picture1 
      Height          =   3915
      Left            =   2160
      Picture         =   "frmCover.frx":8CC3E
      ScaleHeight     =   3855
      ScaleWidth      =   6615
      TabIndex        =   4
      Top             =   2400
      Width           =   6675
   End
   Begin VB.Label Label2 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "退出"
      BeginProperty Font 
         Name            =   "隶书"
         Size            =   26.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   525
      Left            =   7080
      TabIndex        =   3
      Top             =   6840
      Width           =   1125
   End
   Begin VB.Shape Shape2 
      FillColor       =   &H00C0FFFF&
      FillStyle       =   0  'Solid
      Height          =   855
      Left            =   6240
      Shape           =   2  'Oval
      Top             =   6720
      Width           =   2775
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "点击我"
      BeginProperty Font 
         Name            =   "隶书"
         Size            =   26.25
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   -1  'True
         Strikethrough   =   0   'False
      EndProperty
      Height          =   525
      Left            =   3240
      TabIndex        =   2
      Top             =   6840
      Width           =   1680
   End
   Begin VB.Shape Shape1 
      FillColor       =   &H00C0FFFF&
      FillStyle       =   0  'Solid
      Height          =   855
      Left            =   2760
      Shape           =   2  'Oval
      Top             =   6720
      Width           =   2775
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "递归下降法编译演示系统"
      BeginProperty Font 
         Name            =   "隶书"
         Size            =   42
         Charset         =   134
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FFFF80&
      Height          =   840
      Index           =   1
      Left            =   2040
      TabIndex        =   1
      Top             =   1320
      Width           =   9420
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "递归下降法编译演示系统"
      BeginProperty Font 
         Name            =   "隶书"
         Size            =   42
         Charset         =   134
         Weight          =   700
         Underline       =   -1  'True
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000FF&
      Height          =   840
      Index           =   0
      Left            =   2040
      TabIndex        =   0
      Top             =   600
      Width           =   9420
   End
End
Attribute VB_Name = "frmCover"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Form_Load()
Label1(0).Left = (Me.Width - Label1(0).Width) / 2
Label1(1).Left = Label1(0).Left + 50
Label1(1).Top = Label1(0).Top - 50
Picture1.Left = (Me.Width - Picture1.Width) / 2
Label1(0).ZOrder
End Sub

Private Sub Label2_Click()
End
End Sub

Private Sub Label3_Click()
frmCiFa.Show
End Sub
