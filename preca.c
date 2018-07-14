#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void){
    srand(time(NULL));
    int array_enemy[5]={1,2,3,4,5};
    int array_mine[5]={1,2,3,4,5};
    int match=1;
    int chois,chois_e;
    int used_m[4]={0,0,0,0},used_e[4]={0,0,0,0};
    double score_m=0,score_e=0;
    int error=0;
    int sume,summ;
    printf("99と入力するとルールが表示されます\n");
    for(match=0;match<=4;match++){
        error=0;
        printf("カードを選んでください\n");
        for(int i=0;i<5;i++){
            int bad=0;
            for(int k=0;k<=3;k++){
                if(array_mine[i]==used_m[k]){
                    bad+=1;
                }}
                if(bad==0){
                    printf("%d ",array_mine[i]);
                }
        }
        while(error==0){//カード選択
        printf("\nused number:%d,%d,%d,%d",used_m[0],used_m[1],used_m[2],used_m[3]);
            printf("\n選んだカード：");
            if(scanf("%d",&chois)!=1){
                printf("選べる数字を入力してください\n");
                scanf("%*s");
            }else{
            if(1<=chois&&chois<=5){
                for(int j=0;j<=3;j++){
                    if(chois==used_m[j]){
                        printf("選べる数字を入力してください\n");
                        printf("used number:%d,%d,%d,%d",used_m[0],used_m[1],used_m[2],used_m[3]);
                        error-=1;
                    }
                }error+=1;
            }else if(chois==99){
                printf("ルール\n");
                printf("1.お互いに1~5のうち一つの数字を選び数字の大きい方が勝ちです\n");
                printf("2.同じ数字は2回以上使えません\n");
                printf("3.勝った場合、自分の出したカードの半分と相手のカードの合計が自分のスコアに加算されます\n");
                printf("  負けた場合、相手の出したカードの半分と自分のカードの合計が相手のスコアに加算されます\n");
                printf("  引き分けた場合は、出したカードの半分の値がそれぞれのスコアに加算されます\n");
                printf("4.合計5回勝負し、スコアの大きい方が勝者です\n");
            }
            else{
                printf("選べる数字を入力してください\n");
            }
            }
        }//選択終了
        if(match==0){//
            int n=rand()%18;
            if(n<1){
                chois_e=1;
            }else if(1<=n&&n<=5){
                chois_e=2;
            }else if(5<n&&n<=10){
                chois_e=3;
            }else if(10<n&&n<=15){
                chois_e=4;
            }
            else{
                chois_e=5;
            }
            
        }else if(match==1||match==2){//ここで分岐
            if(score_e<=score_m){
                if(sume>=summ){
                    chois_e=1;
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e+=1;
                    }}
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e+=1;
                    }}

                }else{
                    chois_e=4;
                    for(int k=0;k<=match;k++){
                    if(used_e[k]==5){
                        chois_e-=1;
                        for(int k=0;k<=match;k++){
                    if(used_e[k]==4){
                        chois_e-=1;
                    }
                    }}}
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e-=1;
                    }}
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e-=1;
                    }}
                }
            }else{
                if(sume>=summ){
                    chois_e=5;
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e-=1;
                    }}
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e-=1;
                    }}
                }else{
                    chois_e=2;
                    for(int k=0;k<=match;k++){
                    if(used_e[k]==1){
                        chois_e+=1;
                        for(int k=0;k<=match;k++){
                    if(used_e[k]==2){
                        chois_e+=1;
                    }
                    }}}
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e+=1;
                    }}
                    for(int k=0;k<=match;k++){
                    if(chois_e==used_e[k]){
                        chois_e+=1;
                    }}

                }
            }

        }//match1,2end
        else if(match==3){
            int coin=rand()%2;
            int judge=1;
            if(coin==1){
                chois_e=5;
                while(judge!=0){
                    judge=chois_e;
                    for(int k=0;k<=match;k++){
                        if(chois_e==used_e[k]){
                            chois_e-=1;
                        }}
                        judge-=chois_e;
                }
            }else{
                chois_e=1;
                while(judge!=0){
                    judge=chois_e;
                    for(int k=0;k<=match;k++){
                        if(chois_e==used_e[k]){
                            chois_e+=1;
                        }}
                        judge-=chois_e;
                }
            }
        }
        else{//match=4
           chois_e=1;
           int judge=1;
                while(judge!=0){
                    judge=chois_e;
                    for(int k=0;k<=3;k++){
                        if(chois_e==used_e[k]){
                            chois_e+=1;
                        }}
                        judge-=chois_e;
                } 
        }
        printf("相手のカード：%d\n",chois_e);
        printf("自分のカード：%d\n",chois);
        if(chois>chois_e){
            score_m+=(chois_e+(((double)chois)/2));
            printf("You Win!!\n");
        }else if(chois==chois_e){
            score_e+=((double)chois_e)/2;
            score_m+=((double)chois)/2;
            printf("Draw\n");
        }else{
            score_e+=(chois+(((double)chois_e)/2));
            printf("You lose\n");
        }
        used_m[match]=chois;
        used_e[match]=chois_e;
        sume+=chois_e;
        summ+=chois;
        printf("あなたのスコア：%.2f  相手のスコア：%.2f\n",score_m,score_e);
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");


    }//試合終了
    printf("===結果発表===\n");
    if(score_e<score_m){
        printf("^~You're Winner!!~^\n");
    }else if(score_e>score_m){
        printf("You're loser...\n");
    }else{
        printf("  ~Draw~\n");
    }
    printf("Thank you for playing!\n\n");

}