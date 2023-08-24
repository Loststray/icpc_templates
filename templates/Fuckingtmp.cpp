#include <bits/stdc++.h>
using namespace std;
#define N 100
#define M 3
struct Student
{
    char xh[10];
    char name[20];
    char sex; // M  or  F
    double score[M];
    double total;
};
int read_data(struct Student *students,char *file_name)
{
    freopen(file_name,"r",stdin);
    FILE* male,*female;
    auto sbegin = students;
    while(~scanf("%s %s %c %lf %lf",students->xh,students->name,&students->sex,&students->total))
        students++;
    fclose(stdin);
    return students - sbegin;
} 

int main()
{
}