#include "Vsat.h"
//����� ����, � ������� ��� ������� ������ ����������
void Poisk(void){
	system("mode con:cols=125");//������ ������ ������ � 125 �������� � ������
	int i;
	FILE *f;
	HEAD *t;
	INFA k;
	int l = 0;
	for(;;){
		system("cls");
		Po_Seredinke("����� ���� �� ���� > ���������",125);
		puts(" ~ ������� ��� ������� ");
		l = Cifra(Correct(5).s_1);
		f = fopen("���_�����.txt","a+");
		Ch(125);//���������
		puts(" ~ �������� ����� ������");
		puts("\n\t\t1) -  ������ �����|");
		puts("\n\t\t2) - ����� �������|");
		i = Cifra(Correct(7).s_1);
		if(i == 1) {t = tree_make(f,1);po_krasote();Poisk_BT_1(t->koren,l);}//������ �����
		else {
			//����� �������
			t = Poisk_BT_2(l,f);
			if(t->kol == 0) puts(" ~ ������������� ����� �� �������.");
			else {po_krasote();print(t->koren);}
		}
		destroy(t->koren);//�������� ������
		fclose(f);
		puts(" ~ ������ �������� ��� �����? (1 - �� / 0 - ���)");
		fflush(stdin);
		i = Cifra(Correct(3).s_1);
		Ch(125);
		if(!i) return;
	}
}