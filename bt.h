#include "Po_Seredinke.h"
const char sost_1[] = "�_����������";
const char sost_2[] = "�_������������";
//��������� ��������������� ���� �������� ��������� ������
typedef struct info{
	int n;
	char avtor[30];
	char nazv[40];
	int god;
	int kol;
	char sostojanie[15];
}INFA;
//���������� ������ ���� ������ INFA, ������� �������� struct info - ����� � ���������� �� ����� ���� � ������� ������

//��������� �������� ��������� ������
typedef struct tree{
	INFA inf;//�������������� ����
	struct tree *right;//��������� �� ������ ���������
	struct tree *left;//��������� �� ����� ���������
	struct tree *predok;//��������� �� ��������
}TREE;

//��������� ������ ������
typedef struct head{
	TREE *koren;//������(������) ������
	int kol;//���������� ��������� � ������
}HEAD;

//���������� ���������� ��������� � ���������� �� ���������(������)
/*��������, � ������ ������ �������� � ����� ����� ���� ������
����� ��� ����������, ������� �������� � ������, ����� ������ � ������ ������, ����� �������� ���� ��������� ���
������ ����� � ������, � ��� ���� �� �������� � ����� ������ ����� ������
*/
 int usel(const TREE *search_n){
	 int u =0;
	 if(search_n == NULL) return u;
	 u+=usel(search_n->left);
	 u++;
	 u+=usel(search_n->right);
	 return u;
 }
 
 //�������� ��������� ������
 HEAD *sozd(void){
	 HEAD *new_tree = (HEAD*)malloc(sizeof(HEAD));//��������� ������ ��� ������ ������
	 if(new_tree == NULL) return NULL;//���� ������ �� ����������
	 new_tree->koren = NULL;//�������� ��������� �� ������ 
	 new_tree->kol = 0;//���������� � ������ ���� ���������
	 return new_tree;//����������� ��������� �� ������
 }
 
 //��������� ������ � �������� ������ ��� ������ ��������
 TREE **vstav(TREE **search_tree){//���������� ����� ���������(����� ������)
	 TREE **v = search_tree;
			 for(;;){//�������� �� ������ � ������ ����� ��� ��������� ������ ��������
				 if(*v == NULL) return v;//���������� ������� ���������, ���������� ��� �����
				 if(usel((*v)->right)>usel((*v)->left)){/*�������� � ������ ������ ������������� ����������,
				 ������� ������������ ���������� ��������� � ������ � ����� ���������, 
				 ��� ������ - ���� � ��������� � ��� ���� �� ��������� ������(�������) ���������,
				 ���� ����� �������� ����� �������
				 */
					 v = &((*v)->left);
				 }
				 else{
					 v = &((*v)->right);
				 }
			 }
 }
 
 //��������� ������ ������ ��� ������������ ��������
 TREE **vstav_pr(TREE **search_tree){
	 /*������ ���� ������� ���������� ������� ������ ������ ��� ������������ ��������, ������ ��� �������� �� ������,
	 ������������ ��� �������� ��� ������ �������� � �����, ����� ������ ����� ��������� �� ������������ ��� ��������
	 */
	 TREE **pr = search_tree;
	 TREE **t = search_tree;
	 if(t == NULL) return NULL;/*������ ����� ������ ������ �������� � � ��� ��� ���������,
	 ����� ����������� ������� ����� ������, � � ����� ��� ���������
	 */
	 for(;;){
		if((*t) == NULL) return pr;
		pr = t;
		if(usel((*t)->right)>usel((*t)->left)){
			t = &((*t)->left);
		}
		else{
			t = &((*t)->right);
		}
	 }
 }
 
 //������ ������ �������� � �������� ������
