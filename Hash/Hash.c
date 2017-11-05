#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 541
#define NAME_SIZE 20
#define EMPTY 0
#define FALSE 0
#define TRUE 1

struct hash{
    char names[NAME_SIZE];
    unsigned short collision;
}hash_table[TABLE_SIZE];

int hash1(char str[])
{
    int i, h=0;

    for(i=0; i< strlen(str); i++)
    {
        h = ((int)str[i] + h)%TABLE_SIZE;
    }
    return h;
}

int hash2(char str[])
{
    int i, h=0;

    for(i=0; i< strlen(str); i++)
    {
        h = ((int)str[i] + h*h)%TABLE_SIZE;
    }
    return h;
}

int hash_insert1(char name[])
{
    int number = 0;
    int key = hash1(name);

    while(strcmp(hash_table[key].names, "EMPTY") != 0)
    {
        hash_table[key].collision++;
        number++;
        key = (number + key)%TABLE_SIZE;
    }

    strcpy(hash_table[key].names, name);

    return key;
}

int hash_insert2(char name[])
{
    int number = 0;
    int key = hash2(name);


    while(strcmp(hash_table[key].names, "EMPTY") != 0)
    {
        hash_table[key].collision++;
        number++;
        key = (number + key)%TABLE_SIZE;
    }

    strcpy(hash_table[key].names, name);

    return key;
}

void initialize_table()
{
    int i;

    for(i = 0 ; i < TABLE_SIZE ; i++){
        strcpy(hash_table[i].names, "EMPTY");
        hash_table[i].collision = 0;
    }
}

int main()
{
    int col1 = 0;
    int col2 = 0;


    initialize_table();
    char name[NAME_SIZE];
    int i=0;

    FILE *fp1, *fp2;

    fp1 = fopen("names.txt", "r");
    fp2 = fopen("names.txt", "r");

    printf("Using Hash1 \n\n");

    while(fscanf(fp1, "%s", name) != EOF){
        hash_insert1(name);
    }
    while(i < TABLE_SIZE){
        printf("table[%d]:%10s   %d\n", i, hash_table[i].names, hash_table[i].collision);
        col1 += hash_table[i].collision;
        i++;
    }


    initialize_table();
    i = 0;

    printf("Using Hash2 \n");

    while(fscanf(fp2, "%s", name) != EOF){
        hash_insert2(name);
    }
    while(i < TABLE_SIZE){
        printf("table[%d]:%10s   %d\n", i, hash_table[i].names, hash_table[i].collision);
        col2 += hash_table[i].collision;
        i++;
    }

    printf("Total collision number in Hash1 is %d \n", col1);
    printf("Total collision number in Hash2 is %d \n", col2);


}
