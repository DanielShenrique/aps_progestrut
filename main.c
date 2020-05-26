#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Crie um programa que tenha um menu:
//1- Entrar com novos dados
//2- Listar dados
//3- Sair
// Ao selecionar a opção 1, os dados de um aluno devem ser armazenado
//em uma tabela(vetor de registros e em um arquivo),
//cada registro deve ser criado dinamicamente. (realloc)
// Ao selecionar a opção 2, será listado todo os registros.
// Ao selecionar a opção 3, o programa deverá ser encerrado.

unsigned short int ChooseOpcions();
float ChooseGrades();

struct student
{
    char name[20];
    float grade_1, grade_2;
    float average;
};

int main()
{

    struct student *students = NULL;
    struct student *more_students;

    FILE *file;

    char ent_name[20];
    float ent_grade_1, ent_grade_2, ent_average;

    unsigned int size, i;
    unsigned short int opcion;
    char read;

    size = 0;

    do
    {
        //recebe as opções
        opcion = 0;
        printf("Escolha a opcao: (1 - adicionar, 2 - ver todos, 3 - sair)\n");
        opcion = ChooseOpcions();

        if (opcion == 1)
        {
            //aqui faz o registro dos dados
            file = fopen("struct.txt", "a");
            if (file)
            {
                size++;
                more_students = (struct student *)realloc(students, size * sizeof(struct student));

                if (more_students != NULL)
                {
                    students = more_students;

                    fflush(stdin);
                    printf("Nome:\n");
                    fgets(ent_name, sizeof(ent_name), stdin);
                    strcpy(students[size - 1].name, ent_name);
                    printf("Nota da 1 prova:\n");
                    ent_grade_1 = ChooseGrades();
                    students[size - 1].grade_1 = ent_grade_1;
                    printf("Nota da 2 prova:\n");
                    ent_grade_2 = ChooseGrades();
                    students[size - 1].grade_2 = ent_grade_2;

                    students[size - 1].average = (ent_grade_1 + ent_grade_2) / 2;

                    fprintf(file, "Nome: %s", students[size - 1].name);
                    fprintf(file, "Nota_AV1: %.2f\n", students[size - 1].grade_1);
                    fprintf(file, "Nota_AV2: %.2f\n", students[size - 1].grade_2);
                    fprintf(file, "Media: %.2f\n", students[size - 1].average);
                    fprintf(file, "==================\n");

                    fclose(file);
                    system("cls");
                }
                else
                {

                    free(students);
                    printf("Erro ao (re)alocar memoria");
                    return 0;
                }
            }
            else
            {
                printf("Erro na abertura do arquivo. Fim de programa.");
                return 0;
            }
        }
        else
        {
            //aqui mostra os dados registrados
            if (opcion == 2)
            {
                file = fopen("struct.txt", "r");

                if (file)
                {
                    while ((read = getc(file)) != EOF)
                    {
                        printf("%c", read);
                    }
                    fclose(file);
                }
            }
        }

    } while (opcion != 3);

    system("pause");
    return 0;
}

//função para limitar as opções de 1 a 3
unsigned short int ChooseOpcions()
{

    unsigned short int times;

    unsigned short int op;

    times = 0;

    do
    {

        if (times > 0)
        {
            printf("Dado incorreto, as opcao so podem ir de 1 a 3\n");
        }

        scanf("%hu", &op);

        times++;

    } while (op < 1 || op > 3);

    times = 0;

    return op;
}

//função para limitar as notas de 0 a 10
float ChooseGrades()
{
    unsigned short int times;

    float grades;

    times = 0;

    do
    {

        if (times > 0)
        {
            printf("Dado incorreto, as notas so podem ir de 0 a 10\n");
        }

        scanf("%f", &grades);

        times++;
    } while (grades < 0.0 || grades > 10.0);

    times = 0;

    return grades;
}
