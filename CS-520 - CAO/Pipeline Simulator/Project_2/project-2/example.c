
/* main.c
 * Project-2
   Created by Xiang on 2020/1/28.
   Copyright © 2020年 Xiang. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"
#include <limits.h>


 /* This function is related to parsing input file */

static int get_num_from_string(char* buffer) {

	char str[16];
	int j = 0;
	for (int i = 1; buffer[i] != '\0'; ++i) {
		str[j] = buffer[i];
		j++;
	}
	str[j] = '\0';
	return atoi(str);
}
 /* To remove \n \r from instruction */
static char* remove_escape_sequences(char* buffer) {

	char array[strlen(buffer)];
	for (int i=0; i<strlen(buffer);i++){
		array[i] = buffer[i];
	}
	int r = strcspn(array, "\r");
	int n = strcspn(array, "\n");
	if (r < n) {
		array[strcspn(array, "\r")] = '\0';
	}
	else {
		array[strcspn(array, "\n")] = '\0';
	}
	buffer = array;
	return buffer;
}

/*
 * This function is related to parsing input file
 */
static void create_APEX_instruction(APEX_Instruction* ins, char* buffer) {

	if (RUNNING_IN_WINDOWS) {
		buffer = remove_escape_sequences(buffer); // NOTE: This function should only be used while running in windows
	}
	char* token = strtok(buffer, ",");
	int token_num = 0;
	char tokens[6][128];
	while (token != NULL) {
		strcpy(tokens[token_num], token);
		// strcpy(tokens[token_num], remove_escape_sequences(token));
		token_num++;
		token = strtok(NULL, ",");
	}

	strcpy(ins->opcode, tokens[0]);

	// for STORE instruction
	if (strcmp(ins->opcode, "STORE") == 0) {
		ins->rd = get_num_from_string(tokens[1]); // here rs1 is source and Mem[rs2 + imm] is destination
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->imm = get_num_from_string(tokens[3]);
		ins->type = STORE;
	}
	// for STR instruction
	else if (strcmp(ins->opcode, "STR") == 0) {
		ins->rd = get_num_from_string(tokens[1]); // here rd is source and Mem[rs1 + rs2] is destination
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = STR;
	}
	// for LOAD instruction
	else if (strcmp(ins->opcode, "LOAD") == 0) {
		ins->rd = get_num_from_string(tokens[1]); // here rd is destination and Mem[rs1 + imm] is source
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->imm = get_num_from_string(tokens[3]);
		ins->type = LOAD;
	}
	// for LDR instruction
	else if (strcmp(ins->opcode, "LDR") == 0) {
		ins->rd = get_num_from_string(tokens[1]); // here rd is destination and Mem[rs1 + rs2] is source
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = LDR;
	}
	// for MOVC instruction
	else if (strcmp(ins->opcode, "MOVC") == 0) {
		ins->rd = get_num_from_string(tokens[1]); // this is MOV Constant to Register
		ins->imm = get_num_from_string(tokens[2]);
		ins->type = MOVC;
	}
	// for MOV instruction
	else if (strcmp(ins->opcode, "MOV") == 0) {
		ins->rd = get_num_from_string(tokens[1]); // this is MOV One Register value to other Register
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->type = MOV;
	}
	// for ADD instruction
	else if (strcmp(ins->opcode, "ADD") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = ADD;
	}
	// for ADDL instruction
	else if (strcmp(ins->opcode, "ADDL") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->imm = get_num_from_string(tokens[3]);
		ins->type = ADDL;
	}
	// for SUB instruction
	else if (strcmp(ins->opcode, "SUB") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = SUB;
	}
	// for SUBL instruction
	else if (strcmp(ins->opcode, "SUBL") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->imm = get_num_from_string(tokens[3]);
		ins->type = SUBL;
	}
	// for MUL instruction
	else if (strcmp(ins->opcode, "MUL") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = MUL;
	}
	// for DIV instruction
	else if (strcmp(ins->opcode, "DIV") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = DIV;
	}
	// for AND instruction
	else if (strcmp(ins->opcode, "AND") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = AND;
	}
	// for OR instruction
	else if (strcmp(ins->opcode, "OR") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = OR;
	}
	// for EX-OR instruction
	else if (strcmp(ins->opcode, "EX-OR") == 0) {
		ins->rd = get_num_from_string(tokens[1]);
		ins->rs1 = get_num_from_string(tokens[2]);
		ins->rs2 = get_num_from_string(tokens[3]);
		ins->type = EXOR;
	}
	// for BZ instruction Variation 1 only literal
	else if (strcmp(ins->opcode, "BZ") == 0) {
		ins->imm = get_num_from_string(tokens[1]); // while executing our pc starts from 4000 so keep a relative index. // get_code_index() can be used with modifications
		ins->type = BZ;
	}
	// for BNZ instruction Variation 1 only literal
	else if (strcmp(ins->opcode, "BNZ") == 0) {
		ins->imm = get_num_from_string(tokens[1]); // while executing our pc starts from 4000 so keep a relative index. // get_code_index() can be used with modifications
		ins->type = BNZ;
	}
	else if (strcmp(ins->opcode, "JUMP") == 0) {
		ins->rs1 = get_num_from_string(tokens[1]); // while executing our pc starts from 4000 so keep a relative index. // get_code_index() can be used with modifications
		ins->imm = get_num_from_string(tokens[2]); // here jump location is giving by addidng rs1 + imm
		ins->type = JUMP;
	}
	else if ((strcmp(ins->opcode, "HALT") == 0)||(strcmp(ins->opcode, "HALT\n") == 0)) {
		ins->type = HALT;
	}
	else if ((strcmp(ins->opcode, "NOP") == 0)||(strcmp(ins->opcode, "NOP\n") == 0)) {
		ins->type = NOP;
	}
	else {
		if (strcmp(ins->opcode, "") != 0) {
			fprintf(stderr, "Invalid Instruction Found!\n");
			fprintf(stderr, "Replacing %s with %s Instruction\n", ins->opcode, "NOP");
			strcpy(ins->opcode, "NOP");
			ins->type = NOP;
		}
	}
}

/*
 * This function is related to parsing input file
 */
APEX_Instruction* create_code_memory(const char* filename, int* size) {

	if (!filename) {
		return NULL;
	}

	FILE* fp = fopen(filename, "r");
	if (!fp) {
		return NULL;
	}

	char* line = NULL; // the address of the first character position where the input string will be stored.
	size_t len = 0; // size_t is an unsigned integral data type
	ssize_t nread; // ssize_t same as size_t but signed
	int code_memory_size = 0; // for number of lines in a input files

	while ((nread = getline(&line, &len, fp)) != -1) {
		code_memory_size++;
	}
	*size = code_memory_size;
	if (!code_memory_size) {
		fclose(fp);
		return NULL;
	}

	APEX_Instruction* code_memory = malloc(sizeof(*code_memory) * code_memory_size);  // APEX_Instruction struct pointer code_memory
	if (!code_memory) {
		fclose(fp);
		return NULL;
	}

	rewind(fp); // fb is not closed yet, rewind sets the file position to the beginning of the file
	int current_instruction = 0;
	while ((nread = getline(&line, &len, fp)) != -1) {
		create_APEX_instruction(&code_memory[current_instruction], line);
		current_instruction++;
	}

	free(line);
	fclose(fp);
	return code_memory;
}
/* */
void get_inst_name(int inst_type, char* inst_type_str) {

	switch (inst_type) {

		case STORE:
			strcpy(inst_type_str, "STORE");
			break;
		case STR:
			strcpy(inst_type_str, "STR");
			break;
		case LOAD:
			strcpy(inst_type_str, "LOAD");
			break;
		case LDR:
			strcpy(inst_type_str, "LDR");
			break;
		case MOVC:
			strcpy(inst_type_str, "MOVC");
			break;
		case MOV:
			strcpy(inst_type_str, "MOV");
			break;
		case ADD:
			strcpy(inst_type_str, "ADD");
			break;
		case ADDL:
			strcpy(inst_type_str, "ADDL");
			break;
		case SUB:
			strcpy(inst_type_str, "SUB");
			break;
		case SUBL:
			strcpy(inst_type_str, "SUBL");
			break;
		case MUL:
			strcpy(inst_type_str, "MUL");
			break;
		case DIV:
			strcpy(inst_type_str, "DIV");
			break;
		case AND:
			strcpy(inst_type_str, "AND");
			break;
		case OR:
			strcpy(inst_type_str, "OR");
			break;
		case EXOR:
			strcpy(inst_type_str, "EX-OR");
			break;
		case BZ:
			strcpy(inst_type_str, "BZ");
			break;
		case BNZ:
			strcpy(inst_type_str, "BNZ");
			break;
		case JUMP:
			strcpy(inst_type_str, "JUMP");
			break;
		case HALT:
			strcpy(inst_type_str, "HALT");
			break;
		case NOP:
			strcpy(inst_type_str, "NOP");
			break;
		default:
			strcpy(inst_type_str, "INVALID");
			break;
	}
}


void clear_stage_entry(APEX_CPU* cpu, int stage_index){
	// this is to clear any previous entries in stage and avoid conflicts between diff instructions
	cpu->stage[stage_index].rd = INVALID;
	cpu->stage[stage_index].rd_valid = INVALID;;
	cpu->stage[stage_index].rs1 = INVALID;
	cpu->stage[stage_index].rs1_valid = INVALID;
	cpu->stage[stage_index].rs2 = INVALID;
	cpu->stage[stage_index].rs2_valid = INVALID;
	cpu->stage[stage_index].inst_type = INVALID;
	cpu->stage[stage_index].pc = INVALID;
	cpu->stage[stage_index].empty = VALID;
	cpu->stage[stage_index].stage_cycle = INVALID;
	strcpy(cpu->stage[stage_index].opcode, "");
}

void add_bubble_to_stage(APEX_CPU* cpu, int stage_index) {
	// Add bubble to cpu stage
	clear_stage_entry(cpu, stage_index);
	strcpy(cpu->stage[stage_index].opcode, "NOP"); // add a Bubble
	cpu->stage[stage_index].inst_type = NOP;
	cpu->code_memory_size = cpu->code_memory_size + 1;
	cpu->stage[stage_index].empty = 0;
}

void push_func_unit_stages(APEX_CPU* cpu, int after_iq){

	if (after_iq) {
		cpu->stage[MUL_THREE] = cpu->stage[MUL_TWO];
		cpu->stage[MUL_TWO] = cpu->stage[MUL_ONE];
		// and empty the MUL_ONE stage
		clear_stage_entry(cpu, MUL_ONE);

		cpu->stage[INT_TWO] = cpu->stage[INT_ONE];
		// and empty the MUL_ONE stage
		clear_stage_entry(cpu, INT_ONE);

		if ((cpu->stage[MEM].executed)&&(cpu->stage[MEM].stage_cycle>=3)) {
			// and empty the MEM stage
			clear_stage_entry(cpu, MEM);
		}

		if (cpu->stage[BRANCH].executed) {
			// and empty the BRANCH stage
			clear_stage_entry(cpu, BRANCH);
		}

	}
	else {
		if (!cpu->stage[F].stalled) {
			clear_stage_entry(cpu, DRF);
			cpu->stage[DRF] = cpu->stage[F];
			cpu->stage[DRF].executed = 0;
		}
		else if (cpu->stage[F].stalled) {
			if (cpu->stage[BRANCH].empty) {
				cpu->stage[F].stalled = INVALID;
			}
		}
		else {
			add_bubble_to_stage(cpu, DRF);
		}
	}
}


int get_reg_values(APEX_CPU* cpu, int src_reg) {
	// Get Reg values function
	int value = -1;
	value = cpu->regs[src_reg];
	return value;
}

int get_reg_status(APEX_CPU* cpu, int reg_number) {
	// Get Reg Status function
	int status = 1; // 1 is invalid and 0 is valid
	if (reg_number > REGISTER_FILE_SIZE) {
		// Segmentation fault
		fprintf(stderr, "Segmentation fault for Register location :: %d\n", reg_number);
	}
	else {
		status = cpu->regs_invalid[reg_number];
	}
	return status;
}

void set_reg_status(APEX_CPU* cpu, int reg_number, int status) {
	// Set Reg Status function
	// NOTE: insted of set inc or dec regs_invalid
	if (reg_number > REGISTER_FILE_SIZE) {
		// Segmentation fault
		fprintf(stderr, "Segmentation fault for Register location :: %d\n", reg_number);
	}
	else {
		cpu->regs_invalid[reg_number] = cpu->regs_invalid[reg_number] + status;
	}
}