int vstavka(HEAD *search_tree, INFA i){//��� ������� ����� ��������� �� ������ ������ � �������������� ���� ������������ �������� 
	 TREE *n;
	 TREE **v = vstav(&(search_tree->koren));//�������� ����� ���� �������� �������
	 TREE **pr = vstav_pr(&(search_tree->koren));//�������� ����� ��� ������
	 n = *v = (TREE *)malloc(sizeof(TREE));/*��������� ������ ��� ������������ ��������, ������
	 ��������� �� ���������� ������ ����� ������ ������ � �������� �������*/
	 if(n == NULL) return 0;//���� ������ ���, �� ������� ������ ����
	 //�������������� ����� �������
	 n->right = NULL;//������ ���� ������
	 n->left = NULL;//����� ����
	 n->inf = i;//� �������������� ���� �������, �� ��� ���� �������� � ������� ����������
	 n->predok = *pr;//���������� ��������� �� ��������
	 search_tree->kol++;//����������� ���������� ��������� ��������� ������
	 return 1;//������� ������ 1 ���� ������� �������� � ���������������
 }
 
 //���������� ������� �� ��������� �������������� ����� ��������� ��������� ������
 INFA *pol(TREE *search_n, INFA *v){
	 if(search_n == NULL) return v;
	 v = pol(search_n->left,v);
	 *v = search_n->inf; v++;
	 v = pol(search_n->right,v);
 }
 
 //���������� �������������� ����� ��������� ��������� ������ �� ��������� ��������� �������
 INFA *o_pol(TREE *search_n, INFA *v){
	 if(search_n == NULL) return v;
	 v = o_pol(search_n->left,v);
	 search_n->inf = *v; v++;
	 v = o_pol(search_n->right,v);
 }
 
 //�������������� ��������� ������ � �������� ������ ������(���)
 void BST_make(HEAD *search_tree){
	INFA *v,*b,c;
	int i,j,m,l;
	v = (INFA*)malloc(sizeof(INFA)*(search_tree->kol));//��������� ������ ��� ������� �������������� ����� ��������� ������
	b = v;
	pol(search_tree->koren, b);//���������� ����� �������
	b=v;
	for(i=0;i<(search_tree->kol);i++){//���������� �� ������
		b = v;
		for(j = 0; j<(search_tree->kol)-1;j++){
			m = (b+1)->n;
			l = b->n;
			if(l>m){
				c = *b;
				*b = *(b+1);
				*(b+1) = c;
			}
			b++;
		}
	}
	b=v;
	o_pol(search_tree->koren, b);//���������� �������������� ����� ���������������� ��� ������
	free(v);//������������ ����� �������
 }
 
 //�������������� ��������� � ������ ���� ��� �������
 int Redakt(TREE *t,int i){
	 if(t == NULL) return i;
	 i=Redakt(t->left,i);
	 t->inf.n = i; i++;
	 i=Redakt(t->right,i);
 }
 
 //�������� ��������� ������ ������ �� ��������� ������ � �����
