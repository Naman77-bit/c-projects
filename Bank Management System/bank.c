#include <stdio.h>
#include <string.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

typedef struct{
    char name[50];
    int acc_no;
    float bal;
}account;

const char* ACCOUNT_FILE="account.dat";  

int main(){
    while (1){
        int c;
        printf("\n\n***Bank Management System***\n");
        printf("1.Create Account\n");
        printf("2.Deposit Money\n");
        printf("3.Withdraw Money\n");
        printf("4.Check Balance\n");
        printf("5.Exit\n");
        printf("Enter your choice\n"); 
        scanf("%d",&c);

        switch(c){
            case 1:
            create_account();
            break;
            case 2:
            deposit_money();
            break;
            case 3:
            withdraw_money();
            break;
            case 4:
            check_balance();
            break;
            case 5:
            printf("\nClosing the bank,thanks for your visit\n");
            return 0;
            break;
            default:
            printf("\nInvalid Choice!\n");
            break;
        }
    }
}
void create_account(){
    account acc;
    FILE *file=fopen(ACCOUNT_FILE,"ab+");
    
    if(file==NULL){
        printf("\nUnable to open file");
        return;
    }
    
    char cha;
    do{
        cha=getchar();
    } while(cha!='\n' && cha!=EOF);

    printf("\nEnter your name : ");
    fgets(acc.name,sizeof(acc.name), stdin);
    int ind=strcspn(acc.name,"\n");
    acc.name[ind] = '\0';
    printf("\nEnter your account number : "); 
    scanf("%d",&acc.acc_no);
    acc.bal=0;

    fwrite(&acc,sizeof(acc),1,file);
    fclose(file);
    printf("\nAccount created successfully!");
}

void deposit_money(){
    FILE *file=fopen(ACCOUNT_FILE,"rb+");
    if(file==NULL){
        printf("\nUnable to open account file!!");
        return;
    }
    int acc_no;
    float money;
    account acc_r;
    printf("\nenter your account number : "); scanf("%d",&acc_no);
    printf("\nEnter money to deposit : "); scanf("\n%f",&money);

    while(fread(&acc_r,sizeof(acc_r),1,file));{
        if(acc_r.acc_no==acc_no){
            acc_r.bal+=money;
            fseek(file,-sizeof(acc_r),SEEK_CUR);
            fwrite(&acc_r,sizeof(acc_r),1,file);
            fclose(file);
            printf("\nSuccessfully deposited Rs.%.2f New balance is Rs.%.2f",money,acc_r.bal);
            return;
        }
    }
    fclose(file);
    printf("\nMoney could not be deposited as account no. %d was not found in the records",acc_no);
}

void withdraw_money(){
    FILE *file=fopen(ACCOUNT_FILE,"rb+");
    if(file==NULL){
        printf("\nnable to open account file!!!");
        return;
    }
    int acc_no;
    float money;
    account acc_r;
    printf("\nEnter your account no : "); scanf("%d",&acc_no);
    printf("\nEnter the amount you wish to withdraw : "); scanf("%f",&money);

    while(fread(&acc_r, sizeof(acc_r),1,file)){
        if(acc_r.acc_no=acc_no){
            if(acc_r.bal>=money){
                acc_r.bal-=money;
                fseek(file,-sizeof(acc_r),SEEK_CUR);
                fwrite(&acc_r,sizeof(acc_r),1,file);
                printf("\nSuccessfully withdrawn Rs.%.2f  Reamining balance Rs.%.2f",money,acc_r.bal); 
            }
            else{
                printf("\nInsufficient balance!");
            }
            fclose(file);
            return;
        }
    }
    printf("\nMoney could not be withdrawn as account %d was not found in records",acc_no);
}

void check_balance(){
    FILE *file = fopen(ACCOUNT_FILE,"rb");
    if(file==NULL){
        printf("\nUnable to open file");
        return;
    }
    
    int acc_no;
    account acc_read;
    
    char cha;
    do{
        cha=getchar();
    } while(cha!='\n' && cha!=EOF);
    
    printf("\nEnter your account number : "); 
    scanf("%d",&acc_no);
    
    while(fread(&acc_read,sizeof(acc_read),1,file)){  
        if(acc_read.acc_no==acc_no){
            printf("\nYour account balance is Rs%.2f",acc_read.bal);
            fclose(file);
            return;
        }
    }
    
    fclose(file);
    printf("\nAccount No: %d was not found\n",acc_no); 
}