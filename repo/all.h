typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;


#define pc reg[7]
#define MEMSIZE (64*1024)

#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3

#define REGISTER 0
#define MEM 1

#define GET_MR_SS 0
#define GET_MR_DD 1

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
    word ssdd;
}Command;
typedef struct {
    word val;    //значение аргумента
    word adr;    //адрес аргумента
}Arg;


extern Command cmd[];
extern word reg[8];
extern Arg ss,dd;

void mem_dump(Adress start, word n);
void trace(const char * fmt, ...);
word w_read(Adress adr);
void w_write(Adress adr, word w);
byte b_read(Adress adr);
void run();
void regs_print();

Arg get_mr(word w, int forwhat);


void do_mov();
void do_add();
void do_nothing();
unsigned sum(unsigned int a, unsigned int b);
void do_sob();
void do_clr(); 
void do_halt();