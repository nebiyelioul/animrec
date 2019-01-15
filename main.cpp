/*
Nebiye Lioul
*/

#include <fstream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <windows.h>

using namespace std;

struct animal{
char name[20];
char name_of_species[15];
char name_of_genus[15];
char scentific_name[20];
char movement_system[15];
char feeding_system[12];
unsigned int estimated_num;
unsigned int life_span;
char isEndemic[4];
animal *prev,*next;
};

void gotoxy(int x,int y)
{
   COORD coord;
   coord.X=x;
   coord.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


//PROTOTYPE DECLARATIONS,OBJECT CREATION AND INITIALIAZATIONS
fstream file;
animal *start=NULL;
animal *end=NULL;
animal *temp1,*temp2,*temp3;
char temp[15];
int counter=0;
void main_manu();
int check();
char checkchar();
void search(char name[]);
void delete_nth_pos(int);
void sort_estimated();
void sort_by_name();
void sort_by_species();
void sort_lifespan();
void search_species(char name[]);

//FUNCTION DEFINITIONS THAT ARE COMMON FOR MULTIPLE FUNCTIONS
animal *insert()//METHOD USED TO INSERT DATA IN TO THE FILE
{
    int i=8;
    animal*newer =new animal;
   gotoxy(28,6);
   cout<<"ANIMAL REGISTRATION FORM";
   gotoxy(28,7);cout<<"------------------------";
   r:gotoxy(25,i+=2);
   fflush(stdin);
   cout<<"Enter name of the animal : ";
   cin.getline(newer->name,20);
    temp1=start;
   while(temp1!=NULL)
   {
       if (strcmpi(temp1->name,newer->name)==0)
       {    gotoxy(25,i+=2);
           cout<<"The name you inserted is found in the file \n\t\tif you want to enter again press \"Y\" or press any key to goto main menu"<<endl;
            char c=checkchar();
            if (c=='y' || c=='Y')
            {
                goto r;
            }
            else
                main_manu();
       }temp1=temp1->next;
   }
   z:gotoxy(25,i+=2);
   fflush(stdin);
   cout<<"Enter name of species : ";
   cin.getline (newer->name_of_species,15);
   temp1=start;
   while(temp1!=NULL)
   {
       if (strcmpi(temp1->name_of_species,newer->name_of_species)==0)
       {    gotoxy(25,i+=2);
           cout<<"The name you inserted is found in the file \n\t\tif you want to enter again press \"Y\" or press any key to goto main menu"<<endl;
            char c=checkchar();
            if (c=='y' || c=='Y')
            {
                goto z;
            }
            else
                main_manu();
       }temp1=temp1->next;
   }
   gotoxy(25,i+=2);
   cout<<"Enter name of genus : ";
   cin.getline(newer->name_of_genus,15);
   char name[20];
   strcpy(name,newer->name_of_genus);
   gotoxy(25,i+=2);
   strcpy(newer->scentific_name,strcat(name,newer->name_of_species));
   cout<<"Enter movement system : ";
   cin.getline(newer->movement_system,20);
   gotoxy(25,i+=2);
   cout<<"Enter feeding system \n";
   gotoxy(25,i+=2);
   cout<< "\t1. omnivorous \n";
   gotoxy(25,i+=1);
   cout<< "\t2. carnivorous \n";
   gotoxy(25,i+=1);
   cout<< "\t3. herbivorous \n";
   char omni[20]="omnivorous";
   char carn[20]="carnivorous";
   char herb[20]="herbivorous";
   t:
   gotoxy(25,i+=2);
   int b=i+2;
   cout<<" Enter your choice : ";
   int r=check();
   gotoxy(28,i+=2);
   switch(r)
       {
       case 1:
           strcpy(newer->feeding_system,omni);
           break;
       case 2:
           strcpy(newer->feeding_system,carn);
           break;
       case 3:
           strcpy(newer->feeding_system,herb);
           break;
        default :
         {
             cout<<" Invalid input , Retry again"<<endl;
             goto t;
         }
       }
   gotoxy(25,i+=2);
   cout<<"Enter estimated number : ";
   newer->estimated_num=check();
   gotoxy(25,i+=2);
   cout<<"Enter life span : ";
   fflush(stdin);
   newer->life_span=check();
   gotoxy(25,i+=2);
   cout<<"Is Endemic ? "<<endl;
   gotoxy(25,i+=2);
   cout<<"1. YES     2. NO"<<endl;
   char yes[4]="YES";
   char no[3]="NO";
   v:
   gotoxy(28,i+=2);
   int e=check();
   switch(e)
   {
   case 1:
    strcpy(newer->isEndemic,yes);
    break;
   case 2:
    strcpy(newer->isEndemic,no);
    break;
   default:
    {cout<<"Invalid input retry again"<<endl;
    goto v;}
   }
   cout<<endl;
   file.open("file.txt",ios::out | ios::app);
   file<<newer->name<<"        "<<newer->name_of_species<<"        "<<newer->name_of_genus<<"        "<<newer->scentific_name<<"        "<<newer->movement_system<<"        "<<newer->feeding_system<<"        "<<newer->life_span<<"        "<<newer->isEndemic<<endl;
   file.close();
   counter++;
   return newer;
}

void swap()//METHOD USED TO EXCHANGE DATA BETWEEN THE ANIMALS
{
    char temp3[20];
     strcpy(temp3,temp2->name);
     strcpy(temp2->name,temp2->prev->name);
     strcpy(temp2->prev->name,temp3);

     strcpy(temp3,temp2->name_of_species);
     strcpy(temp2->name_of_species,temp2->prev->name_of_species);
     strcpy(temp2->prev->name_of_species,temp3);

     strcpy(temp3,temp2->name_of_genus);
     strcpy(temp2->name_of_genus,temp2->prev->name_of_genus);
     strcpy(temp2->prev->name_of_genus,temp3);

     strcpy(temp3,temp2->scentific_name);
     strcpy(temp2->scentific_name,temp2->prev->scentific_name);
     strcpy(temp2->prev->scentific_name,temp3);

     strcpy(temp3,temp2->movement_system);
     strcpy(temp2->movement_system,temp2->prev->movement_system);
     strcpy(temp2->prev->movement_system,temp3);

     strcpy(temp3,temp2->feeding_system);
     strcpy(temp2->feeding_system,temp2->prev->feeding_system);
     strcpy(temp2->prev->feeding_system,temp3);

     int temp;

     temp=temp2->estimated_num;
     temp2->estimated_num=temp2->prev->estimated_num;
     temp2->prev->estimated_num=temp;

     temp=temp2->life_span;
     temp2->life_span=temp2->prev->life_span;
     temp2->prev->life_span=temp;
}
int check ()// THIS FUNCTION IS USED TO ACCEPT INTEGERS FROM THE KEYBOARD AND CHECK IF IT IS VALID
{
   unsigned int k;
    while(!(cin>>k))
    {
       cin.clear();
       cin.ignore(50,'\n');
    }
    return k;
}

char checkchar()// THIS FUNCTION IS USED TO ACCEPT CHARACTER FROM THE KEYBOARD AND CHECK IF IT IS VALID
{
     char k;
    while(!(cin>>k))
    {
       cout<<"\t\t\t\tyou must enter a character"<<endl;
       cin.clear();
       cin.ignore(50,'\n');
    }
    return k;
}
// METHOD DEFINITIONS
void insert_at_beginning()
 {  system("CLS");
   animal *newer=new animal;
   newer=insert();
   if (start==NULL && end==NULL)
   {
   	start=newer;
   	end=newer;
   	start->next=NULL;
   	start->prev=NULL;
   }
   else
   {
    temp2=start;
    newer->next=temp2;
    newer->prev=NULL;
    start=newer;
    temp2->prev=start;
   }
   //file.close();
   cout<<"Data added successfully";
   cout<<endl;
   system("pause");
   main_manu();
 }

 void insert_at_end() //insert the data at the end
{
   system("CLS");
   animal *newer =new animal;

   newer=insert();

	if(start==NULL && end==NULL)
    {

        newer->next=NULL;
        newer->prev=NULL;
        start=newer;
        end=newer;
    }
   else
   {

        end->next=newer;
        newer->prev=end;
        newer->next=NULL;
        end=newer;
   }
    system("pause");
	main_manu();
}


void insert_at_middle()
{
system("CLS");
if(start==NULL && end==NULL)
		{
			cout<<" THE DLL  is empty "<<endl;
			cout<<" add a new record\n\t press y _ to add record or n_ to terminate a record "<<endl;
		char ch;
		cin>>ch;
		if(ch=='Y'||ch=='y')
		{

			insert_at_beginning();
		}
		else
		{
			exit(1);
		}
		}
		else
		{   h:system("CLS");
		     char name[20];
             cout<<"ENTR NAME THAT YOU WANT TO ADD THE RECORD AFTER IT : ";
             cin>>name;
			    temp1=start;
			while(strcmpi(name,temp1->name)!=0 && temp1->next!=NULL)
			{

				temp1=temp1->next;
			}
			if(temp1->next==NULL){
			if(strcmpi(name,temp1->name)==0)
            {
                cout<<"This is the last file \nif you want add at the end press \"Y\" or press any key to goto main menu"<<endl;
			    char c=checkchar();
			    if (c=='y' || c=='Y')
                {
                    insert_at_end();
                }
                else
                    main_manu();
            }}

			else if (strcmpi(name,temp1->name)!=0)
			{
			    cout<<"value not found !!! \nif you want to enter again press \"Y\" or press any key to goto main menu"<<endl;
			    char c=checkchar();
			    if (c=='y' || c=='Y')
                {
                    goto h;
                }
                else
                    main_manu();
			}
			else
			{
                animal*newer =new animal;
                newer=insert();
				temp2=temp1->next;
				temp1->next=newer;
				newer->prev=temp1;
				newer->next=temp2;
				temp2->prev=newer;
			}
		}
		system("pause");
		main_manu();
		}
inline void show()
{
        cout <<"\n\t\tName : "<<temp1->name<<endl;
        cout <<"\t\tName_of_species : "<<temp1->name_of_species<<endl;
        cout <<"\t\tName_of_genus : "<<temp1->name_of_genus<<endl;
        cout <<"\t\tScientific name : "<<temp1->scentific_name<<endl;
        cout <<"\t\tmovement system : "<<temp1->movement_system<<endl;
        cout <<"\t\tFeeding_system : " <<temp1->feeding_system<<endl;
        cout <<"\t\tEstimated number : "<<temp1->estimated_num<<endl;
        cout <<"\t\tLife span : "<<temp1->life_span<<endl<<endl;
}
void search(char name[])//SEARCH BY NAME
{    int check=-1;
     temp1=start;
     {
     while (temp1!=NULL)
      {
          if(strcmpi(temp1->name,name)==0)
        {
          show();
          check=1;
        }
       temp1=temp1->next;
    }
   }
if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
}

void search_species(char name_of_specie[])
{int check=-1;
      temp1=start;
      while (temp1!=NULL)
      {
          if(strcmpi(temp1->name_of_species,name_of_specie)==0)
        {
               show();
               check=1;
        }
       temp1=temp1->next;
    }
if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
   }

void search_genus(char name_of_genu[])
{     int check=-1;
      temp1=start;
      while (temp1!=NULL)
      {
          if(strcmpi(temp1->name_of_genus,name_of_genu)==0)
        {
           show();
           check=1;
        }
       temp1=temp1->next;
   }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
}
void search_movement(char movement[])
{
int check=-1;

      while (temp1!=NULL)
      {
          if(strcmpi(temp1->movement_system,movement)==0)
        {
           show();
           check=1;
        }
       temp1=temp1->next;
    }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
        system("pause");
        main_manu();
}
}

