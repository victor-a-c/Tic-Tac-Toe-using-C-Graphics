#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include <fstream>
#include <limits>
#include <conio.h>

using namespace std;

char hmenu, leave, gmode;

void menu1(); 		// menu ajuda ou tutorial
					// EN: Help menu or Tutorial

void menu2(); 		// menu modo de jogo
					// EN: game mode menu

void ajuda(); 		// pagina de ajuda
					// EN: Help page

void jogadas(); 	// pagina de tutorial
					// EN: Tutorial page

void linhas(); 		// desenha as linhas do jogo da velha
					// EN: draws tic tac toe lines

void XouY(int vez, int p); 		// decide se X ou Y sera exibido na tela de acordo com a variavel Vez
								// EN: decides if X or Y will be shown on the screen according to the turn variable
								
int checagem(char *a); 		// checa se alguem venceu e retorna um valor que encerra o jogo e declara o ganhador
							// EN: checks if someone won and returns a value that ends the game and declares the winner
							
void PC(char *a,int vez);	// parte logica do jogador PC, onde reage aos inputs do jogador lendo linhas, colunas e diagonais para uma resposta defensiva ou ofensiva
							// EN: logic part of PC Player, reacting to user imput, reading lines, columns and diagonals for a defensive or offensive reaction

 
