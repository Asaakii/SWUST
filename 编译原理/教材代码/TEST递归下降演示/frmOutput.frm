VERSION 5.00
Object = "{5E9E78A0-531B-11CF-91F6-C2863C385E30}#1.0#0"; "MSFLXGRD.OCX"
Begin VB.Form frmOutput 
   AutoRedraw      =   -1  'True
   BackColor       =   &H00C0C0FF&
   Caption         =   "�� �� �� �� �� ��"
   ClientHeight    =   5835
   ClientLeft      =   60
   ClientTop       =   285
   ClientWidth     =   7395
   BeginProperty Font 
      Name            =   "����"
      Size            =   14.25
      Charset         =   134
      Weight          =   400
      Underline       =   0   'False
      Italic          =   0   'False
      Strikethrough   =   0   'False
   EndProperty
   LinkTopic       =   "Form2"
   ScaleHeight     =   5835
   ScaleWidth      =   7395
   StartUpPosition =   3  'Windows Default
   WindowState     =   2  'Maximized
   Begin VB.CheckBox Check1 
      Caption         =   "�ֶ�"
      Height          =   285
      Left            =   3600
      TabIndex        =   14
      Top             =   5760
      Width           =   975
   End
   Begin VB.Timer Timer1 
      Interval        =   100
      Left            =   3360
      Top             =   240
   End
   Begin VB.HScrollBar HScroll1 
      Height          =   375
      Left            =   3840
      TabIndex        =   13
      Top             =   4920
      Width           =   3375
   End
   Begin VB.ListBox output 
      Height          =   1200
      ItemData        =   "frmOutput.frx":0000
      Left            =   9480
      List            =   "frmOutput.frx":0002
      TabIndex        =   11
      Top             =   6360
      Width           =   1935
   End
   Begin MSFlexGridLib.MSFlexGrid data 
      Height          =   1695
      Left            =   9480
      TabIndex        =   10
      Top             =   120
      Width           =   1935
      _ExtentX        =   3413
      _ExtentY        =   2990
      _Version        =   393216
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "����"
         Size            =   14.25
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.ListBox stack 
      Height          =   4050
      ItemData        =   "frmOutput.frx":0004
      Left            =   9480
      List            =   "frmOutput.frx":0006
      TabIndex        =   8
      Top             =   1920
      Width           =   1935
   End
   Begin VB.CommandButton run 
      Caption         =   "����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   21.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   5040
      TabIndex        =   6
      Top             =   5640
      Width           =   2175
   End
   Begin VB.ListBox lstCode 
      BackColor       =   &H00FF8080&
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   5100
      ItemData        =   "frmOutput.frx":0008
      Left            =   0
      List            =   "frmOutput.frx":0060
      TabIndex        =   4
      Top             =   600
      Width           =   3135
   End
   Begin MSFlexGridLib.MSFlexGrid varTable 
      Height          =   3495
      Left            =   3480
      TabIndex        =   1
      Top             =   1200
      Width           =   4695
      _ExtentX        =   8281
      _ExtentY        =   6165
      _Version        =   393216
      Rows            =   1
      Cols            =   4
      BackColor       =   33023
      ForeColorSel    =   16777215
      BackColorBkg    =   8454016
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "MS Sans Serif"
         Size            =   9.75
         Charset         =   0
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.CommandButton Command1 
      Caption         =   "�����������"
      BeginProperty Font 
         Name            =   "����"
         Size            =   10.5
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   495
      Left            =   7320
      TabIndex        =   0
      Top             =   4800
      Width           =   1455
   End
   Begin VB.Label Label6 
      AutoSize        =   -1  'True
      BackColor       =   &H00FF0000&
      BackStyle       =   0  'Transparent
      Caption         =   "�����"
      BeginProperty Font 
         Name            =   "����"
         Size            =   15.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   315
      Left            =   8400
      TabIndex        =   12
      Top             =   6360
      Width           =   990
   End
   Begin VB.Label Label5 
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "����ջ��"
      BeginProperty Font 
         Name            =   "����"
         Size            =   15.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   315
      Left            =   8280
      TabIndex        =   9
      Top             =   1920
      Width           =   1320
   End
   Begin VB.Label Label2 
      Alignment       =   1  'Right Justify
      AutoSize        =   -1  'True
      BackStyle       =   0  'Transparent
      Caption         =   "�ڴ棺"
      BeginProperty Font 
         Name            =   "����"
         Size            =   15.75
         Charset         =   134
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   315
      Left            =   8265
      TabIndex        =   7
      Top             =   120
      Width           =   990
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      BackColor       =   &H00FFFF80&
      BeginProperty Font 
         Name            =   "����"
         Size            =   18
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H000000C0&
      Height          =   360
      Left            =   2880
      TabIndex        =   5
      Top             =   240
      Width           =   210
   End
   Begin VB.Label Label4 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0FF&
      Caption         =   "�� �� �� ��"
      BeginProperty Font 
         Name            =   "����"
         Size            =   15.75
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00C00000&
      Height          =   315
      Left            =   240
      TabIndex        =   3
      Top             =   240
      Width           =   1935
   End
   Begin VB.Label Label3 
      AutoSize        =   -1  'True
      BackColor       =   &H00C0C0FF&
      Caption         =   "��  ��  ��"
      BeginProperty Font 
         Name            =   "����"
         Size            =   15.75
         Charset         =   134
         Weight          =   700
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      ForeColor       =   &H00FF0000&
      Height          =   315
      Left            =   4920
      TabIndex        =   2
      Top             =   840
      Width           =   1770
   End
