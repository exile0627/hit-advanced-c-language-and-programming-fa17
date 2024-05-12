#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10 /*�ַ�����󳤶�*/
#define STU_NUM 30 /*����ѧ������*/
#define COURSE_NUM 6 /*���Ŀ��Կ�Ŀ��*/
#define EL 1e-4 /*�㹻С��һ��ֵ*/
typedef struct student
{
    long num; /*ÿ��ѧ����ѧ��*/
    char name[MAX_LEN]; /*ÿ��ѧ��������*/
    float score[COURSE_NUM]; /*ÿ��ѧ��COURSE_NUM�Ź��εĳɼ�*/
    float sum; /*ÿ��ѧ�����ܳɼ�*/
    float aver;/*ÿ��ѧ����ƽ���ɼ�*/
    float GPA; /*ÿ��ѧ����ѧ�ּ�*/
} STU;
int Menu(void);
void ReadScore(STU stu[],int n,int m);
void AverSumofEveryStudent(STU stu[],int n,int m);
void AverSumofEveryCourse(STU stu[],int n,int m);
void SortbyScore(STU stu[],int n,int m,int(*compare)(float a,float b));
int Ascending(float a,float b);
int Descending(float a,float b);
void AsSortbyNum(STU stu[],int n,int m);
void SortbyName(STU stu[],int n,int m);
void SearchbyNum(STU stu[],int n,int m);
void SearchbyName(STU stu[],int n,int m);
void StatisticAnalysis(STU stu[],int n,int m);
void PrintScore(STU stu[],int n,int m);
void WritetoFile(STU stu[],int n,int m);
void ReadfromFile(STU stu[],int *n,int *m);
void Swap(STU stu[],int k,int i);
void AvSumofEveryStudent(STU stu[],int n,int m);
void AvSumofEveryCourse(STU stu[],int n,int m);
void AddaStudent(STU stu[],int n,int m);
void DeleteaStudent(STU stu[],int n,int m);
void CaculateGPA(STU stu[],int n,int m);
void GenerateRecord(STU stu[],int n,int m);
int main()
{
    char ch,p[50];
    int n=0,m=0,i,ret1,ret2;
    STU stu[STU_NUM];
    for(i=0; i<3; i++)
    {
        printf("Input your password:");
        gets(p);
        if(strcmp(p,"12345678")==0)
        {
            while(1)
            {
                printf("Input student number(n<%d):",STU_NUM);
                ret1=scanf("%d",&n);
                printf("Input course number(m<=%d):",COURSE_NUM);
                ret2=scanf("%d",&m);
                if(n>=30||m>6||ret1!=1||ret2!=1||n<=0||m<=0)
                {
                    printf("Input beyond range!\n");
                    fflush(stdin);
                }
                else
                {
                    break;
                }
            } /*�ݴ���ֻҪ�û�����Ĳ���0-29�Լ�1-6������ʾ���󣬱������������ѭ��*/
            while(1)
            {
                ch=Menu();
                switch (ch)
                {
                case 1:
                    ReadScore(stu,n,m);
                    break;
                case 2:
                    AverSumofEveryCourse(stu,n,m);
                    break;
                case 3:
                    AverSumofEveryStudent(stu,n,m);
                    break;
                case 4:
                    SortbyScore(stu,n,m,Descending);
                    printf("\nSort in descending order by score:\n");
                    PrintScore(stu,n,m);
                    break;
                case 5:
                    SortbyScore(stu,n,m,Ascending);
                    printf("\nSort in ascending order by score:\n");
                    PrintScore(stu,n,m);
                    break;
                case 6:
                    AsSortbyNum(stu,n,m);
                    printf("\nSort in ascending order by number:\n");
                    PrintScore(stu,n,m);
                    break;
                case 7:
                    SortbyName(stu,n,m);
                    printf("\nSort in dictionary order by name:\n");
                    PrintScore(stu,n,m);
                    break;
                case 8:
                    SearchbyNum(stu,n,m);
                    break;
                case 9:
                    SearchbyName(stu,n,m);
                    break;
                case 10:
                    StatisticAnalysis(stu,n,m);
                    break;
                case 11:
                    PrintScore(stu,n,m);
                    break;
                case 12:
                    AvSumofEveryStudent(stu,n,m);
                    WritetoFile(stu,n,m);
                    break;
                case 13:
                    ReadfromFile(stu,&n,&m);
                    break;
                case 14:
                    AddaStudent(stu,n,m);
                    n++;
                    break;
                case 15:
                    DeleteaStudent(stu,n,m);
                    n--;
                    break;
                case 16:
                    CaculateGPA(stu,n,m);
                    break;
                case 17:
                    GenerateRecord(stu,n,m);
                    break;
                case 0:
                    printf("End of program!\n");
                    exit(0);
                default:
                    printf("Input error!\n");
                }
            }
            break;
        }
        else
        {
            printf("Your password is wrong!\n");
        }
    }
    return 0;
}
//�������ܣ���ʾ�˵�������û����������ѡ��
//��������ֵ���û�����Ĺ���ѡ��
int Menu(void)
{
    int itemSelected;
    printf("Management for Students' scores\n");
    printf("1.Input record\n");
    printf("2.Caculate total and average score of every course\n");
    printf("3.Caculate total and average score of every student\n");
    printf("4.Sort in descending order by score\n");
    printf("5.Sort in ascending order by score\n");
    printf("6.Sort in ascending order by number\n");
    printf("7.Sort in dictionary order by name\n");
    printf("8.Search by number\n");
    printf("9.Search by name\n");
    printf("10.Statistic analysis\n");
    printf("11.List record\n");
    printf("12.Write to a file\n");
    printf("13.Read from a file\n");
    printf("14.Add a student\n");
    printf("15.Delete a student\n");
    printf("16.Caculate GPA of every student\n");
    printf("17.Generate students' record randomly\n");
    printf("0.Exit\n");
    printf("Please Input your choice:");
    scanf("%d",&itemSelected); /*�����û�����*/
    return itemSelected;
}
//�������ܣ�����n��ѧ����m�ſγ̳ɼ�
//��������ֵ��void
void ReadScore(STU stu[],int n,int m)
{
    int i,j,ret1,ret[COURSE_NUM],flag=0;
    printf("Input students' ID,name and score:\n");
    for(i=0; i<n; i++)
    {
        while(1)
        {
            flag=0;
            ret1=scanf("%ld%s",&stu[i].num,stu[i].name);
            for(j=0; j<m; j++)
            {
                ret[j]=scanf("%f",&stu[i].score[j]);
                if(ret[j]!=1)
                {
                    flag=1;
                }
            }
            if(ret1!=2||flag==1)
            {
                printf("Input error!Please redo the student:\n");
                fflush(stdin);
            }
            else
            {
                break;
            }
        }
    }
}
//�������ܣ�����ÿ��ѧ�����ſγ̵��ֺܷ�ƽ����
//��������ֵ��void
void AverSumofEveryStudent(STU stu[],int n,int m)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        stu[i].sum=0;
        for(j=0; j<m; j++)
        {
            stu[i].sum=stu[i].sum+stu[i].score[j];
        }
        stu[i].aver=m>0?stu[i].sum/m:-1;//
        printf("student %d: sum = %.0f, aver = %.0f\n",i+1,stu[i].sum,stu[i].aver);
    }
}
//�������ܣ�����ÿ�ſγ̵��ֺܷ�ƽ����
//��������ֵ��void
void AverSumofEveryCourse(STU stu[],int n,int m)
{
    int i,j;
    float sum[COURSE_NUM],aver[COURSE_NUM];
    for(j=0; j<m; j++)
    {
        sum[j]=0;
        for(i=0; i<n; i++)
        {
            sum[j]=sum[j]+stu[i].score[j];
        }
        aver[j]=n>0?sum[j]/n:-1;
        printf("course %d:sum=%.0f, aver=%.0f\n",j+1,sum[j],aver[j]);
    }
}
//�������ܣ���ѡ�񷨽�����sum��Ԫ��ֵ����
//��������ֵ��void
void SortbyScore(STU stu[],int n,int m,int(*compare)(float a,float b))
{
    int i,j,k;
    AvSumofEveryStudent(stu,n,m);
    for(i=0; i<n-1; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if((*compare)(stu[j].sum,stu[k].sum)) k=j;
        }
        if(k!=i)
        {
            Swap(stu,k,i);
        }
    }
}
//�������ܣ�ʹ���ݰ���������
//��������ֵ����a<b������1����a>b������0
int Ascending(float a,float b)
{
    return a<b; /*�����ȽϾ����˰������������a>b���򽻻�*/
}
//�������ܣ�ʹ���ݰ���������
//��������ֵ����a<b������0����a>b������1
int Descending(float a,float b)
{
    return a>b; /*�����ȽϾ����˰������������a>b���򽻻�*/
}
//�������ܣ���ѡ�񷨽�����num��Ԫ��ֵ���ӵ͵�������
//��������ֵ��void
void AsSortbyNum(STU stu[],int n,int m)
{
    int i,j,k;
    for(i=0; i<n-1; i++)
    {
        k=i;
        for(j=i+1; j<n; j++)
        {
            if(stu[j].num<stu[k].num) k=j;
        }
        if(k!=i)
        {
            Swap(stu,k,i);
        }
    }
}
//�������ܣ������ṹ������������ѧ������Ϣ
//��������ֵ��void
void Swap(STU stu[],int k,int i)
{
    STU temp;
    temp=stu[k];
    stu[k]=stu[i];
    stu[i]=temp;
}
//�������ܣ�������ʵ���ַ������ֵ�˳������
//��������ֵ��void
void SortbyName(STU stu[],int n,int m)
{
    int i,j;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(strcmp(stu[j].name,stu[i].name)<0)
            {
                Swap(stu,i,j);
            }
        }
    }
}
//�������ܣ���ѧ�Ų���ѧ���ɼ�����ʾ
//��������ֵ��void
void SearchbyNum(STU stu[],int n,int m)
{
    AvSumofEveryStudent(stu,n,m);
    AvSumofEveryCourse(stu,n,m);
    long number;
    int i,j;
    printf("Input the number you want to search:");
    scanf("%ld",&number);
    for(i=0; i<n; i++)
    {
        if(stu[i].num==number)
        {
            printf("%09ld\t%s\t",stu[i].num,stu[i].name);
            for(j=0; j<m; j++)
            {
                printf("%.0f\t",stu[i].score[j]);
            }
            printf("%.0f\t%.0f\n",stu[i].sum,stu[i].aver);
            return;
        }
    }
    printf("\nNot found! \n");
}
//�������ܣ�����������ѧ���ɼ�����ʾ���ҽ��
//��������ֵ��void
void SearchbyName(STU stu[],int n,int m)
{
    AvSumofEveryStudent(stu,n,m);
    AvSumofEveryCourse(stu,n,m);
    char x[MAX_LEN];
    int i,j;
    printf("Input the name you want to search:");
    scanf("%s",x);
    for(i=0; i<n; i++)
    {
        if(strcmp(stu[i].name,x)==0)
        {
            printf("%09ld\t%s\t",stu[i].num,stu[i].name);
            for(j=0; j<m; j++)
            {
                printf("%.0f\t",stu[i].score[j]);
            }
            printf("%.0f\t%.0f\n",stu[i].sum,stu[i].aver);
            return;
        }
    }
    printf("\nNot found! \n");
}
//�������ܣ�ͳ�Ƹ������ε�ѧ����������ռ�İٷֱ�
//��������ֵ��void
void StatisticAnalysis(STU stu[],int n,int m)
{
    int i,j,total,t[6];
    for(j=0; j<m; j++)
    {
        printf("For course %d:\n",j+1);
        memset(t,0,sizeof(t)); /*������t��ȫ��Ԫ�س�ʼ��Ϊ0*/
        for(i=0; i<n; i++)
        {
            if(stu[i].score[j]>=0&&stu[i].score[j]<60) t[0]++;
            else if(stu[i].score[j]<70) t[1]++;
            else if(stu[i].score[j]<80) t[2]++;
            else if(stu[i].score[j]<90) t[3]++;
            else if(stu[i].score[j]<100) t[4]++;
            else if(stu[i].score[j]==100) t[5]++;
        }
        for(i=0; i<=5; i++)
        {
            if(i==0) printf("<60\t%d\t%.2f%%\n",t[i],(float)t[i]/n*100);
            else if(i==5) printf("%d\t%d\t%.2f%%\n",(i+5)*10,t[i],(float)t[i]/n*100);
            else printf("%d-%d\t%d\t%.2f%%\n",(i+5)*10,(i+5)*10+9,t[i],(float)t[i]/n*100);
        }
    }
}
//�������ܣ���ӡѧ���ɼ�
//��������ֵ��void
void PrintScore(STU stu[],int n,int m)
{
    AvSumofEveryStudent(stu,n,m);
    AvSumofEveryCourse(stu,n,m);
    int i,j;
    for(i=0; i<n; i++)
    {
        printf("%09ld\t%s\t",stu[i].num,stu[i].name);
        for(j=0; j<m; j++)
        {
            printf("%.0f\t",stu[i].score[j]);
        }
        printf("%.0f\t%.0f\n",stu[i].sum,stu[i].aver);
    }
}
//���n��ѧ����ѧ�š�������m�ſγ̵ĳɼ����ļ�student.txt��
//��������ֵ��void
void WritetoFile(STU stu[],int n,int m)
{
    FILE *fp;
    int i,j;
    if((fp=fopen("student.txt","w"))==NULL)
    {
        printf("Failure to open score.txt! \n");
        exit(0);
    }
    fprintf(fp,"%d\t%d\n",n,m);
    for (i=0; i<n; i++)
    {
        fprintf(fp,"%10ld%10s",stu[i].num,stu[i].name);
        for (j=0; j<m; j++)
        {
            fprintf(fp,"%10.0f",stu[i].score[j]);
        }
        fprintf(fp,"%10.0f%10.0f\n",stu[i].sum,stu[i].aver);
    }
    fclose(fp);
}
//���ļ��ж�ȡѧ����ѧ�š��������ɼ�����Ϣд�뵽�ṹ������stu��
//��������ֵ��void
void ReadfromFile(STU stu[],int *n,int *m)
{
    FILE *fp;
    int i,j;
    if ((fp=fopen("student.txt","r"))==NULL)
    {
        printf("Failure to open score.txt!\n");
        exit(0);
    }
    fscanf(fp,"%d\t%d",n,m);
    for (i=0; i<*n; i++)
    {
        fscanf(fp,"%10ld",&stu[i].num);
        fscanf(fp,"%10s",stu[i].name);
        for (j=0; j<*m; j++)
        {
            fscanf(fp,"%10f",&stu[i].score[j]);
        }
        fscanf(fp,"%10f%10f",&stu[i].sum,&stu[i].aver);
    }
    fclose(fp);
}
//�������ܣ�����ÿ��ѧ�����ſγ̵��ֺܷ�ƽ���֣��������
//��������ֵ��void
void AvSumofEveryStudent(STU stu[],int n,int m)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        stu[i].sum=0;
        for(j=0; j<m; j++)
        {
            stu[i].sum=stu[i].sum+stu[i].score[j];
        }
        stu[i].aver=m>0?stu[i].sum/m:-1;
    }
}
//�������ܣ�����ÿ�ſγ̵��ֺܷ�ƽ���֣��������
//��������ֵ��void
void AvSumofEveryCourse(STU stu[],int n,int m)
{
    int i,j;
    float sum[COURSE_NUM],aver[COURSE_NUM];
    for(j=0; j<m; j++)
    {
        sum[j]=0;
        for(i=0; i<n; i++)
        {
            sum[j]=sum[j]+stu[i].score[j];
        }
        aver[j]=n>0?sum[j]/n:-1;
    }
}
//�������ܣ�����ѧ����¼
//��������ֵ��void
void AddaStudent(STU stu[],int n,int m)
{
    int j;
    printf("Input the student's ID,name and score:\n");
    scanf("%ld%s",&stu[n].num,stu[n].name);
    for(j=0; j<m; j++)
    {
        scanf("%f",&stu[n].score[j]);
    }
}
//�������ܣ�ɾ��ĳ��ѧ���ļ�¼
//��������ֵ��void
void DeleteaStudent(STU stu[],int n,int m)
{
    long number;
    int i,j;
    printf("Which student do you want to delete?Input his number:");
    scanf("%ld",&number);
    for(i=0; i<n; i++)
    {
        if(stu[i].num==number)
        {
            for(j=i; j<n-1; j++)
            {
                stu[j]=stu[j+1];
            }
            return;
        }
    }
    printf("The student doesn't exist.\n");
}
//�������ܣ�����ÿ��ѧ����ѧ�ּ�
//��������ֵ��void
void CaculateGPA(STU stu[],int n,int m)
{
    int i,j;
    float weight[COURSE_NUM];
    float sum=0;
    printf("Input the percentage of every course in order(for example:0.1 0.2 0.7):");
    for(i=0; i<m; i++)
    {
        scanf("%f",&weight[i]);
        sum=sum+weight[i];
    }
    if(fabs(sum-1)<EL)
    {
        for(i=0; i<n; i++)
        {
            sum=0;
            for(j=0; j<m; j++)
            {
                sum=sum+stu[i].score[j]*weight[j];
            }
            stu[i].GPA=sum*0.04;
            printf("student %d: GPA = %.1f\n",i+1,stu[i].GPA);
        }
    }
    else
    {
        printf("Input error!\n");
    }
}
//�������ܣ��������ѧ��������Ϣ
//��������ֵ��void
void GenerateRecord(STU stu[],int n,int m)
{
    int i,j;
    for(i=0; i<n; i++)
    {
        stu[i].num=rand()*rand()%1000000000+1;
        stu[i].name[0]='A'+rand()%26;
        for(j=1; j<MAX_LEN; j++)
        {
            stu[i].name[j]='a'+rand()%26;
        }
        stu[i].name[j]='\0';
        for(j=0; j<m; j++)
        {
            stu[i].score[j]=rand()%100;
        }
    }
}