int main(void)
{
	char letra;
	leave = '\0';
	int newg = 0;
	initwindow(800,700);
	
	do
	{	    
	    if(newg == 0)	// impede que os menus apareçam apos a primeira rodada
	    				// EN: prevents menus from being printed after the first game
	    {
	    	do
		    {
		    	cleardevice();
		    	menu1();				
				hmenu = getch();
				
				if(hmenu == 'A' || hmenu == 'a')
			    {
			    	cleardevice();
			    	ajuda();
			    	leave = getch();
				}
				else if(hmenu == 'T' || hmenu == 't')
				{
					cleardevice();
			    	jogadas();
			    	leave = getch();
				}
				
				if(hmenu == 's' || hmenu == 'S')
				{
					break;	// sair do loop
							// EN: leave loop
				}					
			}while(hmenu != 's' || hmenu != 'S');
			
			do
			{
				cleardevice();
			    menu2();					
				gmode = getch();
				
				if(gmode == '1' || gmode == '2' || gmode == '3')
				{
					break;	// sair do loop
							// EN: leave loop
				}		
			}while((gmode != '1') || (gmode != '2') || (gmode != '3'));
		}
	    
	    cleardevice();
		linhas();
	    int x=0;
	    POINT pos;
	    int vez=0;
	    char b[9]={0};
	    for(int i=0;i<9;i++)
	        b[i]=0;
	    
	    // modo de jogo Player vs PC
	    // EN: Game mode Player vc PC
	    if(gmode == '1')
	    {
	    	while(x==0 && vez<=9)
		    {
		    	
				if(GetAsyncKeyState(VK_LBUTTON))	// esperar imput do mouse
													// EN: Wait for mouse imput
		        {
		            GetCursorPos(&pos);
		            long X=mousex();
		            long Y=mousey();
		            int mov=0;	// variavel para contar vezes entre jogador e PC - 0 e 1
		            			// EN: variable to count turns between Player and PC => 0 and 1
		            if(vez%2==0){
		                if(X>280 && X<360 && Y>220 && Y<300 && b[0]==0)     // 1
		                {
		                    XouY(1,1);
		                    mov=1;
		                    b[0]='X';
		                }
		                else if(X>360 && X<440 && Y>220 && Y<300 && b[1]==0)     // 2
		                {
		                    XouY(1,2);
		                    mov=1;
		                    b[1]='X';
		                }
		                else if(X>440 && X<520 && Y>220 && Y<300 && b[2]==0)     // 3
		                {
		                    XouY(1,3);
		                    mov=1;
		                    b[2]='X';
		                }
		                else if(X>280 && X<360 && Y>300 && Y<380 && b[3]==0)     // 4
		                {
		                    XouY(1,4);
		                    mov=1;
		                    b[3]='X';
		                }
		                else if(X>360 && X<540 && Y>300 && Y<380 && b[4]==0)     // 5
		                {
		                    XouY(1,5);
		                    mov=1;
		                    b[4]='X';
		                }
		                else if(X>440 && X<520 && Y>300 && Y<380 && b[5]==0)     // 6
		                {
		                    XouY(1,6);
		                    mov=1;
		                    b[5]='X';
		                }
		                else if(X>280 && X<360 && Y>380 && Y<460 && b[6]==0)     // 7
		                {
		                    XouY(1,7);
		                    mov=1;
		                    b[6]='X';
		                }
		                else if(X>360 && X<440 && Y>380 && Y<460 && b[7]==0)     // 8
		                {
		                    XouY(1,8);
		                    mov=1;
		                    b[7]='X';
		                }
		                else if(X>440 && X<520 && Y>380 && Y<460 && b[8]==0)     // 9
		                {
		                    XouY(1,9);
		                    b[8]='X';
		                    mov=1;
		                }
		                if(mov)
						{
		                    vez++;
		                    x=checagem(b);
		                    delay(200);
		                    if(x!=0 || vez==9)
		                        break;
		                    // Vez do PC
		                    // EN: PC turn
		                    PC(b,vez);
		                    vez++;
		                    x=checagem(b);
		                }
		            }
		        }     
		    }
		    if(x==1)
			{
		        settextstyle(10,0,3);
		        int w=textwidth("Voce Ganhou!!"); // EN: You win
		        outtextxy((800-w)/2,500,"Voce Ganhou!!"); // EN: You win
		        
		        delay(1000); // delay entre a mensagem anterior e de nova partida
		        			// EN: Delay between the previous message and new game
			    settextstyle(10,0,3);
			    int ooo=textwidth("Outra Partida? (Y/N)"); // EN: Play Again?
			    outtextxy((850-ooo)/2,530,"Outra Partida? (Y/N)"); // EN: Play Again?
			    
			    settextstyle(10,0,3);
			    int v=textwidth("Menu (M)");
			    outtextxy((1400-v)/2,650,"Menu (M)");
			    letra = getch(); // pedir imput para loop while
			    				// EN: request imput for while loop
		    }
		    else if(x==2)
			{
		        settextstyle(10,0,3);
		        int w=textwidth("Voce Perdeu"); // EN: You Lost
		        outtextxy((800-w)/2,500,"Voce Perdeu");  // EN: You Lost
				
				delay(1000);
			    settextstyle(10,0,3);
			    int ooo=textwidth("Outra Partida? (Y/N)"); // EN: Play Again?
			    outtextxy((850-ooo)/2,530,"Outra Partida? (Y/N)"); // EN: Play Again?
			    
			    settextstyle(10,0,3);
			    int v=textwidth("Menu (M)");
			    outtextxy((1400-v)/2,650,"Menu (M)");
			    letra = getch();        
		    }
		    else if(x==0)
			{
		        settextstyle(10,0,3);
		        int w=textwidth(" Velha "); // EN: Draw
		        outtextxy((800-w)/2,500," Velha "); // EN: Draw
		        
		        delay(1000);
			    settextstyle(10,0,3);
			    int ooo=textwidth("Outra Partida? (Y/N)"); // EN: Play Again?
			    outtextxy((850-ooo)/2,530,"Outra Partida? (Y/N)"); // EN: Play Again?
			    
			    settextstyle(10,0,3);
			    int v=textwidth("Menu (M)");
			    outtextxy((1400-v)/2,650,"Menu (M)");
			    letra = getch();
		    }
		}
		
		// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		// modo de jogo Player vs Player
		// EN: Game Mode Player vs Player
		if(gmode == '2')
		{
			while(x==0 && vez<=9)
		    {
		    	// jogador 1
				if(GetAsyncKeyState(VK_LBUTTON))	// esperar imput do mouse
													// EN:  Wait for mouse imput
		        {
		            GetCursorPos(&pos);
		            long X=mousex();
		            long Y=mousey();
		            int mov=0;	// variavel para contar vezes entre jogador e PC - 0 e 1
		            			// EN: Variable to count turns between Player and PC
		            if(vez%2==0)
					{
		                if(X>280 && X<360 && Y>220 && Y<300 && b[0]==0)     // 1
		                {
		                    XouY(1,1);
		                    mov=1;
		                    b[0]='X';
		                }
		                else if(X>360 && X<440 && Y>220 && Y<300 && b[1]==0)     // 2
		                {
		                    XouY(1,2);
		                    mov=1;
		                    b[1]='X';
		                }
		                else if(X>440 && X<520 && Y>220 && Y<300 && b[2]==0)     // 3
		                {
		                    XouY(1,3);
		                    mov=1;
		                    b[2]='X';
		                }
		                else if(X>280 && X<360 && Y>300 && Y<380 && b[3]==0)     // 4
		                {
		                    XouY(1,4);
		                    mov=1;
		                    b[3]='X';
		                }
		                else if(X>360 && X<540 && Y>300 && Y<380 && b[4]==0)     // 5
		                {
		                    XouY(1,5);
		                    mov=1;
		                    b[4]='X';
		                }
		                else if(X>440 && X<520 && Y>300 && Y<380 && b[5]==0)     // 6
		                {
		                    XouY(1,6);
		                    mov=1;
		                    b[5]='X';
		                }
		                else if(X>280 && X<360 && Y>380 && Y<460 && b[6]==0)     // 7
		                {
		                    XouY(1,7);
		                    mov=1;
		                    b[6]='X';
		                }
		                else if(X>360 && X<440 && Y>380 && Y<460 && b[7]==0)     // 8
		                {
		                    XouY(1,8);
		                    mov=1;
		                    b[7]='X';
		                }
		                else if(X>440 && X<520 && Y>380 && Y<460 && b[8]==0)     // 9
		                {
		                    XouY(1,9);
		                    b[8]='X';
		                    mov=1;
		                }
		                if(mov)
						{
		                    vez++;
		                    x=checagem(b);
		                    if(x!=0 || vez==9)
		                        break;
		                }
		                
		            }
		        } 
				
				
				//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
				// jogador 2
				
				if(GetAsyncKeyState(VK_LBUTTON))	// esperar imput do mouse
													// EN: Wait for mouse imput
		        {
		            GetCursorPos(&pos);
		            long X=mousex();
		            long Y=mousey();
		            int mov=0;	// variavel para contar vezes entre jogador e PC - 0 e 1
		            			// EN: Variable to count turns between Player and PC
		            if(vez%2!=0)
					{
		                if(X>280 && X<360 && Y>220 && Y<300 && b[0]==0)     // 1
		                {
		                    XouY(0,1);
		                    mov=1;
		                    b[0]='O';
		                }
		                else if(X>360 && X<440 && Y>220 && Y<300 && b[1]==0)     // 2
		                {
		                    XouY(0,2);
		                    mov=1;
		                    b[1]='O';
		                }
		                else if(X>440 && X<520 && Y>220 && Y<300 && b[2]==0)     // 3
		                {
		                    XouY(0,3);
		                    mov=1;
		                    b[2]='O';
		                }
		                else if(X>280 && X<360 && Y>300 && Y<380 && b[3]==0)     // 4
		                {
		                    XouY(0,4);
		                    mov=1;
		                    b[3]='O';
		                }
		                else if(X>360 && X<540 && Y>300 && Y<380 && b[4]==0)     // 5
		                {
		                    XouY(0,5);
		                    mov=1;
		                    b[4]='O';
		                }
		                else if(X>440 && X<520 && Y>300 && Y<380 && b[5]==0)     // 6
		                {
		                    XouY(0,6);
		                    mov=1;
		                    b[5]='O';
		                }
		                else if(X>280 && X<360 && Y>380 && Y<460 && b[6]==0)     // 7
		                {
		                    XouY(0,7);
		                    mov=1;
		                    b[6]='O';
		                }
		                else if(X>360 && X<440 && Y>380 && Y<460 && b[7]==0)     // 8
		                {
		                    XouY(0,8);
		                    mov=1;
		                    b[7]='O';
		                }
		                else if(X>440 && X<520 && Y>380 && Y<460 && b[8]==0)     // 9
		                {
		                    XouY(0,9);
		                    b[8]='O';
		                    mov=1;
		                }
		                if(mov)
						{
		                    vez++;
		                    x=checagem(b);
		                    delay(200);
		                    if(x!=0 || vez==9)
		                        break;
		                }
		            }
		        }
		          
		    }
		    // jogador 1
		    if(x==1)
			{
		        settextstyle(10,0,3);
		        int w=textwidth("X Ganhou!!");
		        outtextxy((800-w)/2,500,"X Ganhou!!");
		        
		        delay(1000); // delay entre a mensagem anterior e de nova partida
			    settextstyle(10,0,3);
			    int ooo=textwidth("Outra Partida? (Y/N)");
			    outtextxy((850-ooo)/2,530,"Outra Partida? (Y/N)");
			    
			    settextstyle(10,0,3);
			    int v=textwidth("Menu (M)");
			    outtextxy((1400-v)/2,650,"Menu (M)");
			    letra = getch(); // pedir imput para loop do while
		    }
		    // jogador 2
		    else if(x==2)
			{
		        settextstyle(10,0,3);
		        int w=textwidth("'O' Ganhou!!");
		        outtextxy((800-w)/2,500,"'O' Ganhou!!");
				
				delay(1000);
			    settextstyle(10,0,3);
			    int ooo=textwidth("Outra Partida? (Y/N)");
			    outtextxy((850-ooo)/2,530,"Outra Partida? (Y/N)");
			    
			    settextstyle(10,0,3);
			    int v=textwidth("Menu (M)");
			    outtextxy((1400-v)/2,650,"Menu (M)");
			    letra = getch();        
		    }
		    else if(x==0)
			{
		        settextstyle(10,0,3);
		        int w=textwidth(" Velha ");
		        outtextxy((800-w)/2,500," Velha ");
		        
		        delay(1000);
			    settextstyle(10,0,3);
			    int ooo=textwidth("Outra Partida? (Y/N)");
			    outtextxy((850-ooo)/2,530,"Outra Partida? (Y/N)");
			    
				settextstyle(10,0,3);
			    int v=textwidth("Menu (M)");
			    outtextxy((1400-v)/2,650,"Menu (M)");
			    letra = getch();
		    }
		}
		
		newg++; // contagem de partidas
				// EN: game counter
		if(letra == 'm' || letra == 'M')
		{
			newg = 0;
			letra = 'y';
		}
	}while(letra == 'y' || letra == 'Y');
}


