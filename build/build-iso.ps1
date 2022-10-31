# make sure we are in the correct directory
$currentDir=Get-Location
if ("$currentDir" -ne "$PSScriptRoot")
{
    try
    {
        pushd "$PSScriptRoot"
        . $PSCommandPath $args
    }
    finally
    {
        popd
    }
    exit
}

if (!([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator))
{
    Write-Output "This script must be run as Adminstrator. Press ENTER to exit."; Read-Host; exit
}

if (!(Get-Command qemu-system-x86_64.exe -errorAction SilentlyContinue))
{
    $env:Path += ";C:\Program Files\qemu;"
    if (!(Get-Command qemu-system-x86_64.exe -errorAction SilentlyContinue))
    {
        Write-Output "QEMU is not installed, or not set in \$PATH. Press ENTER to exit."; Read-Host; exit
    }
}
Write-Output "QEMU installation found."

$hyperv = Get-WindowsOptionalFeature -FeatureName Microsoft-Hyper-V-All -Online
if (!($hyperv.State -eq "Enabled"))
{
    Write-Host "Hyper-V is disabled. Enable Hyper-V and reboot before running this script. Press ENTER to exit."; Read-Host; exit
}

$TMPDISK = "$env:TEMP\ZealOS.vhdx"

function Mount-TempDisk
{
    $global:QEMULETTER = ((Mount-DiskImage -ImagePath $TMPDISK -Access ReadWrite) | Get-Disk | Get-Partition).DriveLetter
}

function Unmount-TempDisk
{
    $be_quiet = Dismount-DiskImage -ImagePath $TMPDISK
}

Write-Output "Making temp vdisk, running auto-install..."

qemu-img create -f vhdx $TMPDISK 1024M
fsutil sparse setflag $TMPDISK 0
fsutil sparse queryflag $TMPDISK 
qemu-system-x86_64 -machine q35,accel=whpx,kernel-irqchip=off -drive format=vhdx,file=$TMPDISK -m 2G -rtc base=localtime -cdrom AUTO.ISO -device isa-debug-exit

Write-Output "Copying all src/ code into vdisk Tmp/OSBuild/ ..."

Remove-Item "..\src\Home\Registry.ZC" -errorAction SilentlyContinue
Remove-Item "..\src\Home\MakeHome.ZC" -errorAction SilentlyContinue
Remove-Item "..\src\Boot\Kernel.ZXE" -errorAction SilentlyContinue
Mount-TempDisk
New-Item -Path "${QEMULETTER}:\Tmp\" -Name "OSBuild" -ItemType "directory"
Copy-Item -Path "..\src\*" -Destination "${QEMULETTER}:\Tmp\OSBuild\" -Recurse -Force
Unmount-TempDisk

Write-Output "Rebuilding kernel headers, kernel, OS, and building Distro ISO ..."

qemu-system-x86_64 -machine q35,accel=whpx,kernel-irqchip=off -drive format=vhdx,file=$TMPDISK -m 2G -rtc base=localtime -device isa-debug-exit

Write-Output "Extracting ISO from vdisk..."

Remove-Item "ZealOS-*.iso" -errorAction SilentlyContinue
Mount-TempDisk
$ZEALISO = "ZealOS-PublicDomain-BIOS-" + (Get-Date -Format "yyyy-MM-dd-HH_mm_ss").toString() + ".iso"
Copy-Item "${QEMULETTER}:\Tmp\MyDistro.ISO.C" -Destination $ZEALISO 
Unmount-TempDisk

Remove-Item $TMPDISK
Write-Output "Finished."
Get-ChildItem "ZealOS*.iso"
