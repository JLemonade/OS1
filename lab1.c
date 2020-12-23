#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

//Построчный вывод значений из аргументов командной строки
void outputToScreen (int argc, char *argv[  ] ) {
for(int i = 1; i < argc; i++) {
printf ("%s\n", argv[i] );
    }
}

//Запись символов, набираемых с клавиатуры в заданный файл
void writeToFile(int argc, char *argv[  ] ) {
if (argc == 1) {
printf ("Файл записи не передан.");
exit(-1);
    }

if (argc>2) {
printf ("Аргументы командной строки имеют много параметров, проверьте, что только путь до файла передан.");
exit(-1);
    }

FILE *F1 = fopen(argv[1], "w");
if (F1 == NULL) {
printf ("Невозможно открыть файл");
exit(-1);
    }

printf ("Введите текст, для записи в файл. При нажатии на ESC будет произведён выход");
int code;
while ((code = getchar()) != 27) {
int putCode = fputc((char)code, F1);
if (putCode == EOF){
printf ("Запись в файле произошла неудачно.");
exit(-1);
        }
    }
int closeCode = fclose (F1);
if (closeCode == EOF){
printf ("Закрытие потока работы с файлом завершилось ошибкой.");
exit(-1);
    }
printf ("Запись в файл осуществлена");
}

//Вывод записей из файла на экран
void printFileToScreen (int argc, char *argv[  ] ) {
if (argc == 1){
printf ("Файл для открытия не передан.");
exit(-1);
    }

if (argc > 3) {
printf ("Аргументы командной строки имеют много параметров, проверьте, что передан только путь до файла и N.");
exit (-1);
    }

FILE *F1 = fopen (argv[1], "r");
if (F1 == NULL){
printf ("Невозможно открыть файл");
exit (-1);
    }
int code;
int N = atoi (argv[2]);
if (N == 0) {
while ((code = getc(F1)) != EOF){
if (code == 10)
printf (" ");
printf  ("%c", (char)code);
        }
} else {
while (1) {
for (int i= 0; i < N; ++i) {
while ((code = getc(F1)) != EOF){
printf  ("%c", (char)code);
if  (code == 10)
break;
                }
            }
int exit Code = getchar();
if (exitCode == 27)
break;
        }
    }
int closeCode= fclose (F1);
if (closeCode== EOF){
printf ("Закрытие потока работы с файлом завершилось с ошибкой.");
        exit(-1);
    }
}

//Копирование из одного файла в другой
void copyFiles(int argc, char *argv[ ] ) {
FILE *source = fopen(argv[1], "r");
if (source == NULL) {
printf("Файл %s не найден", argv[1]);
        exit(-1);
    }
FILE *dest= fopen(argv[2], "w");
if (dest== NULL){
printf("Файл %s не найден", argv[1]);
        exit(-1);
    }
int code;
while ((code = fgetc(source)) != EOF){
fputc(code, dest);
    }
int destCloseCode= fclose(dest);
if (destCloseCode== EOF){
printf("Закрытие потока работы с файлом-источником завершилось с ошибкой.");
        exit (-1);
    }
int sourceCloseCode= fclose(source);
if (sourceCloseCode== EOF){
printf ("Закрытие потока работы с файлом-источником завершилось с ошибкой.");
        exit (-1);
    }
}

//Используется для манипуляций с dirent.
void printDirInfo(DIR *dir){
struct dirent *localDirent;
printf ("%s %s %s %s \n", "id", "name", "extention", "reclen");
while (((localDirent = readdir(dir)) != NULL)) {
printf ("%d - %s [%d] %d\n",
localDirent->d_ino, localDirent->d_name, localDirent->d_type, localDirent->d_reclen);
    }
int closeCode= closedir(dir);
if (closeCode == EOF) {
printf("Закрытие папки завершилось с ошибкой.");
        exit(-1);
    }

}

//Выводит информацию о файлах в текущей и выбранной папке.
void countFiles(int argc, char *argv[ ]){
char cwd[1000];
DIR *current = opendir (getcwd(cwd, sizeof(cwd)));
if (current == NULL){
printf ("Папка по умолчанию не найдена.");
        exit(-1);
    }
DIR *selected = opendir(argv[1]);
if (selected == NULL){
printf("Папка по адресу %s не найдена", argv[1]);
        exit(-1);
    }
printf ("Список файлов в текущей папке: ");
printDirInfo (current);
printf("Список файлов в папке: %s", argv[1]);
printDirInfo(selected);
}