void menu1()
{
	settextstyle(10,0,6);
	int item71=textwidth("Jogo da Velha");
	outtextxy((750-item71)/2,80,"Jogo da Velha");
	
	settextstyle(10,0,3);
	int item7=textwidth("Digite A para Ajuda (regras)"); // EN: Type A for help(rules)
	outtextxy((750-item7)/2,180,"Digite A para Ajuda (regras)");
				
	settextstyle(10,0,3);
	int item8=textwidth("T para o Tutorial (jogadas)"); // EN: Type T for tutorial (plays)
	outtextxy((750-item8)/2,240,"T para o Tutorial (jogadas)");
				
	settextstyle(10,0,3);
	int item9=textwidth("S para jogar");	// EN: S to start
	outtextxy((750-item9)/2,300,"S para jogar");
}

void menu2()
{
	settextstyle(10,0,6);
	int itemm1=textwidth("Jogo da Velha");
	outtextxy((750-itemm1)/2,80,"Jogo da Velha");
			    	
	settextstyle(10,0,3);
	int itemm2=textwidth("Digite 1 para Player vs PC");	// EN: Type 1 for Player vs PC
	outtextxy((750-itemm2)/2,180,"Digite 1 para Player vs PC");
					
	settextstyle(10,0,3);
	int item8=textwidth("Digite 2 para Player vs Player");	// EN: Type 2 for Player vs Player
	outtextxy((750-item8)/2,240,"Digite 2 para Player vs Player");
}

