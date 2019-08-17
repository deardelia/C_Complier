#define MAXTABLE  100
#define MAXOP	  5000
#define	MAXS		10				//printf语句中最多的转换字符数
#define WordMax 500       //最长标识符
#define Max_Table_hang 100    //符号表最大个数
#define Max_Table_lie 100
#define ShuzuMax 500
#define LineMax 200       //最长一行
#define RegMax 4
#define DEEP  20//递归深度
#define MAXPARANUM  100
#define CodeMax 20   // 编码表最多变量和常量
#define MaxBlock     100//基本块最大数
#define RelateMax 5
#define BlockRowMax  50//基本块内四元式最大数


#define INITSTACK 0x7fffeffc
#define VOID 0
#define INT 1
#define CHAR 2
#define WINT 3
#define WCHAR 4
#define Max_func 100//允许的最大函数个数
#define OPTFLAG 0    //优化开关

//出错处理的操作
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

struct symboltable{						//符号表
	char *name;
	int type, lev, adr, kind;
	Cha uchar;

};*/


typedef struct symbolTable   //符号表结构
{
	char name[WordMax];
	int type;
	int kind;//char:12 int ；11
	int number;//整型/函数参数/数组个数
	int cischar;//字符型
	int value;
	char xiabiao[ShuzuMax];//数组存储的内容(不论是字符数组还是整型数组都按照char的形式存储)
	int shuzuflag;//操作时的数组下标
	int funcparaType[MAXPARANUM];
}Mean,*PMean;

Mean table[Max_Table_hang][Max_Table_lie];  //符号表头集合, 0层-全局量


typedef struct node7
{
	 char op[WordMax],op1[WordMax],op2[WordMax],res[WordMax];
     int block_num;//所属基本块编号
     char func_name[WordMax];//所属函数名
	 int op1_code;   //op1编码
	 int op2_code;
     int res_code;
	 struct node7 *next;

}FOUR,*PFOUR;

PFOUR pfour_head,pfour,pfour_now;
FOUR  mid_code[MAXOP];

typedef struct regist   //寄存器状态
{
	char temp[8];
	char name[RegMax];//eax,ecx,edx
	int  state; // 1--被占

}Reg;

typedef struct node6
{
	char func_name[WordMax];
	char reg_name[4];//esi,edi
	int state;
	char value[WordMax];//可能是常数，变量，常量，临时，
}Ret_value;

Reg reg[RegMax];
Ret_value ret_value[2];

typedef struct {//在四元式生成汇编使用
    char name[ 100 ];
    int address;
    int kind;
    int cnt;
}tempvaraddress;//变量表
tempvaraddress addrtable[ 1000 ];//临时变量在栈中的地址表


typedef struct {
    char name[ 100 ];
    int kind;
}funcclass;
funcclass fc[Max_func];//函数表

char f_name[WordMax];


ypedef struct node11
{
    int block_num;
	FOUR siyuan[BlockRowMax];
	int siyuan_num;//四元式数量
    int pre_block[RelateMax];//前继基本块编号
	int aft_block[RelateMax];
	int in[VarMax];
	int out[VarMax];
	int use[VarMax];
	int def[VarMax];
	int live[VarMax];
}BASE_BLOCK;
BASE_BLOCK block_array[MaxBlock];

int four_num;//四元式编号
int all_lie;
int already_ret;
int mistake;//在token用到，若有非法单词则mistake=1详细参见scanner
int sp = INITSTACK;    //栈指针,此地址为即将分配的！！相对fp！！地址
int fp = 0;//帧指针
int ap;//地址表计数器
int isglob;
int constedge = 0;
int tlabelnum = 0;
int codeindex = 0;
int  var_count;
int now_block;
int use_num;      
int def_num;
int seq;
char bianhao[CodeMax][WordMax];//编号表

FILE *fp4;
FILE *fp_final;
 FILE* optcodefile;
FILE* fp_error;


char *get_temp(void);
char* new_label();
