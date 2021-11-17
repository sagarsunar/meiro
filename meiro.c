#include <stdio.h>
int ma[64][4];     // 迷路のデータを記憶する配列
int checked[64];   // そのセルに何歩でたどり着くかを記録する配列
int route[64];     // そのセルのひとつ前のセル番号を記録する配列
void readMaze(){   // ★　迷路のデータをファイルから読み込む関数
    for(int i=0;i<64;i++){
        scanf("%d,%d,%d,%d",&ma[i][0],&ma[i][1],&ma[i][2],&ma[i][3]);
    }
}
void printMaze(){  // ★　迷路のデータを表示する関数
    int wall[4];
    for(int i=0;i<8;i++) printf(" __");
    printf("\n");
    for(int j=0;j<64;j=j+8){
        printf("|");
        for(int i=j;i<j+8;i++){
            for(int k=0;k<4;k++) wall[k]=0;
            for(int k=0;k<4;k++){
                if(ma[i][k]<0) break;
                if(ma[i][k]==(i+1)) wall[2]=1;
                if(ma[i][k]==(i+8)) wall[3]=1;
            }
            if(wall[3]==0) printf("__");  else printf("  ");
            if(wall[2]==0) printf("|");   else printf(" ");
        }
        printf("\n");
    }
}
void findroute(int start,int end,int stepCount){ // ★　迷路の出口までの最短経路を見つける関数
    checked[start]=stepCount;            // 呼ばれた場所に，何歩目で着いたかを記録する
    if(start==end) return;               // ゴールに着いた
    for(int i=0;i<4;i++){                // ４つの方向について調べる
        if(ma[start][i]<0) break;        // 次に行ける場所が無いならループを抜ける
        if(checked[ma[start][i]]>stepCount+1) // 今のセルの方が短い経路のとき次を探す
        {
            route[ma[start][i]]=start;   // 次に行くセルの番号を経路情報として記録する
            findroute(ma[start][i],end,stepCount+1); // 次に行くセルからゴールまでの道を見つける
        }
    }
}
void printRoute(int cell){    // ★　答えを表示する関数
    if(cell!=0) printRoute(route[cell]);
    printf("%d ",cell);
}
int main(){   // ★　メインプログラム
    for(int i=0;i<64;i++) checked[i]=64;
    readMaze();                     // 迷路のデータをファイルから読み込んでma[][]に格納する
    printMaze();                    // 迷路のデータを表示する
    findroute(0,63,(checked[0]=1)); // セル０からセル６３までの道を見つける
    printRoute(63);                 // 答えを出力する
}