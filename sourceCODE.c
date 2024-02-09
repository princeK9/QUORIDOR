# include <stdio.h>
# include <string.h>
#include<conio.h>
# define ROWS 23
# define COLUMNS 45
# define N 17

void initboard(char board[][COLUMNS]);                                     
void showboard(char board[][COLUMNS]);                                     
int whiteupdateboard(char wmove[],char board[][COLUMNS],int pwwall);       
int blackupdateboard(char bmove[],char board[][COLUMNS],int pbwall);
int checkwin(char board[][COLUMNS]);
void deftable(char table[][19]);
void updatetable(char table[][19],char input[],int *px,int *py);
void input(char inp[]);
void printtable(char table[][19],int counter);
int  wcheckvalidity(char wmove[],char board[][COLUMNS],int wwall);
int bcheckvalidity(char bmove[],char board[][COLUMNS],int bwall);
int xalphaint(char a);
int ynumint(char b);
int checkbounds(char userinput[]);
int movecheckw(char wmove[]);
int movecheckb(char bmove[]);
int wallnocheck(char move[],int wall);
void rule();
int wallvalidate(char move[],char board[][COLUMNS]);
int wcheckw(char board[][COLUMNS],char wmove[]);
int wcheckb(char board[][COLUMNS],char bmove[]);
void pathmatrix(int pathmat[17][17],char board[][COLUMNS],char src);
int checkpathblock(char board[][COLUMNS],int pathmat[][N]);
int isPath(int matrix[][N]);
int isaPath(int matrix[][N], int i, int j,int visited[][N]);
int isSafe(int i, int j, int matrix[][N]);
void pathmatrix(int pathmat[17][17],char board[][COLUMNS],char src);



struct coord {
    int x;
    int y;
};

struct coord wp;
struct coord bp;




