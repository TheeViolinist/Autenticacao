#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <gtk/gtk.h>




#define MAX_NOME 100
#define MAX_USUARIOS 100


/*  Struct responsável por armazenar os dados do usuário    */
typedef struct
{
    char nome[MAX_NOME];    /*  Nome do usuário */
    char senhaUsu[MAX_NOME];    /*  Senha criada pelo usuário   */
    int autenticacao1;       /*  primeira autenticação do usuário    */
    int codigo;                 /*  Código do usuário   */

}tConta;

GtkWidget *email;   /*  Variável que irá armazenar o email do usuário digitado na interface */
GtkWidget *label_saida;
GtkWidget *label_saida2;
GtkWidget *label_saida3;
GtkWidget *label_saida4;
GtkWidget *label_entrada;
GtkWidget *label_entrada_autenticador;
GtkWidget *autenticador;
GtkWidget *senha;   /*   Variável que irá armazenar a senha do usuário digitado na interface */
GtkWidget *conteudo;
GtkWidget *janela;  /*  Todos os componentes, como botões e janela são da classe GtkWidget  */
GtkWidget *label_entrada_senha;
GtkWidget *label_entrada_email;
char emailUsuario[MAX_NOME];     /*  Email do usuário    */
char senhaUsuario[MAX_NOME];       /*  Onde será armazenado a senha do usuário */
tConta usuarios[MAX_USUARIOS];      /*  Quantidade de usuários do tipo estruturado criado   */
FILE *fpUsuarios = NULL;            /*  Criação de um stream para um arquivo onde estão os dados dos usuários   */
int n = 0;  /*  Codigo do proximo usuario que será cadastrado   */
int codigo = 0;





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



/***
 * ArmazenaInformacoes(): Função responsável por armazenar informações digitadas na interface de usuário
 * 
 * 
 * Observação:
 *                          Função copia as informações digitadas na interface e passa para duas variáveis
 ****/

gboolean ArmazenaInformacoes(GtkButton *button, gpointer data)
{

    /*  Estamos pegando o email e a senha digitada na interface e armazenando em duas variáveis globais */
    strcpy(emailUsuario, gtk_entry_get_text(GTK_ENTRY(email)));
    strcpy(senhaUsuario, gtk_entry_get_text(GTK_ENTRY(senha)));
    return FALSE;
}

/***
 * ProcuraInformacao(): Função responsável por verificar se as informações digitadas estão corretas
 * 
 * 
 ****/
