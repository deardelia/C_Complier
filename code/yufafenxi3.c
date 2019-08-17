
#include<stdio.h>
#include<string.h>
#include "yufafenxi3.h"

char WORD[10000][500];
char WORD_tag[10000][10];
int column[10000];
int word_number;
int intNum;//由字符串转为数字的整型
int count;//分析计数，记录当前分析到哪个单词
int tablecount=1;//符号表内元素的个数
//int levelvarcount[MAXLEV];
int instructnum=0;//指令数
//int errorplace[MAXERROR];//记录出错所在的行数
//int errorecord[MAXERROR];//记录错误
int currentlev=1;
int errorcount=0;
int funcret=1; //returnfunc:1,  voidfunc:1,
int typeofexp1=11, typeofexp2=12,typeofexp3=13;
int lie=0;
int hang=0;
int funcnum=0;
int ismain = 0;
int midcode_num=0;
int midcode_num2=0;

int tmi;
int mi = 0;    //四元式处理的行数
int paran = 0;
int factclass = 0;
FILE *fp3;
int varreg[ 200 ];
int factor_call=0;
int errnum = 0;
int signal=-1;
int callisfactor=-1;
all_lie=0;
int flag=0;
//symboltable Charbox[MAXTABLE];			//符号表
//mid_opera  operation[MAXOP];

int token(char *fname,char wordTag[][10],char wordRecord[][500]);



int token(char *fname,char wordTag[][10],char wordRecord[][500])//ok
{
    char key[50][30];//文法关键字数组
    strcpy(&(key[0][0]), "const");
    strcpy(&(key[1][0]), "int");
    strcpy(&(key[2][0]), "char");
    strcpy(&(key[3][0]), "void");
    strcpy(&(key[4][0]), "main");
    strcpy(&(key[5][0]), "if");
    strcpy(&(key[6][0]), "then");
    strcpy(&(key[7][0]), "else");
    strcpy(&(key[8][0]), "do");
    strcpy(&(key[9][0]), "while");
	strcpy(&(key[10][0]), "switch");
	strcpy(&(key[11][0]), "case");
    strcpy(&(key[12][0]), "scanf");
    strcpy(&(key[13][0]), "printf");
    strcpy(&(key[14][0]), "return");

    char keyTag[50][30];//存放文法中关键字的类别码
    strcpy(&(keyTag[0][0]), "CONSTTK");
    strcpy(&(keyTag[1][0]), "INTTK");
    strcpy(&(keyTag[2][0]), "CHARTK");
    strcpy(&(keyTag[3][0]), "VOIDTK");
    strcpy(&(keyTag[4][0]), "MAINTK");
    strcpy(&(keyTag[5][0]), "IFTK");
    strcpy(&(keyTag[6][0]), "THENTK");
    strcpy(&(keyTag[7][0]), "ELSETK");
    strcpy(&(keyTag[8][0]), "DOTK");
    strcpy(&(keyTag[9][0]), "WHILETK");
	strcpy(&(keyTag[10][0]), "SWITCHTK");
	strcpy(&(keyTag[11][0]), "CASETK");
    strcpy(&(keyTag[12][0]), "SCANFTK");
    strcpy(&(keyTag[13][0]), "PRINTFTK");
    strcpy(&(keyTag[14][0]), "RETURNTK");

    //打开文件
    FILE *fp;
    char ch;
    char temp[200];//存放完整的单词
    char buffer[20000];//文件缓冲区
    int num,k,j,i=0;//num为存入的词法分析的计数变量,i记录整个文件，j记录当前单词的第几个字符
	int n,m;
    int ii,jj,kk,ll,mm,nn;//分循环判断实型、整型 用
    int linenum=1;//行号初始值为1

    mistake=0;
    num=1;
    if((fp=fopen(fname,"r"))==NULL)
    {
        printf("Error! File not exist!\n");
        scanf("%c",&temp[0]);

    }

    //将文件读到buffer中
    ch = fgetc(fp);
    while(ch!=EOF)
    {
        buffer[i++]=ch;
        ch = fgetc(fp);
    }
    buffer[i]='\0';

    n=i;
    i=0;
    while(i<n)//逐字分析
    {
        //空格 换行 制表符则继续读进下一个
        if( (buffer[i]==' ')||(buffer[i]=='\t')||(buffer[i]=='\n')  )
        {
            if(buffer[i]=='\n')
            {
				linenum++;
            }
            i++;
            continue;
        }
        j=0;

        //关键字或者标识符
        if( ( (buffer[i]>='a')&&(buffer[i]<='z') )||( (buffer[i]>='A')&&(buffer[i]<='Z') ) || (buffer[i]=='_') )
        {

            temp[j]=tolower(buffer[i]);
            i++;j++;
            while( ((buffer[i]>='a')&&(buffer[i]<='z') )||( (buffer[i]>='A')&&(buffer[i]<='Z') )||( (buffer[i]>='0')&&(buffer[i]<='9') ) || (buffer[i]=='_') )
            {
                temp[j]=tolower(buffer[i]);
                i++;j++;

            }
            temp[j]='\0';

            for(k=0;k<15;k++)//判断是否为15个关键字中的
            {
                if(strcmp(temp,key[k])==0)
                {
                    column[num]=linenum;
                    strcpy(&wordTag[num][0],&keyTag[k][0]);
                    strcpy(&wordRecord[num][0],&temp[0]);
                    num++;
                    break;
                }
            }

            if(k==15)//如果不是关键字，就是标识符
            {
                column[num]=linenum;//column为当前词所在行的记录
                strcpy(&wordTag[num][0],"IDEN");
                strcpy(&wordRecord[num][0],&temp[0]);
                num++;
            }
        }

        //是整型常量
        else if(( (buffer[i]>='0')&&(buffer[i]<='9') ) )
        {
            ii=ll=i;
            mm=0;
            temp[mm]=buffer[i];
            i++;
            mm++;
            while(( (buffer[i]>='0')&&(buffer[i]<='9') ))
            {
                temp[mm]=buffer[i];
                i++;mm++;
            }

            temp[mm]='\0';
            jj=0;
            intNum=0;
            nn=i-ii;
			for (nn=strlen(temp)-1;nn>0;nn--,ii++){
				kk = buffer[ii] - '0';
				intNum = intNum+((int)pow(10,nn)*kk);
			}

            column[num]=linenum;
            strcpy(&wordTag[num][0],"INTCON");
            strcpy(&wordRecord[num][0],&temp[0]);
            num++;


        }
        //字符常量
        else if( (buffer[i]=='\'') )
        {
			if(buffer[i+1] == '+' || buffer[i+1] == '-' || buffer[i+1] == '*' || buffer[i+1] == '/' || buffer[i+1] == '_' || isalnum(buffer[i+1] )){
				temp[0]=buffer[i+1];
				temp[1]='\0';
				column[num]=linenum;
				strcpy(&wordTag[num][0],"CHARCON");
				strcpy(&wordRecord[num][0],&temp[0]);
				num++;
			}
			else{
				temp[0]=buffer[i+1];
				temp[1]='\0';
				column[num]=linenum;
				strcpy(&wordTag[num][0],"CHARCON");
				strcpy(&wordRecord[num][0],&temp[0]);
				num++;
				error("null",linenum,37);
			}
			if((buffer[i+2]=='\'') ){
				i=i+3;
			}
			else{
				i=i+2;
				error("null",linenum,38);
			}


        }

        //字符串分析
        else if(buffer[i]=='"')
        {
            ii=i;
            i++;j=0;kk=0;
			while((buffer[i]!='"')&&(buffer[i]!='\0'))
            {
  //  printf("%c,%d %d\n",buffer[i],i,buffer[i]!='\0');
                i++;
                kk++;
            }

            /*if(buffer[i]=='\0')//到文档末尾了，视为不是字符串是DQMARK
            {
                i=i-kk;
                temp[0]='"';
                temp[1]='\0';
                column[num]=linenum;
                strcpy(&wordTag[num][0],"DQMARK");
                strcpy(&wordRecord[num][0],&temp[0]);
                num++;
            }*/
   // printf("strcpy&&&&&\n");
            if(buffer[i]!='\0')//是字符串
            {
				for(ii++;ii<i;ii++,j++){

					temp[j]=buffer[ii];
    //printf("%c,%d %d\n",temp[j],ii,buffer[ii]!='\0');
				}
				temp[j]='\0';
   // printf("%s\n",temp);
				column[num]=linenum;
				strcpy(&wordTag[num][0],"STRCON");
				strcpy(&wordRecord[num][0],&temp[0]);
   // printf("2:%s   %s\n",&temp[0],&wordRecord[num][0]);
				num++;i=i+1;
            }
            /*else if((kk==29)&&(buffer[i]!='\0'))//不是字符串是DQMARK
            {
                i=i-29;
                temp[0]='"';
                temp[1]='\0';
                column[num]=linenum;
                strcpy(&wordTag[num][0],"DQMARK");
                strcpy(&wordRecord[num][0],&temp[0]);
                num++;
            }*/
        }

		//是比较符或运算符或其他单符号
        else if((buffer[i]=='<')&&(buffer[i+1]!='='))
        {
            i++;temp[0]='<';temp[1]='\0';
            column[num]=linenum;
			strcpy(&wordTag[num][0],"LSS");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if((buffer[i]=='>')&&(buffer[i+1]!='='))
        {
            i++;temp[0]='>';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"GRE");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if((buffer[i]=='<')&&(buffer[i+1]=='='))
        {
            i=i+2;temp[0]='<';temp[1]='=';temp[2]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"LEQ");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
         else if((buffer[i]=='>')&&(buffer[i+1]=='='))
        {
            i=i+2;temp[0]='>';temp[1]='=';temp[2]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"GEQ");strcpy(&wordRecord[num][0],&temp[0]);num++;
        }
         else if((buffer[i]=='=')&&(buffer[i+1]=='='))
        {
            i=i+2;temp[0]='=';temp[1]='=';temp[2]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"EQL");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if((buffer[i]=='!')&&(buffer[i+1]=='='))
        {
            i=i+2;temp[0]='!';temp[1]='=';temp[2]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"NEQ");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if((buffer[i]=='='))
        {
             i++;temp[0]='=';temp[1]='\0';
             column[num]=linenum;
            strcpy(&wordTag[num][0],"ASSIGN");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='+')
        {
            i++;temp[0]='+';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"PLUS");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='-')
        {
            i++;temp[0]='-';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"MINU");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='*')
        {
            i++;temp[0]='*';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"MULT");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='/')
        {
            i++;temp[0]='/';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"DIV");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]==';')
        {
            i++;temp[0]=';';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"SEMCON");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]==',')
        {
            i++;temp[0]=',';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"COMMA");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='.')
        {
            i++;temp[0]='.';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"PERIOD");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]==':')
        {
            i++;temp[0]=':';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"COLON");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        /*else if(buffer[i]=='\'')
        {
            i++;temp[0]='\'';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"QMARK");strcpy(&wordRecord[num][0],&temp[0]);num++;
        }*/
        else if(buffer[i]=='(')
        {
            i++;temp[0]='(';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"LPARENT");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]==')')
        {
            i++;temp[0]=')';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"RPARENT");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='[')
        {
            i++;temp[0]='[';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"LBRACK");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]==']')
        {
            i++;temp[0]=']';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"RBRACK");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='{')
        {
            i++;temp[0]='{';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"LBRACE");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else if(buffer[i]=='}')
        {
            i++;temp[0]='}';temp[1]='\0';
            column[num]=linenum;
            strcpy(&wordTag[num][0],"RBRACE");
			strcpy(&wordRecord[num][0],&temp[0]);
			num++;
        }
        else
        {
            error("null",linenum,37);
            return 0;
        }
    }

    return num;

}
void cifanalys()//ok
{
    int flag,record;

    count=1;

    //常量声明，是const即开始调用常量申明，常量分析
    if(!(strcmp(WORD_tag[count],"CONSTTK")))
    {
	//printf("aaaa\n");
        flag = constdecl();
	//printf("flag=%d\n",flag);
        if(flag==0){
            //printf("constdecl end and success!\n");
            //printf("continue...\n");
        }
        else{
            printf("error! constdecl error!\n");
        }
    }

    //变量分析以及带返回值的函数,(若是int或char开头，要么是变量声明定义，要么是函数的定义)
    while((!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))))
    {   //若是int、char则读取下一个词
        if(!(strcmp(WORD_tag[count],"INTTK"))){
            record= 11;
        }
        else{
            record= 12;
        }
        count=count+1;
        //是标识符，进行下一步
        if(!(strcmp(WORD_tag[count],"IDEN"))){
            count=count+1;
            //若不是,;[,则出错(左括号代表函数)
            if( (strcmp(WORD_tag[count],"COMMA"))
               &&(strcmp(WORD_tag[count],"SEMCON"))
               &&(strcmp(WORD_tag[count],"LPARENT"))
               &&(strcmp(WORD_tag[count],"LBRACK")))
            {
                printf("error:vardecl!\n");
				signal=3;//跳到下一个分号或者逗号
                error(WORD[count],column[count],1);
            }
            //若是,;[读进一个是：变量定义
            if((!strcmp(WORD_tag[count],"COMMA"))
               ||(!strcmp(WORD_tag[count],"SEMCON"))
               ||(!strcmp(WORD_tag[count],"LBRACK")))
            {
                count=count+1;
                //调用变量分析程序
				//printf("%s",WORD[count]);
                if(vardef(record)){
                    printf("error:vardef!\n");
                }
                else{
                    if(!(strcmp(WORD_tag[count],"LPARENT"))){
                        count=count-2;
                    }
                    //printf("vardef success!\n");//此时count为；后面的一个
                    //printf("%s\n",WORD_tag[count]);
                }
            }
            else if(!(strcmp(WORD_tag[count],"LPARENT"))){
                count=count-2;
                //printf("iden is return func\n");
				break;
            }
        }
        else{
			signal=0;
            error(WORD[count],column[count],6);//跳到下一个int、char或void
        }

    }

    //是void则为无返回值函数的定义
    while((!(strcmp(WORD_tag[count],"VOIDTK")) ||(!(strcmp(WORD_tag[count],"INTTK"))) ||(!(strcmp(WORD_tag[count],"CHARTK"))))&&(strcmp(WORD_tag[count+1],"MAINTK"))){
        if(!(strcmp(WORD_tag[count],"VOIDTK"))){
           //printf("begin voidfunc!!\n");
            count++;
            if(!(strcmp(WORD_tag[count],"IDEN"))){
                count++;
                voidfunc();
            }
        }
        else if((!(strcmp(WORD_tag[count],"INTTK"))) ||(!(strcmp(WORD_tag[count],"CHARTK")))){
            if(!(strcmp(WORD_tag[count],"INTTK")))
				record=11;
			else
				record=12;
			count++;
            if(!(strcmp(WORD_tag[count],"IDEN"))){
                count++;
                returnfunc(record);
            }
			/*else{
				signal=0;//找到下一个void char 或int的地方
				error(WORD[count],column[count],6);
			}*/
        }

    }
    mainfunc();
    //printf("this is end of cifafenxi!!\n");

}

int constdecl()//ok正确返回0...
{
    //printf("This is a const declaration！\n");
    int typerecord;
    //如果const后是int char
    while(!(strcmp(WORD_tag[count],"CONSTTK")))
    {
        count=count+1;
        if(!(strcmp(WORD_tag[count],"INTTK")))
        {
            typerecord=11;
			count=count+1;
        }
        else if((!(strcmp(WORD_tag[count],"CHARTK"))))
        {
            typerecord=12;
			count=count+1;
        }
		else{
			signal=0;
			error(WORD[count],column[count],10);//找到下一个是const int char void或指示语句的符号
			return 1;
		}
        //调用常量分析并成功返回(返回0)
        if(!constdef(typerecord))
        {
//printf("const def end!\n");
//printf("%s %d\n",WORD_tag[count],strcmp(WORD_tag[count],"SEMCON"));
            if(!(strcmp(WORD_tag[count],"SEMCON")))
            {
                count=count+1;
				continue;
            }


        }
        else{
			signal=0;
            error(WORD[count],column[count],1);//找到下一个int char void 或其他可能是语句开头的类型
            if(!(strcmp(WORD_tag[count],"CONSTTK")))
					continue;
			else
					return 1;
        }

    }
	return 0;
}


