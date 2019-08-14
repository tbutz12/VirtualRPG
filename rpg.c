//
//  rpg.c
//  Role Playing Game
//
//  Created by tristin butz on 02/03/19.
//  Copyright © 2019 tristin butz. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <math.h>

struct Player{
    char playerName[20];
    int playerHP;
    char playerArmor[20];
    char playerWeapon[20];
    int playerLevel;
    int playerXP;
}Player;
struct Orc{
    int orcHP;
    char orcArmor[20];
    int orcArmorStorage;
    char orcWeapon[20];
    int weaponStorage;
    int orcLevel;
    int orcXP;
}Orc[8];
struct Sauron{
    int sauronHP;
    char sauronArmor[20];
    char sauronWeapon[20];
    int sauronLevel;
    int sauronXP;
}Sauron;
struct Gollum{
    int gollumHP;
    char gollumArmor[20];
    char gollumWeapon[20];
    int gollumLevel;
    int gollumXP;
}Gollum;

void fightOrc(struct  Orc Orc[], struct Player *Player, char v, int tempB, int tempA, int armorStorage[]);
int DiceRolls (int a, int b);
void catch_signal (int sig);
int expToLevel(int xp);
void c_signal(int sig);
int file;
int tempA;
int tempB;
int armorStorage[5];


