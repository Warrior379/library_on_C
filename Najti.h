#include "bt.h"
//������� ������ ������ �����
void Najti(void){
	system("mode con:cols=125");//������ ������ ������ � 125 �������� � ������
	int i;
	FILE *f;
	HEAD *t;
	INFA k;
	for(;;){
		system("cls");
		Po_Seredinke("����� �����",125);
		puts("\n\n\n");
		puts(" ~ �������� ����� ����� �� ������ ����������:");
		puts("\t\t\t\t\t\t|1 - ��� �����");
	    printf("\t\t\t\t\t\t _____________\n\n");
		puts("\t\t\t\t\t\t|2 - �����, ������� ���� � ����������");
	    printf("\t\t\t\t\t\t ____________________________________\n\n");
		puts("\t\t\t\t\t\t|3 - �����, ������� � ������������� ����������");
	    printf("\t\t\t\t\t\t _____________________________________________\n\n");
		i = Cifra(Correct(2).s_1);
		f = fopen("���_�����.txt","a+");
		//������� ������ �� ��������� ��������� ����
		t = tree_make(f,i);
		if(t->kol == 0) {puts(" ~ ���������� �����!");fclose(f);break;}
		for(;;){
			system("cls");
			Po_Seredinke("����� �����",125);
			puts("\n ~ �������� �������� ������:");
			puts("\n                                                                1) - �����|");
			puts("\n                                                       2) - �������� �����|");
			puts("\n                                                          3) - ��� �������|");
			puts("\n                                                           4) - ����������|");
			puts("\n                                                          5) - ����� �����|");
			i = Cifra(Correct(6).s_1);
			Ch(125);//���������
			t = Poisk_BT(t,i);//� ����������� �� ��������� ���� ������ �����
			if(t->kol == 0) {puts("\n ~ ���� �� �������� ���������� �� �������.\n");Ch(125);break;}
			po_krasote();//�������� �����
			print(t->koren);//������� ������
			if(t->kol == 1){puts("\n ~ ����� �������! \n");Ch(125);break;}//���� � ��� ����� 1 ��-� �� ������ ����� �������
			puts(" ~ ��� ������� ��������? (1 - �� / 0 - ���)");//���� �� ���, �� ���������� ��� �������� �����
			i = Cifra(Correct(3).s_1);
			Ch(125);
			if(!i) break;
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