int constdef(int type)//ok...
{
    //printf("This is a const define！\n");
    PMean pm=(PMean)malloc(sizeof(Mean));//PMean代表符号表结果指针
	char s[20];
    strcpy(pm->name,WORD[count]);
    if(!(strcmp(WORD_tag[count],"IDEN")))
    {
        count=count+1;
        pm->kind=4;//符号表内记录下类型为4
        if(!(strcmp(WORD_tag[count],"ASSIGN")))
        {
            count=count+1;
            //如果直接是整数或者字符
            if(((!(strcmp(WORD_tag[count],"INTCON")))&&(type==11))//通过参数type判断=左右类型是否匹配
            || ((!(strcmp(WORD_tag[count],"CHARCON")))&&(type==12)))
            {
                if((!(strcmp(WORD_tag[count],"INTCON"))) )
                    type = 11;
                else
                    type=12;

                count=count+1;
                if(type==11){
                    pm->number=transint(WORD[count-1]);
                    pm->type=11;
					generate("const","int",WORD[count-1],pm->name);
                }
                else{
                    pm->cischar=WORD[count-1][0];
                    pm->type=12;
					sprintf(s,"%d",(int)WORD[count-1][0]);
					generate("const","char",s,pm->name);
                }
                insert(pm);
                //此时count所代表的应该为逗号或分号，若是逗号，则再调用变量定义函数
                if(!(strcmp(WORD_tag[count],"COMMA")))
                {
                    count=count+1;
                    return(constdef(type));
                }
                else if(!(strcmp(WORD_tag[count],"SEMCON")))
                    return 0;
            }
            //若跟在==后面的是符号，所以判断count+1是否为整数或
            else if(((!(strcmp(WORD_tag[count+1],"INTCON")))&&(type==11))
                && ((!(strcmp(WORD_tag[count],"MINU")))
                ||  (!(strcmp(WORD_tag[count],"PLUS")))))
            {

                type = 11;
                //读取字符，此时count指向的应为逗号或分号
                count=count+2;
                if((!(strcmp(WORD_tag[count-2],"PLUS"))) )
                {
                    pm->type=11;
                    pm->number=transint(WORD[count-1]);
					generate("const","int",WORD[count-1],pm->name);
                    insert(pm);
                }
                else if( (!(strcmp(WORD_tag[count-2],"MINU"))) )
                {

                    pm->type=11;
                    pm->number=-transint(WORD[count-1]);
					sprintf(s, "%d", pm->number);
					generate("const","int",s,pm->name);
                    insert(pm);
                }
                if(!(strcmp(WORD_tag[count],"COMMA")))
                {
                    count=count+1;
                    return(constdef(type));
                }
                else if(!(strcmp(WORD_tag[count],"SEMCON")))
                    return 0;
            }
            //否则"变量的类型和值的类型不匹配",
            else
            {
                error(WORD[count],column[count],20);
                return 1;
            }
        }
        //否则表示符后面缺少=
        else
        {
            error(WORD[count],column[count],20);
            return 1;
        }
    }
    //否则缺少表示符
    else
    {
        error(WORD[count],column[count],39);
        return 1;
    }
    return 0;
}

int vardef(int type){//ok  数组变量定义的填表问题...
    //printf("This is a var define！\n");
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
	char s[20];
    //若之前是逗号或分号
//printf("%s",WORD[count]);
    if((!(strcmp(WORD_tag[count-1],"COMMA")))||(!(strcmp(WORD_tag[count-1],"SEMCON")))){
        //将逗号或分号之前的变量填入符号表

        strcpy(pm->name,WORD[count-2]);
        pm->kind=0;
        pm->type=type;
        insert(pm);
		if(pm->type==11)
			generate("int","  ","  ",pm->name);
		else if(pm->type==12)
			generate("char","  ","  ",pm->name);
    }
    //若之前是左中括号，代表数组
    else if(!(strcmp(WORD_tag[count-1],"LBRACK"))){
        //若括号中为无符号整数且下一个是右中括号，则填符号表
        if( (!(strcmp(WORD_tag[count],"INTCON")))&&(!(strcmp(WORD_tag[count+1],"RBRACK"))) ){

            strcpy(pm->name,WORD[count-2]);
            pm->kind=3;
            pm->number=transint(WORD[count]);
	//printf("%s\n",pm->xiabiao)
            pm->type=type;
            //printf("dssfff\n");
            insert(pm);
        //printf("dssfff\n");
			sprintf(s,"%d",pm->number);
			if(pm->type==11)
				generate("inta","  ",s,pm->name);
			else if(pm->type==12)
				generate("chara","  ",s,pm->name);

            count=count+3;
        }
        //否则数组定义出错
        else{
            error(WORD[count],column[count],28);//跳到下一个int void char，或者语句开头的地方(标识符开头的语句除外)
            return 1;
        }
    }

    //若是逗号
    if( (!(strcmp(WORD_tag[count-1],"COMMA")))){
        //若逗号之后是标识符
       // printf("%s\n",WORD_tag[count-1]);
        if((!(strcmp(WORD_tag[count],"IDEN")))){
            count=count+2;
            return (vardef(type));
        }
        //逗号之后不是标识符则出错
        else{
			signal=2;
            error(WORD[count],column[count],6);
			return 1;
        }
    }
    //若是分号
    if( (!(strcmp(WORD_tag[count-1],"SEMCON"))) ){
        //分号过后是int或char，则代表新的变量声明开始了
        if((!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))) ){
            if(!(strcmp(WORD_tag[count],"INTTK"))){
                record=11;
            }
            else
                record=12;
            count=count+1;
            //若int或char后面是标识符
            if(!(strcmp(WORD_tag[count],"IDEN"))){
                count=count+1;
                if( (strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK")) &&(strcmp(WORD_tag[count],"LPARENT"))){
                    signal=1;//跳到下一个逗号或者括号
					error(WORD[count],column[count],1);
                    return 1;
                }
                if(!(strcmp(WORD_tag[count],"LPARENT"))){
                    return 0;
                }
                //若是标识符后面是逗号分号或左中括号，则调用变量分析函数
                if( (!(strcmp(WORD_tag[count],"COMMA")))||(!(strcmp(WORD_tag[count],"SEMCON")))||(!(strcmp(WORD_tag[count],"LBRACK"))) ){//如果是逗号或者分号或者左中括号
                    count++;
                    if(vardef(record))
                        return 1;//vardefine出错的话 return 1
                }
            }
            //int或char后面不是标识符则报错
            else{
				signal = 2;
                error(WORD[count],column[count],6);
				return 1;
            }
        }
        //分号后面不是int或char则代表上一轮的变量声明已经结束
        else
            return 0;
    }
    //不是左中括号逗号或分号则报错
    else{
		return 1;
    }
    return 0;
}

int funcpara(PMean pm0){//ok 函数的参数表...
   //printf("This is a parameterlist of function！\n");
    int num=0;
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        return num;
    }
    while((!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK")))){
        if(!(strcmp(WORD_tag[count],"INTTK"))){
            record=11;
        }
        else
            record=12;
        count=count+1;
        if(!(strcmp(WORD_tag[count],"IDEN"))){
            count=count+1;
            //函数声明的形式变量填入符号表
            /*if(enterTable(currentlev+1,record,3,count-1,true)){
                return 1;
            }*/
            pm->kind=5;
            pm->type=record;
            strcpy(pm->name,WORD[count-1]);
			if(record==11)
				generate("para","int", "  ", pm->name);
			else if(record==12)
				generate("para","char", "  ", pm->name);
			pm0->funcparaType[num]=record;
            insert(pm);
            num++;
        }
        else{
			signal=1;//找到下一个逗号或者括号(左右均可)
            error(WORD[count],column[count],6);
			if(!(strcmp(WORD_tag[count],"COMMA"))){
				count=count+1;
				continue;
			}
			else
				return num;//
        }
        //若标识符后不是逗号，则退出循环，代表函数声明形式变量定义结束
        if(strcmp(WORD_tag[count],"COMMA")){
            break;
        }
        //若是逗号则接着往下分析
        else
            count=count+1;
        //若不是int或char则出错

    }
    return num;

}


void returnfunc(int type){//ok...
//printf("This is a return fucntion！\n");
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
	PMean pm0=(PMean)malloc(sizeof(Mean));

    already_ret=0;
	if(type==11)
		generate("declare","int","  ",WORD[count-1]);//声明子函数WORD[count-2]:代表函数名称
	else if(type==12)
		generate("declare","char","  ",WORD[count-1]);

    if(!(strcmp(WORD_tag[count],"LPARENT")))
        count++;
    else{
		signal=0;//跳到下一个类型声明符号int/char/void
        error(WORD[count],column[count],13);
		return;//这样return过后相当于跳过这个函数的声明
	}

    //填符号表
    pm->kind=2;//2代表int/var型的有返回值函数等同于 .type=11
    pm->type=type;

    strcpy(pm->name,WORD[count-2]);

    setCurFunc(pm);//改变当前所在层数即hang++!!，且把lie设为1已经进入新的一层
	setAttribute(pm0,pm);
	pm->number=funcpara(pm);//参数表分析
//printf("funcparaType:%d",pm->funcparaType[0]);
    insert_all(pm);//新建子函数符号表（在0层操作）


    //如果是右括号则括号配对，接上面的参数表分析
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count=count+1;
        //若是{
        if(!(strcmp(WORD_tag[count],"LBRACE"))){
            count=count+1;
            //开始子程序的变量分析
            if(!(strcmp(WORD_tag[count],"CONSTTK"))){
                if(constdecl()){
                    printf("error!!!:constdecl wrong!!!\n");
                }
            }
            if( (!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))) ){
                if(!(strcmp(WORD_tag[count],"INTTK")))
                    record=11;
                else
                    record=12;
                count++;
                if(!(strcmp(WORD_tag[count],"IDEN"))){//!!!!!这里的INDEN很重要
                    count++;
                    if((strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK"))){
                        signal=4;//跳到char int void的地方
						error(WORD[count],column[count],1);
						return;
                    }
                    if( (!(strcmp(WORD_tag[count],"COMMA")))||(!(strcmp(WORD_tag[count],"SEMCON")))||(!(strcmp(WORD_tag[count],"LBRACK"))) ){
                        count++;
                        if(vardef(record)){
                            printf("error!!!:vardef wrong!!!\n");
                        }
						/*else{
							if(!(strcmp(WORD_tag[count],"LPARENT")))
								error(WORD[count],column[count],31);//不允许在子函数中定义函数
						}*/
                    }
                }
                else{
					signal=0;//跳到char int void的地方
                    error(WORD[count],column[count],6);
					return;
                }
            }
            //进入复合语句这是必须的！
            statementList(pm);//进入语句列分析函数
            if(already_ret==0){ //语句列中如遇到return函数则alread_ret会从0变为1，否则又返回值的函数缺少返回语句
                signal=0;
				error(WORD[count],column[count],26);//跳到char int void的地方
				return;
			}
        }
        else{//缺少{errclass = ICV;
			signal=0;
            error(WORD[count],column[count],11);
			return;
        }

        if(!(strcmp(WORD_tag[count],"RBRACE")))//表示当前的函数定义结束
            count++;
        else//否则缺少}报错errclass = ICV;
		{
			signal = 0;
			error(WORD[count],column[count],12);
			return;
		}


    }
    else{//否则函数声明的时候缺少右括号报错
		signal=0;
	    error(WORD[count],column[count],14);
		return;
	}
    generate("endp",pm->name,"  ","  ") ;
}


void voidfunc(){//ok...
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
	PMean pm0=(PMean)malloc(sizeof(Mean));
//printf("This is void function！\n");

    already_ret=1;


	generate("declare","void","  ",WORD[count-1]);//声明子函数WORD[count-2]:代表函数名称

    if(!(strcmp(WORD_tag[count],"LPARENT"))){
        count++;
    }
    else{
		signal=0;
        error(WORD[count],column[count],13);
		return;
	}

    pm->kind=1;//1代表无返回值函数等同于 .type=12
    strcpy(pm->name,WORD[count-2]);

    setCurFunc(pm);
	setAttribute(pm0,pm);
	pm->number=funcpara(pm);//
    insert_all(pm);//新建子函数符号表


    //如果是右括号则括号配对
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count=count+1;
        //若是{
        if(!(strcmp(WORD_tag[count],"LBRACE"))){
            count=count+1;
            //currentlev++;//代表进入新的一层
            //开始子程序的变量分析
            if(!(strcmp(WORD_tag[count],"CONSTTK"))){
                if(constdecl()){
                    printf("error!!!:constdecl wrong!!!\n");
                }
            }
            if( (!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))) ){
                if(!(strcmp(WORD_tag[count],"INTTK")))
                    record=11;
                else
                    record=12;
                count++;
                if(!(strcmp(WORD_tag[count],"IDEN"))){//!!!!!这里的INDEN很重要
                    count++;
                    if((strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK"))){
                        signal=4;
						error(WORD[count],column[count],1);
						return;
                    }
                    if( (!(strcmp(WORD_tag[count],"COMMA")))||(!(strcmp(WORD_tag[count],"SEMCON")))||(!(strcmp(WORD_tag[count],"LBRACK"))) ){
                        count++;
                        if(vardef(record)){
                            printf("error!!!:vardef wrong!!!\n");
                        }
						/*else{
							if(!(strcmp(WORD_tag[count],"LPARENT")))
								error(WORD[count],column[count],31);//不允许在子函数中定义函数
						}*/
                    }
                }
                else{
					signal=0;
                    error(WORD[count],column[count],6);
					return;
                }
            }
            //进入复合语句

            statementList(pm);//进入语句列分析函数
            if(already_ret==0){ //无返回值函数不能有返回语句
				signal=0;
                error(WORD[count],column[count],26);
				return;
			}
        }
        else{
			signal=0;
            error(WORD[count],column[count],11);
			return;
        }

        if(!(strcmp(WORD_tag[count],"RBRACE")))//表示当前的函数定义结束
            count++;
        else{//否则缺少}报错
			signal=0;
            error(WORD[count],column[count],12);
			return;
		}

    }
    else{//否则函数声明的时候缺少右括号报错
		signal=0;
	    error(WORD[count],column[count],14);
		return;
	}
    generate("endp",pm->name,"  ","  ") ;

}


void mainfunc(){//ok...

//printf("this is mainfunc!\n");
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
    PMean pm0=(PMean)malloc(sizeof(Mean));

    already_ret=1;
    if((strcmp(WORD_tag[count],"VOIDTK"))){
        error(WORD[count],column[count-1]+1,2);
		return;
    }
    else
        count=count+1;
    if (strcmp(WORD_tag[count],"MAINTK")){
        error(WORD[count],column[count-1]+1,2);
        return ;
    }
    else
        count=count+1;
    generate("main","  ","  ","  ");

    pm->kind=0;
    strcpy(pm->name,"main");
	setCurFunc(pm);
	insert_all(pm);
    if(strcmp(WORD_tag[count],"LPARENT")){
		signal = 3 ;//跳到下一个逗号或者括号
        error(WORD[count],column[count],13);
	}
    else
        count=count+1;
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count=count+1;
        //若是{
        if(!(strcmp(WORD_tag[count],"LBRACE"))){
            count=count+1;
            //currentlev++;//代表进入新的一层
            //开始子程序的变量分析
            if(!(strcmp(WORD_tag[count],"CONSTTK"))){
                if(constdecl()){
                    printf("error!!!:constdecl wrong!!!\n");
                }
            }
            if( (!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))) ){
                if(!(strcmp(WORD_tag[count],"INTTK")))
                    record=11;
                else
                    record=12;
                count++;
                if(!(strcmp(WORD_tag[count],"IDEN"))){//!!!!!这里的INDEN很重要
                    count++;
                    if((strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK"))){
                        signal=3;//跳到下一个分号或逗号
						error(WORD[count],column[count],1);
                    }
                    if( (!(strcmp(WORD_tag[count],"COMMA")))||(!(strcmp(WORD_tag[count],"SEMCON")))||(!(strcmp(WORD_tag[count],"LBRACK"))) ){
                        count++;
                        if(vardef(record)){
                            printf("error!!!:vardef wrong!!!\n");
                        }
						/*else{
							if(!(strcmp(WORD_tag[count],"LPARENT")))
								error(WORD[count],column[count],31);//不允许在子函数中定义函数
						}*/
                    }
                }
                else{
					signal=3;
                    error(WORD[count],column[count],6);
                }
            }
            //进入复合语句
            /*if(gen(9,0,numoflev[currentlev]))//?????????????????????????产生一条声明指令
                return 1;*/
            statementList(pm);//进入语句列分析函数
            if(already_ret==0){ //无返回值函数不能有返回语句
				signal=1;
                error(WORD[count],column[count],26);
				return;
			}
        }
        else{
			signal=-1;
            error(WORD[count],column[count],11);
			return;
        }

        if(!(strcmp(WORD_tag[count],"RBRACE")))//表示当前的函数定义结束
            count++;
        else{//否则缺少}报错
			signal=-1;
            error(WORD[count],column[count],12);
			return;
		}

    }
    else{//否则函数声明的时候缺少右括号报错
		signal=-1;
	    error(WORD[count],column[count],14);
		return;
	}

    generate("endp","main","  ","  ");

}

