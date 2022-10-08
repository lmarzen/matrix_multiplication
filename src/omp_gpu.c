#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <omp.h>


typedef struct {
        unsigned int rows;
        unsigned int cols;
        double *mat_data;
} matrix_struct;

matrix_struct *get_matrix_struct(char matrix[]) {
    matrix_struct *m = malloc(sizeof(matrix_struct));
    m->rows = 0;
    m->cols = 0;
    FILE* myfile = fopen(matrix, "r");
    
    if(myfile == NULL) {
        printf("Error: The file you entered could not be found.\n");
        exit(EXIT_FAILURE);
    }
    // get the rows and columns
    int ch = 0;
    do {
        ch = fgetc(myfile);
        
        // count the columns at the first line (looking for "\t")
        if(m->rows == 0 && ch == '\t')
            m->cols++;
        
        // count the rows with "\n"
        if(ch == '\n')
            m->rows++;
            
    } while (ch != EOF);
    
    // write rows and cols to struct
    m->cols++;
    
    // allocate memory for matrix data
    m->mat_data = malloc(m->rows * m->cols * sizeof(double)); 
    // int i;
    // for(i=0; i < m->rows; ++i)
    //     m->mat_data[i]=calloc(m->cols, sizeof(double));
        
    
    rewind(myfile);
    int x,y;
    
    // fill matrix with data
    for(x = 0; x < m->rows; x++) {
        for(y = 0; y < m->cols; y++) {
            if (!fscanf(myfile, "%lf", &m->mat_data[x * m->cols + y])) 
            break;
        }
    }
    
    fclose(myfile);

    return m;
}

void print_matrix(matrix_struct *matrix_to_print){
    int i,j;
    for(i = 0; i < matrix_to_print->rows; i++) {
        for(j = 0; j < matrix_to_print->cols; j++) {
            printf("%lf\t",matrix_to_print->mat_data[i * matrix_to_print->cols + j]); //Use lf format specifier, \n is for new line
        }
        printf("\n");
    }
}

void free_matrix(matrix_struct *matrix_to_free) {
    // for(int i = 0; i < matrix_to_free->rows; i++) {
    //     free(matrix_to_free->mat_data[i]);
    // }
    free(matrix_to_free->mat_data);
    free(matrix_to_free);
}


int main(int argc, char **argv)
{
    if(argc != 3){
        printf("ERROR: Please specify only 2 files.\n");
        exit(EXIT_FAILURE);
    }
        
    matrix_struct *m_1 = get_matrix_struct(argv[1]);
    matrix_struct *m_2 = get_matrix_struct(argv[2]);

    if(m_1->cols != m_2->rows){
        printf("ERROR: The number of columns of matrix A must match the number of rows of matrix B.\n");
        exit(EXIT_FAILURE);
    }

    
    // allocate result matrix memory
    matrix_struct *result_matrix = malloc(sizeof(matrix_struct));
    result_matrix->rows = m_1->rows;
    result_matrix->cols = m_2->cols;
    result_matrix->mat_data = calloc(result_matrix->rows * result_matrix->cols, sizeof(double)); 

    // calculate the result matrix with omp (use pragma)
    double *result_data = result_matrix->mat_data;
    double *m_1_data = m_1->mat_data;
    double *m_2_data = m_2->mat_data;
    unsigned int result_size = result_matrix->rows * result_matrix->cols;
    unsigned int m_1_size = m_1->rows * m_1->cols;
    unsigned int m_2_size = m_1->rows * m_1->cols;
    unsigned int result_rows = result_matrix->rows;
    unsigned int result_cols = result_matrix->cols;
    unsigned int m_1_rows = m_1->rows;
    unsigned int m_1_cols = m_1->cols;
    unsigned int m_2_rows = m_2->rows;
    unsigned int m_2_cols = m_2->cols;

    #pragma omp target teams distribute parallel for collapse(2) \
            map(tofrom: result_data[0:result_size])  \
            map(to: result_rows, result_cols,        \
                    m_1_rows, m_1_cols,              \
                    m_2_rows, m_2_cols,              \
                    m_1_data[0:m_1_size],            \
                    m_2_data[0:m_2_size])
    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_cols; j++) {
            for (int k = 0; k < m_1_cols; k++) {

                result_data[i * result_cols + j] += m_1_data[i * m_1_cols + k] * m_2_data[k * m_2_cols + j];
            }
        }
    }

    print_matrix(result_matrix);
    
    free_matrix(m_1);
    free_matrix(m_2);
    free_matrix(result_matrix);
    
    exit(EXIT_SUCCESS);
}
