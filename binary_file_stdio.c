#pragma warning(disable : 4996) //컴파일러 경고 해제, fopen_s말고 그냥 fopen 함수를 쓰기 위함.
#include <stdio.h>
#define M_SIZE 512 //메모리로 쓸 배열 크기 기호상수로 정의
#define INST_SIZE 4 //명령어의 크기 정의, 명령어가 4바이트 단위여서 4로 정의
#define ERROR -1 //오류 발생 메세지

int read_instruction(const unsigned char MEM[], unsigned int i, const unsigned int n); //메모리에 저장한 명령어들을 읽어오는 함수 원형
void translate_instruction(const int IR); //읽어온 명령어들을 해석 후 출력하는 함수 원형

int main()
{
	FILE* fp = NULL; //파일을 읽어올 파일 포인터
	unsigned int i = 0; //반복문에 쓸 변수
	unsigned int instruction_number = 0; //명령어의 개수를 저장할 변수
	unsigned int data_number = 0; //데이터의 개수를 저장할 변수
	unsigned int IR = 0; //명령어를 저장할 변수
	unsigned char MEM[M_SIZE] = { 0 }; //파일에서 불러오는 명령어들을 저장할 변수

	fp = fopen("machine_example\\as_ex01_arith.bin", "rb"); //파일 열기

	if (fp == NULL) //파일 열기 오류 발생시 처리
	{
		printf("파일 열기 오류발생\n"); //문구 출력 후 종료
		return ERROR;
	}

	while (feof(fp) == 0) //파일포인터가 파일의 끝에 도달할 때까지
	{
		fseek(fp, i * INST_SIZE, SEEK_SET); //파일포인터의 위치를 4바이트씩 증가시킴.
		fread(&MEM[i * INST_SIZE], INST_SIZE, 1, fp); //파일포인터의 현 위치에서 메모리에 명령어를 4바이트씩 MEM에 저장함.
		i++; //인덱스 증가
	}

	instruction_number = read_instruction(MEM, 0, INST_SIZE); //명령어의 개수를 불러옴. (처음 4바이트는 명령어의 개수)
	data_number = read_instruction(MEM, INST_SIZE, INST_SIZE * 2); //데이터의 개수를 불러옴. (그 다음 4바이트는 데이터의 개수)

	printf("Number of Instructions: %d, ", instruction_number); //명령어의 개수 출력
	printf("Number of Data: %d\n", data_number); //데이터의 개수 출력

	
	for (i = 8; i < instruction_number * INST_SIZE + INST_SIZE * 2 ; i += INST_SIZE) //명령어의 개수에 명령어의 크기 단위를 곱한만큼 루프를 돔. (+8은 i가 8부터 시작해서)
	{
		IR = read_instruction(MEM, i, i + INST_SIZE); //명령어를 차례대로 IR에 읽어온 후
		translate_instruction(IR); //IR를 해석하여 출력
	}

	fclose(fp); //파일 닫기

	return 0;
}

int read_instruction(const unsigned char MEM[], unsigned int i, const unsigned int n)
{
	int result = 0; //명령어를 저장할 변수

	for (; i < n; i++)
	{
		result |= MEM[i]; //명령어를 비트 OR 연산하여 저장함.

		if (i == n - 1) //마지막 비트 OR 연산 후 탈출
		{
			break;
		}

		result <<= 8; //그 다음 명령어가 순서 대로 쌓일 수 있게 1바이트만큼 왼쪽으로 비트시프트 연산함.
	}

	return result; //결과 반환
	
}

void translate_instruction(const int IR)
{
	int opcode = 0; //opcode를 저장할 변수
	int funct = 0; //funct를 저장할 변수
	const char* opcode_table[] = //opcode 선택을 위한 룩업테이블
	{"R", "bltz", "j", "jal", "beq", "bne", 0, 0, "addi", 0, "slti", 0, "andi", "ori", "xori", "lui", 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "lb", 0, 0, "lw", "lbu", 0, 0, 0, "sb", 0, 0, "sw", 0, 0, 0, 0};
	const char* funct_table[] = //funct 선택을 위한 룩업테이블
	{ "sll", 0, "srl", "sra", 0, 0, 0, 0, "jr", 0, 0, 0, "syscall", 0, 0, 0, "mfhi", 0, "mflo", 0, 0, 0, 0, 0,
		"mul", 0, 0, 0, 0, 0, 0, 0, "add", 0, "sub", 0, "and", "or", "xor", "nor", 0, 0, "slt", 0, 0, 0, 0, 0 };


	opcode = (0xFC000000 & IR) >> 26; //상위 6비트만 IR와 비트 AND 연산하여 추출 후 오른쪽으로 26비트만큼 시프트 연산하여 opcode를 만듬.
	funct = 0x0000003F & IR; //하위 6비트만 IR와 비트 AND 연산하여 추출


	printf("Opc: %2x, Fct: %2x, Inst: %s\n", opcode, funct, opcode_table[opcode] == "R" ? funct_table[funct] : opcode_table[opcode]); //R-format인 경우와 아닌 경우 나눠서 출력
		
}
