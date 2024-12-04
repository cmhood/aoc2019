#!/usr/bin/tcc -run
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

static uint32_t execute(uint32_t const *, uint32_t, uint32_t);
static int step(uint32_t *, uint32_t *);

int
main(void)
{
	uint32_t program[256] = {0};

	char c = ',';
	for (int i = 0; c == ','; ++i) {
		if (i >= 256 || scanf("%d%c", &program[i], &c) != 2) {
			fprintf(stderr, "parse error\n");
			exit(EXIT_FAILURE);
		}
	}

	uint32_t silver = execute(program, 12, 2);
	printf("%" PRIu32 "\n", silver);

	for (int i = 0; i < 10000; ++i) {
		uint32_t x = i / 100;
		uint32_t y = i % 100;
		uint32_t result = execute(program, x, y);
		if (result == 19690720) {
			printf("%d\n", i);
			break;
		}
	}
}

static uint32_t
execute(uint32_t const *program, uint32_t x, uint32_t y)
{
	uint32_t memory[256];
	memcpy(memory, program, sizeof(memory));

	memory[1] = x;
	memory[2] = y;

	uint32_t pc = 0;
	while (!step(memory, &pc)) {}

	return memory[0];
}

static int
step(uint32_t *memory, uint32_t *pc)
{
	uint32_t opcode = memory[*pc];

	if (opcode == 99) {
		return 1;
	}
	if (!(1 <= opcode && opcode <= 2)) {
		fprintf(stderr, "unknown opcode\n");
		exit(EXIT_FAILURE);
	}

	uint32_t indices[3];
	for (int i = 0; i < 3; ++i) {
		indices[i] = memory[*pc + i + 1];
		if (indices[i] >= 256) {
			fprintf(stderr, "operand out of bounds\n");
			exit(EXIT_FAILURE);
		}
	}

	uint32_t l = memory[indices[0]], r = memory[indices[1]];
	memory[indices[2]] = opcode == 1 ? l + r : l * r;

	*pc += 4;
	if (*pc >= 128) {
		fprintf(stderr, "pc out of bounds\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
