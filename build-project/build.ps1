$arch = ""
switch ($env:PROCESSOR_ARCHITECTURE) {
    "AMD64" { $arch = "x86_64" }
    "ARM64" { $arch = "aarch64" }
    "x86" { $arch = "i386" }
    default {
        Write-Error "Unsupported architecture: $($env:PROCESSOR_ARCHITECTURE)"
        exit 1
    }
}

$workers = (Get-CimInstance Win32_ComputerSystem).NumberOfLogicalProcessors

$tempDir = "tmp"
if (Test-Path $tempDir) {
    Remove-Item -Recurse -Force $tempDir
}
New-Item -ItemType Directory -Path $tempDir | Out-Null
Set-Location $tempDir

Invoke-WebRequest -Uri "https://www.antlr.org/download/antlr4-cpp-runtime-4.13.2-source.zip" -OutFile "antlr.zip"
Expand-Archive -LiteralPath "antlr.zip" -DestinationPath "antlr"

cmake -S antlr -B antlr/build -DCMAKE_BUILD_TYPE=Release
cmake --build antlr/build -maxcpucount:$workers

$antlrLibPath = "antlr\build\runtime\libantlr4-runtime.4.13.2.dll"
$destDir = "..\..\external\lib\$arch\windows"
$destLibPath = Join-Path $destDir "libantlr4.dll"

if (-not (Test-Path $destDir)) {
    New-Item -ItemType Directory -Path $destDir -Force | Out-Null
}

Copy-Item $antlrLibPath -Destination $destLibPath -Force
