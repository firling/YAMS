#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int gr[13][10];

typedef struct Joueur Joueur;
struct Joueur{
    char * nom;
    Joueur* suivant;
};


void insertion(Joueur *joueur){

}

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

int check_if_ended(int nb) {

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < nb; j++) {
            if (gr[i][j] == -1) {
                return 0;
            }
        }
    } 

    return 1;
}

int init(int nb) {
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < nb; j++) {
            gr[i][j] = -1;
        }
    }
}

int* totalScore(int player) {
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

void printGrille(int player) {
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

    int* tot = totalScore( player);

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

int choseResult(int player) {
    printf("================================\n\n");
    int res;
    do {
        printf("Veuillez choisir un score [1 - 13] : ");
        scanf("%d", &res);
        if (res < 1 || res > 13 || gr[res-1][player] != -1) {
            printf("Mauvaise entree.\n");
        }
    } while (res < 1 || res > 13 || gr[res-1][player] != -1);
    switch(res) {
        case 1: printf("Vous avez choisi la Somme des 1!\n"); break;
        case 2: printf("Vous avez choisi la Somme des 2!\n"); break;
        case 3: printf("Vous avez choisi la Somme des 3!\n"); break;
        case 4: printf("Vous avez choisi la Somme des 4!\n"); break;
        case 5: printf("Vous avez choisi la Somme des 5!\n"); break;
        case 6: printf("Vous avez choisi la Somme des 6!\n"); break;
        case 7: printf("Vous avez choisi le Brelan!\n"); break;
        case 8: printf("Vous avez choisi le Full!\n"); break;
        case 9: printf("Vous avez choisi la Petite Suite!\n"); break;
        case 10: printf("Vous avez choisi la Grande SUite!\n"); break;
        case 11: printf("Vous avez choisi le Carre!\n"); break;
        case 12: printf("Vous avez choisi le Yams!\n"); break;
        case 13: printf("Vous avez choisi la Chance!\n"); break;
    }
    return res;
}

void printPossibleScores(int* scores, int player) {
    printf("\nScores Possibles:\n");
    printf("================================\n");
    for (int i = 0; i < 13; i++) {
        if (gr[i][player] == -1) {
            printf("[%d] => %s: %d\n", i+1, corres[i], scores[i]);
        }
    }
}

void game(int player) {
    printGrille( player);

    int* dices = fullRoll(5);

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

    printPossibleScores(scores, player);

    int res = choseResult(player);

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

void writeToFile(int nbJoueurs) {
    int written = 0;
    FILE* rep = fopen("resultats.txt", "a+");
    fprintf(rep, "\n=========================================\n");
    fprintf(rep,"\t\t Nouvelle Partie\n");
    fprintf(rep, "=========================================\n");
    for (int player = 0; player < nbJoueurs; player++) {
        fprintf(rep, "JOUEUR %d\n", player+1);

        for (int i = 0; i < 13; i++) {
            fprintf(rep, "%s\t: %d\n", corres[i], gr[i][player]);
        }

        int* tot = totalScore(player);

        fprintf(rep, "\nScore Total : %d (+%d)\n", tot[0], tot[1]);
        if (player + 1 != nbJoueurs) {
            fprintf(rep, "\n==========================================\n");
        }
    }
    fclose(rep);
}

int main() {
    
    int nb = choseNumOfPlayer();
    init(nb);
    int turn = 0;
    
    Joueur* premierJoueur;
    Joueur* JoueurSelect = premierJoueur;

    for (int i = 0; i<nb; i++){
        printf("\nVeuillez entrer le nom du joueur %d : ",i+1);

        char *temp;
        temp = malloc(128);
        scanf(" %s",temp);
        JoueurSelect->nom = temp;
        printf("%s",JoueurSelect->nom);
        printf("\nnb : %d\ni : %d\n",nb,i);

        if (i!= nb){
            Joueur* nouveauJoueur;
            JoueurSelect->suivant = nouveauJoueur;
            JoueurSelect = JoueurSelect->suivant;
        }
        
        free(temp);
    }


    while (check_if_ended(nb) != 1) {
        int player = turn % nb;
        game(player);

        turn ++;
    }
    printf("\n================== Scores Total ==================\n\n");
    for (int i = 0; i < nb; i++) {
        printGrille(i);
    }
    char write;
    printf("Voulez vous enregistrer les résultats dans un fichier (Y/n) ? \n");
    scanf(" %c", &write);
    if (write == 'y' || write == 'Y') {
        printf("Enregistrement dans le fichier 'resultats.txt'");
        writeToFile(nb);
    }
    return 0;
}