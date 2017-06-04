#include <stdio.h>
#include <stdlib.h>

#define N 15
int whoseTurn = 0, undo_player1 = 3, undo_player2 = 3;
int chessboard[N + 1][N + 1] = {0};

void printChessboard(void) //答应棋盘
{
    int i, j;
    system("clear");
    for (i = 0; i < N + 1; i++)
    {
        for (j = 0; j < N + 1; j++)
        {
            if (i == 0)
            {
                printf("%3d", j);
            }
            else if (j == 0)
            {
                printf("%3d", i);
            }
            else if (chessboard[i][j] == 1)
            {
                printf("  X");
            }
            else if (chessboard[i][j] == 2)
            {
                printf("  O");
            }
            else
            {
                printf("  -");
            }
        }
        printf("\n");
    }
}

void clear_buf(void) //清楚缓冲区
{
    int a;
    while ((a = getchar()) != '\n' && a != EOF)
        ;
}

void initGame(void) //初始化game
{
    char c;

    printf("中文界面 输入 y / Y 进入游戏");
    c = getchar();
    clear_buf();
    if (c != 'y' && c != 'Y')
    {
        exit(0);
    }

    printChessboard();
}

int judge(int x, int y) //判断胜负
{
    int i, j;
    int t = 2 - whoseTurn % 2;

    for (i = x - 4, j = y; i <= x; i++)
    {
        if (i >= 1 && i <= N - 4 && t == chessboard[i][j] && t == chessboard[i + 1][j] && t == chessboard[i + 2][j] && t == chessboard[i + 3][j] && t == chessboard[i + 4][j])
            return 1;
    }

    for (i = x, j = y - 4; j <= y; j++)
    {
        if (j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i][j + 1] && t == chessboard[i][j + 2] && t == chessboard[i][j + 3] && t == chessboard[i][j + 4])
            return 1;
    }

    for (i = x - 4, j = y - 4; i <= x, j <= y; i++, j++)
    {
        if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i + 1][j + 1] && t == chessboard[i + 2][j + 2] && t == chessboard[i + 3][j + 3] && t == chessboard[i + 4][j + 4])
            return 1;
    }

    for (i = x + 4, j = y - 4; i >= 1, j <= y; i--, j++)
    {
        if (i >= 1 && i <= N - 4 && j >= 1 && j <= N - 4 && t == chessboard[i][j] && t == chessboard[i - 1][j + 1] && t == chessboard[i - 2][j + 2] && t == chessboard[i - 3][j + 3] && t == chessboard[i - 4][j + 4])
            return 1;
    }

    return 0;
}

void playChess(void)
{
    int i, j, winner;
    char undo;
    if (whoseTurn % 2 == 1)
    {
        printf("轮到玩家1，请输入棋子的位置，格式为行号+空格+列号\n");
        scanf("%d %d", &i, &j);
        clear_buf();
        while (chessboard[i][j] != 0)
        {
            printf("要下的位置已经被占用了，请重新输入：\n");
            scanf("%d %d", &i, &j);
            clear_buf();
        }
        chessboard[i][j] = 1;

        printChessboard();
        if (undo_player1 > 0)
        {
            printf("玩家1要悔棋吗 ? 你还有%d次机会,Y/N \n", undo_player1);
            undo = getchar();
            clear_buf();
            while (undo != 'y' && undo != 'Y' && undo != 'N' && undo != 'n')
            {
                printf("请重新输入：\n");
                undo = getchar();
                clear_buf();
            }
            if ((undo == 'y' || undo == 'Y') && undo_player1 > 0)
            {
                whoseTurn--;
                undo_player1--;
                chessboard[i][j] = 0;
            }
        }
        else
        {
            printf("你没有机会了\n");
        }
    }
    else if (whoseTurn % 2 == 0)
    {
        printf("轮到玩家2，请输入棋子的位置，格式为行号+空格+列号\n");
        scanf("%d %d", &i, &j);
        clear_buf();
        while (chessboard[i][j] != 0)
        {
            printf("要下的位置已经被占用了，请重新输入：\n");
            scanf("%d %d", &i, &j);
            clear_buf();
        }
        chessboard[i][j] = 2;

        printChessboard();
        if (undo_player2 > 0)
        {
            printf("玩家2要悔棋吗 ? 你还有%d次机会,Y/N \n", undo_player2);
            undo = getchar();
            clear_buf();
            while (undo != 'y' && undo != 'Y' && undo != 'N' && undo != 'n')
            {
                printf("请重新输入：\n");
                undo = getchar();
                clear_buf();
            }
            if ((undo == 'y' || undo == 'Y') && undo_player2 > 0)
            {
                whoseTurn--;
                undo_player2--;
                chessboard[i][j] = 0;
            }
        }
        else
        {
            printf("你没有机会了\n");
        }
    }

    printChessboard();

    if (judge(i, j))
    {
        if (1 == whoseTurn % 2)
        {
            printf("玩家1胜！\n");
            exit(0);
        }
        else
        {
            printf("玩家2胜！\n");
            exit(0);
        }
    }
}

int main(void)
{
    initGame();
    while (1)
    {
        whoseTurn++;
        playChess();
        if (whoseTurn == 225)
        {
            printf("平局");
            exit(0);
        }
    }
    return 0;
}