// driver code
int main() {

    char board[ROWS][COLUMNS];
    char table[153][19];
    char wmove[5];
    char bmove[5];
    int pathmat[17][17];

    int bwall=7;
    int wwall=7;
            

    int x=8,y=3,counter=0,wenter=1;

    printf("\033[1;32m||||||||                                    \033[1;33mQUORIDOR\033[1;32m                                   ||||||||\n");

    rule();

    printf("\033[1;32m|||||||.................................\033[1;33mTHE GAME BEGINS\033[1;32m................................||||||||\n");
    printf("|||||||.............................\033[1;33m%c%c%c%c%c HAVE FUN %c%c%c%c%c\033[1;32m...............................||||||||\n\033[1;m",1,2,1,2,1,2,1,2,1,2);
    
    initboard(board);
    deftable(table);
    
    showboard(board);
    

    for (int i=1 ; i<=75 ; i++) {
        if (wenter==1) {
            
            printf("White to move : ");
            input(wmove);
            strlwr(wmove);
            
            if (wmove[0]=='s'&& wmove[1]=='h' && wmove[2]=='o' && wmove[3]=='w' && wmove[4]=='\0') {
                printtable(table,counter);
                i--;
                continue;
            }
            else if (wmove[0]=='q' && wmove[1]=='u' && wmove[2]=='i' && wmove[3]=='t' && wmove[4]=='\0') {
                printf("............THE END............\n");
                break ;
            }
            else if (wmove[0]=='r'&& wmove[1]=='u' && wmove[2]=='l' && wmove[3]=='e' && wmove[4]=='\0') {
                rule();
                i--;
                continue;
            }
            else if (wmove[0]=='w'&& wmove[1]=='a' && wmove[2]=='l' && wmove[3]=='l' && wmove[4]=='\0') {
                printf("White walls left : %d\n",wwall);
                i--;
                continue;
            }

            else 
            {
                if (wcheckvalidity(wmove,board,wwall)) 
                {
                    wwall=whiteupdateboard(wmove,board,wwall);
                    updatetable(table,wmove,&x,&y);
                    showboard(board);
                    if (checkpathblock(board,pathmat)==0) {
                        printf("............STALEMATE...........\n");
                        break;
                    }
                    if (checkwin(board)==1) 
                    {
                        printf(".........WHITE WINS.........\n");
                        printf(".......THANK YOU FOR PLAYING......");
                        break;
                        return 0;
                    }
                } 
                else 
                {
                    printf(".........INVALID MOVE.........\n");
                    printf("Please enter the move again...\n");
                    i--;
                    continue;
                }
                
            }
        
        }
        
        /*__________________________________________________________________________________*/
        
        printf("Black to move : ");
        input(bmove);
        strlwr(bmove);
        
        
        if (bmove[0]=='s'&& bmove[1]=='h' && bmove[2]=='o' && bmove[3]=='w' && bmove[4]=='\0') {
            printtable(table,counter);
            i--;
            wenter = 0;
            continue;
        } 
        else if (bmove[0]=='q' && bmove[1]=='u' && bmove[2]=='i' && bmove[3]=='t' && bmove[4]=='\0') {
            printf("............THE END............\n");
            break ;
        }
        else if (bmove[0]=='r'&& bmove[1]=='u' && bmove[2]=='l' && bmove[3]=='e' && bmove[4]=='\0') {
                rule();
                i--;
                wenter = 0;
                continue;
        }
        else if (bmove[0]=='w'&& bmove[1]=='a' && bmove[2]=='l' && bmove[3]=='l' && bmove[4]=='\0') {
                printf("Black walls left : %d\n",bwall);
                i--;
                wenter = 0;
                continue;
        }

        else {
            if (bcheckvalidity(bmove,board,bwall)) {
                bwall=blackupdateboard(bmove,board,bwall) ;
                updatetable(table,bmove,&x,&y);
                showboard(board);
                if (checkpathblock(board,pathmat)==0) {
                    printf("............STALEMATE...........\n");
                    break;
                }
                if (checkwin(board)==2) {
                    printf(".........BLACK WINS.........\n");
                    break;
                }

            }
            else {
                printf("..............INVALID MOVE.............\n");
                printf("Enter the move again...\n");
                wenter = 0;
                i--;
                continue;

            }

        }

        counter++;     
        wenter = 1;

    }
    
    if (checkwin(board) == 0) {
        printf("...........GAME DRAW...........\n");
    }    

    return 0;
}






//initiallising the game board
void initboard(char board[][COLUMNS]) {
    //initialising the board
    for (int i=0;i<ROWS;i++) {
        if (i%2==0) {
            for (int j=0 ; j<COLUMNS ; j++) {
                if (j%4==0) {
                    board[i][j]='+';
                }
                else {
                    board[i][j]='-';
                }
                
            }


        }
        else {
            for (int j=0 ; j<COLUMNS ; j++) {
                if (j%4==0) {
                    board[i][j]='|';
                }
                else {
                    board[i][j]=' ';
                    
                }
            }
            if (i!=1 && i!= ROWS-2) {
                board[i][2]=(char) 64 + (i-1)/2;
                board[i][COLUMNS-3] = (char)64 + (i-1)/2;
            }
        }

    }

    for (int j=6;j<41;j+=4){
        char x = (int)48 + (j-2)/4;
        board[1][j]=x;
        board[ROWS-2][j]=x;
    }

    wp.x = (ROWS-1)/2;         //whites initial coordinates
    wp.y = 6;

    bp.x = (ROWS-1)/2;          // blacks initial coordinates
    bp.y = COLUMNS - 7;
    

    board[wp.x][wp.y]='W';
    board[bp.x][bp.y]='B';


    
}



//to display the current status of the game board
void showboard(char board[][COLUMNS]) {
    //printing the board

    for (int i=0 ; i<ROWS ; i++) {
        for (int j=0 ; j<COLUMNS ; j++ ) {
            printf("%c",board[i][j]);
        }
        printf("\n");
    }
}



