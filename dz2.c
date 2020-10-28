#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#define MAX 120



int main(void)
{
    system("chcp 65001");

    /////////// Ввод кол-ва эл-тов //////////
    char c;
    int mass[MAX][MAX];
    int ln = 0, verh, rebr, i = 0, j = 0, u = 0;
    int o = 0;

    printf("\nКоличество вершин в графе: ");
    scanf("%i", &verh);
    printf("Количество ребер: ");
    scanf("%i", &rebr);

    

    printf("Ориентированный? \n1 - да / 2 - нет\n");
    scanf("%d", &o);


    /////////// Ввод эл-тов //////////
    printf("\n2 - петля \n1 - обычная свзяь \n0 - нет связи\n");

    if (o == 2) 
    {
        for (i=0; i < rebr; i++)
        {
            for (j=0; j < verh; j++)
            {
                printf("Ребро %i соединено с вершиной %i: ", i + 1, j + 1);
                scanf("%i", &mass[i][j]);    
            }
        }
    }
    
    if (o == 1) 
    {
        for (i=0; i < rebr; i++)
        {
            for (j=0; j < verh; j++)
            {
                printf("Если ребро %i входит в вершину, %i = 1, если выходит = -1: ", i + 1, j + 1);
                scanf("%i", &mass[i][j]);
            
            }
        }
    }

    printf("\nКак выглядит матрица\n");

    for (i = 0; i < rebr; i++)
    {
        for (j = 0; j < verh; j++)
        {
           printf("%d ", mass[i][j]);
        }
        printf("\n");

    }


    ///////////  //////////
      
    char massq[10];
    int dop = 0;
    printf("Есть ли еще связи? \n1 - да\n2 - продолжить\n");
    scanf("%d", &dop);
    getchar();
        if (dop==2)
            {
                printf("Продолаем программу\n");
            }
        if (dop==1)
        {   
            printf("Введите буквы связываемых пар\n");
            i = 0;
            while((c = getchar()) !='\n')
                {    
                    massq[i]=c; 
                    i++;
                }
            massq[i]='\0';
        }
    

    /////////// открытие файла //////////
    FILE* file;

    file = fopen("graph.dot", "w");
        if (o == 1)
            fprintf(file, "digraph DG {\n");
        if (o == 2)
            fprintf(file, "graph DG {\n");

    for (int e = 97; e < (97 + verh); e++)
    {
        fprintf(file, "%c;\n", e);
    }

        if (dop==1){
             for (int e = 0; e < i; e=e+2)
    {
        fprintf(file, "%c -- %c;\n", massq[e], massq[e+1]);
    }
}
    
    /////////// запись в дот //////////

    char q1=0;
    char q2=0;


    if (o == 2) 
    {
        for (i=0; i < rebr; i++)
        {
            bool sw = false;
        for (j = 0; j < verh; j++)
        {
            if ((mass[i][j] == 1) && (sw == true))
            {
                q2 = j + 97;
            }
            if ((mass[i][j] == 1) && (sw == false))
            {
                sw = true;
                q1 = j+97;
            }

            if (mass[i][j] == 2)
                fprintf(file, "%c -- %c;\n", j+97, j+97);

            if (mass[i][j] == 0);
        }

            if ( (q1!=0) && (q2!=0) )
                fprintf(file, "%c -- %c;\n", q1,q2);
        }
    }
    if (o == 1) 
    {
        for (i = 0; i < rebr; i++)
        {
            for (j = 0; j < verh; j++)
            {
                if (mass[i][j] == 1)
                {
                    q1 = j+97;
                }
                if (mass[i][j] == -1)
                {
                    q2 = j+97;
                }
                if (mass[i][j] == 2)
                    fprintf(file, "%c -> %c;\n", j + 97, j + 97);
                
                if (mass[i][j] == 0);
            }
   
        if ((q1 != 0) && (q2 != 0))
            fprintf(file, "%c -> %c;\n", q2, q1);
        }
    }

    fprintf(file, "}\n");
    fclose(file);
    system("dot -Tpng graph.dot -o graph.png");
	system("graph.dot");


/////// Вызов функции для проверки на вязность///////

    int q = 0;  
    printf("Нужна ли проверка на связность?\n1 - нет\n2 - да\n");
    scanf("%d", &q);
    getchar();

    if(q == 2)
    {
        printf ("Проверяю\n");
        int i, j;
        int ur = 0;
        bool Sv = 1;
    
        for (int i = 0; i < rebr; i++) 
            {
                bool tmp = 0; 
                for (int j = 0; j < verh; j++)
                {
                    if (mass[i][j] == 1)
                        tmp = 1;
                    if (mass[j][i] == 1)
                        tmp = 1;
                }
                
                if (tmp == 0)
                    Sv = 0;
            }
                
                if (Sv == 0) 
                {
                    ur = 1;
                }
                else {
                    ur = 0;
                }
    j = 0;   int u = 0;   i = 0;
    
    int e = 0;
    int sum = 0, sum1 = 0;
    bool err = false;

        for (i; i < rebr; i++)
            {
                for (j; j < verh; j++)
                {
                    if (mass[i][j] == 1)
                    {
                        sum += mass[i][j];
                        sum1 += mass[i][j];
                    }
                }
                
                if (sum1 == 0) err = true;
                    sum1 = 0;
                    u++;
                    j = u;
            }

        int a = (((verh - 1) * (verh - 2)) / 2);

        if ((sum >= a)&&(ur==0))

        printf("\nГраф связный!");

        else 
        printf("\nГраф несвязный!");
        }
        else
        {
            printf("Программа завершена!");
        }

}
