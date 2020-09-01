#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stdbool.h>


#define RUNNING_IN_WINDOWS 1

#define DATA_MEMORY_SIZE 4096
#define REGISTER_FILE_SIZE 32

#define CPU_OUT_STAGES 4
#define IQ_SIZE 8

#define LSQ_SIZE 6
#define ROB_SIZE 12
#define RENAME_TABLE_SIZE 24

/* Set this flag to 1 to enable debug messages */
#define ENABLE_DEBUG_MESSAGES 1
#define ENABLE_DEBUG_MESSAGES_L2 1

/* Set this flag to 1 to enable print of Regs, Flags, Memory */
#define ENABLE_REG_MEM_STATUS_PRINT 1
#define ENABLE_PUSH_STAGE_PRINT 0

enum {
	F,
	DRF,
	INT_ONE,
	INT_TWO,
	MUL_ONE,
	MUL_TWO,
	MUL_THREE,
	BRANCH,
	MEM,	// one stage with 3 cycle latency
	WB,		// this is replaces by ROB making the commit and updating the reg or other stages
	NUM_STAGES
};

enum {
	INVALID,
	VALID,
	SUCCESS,
	FAILURE,
	HALTED,
	ERROR,
	EMPTY,
	NUM_EXIT
};

/* Index of Flags */
enum {
	ZF, // Zero Flag index
	CF, // Carry Flag index
	OF, // Overflow Flag index
	IF, // Interrupt Flag index
	NUM_FLAG
};

/* Instructions Type */
enum {
	STORE = 1,
	STR,
	LOAD,
	LDR,
	MOVC,
	MOV,
	ADD,
	ADDL,
	SUB,
	SUBL,
	MUL,
	DIV,
	AND,
	OR,
	EXOR,
	BZ,
	BNZ,
	JUMP,
	HALT,
	NOP
};


/* Format of an APEX instruction  */
typedef struct APEX_Instruction {
	char opcode[128];	// Operation Code
	int rd;           // Destination Register Address
	int rs1;          // Source-1 Register Address
	int rs2;          // Source-2 Register Address
	int imm;          // Literal Value
	int type;         // Inst Type
} APEX_Instruction;

/* Model of CPU stage latch */
typedef struct CPU_Stage {
	int pc;           // Program Counter
	char opcode[128]; // Operation Code
	int rd;           // Destination Register Address
	int rs1;          // Source-1 Register Address
	int rs2;          // Source-2 Register Address
	int imm;          // Literal Value
	int rd_value;     // Destination Register Value
	int rd_valid;     // Destination Register Value Valid
	int rs1_value;    // Source-1 Register Value
	int rs1_valid;    // Source-1 Register Value Valid
	int rs2_value;    // Source-2 Register Value
	int rs2_valid;    // Source-2 Register Value Valid
	int buffer;       // Latch to hold some value (currently used to hold literal value from decode)
	int mem_address;  // Computed Memory Address
	int inst_type;		// instruction type
	int stalled;      // Flag to indicate, stage is stalled
	int executed;     // Flag to indicate, stage has executed or not
	int empty;        // Flag to indicate, stage is empty
	int stage_cycle;  // Keep count of cycle for individual stage // used to Mem stage
	int lsq_index;		// to address lSQ entry in issue queue
} CPU_Stage;

/* Model of APEX CPU */
typedef struct APEX_CPU {

	int clock;		// clock cycles elasped
	int pc;		// current program counter
	int regs[REGISTER_FILE_SIZE];		// integer register file (ARF)
	int regs_invalid[REGISTER_FILE_SIZE];		// integer register valid file (ARF)
	CPU_Stage stage[NUM_STAGES];		// array of CPU_Stage struct. Note: use . in struct with variable names, use -> when its a pointer
	APEX_Instruction* code_memory;		// struct pointer where instructions are stored
	int flags[NUM_FLAG];
	int code_memory_size;
	int data_memory[DATA_MEMORY_SIZE];		// data cache memory
	int ins_completed;		// instruction completed count
} APEX_CPU;

/* Format of an APEX Forward mechanism  */
typedef struct APEX_Forward {
	int status;
	int rd_from;
	int rs1_from;     // CPU stage from which rs2 can be forwarded
	int rs2_from;
	int unstall;
} APEX_Forward;

/* Format of an APEX Issue Queue mechanism  */
typedef struct IQ_FORMAT {
	int status;					// indicate if entry is free or allocated
	int inst_type;			// indicate instruction type
	int inst_ptr;				// indicate pc value of instruction
	int literal;				// hold literal value
	int rd;							// holds desc reg tag
	int rd_ready;			// indicate if src1 is ready
	int rd_value;				// holds desc reg value
	int rs1;						// holds src1 reg tag
	int rs1_ready;			// indicate if src1 is ready
	int rs1_value;			// holds src1 reg value
	int rs2;						// holds src2 reg tag
	int rs2_ready;			// indicate if src2 is ready
	int rs2_value;			// holds src2 reg value
	int stage_cycle;		// holds src2 reg value
	int lsq_index;			// to address lSQ entry in issue queue
} IQ_FORMAT;