//to update the moves played by white on game board
int whiteupdateboard(char wmove[],char board[][COLUMNS],int pwwall){
    // updating the board when white moves
    int l = strlen(wmove);
    
    
    char num = wmove[1];
    char alpha = wmove[0];
    int numint = num - 48;
    int alphaint = alpha - 96 ;

    if (l==2) {
        board[wp.x][wp.y] = ' ';
        
        wp.x = 1 + alphaint * 2  ;
        wp.y = 2 + numint * 4;
        
        board[wp.x][wp.y] = 'W';


    } else if (l==3) {
        

        if (wmove[2]=='h') {
            int x = 1 + alphaint * 2;
            int y = 4 + numint * 4;
            board[x][y]=(char) 186;
            board[x+1][y] = (char) 186;
            board[x+2][y] = (char) 186;
        }
        else if (wmove[2]=='v') {
            int x = 2 + alphaint * 2;
            int y = 2 + numint * 4;
            board[x][y] = (char)205;
            board[x][y-1] = (char)205;
            board[x][y+1] = (char)205;
            board[x][y+3] = (char)205;
            board[x][y+2] = (char)205;
            board[x][y+4] = (char)205;
            board[x][y+5] = (char)205;

        }
        pwwall--;
        printf("White walls left : %d\n",pwwall);

    }
    return pwwall;

}



//to update the moves played by black on game board
int blackupdateboard(char bmove[],char board[][COLUMNS],int pbwall) {
    //updating the board when black plays a move
    int l = strlen(bmove);
    
    char num = bmove[1];
    char alpha = bmove[0];
    int numint = num - 48;
    int alphaint = alpha - 96 ;
    
    if (l==2) {
        board[bp.x][bp.y] = ' ';
 
        bp.x = 1 + alphaint * 2  ;
        bp.y = 2 + numint * 4;

        board[bp.x][bp.y] = 'B';


    } else if (l==3) {
        

        if (bmove[2]=='h') {
            int x = 1 + alphaint * 2;
            int y = 4 + numint * 4;
            board[x][y]=(char) 186;
            board[x+1][y] = (char) 186;
            board[x+2][y] = (char) 186;
        }
        else if (bmove[2]=='v') {
            int x = 2 + alphaint * 2;
            int y = 2 + numint * 4;
            board[x][y] = (char)205;
            board[x][y-1] = (char)205;
            board[x][y+1] = (char)205;
            board[x][y+3] = (char)205;
            board[x][y+2] = (char)205;
            board[x][y+4] = (char)205;
            board[x][y+5] = (char)205;

        }

        pbwall--;
        printf("Black walls left : %d\n",pbwall);
    }
    return pbwall;


}



//to check if any one of the players has won the game
int checkwin(char board[][COLUMNS]) {
    for (int i=3;i<ROWS-3;i+=2) {
        if (board[i][6]=='B') {
            
            return 2;
        }
        else if (board[i][COLUMNS-7]=='W') {
            
            return 1;
        }
        
    }
    return 0;
}



//defining the notation table
void deftable(char table[][19]){
    for (int i=0;i<153;i++){
            if (i%2==0){
                for (int j=0;j<19;j++){
                    if (j%6==0){
                        table[i][j]='+';
                    }
                    else {
                        table[i][j]='-';
                    }
                }
            }
            else {
                for (int j=0;j<19;j++){
                    if (j%6==0){
                        table[i][j]='|';
                    }
                    else {
                        table[i][j]=' ';
                    }
                }
            }
    }

    table[1][9] = 'W';
    table[1][15] = 'B';
    int t = 48;

    for (int i=1 ; i<=9 ; i++) {
        table[1+2*i][3] = t+1;
        t++;
    }  
    for (int i=10;i<=75;i++) {
        int d1 = (int) i/10 ;
        int d2 = i%10;
        table[1+2*i][3]= (char)48 + d1;
        table[1+2*i][4] = (char)48 +d2;
    }
}



