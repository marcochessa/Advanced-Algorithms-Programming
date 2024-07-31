#include <stdio.h>
#define N 30

int main() {
    int V[N];
    int K=0;
    int i=0;
    int tot=0;
    int tmp;
    int count=0;
    int MAX=-1;

    printf("Inserisci gli elementi fino a un massimo di %d\n e -1 per terminare\n",N);

    printf("Inserisci il primo elemento\n");
    scanf("%d",&tmp);
    while(tmp!=-1&&tot<30){
        V[tot]=tmp;
        tot++;
        printf("Inserisci elemento %d\n",tot);
        scanf("%d",&tmp);
    }


    for(i=0; i<tot; i++){
        if(V[i]!=0){
            count++;
        }else{
            if(count>MAX){
                MAX=count;
            }
            count=0;
        }
    }


    for(i=0;i<tot;i++){
        if(V[i]!=0){
            count++;
        }else{
            if(count==MAX){
                printf("sottospazio:[");
                for(int j=i-MAX; j<i; j++){
                    printf("%d",V[j]);
                }
                printf("]\n");
                count=0;
            }
        }
    }

    return 0;
}