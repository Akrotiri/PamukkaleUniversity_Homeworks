/*
 * Author: Fulya AKCAN
 * Date  : 13.10.2013
 * Description: Algoritmalar Dersi - Odev 2
 */
#include <stdio.h>
#include <conio.h>

// Dizi boyutunu hesaplayan macro. Bellekteki dizi boyutunu 
// ilk dizi elemani boyutuna bolerek dizi elemani sayisini buluruz
#define SizeOfArray(x)  (sizeof(x) / sizeof(x[0]))

char *words[] = {"birlik", "onluk", "yuzluk", "binlik", "on binlik"};

// Base : Ussu alinacak taban sayi
// Power: Alinacak us
int pow(int base, int power){
	if(power <= 0)
		return 1;
	else if(power == 1)
		return base;
	return base * pow(base, power - 1);
}

// Klavyeden girilen n haneli bir tam sayiyi (integer) cozumler
int main(int argc, char *argv[]){
	int number = 0, fraction = 0, divider = 0, i = SizeOfArray(words) - 1;	
	printf("Cozumlenecek sayiyi giriniz: ");
	scanf("%d", &number);
	while(number > 0){
		divider = pow(10, i);
		fraction = number / divider;
		printf("%d tane %s sayi \n", fraction, words[i--]);
		number = number - (fraction * divider);
	}
	getch();
	return 0;
}