//to take input moves and commands from the players
void input(char inp[]){
    gets(inp);
}



//to update the notation table after each move of every player
void updatetable(char table[][19],char input[],int *px,int *py){
    char *p,*q;
    p=input;
    q=input;
    int c=0;
    for (int i=0;*q!='\0';q++){
        c++;
    }
    if (c==3){
        for(int i=*px;i<*px+3;i++){
            table[*py][i]=*p;
            p++;
        }
        if (*px==14) {
            *px = 8;
            *py += 2;
        } else if (*px == 8) {
            *px = 14;
        }
    }
    else if (c==2){
        for (int i=*px;i<*px+2;i++){
            table[*py][i]=*p;
            p++;
        }
        if (*px==14) {
            *px = 8;
            *py += 2;
        } else if (*px == 8) {
            *px = 14;
        }
    }
}



//to print the notation table when the command show is called
void printtable(char table[][19],int counter){
    for (int i=0;i<7+2*counter;i++){
        for (int j=0;j<19;j++){
            printf("%c",table[i][j]);
        }
        printf("\n");
    }
    
}



//to check the validity of the whites moves
int wcheckvalidity(char wmove[],char board[][COLUMNS],int wwall) {
    int counter=0;
    //1
    if (checkbounds(wmove)) {
        counter++;
        
    } else {
        return 0;

    }

    //2
    if (movecheckw(wmove)) {
        counter++;

    }else {
        return 0;
    }

    //3
    if (wallnocheck(wmove,wwall)) {
        counter++;
    }else {
        return 0;
    }

    //4
    if (wallvalidate(wmove,board)) {
        counter++;
    } else {
        return 0;
    }
    
    if (wcheckw(board,wmove)) {
        counter++;
    }
    else {
        return 0;
    }

    if (counter==5) {
        return 1;
    }

    
}



//to check the validity of the blacks moves
int  bcheckvalidity(char bmove[],char board[][COLUMNS],int bwall) {
    int counter=0;
    
    //1
    if (checkbounds(bmove)) {
        counter++;

    }
    else {
        return 0;
    }
    
    //2
    if (movecheckb(bmove)) {
        counter++;
    }
    else {
        return 0;
    }
    
    //3
    if (wallnocheck(bmove,bwall)) {
        counter++;
    }else {
        return 0;
    }

    //4
    if (wallvalidate(bmove,board)) {
        counter++;
    } else {
        return 0;
    }
    
    //5
    if (wcheckb(board,bmove)){
        counter++;
    }
    else {
        return 0;
    }


    if (counter==5) {
        return 1;
    }


}



//to convert dispaly co-ordinates into matrix indices
int  xalphaint(char a) {
    int alphaint=a-96;
    int x = 1 + alphaint * 2;

    return x;
}



//to convert dispaly co-ordinates into matrix indices
int ynumint(char b) {
    int numint = b - 48;
    int y = 2 + numint * 4;

    return y;
}



//to check if the move is within the bounds of the board
int checkbounds(char userinput[])
{
    char r,s,t;
    r=userinput[0];
    s=userinput[1];
    t=userinput[2];
    strlwr(userinput);
    int ln=strlen(userinput);
    
    if(ln==2 || ln==3)
    {
        if(r>=97 && r<=105)
        {
            if(s>=49 && s<58)
            {
                if(ln==3)
                {
                    if(t=='h'|| t=='v')
                    {
                        if(r!=105 && s!=57)
                        {
                            return 1;
                        }
                        else return 0;
                    }
                    else return 0;
                }
            }
            else return 0;    
        }
        else return 0;           
    }
    else return 0;           
}