int previous_arithmetic_check(APEX_CPU* cpu, int func_unit) {

	int status = 0;
	int a = 0;
	for (int i=a;i<func_unit; i++) {
		if (strcmp(cpu->stage[i].opcode, "NOP") != 0) {
			a = i;
			break;
		}
	}

	if (a!=0){
		if ((strcmp(cpu->stage[a].opcode, "ADD") == 0) ||
			(strcmp(cpu->stage[a].opcode, "ADDL") == 0) ||
			(strcmp(cpu->stage[a].opcode, "SUB") == 0) ||
			(strcmp(cpu->stage[a].opcode, "SUBL") == 0) ||
			(strcmp(cpu->stage[a].opcode, "MUL") == 0) || (strcmp(cpu->stage[a].opcode, "DIV") == 0)) {

			status = 1;
		}
	}

	return status;
}

APEX_Forward get_cpu_forwarding_status(APEX_CPU* cpu, CPU_Stage* stage) {
	// depending on instruction check if forwarding can happen
	APEX_Forward forwarding;
	forwarding.status = 0;
	forwarding.unstall = 0;
	forwarding.rd_from = -1;
	forwarding.rs1_from = -1;
	forwarding.rs2_from = -1;
	return forwarding;
}

/*
 * ########################################## Issue Queue ##########################################
*/

APEX_IQ* init_issue_queue() {

	APEX_IQ* issue_queue = malloc(sizeof(*issue_queue));

	if (!issue_queue) {
		return NULL;
	}

	memset(issue_queue->iq_entries, 0, sizeof(IQ_FORMAT)*IQ_SIZE);  // all issue entry set to 0

	return issue_queue;
}

void deinit_issue_queue(APEX_IQ* issue_queue) {
	free(issue_queue);
}

int can_add_entry_in_issue_queue(APEX_IQ* issue_queue) {
	int add_position = -1;
	for (int i=0; i<IQ_SIZE; i++) {
		if (issue_queue->iq_entries[i].status == INVALID) {
			add_position = i;
			break;
		}
	}
	if (add_position<0) {
		return FAILURE;
	}
	else {
		return SUCCESS;
	}
}

int add_issue_queue_entry(APEX_IQ* issue_queue, LS_IQ_Entry ls_iq_entry, int* lsq_index) {
	// if instruction sucessfully added then only pass the instruction to function units
	int add_position = -1;
	if (!ls_iq_entry.executed) {
		return FAILURE;
	}
	else {
		for (int i=0; i<IQ_SIZE; i++) {
			if (issue_queue->iq_entries[i].status == INVALID) {
				add_position = i;
				break;
			}
		}
		if (add_position<0) {
			return FAILURE;
		}
		else {
			issue_queue->iq_entries[add_position].status = VALID;
			issue_queue->iq_entries[add_position].inst_type = ls_iq_entry.inst_type;
			issue_queue->iq_entries[add_position].inst_ptr = ls_iq_entry.pc;
			issue_queue->iq_entries[add_position].rd = ls_iq_entry.rd;
			issue_queue->iq_entries[add_position].rd_value = ls_iq_entry.rd_value;
			issue_queue->iq_entries[add_position].rd_ready = ls_iq_entry.rd_valid;
			issue_queue->iq_entries[add_position].rs1 = ls_iq_entry.rs1;
			issue_queue->iq_entries[add_position].rs1_value = ls_iq_entry.rs1_value;
			issue_queue->iq_entries[add_position].rs1_ready = ls_iq_entry.rs1_valid;
			issue_queue->iq_entries[add_position].rs2 = ls_iq_entry.rs2;
			issue_queue->iq_entries[add_position].rs2_value = ls_iq_entry.rs2_value;
			issue_queue->iq_entries[add_position].rs2_ready = ls_iq_entry.rs2_valid;
			issue_queue->iq_entries[add_position].literal = ls_iq_entry.buffer;
			issue_queue->iq_entries[add_position].stage_cycle = INVALID;
			issue_queue->iq_entries[add_position].lsq_index = *lsq_index;
		}
	}
	return SUCCESS;
}


int update_issue_queue_entry(APEX_IQ* issue_queue, LS_IQ_Entry ls_iq_entry) {
	
	int update_pos_sum = 0;
	if (!ls_iq_entry.executed) {
		return FAILURE;
	}
	else {
		// for now loop through entire issue_queue and check
		for (int i=0; i<IQ_SIZE; i++) {
			// check only alloted entries
			if (issue_queue->iq_entries[i].status == VALID) {
				// first check rd ie flow and output dependencies
				if ((ls_iq_entry.rd == issue_queue->iq_entries[i].rs1)&&(issue_queue->iq_entries[i].rs1_ready==INVALID)) {
					issue_queue->iq_entries[i].rs1_value = ls_iq_entry.rd_value;
					issue_queue->iq_entries[i].rs1_ready = VALID;
					// rs1_position[i] = i;
					update_pos_sum += 1;
				}
				if ((ls_iq_entry.rd == issue_queue->iq_entries[i].rs2)&&(issue_queue->iq_entries[i].rs2_ready==INVALID)) {
					issue_queue->iq_entries[i].rs2_value = ls_iq_entry.rd_value;
					issue_queue->iq_entries[i].rs2_ready = VALID;
					// rs2_position[i] = i;
					update_pos_sum += 1;
				}
				// this for updating STORE STR Rd
				if ((issue_queue->iq_entries[i].inst_type==STORE)||(issue_queue->iq_entries[i].inst_type==STR)) {
					if ((ls_iq_entry.rd == issue_queue->iq_entries[i].rd)&&(issue_queue->iq_entries[i].rd_ready==INVALID)) {
						issue_queue->iq_entries[i].rd_value = ls_iq_entry.rd_value;
						issue_queue->iq_entries[i].rd_ready = VALID;
						// rs2_position[i] = i;
						update_pos_sum += 1;
					}
				}
			}
		}
	}
	if (update_pos_sum == 0) {
		if (ENABLE_DEBUG_MESSAGES_L2) {
			fprintf(stderr, "No Update in IQ for Inst %d at pc(%d)\n", ls_iq_entry.inst_type, ls_iq_entry.pc);
		}
	}
	return SUCCESS;
}


int get_issue_queue_index_to_issue(APEX_IQ* issue_queue, int* issue_index) {
	
	int index_sum = 0;
	int stage_cycle_array[IQ_SIZE] = {[0 ... IQ_SIZE-1] = -1};
	for (int i=0; i<IQ_SIZE; i++) {
		// check only alloted entries
		if (issue_queue->iq_entries[i].status == VALID) {
			
			switch (issue_queue->iq_entries[i].inst_type) {

				// check no src reg instructions
				case MOVC: case BZ: case BNZ:
					issue_index[i] = i;
					index_sum += 1;
					break;

				// check single src reg instructions
				case STORE: case LOAD: case MOV: case ADDL: case SUBL: case JUMP:
					if (issue_queue->iq_entries[i].rs1_ready) {
						issue_index[i] = i;
						index_sum += 1;
					}
					break;

				case STR: case LDR: case ADD: case SUB: case MUL: case DIV: case AND: case OR: case EXOR:
					if ((issue_queue->iq_entries[i].rs1_ready)&&(issue_queue->iq_entries[i].rs2_ready)) {
						issue_index[i] = i;
						index_sum += 1;
					}
					break;

				default:
					break;
			}
			// even if inst is invalid inc stage cycle to know how long inst has been in IQ
			issue_queue->iq_entries[i].stage_cycle += 1;
			stage_cycle_array[i] = issue_queue->iq_entries[i].stage_cycle;
		}
	}
	if (index_sum == 0) {
		return FAILURE;
	}
	else {
		int i,j,temp;
		for(i=0; i<IQ_SIZE; i++)
		{
			for(j=i+1; j<IQ_SIZE; j++)
			{
				if(stage_cycle_array[i] < stage_cycle_array[j])
				{
					temp = issue_index[i];
					issue_index[i] = issue_index[j];
					issue_index[j] = temp;
				}
			}
		}
	}

	return SUCCESS;
}


void clear_issue_queue_entry(APEX_IQ* issue_queue) {

	// clear all rob entries
	for(int i=0; i<IQ_SIZE; i++) {
		issue_queue->iq_entries[i].status = INVALID;
		issue_queue->iq_entries[i].inst_type = INVALID;
		issue_queue->iq_entries[i].inst_ptr = INVALID;
		issue_queue->iq_entries[i].literal = INVALID;
		issue_queue->iq_entries[i].rd = INVALID;
		issue_queue->iq_entries[i].rd_ready = INVALID;
		issue_queue->iq_entries[i].rd_value = INVALID;
		issue_queue->iq_entries[i].rs1 = INVALID;
		issue_queue->iq_entries[i].rs1_ready = INVALID;
		issue_queue->iq_entries[i].rs1_value = INVALID;
		issue_queue->iq_entries[i].rs2 = INVALID;
		issue_queue->iq_entries[i].rs2_ready = INVALID;
		issue_queue->iq_entries[i].rs2_value = INVALID;
		issue_queue->iq_entries[i].stage_cycle = INVALID;
		issue_queue->iq_entries[i].lsq_index = INVALID;
	}
}

/*
 * ########################################## Load Store Queue ##########################################
*/

APEX_LSQ* init_ls_queue() {

	APEX_LSQ* ls_queue = malloc(sizeof(*ls_queue));

	if (!ls_queue) {
		return NULL;
	}

	memset(ls_queue->lsq_entries, 0, sizeof(LSQ_FORMAT)*LSQ_SIZE);  // all issue entry set to 0

	return ls_queue;
}

void deinit_ls_queue(APEX_LSQ* ls_queue) {
	free(ls_queue);
}


int can_add_entry_in_ls_queue(APEX_LSQ* ls_queue) {
	int add_position = -1;
	for (int i=0; i<IQ_SIZE; i++) {
		if (ls_queue->lsq_entries[i].status == INVALID) {
			add_position = i;
			break;
		}
	}
	if (add_position<0) {
		return FAILURE;
	}
	else {
		return SUCCESS;
	}
}


int add_ls_queue_entry(APEX_LSQ* ls_queue, LS_IQ_Entry ls_iq_entry, int* lsq_index) {
	// if instruction sucessfully added then only pass the instruction to function units
	int add_position = -1;

	for (int i=0; i<LSQ_SIZE; i++) {
		if (ls_queue->lsq_entries[i].status == INVALID) {
			add_position = i;
			break;
		}
	}
	if (add_position<0) {
		return FAILURE;
	}
	else {
		*lsq_index = add_position;
		ls_queue->lsq_entries[add_position].status = VALID;
		ls_queue->lsq_entries[add_position].load_store = ls_iq_entry.inst_type;
		ls_queue->lsq_entries[add_position].inst_ptr = ls_iq_entry.pc;
		ls_queue->lsq_entries[add_position].rd = ls_iq_entry.rd;
		ls_queue->lsq_entries[add_position].rd_value = ls_iq_entry.rd_value;
		ls_queue->lsq_entries[add_position].rs1 = ls_iq_entry.rs1;
		ls_queue->lsq_entries[add_position].rs1_value = ls_iq_entry.rs1_value;
		ls_queue->lsq_entries[add_position].rs2 = ls_iq_entry.rs2;
		ls_queue->lsq_entries[add_position].rs2_value = ls_iq_entry.rs2_value;
		ls_queue->lsq_entries[add_position].literal = ls_iq_entry.buffer;
		ls_queue->lsq_entries[add_position].mem_valid = INVALID;
		if ((ls_iq_entry.inst_type==STORE)||(ls_iq_entry.inst_type==STR)) {
			ls_queue->lsq_entries[add_position].data_ready = ls_iq_entry.rd_valid;
		}
		else {
			ls_queue->lsq_entries[add_position].data_ready = INVALID;
		}
		ls_queue->lsq_entries[add_position].stage_cycle = INVALID;
	}
	return SUCCESS;
}


int update_ls_queue_entry_mem_address(APEX_LSQ* ls_queue, LS_IQ_Entry ls_iq_entry) {

	if (ls_iq_entry.lsq_index<0) {
		return FAILURE;
	}
	else {
		// same inst data can be copied
		if (ls_queue->lsq_entries[ls_iq_entry.lsq_index].inst_ptr == ls_iq_entry.pc) {
			ls_queue->lsq_entries[ls_iq_entry.lsq_index].mem_address = ls_iq_entry.mem_address;
			ls_queue->lsq_entries[ls_iq_entry.lsq_index].mem_valid = VALID;
		}
	}

	return SUCCESS;
}


