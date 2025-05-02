param (
    [string]$fileName
)

$defaultName = "main"

if (-not $fileName) {
    Write-Warning "No file name provided. Using default name: ${defaultName}"
    $fileName = $defaultName
}

$templatePath = "./template.txt"
$newFilePath = "./${fileName}.cpp"

Copy-Item -Path $templatePath -Destination $newFilePath

Write-Host "File copied to ${newFilePath}"
