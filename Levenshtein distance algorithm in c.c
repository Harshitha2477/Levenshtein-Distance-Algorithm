#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000

int min(int a, int b, int c) {
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}

int levenshtein_distance(const char *s1, const char *s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int i,j;
    int **matrix = (int **)malloc((len1 + 1) * sizeof(int *));
    for (i = 0; i <= len1; i++) {
        matrix[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (i = 0; i <= len1; i++)
        matrix[i][0] = i;

    for (j = 0; j <= len2; j++)
        matrix[0][j] = j;

    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            matrix[i][j] = min(matrix[i - 1][j] + 1,
                               matrix[i][j - 1] + 1,
                               matrix[i - 1][j - 1] + cost);
        }
    }

    int distance = matrix[len1][len2];

    for (i = 0; i <= len1; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return distance;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char s1[MAX_LEN], s2[MAX_LEN];
    while (fscanf(file, "%s %s", s1, s2) == 2) {
        int distance = levenshtein_distance(s1, s2);
        printf("Levenshtein distance between '%s' and '%s' is: %d\n", s1, s2, distance);
    }

    fclose(file);
    return 0;
}

