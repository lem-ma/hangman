/* Hangman Version 1.1
 * Author: lem-ma
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char obtainchar(void)
{
    char b,c=getchar();
    if(c=='\n'||c=='\r'||c==EOF) return EOF;
    while((b=getchar())!='\n'&&b!='\r'&&b!=EOF);
    return c;
}

int hangman(char* word, int len)
{
    puts("Note: Enter <Tab><Enter> at any time to reveal the answer.\n");
    int keep=1,hyphen=0;
    char c,chosen[27],guessed[len+1],*dum;
    for(int i=0;i<27;i++) chosen[i]='\0';
    for(int i=0;i<len;i++)
        (word[i]=='-')?(guessed[i]=putchar('-'),hyphen++):
            (guessed[i]=putchar('_'));
    guessed[len]='\0';
    int nchance=6,ncorrect=hyphen,nchosen=0;
    printf(" \t6 more chances, %d more letters\n",len-ncorrect);
    while(keep)
    {
        fputs("Your guess (enter a lowercase letter): ",stdout);
        while((c=obtainchar())<'a'||c>'z'||strchr(chosen,c))
        {
            if(c=='\t') return 0;
            fputs("Invalid input! Please input again: ",stdout);
        }
        chosen[nchosen]=c;
        nchosen++;
        if((dum=strchr(word,c)))
            for(int i=dum-word;*dum;
                    ((*dum++)==c)?(ncorrect++,guessed[i++]=c):(i++));
        else nchance--;
        keep=(ncorrect!=len)&&(nchance!=0);
        printf("\n%s \t%d more chance(s), %d more letter(s)\nChosen: %s\n"\
                ,guessed,nchance,len-ncorrect,chosen);
    }
    puts("Game ends.");
    if(ncorrect==len) puts("Congratulations!");
    return 0;
}

int main(int argc, char* argv[])
{
    FILE* fp;
    if(argc==1) fp=fopen("wordlist.txt","rb");
    else fp=fopen(argv[1],"rb");
    if(!fp) puts("Wordlist not found!"),getchar(),exit(1);
    if(fseek(fp,0L,SEEK_END)==EOF) perror("error"),exit(1);
    size_t lSize=ftell(fp);
    rewind(fp);
    char buffer[lSize+1];
    if(lSize!=fread(buffer,sizeof(char),lSize,fp))
        fclose(fp),puts("read fails"),exit(1);
    fclose(fp);
    buffer[lSize]='\n';
    srand(time(NULL));
    puts("Hangman\nVersion 1.1 \tAuthor: lem-ma\n");
    int cont=1;
    while(cont)
    {
        size_t start,end,space,mrand=0;
        for(int i=0;i<lSize/RAND_MAX;i++) mrand+=rand();
        for(start=mrand%lSize;(start!=0)&&(buffer[start-1]!='\n');start--);
        int control=1;
        for(end=space=start;buffer[end]!='\n'&&buffer[end]!='\r';end++)
            if(control&&buffer[end]==' ') space=end,control=0;
        if(space==start)
            puts("Wrongly formatted wordlist!"),getchar(),exit(1);
        buffer[space]='\0';
        for(int i=start;(i<space)||hangman(buffer+start,space-start);i++)
        {
            if('A'<=buffer[i]&&'Z'>=buffer[i]) buffer[i]+='a'-'A';
            else if(('a'>buffer[i]||'z'<buffer[i])&&buffer[i]!='-')
                puts("Wrongly formatted wordlist!"),getchar(),exit(1);
        }
        buffer[space]=' ';
        fwrite(buffer+start,sizeof(char),end-start,stdout);
        puts("\n\nEnter \"q\" to exit, or otherwise to start a new game.");
        if(obtainchar()=='q') cont=0;
    }
    return 0;
}
