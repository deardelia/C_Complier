
#include<stdio.h>
#include<string.h>
#include "yufafenxi3.h"

char WORD[10000][500];
char WORD_tag[10000][10];
int column[10000];
int word_number;
int intNum;//���ַ���תΪ���ֵ�����
int count;//������������¼��ǰ�������ĸ�����
int tablecount=1;//���ű���Ԫ�صĸ���
//int levelvarcount[MAXLEV];
int instructnum=0;//ָ����
//int errorplace[MAXERROR];//��¼�������ڵ�����
//int errorecord[MAXERROR];//��¼����
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
int mi = 0;    //��Ԫʽ���������
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
//symboltable Charbox[MAXTABLE];			//���ű�
//mid_opera  operation[MAXOP];

int token(char *fname,char wordTag[][10],char wordRecord[][500]);



int token(char *fname,char wordTag[][10],char wordRecord[][500])//ok
{
    char key[50][30];//�ķ��ؼ�������
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

    char keyTag[50][30];//����ķ��йؼ��ֵ������
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

    //���ļ�
    FILE *fp;
    char ch;
    char temp[200];//��������ĵ���
    char buffer[20000];//�ļ�������
    int num,k,j,i=0;//numΪ����Ĵʷ������ļ�������,i��¼�����ļ���j��¼��ǰ���ʵĵڼ����ַ�
	int n,m;
    int ii,jj,kk,ll,mm,nn;//��ѭ���ж�ʵ�͡����� ��
    int linenum=1;//�кų�ʼֵΪ1

    mistake=0;
    num=1;
    if((fp=fopen(fname,"r"))==NULL)
    {
        printf("Error! File not exist!\n");
        scanf("%c",&temp[0]);

    }

    //���ļ�����buffer��
    ch = fgetc(fp);
    while(ch!=EOF)
    {
        buffer[i++]=ch;
        ch = fgetc(fp);
    }
    buffer[i]='\0';

    n=i;
    i=0;
    while(i<n)//���ַ���
    {
        //�ո� ���� �Ʊ�������������һ��
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

        //�ؼ��ֻ��߱�ʶ��
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

            for(k=0;k<15;k++)//�ж��Ƿ�Ϊ15���ؼ����е�
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

            if(k==15)//������ǹؼ��֣����Ǳ�ʶ��
            {
                column[num]=linenum;//columnΪ��ǰ�������еļ�¼
                strcpy(&wordTag[num][0],"IDEN");
                strcpy(&wordRecord[num][0],&temp[0]);
                num++;
            }
        }

        //�����ͳ���
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
        //�ַ�����
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

        //�ַ�������
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

            /*if(buffer[i]=='\0')//���ĵ�ĩβ�ˣ���Ϊ�����ַ�����DQMARK
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
            if(buffer[i]!='\0')//���ַ���
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
            /*else if((kk==29)&&(buffer[i]!='\0'))//�����ַ�����DQMARK
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

		//�ǱȽϷ��������������������
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

    //������������const����ʼ���ó�����������������
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

    //���������Լ�������ֵ�ĺ���,(����int��char��ͷ��Ҫô�Ǳ����������壬Ҫô�Ǻ����Ķ���)
    while((!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))))
    {   //����int��char���ȡ��һ����
        if(!(strcmp(WORD_tag[count],"INTTK"))){
            record= 11;
        }
        else{
            record= 12;
        }
        count=count+1;
        //�Ǳ�ʶ����������һ��
        if(!(strcmp(WORD_tag[count],"IDEN"))){
            count=count+1;
            //������,;[,�����(�����Ŵ�����)
            if( (strcmp(WORD_tag[count],"COMMA"))
               &&(strcmp(WORD_tag[count],"SEMCON"))
               &&(strcmp(WORD_tag[count],"LPARENT"))
               &&(strcmp(WORD_tag[count],"LBRACK")))
            {
                printf("error:vardecl!\n");
				signal=3;//������һ���ֺŻ��߶���
                error(WORD[count],column[count],1);
            }
            //����,;[����һ���ǣ���������
            if((!strcmp(WORD_tag[count],"COMMA"))
               ||(!strcmp(WORD_tag[count],"SEMCON"))
               ||(!strcmp(WORD_tag[count],"LBRACK")))
            {
                count=count+1;
                //���ñ�����������
				//printf("%s",WORD[count]);
                if(vardef(record)){
                    printf("error:vardef!\n");
                }
                else{
                    if(!(strcmp(WORD_tag[count],"LPARENT"))){
                        count=count-2;
                    }
                    //printf("vardef success!\n");//��ʱcountΪ�������һ��
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
            error(WORD[count],column[count],6);//������һ��int��char��void
        }

    }

    //��void��Ϊ�޷���ֵ�����Ķ���
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
				signal=0;//�ҵ���һ��void char ��int�ĵط�
				error(WORD[count],column[count],6);
			}*/
        }

    }
    mainfunc();
    //printf("this is end of cifafenxi!!\n");

}

