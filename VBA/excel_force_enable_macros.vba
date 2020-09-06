Private Sub Workbook_BeforeClose(Cancel As Boolean)
' Runs after the user goes to close Excel but before any "Save" dialog
' may appear.
'
' Created by: TeachExcel.com
'

' Helper to show you when it runs.
'MsgBox "Close"

' Make the macro run faster by disabling screen updating
Application.ScreenUpdating = False
' Make sure no other events like this one run while we are working here
Application.EnableEvents = False

' Check if changes were made since the worksheets were made visible.
' Store the result into a variable.
' One line IF statement
If ThisWorkbook.Saved = True Then wbSaved = True

' Hide the worksheets and show the welcome screen.
Call Hide_Sheets

' Check if the workbook was saved before the sheets were hidden.
' This value is stored in the wbSaved variable before the worksheets
' are hidden because the process of hiding the worksheets will cause
' Excel to say that changes were made, even though the user himself
' didn't make any changes - all changed were as a result of hiding
' the worksheets and we don't want the user to have to see the Save
' dialog for this since it is not an expected behavior.
' (This can be confusing, I know!)
If wbSaved = True Then

    ' Save the workbook now since sheets were just hidden and we don't want the user
    ' to see them the next time they open this workbook unless they have macros enabled.
    ThisWorkbook.Save
    
End If

' Enable screen updating so Excel works like normal.
Application.ScreenUpdating = True
' Enable events again so everything works as expected
Application.EnableEvents = True

End Sub

Private Sub Workbook_Open()
' Runs when the workbook is opened or immediately after macros are enabled for the first time
' after the workbook is opened.
'
' Created by: TeachExcel.com
'

' Helper to show you when it runs.
'MsgBox "Open"

' Make the macro run faster by disabling screen updating
Application.ScreenUpdating = False
' Make sure no other events like this one run while we are working here
Application.EnableEvents = False

' Call the macro to show the worksheets
Call Show_Sheets

' Enable screen updating so Excel works like normal.
Application.ScreenUpdating = True
' Enable events again so everything works as expected
Application.EnableEvents = True

End Sub
Sub Show_Sheets()
' Show all worksheets except the splash screen
' Show worksheets before hiding the splash screen.
' - must always have at least 1 worksheet visible at any time
'
' Created by: TeachExcel.com
'

' Loop through all worksheets
For Each ws In Sheets

    ' Check if this is the welcome screen or not
    If ws.Name <> "Welcome" Then
        
        ' Show the worksheet
        ws.Visible = xlSheetVisible
        
    End If
    
Next ws

' Hide the welcome screen
Sheets("Welcome").Visible = xlSheetVeryHidden

' Set the workbook as "saved" even though the changes were not saved.
' - the "changes" were to unhide the worksheets and hide the welcome screen.
' - this allows us to not show the user the "Save" dialog if he closes the
'   workbook without actually changing anything in the worksheet.
ActiveWorkbook.Saved = True

End Sub
Sub Hide_Sheets()
' Hide all worksheets except the splash screen
' Show the splash screen before hiding the other worksheets.
' - must always have at least 1 worksheet visible at any time
'
' Created by: TeachExcel.com
'

' Show the welcome screen
Sheets("Welcome").Visible = xlSheetVisible

' Loop through all worksheets
For Each ws In Sheets

    ' Check if this is the welcome screen or not
    If ws.Name <> "Welcome" Then
        
        ' Hide the worksheet
        ws.Visible = xlSheetVeryHidden
        
    End If
    
Next ws

End Sub