void setCurFunc(PMean pm){//ok在子函数声明时使用，时hang++，即代表进入新一层

    if(hang==Max_Table_hang){//确保没有超出符号表最大层数
		error(NULL,0,4);
	    return;
	}
	lie=1;
	hang++;
//all_line?????????//见setFunc.C
	strcpy(table[hang][0].name,pm->name);//pm->name是函数的名字
    table[hang][0].kind=pm->kind;
    table[hang][0].type=pm->type;

}

int statementList(PMean pm){//ok...
    //printf("This is a statement list！\n");
    statement(pm);
    while(statement(pm));



    /*if(!(strcmp(WORD_tag[count],"SEMCON"))){
        count++;
    }
    else{
        error(WORD[count],column[count],1);
    }*/
    return 0;
}

int statement(PMean pm){//ok!!!!!注意分号...
	PMean pm2=(PMean)malloc(sizeof(Mean));//数组内的表达式

    int a;
    //printf("This is a statement！\n");
    if(!(strcmp(WORD_tag[count],"IFTK"))){
        ifstat(pm);
        return 1;
    }

    else if(!(strcmp(WORD_tag[count],"DOTK"))){
        dowhilestat(pm);
        return 1;
    }
	else if(!(strcmp(WORD_tag[count],"SEMCON"))){
        count++;
		return 1;
	}
    else if (!(strcmp(WORD_tag[count],"SCANFTK"))){
        scanfstat();
        //printf("end scanf sucess!%s\n",WORD_tag[count]);
        if((strcmp(WORD_tag[count],"SEMCON"))){
			signal=2;
            error(WORD[count],column[count],1);
		}
		else
			count++;
        return 1;
    }
    else if (!(strcmp(WORD_tag[count],"PRINTFTK"))){
        printfstat();
        if((strcmp(WORD_tag[count],"SEMCON"))){
			signal=2;
            error(WORD[count],column[count],1);
		}
		else
			count++;
        return 1;
    }

    else if (!(strcmp(WORD_tag[count],"SWITCHTK"))){
        switchcasestat(pm);
        return 1;
    }
    //是分号代表当前语句分析结束
    /*else if(!(strcmp(WORD_tag[count],"SEMCON"))){
        count++;
        return 1;
    }*/
    else if(!(strcmp(WORD_tag[count],"RETURNTK"))){
        returnstat();
        already_ret=1;
        if((strcmp(WORD_tag[count],"SEMCON"))){
			signal=2;
            error(WORD[count],column[count],1);
		}
		else
			count++;
        return 1;
    }
    else if(!(strcmp(WORD_tag[count],"IDEN"))){
        count++;
        if(!(strcmp(WORD_tag[count],"ASSIGN"))){
            assignstat();
            if(!(strcmp(WORD_tag[count],"SEMCON"))){
                count++;
            }
            else{
				signal=2;
                error(WORD[count],column[count],1);
			}
        }
        else if(!(strcmp(WORD_tag[count],"LBRACK"))){
            count++;
            assignstat();
			if(!(strcmp(WORD_tag[count],"SEMCON"))){
                count++;
            }
            else{
				signal=2;
                error(WORD[count],column[count],1);
			}
        }
        else if(!(strcmp(WORD_tag[count],"LPARENT"))){
            call(pm);
            if(!(strcmp(WORD_tag[count],"SEMCON"))){
                count++;
            }
            else{
				signal=2;
                error(WORD[count],column[count],1);
			}
        }
        else{
			signal=0;
            error(pm->name,column[count],17);
            //count=count+1;
        }

        return 1;

    }

    else if(!(strcmp(WORD_tag[count],"LBRACE"))){
        count++;
        statementList(pm);
        if (strcmp(WORD_tag[count],"RBRACE")){//若语句列分析完后不是右花括号结尾则报错
            signal=1;
			error(WORD[count],column[count],12);
			return 1;
        }
        count++;
        return 1;
    }
    else
        return 0;
}

int callpara(PMean pm1, int recordType[MAXPARANUM]) //ok //返回函数调用时实参数个数...
{
    int num=1;
    PMean pm=(PMean)malloc(sizeof(Mean));
//printf("This is a parameter of call！\n");
    if(!(strcmp(WORD_tag[count],"RPARENT")))
        return 0;//代表无实参
    expression(pm);
	if(factclass==2)
		recordType[num-1]=12;
	else
		recordType[num-1]=11;
    generate("fupa","  ","  ",pm->name);

    while(!(strcmp(WORD_tag[count],"COMMA"))){
        count=count+1;
        num++;
        expression(pm);
		if(factclass==2)
			recordType[num-1]=12;
		else
			recordType[num-1]=11;
        generate("fupa","  ","  ",pm->name);
    }

	return num;
}

void call(PMean pm){//ok结束时count为)后一个字符...
    int num=0;
	int currentrecord[MAXPARANUM];
//printf("This is call state！\n");
    count++;

    if(!(strcmp(WORD_tag[count-2],"IDEN"))){
       strcpy(pm->name,WORD[count-2]);//pm->name存储函数的名字
       if(!lookup_all(pm))  //在符号表查函数名
	   {
		   signal=0;//找到下一语句的开头
           error(WORD[count-2],column[count-2],7); //函数未定义
		   return ;
	   }
    }
    /*else{
		if(factor_call==1){
			signal=1;
			error(WORD[count],column[count],7);
		}
		else{
			signal=0;
			error(WORD[count],column[count],7);
		}

	}*/

    num=callpara(pm, currentrecord);

    if((strcmp(WORD_tag[count],"RPARENT"))){
		if(factor_call==1){
			signal=2;
			error(WORD[count],column[count],14);
			return;
		}
		else{
			signal=1;
			error(WORD[count],column[count],14);
			return;
		}
	}
    else
        count++;

    if(!checkParaNum(pm->name,num)){//检查参数个数是否正确
		if(factor_call==1){
			signal=2;
			error(WORD[count],column[count],24);
			return;
		}
		else{
			signal=1;
			error(WORD[count],column[count],24);
			return;
		}
	}
	if(!checkParaType(pm->name,num,currentrecord)){//检查参数类型是否和形参匹配
//printf("currentrecord:%d\n",currentrecord[0]);
		if(factor_call==1){
			signal=2;
			error(WORD[count],column[count],25);
			return;
		}
		else{
			signal=1;
			error(WORD[count],column[count],25);
			return;
		}
	}
	if(factor_call!=1)
		generate("call",pm->name,"  ","  ");


}

//少了一种给数组元素赋值的情况!!!!!!
void assignstat(){//ok...
    int line1,kind;
    PMean pm=(PMean)malloc(sizeof(Mean)); //表达式左的标示符
    PMean pm1=(PMean)malloc(sizeof(Mean)); //表达式
    PMean pm2=(PMean)malloc(sizeof(Mean)); //数组下标表达式

//printf("This is a assign stat！\n");
char s[20];

    if(!(strcmp(WORD_tag[count-1],"LBRACK"))){
        //printf("shuzu!\n");
        strcpy(pm->name,WORD[count-2]);
        expression(pm2);
        strcpy(s,pm2->name);
        //pm->shuzuflag=transint(WORD[count-2]);
        pm->kind=3;
        if(!(strcmp(WORD_tag[count],"RBRACK")))
            count++;
        else{
			signal=0;
            error(WORD[count-1],column[count-1],35);
			return;
		}
        if((strcmp(WORD_tag[count],"ASSIGN"))){
			signal=0;
            error(WORD[count-1],column[count-1],21);
			return;
        }

    }
    else{
   // printf("assign %s\n",WORD[count-1]);
        strcpy(pm->name,WORD[count-1]);
        pm->kind=0;
    }


    //和变量的kind一样
    line1=column[count-1];

    if(!lookup(pm)&&!lookup_all(pm)){  //检查标识符是否已经定义
		signal=0;
        error(WORD[count-1],column[count-1],9);
		return;
	}

	/*if(pm->kind==3){
		if(pm->shuzuflag>pm->number){
			error(WORD[count-1],column[count-1],33);//数组越界
		}
	}*/

	kind=lookup_kind(pm);//0:1;
	//printf("%d\n",kind);

    if((kind!=0)&&(kind!=5)&&(kind!=3))//若表达式左边的类型不是变量或者参数
     {
		 signal =0;
         error(WORD[count-1],column[count-1],19);
		 return;
     }
    count++;
//printf("assign %s\n",WORD[count]);
    expression(pm1);//考虑赋值语句的右边
    //printf("assign %s\n",WORD[count-1]);
	if(kind!=3)
		generate("=",pm1->name,"  ",pm->name);
	else
		generate("[]=",pm->name,s,pm1->name);//pm->name[s]=pm1->name
	//printf("assign end\n");
}

void ifstat(PMean pm){//ok...
    PMean pm0=(PMean)malloc(sizeof(Mean));
    PMean pm1=(PMean)malloc(sizeof(Mean)); //表达式1
    PMean pm2=(PMean)malloc(sizeof(Mean));//表达式2
    char if_label[20];
    char s[20];//???????????
//printf("This is a if state！\n");
    strcpy(if_label,new_label());//生成一个标签(表示跳转

    if(!(strcmp(WORD_tag[++count],"LPARENT"))){
        count++;
        expression(pm1);
        if((!(strcmp(WORD_tag[count],"GRE")))||(!(strcmp(WORD_tag[count],"GEQ")))||
            (!(strcmp(WORD_tag[count],"LSS")))||(!(strcmp(WORD_tag[count],"LEQ")))||
            (!(strcmp(WORD_tag[count],"EQL")))||(!(strcmp(WORD_tag[count],"NEQ")))){
                strcpy(s,WORD_tag[count]);
                count++;
                expression(pm2);
                if(strcmp(WORD_tag[count],"RPARENT")){
					signal =1;
                    error(WORD[count],column[count],14);
					return;
                }
                count=count+1;

                if((!(strcmp(s,"GRE"))))
                    generate(">",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"LSS"))))
                    generate("<",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"EQL"))))
                    generate("==",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"GEQ"))))
                    generate(">=",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"LEQ"))))
                    generate("<=",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"NEQ"))))
                    generate("!=",pm1->name,pm2->name,"  ");
        }
        else if(!(strcmp(WORD_tag[count],"ASSIGN"))){
			signal=0;
            error(WORD[count],column[count],21);
            return;
        }

        else{//只有表达式的情况
            if(strcmp(WORD_tag[count],"RPARENT")){
				signal = 1;
                error(WORD[count],column[count],14);
				return;
            }
            count=count+1;
            generate("!=",pm1->name,"0","  ");
        }
		generate("jne", "  ", "  ", if_label);  //比较，为假的时候跳转
        statement(pm);
		generate("lab:", "  ", "  ", if_label);
    }
}


void dowhilestat(){//ok mistake???????...
    PMean pm0=(PMean)malloc(sizeof(Mean));
    PMean pm1=(PMean)malloc(sizeof(Mean)); //表达式1
    PMean pm2=(PMean)malloc(sizeof(Mean));//表达式2
    char label_1[20];
    char label_2[20];
    char s[20];
//printf("This is a dowhile stat！\n");
    strcpy(label_1,new_label());
    strcpy(label_2,new_label());
//printf("%s\n",WORD_tag[count]);

	generate("lab:","  ","  ",label_1);//在do的地方设置一个跳转的标签

    count++;

    statement(pm0);//do之后直接进入语句
//printf("%s\n",WORD_tag[count]);

    if(!(strcmp(WORD_tag[count++],"WHILETK"))){
        if(!(strcmp(WORD_tag[count],"LPARENT"))){
            count++;
            expression(pm1);

            if((!(strcmp(WORD_tag[count],"GRE")))||(!(strcmp(WORD_tag[count],"GEQ")))||
            (!(strcmp(WORD_tag[count],"LSS")))||(!(strcmp(WORD_tag[count],"LEQ")))||
            (!(strcmp(WORD_tag[count],"EQL")))||(!(strcmp(WORD_tag[count],"NEQ")))){
                strcpy(s,WORD_tag[count]);
                //printf("%s\n",WORD_tag[count]);
                count=count+1;
                expression(pm2);

                if((!(strcmp(s,"GRE"))))
                    generate(">",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"LSS"))))
                    generate("<",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"EQL"))))
                    generate("==",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"GEQ"))))
                    generate(">=",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"LEQ"))))
                    generate("<=",pm1->name,pm2->name,"  ");
                else if((!(strcmp(s,"NEQ"))))
                    generate("!=",pm1->name,pm2->name,"  ");

                //generate(label_2,NULL,NULL,NULL);
                if(mistake==0)//!!!!!!!!!!!!!!!!!!!!mistake的定义
                    count=count;//generate("goto",NULL,NULL,label_1);
            }
            else if(!(strcmp(WORD_tag[count],"ASSIGN"))){
				signal=0;
                error(WORD[count],column[count],21);
                return;
            }

            else{
                //count=count;
				generate("!=",pm1->name,"0","  ");
                //generate(label_2,NULL,NULL,NULL);
            }
			generate("jne", "  ", "  ", label_2);
			generate("jmp", "  ", "  ", label_1);
			generate("lab:", "  ", "  ", label_2);
            //printf("dowhile%s\n",WORD_tag[count]);
            if(strcmp(WORD_tag[count],"RPARENT")){
					signal=1;
                    error(WORD[count],column[count],14);
					return;
            }
            else
                count++;
        }
    }
}


void switchcasestat(){//ok...
//printf("This is switchcase stat！\n");
    PMean pm=(PMean)malloc(sizeof(Mean));
    PMean pm0=(PMean)malloc(sizeof(Mean));
    PMean pm1=(PMean)malloc(sizeof(Mean));
    PMean pm2=(PMean)malloc(sizeof(Mean));
    PMean pm3=(PMean)malloc(sizeof(Mean));
	char label_1[20],label_2[20],label_3[20];
    count++;

    strcpy(label_1,new_label());
	strcpy(label_3,new_label());


    if(!(strcmp(WORD_tag[count],"LPARENT"))){
        count++;
        expression(pm0);
	//printf("return expression\n");
    }
    else{
		signal=1;
        error(WORD[count],column[count],13);
		return;
	}

    setAttribute(pm,pm0);//表达式的值存在pm里
//printf("return expression\n");
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count++;
    }
    else{
		signal=1;
        error(WORD[count],column[count],14);
		return;
	}
    if(!(strcmp(WORD_tag[count],"LBRACE"))){
        count++;
    }
    else{
		signal=1;
        error(WORD[count],column[count],11);
		return;
	}

    while(!(strcmp(WORD_tag[count],"CASETK"))){
		generate("lab:", "  ", "  ", label_1);
        count++;
        if((!(strcmp(WORD_tag[count],"INTCON")))||(!(strcmp(WORD_tag[count],"CHARCON")))||(!(strcmp(WORD_tag[count],"MINU")))||(!(strcmp(WORD_tag[count],"PLUS")))){
            if(!(strcmp(WORD_tag[count],"MINU"))){
                count++;
                pm1->name[0]='-';
                sprintf(pm1->name,"%d",-1*transint(WORD[count]));
//printf("#############################################\n");
            }
            else{
                if(!(strcmp(WORD_tag[count],"PLUS")))
                    count++;
				if(!(strcmp(WORD_tag[count],"CHARCON")))
					sprintf(pm1->name,"%d",(int)(WORD[count][0]));
				else
					sprintf(pm1->name,"%d",transint(WORD[count]));
            }
            setAttribute(pm2,pm1);
			strcpy(label_1,new_label());
			strcpy(label_2,new_label());
			generate("==",pm->name,pm2->name,"  ");
			generate("jne","  ","  ",label_1);
			generate("jmp","  ","  ",label_2);
			generate("lab:","  ","  ",label_2);


            count++;
            if(!(strcmp(WORD_tag[count],"COLON"))){
                count++;
                statement(pm3);
				generate("jmp","  ","  ",label_3);
                //emit("jmp","  ","  ",label3);
            }
        }
        else{
			signal=0;
			error(WORD[count],column[count],32);
			return;
        }
    }

    if(!(strcmp(WORD_tag[count],"RBRACE"))){
        count++;
       /* emit("setlab","  ","  ",label1);
        emit("setlab","  ","  ",label3);*/
    }
	else{
		signal=1;
		error(WORD[count],column[count],12);
		return;
	}
	generate("lab:","  ","  ",label_3);
	generate("lab:","  ","  ",label_1);


}