int constdecl()//ok��ȷ����0...
{
    //printf("This is a const declaration��\n");
    int typerecord;
    //���const����int char
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
			error(WORD[count],column[count],10);//�ҵ���һ����const int char void��ָʾ���ķ���
			return 1;
		}
        //���ó����������ɹ�����(����0)
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
            error(WORD[count],column[count],1);//�ҵ���һ��int char void ��������������俪ͷ������
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
    //printf("This is a const define��\n");
    PMean pm=(PMean)malloc(sizeof(Mean));//PMean������ű���ָ��
	char s[20];
    strcpy(pm->name,WORD[count]);
    if(!(strcmp(WORD_tag[count],"IDEN")))
    {
        count=count+1;
        pm->kind=4;//���ű��ڼ�¼������Ϊ4
        if(!(strcmp(WORD_tag[count],"ASSIGN")))
        {
            count=count+1;
            //���ֱ�������������ַ�
            if(((!(strcmp(WORD_tag[count],"INTCON")))&&(type==11))//ͨ������type�ж�=���������Ƿ�ƥ��
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
                //��ʱcount�������Ӧ��Ϊ���Ż�ֺţ����Ƕ��ţ����ٵ��ñ������庯��
                if(!(strcmp(WORD_tag[count],"COMMA")))
                {
                    count=count+1;
                    return(constdef(type));
                }
                else if(!(strcmp(WORD_tag[count],"SEMCON")))
                    return 0;
            }
            //������==������Ƿ��ţ������ж�count+1�Ƿ�Ϊ������
            else if(((!(strcmp(WORD_tag[count+1],"INTCON")))&&(type==11))
                && ((!(strcmp(WORD_tag[count],"MINU")))
                ||  (!(strcmp(WORD_tag[count],"PLUS")))))
            {

                type = 11;
                //��ȡ�ַ�����ʱcountָ���ӦΪ���Ż�ֺ�
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
            //����"���������ͺ�ֵ�����Ͳ�ƥ��",
            else
            {
                error(WORD[count],column[count],20);
                return 1;
            }
        }
        //�����ʾ������ȱ��=
        else
        {
            error(WORD[count],column[count],20);
            return 1;
        }
    }
    //����ȱ�ٱ�ʾ��
    else
    {
        error(WORD[count],column[count],39);
        return 1;
    }
    return 0;
}

int vardef(int type){//ok  �������������������...
    //printf("This is a var define��\n");
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
	char s[20];
    //��֮ǰ�Ƕ��Ż�ֺ�
//printf("%s",WORD[count]);
    if((!(strcmp(WORD_tag[count-1],"COMMA")))||(!(strcmp(WORD_tag[count-1],"SEMCON")))){
        //�����Ż�ֺ�֮ǰ�ı���������ű�

        strcpy(pm->name,WORD[count-2]);
        pm->kind=0;
        pm->type=type;
        insert(pm);
		if(pm->type==11)
			generate("int","  ","  ",pm->name);
		else if(pm->type==12)
			generate("char","  ","  ",pm->name);
    }
    //��֮ǰ���������ţ���������
    else if(!(strcmp(WORD_tag[count-1],"LBRACK"))){
        //��������Ϊ�޷�����������һ�����������ţ�������ű�
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
        //�������鶨�����
        else{
            error(WORD[count],column[count],28);//������һ��int void char��������俪ͷ�ĵط�(��ʶ����ͷ��������)
            return 1;
        }
    }

    //���Ƕ���
    if( (!(strcmp(WORD_tag[count-1],"COMMA")))){
        //������֮���Ǳ�ʶ��
       // printf("%s\n",WORD_tag[count-1]);
        if((!(strcmp(WORD_tag[count],"IDEN")))){
            count=count+2;
            return (vardef(type));
        }
        //����֮���Ǳ�ʶ�������
        else{
			signal=2;
            error(WORD[count],column[count],6);
			return 1;
        }
    }
    //���Ƿֺ�
    if( (!(strcmp(WORD_tag[count-1],"SEMCON"))) ){
        //�ֺŹ�����int��char��������µı���������ʼ��
        if((!(strcmp(WORD_tag[count],"INTTK")))||(!(strcmp(WORD_tag[count],"CHARTK"))) ){
            if(!(strcmp(WORD_tag[count],"INTTK"))){
                record=11;
            }
            else
                record=12;
            count=count+1;
            //��int��char�����Ǳ�ʶ��
            if(!(strcmp(WORD_tag[count],"IDEN"))){
                count=count+1;
                if( (strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK")) &&(strcmp(WORD_tag[count],"LPARENT"))){
                    signal=1;//������һ�����Ż�������
					error(WORD[count],column[count],1);
                    return 1;
                }
                if(!(strcmp(WORD_tag[count],"LPARENT"))){
                    return 0;
                }
                //���Ǳ�ʶ�������Ƕ��ŷֺŻ��������ţ�����ñ�����������
                if( (!(strcmp(WORD_tag[count],"COMMA")))||(!(strcmp(WORD_tag[count],"SEMCON")))||(!(strcmp(WORD_tag[count],"LBRACK"))) ){//����Ƕ��Ż��߷ֺŻ�����������
                    count++;
                    if(vardef(record))
                        return 1;//vardefine����Ļ� return 1
                }
            }
            //int��char���治�Ǳ�ʶ���򱨴�
            else{
				signal = 2;
                error(WORD[count],column[count],6);
				return 1;
            }
        }
        //�ֺź��治��int��char�������һ�ֵı��������Ѿ�����
        else
            return 0;
    }
    //�����������Ŷ��Ż�ֺ��򱨴�
    else{
		return 1;
    }
    return 0;
}

int funcpara(PMean pm0){//ok �����Ĳ�����...
   //printf("This is a parameterlist of function��\n");
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
            //������������ʽ����������ű�
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
			signal=1;//�ҵ���һ�����Ż�������(���Ҿ���)
            error(WORD[count],column[count],6);
			if(!(strcmp(WORD_tag[count],"COMMA"))){
				count=count+1;
				continue;
			}
			else
				return num;//
        }
        //����ʶ�����Ƕ��ţ����˳�ѭ����������������ʽ�����������
        if(strcmp(WORD_tag[count],"COMMA")){
            break;
        }
        //���Ƕ�����������·���
        else
            count=count+1;
        //������int��char�����

    }
    return num;

}


