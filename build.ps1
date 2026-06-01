Write-Host "Compilando projeto C (compilação recursiva)..."

$utilsCFiles = Get-ChildItem -Path ./src -Recurse -Include *.c *.h | ForEach-Object { $_.FullName }

$sourceFiles = @("main.c") + $utilsCFiles

Write-Host "Arquivos fonte:"
$sourceFiles | ForEach-Object { Write-Host "  $_" }

gcc $sourceFiles -o main

if ($?) {
    Write-Host "`nCompilação concluída com sucesso!"
    Write-Host "`nExecutando o programa:"
    ./main
} else {
    Write-Host "`nErro na compilação."
}