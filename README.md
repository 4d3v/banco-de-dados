# Banco de Dados do Zero
*Criando banco de dados do zero com o objetivo de melhorar conhecimentos em C++<br>
*Bando de dados atualmente só performa com std::strings (STL)<br>
*Atualizações e novas features serão implementadas conforme for aprendendo novos conceitos relativos a este projeto<br>
*No momento é recomendado o uso da IDE Visual Studio para construir o projeto (build project)<br>
*Readme completo em breve

*Diretório bd_cli é relativo a linha de comando (CLI), bd_testes é relacionado a testes de unidade

### Usando a Linha de Comando (CLI)
Após clonar o repositório e construir projeto bd_cli ou construir solução inteira (build)

```sh
#cd bin/<Sistema Operacional>/Debug/
#Exemplo:
cd bin/Win32/Debug

# Criando Banco de dados
./bd_cli.exe -c -n NOME_DO_MEU_BD

# Guardar uma chave (key value pair)
./bd_cli.exe -s -n NOME_DO_MEU_BD -k "MINHA CHAVE" -v "MEU VALOR"

# Acessar valor guardado
./bd_cli.exe -g -n NOME_DO_MEU_BD -k "MINHA CHAVE"
```

### Rodando os Testes
Após clonar o repositório e construir projeto bd_testes ou construir solução inteira (build)

#1ª Opção IDE<br>
Acessar no Visual Studio o menu "TEST -> Test Explorer" e clicar botão "Run All Tests"

#2ª Opção CLI<br>
```sh
#cd bin/<Sistema Operacional>/Debug/
#Exemplo:
cd bin/Win32/Debug
./bd_tests.exe
```