int update_ls_queue_entry_reg(APEX_LSQ* ls_queue, LS_IQ_Entry ls_iq_entry) {

	int update_pos = -1;

	for (int i=0; i<LSQ_SIZE; i++) {
		if (ls_queue->lsq_entries[i].status == VALID) {
			if (ls_queue->lsq_entries[i].data_ready==INVALID) {
				if ((ls_queue->lsq_entries[i].load_store==STORE)||(ls_queue->lsq_entries[i].load_store==STR)) {
					if (ls_queue->lsq_entries[i].rd==ls_iq_entry.rd) {
						ls_queue->lsq_entries[i].rd_value = ls_iq_entry.rd_value;
						ls_queue->lsq_entries[i].data_ready = VALID;
						update_pos = i;
					}
				}
			}
		}
	}

	if (update_pos<0) {
		return FAILURE;
	}
	return SUCCESS;
}


int get_ls_queue_index_to_issue(APEX_LSQ* ls_queue, int* lsq_index) {

	int index = -1;
	int prev_index = -1;
	int cycle = 0;
	int prev_cycle = 0;

	for (int i=0; i<LSQ_SIZE; i++) {

		if (ls_queue->lsq_entries[i].status == VALID) {
			if ((ls_queue->lsq_entries[i].load_store==STORE)||(ls_queue->lsq_entries[i].load_store==STR)) {
				if ((ls_queue->lsq_entries[i].mem_valid)&&(ls_queue->lsq_entries[i].data_ready)) {
					index = i;
					cycle = ls_queue->lsq_entries[i].stage_cycle;
				}
			}
			else {
				if (ls_queue->lsq_entries[i].mem_valid) {
					index = i;
					cycle = ls_queue->lsq_entries[i].stage_cycle;
				}
			}

		if (cycle > prev_cycle) {
			prev_cycle = cycle;
			prev_index = index;
		}
		ls_queue->lsq_entries[i].stage_cycle += 1;
		}
	}

	if (prev_index<0) {
		return FAILURE;
	}
	else {
		*lsq_index = prev_index;
	}
	return SUCCESS;
}


void clear_ls_queue_entry(APEX_LSQ* ls_queue) {

	// clear all rob entries
	for(int i=0; i<LSQ_SIZE; i++) {
		ls_queue->lsq_entries[i].status = INVALID;
		ls_queue->lsq_entries[i].load_store = INVALID;
		ls_queue->lsq_entries[i].inst_ptr = INVALID;
		ls_queue->lsq_entries[i].mem_valid = INVALID;
		ls_queue->lsq_entries[i].mem_address = INVALID;
		ls_queue->lsq_entries[i].rd = INVALID;
		ls_queue->lsq_entries[i].rd_value = INVALID;
		ls_queue->lsq_entries[i].data_ready = INVALID;
		ls_queue->lsq_entries[i].rs1 = INVALID;
		ls_queue->lsq_entries[i].rs1_value = INVALID;
		ls_queue->lsq_entries[i].rs2 = INVALID;
		ls_queue->lsq_entries[i].rs2_value = INVALID;
		ls_queue->lsq_entries[i].literal = INVALID;
		ls_queue->lsq_entries[i].stage_cycle = INVALID;
	}
}


void print_ls_iq_content(APEX_LSQ* ls_queue, APEX_IQ* issue_queue) {
	// if require to print the instruction instead of type just call the func fron cpu to print inst
	if (ENABLE_REG_MEM_STATUS_PRINT) {
		char* inst_type_str = (char*) malloc(10);
		printf("\n============ STATE OF ISSUE QUEUE ============\n");
		printf("Index, "
						"Status, "
						"Type, "
						"OpCode, "
						"Rd-value, "
						"Rs1-value-ready, "
						"Rs2-value-ready, "
						"literal, "
						"LSQ Index\n");
		for (int i=0;i<IQ_SIZE;i++) {
			strcpy(inst_type_str, "");
			get_inst_name(issue_queue->iq_entries[i].inst_type, inst_type_str);
			printf("%02d\t|"
							"\t%d\t|"
							"\t%d\t|"
							"\t%.5s\t|"
							"\tR%02d-%d-%d\t|"
							"\tR%02d-%d-%d\t|"
							"\tR%02d-%d-%d\t|"
							"\t#%02d\t|"
							"\t%02d\n",
							i,
							issue_queue->iq_entries[i].status,
							issue_queue->iq_entries[i].inst_type,
							inst_type_str,
							issue_queue->iq_entries[i].rd, issue_queue->iq_entries[i].rd_value, issue_queue->iq_entries[i].rd_ready,
							issue_queue->iq_entries[i].rs1, issue_queue->iq_entries[i].rs1_value, issue_queue->iq_entries[i].rs1_ready,
							issue_queue->iq_entries[i].rs2, issue_queue->iq_entries[i].rs2_value, issue_queue->iq_entries[i].rs2_ready,
							issue_queue->iq_entries[i].literal,
							issue_queue->iq_entries[i].lsq_index);
		}
		printf("\n============ STATE OF LOAD STORE QUEUE ============\n");
		printf("Index, "
						"Status, "
						"Type, "
						"OpCode, "
						"Mem Valid, "
						"Data Ready, "
						"Rd-value, "
						"Rs1-value, "
						"Rs2-value, "
						"literal\n");
		for (int i=0;i<LSQ_SIZE;i++) {
			strcpy(inst_type_str, "");
			get_inst_name(ls_queue->lsq_entries[i].load_store, inst_type_str);
			printf("%02d\t|"
							"\t%d\t|"
							"\t%d\t|"
							"\t%.5s\t|"
							"\t%d\t|"
							"\t%d\t|"
							"\tR%02d-%d\t|"
							"\tR%02d-%d\t|"
							"\tR%02d-%d\t|"
							"\t#%02d\n",
							i,
							ls_queue->lsq_entries[i].status,
							ls_queue->lsq_entries[i].load_store,
							inst_type_str,
							ls_queue->lsq_entries[i].mem_valid,
							ls_queue->lsq_entries[i].data_ready,
							ls_queue->lsq_entries[i].rd, ls_queue->lsq_entries[i].rd_value,
							ls_queue->lsq_entries[i].rs1, ls_queue->lsq_entries[i].rs1_value,
							ls_queue->lsq_entries[i].rs2, ls_queue->lsq_entries[i].rs2_value,
							ls_queue->lsq_entries[i].literal);

		}
		free(inst_type_str);
	}
}


/*
 * ########################################## Reorder Buffer Stage ##########################################
*/

APEX_ROB* init_reorder_buffer() {

	APEX_ROB* rob = malloc(sizeof(*rob));
	if (!rob) {
		return NULL;
	}

	memset(rob->rob_entry, 0, sizeof(APEX_ROB_ENTRY)*ROB_SIZE);  // all rob entry set to 0
	rob->commit_ptr = 0; // rob commit pointer set to 0
	rob->issue_ptr = 0; // rob issue pointer set to 0
	rob->buffer_length  = 0; // rob buffer length set to 0

	return rob;
}

APEX_RENAME* init_rename_table() {

	APEX_RENAME* rename_table = malloc(sizeof(*rename_table));
	if (!rename_table) {
		return NULL;
	}

	memset(rename_table->reg_rename, 0, sizeof(APEX_RENAME_TABLE)*RENAME_TABLE_SIZE);  // all rename table entry set to 0
	memset(rename_table->rat_rename, 0, sizeof(APEX_ARF_TABLE)*RENAME_TABLE_SIZE);  // all rename table entry set to 0
	rename_table->last_rename_pos = 0;

	return rename_table;
}

void deinit_reorder_buffer(APEX_ROB* rob) {
	free(rob);
}

void deinit_rename_table(APEX_RENAME* rename_table) {
	free(rename_table);
}


int can_add_entry_in_reorder_buffer(APEX_ROB* rob) {
	if (rob->issue_ptr == ROB_SIZE) {
		rob->issue_ptr = 0; // go back to zero index
	}
	if (rob->buffer_length == ROB_SIZE) {
		return FAILURE;
	}
	else if (rob->rob_entry[rob->issue_ptr].status) { // checking if enrty if free
		return FAILURE;
	}
	else {
		return SUCCESS;
	}
}


int add_reorder_buffer_entry(APEX_ROB* rob, ROB_Entry rob_entry) {
	
	if (rob->issue_ptr == ROB_SIZE) {
		rob->issue_ptr = 0; // go back to zero index
	}
	if (rob->buffer_length == ROB_SIZE) {
		return FAILURE;
	}
	else if (rob->rob_entry[rob->issue_ptr].status) { // checking if enrty if free
		return FAILURE;
	}
	else {
		rob->rob_entry[rob->issue_ptr].status = VALID;
		rob->rob_entry[rob->issue_ptr].inst_type = rob_entry.inst_type;
		rob->rob_entry[rob->issue_ptr].inst_ptr = rob_entry.pc;
		rob->rob_entry[rob->issue_ptr].rd = rob_entry.rd;
		rob->rob_entry[rob->issue_ptr].rd_value = -1;
		rob->rob_entry[rob->issue_ptr].exception = 0;
		rob->rob_entry[rob->issue_ptr].valid = 0;
		if (rob_entry.inst_type==HALT) {
			rob->rob_entry[rob->issue_ptr].valid = VALID;
		}
		// increment buffer_length and issue_ptr
		rob->buffer_length += 1;
		rob->issue_ptr += 1;
	}
	return SUCCESS;
}


int update_reorder_buffer_entry_data(APEX_ROB* rob, ROB_Entry rob_entry) {
	// check the stage data and update the rob data value
	int update_position = -1;
	if (!rob_entry.executed) {
		return FAILURE;
	}
	else {
		// for now loop through entire rob and check
		// a better way would be checking between commit_ptr and issue_ptr
		for (int i=0; i<ROB_SIZE; i++) {
			// check only alloted entries
			if (rob->rob_entry[i].status == VALID) {
				// check pc to match instructions
				if (rob->rob_entry[i].inst_ptr==rob_entry.pc) {
					update_position = i;
					break;
				}
			}
		}
		if (update_position<0) {
			return FAILURE;
		}
		else {
			if (rob->rob_entry[update_position].rd == rob_entry.rd) {
				rob->rob_entry[update_position].rd_value = rob_entry.rd_value;
				rob->rob_entry[update_position].valid = rob_entry.rd_valid;
				if (rob_entry.inst_type==BRANCH) {
					rob->rob_entry[update_position].valid = rob_entry.rd_valid;
					rob->rob_entry[update_position].exception = rob_entry.rd_valid;
				}
			}
			else {
				return ERROR; // found the pc value inst but failed to match desc reg
			}
		}
	}
	return SUCCESS;
}


int commit_reorder_buffer_entry(APEX_ROB* rob, ROB_Entry* rob_entry) {

	if (rob->commit_ptr == ROB_SIZE) {
		rob->commit_ptr = 0; // go back to zero index
	}
	if (!rob->rob_entry[rob->commit_ptr].valid) {
		return FAILURE;
	}
	else {
		// inst ready to commit
		rob_entry->inst_type = rob->rob_entry[rob->commit_ptr].inst_type;
		rob_entry->executed = rob->rob_entry[rob->commit_ptr].status;
		rob_entry->pc = rob->rob_entry[rob->commit_ptr].inst_ptr;
		rob_entry->rd = rob->rob_entry[rob->commit_ptr].rd;
		rob_entry->rd_value = rob->rob_entry[rob->commit_ptr].rd_value;
		rob_entry->rd_valid = rob->rob_entry[rob->commit_ptr].valid;
		rob_entry->exception = rob->rob_entry[rob->commit_ptr].exception;
		rob_entry->rs1 = INVALID;
		rob_entry->rs1_value = INVALID;
		rob_entry->rs1_valid = INVALID;
		rob_entry->rs2 = INVALID;
		rob_entry->rs2_value = INVALID;
		rob_entry->rs2_valid = INVALID;
		rob_entry->buffer = INVALID;
		rob_entry->stage_cycle = INVALID;

		// free the rob entry
		rob->rob_entry[rob->commit_ptr].status = INVALID;
		rob->rob_entry[rob->commit_ptr].inst_type = INVALID;
		rob->rob_entry[rob->commit_ptr].inst_ptr = INVALID;
		rob->rob_entry[rob->commit_ptr].rd = INVALID;
		rob->rob_entry[rob->commit_ptr].rd_value = INVALID;
		rob->rob_entry[rob->commit_ptr].exception = 0;
		rob->rob_entry[rob->commit_ptr].valid = INVALID;
		// decrement buffer_length and increment commit_ptr
		rob->buffer_length -= 1;
		rob->commit_ptr += 1;
	}
	return SUCCESS;
}


