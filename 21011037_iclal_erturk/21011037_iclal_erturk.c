#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct{
	char name[20];
	char surname[20];
	char userName[20];
	char password[20];
	double scor;
}USER;
void createAccount(char [],char []);
void signin(char [],char []);
void mainMenu(char [],char [],int*);
void readBoardFromFile(char **, char *);
void drawBoard(char**, int, int);
void giveInfo();
void moveRight(char **,int ,int *,int ,int *,int *,int *, int *,char *,int *,char **,int *,int *);//manuel
void moveLeft(char **,int ,int *,int,int *,int *,int *, int *,char *,int *,char **,int *,int *);//manuel
void moveDown(char **,int *,int ,int ,int *,int *,int *, int *,char *,int *,char **,int *, int *);//manuel
void moveUp(char **,int *,int ,int ,int *,int *,int *, int *,char *,int *,char **,int *,int *);//manuel
void moveRight2(char **,int ,int *,int ,int *,int *,int *, int *,char *,int *,char **,int *,int *);//auto
void moveLeft2(char **,int ,int *,int ,int *,int *,int *, int *,char *,int *,char **,int *,int *);//auto
void moveDown2(char **,int *,int ,int ,int *,int *,int *, int *,char *,int *,char **,int *,int *);//auto
void moveUp2(char **,int *,int ,int ,int *,int *,int *, int *,char *,int *,char **,int *,int *);//auto
void printCollected(char **,int );
char** allocMatrix(int , int );
void matrixFree(char **,int );
void play(char **, char *,int ,int,char **,int *,double*);//manuel 
void requestFromUser(int *, int *, char *);
void useExistBoard(char **,char *,int *, int *);
void otoPlay(char **, char *,int ,int,char **,int *,double *);//auto
void swap(double *, double *, int );
void sort(double **, int ,char *);

void menu(char[],char[]);

int main(){

	srand(time(NULL));
	char userName[20];
	int flag=1;
	
	while(flag){//oyuncu cikis yapana kadar devam etsin
		printf("\nWELCOME TO THE ANTIMATTER MAZE GAME\n");
		mainMenu("kullanicilar.bin",userName,&flag);
		if(flag){
			menu(userName,"kullanicilar.bin");	
		}
		
	}	 
	
	return 0;
}

