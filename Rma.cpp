#include<stdio.h>

int Ps[2][100],realTimecapacity[2][100],processesNumber=0,LCM;
void getsystem()
{
    FILE*Inputfile;
    Inputfile = fopen("sys.txt" , "r");
    while(!feof(Inputfile))
    {
        fscanf(Inputfile, "%d %d",&Ps[0][processesNumber],Ps[1][processesNumber]);
        processesNumber++;
    }
}

int lcm(int t[],int tSize)
{
    int initArray[100];
    for(int i=0;i<tSize;i++)
    {
        initArray[i] = t[i];
    }
    int index,m,x,b=1;
    while(b==1)
    {
        b=0;
        x=t[0];
        m=t[0];
        index=0;
        for(int i=0;i<tSize;i++)
        {
            if(x!=t[i])
            {
                b=1;
            }
            if(m>t[i])
            {
                m = t[i];
                index = i;
            }
        }
        if(b==1)
        {
            t[index]=t[index] + initArray[index];
        }
    }
    return t[0];
}

int priorProcess()
{
    //this functions returns the id of the prior process and returns -1 if no process is ready to execute
    int prior = -1;
    int lessperiode = LCM;
    for(int i =0 ;i<processesNumber ;i++)
    {
        if(realTimecapacity[0][i]!=0)
        {
            if(lessperiode > realTimecapacity[1][i])
            {
                prior = i;
                lessperiode=realTimecapacity[1][i];
            }
        }
    }
    return prior;
}
void schedule()
{
    int t , prior;
    // initialising real time/rest time
    for(int i=0;i<processesNumber;i++)
    {
        realTimecapacity[0][i]=Ps[0][i];
        realTimecapacity[1][i]=Ps[1][i];
    }
for(t=0;t<LCM;t++)
{
    //check schedulability necessary condition
    for(int i=0;i<processesNumber;i++)
    {
        if(realTimecapacity[0][i]>realTimecapacity[1][i])
        {
            printf("\n System is not scedulable beacause the task %d csn;t finish its job in its specified period",i);
            return;
        }
    }
    prior = priorProcess();
    if(prior != -1)
    {
        printf("\n(%d-%d)| t%d",t,t+1,prior);
    }
    else
    {
        printf("\n(%d-%d)",t,t+1);
    }
    realTimecapacity[0][prior]--;
    //update period time
    for(int i=0;i<processesNumber;i++)
    {
        realTimecapacity[1][i]--;
        if(realTimecapacity[1][i]==0)
        {
             realTimecapacity[0][i] = Ps[0][i];
             realTimecapacity[1][i] = Ps[1][i];
        }
    }
}
}
int main()
{
    int x,help[100];
    getsystem();
    //schedulability
    float sum=0;
    for(int i =0;i<processesNumber;i++)
    {
        sum = sum +((float)Ps[0][i]/(float)Ps[1][i]);
    }
    if(sum>1)
    {
        printf("\n The system is not schedulable");
    }
    else
    ///getting LCM
    {
        for(int i=-0;i<processesNumber;i++)
        {
            help[i] = Ps[1][i];    
        }
        LCM = lcm(help ,processesNumber);
        ///Start scheduling 
        schedule();
    }
    scanf("%d",&x);
}