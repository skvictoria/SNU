#include <stdio.h>

int num(int a){
    int r = 1;
    while(a--){
        r *=2;
    }
    return r;
}

int main(){
    int n, plus, mask, ascii=65, flag=0;
    printf("enter the value of n\n");
    scanf("%d", &n);
    printf("----------------------------------------------------------------------------------\n");
    for(int j=n-1;j>=0;j--){
        printf("%c\t", ascii);
        ascii++;
    }
    printf("S\tC\tF");
    printf("\n\n");
    for(int i=0; i<=num(n)-1; i++){
        plus = 0; flag = 0;
        for(int j=n-1; j>=0; j--){
            mask = i>>j;
            printf("%d\t", mask&1);
            plus += mask&1;
            if(j==0 || j==1){
                if((mask&1) != 0) flag = 1;
            }
        }
        printf("%x\t", plus&0x01);
        printf("%x\t", (plus&0x02)>>1);
        if(flag==0) printf("1\n");
        else printf("0\n");
    }
    
    printf("----------------------------------------------------------------------------------\n");
    return 0;
}
