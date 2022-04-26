typedef unsigned char byte;
typedef unsigned short int word;
typedef word Adress;


#define pc reg[7]
#define MEMSIZE (64*1024)

#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3

typedef struct {
    word mask;
    word opcode;
    char * name;
    void (*do_func)(void);
}Command;
extern Command cmd[];
extern word reg[8];

void mem_dump(Adress start, word n);
void trace(const char * fmt, ...);
word w_read(Adress adr);
void w_write(Adress adr, word w);
byte b_read(Adress adr);
void run();

void do_halt();
void do_mov();
void do_add();
void do_nothing();
