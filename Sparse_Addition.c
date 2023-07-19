#include <stdio.h>
struct SparseElement
{
    int row;
    int col;
    int value;
};
void createSparseMatrix(int rows, int cols, int matrix[rows][cols], struct SparseElement sparse[])
{
    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] != 0)
            {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }
    sparse[k].row = -1;
}
void addSparseMatrices(struct SparseElement sparseA[], struct SparseElement sparseB[], struct SparseElement result[])
{
    int i = 0, j = 0, k = 0;

    while (sparseA[i].row != -1 && sparseB[j].row != -1)
    {
        if (sparseA[i].row < sparseB[j].row ||
            (sparseA[i].row == sparseB[j].row && sparseA[i].col < sparseB[j].col))
        {
            result[k++] = sparseA[i++];
        }
        else if (sparseA[i].row > sparseB[j].row ||
                 (sparseA[i].row == sparseB[j].row && sparseA[i].col > sparseB[j].col))
        {
            result[k++] = sparseB[j++];
        }
        else
        {
            result[k].row = sparseA[i].row;
            result[k].col = sparseA[i].col;
            result[k].value = sparseA[i].value + sparseB[j].value;
            i++;
            j++;
            k++;
        }
    }

    while (sparseA[i].row != -1)
    {
        result[k++] = sparseA[i++];
    }

    while (sparseB[j].row != -1)
    {
        result[k++] = sparseB[j++];
    }

    result[k].row = -1;
}
void displaySparseMatrix(struct SparseElement sparse[])
{
    int i = 0;
    while (sparse[i].row != -1)
    {
        printf("(%d, %d): %d\n", sparse[i].row, sparse[i].col, sparse[i].value);
        i++;
    }
}
int main()
{
    int matrixA[3][3] =
        {
            {1, 0, 0},
            {0, 5, 0},
            {0, 0, 0}};
    int matrixB[3][3] =
        {
            {0, 0, 9},
            {0, 10, 0},
            {0, 0, 0}};
    struct SparseElement sparseA[2], sparseB[2], result[2];
    createSparseMatrix(3, 3, matrixA, sparseA);
    createSparseMatrix(3, 3, matrixB, sparseB);
    addSparseMatrices(sparseA, sparseB, result);
    printf("Sparse Matrix A:\n");
    displaySparseMatrix(sparseA);
    printf("\nSparse Matrix B:\n");
    displaySparseMatrix(sparseB);
    printf("\nResultant Sparse Matrix:\n");
    displaySparseMatrix(result);
    return 0;
}
