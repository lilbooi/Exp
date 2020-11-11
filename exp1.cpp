#include<iostream>
#include<map>
#include<cstring>
#include<string>
using namespace std;
const string keyWord[35]={"and" ,"array","begin","bool","call","case","char","constant","dim","do",
"else","end","false","for","if","input","integer","not","of","or","output","procedure",
"program","read","real","repeat","set","stop","then","to","true","until",
"var","while","write"};
const int MAXN=105;
string token;
int tlen;  // token长度
int dif;  // 只有标识符和常数有显示，并且通过数字来区分他们的不同。
int row;  // 当前在处理第几行
int col;  // 当前在处理第几列
char ch;  // 当前要处理的字符
bool flag=true; // 当前ch是否有被处理过 or 当前是否没有ch
struct BI{
    char first;
    char second;
    int type;
};
BI biar[5] = {{'*','/',41},{'.','.',46},{'/','*',48},{':','=',50},{'>','=',57}};
map<char, BI> BiDic={{'*',biar[0]}, {'.',biar[1]},{ '/',biar[2]},{ ':',biar[3]},{ '>',biar[4]}};
map<char,int> SiDic={{'(',39}, {')',40}, {'+',43},{',',44},{'-',45},{';',52},{'=',56},{'[',59},{']',60}};

void initToken(){
    tlen=0;
    token="";
}
bool judgeBlank(){
    if(ch==' '||ch=='\t'||ch=='\n')
        return true;
    else return false;
}

int isKeyWord(){
    int t=0;
    for(t=0;t<35;t++){
        if(keyWord[t]==token){
            return t+1;
        }
    }
    return 0;
}

// 用于前面有单词的情况
void solveBlank(){
    if(ch==' '||ch=='\t')
        col++;
    else{
        row++;
        col=0;
    }
}

void printBi(int x){
    if(x==36||x==37||x==38){
        printf("(%d,%d)\n",x,++dif);
        // cout<<"!"<<token<<"!"<<endl;
    }
    else if(x>0)
    {
        printf("(%d,-)\n",x);
        col++;
    }
    // -1: 非法字符
    // -2：字符常熟缺右边单引号
    // -3：注释部分缺右边界符
    else{
        printf("第%d行，第%d个单词有错误\n",row,col);
        if (x==-1){
            printf("错误性质：非法字符\n");
            while(ch!=' '&&ch!='\t'&&ch!='\n'){
                ch=getchar();
            }
        }
        else if(x==-2)
            printf("错误性质：字符常数缺右边的单引号\n");
        else
            printf("错误性质：注释部分缺右边的界符*/\n");
        
    }
    
}

void solveBi(){
    BI bi = BiDic[ch];
    ch=getchar();
    if (judgeBlank())
    {
        printBi(bi.type);solveBlank();
    }
    else if(ch==bi.second) printBi(bi.type+1);
    else
    {
        printBi(bi.type);flag=false;
    }   
}

void judgeToken(){
    initToken();
    if(flag)
        ch = getchar();
    else flag=true;
    if(judgeBlank()){
        if(ch=='\n'){
            col=0;
            row++;
        }
        ch=getchar();
    }
    // 整数 常数
    if(ch>='0'&& ch<='9'){
        while(ch>='0'&&ch<='9'){
            token+=ch;
            ch = getchar();
            flag=false;
        }
        if(judgeBlank()){
            printBi(37);
            solveBlank();
            flag=true;
        }
        else{
            printBi(-1);
        }
    }
    // 单界符 双界符
    else if(ch=='*'||ch=='.'||ch==':'||ch=='/'||ch==':'||ch=='>'){
        solveBi();
    }
    else if(ch=='('||ch==')'||ch=='+'||ch==','||ch=='-'||ch==';'||ch=='='||ch=='['||ch==']')
    {
        printBi(SiDic[ch]);
    }
    // else if(ch=='(') printBi(39);
    // else if(ch==')') printBi(40);
    // else if(ch=='*'){
    //     ch=getchar();
    //     if(judgeBlank()){
    //         printBi(41);
    //         solveBlank();
    //     }
    //     else if(ch=='/') printBi(42);
    //     else
    //     {
    //         printBi(41);
    //         flag=false;
    //     }
    // }
    // else if(ch=='+') printBi(43);
    // else if(ch==',') printBi(44);
    // else if(ch=='-') printBi(45);
    // else if(ch=='.'){
    //     ch=getchar()
    //     if (judgeBlank())
    //     {
    //         printBi(46);solveBlank();
    //     }
    //     else if(ch=='.') printBi(47);
    //     else
    //     {
    //         printBi(46);flag=false;
    //     }        
    // }
    // else if(ch=='/'){
    //     ch=getchar();
    //     if(judgeBlank()) {printBi(48);solveBlank();}
    //     else if(ch=='*') printBi(49);
    //     else
    //     {
    //         printBi(48);flag=false;
    //     }
    // // }
    // else if(ch==':'){

    // }
    else if(ch=='<'){
        ch = getchar();
        if(judgeBlank())
        {    
            printBi(53);
            solveBlank();
        }
        else if(ch=='=')
            printBi(54);
        else if(ch =='>')
            printBi(55);
        else
        {
            printBi(53);
            flag=false;
        }
    }
    // else if(ch=='=') printBi(56);
    // else if(ch=='>'){
    //     ch = getchar();
    //     if(judgeBlank()){
    //         printBi(57);
    //         solveBlank();
    //     }
    //     else if(ch=='=')
    //         printBi(58);
    //     else
    //     {
    //         printBi(57);
    //         flag=false;
    //     }
    // }
    // else if(ch=='[') printBi(59);
    // else if(ch==']') printBi(60);
    
    // 字符常数 
    else if(ch=='\''){
        // 不可跨行
        token+=ch;
        ch=getchar();
        while (ch!='\''&&ch!='\n')
        {
            token+=ch;
            ch=getchar();
        }
        if(ch=='\n'){
            solveBlank();
            printBi(-2);
        }
        else{ token+=ch; printBi(38);}        
    }
    // 标识符 or 保留字
    else if(isalpha(ch)){
        token=ch;
        ch = getchar();
        while(isalpha(ch)||(ch>='0'&&ch<='9')){
            token+=ch;
            ch = getchar();
        }
        int t=-1;
        if(t = isKeyWord()){
            printBi(t);
        }
        else if(judgeBlank()){   
            printBi(36);
            solveBlank();
        }
        else{
            printBi(36);
            flag=false;
        }
        
    }
}
int main()
{
    printf("徐琬玮 18计科1班 201830582128\n");
    char testName[105];
    while(scanf("%s",testName)!=EOF){
        int len=strlen(testName);
        testName[len]='.';
        testName[len+1]='t';
        testName[len+2]='x';
        testName[len+3]='t';
        testName[len+4]='\0';
        freopen(testName,"r",stdin);
        int t=0;
        while(1){
            judgeToken();
            if(ch==EOF) break;
        }
    }
}