void scanfstat(){//ok...  注意这里没有判断最后是否为；结尾
    PMean pm=(PMean)malloc(sizeof(Mean));
    int kind;
    int done=0;
//("This is scanf stat！\n");
    count=count+1;
    if(!(strcmp(WORD_tag[count],"LPARENT"))){
        count=count+1;

        if(!(strcmp(WORD_tag[count],"IDEN"))){
            strcpy(pm->name,WORD[count]);
            if(!lookup(pm)&&!lookup_all(pm)){// 检查是否在符号表， 不在报错
                signal=0;
				error(WORD[count],column[count],9);
				return;
            }

            kind=lookup_kind(pm);
            if(kind==4||kind==1||kind==2||kind==6||kind==3)//标识符类型可以是参数或者变量即为0或5
			{
				signal=0;
				error(WORD[count],column[count],23);
				return;
			}
//printf("scanf : %s\n",WORD[count]);
            generate("scanf","  ","  ",WORD[count]);
            if(!(strcmp(WORD_tag[count+1],"COMMA"))){
                scanfstat();
                //printf("%s",WORD_tag[count]);
                if(strcmp(WORD_tag[count],"RPARENT")&&strcmp(WORD_tag[count],"SEMCON")){
                    signal=1;
					error(WORD[count],column[count],14);
					return;
                }
                else{
					if(!(strcmp(WORD_tag[count],"SEMCON")))
						return;
					else{
						count=count+1;
						return;
					}

                }
            }

            if(strcmp(WORD_tag[++count],"RPARENT")){
				signal=1;
                error(WORD[count],column[count],14);
				return;
            }
            else{
                count=count+1;
                return;
            }
        }
        else{
			signal=3;
            error(WORD[count],column[count],6);
			return;
		}

    }
    else if(!(strcmp(WORD_tag[count],"COMMA"))){
        count=count+1;
        if(!(strcmp(WORD_tag[count],"IDEN"))){
            strcpy(pm->name,WORD[count]);
            if(!lookup(pm)&&!lookup_all(pm)){// 检查是否在符号表， 不在报错
                signal=0;
				error(WORD[count],column[count],9);
				return;
            }

            kind=lookup_kind(pm);
            if(kind==4||kind==1||kind==2||kind==6){//标识符类型可以是参数或者变量即为0或5
                signal=0;
				error(WORD[count],column[count],23);
				return;
			}
            generate("scanf","  ","  ",WORD[count]);
            if(!(strcmp(WORD_tag[count+1],"COMMA"))){
                scanfstat();
                //printf("%s\n",WORD[count]);
                if(!strcmp(WORD_tag[count],"RPARENT")){
                    return;
                }
            }
            count++;


            if(strcmp(WORD_tag[count],"RPARENT")){
				signal=1;
                error(WORD[count],column[count],14);
				return;
            }
            else{
            //printf("scanf %s\n",WORD_tag[count]);
                done=1;
                return;
            }
        }
        else{
			signal=3;
            error(WORD[count],column[count],6);
			return;
		}

    }
    else if((strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"LPARENT"))){
		signal=1;
		error(WORD[count],column[count],13);
		return;
    }

}

void printfstat(){//ok...factclass!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    PMean pm=(PMean)malloc(sizeof(Mean));
    PMean expr=(PMean)malloc(sizeof(Mean));
	char str[1000];
	char shuangyinhao1[200];
	char temp[2000];
	char temp2[200];
//printf("This is print stat！\n");
    if(!(strcmp(WORD_tag[++count],"LPARENT"))){
        count++;
        if(!(strcmp(WORD_tag[count],"STRCON"))){//是字符串或字符串+表达式
            strcpy(shuangyinhao1,"\"");
			strcpy(temp2,"\"");
			strcpy(pm->name,WORD[count]);
			strcat(shuangyinhao1,pm->name);
            count=count+1;
            if(!(strcmp(WORD_tag[count],"COMMA"))){
                count=count+1;
                expression(expr);
                generate("printf",strcat(shuangyinhao1,temp2),expr->name,(factclass == CHAR) ? "char" : "int");
            }

            else{
                generate("printf",strcat(shuangyinhao1,temp2),"",(factclass == CHAR) ? "char" : "int");
            }
        }
        else{//是表达式
            expression(expr);
            //printf("%s\n",WORD_tag[count]);
            generate("printf","",expr->name,(factclass == CHAR) ? "char" : "int");
        }

    }
    else{
		signal=1;
         error(WORD[count],column[count],13);
		 return;
    }

    if((strcmp(WORD_tag[count],"RPARENT"))){
            //printf("dsds\n");
			signal=1;
         error(WORD[count],column[count],14);
		 return;
    }
    else
        count=count+1;


}

void returnstat(){//ok...
    PMean pm=(PMean)malloc(sizeof(Mean));
    count=count+1;

//printf("This is a return stat！\n");
    if((strcmp(WORD_tag[count],"SEMCON"))){//若不是分号，则说明是带括号的返回函数
        if(strcmp(WORD_tag[count],"LPARENT")){
			signal=1;
            error(WORD[count],column[count],13);
			return;
        }
        count=count+1;
        expression(pm);
        if(strcmp(WORD_tag[count],"RPARENT")){
			signal=1;
            error(WORD[count],column[count],14);
			return;
        }
        else
            count=count+1;
        generate("return","  ","  ",pm->name);
    }
    else
        generate("return","  ","  ","  ");
     // match(29);

}


void expression(PMean pm1){//ok...
	factclass = 0;
    int flag=0;
    PMean pm=(PMean)malloc(sizeof(Mean));
//printf("This is expression！\n");
//printf("assign %s\n",WORD_tag[count]);
    if(!(strcmp(WORD_tag[count],"PLUS"))){
		factclass = INT;
        count=count+1;
    }
    else if(!(strcmp(WORD_tag[count],"MINU"))){
		factclass = INT;
        flag=1;
        count=count+1;
    }

    term(pm);
//printf("%s\n",WORD_tag[count]);

    if(flag==1){
        strcpy(pm1->name,get_temp()); //emit3
        generate("-","0",pm->name,pm1->name);
    }
    else{
        setAttribute(pm1,pm);//把pm的信息给pm1
    }

    while((!(strcmp(WORD_tag[count],"PLUS")))||(!(strcmp(WORD_tag[count],"MINU")))){
        //printf("%s\n",WORD_tag[count]);
        char old[20];
		factclass = INT;
        if(!(strcmp(WORD_tag[count],"PLUS"))){
            pm1->type=22;//代表此时是+
        }
        else
            pm1->type=23;//代表此时是-
        count=count+1;

        term(pm);

        strcpy(old,pm1->name);
        strcpy(pm1->name,get_temp());

        if(pm1->type==22) {
		  generate("+",old,pm->name,pm1->name);
        }
        else {
          generate("-",old,pm->name,pm1->name);
        }
    }
//printf("expression__%s\n",WORD_tag[count]);

    return ;

}

void  term(PMean pm1){//ok...
    PMean pm=(PMean)malloc(sizeof(Mean));
//printf("This is term！\n");
    factor(pm);
    setAttribute(pm1,pm);//把pm的信息给pm1，pm存储的信息是因子

	while((!(strcmp(WORD_tag[count],"MULT")))||(!(strcmp(WORD_tag[count],"DIV"))))//×或÷
    {
   // printf("dhgcucg\n");
        char old[20];
		factclass = INT;
        if(!(strcmp(WORD_tag[count],"MULT"))){
            pm1->kind=24;
        }
        else
            pm1->kind=25;
        count++;
        factor(pm);

        strcpy(old,pm1->name);
        strcpy(pm1->name,get_temp());//此时pm1->name为Temp%d(d为整数)

        if(pm1->kind==24)
            generate("*",old,pm->name,pm1->name);
        else
            generate("/",old,pm->name,pm1->name);
    }
    //printf("factorterm%s\n",WORD_tag[count]);

}

void factor(PMean pm1){//!!!!数组的处理ok...
    PMean pm=(PMean)malloc(sizeof(Mean));
    PMean pm2=(PMean)malloc(sizeof(Mean));//数组内的表达式
	char place3[30];
//printf("This is factor！\n");
//printf("assign %s\n",WORD[count]);
    if(!(strcmp(WORD_tag[count],"IDEN"))){//可能是标识符或者有返回值的函数调用
        count++;
        if((strcmp(WORD_tag[count],"LPARENT"))&&(strcmp(WORD_tag[count],"LBRACK")))//是标识符
        {
           strcpy(pm1->name,WORD[count-1]);//把标识符的名字给pm1
           //!!!!!!!!!!!!!注意这里lookup是需要知道pm1->type是11还是12，查看其它用到lookup系列函数的地方！！！！！！！
           //printf("factor lookup%s",pm1->name);
           if(!lookup(pm1)&&!lookup_all(pm1)){
				signal=1;
                error(pm1->name,column[count],9);
				return;
		   }
			int tempC=lookup_type(pm1);
//printf("!!!!!!!!!!!!!%d!!!!!!!!!!!!!\n",tempC);
			if(tempC==12)
				factclass=CHAR;
			else if(tempC==11)
				factclass=INT;

        }

        else if(!(strcmp(WORD_tag[count],"LPARENT"))){//函数调用
            int line=column[count];
			factor_call=1;
            call(pm);
			factor_call=0;
            if(pm->kind==1){
				signal = 2 ;
               error(pm->name,line,22);
			   return;
			}
            pm1->type=pm->type;
			strcpy(place3,get_temp());
			generate("call", pm->name, "  ", place3);
            strcpy(pm1->name,place3);//把pm的name（实际是函数名称即标识符）给pm1
            pm1->kind=2;//代表是有返回值的函数
        }
        else{//是数组！！！！！！！！！！！！！！
			strcpy(pm1->name,WORD[count-1]);
			count++;
			int temp_factclass=factclass;
			int tclass = lookup_type(pm1);
			lookup_all(pm1);
			char ttt[ 30 ];
			int line=column[count];
			if(!(strcmp(WORD_tag[count],"INTCON"))){
                   // printf("%d,%d\n",pm1->number,transint(WORD[count]));
				if(!(pm1->number>transint(WORD[count]))){
					error(pm1->name,line,40);
				}
			}
			expression(pm2);
			if(tclass==11)
				factclass = INT;
			else if(tclass==12)
				factclass=CHAR;
			else
				factclass=temp_factclass;
			//pm1->shuzuflag=transint(WORD[count]);
			if(!lookup(pm1)&&!lookup_all(pm1)){
				signal=1;
                error(pm1->name,column[count],9);
				return;
			}
			strcpy(ttt,pm1->name);
			strcpy(pm1->name,get_temp());
			generate("geta",ttt,pm2->name,pm1->name);
			if(!(strcmp(WORD_tag[count],"RBRACK"))){
				count++;
			}
			else{
				signal = 2;
				error(pm1->name,column[count],35);
				return;
			}
        }
    }

    else if(!(strcmp(WORD_tag[count],"LPARENT"))){//是表达式（表达式）
        count++;
        expression(pm);
        setAttribute(pm1,pm);//把pm的信息都赋给pm1
        if(!(strcmp(WORD_tag[count],"RPARENT"))){
            count++;
        }
        else{
			signal=2;
            error(WORD[count],column[count],14);
			return;
        }
    }

    else if(!(strcmp(WORD_tag[count],"MINU"))){//负整数
        count=count+1;
        pm1->number = -transint(WORD[count]);
		sprintf(pm1->name,"%d",transint(WORD[count])*(-1));
        if((!strcmp(WORD_tag[count],"INTCON"))){//保证是无符号整数
            pm1->kind=0;
            pm1->type=11;
        }
        else
            pm1->kind=6;
        count=count+1;
    }

    else if(!(strcmp(WORD_tag[count],"PLUS"))){//正整数
        count=count+1;
        pm1->number = transint(WORD[count]);
		strcpy(pm1->name,WORD[count]);
        if((!strcmp(WORD_tag[count],"INTCON"))){//保证是无符号整数
            pm1->kind=0;
            pm1->type=11;
        }
        else
            pm1->kind=6;
        count=count+1;
    }

    else if(!(strcmp(WORD_tag[count],"INTCON"))){//整数
        pm1->number=transint(WORD[count]);
        strcpy(pm1->name,WORD[count]);
        if((!strcmp(WORD_tag[count],"INTCON"))){//保证是无符号整数
            pm1->kind=0;
            pm1->type=11;
        }
        else
            pm1->kind=6;//chucuo
        count=count+1;
    }

    else if(!(strcmp(WORD_tag[count],"CHARCON"))){//字符（）转换成其对应的ascal码后当成整数运算
		if ( factclass != INT ) {
            factclass = CHAR;
        }
	   //printf("fegeg\n");
        pm1->number=transint(WORD[count]);//!!!!!!是否为WORD[count][0]？？？？？
		//printf("fegeg\n");
		//strcpy(pm1->name,WORD[count]);
		sprintf(pm1->name,"%d",(int)(WORD[count][0]));
        pm1->kind=0;
        pm1->type=12;
        count=count+1;
    }
    else{
		signal=1;
        error(WORD[count],column[count],17);
		return;
    }

}


void insert(PMean p){//ok
    int i;
    /*if(p->kind==3){
           // printf("%s\n%s\n",p->xiabiao,strcat(p->name,p->xiabiao));
        strcpy(p->name,strcat(p->name,p->xiabiao));
       // printf("%s\n",p->name);
    }*/
//printf("insert %s\n",p->name);
    if(lookup(p))//重复定义
        error(p->name,column[count-1],15);
    else{
		if(p->kind==3){
			stpcpy(table[hang][lie].xiabiao,p->xiabiao);
			strcpy(table[hang][lie].name,p->name);
			table[hang][lie].kind=p->kind;
			table[hang][lie].type=p->type;
			table[hang][lie].number=p->number;
        //printf("insert:%d\n",p->number);
			lie++;
			for(i=0;i<MAXPARANUM;i++){
                table[hang][lie].funcparaType[i]=p->funcparaType[i];
			}
			if(hang==0)
				all_lie++;
		}
		else{
			strcpy(table[hang][lie].name,p->name);

			table[hang][lie].kind=p->kind;
			table[hang][lie].type=p->type;
			if(p->type==11)
				table[hang][lie].number=p->number;
			else if(p->type==12)
				table[hang][lie].cischar=p->cischar;
			lie++;
			for(i=0;i<MAXPARANUM;i++){
                table[hang][lie].funcparaType[i]=p->funcparaType[i];
			}
			if(hang==0)
				all_lie++;
		}

    }
}

int lookup_kind(PMean p)//ok 返回类型
{
    int i=0;

    while(i<lie){
        if(strcmp(table[hang][i].name,p->name)==0){
			// p->number=table[hang][i].number;
			// p->type=table[hang][i].type;
			 return table[hang][i].kind;
		 }
		 i++;
    }
    i=0;
    while(i<all_lie){ //在全局层找
        if(strcmp(table[0][i].name,p->name)==0){
            return table[0][i].kind;
        }
        i++;
    }
    return -1;
}

int lookup_type(PMean p)//ok 返回类型
{
    int i=0;

    while(i<lie){
        if(strcmp(table[hang][i].name,p->name)==0){
			 p->number=table[hang][i].number;
			// p->type=table[hang][i].type;
			    //printf("lookup:%d",p->number);
			 return table[hang][i].type;
		 }
		 i++;
    }
    i=0;
    while(i<all_lie){ //在全局层找
        if(strcmp(table[0][i].name,p->name)==0){
            p->number=table[hang][i].number;
               // printf("lookup:%d",p->number);
            return table[0][i].type;
        }
        i++;
    }
    return -1;
}

