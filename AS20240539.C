//Index Number :- AS20240539
//Name :- Gowthaman Navarathnarajah


#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_CITIES 30


void menu(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
int selcchoice(char vehicletype[][6],int vehicledetails[][4],int choice,char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
int readfromfiles(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
int citymanagement();
int distancemanagement(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
int printdistable(char vehicletype[][6],int vehicledetails[][4], char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
int  vehiclemanagement(char vehicletype[][6], int vehicledetails[][4]);
void deliveryorder(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
void calculations(int weight,int type,int distance,int vehicledetails[][4]);

int main(){
//FILE *file1 = fopen("cities.txt","r");
//FILE *file2 = fopen("UniqueCode.txt","r");
//FILE *file3 = fopen("distance.txt","r");
char vehicletype[][6] = {"Van","Truck","Lorry"};
int vehicledetails[][4] = {{1000,30,60,12},{5000,40,50,6},{10000,80,45,4}};

int numberarray[MAX_CITIES][MAX_CITIES]; char uniquecodearr[MAX_CITIES][10]; char citiesarr[MAX_CITIES][MAX_CITIES];

readfromfiles(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);


}
void menu(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){
    int choice;

    printf("\n--Menu--\n");
    printf("1.City Management(Add,edit or rename a city\n");
    printf("2.Distance Management\n");
    printf("3.Display the vehicle type table\n");
    printf("4.Place a delivery order\n");
    printf("Enter Choice : ");
    scanf("%d",&choice);
    selcchoice(vehicletype,vehicledetails,choice,citiesarr,uniquecodearr,numberarray);
}

int selcchoice(char vehicletype[][6],int vehicledetails[][4],int choice,char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){
    switch(choice){
    case 1:
        citymanagement();
        readfromfiles(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        break;

    case 2:
        distancemanagement(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        break;

    case 3:
        vehiclemanagement(vehicletype,vehicledetails);
        break;
    case 4:
        deliveryorder(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        break;


}



}
int readfromfiles(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){
    FILE *file1 = fopen("cities.txt","r");
    FILE *file2 = fopen("UniqueCode.txt","r");
    FILE *file3 = fopen("distance.txt","r");
    int i = 0;

    while (fgets(citiesarr[i], sizeof(citiesarr[i]), file1)&& i<MAX_CITIES) {
                i++;
           }
    fclose(file1);
    i=0;
     while (fgets(uniquecodearr[i], sizeof(uniquecodearr[i]), file2)&& i<MAX_CITIES) {
                i++;
           }
    fclose(file2);
    i=0;
     for (int i = 0; i < 30;i++) {
        for (int j = 0; j < 30; j++) {
            fscanf(file3, "%d", &numberarray[i][j]);
        }
    }
    fclose(file3);
    menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
    return 0;

}
int citymanagement(){
    int choice; char city[MAX_CITIES],buffer[MAX_CITIES];
     FILE *file1; FILE *temp1;

    printf("1.Add a new city\n");
    printf("2.Rename a city\n");
    printf("3.Remove a city\n");
    printf("Enter Choice : ");
    scanf("%d",&choice);
    getchar();
    if(choice == 1){

        file1 = fopen("cities.txt","a");
        printf("Enter City Name: ");
        fgets(city,sizeof(city),stdin);
        fputs(city,file1);
        fclose(file1);
        printf("Successfully Added %.*s to the list\n",(int)strlen(city)-1,city);
    }
    else if(choice == 2){

        temp1 = fopen("Temporary.txt","w");
        file1 = fopen("cities.txt","r");

        char oldname[MAX_CITIES],newname[MAX_CITIES];

        printf("Enter the city to be renamed : ");
        fgets(oldname,sizeof(oldname),stdin);

        while (fgets(buffer, sizeof(buffer), file1)){
            if(strcmp(buffer,oldname)==0){
                printf("Enter the new name:  ");
                fgets(newname,sizeof(newname),stdin);
                fputs(newname, temp1);

                printf("\nSuccessfully renamed %.*s to %.*s\n",(int)strlen(oldname)-1,oldname,(int)strlen(newname)-1,newname);
                }
            else{
                fputs(buffer,temp1);

                }
            }
        fclose(file1);
        fclose(temp1);
        remove("cities.txt");
        rename("Temporary.txt","cities.txt");

        }

    else if(choice == 3){
            char name[MAX_CITIES];

            temp1 = fopen("Temporary.txt","w");
            file1 = fopen("cities.txt","r");

            printf("Enter the city to be removed : ");
            fgets(name,sizeof(name),stdin);
            while(fgets(buffer,sizeof(buffer),file1)){
                if(strcmp(buffer,name)!=0){
                    fputs(buffer,temp1);
                }
            }
            printf("\nSuccessfully removed city %.*s from the list\n",(int)strlen(name)-1,name);
            fclose(file1);
            fclose(temp1);
            remove("cities.txt");
            rename("Temporary.txt","cities.txt");
            }
            return 0;
}

int distancemanagement(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){
    FILE *file2 = fopen("distance.txt","w");
    FILE *temp1 = fopen("temporary.txt","r");

    char fromcity[4]; char tocity[4]; char buffer[20];
    int toindex=0,fromindex=0,choice;


    printf("1.Input distances between two cities\n");
    printf("2.Edit distances between two cities\n");
    printf("3.Display the distance table\n");
    printf("Enter Choice : ");
    scanf("%d",&choice);
    getchar();

    if(choice == 1){
        //printf("still working");
    }
    else if(choice == 2){
        printf("Enter the first 3 letters of From City : ");
        scanf("%s",fromcity);
        printf("Enter the first 3 letters of To City : ");
        scanf("%s",tocity);
        for(int i=0;i<MAX_CITIES;i++){
                if(strncmp(uniquecodearr[i],fromcity,3)==0){
                    fromindex = i;
                    break;
                }
        }
        for(int i=0;i<MAX_CITIES;i++){
                if(strncmp(uniquecodearr[i],tocity,3)==0){
                    toindex = i;
                    break;
                }
        }
    int newdistance ;
    printf("Enter new distance : ");
    scanf("%d",&newdistance);
    numberarray[fromindex][toindex] = newdistance;
    numberarray[toindex][fromindex] = newdistance;

    for(int i=0;i<MAX_CITIES;i++){
            for(int j=0;j<MAX_CITIES;j++){
                fprintf(file2, "%03d ", numberarray[i][j]);
            }
            fprintf(file2, "\n");
    }
    fclose(file2);
    printf("Distance Changed Successfully\n");
    menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
    return 0;
    }
    else if(choice == 3){
        printdistable(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
    }
}
int printdistable(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){

    printf("\n\n%4c",' ');
        for(int i = 0;i<30;i++){
                printf(" %.3s",uniquecodearr[i]);
        }
    printf("\n");
    printf("%4c------------------------------------------------------------------------------------------------------------------------\n",' ');
        for(int i = 0; i<MAX_CITIES;i++){
                printf("%.3s|%c",uniquecodearr[i],' ');
        for(int j = 0; j<MAX_CITIES;j++){
            printf("%03d%c",numberarray[i][j],' ');
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0;i<MAX_CITIES;i++){
        printf("%.3s - %.*s",uniquecodearr[i],(int)strlen(citiesarr[i]),citiesarr[i]);
    }
    menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);

}

int  vehiclemanagement(char vehicletype[][6], int vehicledetails[][4]){
    printf(" %-12s%-15s%-20s%-20s%-20s\n","Type","Capacity(kg)","Rate per km(LKR)","Avg Speed (km/h)","Fuel Efficiency (km/l)");
    printf("-----------------------------------------------------------------------------------------\n");
    for(int i = 0; i<3;i++){
        printf(" %-5s ",vehicletype[i]);
        for(int j = 0;j<4;j++){
            printf("%-7c%-10d%-1c",' ',vehicledetails[i][j],' ');
        }
        printf("\n");
    }
    printf("\n");
    return 0;

}

void deliveryorder(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){
    char fromname[4],toname[4];
    int weight,type,redirect,fromindex,toindex,distance;


    vehiclemanagement(vehicletype,vehicledetails);
    printf("Enter Source city unique code(Ex:-Col - Colombo) : ");
     scanf("%s",fromname);
    for(int i =0;i<MAX_CITIES;i++){
        if(strncmp(uniquecodearr[i],fromname,3)==0){
            fromindex = i;
            printf("Enter Destination city unique code : ");
            scanf("%s",toname);
            for(int j =0;j<MAX_CITIES;j++){
                if(strncmp(uniquecodearr[j],toname,3)==0){
                    if(strncmp(toname,fromname,3)!=0){
                        toindex = j;
                        printf("Enter Weight : ");
                        scanf("%d",&weight);
                        if(weight<=1000){
                           printf("Enter Vehicle Type(1=Van,2=Truck,3=Lorry) : ");
                           scanf("%d",&type);
                        }
                        else if((weight>1000)&&(weight<=5000)){
                            printf("Enter Vehicle Type(2=Truck,3=Lorry) : ");
                            scanf("%d",&type);
                        }
                        else if((weight>5000)&&(weight<=10000)){
                            type = 3;
                        }
                        else{
                            printf("\nWe do not have vehicles to transport the goods\n");
                            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
                        }

        }
            else{
                printf("\nSource City and Destination City cannot be the same\n");
                menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        }
        distance = numberarray[fromindex][toindex];
        calculations(weight,type,distance,vehicledetails);
        }

        }
         printf("\nDestinantion City Not Available in the list\n");
         printf("Enter the choice(1=View the list,2=Menu): ");
         scanf("%d",&redirect);
         if(redirect==1){
            printf("\n");
            for(int i = 0;i<MAX_CITIES;i++){
                printf("%.3s - %.*s",uniquecodearr[i],(int)strlen(citiesarr[i]),citiesarr[i]);
                }
                menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
            }
        else if(redirect ==2){
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
            }
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        }

        }
        printf("\nSource City Not Available in the list\n");
        printf("Enter the choice(1=View the list,2=Menu): ");
        scanf("%d",&redirect);
        if(redirect==1){
            printf("\n");
            for(int i = 0;i<MAX_CITIES;i++){
                printf("%.3s - %.*s",uniquecodearr[i],(int)strlen(citiesarr[i]),citiesarr[i]);
                }
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        }
        else if(redirect ==2){
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray);
        }
    }

void calculations(int weight,int type,int distance,int vehicledetails[][4]){


    float deliverycost,estdeliveryhrs,fuelconsumption,fuelcost,totalopcost,profitcalc,estdeliveryminutes;
    int finalcharge;
    int fuelprice = 310;
    type = type -1;

    deliverycost = distance * vehicledetails[type][1] *(1+(weight*1.0/10000));
    estdeliveryhrs = (float)distance / vehicledetails[type][2];
    estdeliveryminutes = ((estdeliveryhrs - (int)estdeliveryhrs)*60 +0.5);
    fuelconsumption = (float)distance / vehicledetails[type][3];
    fuelcost = fuelconsumption * fuelprice;
    totalopcost = deliverycost + fuelcost;
    profitcalc = totalopcost * 0.25;
    finalcharge = totalopcost + profitcalc;

}