void ajuda()
{
	settextstyle(10,0,65);
    int w=textwidth("Ajuda");
    outtextxy((750-w)/2,60,"Ajuda");
    
    settextstyle(10,0,3);
	int item1=textwidth("Bem Vindo(a) a pagina de ajuda");
	outtextxy((500-item1)/2,130,"Bem Vindo(a) a pagina de ajuda");
    
    settextstyle(10,0,3);
	int item2=textwidth("Para marcar X, clique na area selecionada");
	outtextxy((650-item2)/2,190,"Para marcar 'X', clique na area selecionada");
    
    settextstyle(10,0,3);
	int item3=textwidth("O seu oponente irá marcar com 'O' ");
	outtextxy((555-item3)/2,220,"O seu oponente irá marcar com 'O' ");
	
	settextstyle(10,0,3);
	int item5=textwidth("Ganha quem marcar 3 'X' ou 'O' em sequencia");
	outtextxy((680-item5)/2,280,"Ganha quem marcar 3 'X' ou 'O' em sequencia");
	settextstyle(10,0,3);
	int item6=textwidth("na horizontal, vertical ou diagonal");
	outtextxy((570-item6)/2,300,"na horizontal, vertical ou diagonal");
	
	settextstyle(10,0,2);
    int h=textheight("V - Para voltar");
    int s=textwidth("V - Para voltar");
    outtextxy(750-s-5,650-h,"V - Para voltar");
    
}


