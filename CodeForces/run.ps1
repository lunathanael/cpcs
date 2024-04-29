param(
    [String]$src = "",
    [Switch]$fast,
    [Switch]$check
)

$target = if ($fast) { "fast" } else { "all" }

if ($src -eq "") {
    make $target
} else {
    make $target SRC=$src
}

$output = Get-Content input.txt | .\a.exe

if ($check) {
    $tempFile = "temp_output.txt"
    $output | Out-File $tempFile
    
    $expectedLines = Get-Content output.txt
    $actualLines = Get-Content $tempFile
    $maxLength = [Math]::Max($expectedLines.Length, $actualLines.Length)
    $differencesFound = $False

    for ($i = 0; $i -lt $maxLength; $i++) {
        $expectedLine = $expectedLines[$i]
        $actualLine = $actualLines[$i]

        if ($expectedLine -ne $actualLine) {
            if (-not $differencesFound) {
                Write-Host "Differences found:"
                $differencesFound = $true
            }
            if ($actualLine -ne $null) {
                Write-Host "Actual (line $(($i + 1)))    >>" -ForegroundColor Red -NoNewline
                Write-Host "$actualLine\n"
            }
            if ($expectedLine -ne $null) {
                Write-Host "Expected (line $(($i + 1)))  <<" -ForegroundColor Green -NoNewline
                Write-Host "$expectedLine\n"
            }
        }
    }
    if (-not $differencesFound) {
        Write-Host "No differences found."
    }
    
    Remove-Item $tempFile
} else {
    $output
}