End
Attribute VB_Name = "frmOutput"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub Command1_Click()
Me.Hide
End Sub

Private Sub Form_Load()
With varTable
   .Row = 0
   .Col = 0
   .Text = "���"
   .Col = 1
   .Text = "������"
   .Col = 2
   .Text = "����"
   .Col = 3
   .Text = "��ַ"
End With

End Sub

Private Sub HScroll1_Change()
s = HScroll1.Value
End Sub

Private Sub run_Click()
    Dim Label(100) As Integer
    Dim i As Integer, inText As String
    Dim command(1) As String
    output.Clear
    stack.Clear
    For i = 0 To lstCode.ListCount - 1
        lstCode.ListIndex = i
        If Right$(lstCode.List(i), 1) = ":" Then
            Label(Val(Mid$(lstCode.List(i), 6, Len(lstCode.List(i)) - 6))) = i '��label�����סÿ����ŵĵ�ַ
        End If
    Next i
    For i = 0 To lstCode.ListCount - 1
        lstCode.ListIndex = i
        Sleep
        If Check1.Value = 1 Then MsgBox "����"
        command(0) = Trim$(Left$(lstCode.List(i), 15))
        command(1) = Trim(Mid$(lstCode.List(i), 16))
        Select Case command(0)
        Case "LOAD"
            data.Row = Val(command(1))
            data.Col = 1
            stack.AddItem data.Text
            stack.ListIndex = stack.ListCount - 1
        Case "LOADI" 'LOADI a������aѹ�������ջ
            stack.AddItem command(1)
            stack.ListIndex = stack.ListCount - 1
        Case "STO" 'STO D ��������ջջ����Ԫ���ݴ���D,��ջ����Ԫ���ݱ��ֲ��䡣
            data.Row = Val(command(1))
            data.Col = 1
            data.Text = stack.Text
        Case "STI" 'STI D ��������ջջ����Ԫ���ݴ���D,��ջ����Ԫ���ݳ�ջ��
            data.Row = Val(command(1))
            data.Col = 1
            data.Text = stack.Text
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "ADD" 'ADD����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ӣ�������ջ����
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) + Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "SUB" 'SUB ����ջ����Ԫ��ȥջ����Ԫ���ݲ���ջ��������ջ����
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) - Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "MULT" 'MULT   ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ����ˣ�������ջ����
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) * Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "DIV" 'DIV    ����ջ����Ԫ��ջ����Ԫ���ݳ�ջ�������������ջ����
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) \ Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "BR" 'BR    lab  ������ת�Ƶ�lab
            i = Label(Val(Mid$(command(1), 6, 10)))
            stack.ListIndex = stack.ListCount - 1
        Case "BRF" 'BRF  lab  ���ջ����Ԫ�߼�ֵ����Ϊ�٣�0����ת�Ƶ�lab
            If stack.Text = "False" Then i = Label(Val(Mid$(command(1), 6, 10)))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "EQ" 'EQ  ��ջ������Ԫ�����ڱȽϣ�����������٣�1��0������ջ��
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) = Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "NOTEQ" 'NOTEQ ��ջ������Ԫ�������ڱȽϣ�����������٣�1��0������ջ��
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) <> Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "GT" 'GT    ��ջ������ջ������������ջ����1��������0
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) > Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "LES" 'LES  ��ջ��С��ջ������������ջ����1��������0
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) < Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "GE" 'GE  ��ջ�����ڵ���ջ������������ջ����1��������0
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) >= Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "LE" 'LE  ��ջ��С�ڵ���ջ������������ջ����1��������0
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) <= Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "AND" 'AND ��ջ������Ԫ���߼������㣬����������٣�1��0������ջ��
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) And Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "OR" 'OR  ��ջ������Ԫ���߼������㣬����������٣�1��0������ջ��
            stack.List(stack.ListCount - 2) = Val(stack.List(stack.ListCount - 2)) Or Val(stack.List(stack.ListCount - 1))
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "NOT" 'NOT  ��ջ�����߼�ֵȡ��
            stack.List(stack.ListCount - 1) = Not stack.List(stack.ListCount - 1)
        Case "IN" 'IN �ӱ�׼�����豸�����̣�����һ���������ݣ�����ջ��
            inText = InputBox("�������������ݣ�")
            stack.AddItem inText
            stack.ListIndex = stack.ListCount - 1
        Case "OUT" 'OUT ��ջ����Ԫ���ݳ�ջ�����������׼����豸�ϣ���ʾ������
            output.AddItem stack.Text
            stack.RemoveItem stack.ListCount - 1
            stack.ListIndex = stack.ListCount - 1
        Case "STOP" 'STOP ִֹͣ��
            MsgBox "���н���"
            Exit Sub
        End Select
    Next i
End Sub



Private Sub Timer1_Timer()
s = Val(HScroll1.Value) * 1000
End Sub
