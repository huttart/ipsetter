'   Set WshShell = CreateObject("WScript.Shell" ) 
'   WshShell.Run """C:\Users\Hutta\AppData\Local\Programs\IP_SETTER_GMC\IP_SETTER_GMC.exe""", 0 
'   Set WshShell = Nothing

Dim objShell
Set objShell = WScript.CreateObject( "WScript.Shell" )
objShell.Run("""C:\Users\Hutta\AppData\Local\Programs\IP_SETTER_GMC\IP_SETTER_GMC.exe""")
Set objShell = Nothing