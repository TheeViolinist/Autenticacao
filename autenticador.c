#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>




#define MAX_NOME 100
#define MAX_USUARIOS 100

GtkWidget *email;   /*  Variável que irá armazenar o email do usuário digitado na interface */
GtkWidget *label_saida;
GtkWidget *label_entrada;
GtkWidget *senha;      /*   Variável que irá armazenar a senha do usuário digitado na interface */
char emailUsuario[MAX_NOME];     /*  Email do usuário    */
char senhaUsuario[MAX_NOME];       /*  Onde será armazenado a senha do usuário */
FILE *fpUsuarios = NULL;            /*  Criação de um stream para um arquivo onde estão os dados dos usuários   */




/*  Struct responsável por armazenar os dados do usuário    */
typedef struct
{
    char nome[MAX_NOME];    /*  Nome do usuário */
    char senhaUsu[MAX_NOME];    /*  Senha criada pelo usuário   */
    int autenticacao1;       /*  primeira autenticação do usuário    */
    int codigo;                 /*  Código do usuário   */

}tConta;


/****
 * RetiraQuebra(): Função responsável por retirar a quebra de linha de todas as strings digitadas pelo usuário  
 * 
 * 
 * 
 * Parâmetros:
 *                  str(entrada e saída): string que será modificada
 * 
 * Retorno:
 *                  nenhum
 ****/

void RetiraQuebra(char *str)
{
    if(str[strlen(str) - 1] == '\n')
    {
        str[strlen(str) - 1] = '\0';
    }
}


