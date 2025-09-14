#include <stdio.h>
#include <stdlib.h>
#define Name "Mykola"
#define LastName "Ivanenko"
#define GroupName "GP-13"
#define Faculty "FFF"
#define University "Igor Sikorsky Kyiv Polytechnic Institute"
int main()
{
 unsigned int semestr;
 float admissionScore;
 int grade1;
 int grade2;
 int grade3;
 double averageGrade;
 unsigned int age;
printf("%s %s Enter following data.\n", Name, LastName);
 printf("Enter semestr:");
 scanf("%u", &semestr);
 printf("Enter your admission score: ");
 scanf("%f", &admissionScore);
printf("Enter grade #1: ");
 scanf("%d", &grade1);
 printf("Enter grade #2:");
 scanf("%d", &grade2);
 printf("Enter grade #3:");
 scanf("%d", &grade3);
 printf("Enter your age: ");
 scanf("%u", &age);
 averageGrade = (double)(grade1 + grade2 + grade3) / 3;
 system("cls");
 printf("%s", University);
 printf("\n%s", Faculty);
 printf("\n%s", GroupName);
 printf("\n---------------------------");
 printf("\nstudent: %s %s", Name, LastName );
 printf("\nage: %u", age);
 printf("\nsemestr: %u", semestr);
 printf("\n---------------------------");
 printf("\nadmission score: %.2f", admissionScore);
 printf("\naverage grade = %.3lf", averageGrade);
 printf("\n");
 return 0;
}
