//Index Number :- AS20240539
//Name :- Gowthaman Navarathnarajah


#include <stdio.h>
#include <string.h>
#include <stdbool.h>


#define MAX_CITIES 30


void menu(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount);
int selcchoice(char vehicletype[][6],int vehicledetails[][4],int choice,char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount);
int readfromfiles(char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]);
int citymanagement(int citycount,char uniquecodearr[][10],char citiesarr[][MAX_CITIES],int numberarray[][MAX_CITIES]);
int inputdistance(char citiesarr[][MAX_CITIES],int numberarray[][MAX_CITIES],int citycount);
int distancemanagement(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount);
int printdistable(char vehicletype[][6],int vehicledetails[][4], char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount);
int  vehiclemanagement(char vehicletype[][6], int vehicledetails[][4]);
void deliveryorder(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount);
void calculations(int weight,int type,int distance,int vehicledetails[][4],int fromindex,int toindex,char citiesarr[][MAX_CITIES],char vehicletype[][6]);
int printdelivery(float calcarray[],char citiesarr[][MAX_CITIES],char vehicletype[][6],int vehicledetails[][4]);
void storereports(float calcarray[],char citiesarr[][MAX_CITIES],char vehicletype[][6]);

int main(){

char vehicletype[][6] = {"Van","Truck","Lorry"};
int vehicledetails[][4] = {{1000,30,60,12},{5000,40,50,6},{10000,80,45,4}};

int numberarray[MAX_CITIES][MAX_CITIES]; char uniquecodearr[MAX_CITIES][10]; char citiesarr[MAX_CITIES][MAX_CITIES]; int citycount;


menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);



}
void menu(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount){
    int choice;
    citycount = readfromfiles(citiesarr,uniquecodearr,numberarray);

    printf("\n\t\t\t\t--Menu--\n");
    printf("\t\t1.City Management(Add,edit or rename a city)\n");
    printf("\t\t2.Distance Management\n");
    printf("\t\t3.Display the vehicle type table\n");
    printf("\t\t4.Place a delivery order\n");
    printf("\n\t\tEnter Choice : ");
    scanf("%d",&choice);
    selcchoice(vehicletype,vehicledetails,choice,citiesarr,uniquecodearr,numberarray,citycount);
}

