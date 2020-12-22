#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>

///This will set the forground color for printing in a console window.
void SetColor(int ForgC)
{
     WORD wColor;
     ///We will need this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     ///We use csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        ///Mask out all but the background attribute, and add in the forgournd color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void SetColorAndBackground(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}

COORD coord = {0,0}; ///set the cordinate to 0, 0 (top-left corner of window);
void gotoxy(int x, int y){
    coord.X = x; coord.Y = y; /// X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void clearWindow()
{
    int i,j;
    for(i = 37; i < 78; i++)
	{
        for(j = 7; j < 25; j++)
		{
            gotoxy(i,j);printf(" ");
        }
    }
    return;
}


void requestspecialdish();
void sanitization();
void main_menu_display(void);
void main_menu_display1(void);
void customer_cart(void);
void pickup();
void feedback();
void booktable();


void menu(void);
void details(void);
void password(char[] );

int getdata();

FILE *fp,*dp,*dt;

typedef struct
{
	int ordernumber;
	int quantity;
	char itemname[100];
}order;
order o[45];

int s;
int again;
int quantity;
double total=0;
int t;
int static flag;
int registeruser=0;
int login=0;
typedef struct
{
    char username[100];
    char pass[100];
}user;

void Register()
{
	system("cls");
	system("color 4e");
	int registerchoice;
    char name[150];
    char pass[100];
    char pass2[100];
    int match,l;
    printf("\t\t\t Enter User Name:\t");
    fseek(stdin,0,SEEK_END);
	fgets(name,100,stdin);
    {
        printf("\n Enter password:");
        password(pass);
        printf("\n Confirm Password:");
        password(pass2);
        if(strcmp(pass,pass2)==0)
		{
            FILE *fp1=fopen("Login.txt", "a+");
            if(fp1==NULL)
            {
                printf("\nTechnical  ERROR!\n");
                exit(1);
            }
            user u;
            strcpy(u.username,name);
            strcpy(u.pass,pass);
            fwrite(&u,sizeof(user),1,fp1);
            fclose(fp1);
	        registeruser=1;
            printf("\n\t\t\t\t Account created Successfully!\n");
            flag=1;
	    
        }
        else{
 	
            printf("\n\n\t\t\t Passwords don't match!\n");
            printf("\t\t\t To try again enter 1!\n\t\t\t Enter 2 to exit:\n");
            int choice;
            scanf("%d",&choice);
            if(choice==1)
                Register();
            else
                exit(1);
        }

    }
}
void password(char str[])
{
    int i=0;
    char c=' ';
    while(i<=10)
    {
        str[i]=getch();
        c=str[i];
        if(c==13)break;
        else
		{
			printf("*");
        	i++;
        }
    }
    printf("\n");
    str[i]='\0';
}

void Login(char name[], char pass[])
{
	system("cls");
	system("color 3e");
    FILE* fp1=fopen("Login.txt","r");
    int i,l;
    user u[20];
    fread(u,sizeof(user),20,fp1);
    for(i=0;i<20;i++)
    {
        if(strcmp(name,u[i].username)==0 && strcmp(pass,u[i].pass)==0)
	    {
            flag=0;
			login=1;
            printf("\n\t\t Login Successful!\n");
         }
    }
    if(login!=1)
    {
    	printf("\n\nLogin failed please Try again!\n\n");
    	main();
    }
    
}
void main_menu_display()
{
	
	system("cls");
	system("color 5e");
	SetColor(3);
	printf("                                 **************************************************************************\n");
	printf("                                                     WELCOME TO PARADISE ONLINE ORDER SYSTEM\n");
	printf("                                 **************************************************************************\n\n\n");
	while(1)
   {
   	system("color 5e");
  	
	printf("\n");
	printf("   	1. BOOK TABLE \n	2. PLACE ORDER\n	3. PICK UP\n 	4. DISPLAY SAFETY PRECAUTIONS \n   	5. FEEDBACK\n	6. Exit \n\n\n ");
	int choice;
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
		case 1:booktable();
			break;
		case 2:customer_cart();
			break;
		case 3:pickup();
			break;
		case 4:sanitization();
			break;
		case 5:feedback();
			break;
		case 6:system("cls");
               printf("\n\n\n");
               printf("*******************************THANK YOU**************************************\n");
		       exit(0);
	}
	
	
   }

}

void main_menu_display1()
{
	
	system("cls");
	system("color 5e");
	SetColor(3);
	printf("                                 **************************************************************************\n");
	printf("                                                     WELCOME TO PARADISE ONLINE ORDER SYSTEM\n");
	printf("                                 **************************************************************************\n\n\n");
	while(1)
   {
   	system("color 5e");
  	
	printf("\n");
	printf("   	1. PLACE ORDER\n	2. PICK UP\n 	3. DISPLAY SAFETY PRECAUTIONS \n   	4. FEEDBACK\n	5. GO TO LOGIN PAGE\n 	6. Exit \n\n\n ");
	int choice;
	scanf("%d",&choice);
	system("cls");
	switch(choice)
	{
	
		case 1:customer_cart();
			break;
		case 2:pickup();
			break;
		case 3:sanitization();
			break;
		case 4:feedback();
			break;
		case 5:main();
		      break;
		case 6:system("cls");
               printf("\n\n\n");
               printf("*******************************THANK YOU**************************************\n");
		       exit(0);
	}
	
	
   }

}

int main()
{
	system("cls");
	int choice;
	char name[100];
	char pass[100];
	SetConsoleTitle("***************************************************************PARADISE ONLINE ORDER SYSTEM******************************************************************");
	system("color 4e");
	printf("                                 **************************************************************************\n");
	printf("                                                     WELCOME TO PARADISE ONLINE ORDER SYSTEM\n");
	printf("                                 **************************************************************************\n\n\n");
	printf("\n\n\n\n\n");
	printf("		1. Login\n		2. Register\n 		3. GuestLogin\n		4. Exit\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:  printf("Enter Username:\n");
				fseek(stdin,0,SEEK_END);
				fgets(name,100,stdin);
                printf("Enter Password:\n");
                password(pass);
                Login(name,pass);
                main_menu_display();
                break;
  		case 2: Register();
				main_menu_display();
				break;
  		case 3:main_menu_display1();
			   break;
	   case 4:exit(1);
	   default:printf("Invalid choice\n Please choose a valid option");
	}
	
}
void booktable()
{
	
	system("color 9e");
	SetColor(0);
	
	FILE *rp=fopen("Reservation.txt","r");
	FILE *rp1=fopen("Reservation.txt","a");
	int check=0,i=0,dd,mm,num_guests;
	time_t s;
	time(&s);
	printf("Enter date on which you want to book table(dd-mm)\n");
	scanf("%d-%d",&dd,&mm);
	struct tm* month=localtime(&s);
	if(dd<=month->tm_mday)
	{
		printf("\n\nPlease enter correct date \n\n");	
		booktable();
	}
	else if(mm==month->tm_mon+1)
	{
		switch(mm)
       {
	    case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:	
		case 12:if(0<dd && dd<=31)
		       {
		       	printf("Enter Number of people\n");
		       	scanf("%d",&num_guests);
		       	while(fscanf(rp,"%d",&i)==1)
		       	{
	       			if(i==dd)
	       			{
			       		check+=1;
			       	}
	       		}
  
	       		if(check==3)
	       		{
		       		printf("Sorry, All Tables are reserved on %d-%d\n",dd,mm);
		       	}
			
		       	else
		       	{
	       			printf("Table Booked Successfully for %d-%d\n",dd,mm);
	       			printf("You can Arrive at restraunt any Time within 24Hrs of Your booking");
	       			printf("**************Your Table would be Sanitized and sealed properly**************");
	       			fprintf(rp1,"%d\n",dd);
	       			fclose(rp);
	       			fclose(rp1);
	       		}
		       }
 				else
 					printf("\n Please,enter Valid Date \n");
   		       break;
		case 2:if(0<dd && dd<=28)
		       {
		       	printf("Enter Number of people\n");
		       	scanf("%d",&num_guests);
		       	while(fscanf(rp,"%d",&i)==1)
		       	{
	       			if(i==dd)
	       			{
			       		check=1;
			       		break;
			       	}
	       		}
		       
	       		if(check==1)
	       		{
		       		printf("Sorry, All Tables are reserved on %d-%d\n",dd,mm);
		       	}
		       	else
		       	{
	       			printf("\nTable Booked Successfully for %d-%d\n",dd,mm);
	       			printf("You can Arrive at restraunt any Time within 24Hrs of Your booking\n");
	       			printf("**************Your Table would be Sanitized and sealed properly**************");
	       			fprintf(rp1,"%d\n",dd);
	       			fclose(rp);
	       			fclose(rp1);
	       		}
		       }
		       	else
		       		printf("\n Please,enter Valid Date \n");
		       		
   		       break;
		case 4:
		case 6:
		case 9:
		case 11:if(0<dd&& dd<=30)
		       {
		       	printf("Enter Number of people\n");
		       	scanf("%d",&num_guests);
		        while(fscanf(rp,"%d",&i)==1)
		       	{
	       			if(i==dd)
	       			{
			       		check=1;
			       		break;
			       	}
	       		}
		       
	       		if(check==1)
	       		{
		       		printf("Sorry, All Tables are reserved on %d-%d\n",dd,mm);
		       	}
		       	else
		       	{
	       			printf("\nTable Booked Successfully for %d-%d\n",dd,mm);
	       			printf("You can Arrive at restraunt any Time within 24Hrs of Your booking\n");
	       			printf("**************Your Table would be Sanitized and sealed properly**************\n");
	       			fprintf(rp1,"%d\n",dd);
	       			fclose(rp);
	       			fclose(rp1);
	       		}
		       }
		       else
		       		printf("\n Please,enter Valid Date \n");
   		       break;
		
	
		default:printf("Invalid date please enter valid date");
			
	   }
		
	}
	else
	{
		printf("\n\nPlease enter date in present month only\n\n");
	}
		       
}

void sanitization()
{
	system("cls");
	system("color 4e");
	SetColor(10);
    printf("\n\nEvery staff member is wearing masks and gloves at their workplace.\n");
	printf(" We are encouraging our customers to wear masks while entering into the premises.\n");
	printf("Every customer is screened at the entrance.\n We are sanitising the customer high touch points");
	printf("for every two hours. We have rearranged the seating positions and maintaining one-metre distance between the staff who are on the floor.\n ");
	printf("We are also sanitising the complete place before and after everyday. To maintain social distancing in the kitchen, we have markers.\n To ensure the same in the main area, we have introduced digital menus and encouraging our customers to pay their bills through digital mode.\n Providing quality food and service with safe customer experience is our utmost priority.\n");
    Sleep(5000);
}

void feedback()
{
	char message[100];
	printf("Enter your feedback message:\n");
	fseek(stdin,0,SEEK_END);
	fgets(message,100,stdin);
	printf("****************************Thanks for your feedback***************************\nYour feedback msg\n");
	puts(message);
}

void customer_cart(void)
{
	
	system("cls");
	system("color 6e");
	printf("                    ************************************************\n                                      WELCOME\n                    ************************************************\n\n");
	printf("               CHOOSE--->\n\n               1. MENU\n\n               \n\n                      OR\n\n               2. Back To Main Menu\n\n   Enter Your Choice  -->");
	int k;
	scanf("%d",&k);
	if(k==1)
	{
		system("cls");
		menu();
	}
	else if(k==2)
	{
		system("cls");
	}
	else if(k==3)
	{
		system("cls");
		main();
	}
	else
	{
		printf("Wrong Input !");
		customer_cart();
	}
}
void display_cart()
{
	system("cls");
	system("color 4e");
	FILE *write=fopen("Cart.txt","w");
	int i;
	printf("\n************************************YOUR CART***********************************************\n");
	for(i=1;i<45;i++)
	{
		if(o[i].ordernumber==1)
		{
			if(o[i].quantity>0)
			fprintf(write,"\n  ID <%d> - %s <quantity %d> \n",i,o[i].itemname,o[i].quantity);
		}
	}

	fclose(write);
	
	
	
	
	
	FILE *cart;
	char v;
	
    cart=fopen("Cart.txt","r");
    if(cart==NULL)
    	printf("Technical Error\n\n");
	while((v=getc(cart))!=EOF)
        {
        	printf("%c",v);
		}
         fclose(cart);
         
 	printf("\n**********************************************************************************************\n");
	
	
}
void menu(void)
{
	int choice;
	int again;
	int quantity;
	double price=0;
	SetColor(0);
	
	printf("                    ****************************************\n                                   MENU\n                    ****************************************\n\n");        
	char v;
	FILE *vmenu;
	system("color 5e");
	
    vmenu=fopen("Menu.txt","rt");
	while((v=getc(vmenu))!=EOF)
        {
        	printf("%c",v);
		}
         fclose(vmenu);
    printf("\n\nEnter What You Want :");
	printf("\n\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=200*(o[1].quantity);
		total=total + 200*(quantity);
		printf("\n");
		o[1].quantity=quantity;
		o[1].ordernumber=1;
		strcpy(o[1].itemname,"Veg Spring roll");

        printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}

		

	else if(choice==2)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=253*(o[2].quantity);
		total=total + 253*(quantity);
		printf("\n");
		
		o[2].quantity=quantity;
		o[2].ordernumber=1;
		strcpy(o[2].itemname,"Veg Manchuria");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==3)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=253*(o[3].quantity);
		total=total + 253*(quantity);
		printf("\n");
		
		o[3].quantity=quantity;
		o[3].ordernumber=1;
		strcpy(o[3].itemname,"Gobi Manchuria");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==4)
	{
		printf("Quantity :");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=262*(o[4].quantity);
		total=total + 262*(quantity);
		
		o[4].quantity=quantity;
		o[4].ordernumber=1;
		strcpy(o[4].itemname,"Chilli Paneer");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==5)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=262*(o[5].quantity);
		total=total + 262*(quantity);
		
		o[5].quantity=quantity;
		o[5].ordernumber=1;
		strcpy(o[5].itemname,"Paneer 65");
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==6)
	{
		printf("Quantity :");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=212*(o[6].quantity);
		total=total + 212*(quantity);
		
		o[6].quantity=quantity;
		o[6].ordernumber=1;
		strcpy(o[6].itemname,"Egg Spring roll");
		
		printf("\nPress 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	}
	else if(choice==7)
	{
		printf("Quantity :");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=212*(o[7].quantity);
		total=total + 212*(quantity);
		
		o[7].quantity=quantity;
		o[7].ordernumber=1;
		strcpy(o[7].itemname,"Chicken Spring roll");
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
			
	}
	else if(choice==8)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=354*(o[8].quantity);
		total=total + 354*(quantity);
		printf("\n");
		
		o[8].quantity=quantity;
		o[8].ordernumber=1;
		strcpy(o[8].itemname,"Chicken 65");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==9)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=354*(o[9].quantity);
		total=total + 354*(quantity);
		printf("\n");
		
		o[9].quantity=quantity;
		o[9].ordernumber=1;
		strcpy(o[9].itemname,"Chilli Chicken");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==10)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=354*(o[10].quantity);
		total=total + 354*(quantity);
		printf("\n");
		
		o[10].quantity=quantity;
		o[10].ordernumber=1;
		strcpy(o[10].itemname,"Chicken Drumsticks");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==11)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=410*(o[11].quantity);
		total=total + 410*(quantity);
		printf("\n");
		
		o[11].quantity=quantity;
		o[11].ordernumber=1;
		strcpy(o[11].itemname,"Apollo Fish");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==12)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=432*(o[12].quantity);
		total=total + 432*(quantity);
		printf("\n");
		
		o[12].quantity=quantity;
		o[12].ordernumber=1;
		strcpy(o[12].itemname,"Chilli Prawns");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==13)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=211*(o[13].quantity);
		total=total + 211*(quantity);
		printf("\n");
		
		o[13].quantity=quantity;
		o[13].ordernumber=1;
		strcpy(o[13].itemname,"Veg Soft Noodles");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==14)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=184*(o[14].quantity);
		total=total + 184*(quantity);
		printf("\n");
		
		o[14].quantity=quantity;
		o[14].ordernumber=1;
		strcpy(o[14].itemname,"Egg Soft Noodles");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==15)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=223*(o[15].quantity);
		total=total + 223*(quantity);
		printf("\n");
		
		o[15].quantity=quantity;
		o[15].ordernumber=1;
		strcpy(o[15].itemname,"Chicken Soft Noodles");
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
		
	}
	else if(choice==16)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=211*(o[16].quantity);
		total=total + 211*(quantity);
		printf("\n");
		
		o[16].quantity=quantity;
		o[16].ordernumber=1;
		strcpy(o[16].itemname,"Veg Fried Rice");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==17)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=223*(o[17].quantity);
		total=total + 223*(quantity);
		printf("\n");
		
		o[17].quantity=quantity;
		o[17].ordernumber=1;
		strcpy(o[17].itemname,"Egg Fried Rice");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==18)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=223*(o[18].quantity);
		total=total + 223*(quantity);
		printf("\n");
		
		o[18].quantity=quantity;
		o[18].ordernumber=1;
		strcpy(o[18].itemname,"Chicken Fried Rice");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==19)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=229*(o[19].quantity);
		total=total + 229*(quantity);
		printf("\n");
		
		o[19].quantity=quantity;
		o[19].ordernumber=1;
		strcpy(o[19].itemname,"Dal Fry");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==20)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=200*(o[20].quantity);
		total=total + 229*(quantity);
		printf("\n");
		
		o[20].quantity=quantity;
		o[20].ordernumber=1;
		strcpy(o[20].itemname,"Dal Makhni");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==21)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=229*(o[21].quantity);
		total=total + 229*(quantity);
		printf("\n");
		
		o[21].quantity=quantity;
		o[21].ordernumber=1;
		strcpy(o[21].itemname,"Kadai Veg");
		
		printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==22)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=241*(o[22].quantity);
		total=total + 241*(quantity);
		printf("\n");
		
		o[22].quantity=quantity;
		o[22].ordernumber=1;
		strcpy(o[22].itemname,"Kadaai Paneer");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==23)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=241*(o[23].quantity);
		total=total + 241*(quantity);
		printf("\n");
		
		o[23].quantity=quantity;
		o[23].ordernumber=1;
		strcpy(o[23].itemname,"Malai Kofta");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==24)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=241*(o[24].quantity);
		total=total + 241*(quantity);
		printf("\n");
		
		o[24].quantity=quantity;
		o[24].ordernumber=1;
		strcpy(o[24].itemname,"Paneer Butter Masala");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==25)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=241*(o[25].quantity);
		total=total + 241*(quantity);
		printf("\n");
		
		o[25].quantity=quantity;
		o[25].ordernumber=1;
		strcpy(o[25].itemname,"Palak Paneer");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==26)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=229*(o[26].quantity);
		total=total + 229*(quantity);
		printf("\n");
		
		o[26].quantity=quantity;
		o[26].ordernumber=1;
		strcpy(o[26].itemname,"Egg Masala");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==27)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=318*(o[27].quantity);
		total=total + 318*(quantity);
		printf("\n");
		
		o[27].quantity=quantity;
		o[27].ordernumber=1;
		strcpy(o[27].itemname,"Chicken Curry");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==28)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=330*(o[28].quantity);
		total=total + 330*(quantity);
		printf("\n");
		
		o[28].quantity=quantity;
		o[28].ordernumber=1;
		strcpy(o[28].itemname,"Fish Masala");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==29)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=330*(o[29].quantity);
		total=total + 330*(quantity);
		printf("\n");
		
		o[29].quantity=quantity;
		o[29].ordernumber=1;
		strcpy(o[29].itemname,"Butter Chicken");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==30)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=330*(o[30].quantity);
		total=total + 330*(quantity);
		printf("\n");
		
		o[30].quantity=quantity;
		o[30].ordernumber=1;
		strcpy(o[30].itemname,"P@radise Special Chicken");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==31)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=330*(o[31].quantity);
		total=total + 330*(quantity);
		printf("\n");
		
		o[31].quantity=quantity;
		o[31].ordernumber=1;
		strcpy(o[31].itemname,"Chicken Tikka Masala");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==32)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=330*(o[32].quantity);
		total=total + 330*(quantity);
		printf("\n");
		
		o[32].quantity=quantity;
		o[32].ordernumber=1;
		strcpy(o[32].itemname,"Chicken Nawabi");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==33)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=354*(o[33].quantity);
		total=total + 354*(quantity);
		printf("\n");
		
		o[33].quantity=quantity;
		o[33].ordernumber=1;
		strcpy(o[33].itemname,"Mutton Rogan Gosh");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==34)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=354*(o[34].quantity);
		total=total + 354*(quantity);
		printf("\n");
		
		o[34].quantity=quantity;
		o[34].ordernumber=1;
		strcpy(o[34].itemname,"Kadai Ghost");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==35)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=354*(o[35].quantity);
		total=total + 354*(quantity);
		printf("\n");
		
		o[35].quantity=quantity;
		o[35].ordernumber=1;
		strcpy(o[35].itemname,"Prawns Masala");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==36)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=52*(o[36].quantity);
		total=total + 52*(quantity);
		printf("\n");
		
		o[36].quantity=quantity;
		o[36].ordernumber=1;
		strcpy(o[36].itemname,"Tandoori Roti");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==37)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=52*(o[37].quantity);
		total=total + 52*(quantity);
		printf("\n");
		
		o[37].quantity=quantity;
		o[37].ordernumber=1;
		strcpy(o[37].itemname,"Rumali Roti");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==38)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=67*(o[38].quantity);
		total=total + 67*(quantity);
		printf("\n");
		
		o[38].quantity=quantity;
		o[38].ordernumber=1;
		strcpy(o[38].itemname,"Plain Naan");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==39)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=39*(o[39].quantity);
		total=total + 77*(quantity);
		printf("\n");
		
		o[39].quantity=quantity;
		o[39].ordernumber=1;
		strcpy(o[39].itemname,"Butter Naan");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==40)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=77*(o[40].quantity);
		total=total + 77*(quantity);
		printf("\n");
		
		o[40].quantity=quantity;
		o[40].ordernumber=1;
		strcpy(o[40].itemname,"Aloo Paratha");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==41)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=41*(o[41].quantity);
		total=total + 96*(quantity);
		printf("\n");
		
		o[41].quantity=quantity;
		o[41].ordernumber=1;
		strcpy(o[41].itemname,"Double Ka Meetha");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==42)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=143*(o[42].quantity);
		total=total + 143*(quantity);
		printf("\n");
		
		o[42].quantity=quantity;
		o[42].ordernumber=1;
		strcpy(o[42].itemname,"Qubani ka Meetha");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==43)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=102*(o[43].quantity);
		total=total + 102*(quantity);
		printf("\n");
		
		o[43].quantity=quantity;
		o[43].ordernumber=1;
		strcpy(o[43].itemname,"Gulab Jamun");
		
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	else if(choice==44)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=119*(o[44].quantity);
		total=total + 119*(quantity);
		printf("\n");
		
		o[44].quantity=quantity;
		o[44].ordernumber=1;
		strcpy(o[44].itemname,"Gajar ka Halwa");
			printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
		
	}
	else if(choice==45)
	{
		printf("Quantity :  ");
		scanf("%d",&quantity);
		
		while(quantity<0)
		{
			printf("Please Enter quantity correctly:\n");
			scanf("%d",&quantity);
		}
		
		total-=114*(o[45].quantity);
		total=total + 114*(quantity);
		printf("\n");
		
		o[45].quantity=quantity;
		o[45].ordernumber=1;
		strcpy(o[45].itemname,"Chocolate Brownie");
		
		printf("Press 1 To Order Again :\n Press 2 To view Cart \nPress 3 To Get Your Total:\n\nEnter Your Choice :");
		scanf("%d",&again);
		printf("\n");
		if(again==1)
		{
			printf("\n\n");
			menu();
		}
		else if(again==2)
		{
			display_cart();
				printf("Press 1 To Order Again :\nPress 2 To Get Your Total:\n\nEnter Your Choice :");
				scanf("%d",&again);
				printf("\n");
				if(again==1)
				{
					printf("\n\n");
					menu();
				}
				else if(again==2)
				{
					printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
					int totl = total;
					FILE *ttl;
					ttl = fopen("order.txt","a");
					fprintf(ttl,"\nGrand Total : %d\n",totl);
					fclose(ttl);
	
			
				}
		}
		else if(again==3)
		{
			printf("Your Total Amount Is : Rs. %.2lf\n\n",total);
			int totl = total;
			FILE *ttl;
			ttl = fopen("order.txt","a");
			fprintf(ttl,"\nGrand Total : %d\n",totl);
			fclose(ttl);
	
		
		}
	
	}
	
	else
	{
		printf("Wrong Input! Re-enter THe Correct Option\n\n");
		if(getch())
		menu();
	}
}
void pickup()
{
	customer_cart();
	details();
}