void createAccount(char fileName[], char userName[]){
	USER user;
	USER userFromFile;
	FILE *fs = fopen(fileName,"rb+");
	if (fs == NULL) {
	    printf("File could not be opened!\n");
	} 
	else {
		printf("\nName: ");
		scanf(" %s", user.name);
		printf("SurName: ");
		scanf(" %s",user.surname);
		int dd=1,found=0;
		int i=0;
		while(dd){
			int dd2=1;
			found=0;
			printf("userName: ");
			scanf(" %s",user.userName);
			fseek(fs,0,SEEK_SET);
			while(fread(&userFromFile, sizeof(USER), 1, fs) == 1 && dd2){
				if(strcmp(userFromFile.userName,user.userName)==0){
					printf("You can not take this username.\n");				
					dd=1;
					found=1;
					dd2=0;
				}
				else{
					dd2=1;
				}			
			}
			if(found==0){
				dd=0;
			}	
									
		}
		strcpy(userName,user.userName);
		printf("password: ");
		scanf(" %s", user.password);
		user.scor=0;
		fseek(fs, 0, SEEK_END);
		fwrite(&user,sizeof(USER),1,fs);
		fclose(fs);
		printf("\nKaydiniz tamamlanmistir.");
		sleep(1); system("cls");    
	}
	
}
void signin(char fileName[], char userName[]){
	int i=0,dd=1;
	USER user;
	USER userFromFile;
	FILE *fs = fopen(fileName,"rb");
	if (fs == NULL) {
	    printf("File could not be opened!\n");
	} 
	else {
		while(dd){
			int dd2=1,dd3=1;
			printf("\nuserName: ");
			scanf(" %s",user.userName);	
			fseek(fs,0,SEEK_SET);
			while(fread(&userFromFile, sizeof(USER), 1, fs) == 1 && dd2){
				if(strcmp(userFromFile.userName,user.userName)==0){
					while(dd3){
						printf("password: ");
						scanf(" %s", &user.password);
						if(strcmp(userFromFile.password,user.password)==0){
							printf("\nSign in succesful.\n");
							sleep(1);system("cls");
							strcpy(userName,userFromFile.userName);
							dd3=0;
							dd2=0;
							dd=0;
							
						}
						else{
							printf("\nWrong password!!\n");
							dd3=1;
							dd=1;
						}						
					}								
				}						
			}			
		} 
		fclose(fs); 
	}	
}
void mainMenu(char fileName[],char userName[],int *flag){
	int choice;
	printf("\n1-Sign in\n2-Sign up\n3-Exit the game\n");
	int dd=1;
	while (dd){
		printf("Choice: ");
		scanf("%d",&choice);
		sleep(1); system("cls");
		if(choice==1){
			signin(fileName,userName);
			dd=0;
		}	
		else if(choice==2){
			createAccount(fileName,userName);
			dd=0;
		}
		else if(choice==3){
			printf("\nGame exited..");
			*flag=0;
			dd=0;
		}
		else{
			printf("\nWrong choice!!\n");
			dd=1;
		}
		printf("\n");
	}
}
void readBoardFromFile(char **matrix, char *fileName){
	int i,j;
	char temp;
	FILE *data = fopen(fileName,"r");
	if(!data){
        printf("File could not be opened!");
        printf("File name: %s\n", fileName);
		return;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %c\n",&i,&j,&temp);  
		matrix[i][j]=temp;  
    }     
  	fclose(data); 
}
void drawBoard(char** matrix, int row, int column){
    int i,j,k;
    printf("\n     ");
    for(i=0;i<row;i++){
        printf("\n");        
        for (k=0;k<column;k++)
            printf("-------");
        printf("\n");
        printf("|  %c   |",matrix[i][0]);
        for(j=1;j<column;j++)
            
            printf("  %c   |",matrix[i][j]);           
    }
    printf("\n");
 	for (k=0;k<column;k++)
        printf("-------");
}
void giveInfo(){
	printf("\nInformation about symbols\n");
	printf("P+\t  :P\t\te-       :e\t\tP-\t:p\t\te+\t:E\n");
	printf("Black hole:K\t\tUser:X\t\tExit   :C\t\tRoad\t:0\n");
	printf("Wall\t  :1\t\tEnterance    :G\n\n");
}
void moveRight(char **matrix,int x,int *y,int column,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if(matrix[x][*y+1]!='1' && (*y+1)!=column){//matrix sinirlarina ve duvarlara girmeyecek sekilde kullanicinin hareketini saglar ve parcacik varsa toplatir				
		matrix[x][*y]=*temp;
		*y=*y+1;
		if(matrix[x][*y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;			
		}
		else if(matrix[x][*y]=='p'){
			(*p)++;	
			*temp = '0';
			strcpy(collected[*count],"P-");	
			(*count)++;		
		}
		else if(matrix[x][*y]=='E'){
			(*E)++;	
			*temp = '0';
			strcpy(collected[*count],"e+");
			(*count)++;	
		}
		else if(matrix[x][*y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");
			(*count)++;			
		}
		else if(matrix[x][*y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}
			*dd2=0;							
		}
		else if(matrix[x][*y]=='K'){//oyun sonlan�r
			printf("\nGame over..\n");
			*dd2=0;
			
		}
		else if(matrix[x][*y]=='G'){
			*temp = 'G';
		}
		else{
			*temp = '0';
		}		
	}
}
void moveLeft(char **matrix,int x,int *y,int column,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if(matrix[x][*y-1]!='1' && (*y)!=0){///matrix sinirlarina ve duvarlara girmeyecek sekilde kullanicinin hareketini saglar ve parcacik varsa toplatir					
		matrix[x][*y]=*temp;
		*y=*y-1;
		if(matrix[x][*y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;				
		}
		else if(matrix[x][*y]=='p'){
			(*p)++;	
			*temp = '0';
			strcpy(collected[*count],"P-");
			(*count)++;			
		}
		else if(matrix[x][*y]=='E'){
			(*E)++;	
			*temp = '0';	
			strcpy(collected[*count],"e+");
			(*count)++;	
		}
		else if(matrix[x][*y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");
			(*count)++;			
		}
		else if(matrix[x][*y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}
			*dd2=0;							
		}
		else if(matrix[x][*y]=='K'){
			printf("\nGame over..\n");
			*dd2=0;
			
		}
		else if(matrix[x][*y]=='G'){
			*temp = 'G';
		}
		else{
			*temp = '0';
		}		
	}	
}
void moveDown(char **matrix,int *x,int y,int row,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count, int *antiH){
	if((*x+1)!=row && matrix[*x+1][y]!='1'){//matrix sinirlarina ve duvarlara girmeyecek sekilde kullanicinin hareketini saglar ve parcacik varsa toplatir					
		matrix[*x][y]=*temp;
		*x=*x+1;
		if(matrix[*x][y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;				
		}
		else if(matrix[*x][y]=='p'){
			(*p)++;	
			*temp = '0';	
			strcpy(collected[*count],"P-");
			(*count)++;		
		}
		else if(matrix[*x][y]=='E'){
			(*E)++;	
			*temp = '0';
			strcpy(collected[*count],"e+");	
			(*count)++;	
		}
		else if(matrix[*x][y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");;
			(*count)++;			
		}
		else if(matrix[*x][y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}
			*dd2=0;							
		}
		else if(matrix[*x][y]=='K'){
			printf("\nGame over..\n");
			*dd2=0;
			
		}
		else if(matrix[*x][y]=='G'){
			*temp = 'G';
		}	
		else{
			*temp = '0';
		}	
	}
}
void moveUp(char **matrix,int *x,int y,int row,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if((*x)!=0 && matrix[*x-1][y]!='1'){//matrix sinirlarina ve duvarlara girmeyecek sekilde kullanicinin hareketini saglar ve parcacik varsa toplatir						
		matrix[*x][y]=*temp;
		*x=*x-1;		
		if(matrix[*x][y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;			
		}
		else if(matrix[*x][y]=='p'){
			(*p)++;	
			*temp = '0';	
			strcpy(collected[*count],"P-");
			(*count)++;		
		}
		else if(matrix[*x][y]=='E'){
			(*E)++;	
			*temp = '0';
			strcpy(collected[*count],"e+");
			(*count)++;		
		}
		else if(matrix[*x][y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");	
			(*count)++;		
		}
		else if(matrix[*x][y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}			
			*dd2=0;							
		}
		else if(matrix[*x][y]=='K'){//oyun sonlanir
			printf("\nGame over..\n");
			*dd2=0;
			
		}
		else if(matrix[*x][y]=='G'){
			*temp = 'G';
		}
		else{
			*temp = '0';
		}		
	}
}
void moveRight2(char **matrix,int x,int *y,int column,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if(matrix[x][*y+1]!='1' && (*y+1)!=column && matrix[x][*y+1]!='K'){	//matrix sinirlarina duvarlara ve karadeliige girmeyecek sekilde hareket eder ve parcacik varsa toplar					
		matrix[x][*y]=*temp;
		*y=*y+1;
		if(matrix[x][*y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;			
		}
		else if(matrix[x][*y]=='p'){
			(*p)++;	
			*temp = '0';
			strcpy(collected[*count],"P-");	
			(*count)++;		
		}
		else if(matrix[x][*y]=='E'){
			(*E)++;	
			*temp = '0';
			strcpy(collected[*count],"e+");
			(*count)++;	
		}
		else if(matrix[x][*y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");
			(*count)++;			
		}
		else if(matrix[x][*y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}
			*dd2=0;							
		}
		else if(matrix[x][*y]=='G'){
			*temp = 'G';
		}
		else{
			*temp = '0';
		}		
	}
}
void moveLeft2(char **matrix,int x,int *y,int column,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if(matrix[x][*y-1]!='1' && (*y)!=0 && matrix[x][*y-1]!='K'){//matrix sinirlarina duvarlara ve karadeliige girmeyecek sekilde hareket eder ve parcacik varsa toplar							
		matrix[x][*y]=*temp;
		*y=*y-1;
		if(matrix[x][*y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;				
		}
		else if(matrix[x][*y]=='p'){
			(*p)++;	
			*temp = '0';
			strcpy(collected[*count],"P-");
			(*count)++;			
		}
		else if(matrix[x][*y]=='E'){
			(*E)++;	
			*temp = '0';	
			strcpy(collected[*count],"e+");
			(*count)++;	
		}
		else if(matrix[x][*y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");
			(*count)++;			
		}
		else if(matrix[x][*y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}
			*dd2=0;							
		}
		else if(matrix[x][*y]=='G'){
			*temp = 'G';
		}
		else{
			*temp = '0';
		}		
	}	
}
void moveDown2(char **matrix,int *x,int y,int row,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if(matrix[*x+1][y]!='1' && (*x+1)!=row && matrix[*x+1][y]!='K'){//matrix sinirlarina duvarlara ve karadeliige girmeyecek sekilde hareket eder ve parcacik varsa toplar							
		matrix[*x][y]=*temp;
		*x=*x+1;
		if(matrix[*x][y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;				
		}
		else if(matrix[*x][y]=='p'){
			(*p)++;	
			*temp = '0';	
			strcpy(collected[*count],"P-");
			(*count)++;		
		}
		else if(matrix[*x][y]=='E'){
			(*E)++;	
			*temp = '0';
			strcpy(collected[*count],"e+");	
			(*count)++;	
		}
		else if(matrix[*x][y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");;
			(*count)++;			
		}
		else if(matrix[*x][y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}
			*dd2=0;							
		}
		else if(matrix[*x][y]=='G'){
			*temp = 'G';
		}	
		else{
			*temp = '0';
		}	
	}
}
void moveUp2(char **matrix,int *x,int y,int row,int *P,int *p,int *E, int *e,char *temp,int *dd2,char **collected,int *count,int *antiH){
	if((*x)!=0 && matrix[*x-1][y]!='1' && matrix[*x-1][y]!='K'){//matrix sinirlarina duvarlara ve karadelige girmeyecek sekilde hareket eder ve parcacik varsa toplar							
		matrix[*x][y]=*temp;
		*x=*x-1;		
		if(matrix[*x][y]=='P'){
			(*P)++;
			*temp = '0';
			strcpy(collected[*count],"P+");
			(*count)++;			
		}
		else if(matrix[*x][y]=='p'){
			(*p)++;	
			*temp = '0';	
			strcpy(collected[*count],"P-");
			(*count)++;		
		}
		else if(matrix[*x][y]=='E'){
			(*E)++;	
			*temp = '0';
			strcpy(collected[*count],"e+");
			(*count)++;		
		}
		else if(matrix[*x][y]=='e'){
			(*e)++;	
			*temp = '0';
			strcpy(collected[*count],"e-");	
			(*count)++;		
		}
		else if(matrix[*x][y]=='C'){
			if(*p-*P>0 && *E-*e>0){
				if(*p>*E){
					printf("\nExit reached.\n%d antimatter produced.",*E-*e);
					*antiH=*E-*e;
				}
				else{
					printf("\nExit reached.\n%d antimatter produced.",*p-*P);
					*antiH=*p-*P;
				}	
			}
			else{
				printf("\nExit reached.\n0 antimatter produced.");
			}			
			*dd2=0;							
		}
		else if(matrix[*x][y]=='G'){
			*temp = 'G';
		}
		else{
			*temp = '0';
		}		
	}
}
void printCollected(char **toplanan,int count){
	int i;
	printf("\n\nCollected subatomic particlers:\n");
	for(i=0;i<count;i++){
		printf("%s ",toplanan[i]);
	}
	printf("\n");
}
char** allocMatrix(int row, int column){
	int i;
	char **matrix;
	matrix=(char**)malloc(row*sizeof(char*));
	for(i=0;i<row;i++){
		matrix[i]=(char*)malloc(column*sizeof(char));						
	}
	return matrix;	
}
void matrixFree(char **matrix,int row){
	int i;
	for(i=0;i<row;i++){
		free(matrix[i]);	
	}
	free(matrix);
}
void play(char **matrix, char *fileName,int row,int column,char **collected,int *antiH,double*resTime){//manuel 
	readBoardFromFile(matrix,fileName);
	int i,j,x,y,count,P=0,p=0,E=0,e=0,direction;
	char temp;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(matrix[i][j]=='G'){
				x=i;
				y=j;
				temp='G';
			}
		}
	}
	time_t startTime, currentTime;
    double totalTime;
    int timeLimit = 75;					
	int dd2=1;
	count=0;
	collected=allocMatrix(25,3);//25 parca toplayabilsin max	
	startTime = time(NULL);
	while(dd2){						
		matrix[x][y]='X';						
		drawBoard(matrix,row,column);
		printf("\n\nDirection: ");		
		direction=getch();
		if (totalTime >= timeLimit) {
	        printf("Time is up. Game over..\n");
	        dd2=0;
	    }
		if(direction==27){//esc
			printf("CIKIS!");
			dd2=0;
		}
		else if(direction==77){
			moveRight(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd2,collected,&count,antiH);							
			printCollected(collected,count);
			
		}
		else if(direction==80){
			moveDown(matrix,&x,y,row,&P,&p,&E, &e,&temp,&dd2,collected,&count,antiH);
			printCollected(collected,count);
		}
		else if(direction==75){
			moveLeft(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd2,collected,&count,antiH);
			printCollected(collected,count);
		}
		else if(direction==72){
			moveUp(matrix,&x,y,row,&P,&p,&E, &e,&temp,&dd2,collected,&count,antiH);
			printCollected(collected,count);
		}
		if(matrix[x][y]!='C' && matrix[x][y]!='K'){
			sleep(1); system("cls");
		}
		if(matrix[x][y]!='C'){			
			currentTime = time(NULL);
			totalTime = difftime(currentTime, startTime);
			if (totalTime >= timeLimit) {
				*resTime=totalTime;
	            printf("Time is up. Game over..\n");
	            dd2=0;
	        }
		}
		else{
			currentTime = time(NULL);
			totalTime = difftime(currentTime, startTime);
			*resTime=totalTime;
		}
		
	
	}
	if(matrix[x][y]=='K'){			
		*resTime=75;	            
	        
	}
}
void requestFromUser(int *row, int *column, char *fileName){
	giveInfo();
	printf("\nEnter the row number of game board: ");
	scanf("%d",row);
	printf("\nEnter the column number of game board: ");
	scanf("%d",column);	
	printf("\nEnter the file name: ");
	scanf(" %s",fileName);	
}
void useExistBoard(char **matrix,char *fileName,int *row, int *column){//� created
	int choice4=4;
	printf("\n1-Game board 1 (6x10)\n2-Game board 2 (5x5)\n3-Game board 3 (7x7)\n");					
	while(choice4!=1 && choice4!=2 && choice4!=3){
		printf("Choose game board: ");	
		scanf("%d",&choice4);
	}
	if(choice4==1){
		*row=6;
		*column=10;
		strcpy(fileName,"tahta1.txt");		
	}
	else if(choice4==2){
		*row=5;
		*column=5;
		strcpy(fileName,"tahta2.txt");
	}
	else{
		*row=7;
		*column=7;
		strcpy(fileName,"tahta3.txt");
	}	
}
void otoPlay(char **matrix, char *fileName,int row,int column,char **collected,int *antiH,double *resTime){//otomatik oyun fonksidirectionu
	int directions[4]={77,75,80,72};
	int randomNum;
	int dd=1;
	readBoardFromFile(matrix,fileName);
	int i,j,x,y,count,P=0,p=0,E=0,e=0,direction;
	char temp;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			if(matrix[i][j]=='G'){
				x=i;
				y=j;
				temp='G';
			}
		}
	}
	time_t startTime, currentTime;
    double totalTime;
    int timeLimit = 150;					
	count=0;
	collected=allocMatrix(25,3);
	startTime = time(NULL);
	while(dd){
		matrix[x][y]='X';						
		drawBoard(matrix,row,column);
		randomNum = rand() % 4;
		if(x==0 || matrix[x-1][y]=='1'){
			if(x+1==row || matrix[x+1][y]=='1'){
				if(y==0 || matrix[x][y-1]=='1'){
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
				}
				else if(y+1==column || matrix[x][y+1]=='1'){
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
					else if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(y==0 || matrix[x][y-1]=='1'){
				if(x+1==row || matrix[x+1][y]=='1'){
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}	
				}
				else if(y+1==column || matrix[x][y+1]=='1'){
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
					else if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(y+1==column || matrix[x][y+1]=='1'){
				if(x+1==row || matrix[x+1][y]=='1'){
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else if(y==0 || matrix[x][y-1]=='1'){
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
					else if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else{
				if(directions[randomNum]==77){
					moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
					printCollected(collected,count);
				}
				else if(directions[randomNum]==75){
					moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}
				else if(directions[randomNum]==80){
					moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}	
			}
				
		}
		else if(x+1==row || matrix[x+1][y]=='1'){
			if(x==0 || matrix[x-1][y]=='1'){
				if(y==0 || matrix[x][y-1]=='1'){
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
				}
				else if(y+1==column || matrix[x][y+1]=='1'){
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
					else if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(y==0 || matrix[x][y-1]=='1'){
				if(x==0 || matrix[x-1][y]=='1'){
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
				}
				else if(y+1==column || matrix[x][y+1]=='1'){
					if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
					else if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(y+1==column || matrix[x][y+1]=='1'){
				if(x==0 || matrix[x-1][y]=='1'){
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else if(y==0 || matrix[x][y-1]=='1'){
					if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
					else if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}			
			}
			else{
				if(directions[randomNum]==77){
					moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
					printCollected(collected,count);
				}
				else if(directions[randomNum]==75){
					moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}
				else if(directions[randomNum]==72){
					moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}	
			}
		}
		else if(y==0 || matrix[x][y-1]=='1'){
			if(x==0 || matrix[x-1][y]=='1'){
				if(y+1==column || matrix[x][y+1]=='1'){
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else if(x+1==row || matrix[x+1][y]=='1'){
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
					else if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
					
			}
			else if(x+1==row || matrix[x+1][y]=='1'){
				if(x==0 || matrix[x-1][y]=='1'){
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
				}
				else if(y+1==column || matrix[x][y+1]=='1'){
					if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==77){
						moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
						printCollected(collected,count);
					}
					else if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(y+1==column || matrix[x][y+1]=='1'){
				if(x+1==row || matrix[x+1][y]=='1'){
					if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else if(x==0 || matrix[x-1][y]=='1'){
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
					else if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else{
				if(directions[randomNum]==77){
					moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
					printCollected(collected,count);
				}
				else if(directions[randomNum]==80){
					moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}
				else if(directions[randomNum]==72){
					moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}	
			}
				
		}
		else if(y+1==column || matrix[x][y+1]=='1'){
			if(x==0 || matrix[x-1][y]=='1'){
				if(x+1==row || matrix[x+1][y]=='1'){
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else if(y==0 || matrix[x][y-1]=='1'){
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
					else if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(x+1==row || matrix[x+1][y]=='1'){
				if(x==0 || matrix[x-1][y]=='1'){
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else if(y==0 || matrix[x][y-1]=='1'){
					if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==75){
						moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
					else if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else if(y==0 || matrix[x][y-1]=='1'){
				if(x==0 || matrix[x-1][y]=='1'){
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				else if(x+1==row || matrix[x+1][y]=='1'){
					if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
				}
				else{
					if(directions[randomNum]==80){
						moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}
					else if(directions[randomNum]==72){
						moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
						printCollected(collected,count);
					}	
				}
				
			}
			else{
				if(directions[randomNum]==75){
					moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}
				else if(directions[randomNum]==80){
					moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}
				else if(directions[randomNum]==72){
					moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
					printCollected(collected,count);
				}	
			}
				
		}
		else{
			if(directions[randomNum]==77){
				moveRight2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);			
				printCollected(collected,count);
			}
			else if(directions[randomNum]==75){
				moveLeft2(matrix,x,&y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
				printCollected(collected,count);
			}
			else if(directions[randomNum]==80){
				moveDown2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
				printCollected(collected,count);
			}
			else{
				moveUp2(matrix,&x,y,column,&P,&p,&E, &e,&temp,&dd,collected,&count,antiH);
				printCollected(collected,count);
			}
		}
		if(matrix[x][y]!='C'){
			sleep(1); system("cls");
			currentTime = time(NULL);
			totalTime = difftime(currentTime, startTime);
			if (totalTime >= timeLimit) {//zaman dolarsa oyun biter
				*resTime=totalTime;
	            printf("Time is up. Game over..\n");
	            dd=0;
	        }
		}
		else{//cikisa ulastiginda zaman dolmazsa puan hesaplanabilmesi icin gecen zaman tutulur
			currentTime = time(NULL);
			totalTime = difftime(currentTime, startTime);
			*resTime=totalTime;
		}
	}
}
void swap(double *row1, double *row2, int col_count) {//scor matrixinin satirlarinin yeri degistirilir
	int i;
    for (i = 0; i < 2; i++) {
        double temp = row1[i];
        row1[i] = row2[i];
        row2[i] = temp;
    }
}
void sort(double **scors, int n,char *fileName2){//scorlar� s�ralar
	int i,j;
	for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (scors[j][0] < scors[j+1][0]) {
                swap(scors[j], scors[j+1],n);
            }
        }
    }
    FILE *fs = fopen(fileName2,"rb");
    if (fs == NULL) {
	    printf("File could not be opened!\n");
	} 
	else {
		USER k;
	    if(n<=5){
	    	for(i=0;i<n;i++){   		
				fseek(fs,(scors[i][1])*sizeof(USER),SEEK_SET);
				fread(&k, sizeof(USER), 1, fs);
				printf("%d.%s\tscor:%lf\n",i+1,k.userName,k.scor);
			}
		}
		else{
			for(i=0;i<5;i++){
				fseek(fs,(scors[i][1])*sizeof(USER),SEEK_SET);
				fread(&k, sizeof(USER), 1, fs);
				printf("%d.%s\tscor:%lf\n",i+1,k.userName,k.scor);
			}
		}
		fclose(fs);    
	}
    
}
void menu(char userName[],char fileName2[]){
	USER k;
	USER userFromFile;
	int cloice1,choice2,dd=1,back;	
	char fileName[20];
	char **matrix;
	int row,column,i,j;
	char temp;
	char **collected;
	int antiH=0;
	double scor;
	while(dd){
		sleep(1); system("cls");
		printf("\nMENU\n");
		printf("1-Leaderboard\n2-How to play?\n3-Start game\n4-Exit\n");
		printf("Choose: ");
		scanf("%d",&cloice1);
		sleep(1); system("cls");
		if(cloice1==1){//Leaderboardnda en yuksek 5 skor ve sahipleri olacak
			FILE *fs = fopen(fileName2,"rb");
			fseek(fs,0,SEEK_SET);
			i=0;			
			while(fread(&userFromFile, sizeof(USER), 1, fs) == 1 ){
				i++;
			}
			double **scors;
			scors=(double**)malloc(i*sizeof(double*));
			for(j=0;j<i;j++){
				scors[j]=(double*)malloc(2*sizeof(double));
			}
			fseek(fs,0,SEEK_SET);
			i=0;			
			while(fread(&userFromFile, sizeof(USER), 1, fs) == 1 ){
				scors[i][0]=userFromFile.scor;
				scors[i][1]=(double)i;
				i++;
			}
			fclose(fs);
			sort(scors,i,fileName2);
			
			free(scors);
			back=2;
			while(back!=1){
				printf("\nEnter 1 for go back: ");
				scanf("%d",&back);	
			}
			dd=1;
		}	
		else if(cloice1==2){//nas�l playn�r
			printf("\nIt is played using the arrow keys on the keyboard..\n");
			printf("\nThere are subatomic particles on the roads in the maze. The user starts the game from the specified entry point and progresses towards the exit point. Antihydrogen will be produced using subatomic particles collected from the paths of the labyrinth. ");
			printf("\nThere are the following particles on the roads in the maze.\n");
			printf("\np+\t:proton\ne-\t:electron\np-\t:antiproton\ne+\t:antielectron\n");
			printf("\nIn order to produce antihydrogen, you must have only P- and e+ particles at the exit of the maze.");
			printf("\nIf a particle and its antiparticle with the opposite sign come together, they annihilate each other.");
			printf("\nBlack holes are denoted by K. If you pass through the cells containing black holes, the game ends.");
			printf("\nIf the user cannot reach the exit within a certain game time, the game ends.");
			printf("\nYou earn 10 points for the amount of antihydrogen created, and if you complete it in a short time, you will earn more points.\n");
			giveInfo();
			back=2;
			while(back!=1){
				printf("\nEnter 1 for go back: ");
				scanf("%d",&back);	
				system("cls");
			}			
			dd=1;
		}
		else if(cloice1==3){//Start game
			double time=0;
			scor=0;
			printf("\nGAME MODES\n");
			printf("1-User controlled mode\n2-Auto play mode\n");
			choice2=4;
			while(choice2!=1 && choice2!=2){
				printf("\nchoose mode: ");
				scanf("%d",&choice2);	
			}
			sleep(1); system("cls");
			if(choice2==1){//////////////////////////////////////////manuel
				antiH=0;
				scor=20;
				int choice3=3;
				while(choice3!=1 && choice3!=2){
					printf("\n1-play with exist game boards\n2-Load game board\nHow do you want to play: ");
					scanf("%d",&choice3);	
				}
				sleep(1); system("cls");
				if(choice3==1){//hazir tahta yukle
					giveInfo();
					useExistBoard(matrix,fileName,&row,&column);
					sleep(1); system("cls");
					matrix=allocMatrix(row,column);
					play(matrix,fileName,row,column,collected,&antiH,&time);
					if(time>=75){
						scor=20;
					}
					else{
						scor+=(double)antiH*10.0*(1000.0/time);	
					}
					printf("\nThe score you won: %lf",scor);
					int dd2=1;
					FILE *fs = fopen(fileName2,"rb+");
					fseek(fs,0,SEEK_SET);
					i=0;
					while(dd2 && fread(&userFromFile, sizeof(USER), 1, fs) == 1){
						if(strcmp(userFromFile.userName,userName)==0){												
							dd2=0;												
						}
						else{
							i++;
						}						
					}
					userFromFile.scor+=scor;
					printf("\nTotal scor: %lf\n",userFromFile.scor);
					fseek(fs,i*sizeof(USER),SEEK_SET);
					fwrite(&userFromFile, sizeof(USER), 1, fs);
					fclose(fs);
					back=2;
					while(back!=1){
						printf("\nEnter 1 for go back: ");
						scanf("%d",&back);	
					}								
					dd=1;								
				}
				else{
					requestFromUser(&row,&column,fileName);
					matrix=allocMatrix(row,column);	
					play(matrix,fileName,row,column,collected,&antiH,&time);
					if(time>=75){
						scor=20;
					}
					else{
						scor+=(double)antiH*10.0*(1000.0/time);	
					}				
					printf("\nThe score you won: %lf",scor);
					int dd2=1;
					FILE *fs = fopen(fileName2,"rb+");
					fseek(fs,0,SEEK_SET);
					i=0;
					while( dd2 && fread(&userFromFile, sizeof(USER), 1, fs) == 1){
						if(strcmp(userFromFile.userName,userName)==0){							
							dd2=0;												
						}
						else{
							i++;
						}
						
					}
					userFromFile.scor+=scor;
					printf("\nTotal scor: %lf\n",userFromFile.scor);
					fseek(fs,i*sizeof(USER),SEEK_SET);
					fwrite(&userFromFile, sizeof(USER), 1, fs);
					fclose(fs);
					back=2;
					while(back!=1){
						printf("\nEnter 1 for go back: ");
						scanf("%d",&back);	
					}								
					dd=1;									
				}
														
			}
			else{//AUTO////////////////////////////////////////////////
				scor=20;
				antiH=0;
				int choice3=3;
				while(choice3!=1 && choice3!=2){
					printf("\n1-play with exist game boards\n2-Load game board\nHow do you want to play: ");
					scanf("%d",&choice3);	
				}				
				if(choice3==1){//hazir yukle
					giveInfo();
					useExistBoard(matrix,fileName,&row,&column);
					sleep(1); system("cls");
					matrix=allocMatrix(row,column);
					otoPlay(matrix,fileName,row,column,collected,&antiH,&time);	
					if(time>=150){
						scor=20;
					}
					else{
						scor+=(double)antiH*20.0*(1000.0/time);	
					}
					printf("\nThe score you won: %lf",scor);
					int dd2=1;
					FILE *fs = fopen(fileName2,"rb+");
					fseek(fs,0,SEEK_SET);
					i=0;
					while(dd2 && fread(&userFromFile, sizeof(USER), 1, fs) == 1){
						if(strcmp(userFromFile.userName,userName)==0){							
							dd2=0;												
						}
						else{
							i++;
						}
						
					}
					userFromFile.scor+=scor;
					printf("\nTotal scor: %lf\n",userFromFile.scor);
					fseek(fs,i*sizeof(USER),SEEK_SET);
					fwrite(&userFromFile, sizeof(USER), 1, fs);
					fclose(fs);
					back=2;
					while(back!=1){
						printf("\nEnter 1 for go back: ");
						scanf("%d",&back);	
					}								
					dd=1;				
				}
				else{//kullanıcıdan iste
					requestFromUser(&row,&column,fileName);
					matrix=allocMatrix(row,column);	
					otoPlay(matrix,fileName,row,column,collected,&antiH,&time);	
					if(time>=150){
						scor=20;
					}
					else{
						scor+=(double)antiH*20.0*(1000.0/time);	
					}
					printf("\nThe score you won: %lf",scor);
					int dd2=1;
					FILE *fs = fopen(fileName2,"rb+");
					fseek(fs,0,SEEK_SET);
					i=0;
					while(dd2 && fread(&userFromFile, sizeof(USER), 1, fs) == 1){
						if(strcmp(userFromFile.userName,userName)==0){													
							dd2=0;												
						}
						else{
							i++;
						}
						
					}
					userFromFile.scor+=scor;
					printf("\nTotal scor: %lf\n",userFromFile.scor);
					fseek(fs,i*sizeof(USER),SEEK_SET);
					fwrite(&userFromFile, sizeof(USER), 1, fs);
					fclose(fs);
					back=2;
					while(back!=1){
						printf("\nEnter 1 for go back: ");
						scanf("%d",&back);	
					}								
					dd=1;								
				}
				
				
			}
		}
		else if(cloice1==4){
			printf("\nExit..\n");
			sleep(1); system("cls");
			dd=0;
		}
		else{
			dd=1;
		}
	}
}

