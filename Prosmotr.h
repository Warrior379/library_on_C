#include "Enable.h"
//������� ��� ��������� ��������� ��������� ����
void Prosmotr(){
	int i;
	FILE *f;
	HEAD *t;
	for(;;){
		system("mode con:cols=125");//������ ������ ������ � 125 �������� � ������
		system("cls");
		Po_Seredinke("��������",125);
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
		t = tree_make(f,i);//������� ������ �� ��������� ��������� ����
		if(t->kol == 0) {puts(" ~ ���������� �����!");fclose(f);break;}
		po_krasote();//�������� �����
		print(t->koren);//����� ������ �� �����
		destroy(t->koren);//�������� ������
		fclose(f);//��������� ����
		puts("\n ~ ������ ����������� ������ �����? (1 - �� / 0 - ���) \n");
		fflush(stdin);
		i = Cifra(Correct(3).s_1);
		if(!i) return;
	}
}