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
int tlen;  // token len
int dif;  // id和常数 不同的个数
int row=1;  //  错误第几行
int col;  // 错误第几列
char ch;  // 当前要处理的char
bool flag=true; // true：当前ch已经处理了，false: 还未处理
// 双界符
struct BI{
    char first;
    char second;
    int type;
};
BI biar[5] = {{'*','/',41},{'.','.',46},{'/','*',48},{':','=',50},{'>','=',57}};
map<char, BI> BiDic={{'*',biar[0]}, {'.',biar[1]},{ '/',biar[2]},{ ':',biar[3]},{ '>',biar[4]}};
map<char,int> SiDic={{'(',39}, {')',40}, {'+',43},{',',44},{'-',45},{';',52},{'=',56},{'[',59},{']',60}};

map<string, int> TokenDic; 

void initToken(){
    tlen=0;
    token="";
}

bool judgeBlank(){
    if(ch==' '||ch=='\t'||ch=='\n')
        return true;
    else return false;
}
bool isRop(){
    return ch=='<'||ch=='>'||ch=='=';
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

void solveBlank(){
    if(ch==' '||ch=='\t')
        col++;
    else{
        row++;
        col=0;
    }
    flag=true;
}

void printBi(int x){
    col++;
    if(x==36||x==37||x==38){
        if(TokenDic.count(token))
            printf("(%d,%d)\n",x,TokenDic[token]);
        else 
            printf("(%d,%d)\n",x,TokenDic[token]=++dif);
        // cout<<"!"<<token<<"!"<<endl;
    }
    else if(x>0)
    {
        printf("(%d,-)\n",x);
    }
    // -1: 非法字符，即不是SAMPLE字符集的符号
    // -2：字符常数缺右边的单引号
    // -3：注释部分缺右边的界符*/
    else{
        printf("出现次法错误，位置与第%d行，第%d个词语\n",row,col);
        if (x==-1){
            printf("非法字符，即不是SAMPLE字符集的符号\n");
            while(ch!=' '&&ch!='\t'&&ch!='\n'){
                ch=getchar();
            }
        }
        else if(x==-2)
            printf("字符常数缺右边的单引号，且不能跨行\n");
        else
            printf("注释部分缺右边的界符*/，且不能跨行\n");
        
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
            // printf("row:%d\n",row);
        }
        ch=getchar();
    }
    // 数字常数
    if(ch>='0'&& ch<='9'){
        while(ch>='0'&&ch<='9'){
            token+=ch;
            ch = getchar();
            flag=false;
        }
        if(judgeBlank()){
            printBi(37);
            solveBlank();
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||isRop()||ch==';'){
            printBi(37);
        }
        else printBi(-1);
    }
    // 单界符
    else if(ch=='*'||ch=='.'||ch==':'||ch=='>'){
        solveBi();
    }
    // 双界符
    else if(ch=='('||ch==')'||ch=='+'||ch==','||ch=='-'||ch==';'||ch=='='||ch=='['||ch==']')
    {
        printBi(SiDic[ch]);
    }
    // 可能的annotation
    else if(ch=='/'){
        ch = getchar();
        if(ch=='*'){
            int isEnd=0;
            while(ch!='\n'&&isEnd!=2){
                ch=getchar();
                if(ch=='*'&&!isEnd) isEnd=1;
                else if(isEnd==1&&ch!='/') isEnd=0;
                else if(isEnd==1&&ch=='/') isEnd=2;
            }
            if(ch=='\n'){
                solveBlank();
                printBi(-3);
            }
        }
        else{
            flag=false;
            printBi(48);
        } 
        
    }
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
    // 字符串常数
    else if(ch=='\''){
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
    // identifier or keyword
    else if(isalpha(ch)){
        token=ch;
        ch = getchar();
        while(isalpha(ch)||(ch>='0'&&ch<='9')){
            token+=ch;
            ch = getchar();
        }
        int t=-1;
        flag=false;
        if(t = isKeyWord()){
            printBi(t);
        }
        else if(judgeBlank()){   
            printBi(36);
            solveBlank();
        }
        else{
            printBi(36);
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