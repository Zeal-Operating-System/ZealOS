Remove-Item -Recurse -Force .\src\*
Copy-Item -Recurse -Force Z:\* .\src\
Remove-Item .\Zenith-latest*.iso
Move-Item .\src\Tmp\MyDistro.ISO.C .\Zenith-latest-$(Get-Date -Format "yyyy-MM-dd-HH_mm_ss").iso
