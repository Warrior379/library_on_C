#include "Sort.h"
//������� ��� ���� ����� ������� �����
void Otdat(){
	system("mode con:cols=125");//������ ������ ������ � 125 �������� � ������
	char s[80];//��� ����������� ����� �����
	int i;
	FILE *f;
	HEAD *t,*t_1;
	for(;;){
		system("cls");
		strcpy(s,"���_�����.txt");
		f = fopen(s,"a+");
		t = tree_make(f,1);//������� ������ �� ��������� ���� ����
		t_1 = tree_make(f,3);//�� ��������� ���� ������� � �������������
		if(t_1->kol == 0) {puts(" ~ ���������� �����");fclose(f);destroy(t->koren);destroy(t_1->koren);return;}
		else{
			fclose(f);
			system("cls");
			Po_Seredinke("������ �����",125);
			puts("\n");
			po_krasote();
			print(t_1->koren);//������� �� �� ���� � �������������
			puts(" ~ ������� ����� �����, ������� ������ ������ ");
			for(;;){
				i = Cifra(Correct(5).s_1);
				if((i > 0)&&(i<=(t_1->kol))) break;
				//����� ��������� ����� �� ������ ��������� ���-�� ���� � �������������
			}
			t = give_it_back(t,i);
			//���������� � ����� ������ ���������  ������� � ������ ����, ������� � �������������
			f = fopen(s,"w");//�������������� ����
			Shapka(f);//�������� ����� � ����
			fprint(t->koren,f);//�������� ���� ������ � ����
			destroy(t->koren);//������� ������ ������
			destroy(t_1->koren);//������� ������
			fclose(f);
			Ch(125);
			puts(" ~ ������ ������ ��� �����? (1 - �� / 0 - ���)");
			fflush(stdin);
			i = Cifra(Correct(3).s_1);
			Ch(125);
			if(!i) return;
		}
	}
}