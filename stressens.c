#include<stdio.h>
 #include<math.h>
 #include<stdlib.h>
 #include<time.h>
 
 // int upper = 1000, lower = -1000;
 void fillMatrices(int n, int a[n][n], int b[n][n]){
     for(int i=0; i<n; i++){
         for(int j=0; j<n; j++){
             a[i][j] = rand();
             b[i][j] = rand();
             // a[i][j] = (rand() % (upper - lower + 1)) + lower;
             // b[i][j] = (rand() % (upper - lower + 1)) + lower;
         }
     }
 }
 
 void printMatrix(int n, int matrix[][n], char *name){
     printf("Matrix %s: \n", name);
     for(int i=0; i<n; i++){
         printf("| ");
         for(int j=0; j<n; j++){
             printf("%3d ", matrix[i][j]);
         }
         printf(" |\n");
     }
     printf("\n");
 }
 
 void multiplyMatricesConventional(int n, int matrixA[][n], int matrixB[][n], int result[][n]){
     for(int i=0; i<n; i++){
         for(int j=0; j<n; j++){
             result[i][j] = 0;
             for(int k=0; k<n; k++){
                 result[i][j] += matrixA[i][k] * matrixB[k][j];
             }
         }
     }
 }
 
 void addMatrices(int n, int A[][n], int B[][n], int C[][n]) {
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             C[i][j] = A[i][j] + B[i][j];
         }
     }
 }
 void subtractMatrices(int n, int A[][n], int B[][n], int C[][n]) {
     for (int i = 0; i < n; i++) {
         for (int j = 0; j < n; j++) {
             C[i][j] = A[i][j] - B[i][j];
         }
     }
 }
 void strassenMultiplication(int n, int A[][n], int B[][n], int C[][n]) {
     if (n == 1) {
         C[0][0] = A[0][0] * B[0][0];
         return;
     }
 
     int half = n / 2;
 
     // allocate memory for sub-matrices
     int A11[half][half], A12[half][half], A21[half][half], A22[half][half];
     int B11[half][half], B12[half][half], B21[half][half], B22[half][half];
     int C11[half][half], C12[half][half], C21[half][half], C22[half][half];
     int M1[half][half], M2[half][half], M3[half][half], M4[half][half], M5[half][half], M6[half][half], M7[half][half];
     int AA[half][half], BB[half][half];
 
     // divide A, B and C into sub-matrices
     for (int i = 0; i < half; i++) {
         for (int j = 0; j < half; j++) {
             A11[i][j] = A[i][j];
             A12[i][j] = A[i][j + half];
             A21[i][j] = A[i + half][j];
             A22[i][j] = A[i + half][j + half];
 
             B11[i][j] = B[i][j];
             B12[i][j] = B[i][j + half];
             B21[i][j] = B[i + half][j];
             B22[i][j] = B[i + half][j + half];
         }
     }
 
     // compute M1, M2, ..., M7
     subtractMatrices(half, B12, B22, AA);
     strassenMultiplication(half, A11, AA, M1);
 
     addMatrices(half, A11, A12, AA);
     strassenMultiplication(half, AA, B22, M2);
 
     addMatrices(half, A21, A22, AA);
     strassenMultiplication(half, AA, B11, M3);
 
     subtractMatrices(half, B21, B11, AA);
     strassenMultiplication(half, A22, AA, M4);
 
     addMatrices(half, A11, A22, AA);
     addMatrices(half, B11, B22, BB);
     strassenMultiplication(half, AA, BB, M5);
 
     subtractMatrices(half, A12, A22, AA);
     addMatrices(half, B21, B22, BB);
     strassenMultiplication(half, AA, BB, M6);
 
     subtractMatrices(half, A11, A21, AA);
     addMatrices(half, B11, B12, BB);
     strassenMultiplication(half, AA, BB, M7);
 
     // compute C11, C12, C21, C22
     addMatrices(half, M5, M4, AA);
     subtractMatrices(half, AA, M2, BB);
     addMatrices(half, BB, M6, C11);
 
     addMatrices(half, M1, M2, C12);
     addMatrices(half, M3, M4, C21);
 
     subtractMatrices(half, M5, M3, AA);
     subtractMatrices(half, AA, M7, BB);
     addMatrices(half, BB, M1, C22);
 
     // combine sub-matrices into C
     for (int i = 0; i < half; i++) {
         for (int j = 0; j < half; j++) {
             C[i][j] = C11[i][j];
             C[i][j + half] = C12[i][j];
             C[i + half][j] = C21[i][j];
             C[i + half][j + half] = C22[i][j];
         }
     }
 }
 
 
 
 int main(){
     printf("\n");
     // int n = 4;
 
     // printf("Enter the size of the matrices: ");
     // scanf("%d", &n);
 
 //     int A[n][n], B[n][n], ConventionalResult[n][n], StrassenResult[n][n];
 
 //     // prompt the user to enter the matrix elements
 //     // printf("Enter the elements of matrix A:\n");
 //     // for (int i = 0; i < n; i++) {
 //     //     for (int j = 0; j < n; j++) {
 //     //         scanf("%d", &A[i][j]);
 //     //     }
 //     // }
 
 //     // printf("Enter the elements of matrix B:\n");
 //     // for (int i = 0; i < n; i++) {
 //     //     for (int j = 0; j < n; j++) {
 //     //         scanf("%d", &B[i][j]);
 //     //     }
 //     // }
 
 //     /* Inputs:
 //     4
 // 1 0 2 -3
 // 3 -1 0 -2
 // 1 -3 2 0
 // -3 2 0 1
 
 // 2 3 -2 3
 // 3 -1 0 2
 // -1 0 1 0
 // 0 2 -3 -1
 //     */
 
 
 //    printf("\n\n------\n\n");
 //     int testArr1[] = {
 //         1, 0, 2, -3,
 //         3, -1, 0, -2,
 //         1, -3, 2, 0,
 //         -3, 2, 0, 1
 //     };
 //     int testArr2[] = {
 //         2, 3, -2, 3,
 //         3, -1, 0, 2,
 //         -1, 0, 1, 0,
 //         0, 2, -3, -1
 //     };
 //     // Expected
 //     // {
 //     //     0, -3, 9, -6,
 //     //     3, 6, 0, 9
 //     //     -9, 6, 0, -3
 //     //     0, -9, 3, -6
 //     // }
 
 //     int testIdx = 0;
 
 //     for(int i=0; i<n; i++){
 //         for(int j=0; j<n; j++){
 //             A[i][j] = testArr1[testIdx];
 //             B[i][j] = testArr2[testIdx];
 //             testIdx++;
 //         }
 //     }
 
 //     printMatrix(n, A, "A");
 //     printMatrix(n, B, "B");
 
 //     multiplyMatricesConventional(n, A, B, ConventionalResult);
 //     strassenMultiplication(n, A, B, StrassenResult);
 //     printMatrix(n, ConventionalResult, "Conventional method:");
 //     printMatrix(n, StrassenResult, "Multiplication by strassen's method:");
 
 
     char *timesFileName = "times.txt";
     FILE *timesFilePtr = fopen(timesFileName, "w");
     printf("Storing times in (%s) ..... \n", timesFileName);
     fprintf(timesFilePtr, "Matrix size \tConventional \t\t Strassen's  \n");
 
     int num, startTime, endTime, rangeTill;
     double t1, t2;
     for(int n=1; n<=256; n*=2){
         int A[n][n], B[n][n], ConventionalResult[n][n], StrassenResult[n][n];
         fillMatrices(n, A, B);
 
         startTime = clock();
         multiplyMatricesConventional(n, A, B, ConventionalResult);
         endTime = clock();
         t1 = 1.0 * (endTime - startTime);
 
         startTime = clock();
         strassenMultiplication(n, A, B, StrassenResult);
         endTime = clock();
         t2 = 1.0 * (endTime - startTime);
 
         // printMatrix(n, A, "A");
         // printMatrix(n, B, "B");
 
         // printMatrix(n, ConventionalResult, "Conventional method:");
         // printMatrix(n, StrassenResult, "Multiplication by strassen's method:");
         // printf("-\n-\n-\n");
 
         fprintf(timesFilePtr, "%4d \t\t\t   %14lf \t\t %13lf \n", n, t1 / CLOCKS_PER_SEC, t2 / CLOCKS_PER_SEC);
     }
 
     fclose(timesFilePtr);
     printf("Done! \n\n");
 
 
     printf("Bye !\n\n");
     return 0;
 }

