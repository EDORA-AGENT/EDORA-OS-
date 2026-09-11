$ErrorActionPreference = 'Stop'

$repo = (Get-Location).Path
$buildDir = Join-Path $repo 'build'
$bootAsm = Join-Path $repo 'boot\32\boot.asm'
$kernelEntry = Join-Path $repo 'kernel\real32\kernel_entry.asm'
$kernelMain = Join-Path $repo 'kernel\real32\kernel_main.cpp'
$vgaCpp = Join-Path $repo 'kernel\real32\drivers\vga.cpp'
$keyboardCpp = Join-Path $repo 'kernel\real32\drivers\keyboard.cpp'
$linker = Join-Path $repo 'kernel\real32\linker.ld'
$imgPath = Join-Path $buildDir 'edora.img'

New-Item -ItemType Directory -Force -Path $buildDir | Out-Null

$clang = 'D:\CodeBlocks\MinGW\bin\clang++.exe'
$nasm = 'D:\CodeBlocks\MinGW\bin\nasm.exe'
$lld = 'D:\CodeBlocks\MinGW\bin\ld.lld.exe'
$qemu = 'C:\Program Files\qemu\qemu-system-i386.exe'

Write-Host '==> Assembling bootloader'
& $nasm -f bin $bootAsm -o (Join-Path $buildDir 'boot.bin')

Write-Host '==> Assembling kernel entry'
& $nasm -f elf32 $kernelEntry -o (Join-Path $buildDir 'kernel_entry.o')

Write-Host '==> Compiling keyboard driver'
& $clang --target=i386-unknown-elf -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -fno-stack-check -m32 -c $keyboardCpp -o (Join-Path $buildDir 'keyboard.o')

Write-Host '==> Compiling VGA driver'
& $clang --target=i386-unknown-elf -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -fno-stack-check -m32 -c $vgaCpp -o (Join-Path $buildDir 'vga.o')

Write-Host '==> Compiling kernel main'
& $clang --target=i386-unknown-elf -ffreestanding -fno-exceptions -fno-rtti -fno-stack-protector -fno-stack-check -m32 -c $kernelMain -o (Join-Path $buildDir 'kernel_main.o')

Write-Host '==> Linking kernel'
& $lld -m elf_i386 -T $linker --oformat binary -o (Join-Path $buildDir 'kernel.bin') (Join-Path $buildDir 'kernel_entry.o') (Join-Path $buildDir 'kernel_main.o') (Join-Path $buildDir 'keyboard.o') (Join-Path $buildDir 'vga.o')

Write-Host '==> Producing disk image'
$boot = [System.IO.File]::ReadAllBytes((Join-Path $buildDir 'boot.bin'))
$kernel = [System.IO.File]::ReadAllBytes((Join-Path $buildDir 'kernel.bin'))
$img = New-Object byte[] (512 * 32)
[System.Buffer]::BlockCopy($boot, 0, $img, 0, [Math]::Min($boot.Length, $img.Length))
[System.Buffer]::BlockCopy($kernel, 0, $img, 512, [Math]::Min($kernel.Length, $img.Length - 512))
[System.IO.File]::WriteAllBytes($imgPath, $img)

Write-Host '==> Booting in QEMU'
& $qemu -drive file=$imgPath,format=raw -boot c