void returnfunc(int type){//ok...
//printf("This is a return fucntion��\n");
    int record;
    PMean pm=(PMean)malloc(sizeof(Mean));
	PMean pm0=(PMean)malloc(sizeof(Mean));

    already_ret=0;
	if(type==11)
		generate("declare","int","  ",WORD[count-1]);//�����Ӻ���WORD[count-2]:����������
	else if(type==12)
		generate("declare","char","  ",WORD[count-1]);

    if(!(strcmp(WORD_tag[count],"LPARENT")))
        count++;
    else{
		signal=0;//������һ��������������int/char/void
        error(WORD[count],column[count],13);
		return;//����return�����൱�������������������
	}

    //����ű�
    pm->kind=2;//2����int/var�͵��з���ֵ������ͬ�� .type=11
    pm->type=type;

    strcpy(pm->name,WORD[count-2]);

    setCurFunc(pm);//�ı䵱ǰ���ڲ�����hang++!!���Ұ�lie��Ϊ1�Ѿ������µ�һ��
	setAttribute(pm0,pm);
	pm->number=funcpara(pm);//���������
//printf("funcparaType:%d",pm->funcparaType[0]);
    insert_all(pm);//�½��Ӻ������ű���0�������


    //�������������������ԣ�������Ĳ��������
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count=count+1;
        //����{
        if(!(strcmp(WORD_tag[count],"LBRACE"))){
            count=count+1;
            //��ʼ�ӳ���ı�������
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
                if(!(strcmp(WORD_tag[count],"IDEN"))){//!!!!!�����INDEN����Ҫ
                    count++;
                    if((strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK"))){
                        signal=4;//����char int void�ĵط�
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
								error(WORD[count],column[count],31);//���������Ӻ����ж��庯��
						}*/
                    }
                }
                else{
					signal=0;//����char int void�ĵط�
                    error(WORD[count],column[count],6);
					return;
                }
            }
            //���븴��������Ǳ���ģ�
            statementList(pm);//��������з�������
            if(already_ret==0){ //�������������return������alread_ret���0��Ϊ1�������ַ���ֵ�ĺ���ȱ�ٷ������
                signal=0;
				error(WORD[count],column[count],26);//����char int void�ĵط�
				return;
			}
        }
        else{//ȱ��{errclass = ICV;
			signal=0;
            error(WORD[count],column[count],11);
			return;
        }

        if(!(strcmp(WORD_tag[count],"RBRACE")))//��ʾ��ǰ�ĺ����������
            count++;
        else//����ȱ��}����errclass = ICV;
		{
			signal = 0;
			error(WORD[count],column[count],12);
			return;
		}


    }
    else{//������������ʱ��ȱ�������ű���
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
//printf("This is void function��\n");

    already_ret=1;


	generate("declare","void","  ",WORD[count-1]);//�����Ӻ���WORD[count-2]:����������

    if(!(strcmp(WORD_tag[count],"LPARENT"))){
        count++;
    }
    else{
		signal=0;
        error(WORD[count],column[count],13);
		return;
	}

    pm->kind=1;//1�����޷���ֵ������ͬ�� .type=12
    strcpy(pm->name,WORD[count-2]);

    setCurFunc(pm);
	setAttribute(pm0,pm);
	pm->number=funcpara(pm);//
    insert_all(pm);//�½��Ӻ������ű�


    //��������������������
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count=count+1;
        //����{
        if(!(strcmp(WORD_tag[count],"LBRACE"))){
            count=count+1;
            //currentlev++;//��������µ�һ��
            //��ʼ�ӳ���ı�������
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
                if(!(strcmp(WORD_tag[count],"IDEN"))){//!!!!!�����INDEN����Ҫ
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
								error(WORD[count],column[count],31);//���������Ӻ����ж��庯��
						}*/
                    }
                }
                else{
					signal=0;
                    error(WORD[count],column[count],6);
					return;
                }
            }
            //���븴�����

            statementList(pm);//��������з�������
            if(already_ret==0){ //�޷���ֵ���������з������
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

        if(!(strcmp(WORD_tag[count],"RBRACE")))//��ʾ��ǰ�ĺ����������
            count++;
        else{//����ȱ��}����
			signal=0;
            error(WORD[count],column[count],12);
			return;
		}

    }
    else{//������������ʱ��ȱ�������ű���
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
		signal = 3 ;//������һ�����Ż�������
        error(WORD[count],column[count],13);
	}
    else
        count=count+1;
    if(!(strcmp(WORD_tag[count],"RPARENT"))){
        count=count+1;
        //����{
        if(!(strcmp(WORD_tag[count],"LBRACE"))){
            count=count+1;
            //currentlev++;//��������µ�һ��
            //��ʼ�ӳ���ı�������
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
                if(!(strcmp(WORD_tag[count],"IDEN"))){//!!!!!�����INDEN����Ҫ
                    count++;
                    if((strcmp(WORD_tag[count],"COMMA"))&&(strcmp(WORD_tag[count],"SEMCON"))&&(strcmp(WORD_tag[count],"LBRACK"))){
                        signal=3;//������һ���ֺŻ򶺺�
						error(WORD[count],column[count],1);
                    }
                    if( (!(strcmp(WORD_tag[count],"COMMA")))||(!(strcmp(WORD_tag[count],"SEMCON")))||(!(strcmp(WORD_tag[count],"LBRACK"))) ){
                        count++;
                        if(vardef(record)){
                            printf("error!!!:vardef wrong!!!\n");
                        }
						/*else{
							if(!(strcmp(WORD_tag[count],"LPARENT")))
								error(WORD[count],column[count],31);//���������Ӻ����ж��庯��
						}*/
                    }
                }
                else{
					signal=3;
                    error(WORD[count],column[count],6);
                }
            }
            //���븴�����
            /*if(gen(9,0,numoflev[currentlev]))//?????????????????????????����һ������ָ��
                return 1;*/
            statementList(pm);//��������з�������
            if(already_ret==0){ //�޷���ֵ���������з������
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

        if(!(strcmp(WORD_tag[count],"RBRACE")))//��ʾ��ǰ�ĺ����������
            count++;
        else{//����ȱ��}����
			signal=-1;
            error(WORD[count],column[count],12);
			return;
		}

    }
    else{//������������ʱ��ȱ�������ű���
		signal=-1;
	    error(WORD[count],column[count],14);
		return;
	}

    generate("endp","main","  ","  ");

}