void jogadas()
{
	settextstyle(10,0,6);
    int w=textwidth("Tutorial");
    outtextxy((750-w)/2,60,"Tutorial");
    
    settextstyle(10,0,3);
	int item1=textwidth("Bem Vindo(a) a pagina de tutorial");
	outtextxy((550-item1)/2,130,"Bem Vindo(a) a pagina de tutorial");
    
    settextstyle(10,0,3);
	int item2=textwidth("Ganhar:");
	outtextxy((185-item2)/2,190,"Ganhar:");
	settextstyle(10,0,3);
	int item22=textwidth("Se você tem duas peças numa linha,");
	outtextxy((563-item22)/2,210,"Se você tem duas peças numa linha,");
	settextstyle(10,0,3);
	int item23=textwidth("ponha a terceira");
	outtextxy((315-item23)/2,230,"ponha a terceira");
    
    settextstyle(10,0,3);
	int item3=textwidth("Bloquear:");
	outtextxy((220-item3)/2,270,"Bloquear:");
	settextstyle(10,0,3);
	int item32=textwidth("Se o oponente tiver duas peças em linha,");
	outtextxy((650-item32)/2,290,"Se o oponente tiver duas peças em linha,");
	settextstyle(10,0,3);
	int item33=textwidth("ponha a terceira para bloqueá-lo");
	outtextxy((540-item33)/2,310,"ponha a terceira para bloqueá-lo");
	
	settextstyle(10,0,3);
	int item4=textwidth("Triângulo:");
	outtextxy((230-item4)/2,350,"Triângulo:");
	settextstyle(10,0,3);
	int item42=textwidth("Crie uma oportunidade em que você");
	outtextxy((550-item42)/2,370,"Crie uma oportunidade em que você");
	settextstyle(10,0,3);
	int item43=textwidth("poderá ganhar de duas maneiras");
	outtextxy((510-item43)/2,390,"poderá ganhar de duas maneiras");
	
	settextstyle(10,0,2);
    int h=textheight("V - Para voltar"); // V to go back
    int s=textwidth("V - Para voltar");
    outtextxy(750-s-5,650-h,"V - Para voltar");
    
}

