#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int read_instruction(unsigned char MEM[], unsigned int i, unsigned int n);
void translate_instruction(int IR);

int main()
{
	FILE* fp = NULL;
	unsigned int i = 0, j =0;
	unsigned int instruction_number = 0;
	unsigned int data_number = 0;
	unsigned int IR = 0;
	unsigned char MEM[512] = { 0 };

	fp = fopen("machine_example\\as_ex01_arith.bin", "rb");

	if (fp == NULL)
	{
		printf("오류발생\n");
		return 0;
	}

	while (feof(fp) == 0)
	{
		fseek(fp, i * 4, SEEK_SET);
		fread(&MEM[i * 4], sizeof(int), 1, fp);
		i++;
	}

	instruction_number = read_instruction(MEM, 0, 4);	
	data_number = read_instruction(MEM, 4, 8);

	printf("Number of Instructions: %d, ", instruction_number);
	printf("Number of Data: %d\n", data_number);

	
	for (i = 8; i < instruction_number * 4 + 8; i += 4)
	{
		IR = read_instruction(MEM, i, i + 4);
		translate_instruction(IR);
	}
	

	fclose(fp);

	return 0;
}

int read_instruction(unsigned char MEM[], unsigned int i, unsigned int n)
{
	int result = 0;

	for (; i < n; i++)
	{
		result |= MEM[i];

		if (i == n - 1)
		{
			break;
		}

		result <<= 8;
	}

	return result;
	
}

void translate_instruction(int IR)
{
	int opcode = 0;
	int funct = 0;
	char* opcode_table[] =
	{"R", "bltz", "j", "jal", "beq", "bne", 0, 0, "addi", 0, "slti", 0, "andi", "ori", "xori", "lui", 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "lb", 0, 0, "lw", "lbu", 0, 0, 0, "sb", 0, 0, "sw", 0, 0, 0, 0};
	char* funct_table[] =
	{ "sll", 0, "srl", "sra", 0, 0, 0, 0, "jr", 0, 0, 0, "syscall", 0, 0, 0, "mfhi", 0, "mflo", 0, 0, 0, 0, 0,
		"mul", 0, 0, 0, 0, 0, 0, 0, "add", 0, "sub", 0, "and", "or", "xor", "nor", 0, 0, "slt", 0, 0, 0, 0, 0 };


	opcode = (0xFC000000 & IR) >> 26;
	funct = 0x0000003F & IR;


	printf("Opc: %2x, Fct: %2x, Inst: %s\n", opcode, funct, opcode_table[opcode] == "R" ? funct_table[funct] : opcode_table[opcode]);
		
}