void details(void)
{
	char name1[20];
	char name2[20];
	char phone[11];
	char vehiclenumber[40];
	char landmark[30];
	printf("Please Give Your Contact Details \n");
	printf(" First Name : ");
	fseek(stdin,0,SEEK_END);
	fgets(name1,100,stdin);
	printf("Last Name : ");
	fseek(stdin,0,SEEK_END);
	fgets(name2,100,stdin);
	printf("Phone : ");
	fseek(stdin,0,SEEK_END);
	fgets(phone,100,stdin);
	while(strlen(phone)!=11)
	{
		printf("Enter 10 digit mobile number only\n");
		fseek(stdin,0,SEEK_END);
		fgets(phone,100,stdin);
	}
	printf("Vehicle Number : ");
	fseek(stdin,0,SEEK_END);
	fgets(vehiclenumber,100,stdin);
	printf("\n\n");
	printf("Your Entered Details Are --->\n");
	FILE *cust;
	cust = fopen("order.txt","a");
	fprintf(cust,"Order Placed By : %s %s\nPhone number : %s\n",name1,name2,phone);
	fclose(cust);
	printf("    -->First Name :  %s\n    -->Last Name   :  %s\n    -->Phone     :%s \n    -->Vehicle Number  :%s \n  \n",name1,name2,phone,vehiclenumber);
	printf("\n\n\n");
	printf("                       *********************************************************************************************\n");
	printf("                                             Your Order Will Be Ready  In 30 minutes.\n");
	printf("                                                       .....HAPPY ORDERING.....\n");
	printf("                       *********************************************************************************************\n");
	
	printf("Press Any To The MainMenu.");
	if(getch())
	customer_cart();
}
       