void linhas()
{
    settextstyle(10,0,6);
    int w=textwidth("Jogo da Velha");
    outtextxy((750-w)/2,80,"Jogo da Velha");
    //   x1, y1, x2, y2
	line(360,220,360,460); // desenha cada linha
	line(360+1,220,360+1,460);
	line(360-1,220,360-1,460);
	//   x1, y1, x2, y2
	line(280,300,520,300);
	line(280,300+1,520,300+1);
	line(280,300-1,520,300-1);
	//   x1, y1, x2, y2
	line(280,380,520,380);
	line(280,380+1,520,380+1);
	line(280,380-1,520,380-1);
	//   x1, y1, x2, y2
	line(440,220,440,460);
	line(440+1,220,440+1,460);
	line(440-1,220,440-1,460);

}

void XouY(int vez, int p)
{
	// imprime o X ou Y dos jogadores
	// EN: Prints X or Y of players
    settextstyle(10,0,6);
    int w=0,h=0;
    if(vez==1)
	{
        h=textheight("X");
        w=textwidth("X");
    }
    else{
        h=textheight("O");
        w=textwidth("O");
    }
    int x=(480-w)/2;
    int y=(80-h)/2;
    switch(p)
    {
        case 1:
            if(vez==1)
                outtextxy(x+80,y+220,"X");
            else
                outtextxy(x+80,y+220,"O");
            break;
        case 2:
            if(vez==1)
                outtextxy(x+160,y+220,"X");
            else
                outtextxy(x+160,y+220,"O");
            break;
        case 3:
            if(vez==1)
                outtextxy(x+240,y+220,"X");
            else
                outtextxy(x+240,y+220,"O");
            break;
        case 4:
            if(vez==1)
                outtextxy(x+80,y+300,"X");
            else
                outtextxy(x+80,y+300,"O");
            break;
        case 5:
            if(vez==1)
                outtextxy(x+160,y+300,"X");
            else
                outtextxy(x+160,y+300,"O");
            break;
        case 6:
            if(vez==1)
                outtextxy(x+240,y+300,"X");
            else
                outtextxy(x+240,y+300,"O");
            break;
        case 7:
            if(vez==1)
                outtextxy(x+80,y+380,"X");
            else
                outtextxy(x+80,y+380,"O");
            break;
        case 8:
            if(vez==1)
                outtextxy(x+160,y+380,"X");
            else
                outtextxy(x+160,y+380,"O");
            break;
        case 9:
            if(vez==1)
                outtextxy(x+240,y+380,"X");
            else
                outtextxy(x+240,y+380,"O");
            break;

    }
}

int checagem(char *a)
{
    // return || '0' nada || '1' player 1 || '2' player 2

    //diagonal
    if((a[0]==a[4] && a[0]==a[8] && a[0]=='X') || (a[2]==a[4] && a[2]==a[6] && a[2]=='X'))
    {
    	return 1;
	}        
    else if((a[0]==a[4] && a[0]==a[8] && a[0]=='O') || (a[2]==a[4] && a[2]==a[6] && a[2]=='O'))
    {
    	return 2;
	}

    // horizontal
    if((a[0]==a[1] && a[1]==a[2] && a[0]=='X') || (a[3]==a[4] && a[4]==a[5] && a[3]=='X') || (a[6]==a[7] && a[7]==a[8] && a[6]=='X'))
    {
    	return 1;
	}
    else if((a[0]==a[1] && a[1]==a[2] && a[0]=='O') || (a[3]==a[4] && a[4]==a[5] && a[3]=='O') || (a[6]==a[7] && a[7]==a[8] && a[6]=='O'))
    {
    	return 2;
	}

    // vertical
    if((a[0]==a[3] && a[3]==a[6] && a[0]=='X') || (a[1]==a[4] && a[4]==a[7] && a[1]=='X') || (a[2]==a[5] && a[5]==a[8] && a[2]=='X'))
    {
    	return 1;
	}
    if((a[0]==a[3] && a[3]==a[6] && a[0]=='O') || (a[1]==a[4] && a[4]==a[7] && a[1]=='O') || (a[2]==a[5] && a[5]==a[8] && a[2]=='O'))
    {
    	return 2;
	}
    return 0;
}