void insert_all(PMean p){//ok
    int i;
    if(lookup_all(p))
        error(p->name,column[count],15);
    else{
        strcpy(table[0][all_lie].name,p->name);
        table[0][all_lie].type=p->type;
        table[0][all_lie].kind=p->kind;
        table[0][all_lie].number=p->number;    //函数参数个数
        for(i=0;i<10;i++){
//printf("p->funcparaType[i] : %d\n",p->funcparaType[i]);
                table[0][all_lie].funcparaType[i]=p->funcparaType[i];
//printf("table[0][%d].funcparaType[i]:%d, name:%s\n",i,table[0][all_lie].funcparaType[i],p->name);
        }
        all_lie++;
        if(hang==0)
            lie++;
    }
}

int lookup_all(PMean p){//ok
    int i=0;
    while(i<all_lie){ //0层找
        if(strcmp(table[0][i].name,p->name)==0){//&&p->type==table[0][i].type)
            //if(p->type==11 || (p->type==12 && p->kind==2))
            p->number=table[0][i].number;
            //else
            p->cischar=table[0][i].cischar;
            p->type=table[0][i].type;
            p->kind=table[0][i].kind;
			strcpy(p->xiabiao,table[0][i].xiabiao);
            return 1;
        }
		 i++;
	 }
     return 0;
}

int lookup(PMean p){//ok

	int i=0;
    while(i<lie){//在当前层找
        if(strcmp(table[hang][i].name,p->name)==0){
            //if(p->type==11 && p->type==table[hang][i].type)
            //{

				p->number=table[hang][i].number;
                //return 1;
           // }
            //else if(p->type==12 && p->type==table[hang][i].type)
           // {

				p->cischar=table[hang][i].cischar;
				p->type=table[hang][i].type;
				p->kind=table[hang][i].kind;
				strcpy(p->xiabiao,table[hang][i].xiabiao);
				return 1;



        }

            //!!!!!!!!!
            //else{//否则标识符名称相同但是类型不同
               // p->number=(int)table[hang][i].cischar;
                //p->kind=table[hang][i].kind;
                //return 1;
            //}
       // }
        i++;
    }
     return 0;
}




void generate(char *op, char *op1,char *op2, char *res){//ok
    static int now_block=0;
    //!!!!!!!!!!miastake-->token
    if(mistake==0){
		if(op[0]=='L'){//L开头的是跳转指令的标签
	//printf("there\n");
            fprintf(fp4,"%s:\n",op);
			strcpy(mid_code[midcode_num].op,op);
			midcode_num++;
			//printf("there\n");
		}

        else  {
   // printf("generate:%s\n",op1);
			fprintf(fp4,"%s %s %s %s\n",op,op1,op2,res);
			strcpy(mid_code[midcode_num].op,op);
			strcpy(mid_code[midcode_num].op1,op1);
			strcpy(mid_code[midcode_num].op2,op2);
			strcpy(mid_code[midcode_num].res,res);
			midcode_num++;
		}
	}

	pfour=(PFOUR)malloc(sizeof(FOUR)) ;
    pfour_now=(PFOUR)malloc(sizeof(FOUR)) ;
	pfour_head=(PFOUR)malloc(sizeof(FOUR)) ;

	strcpy(pfour->op,op);
//printf("there1\n");
    if(op[0]=='j'){

        now_block++;   //跳转，说明到一个新的基本快
        pfour->block_num=now_block;
//printf("there2\n");
        pfour->next=NULL;
        //printf("there2\n");
        pfour_now->next=pfour;
        pfour_now=pfour_now->next;

        return;
    }
    if(op1!=NULL)
        strcpy(pfour->op1,op1);
	else
        strcpy(pfour->op1,"  ");
	if(op2!=NULL)
        strcpy(pfour->op2,op2);
	else
        strcpy(pfour->op2,"  ");
	if(res!=NULL)
        strcpy(pfour->res,res);
	else
        strcpy(pfour->res,"  ");

    //若是和函数退出调用返回比较有关则所在块层发生变化(理解基本快的划分原则)
    if(strcmp(op,"goto")==0||strcmp(op,"return")==0||strcmp(op,"call")==0||strcmp(op,"endp")==0||strcmp(op,"end_main")==0){
        pfour->block_num=now_block;
        now_block++;
    }
    else if(strcmp(op,"gre")==0||strcmp(op,"lss")==0||strcmp(op,"eql")==0||strcmp(op,"geq")==0||strcmp(op,"leq")==0||strcmp(op,"neq")==0){
        pfour->block_num=now_block;
        now_block++;
    }//进入下个基本块

     else {
        pfour->block_num=now_block;
     }



}

int transint(char temp[])//ok
{
    int i;
    int result=0;
    int j=1;

    for(i=strlen(temp)-1 ;i>=0; i--,j=j*10)
    {
        result=result+j*(temp[i]-'0');
    }
    return result;
}


char *new_label(){//ok
    static int order=0;
	static char labelname[20];
    order++;
	sprintf(labelname,"_LABEL_%d",order);

	return labelname;
}

char *get_temp(){//ok
    static int c=0;
	static char tempname[20];
    c++;
	sprintf(tempname,"$_%d",c);

	return tempname;
}

void setAttribute(PMean pm1, PMean pm){//ok
    strcpy(pm1->name,pm->name);
    pm1->number=pm->number;
    pm1->type=pm->type;
    pm1->kind=pm->kind;
	pm1->shuzuflag=pm->shuzuflag;

}

int checkParaNum(char *fname,int count){
    int i=0;
    for(;i<all_lie;i++){
        if(strcmp(fname,table[0][i].name)==0&&count==table[0][i].number)
		  return 1;
    }
	return 0;
}

int checkParaType(char *fname, int count, int *currenttype){
//printf("checkParaType\n");
	int i=0;
	int j=0;
    for(;i<all_lie;i++){
        if(strcmp(fname,table[0][i].name)==0){
        //printf("name:%s, lie=%d\n",fname,i);
			while(j<count){
//printf("%s table[0][%d].funcparaType[j]:%d,  %d \n",table[0][i].name,i,table[0][i].funcparaType[j],currenttype[j]);
				if(table[0][i].funcparaType[j]==currenttype[j]){
					j=j+1;
					continue;
				}
				else{
					return 0;
				}
			}
			return 1;
		}

    }
	return 0;
}
//////////////////////////////////////////////////////////////optimize/////////////////////////////////////////////////////////////////////////
//扫描这个四元式数组，处理所有的基本块

void scan()
{
    //找到函数开始
    while ( strcmp(mid_code[ codeindex ].op, "declare") != 0 &&  codeindex<midcode_num ) codeindex++;
if(codeindex==midcode_num){
	//printf("there is not block to optimize\n");
}
    while ( codeindex < midcode_num ) {
        combine();
        delpublic();
        codeindex++;
    }
    delsetlab();
    return;
}

//合并常数,合并后的格式为=12   res
void combine() {
    int i = codeindex;
	int num1, num2, temp;
    char sum[ 30 ];
	//在运算式中
//printf("combine\n");
    while ( strcmp(mid_code[ i ].op, "+") == 0 || strcmp(mid_code[ i ].op, "-") == 0 || strcmp(mid_code[ i ].op, "*") == 0 || strcmp(mid_code[ i ].op, "/") == 0 ) {
        if ( isconst(mid_code[ i ].op1) && isconst(mid_code[ i ].op2) ) {//连续两个操作数都是数字
            num1 = atoi(mid_code[ i ].op1);
            num2 = atoi(mid_code[ i ].op2);
            if ( strcmp(mid_code[ i ].op, "+") == 0 ) temp = num1 + num2;
            if ( strcmp(mid_code[ i ].op, "-") == 0 ) temp = num1 - num2;
            if ( strcmp(mid_code[ i ].op, "*") == 0 ) temp = num1*num2;
            if ( strcmp(mid_code[ i ].op, "/") == 0 ) temp = num1 / num2;
            sprintf(sum, "%d", temp);
            strcpy(mid_code[ i ].op, "=");
            strcpy(mid_code[ i ].op1, sum);
            strcpy(mid_code[ i ].op2, "  ");
        }
        i++;
    }
}

//删除公共子表达式
void delpublic()
{
//printf("delpublic\n");

    int i, j, h, k;
    //划分基本块
    for ( i = codeindex; strcmp(mid_code[ i ].op, "+") == 0 || strcmp(mid_code[ i ].op, "-") == 0 || strcmp(mid_code[ i ].op, "*") == 0 || strcmp(mid_code[ i ].op, "/") == 0 || strcmp(mid_code[ i ].op, "=") == 0; i++ ) {
        if ( i >= midcode_num ){
            return;
        }
        if ( mid_code[ i ].res[ 0 ] == '$' ) {
            for ( j = i + 1; strcmp(mid_code[ j ].op, "+") == 0 || strcmp(mid_code[ j ].op, "-") == 0 || strcmp(mid_code[ j ].op, "*") == 0 || strcmp(mid_code[ j ].op, "/") == 0 || strcmp(mid_code[ j ].op, "=") == 0; j++ ) {
                if ( j >= midcode_num ){
                    return;
                }
                //寻找公共子表达式,若运算符和操作数1,2均相同且都是赋值给临时变量
                if ( strcmp(mid_code[ j ].op, mid_code[ i ].op) == 0 && strcmp(mid_code[ j ].op1, mid_code[ i ].op1) == 0 && strcmp(mid_code[ j ].op2, mid_code[ i ].op2) == 0 && mid_code[ j ].res[ 0 ] == '$' ) {
                    //找到在给临时变量复制后的临时变量作为操作数的式子，修改变量的名字(相当于用临时变量1代替原本作为操作数的临时变量2)
                    for ( h = j + 1; strcmp(mid_code[ h ].op, "+") == 0 || strcmp(mid_code[ h ].op, "-") == 0 || strcmp(mid_code[ h ].op, "*") == 0 || strcmp(mid_code[ h ].op, "/") == 0 || strcmp(mid_code[ h ].op, "=") == 0; h++ ) {
                        if ( h >= midcode_num ){
                            return;
                        }
                        if ( strcmp(mid_code[ h ].op1, mid_code[ j ].res) == 0 )
                            strcpy(mid_code[ h ].op1, mid_code[ i ].res);
                        if ( strcmp(mid_code[ h ].op2, mid_code[ j ].res) == 0 )
                            strcpy(mid_code[ h ].op2, mid_code[ i ].res);
                    }
                    for ( k = j; k< midcode_num; k++ ) {
                        strcpy(mid_code[ k ].op, mid_code[ k + 1 ].op);     //删除
                        strcpy(mid_code[ k ].op1, mid_code[ k + 1 ].op1);
                        strcpy(mid_code[ k ].op2, mid_code[ k + 1 ].op2);
                        strcpy(mid_code[ k ].res, mid_code[ k + 1 ].res);
                    }
                    midcode_num--;
                    j--;
                }
            }
        }
    }
}

//删除冗余跳转代码
void delsetlab()
{
//printf("delsetlab\n");

    int i, k, j, t, flag;
    char temp[ 30 ][ 10 ];
    for ( i = 0; i < midcode_num; i++ ) {
        if ( i >= midcode_num ){
            return;
        }
		//遇到lab就展开分析
        if ( strcmp(mid_code[ i ].op, "lab:") == 0 ) {
            j = 0;
            flag = i;
            i = i + 1;
			//把一个lab之后紧接着的lab都消除
            while ( strcmp(mid_code[ i ].op, "lab:") == 0 ) {
                strcpy(temp[ j++ ], mid_code[ i ].res);
                for ( k = i; k<midcode_num; k++ ) {
                    strcpy(mid_code[ k ].op, mid_code[ k + 1 ].op);     //删除
                    strcpy(mid_code[ k ].op1, mid_code[ k + 1 ].op1);
                    strcpy(mid_code[ k ].op2, mid_code[ k + 1 ].op2);
                    strcpy(mid_code[ k ].res, mid_code[ k + 1 ].res);
                }
                midcode_num--;
            }
            if ( j == 0 ) continue;
            for ( k = 0; k <= midcode_num; k++ ) {
                if ( k >= midcode_num ){
                    return;
                }
				//在消除冗余标签后，找到之前和跳转有关的指令，若是跳到冗余标签则改为跳到当下的有效标签(替代冗余标签的标签处)
                if ( strcmp(mid_code[ k ].op, "jmp") == 0 || strcmp(mid_code[ k ].op, "jne") == 0 ) {
                    for ( t = 0; t<j; t++ ) {//j记录的是有多少冗余标签
                        if ( strcmp(mid_code[ k ].res, temp[ t ]) == 0 )
                            strcpy(mid_code[ k ].res, mid_code[ flag ].res);
                    }
                }
            }
        }
    }
}



//活跃变量分析
int ret_code(char *op1) //返回编号
{
	int i;
    for(i=0;i<var_count;i++)
	{
       if(strcmp(op1,bianhao[i])==0)
		   return i;
	}

	strcpy(bianhao[var_count++],op1);
	return i;
}
void def_use(){
	int i=0;
    int now_block=0;
	int mark=1;//计算in ，out 循环标志
	int curren_mid;
	var_count=0;
	now_block=0;
	use_num=0;
	def_num=0;
	seq=0;
	curren_mid=codeindex;

	pfour_now=pfour_head->next;
    now_block=pfour_now->block_num;

	while(pfour_now!=NULL){
		if(now_block<pfour_now->block_num) //进入下个基本块
		{
            now_block=pfour_now->block_num;
		}
		if(strcmp(pfour_now->op,"=")==0) //def
		{
			//	strcpy(array[now_block].def[use_num++],pfour_now->res);

				/////////////////////////////////////////////////////
				if((pfour_now->op1[0]!='$'))//op1是变量
				{
					  int t;
                      //strcpy(array[now_block].use[use_num++],pfour_now->op1);
					  t=ret_code(pfour_now->op1);//返回编号

					  if(block_array[now_block].def[t]!=1)
                      block_array[now_block].use[t]=1;

                     t=ret_code(pfour_now->res);
					 block_array[now_block].def[t]=1;

				}
		}
		else
		{
				if(strcmp("  ",pfour_now->op1)!=0)
				{
				     if((pfour_now->op1[0]=='$'))
					 {
                      int t;
                      //strcpy(array[now_block].use[use_num++],pfour_now->op1);
					  t=ret_code(pfour_now->op1);//返回编号,若第一次出现，加入编号表

					  if(block_array[now_block].def[t]!=1)
                      block_array[now_block].use[t]=1;
					 }
				}

				if(strcmp("  ",pfour_now->op2)!=0)
				{
				     if((pfour_now->op2[0]=='$'))
					 {
                             int t;
                      //strcpy(array[now_block].use[use_num++],pfour_now->op1);
					  t=ret_code(pfour_now->op2);                   //返回编号,若第一次出现，加入编号表

					  if(block_array[now_block].def[t]!=1)
                      block_array[now_block].use[t]=1;
					 }
				}

		}

	}

}
void init_in()
{
	int i,j;
 for(i=0;i<now_block;i++)
	 for(j=0;j<RelateMax;j++)
   block_array[i].in[j]=0;
}

void in_out()
{
    int mark=1;
    init_in(); //初始化in 集合

     while(mark==1) //标记in
	 {
		 int i;
         for(i=0;i<now_block;i++)
		 {
			 int j;

			 //for(j=0;j<LiveMax;j++) in[j]=0;
              int old=0;
              for(j=0;j<RelateMax;j++)  //求out[]
			  {
				  int k,old;
				  k=block_array[i].aft_block[j];
             block_array[i].out[j]=block_array[i].out[j]||block_array[k].in[j];

		     old=block_array[i].in[j];
		         block_array[i].in[j]= block_array[i].use[j]|( block_array[i].out[j]&(~block_array[i].def[j]));

			     if(old!=block_array[i].in[j]) mark=1;//in 变化
			  }



		 }

	 }

}


//判断是不是数字
int isconst(char name[])
{
    int i = 0;
    if ( name[ i ] == '-' ) i++;
    while ( name[ i ] != '\0' ) {
        if ( name[ i ]>'9' || name[ i ]<'0' ) return 0;
        i++;
    }
    return 1;
}

