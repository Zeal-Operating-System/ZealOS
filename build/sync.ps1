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

$choice = $args[0]

function print_usage()
{
    Write-Output "Usage: sync.ps1 [ repo | vm ]"
    Write-Output ""
    Write-Output " repo - overwrites src/ with virtual disk contents."
    Write-Output " vm - overwrites virtual disk with src/ contents."
    Write-Output ""
    exit
}

if ($args.count -eq 0)
{
    print_usage
}
if ($choice -ne 'repo' -and $choice -ne "vm")
{
    print_usage
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

# Set this
$ZEALDISK=""
# Examples:
#$ZEALDISK = "$HOME\VirtualBox VMs\ZEAL\ZEAL.vdi"
#$ZEALDISK="$HOME\vmware\ZealOS\ZealOS.vmdk"
#$ZEALDISK="ZealOS.qcow2"

if ($ZEALDISK -eq "")
{
    Write-Output "Please edit this script with the full path to your ZealOS virtual disk. Press ENTER to exit."; Read-Host; exit
}
if (!(Test-Path -Path $ZEALDISK))
{
    Write-Output "$ZEALDISK is not a path to a file. Press ENTER to exit."; Read-Host; exit
}

$TEMPZEALDISK = "$env:TEMP\TempZealDisk.vhd"
qemu-img convert -O vpc $ZEALDISK $TEMPZEALDISK
fsutil sparse setflag $TEMPZEALDISK 0
fsutil sparse queryflag $TEMPZEALDISK 

function Mount-ZealDisk
{
    $global:ZEALLETTER = ((Mount-DiskImage -ImagePath $TEMPZEALDISK -Access ReadWrite) | Get-Disk | Get-Partition -PartitionNumber 1).DriveLetter
}

function Unmount-ZealDisk
{
    $be_quiet = Dismount-DiskImage -ImagePath $TEMPZEALDISK
}

switch ($choice)
{
    "repo"
    {
        Write-Output "Emptying src..."
        Remove-Item "..\src\*" -Recurse -Force
        Mount-ZealDisk
        Write-Output "Copying vdisk root to src..."
        Copy-Item -Path "${ZEALLETTER}:\*" -Destination "..\src\" -Recurse -Force
        Remove-Item "..\src\Boot\BootMHD2.BIN"
        Remove-Item "..\src\Boot\KERNEL.ZXE"
        Unmount-ZealDisk
        Remove-Item $TEMPZEALDISK
        Write-Output "Finished."
    }

    "vm"
    {
        Write-Output ""
        Write-Output "TODO: Windows sync.ps1 vm"
        Write-Output "since this is not implemented yet, you can instead use build-iso.ps1"
        Write-Output "to make a Distro ISO, and use that to install changes over your existing VM."
        Write-Output ""
        <#
        Mount-ZealDisk
        Write-Output "Copying src to vdisk..."
        Copy-Item -Path "..\src\*" -Destination "${ZEALLETTER}:\" -Recurse -Force
        Unmount-ZealDisk
        switch ([System.IO.Path]::GetExtension($ZEALDISK))
        {
            ".vdi" {qemu-img convert -O vdi $TEMPZEALDISK $ZEALDISK} # Non-working... re-building a HDD changes file UUID, which confuses Virtualbox...
        }
        Write-Output "Finished."
        #>
    }
}