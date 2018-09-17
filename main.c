#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define num_threads 27
#define in_file "SudokuPuzzle.txt"


int valid[num_threads] = {0};

typedef int bool;
#define true 1;
#define false 0;

typedef struct {
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
}params;

int sudokuPuzzle[9][9];
bool columns[9];
bool rows[9];
bool threebythree[9];

void fillPuzzle(){
    FILE *fp = fopen(in_file, "r");

    int num;
    int i;
    int j;

    for(i=0; i < 9; i++){
        for(j=0; j < 9; j++){
            num = fscanf(fp, " %1d, &num");
            sudokuPuzzle[i][j] = num;
        }
    }
    for (i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            printf("%d ", sudokuPuzzle[i][j]);
            printf("\n");
        }
    }
    fclose(fp);
}

void validateColumns(void* param){

}

void validateRows(void* param){

}

void validate3x3(void* param){

}

int main() {
    pthread_t tid[num_threads];
    pthread_attr_t attr[num_threads];
    params thrParam[num_threads];
    
    int index = 0;
    int i,j,k,l;

    fillPuzzle();
    params *position;

    position = (params *)param;
    while( i < 9 ){
        pthread_create(&tid, )
    }
}