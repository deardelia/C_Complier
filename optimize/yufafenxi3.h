#define MAXTABLE  100
#define MAXOP	  5000
#define	MAXS		10				//printf���������ת���ַ���
#define WordMax 500       //���ʶ��
#define Max_Table_hang 100    //���ű�������
#define Max_Table_lie 100
#define ShuzuMax 500
#define LineMax 200       //�һ��
#define RegMax 4
#define DEEP  20//�ݹ����
#define MAXPARANUM  100
#define CodeMax 20   // ������������ͳ���
#define MaxBlock     100//�����������
#define RelateMax 5
#define BlockRowMax  50//����������Ԫʽ�����


#define INITSTACK 0x7fffeffc
#define VOID 0
#define INT 1
#define CHAR 2
#define WINT 3
#define WCHAR 4
#define Max_func 100//��������������
#define OPTFLAG 0    //�Ż�����

//������Ĳ���
#define QUIT 1
#define DONOTHING 2
#define ICV    3
#define CICVIFIRSP 4
#define CS    5
#define CLR 6
#define IWFRSPIFCV 7
#define IWFLIRSPE 8
#define IWFXXXANE 9



/*union Cha{
	int num;
	char cischar;
};

struct symboltable{						//���ű�
	char *name;
	int type, lev, adr, kind;
	Cha uchar;

};*/


typedef struct symbolTable   //���ű�ṹ
{
	char name[WordMax];
	int type;
	int kind;//char:12 int ��11
	int number;//����/��������/�������
	int cischar;//�ַ���
	int value;
	char xiabiao[ShuzuMax];//����洢������(�������ַ����黹���������鶼����char����ʽ�洢)
	int shuzuflag;//����ʱ�������±�
	int funcparaType[MAXPARANUM];
}Mean,*PMean;

Mean table[Max_Table_hang][Max_Table_lie];  //���ű�ͷ����, 0��-ȫ����


typedef struct node7
{
	 char op[WordMax],op1[WordMax],op2[WordMax],res[WordMax];
     int block_num;//������������
     char func_name[WordMax];//����������
	 int op1_code;   //op1����
	 int op2_code;
     int res_code;
	 struct node7 *next;

}FOUR,*PFOUR;

PFOUR pfour_head,pfour,pfour_now;
FOUR  mid_code[MAXOP];

typedef struct regist   //�Ĵ���״̬
{
	char temp[8];
	char name[RegMax];//eax,ecx,edx
	int  state; // 1--��ռ

}Reg;

typedef struct node6
{
	char func_name[WordMax];
	char reg_name[4];//esi,edi
	int state;
	char value[WordMax];//�����ǳ�������������������ʱ��
}Ret_value;

Reg reg[RegMax];
Ret_value ret_value[2];

typedef struct {//����Ԫʽ���ɻ��ʹ��
    char name[ 100 ];
    int address;
    int kind;
    int cnt;
}tempvaraddress;//������
tempvaraddress addrtable[ 1000 ];//��ʱ������ջ�еĵ�ַ��


typedef struct {
    char name[ 100 ];
    int kind;
}funcclass;
funcclass fc[Max_func];//������

char f_name[WordMax];


ypedef struct node11
{
    int block_num;
	FOUR siyuan[BlockRowMax];
	int siyuan_num;//��Ԫʽ����
    int pre_block[RelateMax];//ǰ�̻�������
	int aft_block[RelateMax];
	int in[VarMax];
	int out[VarMax];
	int use[VarMax];
	int def[VarMax];
	int live[VarMax];
}BASE_BLOCK;
BASE_BLOCK block_array[MaxBlock];

int four_num;//��Ԫʽ���
int all_lie;
int already_ret;
int mistake;//��token�õ������зǷ�������mistake=1��ϸ�μ�scanner
int sp = INITSTACK;    //ջָ��,�˵�ַΪ��������ģ������fp������ַ
int fp = 0;//ָ֡��
int ap;//��ַ�������
int isglob;
int constedge = 0;
int tlabelnum = 0;
int codeindex = 0;
int  var_count;
int now_block;
int use_num;      
int def_num;
int seq;
char bianhao[CodeMax][WordMax];//��ű�

FILE *fp4;
FILE *fp_final;
 FILE* optcodefile;
FILE* fp_error;


char *get_temp(void);
char* new_label();
