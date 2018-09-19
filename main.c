#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define num_threads 27
#define in_file "SudokuPuzzle.txt"


int valid[num_threads] = {0};

typedef int bool;
#define TRUE 1
#define FALSE 0

typedef struct {
    int topRow;
    int bottomRow;
    int leftColumn;
    int rightColumn;
}tableStruct;

int tid_column[9];
int tid_row[9];
int tid_3x3[9];


int sudokuPuzzle[9][9];
bool columns[9];
bool rows[9];
bool threebythree[9];
bool validCol = TRUE;
bool validRow = TRUE;
bool validSub = TRUE;

void fillPuzzle(){
    FILE *fp = fopen(in_file, "r");

    int num;
    int digit;
    int i;
    int j;

    for(i=0; i < 9; i++){
        for(j=0; j < 9; j++){
            num = fscanf(fp, " %d,", &digit );
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


void *columnRunner(void *param) {
    tableStruct *parameters;
    int topRow, bottomRow, leftColumn, rightColumn;
    int i, j, f;
    pthread_t self;

    parameters = (tableStruct *) param;

    topRow = parameters->topRow;
    bottomRow = parameters->bottomRow;
    leftColumn = parameters->leftColumn;
    rightColumn = parameters->rightColumn;

    for( f = 0; f < 9; f++){
        columns[f] = FALSE;
    }

    for ( i = topRow; i <= bottomRow; i++) {
        for ( j = leftColumn; j <= rightColumn; j++) {
            if (sudokuPuzzle[i][j] > 0 || sudokuPuzzle[i][j] < 10)
                columns[sudokuPuzzle[i][j]] = TRUE;
        }
    }
    self = pthread_self();
    pthread_exit(0);
}
void *rowRunner(void *param) {
    tableStruct *parameters;
    int topRow, bottomRow, leftColumn, rightColumn;
    int i, j, f;
    pthread_t self;

    parameters = (tableStruct *) param;

    topRow = parameters->topRow;
    bottomRow = parameters->bottomRow;
    leftColumn = parameters->leftColumn;
    rightColumn = parameters->rightColumn;

    for( f = 0; f < 9; f++){
        rows[f] = FALSE;
    }

    for (i = topRow; i <= bottomRow; i++) {
        for ( j = leftColumn; j <= rightColumn; j++) {
            if (sudokuPuzzle[i][j] > 0 || sudokuPuzzle[i][j] < 10)
                rows[sudokuPuzzle[i][j]] = TRUE;
        }
    }
    self = pthread_self();
    pthread_exit(0);
}
void *subRunner(void *param) {
    tableStruct *parameters;
    int topRow, bottomRow, leftColumn, rightColumn;
    int i, j, f;
    pthread_t self;

    parameters = (tableStruct *) param;

    topRow = parameters->topRow;
    bottomRow = parameters->bottomRow;
    leftColumn = parameters->leftColumn;
    rightColumn = parameters->rightColumn;

    for(f = 0; f < 9; f++){
        threebythree[f] = FALSE;
    }

    for ( i = topRow; i <= bottomRow; i++) {
        for ( j = leftColumn; j <= rightColumn; j++) {
            if (sudokuPuzzle[i][j] > 0 || sudokuPuzzle[i][j] < 10)
                threebythree[sudokuPuzzle[i][j]] = TRUE;
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
    int i = 0;

    pthread_t tid[num_threads];
    pthread_attr_t attr[num_threads];
    tableStruct thrParam[num_threads];

    for( i = 0; i < num_threads; i++){
        pthread_attr_init(&(attr[i]));
    }

    // Column
    for( i = 0; i < 9; i++) {
        thrParam[index].topRow = 0;
        thrParam[index].bottomRow = 8;
        thrParam[index].leftColumn = i;
        thrParam[index].rightColumn = i;
        pthread_create(&(tid[index]), &(attr[index]), *columnRunner, &(thrParam[index]));
        tid_column[i] = tid[index];
        index++;
    }
    //Row
    for(i = 0; i < 9; i++){
        thrParam[index].topRow = i;
        thrParam[index].bottomRow = i;
        thrParam[index].leftColumn = 0;
        thrParam[index].rightColumn = 8;
        pthread_create(&(tid[index]), &(attr[index]), *rowRunner, &(thrParam[index]));
        tid_column[i] = tid[index];
        index++;
    }
    // 3x3
    for( i = 0; i< 9; i + 3 ){
            int j;
            k + 3;
        for(  j = 0; j < 9; j + 3){
            l + 3;
            thrParam[index].topRow = i;
            thrParam[index].bottomRow = k;
            thrParam[index].leftColumn = j;
            thrParam[index].rightColumn = l;
            pthread_create(&(tid[index]), &(attr[index]), *subRunner, &(thrParam[index]));
            tid_3x3[i] = tid[index];
            index++;
        }
        l = 0;
    }
    for ( i = 0; i < num_threads; i++){
       pthread_join(tid[i], NULL);
    }
    for(i = 0; i < 9; i++){
        if( columns[i] == FALSE ) {
            printf("Column: %d is invalid!", tid_column[i]);
            printf("\n");
            validCol = FALSE;
            exit(0);
        }
        else{
            printf("Column: %d is valid!", tid_column[i]);
            printf("\n");
            exit(0);
        }


        if( rows[i] == FALSE ) {
            printf("Row: %d is invalid!", tid_row[i]);
            printf("\n");
            validRow = FALSE;
            exit(0);
        }
        else{
            printf("Row: %d is valid!", tid_row[i]);
            printf("\n");
            exit(0);
        }

        if( threebythree[i] == FALSE ) {
            printf("Subgrid: %d is invalid", tid_3x3[i]);
            printf("\n");
            validSub = FALSE;
            exit(0);
        }
        else{
            printf("Subgrid: %d is valid", tid_3x3[i]);
            printf("\n");
            exit(0);
        }

    }

    if(validRow, validCol, validSub == FALSE){
        printf("Sudoku Solution is invalid");
    }
    else{
        printf("Sudoku Solution is valid");
    }

}