#include "Rabota_s_bibliotekoj.h"
//������� �������� ����� ����������
void SOZD(void){
	system("cls");//������ �����
	char s[30];//��� �������� ����������
	Po_Seredinke("�������� ����������",60);
	puts("\n ~ ������� �������� ���������� \n");
	strcpy(s,Correct(4).s_1);
	//�������
	mkdir(s);
	printf("\n ~ ���������� \"%s\" ������� �������! ~\n",s);
	return;
}
//������� ��� �������������� ����������
void IZMENIT(void){
	system("cls");
	Po_Seredinke("�������������� ����������",60);
	puts("\n");
	puts("\n ~ ������� ����� ����������, ������� ������ ������������� \n");
	BIB(3);//��������������� ���������
	return;
}
//������� ��� �������� ����������
void OTKRIT(void){
	system("cls");
	Po_Seredinke("�������� ����������",60);
	puts("\n");
	puts("\n ~ ������� ����� ����������, ������� ������ ������� \n");
	BIB(1);//��������� ���������
	return;
}
//������� ��� �������� ����������
void UDALIT(void){
	system("cls");
	Po_Seredinke("�������� ����������",60);
	puts("\n");
	puts("\n ~ ������� �������� ����������, ������� ������ ������� \n");
	BIB(2);//������� ���������
	return;
}
//�������� ������ ���������
void O_programme(void){
	system("cls");
	puts("   ~           ������ ��������� ����� ������� ����������.|");
	puts("  _______________________________________________________");
	puts("   ~           ��� ����� ���� ������������ ��� ��� ������|");
	puts("  _______________________________________________________");
	puts("   ~                        ��� � ��� ������������ �����!|");
	puts("  _______________________________________________________");
	puts("   ~       ������������ ��� ���� ����� ������� ����������|");
	puts("  _______________________________________________________");
	puts("   ~               ����������� �� ���� � ���������� ����,|");
	puts("  _______________________________________________________");
	puts("   ~                          ������� �� ����� ���������,|");
	puts("  _______________________________________________________");
	puts("   ~                                    ��� ����� ������!|");
	puts("  _______________________________________________________");
	puts("   ~                  ���������� ������������ ����� �����|");
	puts("  _______________________________________________________");
	puts("   ~        � ������� ���� ��������� ������� ������ ����,|");
	puts("  _______________________________________________________");
	puts("   ~                            ������� ���� � ����������|");
	puts("  _______________________________________________________");
	puts("   ~                      � ����, ������� ����� ��������.|");
	puts("  _______________________________________________________");
	Po_Seredinke("������ ��������� 1.0",60);
}
//� ���������� ���������
void Razrab(void){
	system("cls");
	Po_Seredinke("�������� ������������ ��������������� �����������",60);
	Po_Seredinke("�������� ������������ ������",60);
	Po_Seredinke("������� �������������� ������",60);
	Po_Seredinke("������� ������ �� - 175",60);
	Po_Seredinke("��������� ������ ����������",60);
	Po_Seredinke("������",60);
	Po_Seredinke("2018",60);
	Po_Seredinke("������ ��������� 1.0",60);
}