gboolean ProcuraInformacao(GtkButton *button, gpointer data)
{
    
    /*  Variável responsável por percorrer o array  */
    int contador = 0;
    char texto[MAX_NOME];
    while(1)
    {
        /*  Estamos percorrendo o array até encontrar as informações dada pelo usuário  */
        if(strcmp(usuarios[contador].nome, emailUsuario) == 0 && strcmp(usuarios[contador].senhaUsu, senhaUsuario) == 0)
        {
            /*  Se encontrado, avisamos que deu tudo certo e fechamos a função  */
            sprintf(texto, "As informacoes foram digitadas corretamente.\n");
            gtk_label_set_text(GTK_LABEL(label_saida), texto);
            codigo = contador;
            return FALSE;
        }
        /*  Se não for encontrado, ou seja, chegamos no limite do arquivo que é igual ao valor de n, logo fechamos o loop */
        if(contador == n)
        {
            break;
        }
        contador++;
    }

    /*  Digitamos que as informações digitadas foram erradas    */ 
    sprintf(texto, "As informacoes nao foram digitadas corretamente.\n");
    gtk_label_set_text(GTK_LABEL(label_saida), texto);
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

/*  Função para anexar os dados da criação da conta */
void AnexaDados(tConta *ptrUsuarios)
{

    
    fprintf(fpUsuarios,"%s\n%s\n%d\n%d\n", ptrUsuarios->nome, ptrUsuarios->senhaUsu, ptrUsuarios->autenticacao1, ptrUsuarios->codigo);
    

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

gboolean CadastraInformacao(GtkButton *button, gpointer data)
{
    char texto[MAX_NOME], texto2[MAX_NOME];
    CriarConta(&usuarios[n]);
    PrimeiraAutenticao(&usuarios[n]);
    AnexaDados(&usuarios[n]);
    /*  Estamos falando ao usuário tudo que ele precisa saber para conseguir se logar no programa   */
    sprintf(texto, "Conta criada com sucesso, por favor, clique no botao de sair e abra novamente o programa\n");
    sprintf(texto2, "Sua autenticacao eh: %d", usuarios[n].autenticacao1);
    gtk_label_set_text(GTK_LABEL(label_saida), texto);
    gtk_label_set_text(GTK_LABEL(label_saida2), texto2);
    return FALSE;


}


gboolean Autenticar(GtkButton *button, gpointer data)
{
    char texto[MAX_NOME], texto2[MAX_NOME];
    double autenticador1;
    autenticador1 = atol(gtk_entry_get_text(GTK_ENTRY(autenticador)));
  
   
    if(autenticador1 / usuarios[codigo].autenticacao1 == 1.0)
    {
        sprintf(texto, "Bem vindo");
        gtk_label_set_text(GTK_LABEL(label_saida3), texto);
        
    }
    
    sprintf(texto2, "voce digitou errado, tente novamente.");
    gtk_label_set_text(GTK_LABEL(label_saida4), texto2);
    return FALSE;
}

int main(int argc, char **argv)
{

   
    

    fpUsuarios = fopen("usuarios.txt", "r+");    /*  Abertura para leitura do arquivo    */
    if(fpUsuarios == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        return 1;
    }
    
    

    /*  Estamos fazendo a leitura de um arquivo e armazenando cada informação de usuário em um array    */
    while(1)
    {

        /*  Aqui pegamos o seu email/nome   */
        fgets(usuarios[n].nome, MAX_NOME, fpUsuarios);
        RetiraQuebra(usuarios[n].nome);
        /*  Aqui pegamos a senha do usuário */
        fgets(usuarios[n].senhaUsu, MAX_NOME, fpUsuarios);
        RetiraQuebra(usuarios[n].senhaUsu);
        /*  Pegamos a primeira autenticacao */
        fscanf(fpUsuarios, "%d%*c", &usuarios[n].autenticacao1);
        /*  E por fim pegamos o código de usuário   */
        fscanf(fpUsuarios, "%d%*c", &usuarios[n].codigo);
        if(feof(fpUsuarios))
        {
            break;
        }
        /*  Soma do codigo, para poder cadastrar um novo usuário    */
        n++;
    }
    /*  Retorna o próximo código de usuário que será cadastrado */
    usuarios[n].codigo = n;
   

   
    
   
    GtkWidget *botaoConectar;
    GtkWidget *botaoSair;
    GtkWidget *botaoCadastrar;
    GtkWidget *botaoAutenticar;
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

    


    /*  Criação do botão de cadastro    */
    botaoCadastrar = gtk_button_new_with_label("Cadastrar");
    gtk_box_pack_start(GTK_BOX(conteudo), botaoCadastrar, FALSE, FALSE, 0);



    /* Botao de fechar o programa   */
    botaoSair = gtk_button_new_with_label("Sair");

    /*  Adicionando o botão ao conteúdo */
    gtk_box_pack_start(GTK_BOX(conteudo), botaoSair, FALSE, FALSE, 0);


    /*  label onde será escrito todas as informações de saida   */
    label_saida = gtk_label_new(" ");
    gtk_box_pack_start(GTK_BOX(conteudo), label_saida, FALSE, FALSE, 0);

    label_saida2 = gtk_label_new(" ");
    gtk_box_pack_start(GTK_BOX(conteudo),label_saida2, FALSE, FALSE, 0);

    label_entrada_autenticador = gtk_label_new("Digite sua autenticacao: ");
    gtk_box_pack_start(GTK_BOX(conteudo), label_entrada_autenticador, FALSE, FALSE, 0);
    autenticador = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(conteudo), autenticador, FALSE, FALSE,0);


    botaoAutenticar = gtk_button_new_with_label("Autenticar");
    gtk_box_pack_start(GTK_BOX(conteudo), botaoAutenticar, FALSE, FALSE, 0);

    label_saida3 = gtk_label_new(" ");
    gtk_box_pack_start(GTK_BOX(conteudo), label_saida3, FALSE, FALSE, 0);
    /*  Estamos conectado o objeto botão a ação de ser ciclicado, quando isso acontecer chamamos a função de armazenamento  */
    g_signal_connect(G_OBJECT(botaoConectar), "clicked", G_CALLBACK(ArmazenaInformacoes), NULL);

    label_saida4 = gtk_label_new(" ");
    gtk_box_pack_start(GTK_BOX(conteudo), label_saida4, FALSE, FALSE, 0);

    /*  Chamada da função para verificar se existe o login e a senha digitadas  */
    g_signal_connect(G_OBJECT(botaoConectar), "clicked", G_CALLBACK(ProcuraInformacao), NULL );

    /*  Chamada da função de cadastro   */
    g_signal_connect(G_OBJECT(botaoCadastrar), "clicked", G_CALLBACK(CadastraInformacao), NULL);

    g_signal_connect(G_OBJECT(botaoAutenticar), "clicked", G_CALLBACK(Autenticar), NULL);
    /*  Conecta-se o botão de sair com o cancelamento do programa   */
    g_signal_connect(G_OBJECT(botaoSair), "clicked", G_CALLBACK(gtk_main_quit), NULL);
    
    
    


    gtk_widget_show_all(janela); /* Comando para mostrar a janela   */


    gtk_main(); /*  Função onde ocorrerá o main loop, loop de eventos, onde será armazenado todas as interações com a janela    */

    

    


    fclose(fpUsuarios);

    
    





    
    

    return 0;
}