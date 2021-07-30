Remove-Item -Recurse -Force .\src\*
Copy-Item -Recurse -Force Z:\* .\src\
Remove-Item .\ZealOS-*.iso
Move-Item .\src\Tmp\MyDistro.ISO.C .\ZealOS-$(Get-Date -Format "yyyy-MM-dd-HH_mm_ss").iso