void setCurFunc(PMean pm){//ok���Ӻ�������ʱʹ�ã�ʱhang++�������������һ��

    if(hang==Max_Table_hang){//ȷ��û�г������ű�������
		error(NULL,0,4);
	    return;
	}
	lie=1;
	hang++;
//all_line?????????//��setFunc.C
	strcpy(table[hang][0].name,pm->name);//pm->name�Ǻ���������
    table[hang][0].kind=pm->kind;
    table[hang][0].type=pm->type;

}

int statementList(PMean pm){//ok...
    //printf("This is a statement list��\n");
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

int statement(PMean pm){//ok!!!!!ע��ֺ�...
	PMean pm2=(PMean)malloc(sizeof(Mean));//�����ڵı��ʽ

    int a;
    //printf("This is a statement��\n");
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
    //�ǷֺŴ���ǰ����������
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
        if (strcmp(WORD_tag[count],"RBRACE")){//������з���������һ����Ž�β�򱨴�
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

int callpara(PMean pm1, int recordType[MAXPARANUM]) //ok //���غ�������ʱʵ��������...
{
    int num=1;
    PMean pm=(PMean)malloc(sizeof(Mean));
//printf("This is a parameter of call��\n");
    if(!(strcmp(WORD_tag[count],"RPARENT")))
        return 0;//������ʵ��
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

void call(PMean pm){//ok����ʱcountΪ)��һ���ַ�...
    int num=0;
	int currentrecord[MAXPARANUM];
//printf("This is call state��\n");
    count++;

    if(!(strcmp(WORD_tag[count-2],"IDEN"))){
       strcpy(pm->name,WORD[count-2]);//pm->name�洢����������
       if(!lookup_all(pm))  //�ڷ��ű�麯����
	   {
		   signal=0;//�ҵ���һ���Ŀ�ͷ
           error(WORD[count-2],column[count-2],7); //����δ����
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

    if(!checkParaNum(pm->name,num)){//�����������Ƿ���ȷ
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
	if(!checkParaType(pm->name,num,currentrecord)){//�����������Ƿ���β�ƥ��
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

//����һ�ָ�����Ԫ�ظ�ֵ�����!!!!!!
void assignstat(){//ok...
    int line1,kind;
    PMean pm=(PMean)malloc(sizeof(Mean)); //���ʽ��ı�ʾ��
    PMean pm1=(PMean)malloc(sizeof(Mean)); //���ʽ
    PMean pm2=(PMean)malloc(sizeof(Mean)); //�����±���ʽ

//printf("This is a assign stat��\n");
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


    //�ͱ�����kindһ��
    line1=column[count-1];

    if(!lookup(pm)&&!lookup_all(pm)){  //����ʶ���Ƿ��Ѿ�����
		signal=0;
        error(WORD[count-1],column[count-1],9);
		return;
	}

	/*if(pm->kind==3){
		if(pm->shuzuflag>pm->number){
			error(WORD[count-1],column[count-1],33);//����Խ��
		}
	}*/

	kind=lookup_kind(pm);//0:1;
	//printf("%d\n",kind);

    if((kind!=0)&&(kind!=5)&&(kind!=3))//�����ʽ��ߵ����Ͳ��Ǳ������߲���
     {
		 signal =0;
         error(WORD[count-1],column[count-1],19);
		 return;
     }
    count++;
//printf("assign %s\n",WORD[count]);
    expression(pm1);//���Ǹ�ֵ�����ұ�
    //printf("assign %s\n",WORD[count-1]);
	if(kind!=3)
		generate("=",pm1->name,"  ",pm->name);
	else
		generate("[]=",pm->name,s,pm1->name);//pm->name[s]=pm1->name
	//printf("assign end\n");
}

void ifstat(PMean pm){//ok...
    PMean pm0=(PMean)malloc(sizeof(Mean));
    PMean pm1=(PMean)malloc(sizeof(Mean)); //���ʽ1
    PMean pm2=(PMean)malloc(sizeof(Mean));//���ʽ2
    char if_label[20];
    char s[20];//???????????
//printf("This is a if state��\n");
    strcpy(if_label,new_label());//����һ����ǩ(��ʾ��ת

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

        else{//ֻ�б��ʽ�����
            if(strcmp(WORD_tag[count],"RPARENT")){
				signal = 1;
                error(WORD[count],column[count],14);
				return;
            }
            count=count+1;
            generate("!=",pm1->name,"0","  ");
        }
		generate("jne", "  ", "  ", if_label);  //�Ƚϣ�Ϊ�ٵ�ʱ����ת
        statement(pm);
		generate("lab:", "  ", "  ", if_label);
    }
}


void dowhilestat(){//ok mistake???????...
    PMean pm0=(PMean)malloc(sizeof(Mean));
    PMean pm1=(PMean)malloc(sizeof(Mean)); //���ʽ1
    PMean pm2=(PMean)malloc(sizeof(Mean));//���ʽ2
    char label_1[20];
    char label_2[20];
    char s[20];
//printf("This is a dowhile stat��\n");
    strcpy(label_1,new_label());
    strcpy(label_2,new_label());
//printf("%s\n",WORD_tag[count]);

	generate("lab:","  ","  ",label_1);//��do�ĵط�����һ����ת�ı�ǩ

    count++;

    statement(pm0);//do֮��ֱ�ӽ������
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
                if(mistake==0)//!!!!!!!!!!!!!!!!!!!!mistake�Ķ���
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
//printf("This is switchcase stat��\n");
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

    setAttribute(pm,pm0);//���ʽ��ֵ����pm��
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


void scanfstat(){//ok...  ע������û���ж�����Ƿ�Ϊ����β
    PMean pm=(PMean)malloc(sizeof(Mean));
    int kind;
    int done=0;
//("This is scanf stat��\n");
    count=count+1;
    if(!(strcmp(WORD_tag[count],"LPARENT"))){
        count=count+1;

        if(!(strcmp(WORD_tag[count],"IDEN"))){
            strcpy(pm->name,WORD[count]);
            if(!lookup(pm)&&!lookup_all(pm)){// ����Ƿ��ڷ��ű� ���ڱ���
                signal=0;
				error(WORD[count],column[count],9);
				return;
            }

            kind=lookup_kind(pm);
            if(kind==4||kind==1||kind==2||kind==6||kind==3)//��ʶ�����Ϳ����ǲ������߱�����Ϊ0��5
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
            if(!lookup(pm)&&!lookup_all(pm)){// ����Ƿ��ڷ��ű� ���ڱ���
                signal=0;
				error(WORD[count],column[count],9);
				return;
            }

            kind=lookup_kind(pm);
            if(kind==4||kind==1||kind==2||kind==6){//��ʶ�����Ϳ����ǲ������߱�����Ϊ0��5
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
//printf("This is print stat��\n");
    if(!(strcmp(WORD_tag[++count],"LPARENT"))){
        count++;
        if(!(strcmp(WORD_tag[count],"STRCON"))){//���ַ������ַ���+���ʽ
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
        else{//�Ǳ��ʽ
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

//printf("This is a return stat��\n");
    if((strcmp(WORD_tag[count],"SEMCON"))){//�����Ƿֺţ���˵���Ǵ����ŵķ��غ���
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
//printf("This is expression��\n");
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
        setAttribute(pm1,pm);//��pm����Ϣ��pm1
    }

    while((!(strcmp(WORD_tag[count],"PLUS")))||(!(strcmp(WORD_tag[count],"MINU")))){
        //printf("%s\n",WORD_tag[count]);
        char old[20];
		factclass = INT;
        if(!(strcmp(WORD_tag[count],"PLUS"))){
            pm1->type=22;//�����ʱ��+
        }
        else
            pm1->type=23;//�����ʱ��-
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
//printf("This is term��\n");
    factor(pm);
    setAttribute(pm1,pm);//��pm����Ϣ��pm1��pm�洢����Ϣ������

	while((!(strcmp(WORD_tag[count],"MULT")))||(!(strcmp(WORD_tag[count],"DIV"))))//�����
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
        strcpy(pm1->name,get_temp());//��ʱpm1->nameΪTemp%d(dΪ����)

        if(pm1->kind==24)
            generate("*",old,pm->name,pm1->name);
        else
            generate("/",old,pm->name,pm1->name);
    }
    //printf("factorterm%s\n",WORD_tag[count]);

}

void factor(PMean pm1){//!!!!����Ĵ���ok...
    PMean pm=(PMean)malloc(sizeof(Mean));
    PMean pm2=(PMean)malloc(sizeof(Mean));//�����ڵı��ʽ
	char place3[30];
//printf("This is factor��\n");
//printf("assign %s\n",WORD[count]);
    if(!(strcmp(WORD_tag[count],"IDEN"))){//�����Ǳ�ʶ�������з���ֵ�ĺ�������
        count++;
        if((strcmp(WORD_tag[count],"LPARENT"))&&(strcmp(WORD_tag[count],"LBRACK")))//�Ǳ�ʶ��
        {
           strcpy(pm1->name,WORD[count-1]);//�ѱ�ʶ�������ָ�pm1
           //!!!!!!!!!!!!!ע������lookup����Ҫ֪��pm1->type��11����12���鿴�����õ�lookupϵ�к����ĵط���������������
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

        else if(!(strcmp(WORD_tag[count],"LPARENT"))){//��������
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
            strcpy(pm1->name,place3);//��pm��name��ʵ���Ǻ������Ƽ���ʶ������pm1
            pm1->kind=2;//�������з���ֵ�ĺ���
        }
        else{//�����飡��������������������������
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

    else if(!(strcmp(WORD_tag[count],"LPARENT"))){//�Ǳ��ʽ�����ʽ��
        count++;
        expression(pm);
        setAttribute(pm1,pm);//��pm����Ϣ������pm1
        if(!(strcmp(WORD_tag[count],"RPARENT"))){
            count++;
        }
        else{
			signal=2;
            error(WORD[count],column[count],14);
			return;
        }
    }

    else if(!(strcmp(WORD_tag[count],"MINU"))){//������
        count=count+1;
        pm1->number = -transint(WORD[count]);
		sprintf(pm1->name,"%d",transint(WORD[count])*(-1));
        if((!strcmp(WORD_tag[count],"INTCON"))){//��֤���޷�������
            pm1->kind=0;
            pm1->type=11;
        }
        else
            pm1->kind=6;
        count=count+1;
    }

    else if(!(strcmp(WORD_tag[count],"PLUS"))){//������
        count=count+1;
        pm1->number = transint(WORD[count]);
		strcpy(pm1->name,WORD[count]);
        if((!strcmp(WORD_tag[count],"INTCON"))){//��֤���޷�������
            pm1->kind=0;
            pm1->type=11;
        }
        else
            pm1->kind=6;
        count=count+1;
    }

    else if(!(strcmp(WORD_tag[count],"INTCON"))){//����
        pm1->number=transint(WORD[count]);
        strcpy(pm1->name,WORD[count]);
        if((!strcmp(WORD_tag[count],"INTCON"))){//��֤���޷�������
            pm1->kind=0;
            pm1->type=11;
        }
        else
            pm1->kind=6;//chucuo
        count=count+1;
    }

    else if(!(strcmp(WORD_tag[count],"CHARCON"))){//�ַ�����ת�������Ӧ��ascal��󵱳���������
		if ( factclass != INT ) {
            factclass = CHAR;
        }
	   //printf("fegeg\n");
        pm1->number=transint(WORD[count]);//!!!!!!�Ƿ�ΪWORD[count][0]����������
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
    if(lookup(p))//�ظ�����
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

int lookup_kind(PMean p)//ok ��������
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
    while(i<all_lie){ //��ȫ�ֲ���
        if(strcmp(table[0][i].name,p->name)==0){
            return table[0][i].kind;
        }
        i++;
    }
    return -1;
}

int lookup_type(PMean p)//ok ��������
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
    while(i<all_lie){ //��ȫ�ֲ���
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
        table[0][all_lie].number=p->number;    //������������
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
    while(i<all_lie){ //0����
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
    while(i<lie){//�ڵ�ǰ����
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
            //else{//�����ʶ��������ͬ�������Ͳ�ͬ
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
		if(op[0]=='L'){//L��ͷ������תָ��ı�ǩ
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

        now_block++;   //��ת��˵����һ���µĻ�����
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

    //���Ǻͺ����˳����÷��رȽ��й������ڿ�㷢���仯(��������Ļ���ԭ��)
    if(strcmp(op,"goto")==0||strcmp(op,"return")==0||strcmp(op,"call")==0||strcmp(op,"endp")==0||strcmp(op,"end_main")==0){
        pfour->block_num=now_block;
        now_block++;
    }
    else if(strcmp(op,"gre")==0||strcmp(op,"lss")==0||strcmp(op,"eql")==0||strcmp(op,"geq")==0||strcmp(op,"leq")==0||strcmp(op,"neq")==0){
        pfour->block_num=now_block;
        now_block++;
    }//�����¸�������

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
//ɨ�������Ԫʽ���飬�������еĻ�����

void scan()
{
    //�ҵ�������ʼ
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

//�ϲ�����,�ϲ���ĸ�ʽΪ=12   res
void combine() {
    int i = codeindex;
	int num1, num2, temp;
    char sum[ 30 ];
	//������ʽ��
//printf("combine\n");
    while ( strcmp(mid_code[ i ].op, "+") == 0 || strcmp(mid_code[ i ].op, "-") == 0 || strcmp(mid_code[ i ].op, "*") == 0 || strcmp(mid_code[ i ].op, "/") == 0 ) {
        if ( isconst(mid_code[ i ].op1) && isconst(mid_code[ i ].op2) ) {//����������������������
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

//ɾ�������ӱ��ʽ
void delpublic()
{
//printf("delpublic\n");

    int i, j, h, k;
    //���ֻ�����
    for ( i = codeindex; strcmp(mid_code[ i ].op, "+") == 0 || strcmp(mid_code[ i ].op, "-") == 0 || strcmp(mid_code[ i ].op, "*") == 0 || strcmp(mid_code[ i ].op, "/") == 0 || strcmp(mid_code[ i ].op, "=") == 0; i++ ) {
        if ( i >= midcode_num ){
            return;
        }
        if ( mid_code[ i ].res[ 0 ] == '$' ) {
            for ( j = i + 1; strcmp(mid_code[ j ].op, "+") == 0 || strcmp(mid_code[ j ].op, "-") == 0 || strcmp(mid_code[ j ].op, "*") == 0 || strcmp(mid_code[ j ].op, "/") == 0 || strcmp(mid_code[ j ].op, "=") == 0; j++ ) {
                if ( j >= midcode_num ){
                    return;
                }
                //Ѱ�ҹ����ӱ��ʽ,��������Ͳ�����1,2����ͬ�Ҷ��Ǹ�ֵ����ʱ����
                if ( strcmp(mid_code[ j ].op, mid_code[ i ].op) == 0 && strcmp(mid_code[ j ].op1, mid_code[ i ].op1) == 0 && strcmp(mid_code[ j ].op2, mid_code[ i ].op2) == 0 && mid_code[ j ].res[ 0 ] == '$' ) {
                    //�ҵ��ڸ���ʱ�������ƺ����ʱ������Ϊ��������ʽ�ӣ��޸ı���������(�൱������ʱ����1����ԭ����Ϊ����������ʱ����2)
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
                        strcpy(mid_code[ k ].op, mid_code[ k + 1 ].op);     //ɾ��
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

//ɾ��������ת����
void delsetlab()
{
//printf("delsetlab\n");

    int i, k, j, t, flag;
    char temp[ 30 ][ 10 ];
    for ( i = 0; i < midcode_num; i++ ) {
        if ( i >= midcode_num ){
            return;
        }
		//����lab��չ������
        if ( strcmp(mid_code[ i ].op, "lab:") == 0 ) {
            j = 0;
            flag = i;
            i = i + 1;
			//��һ��lab֮������ŵ�lab������
            while ( strcmp(mid_code[ i ].op, "lab:") == 0 ) {
                strcpy(temp[ j++ ], mid_code[ i ].res);
                for ( k = i; k<midcode_num; k++ ) {
                    strcpy(mid_code[ k ].op, mid_code[ k + 1 ].op);     //ɾ��
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
				//�����������ǩ���ҵ�֮ǰ����ת�йص�ָ��������������ǩ���Ϊ�������µ���Ч��ǩ(��������ǩ�ı�ǩ��)
                if ( strcmp(mid_code[ k ].op, "jmp") == 0 || strcmp(mid_code[ k ].op, "jne") == 0 ) {
                    for ( t = 0; t<j; t++ ) {//j��¼�����ж��������ǩ
                        if ( strcmp(mid_code[ k ].res, temp[ t ]) == 0 )
                            strcpy(mid_code[ k ].res, mid_code[ flag ].res);
                    }
                }
            }
        }
    }
}



//��Ծ��������
int ret_code(char *op1) //���ر��
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
	int mark=1;//����in ��out ѭ����־
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
		if(now_block<pfour_now->block_num) //�����¸�������
		{
            now_block=pfour_now->block_num;
		}
		if(strcmp(pfour_now->op,"=")==0) //def
		{
			//	strcpy(array[now_block].def[use_num++],pfour_now->res);

				/////////////////////////////////////////////////////
				if((pfour_now->op1[0]!='$'))//op1�Ǳ���
				{
					  int t;
                      //strcpy(array[now_block].use[use_num++],pfour_now->op1);
					  t=ret_code(pfour_now->op1);//���ر��

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
					  t=ret_code(pfour_now->op1);//���ر��,����һ�γ��֣������ű�

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
					  t=ret_code(pfour_now->op2);                   //���ر��,����һ�γ��֣������ű�

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
    init_in(); //��ʼ��in ����

     while(mark==1) //���in
	 {
		 int i;
         for(i=0;i<now_block;i++)
		 {
			 int j;

			 //for(j=0;j<LiveMax;j++) in[j]=0;
              int old=0;
              for(j=0;j<RelateMax;j++)  //��out[]
			  {
				  int k,old;
				  k=block_array[i].aft_block[j];
             block_array[i].out[j]=block_array[i].out[j]||block_array[k].in[j];

		     old=block_array[i].in[j];
		         block_array[i].in[j]= block_array[i].use[j]|( block_array[i].out[j]&(~block_array[i].def[j]));

			     if(old!=block_array[i].in[j]) mark=1;//in �仯
			  }



		 }

	 }

}


//�ж��ǲ�������
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

//��ӡ�Ż������Ԫʽ
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
    char siyuan[LineMax],label[WordMax];//���
    int all_state[DEEP][RegMax+2]; //������ǰ����״̬
    int now_deep=0;
    int already_para=0;
    int used_reg=0;//ʹ�ù�����ʱ�������
    int para_count=0;
	funcclass tfc;
	mi=ap=0;
    fclose(fp4);
    fp4=fopen("siyuanshi.txt","r");
	fprintf(fp_final,"\t.text\n");
	fprintf(fp_final,"\t\tori\t$fp\t$sp\t0\n");//ori $fp $sp 0(fp��ָ֡�룬sp:��ջָ��)
	fprintf(fp_final,"\t\tli\t$t9\t0x7fffeffc\t#global stack bottom\n");//li $t9 0x7fffeffc ��ȫ�ֱ�����ջ�ף�
	fprintf(fp_final,"\t\tli\t$t8\t0x10010000\t#save word\n");//li $t8 0x10010000 ����
//printf("%d %d\n",midcode_num2,mi);//(172)
//printf("%s %s \n",mid_code2[ mi ].op);
	//ȫ�ֳ���
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
		//ȫ�ֱ���
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
		//��������
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


//���������ݣ�����������end�Ϳ�ʼ��func
void funcasm(){
memset(varreg, 0xff, sizeof(int) * 200);
//printf("begin funcasm\n");
	int i;
	int temp;
	sp = 0;//���ƫ��Ϊ0
	fprintf(fp_final,"\t\t#Save Register\n");//�����ֳ�
	savesreg();//��֮ǰ�Ĵ�����ֵ�ñ���Ķ�������
	fprintf(fp_final,"\t\tsw\t$fp\t($sp)\n");//������һ��������$fp  //sw $fp ($sp)
	fprintf(fp_final,"\t\tadd\t$fp\t$sp\t$0\n");//���ñ�����$fp��//$fp=$sp  add $fp $sp $0
	sp -= 4;
	fprintf(fp_final,"\t\tsubi\t$sp\t$sp\t4\n");//$sp-=4//subi $sp $sp 4
	fprintf(fp_final,"\t\tsw\t$ra\t($sp)\n");//����$ra//sw $ra ($sp)
	sp -= 4;
	fprintf(fp_final,"\t\tsubi\t$sp\t$sp\t4\n");//$sp-=4//subi $sp $sp 4
	fprintf(fp_final,"\t\t#Save Register Done!\n");
	//��ʱ��������
    tmi = mi;
	temp=mi;
	while ( strcmp(mid_code2[ tmi ].op, "endp") != 0 ) {//ֱ������������Ԫʽ���˳�
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
        if ( strcmp(mid_code2[ mi ].op, "jmp") == 0 ) jmpasm();//��goto��Ϊjmp?????
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
            //���ü����Ż�
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
	//�ָ��ֳ�
	fprintf(fp_final,"__FEND_LAB_%d:\n",funcnum);//������ʼ
	fprintf(fp_final,"\t\tlw\t$ra\t-4($fp)\n");//�ָ�$ra
	fprintf(fp_final,"\t\tadd\t$sp\t$fp\t$0\n");//��ջ,�ָ�$sp
	fprintf(fp_final,"\t\tlw\t$fp\t($fp)\n");//�ָ���һ��������fp
	loadsreg();//�ָ�$s0-$s7
	if ( ismain ) {
        fprintf(fp_final,"\t\tli\t$v0\t10\n" );
        fprintf(fp_final,"\t\tsyscall\n" );//��ֹ����
    } else {
        fprintf(fp_final,"\t\tjr\t$ra\t\n");//����
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

int funckind(char *fname) {//!!!!!!��fc�й���funcasm���õ�?????????fc.size()???
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

int findvartable(char *name) {//scafasm pritasm�õ�
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

//���һ�������ַ
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

//����ַ�������Ե�ַ��sp����
void insertaddress(int kind, int addr, int nmi) {//!!!ȥ���õ��ĵط�
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

void pushstack(char* item, int lenth) {//!!!ȥ���õ��ĵط�
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
//���op1�Ƿ�Ϊ���������ǵĻ���move $v0
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
        //������Ԫ��a[i]��ַ
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
        //������Ԫ��a[i]��ַ
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
    fprintf(fp_final, "\t\tj\t__FEND_LAB_%d\n" , funcnum );//��������
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
    //��������
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

    //���鶨��
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
            printf("1: %d line , lack��\n",line);
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
        case 4:										//OUTOFTABLE?????????????????��������֣�����
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
			 signal == 0 ? IWFLIRSPE ://�ڵ���������ҵ���һ���
             signal == 1 ? IWFXXXANE ://�ڱ��ʽ��call������һ����������
            -1;
               break;

        case 9:    printf("9: %d��, %s index is not defined\n",line,name+1);
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
				printf("15: %d line��index %s defined again\n",line,name+1);
				errclass = DONOTHING;
               break;
        /*case 16:   printf("16: %d line��lack \"\n",line);
               break;*/
        case 17:   printf("17: %d line, this sentence is illegal/the order of the sentence is wrong\n",line);
				errclass =
				signal == 0 ?  IWFLIRSPE:
				signal == 1 ? IWFXXXANE :
				-1;
               break;
        /*case 18:   printf("18: %d line��const is not assinged\n",line);
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
        case 21: printf("21: %d line, there should be ��=��\n",line);
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
	   /*case 27:printf("%d��, ��ֵ�����������Ͳ�ƥ��\n",line);
			 break;*/
	   case 28:printf("28: %d line, there is no number inside of the array/something wrong when define the array\n",line);
			 errclass = IWFRSPIFCV;
			 break;
	   /*case 29:printf("%d��, �˴�ӦΪ��\n",line);
			 break;
	   case 30:printf("%d��, �˴�ӦΪ����\n",line);
			 break;
	   case 31:printf("%d��, ���������Ӻ����ж��庯��\n",line);
			 break;*/
	   case 32:printf("32: %d line, there lack case\n",line);
			errclass =
			signal == 0 ?  IWFLIRSPE:
            signal == 1 ? ICV :
			-1;
			 break;
	   /*case 33:printf("%d��, �˴�����Խ��\n",line);
			 break;
		case 34:printf("%d��, ȱ��[\n",line);
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
   /* case 32: fprintf(stdout,"%d��, Ӧ�С�=��\n",line,name);
		     break;
	 case 32: fprintf(stdout,"%d��, Ӧ�С�=��\n",line,name);
		     break;*/
	}
	switch ( errclass ){
        case QUIT:
            system("pause");
            exit(0);
            break;
        case DONOTHING:
            break;
        case ICV://������һ��������������int/char/void
            while ( strcmp(WORD_tag[count] ,"INTTK" )&& strcmp(WORD_tag[count] , "CHARTK")&& strcmp(WORD_tag[count], "VOIDTK" )) {
                count++;
            }
            break;
        case CICVIFIRSP://������һ�����¼��ϵ�Ԫ��{ CONSTTK INTTK CHARTK VOIDTK IFTK WHILETK FORTK IDEN RETURNTK SCANFTK PRINTFTK}
            while ( strcmp(WORD_tag[count]  ,"CONSTTK") && strcmp(WORD_tag[count]  ,"INTTK") && strcmp(WORD_tag[count]  ,"CHARTK") && strcmp(WORD_tag[count]  ,"VOIDTK")&& strcmp(WORD_tag[count]  ,"IFTK") && strcmp(WORD_tag[count]  ,"DOTK")
                && strcmp(WORD_tag[count]  ,"SWITCHTK") && strcmp(WORD_tag[count]  ,"IDEN") && strcmp(WORD_tag[count]  ,"RETURNTK") && strcmp(WORD_tag[count]  ,"SCANFTK")&& strcmp(WORD_tag[count]  ,"PRINTFTK")){
                count++;
            }
            break;
        case CS://������һ�����Ż��߷ֺ�
            while ( strcmp(WORD_tag[count]  ,"COMMA ")&& strcmp(WORD_tag[count]  ,"SEMCON") ) {
                count++;
            }
            break;
        case CLR://������һ�����Ż�������
            while ( strcmp(WORD_tag[count]  ,"COMMA") && strcmp(WORD_tag[count]  ,"LPARENT") && strcmp(WORD_tag[count]  ,"RPARENT") ) {
                count++;
            }
            break;
        case IWFRSPIFCV://������һ������е�FIRST����Ԫ��֮һ
            while ( strcmp(WORD_tag[count]  ,"IFTK")&& strcmp(WORD_tag[count]  ,"DOTK") && strcmp(WORD_tag[count]  ,"SWITCHTK") &&strcmp( WORD_tag[count]  ,"RETURNTK")&& strcmp(WORD_tag[count]  ,"SCANFTK")
                &&strcmp( WORD_tag[count]  ,"PRINTFTK")&& strcmp(WORD_tag[count]  ,"INTTK") && strcmp(WORD_tag[count]  ,"CHARTK") && strcmp(WORD_tag[count]  ,"VOIDTK")) {
                count++;
            }
            break;
        case IWFLIRSPE://������һ�����¼��ϵ�Ԫ�أ�{IFTK WHILETK FORTK LBRACK IDEN RETURNTK SCANFTK PRINTFTK ELSETK RBRACE}
            while ( strcmp(WORD_tag[count]  ,"IFTK") &&strcmp( WORD_tag[count]  ,"DOTK")&& strcmp(WORD_tag[count]  ,"SWITCHTK") && strcmp(WORD_tag[count]  ,"IDEN")
                && strcmp(WORD_tag[count]  ,"RETURNTK") && strcmp(WORD_tag[count]  ,"SCANFTK")&& strcmp(WORD_tag[count]  ,"PRINTFTK ") &&strcmp( WORD_tag[count]  ,"RBRACE")) {
                //printf("find }\n");
				count++;
            }
            break;
        case IWFXXXANE://������һ�����¼��ϵ�Ԫ�أ�{ IFTK WHILETK FORTK LBRACK IDEN RETURNTK SCANFTK PRINTFTK  SEMCON ELSETK RPARENT COMMA PLUS MINU MULT DIV LSS LEQ GRE GEQ NEQ EQL}
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

	//if(pword==NULL)!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!�ҵ���������ʱ�Ľ�����
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

	//���дʷ����������cifafenxi.txt
	for(i=1;i<number;i++)
	{
		fprintf(fp2,"%d %s %s\n",i,WORD_tag[i],WORD[i]);
	}
    fclose(fp2);

    i=errorcount;

	//�����﷨�����Լ�������Ԫʽ����Ԫʽ�������siyuanshi.txt��
    printf("begin cifafenxi&siyuanshi\n");
	cifanalys();



	//��ʼ��Ԫʽ���Ż�
	printf("begin optimieze\n");
	scan();
	printOptimize();//�洢�Ż������Ԫʽ��optMidCode.txt
	fclose(fp_error);

	//��ʼ���ָ������
	printf("begin assembly\n");
    assembly();
	fclose(fp_final);


}