HEAD *tree_make(FILE *F, int i){
	HEAD *t;
	char s[130];
	t = sozd();//��������� ������ ��������� ������
	INFA infa;
	fseek(F,0,SEEK_END);//�������� ��������� � ����� � �����
	long pos=ftell(F);//����������� ������ �������� ����� � �����
	if(pos>0){/*���� ������� ���� ������ �� pos = 0, ���� ���� ������ �� ����� �������� �������� � ����� ������ �� ���������,
	� ������ ����� ����� = ������. ���� ���� �� ������ �� pos ����� > 0*/
		rewind(F);//����������� ��������� � ������ �����
		fgets(s,131,F);//���������� ����� ������ ������ � �����
		fgets(s,131,F);//���������� ������ ������ � �����
	  while(!feof(F)){//���� �� ��������� ����� �����
		fscanf(F,"-----------------------------------------------------------------------------------------------------------------------------\n\
		| %d | %s | %s | %d | %d | %s | \n\
		-----------------------------------------------------------------------------------------------------------------------------\n"\
		, &infa.n,&infa.avtor,&infa.nazv,&infa.god,&infa.kol,&infa.sostojanie);//���������� ������ �� ����� � ��������� ��������������� ����
		switch(i){//������� ������ �������� � �������� ������ �� ��������� ��������� ���������; 
			//��������� ��� �����
			case 1: if(!vstavka(t,infa)) puts("������ ����������");break;
			//��������� ������ �����, ������� � ����������
			case 2: if(strcmp(infa.sostojanie, sost_1) == 0) {if(!vstavka(t,infa)) puts("������ ����������");}break; 
			//��������� ������ �����, ������� � �������������
			case 3: if(strcmp(infa.sostojanie, sost_2) == 0) {if(!vstavka(t,infa)) puts("������ ����������");}break;
		}
		
	}
	BST_make(t);//�������������� ����������� ��������� ������ � �������� ������ ������(���)
	if(i!=1) Redakt(t->koren,1);//���� ��� ����� �� ���������� ��� �� ������� � ������������� �� ��������� ����� � �� ���� �������������
	}
	return t;
  }
  
  //�������� ��������� ������ ������ �� ��������� ������ � ������� �������� 
  HEAD *tree_make_1(INFA *I,int m){//I - ��������� �� ������ ������� ������� m - ����������� �������
	HEAD *t;
	t = sozd();//��������� ������ ��������� ������
	int i;
	for(i = 0; i<m; i++){
		if(!vstavka(t,*I)) puts("������ ����������");
		I++;
	}
	BST_make(t);//�������������� ����������� ��������� ������ � �������� ������ ������(���)
	return t;
  }
  
  //����� �� ����� ��������� ������
 void print(TREE *search_n){
	 if(search_n == NULL) return;
	 print(search_n->left);
	 Ch(125);//����� �������
	 //������������� �����
	 DeEdit(search_n->inf.avtor);DeEdit(search_n->inf.nazv);DeEdit(search_n->inf.sostojanie);
	 printf(" | %5d | %30s | %40s | %4d | %10d | %15s | ", search_n->inf.n,search_n->inf.avtor,search_n->inf.nazv,search_n->inf.god,search_n->inf.kol,search_n->inf.sostojanie);
	 Ch(125);//����� �������
	 print(search_n->right);
 }
 
 
void Shapka(FILE *f){
	int pos;
	for(pos = 1; pos<126; pos++)
		fprintf(f,"-");
	fprintf(f,"\n | %5s | %30s | %40s | %4s | %10s | %15s | \n",S1,S2,S3,S4,S5,S6);
}
 //���������� ����� ������� �������������� ����� ��������� ��������� ������
  void fprint(const TREE *search_n,FILE *F){
	 if(search_n == NULL) return;
	 fprint(search_n->left,F);
	 int pos;
	 for(pos = 1; pos<126; pos++)
			fprintf(F,"-");//����������� � ����� ���������
	 fprintf(F,"\n | %5d | %30s | %40s | %4d | %10d | %15s | \n", search_n->inf.n,search_n->inf.avtor,search_n->inf.nazv,search_n->inf.god,search_n->inf.kol,search_n->inf.sostojanie);
	 for(pos = 1; pos<126; pos++)
			fprintf(F,"-");//����������� � ����� ���������
	 fprintf(F,"\n");
	 fprint(search_n->right,F);
 }
 
 //�������� ��������� ������
 void destroy(TREE *search_n){
	 if(search_n == NULL) return;
	 destroy(search_n->left);
	 free(search_n);
	 destroy(search_n->right);
 }
 
 //�������� ��������� ����� i � �������� ������ t
 HEAD *del(HEAD *t, int i,int k){
		INFA *v,*b,*c;
		int j,m,l=0;
		v = (INFA*)malloc(sizeof(INFA)*(t->kol));//��������� ������ ��� ������� �������������� ����� ��������� ������
		m = t->kol;
		b = v;
		pol(t->koren, b);//���������� ����� �������
		b = v;
		destroy(t->koren);//�������� ������
		free(t);
		for(j = 0; j<m;j++){
			switch(k){
				//���� ��� ���� ������� ����� �� ������ ����, ������� � ����������
				case 1: if(!strcmp((b->sostojanie),sost_1))l++;break;
				//���� ��� ���� ������� ����� �� ������ ������ ����
				case 2: l++; break;
			}
			if(l == i){i = j; break;}//����� ���������� �������� � ����� ������
			b++;
		}
		b = v;
		b = b + i;//������� � ����� ��������
		for(j = i; j<m; j++){//�������� ������� ��������
			if(b == v+m) {free(b);break;}
			*b = *(b+1);
			b->n --;
			b++;
		}
		b = v;
		t = tree_make_1(v,m-1);//�������� ������ �� ��������� ������� ��������
		return t;
	}
	