void search_feeding(char feeding[])
{
int check=-1;

      while (temp1!=NULL)
      {
          if(strcmpi(temp1->feeding_system,feeding)==0)
        {
           show();
           check=1;
        }
       temp1=temp1->next;
    }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
        system("pause");
        main_manu();
}
}

void search_scientific(char scientific_name[])
{
int check=-1;
      temp1=start;
      while (temp1!=NULL)
      {
          if(strcmpi(temp1->scentific_name,scientific_name)==0)
        {
            show();
            check=1;
        }
       temp1=temp1->next;
    }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
}

void search_lifespan(int life)
{
      int check=-1;
      temp1=start;
      while (temp1!=NULL)
      {
          if(temp1->life_span==life)
        {
            show();
            check=1;
        }
       temp1=temp1->next;
    }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
}

void search_estimated(int estimated)
{
      int check=-1;
      temp1=start;
      while (temp1!=NULL)
      {
          if(temp1->estimated_num==estimated)
        {
            show();
            check=1;
        }
       temp1=temp1->next;
    }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
}

void search_endemic(char endemic[])
{
      int check=-1;
      temp1=start;
      while (temp1!=NULL)
      {
          if(strcmpi(temp1->isEndemic,endemic)==0)
        {
             show();
             check=1;
        }
       temp1=temp1->next;
    }
   if (check==-1)
{
    cout<<"Result not found"<<endl;
    system("pause");
    main_manu();
}
}
void searc()
{
    char name[15];
if (start==NULL && end==NULL)
{cout<<"There is no file to search"<<endl;
            system("pause");
            main_manu();}
else{
    int i=6;
    gotoxy(25,i);cout<<" 1. search by name "<<endl;
    gotoxy(25,i+=2);cout<<" 2. search by name of species "<<endl;
    gotoxy(25,i+=2);cout<<" 3. search by name of genus "<<endl;
    gotoxy(25,i+=2);cout<<" 4. search by estimated number"<<endl;
    gotoxy(25,i+=2);cout<<" 5. search by feeding system "<<endl;
    gotoxy(25,i+=2);cout<<" 6. search by scientific name "<<endl;
    gotoxy(25,i+=2);cout<<" 7. search by life span"<<endl;
    gotoxy(25,i+=2);cout<<" 8. search by movement system"<<endl<<endl;
    gotoxy(25,i+=2);cout<<"Enter your choice :";
            r:int y=check();
     system("CLS");gotoxy(25,5);
            switch(y)
            {
            case 1:
                {
                cout<<"Enter the name you want to find : ";
                cin>>name;
                search(name);

                break; }
            case 2:
                {
                cout<<"Enter the name of species you want to find : ";
                cin>>name;
                search_species(name);
                }
                break;
            case 3:
                  {
                cout<<"Enter the name of genus you want to find : ";
                cin>>name;
                search_genus(name);
                }
                break;
            case 4:
                {
                cout<<"Enter the estimated number of the animal you want to find : ";
                int n;
                cin>>n;
                search_estimated(n);
                }
                break;
            case 5:
                {
                cout<<"Enter the feeding system of the animal you want to find : ";
                cin>>name;
                search_feeding(name);;
                }
                break;
            case 6:
                {
                cout<<"Enter the scientific name of the animal you want to find : ";
                cin>>name;
                search_scientific(name);
                }
                break;
            case 7:
                {
                cout<<"Enter the life span of the animal you want to find : ";
                int n;
                cin>>n;
                search_lifespan(n);
                }
                break;
            case 8:
                {
                cout<<"Enter the movement system of the animal you want to find : ";
                cin>>name;
                search_movement(name);
                }
                break;
            default :
                {
                    cout<<"invalid input try again !!!!"<<endl;
                    goto r;
                }
           }}

          system("pause");
          main_manu();
}
void delete_single(char name[])
{
temp1=start;
cout<<"are you sure you want to delete (y/n)"<<endl;
                h:char h=checkchar();
                if (h=='y' || h=='Y' || h=='N' || h=='n')
                {
                 if (h=='y' || h=='Y' ){
                	while(strcmpi(temp1->name,name)!=0  && strcmpi(temp1->name_of_species,name)!=0  && strcmpi(temp1->scentific_name,name)!=0  )
                    {
                    temp2=temp1;
                    temp1=temp1->next;
                    temp3=temp1;
                    }
                    temp1=temp1->next;
                    temp2->next=temp1;
                    temp1->prev=temp2;
                    counter--;
                    delete temp3;
                    cout<<" deleted succesfully"<<endl;
                    system("pause");
                    main_manu();
              }
              else
                main_manu();
              }
			 else
			 {
			  cout<<"Invalid input try again "<<endl;
			  goto h;
			  }
			  }

