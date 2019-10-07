#include "Sort.h"
//функция для того чтобы вернуть книгу
void Otdat(){
	system("mode con:cols=125");//делаем размер буфера в 125 символов в ширину
	char s[80];//для запоминания имени файла
	int i;
	FILE *f;
	HEAD *t,*t_1;
	for(;;){
		system("cls");
		strcpy(s,"Все_книги.txt");
		f = fopen(s,"a+");
		t = tree_make(f,1);//создаем дерево на основании всех книг
		t_1 = tree_make(f,3);//на основании книг которые у пользователей
		if(t_1->kol == 0) {puts(" ~ Библиотека пуста");fclose(f);destroy(t->koren);destroy(t_1->koren);return;}
		else{
			fclose(f);
			system("cls");
			Po_Seredinke("ОТДАТЬ КНИГУ",125);
			puts("\n");
			po_krasote();
			print(t_1->koren);//выводим то шо есть у пользователей
			puts(" ~ Введите номер книги, которую хотите отдать ");
			for(;;){
				i = Cifra(Correct(5).s_1);
				if((i > 0)&&(i<=(t_1->kol))) break;
				//номер выбранной книги не должен превышать кол-во книг у пользователей
			}
			t = give_it_back(t,i);
			//возвращаем в общий список выбранный  элемент в списке книг, которые у пользователей
			f = fopen(s,"w");//перезаписываем файл
			Shapka(f);//печатаем шапку в файл
			fprint(t->koren,f);//печатаем само дерево в файл
			destroy(t->koren);//удаляем первое дерево
			destroy(t_1->koren);//удаляем второе
			fclose(f);
			Ch(125);
			puts(" ~ Хотите отдать еще книги? (1 - Да / 0 - Нет)");
			fflush(stdin);
			i = Cifra(Correct(3).s_1);
			Ch(125);
			if(!i) return;
		}
	}
}