int can_rename_reg_tag(APEX_RENAME* rename_table) {

	int rename_position = -1;
	int search_start = 0;

	if (rename_table->last_rename_pos<(RENAME_TABLE_SIZE-1)) {
		search_start = rename_table->last_rename_pos;
	}

	for (int i=search_start; i<RENAME_TABLE_SIZE; i++) {
		if (rename_table->reg_rename[i].tag_valid==INVALID) {
			rename_position = i;
			break;
		}
	}
	if (rename_position<0) {
		return FAILURE;
	}
	else {
		return SUCCESS;
	}
}


int check_if_reg_renamed(int arch_reg, APEX_RENAME* rename_table) {
	
	int rename_position = -1;

	for (int i=RENAME_TABLE_SIZE-1; i>=0; i--) {
		if (rename_table->reg_rename[i].tag_valid==VALID) {
			if (rename_table->reg_rename[i].rename_tag == arch_reg) {
				rename_position = i;
				break;
			}
		}
	}
	if (rename_position<0) {
		return FAILURE;
	}
	else {
		return SUCCESS;
	}
}


int get_reg_renamed_tag(int* src_reg, APEX_RENAME* rename_table) {
	// this gives already renamed arch regs
	// check in reverse order
	int rename_position = -1;

	for (int i=RENAME_TABLE_SIZE-1; i>=0; i--) {
		if (rename_table->reg_rename[i].tag_valid==VALID) {
			if (rename_table->reg_rename[i].rename_tag == *src_reg) {
				rename_position = i;
				break;
			}
		}
	}
	if (rename_position<0) {
		return FAILURE;
	}
	else {
		*src_reg = rename_position;
	}
	return SUCCESS;
}


int get_phy_reg_renamed_tag(int phy_reg, APEX_RENAME* rename_table) {
	// any_reg is P
	// check in reverse order
	int arch_reg = -1;

	if (rename_table->reg_rename[phy_reg].tag_valid==VALID) {
		arch_reg = rename_table->reg_rename[phy_reg].rename_tag;
	}

	return arch_reg;
}


int rename_desc_reg(int* desc_reg, APEX_RENAME* rename_table) {
	// this actually renames the regs
	int rename_position = -1;
	int search_start = 0;

	if (rename_table->last_rename_pos<(RENAME_TABLE_SIZE-1)) {
		search_start = rename_table->last_rename_pos;
	}

	for (int i=search_start; i<RENAME_TABLE_SIZE; i++) {
		if (rename_table->reg_rename[i].tag_valid==INVALID) {
			rename_position = i;
			break;
		}
	}
	if (rename_position<0) {
		return FAILURE;
	}
	else {
		rename_table->reg_rename[rename_position].rename_tag = *desc_reg;
		*desc_reg = rename_position;
		rename_table->reg_rename[rename_position].tag_valid = VALID;
		rename_table->last_rename_pos = rename_position;
	}

	return SUCCESS;
}


void clear_rename_table(APEX_RENAME* rename_table) {

	// clear all rename
	for(int i=0; i<RENAME_TABLE_SIZE; i++) {
		rename_table->reg_rename[i].tag_valid = INVALID;
		rename_table->reg_rename[i].rename_tag = INVALID;
	}
	rename_table->last_rename_pos = INVALID;
}


void clear_reorder_buffer(APEX_ROB* rob) {

	// clear all rob entries
	for(int i=0; i<ROB_SIZE; i++) {
		rob->rob_entry[i].status = INVALID;
		rob->rob_entry[i].inst_type = INVALID;
		rob->rob_entry[i].inst_ptr = INVALID;
		rob->rob_entry[i].rd = INVALID;
		rob->rob_entry[i].rd_value = INVALID;
		rob->rob_entry[i].exception = INVALID;
		rob->rob_entry[i].valid = INVALID;
	}
	rob->commit_ptr = INVALID;
	rob->issue_ptr = INVALID;
	rob->buffer_length = INVALID;
}


void print_rob_and_rename_content(APEX_ROB* rob, APEX_RENAME* rename_table) {

	if (ENABLE_REG_MEM_STATUS_PRINT) {
		char* inst_type_str = (char*) malloc(10);
		printf("\n============ STATE OF REORDER BUFFER ============\n");
		printf("ROB Buffer Length: %d, Commit Pointer: %d, Issue Pointer: %d\n", rob->buffer_length, rob->commit_ptr, rob->issue_ptr);
		printf("Index, "
						"Status, "
						"Type, "
						"OpCode, "
						"Rd-value, "
						"Exception, "
						"Valid\n");
		for (int i=0;i<ROB_SIZE;i++) {
			strcpy(inst_type_str, "");
			get_inst_name(rob->rob_entry[i].inst_type, inst_type_str);
			printf("%02d\t|"
							"\t%d\t|"
							"\t%d\t|"
							"\t%.5s\t|"
							"\tR%02d-%d\t|"
							"\t%d\t|"
							"\t%d\n",
							i,
							rob->rob_entry[i].status,
							rob->rob_entry[i].inst_type,
							inst_type_str,
							rob->rob_entry[i].rd, rob->rob_entry[i].rd_value,
							rob->rob_entry[i].exception,
							rob->rob_entry[i].valid);
		}
		printf("\n============ STATE OF RENAME ADDR TABLE ============\n");
		printf("Index, "
						"Tag, "
						"Valid\n");
		for (int i=0;i<RENAME_TABLE_SIZE;i++) {
			printf("P%02d\t|"
							"\tR%02d\t|"
							"\t%d\n",
							i,
							rename_table->reg_rename[i].rename_tag,
							rename_table->reg_rename[i].tag_valid);
		}
	free(inst_type_str);
	}
}

/*
 * ########################################## Initialize CPU ##########################################
 */

APEX_CPU* APEX_cpu_init(const char* filename) {
	// This function creates and initializes APEX cpu.
	if (!filename) {
		return NULL;
	}
	// memory allocation of struct APEX_CPU to struct pointer cpu
	APEX_CPU* cpu = malloc(sizeof(*cpu));
	if (!cpu) {
		return NULL;
	}

	/* Initialize PC, Registers and all pipeline stages */
	cpu->pc = 4000;
	memset(cpu->regs, 0, sizeof(int) * REGISTER_FILE_SIZE);  // fill a block of memory with a particular value here value is 0 for 32 regs with size 4 Bytes
	memset(cpu->regs_invalid, 0, sizeof(int) * REGISTER_FILE_SIZE);  // all registers are valid at start, set to value 1
	memset(cpu->stage, 0, sizeof(CPU_Stage) * NUM_STAGES); // all values in stage struct of type CPU_Stage like pc, rs1, etc are set to 0
	memset(cpu->data_memory, 0, sizeof(int) * DATA_MEMORY_SIZE); // from 4000 to 4095 there will be garbage values in data_memory array
	memset(cpu->flags, 0, sizeof(int) * NUM_FLAG); // all flag values in cpu are set to 0

	/* Parse input file and create code memory */
	cpu->code_memory = create_code_memory(filename, &cpu->code_memory_size);

	if (!cpu->code_memory) {
		free(cpu); // If code_memory is not created free the memory for cpu struct
		return NULL;
	}
	// Below code just prints the instructions and operands before execution
	if (ENABLE_DEBUG_MESSAGES) {
		fprintf(stderr,"APEX_CPU : Initialized APEX CPU, loaded %d instructions\n", cpu->code_memory_size);
		fprintf(stderr, "APEX_CPU : Printing Code Memory\n");
		printf("%-9s %-9s %-9s %-9s %-9s\n", "opcode", "rd", "rs1", "rs2", "imm");

		for (int i = 0; i < cpu->code_memory_size; ++i) {
			printf("%-9s %-9d %-9d %-9d %-9d\n", cpu->code_memory[i].opcode, cpu->code_memory[i].rd, cpu->code_memory[i].rs1, cpu->code_memory[i].rs2, cpu->code_memory[i].imm);
		}
	}

	/* Make all stages busy except Fetch stage, initally to start the pipeline */
	for (int i = 0; i < NUM_STAGES; i++) {
		cpu->stage[i].empty = 1;
	}

	return cpu;
}

/*
 * ########################################## Stop CPU ##########################################
 */

void APEX_cpu_stop(APEX_CPU* cpu) {
	// This function de-allocates APEX cpu.
	free(cpu->code_memory);
	free(cpu);
}

int get_code_index(int pc) {
	// Converts the PC(4000 series) into array index for code memory
	// First instruction index is 0
	return (pc - 4000) / 4;
}

/*
 * ########################################## Print Stage ##########################################
*/

static void print_instruction(CPU_Stage* stage) {
	// This function prints operands of instructions in stages.
	switch (stage->inst_type) {

		case STORE: case LOAD: case ADDL: case SUBL:
			printf("%s,R%d,R%d,#%d ", stage->opcode, stage->rd, stage->rs1, stage->buffer);
			break;

		case STR: case LDR: case ADD: case SUB:case MUL: case DIV: case AND: case OR: case EXOR:
			printf("%s,R%d,R%d,R%d ", stage->opcode, stage->rd, stage->rs1, stage->rs2);
			break;

		case MOVC: case JUMP:
			printf("%s,R%d,#%d ", stage->opcode, stage->rd, stage->buffer);
			break;

		case MOV:
			printf("%s,R%d,R%d ", stage->opcode, stage->rd, stage->rs1);
			break;

		case BZ: case BNZ:
			printf("%s,#%d ", stage->opcode, stage->buffer);
			break;

		case HALT: case NOP:
			printf("%s ", stage->opcode);
			break;

		default:
			if (!stage->empty) {
				printf("<<- %s ->>", stage->opcode);
			}
			break;
	}
}


static void print_stage_status(CPU_Stage* stage) {
	// This function prints status of stages.
	if (stage->empty) {
		printf(" ---> EMPTY ");
	}
	else if (stage->stalled) {
		printf(" ---> STALLED ");
	}
}

static void print_stage_content(char* name, CPU_Stage* stage) {
	// Print function which prints contents of stage
	printf("%-15s: %d: pc(%d) ", name, stage->executed, stage->pc);
	print_instruction(stage);
	print_stage_status(stage);
	printf("\n");
}

void print_cpu_content(APEX_CPU* cpu) {
	// Print function which prints contents of cpu memory
	if (ENABLE_REG_MEM_STATUS_PRINT) {
		printf("\n============ STATE OF CPU FLAGS ============\n");
		// print all Flags
		printf("Falgs::  ZeroFlag, CarryFlag, OverflowFlag, InterruptFlag\n");
		printf("Values:: %d\t|\t%d\t|\t%d\t|\t%d\n", cpu->flags[ZF],cpu->flags[CF],cpu->flags[OF],cpu->flags[IF]);

		// print all regs along with valid bits
		printf("\n============ STATE OF ARCHITECTURAL REGISTER FILE ============\n");
		printf("NOTE :: 0 Means Valid & 1 Means Invalid\n");
		printf("Registers, Values, Invalid\n");
		for (int i=0;i<REGISTER_FILE_SIZE;i++) {
			printf("R%02d\t|\t%02d\t|\t%d\n", i, cpu->regs[i], cpu->regs_invalid[i]);
		}

		// print 100 memory location
		printf("\n============ STATE OF DATA MEMORY ============\n");
		printf("Mem Location, Values\n");
		for (int i=0;i<100;i++) {
			printf("M%02d\t|\t%02d\n", i, cpu->data_memory[i]);
		}
		printf("\n");
	}
}

/*
 * ########################################## Regs Status Stage ##########################################
*/
void set_arch_reg_status(APEX_CPU* cpu, APEX_RENAME* rename_table, int reg_number, int status) {
	// Set Reg Status function
	// NOTE: instead of set inc or dec regs_invalid
	if (reg_number > REGISTER_FILE_SIZE) {
		// Segmentation fault
		fprintf(stderr, "Segmentation fault for Register location :: %d\n", reg_number);
	}
	else {
		int src_reg = -1;
		src_reg = get_phy_reg_renamed_tag(reg_number, rename_table);
		if (src_reg<0) {
			;// the phy reg is not tagged with arch rsgs
		}
		else {
			set_reg_status(cpu, src_reg, status);
		}
	}
}