void delete_by_genus(char name[])
{
cout<<"are you sure you want to delete (y/n)"<<endl;
    h:char h=checkchar();
    if (h=='y' || h=='Y' || h=='N' || h=='n')
       {
         if (h=='y' || h=='Y' )
            {
          temp2=start;
          temp1=temp2->next;
          while(temp1->next!=NULL)
           {
           if(strcmpi(temp1->name_of_genus,name)==0)
               {
                temp3=temp1;
                temp1=temp1->next;
                temp2->next=temp1;
                temp1->prev=temp2;
                counter--;
                delete temp3;
               }
           else
               {
                temp2=temp2->next;
                temp1=temp1->next;
               }
           }
           }
        else
            main_manu();
       }
    else
       {
          cout<<"Invalid input try again "<<endl;
          goto h;
       }
}

void delete_by_movement(char name[])
{
cout<<"are you sure you want to delete (y/n)"<<endl;
    h:char h=checkchar();
    if (h=='y' || h=='Y' || h=='N' || h=='n')
       {
         if (h=='y' || h=='Y' )
            {
          temp2=start;
          temp1=temp2->next;
          while(temp1->next!=NULL)
           {
           if(strcmpi(temp1->movement_system,name)==0)
               {
                temp3=temp1;
                temp1=temp1->next;
                temp2->next=temp1;
                temp1->prev=temp2;
                counter--;
                delete temp3;
               }
           else
               {
                temp2=temp2->next;
                temp1=temp1->next;
               }
           }
           }
        else
            main_manu();
       }
    else
       {
          cout<<"Invalid input try again "<<endl;
          goto h;
       }
}
void delete_by_endemic(char name[])
{
cout<<"are you sure you want to delete (y/n)"<<endl;
    h:char h=checkchar();
    if (h=='y' || h=='Y' || h=='N' || h=='n')
       {
         if (h=='y' || h=='Y' )
            {
          temp2=start;
          temp1=temp2->next;
          while(temp1->next!=NULL)
           {
           if(strcmpi(temp1->isEndemic,name)==0)
               {
                temp3=temp1;
                temp1=temp1->next;
                temp2->next=temp1;
                temp1->prev=temp2;
                counter--;
                delete temp3;
               }
           else
               {
                temp2=temp2->next;
                temp1=temp1->next;
               }
           }
           }
        else
            main_manu();
       }
    else
       {
          cout<<"Invalid input try again "<<endl;
          goto h;
       }
}
void delete_by_feeding(char name[])
{
cout<<"are you sure you want to delete (y/n)"<<endl;
    h:char h=checkchar();
    if (h=='y' || h=='Y' || h=='N' || h=='n')
       {
         if (h=='y' || h=='Y' )
            {
          temp2=start;
          temp1=temp2->next;
          while(temp1->next!=NULL)
           {
           if(strcmpi(temp1->feeding_system,name)==0)
               {
                temp3=temp1;
                temp1=temp1->next;
                temp2->next=temp1;
                temp1->prev=temp2;
                counter--;
                delete temp3;
               }
           else
               {
                temp2=temp2->next;
                temp1=temp1->next;
               }
           }
           }
        else
            main_manu();
       }
    else
       {
          cout<<"Invalid input try again "<<endl;
          goto h;
       }
}
void delete_by_estimated(int num)
{
cout<<"are you sure you want to delete (y/n)"<<endl;
    h:char h=checkchar();
    if (h=='y' || h=='Y' || h=='N' || h=='n')
       {
         if (h=='y' || h=='Y' )
            {
          temp2=start;
          temp1=temp2->next;
          while(temp1->next!=NULL)
           {
           if(temp1->estimated_num==num)
               {
                temp3=temp1;
                temp1=temp1->next;
                temp2->next=temp1;
                temp1->prev=temp2;
                counter--;
                delete temp3;
               }
           else
               {
                temp2=temp2->next;
                temp1=temp1->next;
               }
           }
           }
        else
            main_manu();
       }
    else
       {
          cout<<"Invalid input try again "<<endl;
          goto h;
       }
}
void delete_by_lifespan(int num)
{
cout<<"are you sure you want to delete (y/n)"<<endl;
    h:char h=checkchar();
    if (h=='y' || h=='Y' || h=='N' || h=='n')
       {
         if (h=='y' || h=='Y' )
            {
          temp2=start;
          temp1=temp2->next;
          while(temp1->next!=NULL)
           {
           if(temp1->life_span==num)
               {
                temp3=temp1;
                temp1=temp1->next;
                temp2->next=temp1;
                temp1->prev=temp2;
                counter--;
                delete temp3;
               }
           else
               {
                temp2=temp2->next;
                temp1=temp1->next;
               }
           }
           }
        else
            main_manu();
       }
    else
       {
          cout<<"Invalid input try again "<<endl;
          goto h;
       }
}
void delete_at_end()
{
   system("CLS");
 if(start==NULL && end == NULL)
      {
          cout<<"no animal to delete"<<endl;
      }
       else if(start == end)
    {
        start=NULL;
        end=NULL;
        counter--;
        cout<<"deleted successfully"<<endl;
        system("pause");
        main_manu();
    }
     else
     {
         temp1=end;
         end=end->prev;
         temp1->prev=NULL;
         end->next=NULL;
         delete temp1;
         counter--;
     }
	  system("pause");
	  main_manu();
}

