// Creator: | Vlasenko Max | KPI | First course | cypher Hilla
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Blue  "\x1b[96m"
#define Red   "\x1b[101m"
#define Res   "\x1b[0m"
#define N 2 // размер матрицы
#define Alphabet 28 // алфавит

void decryption(int inverse[N][N], int key[], int res[], int s);
int  findDeterminant(int matrix[N][N]);
void inverseMarrix(int matrix[N][N], int inverse[N][N], int det);

int main(void)  {
    puts(Red"\nCreator: Vlasenko Max | KPI | First course | cypher Hilla"Res); 
    int i, j, k, b, var; char cypher[100]; // max.lenght шифра

    char Array[Alphabet] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', ' ', '.'};
    int n[Alphabet] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};

    printf(Blue"\nВведіть повідомлення: \n"Res);
    fgets(cypher, 100, stdin);
    if (strlen(cypher) % 2 == 0) {
        puts(Red"Error: непарна кількість букв для шифру"Res);
        _Exit(0);
    }
    int s = strlen(cypher), key[s], res[s], inverse[N][N];
    
    for (i = 0; cypher[i] != 0; i++)
        for (j = 0; j < Alphabet; j++) 
            if (cypher[i] == Array[j])
                key[i] = n[j];              // ключ введеного текста
                
    int matrix[N][N] = { {-3, -3},          // матрица шифрования
                         {5, 2} };    
    
    int det = findDeterminant(matrix);
    inverseMarrix(matrix, inverse, det);

    printf("\nРозшифровать"Blue" <1>"Res" | Зашифровать "Blue"<2>"Res": ");
    scanf("%d", &var);
    if (var == 1) {
        decryption(inverse, key, res, s); // ГЛАВНОЕ
        printf(Blue"\nРозшифроване повідомлення:\n"Res);
    }
    if (var == 2) {
        decryption(matrix, key, res, s);
        printf(Blue"\nЗакодоване повідомлення:\n"Res);
    }
    for (i = 0; i < s - 1; i++)
        for (j = 0; j < Alphabet; j++) 
            if (res[i] == n[j]) {
                cypher[i] = Array[j];
                printf("%c", cypher[i]);
                break;
            }
    return 0;
}

void decryption(int inverse[N][N], int key[], int res[], int s){
    for (int i = 0; i < s; i++)
        res[i] = 0;
    for (int k = 0; k < s; k += 2) {
        res[k] = inverse[0][0] * key[k] + inverse[0][1] * key[k + 1];
        res[k + 1] = inverse[1][0] * key[k] + inverse[1][1] * key[k + 1];
        while (res[k] < 0)
            res[k] += Alphabet;
        res[k] %= Alphabet;
        while (res[k + 1] < 0)    
            res[k + 1] += Alphabet;
        res[k + 1] %= Alphabet;
    }
}

void inverseMarrix(int matrix[N][N], int inverse[N][N], int det) {
    if (det == 0) {
        puts(Red"Error: Оберненої матриці не існує"Res);
        _Exit(0);
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if (i == 0 && j == 0) {
                inverse[i][j] = matrix[i + 1][j + 1];
                inverse[i + 1][j + 1] = matrix[i][j];
                break;
            }
            if (i != j) {
                inverse[i][j] = -1 * matrix[i][j];
                inverse[j][i] = -1 * matrix[j][i];
                break;
            }
        }
    }

    for (int i = 2; i <= abs(det); i++)
        if (det % i == 0 && Alphabet % i == 0) {
            puts(Red"\nError: Шифр не можливий det має спільні дільники з mod(Alphabet)"Res);
            _Exit(0);
        }
                                    
    for (int i = 0; i < N; i++) {                 // НАЙТИ k, при котором temp целое
        for (int j = 0; j < N; j++) {             // temp / det
            for (int k = 1; ; k++){ 
                int temp = 0;
                if (det > 0) {
                    temp = (inverse[i][j] + Alphabet * k);
                    if (temp % det == 0) {
                        inverse[i][j] = temp / det;
                        break;
                    }
                }
                if (det < 0) {
                    temp = (-1 * inverse[i][j] + Alphabet * k);
                    if (temp % abs(det) == 0) {
                        inverse[i][j] = temp / abs(det);
                        break;
                    }
                }
            }
            inverse[i][j] %= Alphabet;
        }
    }
}

int findDeterminant(int matrix[N][N]) {
    int determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    return determinant;
}