#!/bin/zsh

echo "Compilando o programa...\n"

# Compilação dos arquivos fonte
gcc -o megasena main.c megasena.c

# Verifica se a compilação foi bem sucedida
if [ $? -eq 0 ]; then
    echo "Compilação bem sucedida!"
else
    echo "\nErro durante a compilação."
fi
