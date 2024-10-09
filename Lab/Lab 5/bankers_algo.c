// using both algo, safety and resource allocation graph
// no of processes, resources, allocation matrix, request


#include <stdio.h>

int main()
{
    int process,resource,i,j,instant,k=0,count1=0,count2=0;
    printf("Enter number of processes: ");
    scanf("%d",&process);
    printf("ENter number of Resources: ");scanf("%d",&resource);
    int avail[resource],max[process][resource],allot[process][resource],need[process][resource],completed[process];
    for(i=0;i<process;i++)
    completed[i]=0;

    printf("Enter number of Instances\n");

    for(i=0;i<resource;i++)
    {
        scanf("%d",&instant);
        avail[i]=instant;
    }

    printf("ENter max number of instances of resources that a process need:\n ");
    for(i=0;i<process;i++)
    {
        printf("\nFor P[%d]",i);
        for(j=0;j<resource;j++)
        {
            scanf("%d",&instant);
            max[i][j]=instant;
        }
    }

    printf("\nENter no. of instances already allocated to process:\n");
    for(i=0;i<process;i++)
    {
        printf("\nFor P[%d]",i);
        for(j=0;j<resource;j++)
        {
            scanf("%d",&instant);
            allot[i][j]=instant;
            need[i][j]=max[i][j]-allot[i][j];
        }
    }

    printf("\nSafe Sequence is: ");
    while(count1!=process)
    {
        count2=count1;
        for(i=0;i<process;i++)
        {
            for(j=0;j<resource;j++)
            {
                if(need[i][j]<=avail[j])
                {
                    k++;
                }
            }
            if(k==resource && completed[i])
            {
                printf("p[%d]\t",i);
                completed[i]=1;
                for(j=0;j<resource;j++)
                {
                    avail[j]=avail[j]+allot[i][j];
                }
                count1++;
            }
            k=0;
        }
        if(count1==count2)
        {
            printf(".....Deadlock Occured");
            break;
        }
    }

    return 0;
}