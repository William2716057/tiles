#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	int tiles[2][6];

	srand(time(NULL));

	for (int col = 0; col < 6; col++) {
		tiles[0][col] = rand() %2;
		tiles[1][col] = 1 - tiles[0][col];

		}

	for (int row = 0; row < 2; row++) {
		for (int col = 0; col < 6; col++) {
			printf("[%d] ", tiles[row][col]);
		}
		printf("\n");
	}

	return 0;
}
