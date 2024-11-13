#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int disk_req[100], finish[100];
int choice, head, head1, distance, no_req,track;

void menu()
{
	printf("\n\n1. INPUT \n2. SSTF\n3. SCAN \n4. CLOOK \n5. EXIT");
	
	printf("\nEnter your choice: ");
	scanf("%d",&choice);
}

void input()
{
	printf("Enter no of tracks:\n");
	scanf("%d",&track);
	
	printf("Enter no of disk requests:\n");
	scanf("%d",&no_req);
	
	printf("Enter disk requests in fifo order:\n");
	for(int i=0; i<no_req; i++)
	{
		scanf("%d",&disk_req[i]);
	}
	
	printf("Enter current gead position\n");
	scanf("%d",&head1);
}

void sstf()
{
	int i, index, distace=0, min, diff;
	int pending=no_req;
	head=head1;
	
	
	
	for(i=0; i<no_req; i++)
	{
		finish[i]=0;
	}
	printf("%d -> ",head);
	
	while(pending>0)
	{
		min=9999;
		
		for(i=0; i<no_req; i++)
		{
			diff=abs(head-disk_req[i]);
			if(finish[i]==0 && diff<min)
			{
				min=diff;
				index=i;
			}
		}
		
		finish[index]=1;
		distance+=abs(head-disk_req[index]);
		head=disk_req[index];
		pending--;
		printf("%d -> ",head);
	}
	printf("END");
	printf("\nTotal distance traversed= %d", distance);
}

void sort()
{
	int i, j, temp;
	
	for(i=0; i<no_req; i++)
	{
		for(j=0; j<no_req; j++)
		{
			if(disk_req[i]<disk_req[j])
			{
				temp=disk_req[i];
				disk_req[i]=disk_req[j];
				disk_req[j]=temp;
			}
		}
	}
}

void scan()
{
	int i, index, distance=0, dir;
	head=head1;
	
	printf("\n 1. right\n 0. left");
	scanf("%d",&dir);
	
	sort();
	printf("\nSorted are:\n");
	for(i=0; i<no_req; i++)
	{
		printf("%d -> ",disk_req[i]);
	}
		
	i=0;
	
	while(head>disk_req[i])
	{
		index=i;
		i++;		
	}
	
	//printf("Index:",index);
	
	printf("\nIndex: ",index);
	printf("%d -> ",head);
	
	if(dir==1)
	{
		
		sort();
		for(i=index+1; i<no_req; i++)
		{
			printf("%d -> ",disk_req[i]);
			distance=abs(head-disk_req[i]);
			head=disk_req[i];
		}
		distance+=abs(head-(track-1));
		printf("%d ->",track-1);
		head=track-1;
		
		for(i=index; i>=0; i--)
		{
			printf("%d ->", disk_req[i]);
			distance+=abs(head-disk_req[i]);
			head=disk_req[i];
		}
	}
	else
	{
		sort();
		for(i=index; i>=0; i--)
		{
			printf("%d -> ", disk_req[i]);
			distance+=abs(head-disk_req[i]);
			head=disk_req[i];
			
		}
		distance+=abs(head-0);
		head=0;
		printf("0 -> ");
		
		for(i=index+1; i<no_req; i++)
		{
			printf("%d -> ",disk_req[i]);
			distance+=abs(head-disk_req[i]);
			head=disk_req[i];
		}
	}
	printf("End");
	printf("\n Total Distance Traversed: %d",distance);
}



void clook()
{
    int i, index, distance = 0, dir;
    head = head1;

    printf("\n 1. right\n 0. left");
    scanf("%d", &dir);

    sort();
    printf("\nSorted requests are:\n");
    for (i = 0; i < no_req; i++)
    {
        printf("%d  ", disk_req[i]);
    }

    i = 0;

    while (head > disk_req[i])
    {
        index = i;
        i++;
    }

    printf("\nIndex: %d -> %d -> ", index, head);
    printf("\n%d -> ",head);

    if (dir == 1)
    {
    	sort();
        for (i = index+1; i < no_req; i++)
        {
            printf("%d -> ", disk_req[i]);
            distance += abs(head - disk_req[i]);
            head = disk_req[i];
        }

        for (i = 0; i <= index; i++)
        {
            printf("%d ->", disk_req[i]);
            distance += abs(head - disk_req[i]);
            head = disk_req[i];
        }
    }
    else
    {
    	sort();
        for (i = index; i >= 0; i--)
        {
            printf("%d -> ", disk_req[i]);
            distance += abs(head - disk_req[i]);
            head = disk_req[i];
        }

        for (i = (no_req - 1); i > index; i--)
        {
            printf("%d -> ", disk_req[i]);
            distance += abs(head - disk_req[i]);
            head = disk_req[i];
        }
    }
    printf("End\n");
    printf("Total Distance Traversed: %d\n", distance);
}


int main()
{	
	
	while(1)
	{
		menu();
		switch(choice)
		{
			case 1: input();
				break;
				
			case 2: sstf();
				break;
				
			case 3: scan();
				break;
				
			case 4: clook();
				break;
				
			case 5: exit(0);
				break;
				
			default: printf("\n Enter valid choice");
				break;
		}
	}
	return 0;
	
	
}
