#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int main() {
    int allocation[P][R] = {{0,1,0},{2,0,0},{3,0,2},{2,1,1},{0,0,2}};
    int max[P][R]        = {{7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3}};
    int available[R]     = {3,3,2};
    int need[P][R], work[R], safe[P], count=0;

    for(int i=0;i<R;i++) work[i]=available[i];
    for(int i=0;i<P;i++) for(int j=0;j<R;j++) need[i][j]=max[i][j]-allocation[i][j];

    bool finish[P]={false};
    while(count<P){
        bool found=false;
        for(int p=0;p<P;p++){
            if(!finish[p]){
                bool can=true;
                for(int r=0;r<R;r++) if(need[p][r]>work[r]) { can=false; break; }
                if(can){
                    for(int r=0;r<R;r++) work[r]+=allocation[p][r];
                    safe[count++]=p;
                    finish[p]=true;
                    found=true;
                }
            }
        }
        if(!found) break;
    }

    bool deadlock=false;
    for(int i=0;i<P;i++) if(!finish[i]) deadlock=true;

    if(deadlock){
        printf("Deadlock! Processes: ");
        for(int i=0;i<P;i++) if(!finish[i]) printf("P%d ",i);
    } else{
        printf("Safe sequence: ");
        for(int i=0;i<P;i++) printf("P%d ",safe[i]);
    }
    printf("\n");
    return 0;
}
