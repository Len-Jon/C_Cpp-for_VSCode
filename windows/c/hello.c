#include<stdio.h>
int main(void)
{
    printf("Hello, world!\n你好，世界！\n"); //因为Windows的编码比较特殊，所以需要用中文字符来检查配置效果
    char chs[10] = {0};
    scanf("%s", chs);
    printf("%s\n", chs);
    return 0;
}