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
}tableSruct;

int tid_column[9];
int tid_row[9];
int tid_3x3[9];


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

void columnRunner(void* param) {
    tableStruct *parameters;
    int topRow, bottomRow, leftColumn, rightColumn;
    int i, j;
    pthread_t self;

    parameters = (tableStruct *) param;

    topRow = parameters->topRow;
    bottomRow = parameters->bottomRow;
    leftColumn = parameters->leftColumn;
    rightColumn = parameters->rightColumn;

    for(int f = 0; f < 9; f++){
        column[f] = false;
    }

    for (int i = topRow; i <= bottomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            if (sudokuPuzzle[i][j] > 0 && sudokuPuzzle[i][j] < 10)
                column[sudokuPuzzle[i][j]] = true;
        }
    }
    self = pthread_self();
    pthread_exit(0);
}
void rowRunner(void* param) {
    tableStruct *parameters;
    int topRow, bottomRow, leftColumn, rightColumn;
    int i, j;
    pthread_t self;

    parameters = (tableStruct *) param;

    topRow = parameters->topRow;
    bottomRow = parameters->bottomRow;
    leftColumn = parameters->leftColumn;
    rightColumn = parameters->rightColumn;

    for(int f = 0; f < 9; f++){
        row[f] = false;
    }

    for (int i = topRow; i <= bottomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            if (sudokuPuzzle[i][j] > 0 && sudokuPuzzle[i][j] < 10)
                row[sudokuPuzzle[i][j]] = true;
        }
    }
    self = pthread_self();
    pthread_exit(0);
}
void 3x3Runner(void* param) {
    tableStruct *parameters;
    int topRow, bottomRow, leftColumn, rightColumn;
    int i, j;
    pthread_t self;

    parameters = (tableStruct *) param;

    topRow = parameters->topRow;
    bottomRow = parameters->bottomRow;
    leftColumn = parameters->leftColumn;
    rightColumn = parameters->rightColumn;

    for(int f = 0; f < 9; f++){
        threebythree[f] = false;
    }

    for (int i = topRow; i <= bottomRow; i++) {
        for (int j = leftColumn; j <= rightColumn; j++) {
            if (sudokuPuzzle[i][j] > 0 && sudokuPuzzle[i][j] < 10)
                threebythree[sudokuPuzzle[i][j]] = true;
        }
    }
    self = pthread_self();
    pthread_exit(0);
}

int main() {

    fillPuzzle();
    int index = 0;

    //Two variables for the 3x3
    int k = 2;
    int l = 2;

    pthread_t tid[num_threads];
    pthread_attr_t attr[num_threads];
    tableSruct thrParam[num_threads];

    for( i = 0; i < num_threads; i++){
        pthread_attr_init(&(attr[i]));
    }

    // Column
    for( int i = 0; i < 9; i++) {
        thrParam[index] = {0, 8, i, i};
        pthread_create(&(tid[index]), &(attr[index]), runner, thrParam[index]);
        tid_column[i] = tid[index];
        index++;
    }
    //Row
    for(int i = 0; i < 9; i++){
        thrParam[index] = {i, i, 0, 8 };
        pthread_create(&(tid[index]), &(attr[index]), runner, thrParam[index]);
        tid_column[i] = tid[index];
        index++;
    }
    // 3x3
    for( int i = 0; i< 9; i + 3 ){
            k + 3;
        for( int j = 0; i < 9; i + 3){
            l + 3;
            thrParam = {i, k, j, l};
            pthread_create(&(tid[index]), &(attr[index]), runner, thrParam[index]);
            tid_3x3[i] = tid[index];
            index++;
        }
    }
    for ( i = 0; i < num_threads; i++){
       pthread_join(tid_column[i], NULL);
       pthread_join(tid_row[i], NULL);
       pthread_join(tid_3x3[i], NULL);

    }

}