void delete_at_beginning()
{
    system("CLS");
	if (start==NULL && end==NULL)
	    {
		  cout<<"There is no file to delete";
     	}
    else if(start == end)
    {
        start=NULL;
        end=NULL;
        counter--;
        cout<<"deleted successfully"<<endl;
        system("pause");
        main_manu();
    }
	else
	  {
	    temp1=start;
	  	start=start->next;
	  	start->prev=NULL;
	  	temp1->next=NULL;
	  	counter--;
	  	delete temp1;
	  }
	  system("pause");
	  main_manu();
}
void delete_at_middle()
{
     if (counter > 0 && counter <= 2)
                {
                    cout<<"   Impossible , There is no enough file to delete ,"<<endl;
                    cout<<"   so you should delete the first or the last animal."<<endl;
                    cout<<"   In order to delete choose from the alternatives "<<endl<<endl;
                    cout<<"      1 . Delete the first file"<<endl;
                    cout<<"      2 . Delete the last file "<<endl<<endl;
                    t:
                    cout<<"\t\t\t >> ";
                    int n=check();
                    switch(n)
                    {
                    case 1:
                        delete_at_beginning();
                        break;
                    case 2:
                        delete_at_end();
                        break;
                    default :
                        {
                        cout<<"Incorrect value ,try again"<<endl;
                        goto t;}
                            break;
                    }
                 }
         else {
                    cout<<"\t\t1:Delete by by name"<<endl;
                    cout<<"\t\t2:Delete by by name of species"<<endl;
					cout<<"\t\t3:Delete by by scientific name"<<endl;
                    cout<<"\t\t4:Delete by by name of genus"<<endl;
					cout<<"\t\t5:Delete by by name of movement system"<<endl;
					cout<<"\t\t6:Delete by by feeding system"<<endl;
					cout<<"\t\t7:Delete by by life span"<<endl;
					cout<<"\t\t8:Delete by by endemic"<<endl;
					cout<<"\t\t9:Delete by by estimated number"<<endl;
					cout<<"\t\t10:Delete at specific position"<<endl;
					cout<<"\t\t11:Return to main menu"<<endl;
         cout<<"\n\tNotice : choices from 1-3 and 10 delete single animal record and others delete 1 or more record"<<endl;
                     p:int h=check();
                     if (h>11 || h<0)
                     {
                         cout<<"Invalid input"<<endl;
                         goto p;
                     }
                     switch(h)
                     { system("CLS");
                         char name[20];
                     case 1:{
                         cout<<"Enter the name of the animal : ";
                         cin>>name;
                         search(name);
                         delete_single(name);
                        }
                        break;
                     case 2:
                         {
                         cout<<"Enter the species name of the animal : ";
                         cin>>name;
                         search_species(name);
                         delete_single(name);
                         }
                        break;
                     case 3:
                         {
                         cout<<"Enter the name of the animal : ";
                         cin>>name;
                         search_scientific(name);
                         delete_single(name);
                         }
                        break;
                    case 4:
                         {
                         cout<<"Enter the genus name of the animal : ";
                         cin>>name;
                         search_genus(name);
                         delete_by_genus(name);
                         }
                        break;
                    case 5:
                         {
                         cout<<"Enter the movement system of the animal : ";
                         cin>>name;
                         search_movement(name);
                         delete_by_movement(name);
                         }
                        break;
                    case 6:
                         {
                         cout<<"Enter feeding system of the animal : ";
                         cin>>name;
                         search_feeding(name);
                         delete_by_feeding(name);
                         }
                        break;
                    case 7:
                         {
                         cout<<"Enter the life span of the animal : ";
                         int j=check();
                         search_lifespan(j);
                         delete_by_lifespan(j);
                         }
                        break;
                    case 8:
                         {
                         cout<<"Enter your choice (yes/no) : ";
                         cin>>name;
                         search_endemic(name);
                         delete_by_endemic(name);
                         }
                        break;
                    case 9:
                         {
                         cout<<"Enter the estimated number of the animals : ";
                         int j=check();
                         search_estimated(j);
                         delete_by_estimated(j);
                         }
                        break;
                    case 10:
                         {
                         cout<<"Enter the number of record you want to delete : ";
                         int j=check();
                         delete_nth_pos(j);
                         }
                        break;
                    case 11:
                        main_manu();
                        break;
                     }

}}

void delete_nth_pos(int k)
{
	int i=1;
	temp1=start;
	while (temp1!=NULL && i!=k)
	{
		i++;
		temp1=temp1->next;
	}
	if (temp1==NULL && i!=k)
         {
         	cout<<"There are only "<<(i-1)<<" records "<<endl;
		 }
    else if (temp1->next==NULL)
    {
    	delete_at_end();

	}
	else if(i==1)
	{
		delete_at_beginning();
	}
	else
	{   show();
		temp2=temp1->prev;
		temp3=temp1;
		temp1=temp1->next;
		temp1->prev=temp2;
		temp2->next=temp1;
		temp3->next=NULL;
		temp3->prev=NULL;
		delete temp3;
		cout<<"Deleted successfully"<<endl;
	}
	system("pause");
	main_manu();
}

void displayAll()
{
    system("CLS");
    animal *temp3=new animal;
    int i;
    temp3=start;
    if(start==NULL && end == NULL)
    cout<<"no record to display"<<endl;
    else
    { int i=4;
       gotoxy(2,i);cout<<"name";gotoxy(17,i);cout<<"Species";gotoxy(32,i);cout<<"Genus";gotoxy(45,i);cout<<"scientific name";gotoxy(65,i);cout<<"movement system";gotoxy(83,i);cout<<"feeding system";gotoxy(99,i);cout<<"estimated number";gotoxy(117,i);cout<<"life span";gotoxy(128,i);cout<<"Endemic"<<endl;
       for (int i=2;i<=128;i++)
       {
           cout<<"-";
       }
        i=7;
    while(temp3!=NULL)
      {

          gotoxy(2,i);cout<<temp3->name;gotoxy(17,i);cout<<temp3->name_of_species;gotoxy(32,i);cout<<temp3->name_of_genus;gotoxy(45,i);cout<<temp3->scentific_name;gotoxy(65,i);cout<<temp3->movement_system;gotoxy(83,i);cout<<temp3->feeding_system;gotoxy(99,i);cout<<temp3->estimated_num;gotoxy(117,i);cout<<temp3->life_span;gotoxy(128,i);cout<<temp3->isEndemic<<endl;
           i+=2;
           temp3=temp3->next;}
    }
    cout<<counter;
   	}

