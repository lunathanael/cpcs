param(
    [String]$src = "",
    [Switch]$fast
)

$target = if ($fast) { "fast" } else { "all" }

if ($src -eq "") {
    make $target
} else {
    make $target SRC=$src
}

Get-Content input.txt | .\a.exe
