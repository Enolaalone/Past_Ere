# C 文件读写

## 打开文件

您可以使用 **fopen( )** 函数来创建一个新的文件或者打开一个已有的文件，这个调用会初始化类型 **FILE** 的一个对象，类型 **FILE** 包含了所有用来控制流的必要的信息。下面是这个函数调用的原型：

```c
FILE *fopen( const char *filename, const char *mode );
```

| r    | 打开一个已有的文本文件，允许读取文件。                       |
| ---- | ------------------------------------------------------------ |
| w    | 打开一个文本文件，允许写入文件。如果文件不存在，则会创建一个新文件。在这里，您的程序会从文件的开头写入内容。如果文件存在，则该会被截断为零长度，重新写入。 |
| a    | 打开一个文本文件，以追加模式写入文件。如果文件不存在，则会创建一个新文件。在这里，您的程序会在已有的文件内容中追加内容。 |
| r+   | 打开一个文本文件，允许读写文件。                             |
| w+   | 打开一个文本文件，允许读写文件。如果文件已存在，则文件会被截断为零长度，如果文件不存在，则会创建一个新文件。 |
| a+   | 打开一个文本文件，允许读写文件。如果文件不存在，则会创建一个新文件。读取会从文件的开头开始，写入则只能是追加模式 |



## 关闭文件

为了关闭文件，请使用 fclose( ) 函数。函数的原型如下：

```
 int fclose( FILE *fp );
```

如果成功关闭文件，**fclose( )** 函数返回零，如果关闭文件时发生错误，函数返回 **EOF**。这个函数实际上，会清空缓冲区中的数据，关闭文件，并释放用于该文件的所有内存。EOF 是一个定义在头文件 **stdio.h** 中的常量。

C 标准库提供了各种函数来按字符或者以固定长度字符串的形式读写文件。

## 写入

### fputs（）

C 库函数 **int fputs(const char \*str, FILE \*stream)** 把字符串写入到指定的流 stream 中，但不包括空字符

```c
    FILE *pf= fopen("ABC.txt","w");
    char a[100]="你好！\n我爱你！";
    fputs(a,pf);
    fclose(pf);
```

## fprintf()格式化写入

C 库函数 **int fprintf(FILE \*stream, const char \*format, ...)** 发送格式化输出到流 stream 中

```c
    FILE *pf= fopen("ABC.txt","w");
    char a[100]="你好！\n我爱你！";
    fprintf(pf,"%s",a);
    fclose(pf);
```

## fwrite()数组写入

C 库函数 **size_t fwrite(const void \*ptr, size_t size, size_t nmemb, FILE \*stream)** 把 **ptr** 所指向的数组中的数据写入到给定流 **stream** 中。

- **ptr** -- 这是指向要被写入的元素数组的指针。
- **size** -- 这是要被写入的每个元素的大小，以字节为单位。//单字节
- **nmemb** -- 这是元素的个数，每个元素的大小为 size 字节。
- **stream** -- 这是指向 FILE 对象的指针，该 FILE 对象指定了一个输出流。

```c
   FILE *pf= fopen("ABC.txt","w");
    char a[100]="世界！\n我爱你！";
    fwrite(a,sizeof (char), strlen(a),pf);
    fclose(pf);
    return 0;
```

## 读取

### fgets()

C 库函数 **char \*fgets(char \*str, int n, FILE \*stream)** 从指定的流 stream 读取一行，并把它存储在 **str** 所指向的字符串内。当读取 **(n-1)** 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。

```c
    FILE *fp=fopen("./598854课程.txt","r");
    char a[100];
    fgets(a,100,fp);
    printf("%s",a);
    fclose(fp);
```

### fscanf()

**使用 fscanf 函数从文件中获取数据 :** 此处读取的数据格式是 “%s” , 遇到空格或回车 , 就当做一个新的字符串进行处理 ;

```c
    char a[1500];
//    fgets(a,100,fp);
    fscanf(fp,"%s",a);
    printf("%s\n",a);
    fclose(fp);
```

