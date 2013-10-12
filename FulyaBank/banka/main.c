/*
 * Author: Fulya AKCAN
 * Date  : 13.10.2013
 * This program simply demonstrates a bank application 
 * which simulates paying cash into a bank account, 
 * withdrawal of cash from a bank account or 
 * transferring cash to another bank account.
 */

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>

#define NEWLINE "\n"
#define True 1
#define SizeOfArray(x)  (sizeof(x) / sizeof(x[0]))

float para_miktari[] = {500.00,400.23,230.65};
char* hesap_no[] = {"100.80.23","100.80.25","100.80.28"};
char* username[] = {"fulya","recep","kadir"};
char* password[] = {"akcan","erol","yaldir"};

int login(int choice) {
	char *input_username, *input_password;
	int valid;
	input_username = (char*) malloc(sizeof(char) * 50);
	input_password = (char*) malloc(sizeof(char) * 50);
	printf("Kullanici adinizi giriniz: ");
	scanf("%s",input_username);
	printf("Sifrenizi giriniz: ");
	scanf("%s",input_password);

	if(strcmp(input_username,username[choice]) == 0 && strcmp(input_password,password[choice]) == 0){
		printf("Girdiginiz bilgiler dogru\n");
		valid = 1;
	}
	else{
		printf("Girdiginiz bilgiler yanlis!\n");
		valid = 0;
	}
	free(input_username);
	free(input_password);
	system("cls");
	return valid;
}


void hesapGoster(int hesap) {
	printf("Hesap no: %s\n",hesap_no[hesap]);
	printf("Mevduat: %.2f\n",para_miktari[hesap]);
}

int paraEkle(int hesap, float miktar) {	
	para_miktari[hesap] = para_miktari[hesap] + miktar;
	return 1;
}

int paraCek(int hesap, float miktar) {
	int valid;
	if (miktar > para_miktari[hesap]){
		printf("Bakiyeniz yetersiz!\n");
		valid = 0;
	}
	else {
		para_miktari[hesap] = para_miktari[hesap] - miktar;
		valid = 1;
	}
	return valid;
}

void havale(int hesap1,int hesap2,float miktar) {
	if(paraCek(hesap1, miktar)){
		paraEkle(hesap2, miktar);
	}
}

int menu() {
	int choice = 1;	
	printf(NEWLINE);
	printf("1) Hesap Bilgileri" NEWLINE);
	printf("2) Para Ekle" NEWLINE);
	printf("3) Para Cek" NEWLINE);
	printf("4) Havale" NEWLINE);
	printf("5) Programdan Cik" NEWLINE);
	printf("Seciminiz: ");
	scanf("%d",&choice);
	
	system("cls");
	return choice;
}

int hesapBul(char* hesapNo) {
	int index;
	int arraySize = SizeOfArray(hesap_no);
	for(index = 0;index < arraySize; index++){
		if(strcmp(hesapNo,hesap_no[index]) == 0){
			return index;
		}
	}
	return -1;
}

int main(int argc, char *argv[]) { 
	float miktar = 0;
	int hesap_no1_index, hesap_no2_index;
	char *havale_no;
	havale_no = (char*) malloc(sizeof(char) * 50);

	do {
		printf("Islem yapilacak hesap numarasini giriniz: ");
		scanf("%s", havale_no);
		hesap_no1_index = hesapBul(havale_no);
		if(hesap_no1_index == -1){
			printf("Hesap numarasi bulunamadi. Tekrar giriniz!" NEWLINE);		
		}
	} while(hesap_no1_index == -1);
	
	while(login(hesap_no1_index) != 1);

	do{
		switch(menu()){
			case 1:
				hesapGoster(hesap_no1_index);
				break;
			case 2:				
				printf("Eklemek istediginiz para miktarini giriniz: ");
				scanf("%f",&miktar);
				paraEkle(hesap_no1_index, miktar);
				break;
			case 3:
				printf("Cekmek istediginiz para miktarini giriniz: ");
				scanf("%f",&miktar);
				paraCek(hesap_no1_index,miktar);
				break;
			case 4:				
				printf("Havale edilecek hesap numarasini giriniz: ");
				scanf("%s", havale_no);
				hesap_no2_index = hesapBul(havale_no);
				if(hesap_no2_index != -1){
					printf("Havale etmek istediginiz para miktarini giriniz: ");
					scanf("%f",&miktar);
					havale(hesap_no1_index, hesap_no2_index, miktar);
					hesapGoster(hesap_no1_index);
					hesapGoster(hesap_no2_index);
				}
				else{
					printf("Havale edilecek hesap numarasi bulunamadi!" NEWLINE);
				}				
				break;
			case 5:
			default:
				free(havale_no);
				return 0;
		}
	} while(True);

	free(havale_no);
	return 0;
}