//to check the validity of the move input by the user for white without the condition of walls
int movecheckw(char wmove[]){
    if (strlen(wmove)==2) {
        int y=ynumint(wmove[1]);
        int x=xalphaint(wmove[0]);

        
        int d1 = x-wp.x;
        int d2 = y-wp.y;
        int d3 = x-bp.x;
        int d4 = y-bp.y;
        if ((d1==0 && d2==4 || d2==0 && d1==2 || d1==0 && d2==-4 || d2==0 && d1==-2) && (d3!=0 || d4!=0)){
            return 1;
        }
        else if (((d1==4 && d2==0) || (d1==-4 && d2==0)) && ((d3==2 && d4==0) || (d3==-2 && d4==0))){
            return 1;
        }
        else if (((d1==0 && d2==8) || (d1==0 && d2==-8)) && ((d3==0 && d4==4) || (d3==0 && d4==-4))){
            return 1;
        }
        else {
            return 0;
        }

    }
    else {
        return 1;
    }
}



//to check the validity of the move input by the user for black without the condition of walls
int movecheckb(char bmove[]){
    if (strlen(bmove)==2) {
        int y=ynumint(bmove[1]);
        int x=xalphaint(bmove[0]);

        
        int d1 = x-bp.x;
        int d2 = y-bp.y;
        int d3 = x-wp.x;
        int d4 = y-wp.y;
        if ((d1==0 && d2==4 || d2==0 && d1==2 || d1==0 && d2==-4 || d2==0 && d1==-2) && (d3!=0 || d4!=0)){
            return 1;
        }
        else if (((d1==4 && d2==0) || (d1==-4 && d2==0)) && ((d3==2 && d4==0) || (d3==-2 && d4==0))){
            return 1;
        }
        else if (((d1==0 && d2==8) || (d1==0 && d2==-8)) && ((d3==0 && d4==4) || (d3==0 && d4==-4))){
            return 1;
        }

        else {
            return 0;
        }
    }
    else {
        return 1;
    }
    
}



//all the rules have been stored here
void rule()
{   printf("\x1b[34m===============================================================================================\n");
    printf("===============================================================================================\n");
    printf("\x1b[30m\x1b[29m||||||||-------------------------------------RULES-------------------------------------||||||||\n");
    printf("||||||||--------------------------------PLAYER ONE ::::  W-----------------------------||||||||\n");
    printf("||||||||--------------------------------PLAYER TWO ::::  B-----------------------------||||||||\n");
    printf("||||||||--------------------------------NOTATIONS ::::::-------------------------------||||||||\n");
    printf("||||||||----------moves in the form notations using board defined coordinates----------||||||||\n");
    printf("||||||||---------player has to enter the coordinate of his defined destination---------||||||||\n");
    printf("||||||||--------------------------KEY FEATURE:: WALLS :::---> -------------------------||||||||\n");
    printf("||||||||players are allowed to block two set of moves of their opponent by wall feature||||||||\n");
    printf("||||||||----------'h'  stands for vertical and 'v' stands for horizontal wall----------||||||||\n");
    printf("||||||||-----------------------------OBJECTIVE OF THE GAME-----------------------------||||||||\n");
    printf("||||||||-----------to reach the opposite end of the board as initially placed----------||||||||\n");
    printf("||||||||------------------------------COMMANDS ALLOWED:::------------------------------||||||||\n");
    printf("||||||||=================================1. SHOW ::--> ================================||||||||\n");
    printf("||||||||-------------show commands for printing the notationboard for game-------------||||||||\n");
    printf("||||||||=================================2. RULE=======================================||||||||\n");
    printf("||||||||--------------this commands displays set of basics rules in brief--------------||||||||\n");
    printf("||||||||=================================3. WALL=======================================||||||||\n");
    printf("||||||||==============allows the user to check no. of walls left with it ==============||||||||\n");
    printf("||||||||=================================4. QUIT::-->==================================||||||||\n");
    printf("||||||||--------------------------------to quit the game-------------------------------||||||||\n");
    printf("\x1b[0m\x1b[34m===============================================================================================\n");
    printf("\x1b[34m===============================================================================================\n\x1b[0m");
}



