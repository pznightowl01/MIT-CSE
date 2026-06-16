#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define KEY 0x1234
#define BOARD_SZ 9

struct shm_t {
    char board[BOARD_SZ];
    int turn;
    int moves;
    int winner;
};

void draw(const char *b){
    for(int i=0;i<BOARD_SZ;i++){
        printf(" %c", b[i]?b[i]:'1'+i);
        if(i%3!=2)printf(" |");
        else printf("
");
    }
}

int win(const char *b, char c){
    int w[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for(int i=0;i<8;i++)
        if(b[w[i][0]] == c && b[w[i][1]] == c && b[w[i][2]] == c)
            return 1;
    return 0;
}

int main(int ac,char **av){
    if(ac!=2 || (av[1][0]!='X' && av[1][0]!='O')) return 1;
    int me = av[1][0]=='X'?0:1;
    int shmid = shmget(KEY,sizeof(struct shm_t),0666 | (me==0?IPC_CREAT:0));
    struct shm_t *shm = shmat(shmid,NULL,0);
    if(me==0) memset(shm,0,sizeof(*shm));
    shm->turn=0; shm->winner=-1;
    char sym=me==0?'X':'O';
    while(shm->winner<0){
        while(shm->turn!=me && shm->winner<0) usleep(50000);
        system("clear");
        draw(shm->board);
        if(shm->winner>=0) break;
        int pos;
        do {
            printf("Enter move (1-9): "); fflush(stdout);
            pos = getchar()-'1';
            while(getchar()!='
');
        } while(pos<0 || pos>=9 || shm->board[pos]);
        shm->board[pos] = sym;
        shm->moves++;
        if(win(shm->board,sym)) shm->winner=me;
        else if(shm->moves>=9) shm->winner=2;
        else shm->turn=1-me;
    }
    system("clear"); draw(shm->board);
    if(shm->winner==2) printf("Draw!
");
    else printf("%c wins!
", shm->winner? 'O':'X');
    if(me==0) shmctl(shmid, IPC_RMID, NULL);
    shmdt(shm);
    return 0;
}