//打印优化后的四元式
void printOptimize()
{
    optcodefile = fopen("1514059_yuxinyi_afterSiyuanshi.txt", "w");
    int i = 0;
    while ( i<midcode_num ) {
        fprintf(optcodefile, "%s ", mid_code[ i ].op);
        strcpy(mid_code2[midcode_num2].op,mid_code[ i ].op);
        fprintf(optcodefile, "%s ", mid_code[ i ].op1);
        strcpy(mid_code2[midcode_num2].op1,mid_code[ i ].op1);
        fprintf(optcodefile, "%s ", mid_code[ i ].op2);
        strcpy(mid_code2[midcode_num2].op2,mid_code[ i ].op2);
        fprintf(optcodefile, "%s\n", mid_code[ i ].res);
        strcpy(mid_code2[midcode_num2].res,mid_code[ i ].res);
        midcode_num2++;
        if ( strcmp(mid_code[ i ].op, "endp") == 0 )
            fprintf(optcodefile, "\n\n");
        i++;
    }
	//printf("111   __: %d\n",midcode_num2);
    fclose(optcodefile);
    return;
}



///////////////////////////////////mid_code---->>> mips///////////////////////////////////////////////////////////

void assembly(){
    char op[WordMax],op1[WordMax],op2[WordMax],res[WordMax];
    char siyuan[LineMax],label[WordMax];//标号
    int all_state[DEEP][RegMax+2]; //进函数前保存状态
    int now_deep=0;
    int already_para=0;
    int used_reg=0;//使用过的临时变量编号
    int para_count=0;
	funcclass tfc;
	mi=ap=0;
    fclose(fp4);
    fp4=fopen("siyuanshi.txt","r");
	fprintf(fp_final,"\t.text\n");
	fprintf(fp_final,"\t\tori\t$fp\t$sp\t0\n");//ori $fp $sp 0(fp：帧指针，sp:堆栈指针)
	fprintf(fp_final,"\t\tli\t$t9\t0x7fffeffc\t#global stack bottom\n");//li $t9 0x7fffeffc （全局变量的栈底）
	fprintf(fp_final,"\t\tli\t$t8\t0x10010000\t#save word\n");//li $t8 0x10010000 （）
//printf("%d %d\n",midcode_num2,mi);//(172)
//printf("%s %s \n",mid_code2[ mi ].op);
	//全局常量
	//printf("%d\n",midcode_num2);
	while(mi<midcode_num2){
		while ( strcmp(mid_code2[ mi ].op, "const") == 0 ){
//printf("global const\n");
			pushstack(mid_code2[ mi ].op2,1);
			if(strcmp("int",mid_code2[ mi ].op1)==0){
				insertaddress(WINT,-1,-1);
			}
			else
				insertaddress(WCHAR,-1,-1);
			mi++;
		}
		//全局变量
		while ( strcmp(mid_code2[ mi ].op, "int") == 0 || strcmp(mid_code2[ mi ].op, "char") == 0 || strcmp(mid_code2[ mi ].op, "inta") == 0 || strcmp(mid_code2[ mi ].op, "chara") == 0 ) {
			if( strcmp(mid_code2[ mi ].op, "int") == 0 || strcmp(mid_code2[ mi ].op, "char") == 0){
//printf("global var\n");
				pushstack("0",1);
				if (strcmp("int",mid_code2[ mi ].op) == 0 ) {
					insertaddress(WINT,-1,-1);
				} else {
					insertaddress(WCHAR,-1,-1);
				}
				mi++;
			}
			else if(strcmp(mid_code2[ mi ].op, "inta") == 0 || strcmp(mid_code2[ mi ].op, "chara") == 0 ){
//printf("global shuzu\n");
				pushstack("0", atoi(mid_code2[mi].op2));
				if (strcmp("inta",mid_code2[ mi ].op) == 0 ) {
					insertaddress(WINT,-1,-1);
				} else {
					insertaddress(WCHAR,-1,-1);
				}
				mi++;
			}
		}

		fprintf(fp_final,"\t\tj\t__main\n");
		constedge = ap;
		//函数定义
		while ( strcmp(mid_code2[mi].op, "declare") == 0 || strcmp(mid_code2[mi].op, "main") == 0) {
//printf("function\n");
		   if ( strcmp(mid_code2[ mi ].op1, "char") == 0 ) {
                tfc.kind = CHAR;
                strcpy(tfc.name, mid_code2[ mi ].res);
                fc[funcnum]=tfc;
            } else if ( strcmp(mid_code2[ mi ].op1, "int") == 0 ) {
                tfc.kind = INT;
                strcpy(tfc.name, mid_code2[ mi ].res);
                fc[funcnum]=tfc;
            } else {
                tfc.kind = VOID;
                strcpy(tfc.name, mid_code2[ mi ].res);
                fc[funcnum]=tfc;
            }
            if ( strcmp(mid_code2[ mi ].op, "main") == 0 ) {
                ismain = 1;
                fprintf(fp_final, "__main:\n");
            } else {
                ismain = 0;
                fprintf(fp_final,"%s:\n", mid_code2[ mi ].res );
            }
            mi++;
			funcnum++;
            funcasm();
        }
	}

}


//处理函数内容，不处理最后的end和开始的func
void funcasm(){
memset(varreg, 0xff, sizeof(int) * 200);
//printf("begin funcasm\n");
	int i;
	int temp;
	sp = 0;//相对偏移为0
	fprintf(fp_final,"\t\t#Save Register\n");//保存现场
	savesreg();//将之前寄存器的值该保存的都保存了
	fprintf(fp_final,"\t\tsw\t$fp\t($sp)\n");//保存上一个函数的$fp  //sw $fp ($sp)
	fprintf(fp_final,"\t\tadd\t$fp\t$sp\t$0\n");//设置本函数$fp：//$fp=$sp  add $fp $sp $0
	sp -= 4;
	fprintf(fp_final,"\t\tsubi\t$sp\t$sp\t4\n");//$sp-=4//subi $sp $sp 4
	fprintf(fp_final,"\t\tsw\t$ra\t($sp)\n");//保存$ra//sw $ra ($sp)
	sp -= 4;
	fprintf(fp_final,"\t\tsubi\t$sp\t$sp\t4\n");//$sp-=4//subi $sp $sp 4
	fprintf(fp_final,"\t\t#Save Register Done!\n");
	//临时变量定义
    tmi = mi;
	temp=mi;
	while ( strcmp(mid_code2[ tmi ].op, "endp") != 0 ) {//直到函数结束四元式才退出
//printf("%s %s %s %s:\n",mid_code2[ mi ].op,mid_code2[ mi ].op1,mid_code2[ mi ].op2,mid_code2[ mi ].res);
 //fprintf(fp_final,"temp;%s %s %s\n",mid_code2[ tmi ].op1,mid_code2[ tmi ].op2,mid_code2[ tmi ].res);
		char v1[100], v2[100], v3[100];
        strcpy(v1, mid_code2[ tmi ].op1);
        strcpy(v2, mid_code2[ tmi ].op2);
        strcpy(v3, mid_code2[ tmi ].res);


        if ( v1[ 0 ] == '$' && varaddr(v1) == -1 ) {
            pushstack("0",1);
            insertaddress(INT, -1, tmi);
        }
        if ( v2[ 0 ] == '$' && varaddr(v2) == -1 ) {
            pushstack("0",1);
            insertaddress(INT, -1, tmi);
        }
        if ( v3[0] == '$' && varaddr(v3) == -1 ) {
            pushstack("0",1);
            if ( strcmp(mid_code2[tmi].op, "call") == 0 ) {
                insertaddress(funckind(mid_code2[tmi].op1), -1, tmi);
            }
            else if ( strcmp(mid_code2[ tmi ].op, "geta") == 0 ){
                insertaddress(varkind(v1), -1, tmi);
            }
            else{
                insertaddress(INT, -1, tmi);
            }
        }
        tmi++;
    }
mi=temp;
	while ( strcmp(mid_code2[ mi ].op, "endp") != 0 ) {
//printf("%s %s %s %s:\n",mid_code2[ mi ].op,mid_code2[ mi ].op1,mid_code2[ mi ].op2,mid_code2[ mi ].res);
        paran = 0;
        for ( i = 0; i < strlen(mid_code2[ mi ].op); i++ ) {
            if ( mid_code2[ mi ].op[ i ] == ' ' ) {
                mid_code2[ mi ].op[ i ] = '\0';
                break;
            }
        }
        if ( strcmp(mid_code2[ mi ].op, "+") == 0 ) addasm();
        if ( strcmp(mid_code2[ mi ].op, "-") == 0 ) subasm();
        if ( strcmp(mid_code2[ mi ].op, "*") == 0 ) mulasm();
        if ( strcmp(mid_code2[ mi ].op, "/") == 0 ) divasm();
        if ( strcmp(mid_code2[ mi ].op, ">") == 0 ) greasm();
        if ( strcmp(mid_code2[ mi ].op, ">=") == 0 ) geqasm();
        if ( strcmp(mid_code2[ mi ].op, "<") == 0 ) lssasm();
        if ( strcmp(mid_code2[ mi ].op, "<=") == 0 ) leqasm();
        if ( strcmp(mid_code2[ mi ].op, "!=") == 0 ) neqasm();
        if ( strcmp(mid_code2[ mi ].op, "==") == 0 ) eqlasm();
        if ( strcmp(mid_code2[ mi ].op, "=") == 0 ) assasm();
        if ( strcmp(mid_code2[ mi ].op, "[]=") == 0 ) aassasm();
        if ( strcmp(mid_code2[ mi ].op, "geta") == 0 ) assaasm();
        if ( strcmp(mid_code2[ mi ].op, "lab:") == 0 ) setlabasm();//"lab:", "  ", "  ", label1
        if ( strcmp(mid_code2[ mi ].op, "scanf") == 0 ) {
            scfasm();
        }
        if ( strcmp(mid_code2[ mi ].op, "printf") == 0 ) {
            prtasm();
        }
        if ( strcmp(mid_code2[ mi ].op, "jne") == 0 ) jneasm();
        if ( strcmp(mid_code2[ mi ].op, "jmp") == 0 ) jmpasm();//把goto改为jmp?????
        if ( strcmp(mid_code2[ mi ].op, "fupa") == 0 ) fupaasm();
        if ( strcmp(mid_code2[ mi ].op, "call") == 0 ) callasm();
        if ( strcmp(mid_code2[ mi ].op, "return") == 0 ) retasm();
        if ( strcmp(mid_code2[ mi ].op, "para") == 0 ) paraasm();
        /*if ( OPTFLAG ) {
            int flag = 0;
            while ( strcmp(mid_code2[ mi ].op, "int") == 0
                || strcmp(mid_code2[ mi ].op, "char") == 0 ) {
                flag = 1;
                intcharasm();
                mi++;
            }
            if (flag)    mi--;
            //引用计数优化
            cntopt();
        } else {*/
			if ( strcmp(mid_code2[ mi ].op, "int") == 0
                || strcmp(mid_code2[ mi ].op, "char") == 0 ) {
						intcharasm();
			 }

        if ( strcmp(mid_code2[ mi ].op, "const") == 0 ) constdefasm();
//printf("return const:\n");
//printf("%s %s %s %s:\n",mid_code2[ mi ].op,mid_code2[ mi ].op1,mid_code2[ mi ].op2,mid_code2[ mi ].res);
        if ( strcmp(mid_code2[ mi ].op, "inta") == 0 || strcmp(mid_code2[ mi ].op, "chara") == 0 )
				intcharaasm();
        mi++;
    }

	ap = constedge;
	//恢复现场
	fprintf(fp_final,"__FEND_LAB_%d:\n",funcnum);//结束开始
	fprintf(fp_final,"\t\tlw\t$ra\t-4($fp)\n");//恢复$ra
	fprintf(fp_final,"\t\tadd\t$sp\t$fp\t$0\n");//退栈,恢复$sp
	fprintf(fp_final,"\t\tlw\t$fp\t($fp)\n");//恢复上一个函数的fp
	loadsreg();//恢复$s0-$s7
	if ( ismain ) {
        fprintf(fp_final,"\t\tli\t$v0\t10\n" );
        fprintf(fp_final,"\t\tsyscall\n" );//终止程序
    } else {
        fprintf(fp_final,"\t\tjr\t$ra\t\n");//返回
    }
    mi = mi + 1;
    return;
}

void savesreg(){
	int i;
	for(i=0;i<8;i++){
		fprintf(fp_final,"\t\tsw\t$t%d\t%d($t8)\n",i,i*4);//sw $t%d %d($t8)($t8 0x10010000)
	}
}
void loadsreg(){
	int i;
	for (i = 0; i < 8; i++ ) {
        fprintf(fp_final, "\t\tlw\t$t%d\t%d($t8)\n" ,i ,4 * i);
    }

}

int funckind(char *fname) {//!!!!!!和fc有关在funcasm中用到?????????fc.size()???
    int i;
    for ( i = 0; i < 100; i++ ) {
        if ( strcmp(fc[i].name, fname) == 0 ) {
            return fc[ i ].kind;
        }
    }
}