/* Format of an APEX Load Strore Queue mechanism  */
typedef struct LSQ_FORMAT {
	int status;					// indicate if entry is free or allocated
	int load_store;			// indicate if entry is for load or store // use as inst_type
	int inst_ptr;				// indicate pc value of instruction
	int mem_valid;			// indicate if memory address is valid
	int mem_address;
	int rd;							// holds destination reg tag
	int rd_value;				// holds src1 reg value
	int data_ready;			// indicate if data is ready
	int rs1;						// holds src1 reg tag
	int rs1_value;			// holds src1 reg value
	int rs2;						// holds src1 reg tag
	int rs2_value;			// holds src1 reg value
	int literal;				// hold literal value
	int stage_cycle;
} LSQ_FORMAT;


typedef struct APEX_IQ {
	IQ_FORMAT iq_entries[IQ_SIZE];
}APEX_IQ;


typedef struct APEX_LSQ {
	LSQ_FORMAT lsq_entries[LSQ_SIZE];
}APEX_LSQ;

/* Format of an Load Store & Issue Queue entry/update mechanism  */
typedef struct LS_IQ_Entry {
	int inst_type;
	int executed;
	int pc;
	int rd;
	int rd_value;
	int rd_valid;
	int rs1;
	int rs1_value;
	int rs1_valid;
	int rs2;
	int rs2_value;
	int rs2_valid;
	int buffer;
	int mem_address;
	int lsq_index;
	int stage_cycle;
} LS_IQ_Entry;

/* Format of an APEX ROB mechanism  */
typedef struct APEX_ROB_ENTRY {
	int status;					// indicate if entry is free or allocated
	int inst_type;			// indicate instruction type
	int inst_ptr;				// holds instruction address
	int rd;							// holds destination reg tag
	int rd_value;			  // holds destination reg value
	int exception;			// indicate if there is exception
	int valid;					// indicate if instruction is ready to commit
} APEX_ROB_ENTRY;


typedef struct APEX_ARF_TABLE {
	// array index is used to tell if its P0 or Pn
	// this tells us from which rob entry we will get our Pn Value
	int tag_valid;				// tells if rob tag is valid or not
	int rob_tag;					// holds the index of rob entry ie issue_ptr
}APEX_ARF_TABLE;


typedef struct APEX_RENAME_TABLE {
	// array index is used to tell if its P0 or Pn
	// this tells us which Pn will holds our desc reg value
	int tag_valid;					// tells if rename entry gor desc reg is valid
	int rename_tag;					// holds the index of desc reg like R0 or Rn
} APEX_RENAME_TABLE;


typedef struct APEX_ROB {
	int commit_ptr;				  // pointer index for commit rob entry
	int issue_ptr;					// pointer index of last rob entry
	int buffer_length;			// rob buffer length
	APEX_ROB_ENTRY rob_entry[ROB_SIZE];					// array of ROB_SIZE rob entry struct. Note: use . in struct with variable names, use -> when its a pointer
} APEX_ROB;


typedef struct APEX_RENAME {
	APEX_RENAME_TABLE reg_rename[RENAME_TABLE_SIZE];
	APEX_ARF_TABLE rat_rename[RENAME_TABLE_SIZE];
	int last_rename_pos;
} APEX_RENAME;


/* Format of an ROB entry/update mechanism  */
typedef struct ROB_Entry {
	int inst_type;
	int executed;
	int pc;
	int rd;
	int rd_value;
	int rd_valid;
	int rs1;
	int rs1_value;
	int rs1_valid;
	int rs2;
	int rs2_value;
	int rs2_valid;
	int buffer;
	int exception;
	int stage_cycle;
} ROB_Entry;

/* typedef struct CPU_Instruction
{
	char opcode[128];	// Operation Code
	int rd;		    // Destination Register Address
	int rs1;		    // Source-1 Register Address
	int rs2;		    // Source-2 Register Address
	int imm;		    // Literal Value
    bool is_imm; // whether is imm
    char trace[128];
} CPU_Instruction;

void create_CPU_instruction(CPU_Instruction* ins, char* buffer);

void print_Instruction(CPU_Instruction* ins);*/

APEX_Instruction* create_code_memory(const char* filename, int* size);

APEX_CPU* APEX_cpu_init(const char* filename);

int simulate(APEX_CPU* cpu, int num_cycle);

int display(APEX_CPU* cpu, int num_cycle);

void print_cpu_content(APEX_CPU* cpu);

int APEX_cpu_run(APEX_CPU* cpu, int num_cycle, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table);