int selcchoice(char vehicletype[][6],int vehicledetails[][4],int choice,char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount){
    switch(choice){
    case 1:
        citymanagement(citycount,uniquecodearr,citiesarr,numberarray);
        menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        break;

    case 2:
        distancemanagement(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        break;

    case 3:
        vehiclemanagement(vehicletype,vehicledetails);
        break;
    case 4:
        deliveryorder(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        break;


}



}
int readfromfiles(char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES]){
    FILE *file1 = fopen("cities.txt","r");
    FILE *file2 = fopen("UniqueCode.txt","r");
    FILE *file3 = fopen("distance.txt","r");
    int i = 0; int count;

    while (fgets(citiesarr[i], sizeof(citiesarr[i]), file1)&& i<MAX_CITIES) {
                i++;
           }
    count = i;
    fclose(file1);
    i=0;
     while (fgets(uniquecodearr[i], sizeof(uniquecodearr[i]), file2)&& i<MAX_CITIES) {
                i++;
           }
    fclose(file2);
    i=0;
     for (int i = 0; i < count;i++) {
        for (int j = 0; j < count; j++) {
            fscanf(file3, "%d", &numberarray[i][j]);
        }
    }
    fclose(file3);
    return count;

    //return 0;

}
int citymanagement(int citycount,char uniquecodearr[][10],char citiesarr[][MAX_CITIES],int numberarray[][MAX_CITIES]){
    int choice; char city[MAX_CITIES],buffer[MAX_CITIES],unique[4];
     FILE *file1; FILE *temp1;

    printf("\n\t1.Add a new city\n");
    printf("\t2.Rename a city\n");
    printf("\t3.Remove a city\n");
    printf("\tEnter Choice : ");
    scanf("%d",&choice);
    getchar();
    if(choice == 1){
        if(citycount<MAX_CITIES){

            file1 = fopen("cities.txt","a");
            FILE *file2 = fopen("UniqueCode.txt","a");

            printf("\nEnter City Name: ");
            fgets(city,sizeof(city),stdin);
            fputs(city,file1);
            strcpy(citiesarr[citycount], city);
            printf("Enter a 3 letter unique code to that city : ");
            fgets(unique,sizeof(unique),stdin);
            fprintf(file2,"\n");
            fputs(unique,file2);

            fclose(file1);
            fclose(file2);
            printf("Successfully Added %.*s to the list\n",(int)strlen(city)-1,city);

            inputdistance(citiesarr,numberarray,citycount);

        }
        else{
            printf("Maximum Numbers of Cities Reached Please Contact the Administrator to add more cities\n");
        }
    }
    else if(choice == 2){

        temp1 = fopen("Temporary.txt","w");
        file1 = fopen("cities.txt","r");
        FILE *file2 = fopen("UniqueCode.txt","w");

        char oldname[MAX_CITIES],newname[MAX_CITIES];

        printf("Enter the city to be renamed : ");
        fgets(oldname,sizeof(oldname),stdin);
        int i = 0;
        while (fgets(buffer, sizeof(buffer), file1)){
            if(strcmp(buffer,oldname)==0){
                printf("Enter the new name:  ");
                fgets(newname,sizeof(newname),stdin);
                fputs(newname, temp1);
                printf("Enter a 3 letter unique code : ");
                scanf("%s",uniquecodearr[i]);
                fputs(uniquecodearr[i], file2);
                fputs("\n",file2);

                printf("\nSuccessfully renamed %.*s to %.*s\n",(int)strlen(oldname)-1,oldname,(int)strlen(newname)-1,newname);
                }
            else{
                fputs(buffer,temp1);
                fputs(uniquecodearr[i], file2);
                }
            i++;
            }
        fclose(file1);
        fclose(file2);
        fclose(temp1);
        remove("cities.txt");
        rename("Temporary.txt","cities.txt");

        }

    else if(choice == 3){
            char name[MAX_CITIES];

            temp1 = fopen("Temporary.txt","w");
            file1 = fopen("cities.txt","r");
            FILE *file2 = fopen("UniqueCode.txt","w");

            printf("Enter the city to be removed : ");
            fgets(name,sizeof(name),stdin);
            int i =0;
            while(fgets(buffer,sizeof(buffer),file1)){
                if(strcmp(buffer,name)!=0){
                    fputs(buffer,temp1);
                    fputs(uniquecodearr[i],file2);
                }
                i++;
            }
            printf("\nSuccessfully removed city %.*s from the list\n",(int)strlen(name)-1,name);
            fclose(file1);
            fclose(file2);
            fclose(temp1);
            remove("cities.txt");
            rename("Temporary.txt","cities.txt");
            }
            return 0;
}
int inputdistance(char citiesarr[][MAX_CITIES],int numberarray[][MAX_CITIES],int citycount){
    FILE *file1 = fopen("distance.txt","w");

    int inputdistance;

    for(int i=0;i<(citycount);i++){
        printf("Enter distance from %.*s to %.*s : ",(int)strlen(citiesarr[citycount])-1,citiesarr[citycount],(int)strlen(citiesarr[i])-1,citiesarr[i]);
        scanf("%d",&inputdistance);
        numberarray[citycount][i] = inputdistance;
        numberarray[i][citycount] = inputdistance;
    }
    numberarray[citycount][citycount] = 0;


    for(int i=0;i<=citycount;i++){
            for(int j=0;j<=citycount;j++){
                fprintf(file1, "%03d ", numberarray[i][j]);
            }
            fprintf(file1, "\n");
    }
    fclose(file1);
    return 0;

}

int distancemanagement(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount){

    char fromcity[4]; char tocity[4]; char buffer[20];
    int toindex=0,fromindex=0,choice;

    printf("1.Edit distances between two cities\n");
    printf("2.Display the distance table\n");
    printf("Enter Choice : ");
    scanf("%d",&choice);
    getchar();

    if(choice == 1){
        FILE *file2 = fopen("distance.txt","w");
        //FILE *temp1 = fopen("temporary.txt","r");
        printf("Enter the first 3 letters of From City : ");
        scanf("%s",fromcity);
        printf("Enter the first 3 letters of To City : ");
        scanf("%s",tocity);
        for(int i=0;i<citycount;i++){
                if(strncmp(uniquecodearr[i],fromcity,3)==0){
                    fromindex = i;
                    break;
                }
        }
        for(int i=0;i<citycount;i++){
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

    for(int i=0;i<citycount;i++){
            for(int j=0;j<citycount;j++){
                fprintf(file2, "%03d ", numberarray[i][j]);
            }
            fprintf(file2, "\n");
    }
    fclose(file2);
    printf("Distance Changed Successfully\n");
    menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
    return 0;
    }
    else if(choice == 2){
        printdistable(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
    }
}
int printdistable(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount){

    printf("\n\n%4c",' ');
        for(int i = 0;i<citycount;i++){
                printf(" %.3s",uniquecodearr[i]);
        }
    printf("\n\n");
        for(int i = 0; i<citycount;i++){
                printf("%.3s|%c",uniquecodearr[i],' ');
        for(int j = 0; j<citycount;j++){
            printf("%03d%c",numberarray[i][j],' ');
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0;i<citycount;i++){
        printf("%.3s - %.*s",uniquecodearr[i],(int)strlen(citiesarr[i]),citiesarr[i]);
    }
    menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);

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

void deliveryorder(char vehicletype[][6],int vehicledetails[][4],char citiesarr[][MAX_CITIES],char uniquecodearr[][10],int numberarray[][MAX_CITIES],int citycount){
    char fromname[4],toname[4];
    int weight,type,redirect,fromindex,toindex,distance;


    vehiclemanagement(vehicletype,vehicledetails);
    printf("Enter Source city unique code(Ex:-Col - Colombo) : ");
     scanf("%s",fromname);
    for(int i =0;i<citycount;i++){
        if(strncmp(uniquecodearr[i],fromname,3)==0){
            fromindex = i;
            printf("Enter Destination city unique code : ");
            scanf("%s",toname);
            for(int j =0;j<citycount;j++){
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
                            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
                        }

        }
            else{
                printf("\nSource City and Destination City cannot be the same\n");
                menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        }
        distance = numberarray[fromindex][toindex];
        calculations(weight,type,distance,vehicledetails,fromindex,toindex,citiesarr,vehicletype);
        menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        }

        }
         printf("\nDestinantion City Not Available in the list\n");
         printf("Enter the choice(1=View the list,2=Menu): ");
         scanf("%d",&redirect);
         if(redirect==1){
            printf("\n");
            for(int i = 0;i<citycount;i++){
                printf("%.3s - %.*s",uniquecodearr[i],(int)strlen(citiesarr[i]),citiesarr[i]);
                }
                menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
            }
        else if(redirect ==2){
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
            }
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        }

        }
        printf("\nSource City Not Available in the list\n");
        printf("Enter the choice(1=View the list,2=Menu): ");
        scanf("%d",&redirect);
        if(redirect==1){
            printf("\n");
            for(int i = 0;i<citycount;i++){
                printf("%.3s - %.*s",uniquecodearr[i],(int)strlen(citiesarr[i]),citiesarr[i]);
                }
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        }
        else if(redirect ==2){
            menu(vehicletype,vehicledetails,citiesarr,uniquecodearr,numberarray,citycount);
        }
    }

void calculations(int weight,int type,int distance,int vehicledetails[][4],int fromindex,int toindex,char citiesarr[][MAX_CITIES],char vehicletype[][6]){


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

    float calcarray[]={weight,type,distance,fromindex,toindex,deliverycost,estdeliveryhrs,estdeliveryminutes,fuelconsumption,fuelcost,totalopcost,profitcalc,finalcharge};
    printdelivery(calcarray,citiesarr,vehicletype,vehicledetails);
    storereports(calcarray,citiesarr,vehicletype);
}

int printdelivery(float calcarray[],char citiesarr[][MAX_CITIES],char vehicletype[][6],int vehicledetails[][4]){

    int strlen1 = strlen(citiesarr[(int)calcarray[3]])-1;
    int strlen2 = strlen(citiesarr[(int)calcarray[4]])-1;
    int type = (int)calcarray[1];

    printf("\n\n==============================================================\n");
    printf("\nDELIVERY COST ESTIMATION\n");
    printf("\n--------------------------------------------------------------\n");
    printf("\nFrom: %.*s\n",strlen1,citiesarr[(int)calcarray[3]]);
    printf("\nTo: %.*s\n",strlen2,citiesarr[(int)calcarray[4]]);
    printf("\nMinimum Distance: %d\n",(int)calcarray[2]);
    printf("\nVehicle: %s\n",vehicletype[type]);
    printf("\nWeight: %d kg\n",(int)calcarray[0]);
    printf("\n--------------------------------------------------------------\n");
    printf("\nBase Cost: %d × %d × (1+%d/10000) = %d LKR\n ",(int)calcarray[2],vehicledetails[type][1],(int)calcarray[0],(int)calcarray[5]);
    printf("\nFuel Used: %.2f  L\n",calcarray[8]);
    printf("\nFuel Cost: %.2f LKR\n",calcarray[9]);
    printf("\nOperational Cost: %.2f LKR\n",calcarray[10]);
    printf("\nProfit: %.2f LKR\n",calcarray[11]);
    printf("\nCustomer Charge: %.2f LKR\n",calcarray[12]);
    if((int)calcarray[7]>=10){
        printf("\nEstimated Time: %d hours and %d minutes\n",(int)calcarray[6],(int)calcarray[7]);
    }
    else{
        printf("\nEstimated Time: %d hours\n",(int)calcarray[6]);
    }
    printf("\n==============================================================\n");
    return 0;

}

void storereports(float calcarray[],char citiesarr[][MAX_CITIES],char vehicletype[][6]){

    float storereportarr[50][11];
    static int row = 0;

    FILE *file1 = fopen("Store.txt","a");
    int strlen1 = strlen(citiesarr[(int)calcarray[3]])-1;
    int strlen2 = strlen(citiesarr[(int)calcarray[4]])-1;


    fprintf(file1,"%10.*s %16.*s %15s %11d",strlen1,citiesarr[(int)calcarray[3]],strlen2,citiesarr[(int)calcarray[4]],vehicletype[(int)calcarray[1]],(int)calcarray[0]);
    fprintf(file1,"%10d %9dhr and %d mins %9.2f",(int)calcarray[5],(int)calcarray[6],(int)calcarray[7],calcarray[8]);
    fprintf(file1,"%18.2f %10d %22d %10d\n",calcarray[9],(int)calcarray[10],(int)calcarray[11],(int)calcarray[12]);
    fclose(file1);

    for(int i = 0;i<11;i++){
        if(i!=6){
            storereportarr[row][i] = calcarray[i];
        }

    }
    row++;
}








