/*
 ============================================================================
 Name        : travelling-salesman.c
 Author      : 
 Version     :
 Copyright   : none :)
 Description : solution to travelling salesman problem
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//prototypes
void makeMatrix(int rows, int columns, int matrix[rows][columns], int stops, int coordinates[stops][2]);
void printMatrix(int rows, int columns, int matrix[rows][columns]);
void nearestNeighbour(int stops, int coordinates[stops][2]);

int main(void) {
	//define rows, columns of a grid and number of stops (cities)
	int rows = 10, columns = 10;
	int matrix[rows][columns];
	int stops = 10;
	//misc
	int coordinates[stops][2];
	//call function to create, print and solve
	makeMatrix(rows, columns, matrix, stops, coordinates);
	printMatrix(rows, columns, matrix);
	nearestNeighbour(stops, coordinates);
	return 0;
}

void makeMatrix(int rows, int columns, int matrix[rows][columns], int stops, int coordinates[stops][2]){
	//seed for RNG
	srand (time(NULL));

	//create randomly filled coordinates matrix - number of stops changes number of rows, number of rows changes range of RNG - for matrix 100x100 it goes from 0 to 100.
	int i, j, k, l;
	for(k = 0; k<stops; k++){
		for(l = 0; l<2; l++){
			coordinates[k][l] = rand() % rows;
			//printf("%d ", coordinates[k][l]);

		}
		//printf("\n");
	}

	//fill whole matrix with -1
	for(i = 0; i<rows; i++){
		for(j = 0; j<columns; j++){
			matrix[i][j] = -1;
		}
	}
	//assign a number of a stop to corresponding coordinate, pulled from "coordinates" matrix, which is randomly filled
	for(i=0; i<stops; i++){
		for(j=0; j<2; j++){
			int row = coordinates[i][0];
			int column = coordinates[i][1];
			matrix[row][column] = i;
			//printf("%d", i);
		}
	}
}

void printMatrix(int rows, int columns, int matrix[rows][columns]){
	//for every element of every row print a number of a stop or blank space if it's equal to -1 (eg empty, not a stop)
	for(int i = 0; i<rows; i++){
			for(int j = 0; j<columns; j++){
				if(matrix[i][j] == -1){
					printf("   ");
				}
				else{
					printf("%3d", matrix[i][j]);
				}

			}
			printf("\n");
	}
}
void nearestNeighbour(int stops, int coordinates[stops][2]){
	float currdist = 0.0;
	float dist = 0.0;
	float totaldist = 0.0;
	int position = 0;
	int nxtposition = 0;
	int used[stops];
	//fill used stops matrix with zeroes
	for(int k = 0; k < stops; k++){
		used[k] = 0;
	}
	//set starting point to used
	used[0] = 1;

	//main loop of algorithm
	for (int j = 0; j < stops; j++) {
		//set dist and nxtposition to 0 every iteration
		dist = 0.0;
		nxtposition = 0;
		for(int i = 0; i < stops; i++){
			//calculate distance to i-th point, pulled from coordinates matrix
			currdist = sqrt(pow(coordinates[position][0]-coordinates[i][0], 2)+pow(coordinates[position][1]-coordinates[i][1], 2));

			//printf("\nx1 = %d, x2 = %d, y1 = %d. y2 = %d\n", coordinates[position][0], coordinates[i][0], coordinates[position][1], coordinates[i][1]);
			//printf("%f %f    ", currdist, dist);

			//if current distance is smaller than last smallest distance, change distance and position
			if((currdist < dist) || (dist == 0)){
				//check if point is already used
				if(used[i] != 1){
					dist = currdist;
					nxtposition = i;

				}
			}
		}
		//set position to used, calculate total distance
		used[nxtposition] = 1;
		printf("position is %d \n", nxtposition);
		position = nxtposition;
		totaldist += dist;

	}
	printf("total distance travelled is: %f", totaldist);
}