/*
 * ########################################## Fetch Stage ##########################################
*/
int fetch(APEX_CPU* cpu) {

	CPU_Stage* stage = &cpu->stage[F];
	stage->executed = 0;

	if (!stage->stalled) {
		/* Store current PC in fetch latch */
		stage->pc = cpu->pc;

		/* Index into code memory using this pc and copy all instruction fields into fetch latch */
		APEX_Instruction* current_ins = &cpu->code_memory[get_code_index(cpu->pc)];
		strcpy(stage->opcode, current_ins->opcode);
		stage->rd = current_ins->rd;
		stage->rd_valid = 0;
		stage->rs1 = current_ins->rs1;
		stage->rs1_valid = 0;
		stage->rs2 = current_ins->rs2;
		stage->rs2_valid = 0;
		stage->imm = current_ins->imm;
		stage->buffer = current_ins->imm;
		stage->inst_type = current_ins->type;

		/* Copy data from Fetch latch to Decode latch*/
		stage->executed = 1;
		// cpu->stage[DRF] = cpu->stage[F]; // this is cool I should empty the fetch stage as well to avoid repetition ?
		// cpu->stage[DRF].executed = 0;
		if (stage->inst_type == 0) {
			// stop fetching Instructions, exit from writeback stage
			stage->stalled = 0;
			stage->empty = 1;
		}
		else {
			/* Update PC for next instruction */
			cpu->pc += 4;
			stage->empty = 0;
		}
	}
	else {
		//If Fetch has HALT and Decode has HALT fetch only one Inst
		if (cpu->stage[DRF].inst_type == HALT) {
			// just fetch the next instruction
			stage->pc = cpu->pc;
			APEX_Instruction* current_ins = &cpu->code_memory[get_code_index(cpu->pc)];
			strcpy(stage->opcode, current_ins->opcode);
			stage->rd = current_ins->rd;
			stage->rd_valid = 0;
			stage->rs1 = current_ins->rs1;
			stage->rs1_valid = 0;
			stage->rs2 = current_ins->rs2;
			stage->rs2_valid = 0;
			stage->imm = current_ins->imm;
			stage->inst_type = current_ins->type;
		}
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Fetch", stage);
	}

	return 0;
}

/*
 * ########################################## Decode Stage ##########################################
*/

int decode(APEX_CPU* cpu, APEX_RENAME* rename_table) {

	CPU_Stage* stage = &cpu->stage[DRF];
	stage->executed = 0;
	int ret = -1;
	// decode should stall if IQ is full
	if (!stage->stalled) {
		/* Read data from register file for store */
		switch(stage->inst_type) {

			case STORE:  // ************************************* STORE ************************************* //

				stage->buffer = stage->imm; // keeping literal value in buffer to calculate mem add in exe stage
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if desc regs are renamed
				if (check_if_reg_renamed(stage->rd, rename_table)==SUCCESS) {
					// get the desc reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rd), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rd);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rd)==INVALID) {
						stage->rd_value = get_reg_values(cpu, stage->rd);
						stage->rd_valid = VALID;
					}
				}
				break;

			case STR:  // ************************************* STR ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if desc regs are renamed
				if (check_if_reg_renamed(stage->rd, rename_table)==SUCCESS) {
					// get the desc reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rd), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rd);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rd)==INVALID) {
						stage->rd_value = get_reg_values(cpu, stage->rd);
						stage->rd_valid = VALID;
					}
				}

				break;

			case LOAD:  // ************************************* LOAD ************************************* //
				// read literal and register values
				stage->buffer = stage->imm; // keeping literal value in buffer to calculate mem add in exe stage
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rd);
					}
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case LDR:  // ************************************* LDR ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rd);
					}
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case MOVC:  // ************************************* MOVC ************************************* //
				// read literal values
				stage->buffer = stage->imm; // keeping literal value in buffer to load in mem stage
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case MOV:  // ************************************* MOV ************************************* //
				// read register values
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case ADD:  // ************************************* ADD ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case ADDL:  // ************************************* ADDL ************************************* //
				// read only values of last two registers
				stage->buffer = stage->imm; // keeping literal value in buffer to add in exe stage
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rd);
					}
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case SUB:   // ************************************* SUB ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case SUBL:  // ************************************* SUBL ************************************* //
				// read only values of last two registers
				stage->buffer = stage->imm; // keeping literal value in buffer to add in exe stage
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case MUL:  // ************************************* MUL ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case DIV:  // ************************************* DIV ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case AND:  // ************************************* AND ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case OR:  // ************************************* OR ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs2)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case EXOR:  // ************************************* EX-OR ************************************* //
				// read only values of last two registers
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs1_value = get_reg_values(cpu, stage->rs1);
						stage->rs1_valid = VALID;
					}
				}
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs2, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs2), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs2);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				// check if renaming can be done
				if (can_rename_reg_tag(rename_table)==SUCCESS) {
					// change the desc regs tag
					ret = rename_desc_reg(&(stage->rd), rename_table);
				}
				else {
					printf("Cannot Rename Register R%d of pc(%d) :: %s\n", stage->rd, stage->pc, stage->opcode);
				}
				break;

			case BZ:  // ************************************* BZ ************************************* //
				// read literal values
				stage->buffer = stage->imm; // keeping literal value in buffer to jump in exe stage
				break;

			case BNZ:  // ************************************* BNZ ************************************* //
				// read literal values
				stage->buffer = stage->imm; // keeping literal value in buffer to jump in exe stage
				break;

			case JUMP:   // ************************************* JUMP ************************************* //
				// read literal and register values
				stage->buffer = stage->imm; // keeping literal value in buffer to calculate mem add in exe stage
				// check if src regs are renamed
				if (check_if_reg_renamed(stage->rs1, rename_table)==SUCCESS) {
					// get the src reg renamed tag
					ret = get_reg_renamed_tag(&(stage->rs1), rename_table);
					if (ret!=SUCCESS) {
						printf("Failed to get renamed tag for R%d\n", stage->rs1);
					}
				}
				else {
					// check arch reg if valid read from them
					// here 0 is valid and any other number is invalid
					if(get_reg_status(cpu, stage->rs1)==INVALID) {
						stage->rs2_value = get_reg_values(cpu, stage->rs2);
						stage->rs2_valid = VALID;
					}
				}
				break;

			case HALT:  // ************************************* HALT ************************************* //
				// Halt causes a type of Intrupt where Fetch is stalled and cpu intrupt Bit is Set
				// Stop fetching new instruction but allow all the instruction to go from Decode Writeback
				cpu->stage[F].stalled = 1; // add NOP from fetch stage
				cpu->flags[IF] = 1; // Halt as Interrupt
				break;

			case NOP:  // ************************************* NOP ************************************* //
				break; // Nothing

			default:
				if (strcmp(stage->opcode, "") != 0) {
					fprintf(stderr, "Decode/RF Invalid Instruction Found :: %s\n", stage->opcode);
				}
				break;
		}

		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Decode/RF", stage);
	}

	return 0;
}

/*
 * ########################################## Int FU One Stage ##########################################
*/
int int_one_stage(APEX_CPU* cpu, APEX_RENAME* rename_table) {

	CPU_Stage* stage = &cpu->stage[INT_ONE];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		switch(stage->inst_type) {

			case STORE: case STR:  // ************************************* STORE or STR ************************************* //
				break;
			// ************************************* LOAD to EX-OR ************************************* //
			case LOAD: case LDR: case MOVC: case MOV: case ADD: case ADDL: case SUB: case SUBL: case DIV: case AND: case OR: case EXOR:
				// make desitination regs invalid count increment by one following instructions stall
				set_arch_reg_status(cpu, rename_table, stage->rd, 1);
				stage->rd_valid = INVALID;
				break;

			case JUMP:  // ************************************* JUMP ************************************* //
				break;

			case HALT:  // ************************************* HALT ************************************* //
				break;

			case NOP:  // ************************************* NOP ************************************* //
				break;

			default:
				break;
		}
		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Int FU One", stage);
	}

	return 0;
}

/*
 * ########################################## Int FU Two Stage ##########################################
*/
int int_two_stage(APEX_CPU* cpu) {

	CPU_Stage* stage = &cpu->stage[INT_TWO];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		switch(stage->inst_type) {

			case STORE: case LOAD:  // ************************************* STORE or LOAD ************************************* //
				// create memory address using literal and register values
				stage->mem_address = stage->rs1_value + stage->buffer;
				break;

			case STR: case LDR: // ************************************* STR or LDR ************************************* //
				// create memory address using two source register values
				stage->mem_address = stage->rs1_value + stage->rs2_value;
				break;

			case MOVC:	// ************************************* MOVC ************************************* //
				// move buffer value to rd_value so it can be forwarded
				stage->rd_value = stage->buffer;
				stage->rd_valid = VALID;
				break;

			case MOV:	// ************************************* MOV ************************************* //
				// move rs1_value value to rd_value so it can be forwarded
				stage->rd_value = stage->rs1_value;
				stage->rd_valid = VALID;
				break;

			case ADD:	// ************************************* ADD ************************************* //
				// add registers value and keep in rd_value for mem / writeback stage
				if ((stage->rs2_value > 0 && stage->rs1_value > INT_MAX - stage->rs2_value) ||
					(stage->rs2_value < 0 && stage->rs1_value < INT_MIN - stage->rs2_value)) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Overflow Occurred\n");
					}
					stage->rd_valid = VALID;
					cpu->flags[OF] = 1; // there is an overflow
				}
				else {
					stage->rd_value = stage->rs1_value + stage->rs2_value;
					stage->rd_valid = VALID;
					cpu->flags[OF] = 0; // there is no overflow
					if (stage->rd_value == 0) {
						cpu->flags[ZF] = 1; // computation resulted value zero
					}
					else {
						cpu->flags[ZF] = 0; // computation did not resulted value zero
					}
				}
				break;

			case ADDL:	// ************************************* ADDL ************************************* //
				// add literal and register value and keep in rd_value for mem / writeback stage
				if ((stage->buffer > 0 && stage->rs1_value > INT_MAX - stage->buffer) ||
					(stage->buffer < 0 && stage->rs1_value < INT_MIN - stage->buffer)) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Overflow Occurred\n");
					}
					stage->rd_valid = VALID;
					cpu->flags[OF] = 1; // there is an overflow
				}
				else {
					stage->rd_value = stage->rs1_value + stage->buffer;
					stage->rd_valid = VALID;
					cpu->flags[OF] = 0; // there is no overflow
					if (stage->rd_value == 0) {
						cpu->flags[ZF] = 1; // computation resulted value zero
					}
					else {
						cpu->flags[ZF] = 0; // computation did not resulted value zero
					}
				}
				break;

			case SUB:	// ************************************* SUB ************************************* //
				// sub registers value and keep in rd_value for mem / writeback stage
				if (stage->rs2_value > stage->rs1_value) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Carry Occurred\n");
					}
					stage->rd_value = stage->rs1_value - stage->rs2_value;
					stage->rd_valid = VALID;
					cpu->flags[CF] = 1; // there is an carry
				}
				else {
					stage->rd_value = stage->rs1_value - stage->rs2_value;
					stage->rd_valid = VALID;
					cpu->flags[CF] = 0; // there is no carry
					if (stage->rd_value == 0) {
						cpu->flags[ZF] = 1; // computation resulted value zero
					}
					else {
						cpu->flags[ZF] = 0; // computation did not resulted value zero
					}
				}
				break;

			case SUBL:	// ************************************* SUBL ************************************* //
				// sub literal and register value and keep in rd_value for mem / writeback stage
				if (stage->buffer > stage->rs1_value) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Carry Occurred\n");
					}
					stage->rd_value = stage->rs1_value - stage->buffer;
					stage->rd_valid = VALID;
					cpu->flags[CF] = 1; // there is an carry
				}
				else {
					stage->rd_value = stage->rs1_value - stage->buffer;
					stage->rd_valid = VALID;
					cpu->flags[CF] = 0; // there is no carry
					if (stage->rd_value == 0) {
						cpu->flags[ZF] = 1; // computation resulted value zero
					}
					else {
						cpu->flags[ZF] = 0; // computation did not resulted value zero
					}
				}
				break;

			case DIV:	// ************************************* DIV ************************************* //
				// div registers value and keep in rd_value for mem / writeback stage
				if (stage->rs2_value != 0) {
					stage->rd_value = stage->rs1_value / stage->rs2_value;
					stage->rd_valid = VALID;
					if (stage->rd_value == 0) {
						cpu->flags[ZF] = 1; // computation resulted value zero
					}
					else {
						cpu->flags[ZF] = 0; // computation did not resulted value zero
					}
				}
				else {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Division By Zero Returning Value Zero\n");
					}
					stage->rd_value = 0;
					stage->rd_valid = VALID;
				}
				break;

			case AND:	// ************************************* AND ************************************* //
				// logical AND registers value and keep in rd_value for mem / writeback stage
				stage->rd_value = stage->rs1_value & stage->rs2_value;
				stage->rd_valid = VALID;
				break;

			case OR:	// ************************************* OR ************************************* //
				// logical OR registers value and keep in rd_value for mem / writeback stage
				stage->rd_value = stage->rs1_value | stage->rs2_value;
				stage->rd_valid = VALID;
				break;

			case EXOR:	// ************************************* EX-OR ************************************* //
				// logical OR registers value and keep in rd_value for mem / writeback stage
				stage->rd_value = stage->rs1_value ^ stage->rs2_value;
				stage->rd_valid = VALID;
				break;

			case JUMP:  // ************************************* JUMP ************************************* //
				break;

			case HALT:  // ************************************* HALT ************************************* //
				break;

			case NOP:  // ************************************* NOP ************************************* //
				break;

			default:
				break;
		}
		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Int FU Two", stage);
	}

	return 0;
}