void PC(char *a,int vez)
{
    int pcv[8],p[8];  // dois vetores com valores arbitrarios
    for(int i=0;i<8;i++) // valores 0 e -1 para serem usados pelo jogador 2 (PC) usando os algoritimos de ataque e defesa abaixo
	{
        pcv[i]=0;p[i]=-1;
    }
    // ataque
    for(int i=0;i<9;i++)
	{
        if(a[i]=='O')
		{
            pcv[i/3]++;
            pcv[3+i%3]++;
            if(i%4==0)
                pcv[6]++;
            if(i==2 || i==4 || i==6)
                pcv[7]++;
        }
        else if(a[i]==0)
		{
            p[i/3]=i;
            p[3+i%3]=i;
            if(i%4==0)
                p[6]=i;
            if(i==2 || i==4 || i==6)
                p[7]=i;
        }
    }
    for(int i=0;i<8;i++)
	{
        if(pcv[i]==2 && p[i]!=-1)
		{
            XouY(0,p[i]+1);
            a[p[i]]='O';
            return;
        }
        p[i]=-1;pcv[i]=0;
    }
    // defender
    for(int i=0;i<9;i++)
	{
        if(a[i]=='X')
		{
            pcv[i/3]++;
            pcv[3+i%3]++;
            if(i%4==0)
                pcv[6]++;
            if(i==2 || i==4 || i==6)
                pcv[7]++;
        }
        else if(a[i]==0)
		{
            p[i/3]=i;
            p[3+i%3]=i;
            if(i%4==0)
                p[6]=i;
            if(i==2 || i==4 || i==6)
                p[7]=i;
        }
    }
    for(int i=0;i<8;i++)
	{
        if(pcv[i]==2 && p[i]!=-1)
		{
            XouY(0,p[i]+1);
            a[p[i]]='O';
            return;
        }
        p[i]=-1;pcv[i]=0;
    }
    if(a[4]==0)
	{
        XouY(0,5);
        a[4]='O';
        return;
    }
    if(vez==1)
	{
        XouY(0,1);
        a[0]='O';
        return;
    }
    if(vez==3)
	{
        if(a[4]=='X')
		{
            XouY(0,3);
            a[2]='O';
            return;
        }
        p[0]=p[1]=-1;int j=0;
        for(int i=0;i<9;i++)
            if(a[i]=='X')
                p[j++]=i;
        if((p[0]==3 && p[1]==5) || (p[0]==2 && p[1]==7))
		{
            XouY(0,1);
            a[0]='O';
            return;
        }
        if(p[0]+p[1]==8)
		{
            XouY(0,2);
            a[1]='O';
            return;
        }
        if(p[0]==0 || p[0]==1)
		{
            if(p[1]==5 || p[1]==8)
			{
                XouY(0,3);
                a[2]='O';
                return;
            }
            else if(p[1]==3 || p[1]==6)
			{
                XouY(0,1);
                a[0]='O';
                return;
            }
            else
			{
                XouY(0,7);
                a[6]='O';
                return;
            }
        }
        else if(p[0]==1 || p[0]==2)
		{
            if(p[1]==3 || p[1]==6)
			{
                XouY(0,1);
                a[0]='O';
                return;
            }
            else
			{
                XouY(0,9);
                a[8]='O';
                return;
            }
        }
        else if(p[0]==3)
		{
            XouY(0,7);
            a[6]='O';
            return;
        }
        XouY(0,9);
        a[8]='O';
        return;
    }
    for(int i=0;i<9;i++)
	{
        if(a[i]==0)
		{
            XouY(0,1+i);
            a[i]='O';
            return;
        }
    }
}