void displayback()
{
    system("CLS");
    temp3=end;
    if(start==NULL && end == NULL)
        cout<<"no record to display"<<endl;

    else
    {
      int i=4;
       gotoxy(2,i);cout<<"name";gotoxy(17,i);cout<<"Species";gotoxy(32,i);cout<<"Genus";gotoxy(45,i);cout<<"scientific name";gotoxy(65,i);cout<<"movement system";gotoxy(83,i);cout<<"feeding system";gotoxy(99,i);cout<<"estimated number";gotoxy(117,i);cout<<"life span";gotoxy(128,i);cout<<"Endemic"<<endl;
       for (int i=2;i<=128;i++)
       {
           cout<<"-";
       }
       i=7;
    while(temp3!=NULL)
      {

          gotoxy(2,i);cout<<temp3->name;gotoxy(17,i);cout<<temp3->name_of_species;gotoxy(32,i);cout<<temp3->name_of_genus;gotoxy(45,i);cout<<temp3->scentific_name;gotoxy(65,i);cout<<temp3->movement_system;gotoxy(83,i);cout<<temp3->feeding_system;gotoxy(99,i);cout<<temp3->estimated_num;gotoxy(117,i);cout<<temp3->life_span;gotoxy(128,i);cout<<temp3->isEndemic<<endl;
           i+=2;
           temp3=temp3->prev;}
    }
}
void search_max_lifespan()
{
    if(start==NULL)
    {
        cout<<endl<<"The List Is Empty"<<endl;
    }
    else
    {
        animal *max=start;
        max->life_span=start->life_span;

        int c=0;

        for(temp1=start; temp1!=NULL; temp1=temp1->next)
        {
            if(temp1->life_span>max->life_span)
            {
                max->life_span=temp1->life_span;
                strcpy(max->name,temp1->name);
                strcpy(max->name_of_species,temp1->name_of_species);
                strcpy(max->name_of_genus,temp1->name_of_genus);
                strcpy(max->scentific_name,temp1->scentific_name);
                strcpy(max->movement_system,temp1->movement_system);
                strcpy(max->feeding_system,temp1->feeding_system);
                strcpy(max->isEndemic,temp1->isEndemic);
                max->life_span=temp1->life_span;
                max->estimated_num=temp1->estimated_num;
                c=1;
            }

        }
        temp1=max;
show();
    }
    cout<<endl<<"Searching sucessfully"<<endl;
    system("pause");
    main_manu();
}

void search_max_estimated()
{
    if(start==NULL)
    {
        cout<<endl<<"The List Is Empty"<<endl;
    }
    else
    {
        animal *max=start;
        max->estimated_num=start->estimated_num;

        int c=0;

        for(temp1=start; temp1!=NULL; temp1=temp1->next)
        {
            if(temp1->estimated_num > max->estimated_num)
            {
                max->life_span=temp1->life_span;
                strcpy(max->name,temp1->name);
                strcpy(max->name_of_species,temp1->name_of_species);
                strcpy(max->name_of_genus,temp1->name_of_genus);
                strcpy(max->scentific_name,temp1->scentific_name);
                strcpy(max->movement_system,temp1->movement_system);
                strcpy(max->feeding_system,temp1->feeding_system);
                strcpy(max->isEndemic,temp1->isEndemic);
                max->estimated_num=temp1->estimated_num; c=1;
            }

        }
        temp1=max;
        show();
    }
    cout<<endl<<"Searching sucessfully"<<endl;
    system("pause");
    main_manu();
}
void search_minimum_lifespan()
{
  if(start==NULL)
    {
        cout<<endl<<"The List Is Empty"<<endl;
    }
    else
    {
        animal *min=start;
        min->life_span=start->life_span;

        int c=0;

        for(temp1=start; temp1!=NULL; temp1=temp1->next)
        {
            if(temp1->life_span<min->life_span)
            {
                min->estimated_num=temp1->estimated_num;
                strcpy(min->name,temp1->name);
                strcpy(min->name_of_species,temp1->name_of_species);
                strcpy(min->name_of_genus,temp1->name_of_genus);
                strcpy(min->scentific_name,temp1->scentific_name);
                strcpy(min->movement_system,temp1->movement_system);
                strcpy(min->feeding_system,temp1->feeding_system);
                strcpy(min->isEndemic,temp1->isEndemic);
                min->life_span=temp1->life_span;
                c=1;
            }

        }   int i=4;
            gotoxy(25,i+=2);cout <<"Name : "<<min->name<<endl;
            gotoxy(25,i+=2);cout <<"Name_of_species : "<<min->name_of_species<<endl;
            gotoxy(25,i+=2);cout <<"Name_of_genus : "<<min->name_of_genus<<endl;
            gotoxy(25,i+=2);cout <<"Scientific name : "<<min->scentific_name<<endl;
            gotoxy(25,i+=2);cout <<"movement system : "<<min->movement_system<<endl;
            gotoxy(25,i+=2);cout <<"Feeding_system : " <<min->feeding_system<<endl;
            gotoxy(25,i+=2);cout <<"Estimated number : "<<min->estimated_num<<endl;
            gotoxy(25,i+=2);cout <<"Life span : "<<min->life_span<<endl<<endl;
    }
    cout<<endl<<"Searching sucessfully"<<endl;
    system("pause");
    main_manu();
}
void search_minimum_estimated()
{
  if(start==NULL)
    {
        cout<<endl<<"The List Is Empty"<<endl;
    }
    else
    {
        animal *min=start;
        min->estimated_num=start->estimated_num;

        int c=0;

        for(temp1=start; temp1!=NULL; temp1=temp1->next)
        {
            if(temp1->estimated_num<min->estimated_num)
            {
                min->estimated_num=temp1->estimated_num;
                strcpy(min->name,temp1->name);
                strcpy(min->name_of_species,temp1->name_of_species);
                strcpy(min->name_of_genus,temp1->name_of_genus);
                strcpy(min->scentific_name,temp1->scentific_name);
                strcpy(min->movement_system,temp1->movement_system);
                strcpy(min->feeding_system,temp1->feeding_system);
                strcpy(min->isEndemic,temp1->isEndemic);
                min->life_span=temp1->life_span;
                c=1;
            }

        }
            int i=4;
            gotoxy(25,i+=2);cout <<"Name : "<<min->name<<endl;
            gotoxy(25,i+=2);cout <<"Name_of_species : "<<min->name_of_species<<endl;
            gotoxy(25,i+=2);cout <<"Name_of_genus : "<<min->name_of_genus<<endl;
            gotoxy(25,i+=2);cout <<"Scientific name : "<<min->scentific_name<<endl;
            gotoxy(25,i+=2);cout <<"movement system : "<<min->movement_system<<endl;
            gotoxy(25,i+=2);cout <<"Feeding_system : " <<min->feeding_system<<endl;
            gotoxy(25,i+=2);cout <<"Estimated number : "<<min->estimated_num<<endl;
            gotoxy(25,i+=2);cout <<"Life span : "<<min->life_span<<endl<<endl;
    }
    cout<<endl<<"Searching sucessfully"<<endl;
    system("pause");
    main_manu();
}
void top_ten_by_estimated()
 {   system("CLS");
     sort_estimated();
     int i=0;
     temp1=end;
     cout<<"/t Top 10 animals live in the park by their number"<<endl;
     while(temp1!=NULL && i<=10)
     {
         cout<<"\n-------------------------------------------------"<<endl;
         show();
         cout<<"-------------------------------------------------"<<endl;
         temp1=temp1->prev;i++;
     }
 }

  void top_ten_by_lifespan()
 {   system("CLS");
     sort_lifespan();
     int i=0;
     temp1=end;
    cout<<"/t Top 10 animals live in the park by their life span"<<endl;
     while(temp1!=NULL && i<=10)
     {
         cout<<"\n-------------------------------------------------"<<endl;
         show();
         cout<<"-------------------------------------------------"<<endl;
         temp1=temp1->prev;i++;
     }
 }

 void top_ten_by_name()
 {   system("CLS");
     sort_by_name;
     int i=0;
     temp1=start;
     cout<<"\t The first 10 animal by their name alphabetical order"<<endl;
     while(temp1!=NULL && i<=10)
     {
         cout<<"\n-------------------------------------------------"<<endl;
         show();
         cout<<"-------------------------------------------------"<<endl;
         temp1=temp1->next;i++;
     }
 }
 void top_ten_by_species()
 {   system("CLS");
     sort_by_species();
     int i=0;
     temp1=start;
     cout<<"\t The first 10 animals by their name of species"<<endl;
     while(temp1!=NULL && i<=10)
     {
         cout<<"\n-------------------------------------------------"<<endl;
         show();
         cout<<"-------------------------------------------------"<<endl;
         temp1=temp1->next;i++;
     }
 }
 void average_lifespan()
{
    temp1=start;
    int i=0,sum=0;
    double average;
    while(temp1!=NULL)
    {
        sum+=temp1->life_span;
        i++;temp1=temp1->next;
    }
    average=sum/i;
    cout<<"The average life span of the animals in the park is "<<average <<" "<<endl;
}
void display()
{
    system("CLS");int i=6;
    gotoxy(25,i);cout<<"1. Display all records forward"<<endl;
    gotoxy(25,i+=2);cout<<"2. Display all records backward"<<endl;
    gotoxy(25,i+=2);cout<<"3. The animal with maximum number"<<endl;
    gotoxy(25,i+=2);cout<<"4. The animal with minimum number"<<endl;
    gotoxy(25,i+=2);cout<<"5. The animal with maximum life span"<<endl;
    gotoxy(25,i+=2);cout<<"6. The animal with minimum life span"<<endl;
    gotoxy(25,i+=2);cout<<"7. Top tens "<<endl;
    gotoxy(25,i+=2);cout<<"8. Average life span of the animals in the park"<<endl;
    gotoxy(25,i+=2);cout<<"9. Return to main menu"<<endl;
    gotoxy(28,i+=2);cout<<" Enter your choice : ";
    i:int t=check();
    if (t>9 || t<0)
    {   gotoxy(25,i+=2);
        cout<<"Invalid input try again"<<endl;
        goto i;
    }
    switch(t)
      {
      case 1:
        displayAll();
        break;
      case 2:
        displayback();
        break;
      case 3:
        search_max_estimated();
        break;
      case 4:
        search_minimum_estimated();
        break;
      case 5:
        search_max_lifespan();
        break;
      case 6:
        search_minimum_lifespan();
        break;
      case 7:
        {  system("CLS");int i=6;
            gotoxy(25,i);cout<<" 1. Top 10 by estimated number"<<endl;
            gotoxy(25,i+=2);cout<<" 2. Top 10 by name alphabetical order"<<endl;
            gotoxy(25,i+=2);cout<<" 3. Top 10 by name of species"<<endl;
            gotoxy(25,i+=2);cout<<" 4. Top 10 by life span"<<endl;
            gotoxy(25,i+=2);cout<<" 5. Return to main menu"<<endl;
            gotoxy(28,i+=2);cout<<"Enter your choice : ";
            m:int y=check();
            if(y<0 || y>5)
            {
                cout<<"Invalid input try again "<<endl;
                goto m;
            }
            switch(y)
            {
            case 1:
                top_ten_by_estimated();
                break;
            case 2:
                top_ten_by_name();
                break;
            case 3:
                top_ten_by_species();
                break;
            case 4:
                top_ten_by_lifespan();
                break;
            case 5:
                main_manu();
                break;
            }
        }
            case 8:
                average_lifespan();
                break;
            case 9:
                main_manu();
                break;

      }
system("pause");
main_manu();
}
void update_estamated_num(char name[])
{
    system("CLS");
cout<<"values before modify"<<endl;
 search(name);
 temp1=start;
   while (temp1!=NULL)
     {
    if (strcmpi(name,temp1->name)==0)
        {
         cout<<"ENTER THE UPDATED INFORMATION"<<endl;
         cout<<"Enter recent estimated number of "<<temp1->name<<" : ";
         temp1->estimated_num=check();
         cout<<"\n values after modify"<<endl;
         show();
         system("pause");
         main_manu();
       }
       temp1=temp1->next;
     }
system("pause");
main_manu();
}