/*
 * ########################################## Mul FU One Stage ##########################################
*/

int mul_one_stage(APEX_CPU* cpu, APEX_RENAME* rename_table) {

	CPU_Stage* stage = &cpu->stage[MUL_ONE];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		switch(stage->inst_type) {

			case MUL:  // ************************************* MUL ************************************* //
				// mul registers value and keep in rd_value for mem / writeback stage
				// if possible check y it requires 3 cycle
				set_arch_reg_status(cpu, rename_table, stage->rd, 1);
				stage->rd_valid = INVALID;
				break;

			default:
				break;
		}
		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Mul FU One", stage);
	}

	return 0;
}

/*
 * ########################################## Mul FU Two Stage ##########################################
*/

int mul_two_stage(APEX_CPU* cpu) {

	CPU_Stage* stage = &cpu->stage[MUL_TWO];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		switch(stage->inst_type) {

			case MUL:  // ************************************* MUL ************************************* //
				// mul registers value and keep in rd_value for mem / writeback stage
				// if possible check y it requires 3 cycle
				stage->rd_value = stage->rs1_value * stage->rs2_value;
				stage->rd_valid = INVALID;
				break;

			default:
				break;
		}
		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Mul FU Two", stage);
	}

	return 0;
}

/*
 * ########################################## Mul FU Three Stage ##########################################
*/
int mul_three_stage(APEX_CPU* cpu) {

	CPU_Stage* stage = &cpu->stage[MUL_THREE];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		switch(stage->inst_type) {

			case MUL:  // ************************************* MUL ************************************* //
				// mul registers value and keep in rd_value for mem / writeback stage
				// if possible check y it requires 3 cycle
				stage->rd_value = stage->rs1_value * stage->rs2_value;
				stage->rd_valid = VALID;
				if (stage->rd_value == 0) {
					cpu->flags[ZF] = 1; // computation resulted value zero
				}
				else {
					cpu->flags[ZF] = 0; // computation did not resulted value zero
				}
				break;

			default:
				break;
		}
		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Mul FU Three", stage);
	}

	return 0;
}

/*
 * ########################################## Branch FU Stage ##########################################
*/
int branch_stage(APEX_CPU* cpu) {

	CPU_Stage* stage = &cpu->stage[BRANCH];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		int new_pc;
		switch(stage->inst_type) {

			case BZ:  // ************************************* BZ ************************************* //
				// load buffer value to mem_address
				stage->mem_address = stage->buffer;
				new_pc = stage->pc + stage->mem_address;
				if ((new_pc < 4000)||(new_pc > ((cpu->code_memory_size*4)+4000))) {
					fprintf(stderr, "Instruction %s Invalid Relative Address %d\n", stage->opcode, new_pc);
				}
				else {
					if (cpu->flags[ZF] == VALID) {
						clear_stage_entry(cpu, DRF);
						clear_stage_entry(cpu, F);
						stage->rd_value = INVALID;
						stage->rd_valid = VALID;
						cpu->pc = new_pc;
						// stall F so it wont fetch in same cycle
						cpu->stage[F].stalled = VALID;
					}
					else {
						stage->rd_value = VALID;
						stage->rd_valid = INVALID;
					}
				}
				break;

			case BNZ:  // ************************************* BNZ ************************************* //
				// load buffer value to mem_address
				stage->mem_address = stage->buffer;
				new_pc = stage->pc + stage->mem_address;
				if ((new_pc < 4000)||(new_pc > ((cpu->code_memory_size*4)+4000))) {
					fprintf(stderr, "Instruction %s Invalid Relative Address %d\n", stage->opcode, new_pc);
				}
				else {
					if (cpu->flags[ZF] == INVALID) {
						stage->rd_value = VALID;
						stage->rd_valid = VALID;
						clear_stage_entry(cpu, DRF);
						clear_stage_entry(cpu, F);
						cpu->pc = new_pc;
						// stall F so it wont fetch in same cycle
						cpu->stage[F].stalled = VALID;
					}
					else {
						stage->rd_value = INVALID;
						stage->rd_valid = INVALID;
					}
				}
				break;

			case JUMP:  // ************************************* BNZ ************************************* //
				// load buffer value to mem_address
				stage->mem_address = stage->rs1_value + stage->buffer;
				new_pc = stage->mem_address;
				if ((new_pc < 4000)||(new_pc > ((cpu->code_memory_size*4)+4000))) {
					fprintf(stderr, "Instruction %s Invalid Address %d\n", stage->opcode, new_pc);
				}
				else {
					// so rob can commite
					stage->rd_value = INVALID;
					stage->rd_valid = VALID;
					// just change the pc and flush the F and DRF
					cpu->pc = new_pc;
					clear_stage_entry(cpu, DRF);
					clear_stage_entry(cpu, F);
				}
				break;

			default:
				break;
		}
		stage->executed = 1;
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Branch FU", stage);
	}

	return 0;
}

/*
 * ########################################## Mem FU Stage ##########################################
*/
int mem_stage(APEX_CPU* cpu) {

	CPU_Stage* stage = &cpu->stage[MEM];
	stage->executed = 0;
	if ((!stage->stalled)&&(!stage->empty)) {
		/* Read data from register file for store */
		if (stage->stage_cycle >= 3) {

			switch(stage->inst_type) {

				case STORE: case STR:  // ************************************* STORE or STR ************************************* //
				// use memory address and write value in data_memory
				if (stage->mem_address > DATA_MEMORY_SIZE) {
					// Segmentation fault
					fprintf(stderr, "Segmentation fault for writing memory location :: %d\n", stage->mem_address);
				}
				else {
					// wait for 3 cycles
					if (stage->rd_valid == VALID) {
						cpu->data_memory[stage->mem_address] = stage->rd_value;
						stage->executed = 1;
					}
					else {
						stage->executed = 0;
					}
				}
				break;

				case LOAD: case LDR:  // ************************************* LOAD or LDR ************************************* //
				// use memory address and write value in desc reg
				if (stage->mem_address > DATA_MEMORY_SIZE) {
					// Segmentation fault
					fprintf(stderr, "Segmentation fault for accessing memory location :: %d\n", stage->mem_address);
				}
				else {
					// wait for 3 cycles
					stage->rd_value = cpu->data_memory[stage->mem_address];
					stage->rd_valid = VALID;
					stage->executed = 1;
				}
				break;

				default:
				break;
			}
		}
		else {
			stage->stage_cycle += 1;
		}
	}

	if (ENABLE_DEBUG_MESSAGES) {
		print_stage_content("Mem FU", stage);
		printf("Mem FU Cycle :: %d\n",stage->stage_cycle);
	}

	return 0;
}

/*
 * ########################################## Writeback Stage ##########################################
*/
int writeback_stage(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table) {

	// take MUL_THREE, INT_TWO Stage and update the ROB entry so in next cycle
	// instruction can be commited

	int cpu_stages[CPU_OUT_STAGES] = {INT_TWO, MUL_THREE, BRANCH, MEM};

	for (int i=0; i<CPU_OUT_STAGES; i++) {

		CPU_Stage* stage = &cpu->stage[cpu_stages[i]];

		if ((stage->executed)&&(!stage->empty)) {
			int ret = -1;
			LS_IQ_Entry ls_iq_entry = {
				.inst_type = stage->inst_type,
				.executed = stage->executed,
				.pc = stage->pc,
				.rd = stage->rd,
				.rd_value = stage->rd_value,
				.rd_valid = stage->rd_valid,
				.rs1 = stage->rs1,
				.rs1_value = stage->rs1_value,
				.rs1_valid = stage->rs1_valid,
				.rs2 = stage->rs2,
				.rs2_value = stage->rs2_value,
				.rs2_valid = stage->rs2_valid,
				.buffer = stage->buffer,
				.mem_address = stage->mem_address,
				.lsq_index = stage->lsq_index,
				.stage_cycle = stage->stage_cycle};

			ROB_Entry rob_entry = {
				.inst_type = stage->inst_type,
				.executed = stage->executed,
				.pc = stage->pc,
				.rd = stage->rd,
				.rd_value = stage->rd_value,
				.rd_valid = stage->rd_valid,
				.rs1 = stage->rs1,
				.rs1_value = stage->rs1_value,
				.rs1_valid = stage->rs1_valid,
				.rs2 = stage->rs2,
				.rs2_value = stage->rs2_value,
				.rs2_valid = stage->rs2_valid,
				.buffer = stage->buffer,
				.exception = stage->rd_valid,
				.stage_cycle = stage->stage_cycle};

			if ((cpu_stages[i]==INT_TWO)&&((stage->inst_type==STORE)||(stage->inst_type==STR)||(stage->inst_type==LOAD)||(stage->inst_type==LDR))) {
				ret = update_ls_queue_entry_mem_address(ls_queue, ls_iq_entry);
				if (ret!=SUCCESS) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Failed to Update LSQ Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}
				continue;
			}
			else if (cpu_stages[i]==BRANCH) {
				ret = update_reorder_buffer_entry_data(rob, rob_entry);
				if (ret==ERROR) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Writeback Failed to Update Rob Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}
				if (ret==FAILURE) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Writeback Nothing to Update in Rob Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}
				continue;
			}
			else {
				ret = update_reorder_buffer_entry_data(rob, rob_entry);
				if (ret==ERROR) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Writeback Failed to Update Rob Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}
				if (ret==FAILURE) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Writeback Nothing to Update in Rob Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}

				ret = update_issue_queue_entry(issue_queue, ls_iq_entry);
				if (ret==FAILURE) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Writeback Failed to Update IQ Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}

				ret = update_ls_queue_entry_reg(ls_queue, ls_iq_entry);
				if (ret==FAILURE) {
					if (ENABLE_DEBUG_MESSAGES_L2) {
						fprintf(stderr, "Writeback Nothing to Update in LSQ Entry (%d) for pc(%d):: %.5s\n", ret, stage->pc, stage->opcode);
					}
				}
				// Also update DRF regs so next they can be dispatched
				switch (cpu->stage[DRF].inst_type) {
					// check single src reg instructions
					case STORE: case LOAD: case MOV: case ADDL: case SUBL: case JUMP:
						if ((cpu->stage[DRF].rs1==stage->rd)&&(cpu->stage[DRF].rs1_valid==INVALID)) {
							cpu->stage[DRF].rs1_value = stage->rd_value;
							cpu->stage[DRF].rs1_valid = stage->rd_valid;
						}
						break;
					// check two src reg instructions
					case STR: case LDR: case ADD: case SUB: case MUL: case DIV: case AND: case OR: case EXOR:
						if ((cpu->stage[DRF].rs1==stage->rd)&&(cpu->stage[DRF].rs1_valid==INVALID)) {
							cpu->stage[DRF].rs1_value = stage->rd_value;
							cpu->stage[DRF].rs1_valid = stage->rd_valid;
						}
						if ((cpu->stage[DRF].rs2==stage->rd)&&(cpu->stage[DRF].rs2_valid==INVALID)) {
							cpu->stage[DRF].rs2_value = stage->rd_value;
							cpu->stage[DRF].rs2_valid = stage->rd_valid;
						}
						break;
					// confirm if for Store we need to read all three src reg
					default:
						break;
				}
			}
		}
		else {
			if (ENABLE_DEBUG_MESSAGES_L2) {
				fprintf(stderr, "Writeback for Stage %d Not Ready to Process\n", cpu_stages[i]);
			}
		}
	}

	return 0;
}

