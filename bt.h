#include "Po_Seredinke.h"
const char sost_1[] = "В_библиотеке";
const char sost_2[] = "У_пользователя";
//Структура информационного поля элемента бинарного дерева
typedef struct info{
	int n;
	char avtor[30];
	char nazv[40];
	int god;
	int kol;
	char sostojanie[15];
}INFA;
//объявление нового типа данных INFA, который является struct info - чтобы в дальнейшем не иметь дела с длинным именем

//Структура элемента бинарного дерева
typedef struct tree{
	INFA inf;//Информационной поле
	struct tree *right;//Указатель на правое поддерево
	struct tree *left;//Указатель на левое поддерево
	struct tree *predok;//Указатель на родителя
}TREE;

//Структура головы дерева
typedef struct head{
	TREE *koren;//корень(голова) дерева
	int kol;//количество элементов в дереве
}HEAD;

//определяет количество элементов в переденном ей поддереве(дереве)
/*рекурсия, в данном случае движение в самый левый лист дерева
после его достижения, функция вернется к предку, потом пойдет в правое дерево, после подсчета всех элементов там
пойдет вверх к предку, и так пока не окажется в самом правом листе дерева
*/
 int usel(const TREE *search_n){
	 int u =0;
	 if(search_n == NULL) return u;
	 u+=usel(search_n->left);
	 u++;
	 u+=usel(search_n->right);
	 return u;
 }
 
 //создание бинарного дерева
 HEAD *sozd(void){
	 HEAD *new_tree = (HEAD*)malloc(sizeof(HEAD));//выделение памяти для головы дерева
	 if(new_tree == NULL) return NULL;//если память не выделилась
	 new_tree->koren = NULL;//создание указателя на корень 
	 new_tree->kol = 0;//изначально в дереве нуль элементов
	 return new_tree;//возвращения указателя на голову
 }
 
 //получение адреса в бинарном дереве для нового элемента
 TREE **vstav(TREE **search_tree){//передается адрес поддерева(корня дерева)
	 TREE **v = search_tree;
			 for(;;){//движение по дереву в поиске места для добаления нового элемента
				 if(*v == NULL) return v;//достижение пустого указателя, возвращаем его адрес
				 if(usel((*v)->right)>usel((*v)->left)){/*элементы в дереве должны распологаться равномерно,
				 поэтому сравнивается количество элементов в правом и левом поддереве, 
				 где меньше - туда и переходим и так пока не достигнут пустой(нулевой) указатель,
				 куда можно добавить новый элемент
				 */
					 v = &((*v)->left);
				 }
				 else{
					 v = &((*v)->right);
				 }
			 }
 }
 
 //получение адреса предка для вставляемого элемента
 TREE **vstav_pr(TREE **search_tree){
	 /*работа этой функции аналогична функции поиска адреса для вставляемого элемента, только при движении по дереву,
	 запоминается еще родитель при каждом переходе к детям, когда найден путой указатель то возвращается его родитель
	 */
	 TREE **pr = search_tree;
	 TREE **t = search_tree;
	 if(t == NULL) return NULL;/*случай когда дерево только созданно и в нем нет элементов,
	 тогда вставляемый элемент будет корнем, а у корня нет родителей
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
 
 //встака нового элемента в бинарное дерево
int vstavka(HEAD *search_tree, INFA i){//для вставки нужен указатель на голову дерева и информационное поле вставляемого элемента 
	 TREE *n;
	 TREE **v = vstav(&(search_tree->koren));//получаем адрес куда вставить элемент
	 TREE **pr = vstav_pr(&(search_tree->koren));//получаем адрес его предка
	 n = *v = (TREE *)malloc(sizeof(TREE));/*выделение памяти для вставляемого элемента, причем
	 указатель на выделяюмую память будет жестко связан с бинарным деревом*/
	 if(n == NULL) return 0;//если памяти нет, то функция вернет нуль
	 //инициализируем новый элемент
	 n->right = NULL;//правый лист пустой
	 n->left = NULL;//левый тоже
	 n->inf = i;//в информационное поле заносим, то что было передано в функцию изначально
	 n->predok = *pr;//записываем указатель на родителя
	 search_tree->kol++;//увеличиваем количество элементов бинарного дерева
	 return 1;//функция вернет 1 если элемент добавлен и инициализирован
 }
 
 //заполнение массива на основании информационных полей элементов бинарного дерева
 INFA *pol(TREE *search_n, INFA *v){
	 if(search_n == NULL) return v;
	 v = pol(search_n->left,v);
	 *v = search_n->inf; v++;
	 v = pol(search_n->right,v);
 }
 
 //заполнение информационных полей элементов бинарного дерева на основании элементов массива
 INFA *o_pol(TREE *search_n, INFA *v){
	 if(search_n == NULL) return v;
	 v = o_pol(search_n->left,v);
	 search_n->inf = *v; v++;
	 v = o_pol(search_n->right,v);
 }
 
 //преобразование бинарного дерева в бинарное дерева поиска(БДП)
 void BST_make(HEAD *search_tree){
	INFA *v,*b,c;
	int i,j,m,l;
	v = (INFA*)malloc(sizeof(INFA)*(search_tree->kol));//выделение памяти для массива информационных полей бинарного дерева
	b = v;
	pol(search_tree->koren, b);//заполнение этого массива
	b=v;
	for(i=0;i<(search_tree->kol);i++){//сортировка по номеру
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
	o_pol(search_tree->koren, b);//заполнение информационных полей отсортированными инф полями
	free(v);//освобождение этого массива
 }
 
 //редактирование нумерации в случае если она сбилась
 int Redakt(TREE *t,int i){
	 if(t == NULL) return i;
	 i=Redakt(t->left,i);
	 t->inf.n = i; i++;
	 i=Redakt(t->right,i);
 }
 
 //Создание бинарного дерева поиска на основании данных в файле
HEAD *tree_make(FILE *F, int i){
	HEAD *t;
	char s[130];
	t = sozd();//создается голова бинарного дерева
	INFA infa;
	fseek(F,0,SEEK_END);//смещение указателя в файле в конец
	long pos=ftell(F);//определение номера текущего байта в файле
	if(pos>0){/*если текущий байт первый то pos = 0, если файл пустой то после смещения укзателя в конец ничего не изменится,
	в пустом файле конец = началу. Если файл не пустой то pos будет > 0*/
		rewind(F);//возвращение указателя в начало файла
		fgets(s,131,F);//пропускаем самую первую строку в файле
		fgets(s,131,F);//пропускаем вторую строку в файле
	  while(!feof(F)){//пока не достигнут конец файла
		fscanf(F,"-----------------------------------------------------------------------------------------------------------------------------\n\
		| %d | %s | %s | %d | %d | %s | \n\
		-----------------------------------------------------------------------------------------------------------------------------\n"\
		, &infa.n,&infa.avtor,&infa.nazv,&infa.god,&infa.kol,&infa.sostojanie);//считывание данных из файла в структуру информационного поля
		switch(i){//вставка нового элемента в бинарное дерево на основании считанной структуры; 
			//считываем все книги
			case 1: if(!vstavka(t,infa)) puts("Ошибка добавления");break;
			//считываем только книги, которые в библиотеке
			case 2: if(strcmp(infa.sostojanie, sost_1) == 0) {if(!vstavka(t,infa)) puts("Ошибка добавления");}break; 
			//считываем только книги, которые у пользователей
			case 3: if(strcmp(infa.sostojanie, sost_2) == 0) {if(!vstavka(t,infa)) puts("Ошибка добавления");}break;
		}
		
	}
	BST_make(t);//преобразование полученного бинарного дерева в бинарное дерево поиска(БДП)
	if(i!=1) Redakt(t->koren,1);//если это книги из библиотеке или те которые у пользователей то нумерация сбита и ее надо нормализовать
	}
	return t;
  }
  
  //Создание бинарного дерева поиска на основании данных в массиве структур 
  HEAD *tree_make_1(INFA *I,int m){//I - указатель на первый элемент массива m - размерность массива
	HEAD *t;
	t = sozd();//создается голова бинарного дерева
	int i;
	for(i = 0; i<m; i++){
		if(!vstavka(t,*I)) puts("Ошибка добавления");
		I++;
	}
	BST_make(t);//преобразование полученного бинарного дерева в бинарное дерево поиска(БДП)
	return t;
  }
  
  //вывод на экран бинарного дерева
 void print(TREE *search_n){
	 if(search_n == NULL) return;
	 print(search_n->left);
	 Ch(125);//вывод штрихов
	 //декодирование строк
	 DeEdit(search_n->inf.avtor);DeEdit(search_n->inf.nazv);DeEdit(search_n->inf.sostojanie);
	 printf(" | %5d | %30s | %40s | %4d | %10d | %15s | ", search_n->inf.n,search_n->inf.avtor,search_n->inf.nazv,search_n->inf.god,search_n->inf.kol,search_n->inf.sostojanie);
	 Ch(125);//вывод штрихов
	 print(search_n->right);
 }
 
 
void Shapka(FILE *f){
	int pos;
	for(pos = 1; pos<126; pos++)
		fprintf(f,"-");
	fprintf(f,"\n | %5s | %30s | %40s | %4s | %10s | %15s | \n",S1,S2,S3,S4,S5,S6);
}
 //заполнение файла данными информационных полей элементов бинарного дерева
  void fprint(const TREE *search_n,FILE *F){
	 if(search_n == NULL) return;
	 fprint(search_n->left,F);
	 int pos;
	 for(pos = 1; pos<126; pos++)
			fprintf(F,"-");//прописываем в файле штриховку
	 fprintf(F,"\n | %5d | %30s | %40s | %4d | %10d | %15s | \n", search_n->inf.n,search_n->inf.avtor,search_n->inf.nazv,search_n->inf.god,search_n->inf.kol,search_n->inf.sostojanie);
	 for(pos = 1; pos<126; pos++)
			fprintf(F,"-");//прописываем в файле штриховку
	 fprintf(F,"\n");
	 fprint(search_n->right,F);
 }
 
 //удаление бинарного дерева
 void destroy(TREE *search_n){
	 if(search_n == NULL) return;
	 destroy(search_n->left);
	 free(search_n);
	 destroy(search_n->right);
 }
 
 //удаление заданного элеме i в бинарном дереве t
 HEAD *del(HEAD *t, int i,int k){
		INFA *v,*b,*c;
		int j,m,l=0;
		v = (INFA*)malloc(sizeof(INFA)*(t->kol));//выделение памяти для массива информационных полей бинарного дерева
		m = t->kol;
		b = v;
		pol(t->koren, b);//заполнение этого массива
		b = v;
		destroy(t->koren);//удаление дерева
		free(t);
		for(j = 0; j<m;j++){
			switch(k){
				//если нам надо удалять книги из списка книг, которые в библиотеке
				case 1: if(!strcmp((b->sostojanie),sost_1))l++;break;
				//если нам надо удалять книги из общего списка книг
				case 2: l++; break;
			}
			if(l == i){i = j; break;}//номер найденного элемента в общем списке
			b++;
		}
		b = v;
		b = b + i;//переход к этому элементу
		for(j = i; j<m; j++){//удаление нужного элемента
			if(b == v+m) {free(b);break;}
			*b = *(b+1);
			b->n --;
			b++;
		}
		b = v;
		t = tree_make_1(v,m-1);//создание дерева на основании массива структур
		return t;
	}
	
//функция для того чтобы взять книгу из библиотеки
HEAD *take_1(HEAD *t, int i){
	INFA *v,*b,*c,*a;
	int j,m,l=0;
	v = (INFA*)malloc(sizeof(INFA)*((t->kol)+1));//выделение памяти для массива информационных полей бинарного дерева
	//на 1 больше так как появляется новый элемент в списке - та же книга но с другим состоянием
	m = t->kol+1;
	b = v;
	pol(t->koren, b);//заполнение этого массива
	b = v;
	destroy(t->koren);//удаление дерева
	for(j = 0; j<m;j++){
		if(!strcmp((b->sostojanie),sost_1))l++;//взять мы можем книги только из библиотеки
		if(l == i){i = j; break;}//находим нужную книгу в общем списке
		b++;
	}
	b = v;
	b = b + i;
	b->kol --;//кол-во книг в библиотеке уменьшается на одну
	
	for(j = 0,c = v; j<m;j++,c++){/*если уже кто-то брал такую же книгу, то новый элемент не нужен
		нужно просто увеличить кол-во книг этого элемента на 1
		*/
		if (j == m-1) break;
		if(!strcmp((c->sostojanie),sost_1)) continue;
		if((!strcmp((c->avtor),(b->avtor)))&&(!strcmp((c->nazv),(b->nazv)))&&((c->god) == (b->god))) {l = -1;break;}
	}
	if(l == -1){
		c->kol++;//увеличиваем
		t = tree_make_1(v,m-1);//создание дерева на основании массива структур
	}
	else{//если эта книга берется впервые
		*(v+m-1) = *b;//в конец добавляем новый элемент
		(v+m-1)->kol = 1;//его кол-во будет 1
		(v+m-1)->n = m;
		strcpy((v+m-1)->sostojanie,sost_2);//состояние у пользователя
		t = tree_make_1(v,m);//создание дерева на основании массива структур
	}
	if(b->kol == 0) t = del(t,i+1,2);//если мы забрали последнюю книгу, то надо ее удалить в общем списке
	return t;
}

//функция для того чтобы вернуть книгу в библиотеку
//ее работа аналогично предыдущей функции, только состояния меняются
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

//функция для сортировки дерева
HEAD *Sort_BT(HEAD *t,int p_r){
	INFA *v,*b,c;
	int i,j;
	v = (INFA*)malloc(sizeof(INFA)*(t->kol));//выделение памяти для массива информационных полей бинарного дерева
	b = v;
	pol(t->koren, b);//заполнение этого массива
	b=v;
	for(i=0;i<(t->kol);i++){
		b = v;
		for(j = 0; j<(t->kol)-1;j++){
			switch(p_r){
				//сортируем по автору
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
				//сортируем по названию книги
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
				//сортируем по году
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
				//сортируем по количеству
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
				//сортируем по номеру
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
	o_pol(t->koren, b);//заполнение информационных полей отсортированными инф полями
	free(v);//освобождение этого массива
	return t;
}

//вывод на экран элементов списка, которые изданы позже заданного года
void Poisk_BT_1(TREE *h,int god){
	 if(h == NULL) return;
	 Poisk_BT_1(h->left, god);
	 if(h->inf.god > god) {//если больша заданного года то вывести
		Ch(125);
		DeEdit(h->inf.avtor);DeEdit(h->inf.nazv);DeEdit(h->inf.sostojanie);
		printf(" | %5d | %30s | %40s | %4d | %10d | %15s | ", h->inf.n,h->inf.avtor,h->inf.nazv,h->inf.god,h->inf.kol,h->inf.sostojanie);
		Ch(125);
	 }
	 Poisk_BT_1(h->right, god);
 }
 
//Создание бинарного дерева  на основании данных в файле
HEAD *Poisk_BT_2(int god,FILE *F){
	 HEAD *t;
	 char s[130];
	t = sozd();//создается голова двусвязного списка
	INFA infa;
	fseek(F,0,SEEK_END);//смещение указателя в файле в конец
	long pos=ftell(F);//определение номера текущего байта в файле
	if(pos>0){/*если текущий байт первый то pos = 0, если файл пустой то после смещения укзателя в конец ничего не изменится,
	в пустом файле конец = началу. Если файл не пустой то pos будет > 0*/
		rewind(F);//возвращение указателя в начало файла
		fgets(s,131,F);//пропускаем самую первую строку в файле
		fgets(s,131,F);//пропускаем вторую строку в файле
	  while(!feof(F)){//пока не достигнут конец файла
		fscanf(F,"-----------------------------------------------------------------------------------------------------------------------------\n\
		| %d | %s | %s | %d | %d | %s | \n\
		-----------------------------------------------------------------------------------------------------------------------------\n"\
		, &infa.n,&infa.avtor,&infa.nazv,&infa.god,&infa.kol,&infa.sostojanie);
		//если книга издана позже чем заданный год, то она добавляется в список
		if(infa.god>god) if(!vstavka(t,infa)) {puts("Ошибка добавления");break;}
	  }
	 Redakt(t->koren,1);//редактируем нумерацию
	}
	return t;
}

 //заполнение целочисленного массива на основании номеров информационных полей элементов бинарного дерева
int *i_pol(TREE *search_n, int *v){
	 if(search_n == NULL) return v;
	 v = i_pol(search_n->left,v);
	 *v = search_n->inf.n; v++;
	 v = i_pol(search_n->right,v);
 }
 
 //функция поиска книги по заданному параметру p_r
HEAD *Poisk_BT(HEAD *t,int p_r){
	INFA *v,*b;
	int i,j;
	v = (INFA*)malloc(sizeof(INFA)*(t->kol));//выделение памяти для массива информационных полей бинарного дерева
	b = v;
	pol(t->koren, b);//заполнение этого массива
	b=v;
	switch(p_r){
		//поиск по автору
		case 1:{
			INFA *c,*m;
			int k=0;
			char  l[20];
			printf(" ~ Введите автора\n");
			strcpy(l,Correct(4).s_1);
			for(;;){//считается сколько книг у этого автора
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->avtor)) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//выделяем соотвественно массив
			m = c;
			for(;;){//заполняем книгами этого автора
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->avtor)) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//создаем на основании массива дерево
			free(c);
		}break;
		//поиск по названию книги
		case 2:{
			INFA *c,*m;
			int k=0;
			char  l[20];
			printf(" ~ Введите название книги\n");
			strcpy(l,Correct(9).s_1);
			for(;;){//считается сколько таких книг есть
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->nazv)) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//выделяем соотвественно массив
			m = c;
			for(;;){//заполняем этими книгами
				if(b == v+t->kol+1) break;
				if(!strcmp(l,b->nazv)) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//создаем на основании массива дерево
			free(c);
		}break;
		//поиск по году
		case 3:{
			INFA *c,*m;
			int k=0;
			int  l;
			printf(" ~ Введите год издания\n");
			l = Cifra(Correct(5).s_1);
			for(;;){//считается сколько таких книг есть
				if(b == v+t->kol+1) break;
				if(l == b->god) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//выделяем соотвественно массив
			m = c;
			for(;;){//заполняем этими книгами
				if(b == v+t->kol+1) break;
				if(l == b->god) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//создаем на основании массива дерево
			free(c);
		}break;
		//поиск по количеству
		case 4:{
			INFA *c,*m;
			int k=0;
			int  l;
			printf(" ~ Введите количество книг\n");
			l = Cifra(Correct(5).s_1);
			for(;;){//считается сколько таких книг есть
				if(b == v+t->kol+1) break;
				if(l == b->kol) k++;
				b++;
			}
			b=v;
			c = (INFA*)malloc(sizeof(INFA)*k);//выделяем соотвественно массив
			m = c;
			for(;;){//заполняем этими книгами
				if(b == v+t->kol+1) break;
				if(l == b->kol) {*c = *b;c++;}
				b++;
			}
			c = m;
			destroy(t->koren);
			t = tree_make_1(c,k);//создаем на основании массива дерево
			free(c);
		}break;
		//поиск по номеру
		case 5:{
			int *ch = (int*)malloc(sizeof(int)*t->kol);
			int *p = ch;
			i_pol(t->koren,p);//заполянем массив номерами полей дерева
			TREE *h = t->koren;
			int  l;
			int i,k;
			v = (INFA*)malloc(sizeof(INFA));//книга с определенным номером - всего одна
			puts(" ~ Введите номер книги, которую хотите найти ");
			for(;;){//можно будет ввести только номер той книги которая есть
				l = Cifra(Correct(5).s_1);
				for(i=0,p = ch;i<(t->kol);i++,p++){
					if(*p == l){k=1;break;}
				}
				if(k == 1) break;
			}
			for(;;){//движение по БДП в поисках нужного элемента 
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
	free(v);//освобождение этого массива
	return t;
}