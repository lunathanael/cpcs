param (
    [string]$fileName
)

if (-not $fileName) {
    Write-Error "No file name provided. Usage: .\scriptName.ps1 [-fileName] <name>"
    exit
}

$templatePath = "./template.cpp"
$newFilePath = "./${fileName}.cpp"

Copy-Item -Path $templatePath -Destination $newFilePath

Write-Host "File copied to ${newFilePath}"