//������� ��� ���� ����� ����� ����� �� ����������
HEAD *take_1(HEAD *t, int i){
	INFA *v,*b,*c,*a;
	int j,m,l=0;
	v = (INFA*)malloc(sizeof(INFA)*((t->kol)+1));//��������� ������ ��� ������� �������������� ����� ��������� ������
	//�� 1 ������ ��� ��� ���������� ����� ������� � ������ - �� �� ����� �� � ������ ����������
	m = t->kol+1;
	b = v;
	pol(t->koren, b);//���������� ����� �������
	b = v;
	destroy(t->koren);//�������� ������
	for(j = 0; j<m;j++){
		if(!strcmp((b->sostojanie),sost_1))l++;//����� �� ����� ����� ������ �� ����������
		if(l == i){i = j; break;}//������� ������ ����� � ����� ������
		b++;
	}
	b = v;
	b = b + i;
	b->kol --;//���-�� ���� � ���������� ����������� �� ����
	
	for(j = 0,c = v; j<m;j++,c++){/*���� ��� ���-�� ���� ����� �� �����, �� ����� ������� �� �����
		����� ������ ��������� ���-�� ���� ����� �������� �� 1
		*/
		if (j == m-1) break;
		if(!strcmp((c->sostojanie),sost_1)) continue;
		if((!strcmp((c->avtor),(b->avtor)))&&(!strcmp((c->nazv),(b->nazv)))&&((c->god) == (b->god))) {l = -1;break;}
	}
	if(l == -1){
		c->kol++;//�����������
		t = tree_make_1(v,m-1);//�������� ������ �� ��������� ������� ��������
	}
	else{//���� ��� ����� ������� �������
		*(v+m-1) = *b;//� ����� ��������� ����� �������
		(v+m-1)->kol = 1;//��� ���-�� ����� 1
		(v+m-1)->n = m;
		strcpy((v+m-1)->sostojanie,sost_2);//��������� � ������������
		t = tree_make_1(v,m);//�������� ������ �� ��������� ������� ��������
	}
	if(b->kol == 0) t = del(t,i+1,2);//���� �� ������� ��������� �����, �� ���� �� ������� � ����� ������
	return t;
}

//������� ��� ���� ����� ������� ����� � ����������
//�� ������ ���������� ���������� �������, ������ ��������� ��������
HEAD *give_it_back(HEAD *t, int i){
	INFA *v,*b,*c,*a;
	int j,m,l=0;
	v = (INFA*)malloc(sizeof(INFA)*((t->kol)+1));
	m = t->kol+1;
	b = v;
	pol(t->koren, b);
	b = v;
	destroy(t->koren);
	for(j = 0; j<m;j++){
		if(!strcmp((b->sostojanie),sost_2))l++;
		if(l == i){i = j; break;}
		b++;
	}
	b = v;
	b = b + i;
	b->kol --;
	
	for(j = 0,c = v; j<m;j++,c++){
		if (j == m-1) break;
		if(!strcmp((c->sostojanie),sost_2)) continue;
		if((!strcmp((c->avtor),(b->avtor)))&&(!strcmp((c->nazv),(b->nazv)))&&((c->god) == (b->god))) {l = -1;break;}
	}
	if(l == -1){
		c->kol++;
		t = tree_make_1(v,m-1);
	}
	else{
		*(v+m-1) = *b;
		(v+m-1)->kol = 1;
		(v+m-1)->n = m;
		strcpy((v+m-1)->sostojanie,sost_1);
		t = tree_make_1(v,m);
	}
	if(b->kol == 0) t = del(t,i+1,2);
	return t;
}

