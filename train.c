#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

char *student[] = {"Tetiana", "Andrey", "Igor", "Anastasia", "Alibi"};
int age[] = {20, 21, 22, 23, 24};
typedef struct Students T_Students;
typedef struct Studend{
    pthread_t id;
    pthread_mutex_t mtx_student_rigt;
    pthread_mutex_t mtx_student_left;
    int id_rigt;
    int id_left;
    char *name;
    int age;
    int graid;
    int id_of_students;
    T_Students *student;
} Student_t;

typedef struct Students{
    Student_t **student;
    pthread_t monitor;
    pthread_mutex_t mtx_monitor;
    int exit;
} T_Students;

void *printStudentInfo(void *argv)
{
    Student_t *s = (Student_t *)argv;
    pthread_mutex_lock(&s->mtx_student_rigt);
    printf("student %d take %d right\n", s->id_of_students, s->id_rigt);
    pthread_mutex_lock(&s->mtx_student_left);
    printf("student %d take %d left\n", s->id_of_students, s->id_left);
    printf("%s\n", s->name);
    printf("%d\n", s->age);
    printf("%d\n", s->graid);
    pthread_mutex_unlock(&s->mtx_student_rigt);
    pthread_mutex_unlock(&s->mtx_student_left);
    return NULL;
}

void *monitor(void *argv)
{
    T_Students *students = (T_Students *) argv;
    while (!students->exit)
    {
        for (int i = 0; i < 5; i++)
        {
            pthread_mutex_lock(&students->mtx_monitor);
            if (students->student[i]->graid == 0)
            {
                students->exit = 1;
                printf("grade not good\n");
            }
            pthread_mutex_unlock(&students->mtx_monitor);
        }
        usleep(100000); // Предотвращает загрузку процессора бесконечным циклом
    }
    return NULL;
}

Student_t **init_value()
{
    Student_t **s;
    s = malloc(sizeof(Student_t *) * 5);
    int i = 0;
    while (i < 5)
    {
        s[i] = malloc(sizeof(Student_t));
        s[i]->name = student[i];
        s[i]->age = age[i];
        s[i]->graid = 125;
        s[i]->id_rigt = i;
        s[i]->id_left = (i + 1) % 5;
        s[i]->id_of_students = i;
        i++;
    }
    return s;
}

void change_value(Student_t **studen)
{
    usleep(1000000);
    studen[3]->graid =0;
    usleep(100);
}
void init_mutex(Student_t **students)
{
    int i =0;
    while (i < 5)
    {
        pthread_mutex_init(&students[i]->mtx_student_rigt, NULL);
        
    
        pthread_mutex_init(&students[i]->mtx_student_left, NULL);
        i++;
    }
}
void init_mutext_global(T_Students *student)
{
    student->exit = 0;
    pthread_mutex_init(&student->mtx_monitor, NULL);
}

void free_students(Student_t **student, T_Students *s)
{
    int i = 0;
    while (i < 5)
    {
        pthread_mutex_destroy(&student[i]->mtx_student_rigt);
        pthread_mutex_destroy(&student[i]->mtx_student_left);
        free(student[i]);
        i++;
    }
    free(student);
    pthread_mutex_destroy(&s->mtx_monitor);
}
int main()
{
    // Student_t s = {"Tetiana", 28, 125};
    // printf("%s", s.name);
    T_Students students;
    Student_t **s;

    s = init_value();
    init_mutext_global(&students);
    init_mutex(s);
    students.student = s;
    int i = 0;
    change_value(students.student);
    pthread_create(&students.monitor, NULL, &monitor, &students);
    
    while (i < 5)
    {
        pthread_create(&(students.student[i]->id), NULL, &printStudentInfo, s[i]);
        i++;
    }
    i = 0;
    while (i < 5)
    {
        pthread_join(students.student[i]->id, NULL);
        i++;
    }
    pthread_join(students.monitor, NULL);   
    pthread_mutex_destroy(&students.mtx_monitor);
    free_students(students.student, &students);
}