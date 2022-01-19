# Autenticador



# Sobre o projeto

<p> O projeto foi criado como prática para a biblioteca GTK+, todo o seu desenvolvimento se encontra nesse repositório. <p>

<p> Esse trabalho se baseia nos autenticadores mais simples, no qual possui uma interface em que você pode se logar, cadastrar e posteriormente tentar entrar com sua autenticação. <p>

## Design
<p><div align = "center" >
<img src =  "https://github.com/TheeViolinist/Autenticacao/blob/main/src/assets/to_readme/programa.png" height = "350px" width = "200px">
</div><p>

## Programas utilizados
* Visual Stdio Code

## Linguagens utilizadas
* C

### Como executar o projeto

<p> Para executá-lo é necessário baixar o arquivo usuários.txt e o programa compilado que é o autenticador.c, além disso possuir gcc ou g++ e a biblioteca GTK+ ou GTK 3.0, no qual poderá ser baixado no seguinte link: https://www.gtk.org/ . <p>

1. Vá até o diretório dos arquivos baixados e execute o comando

```bash
	gcc -o autenticador  autenticador.c `pkg-config --cflags --libs gtk+-3.0` (linux)
	g++ -o autenticador  autenticador.c `pkg-config --cflags --libs gtk+-3.0` (windows)
	./autenticador
```
<p> Após executar todo os passos, é só se divertir. 	<p>

# Colaboradores
* Leandro Lucas de Oliveira Bandeira