void update_genus(char name[])
{
    system("CLS");
    int check=0;
cout<<"values before modify"<<endl;
search(name);
temp1=start;
   while (temp1!=NULL)
     {
    if (strcmpi(name,temp1->name)==0)
        {
         cout<<"ENTER THE UPDATED INFORMATION"<<endl;
         cout<<"Enter updated name of genus : ";
         cin>>temp1->name_of_genus;
         strcpy(temp1->scentific_name,strcat(temp1->name_of_genus,temp1->name_of_species));
         cout<<"\n values after modify"<<endl;
         show();
         system("pause");
         main_manu();
       }
       temp1=temp1->next;
     }
system("pause");
main_manu();
}
void update_endmic(char name[])
{
     system("CLS");
cout<<"values before modify"<<endl;
search(name);
    temp1=start;
   while (temp1!=NULL)
     {
    if (strcmpi(name,temp1->name)==0)
        {
         cout<<"ENTER THE UPDATED INFORMATION"<<endl;
         cout<<"Is "<<temp1->name<<" endemic?  ";
            cout<<"1. YES     2. NO"<<endl;
           char yes[4]="YES";
           char no[3]="NO";
           v:
           int e=check();
           switch(e)
           {
           case 1:
            strcpy(temp1->isEndemic,yes);
            break;
           case 2:
            strcpy(temp1->isEndemic,no);
            break;
           default:
            {cout<<"Invalid input retry again"<<endl;
            goto v;}
           }
         cout<<"\n values after modify"<<endl;
         show();
         system("pause");
         main_manu();
       }
       temp1=temp1->next;
     }
system("pause");
main_manu();
}

void update_life_span(char name[])
{
    system("CLS");
     cout<<"values before modify"<<endl;
      search(name);
    temp1=start;
      while (temp1!=NULL)
      {
          if(strcmpi(temp1->name,name)==0)
        {
         cout<<"ENTER THE UPDATED INFORMATION"<<endl;
         cout<<"Enter recent Life span : ";
         temp1->life_span=check();
         cout<<"\n values after modify"<<endl;
           show();
         system("pause");
         main_manu();
        }
       temp1=temp1->next;
    }
system("pause");
main_manu();
}

void update_all(char name[])
{
    system("CLS");
     cout<<"values before modify"<<endl;
      search(name);
    temp1=start;
      while (temp1!=NULL)
      {
          if(strcmpi(temp1->name,name)==0)
        {int i=4;
         gotoxy(27,i+=2);cout<<"ENTER THE UPDATED INFORMATION OF "<<(temp1->name)<<endl;
         gotoxy(25,i+=2);cout<<"Enter recent life span : ";
         temp1->life_span=check();
         gotoxy(25,i+=2);cout<<"Enter recent estimated number of "<<temp1->name<<" : ";
         temp1->estimated_num=check();
         gotoxy(25,i+=2);cout<<"\nIs "<<temp1->name<<" endemic?  ";
         cout<<"1. YES     2. NO"<<endl;
           char yes[4]="YES";
           char no[3]="NO";
           v:
           gotoxy(25,i+=2);int e=check();
           switch(e)
           {
           case 1:
            strcpy(temp1->isEndemic,yes);
            break;
           case 2:
            strcpy(temp1->isEndemic,no);
            break;
           default:
            {cout<<"Invalid input retry again"<<endl;
            goto v;}
         gotoxy(25,i+=2);cout<<"\nEnter updated name of genus : ";
         cin>>temp1->name_of_genus;cout<<endl;
         strcpy(temp1->scentific_name,strcat(temp1->name_of_genus,temp1->name_of_species));
         gotoxy(25,i+=2);cout<<"Updated successfully"<<endl;
         gotoxy(25,i+=2);cout<<"\n values after modify"<<endl;
         show();
         system("pause");
         main_manu();
        }
       temp1=temp1->next;
    }
}}
void sort_by_name()
{
 for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
 if ((strcmpi(temp2->prev->name,temp2->name))>0)
            {
             swap();
            }}}
}

