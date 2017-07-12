//
// Created by arloor on 17-7-10.
//

#include "header/std_io.h"
#include<stdio.h>
#include <stdlib.h>


/**
 * 用一个文件的生命周期来说明标准（带缓冲的）的文件IO
 * 包括create open read write close和lseek
 * @return
 */

void std_io() {
    printf("主要看注释哦，控制台输出没什么东西\n");
    //定义路径，打开或者创建文件
    //+表示读和写 r读 w截断为0写（重新创建） a（追加）
    char *path = "../data/std_io.txt";
    FILE *fp = fopen(path, "w+");
    //对打开/创建文件的说明:
    //（1）FIlE *fopen(char* pathname,char* type);//type:r w a r+ w+ a+
    //（2）FIlE *freopen(char* pathname,char* type,FILE *fp);
    //先关闭流，再在流上打开一个文件，并且清除文件的定向。
    //一般用于将一个指定的文件打开为stdin stdout stderr
    //关于流的定向（流读写的字符是单字节还是多字节)
    // 流创建时并没有设置定向，使用多字节IO函数，定向设置为宽定向。
    // 使用单字节IO函数，定向设置为单字节定向。
    // 使用freopen清除定向之后可以使用fwide（FILE* fp,mode）设置定向。
    // mode 字节定向<0 宽定向>0   如果为0,不修改定向，只是返回当前定向的mode
    // 注意：之改变未定向的流的定向（保险起见一定要freopen）
    //（3）FILE *fdopen(int fd, char* type);
    // 使用一个已经存在的文件描述符fd来打开。fd可以通过open create dup等来获得。
    // 经常用于由创建管道和网络通信通道函数返回的描述符。这些特殊类型的文件不能用标准IO的fopen打开，所以需要使用fd。
    // fdopen的type意义有区别：截断不由type的w决定而由fd的O_APPEND决定。
    // 即不会重新创建，保留原文件的一切（这总结多好，书上说的迷糊）
    // 至于r或者w能不能生效（会不会和fd的OFLAG冲突，谁生效），树上没说，以后需要时再实践

    //对type的+的其他约束：
    // 即读和写打开一个文件时，读写之间一定要调用括号中的函数！没有实践，书上这么说。
    // 输出write （fflush | fseek | fsetpos | rewind ——定位或者刷新）输入read
    // 输入read(没有到达尾端)  （fseek | fsetpos | rewind ——定位）输出write

    //这些打开文件流的方式无法控制访问权限（无缓冲的IO可以设置），我们可以调用umusk方法来设置访问权限（见4.8）
    //关于打开创建文件说明结束。。




    // (可选)设置文件流的缓冲方式。
    // 缓冲方式系统其实已经默认赋予：
    // 标准错误是不带缓冲的。指向终端设备的是行缓冲，其他为全缓冲。
    // 只有需要自己设定缓冲方式时才调用这个方法。
    // 设置缓冲必须在打开文件之后立即执行。
    // 首先定义一个BUFSIZ大小的内存空间（char*类型）作为缓冲区
    // 然后void setbuff(FIlE fp,char * buff)来定义缓冲区。
    // 设置之后一般默认为全缓冲，但是有些系统会将指向终端设备的缓冲设为行缓冲
    // 当buff设为NULL时，就是无缓冲
    char *buff = (char *) malloc(BUFSIZ);//关闭流时需要记得释放
    setbuf(fp, buff);
    //另一种设置缓冲的方法：
    // int setvbuff(FIlE* fp, char* buf,int mode,size_t size)
    // mode: _IOFBF全缓冲 _IOLBF行缓冲 _IONBF不缓冲
    // 如果mode为不缓冲(_IONBF)则忽略buff和size
    // 如果全缓冲或者行缓冲：buf和size可指定的选择一个缓冲区和他的长度。
    // 如果buf为NULL，系统将自动分配大小为BUFSIZ的缓冲区
    //因此上面的命令等同于：
    // setvbuf(fp,NULL,_IOFBF,0);


    //-----------------------------读和写流 非格式化的 开始-----------------------------------
    //三种非格式化IO：
    //  （1）每次读写一个字符的IO
    //      int getc(FIlE* fp);可能是宏
    //      int putc(int c,FILE* fp);可能是宏
    //      int fgetc(FIlE* fp);一定是函数可以取地址当函数指针
    //      int fputc(int c,FILE* fp);一定是函数可以取地址当函数指针
    //      int getchar(void); 从标准输入读 =getc(stdin)
    //      int putchar(void); 输出到标准输出 =putc(stdout)
    //      返回int而不是char的原因：EOF=-1 这些读出来的字符需要和EOF比较（比如晴空缓存的一般方法）
    //      int ungetc(int c,FILE* fp);//把字符送回到流中（缓冲区，如果无缓冲呢？），以便下次读取能读到。

    //      关于EOF和文件结束/出错标志：出错和文件结束都是EOF，下面两个函数判断到底是哪个
    //      一般出现EOF项羽傲判断到底读完还是出错时调用
    //      int ferror(FILE* fp);//是否出错，true返回非0
    //      int feof(FILE* fp);//是否结束，true返回非0
    //      int clearerr(FIlE* fp);//清除两种标志。
    //  （2）每次读写一行的IO
    //      char *fgets(char* buf,int n,FILE* fp);buff为自己设定的缓冲，n为缓冲区大小。
    //                                            读到\n或者n-1字符结束，第n个字符永远是NULL
    //      char *gets(char* buf);不推荐使用，不指定缓冲区大小可能会引起缓冲区溢出
    //
    //      int fputs(const char *str,FILE* fp);//将一个以null为结束的字符串写到指定的流。NULL不写出。
    //      int puts(const char *str);//将一个以null为结束的字符串写到标准输出。NULL不写出。随后跟一个'\n'
    //  （3）直接IO（二进制读写,或者写入一个结构体）
    //      直接把数据结构保存到文件的能力还是很可怕的，666
    //      size_t fread(void* ptr,size_t size,size_t nobj,FILE* fp);
    //      size_t fwrite(void* ptr,size_t size,size_t nobj,FILE* fp);
    //      注意二进制读只能读同一系统上的已写数据。
    //      这里来两个例子：
    printf("以二进制方式写一个float[5]数组的第2-5位\ndata[5]={1.1,2.2,3.3,4.4,5.5};\n");
    float data[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    if ((fwrite(&data[1], sizeof(float), 4, fp)) != 4)//写data的2-5位
        fputs("写错误\n", stderr);
    fflush(fp);
    fseek(fp, 0, SEEK_SET);//还记得上面说的读写之间要加一些函数吗，嘿嘿嘿
    float data_read[4];
    if ((fread(&data_read[0], sizeof(float), 4, fp)) != 4)
        fputs("读错误\n", stderr);
    printf("读到的第一个float为：%f\n\n", data_read[0]);
    //因为读完了，所以这里不用插函数

    //但是从头写还是设置偏移的
    fseek(fp, 0, SEEK_SET);
    printf("以二进制方式写一个结构体\n");
    struct item {
        int id;
        char *name;
    };
    struct item aitem;
    aitem.id = 0;
    aitem.name = "a pig";
    if ((fwrite(&aitem, sizeof(struct item), 1, fp)) != 1)//写data的2-5位
        fputs("写错误\n", stderr);
    fflush(fp);
    fseek(fp, SEEK_SET, 0);//还记得上面说的读写之间要加一些函数吗，嘿嘿嘿
    struct item aitem_read;
    if ((fread(&aitem_read, sizeof(struct item), 1, fp)) != 1)
        fputs("读错误\n", stderr);
    printf("读到的第一个struct：id为：%d，name为：%s\n\n", aitem_read.id, aitem_read.name);
    //-----------------------------读和写流  结束-----------------------------------


    //-----------------------------定位流  开始-----------------------------------
    //long ftell(FILE *fp);//返回当前位置
    //int fseek(FILE *fp,long offset,int whence);//定位，跟lseek一样
    //void rewind(FILE *fp);重新定位到开头
    //说明：对于文本文件（非二进制文件）不能以简单的字节偏移量来度量，应以字符来度量
    //所以文本文件的whence只能是SEEK_SET,offset要么是0,要么是ftell返回的。
    //off_t ftello(FILE *fp);//返回当前位置,以off_t为返回。
    //int fseeko(FILE *fp,off_t offset,int whence);//定位，跟lseek一样，以off_t作为参数。
    //-----------------------------定位流  结束-----------------------------------

    //-----------------------------读和写流 格式化的 开始-----------------------------------
    //格式化输出
    //int printf(const char* format,...);
    //int fprintf(FILE *fp,const char *format,...);
    //int dprintf(int fd,const char* format,...)
    //int sprint(char* buf,const char* format,....);写到内存中，不知顶缓冲大小
    //int snprintf(char* buf,size_t n,const char* format,....);写到内存中，指定缓冲大小
    //格式化输入
    //int scanf(const char *format,....)
    //int fscanf(FILE *fp,const char *format,....)
    //int sscanf(const char* buff,const char *format,....)
    //-----------------------------读和写流 格式化的 结束-----------------------------------




    //关闭文件流：
    //所有输入被丢弃，所有输出被刷新。系统自动分配的缓冲区被释放（自己定义的缓冲区需要自己free）
    //当exit或者main返回时，所有流会被系统关闭。
    fclose(fp);
    free(buff);
    return;
}