int DiceRolls (int a, int b) {
    int range = a - b;
    write(file, &range, sizeof(int));
    read(file, &range, 1);
    return range + b;
  //  return rand() % (a - b + 1) + b;
    
}
void catch_signal (int sig){
    FILE *file = fopen("rpg.save" , "wb");
    fwrite(&Player, sizeof(Player), 1, file);
    fwrite(Orc, sizeof(struct Orc), 8 , file);
    fwrite(&Gollum, sizeof(Gollum), 1, file);
    fwrite(&Sauron, sizeof(Sauron), 1 , file);
    fclose(file);
}
int expToLevel (int xp){
    xp /= 1000;
    xp = log2(xp);
    return xp;
}
int main(int argc, char *argv[]) {
    file = open("/dev/dice", O_RDWR);
    signal(SIGINT, catch_signal);
    signal(SIGTERM, catch_signal);
    signal(SIGRTMIN, c_signal);
    char *armors[30];
    char *weapons[30];
        char in[3];
        printf("Would you like to continue from your last save? (y/n) ");
        scanf("%s", in);
        if(!strcmp(in, "y")){
            FILE *save = fopen("rpg.save", "r");
            fread(&Player, sizeof(Player), 1, save);
            fread(Orc, sizeof(struct Orc), 8 , save);
            fread(&Gollum, sizeof(Gollum), 1, save);
            fread(&Sauron, sizeof(Sauron), 1 , save);
                    fclose(save);
        }
        else{
    Player.playerXP = 2000;
    Player.playerLevel = 1;
    Player.playerHP = 20 + (Player.playerLevel - 1) * 5;
    printf("What is your name?\n");
    char name[20];
    scanf("%s" , name);
    strcpy(Player.playerName, name);
    srand((unsigned int)time(NULL));
    armors[0] = "0: cloth (AC=10)\n";
    armors[1] = "1: studded leather (AC=12)\n";
    armors[2] = "2: ring mail (AC=14)\n";
    armors[3] = "3: chain mail (AC=16)\n";
    armors[4] = "4: plate (AC=18)\n";
    printf("List of available armors: \n");
    int x;
    for(x = 0; x< 5; x++){
        printf("%s" , armors[x]);
    }
    printf("\nChoose %s's armor(0~4): \n" , Player.playerName);
    scanf("%d", &tempA);

    weapons[0] = "0: dagger (damage = 1d4)\n";
    weapons[1] = "1: short sword (damage = 1d6)\n";
    weapons[2] = "2: long sword (damage = 1d8)\n";
    weapons[3] = "3: great sword (damage = 2d6)\n";
    weapons[4] = "4: great axe (damage = 1d12)\n";
    printf("\nList of available weapons: \n");
    int y;
    for(y = 0; y< 5; y++){
        printf("%s" , weapons[y]);
    }
    printf("\nChoose %s's weapon(0~4): \n" , Player.playerName);
    scanf("%d", &tempB);
    printf("Player setup complete:\n");
    int armorStorage[5];
    int player1HP = 20;
    armors[0] = "cloth";
    armors[1] = "studded leather";
    armors[2] = "ring mail";
    armors[3] = "chain mail";
    armors[4] = "plate";
    switch(tempA){
        case 0 :
            armorStorage[0] = 10;
            break;
        case 1 :
            armorStorage[1] = 12;
            break;
        case 2 :
            armorStorage[2] = 14;
            break;
        case 3 :
            armorStorage[3] = 16;
            break;
        case 4 :
            armorStorage[4] = 18;
            break;
    }
            weapons[0] = "dagger";
            weapons[1] = "short sword";
            weapons[2] = "long sword";
            weapons[3] = "great sword";
            weapons[4] = "great axe";
    strcpy(Player.playerArmor , armors[tempB]);
    strcpy(Player.playerWeapon , weapons[tempA]);
    printf("[ %s: hp = %d, armor = %s, weapon = %s ]\n\n" , Player.playerName, player1HP, Player.playerArmor , Player.playerWeapon);
            Sauron.sauronHP = 115;
            strcpy(Sauron.sauronArmor , armors[4]);
            strcpy(Sauron.sauronWeapon , weapons[4]);
            Sauron.sauronLevel = 20;
            Sauron.sauronXP = 1048576000;
    
            Gollum.gollumHP = 10;
            strcpy(Gollum.gollumArmor , armors[0]);
            strcpy(Gollum.gollumWeapon , weapons[0]);
            Gollum.gollumLevel = 1;
            Gollum.gollumXP = 2000;
    int k = 0;
    for(k = 0; k < 8; k++){
        Orc[k].orcLevel = 1;
        Orc[k].orcXP = 2000;
        Orc[k].orcHP = 20 + (Orc[k].orcLevel - 1) * 5;
        strcpy(Orc[k].orcArmor , armors[DiceRolls(4, 0)]);
        strcpy(Orc[k].orcWeapon , weapons[DiceRolls(4,0)]);
        if(!strcmp(Orc[k].orcArmor, "cloth")){
            Orc[k].orcArmorStorage = 0;
        }
        else if(!strcmp(Orc[k].orcArmor, "studded leather")){
            Orc[k].orcArmorStorage = 1;
        }
        else if(!strcmp(Orc[k].orcArmor, "ring mail")){
            Orc[k].orcArmorStorage = 2;
        }
        else if(!strcmp(Orc[k].orcArmor, "chain mail")){
            Orc[k].orcArmorStorage = 3;
        }
        else {
            Orc[k].orcArmorStorage = 4;
        }
        if(!strcmp(Orc[k].orcWeapon, "dagger")){
            Orc[k].weaponStorage = 0;
        }
        else if(!strcmp(Orc[k].orcWeapon, "short sword")){
            Orc[k].weaponStorage = 1;
        }
        else if(!strcmp(Orc[k].orcWeapon, "long sword")){
            Orc[k].weaponStorage = 2;
        }
        else if(!strcmp(Orc[k].orcWeapon, "great sword")){
            Orc[k].weaponStorage = 3;
        }
        else {
            Orc[k].weaponStorage = 4;
        }
        
    }
        }
    char input[20];
    while(strcmp(input, "quit" )){
        if(strcmp(input, "stats") && strcmp(input, "fight ") && strcmp(input, "look") && strcmp(input, "quit")){
            strcpy(Orc->orcArmor , armors[DiceRolls(4, 0)]);
            strcpy(Orc->orcWeapon , weapons[DiceRolls(4,0)]);
            printf("All is peaceful in the land of Mordor\n");
            printf("Sauron and his minions are blissfully going about their business:\n");
            printf("0: [Sauron: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                       Sauron.sauronHP, Sauron.sauronArmor, Sauron.sauronWeapon, Sauron.sauronLevel, Sauron.sauronXP);
            printf("1: [Orc 1: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                    Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("2: [Orc 2: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[1].orcHP, Orc[1].orcArmor, Orc[1].orcWeapon, Orc[1].orcLevel, Orc[1].orcXP);
            printf("3: [Orc 3: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[2].orcHP, Orc[2].orcArmor, Orc[2].orcWeapon, Orc[2].orcLevel, Orc[2].orcXP);
            printf("4: [Orc 4: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[3].orcHP, Orc[3].orcArmor, Orc[3].orcWeapon, Orc[3].orcLevel, Orc[3].orcXP);
            printf("5: [Orc 5: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[4].orcHP, Orc[4].orcArmor, Orc[4].orcWeapon, Orc[4].orcLevel, Orc[4].orcXP);
            printf("6: [Orc 6: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[5].orcHP, Orc[5].orcArmor, Orc[5].orcWeapon, Orc[5].orcLevel, Orc[5].orcXP);
            printf("7: [Orc 7: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                  Orc[6].orcHP, Orc[6].orcArmor, Orc[6].orcWeapon, Orc[6].orcLevel, Orc[6].orcXP);
            printf("8: [Orc 8: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[7].orcHP, Orc[7].orcArmor, Orc[7].orcWeapon, Orc[7].orcLevel, Orc[7].orcXP);
            printf("9: [Gollum: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Gollum.gollumHP, Gollum.gollumArmor, Gollum.gollumWeapon, Gollum.gollumLevel, Gollum.gollumXP);
            printf("Also at the scene are some adventurers looking for trouble:\n");
            printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
        }
        printf("command >> ");
        char temp;
        scanf("%c",&temp);
        scanf("%[^\n]", input);
        if(!strcmp(input, "quit")){
            catch_signal(12);
            return 0;
        }
        if(!strcmp(input, "fight 0")){
            while(Player.playerHP >= 0 && Sauron.sauronHP >= 0){
            int attack = DiceRolls(20,1);
            if(attack > armorStorage[4]){
                int x = 0;
                if(tempB == 0){
                    x = DiceRolls(4,1);
                }
                else if(tempB == 1){
                    x = DiceRolls(6,1);
                }
                else if(tempB == 2){
                    x = DiceRolls(8,1);
                }
                else if(tempB == 3){
                    x = (DiceRolls(6, 1) + DiceRolls(6,1));
                }
                else if(tempB == 4){
                    x = DiceRolls(12, 1);
                }
                printf("%s hits Sauron for %d damage (attack roll) %d\n" , Player.playerName, x, attack);
                Sauron.sauronHP -= x;
            }
            else{
                printf("%s misses Sauron (attack roll) %d\n" , Player.playerName, attack);
            }
                int attack2 = DiceRolls(20, 1);
                int damage = DiceRolls(12,1);
                    if(attack2 > armorStorage[tempA]){
                    printf("Sauron hits %s for %d damage (attack roll) %d\n" , Player.playerName, damage, attack2);
                    Player.playerHP -= damage;
                    }
                    else{
                    printf("Sauron misses %s (attack roll) %d\n" , Player.playerName, attack2);
                    }
            }
                        if(Player.playerHP > Sauron.sauronHP){
                        printf("\nSauron is killed by %s\n", Player.playerName);
                        printf("Get Sauron's plate, exchanging %s's current armor %s (y/n)? ", Player.playerName, Player.playerArmor);
                        char obtain[1];
                        Sauron.sauronHP = 20 + (Sauron.sauronLevel - 1) * 5;
                        scanf("%s", obtain);
                            if(!strcmp(obtain, "y")){
                            strcpy(Player.playerArmor , Sauron.sauronArmor);
                            }
                            printf("Get Sauron's great axe, exchanging %s's current weapon %s (y/n)? ", Player.playerName, Player.playerWeapon);
                            scanf("%s", obtain);
                                if(!strcmp(obtain, "y")){
                                strcpy(Player.playerArmor , Sauron.sauronArmor);
                                }
                            Player.playerXP += 2000 * 20;
                            Player.playerLevel = expToLevel(Player.playerXP);
                            Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
                        }
                        else if(Sauron.sauronHP > Player.playerHP){
                        printf("%s is killed by Sauron\n" , Player.playerName);
                            printf("Respawning %s...\n" , Player.playerName);
                            Sauron.sauronXP += 2000 * 20;
                            Sauron.sauronLevel = expToLevel(Sauron.sauronXP);
                            Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
                            Player.playerXP = pow(2, expToLevel(Player.playerXP)) * 1000;
                            printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                                   Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
                        }
                        else{
                            printf("Respawning %s...\n" , Player.playerName);
                            Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
                            Player.playerXP = pow(2, expToLevel(Player.playerXP)) * 1000;
                            Sauron.sauronHP = 115;
                            printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                                   Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
                        }
            
        }
        if(!strncmp(input, "fight", 5)){
        char v = input[6];
        switch(v){
            case '1' : fightOrc(&Orc[0], &Player, v, tempB, tempA, armorStorage);break;
            case '2' : fightOrc(&Orc[1], &Player, v, tempB,  tempA, armorStorage); break;
            case '3': fightOrc(&Orc[2], &Player, v, tempB,  tempA, armorStorage); break;
            case '4': fightOrc(&Orc[3], &Player, v, tempB,  tempA, armorStorage); break;
            case '5': fightOrc(&Orc[4], &Player, v, tempB,  tempA, armorStorage); break;
            case '6': fightOrc(&Orc[5], &Player, v, tempB,  tempA, armorStorage); break;
            case '7': fightOrc(&Orc[6], &Player, v, tempB, tempA, armorStorage); break;
            case '8': fightOrc(&Orc[7], &Player, v, tempB, tempA, armorStorage); break;
            }
        }
        if(!strcmp(input, "fight 9")){
            while(Player.playerHP >= 0 && Gollum.gollumHP >= 0){
                int attack = DiceRolls(20,1);
                if(attack > armorStorage[0]){
                    int x = 0;
                    if(tempB == 0){
                        x = DiceRolls(4,1);
                    }
                    else if(tempB == 1){
                        x = DiceRolls(6,1);
                    }
                    else if(tempB == 2){
                        x = DiceRolls(8,1);
                    }
                    else if(tempB == 3){
                        x = (DiceRolls(6, 1) + DiceRolls(6,1));
                    }
                    else if(tempB == 4){
                        x = DiceRolls(12, 1);
                    }
                    printf("%s hits Gollum for %d damage (attack roll) %d\n" , Player.playerName, x, attack);
                    Gollum.gollumHP -= x;
                }
                else{
                    printf("%s misses Gollum (attack roll) %d\n" , Player.playerName, attack);
                }
                int attack2 = DiceRolls(20, 1);
                int damage = DiceRolls(6,1);
                if(attack2 > armorStorage[tempA]){
                    printf("Gollum hits %s for %d damage (attack roll) %d\n" , Player.playerName, damage, attack2);
                    Player.playerHP -= damage;
                }
                else{
                    printf("Gollum misses %s (attack roll) %d\n" , Player.playerName, attack2);
                }
            }
            if(Player.playerHP > Gollum.gollumHP){
                printf("\nGollum is killed by %s\n", Player.playerName);
                Gollum.gollumHP = 20 + (Gollum.gollumLevel - 1) * 5;
                printf("Get Gollum's cloth, exchanging %s's current armor %s (y/n)? ", Player.playerName, Player.playerArmor);
                char obtain[1];
                scanf("%s", obtain);
                if(!strcmp(obtain, "y")){
                    strcpy(Player.playerArmor , Gollum.gollumArmor);
                }
                printf("Get Gollum's dagger, exchanging %s's current weapon %s (y/n)? ", Player.playerName, Player.playerWeapon);
                scanf("%s", obtain);
                if(!strcmp(obtain, "y")){
                    strcpy(Player.playerWeapon , Gollum.gollumWeapon);
                }
                Player.playerXP += 2000 * 20;
                Player.playerLevel = expToLevel(Player.playerXP);
                Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
            }
            else if(Gollum.gollumHP > Player.playerHP){
                Gollum.gollumXP += 2000 * 20;
                Gollum.gollumLevel = expToLevel(Gollum.gollumXP);
                printf("%s is killed by Gollum\n" , Player.playerName);
                printf("Respawning %s...\n" , Player.playerName);
                Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
                Player.playerXP = pow(2, expToLevel(Player.playerXP)) * 1000;
                printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                       Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
            }
            else{
                printf("Respawning %s...\n" , Player.playerName);
                Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
                Player.playerXP = pow(2, expToLevel(Player.playerXP)) * 1000;
                Gollum.gollumHP = 15;
                printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                       Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
            }
            
        }
        if(!strcmp(input, "stats")){
            printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
            
            }
        if(!strcmp(input, "look")){
            if(Orc->orcHP <= 0){
                Orc->orcHP = 20 + (Orc->orcLevel - 1) * 5;
            }
            if(Gollum.gollumHP <= 0){
                Gollum.gollumHP = 20 + (Gollum.gollumLevel - 1) * 5;
            }
            if(Sauron.sauronHP <= 0){
                Sauron.sauronHP = 20 + (Sauron.sauronLevel - 1) * 5;
            }
            printf("All is peaceful in the land of Mordor.\n");
            printf("Sauron and his minions are blissfully going about their business:\n");
            printf("0: [Sauron: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Sauron.sauronHP, Sauron.sauronArmor, Sauron.sauronWeapon, Sauron.sauronLevel, Sauron.sauronXP);
            printf("1: [Orc 1: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("2: [Orc 2: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("3: [Orc 3: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("4: [Orc 4: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("5: [Orc 5: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("6: [Orc 6: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("7: [Orc 7: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("8: [Orc 8: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
            printf("9: [Gollum: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Gollum.gollumHP, Gollum.gollumArmor, Gollum.gollumWeapon, Gollum.gollumLevel, Gollum.gollumXP);
            printf("Also at the scene are some adventurers looking for trouble:\n");
            printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                   Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
        }

    }
    return 0;
}
void fightOrc(struct Orc Orc[], struct Player *Player , char v, int tempB, int tempA, int armorStorage[]){
                char x = v;
    while(Player->playerHP > 0 && Orc->orcHP > 0){
                int attack = DiceRolls(20,1);
                if(attack > Orc->orcArmorStorage){
                    int b = 0;
                    if(tempB == 0){
                        b = DiceRolls(4,1);
                    }
                    else if(tempB == 1){
                        b = DiceRolls(6,1);
                    }
                    else if(tempB == 2){
                        b = DiceRolls(8,1);
                    }
                    else if(tempB == 3){
                        b = (DiceRolls(6, 1) + DiceRolls(6,1));
                    }
                    else if(tempB == 4){
                        b = DiceRolls(12, 1);
                    }
                    printf("%s hits Orc %c for %d damage (attack roll) %d\n" , Player->playerName, x,  b, attack);
                    Orc->orcHP -= b;
                }
                else{
                    printf("%s misses Orc %c (attack roll) %d\n" , Player->playerName, x, attack);
                }
                int attack2 = DiceRolls(20, 1);
                int y = 0;
                if(Orc->weaponStorage == 0){
                    y = DiceRolls(4,1);
                }
                else if(Orc->weaponStorage == 1){
                    y = DiceRolls(6,1);
                }
                else if(Orc->weaponStorage == 2){
                    y = DiceRolls(8,1);
                }
                else if(Orc->weaponStorage == 3){
                    y = (DiceRolls(6, 1) + DiceRolls(6,1));
                }
                else if(Orc->weaponStorage == 4){
                    y = DiceRolls(12, 1);
                }
                if(attack2 > armorStorage[tempA]){
                    printf("Orc %c hits %s for %d damage (attack roll) %d\n" ,x, Player->playerName, y, attack2);
                    Player->playerHP -= y;
                }
                else{
                    printf("Orc %c misses %s (attack roll) %d\n" ,x,  Player->playerName, attack2);
                }
        }
            if(Player->playerHP > 0 && (Orc->orcHP < 0)){
                printf("\nOrc %c is killed by %s\n", x, Player->playerName);
                Orc->orcHP = 20 + (Orc->orcLevel - 1) * 5;
                Orc->orcLevel = DiceRolls(Player->playerLevel, 1);
                Orc->orcHP = 20 + (Orc->orcLevel - 1) * 5;
                printf("Get Orc %c's %s, exchanging %s's current armor %s (y/n)? ", x, Orc->orcArmor, Player->playerName, Player->playerArmor);
                char obtain[1];
                scanf("%s", obtain);
                if(!strcmp(obtain, "y")){
                    strcpy(Player->playerArmor , Orc->orcArmor);
                }
                printf("Get Orc %c's %s, exchanging %s's current weapon %s (y/n)? ", x, Orc->orcWeapon, Player->playerName, Player->playerWeapon);
                scanf("%s", obtain);
                if(!strcmp(obtain, "y")){
                    strcpy(Player->playerWeapon , Orc->orcWeapon);
                }
                Player->playerXP += 2000 * 20;
                Player->playerLevel = expToLevel(Player->playerXP);
                Player->playerHP =  20 + (Player->playerLevel - 1) * 5;
            }
            else if(Player->playerHP <= 0 && Orc->orcHP > 0){
                Orc->orcXP += 2000 * 20;
                Orc->orcLevel = expToLevel(Orc->orcXP);
                printf("%s is killed by Orc %c\n" , Player->playerName, x);
                printf("Respawning %s...\n" , Player->playerName);
                Player->playerHP =  20 + (Player->playerLevel - 1) * 5;
                Player->playerXP = pow(2, expToLevel(Player->playerXP)) * 1000;
                printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                       Player->playerName, Player->playerHP, Player->playerArmor, Player->playerWeapon, Player->playerLevel, Player->playerXP);
            }
            else {
                printf("Respawning %s...\n" , Player->playerName);
                Player->playerHP =  20 + (Player->playerLevel - 1) * 5;
                Player->playerXP = pow(2, expToLevel(Player->playerXP))* 1000;
                Orc->orcLevel = DiceRolls(Player->playerLevel, 1);
                Orc->orcHP = 20 + (Orc->orcLevel - 1) * 5;
                printf("0: [%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
                       Player->playerName, Player->playerHP, Player->playerArmor, Player->playerWeapon, Player->playerLevel, Player->playerXP);
            }
    
    
}

void c_signal(int sig){
    printf("\nEARTHQUAKE!!!\n\n");
    Sauron.sauronHP -= 20;
    if(Sauron.sauronHP > 0){
        printf("0: [Sauron suffers -20 damage but survives.\n");
    }
    else{
        printf("Sauron suffers -20 damage and dies. Respawning... \n");
    }
    Orc[0].orcHP -= 20;
    if(Orc[0].orcHP > 0){
        printf("Orc 1 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 1 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 1: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[0].orcHP, Orc[0].orcArmor, Orc[0].orcWeapon, Orc[0].orcLevel, Orc[0].orcXP);
        Orc[0].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[0].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[1].orcHP -= 20;
    if(Orc[1].orcHP > 0){
        printf("Orc 2 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 2 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 2: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[1].orcHP, Orc[1].orcArmor, Orc[1].orcWeapon, Orc[1].orcLevel, Orc[1].orcXP);
        Orc[1].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[1].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[2].orcHP -= 20;
    if(Orc[2].orcHP > 0){
        printf("Orc 3 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 3 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 3: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[2].orcHP, Orc[2].orcArmor, Orc[2].orcWeapon, Orc[2].orcLevel, Orc[2].orcXP);
        Orc[2].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[2].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[3].orcHP -= 20;
    if(Orc[3].orcHP > 0){
        printf("Orc 4 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 4 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 4: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[3].orcHP, Orc[3].orcArmor, Orc[3].orcWeapon, Orc[3].orcLevel, Orc[3].orcXP);
        Orc[3].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[3].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[4].orcHP -= 20;
    if(Orc[4].orcHP > 0){
        printf("Orc 5 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 5 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 5: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[4].orcHP, Orc[4].orcArmor, Orc[4].orcWeapon, Orc[4].orcLevel, Orc[4].orcXP);
        Orc[4].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[4].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[5].orcHP -= 20;
    if(Orc[5].orcHP > 0){
        printf("Orc 6 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 6 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 6: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[5].orcHP, Orc[5].orcArmor, Orc[5].orcWeapon, Orc[5].orcLevel, Orc[5].orcXP);
        Orc[5].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[5].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[6].orcHP -= 20;
    if(Orc[6].orcHP > 0){
        printf("Orc 7 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 7 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 7: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[6].orcHP, Orc[6].orcArmor, Orc[6].orcWeapon, Orc[6].orcLevel, Orc[6].orcXP);
        Orc[6].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[6].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Orc[7].orcHP -= 20;
    if(Orc[7].orcHP > 0){
        printf("Orc 8 suffers -20 damage but survives. \n");
    }
    else{
        printf("Orc 8 suffers -20 damage and dies. Respawning...\n");
        printf("[Orc 8: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Orc[7].orcHP, Orc[7].orcArmor, Orc[7].orcWeapon, Orc[7].orcLevel, Orc[7].orcXP);
        Orc[7].orcLevel = DiceRolls(Player.playerLevel, 1);
        Orc[7].orcHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    Gollum.gollumHP -= 20;
    if(Gollum.gollumHP > 0){
        printf("Gollum suffers -20 damage but survives. \n");
    }
    else{
        printf("Gollum suffers -20 damage and dies. Respawning...\n");
        printf("[Gollum: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
               Gollum.gollumHP, Gollum.gollumArmor, Gollum.gollumWeapon, Gollum.gollumLevel, Gollum.gollumXP);
        Gollum.gollumHP = 20 + (Orc->orcLevel - 1) * 5;
    }
    if(Player.playerHP > 20){
        printf("%s suffers -20 damage but survives.\n", Player.playerName);
    }
    else{
        printf("%s suffers -20 damage and dies. Respawning...\n", Player.playerName);
    }
    printf("[%s: hp = %d, armor=%s, weapon=%s, level=%d, xp=%d ]\n",
           Player.playerName, Player.playerHP, Player.playerArmor, Player.playerWeapon, Player.playerLevel, Player.playerXP);
            Player.playerHP =  20 + (Player.playerLevel - 1) * 5;
}

