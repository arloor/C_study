//
// Created by arloor on 17-7-6.
//

#include "header/non_buffer_io.h"
#include<stdio.h>
#include<stdlib.h>
#include <fcntl.h>
#include <zconf.h>
#include <string.h>

/**
 * 用一个文件的生命周期来说明不带缓冲的文件IO
 * 包括create open read write close和lseek
 * @return
 */

void non_buff_io() {


    char *path = "../data/non_buffer_io.txt";
    // ------------------创建----------------------------------------
    // 这里使用creat和open分别实现
    int fd = creat(path, S_IRWXU | S_IRWXG | S_IRWXO);//第二个参数是mode，定义权限，所有者/组/其他 755
    //int fd=open(path,O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXG|S_IRWXO);//与上面的完全相同。这里第三个参数mode是可选的
    //O_CREAT:若不存在则创建;O_WRONLY:只允许写;O_RDWR:读写;O_TRUNK:如果文件存在，且具有写的能力，则截断为0

    //上面两个有问题是：文件描述符只能写不能读，改善如下：（O_WRONLY->O_RDWR）
    fd = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);//O_WRONLY->O_RDWR,这样就有写的能力了。


    //-------------------写--------------------------------------------
    char *towrite1 = "1st_line：ilovelfy\n";
    char *towrite2 = "2nd_line：diff\n";
    size_t len1 = strlen(towrite1);
    size_t len2 = strlen(towrite2);

    printf("将要写入长度为%d的:%s", len1, towrite1);
    write(fd, towrite1, len1);//写第一行
    printf("将要写入长度为%d的:%s", len2, towrite2);
    write(fd, towrite2, len2);//写第二行
    printf("\n");

    //--------------------读----------------------------------------------
    //首先穿插lseek和文件偏移量的介绍
    //偏移量是指当前要读或者写的字节相对文件开头的偏移量（字节数），
    //文件的读写都是从当前偏移量开始的，并且每次读写都会递增所读写的字节数。
    //但是任何read/write造成的偏移量增加都不会使偏移量超过文件末尾字节的偏移量（即使SEEK_CUR+reed_size>SEEK_END）
    //没有O_APPEND选项的打开，初始偏移量都为0;有O_APPEND则偏移量为SEEK_END。
    //lseek设置偏移量时，偏移量可以超出文件末尾(可以大于SEEK_END)，但不能小于文件头（不能<0）。下面有lseek超出文件末尾的例子。
    off_t off = lseek(fd, 0, SEEK_CUR);//这是当前的偏移
    printf("完成两次写后的偏移量为：%d\n", off);

    printf("将偏移设为0，以便从头读\n");
    off = lseek(fd, 0, SEEK_SET);//将偏移设为0
    printf("当前的偏移量为：%d\n", off);
    printf("\n");


    char *read_result = (char *) calloc(len1, sizeof(char));
    read(fd, read_result, len1);
    printf("读到：\n%s", read_result);
    off = lseek(fd, 0, SEEK_CUR);//这是当前的偏移
    printf("当前的偏移量为：%d\n", off);
    printf("\n");

    read(fd, read_result, len2);
    printf("读到：\n%s", read_result);
    off = lseek(fd, 0, SEEK_CUR);//这是当前的偏移
    printf("当前的偏移量为：%d\n", off);
    printf("     * 可以看到这次读到的有部分第一行的东西，原因是：我们使用了同一个内存空间来保存两次读的结果\n"
                   "     * 所以：第二次读的结果覆盖了第一次读的结果，但是没有覆盖完全，因为没有那么长。剩下部分第一行的得以保留\n"
                   "     * 要避免出现这种情况，两种解决方案:\n"
                   "     * 1.使用不同的内存空间保存不同的行，不同内存空间可以使用数组来管理\n"
                   "     * 2.使用一个内存空间，那么需要每次使用完此空间，就把所有的字节置为'\\0'，下面有例子\n\n");
    printf("\n");

    //对于控制台输出的说明
    /**
     * 第二次读之后的输出为：
     *  读到：
        2nd_line：diff
        lfy
        当前的偏移量为：36
     * 可以看到这次读到的有部分第一行的东西，原因是：我们使用了同一个内存空间来保存两次读的结果
     * 所以：第二次读的结果覆盖了第一次读的结果，但是没有覆盖完全，因为没有那么长。剩下部分第一行的得以保留
     * 要避免出现这种情况，两种解决方案:
     * 1.使用不同的内存空间保存不同的行，不同内存空间可以使用数组来管理
     * 2.使用一个内存空间，那么需要每次使用完此空间，就把所有的字节置为'\0'，下面有例子
     */

    off_t end = lseek(fd, 0, SEEK_END);
    //下面使用lseek来超出文件末尾
    printf("下面使用lseek来超出文件末尾");
    off = lseek(fd, 100, SEEK_END);

    printf("当前的偏移量为：%d>%d  已经超出末尾\n", off, end);
    //下面尝试读看看发生什么
    //读之前首先把内存空间置为'\0'
    int i = 0;
    while (*(read_result + i) != '\0') {
        *(read_result + i) = '\0';
        i++;
    }
    read(fd, read_result, len1);
    printf("读到：\n%s", read_result);
    printf("读到为空\n");//读到为空
    off = lseek(fd, 0, SEEK_CUR);//这是当前的偏移
    printf("当前的偏移量为：%d\n", off);//发现超过文件尾的读将偏移量置为文件末尾
    printf("发现超过文件尾的读将偏移量置为文件末尾\n");
    printf("\n");


    //下面重新使用lseek来超出文件末尾
    printf("下面使用lseek来超出文件末尾");
    off = lseek(fd, 20, SEEK_END);
    printf("当前的偏移量为：%d>%d  已经超出末尾\n", off, end);
    //下面尝试写看看会发生什么
    char *end_over_write = "end_over_write\n";
    size_t len_end_over_write = strlen(end_over_write);
    printf("将要写入长度为%d的:%s", len_end_over_write, end_over_write);
    write(fd, end_over_write, len_end_over_write);
    off = lseek(fd, 0, SEEK_CUR);//这是当前的偏移
    printf("当前的偏移量为：%d\n", off);//可以看到是从超过末尾的当前偏移开始写的，并没有恢复到文件尾
    printf("可以看到是从超过末尾的当前偏移开始写的，并没有恢复到文件尾\n");
    printf("\n");

    //下面考虑95-115这段偏移里有什么
    //首先一次性全读
    printf("首先一次性全读\n");
    char *all_content = (char *) calloc(1024, sizeof(char));
    off = lseek(fd, 0, SEEK_SET);//这是当前的偏移
    read(fd, all_content, 1024);
    printf("%s", all_content);
    //并没有读到超过文件末尾的一行，可见超过末尾的读不算在文件里啊，
    // 可是用程序打开b.txt,是看得到超过文件末尾的写的。
    printf("注意：no 超过末尾的 被打印\n");


    //研究了一下：
    //使用od命令查看文件内容
    printf("研究为什么：使用od命令查看文件内容\n");
    fflush(stdout);//这个控制上面的输出绝对在下面system之前。刷新的重要性啊
    system("od -c ../data/non_buffer_io.txt");
    //发现95-115为' ',这就是读失败的原因。
    //另外发现如果write的内容中有'\0',同样会截断写。代码就不体现了。
    //这很正常，因为'\0'结束字符串嘛。
    //更新：后来发现，这种超过文件长度之后再写造成的连续'\0'被称为空洞
    //
    //至于原子性操作pread，pwrite并没有用代码体现，现在总结如下\n");
    //ssize_t pread(int fd,void *buf,size_t nbytes,off_t offest);\n");
    //ssize_t pwrite(int fd,void *buf,size_t nbytes,off_t offest);\n");
    //原子性的定位然后IO:无法中断定位和读写，不会因为别的线程改变了偏移量而错误\n");
    //读和写不改变偏移量\n");
    //
    //另外，apue上谈到O_APEEND这个标记并不是简单地定位到文件末尾然后再读写\n");
    //O_APPEND的读写过程也是原子性的，就是定位和读写不可中断\n");
    printf("//发现95-115为'\\0',这就是读失败的原因。\n");
    printf("//另外发现如果write的内容中有'\\0',同样会截断写。代码就不体现了。\n");
    printf("//这很正常，因为'\\0'结束字符串嘛。\n至此，研究结束\n");
    printf("//更新：后来发现，这种超过文件长度之后再写造成的连续'\\0'被称为空洞\n");
    printf("\n");
    printf("//至于原子性操作pread，pwrite并没有用代码体现，现在总结如下\n");
    printf("//ssize_t pread(int fd,void *buf,size_t nbytes,off_t offest);\n");
    printf("//ssize_t pwrite(int fd,void *buf,size_t nbytes,off_t offest);\n");
    printf("//原子性的定位然后IO:无法中断定位和读写，不会因为别的线程改变了偏移量而错误\n");
    printf("//读和写不改变偏移量\n");
    printf("\n");
    printf("//另外，apue上谈到O_APEEND这个标记并不是简单地定位到文件末尾然后再读写\n");
    printf("//O_APPEND的读写过程也是原子性的，就是定位和读写不可中断\n");
    printf("\n");



    //-----------------------关闭---------------------------------
    close(fd);//

    return;
}