//to check if the number of walls have been exhausted or not
int wallnocheck(char move[],int wall){
    if (strlen(move)==3) {
        if (wall!=0) {
            return 1;
        }
        else {
            printf("........YOU HAVE RUN OUT OF WALLS.......");
            return 0;

        }
    }
    else {
        return 1;
    }
}



//to check validity of the wall being placed on the board
int wallvalidate(char move[],char board[][COLUMNS]) {
    if (strlen(move)==3) {
        int x = xalphaint(move[0]);
        int y = ynumint(move[1]);


        if (move[2]=='h'){
            if (board[x][y+2]!=(char)186 && board[x+2][y+2]!=(char)186 && board[x+1][y+2]!=(char)205) {
                return 1;
            } else {
                return 0;
            }
        } else if (move[2]=='v') {
            if (board[x+1][y]!=(char)205 && board[x+1][y+4]!=(char)205 && board[x+1][y+2]!=(char)186) {
                return 1;
            } else {
                return 0;
            }
        }


    }
    else {
        return 1;
    }
}



// to check if whites move is going through a wall
int wcheckw(char board[][COLUMNS],char wmove[]){
    if (strlen(wmove)==2) {
        int x = xalphaint(wmove[0]);
        int y = ynumint(wmove[1]);
        int d1 = x-wp.x;
        int d2 = y-wp.y;
        int d3 = bp.x-wp.x;
        int d4 = bp.y-wp.y;
        if (d2==4){
            if (board[wp.x][wp.y+2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==-4){
            if (board[wp.x][wp.y-2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==2){
            if (board[wp.x+1][wp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==-2){
            if (board[wp.x-1][wp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==8 && d4!=4){
            if (board[wp.x][wp.y+6]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==-8 && d4!=-4){
            if (board[wp.x][wp.y-6]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==4 && d3!=2){
            if (board[wp.x+3][wp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==-4 && d3!=-2){
            if (board[wp.x-3][wp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==8 && d4==4){
            if (board[wp.x][wp.y+6]!=(char)186 && board[wp.x][wp.y+2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==-8 && d4==-4){
            if (board[wp.x][wp.y-6]!=(char)186 && board[wp.x][wp.y-2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==4 && d3==2){
            if (board[wp.x+3][wp.y]!=(char)205 && board[wp.x+1][wp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==-4 && d3==-2){
            if (board[wp.x-3][wp.y]!=(char)205 && board[wp.x-1][wp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }

    }
    else {
        return 1;
    }

}



// to check if blacks move is going through a wall
int wcheckb(char board[][COLUMNS],char bmove[]){
    if (strlen(bmove)==2) {
        int x = xalphaint(bmove[0]);
        int y = ynumint(bmove[1]);
        int d1 = x-bp.x;
        int d2 = y-bp.y;
        int d3 = wp.x-bp.x;
        int d4 = wp.y-bp.y;
        if (d2==4){
            if (board[bp.x][bp.y+2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==-4){
            if (board[bp.x][bp.y-2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==2){
            if (board[bp.x+1][bp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==-2){
            if (board[bp.x-1][bp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==8 && d4!=4){
            if (board[bp.x][bp.y+6]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==-8 && d4!=-4){
            if (board[bp.x][bp.y-6]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==4 && d3!=2){
            if (board[bp.x+3][bp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==-4 && d3!=-2){
            if (board[bp.x-3][bp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==8 && d4==4){
            if (board[bp.x][bp.y+6]!=(char)186 && board[bp.x][bp.y+2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d2==-8 && d4==-4){
            if (board[bp.x][bp.y-6]!=(char)186 && board[bp.x][bp.y-2]!=(char)186){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==4 && d3==2){
            if (board[bp.x+3][bp.y]!=(char)205 && board[bp.x+1][bp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }
        else if (d1==-4 && d3==-2){
            if (board[bp.x-3][bp.y]!=(char)205 && board[bp.x-1][bp.y]!=(char)205){
                return 1;
            }
            else {
                return 0;
            }
        }

    }
    else {
        return 1;
    }

}



//to create the integer matrix having source as 1 , destination as 2 , blocked cells as 0
//and traversable cells as 3
void pathmatrix(int pathmat[17][17],char board[][COLUMNS],char src) {
    for (int i=3;i<ROWS-3;i++) {
        for (int j=6;j<=COLUMNS-7;j+=2) {
            int x = i-3;
            int y = (j-6)/2 ;
            if (board[i][j]=='|' || board[i][j]=='-' || board[i][j]==' ') {
                pathmat[x][y]=3;

            } else if (board[i][j]==(char)186 || board[i][j]==(char)205 || board[i][j]=='+') {
                pathmat[x][y]=0;

            } else if (board[i][j]==src) {
                pathmat[x][y]=1;
            } else {
                pathmat[x][y] = 3;
            }
        }
    }

    
}



int isSafe(int i, int j, int matrix[][N])
{
    if (i >= 0 && i < N && j >= 0 && j < N)
        return 1;
    return 0;
}
 
// Returns 1 if there is a
// path from a source (a
// cell with value 1) to a
// destination (a cell with
// value 2)
int isaPath(int matrix[][N], int i, int j,int visited[][N])
{
    // Checking the boundaries, walls and
    // whether the cell is unvisited
    if (isSafe(i, j, matrix) && matrix[i][j] != 0 && !visited[i][j]) {
        // Make the cell visited
        visited[i][j] = 1;
 
        // if the cell is the required
        // destination then return 1
        if (matrix[i][j] == 2)
            return 1;
 
        // traverse up
        int up = isaPath(matrix, i - 1, j, visited);
 
        // if path is found in up
        // direction return 1
        if (up)
            return 1;
 
        // traverse left
        int left = isaPath(matrix, i, j - 1, visited);
 
        // if path is found in left
        // direction return 1
        if (left)
            return 1;
 
        // traverse down
        int down = isaPath(matrix, i + 1, j, visited);
 
        // if path is found in down
        // direction return 1
        if (down)
            return 1;
 
        // traverse right
        int right = isaPath(matrix, i, j + 1, visited);
 
        // if path is found in right
        // direction return 1
        if (right)
            return 1;
    }
 
    // no path has been found
    return 0;
}
 
// Method for finding and printing
// whether the path exists or not
int isPath(int matrix[][N])
{
 
    // Defining visited array to keep
    // track of already visited indexes
    int visited[N][N];
    memset(visited, 0, sizeof(visited));
 
    // Flag to indicate whether the
    // path exists or not
    int flag = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            // if matrix[i][j] is source
            // and it is not visited
            if (matrix[i][j] == 1 && !visited[i][j])
 
                // Starting from i, j and
                // then finding the path
                if (isaPath(matrix, i, j, visited)) {
 
                    // if path exists
                    flag = 1;
                    break;
                }
        }
    }
    
    return flag;
}



//to finally check if all the paths are blocked for any of the pieces
int checkpathblock(char board[][COLUMNS],int pathmat[][N]) {
    int cw=0,cb=0;
    for (int i=0;i<17;i+=2) {
        pathmatrix(pathmat,board,'W');
        

        if (i!=0) {
            pathmat[i-2][16]=3;
            pathmat[i][16]=2;
        } else {
            pathmat[i][16]=2;
        }

        if (isPath(pathmat)) {
            cw++;
        } 

        
    }
    pathmat[16][16]=3;



    for (int i=0;i<17;i+=2) {
        pathmatrix(pathmat,board,'B');

        if (i!=0) {
            pathmat[i-2][0]=3;
            pathmat[i][0]=2;
        } else {
            pathmat[i][0]=2;
        }

        if (isPath(pathmat)) {
            cb++;
        } 
    }
    
    if (cw!=0 && cb!=0) {
        return 1;
    } else {
        return 0;
    }

}

//-----------------------------THE END-------------------------------//