/*
 * ########################################## Dispatch Stage ##########################################
*/
int dispatch_instruction(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table){
	// check if ISQ entry is free and ROB entry is free then dispatch the instruction
	CPU_Stage* stage = &cpu->stage[DRF];
	if (stage->executed) {
		int ret = 0;
		int lsq_index = -1;

		LS_IQ_Entry ls_iq_entry = {
			.inst_type = stage->inst_type,
			.executed = stage->executed,
			.pc = stage->pc,
			.rd = stage->rd,
			.rd_value = stage->rd_value,
			.rd_valid = stage->rd_valid,
			.rs1 = stage->rs1,
			.rs1_value = stage->rs1_value,
			.rs1_valid = stage->rs1_valid,
			.rs2 = stage->rs2,
			.rs2_value = stage->rs2_value,
			.rs2_valid = stage->rs2_valid,
			.buffer = stage->buffer,
			.stage_cycle = INVALID}; // so that which issue is called it stalls this just added inst for at least 1 cycyle

		ROB_Entry rob_entry = {
			.inst_type = stage->inst_type,
			.executed = stage->executed,
			.pc = stage->pc,
			.rd = stage->rd,
			.rd_value = stage->rd_value,
			.rd_valid = stage->rd_valid,
			.rs1 = stage->rs1,
			.rs1_value = stage->rs1_value,
			.rs1_valid = stage->rs1_valid,
			.rs2 = stage->rs2,
			.rs2_value = stage->rs2_value,
			.rs2_valid = stage->rs2_valid,
			.exception = INVALID,
			.buffer = stage->buffer,
			.stage_cycle = INVALID};

		switch (stage->inst_type) {
			case STORE: case STR: case LOAD: case LDR:
				// add entry to LSQ and ROB
				// check if LSQ entry is available and rob entry is available
				if ((can_add_entry_in_issue_queue(issue_queue)==SUCCESS)&&(can_add_entry_in_ls_queue(ls_queue)==SUCCESS)&&(can_add_entry_in_reorder_buffer(rob)==SUCCESS)) {
					ret = add_ls_queue_entry(ls_queue, ls_iq_entry, &lsq_index);
					if(ret==SUCCESS) {
						ret = add_issue_queue_entry(issue_queue, ls_iq_entry, &lsq_index);
						ret = add_reorder_buffer_entry(rob, rob_entry);
					}
					else {
						if (ENABLE_DEBUG_MESSAGES_L2) {
							fprintf(stderr, "LSQ IQ ROB Eentry Failed for Inst Type :: %d\n", stage->inst_type);
						}
					}
				}
				else{
					// stall DRF and Fetch stage
					cpu->stage[DRF].stalled = VALID;
					cpu->stage[F].stalled = VALID;
				}
				break;

			case MOVC ... JUMP:
				// add entry to ISQ and ROB
				// check if IQ entry is available and rob entry is available
				if ((can_add_entry_in_issue_queue(issue_queue)==SUCCESS)&&(can_add_entry_in_reorder_buffer(rob)==SUCCESS)) {
					ret = add_issue_queue_entry(issue_queue, ls_iq_entry, &lsq_index);
					ret = add_reorder_buffer_entry(rob, rob_entry);
					if(ret!=SUCCESS) {
						if (ENABLE_DEBUG_MESSAGES_L2) {
							fprintf(stderr, "IQ ROB Eentry Failed for Inst Type :: %d\n", stage->inst_type);
						}
					}
				}
				else{
					// stall DRF and Fetch stage
					cpu->stage[DRF].stalled = VALID;
					cpu->stage[F].stalled = VALID;
				}
				break;

			case HALT:
				// add entry to ROB
				if (can_add_entry_in_reorder_buffer(rob)==SUCCESS) {
					ret = add_reorder_buffer_entry(rob, rob_entry);
					if(ret!=SUCCESS) {
						if (ENABLE_DEBUG_MESSAGES_L2) {
							fprintf(stderr, "ROB Eentry Failed for Inst Type :: %d\n", stage->inst_type);
						}
					}
				}
				break;

			default:
				break;
		}
	}
	else {
		if (!stage->empty){
			if (ENABLE_DEBUG_MESSAGES_L2) {
				fprintf(stderr, "Dispatch Failed DRF has non executed instruction :: pc(%d) %s\n", stage->pc, stage->opcode);
			}
		}
	}

	return 0;
}

/*
 * ########################################## Issue Stage ##########################################
*/
int issue_instruction(APEX_CPU* cpu, APEX_IQ* issue_queue, APEX_LSQ* ls_queue) {
	// check if respective FU is free and All Regs Value are Valid then issue the instruction
	// get issue_index of all the instruction
	int ret = 0;
	int issue_index[IQ_SIZE] = {[0 ... IQ_SIZE-1] = -1};
	ret = get_issue_queue_index_to_issue(issue_queue, issue_index);
	if (ret==SUCCESS) {
		char* inst_type_str = (char*) malloc(10);
		for (int i=0; i<IQ_SIZE; i++) {
			if (issue_index[i]>-1) {
				int stage_num = -1;

				switch (issue_queue->iq_entries[issue_index[i]].inst_type) {

					case STORE: case STR: case LOAD: case LDR: case MOVC: case MOV: case ADD: case ADDL: case SUB: case SUBL: case DIV: case AND: case OR: case EXOR:
						stage_num = INT_ONE;
						break;

					case MUL:
						stage_num = MUL_ONE;
						break;

					case BZ: case BNZ:
						stage_num = BRANCH;
						break;

					default:
						break;
				}
				if (stage_num>DRF) {
					CPU_Stage* stage = &cpu->stage[stage_num];
					if ((stage->executed)||(stage->empty)) {
						strcpy(inst_type_str, "");
						stage->executed = INVALID;
						stage->empty = INVALID;
						stage->inst_type = issue_queue->iq_entries[issue_index[i]].inst_type;
						get_inst_name(stage->inst_type, inst_type_str);
						strcpy(stage->opcode, inst_type_str);
						stage->pc = issue_queue->iq_entries[issue_index[i]].inst_ptr;
						stage->rd = issue_queue->iq_entries[issue_index[i]].rd;
						stage->rd_value = issue_queue->iq_entries[issue_index[i]].rd_value;
						if ((stage->inst_type==STORE)||(stage->inst_type==STR)) {
							stage->rd_valid = issue_queue->iq_entries[issue_index[i]].rd_ready;;
						}
						else {
							stage->rd_valid = INVALID;
						}
						stage->rs1 = issue_queue->iq_entries[issue_index[i]].rs1;
						stage->rs1_value = issue_queue->iq_entries[issue_index[i]].rs1_value;
						stage->rs1_valid = issue_queue->iq_entries[issue_index[i]].rs1_ready;
						stage->rs2 = issue_queue->iq_entries[issue_index[i]].rs2;
						stage->rs2_value = issue_queue->iq_entries[issue_index[i]].rs2_value;
						stage->rs2_valid = issue_queue->iq_entries[issue_index[i]].rs2_ready;
						stage->buffer = issue_queue->iq_entries[issue_index[i]].literal;
						stage->lsq_index = issue_queue->iq_entries[issue_index[i]].lsq_index;
						// remove the entry from issue_queue or mark it as invalid
						issue_queue->iq_entries[issue_index[i]].status = INVALID;
						issue_queue->iq_entries[issue_index[i]].inst_type = INVALID;
						issue_queue->iq_entries[issue_index[i]].inst_ptr = INVALID;
						issue_queue->iq_entries[issue_index[i]].rd = INVALID;
						issue_queue->iq_entries[issue_index[i]].rd_value = INVALID;
						issue_queue->iq_entries[issue_index[i]].rd_ready = INVALID;
						issue_queue->iq_entries[issue_index[i]].rs1 = INVALID;
						issue_queue->iq_entries[issue_index[i]].rs1_value = INVALID;
						issue_queue->iq_entries[issue_index[i]].rs1_ready = INVALID;
						issue_queue->iq_entries[issue_index[i]].rs2 = INVALID;
						issue_queue->iq_entries[issue_index[i]].rs2_value = INVALID;
						issue_queue->iq_entries[issue_index[i]].rs2_ready = INVALID;
						issue_queue->iq_entries[issue_index[i]].literal = INVALID;
						issue_queue->iq_entries[issue_index[i]].lsq_index = INVALID;
						issue_queue->iq_entries[issue_index[i]].stage_cycle = INVALID;
					}
				}
				if (ENABLE_DEBUG_MESSAGES_L2) {
					fprintf(stderr, "Inst issueed to Unit :: %d\n", stage_num);
				}
			}
		}
		free(inst_type_str);
	}
	else {
		if (ENABLE_DEBUG_MESSAGES_L2) {
			fprintf(stderr, "No Inst to issue to Unit\n");
		}
	}

	int lsq_index = -1;
	ret = get_ls_queue_index_to_issue(ls_queue, &lsq_index);
	if (ret==SUCCESS) {
		char* inst_type_str = (char*) malloc(10);
		CPU_Stage* stage = &cpu->stage[MEM];
		if ((stage->executed)||(stage->empty)) {
			strcpy(inst_type_str, "");
			stage->executed = INVALID;
			stage->empty = INVALID;
			stage->inst_type = ls_queue->lsq_entries[lsq_index].load_store;
			get_inst_name(stage->inst_type, inst_type_str);
			strcpy(stage->opcode, inst_type_str);
			stage->pc = ls_queue->lsq_entries[lsq_index].inst_ptr;
			stage->rd = ls_queue->lsq_entries[lsq_index].rd;
			stage->rd_value = ls_queue->lsq_entries[lsq_index].rd_value;
			stage->rd_valid = ls_queue->lsq_entries[lsq_index].data_ready;
			stage->rs1 = ls_queue->lsq_entries[lsq_index].rs1;
			stage->rs1_value = ls_queue->lsq_entries[lsq_index].rs1_value;
			stage->rs1_valid = VALID;
			stage->rs2 = ls_queue->lsq_entries[lsq_index].rs2;
			stage->rs2_value = ls_queue->lsq_entries[lsq_index].rs2_value;
			stage->rs2_valid = VALID;
			stage->buffer = ls_queue->lsq_entries[lsq_index].literal;
			stage->mem_address = ls_queue->lsq_entries[lsq_index].mem_address;

			// remove the entry from issue_queue or mark it as invalid
			ls_queue->lsq_entries[lsq_index].status = INVALID;
			ls_queue->lsq_entries[lsq_index].load_store = INVALID;
			ls_queue->lsq_entries[lsq_index].inst_ptr = INVALID;
			ls_queue->lsq_entries[lsq_index].mem_valid = INVALID;
			ls_queue->lsq_entries[lsq_index].rd = INVALID;
			ls_queue->lsq_entries[lsq_index].rd_value = INVALID;
			ls_queue->lsq_entries[lsq_index].data_ready = INVALID;
			ls_queue->lsq_entries[lsq_index].literal = INVALID;
			ls_queue->lsq_entries[lsq_index].rs1 = INVALID;
			ls_queue->lsq_entries[lsq_index].rs1_value = INVALID;
			ls_queue->lsq_entries[lsq_index].rs2 = INVALID;
			ls_queue->lsq_entries[lsq_index].rs2_value = INVALID;
			ls_queue->lsq_entries[lsq_index].stage_cycle = INVALID;
		}
		else {
			if (ENABLE_DEBUG_MESSAGES_L2) {
				fprintf(stderr, "Cannot Issue Inst To Mem Stage\n");
			}
		}
	}

	return 0;
}

/*
 * ########################################## Execute Stage ##########################################
*/
int execute_instruction(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table) {
	// check if respective FU has any instructions and execute them
	// call each unit one by one
	// branch will be called last idk y ?
	int_one_stage(cpu, rename_table);
	int_two_stage(cpu);
	mul_one_stage(cpu, rename_table);
	mul_two_stage(cpu);
	mul_three_stage(cpu);
	branch_stage(cpu);
	mem_stage(cpu);

	writeback_stage(cpu, ls_queue, issue_queue, rob, rename_table);

	return 0;
}

/*
 * ########################################## Branch Misprediction Stage ##########################################
*/
void branch_misprediction(APEX_CPU* cpu, ROB_Entry* rob_entry, APEX_ROB* rob, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_RENAME* rename_table) {

	clear_rename_table(rename_table);
	clear_reorder_buffer(rob);

	clear_issue_queue_entry(issue_queue);
	clear_ls_queue_entry(ls_queue);

	// clear all the cpu stages
	// change pc and flush F DRF
	clear_stage_entry(cpu, DRF);
	clear_stage_entry(cpu, F);
	// stall F so it wont fetch in same cycle
	cpu->stage[F].stalled = VALID;

}

