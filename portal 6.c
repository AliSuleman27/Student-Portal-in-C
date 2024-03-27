#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>

typedef struct course{
	char course_code[50];
	char course_name[50];
	int creditHrs;
	int semester;
}course;

//student structure
typedef struct student{

	int roll;	
	char full_name[50];
	char degree[50];
	char depart[50];
	char pass[50];	
	char section;
	int n; int semester;
	struct subjectDetails
	{
		char course_code[15];
		char c_name[50];
		int credithr;
		char c_teacher[50];
		int tot;  //total
		int obt;  //marks obt
	}sub[6];
}student;


// general functions
void getpwd(char pwd[])
{
	int i; char ch;
	while(1)
	{
		ch = getch();
		if(ch==13 || ch==9)
		{
			pwd[i] = '\0';
			break;
		}
		else if(ch == 8)
		{
			if(i>0)
			{
				i--;
				printf("\b \b");
			}
			
		}
		else
		{
			pwd[i] = ch;
			printf("* \b");
			i++;
		}
	}
}
void gotoxy(int x, int y)
{
	COORD pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void console()
{
	int i;
	system("cls");
	system("COLOR 3F");
	printf("\n\t\t\t\tNational University of Computer and Emerging Sciences\n\n");
	printf("\t\t\t\t\t\tFinal Project Semester 1\n");
	printf("\n\t\t\t\t\tPowered By: Ali Suleman ++ Abdul Wasay\n");
	gotoxy(12,6);
	for(i=0;i<90;i++)
	printf("-");
}

//management and its functions
void addNew()
{
	FILE *fp;
	system("cls");
	student *s;
	// variables for password
	unsigned int randChar; char ch[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890!@#$%^&*()";
	int i,n=1,j;
	printf("\n------------------------------------------ STUDENT REGISTARTION FORM -----------------------------------------------\n\n\n");
	re:
	printf("Enter How many students you want register: ");
	scanf("%d",&n);

	s = (student*)calloc(n,sizeof(student));
	fp = fopen("studentData.txt","a+");
	
	for(i=0;i<n;i++)
	{
			
			printf("\nEnter ID:  \t\t\t\t");
			scanf("%d",&s[i].roll);
			fflush(stdin);
			printf("\nGenerated Password: \t\t\t");
			{
				srand(time(NULL));
				for(j=0;j<8;j++)
				{
					randChar = rand()%72;
					s[i].pass[j] = ch[randChar];
				}
			}
			puts(s[i].pass);
			printf("\nEnter Student Name: \t\t\t");
			gets(s[i].full_name);
			printf("\nEnter Degree Enrolled: (BS/MS/PhD): \t");
			gets(s[i].degree);
			printf("\nEnter Department: (AI,CS,DS,etc.): \t");
			gets(s[i].depart);
			printf("\nEnter Semester: \t\t");
			scanf("%d",&s[i].semester);
			fflush(stdin);
			printf("\nEnter Section:(A to Z): \t\t");
			scanf("%c",&s[i].section);
			printf("\n****************************\n");
			fwrite(&s[i],sizeof(student),1,fp);
						
	}
	fclose(fp);

}

void displayStds()
{
	int j;
	student ss;
	FILE *fp;
	fp = fopen("studentData.txt","r");
	printf("\n%-5s%-20s","ID","NAME");
	printf("%-5s.%s","DEGREE","DEPART");
	printf("\t\t%s","SEMESTER");
	while(fread(&ss,sizeof(student),1,fp))
	{
				printf("\n%-5d%-20s",ss.roll,ss.full_name);
				printf("%-5s%-20s",ss.degree,ss.depart);
				printf("%-54d",ss.semester);
	}
	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(student);
	printf("\n==============Statistics===============");
	printf("\n\nNo of Stduents Enrolled = %d",n);
	printf("\n=======================================\n");
		printf("Press any key to go back.......");
	getch();
	fclose(fp);
}

void searchStd()
{
	
	int j;
	student ss;
	FILE *fp;
	int found;
	int key;
	printf("\n------------------------------------------ STUDENT SEARCH-----------------------------------------------\n\n\n");
	re:

       	printf("Enter ID of student: \n");
        scanf("%d",&key);

		found = 0;
	fp = fopen("studentData.txt","r");
	while(fread(&ss,sizeof(student),1,fp))
	{
		if(ss.roll == key)
		{
			    printf("\n%-5s%-20s","ID","NAME");
				printf("%-5s.%s","DEGREE","DEPART");
				printf("\t\t%s","SEMESTER");
				found = 1;
				printf("\n%-5d%-20s",ss.roll,ss.full_name);
				printf("%-5s%-20s",ss.degree,ss.depart);
				printf("%-54d",ss.semester);
		}
	}
	if(found!=1)
	printf("\nStudent Not found!!! \nMessage: (Maybe you have entered wrong roll # or student student does not exist) ");
	
	printf("\n--------------------------------------\n");
	printf("\n\n Do you want to search again(y/n):  ");
	fflush(stdin);
	char tempo;
	scanf("%c",&tempo);
	printf("\n--------------------------------------\n");
	if(tempo=='y' || tempo=='Y')
	goto re;
	else
	{
	printf("\n\nPress any key to go back.......");
	getch();	
	}

		fclose(fp);
}

void modifyStd()
{
	system("cls");
	printf("\n------------------------------------------  MODIFY STUDENT -----------------------------------------------\n\n\n");
	int j,i;
	student ss;
	FILE *fp,*fpa;
	int found;
		    int key;

       	printf("Enter ID of student: \n");
        scanf("%d",&key);

		found = 0;
	fp = fopen("studentData.txt","r");
	fpa = fopen("tempstore.txt","w");
	while(fread(&ss,sizeof(student),1,fp))
	{
		if(ss.roll == key)
		{
			found=1;
			printf("\n\n\t\t\t\tRECORD FOUND!!!!!!!");
			printf("\n%-5s%-20s","ID","NAME");
			printf("%-5s.%s","DEGREE","DEPART");
			printf("\t\t%s","COURSES ENROLLED");
			printf("\n%-5d%-20s",ss.roll,ss.full_name);
			printf("%-5s%-20s",ss.degree,ss.depart);
			printf("%4d",ss.semester);
			
			printf("\n-----------------------------------------------------------------------------------------");
			printf("\n\n\t\t\t\tEnter the new details of student: ");
			fflush(stdin);
			printf("\nEnter New Name: \t\t\t");
			gets(ss.full_name);
			printf("\nEnter Degree Enrolled: (BS/MS/PhD): \t");
			gets(ss.degree);
			printf("\nEnter Department: (AI,CS,DS,etc.): \t");
			gets(ss.depart);
			printf("\nEnter Semester: \t\t\t");
			scanf("%d",&ss.semester);
			fflush(stdin);
			printf("\nEnter Section:(A to Z): \t\t");
			scanf("%c",&ss.section);
			printf("\n****************************\n");

		}
	fwrite(&ss,sizeof(student),1,fpa);
	}
	fclose(fp);
	fclose(fpa);
	
	if(found == 1)
	{
			fp = fopen("studentData.txt","w");
			fpa = fopen("tempstore.txt","r");
			
			while(fread(&ss,sizeof(student),1,fpa))
			{
				fwrite(&ss,sizeof(student),1,fp);
			}
			
			for(i=0; i<3; i++)
      		  {
            printf(".\t");
            Sleep(250);
   		     }
   		     
			printf("\nRecord Updated Successfully\nPress any key to go back......");
			getch();
			fclose(fp);
			fclose(fpa);

	}
	else
	{
		printf("\nMessage ----> Record Not Found!!!!!!");
		Beep(1200,800);
	}
	
}


void removeStd()
{
	system("cls");
	printf("\n------------------------------------------  REMOVE STUDENT -----------------------------------------------\n\n\n");
	int j,i;
	student ss;
	FILE *fp,*fpa;
	int found; char ch;
		    int key;

       	printf("Enter ID of student: \n");
        scanf("%d",&key);

		found = 0;
	fp = fopen("studentData.txt","r");
	fpa = fopen("tempstore.txt","w");
	
	while(fread(&ss,sizeof(student),1,fp))
	{
		
		if(ss.roll != key)
		{
			found=1;
			fwrite(&ss,sizeof(student),1,fpa);
		}
		else
		{
				printf("\n%-5s%-20s","ID","NAME");
				printf("%-5s.%s","DEGREE","DEPART");
				printf("\t\t%s","COURSES ENROLLED");
				found = 1;
				printf("\n%-5d%-20s",ss.roll,ss.full_name);
				printf("%-5s%-20s",ss.degree,ss.depart);
				for(j=0;j<6;j++)
				{
				printf("%4s ",ss.sub[j].course_code);
				printf("%5s   ",ss.sub[j].c_name);
				}
		}

	}
	fclose(fp);
	fclose(fpa);
	
	if(found == 1)
	{
			fp = fopen("studentData.txt","w");
			fpa = fopen("tempstore.txt","r");
			
			while(fread(&ss,sizeof(student),1,fpa))
			{
				fwrite(&ss,sizeof(student),1,fp);
			}
			
			printf("\nDeleting searched record");
			for(i=0; i<3; i++)
      		  {
            printf(".\t.");
            Sleep(400);
   		     }
   		     
			printf("\n\nRecord Updated Successfully\nEnter any key to go back");
			getch();
			fclose(fp);
			fclose(fpa);

	}
	else
	{
		printf("\nSorry.... record not found");
	}
	
}

void ViewPwds()
{
	printf("\n------------------------------------------  STUDENTS ID-PASSWORDS -----------------------------------------------\n\n\n");
	printf("\n%-5s%-20s","ID","NAME");
	printf("%-5s","PASSWORD");
	int j;
	student ss;
	FILE *fp;
	fp = fopen("studentData.txt","r");
	while(fread(&ss,sizeof(student),1,fp))
	{
		printf("\n%-5d%-20s",ss.roll,ss.full_name);
		printf("%-5s",ss.pass);
	}
	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(student);
	printf("\n\n\n==============Statistics===============");
	printf("\n\nNo of Passwords Found = %d",n);
	printf("\n=======================================\n");
		printf("Press any key to go back.......");
	getch();
	fclose(fp);
}

void change()
{
	system("color 3F");
		FILE *fp;
	fflush(stdin);
	char pwd1[50], pwd2[50];

	fp = fopen("managlog.txt","w");
	fflush(stdin);
	gotoxy(42,10);
	printf("-------------------------------------------------------");
	gotoxy(42,12);
	printf("Enter new password: ");
	getpwd(pwd1);
	fflush(stdin);
	gotoxy(42,14);
	printf("Enter again to confirm password: ");
	getpwd(pwd2);
	if(strcmp(pwd1,pwd2)==0)
	{
			gotoxy(42,16);
			printf("Password Changed successfully :) ");
			
			fwrite(&pwd1,50,1,fp);
			fclose(fp);
	}
	else
	{
		gotoxy(42,16);
		printf("\b\n Something Went Wrong!!!!");
	}
	gotoxy(42,18);
	printf("---------------------------------------------------------");
	getch();


	
}

void messageGo()
{
	printf("\nPress any key to continue...........");
}

void addCourse()
{
	FILE *fp;
	int i,n;
	course *c;
	system("cls");
	console();
	printf("\n------------------------------------------ ADD NEW COURSE -----------------------------------------------\n\n\n");
	printf("\nHow many courses you want to add: ");
	scanf("%d",&n);
	c = (course*)calloc(n,sizeof(course));
	fp = fopen("course.txt","a+");
	if(fp==NULL)
	{
		printf("\nError Opening File!!!!");
		Beep(1200,800);
		exit(1);
	}
	for(i=0;i<n;i++)
	{
	fflush(stdin);
	printf("Enter Course Course: \t");
	gets(c[i].course_code);
	printf("Enter Course Name: \t");
	gets(c[i].course_name);
	printf("Enter Credit Hourse: \t");
	scanf("%d",&c[i].creditHrs);
	printf("Enter Semester: \t");
	scanf("%d",&c[i].semester);
	printf("\n-------------------------------------------\n");
	fwrite(&c[i],sizeof(course),1,fp);
	}
	printf("\nMessage:  Courses Added Successfully");
	fclose(fp);
	printf("\nDo you want to add more courses (y/n): \t");
	char temp;
	fflush(stdin);
	scanf("%c",&temp);
	
	if(temp=='y' || temp=='Y')
	addCourse();
		
	getch();
	
}

void removeCourse()
{
	FILE *fp, *fp1;
	int i,flag=0;
	course c;
	char remCourse[50];
	system("cls");
	console();
	printf("\n------------------------------------------ REMOVE COURSE -----------------------------------------------\n\n\n");
	
	fp = fopen("course.txt","r");
	fp1 = fopen("tempstore.txt","w");
	if(fp == NULL)
	{
		system("cls");
		printf("Error File opening: \n");
		Beep(1200,800);
		exit(1);
	}
	fflush(stdin);
	printf("\nEnter Course Code: ");
	gets(remCourse);
	while(fread(&c,sizeof(course),1,fp)==1)
	{
		if(strcmp(c.course_code,remCourse)!=0)
		{
			fwrite(&c,sizeof(course),1,fp1);
		}
		else
		{
			flag = 1;
		}
	}
	fclose(fp);
	fclose(fp1);
	if(flag)
	{
		fp1 = fopen("tempstore.txt","r");
		fp = fopen("course.txt","w");
		while(fread(&c,sizeof(course),1,fp1)==1)
		{
			fwrite(&c,sizeof(course),1,fp);
		}
		printf("\nMessage:  Courses Removed Successfully");
		fclose(fp);
		fclose(fp1);
	
	}
	else
	{
		printf("\n\n\t\tError: No course with this code was found!!!!!");
		Beep(1200,800);
	}
	
		printf("\nDo you want to remove more courses (y/n): \t");
		char temp;
		scanf("%c",&temp);
		
		if(temp=='y' || temp=='Y')
		removeCourse();
	
}

void viewCourses()
{
	FILE *fp;
	course c;
	system("cls");
	console();
	fp = fopen("course.txt","r");
	printf("\n");
	printf("\n\t%-20s%-20s%-20s%-20s","Course Code","Course Name","Credit Hours","Semester Offered In\n");
	while(fread(&c,sizeof(course),1,fp)==1)
	{
		printf("\t%-20s%-20s%-20d%-20d",c.course_code,c.course_name,c.creditHrs,c.semester);
		printf("\n");
	}

	fseek(fp,0,SEEK_END);
	int n = ftell(fp)/sizeof(course);
	printf("\n==============Statistics===============");
	printf("\n\nTotal Number of Courses = %d",n);
	printf("\n=======================================\n");
		printf("Press any key to go back.......");
			fclose(fp);
	getch();
	
	
}

void management()
{
		re:
		system("cls");
	
		console();
		int select;
		printf("\n\n\n\t\t\t\tSelect any one of the tabs: ");
		printf("\n\n\t\t\t\t1. Student");
        printf("\n\n\t\t\t\t2. Courses");
        printf("\n\n\t\t\t\t3. Teacher's\n\t\t");
		scanf("%d",&select);
		
		switch(select)
		{
			//student entry, modification, removal, etc
			case 1:{
				
				system("cls");
				console();
				printf("\n\n\t\t\t\t...Please Press the desired key from the menu.....");
				printf("\n\n\t\t\t\t1. Add New Student");
        		printf("\n\n\t\t\t\t2. Modify Student");
        		printf("\n\n\t\t\t\t3. Show All Student");
       	 		printf("\n\n\t\t\t\t4. Search Student");
        		printf("\n\n\t\t\t\t5. Remove Student");
        		printf("\n\n\t\t\t\t6. View Student's Passwords");
    			printf("\n\n\t\t\t\t7. Change Password");
       		 	printf("\n\n\t\t\t\t8. Exit from Student Tab\n\t");
       		 	int mch; //refers to managements choice
       		 	scanf("%d",&mch);
        
        		switch(mch)
       		 	{
        		case 1:
        			addNew();
        		break;
        	
        		case 2:
        			modifyStd();
        		break;
        		
        		case 3:
        			system("cls");
        			printf("\n---------------------------- STUDENT DETAILS -------------------------------------\n");
        		//	printf("\n%-5s%-20s","ID","NAME");
				//	printf("%-5s.%s","DEGREE","DEPART");
				//	printf("\t\t%s","COURSES ENROLLED");
        			displayStds();
        		break;
        	
        		case 4:
        			system("cls");
        			searchStd();
        		break;
        	
        		case 5:
     		   		system("cls");
       		 		removeStd();
					break;
				case 6:
					system("cls");
					ViewPwds();
				break;
				case 7:
					system("cls");
					change();
				break;
				case 8:

					system("cls");
					management();
				break;
				}
	
			goto re;  
			break;
		}
			
			//course addition
			case 2:{
				z:
			system("cls");
				console();
				printf("\n\n\t\t\t\t...Please Press the desired key from the menu.....");
				printf("\n\n\t\t\t\t1. Search Course Enrollment");
				printf("\n\n\t\t\t\t2. Add New Course");
				printf("\n\n\t\t\t\t3. View All Course Being Offered");	
        		printf("\n\n\t\t\t\t4. Remove Course");
        		printf("\n\n\t\t\t\t5. Withdraw Student's  Course");
				printf("\n\n\t\t\t\t6. Exit\n\t\t\t");
        
        		int cchoice;
        		scanf("%d",&cchoice);
        		switch(cchoice)
        		{
					case 1:
						break;
					case 2:
        				addCourse();
        				break;
        			case 3:
        				viewCourses();
        				break;
        			case 4:
        				removeCourse();
        				break;
        			case 6:
        				system("cls");
        				management();
        				break;

				}
				getch();
				goto z;
			break;
			}
			
			case 3:
			break;
		}


        
         
}


void managementlogin()
{
	FILE * fp;
		system("COLOR 5F");	
		int i; char pwd[50], userpwd[50]; char ch;
		system("cls");
		fp = fopen("managlog.txt","r");
		fread(&pwd,sizeof(pwd),1,fp);
		gotoxy(42,10);
		printf("******************** ADMIN LOGIN MENU **************************");
		gotoxy(42,14);
		printf("Enter Password: ");
		fflush(stdin);
		getpwd(userpwd);

	if(strcmp(pwd,userpwd)!=0)
	{
	gotoxy(42,16);
	printf("Incorrect Password!!!!");
	Beep(1200,800);
	getch();
	system("cls");
	main();
	}
	fclose(fp);
	gotoxy(42,16);
	printf("Password Matched :)");
	getch();
		system("cls");
		gotoxy(42,12);
		printf("______________________________________");
		
		gotoxy(42,12) ;
		printf("\tWait Managment Portal is Loading...\n");
		gotoxy(42,13);
		for(i=0; i<3; i++)
        {
            printf("\t(*)");
            Sleep(500);
        }
        
        printf("\n\n\n\n");
        gotoxy(42,14);
        printf("****************************************\n");
        gotoxy(42,16);
          printf("    WELCOME TO NU-MANAGEMENT PORTAL       \n");
        gotoxy(42,18);
        printf("****************************************\n\n");
        
		printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
		getch();
	management();		
}


void teacher()
{
	printf("Welcome to teacher's portal'");
}

// student portal and its functions
void mydetails(int ID)
{
	
	system("cls");
	console();
	FILE *fp; int found=0;
	student s;

	fp = fopen("studentData.txt","r");
	while(fread(&s,sizeof(student),1,fp)==1)
	{
		if(s.roll == ID)
		{
			found=1;
			printf("\n\n\n\t\t\t------------------------------------------------------------\n");
			printf("\t\t\t---------------------- MY DETAILS --------------------------\n");
			printf("\t\t\t------------------------------------------------------------\n\n");
			printf("\t\t\t\tID: \t\t\t%d",s.roll);
			printf("\n\t\t\t\tStudent's Name: \t");
			puts(s.full_name);
			printf("\n\t\t\t\tDegree: \t\t");
			puts(s.degree);
			printf("\n\t\t\t\tDepartment: \t\t");
			puts(s.depart);
			
		}
	}
	messageGo();
	getch();
	
	fclose(fp);
	
}

void changemypass(int ID)
{
	
	int i=0;
	FILE *fp, *fp1;
	student ss;
	char pwd[50],pwd2[50];
	system("cls");
	
	gotoxy(42,8);
	printf("    :---CHANGE MY PASSWORD---:   ");
	fp = fopen("studentData.txt","r");
	fp1 = fopen("tempstore.txt","w");
	
	if (fp == NULL)
	{
		Beep(1200,800);
		gotoxy(42,9);
		printf("Error file opening\n");
		exit(1);
	}
	while(fread(&ss,sizeof(student),1,fp)==1)
	{
		if(ss.roll==ID)
		{
			gotoxy(42,10);
			printf("Enter a password of atleast 8 characters: ");
			gotoxy(42,12);
			printf("Enter New Password: \t\t");
			getpwd(pwd);
			gotoxy(42,14);
			printf("Confirm your password: \t");
			getpwd(pwd2);
			if(strcmp(pwd,pwd2)==0 && strlen(pwd)>=8)
			{
				//printf("\n");
				strcpy(ss.pass,pwd);
				gotoxy(42,16);
				for(i=0;i<5;i++){printf(".. ");Sleep(500);}
				gotoxy(42,18);
				printf("Password Changed Successfully");	
			}
			else
			{
				if(strcmp(pwd,pwd2)!=0)
				{
					gotoxy(42,16);
					printf("Password Donot matched :(");
				}
				else if(strcmp(pwd,pwd2)==0 && strlen(pwd)<8)
				{
					gotoxy(42,16);
					printf("Password is too short :( Type a strong password of atleast 8 characters");
				}
			}
		}
		fwrite(&ss,sizeof(student),1,fp1);
	}
	
	fclose(fp);
	fclose(fp1);
	
	fp = fopen("studentData.txt","w");
	fp1 = fopen("tempstore.txt","r");
	
	while(fread(&ss,sizeof(student),1,fp1))
	{
		fwrite(&ss,sizeof(student),1,fp);
	}
	fclose(fp);
	fclose(fp1);
	getch();
	
}

void registerInCourse(int ID)
{
	system("cls");
	FILE *fp, *fp1, *fp2;
	student s;
	course c;
	char cc[50];

	int i,j=0, n,m, sem;
	console();
	fp = fopen("studentData.txt","r");
	if(fp = NULL){
		printf("Error File opening\n\n");
		exit(1);
	}
	printf("\n------------------------------------------ ENROLL COURSE -----------------------------------------------\n\n\n");
	// checking in which semester student is???
	fp = fopen("studentData.txt","r");
	while(fread(&s,sizeof(student),1,fp)==1)
	{
		if(s.roll==ID)
		{
			sem = s.semester;
		}
	}
	fclose(fp); printf("\n%d",sem);
	fp1 = fopen("course.txt","r");
	printf("Following Courses are being offered: \n");
	printf("\n\t%-20s%-20s%-20s","Course Code","Course Name","Credit Hours");
	while(fread(&c,sizeof(course),1,fp1)==1)
	{
		if(c.semester==sem)
		{
		printf("\t%-20s%-20s%-20d",c.course_code,c.course_name,c.creditHrs);
		printf("\n");
		}
	}
	fclose(fp1);
	printf("\n\nPress Enter for Enrollement ----");
	getch();
	fp = fopen("studentData.txt","r");
	fp1 = fopen("course.txt","r");
	fp2 = fopen("tempstore.txt","w");
	
//	while(fread)
	
	printf("\nhow many courses you want to enroll in: (Remember ! You cannot enroll yourself in more than 6 courses)");
	printf("\nNo of Course : \t\t");
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		j++;
		while(fread(&s,sizeof(student),1,fp)==1)
		{
			if(s.roll==ID)
			{
				fflush(stdin);
				printf("\nEnter Course Code %d: \t",j);
				gets(cc);
				while(fread(&c,sizeof(course),1,fp1)==1)
				{
					if(strcmp(c.course_code,cc)==0)
					{
						strcpy(s.sub[i].c_name,c.course_name);
						s.sub[i].credithr = c.creditHrs;
						s.n=i;
					}
				}
			}
			fwrite(&s,sizeof(student),1,fp2);
		}
	}
	fclose(fp);fclose(fp1);fclose(fp2);
	
	fp2 = fopen("tempstore.txt","r");
	fp = fopen("studentData.txt","w");
		while(fread(&s,sizeof(student),1,fp2))
		{
			fwrite(&s,sizeof(student),1,fp);
		}

	fclose(fp1);
	getch();

	
}

void studentportal()
{
		FILE * fp;
		student s;
		system("COLOR 3F");	
		int i,ID,found=0; char userpwd[50]; char ch;
		system("cls");
		fp = fopen("studentData.txt","r");
		gotoxy(42,10);
		printf("******************** LOGIN MENU **************************");
		gotoxy(42,11);
		printf("Enter Your ID: ");
		scanf("%d",&ID);
		gotoxy(42,12);
		printf("Enter Password: ");
		fflush(stdin);
		getpwd(userpwd);

	while(fread(&s,sizeof(student),1,fp)==1)
	{
		if(s.roll==ID && strcmp(s.pass,userpwd)==0)
		{
			found = 1;
			break;
		}
	}
	fclose(fp);
	if(found==0)
	{
		gotoxy(42,14);
		printf("Something Went Wrong :) Incorrect Password or ID");
		Beep(1200,800);
		exit(1);
	}
	gotoxy(42,16);
	printf("Password Matched :)");
	getch();
		system("cls");
		gotoxy(42,12);
		printf("______________________________________");
		
		gotoxy(42,12) ;
		printf("\tWait Student Portal is Loading...\n");
		gotoxy(42,13);
		for(i=0; i<3; i++)
        {
            printf("\t(*)");
            Sleep(500);
        }
        
        printf("\n\n\n\n");
        gotoxy(42,14);
        printf("****************************************\n");
        gotoxy(42,16);
          printf("    WELCOME TO NU-STUDENT PORTAL       \n");
        gotoxy(42,18);
        printf("****************************************\n\n");
        
		printf("\n\n\n\n\n\t\t\t\t\tPress any key to continue...... ");
		getch();
		
		y:
		system("cls");
		console();
		printf("\n\n\t\t\t\t...Please Press the desired key from the menu.....");
		printf("\n\n\t\t\t\t1. Information");
		printf("\n\n\t\t\t\t2. Register myself in Course");
    	printf("\n\n\t\t\t\t3. Change Password");
        printf("\n\n\t\t\t\t4. Exit\n\t");
        
        //sch refers to student choice
        int sch;
        scanf("%d",&sch);
        
		switch(sch)
		{
			case 1:
			mydetails(ID);	
			break;
			case 2:
			registerInCourse(ID);
			break;
			case 3:
			changemypass(ID);
			break;
			case 4:
			system("cls");
			main();
			break;
		}
		goto y;
}


int main()
{
	system("COLOR 0F");
	SetConsoleTitle("Student Management System | Natioanl University");
	
	repeat:
	gotoxy(42,8);
	printf("Choose from the Menu Below: ");
	gotoxy(42,11);
	printf("1.Management Member| 2.Student Login |  3.Teacher's Login'");
	gotoxy(42,12);
	printf("______________________________________");
	

	int ts;
	printf("\n\n\n\n");
	gotoxy(42,19);
	scanf("%d",&ts);
	
	if(ts==1)
	managementlogin();
	
	else if (ts==2)
	studentportal();
	
	else if (ts==3)
	teacher();
	
	system("cls");
	goto repeat;

	
	
	
return 1;

	
return 0;	
}

