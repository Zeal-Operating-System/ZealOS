$dir = "~\Projects\ZenithOS"
Remove-Item -Recurse -Force ${dir}\src\*
Copy-Item -Recurse -Force Z:/* ${dir}\src\
Remove-Item ${dir}\*.iso
Move-Item ${dir}\src\Tmp\MyDistro.ISO.C ${dir}\Zenith-latest-$(Get-Date -Format "yyyy-MM-dd-HH_mm_ss").iso