int varkind(char *name) {
    int t ;
	t= ap - 1;
    if ( name[ 0 ] == '+' || name[ 0 ] == '-' || name[ 0 ] >= '0'&&name[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {
        if ( strcmp(addrtable[ t ].name, name) == 0 )
            return addrtable[ t ].kind;
        t--;
    }
    return -1;
}

int findvartable(char *name) {//scafasm pritasm用到
    int t;
	t= ap - 1;
    if ( name[ 0 ] == '+' || name[ 0 ] == '-' || name[ 0 ] >= '0'&&name[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {
        if ( strcmp(addrtable[ t ].name, name) == 0 )
            return t;
        t--;
    }
    return -1;
}

//查找汇编变量地址
int varaddr(char *name) {
    int t;
	t = ap - 1;
    isglob = 0;
    if ( name[ 0 ] == '+' || name[ 0 ] == '-' || name[ 0 ] >= '0'&&name[ 0 ] <= '9' )
        return -1;
    while ( t >= 0 ) {
        if ( strcmp(addrtable[ t ].name, name) == 0 ) {
            if ( t < constedge ) {
                isglob = 1;
            }
            return addrtable[ t ].address;
        }
        t--;
    }
    return -1;
}

//给地址表插入相对地址，sp不变
void insertaddress(int kind, int addr, int nmi) {//!!!去找用到的地方
//printf("insertaddress\n");
    if ( nmi == -1 ) {
        strcpy(addrtable[ ap ].name, mid_code2[ mi ].res);
    } else {
        strcpy(addrtable[ ap ].name, mid_code2[ nmi ].res);
    }
    if ( addr == -1 ) {
        addrtable[ ap ].address = sp + 4;
    } else {
        addrtable[ ap ].address = addr;
    }
    addrtable[ ap ].kind = kind;
    addrtable[ ap ].cnt = 0;
    ap++;
}

void pushstack(char* item, int lenth) {//!!!去找用到的地方
//printf("pushstack\n");
    if ( lenth == 1 ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\t#%s\n",item , mid_code2[tmi].res ); //li    $t0 item
        fprintf(fp_final, "\t\tsw\t$t0\t($sp)\n" );      //sw    $t0 $sp
    }
    sp -= ( 4 * lenth );
    fprintf(fp_final, "\t\tsubi\t$sp\t$sp\t%d\n" , 4 * lenth ); //subi  $sp $sp 4
    return;
}

//    add a,	b,	c
void addasm(){
//printf("addasm\n");

	int addr1, addr2, addr3;
	if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1 -2147479548);
        else
            fprintf(fp_final,"\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2 );
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    addr3 = varaddr(mid_code2[ mi ].res);
    fprintf(fp_final,  "\t\tadd\t$t0\t$t0\t$t1\n");
    if ( isglob )
        fprintf(fp_final,"\t\tsw\t$t0\t%d($t9)\n" ,addr1-2147479548 );
    else
        fprintf(fp_final,"\t\tsw\t$t0\t%d($fp)\n" ,addr3 );

}

//    sub, a, b, c
void subasm() {
	//printf("subasm\n");

    int addr1, addr2, addr3;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1 -2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    addr3 = varaddr(mid_code2[ mi ].res);
    fprintf(fp_final,"\t\tsub\t$t0\t$t0\t$t1\n" );
    if ( isglob )
        fprintf(fp_final, "\t\tsw\t$t0\t%d($t9)\n" , addr3-2147479548);
    else
        fprintf(fp_final,"\t\tsw\t$t0\t%d($fp)\n" , addr3 );
}

//    mul, a, b, c
void mulasm() {
	//printf("mulasm\n");

    int addr1, addr2, addr3;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1 -2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    addr3 = varaddr(mid_code2[ mi ].res);
    fprintf(fp_final,"\t\tmul\t$t0\t$t0\t$t1\n" );
    if ( isglob )
        fprintf(fp_final,"\t\tsw\t$t0\t%d($t9)\n" ,addr3 -2147479548);
    else
        fprintf(fp_final, "\t\tsw\t$t0\t%d($fp)\n" , addr3 );
}

//    div, a, b, c
void divasm() {
//printf("divasm\n");

    int addr1, addr2, addr3;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1-2147479548 );
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    addr3 = varaddr(mid_code2[ mi ].res);
    fprintf(fp_final, "\t\tdiv\t$t0\t$t0\t$t1\n" );
    if ( isglob )
        fprintf(fp_final,"\t\tsw\t$t0\t%d($t9)\n" ,addr3 -2147479548);
    else
        fprintf(fp_final, "\t\tsw\t$t0\t%d($fp)\n" , addr3 );
}

//    lab,  ,  ,
void setlabasm() {
//printf("setlabasm\n");

    fprintf(fp_final,"%s:\n", mid_code2[ mi ].res );
}


//    jmp ,  ,  ,
void jmpasm() {
    fprintf(fp_final,"\t\tj\t%s\n" , mid_code2[ mi ].res );
}

//    jne
void jneasm() {
//printf("jneasm\n");

    fprintf(fp_final, "\t\tbne\t$t0\t1\t%s\n" ,mid_code2[ mi ].res);
}

//    call, f ,   , a
void callasm() {
//printf("callasm\n");

	int addr2;
    fprintf(fp_final, "\t\tjal\t%s\n" , mid_code2[ mi ].op1 );
    fprintf(fp_final, "\t\tnop\n");
    if ( mid_code2[ mi ].res[ 0 ] != ' ' && mid_code2[ mi ].res[ 0 ] != '\0' ) {
        addr2 = varaddr(mid_code2[ mi ].res);
        if ( isglob )
            fprintf(fp_final,"\t\tsw\t$v0\t%d($t9)\n" , addr2 -2147479548);
        else
            fprintf(fp_final, "\t\tsw\t$v0\t%d($fp)\n ",addr2 );
    }
}


//    >//
void greasm() {
//printf("greasm\n");

    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1 -2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    fprintf(fp_final,"\t\tslt\t$t0\t$t1\t$t0\n" );
}

//    >=
void geqasm() {
//printf("geqasm\n");

    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1-2147479548 );
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    fprintf(fp_final, "\t\tslt\t$t0\t$t0\t$t1\n" );
    fprintf(fp_final, "\t\tli\t$t1\t1\n" );
    fprintf(fp_final, "\t\tsub\t$t0\t$t1\t$t0\n" );
}

//    <
void lssasm() {
//printf("lssasm\n");

    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1-2147479548 );
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    fprintf(fp_final, "\t\tslt\t$t0\t$t0\t$t1\n" );
}

//    <=
void leqasm() {
//printf("leqasm\n");

    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1 -2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    fprintf(fp_final, "\t\tslt\t$t0\t$t1\t$t0\n");
    fprintf(fp_final,"\t\tli\t$t1\t1\n");
    fprintf(fp_final,"\t\tsub\t$t0\t$t1\t$t0\n" );
}

//    ==
void eqlasm() {
//printf("eqlasm\n");

    int t1;
    int t2;
    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1 -2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }

    t1 = tlabelnum++;
    t2 = tlabelnum++;
    fprintf(fp_final, "\t\tbne\t$t0\t$t1\t__tLABEL%d\n",t1 );
    fprintf(fp_final, "\t\tli\t$t0\t1\n" );
    fprintf(fp_final, "\t\tj\t__tLABEL%d\n" , t2 );
    fprintf(fp_final, "__tLABEL%d:\n" , t1 );
    //cout << "__tLABEL" << t1 << ":" );
    fprintf(fp_final, "\t\tli\t$t0\t0\n" );
    fprintf(fp_final, "__tLABEL%d:\n" , t2 );
}

//    !=
void neqasm() {
//printf("neqasm\n");

    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
        if ( isglob )
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n" , addr1-2147479548 );
        else
            fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" , addr1 );
    }
    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        fprintf(fp_final,"\t\tli\t$t1\t%s\n" ,mid_code2[ mi ].op2);
    } else {
        addr2 = varaddr(mid_code2[ mi ].op2);
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addr2-2147479548);
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addr2 );
    }
    int t1 = tlabelnum++;
    int t2 = tlabelnum++;
    fprintf(fp_final, "\t\tbeq\t$t0\t$t1\t__tLABEL%d\n",t1 );
    fprintf(fp_final, "\t\tli\t$t0\t1\n" );
    fprintf(fp_final, "\t\tj\t__tLABEL%d\n" , t2 );
    fprintf(fp_final, "__tLABEL%d:\n" , t1 );
    //cout << "__tLABEL" << t1 << ":" );
    fprintf(fp_final, "\t\tli\t$t0\t0\n" );
    fprintf(fp_final, "__tLABEL%d:\n" , t2 );
}

//    =//
void assasm() {
//printf("assasm\n");

    int addr1, addr2;
    if ( isdigit(mid_code2[ mi ].op1[ 0 ]) || mid_code2[ mi ].op1[ 0 ] == '-' || mid_code2[ mi ].op1[ 0 ] == '+' ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" , mid_code2[ mi ].op1 );
    } else {
        addr1 = varaddr(mid_code2[ mi ].op1);
//检查op1是否为函数名，是的话就move $v0
        if ( isglob )
            fprintf(fp_final, "\t\tlw\t$t0\t%d($t9)\n" ,addr1-2147479548 );//ls $t0 %d($t9)
        else
            fprintf(fp_final,"\t\tlw\t$t0\t%d($fp)\n" ,addr1 );
    }
    addr2 = varaddr(mid_code2[ mi ].res);
    if (isglob )
        fprintf(fp_final,"\t\tsw\t$t0\t%d($t9)\n", addr2-2147479548);
    else
        fprintf(fp_final, "\t\tsw\t$t0\t%d($fp)\n" , addr2 );
}

//    []= , a , i , t
void aassasm() {
	//printf("aassasm\n");

    int addr1, addr2, addrt;
    int tisglob;
	tisglob	= isglob;
	addr1 = varaddr(mid_code2[ mi ].op1);
	tisglob	= isglob;

    if ( isdigit(mid_code2[ mi ].op2[0]) ) {
        addr1 += (atoi(mid_code2[ mi ].op2) * 4);//???????????????
        if ( isdigit(mid_code2[ mi ].res[ 0 ]) || mid_code2[ mi ].res[ 0 ] == '-' || mid_code2[ mi ].res[ 0 ] == '+' ) {
            fprintf(fp_final,"\t\tli\t$t0\t%s\n" ,mid_code2[ mi ].res);
        } else {
            addr2 = varaddr(mid_code2[ mi ].res);
            if ( isglob ) {
                fprintf(fp_final, "\t\tlw\t$t0\t%d($t9)\n" ,addr2-2147479548 );
            }else
                fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" ,addr2 );
        }
        if (tisglob)
            fprintf(fp_final,"\t\tsw\t$t0\t%d($t9)\n",addr1- 2147479548);
        else
            fprintf(fp_final, "\t\tsw\t$t0\t%d($fp)\n", addr1 );
    } else {
        //求数组元素a[i]地址
        addrt = varaddr(mid_code2[ mi ].op2);//addrt = &i
        if (isglob)
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n" , addrt-2147479548 );    //t1 = i
        else
            fprintf(fp_final, "\t\tlw\t$t1\t%d($fp)\n" , addrt );    //t1 = i
        fprintf(fp_final, "\t\tmul\t$t1\t$t1\t4\n") ;  //t1 = t1 * 4 (t1 = offset)
        fprintf(fp_final, "\t\taddi\t$t1\t$t1\t%d\n" ,addr1 );    //t1 = &a[i] - $fp
		if(tisglob==0)
			fprintf(fp_final, "\t\tadd\t$t1\t$t1\t$fp\n" );//t1 = &a[i]
        if ( isdigit(mid_code2[ mi ].res[ 0 ]) || mid_code2[ mi ].res[ 0 ] == '-' || mid_code2[ mi ].res[ 0 ] == '+' ) {
            fprintf(fp_final, "\t\tli\t$t0\t%s\n" ,mid_code2[ mi ].res );
        } else {
            addr2 = varaddr(mid_code2[ mi ].res);
            if ( isglob ) {
                fprintf(fp_final, "\t\tlw\t$t0\t%d($t9)\n" , addr2-2147479548 );
            } else {
                fprintf(fp_final, "\t\tlw\t$t0\t%d($fp)\n" ,addr2 );
            }

        }
        fprintf(fp_final, "\t\tsw\t$t0\t0($t1)\n" );
    }
}

//geta, a, n, b
void assaasm() {//
	//printf("assaasm\n");

    int addr1 ;
    int tisglob;
	int addr2;
	int addrt;

	tisglob	= isglob;
    addr1= varaddr(mid_code2[ mi ].op1);
	tisglob	= isglob;

    if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
        addr1 += ( atoi(mid_code2[ mi ].op2) * 4 );    //addr1 = &a[n]
        addr2 = varaddr(mid_code2[ mi ].res);        //addr2 = &b
        if ( tisglob ) {
            fprintf(fp_final,"\t\tlw\t$t0\t%d($t9)\n",addr1-2147479548);
        }else
            fprintf(fp_final,"\t\tlw\t$t0\t%d($fp)\n" , addr1 );
        if ( isglob ) {
            fprintf(fp_final,"\t\tsw\t$t0\t%d($t9)\n" ,addr2 -2147479548);
        }else
            fprintf(fp_final,"\t\tsw\t$t0\t%d($fp)\n" , addr2 );
    } else {
        //求数组元素a[i]地址
        addrt = varaddr(mid_code2[ mi ].op2);//addrt = &i
        if ( isglob ) {
            fprintf(fp_final, "\t\tlw\t$t1\t%d($t9)\n",addrt-2147479548);    //t1 = i
        }else
            fprintf(fp_final,"\t\tlw\t$t1\t%d($fp)\n", addrt );    //t1 = i
        fprintf(fp_final, "\t\tmul\t$t1\t$t1\t4\n");    //t1 = t1 * 4 (t1 = offset)
        fprintf(fp_final, "\t\taddi\t$t1\t$t1\t%d\n" , addr1);    //t1 = &a[i] - $fp
		if(tisglob==0)
			fprintf(fp_final, "\t\tadd\t$t1\t$t1\t$fp\n");
        fprintf(fp_final, "\t\tlw\t$t1\t0($t1)\n");    //t1 = a[i]
        addr2 = varaddr(mid_code2[ mi ].res);    //addr2 = &b
        if (isglob)
            fprintf(fp_final,"\t\tsw\t$t1\t%d($t9)\n" , addr2-2147479548 );
        else
            fprintf(fp_final,"\t\tsw\t$t1\t%d($fp)\n", addr2 );
    }
}

//scf ,   ,   , a
void scfasm() {
	//printf("scfasm\n");

    int addr;
    int ti;
    int kind;

	ti	= findvartable(mid_code2[ mi ].res);
	kind	= addrtable[ ti ].kind;
	addr	= varaddr(mid_code2[ mi ].res);

    if ( kind == INT || kind == WINT ) {
        fprintf(fp_final,"\t\tli\t$v0\t5\n" );
        fprintf(fp_final, "\t\tsyscall\n");
        //fprintf(fp_final, "\t\tsubi\t$v0\t$v0\t" << ( int )'0' );
        if (isglob)
            fprintf(fp_final, "\t\tsw\t$v0\t%d($t9)\n" , addr-2147479548 );
        else
            fprintf(fp_final,"\t\tsw\t$v0\t%d($fp)\n" , addr);
    } else {
        fprintf(fp_final, "\t\tli\t$v0\t12\n");
        fprintf(fp_final,"\t\tsyscall\n" );
        if ( isglob )
            fprintf(fp_final,"\t\tsw\t$v0\t%d($t9)\n" , addr -2147479548);
        else
            fprintf(fp_final,"\t\tsw\t$v0\t%d($fp)\n" , addr );
    }
}

