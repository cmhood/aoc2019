#!/usr/bin/tcc -run
#include <stdio.h>
#include <stdlib.h>

static int calculate_fuel(int);

int
main(void)
{
	int silver = 0, gold = 0, mass;
	while (scanf("%d\n", &mass) == 1) {
		silver += mass / 3 - 2;
		gold += calculate_fuel(mass);
	}
	if (!feof(stdin)) {
		fprintf(stderr, "parse error\n");
		exit(EXIT_FAILURE);
	}
	printf("%d\n%d\n", silver, gold);
}

static int
calculate_fuel(int mass)
{
	mass = mass / 3 - 2;
	if (mass <= 0) {
		return 0;
	}
	return mass + calculate_fuel(mass);
}
