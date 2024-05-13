# Mega-Sena

> Esse projeto pertence ao trabalho da AV2 da matéria de TIC do 1º período de CCOMP da Unifeso

### Compilando e rodando o programa

Foi criado um script, testado somente no ZSH, para auxiliar na execução do software

```bash
./build.sh
```

Esse script fará as seguintes coisas:
- Limpar o terminal para não confundir o que pertence ao build anterior;
- Compilar os arquivos `main.c` e `megasena.c` para o arquivo `megasena`;
- Se a compilação for bem sucedida, o script irá rodar o programa.
- Se a compilação falhar, o script irá mostrar uma mensagem de erro.