//prt, a, b, symb
void prtasm() {
	//printf("prtasm\n");

    int addr;
	int len;
	int i;
	int ti;
	int kind;
//printf("%s %s %s %s:\n",mid_code2[ mi ].op,mid_code2[ mi ].op1,mid_code2[ mi ].op2,mid_code2[ mi ].res);

    if ( mid_code2[ mi ].op1[ 0 ] != '\0' ) {
        len = strlen(mid_code2[ mi ].op1);
        for ( i = 1; i < len-1; i++ ) {
//printf("%c\n",mid_code2[ mi ].op1[i]);
            fprintf(fp_final, "\t\tli\t$v0\t11\n" );
//printf("string:\n");
            fprintf(fp_final, "\t\tli\t$a0\t%d\n" ,(int)(mid_code2[ mi ].op1[i]) );
//printf("string:\n");
            fprintf(fp_final, "\t\tsyscall\n" );
        }
    }
//printf("%d\n",mid_code2[ mi ].op2[ 0 ] == '\0');
    if ( mid_code2[ mi ].op2[ 0 ] != ' ' && mid_code2[ mi ].op2[ 0 ] != '\0' ) {
        if ( isdigit(mid_code2[mi].op2[0]) && strcmp(mid_code2[mi].res, "char") == 0 ) {
            fprintf(fp_final, "\t\tli\t$v0\t11\n" );
            fprintf(fp_final, "\t\tli\t$a0\t%s\n",mid_code2[ mi ].op2 );
            fprintf(fp_final, "\t\tsyscall\n" );
            return;
        } else if ( isdigit(mid_code2[ mi ].op2[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
            fprintf(fp_final, "\t\tli\t$v0\t1\n" );
            fprintf(fp_final, "\t\tli\t$a0\t%s\n" , mid_code2[ mi ].op2 );
            fprintf(fp_final, "\t\tsyscall\n" );
            return;
        }
        addr = varaddr(mid_code2[ mi ].op2);
         ti = findvartable(mid_code2[ mi ].op2);
         kind = addrtable[ ti ].kind;
        if ( kind == INT || kind == WINT || strcmp(mid_code2[ mi ].res,"int")==0) {
            fprintf(fp_final, "\t\tli\t$v0\t1\n" );
            if ( isglob ) {
                fprintf(fp_final, "\t\tlw\t$a0\t%d($t9)\n" ,addr - 2147479548);
            }else
            fprintf(fp_final, "\t\tlw\t$a0\t%d($fp)\n" , addr);
            fprintf(fp_final, "\t\tsyscall\n" );
        } else {
            fprintf(fp_final, "\t\tli\t$v0\t11\n" );
            if ( isglob )
				fprintf(fp_final, "\t\tlw\t$a0\t%d($t9)\n",addr  -2147479548);
            else    fprintf(fp_final, "\t\tlw\t$a0\t%d($fp)\n", addr );
            fprintf(fp_final, "\t\tsyscall\n" );
        }
    }
}

//fupa,   ,   , a     ==> a is a function parameter
void fupaasm() {
	//printf("fupaasm\n");
	int addrt;
    if ( isdigit(mid_code2[mi].res[0]) ) {
        fprintf(fp_final, "\t\tli\t$t0\t%s\n" ,mid_code2[ mi ].res );
    } else {
		addrt=varaddr(mid_code2[ mi ].res);
        if(isglob){
			fprintf(fp_final, "\t\tlw\t$t0\t%d",addrt-2147479548); //li    $t0 item
            fprintf(fp_final, "($t9)\n" );
        }else{
			fprintf(fp_final, "\t\tlw\t$t0\t%d",addrt);
            fprintf(fp_final, "($fp)\n" );
        }
    }
    fprintf(fp_final, "\t\tsw\t$t0\t($sp)\n" );      //sw    $t0 $sp
    sp -= 4;
    fprintf(fp_final, "\t\tsubi\t$sp\t$sp\t4\n" ); //subi  $sp $sp 4
}

//ret ,   ,   , (a)   ==> return a / return
void retasm() {
	//printf("retasm\n");

    if ( mid_code2[ mi ].res[ 0 ] != ' ' && mid_code2[ mi ].res[ 0 ] != '\0' ) {
        if ( isdigit(mid_code2[ mi ].res[ 0 ]) || mid_code2[ mi ].op2[ 0 ] == '-' || mid_code2[ mi ].op2[ 0 ] == '+' ) {
            fprintf(fp_final, "\t\tli\t$v0\t%s\n" ,mid_code2[ mi ].res );
        } else {
            int addr2 = varaddr(mid_code2[ mi ].res);
            if ( isglob )
                fprintf(fp_final, "\t\tlw\t$v0\t%d($t9)\n",addr2 -2147479548);
            else
                fprintf(fp_final, "\t\tlw\t$v0\t%d($fp)\n",addr2 );
        }
    }
    fprintf(fp_final, "\t\tj\t__FEND_LAB_%d\n" , funcnum );//跳至结束
}

//para, int, , a //
void paraasm() {
	//printf("paraasm\n");

	int paranum;
	int i;
	int kind ;
    paranum = 0;
    for ( i = mi; i < midcode_num2; i++ ) {
        if ( strcmp(mid_code2[ i ].op, "para") == 0 )
            paranum++;
        else
            break;
    }
    for ( i = 0; i < paranum; i++ ) {
        kind = (strcmp(mid_code2[ mi ].op1, "int") == 0) ? INT : CHAR;
        insertaddress(kind, 4 * ( paranum - i ),-1);
        mi++;
    }
    mi--;
}

void intcharasm() {
	//printf("intcharasm\n");

    if ( isdigit(mid_code2[ mi ].op2[0]) ) {
        pushstack(mid_code2[ mi ].op2,1);
    } else {
        pushstack("0",1);
    }
    if ( strcmp(mid_code2[ mi ].op, "int") == 0 ) {
        insertaddress(INT,-1,-1);
    } else {
        insertaddress(CHAR,-1,-1);
    }
}

void constdefasm() {
	//printf("constdefasm\n");

//printf("const:\n");
    //常量定义
//printf("%s %s %s %s:\n",mid_code2[ mi ].op,mid_code2[ mi ].op1,mid_code2[ mi ].op2,mid_code2[ mi ].res);

    while ( strcmp(mid_code2[ mi ].op, "const") == 0 ) {
//printf("%s %s %s %s:\n",mid_code2[ mi ].op,mid_code2[ mi ].op1,mid_code2[ mi ].op2,mid_code2[ mi ].res);
        pushstack(mid_code2[ mi ].op2,1);
        if ( strcmp(mid_code2[ mi ].op1, "int") == 0 ) {
            insertaddress(INT,-1,-1);
        } else {
            insertaddress(CHAR,-1,-1);
        }
        mi++;
    }
    mi--;
}

void intcharaasm() {
	//printf("intcharaasm\n");

    //数组定义
    while ( strcmp(mid_code2[ mi ].op, "inta") == 0 || strcmp(mid_code2[ mi ].op, "chara") == 0 ) {
        pushstack("0", atoi(mid_code2[ mi ].op2));
        if ( strcmp(mid_code2[ mi ].op, "inta") == 0 ) {
            insertaddress(INT,-1,-1);
        } else {
            insertaddress(CHAR,-1,-1);
        }
        mi++;
    }
    mi--;

}


////////////////////////////////////////////error_deal//////////////////////////////////////

void error(char *name,int line,int error_type)
{
	int errclass=-1;
	errnum ++;
	/*if(mistake==0)
	{
		mistake=1;
		//fclose(fp4);
		//fp4=fopen("siyuanshi.txt","w");
	}*/

	switch(error_type)
	{
        case 1:
            printf("1: %d line , lack；\n",line);
			errclass =
            signal == 0 ? CICVIFIRSP :
            signal == 1 ? IWFRSPIFCV :
            signal == 2 ? IWFLIRSPE :
			signal == 3 ? CS:
			signal == 4 ? ICV:
            -1;
            break;
        case 2:
			errclass = DONOTHING;
            printf("2: no main func\n");
            break;
		case 3:
			errclass = DONOTHING;
            printf("3: something wrong defined at mainfunc \n");
            break;
        case 4:										//OUTOFTABLE?????????????????在哪里出现？？？
            printf("4: %d line, there is no room for symbolTable\n",line);
			errclass = QUIT;
            break;
        case 6:    printf("6: %d line, %s index is illegal/there should have index \n",line,name+1);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? CLR :
            signal == 2 ? IWFRSPIFCV :
            signal == 3 ? IWFLIRSPE :
            signal == 4 ? IWFXXXANE :
            -1;
              break;
        case 7:    printf("7: %d line, function %s is undefined\n",line,name+1);
			 errclass =
			 signal == 0 ? IWFLIRSPE ://在调用语句则找到下一语句
             signal == 1 ? IWFXXXANE ://在表达式的call中找下一语句或者其他
            -1;
               break;

        case 9:    printf("9: %d行, %s index is not defined\n",line,name+1);
			 errclass =
			 signal == 0 ?	IWFLIRSPE:
			 signal == 1 ? IWFXXXANE :
			 -1;
               break;
        case 10:   printf("10: %d line, lack kindSymbol/lack key word\n",line);//????????
				errclass = signal == 0 ? CICVIFIRSP :
				signal == 1 ? CLR :
                signal == 2 ? IWFRSPIFCV :
				-1;
               break;
        case 11:   printf("11: %d line, lack {\n",line);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            -1;
               break;
        case 12:  printf("12: %d line, lack }\n",line);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            -1;
               break;
        case 13:   printf("13: %d line, lack (\n",line);
				errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            signal == 2 ? IWFXXXANE :
			signal == 3 ? CLR:
            -1;
               break;
        case 14:   printf("14: %d line, lack )\n",line);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            signal == 2 ? IWFXXXANE :
            -1;
               break;
        case 15:
				printf("15: %d line，index %s defined again\n",line,name+1);
				errclass = DONOTHING;
               break;
        /*case 16:   printf("16: %d line，lack \"\n",line);
               break;*/
        case 17:   printf("17: %d line, this sentence is illegal/the order of the sentence is wrong\n",line);
				errclass =
				signal == 0 ?  IWFLIRSPE:
				signal == 1 ? IWFXXXANE :
				-1;
               break;
        /*case 18:   printf("18: %d line，const is not assinged\n",line);
               break;*/
        case 19:   printf("19: %d line, left side of the assign statement is not var\n",line);
			errclass =
			signal == 0 ?  IWFLIRSPE:
            signal == 1 ? ICV :
			-1;
               break;
        case 20:   printf("20: %d line, the kind of the assign statment's right is wrong\n",line);
				errclass = CICVIFIRSP;
               break;
        case 21: printf("21: %d line, there should be ‘=’\n",line);
			errclass =
			signal == 0 ?  IWFLIRSPE:
            signal == 1 ? ICV :
			-1;
               break;
        case 22: printf("22: %d line, %s can't be void \n",line,name+1);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            signal == 2 ? IWFXXXANE :
            -1;
		     break;
        case 23:    printf("23: %d line, %s the kind of the index is wrong\n",line,name+1);
			errclass =
			signal == 0 ?  IWFLIRSPE:
            signal == 1 ? ICV :
			-1;
               break;
        case 24: printf("24: %d line, the parameters' number is wrong\n",line);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            signal == 2 ? IWFXXXANE :
            -1;
		     break;
		case 25: printf("25: %d line, the kind of parameters is not match \n",line);
			errclass =
            signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
            signal == 2 ? IWFXXXANE :
            -1;
		     break;
        case 26: printf("26: %d line , func %s don't have return stat\n",line,name+1);
			errclass =
			signal == 0 ? ICV :
            signal == 1 ? IWFLIRSPE :
			-1;
		     break;
	   /*case 27:printf("%d行, 赋值符号两边类型不匹配\n",line);
			 break;*/
	   case 28:printf("28: %d line, there is no number inside of the array/something wrong when define the array\n",line);
			 errclass = IWFRSPIFCV;
			 break;
	   /*case 29:printf("%d行, 此处应为：\n",line);
			 break;
	   case 30:printf("%d行, 此处应为整数\n",line);
			 break;
	   case 31:printf("%d行, 不允许在子函数中定义函数\n",line);
			 break;*/
	   case 32:printf("32: %d line, there lack case\n",line);
			errclass =
			signal == 0 ?  IWFLIRSPE:
            signal == 1 ? ICV :
			-1;
			 break;
	   /*case 33:printf("%d行, 此处数组越界\n",line);
			 break;
		case 34:printf("%d行, 缺少[\n",line);
			 break;*/
		case 35:printf("35: %d line , lack ]\n",line);
			errclass =
			signal == 0 ?  IWFLIRSPE:
            signal == 1 ? ICV :
			signal == 2 ? IWFXXXANE:
			-1;
		     break;
		/*case 36:printf("36: %d line,  lack \n",line);//DOUBLEQUOTESLACK
			errclass = DONOTHING;
			break;*/
		case 37:printf("37:%d line,  the symbol is not accepted \n",line);//UNACCEPTATLECHAR
			errclass = DONOTHING;
			break;
		case 38:printf("38: %d line ,  lack'\n",line);//SINGLEQUOTESLACK
			errclass = DONOTHING;
			break;
		case 39:printf("39: %d line,  the define of const failed\n",line);//CSTDEFINEFAIL
			errclass = CICVIFIRSP;
			break;
		case 40:printf("40: %d line,  the array is overflip\n",line);//CSTDEFINEFAIL
			errclass = DONOTHING;
			break;
		default:
            break;
   /* case 32: fprintf(stdout,"%d行, 应有‘=’\n",line,name);
		     break;
	 case 32: fprintf(stdout,"%d行, 应有‘=’\n",line,name);
		     break;*/
	}
	switch ( errclass ){
        case QUIT:
            system("pause");
            exit(0);
            break;
        case DONOTHING:
            break;
        case ICV://跳到下一个类型声明符号int/char/void
            while ( strcmp(WORD_tag[count] ,"INTTK" )&& strcmp(WORD_tag[count] , "CHARTK")&& strcmp(WORD_tag[count], "VOIDTK" )) {
                count++;
            }
            break;
        case CICVIFIRSP://跳到下一个以下集合的元素{ CONSTTK INTTK CHARTK VOIDTK IFTK WHILETK FORTK IDEN RETURNTK SCANFTK PRINTFTK}
            while ( strcmp(WORD_tag[count]  ,"CONSTTK") && strcmp(WORD_tag[count]  ,"INTTK") && strcmp(WORD_tag[count]  ,"CHARTK") && strcmp(WORD_tag[count]  ,"VOIDTK")&& strcmp(WORD_tag[count]  ,"IFTK") && strcmp(WORD_tag[count]  ,"DOTK")
                && strcmp(WORD_tag[count]  ,"SWITCHTK") && strcmp(WORD_tag[count]  ,"IDEN") && strcmp(WORD_tag[count]  ,"RETURNTK") && strcmp(WORD_tag[count]  ,"SCANFTK")&& strcmp(WORD_tag[count]  ,"PRINTFTK")){
                count++;
            }
            break;
        case CS://跳到下一个逗号或者分号
            while ( strcmp(WORD_tag[count]  ,"COMMA ")&& strcmp(WORD_tag[count]  ,"SEMCON") ) {
                count++;
            }
            break;
        case CLR://跳到下一个逗号或者括号
            while ( strcmp(WORD_tag[count]  ,"COMMA") && strcmp(WORD_tag[count]  ,"LPARENT") && strcmp(WORD_tag[count]  ,"RPARENT") ) {
                count++;
            }
            break;
        case IWFRSPIFCV://跳到下一个语句列的FIRST集合元素之一
            while ( strcmp(WORD_tag[count]  ,"IFTK")&& strcmp(WORD_tag[count]  ,"DOTK") && strcmp(WORD_tag[count]  ,"SWITCHTK") &&strcmp( WORD_tag[count]  ,"RETURNTK")&& strcmp(WORD_tag[count]  ,"SCANFTK")
                &&strcmp( WORD_tag[count]  ,"PRINTFTK")&& strcmp(WORD_tag[count]  ,"INTTK") && strcmp(WORD_tag[count]  ,"CHARTK") && strcmp(WORD_tag[count]  ,"VOIDTK")) {
                count++;
            }
            break;
        case IWFLIRSPE://跳到下一个以下集合的元素：{IFTK WHILETK FORTK LBRACK IDEN RETURNTK SCANFTK PRINTFTK ELSETK RBRACE}
            while ( strcmp(WORD_tag[count]  ,"IFTK") &&strcmp( WORD_tag[count]  ,"DOTK")&& strcmp(WORD_tag[count]  ,"SWITCHTK") && strcmp(WORD_tag[count]  ,"IDEN")
                && strcmp(WORD_tag[count]  ,"RETURNTK") && strcmp(WORD_tag[count]  ,"SCANFTK")&& strcmp(WORD_tag[count]  ,"PRINTFTK ") &&strcmp( WORD_tag[count]  ,"RBRACE")) {
                //printf("find }\n");
				count++;
            }
            break;
        case IWFXXXANE://跳到下一个以下集合的元素：{ IFTK WHILETK FORTK LBRACK IDEN RETURNTK SCANFTK PRINTFTK  SEMCON ELSETK RPARENT COMMA PLUS MINU MULT DIV LSS LEQ GRE GEQ NEQ EQL}
            while ( strcmp(WORD_tag[count]  ,"IFTK")&& strcmp(WORD_tag[count]  ,"DOTK") && strcmp(WORD_tag[count]  ,"SWITCHTK") && strcmp(WORD_tag[count]  ,"IDEN") && strcmp(WORD_tag[count]  ,"RETURNTK")
                && strcmp(WORD_tag[count]  ,"SCANFTK") && strcmp(WORD_tag[count]  ,"PRINTFTK")&& strcmp(WORD_tag[count]  ,"SEMCON")&& strcmp(WORD_tag[count]  ,"RPARENT")
                &&strcmp( WORD_tag[count]  ,"COMMA") && strcmp(WORD_tag[count]  ,"PLUS") && strcmp(WORD_tag[count]  ,"MINU")&& strcmp(WORD_tag[count]  ,"MULT") && strcmp(WORD_tag[count]  ,"DIV")
                &&strcmp( WORD_tag[count]  ,"LSS") && strcmp(WORD_tag[count]  ,"LEQ")&& strcmp(WORD_tag[count]  ,"GRE")&& strcmp(WORD_tag[count]  ,"GEQ")&& strcmp(WORD_tag[count]  ,"NEQ")&&strcmp( WORD_tag[count] , "EQL") ) {
                count++;
            }
            break;
		/*case -1:
			while(WORD_tag[count] !=  SEMCON){
				count++;
			}
			break;*/
        default:
            break;
    }

	//if(pword==NULL)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!找到整个结束时的结束符
    //exit(0);

}


/////////////////////////////////////////////main////////////////////////////////

int main()
{
//printf("begin!!\n");
    char filename[100];
	FILE *fp2;
	int number,i;
	//printf("please input file path:\n");
	printf("Please input the file name:\n");
    scanf("%s",filename);
    //strcpy(filename,"new.txt");
    number = token(filename,WORD_tag,WORD);
	fp2 = fopen("cifafenxi2.txt","w");
	fp4=fopen("15141059_yuxinyi_beforeSiyuanshi.txt","w");
	fp_error=fopen("errorrecord2.txt","w");
	//fp3=fopen("yufafenxi.txt","w");
	fp_final=fopen("1514059_yuxinyi_afterMubiao.txt","w");

	//进行词法分析结果在cifafenxi.txt
	for(i=1;i<number;i++)
	{
		fprintf(fp2,"%d %s %s\n",i,WORD_tag[i],WORD[i]);
	}
    fclose(fp2);

    i=errorcount;

	//进行语法语义以及生成四元式，四元式结果存在siyuanshi.txt里
    printf("begin cifafenxi&siyuanshi\n");
	cifanalys();



	//开始四元式的优化
	printf("begin optimieze\n");
	scan();
	printOptimize();//存储优化后的四元式到optMidCode.txt
	fclose(fp_error);

	//开始汇编指令生成
	printf("begin assembly\n");
    assembly();
	fclose(fp_final);


}
