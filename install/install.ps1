#!/usr/bin/env pwsh

$INSTALL_PREFIX = $env:INSTALL_PREFIX
if (-not $INSTALL_PREFIX) {
    $INSTALL_PREFIX = "C:\Program Files\Logos"
}

$TEMP_DIR = New-Item -ItemType Directory -Path ([System.IO.Path]::GetTempPath()) -Name ("logos_install_" + [System.Guid]::NewGuid().ToString())

function Cleanup {
    Write-Host "Cleaning up"
    Remove-Item -Recurse -Force $TEMP_DIR -ErrorAction SilentlyContinue
}

function Install-Dependencies {
    Write-Host "Installing dependencies..."

    $packages = @(
        "Git.Git",
        "Kitware.CMake",
        "LLVM.LLVM"
    )

    foreach ($pkg in $packages) {
        Write-Host "Installing $pkg..."
        winget install --id $pkg --accept-package-agreements --accept-source-agreements --silent
    }

    $env:Path = "C:\Program Files\Git\bin;C:\Program Files\CMake\bin;C:\Program Files\LLVM\bin;" + $env:Path
}

function Install-Logos {
    Write-Host "Installing Logos..."

    Push-Location $TEMP_DIR

    git clone -q --depth 1 -b dev https://github.com/rmordechay/logos.git
    Set-Location logos

    $buildDir = Join-Path $PWD "build"
    $workers = [Environment]::ProcessorCount

    cmake -S . -B $buildDir -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" -DLOGOS_RELEASE=ON
    cmake --build $buildDir --parallel $workers
    cmake --install $buildDir

    Pop-Location
}

#Install-Dependencies
Install-Logos

Write-Host ""
Write-Host "Installation done."
Write-Host "- $INSTALL_PREFIX\bin\lgs.exe"
Write-Host "- $INSTALL_PREFIX\lib\lgs_runtime.dll"

Cleanup