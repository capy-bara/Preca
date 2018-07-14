/*工学システム　201511155　田巻徳志*/
/*レベル選択が可能なエアホッケーのようなゲーム*/
#include<stdio.h>
#include<unistd.h>
#include<termios.h>
#include<fcntl.h>
#include<stdlib.h>
//#include <conio.h> Windows以外で使えないので参照プログラムで代用
#define M 40//横幅
#define N 23//高さ
int kbhit(void){//http://tricky-code.net/mine/c/mc06linuxkbhit.php 参照
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
int main() {
  int x=(int)M/2,y=(int)N/2;//ballの位置
  char wall1[4]={'<','=','=','>'};//壁の設計
  double w1=M/2,w2=M/2;//壁の初期位置の設定
  double dw2=0.5;//敵の壁の移動変数
  int dx=1,dy=1;//玉の移動変数
  int score1=0,score2=0;
  char wall2[4]={'<','=','=','>'};
  int level=0,goal=0;//レベル設定とゴール判定
  int mes=M-2;//得点メッセージを流すための変数
  char message1[16]={'Y','o','u',' ','g','o','t',' ','a',' ','p','o','i','n','t','!'};
  char message2[16]={'Y','o','u',' ','l','o','s','t',' ','a',' ','p','o','i','n','t'};
  /*ゲーム説明*/
  while(1){
  for(int a=0;a<N;a++){//y
    for(int b=0;b<M;b++){//x
      if(a==0||a==N-1){
        if(b==0||b==M-1){
          printf("$");
        }else{
          printf("~");
        }
      }else if(a-(int)N/2==-1){
        printf("半角の9,0キーで操作します");
        b=M;//行の終了
      }else if(a-(int)N/2==0){
        printf("9で左、0で右に移動します");
        b=M;
      }else if(a-(int)N/2==1){
        printf("ルールは5ポイント先取です");
        b=M;
      }else if(a-(int)N/2==2){
        printf("レベルを1~5キーで入力すると開始します");
        b=M;
      }
    }//b
    printf("\n");
  }//a
  usleep(100000);
  if(kbhit()){//レベルの設定
    level=(int)getchar();
    if(level=='1'){//レベルをアスキーコードから数字への変換
    level=1;
    break;
    }else if(level=='2'){
    level=2;
    break;
    }else if(level=='3'){
    level=3;
    break;
    }else if(level=='4'){
    level=4;
    break;
    }if(level=='5'){
    level=5;
    break;
    }
  }
  
  }//whileの終了
 dw2*=level;//レベルによる壁の速さの変更

  /*本編の開始*/
  while(score1<5&&score2<5){
      printf("\n");//入力による行のズレを解消
    for(int j=0;j<N;j++){//y
      for(int i=0;i<M;i++){//x
	if((int)x==i&&(int)y==j&&goal==0){//玉の出力
	  printf("O");
	}else if(i==0||i==M-1){//側面の壁の出力
	  printf("|");
	}else if(((i-M/2)*(i-M/2)>25)&&(j==0||j==N-1)){//ゴールの作成
	  printf("-");
	}else if(j==N-2&&(int)w1==i){
	  for(int k=0;k<4;k++){//自分の壁を出力
	    printf("%c",wall1[k]);
	  }i+=3;
	}else if(j==1&&(int)w2==i){
	  for(int k=0;k<4;k++){//敵の壁を出力
	    printf("%c",wall2[k]);
	  }i+=3;
	}else if(j==(int)N/2&&(goal==1||goal==2)&&i>=mes){//得点メッセージ
    if(goal==1){
      if(i-mes<16){
        printf("%c",message1[i-mes]);
      }else{
        printf(" ");
      }
    }else{
      if(i-mes<16){
        printf("%c",message2[i-mes]);
      }else{
        printf(" ");
      }
    }
  }
	else{printf(" ");
	}
      }//x
      if(j==5){//敵スコアの出力
	printf("相手のスコア:%d",score2);
      }else if(j==N-5){//自分のスコアの出力
	printf("自分のスコア:%d",score1);
      }
          printf("\n");//ここまでで画面出力は終了
    }//y
    if((int)mes<=0){//mesをリセットしゲームを再開
    if(goal==1){
      dy=1;//得点した側に向かって玉が飛んでいく
    }else{
      dy=-1;//得点した側に向かって玉が飛んでいく
    }
      goal=0;
      mes=M-2;
    x=(int)rand()%(M-1)+1;//再開時の玉のx座標をランダムにする
    y=(int)N/2;//yは真ん中から
    }
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*///跳ね返り系
    if(y+dy==N-2){//自分の壁による跳ね返り
      if((int)w1-1<=x&&x<=(int)w1+1){//壁の左側に当たると左方向に
      dx=-1;
      dy=-1;
      }else if((int)w1+2<=x&&x<=(int)w1+4){//右側に当たると右方向に跳ね返す
      dx=1;
      dy=-1;
    }
    }if(y+dy==1){//敵の壁での跳ね返り
      if((int)w2-1<=x&&x<=(int)w2+1){
      dx=-1;
      dy=1;
      }else if((int)w2+2<=x&&x<=(int)w2+4){
      dx=1;
      dy=1;
    }
    }
    if(x==M-2||x==1)dx*=-1;//x方向の外壁での跳ね返り
    if((int)w2>=(int)(M-5-1.5*level)||(int)w2<=(int)(1+1.5*level))dw2*=-1;//敵の壁の往復運動
    if(y==N-2||y==1)dy*=-1;//y方向の外壁の跳ね返り
    x+=dx;//玉の移動
    y+=dy;//・・
    w2+=dw2;//敵の壁の移動
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*///入力関係
    int c=1;//入力による値の宣言と初期化
    for(;;){
if(!kbhit()){/*キーが押されていたら、変数cにキー取得*/
  break;}
else c=getchar();
}
    if(c=='9'&&w1>1){//9キーが押されているなら左に一マス
      w1-=1;
      }
      else if(c=='0'&&w1+3<M-1){//0キーが押されているなら右に一マス
        w1+=1;
      }
    if(goal!=0){//待機時間
    usleep(100000);//得点メッセージ中の速度
    mes-=1;//得点メッセージを流すための変数
  }else{
    usleep(90000/(level-0.5));//レベルによる速さの変更
  }
  /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*///スコア関係
  if(y+dy==0&&((x+dx-M/2)*(x+dx-M/2)<=25)){//壁がなくゴールに向かっている時得点とする
    score1+=1;
    goal=1;
  }else if(y+dy==N-1&&((x+dx-M/2)*(x+dx-M/2)<=25)){
    score2+=1;
    goal=2;
  }
  
  }//本編whileの終了
  if(score1==5){
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    printf("    You Win!!!!\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");
  }else{
    printf("~~~~~~~~~~~~~~~~~~~~\n");
    printf("    You lost...\n");
    printf("~~~~~~~~~~~~~~~~~~~~\n");
  }
  printf("Thank you for playing!\n");
}