void sort_by_species()
{
 for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
 if ((strcmpi(temp2->prev->name_of_species,temp2->name_of_species))>0)
            {
             swap();
            }}}
}

void sort_by_genus()
{
 for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
 if ((strcmpi(temp2->prev->name_of_genus,temp2->name_of_genus))>0)
            {
             swap();
            }}}
}

void sort_by_movement()
{
 for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
 if ((strcmpi(temp2->prev->movement_system,temp2->movement_system))>0)
            {
             swap();
            }}}
}

void sort_by_feeding()
{
 for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
 if ((strcmpi(temp2->prev->feeding_system,temp2->feeding_system))>0)
            {
             swap();
            }}}
}

void sort_scentificname()
{
 for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
 if ((strcmpi(temp2->prev->scentific_name,temp2->scentific_name))>0)
            {
             swap();
            }}}
}
 void sort_estimated()
 {
  for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
    if (temp2->prev->estimated_num>temp2->estimated_num)
            {
             swap();
            }}}
 }

 void sort_lifespan()
 {
  for (temp1=start->next;temp1!=end->next;temp1=temp1->next)
     {
       for (temp2=temp1;temp2!=start;temp2=temp2->prev)
{
    if (temp2->prev->life_span>temp2->life_span)
            {
             swap();
            }}}
 }

 void sort()
 {     if (start ==NULL && end == NULL)
 {   system("CLS");
     cout<<"There is no record to sort"<<endl;
     system("pause");
     main_manu();
 }
     system("CLS");int i=4;
        gotoxy(25,i+=2);cout<<" 1. sort by name"<<endl;
        gotoxy(25,i+=2);cout<<" 2. sort by feeding system"<<endl;
        gotoxy(25,i+=2);cout<<" 3. sort by name of genus "<<endl;
        gotoxy(25,i+=2);cout<<" 4. sort by movement system "<<endl;
        gotoxy(25,i+=2);cout<<" 5. sort by name of species"<<endl;
        gotoxy(25,i+=2);cout<<" 6. sort by estimated number "<<endl;
        gotoxy(25,i+=2);cout<<" 7. sort by life span "<<endl;
        gotoxy(25,i+=2);cout<<" 8. sort by scientific name "<<endl;
        gotoxy(25,i+=2);cout<<" 9. Return to main menu"<<endl;
        o:gotoxy(28,i+=2);cout<<"enter your choice : ";
            int y=check();
             if (y<0 || y>9)
             {
                 cout<<"you must enter a number (1-9)"<<endl;
                 goto o;
             }
            switch(y)
            {
            case 1:
                sort_by_name();
                break;
            case 2:
                sort_by_feeding();
                break;
            case 3:
                sort_by_genus();
                break;
            case 4:
                sort_by_movement();
                break;
            case 5:
                sort_by_species();
                break;
            case 6:
                sort_estimated();
                break;
            case 7:
                sort_lifespan();
                break;
            case 8:
                sort_scentificname();
                break;
            case 9:
                main_manu();
                break;
            }
 }
void count_occurence_by_genus()
{
    char name[20];
    int count = 0;
    int check=-1;
    cout<<"Enter the name of genus : ";
    cin>>name;
    temp1=start;
    while (temp1 != NULL)
    {
        if (strcmp(temp1->name_of_genus,name)==0)
            count++;check=1;
        temp1=temp1->next;
    }
    cout<<"The genus name you inserted has occurred "<<count<<" times";
if(check==-1)
{
    cout<<"Result not found"<<endl;
}
}

void count_occurence_by_movement()
{
    char name[20];
    int count = 0,check=-1;
    cout<<"Enter movement system : ";
    cin>>name;
    temp1=start;
    while (temp1 != NULL)
    {
        if (strcmp(temp1->movement_system,name)==0)
            count++;check=1;
        temp1=temp1->next;
    }
    cout<<"The movement system you inserted has occurred "<<count<<" times";
if(check==-1)
{
    cout<<"Result not found"<<endl;
}
}

void count_occurence_by_feeding()
{
    char name[20];
    int count = 0,check=-1;
    cout<<"Enter feeding system : ";
    cin>>name;
    temp1=start;
    while (temp1 != NULL)
    {
        if (strcmp(temp1->feeding_system,name)==0)
            count++;check=1;
        temp1=temp1->next;
    }
    cout<<"The feeding system you inserted has occurred "<<count<<" times";
if(check==-1)
{
    cout<<"Result not found"<<endl;
}
}

void count_occurence_by_lifespan()
{
    int count = 0,che=-1;
    cout<<"Enter the life span : ";
    int k=check();
    temp1=start;
    while (temp1 != NULL)
    {
        if (temp1->life_span==k)
            count++;
            che=1;
        temp1=temp1->next;
    }
    cout<<"The life span you inserted has occured "<<count<<" times";
if(che==-1)
{
    cout<<"Result not found"<<endl;
}
}
void count_occurence_by_estimated()
{
    int count = 0,che=-1;
    cout<<"Enter the estimated number : ";
    int k=check();
    temp1=start;
    while (temp1 != NULL)
    {
        if (temp1->estimated_num==k)
            count++;che=1;
        temp1=temp1->next;
    }
    cout<<"The estimated number you inserted has occured "<<count<<" times";
if(che==-1)
{
    cout<<"Result not found"<<endl;
}
}

void count_occurence_by_endemic()
{
    char name[5];
    int count = 0,check=-1;
    cout<<"Enter \"yes\" for endemic and \"no\" for not endemic : ";
    cin>>name;
    temp1=start;
    while (temp1 != NULL)
    {
        if (strcmp(temp1->isEndemic,name)==0)
            count++;check=1;
        temp1=temp1->next;
    }
    cout<<"The serial no you inserted has occured "<<count<<" times";
if(check==-1)
{
    cout<<"Result not found"<<endl;
}
}