//������� ��� ���������� ������
HEAD *Sort_BT(HEAD *t,int p_r){
	INFA *v,*b,c;
	int i,j;
	v = (INFA*)malloc(sizeof(INFA)*(t->kol));//��������� ������ ��� ������� �������������� ����� ��������� ������
	b = v;
	pol(t->koren, b);//���������� ����� �������
	b=v;
	for(i=0;i<(t->kol);i++){
		b = v;
		for(j = 0; j<(t->kol)-1;j++){
			switch(p_r){
				//��������� �� ������
				case 1:{
					char  l[20],m[20];
					strcpy(m,(b+1)->avtor);
					strcpy(l,b->avtor);
					if(strcmp(l,m)>0){
						c = *b;
						*b = *(b+1);
						*(b+1) = c;
					}
				}break;
				//��������� �� �������� �����
				case 2:{
					char l[20],m[20];
					strcpy(m,(b+1)->nazv);
					strcpy(l,b->nazv);
					if(strcmp(l,m)>0){
						c = *b;
						*b = *(b+1);
						*(b+1) = c;
					}
				}break;
				//��������� �� ����
				case 3:{
					int l,m;
					m = (b+1)->god;
					l = b->god;
					if(l>m){
						c = *b;
						*b = *(b+1);
						*(b+1) = c;
					}
				}break;
				//��������� �� ����������
				case 4:{
					int l,m;
					m = (b+1)->kol;
					l = b->kol;
					if(l>m){
						c = *b;
						*b = *(b+1);
						*(b+1) = c;
					}
				}break;
				//��������� �� ������
				case 5:{
					int l,m;
					m = (b+1)->n;
					l = b->n;
					if(l>m){
						c = *b;
						*b = *(b+1);
						*(b+1) = c;
					}
				}break;
			}
			b++;
		}
	}
	b=v;
	o_pol(t->koren, b);//���������� �������������� ����� ���������������� ��� ������
	free(v);//������������ ����� �������
	return t;
}

//����� �� ����� ��������� ������, ������� ������ ����� ��������� ����
void Poisk_BT_1(TREE *h,int god){
	 if(h == NULL) return;
	 Poisk_BT_1(h->left, god);
	 if(h->inf.god > god) {//���� ������ ��������� ���� �� �������
		Ch(125);
		DeEdit(h->inf.avtor);DeEdit(h->inf.nazv);DeEdit(h->inf.sostojanie);
		printf(" | %5d | %30s | %40s | %4d | %10d | %15s | ", h->inf.n,h->inf.avtor,h->inf.nazv,h->inf.god,h->inf.kol,h->inf.sostojanie);
		Ch(125);
	 }
	 Poisk_BT_1(h->right, god);
 }
 
//�������� ��������� ������  �� ��������� ������ � �����
HEAD *Poisk_BT_2(int god,FILE *F){
	 HEAD *t;
	 char s[130];
	t = sozd();//��������� ������ ����������� ������
	INFA infa;
	fseek(F,0,SEEK_END);//�������� ��������� � ����� � �����
	long pos=ftell(F);//����������� ������ �������� ����� � �����
	if(pos>0){/*���� ������� ���� ������ �� pos = 0, ���� ���� ������ �� ����� �������� �������� � ����� ������ �� ���������,
	� ������ ����� ����� = ������. ���� ���� �� ������ �� pos ����� > 0*/
		rewind(F);//����������� ��������� � ������ �����
		fgets(s,131,F);//���������� ����� ������ ������ � �����
		fgets(s,131,F);//���������� ������ ������ � �����
	  while(!feof(F)){//���� �� ��������� ����� �����
		fscanf(F,"-----------------------------------------------------------------------------------------------------------------------------\n\
		| %d | %s | %s | %d | %d | %s | \n\
		-----------------------------------------------------------------------------------------------------------------------------\n"\
		, &infa.n,&infa.avtor,&infa.nazv,&infa.god,&infa.kol,&infa.sostojanie);
		//���� ����� ������ ����� ��� �������� ���, �� ��� ����������� � ������
		if(infa.god>god) if(!vstavka(t,infa)) {puts("������ ����������");break;}
	  }
	 Redakt(t->koren,1);//����������� ���������
	}
	return t;
}

 //���������� �������������� ������� �� ��������� ������� �������������� ����� ��������� ��������� ������
