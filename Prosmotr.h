#include "Enable.h"
//функция для просмотра выбранной категории книг
void Prosmotr(){
	int i;
	FILE *f;
	HEAD *t;
	for(;;){
		system("mode con:cols=125");//делаем размер буфера в 125 символов в ширину
		system("cls");
		Po_Seredinke("ПРОСМОТР",125);
		puts("\n\n\n");
		puts(" ~ Выберите какие книги вы хотите посмотреть:");
		puts("\t\t\t\t\t\t|1 - все книги");
	    printf("\t\t\t\t\t\t _____________\n\n");
		puts("\t\t\t\t\t\t|2 - книги, которые есть в библиотеке");
	    printf("\t\t\t\t\t\t ____________________________________\n\n");
		puts("\t\t\t\t\t\t|3 - книги, которые у пользователей библиотеки");
	    printf("\t\t\t\t\t\t _____________________________________________\n\n");
		i = Cifra(Correct(2).s_1);
		f = fopen("Все_книги.txt","a+");
		t = tree_make(f,i);//создаем дерево на основании выбранных книг
		if(t->kol == 0) {puts(" ~ Библиотека пуста!");fclose(f);break;}
		po_krasote();//печатаем шапку
		print(t->koren);//вывод дерева на экран
		destroy(t->koren);//удаление дерева
		fclose(f);//закрываем файл
		puts("\n ~ Хотите просмотреть другие файлы? (1 - Да / 0 - Нет) \n");
		fflush(stdin);
		i = Cifra(Correct(3).s_1);
		if(!i) return;
	}
}