void count_occurence()
{      system("CLS");
       if (start==NULL && end==NULL)
       {
           cout<<"There is no record to display"<<endl;
           system("pause");
           main_manu();
       }
        system("CLS");int i=4;
        gotoxy(25,i+=2);cout<<" What do You Want"<<endl;
        gotoxy(25,i+=2);cout<<"1. count occurrence by name of genus"<<endl;
        gotoxy(25,i+=2);cout<<"2. count occurrence by name of movement system"<<endl;
        gotoxy(25,i+=2);cout<<"3. count occurrence by feeding system"<<endl;
        gotoxy(25,i+=2);cout<<"4. count occurrence by life span"<<endl;
        gotoxy(25,i+=2);cout<<"5. count occurrence by endemic"<<endl;
        gotoxy(25,i+=2);cout<<"6. count occurrence by estimated number"<<endl;
        gotoxy(25,i+=2);cout<<"7. Return To main menu"<<endl;
        j:gotoxy(28,i+=2);cout<<" Enter your option : ";
         int choice=check();
        switch(choice)
        {
        case 1:
           count_occurence_by_genus();
            break;
        case 2:
            count_occurence_by_movement();
            break;
        case 3:
            count_occurence_by_feeding();
            break;
        case 4:
            count_occurence_by_lifespan();
            break;
        case 5:
            count_occurence_by_endemic();
            break;
        case 6:
            count_occurence_by_estimated();
            break;
        case 7:
            main_manu();
            break;
        default:
            cout<<"ENTER AN APPPROPRIATE CHOICE"<<endl;
            goto j;
        }
cout<<endl;
system("pause");
main_manu();
}
void intro ()
{
system("CLS");
cout<<"\n\n\t\t\t---------------------------------------";
	  cout<<"\n\t\t\t-                                     -    ";
	  cout<<"\n\t\t\t-              L      C               -    ";
	  cout<<"\n\t\t\t-         L                O          -    ";
	  cout<<"\n\t\t\t-      E                      M       -    ";
	  cout<<"\n\t\t\t-    W                            E   -    ";
	  cout<<"\n\t\t\t-                 TO                  -    ";
	  cout<<"\n\t\t\t---------------------------------------     \n\n";
     cout<<"******************************************************************************** "<<endl;
gotoxy( 20 , 13 );
cout <<"SEMEN MOUNTAIN NATIONAL PARK ANIMAL SPECIES " ;
gotoxy( 35 , 15 );
cout <<"RECORD MANAGEMENT" ;
gotoxy( 40 , 17 );
cout <<"SYSTEM" ;
getch();
}

void main_manu()
{   system("CLS");
    int i=4;
    gotoxy(25,i+=2);cout<<"What do you want to do ?"<<endl;
    gotoxy(25,i+=1);cout<<"--------------------------"<<endl;
    gotoxy(25,i+=2);cout<<"1 . Add data to the list "<<endl;
    gotoxy(25,i+=2);cout<<"2 . Display to the list "<<endl;
    gotoxy(25,i+=2);cout<<"3 . Delete data from the list"<<endl;
    gotoxy(25,i+=2);cout<<"4 . Search a data from the list "<<endl;
    gotoxy(25,i+=2);cout<<"5 . Update data to the list "<<endl;
    gotoxy(25,i+=2);cout<<"6 . sort data "<<endl;
    gotoxy(25,i+=2);cout<<"7 . count number of occurrence "<<endl;
    gotoxy(25,i+=2);cout<<"8 . Quit"<<endl;
    n:gotoxy(28,i+=2);cout<<"Enter your choice : ";
    int choice=check();
    if(choice<0 || choice>8)
    {
        cout<<"you must enter a number (1-8)"<<endl;
        goto n;
    }
    system("CLS");
    switch(choice)
    {
        case 1:
            {
                system("CLS");int i=6;
                gotoxy(25,i);cout<<"Where do you want to add the data ?"<<endl<<endl;
                gotoxy(25,i+=2);cout<<"1. At the beginning" <<endl;
                gotoxy(25,i+=2);cout<<"2. At the middle" <<endl;
                gotoxy(25,i+=2);cout<<"3. At the end" <<endl;
                gotoxy(25,i+=2);cout<<"4. Return to main menu" <<endl;
                gotoxy(28,i+=2);cout<<">>";
                f:int c=check();
                switch(c)
                {
               case 1:
                insert_at_beginning();
                break;
               case 2:
                insert_at_middle();
                break;
               case 3:
                insert_at_end();
                break;
               case 4:
                main_manu();
               default:
                {
                    cout<<"Invalid input try again"<<endl;
                    goto f;
                }
                }
                }

             break;
        case 2:
            {
            system("CLS");
            display();
            system("pause");
            main_manu();
            }
            break;
        case 3:{
          if(start==NULL && end==NULL) {
             cout<<"There is no file to delete"<<endl;
                        system("pause");
                        main_manu();
           }
           else
           {
               system("CLS");
             cout<<"Where do you want to delete the data ?"<<endl<<endl;
                cout<<"1. At the beginning" <<endl;
                cout<<"2. At the middle" <<endl;
                cout<<"3. At the end" <<endl;
                u:int c=check();;

                    if (c>3 || c<0)
                    {
                        cout<<"you must enter a number (1-3)"<<endl;
                        goto u;
                    }
                switch(c)
                {
               case 1:{
                   temp1=start;
                   show();
                    cout<<"are you sure you want to delete (y/n)"<<endl;
                    h:char h=checkchar();
                    if (h=='y' || h=='Y' || h=='N' || h=='n')
                    {
                      if (h=='y' || h=='Y' )
                     {
                       delete_at_beginning();
                        }
                       else
                         main_manu();
                    }
                   else
                       {
                          cout<<"Invalid input try again "<<endl;
                          goto h;
                       }
                       }
                break;
               case 2:
                {
                delete_at_middle();
                main_manu();}
                break;
               case 3:{
                   temp1=start;
                   show();
                    cout<<"are you sure you want to delete (y/n)"<<endl;
                    k:char h=checkchar();
                    if (h=='y' || h=='Y' || h=='N' || h=='n')
                    {
                      if (h=='y' || h=='Y' )
                     {
                       delete_at_beginning();
                        }
                       else
                         main_manu();
                    }
                   else
                       {
                          cout<<"Invalid input try again "<<endl;
                          goto k;
                       }
                    }
                break;
                }
                }}
               break;
        case 4:
           {   system("CLS");
               searc();
               system("pause");
               main_manu();
           }
                break;
        case 5:
           {
            system("CLS");
            char name[15];
            if (start==NULL && end==NULL)
           {
           cout<<"There is no file to update"<<endl;
           system("pause");
            main_manu();
            }
            else{int i=6;
                gotoxy(25,i);cout<<" 1. update life span of the animal"<<endl;
                gotoxy(25,i+=2);cout<<" 2. update estimated number of the animal"<<endl;
                gotoxy(25,i+=2);cout<<" 3. update name of genus "<<endl;
                gotoxy(25,i+=2);cout<<" 4. update endemic "<<endl;
                gotoxy(25,i+=2);cout<<" 5. update all "<<endl;
                gotoxy(25,i+=2);cout<<" 6. Return to main menu"<<endl;
            o: gotoxy(25,i+=2);cout<<"enter your choice : ";
            int y=check();

             if (y<0 || y>6)
             {
                 cout<<"you must enter a number (1-5)"<<endl;
                 goto o;
             }
              cout<<"Enter the name you want to modify : ";
              cin>>name;
            switch(y)
            {
                system("CLS");
            case 1:
                update_life_span(name);
                break;
            case 2:
                update_estamated_num(name);
                break;
            case 3:
                update_genus(name);
                break;
            case 4:
                update_endmic(name);
                break;
            case 5:
                update_all(name);
                break;
            case 6:
                exit(0);
                break;
            }
           }

         system("pause");
         main_manu(); }
            case 6:
                {
                   sort();
                   system("pause");
                   main_manu();
                }
            case 7:
                count_occurence();
                break;
            case 8:
                exit(0);
                break;
                       }
}

int main()
{
    system("color ");
    intro();
    main_manu();
}
