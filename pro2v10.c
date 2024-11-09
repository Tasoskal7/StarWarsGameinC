/* ANASTASIOS KALOMOIRIS
AM: 2022202200067
dit22067@uop.gr

IOANNA TAXIARCHIA MICHOU
AM: 2022202200133
dit22133@uop.gr
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>


#define minN 5
#define maxN 20
#define minM 5
#define maxM 20



void fillArray(double perc1, double perc2);
void printArray(void);
void game(void);
void moveLeila(char move);
void help(void);
void moveObject(void);
void moveStormRandomly(void);
void DarthVaderMove(void);

char **array;
char **blank_array;
int m,n;
int leia_x, leia_y;
int leia_steps = 0;
int d_x, d_y;
int life = 1;
int choice;
double perc1;
double perc2;
int direct;// 1 deksia ,2 aristera , 3 pano , 4 katw
int moved_boxes = 0;

int main(void)
{
    int i, j;

    srand(time(NULL));
    direct = rand()%4+1;
    printf("!!!!!Welcome to the game!!!!!\n");
    printf("Please enter the dimensions you would like to start with.\n");
    scanf("%d %d", &n, &m);

    do //elenxos an ta dimensions einai mesa sto orio
    {
        if(n < minN || m < minM)
        {
            printf("You can only choose a dimension between 5 & 20\n");
            scanf("%d %d", &n, &m);
        }
        if(n > maxN || m > maxM)
        {
            printf("You can only choose a dimension between 5 & 20\n");
            scanf("%d %d", &n, &m);
        }
    } 
    while(n < minN || m < minM|| n > maxN || m > maxM);

    array = (char**)malloc((n + 2)* sizeof(char*)); //malloc gia ton pinaka me ta stoixeia 
    if(array == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    for(i = 0; i < n + 2 ; i++)
    {
        array[i] = (char*)malloc((m + 2)*sizeof(char));
        if(array[i] == NULL)
        {
            printf("Memory allocation failed!");
            exit(1);
        }
    }

    blank_array = (char**)malloc((n + 2)* sizeof(char*)); //malloc gia ton pinaka me ta # 
    if(blank_array == NULL)
    {
        printf("Memory allocation failed!");
        exit(1);
    }

    for(i = 0; i < n + 2; i++)
    {
        blank_array[i] = (char*)malloc((m + 2)*sizeof(char));
        if(blank_array[i] == NULL)
        {
            printf("Memory allocation failed!");
            exit(1);
        }
    }

    printf("Please choose difficulty level\n");
    printf("1: Begginer, 2: Semipro, 3: Worldclass, 4:Ultimate\n");
    scanf("%d",&choice);
    while(1)
    {
        switch(choice)
        {
            case 1:
                perc1 = 0.02;
                perc2 = 0.13;
                fillArray(perc1, perc2);
                printArray();
                game();
                break;
            case 2:
                perc1 = 0.05;
                perc2 = 0.1;
                fillArray(perc1, perc2);
                printArray();
                game();
                break;
            case 3:
                perc1 = 0.1;
                perc2 = 0.05;
                fillArray(perc1, perc2);
                printArray();
                game();
                break;
            case 4:
                perc1 = 0.15;
                perc2 = 0;
                fillArray(perc1, perc2);
                printArray();
                game();
                break;
            default:
                printf("You can only choose between 1-4\n");
                scanf("%d", &choice);
        }
    }

    for(i = 0; i < n + 2; i++)
    {
        free(array[i]);
    }
    free(array);

    for(i = 0; i < n + 2; i++)
    {
        free(blank_array[i]);
    }
    free(blank_array);
}

void fillArray(double perc1, double perc2) //gemisma tou pinaka me ta stoixeia
{
    int i=0, j=0;
    int leia=0, DarthVader=0, R2D2=0, stormtroopers=0, object=0;
    int sum_object=0;
    i = rand()%n + 1;
    j = rand()%m + 1;

    for(i = 1; i <= n; i++)  //gemisma oloklhrou tou pinaka me '.'
    {
        for(j = 1; j <= m; j++)
        {
            array[i][j] = '.';
        }
    }
    
    while(leia < 1)  //topothethsh ths leia
    {
        i = rand()%n + 1;
        j = rand()%m + 1;
        if(array[i][j] == '.') 
        {
            array[i][j] = 'L';
            leia_x = i;
            leia_y = j;
            leia++;
        }
        
    }

    i = rand()%n + 1;
    j = rand()%m + 1;

    while(DarthVader < 1) //topothethsh tou Darth Vader
    {
        i = rand()%n + 1;
        j = rand()%m + 1;
        if(array[i][j]=='.') 
        {
            if((i == 1 && j == 1) || (i == 1 && j == m) || (i == n && j == 1) || (i == n && j == m)) //o darth vader mporei na einai mono se gonia
            {   
                array[i][j] = 'D';
                d_x = i;
                d_y = j;
                DarthVader++;
            }
        }
    }

    i = rand()%n + 1;
    j = rand()%m + 1;

    while(R2D2 < 1) //topothethsh tou R2D2
    {
        i = rand()%n + 1;
        j = rand()%m + 1;
        if(array[i][j] == '.')
        {
            array[i][j] = 'R';
            R2D2++;
        }
    }

    int sum_stormtroopers = (n*m)*perc1; //topothethsh tvn stormtroopers
    stormtroopers= 0;
    while(stormtroopers < sum_stormtroopers)
    {
        i = rand()%n + 1;
        j = rand()%m + 1;
        if(array[i][j] == '.')
        {
            array[i][j] = '@';
            i = rand()%n + 1;
            j = rand()%m + 1;
            stormtroopers++;
        }
    }

    if(sum_stormtroopers < 2) //prepei na yperxoun toulaxiston 2 stormtroopers
    {
        while(sum_stormtroopers<2){
            i = rand()%n + 1;
            j = rand()%m + 1;
            if(array[i][j] == '.')
            {
                array[i][j] = '@';
                sum_stormtroopers++;
            }
        }
    }

    sum_object = (n*m)*perc2; //topothethsh tvn empodivn
    while(object < sum_object)
    {
        i = rand()%n + 1;
        j = rand()%m + 1;
        if(array[i][j] == '.')
        {
            array[i][j] = 'X';
            object++;
        }
    }

    for(i = 1; i <= n; i++)  //gemizei ton keno pinaka me '#'
    {
        for(j = 1; j <= m; j++)
        {
            
            blank_array[i][j] = '#';
           
            
        }
    }
}

void printArray(void)
{
    int i, j, z, x, y;

    //Emfanish ton grammatvn orizontia
    printf("   ");
    for(z = 1; z <= m; z++)
    {
        printf("%2c ", 'A' + (z - 1));
    }
    printf("\n");
    printf("---");
    for(i = 0; i < m; i++)
    {
        printf("---");
    }
    printf("\n"); 
    
    //emfanish toy telikou array
    for (i = 1; i <= n; i++)
    {
        printf("%2d|", i);
        for (j = 1; j <= m; j++)
        {
            if(i == leia_x || j == leia_y )                
            {
                      
                printf("%2c ",array[i][j]);
            }
            else if( array[i][j] == 'D')
            { 
                
                printf("%2c ",array[i][j]);
            }
            else if( array[i][j] == 'X')
            {
                
                printf("%2c ", array[i][j]);
            }
            else               
            {              
                printf("%2c ", blank_array[i][j]);
            }    
          
        }
        printf("\n");     
    }
    printf("Current lifes: %d\n",life);    
}

void game(void) //jekinaei to paixnidi
{
    int i,j;
    char move[100];  //enas buffer pinakas pou apothhkeuei entoles pou eisagei o xrhsths
    while (1)
    {
        printf("Enter movement command (U/u/D/d/L/l/R/r  Or H/h(HELP) Or '>'(Move obstacle) Or X/x(Exit)): ");
        printf("\n");
        scanf("%s", &move);
        if(strcmp(move, "H") == 0 || strcmp(move, "h") == 0)
        {
            help();
            move[100]=NULL;
            game();
        }

        if(strcmp(move, "X") == 0 || strcmp(move, "x") == 0) //termatizei to paixnidi
        {
            printf("Game is over!!!!!!\n");
            exit(1);
        }
        if(strcmp(move, ">") == 0) //metakinei empodio
        {
            if(moved_boxes < 2)
            {
                moveObject();
                move[100]=NULL;
                moved_boxes++;
                printArray();
                game();
            }
            else
            {
                printf("You can only move 2 objects per game\n");
                game();
            }
        }
        for (i = 0; i < strlen(move); i++) 
        {
            moveLeila(move[i]);
                if (leia_steps % 2 != 0) 
                {
                    DarthVaderMove();
                }
        }
        printArray();
        printf("\n");     
        move[100]=NULL;
    }
}

void moveLeila(char move)
{
    int new_x = leia_x;
    int new_y = leia_y;

    switch (move)
    {
        case 'U':
        case 'u':
            new_x--;
            break;
        case 'D':
        case 'd':
            new_x++;
            break;
        case 'L':
        case 'l':
            new_y--;
            break;
        case 'R':
        case 'r':
            new_y++;
            break;
    }

    if(new_x < 1 || new_x > n || new_y < 1 || new_y > m || array[new_x][new_y] == 'X') //elegxei ta oria tou pinaka
    {
        printf("Invalid move! Please try again.\n");
    }
    else if(array[new_x][new_y] == '@' && life == 1)
    {
        array[leia_x][leia_y] = '.';
        array[new_x][new_y] = 'L';
        leia_x = new_x;
        leia_y = new_y;
        printf("LEIA KILLED A STORMTROOPER! but lost a life\n");
        life--;
        leia_steps++;
        moveStormRandomly();
    }
    else if(array[new_x][new_y] == '@' && life == 0)
    {
       printf("LEIA WAS KILLED BY STORMTROOPER! end of the game\n");
       array[leia_x][leia_y] = '.';
       array[new_x][new_y] = '@';
       printArray();
       exit(1);
    }
    else if(array[new_x][new_y] == 'R')
    {
        n = n-1;
        m = m-1;
        if(n==4 || m==4)
        {
            printf("CONGRATS YOU WON!!!!\n");
            exit(1);
        }
        printf("ON TO THE NEXT LEVEL!!!!!!!!\n");
        moved_boxes = 0;
        fillArray(perc1,perc1);
        printArray();
        game();
    }
    else if(array[new_x][new_y] == 'D')
    {
        printf("DARK SIDE WINS ... goodbye\n");
        life--;
        array[leia_x][leia_y] = '.'; 
        array[new_x][new_y] = 'D';
        printArray();
        exit(1);
    }
    else
    {
        array[leia_x][leia_y] = '.';
        array[new_x][new_y] = 'L';
        leia_x = new_x;
        leia_y = new_y;
        leia_steps++;
        moveStormRandomly();

    }
}

void help(void) //Entolh voitheias
{
    int i, j, z;

    //Emfanish ton grammatvn orizontia
    printf("   ");
    for (z = 1; z <= m; z++)
    {
        printf("%2c ", 'A' + (z - 1));
    }
    printf("\n");
    printf("---");
    for(i = 0; i < m; i++)
    {
        printf("---");
    }
    printf("\n");

    for (i = 1; i <= n; i++)
    {
        printf("%2d|", i);
        for (j = 1; j <= m; j++)
        {
            printf("%2c ",array[i][j]);
        }
        printf("\n");
    }

    printArray();
}

void moveObject(void)
{
    char from_col, to_col;
    int from_row, to_row;

    printf("Enter the command to move the object (e.g., E3>G3): ");
    scanf(" %c%d>%c%d", &from_col, &from_row, &to_col, &to_row);

    // Metatroph sthlhs se kegalaia 
    from_col = toupper(from_col);
    to_col = toupper(to_col);

    //Kanei ta grammata arithmous
    int from_col_index = from_col - 'A' + 1;
    int to_col_index = to_col - 'A' + 1;

    if (from_row < 1 || from_row > n || from_col_index < 1 || from_col_index > m || array[from_row][from_col_index] != 'X')
    {
        printf("Invalid source position or no object found at the specified position.\n");
        return;
    }
    if (to_row < 1 || to_row > n || to_col_index < 1 || to_col_index > m || array[to_row][to_col_index] != '.')
    {
        printf("Invalid destination position or destination is not empty.\n");
        return;
    }

    //Metakinei to empodio
    array[to_row][to_col_index] = 'X';
    array[from_row][from_col_index] = '.';
}

void moveStormRandomly(void) 
{
    int i, j;
    for (i = 1; i <= n; i++) 
    {
        for (j = 1; j <= m; j++) 
        {
            if (array[i][j] == '@') 
            {
                //allazei kateuthinsh otan xreiazetai
                if (direct == 1 && (j == m || array[i][j + 1] != '.')) 
                {
                    direct = 2; 
                } 
                else if (direct == 2 && (j == 1 || array[i][j - 1] != '.')) 
                {
                    direct = 1; 
                }
                else if (direct == 3 && (i == 1 || array[i - 1][j] != '.')) 
                {
                    direct = 4; 
                } 
                else if (direct == 4 && (i == n || array[i + 1][j] != '.')) 
                {
                    direct = 3; 
                }

                switch (direct) 
                {
                    case 1: //dejia
                        if (j <m && array[i][j + 1] == '.') 
                        {
                            array[i][j] = '.';
                            array[i][j + 1] = '@';
                        }
                        break;
                    case 2: //aristera
                        if (j > 1 && array[i][j - 1] == '.') 
                        {
                            array[i][j] = '.';
                            array[i][j - 1] = '@';
                        }
                        break;
                    case 3: //pano
                        if (i > 1 && array[i - 1][j] == '.') 
                        {
                            array[i][j] = '.';
                            array[i - 1][j] = '@';
                        }
                        break;
                    case 4: //katv
                        if (i < n && array[i + 1][j] == '.') 
                        {
                            array[i][j] = '.';
                            array[i + 1][j] = '@';
                        }
                        break;
                }
            }
        }
    }
}

void DarthVaderMove(void) 
{
    int new_d_x = d_x, new_d_y = d_y;

    //Ypologizei thn nea thesh
    if (d_x < leia_x && d_x + 1 < n && array[d_x + 1][d_y] == '.') 
    {
        new_d_x++;
    } 
    else if (d_x > leia_x && d_x - 1 > 0 && array[d_x - 1][d_y] == '.') 
    {
        new_d_x--;
    }

    if (d_y < leia_y && d_y + 1 < m && array[new_d_x][d_y + 1] == '.') 
    {
        new_d_y++;
    } 
    else if (d_y > leia_y && d_y - 1 > 0 && array[new_d_x][d_y - 1] == '.') 
    {
        new_d_y--;
    }
    if ((new_d_x == leia_x && new_d_y == leia_y) || (new_d_x == leia_x && new_d_y + 1 == leia_y) || (new_d_x == leia_x + 1 && new_d_y == leia_y) || (new_d_x == leia_x + 1 && new_d_y + 1 == leia_y)) 
    {
        printf("Game over! Darth Vader caught Princess Leia.\n");
        exit(0);
    }

    array[d_x][d_y] = '.';
    array[new_d_x][new_d_y] = 'D';
    d_x = new_d_x;
    d_y = new_d_y;

}
