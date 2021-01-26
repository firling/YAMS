#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char corres [13][50] = {
    "Somme des 1 ",
    "Somme des 2 ",
    "Somme des 3 ",
    "Somme des 4 ",
    "Somme des 5 ",
    "Somme des 6 ",
    "Brelan      ",
    "Full        ",
    "Petite Suite",
    "Grande Suite",
    "Carre       ",
    "Yams        ",
    "Chance      "
};

int check_if_ended(int (*gr)[10], int nb) {

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < nb; j++) {
            if (gr[i][j] == -1) {
                return 0;
            }
        }
    } 

    return 1;
}

int init(int (*gr)[10], int nb) {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < nb; j++) {
            gr[i][j] = -1;
        }
    }
}

int* totalScore(int (*gr)[10], int player) {
    int tot = 0;
    int* res = malloc(sizeof(int) * 2);
    res[1] = 0;
    for (int i = 0; i < 13; i++) {
        if (gr[i][player] > -1) {
            tot += gr[i][player];
        }
        if (i == 5 && tot >= 63) {
            tot += 35;
            res[1] = 35;
        }
    }
    res[0] = tot;
    return res;
}

void printGrille(int (*gr)[10], int player) {
    printf("\n==========================================\n");
    printf("     JOUEUR %d\n", player+1);
    printf("==========================================\n\n");

    for (int i = 0; i < 13; i++) {
        if (gr[i][player] > -1) {
            printf("%s\t: %d\n", corres[i], gr[i][player]);
        } else {
            printf("%s\t: \n", corres[i]);
        }
    }

    int bonus = 0;
    if (gr[0][player] + gr[1][player] + gr[2][player] + gr[3][player] + gr[4][player] + gr[5][player] >= 63 ) {
        bonus = 35;
    }

    int* tot = totalScore(gr, player);

    printf("\nScore Total : %d (+%d)\n", tot[0], tot[1]);
    
    printf("\n==========================================\n\n");
}

int roll(){

    return rand() % 6 + 1;
}

int* fullRoll(int nbDice){

    static int rolls[5];

    time_t t;
       
    /* Intializes random number generator */
    srand((unsigned) time(&t));

    /* Print 5 random numbers from 1 to 6 */
    for( int i = 0 ; i < nbDice ; i++ ) {
        rolls[i] = rand() % 6 + 1;
    }
    return rolls;
}

int* checkOccurences(int *rolls){
    static int occurences[6];
    
    for (int i = 0; i < 6; i++)
    {
        occurences[i] = 0;
        
        for (int y = 0; y < 6; y++)
        {
            if(rolls[y] == i+1){
                
                occurences[i]++;

            }
        }
        
    }
    
    return occurences;
}

int* calculScore(int *rolls) {
    static int scores[13];

    int* occurences = checkOccurences(rolls);

    for (int i = 1; i < 7; i++) {
        scores[i-1] = occurences[i-1] * i;
    }

    /* Chance */
    scores[12] = 0;
    for (int i = 0; i<5; i++) {
        scores[12] += rolls[i];
    }

    /* Brelan & Full */
    scores[6] = 0;
    scores[7] = 0;
    for (int i = 0; i<6; i++) {
        if (occurences[i] >= 3) {
            scores[6] = scores[12];
            for (int j = 0; j<6; j++) {
                if (occurences[j] == 2) {
                    scores[7] = 30;
                }
            }
        }
    }

    /* Carré */
    scores[10] = 0;
    for (int i = 0; i<6; i++) {
        if(occurences[i] >= 4) {
            scores[10] = 40;
        }
    }

    /* Yams */
    scores[11] = 0;
    for (int i = 0; i<6; i++) {
        if (occurences[i] == 5) {
            scores[11] = 50;
        }
    }

    /* Petite / grande Suite */
    scores[8] = 0;
    scores[9] = 0;
    int start = 1000;
    for (int j = 0; j < 5; j++) {
        if (rolls[j] < start) {
            start = rolls[j];
        }
    }
    int i = 0;
    for (i = 0; i<4; i++) {
        int temp = start;
        for (int j = 0; j < 5; j++) {
            if (rolls[j] == start+1) {
                start++;
                break;
            } 
        }
        if (temp == start) { break; }
    }

    if (i == 4) {
        scores[9] = 30;
        scores[8] = 15;
    } else if( i == 3) {
        scores[8] = 15;
    }

    return scores;
}

int choseResult(int (*gr)[10], int player) {
    printf("================================\n\n");
    int res;
    do {
        printf("Veuillez choisir un score [1 - 13] : ");
        scanf("%d", &res);
        if (res < 1 || res > 13 || gr[res-1][player] != -1) {
            printf("Mauvaise entree.\n");
        }
    } while (res < 1 || res > 13 || gr[res-1][player] != -1);

    return res;
}

void printPossibleScores(int* scores, int (*gr)[10], int player) {
    printf("\nScores Possibles:\n");
    printf("================================\n");
    for (int i = 0; i < 13; i++) {
        if (gr[i][player] == -1) {
            printf("[%d] => %s: %d\n", i+1, corres[i], scores[i]);
        }
    }
}

void game(int (*gr)[10], int player) {
    printGrille(gr, player);

    int* dices = fullRoll(5);
    // int* dices = malloc(sizeof(int)*5);
    // dices[0] = 2;
    // dices[1] = 6;
    // dices[2] = 2;
    // dices[3] = 2;
    // dices[4] = 2;

    int nbLancer = 1;
    int done = 0;

    for(int i = 0; i < 5; i++) {
        printf("de num %d => %d\n", i+1, dices[i]);
    }

    while (done == 0 && nbLancer < 3) {
        printf("Relancer les des ? Choisissez les numero des des a changer separe par des virgules. \nEnter c sinon : ");
        char changeDice[20];
        scanf("%s", changeDice);

        if (strcmp(changeDice, "c") == 0 || strcmp(changeDice, "C") == 0) { done = 1; };
        char *ptr = strtok(changeDice, ",");
        int temp, i = 0;
        int numDice[5];

        while (ptr != NULL) {
            temp = (int)*ptr;
            temp -= 49;

            if (temp > 5 || temp < 0) {break;}

            int tempRoll = roll();
            dices[temp] = tempRoll;

            ptr = strtok(NULL, ",");
            i++;
        }

        printf("\nNouveau Dés\n");
        printf("================================\n");

        for(int i = 0; i < 5; i++) {
            printf("de num %d => %d\n", i+1, dices[i]);
        }
        
        printf("================================\n");

        nbLancer++;
    }

    int* scores = calculScore(dices);

    printPossibleScores(scores, gr, player);

    int res = choseResult(gr, player);

    gr[res-1][player] = scores[res-1];
}

int choseNumOfPlayer(){
    int nb;
    do {
        printf("Choisissez le nombre de joueur souhaite (max: 10) : ");
        scanf("%d", &nb);
        if (nb < 1 || nb > 10) {
            printf("Mauvaise entree.\n\n");
        }
    } while(nb < 1 || nb > 10);
    return nb;
}

int main() {
    int grille[13][10];
    int nb = choseNumOfPlayer();
    init(grille, nb);
    int turn = 0;
    while (check_if_ended(grille, nb) != 1) {
        int player = turn % nb;
        
        game(grille, player);

        turn ++;
    }
    printf("\n================== Scores Total ==================\n\n");
    for (int i = 0; i < nb; i++) {
        printGrille(grille, i);
    }
    return 0;
}