#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LEN 10 /*字符串最大长度*/
#define STU_NUM 30 /*最多的学生人数*/
#define COURSE_NUM 6 /*最多的考试科目数*/
#define EL 1e-4 /*足够小的一个值*/
typedef struct student
{
    long num; /*每个学生的学号*/
    char name[MAX_LEN]; /*每个学生的姓名*/
    float score[COURSE_NUM]; /*每个学生COURSE_NUM门功课的成绩*/
    float sum; /*每个学生的总成绩*/
    float aver;/*每个学生的平均成绩*/
    float GPA; /*每个学生的学分绩*/
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
            } /*容错处理：只要用户输入的不是0-29以及1-6，都提示错误，避免程序陷入死循环*/
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
//函数功能：显示菜单并获得用户键盘输入的选项
//函数返回值：用户输入的功能选项
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
    scanf("%d",&itemSelected); /*读入用户输入*/
    return itemSelected;
}
//函数功能：输入n个学生的m门课程成绩
//函数返回值：void
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
//函数功能：计算每个学生各门课程的总分和平均分
//函数返回值：void
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
//函数功能：计算每门课程的总分和平均分
//函数返回值：void
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
//函数功能：按选择法将数组sum的元素值排序
//函数返回值：void
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
//函数功能：使数据按升序排序
//函数返回值：若a<b，返回1；若a>b，返回0
int Ascending(float a,float b)
{
    return a<b; /*这样比较决定了按升序排序，如果a>b，则交换*/
}
//函数功能：使数据按降序排序
//函数返回值：若a<b，返回0；若a>b，返回1
int Descending(float a,float b)
{
    return a>b; /*这样比较决定了按降序排序，如果a>b，则交换*/
}
//函数功能：按选择法将数组num的元素值按从低到高排序
//函数返回值：void
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
//函数功能：交换结构体数组中两个学生的信息
//函数返回值：void
void Swap(STU stu[],int k,int i)
{
    STU temp;
    temp=stu[k];
    stu[k]=stu[i];
    stu[i]=temp;
}
//函数功能：交换法实现字符串按字典顺序排序
//函数返回值：void
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
//函数功能：按学号查找学生成绩并显示
//函数返回值：void
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
//函数功能：按姓名查找学生成绩并显示查找结果
//函数返回值：void
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
//函数功能：统计各分数段的学生人数及所占的百分比
//函数返回值：void
void StatisticAnalysis(STU stu[],int n,int m)
{
    int i,j,total,t[6];
    for(j=0; j<m; j++)
    {
        printf("For course %d:\n",j+1);
        memset(t,0,sizeof(t)); /*将数组t的全部元素初始化为0*/
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
//函数功能：打印学生成绩
//函数返回值：void
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
//输出n个学生的学号、姓名及m门课程的成绩到文件student.txt中
//函数返回值：void
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
//从文件中读取学生的学号、姓名及成绩等信息写入到结构体数组stu中
//函数返回值：void
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
//函数功能：计算每个学生各门课程的总分和平均分，但无输出
//函数返回值：void
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
//函数功能：计算每门课程的总分和平均分，但无输出
//函数返回值：void
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
//函数功能：增加学生记录
//函数返回值：void
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
//函数功能：删除某个学生的记录
//函数返回值：void
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
//函数功能：计算每个学生的学分绩
//函数返回值：void
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
//函数功能：随机生成学生数据信息
//函数返回值：void
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
