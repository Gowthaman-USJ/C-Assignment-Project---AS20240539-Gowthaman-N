//Index Number :- AS20240539
//Name :- Gowthaman Navarathnarajah


#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int citymanagement(FILE *file1);

int main(){
FILE *file1;
citymanagement(file1);
}

int citymanagement(FILE *file1){
    int choice; char city[20];

    printf("1.Add a new city\n");
    printf("2.Rename or remove a city\n");
    printf("Enter Choice : ");
    scanf("%d",&choice);
    getchar();
    if(choice == 1){

        file1 = fopen("cities.txt","a");
        printf("Enter City Name: ");
        fgets(city,20,stdin);
        fputs(city,file1);
        fclose(file1);
    }
    else if(choice == 2){
        int choice2;  FILE *temp1;
        char buffer[20];

        temp1 = fopen("Temporary.txt","w");
        file1 = fopen("cities.txt","r");

        printf("1.Rename a city\n");
        printf("2.Remove a city\n");
        printf("Enter Choice: ");
        scanf("%d",&choice2);
        getchar();

        if(choice2 == 1){
            char oldname[20]; char newname[20];

            printf("Enter the city to be renamed : ");
            fgets(oldname,20,stdin);
            oldname[strlen(oldname)] = '\0';

            while (fgets(buffer, 20, file1)){
                if(strcmp(buffer,oldname)==0){
                    printf("Enter the new name:  ");
                    fgets(newname,20,stdin);

                    fputs(newname, temp1);
                    fputs("\n",temp1);
                }
                else{
                    fputs(buffer,temp1);
                    printf("\nSuccessfully renamed %.*s to %.*s\n",(int)strlen(oldname)-1,oldname,(int)strlen(newname)-1,newname);
                }
            }
            fclose(file1);
            fclose(temp1);
            remove("cities.txt");
            rename("Temporary.txt","cities.txt");


            return 0;

        }

        else if(choice == 2){
            char name[20];

            printf("Enter the city to be removed : ");
            fgets(name,20,stdin);
            while(fgets(buffer,20,file1)){
                if(strcmp(buffer,name)!=0){
                    fputs(buffer,temp1);
                }
            }
            printf("Successfully removed city %.*s from the list\n",(int)strlen(name)-1,name);
            fclose(file1);
            fclose(temp1);
            remove("cities.txt");
            rename("Temporary.txt","cities.txt");

            }

        }
        return 0;

    }