void APEX_cpu_stop(APEX_CPU* cpu);

void set_arch_reg_status(APEX_CPU* cpu, APEX_RENAME* rename_table, int reg_number, int status);

// ##################### Sub calls ##################### //

int int_one_stage(APEX_CPU* cpu, APEX_RENAME* rename_table);

int int_two_stage(APEX_CPU* cpu);

int mul_one_stage(APEX_CPU* cpu, APEX_RENAME* rename_table);

int mul_two_stage(APEX_CPU* cpu);

int mul_three_stage(APEX_CPU* cpu);

int branch_stage(APEX_CPU* cpu);

int mem_stage(APEX_CPU* cpu);

int writeback_stage(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table);

// ##################### Out-of-Order ##################### //

int fetch(APEX_CPU* cpu);

int decode(APEX_CPU* cpu, APEX_RENAME* rename_table);

int dispatch_instruction(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table);

int issue_instruction(APEX_CPU* cpu, APEX_IQ* issue_queue, APEX_LSQ* ls_queue);

int execute_instruction(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table); // cpu execute will hav diff FU calls

int commit_instruction(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table);

void branch_misprediction(APEX_CPU* cpu, ROB_Entry* rob_entry, APEX_ROB* rob, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_RENAME* rename_table);

// ##################### forwarding ##################### //

void get_inst_name(int inst_type, char* inst_type_str);
void clear_stage_entry(APEX_CPU* cpu, int stage_index);
void add_bubble_to_stage(APEX_CPU* cpu, int stage_index);
void push_func_unit_stages(APEX_CPU* cpu, int after_iq);

int get_reg_values(APEX_CPU* cpu, int src_reg);
int get_reg_status(APEX_CPU* cpu, int reg_number);
void set_reg_status(APEX_CPU* cpu, int reg_number, int status);
int previous_arithmetic_check(APEX_CPU* cpu, int func_unit);

APEX_Forward get_cpu_forwarding_status(APEX_CPU* cpu, CPU_Stage* stage);

// ##################### Issue and Load store queue ##################### //

APEX_IQ* init_issue_queue();
void deinit_issue_queue(APEX_IQ* issue_queue);

int can_add_entry_in_issue_queue(APEX_IQ* issue_queue);
int add_issue_queue_entry(APEX_IQ* issue_queue, LS_IQ_Entry ls_iq_entry, int* lsq_index);

int update_issue_queue_entry(APEX_IQ* issue_queue, LS_IQ_Entry ls_iq_entry);
int get_issue_queue_index_to_issue(APEX_IQ* issue_queue, int* issue_index);

APEX_LSQ* init_ls_queue();
void deinit_ls_queue(APEX_LSQ* ls_queue);

int can_add_entry_in_ls_queue(APEX_LSQ* ls_queue);
int add_ls_queue_entry(APEX_LSQ* ls_queue, LS_IQ_Entry ls_iq_entry, int* add_position);

int update_ls_queue_entry_mem_address(APEX_LSQ* ls_queue, LS_IQ_Entry ls_iq_entry);
int update_ls_queue_entry_reg(APEX_LSQ* ls_queue, LS_IQ_Entry ls_iq_entry);

int get_ls_queue_index_to_issue(APEX_LSQ* ls_queue, int* lsq_index);

void clear_issue_queue_entry(APEX_IQ* issue_queue);
void clear_ls_queue_entry(APEX_LSQ* ls_queue);

void print_ls_iq_content(APEX_LSQ* ls_queue, APEX_IQ* issue_queue);

// ##################### Buffer and register renaming ##################### //


APEX_ROB* init_reorder_buffer();
APEX_RENAME* init_rename_table();
void deinit_reorder_buffer(APEX_ROB* rob);
void deinit_rename_table(APEX_RENAME* rename_table);

int can_add_entry_in_reorder_buffer(APEX_ROB* rob);
int add_reorder_buffer_entry(APEX_ROB* rob, ROB_Entry rob_entry);

int can_rename_reg_tag(APEX_RENAME* rename_table);
int rename_desc_reg(int* desc_reg, APEX_RENAME* rename_table);

int check_if_reg_renamed(int any_reg, APEX_RENAME* rename_table);
int get_reg_renamed_tag(int* src_reg, APEX_RENAME* rename_table);

int get_phy_reg_renamed_tag(int reg_number, APEX_RENAME* rename_table);

int update_reorder_buffer_entry_data(APEX_ROB* rob, ROB_Entry rob_entry);
int commit_reorder_buffer_entry(APEX_ROB* rob, ROB_Entry* rob_entry);

void clear_rename_table(APEX_RENAME* rename_table);
void clear_reorder_buffer(APEX_ROB* rob);

void print_rob_and_rename_content(APEX_ROB* rob, APEX_RENAME* rename_table);

#endif