/*
 * ########################################## Commit Stage ##########################################
*/
int commit_instruction(APEX_CPU* cpu, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table) {
	// check if rob entry is valid and data is valid then commit instruction and free rob entry
	int ret = -1;

	ROB_Entry* rob_entry = malloc(sizeof(*rob_entry));
	// entry removed from rob
	ret = commit_reorder_buffer_entry(rob, rob_entry);

	if (ret==SUCCESS) {
		if ((rob_entry->inst_type==STORE)||(rob_entry->inst_type==STR)) {
			; // no need to free regs or pass rd value
		}
		else if (rob_entry->inst_type==JUMP) {
			; // no need to free regs or pass rd value
		}
		else if (rob_entry->inst_type==BZ) {
			// no need to free regs or pass rd value
			if ((cpu->flags[ZF]==VALID)&&(rob_entry->exception)) {
				// branch misspredicted
				// revert the changes
				branch_misprediction(cpu, rob_entry, rob, ls_queue, issue_queue, rename_table);
				// pc of branch inst plus 4 will be nex pc
				cpu->pc = rob_entry->pc + 4;
			}
		}
		else if (rob_entry->inst_type==BNZ) {
			// no need to free regs or pass rd value
			if ((cpu->flags[ZF]==INVALID)&&(rob_entry->exception)) {
				// branch misspredicted
				// revert the changes
				branch_misprediction(cpu, rob_entry, rob, ls_queue, issue_queue, rename_table);
				// pc of branch inst plus 4 will be nex pc
				cpu->pc = rob_entry->pc + 4;
			}
		}
		else if (rob_entry->inst_type==HALT) {
			// exit the simulation
			return HALT;
		}
		else {
			// also update IQ here as well
			LS_IQ_Entry ls_iq_entry = {
				.inst_type = rob_entry->inst_type,
				.executed = rob_entry->executed,
				.pc = rob_entry->pc,
				.rd = rob_entry->rd,
				.rd_value = rob_entry->rd_value,
				.rd_valid = rob_entry->rd_valid,
				.rs1 = rob_entry->rs1,
				.rs1_value = rob_entry->rs1_value,
				.rs1_valid = rob_entry->rs1_valid,
				.rs2 = rob_entry->rs2,
				.rs2_value = rob_entry->rs2_value,
				.rs2_valid = rob_entry->rs2_valid,
				.buffer = rob_entry->buffer,
				.stage_cycle = rob_entry->stage_cycle};

			ret = update_issue_queue_entry(issue_queue, ls_iq_entry);
			if (ret==FAILURE) {
				if (ENABLE_DEBUG_MESSAGES_L2) {
					fprintf(stderr, "Commit Failed to Update IQ Entry (%d) for pc(%d)\n", ret, ls_iq_entry.pc);
				}
			}

			ret = update_ls_queue_entry_reg(ls_queue, ls_iq_entry);
			if (ret==FAILURE) {
				if (ENABLE_DEBUG_MESSAGES_L2) {
					fprintf(stderr, "Commit Nothing to Update in LSQ Entry (%d) for pc(%d)\n", ret, ls_iq_entry.pc);
				}
			}

			// put the value in DRF
			switch (cpu->stage[DRF].inst_type) {
				// check single src reg instructions
				case STORE: case LOAD: case MOV: case ADDL: case SUBL: case JUMP:
				if ((cpu->stage[DRF].rs1==rob_entry->rd)&&(cpu->stage[DRF].rs1_valid==INVALID)) {
					cpu->stage[DRF].rs1_value = rob_entry->rd_value;
					cpu->stage[DRF].rs1_valid = rob_entry->rd_valid;
				}
				break;
				// check two src reg instructions
				case STR: case LDR: case ADD: case SUB: case MUL: case DIV: case AND: case OR: case EXOR:
				if ((cpu->stage[DRF].rs1==rob_entry->rd)&&(cpu->stage[DRF].rs1_valid==INVALID)) {
					cpu->stage[DRF].rs1_value = rob_entry->rd_value;
					cpu->stage[DRF].rs1_valid = rob_entry->rd_valid;
				}
				if ((cpu->stage[DRF].rs2==rob_entry->rd)&&(cpu->stage[DRF].rs2_valid==INVALID)) {
						cpu->stage[DRF].rs2_value = rob_entry->rd_value;
						cpu->stage[DRF].rs2_valid = rob_entry->rd_valid;
				}
				break;
				// confirm if for Store we need to read all three src reg
				default:
				break;
			}
		// change decs reg in cpu
		// undo the renaming
		// put the value in arch reg and increment valid valid count
		int src_reg = -1;
		src_reg = get_phy_reg_renamed_tag(rob_entry->rd, rename_table);
		if (src_reg<0) {
			if (ENABLE_DEBUG_MESSAGES_L2) {
				fprintf(stderr, "Commit Failed to Rename :: P%d for pc(%d)\n", rob_entry->rd, rob_entry->pc);
			}
		}
		else {
			// free the physical regs
			cpu->regs[src_reg] = rob_entry->rd_value;
			rename_table->reg_rename[rob_entry->rd].tag_valid = INVALID;
			set_reg_status(cpu, src_reg, -1);
			}
		}
	}
	else {
		printf("Failed to Commit Rob Entry\n");
	}

	return 0;
}

/*
 * ########################################## CPU Run ##########################################
*/

int APEX_cpu_run(APEX_CPU* cpu, int num_cycle, APEX_LSQ* ls_queue, APEX_IQ* issue_queue, APEX_ROB* rob, APEX_RENAME* rename_table) {

	int ret = 0;

	while (ret==0) {

		/* Requested number of cycle committed, so pause and exit */
		if ((num_cycle>0)&&(cpu->clock == num_cycle)) {
			printf("\n--------------------------------\n");
			printf("Requested %d Cycle Completed", num_cycle);
			printf("\n--------------------------------\n");
			break;
		}
		else {
			cpu->clock++; // places here so we can see prints aligned with executions

			if (ENABLE_DEBUG_MESSAGES) {
				printf("\n--------------------------------\n");
				printf("Clock Cycle #: %d\n", cpu->clock);
				printf("%-15s: Executed: Instruction\n", "Stage");
				printf("--------------------------------\n");
			}

			int stage_ret = 0;
			// commit inst
			stage_ret = commit_instruction(cpu, ls_queue, issue_queue, rob, rename_table);
			if (stage_ret==HALT) {
				ret = stage_ret;
			}
			// adding inst to FU
			stage_ret = issue_instruction(cpu, issue_queue, ls_queue);
			// executing inst
			stage_ret = execute_instruction(cpu, ls_queue, issue_queue, rob, rename_table);
			// adding inst to IQ, LSQ, ROB
			stage_ret = dispatch_instruction(cpu, ls_queue, issue_queue, rob, rename_table);
			// push only before IQ Stages
			push_func_unit_stages(cpu, INVALID);
			// only renaming happens
			stage_ret = decode(cpu, rename_table);
			// after renaming is done just fetch the values from CPU OUTPUT Stages
			// and update the DRF stage so while dispatching dependencies are handled
			// fetch inst from code memory
			stage_ret = fetch(cpu);
			// dispatch func will have rename call inside
			print_ls_iq_content(ls_queue, issue_queue);
			print_rob_and_rename_content(rob, rename_table);

			// push only after IQ Stages
			push_func_unit_stages(cpu, VALID);

			// if ((stage_ret!=HALT)&&(stage_ret!=SUCCESS)) {
			// 	ret = stage_ret;
			// }
		}
	}

	return ret;
}

/*
 * #############################################################################################
 * ########################################## Main Function (Driver) ##########################################
 * #############################################################################################
*/

int main(int argc, const char * argv[]) {
    
    /*char *buffer = malloc(100);
    strcpy(buffer, "0016 sub R2, R0, R1");
    CPU_Instruction* ins = malloc(sizeof(ins));
    create_CPU_instruction(ins, buffer);
    print_Instruction(ins);
    
    
    strcpy(buffer, "0020 bgez R2, #0028\n");
    CPU_Instruction* ins2 = malloc(sizeof(ins));
    create_CPU_instruction(ins2, buffer);
    print_Instruction(ins2);*/
    
    char command[20];
	char* cmd;
	int num_cycle = 0;
	char func[10];
	// argc = count of arguments, executable being 1st argument in argv[0]
	if ((argc == 4)||(argc == 2)) {
		fprintf(stderr, "APEX_INFO : Initializing CPU !!!\n");
		APEX_CPU* cpu = APEX_cpu_init(argv[1]);
		APEX_LSQ* ls_queue = init_ls_queue();
		APEX_IQ* issue_queue = init_issue_queue();
		APEX_ROB* rob = init_reorder_buffer();
		APEX_RENAME* rename_table = init_rename_table();

		if ((!cpu)||(!issue_queue)||(!ls_queue)||(!rob)||(!rename_table)) {
			fprintf(stderr, "APEX_Error : Unable to initialize CPU\n");
			exit(1);
		}
		int ret = 0;
		if (argc == 4) {
			strcpy(func, argv[2]);
			num_cycle = atoi(argv[3]);
			if (((strcmp(func, "display") == 0)||(strcmp(func, "simulate")==0))&&(num_cycle>0)) {
				ret = APEX_cpu_run(cpu, num_cycle, ls_queue, issue_queue, rob, rename_table);
				if (ret == SUCCESS) {
					printf("Simulation Complete\n");
				}
				else {
					printf("Simulation Return Code %d\n",ret);
				}
				if (strcmp(func, "display") == 0) {
					// show everything
					print_cpu_content(cpu);
					print_ls_iq_content(ls_queue, issue_queue);
					print_rob_and_rename_content(rob, rename_table);
				}
			}
			else {
				fprintf(stderr, "Invalid parameters passed !!!\n");
				if (!num_cycle) {
					fprintf(stderr, "Number of Cycles cannot be 0\n");
				}
				fprintf(stderr, "APEX_Help : Usage %s <input_file> <func(eg: simulate Or display)> <num_cycle>\n", argv[0]);
				exit(1);
			}
		}
		else if (argc == 2) {
			while (ret==0) {
				fprintf(stderr, "Usage ?: <func(eg: simulate Or display)> <num_cycle>\n");
				fprintf(stderr, "Exit : exit<space><entre>\n");
				fgets(command, 20, stdin);
				cmd = strtok (command," ");
				strcpy(func, cmd);
				cmd = strtok (NULL," ");
				num_cycle = atoi(cmd);
				if (strcmp(func, "exit") == 0) {
					printf("Terminating Simulation\n");
					ret = 1;
					break;
				}
				if (((strcmp(func, "display") == 0)||(strcmp(func, "simulate")==0))&&(num_cycle>0)) {
					ret = APEX_cpu_run(cpu, num_cycle, ls_queue, issue_queue, rob, rename_table);
					if (ret == SUCCESS) {
						printf("Simulation Complete\n");
					}
					else {
						printf("Simulation Return Code %d\n",ret);
					}
					if (strcmp(func, "display") == 0) {
						// show everything
						print_cpu_content(cpu);
						print_ls_iq_content(ls_queue, issue_queue);
						print_rob_and_rename_content(rob, rename_table);
					}
					// printf("FUNC :: %s, CYCLE  :: %d\n",func, num_cycle);
				}
				else {
					fprintf(stderr, "Invalid parameters passed !!!\n");
					if (!num_cycle) {
						fprintf(stderr, "Number of Cycles cannot be 0\n");
					}
					fprintf(stderr, "APEX_Help : Usage %s <input_file> <func(eg: simulate Or display)> <num_cycle>\n", argv[0]);
				}
			}
		}
		printf("Press Any Key to Exit Simulation\n");
		getchar();
		deinit_issue_queue(issue_queue);
		deinit_ls_queue(ls_queue);
		deinit_rename_table(rename_table);
		deinit_reorder_buffer(rob);
		APEX_cpu_stop(cpu);
	}
	else {
		fprintf(stderr, "Invalid parameters passed !!!\n");
		fprintf(stderr, "APEX_Help : For One Time Execution !!!\n");
		fprintf(stderr, "Type: %s <input_file> <func(eg: simulate Or display)> <num_cycle>\n", argv[0]);
		fprintf(stderr, "APEX_Help : For N Time Execution !!!\n");
		fprintf(stderr, "Type: %s <input_file>\n", argv[0]);
		exit(1);
	}
	return 0;
}