gboolean ArmazenaInformacoes(GtkButton *button, gpointer data)
{

    /*  Estamos pegando o email e a senha digitada na interface e armazenando em duas variáveis globais */
    strcpy(emailUsuario, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(senhaUsuario, gtk_entry_get_text(GTK_ENTRY(senha)));
    return FALSE;
}


gboolean ProcuraInformacao(GtkButton *button, gpointer data)
{
    char bufferEmail[MAX_NOME];
    char bufferSenha[MAX_NOME];

    rewind(fpUsuarios);
    while(1)
    {
        fgets(bufferEmail, MAX_NOME, fpUsuarios);
        RetiraQuebra(bufferEmail);
        fgets(bufferSenha, MAX_NOME, fpUsuarios);
        RetiraQuebra(bufferSenha);
        if(strcmp(bufferEmail, emailUsuario) == 0 && strcmp(bufferSenha, senhaUsuario) == 0)
        {
            printf("As informacoes estao corretas.\n");
            
        }
        break;
        

    }
    return FALSE;
}



/****
 * CriarConta(): Função responsável pela criação de conta do usuário
 * 
 * 
 * Parâmetros:
 *               ptrUsuarios(entrada e saída): ponteiro do tipo estruturado do usuário
 * 
 * 
 * Retorno:
 *                  nenhum
 * 
 ****/
void CriarConta(tConta *ptrUsuarios)
{
    /*  Dois nomes, porque será necessário verificar se o usuário digitou a senha corretamente  */
    char senha1[MAX_NOME], senha2[MAX_NOME];
    printf("Digite o seu email: ");
    fgets(ptrUsuarios->nome, MAX_NOME, stdin);
    RetiraQuebra(ptrUsuarios->nome);
    printf("Digite sua senha: ");
    fgets(senha1, MAX_NOME, stdin);
    RetiraQuebra(senha1);
    while(1)
    {
        printf("Digite a senha novamente: ");
        fgets(senha2, MAX_NOME, stdin);
        RetiraQuebra(senha2);
        /*  Comparo se as duas senhas digitas pelo usuário são iguais   */
        if(strcmp(senha1, senha2) == 0)
        {
            /*  Se forem, vamos colocá-la como senha do usuário */
            strcpy(ptrUsuarios->senhaUsu, senha2);
            break;

        }
        /*  Caso não seja, o loop será infinito até que o usuário digite uma senha correta  */
        else
        {
            printf("\n senha digitada errada\n");
            printf("\n");
        }
    }
    
    

}


/****
 * PrimeiraAutenticacao(): Primeira autenticação do usuário 
 * 
 * 
 * Parâmetros:
 *                      ptrUsuarios(saída): local que será armazenado a primeira autenticação do usuário
 * 
 * 
 * Retorno:
 *                      nenhum
 ****/
void PrimeiraAutenticao(tConta *ptrUsuarios)
{

    /*  Primeira senha de autenticacao    */
    /*  Inicialização da semennte para sempre gerar um número aleatório */
    srand(time(NULL));
    /*  Gerando um número aleatório de 4 digitos    */
    ptrUsuarios->autenticacao1 = rand() % 1000 + 1000;

}
/*  Função para anexar os dados da criação da conta */
void AnexaDados(tConta *ptrUsuarios, FILE *fpUsuario)
{


    fprintf(fpUsuario,"%s\n%s\n%d\n%d\n", ptrUsuarios->nome, ptrUsuarios->senhaUsu, ptrUsuarios->autenticacao1, ptrUsuarios->codigo);
    

}


int main(int argc, char **argv)
{
    tConta usuarios[MAX_USUARIOS];      /*  Quantidade de usuários do tipo estruturado criado   */

    

    fpUsuarios = fopen("usuarios.txt", "r+");    /*  Abertura para leitura do arquivo    */
    if(fpUsuarios == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }
    
    int n = 0;  /*  Codigo do proximo usuario que será cadastrado   */


    /*  Função responsável pela leitura dos dados e retornar o valor de n   */
    while(1)
    {
        fgets(usuarios[n].nome, MAX_NOME, fpUsuarios);
        fgets(usuarios[n].senhaUsu, MAX_NOME, fpUsuarios);
        fscanf(fpUsuarios, "%d%*c", &usuarios[n].autenticacao1);
        fscanf(fpUsuarios, "%d%*c", &usuarios[n].codigo);
        if(feof(fpUsuarios))
        {
            break;
        }

        n++;
    }
    /*  Retorna o próximo código de usuário que será cadastrado */
    usuarios[n].codigo = n;
   

    GtkWidget *janela;  /*  Todos os componentes, como botões e janela são da classe GtkWidget  */
    GtkWidget *conteudo;
    GtkWidget *label_entrada_senha;
    GtkWidget *label_entrada_email;
    GtkWidget *botaoConectar;
    GtkWidget *botaoSair;
    gtk_init(&argc, &argv); /*  Inicialização da biblioteca */

    janela=gtk_window_new(GTK_WINDOW_TOPLEVEL); /*  Anteriormente foi declarado um ponteiro do tipo gtkWidget   */
    /*  Agora essa janela é do tipo window  */
    gtk_window_set_position(GTK_WINDOW(janela), GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(janela), 640, 480);

    g_signal_connect(G_OBJECT(janela), "destroy", G_CALLBACK(gtk_main_quit), NULL);/*  Precisamos acrescentar um comando, pois quando fecha a janela deveriamos fechar o programa  */
    /*  é bem intuitivo, quando o objeto janela for destruido, chame a função para fechar o main loop e retorne para ela um ponteiro nulo   */

    /*  A janela só pode conter um container    */
    /*  A box é horizontal  */
    conteudo = gtk_box_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(janela), conteudo);


    /*  Criação do label de email    */
    label_entrada_email = gtk_label_new("Digite seu email: ");
    /*  Adicionando ela ao conteúdo */
    gtk_box_pack_start(GTK_BOX(conteudo), label_entrada_email,  FALSE, FALSE, 0);


    /*  Cria uma nova entrada*/
    email = gtk_entry_new();
    /*  Adicionando a entrada ao conteúdo   */
    gtk_box_pack_start(GTK_BOX(conteudo), email, FALSE, FALSE, 0);
    

    /*  Criando a label de senha    */
    label_entrada_senha = gtk_label_new("Digite sua senha: ");
    /*  Adicionando ela ao conteúdo */
    gtk_box_pack_start(GTK_BOX(conteudo), label_entrada_senha, FALSE, FALSE, 0);

    /*  Criando a entrada da senha  */
    senha = gtk_entry_new();
    /*  Adicionando ela ao conteudo */
    gtk_box_pack_start(GTK_BOX(conteudo), senha, FALSE, FALSE,0);


    /*  Criando um botão para se conectar   */
    botaoConectar = gtk_button_new_with_label("Conectar");
    /*  Adicionandoo o botão ao conteúdo    */
    gtk_box_pack_start(GTK_BOX(conteudo), botaoConectar, FALSE, FALSE, 0);

    /* Botao de fechar o programa   */
    botaoSair = gtk_button_new_with_label("Sair");

    /*  Adicionando o botão ao conteúdo */
    gtk_box_pack_start(GTK_BOX(conteudo), botaoSair, FALSE, FALSE, 0);


    /*  Estamos conectado o objeto botão a ação de ser ciclicado, quando isso acontecer chamamos a função de armazenamento  */
    g_signal_connect(G_OBJECT(botaoConectar), "clicked", G_CALLBACK(ArmazenaInformacoes), NULL);

    /*  Chamada da função para verificar se existe o login e a senha digitadas  */
    g_signal_connect(G_OBJECT(botaoConectar), "clicked", G_CALLBACK(ProcuraInformacao), NULL );
    g_signal_connect(G_OBJECT(botaoSair), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(janela); /* Comando para mostrar a janela   */

    gtk_main(); /*  Função onde ocorrerá o main loop, loop de eventos, onde será armazenado todas as interações com a janela    */

    printf("%s", emailUsuario);
    




   
    
    /*
    CriarConta(&usuarios[n]);
    PrimeiraAutenticao(&usuarios[n]);
    AnexaDados(&usuarios[n], fpUsuarios);
    */
   
            

    fclose(fpUsuarios);

    
    





    
    

    return 0;
}