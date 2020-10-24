#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#define MAX 120


void put();
void check();



int main(void)
{
    int i;

    printf("----Меню-----\n");
    printf("Выберите действие\n1.Задать граф\n2.Проверка на связность графа\n");
    i = getchar();

    switch (i)
    {
    case '1':
        put();
        break;
    case '2':
        //check();
        break;
    
    default:
        break;
    }

}


void put(){

    /////////// Ввод кол-ва эл-тов //////////
    char c;
    int mass[MAX][MAX];
    int ln = 0, verh, rebr, i = 0, j = 0, u = 0;
    int o = 0;

    printf("Количество вершин в графе: ");
    scanf("%i", &verh);
    printf("Количество ребер: ");
    scanf("%i", &rebr);
    //c = getchar();

    printf("Ориентированный? 1-да / 2-нет\n");
    scanf("%d", &o);


    /////////// Ввод эл-тов //////////
    printf("2 - петля 1 - обычная свзяь 0 - нет связи\n");

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

    for (i = 0; i < rebr; i++)
    {
        for (j = 0; j < verh; j++)
        {
           printf("%d ", mass[i][j]);
        }
        printf("\n");

    }


    /////////// Учет кратности //////////
      
    char massq[10];
    int dop=0;
    printf("есть ли еще связи?");
    scanf("%d", &dop);
    getchar();
        if (dop==2)
            {;}
        if (dop==1)
        {   
            i=0;
            while((c = getchar()) !='\n')
                {    
                    massq[i]=c; i++;
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

}
