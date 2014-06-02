#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cstring>

void printboard(char *board, int N)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i*N+j]);
        }
        printf("\n");
    }
    for (int i = 0; i < N; i++) printf("--");
    printf("\n");
}

bool threatened(char *board, int N, int r, int c)
{
    //check column
    for (int i = 0; i < N; i++) {
        if (board[i*N+c] != '.') {
            return true;
        }
    }
    //check \ diagonal
    for (int i = 0, j = 0; (r + i) < N && (c + j) < N; i++, j++) {
        if (board[(r + i) * N + (c + j)] != '.') {
            return true;
        }
    }
    for (int i = 0, j = 0; (r + i) >= 0 && (c + j) >= 0; i--, j--) {
        if (board[(r + i) * N + (c + j)] != '.') {
            return true;
        }
    }
    //check / diagonal
    for (int i = 0, j = 0; (r + i) < N && (c + j) >= 0; i++, j--) {
        if (board[(r + i) * N + (c + j)] != '.') {
            return true;
        }
    }
    for (int i = 0, j = 0; (r + i) >= 0 && (c + j) < N; i--, j++) {
        if (board[(r + i) * N + (c + j)] != '.') {
            return true;
        }
    }
    return false;
}

void nqueens(std::vector<char*>& solns, char *board, int N, int count = 0)
{
    //if we have a solution
    if (count == N) {
        solns.push_back(strdup(board));
        return;
    }
    //for each index of our current row
    for (int i = 0; i < N; i++) {
        //if not threatened, place queen there and try from there.
        if (!threatened(board, N, count, i)) {
            //make move
            board[count * N + i] = 'Q';
            //Recurse
            nqueens(solns, board, N, count + 1);
            //unmake move
            board[count * N + i] = '.';
        }
    }
}

int main(int argc, char **argv)
{
    int N = 8;
    std::vector<char*> solns;
    if (argc >=2) N = atoi(argv[1]);
    char *board = (char*)malloc(N*N + 1);
    for (int i = 0; i < N*N; i++) board[i] = '.';
    board[N*N] = 0;
    nqueens(solns, board, N);
    for (int i = 0; i < solns.size(); i++) {
        printboard(solns[i], N);
    }
}