Attribute VB_Name = "Module1"
Option Explicit
Public s As Long

Public Sub Sleep()
Dim t As Long
For t = 0 To s
Next t
DoEvents
End Sub