int *i_pol(TREE *search_n, int *v){
	 if(search_n == NULL) return v;
	 v = i_pol(search_n->left,v);
	 *v = search_n->inf.n; v++;
	 v = i_pol(search_n->right,v);
 }
 
 //������� ������ ����� �� ��������� ��������� p_r
HEAD *Poisk_BT(HEAD *t,int p_r){
	INFA *v,*b;
	int i,j;
	v = (INFA*)malloc(sizeof(INFA)*(t->kol));//��������� ������ ��� ������� �������������� ����� ��������� ������
	b = v;
	pol(t->koren, b);//���������� ����� �������
	b=v;
	switch(p_r){
		//����� �� ������
		case 1:{
			INFA *c,*m;
			int k=0;
			char  l[20];
			printf(" ~ ������� ������\n");
			strcpy(l,Correct(4).s_1);
			for(;;){//��������� ������� ���� � ����� ������
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->avtor)) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//�������� ������������� ������
			m = c;
			for(;;){//��������� ������� ����� ������
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->avtor)) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//������� �� ��������� ������� ������
			free(c);
		}break;
		//����� �� �������� �����
		case 2:{
			INFA *c,*m;
			int k=0;
			char  l[20];
			printf(" ~ ������� �������� �����\n");
			strcpy(l,Correct(9).s_1);
			for(;;){//��������� ������� ����� ���� ����
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->nazv)) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//�������� ������������� ������
			m = c;
			for(;;){//��������� ����� �������
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->nazv)) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//������� �� ��������� ������� ������
			free(c);
		}break;
		//����� �� ����
		case 3:{
			INFA *c,*m;
			int k=0;
			int  l;
			printf(" ~ ������� ��� �������\n");
			l = Cifra(Correct(5).s_1);
			for(;;){//��������� ������� ����� ���� ����
				if(b == v+t->kol+1) break;
				if(l == b->god) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//�������� ������������� ������
			m = c;
			for(;;){//��������� ����� �������
				if(b == v+t->kol+1) break;
				if(l == b->god) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//������� �� ��������� ������� ������
			free(c);
		}break;
		//����� �� ����������
		case 4:{
			INFA *c,*m;
			int k=0;
			int  l;
			printf(" ~ ������� ���������� ����\n");
			l = Cifra(Correct(5).s_1);
			for(;;){//��������� ������� ����� ���� ����
				if(b == v+t->kol+1) break;
				if(l == b->kol) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//�������� ������������� ������
			m = c;
			for(;;){//��������� ����� �������
				if(b == v+t->kol+1) break;
				if(l == b->kol) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//������� �� ��������� ������� ������
			free(c);
		}break;
		//����� �� ������
		case 5:{
			int *ch = (int*)malloc(sizeof(int)*t->kol);
			int *p = ch;
			i_pol(t->koren,p);//��������� ������ �������� ����� ������
			TREE *h = t->koren;
			int  l;
			int i,k;
			v = (INFA*)malloc(sizeof(INFA));//����� � ������������ ������� - ����� ����
			puts(" ~ ������� ����� �����, ������� ������ ����� ");
			for(;;){//����� ����� ������ ������ ����� ��� ����� ������� ����
				l = Cifra(Correct(5).s_1);
				for(i=0,p = ch;i<(t->kol);i++,p++){
					if(*p == l){k=1;break;}
				}
				if(k == 1) break;
			}
			for(;;){//�������� �� ��� � ������� ������� �������� 
				if(h == NULL) break;
				else if(l == h->inf.n) {*v = (h->inf);break;}
				else if(l>h->inf.n) {
				h  = h->right;
				}
				else h = h->left;
			}
			destroy(t->koren);
			t = tree_make_1(v,1);
		}break;
	}
	free(v);//������������ ����� �������
	return t;
}