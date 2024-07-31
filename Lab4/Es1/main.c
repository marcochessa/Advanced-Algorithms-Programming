#include <stdio.h>
#include <windef.h>

int gcd(int a, int b);

int main() {

    int MCD;
    int N=2160;
    int M=2880;

    MCD=gcd(N,M);
    printf("Il massimo comune divisore: %d\n",MCD);
    return 0;
}

int gcd(int a, int b) {

    //Condizioni di terminazione
    if(a==1){
        return a;
    }

    if(b==1){
        return b;
    }

    if(a==b){
        return a;
    }

    if(a%2==0 && b%2==0){
        return 2*gcd(a/2,b/2);
    }

    if(a%2==1 && b%2==0){
        return gcd(a,b/2);
    }

    if(a%2==0 && b%2==1){
        return gcd(a/2,b);
    }

    if(a%2==1 && b%2==1){
        if(a<b){
            return gcd((b-a)/2,b);
        }
        if(a>b){
            return gcd((a-b)/2,b);
        }
    }

}