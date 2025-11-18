#include <stdio.h>

#define MAX_NAME_LEN 30
#define NUM_SCORES 3

struct Student {
    char firstName[MAX_NAME_LEN + 1];
    char lastName[MAX_NAME_LEN + 1];
    int scores[NUM_SCORES];
    float average;
};

float calculateAverage(const int scores[], int numScores){
    float average = 0.0f;
    for(int i = 0; i < numScores; i++){
        average += scores[i];
    }

    average = average / numScores;

    return average;
}


int main(void){

    FILE* fp = fopen("students.txt", "w");

    if (fp == NULL) {
        perror("fopen");
        return 1;
    }

    struct Student s;

    char choice[10];

    do {

        printf("Please enter your name: ");
        scanf("%s", s.firstName);

        printf("Please enter your last name: ");
        scanf("%s", s.lastName);

        for(int i = 0; i < NUM_SCORES; i++){

            printf("Please enter score %d: ", i + 1);
            scanf("%d", &s.scores[i]);

        }

        s.average = calculateAverage(s.scores, NUM_SCORES);

        fprintf(fp, "%s %s %d %d %d %f\n", s.firstName, s.lastName, s.scores[0], s.scores[1], s.scores[2], s.average);

        printf("Add another student? (Y/N): ");
        scanf("%9s", choice);
        
    } while (choice[0] == 'y' || choice[0] == 'Y');

    fclose(fp);
    fp = NULL;

    fp = fopen("students.txt", "r");

    if(fp != NULL){
        printf("\n--- Student Records ---\n");

        while (fscanf(fp, "%s %s %d %d %d %f", s.firstName, s.lastName, &s.scores[0], &s.scores[1], &s.scores[2], &s.average) == 6) {
            printf("Name is: %s %s\n", s.firstName, s.lastName);
            printf("Scores: %d %d %d\n", s.scores[0], s.scores[1], s.scores[2]);
            printf("Average: %f\n", s.average);
        }

        fclose(fp);
        fp = NULL;
    } else {
        perror("fopen");
    }

    return 0;
}