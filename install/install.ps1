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
        "ninja-build.ninja"
    )
    foreach ($pkg in $packages) {
        Write-Host "Installing $pkg"
        winget install --id $pkg --accept-package-agreements --accept-source-agreements --silent
    }
    Write-Host "Installing LLVM.LLVM"
    winget install --id "LLVM.LLVM" --version "19.1.7" --accept-package-agreements --accept-source-agreements --silent
    $env:Path += ";C:\Program Files\Git\bin;C:\Program Files\CMake\bin;C:\Program Files\LLVM\bin;C:\Program Files\Ninja;"
}

function Setup-MSVCEnvironment {
    Write-Host "Configuring MSVC environment..."
    $vswhere = "$env:ProgramFiles(x86)\Microsoft Visual Studio\Installer\vswhere.exe"
    if (-not (Test-Path $vswhere)) {
        Invoke-WebRequest -Uri "https://aka.ms/vs/17/release/vswhere.exe" -OutFile (New-Item -Force -Path $vswhere -ItemType File)
    }
    $vsPath = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $vsPath) {
        $url = "https://aka.ms/vs/17/release/vs_BuildTools.exe"
        $installer = "$env:TEMP\vs_BuildTools.exe"
        Invoke-WebRequest -Uri $url -OutFile $installer
        Start-Process -FilePath $installer -ArgumentList "--quiet","--wait","--norestart","--add","Microsoft.VisualStudio.Workload.VCTools","--includeRecommended" -Wait
        $vsPath = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    }
    $vcvars = Join-Path $vsPath "VC\Auxiliary\Build\vcvars64.bat"
    if (Test-Path $vcvars) {
        $envDump = cmd /c "`"$vcvars`" && set"
        foreach ($line in $envDump) {
            if ($line -match "^(.*?)=(.*)$") {
                Set-Item -Force -Path "Env:\$($matches[1])" -Value $matches[2]
            }
        }
    }
}

function Install-Logos {
    Write-Host "Installing Logos..."
    Push-Location $TEMP_DIR
    git clone -q --depth 1 -b dev https://github.com/rmordechay/logos.git
    Set-Location logos
    $buildDir = Join-Path $PWD "build"
    $workers = [Environment]::ProcessorCount
    cmake -S . -B $buildDir -G "Ninja" -DCMAKE_C_COMPILER="C:/Program Files/LLVM/bin/clang.exe" -DCMAKE_CXX_COMPILER="C:/Program Files/LLVM/bin/clang++.exe" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX="$INSTALL_PREFIX" -DLOGOS_RELEASE=ON
    cmake --build $buildDir --parallel $workers
    cmake --install $buildDir
    Pop-Location
}

Install-Dependencies
Setup-MSVCEnvironment
Install-Logos

Write-Host ""
Write-Host "Installation done."
Write-Host "- $INSTALL_PREFIX\bin\lgs.exe"
Write-Host "- $INSTALL_PREFIX\lib\lgs_runtime.dll"

Cleanup
