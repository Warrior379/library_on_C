#include "Vsat.h"
//поиск книг, у которых год издания больше введенного
void Poisk(void){
	system("mode con:cols=125");//делаем размер буфера в 125 символов в ширину
	int i;
	FILE *f;
	HEAD *t;
	INFA k;
	int l = 0;
	for(;;){
		system("cls");
		Po_Seredinke("ПОИСК КНИГ ПО ГОДУ > ЗАДАННОГО",125);
		puts(" ~ Введите год издания ");
		l = Cifra(Correct(5).s_1);
		f = fopen("Все_книги.txt","a+");
		Ch(125);//штриховка
		puts(" ~ Выберите метод поиска");
		puts("\n\t\t1) -  Просто вывод|");
		puts("\n\t\t2) - Вывод списком|");
		i = Cifra(Correct(7).s_1);
		if(i == 1) {t = tree_make(f,1);po_krasote();Poisk_BT_1(t->koren,l);}//просто вывод
		else {
			//вывод списком
			t = Poisk_BT_2(l,f);
			if(t->kol == 0) puts(" ~ Запрашиваемая книга не найдена.");
			else {po_krasote();print(t->koren);}
		}
		destroy(t->koren);//удаление дерева
		fclose(f);
		puts(" ~ Хотите поискать еще книги? (1 - Да / 0 - Нет)");
		fflush(stdin);
		i = Cifra(Correct(3).s_1);
		Ch(125);
		if(!i) return;
	}
}