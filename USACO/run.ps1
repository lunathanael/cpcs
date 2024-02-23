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
    
    $compareResult = Compare-Object -ReferenceObject (Get-Content output.txt) -DifferenceObject (Get-Content $tempFile)
    
    if ($compareResult) {
        Write-Host "Differences found between output.txt"
        $compareResult | ForEach-Object { Write-Host $_.InputObject }
    } else {
        Write-Host "No differences found. Outputs are identical."
    }
    
    Remove-Item $tempFile
} else {
    $output
}
