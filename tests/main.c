#include <stdio.h>
#include <string.h>


int main(void){

    printf("Hello world\n");

    char * s = "1 2 + 44 + 0 1 444 /";

    int mes_entiers [10];
    int compteur = 0;

    int current_int = 0;
    int last_est_entier = 0;

    for(int i = 0; i<strlen(s); i++){
        char ch = s[i];

        if(ch == ' ' && last_est_entier){
            //ajouter a la liste si on casse un int
            printf("ajout d'un entier %d\n", current_int);
            mes_entiers[compteur] = current_int;
            compteur++;
            current_int = 0;
            last_est_entier = 0;
            continue;
        }

        if(ch == ' '){
            continue;
        }

        if(ch >= 48 && ch <= 57){
            current_int = 10*current_int + (ch-48);
            last_est_entier = 1;
        }else {
            printf("pas entier : %c\n", ch);
            last_est_entier = 0;
        }
    }

    if(last_est_entier){
        printf("ajout d'un entier %d\n", current_int);
        mes_entiers[compteur] = current_int;
        compteur++;
        current_int = 0;
        last_est_entier = 0;
    }

    return 0;
}