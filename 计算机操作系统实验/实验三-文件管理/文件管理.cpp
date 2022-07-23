#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include <stdbool.h>

#define BLOCKSIZE      1024         // ���̿��С
#define SIZE           1024000      // 1000�����̿鹹����������̿ռ�
#define END            65535        // FAT���ļ�������־
#define FREE           0            // FAT���̿���б�־
#define ROOTBLOCKNUM   2            //������ǰ����������Ŀ¼�ļ�
#define MAXOPENFILE    10           //���ͬʱ���ļ�����
#define ERROR          -1
#define OK             1
#define MAXTEXT        2000         //text����С

//�ļ����ƿ�(Ŀ¼�
typedef struct FCB{
    char filename[8];               //�ļ���
    char exname[3];                 //�ļ���չ��
    unsigned char attribute;        //�ļ������ֶΣ�0��Ŀ¼�ļ���1�������ļ�
    unsigned short time;            //�ļ�����ʱ��
    unsigned short date;            //�ļ���������
    unsigned short first;           //�ļ���ʼ�̿��
    unsigned long length;           //�ļ����ȣ��ֽ�����
    char free;                      //��ʾĿ¼���Ƿ�Ϊ�գ���ֵΪ0�����ʾ�գ�ֵΪ1����ʾ�ѷ��䡣
}fcb;

typedef struct FAT{
    unsigned short id;              //unsigned short ռ�����ֽڣ�0-65535
}fat;

typedef struct USEROPEN{
    char filename[8];               //�ļ���
    char exname[3];                 //�ļ���չ��
    unsigned char attribute;        //�ļ������ֶΣ�0��Ŀ¼�ļ���1�������ļ� ������
    unsigned short time;            //�ļ�����ʱ��
    unsigned short date;            //�ļ���������
    unsigned short first;           //�ļ���ʼ�̿��
    unsigned long length;           //�ļ����ȣ��ֽ�����
    //�������ļ�FCB�����ݣ������Ǽ�¼�й��ļ�ʹ�õĶ�̬��Ϣ��
    int father;                     //��Ŀ¼���ļ�������
    char dir[80];                   //���ļ�����·�����Ա���ټ��ָ���ļ��Ƿ��Ѿ��򿪡���ô��飿����
    int count;                      //��дָ���λ��
    char fcbstate;                  //�ļ���FCB�Ƿ��Ѿ����޸ģ�����޸��ˣ�����Ϊ1������Ϊ0
    char topenfile;                 //�򿪱����Ƿ�Ϊ�գ���ֵΪ0�����ʾ�ѱ�ռ��
}useropen;

typedef struct BLOCK0{
    char information[200];          //�洢һЩ������Ϣ������̿��С�����̿�������
    unsigned short root;            //��Ŀ¼�ļ�����ʼ�̿��
    unsigned char* startblock;      //�����������������ʼλ��
}block0;

//ȫ�ֱ�������
unsigned char *myvhard;             //ָ��������̵���ʼ��ַ
useropen openfile[MAXOPENFILE];      //�û����ļ������飬���ͬʱ��10���ļ�
int curdir;                         //��ǰĿ¼���ļ�������fd
char currentdir[80];                //��¼��ǰĿ¼��Ŀ¼��
unsigned char* startp;              //��¼�����������������ʼλ��
time_t c_time;                      //�ļ�ϵͳ����ʱ��
char filesys_name[] = "FAT16";      //�ļ�ϵͳ�ļ����ļ���
unsigned char *buf;

void startsys();                    //��ʼ���ļ�ϵͳ
void my_format();                   //��������̽��и�ʽ��
int my_cd(char *dirname);          //����ǰĿ¼��Ϊָ����Ŀ¼
void my_mkdir(char *dirname);       //�ڵ�ǰĿ¼�´�����Ϊdirname����Ŀ¼
void my_rmdir(char *dirname);       //�ڵ�ǰĿ¼��ɾ����Ϊdirname����Ŀ¼
void my_ls();                       //��ʾ��ǰĿ¼�����ݣ���Ŀ¼���ļ���Ϣ��
int my_create(char *filename);      //������Ϊfilename�����ļ���
void my_rm(char *filename);         //ɾ����Ϊfilename���ļ�
int my_open(char *filename);        //�򿪵�ǰĿ¼����Ϊfilename���ļ�
void my_close(int fd);              //�ر�֮ǰ��my_open()�򿪵��ļ�������Ϊfd���ļ�
int my_write(int fd);               //���û�ͨ���������������д��fd��ָ�����ļ���
int do_write(int fd, char *text, int len, char wstyle); //���������е�����д��ָ���ļ���
int myread(int fd, int len);       //����ָ���ļ��дӶ�дָ�뿪ʼ�ĳ���Ϊlen�����ݵ��û��ռ���
int do_read(int fd, int len, char *text);   //����ָ���ļ��дӶ�дָ�뿪ʼ�ĳ���Ϊlen�����ݵ��û��ռ��text��
void my_exitsys();                  //�˳��ļ�ϵͳ
void extractDir(char *dirname, char * dir,char *filename);
int findFreeBlock();

//�����ļ�����startsys()
void startsys()
{
    int pos = 0; //��¼д��������̵�λ��
    int i,j;
    FILE* fp;
    fcb* root;
    block0 *guide;

    //�����ļ�ϵͳ�����������
    if((fp = fopen(filesys_name,"r")) == NULL)
    {
        printf("�ļ�ϵͳ�����ڣ��������ļ�ϵͳ\n");
        my_format();
    }
    else
    {
        printf("�ļ�ϵͳ�Ѵ��ڣ�����д��\n");
        for(i = 0;i < (SIZE / BLOCKSIZE);i ++)
        {
            fread(buf,BLOCKSIZE,1,fp);
            for(j = 0;j < BLOCKSIZE;j ++)
            {
                myvhard[pos + j] = buf[j];
            }
            pos += BLOCKSIZE;
        }
        fclose(fp);
    }

    /*
        char *strcpy(char* dest, const char *src);
        params:
            dest:Ŀ���ַ��
            src��Դ�ַ�����ַ
        ˵����"="��ֵ��ʽֻ�ǽ�Դ��ַ��ָ�븳ֵ����Ŀ�ĵ�ַָ�룬����ָ��ͬһ�ַ�����
              strcpy�ǽ�Դ��ַ����ַ������Ƶ���Ŀ���ַ�ռ䣬����ָ��ͬλ�õ������ַ���
    */
    root = (fcb*)(myvhard + 5 * BLOCKSIZE);
    strcpy(openfile[0].filename, root->filename);
    strcpy(openfile[0].exname, root->exname);
    openfile[0].attribute = root->attribute;
    openfile[0].time = root->time;
    openfile[0].date = root->date;
    openfile[0].first = root->first;
    openfile[0].length = root->length;
    //printf("In startsys,openfile[0].length:%d\n",openfile[0].length);
    openfile[0].father = 0;
    strcpy(openfile[0].dir, "\\root\\");
    openfile[0].count = 0;
    openfile[0].fcbstate = 0;
    openfile[0].topenfile = 1;  //�򿪱����Ƿ�Ϊ�գ�1Ϊ�ǿգ�0Ϊ��
}


//���̸�ʽ������my_format()
void my_format()
{
    //���ﶼֻ���ô�������̿ռ��з���ռ����������Fat1��fat2������ֱ�ӳɱ���
    FILE *fp;
    block0* guide;
    fat *fat1,*fat2;
    fcb *root;
    int i;
    char buf[SIZE];
    time_t now_time;
    struct tm *lc_time;

    guide = (block0 *)myvhard;
    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat2 = (fat*)(myvhard + BLOCKSIZE * 3);
    root = (fcb*)(myvhard + BLOCKSIZE * 5);

    //��ʼ��������
    strcpy(guide->information,"ÿ����Ĵ�С��1024�ֽڣ������Ŀ��1000��");
    guide->root = 5;
    guide->startblock = (unsigned char *)root;          //���������������ʼλ��

    //��ʼ��fat1,fat2,ǰ5�����̿��Ѿ������ȥ��
    for(i = 0;i < 5;i++)
    {
        fat1->id = END;
        fat2->id = END;
        fat1 ++;
        fat2 ++;
    }
    fat1->id = 6;
    fat2->id = 6;
    fat1++;
    fat2++;
    fat1->id = END;
    fat2->id = END;
    fat1++;
    fat2++;
    for(i = 7;i < (SIZE / BLOCKSIZE);i++)
    {
        fat1->id = FREE;
        fat2->id = FREE;
        fat1++;
        fat2++;
    }

    //��ʼ����Ŀ¼�ļ�
    strcpy(root->filename, ".");
    strcpy(root->exname,"");
    root->attribute = 0;
    /*
        time_t time(time_t *calptr)
        parameters:
            calptc:time_t���ͱ�����ַ
        return:
            ��1970-1-1,00:00:00�����ڵ�����
    */
    time(&now_time);                //ʱ�䣺��
    /*
        struct tm *localtime(const time_t * calptr);
        params:
            calptc:time_t���ͱ�����ַ;
        returns:
            ����һ���ṹ��
            �������https://blog.csdn.net/qq_22122811/article/details/52741483
    */
    lc_time = localtime(&now_time);
    root->time = lc_time->tm_hour * 2048 + lc_time->tm_min * 32 + lc_time->tm_sec / 2;
    root->date = (lc_time->tm_year - 80) * 512 + (lc_time->tm_mon + 1) * 32 + lc_time->tm_mday;
    root->first = 5;
    root->length = 2 * sizeof(fcb);   //Ӧ�����ļ��峤�Ȱ�
    root->free = 1;   //��ʾĿ¼���Ƿ�Ϊ�գ�0��ʾ�գ�1��ʾ�ѷ��� ������

    root++;
    time(&now_time);
    lc_time = localtime(&now_time);
    strcpy(root->filename, "..");
    strcpy(root->exname, "");
    root->attribute = 0;
    root->time = lc_time->tm_hour * 2048 + lc_time->tm_min * 32 + lc_time->tm_sec / 2;
    root->date = (lc_time->tm_year - 80) * 512 + (lc_time->tm_mon + 1) * 32 + lc_time->tm_mday;
    root->first = 5;
    root->length = 2 * sizeof(fcb);
    root->free = 1;
    //���ļ�ϵͳ�е��ļ�д�����������
    /*
        FILE * fopen ( const char * filename, const char * mode )
        params:g g
            filename: Ҫ�򿪵��ļ���
            mode: Ҫ���еĲ���
        return:
            �ļ������򷵻��ļ���ָ�룬���򷵻ؿ�ָ��
    */
    fp = fopen(filesys_name,"w");
    /*
        size_t fwrite ( const void * ptr, size_t siz                                                                                                        e, size_t count, FILE * stream );
        params:
            ptr��ָ��Ҫ��д�������
            size��ÿ�����ݵĴ�С��
            count�����ݵĸ���
            stream������ļ���ָ��

    */
    fwrite(myvhard,SIZE,1,fp);
    fclose(fp);
}

//���ĵ�ǰĿ¼����
int my_cd(char *dirname)
{
    char *dir,*next;
    int fd,tmp,father;

    dir = strtok(dirname,"\\");
    next = strtok(NULL,"\\");
    //����!next��Ŀ�����жϺ����Ƿ�������Ŀ¼
    if(strcmp(dir,".") == 0)
    {
        if(!next)
        {
            printf("���ǵ�ǰĿ¼��\n");
            return OK;
        }
        else
        {
            dir = next;
            next = strtok(NULL,"\\");
        }
    }
    else if(strcmp(dir,"..") == 0)
    {
        if(curdir)  //�ж��ǲ��Ǹ�Ŀ¼,��Ŀ¼���û��򿪱���Ϊ0
        {
            tmp = openfile[curdir].father;      //��Ŀ¼���ô����Ǳ��������ڴ�������
            my_close(curdir);
            curdir = tmp;
            if(!next)
                return OK;
            else
            {
                dir = next;
                next = strtok(NULL,"\\");
            }
        }
        else
        {
            printf("��ǰĿ¼�Ǹ�Ŀ¼!\n");
            return ERROR;
        }
    }
    else if(strcmp(dir,"root") == 0)
    {
        while(curdir)   //ѭ��ֱ����ǰĿ¼Ϊ��Ŀ¼
        {
            tmp = openfile[curdir].father;
            my_close(curdir);
            curdir = tmp;
        }
        dir = next;
        next = strtok(NULL,"\\");
    }
    while(dir)
    {
        //���fd�������򿪵�Ŀ¼��Ϊ��ǰĿ¼
        fd = my_open(dir);
        if(openfile[fd].attribute)
        {
            printf("�ⲻ��Ŀ¼��\n");
            return ERROR;
        }
        else
        {
            if(fd == -2)
                return ERROR;
            else if(fd != ERROR)
                curdir = fd;
            else
            {
                printf("��Ŀ¼ʧ��!\n");
                return ERROR;
            }
        }
        dir = next;
        next = strtok(NULL,"\\");
    }
    //printOpenFile();
    return OK;
}

//������Ŀ¼����
void my_mkdir(char* dirname)
{
    int num,blk_num,i,fd,value,father;
    fcb *fcbptr, *pos;
    fat *fat1, *fat2;
    time_t now;
    struct tm *lc_time;
    char text[MAXTEXT];
    char dir[80] = "",filename[20] ,dir_tmp[80];
    char *fname,*exname;

    //����dir_tmp����Ϊ����ֱ�Ӱ�openfile[curdir].dir����my_cd()
    strcpy(dir_tmp,openfile[curdir].dir);
    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat2 = (fat*)(myvhard + 3 * BLOCKSIZE);
    //��ȡ��ָ��Ŀ¼�ʹ�����Ŀ¼�������л���ָ��Ŀ¼
    extractDir(dirname,dir,filename);
    if(!(strcmp(dir,"") == 0))
        value = my_cd(dir);
    if(value == ERROR)
        return;
    fname = strtok(filename,".");
    exname = strtok(NULL,".");
    if(exname != NULL)
    {
        printf("Ŀ¼û��exname��\n");
        my_cd(dir_tmp);
        return;
    }
    //��ȡ��ǰĿ¼�����ݣ��ж���Ŀ¼�Ƿ����
    openfile[curdir].count = 0;
    num = do_read(curdir,openfile[curdir].length,text);
    fcbptr = (fcb*)text;
    for(i = 0; i < (num / sizeof(fcb)); i++)
    {
        if((!strcmp(fcbptr->filename,fname)))
        {
            printf("Ҫ�������ļ����Ѵ��ڣ�\n");
            return;
        }
        fcbptr ++;
    }
    //Ѱ�ҿ���Ŀ¼���λ��
    fcbptr = (fcb *)text;
    for(i = 0; i < (num / sizeof(fcb)); i++)
    {
        if(fcbptr->free == 0)
            break;
        fcbptr++;
    }
    //Ѱ�ҿ��д��̿�
    blk_num = findFreeBlock();
    if(blk_num == ERROR)
        return;
    (fat1 + blk_num)->id = END;
    (fat2 + blk_num)->id = END;
    //��ʼ��Ŀ¼�ļ���fcb
    strcpy(fcbptr->filename, fname);
    strcpy(fcbptr->exname, "");
    fcbptr->attribute = 0;
    time(&now);
    lc_time = localtime(&now);
    fcbptr->time = lc_time->tm_hour * 2048 + lc_time->tm_min * 32 + lc_time->tm_sec / 2;
    fcbptr->date = (lc_time->tm_year - 80) * 512 + (lc_time->tm_mon + 1) * 32 + lc_time->tm_mday;
    fcbptr->first = blk_num;
    fcbptr->length = 2 * sizeof(fcb);
    fcbptr->free = 1;
    //��Ŀ¼ָ�붨λ������Ŀ¼��
    openfile[curdir].count = i * sizeof(fcb);
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);

    //���µ�ǰĿ¼�е�һ��fcb������
    fcbptr = (fcb*)text;
    fcbptr->length = openfile[curdir].length;
    openfile[curdir].count = 0;
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);

    //����Ŀ¼�ļ�������"."��".."����Ŀ¼��
    fd = my_open(fname);
    if(fd == ERROR)
        return;
    fcbptr = (fcb*)malloc(sizeof(fcb));
    strcpy(fcbptr->filename, ".");
    strcpy(fcbptr->exname, "");
    fcbptr->attribute = 0;
    time(&now);
    lc_time = localtime(&now);
    fcbptr->time = lc_time->tm_hour * 2048 + lc_time->tm_min * 32 + lc_time->tm_sec / 2;
    fcbptr->date = (lc_time->tm_year - 80) * 512 + (lc_time->tm_mon + 1) * 32 + lc_time->tm_mday;
    fcbptr->first = blk_num;
    fcbptr->length = 2 * sizeof(fcb);
    fcbptr->free = 1;
    do_write(fd, (char *)fcbptr, sizeof(fcb),2);

    pos = (fcb*)text;
    strcpy(fcbptr->filename, "..");
    strcpy(fcbptr->exname, "");
    fcbptr->attribute = pos->attribute;
    fcbptr->time = pos->time;
    fcbptr->date = pos->date;
    fcbptr->first = pos->first;
    fcbptr->length = pos->length;
    fcbptr->free = 1;
    do_write(fd, (char *)fcbptr, sizeof(fcb), 2);
    my_close(fd);

    //���µ�ǰĿ¼�ĸ�Ŀ¼�и���ĳ���
    father = openfile[curdir].father;
    openfile[father].count = father;
    num = do_read(father,openfile[father].length,text);
    fcbptr = (fcb*)text;
    //printFcb(father);
    for(i = 0; i < (num / sizeof(fcb)); i++)
    {
        if((!strcmp(fcbptr->filename,openfile[curdir].filename)) && (!strcmp(fcbptr->exname,openfile[curdir].exname)))
        {
            fcbptr->length = openfile[curdir].length;
            break;
        }
        fcbptr ++;
    }
    openfile[father].count = i * sizeof(fcb);
    do_write(father,(char *)fcbptr, sizeof(fcb), 2);
    openfile[curdir].fcbstate = 1;
    //printFcb(father);
    //printOpenFile();

    my_cd(dir_tmp);
}

//ɾ����Ŀ¼����
void my_rmdir(char *dirname)
{
    int num1,num2,blk_num,i,fd,j;
    fcb *fcbptr,*fcbptr2;
    fat *fat1,*fat2,*fatptr1,*fatptr2;
    char text[MAXTEXT],text2[MAXTEXT];
    char dir[80] = "",filename[8] = "",dir_tmp[80] = "";

    //����dir_tmp����Ϊ����ֱ�Ӱ�openfile[curdir].dir����ȥ
    strcpy(dir_tmp,openfile[curdir].dir);
    //��ȡ·����Ŀ¼��
    extractDir(dirname,dir,filename);
    if(!(strcmp(dir,"") == 0))
        my_cd(dir);
    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat2 = (fat*)(myvhard + 3 * BLOCKSIZE);
    //�ж�Ҫɾ�����ǲ��ǵ�ǰĿ¼���߸�Ŀ¼
    if(strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0)
    {
        printf("�޷�ɾ����ǰĿ¼�͸�Ŀ¼��\n");
        return;
    }
    //��ȡ��Ŀ¼�ļ�����
    openfile[curdir].count = 0;
    num1 = do_read(curdir, openfile[curdir].length, text);
    fcbptr = (fcb*)text;
    for(i = 0; i < (num1 / sizeof(fcb)); i ++)
    {
        if(strcmp(fcbptr->filename, filename) == 0 && strcmp(fcbptr->exname, "") == 0)
            break;
        fcbptr++;
    }
    if( i == (num1 / sizeof(fcb)))
    {
        printf("Ҫɾ����Ŀ¼�����ڣ�\n");
        return;
    }

    //��Ҫɾ�����ļ�
    fd = my_open(filename);
    num2 = do_read(fd, openfile[fd].length, text2);
    fcbptr2 = (fcb*)text2;
    //�ж�ָ���ļ��ܲ���ɾ��
    for(j = 0; j < (num2 / sizeof(fcb)); j++)
    {
        if(strcmp(fcbptr2->filename, ".") && strcmp(fcbptr2->filename, "..") && strcmp(fcbptr2->filename, ""))
        {
            my_close(fd);
            printf("ɾ����Ŀ¼ʧ�ܡ�Ŀ¼��Ϊ�գ�\n");
            return;
        }
        fcbptr2++;
    }
    //����ָ��Ŀ¼ռ�ݵĴ��̿�
    blk_num = openfile[fd].first;
    while(blk_num != END)
    {
        fatptr1 = fat1 + blk_num;
        fatptr2 = fat2 + blk_num;
        blk_num = fatptr1->id;
        fatptr1->id = FREE;
        fatptr2->id = FREE;
    }
    my_close(fd);
    strcpy(fcbptr->filename, "");
    fcbptr->free = 0;
    openfile[curdir].count = i * sizeof(fcb);
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);
    openfile[curdir].fcbstate = 1;

    my_cd(dir_tmp);
}

//��ʾĿ¼����
void my_ls()
{
    fcb *fcbptr;
    char text[MAXTEXT];
    int num, i;

    openfile[curdir].count = 0;
    num = do_read(curdir, openfile[curdir].length, text);
    fcbptr = (fcb *)text;
    for(i = 0; i < num / sizeof(fcb); i++)
    {
        if(fcbptr->free)
        {
            if(!fcbptr->attribute)
                printf("%s\\\t\t<DIR>\t\t%d/%d/%d\t%02d:%02d:%02d\n", fcbptr->filename, (fcbptr->date >> 9) + 1980, (fcbptr->date >> 5) & 0x000f, fcbptr->date & 0x001f, fcbptr->time >> 11, (fcbptr->time >> 5) & 0x003f, fcbptr->time & 0x001f * 2);
            else
            {
                printf("%s.%s\t\t%dB\t\t%d/%d/%d\t%02d:%02d:%02d\t\n", fcbptr->filename, fcbptr->exname, (int)(fcbptr->length), (fcbptr->date >> 9) + 1980, (fcbptr->date >> 5) & 0x000f, fcbptr->date & 0x001f, fcbptr->time >> 11, (fcbptr->time >> 5) & 0x3f, fcbptr->time & 0x1f * 2);
            }
        }
        fcbptr++;
    }
}

//�����ļ�����
int my_create(char *dirname)
{
    int num,blk_num,i,father;
    time_t now;
    struct tm *lc_time;
    fat *fat1,*fat2;
    fcb *pos; //pos������λ��������ʲôĿ¼��
    char *fname,*exname;
    char dest_dir[80] = "",filename[20] = "",text[MAXTEXT] = "",dir_tmp[80] = ""; //Ҫ�����ļ���Ŀ¼

    strcpy(dir_tmp,openfile[curdir].dir);
    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat2 = (fat*)(myvhard + 3 * BLOCKSIZE);
    extractDir(dirname, dest_dir, filename);
    if(!(strcmp(dest_dir,"") == 0))
        my_cd(dest_dir);
    fname = strtok(filename,".");
    exname = strtok(NULL,".");
    if(strcmp(fname,"") == 0)
    {
        printf("�ļ���Ϊ�գ�\n");
        return ERROR;
    }
    if(!exname)
    {
        printf("�ⲿ����Ϊ�գ�\n");
        return ERROR;
    }

    //Ҫ������Ŀ¼�ļ����Ƿ��Ѿ���ͬ���ļ�,��Ŀ¼�ļ��д洢�����ļ���FCB
    openfile[curdir].count = 0;
    num = do_read(curdir,openfile[curdir].length,text);
    if(num == ERROR)
    {
        printf("��ȡ���ļ�ʧ�ܣ�\n");
        return ERROR;
    }
    pos = (fcb*)text;
    for(i = 0; i< (num / sizeof(fcb)); i++)
    {
        //�����Ƿ���ͬ���ļ�
        if((!strcmp(pos->filename,fname)) && (!(strcmp(pos->exname,exname))))
        {
            printf("Ҫ�������ļ����Ѵ��ڣ�\n");
            return ERROR;
        }
        pos ++;
    }

    //ȷ����û�������ļ���Ȼ��ʼ�����ļ���
    //Ҫ�ڸ�Ŀ¼��������ļ���Ŀ¼��
    pos = (fcb *)text;
    for(i = 0; i < num / sizeof(fcb); i++)
    {
        if(pos->free == 0)
            break;
        pos++;
    }
    blk_num = findFreeBlock();
    if(blk_num == ERROR)
        return ERROR;
    (fat1 + blk_num)->id = END;
    (fat2 + blk_num)->id = END;
    //��ʼ�����ļ���fcb
    strcpy(pos->filename, fname);
    strcpy(pos->exname, exname);
    pos->attribute = 1;
    time(&now);
    lc_time = localtime(&now);
    pos->time = lc_time->tm_hour * 2048 + lc_time->tm_min * 32 + lc_time->tm_sec / 2;
    pos->date = (lc_time->tm_year - 80) * 512 + (lc_time->tm_mon + 1) * 32 + lc_time->tm_mday;
    pos->first = blk_num;
    pos->length = 0;   //Ӧ�����ļ��峤�Ȱ�
    pos->free = 1;   //��ʾĿ¼���Ƿ�Ϊ�գ�0��ʾ�գ�1��ʾ�ѷ���

    openfile[curdir].count = i * sizeof(fcb);
    do_write(curdir, (char *)pos, sizeof(fcb), 2);

    //���µ�ǰĿ¼�ĵ�һ��Ŀ¼��
    pos = (fcb *)text;
    pos->length = openfile[curdir].length;
    openfile[curdir].count = 0;
    do_write(curdir, (char *)pos, sizeof(fcb), 2);
    openfile[curdir].fcbstate = 1;

    //���¸�Ŀ¼�еĵ�ǰĿ¼��Ŀ¼��
    father = openfile[curdir].father;
    openfile[father].count = father;
    num = do_read(father,openfile[father].length,text);
    pos = (fcb*)text;
    //printFcb(father);
    for(i = 0; i < (num / sizeof(fcb)); i++)
    {
        if((!strcmp(pos->filename,openfile[curdir].filename)) && (!strcmp(pos->exname,openfile[curdir].exname)))
        {
            pos->length = openfile[curdir].length;
            break;
        }
        pos ++;
    }
    openfile[father].count = i * sizeof(fcb);
    do_write(father,(char *)pos, sizeof(fcb), 2);

    my_cd(dir_tmp);
}

//ɾ���ļ�����
void my_rm(char *dirname)
{
    fcb *pos;
    fat *fat1, *fat2, *fatptr1, *fatptr2;
    char *fname, *exname, text[MAXTEXT];
    int num,i,blk_num;
    char dir[80] = "",filename[20] = "",dir_tmp[80] = "";

    strcpy(dir_tmp,openfile[curdir].dir);
    //��ȡ·����Ŀ¼��
    extractDir(dirname,dir,filename);
    if(!(strcmp(dir,"") == 0))
        my_cd(dir);
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    fname = strtok(filename, ".");
    exname = strtok(NULL, ".");
    if(strcmp(fname,"") == 0)
    {
        printf("�ļ���Ϊ�գ�\n");
        return;
    }
    if(!exname)
    {
        printf("�ⲿ����Ϊ�գ�\n");
        return;
    }
    openfile[curdir].count = 0;
    num = do_read(curdir, openfile[curdir].length, text);
    pos = (fcb *)text;
    for(i = 0; i < (num / sizeof(fcb)); i++)
    {
        if(strcmp(pos->filename, fname) == 0 && strcmp(pos->exname, exname) == 0)
            break;
        pos++;
    }
    if(i == num / sizeof(fcb))
    {
        printf("�����ļ������ڡ�\n");
        return;
    }
    blk_num = pos->first;
    while(blk_num != END)
    {
        fatptr1 = fat1 + blk_num;
        fatptr2 = fat2 + blk_num;
        blk_num = fatptr1->id;
        fatptr1->id = FREE;
        fatptr2->id = FREE;
    }
    strcpy(pos->filename, "");
    pos->free = 0;
    openfile[curdir].count = i * sizeof(fcb);
    do_write(curdir, (char *)pos, sizeof(fcb), 2);
    openfile[curdir].fcbstate = 1;


    my_cd(dir_tmp);
}

//���ļ�����
int my_open(char* dirname)
{
    int i,num,value;
    int fd = -1;
    fcb* fcbptr;
    char *fname,exname[3] = "",*tmp;
    char dest_dir[80] = "",filename[20] = "",text[MAXTEXT]; //Ҫ�����ļ���Ŀ¼

    if(strlen(dirname) == 0)
        return -2;
    extractDir(dirname, dest_dir, filename);
    if(!(strcmp(dest_dir,"") == 0))
        value = my_cd(dest_dir);
    fname = strtok(filename,".");
    tmp = strtok(NULL,".");
    /*
        char* strtok(char* str,constchar* delimiters );
        params:
            str:Ҫ�ָ���ַ�����
            delimiters:���ڷָ�ķ���
        return:
             s��ͷ��ʼ��һ�������ָ�Ĵ�����s�е��ַ����ҵ�ĩβʱ������NULL��
        ˵�����ڵ��õ�һ��strtok֮�󣬶�ȡ�¸��Ӵ���Ҫ���µ���strtok��str��Ҫ����ΪNULL
    */
    if(tmp)
        strcpy(exname,tmp);
    else
        strcpy(exname, "");
    for(i = 0; i < MAXOPENFILE; i++)
    {
        /*
            extern int strcmp(const char *s1,const char *s2);�Ƚ������ַ�����С
            return:
                value:
                    if s1<s2: value < 0;
                    if s1 == s2: value = 0;
                    if s1 > s2 : values > 0;
        */
        if(!strcmp(fname,openfile[i].filename) && !strcmp(exname,openfile[i].exname))
        {
            return i;
        }
    }
    //�鿴��Ŀ¼�е�fcb
    openfile[curdir].count = 0;
    num = do_read(curdir, openfile[curdir].length, text);
    fcbptr = (fcb*)text;
    for(i = 0; i< (num / sizeof(fcb)); i++)
    {
        if(strcmp(fcbptr->filename, fname) == 0 && strcmp(fcbptr->exname,exname) == 0)
            break;
        fcbptr++;
    }
    if(i == num / sizeof(fcb))
    {
        printf("�����ļ������ڡ�\n");
        return ERROR;
    }
    //�����û��򿪱�Ŀ���λ��
    for(i = 0; i < MAXOPENFILE; i++)
    {
        if(openfile[i].topenfile == 0)
        {
            fd = i;
            break;
        }
    }
    if(fd == -1)
    {
        printf("�û��򿪱��޿��б���!\n");
        return ERROR;
    }
    strcpy(openfile[fd].filename, fname);
    strcpy(openfile[fd].exname, fcbptr->exname);
    openfile[fd].attribute = fcbptr->attribute;
    openfile[fd].time = fcbptr->time;
    openfile[fd].date = fcbptr->date;
    openfile[fd].first = fcbptr->first;
    openfile[fd].length = fcbptr->length;
    strcpy(openfile[fd].dir, openfile[curdir].dir);
    strcat(openfile[fd].dir, filename);
    if(!fcbptr->attribute)
        strcat(openfile[fd].dir, "\\");
    openfile[fd].father = curdir;
    openfile[fd].count = 0;
    openfile[fd].fcbstate = 0;
    openfile[fd].topenfile = 1;
    return fd;
}

//�ر��ļ�����
void my_close(int fd)
{
    fcb *fcbptr, *pos;
    int father,num,i;
    char text[MAXTEXT];

    //���fd����Ч��
    if(fd < 0 || fd >= MAXOPENFILE)
    {
        printf("����fd������Χ��\n");
        return;
    }
    if(openfile[fd].fcbstate)
    {
        fcbptr = (fcb *)malloc(sizeof(fcb));
        strcpy(fcbptr->filename, openfile[fd].filename);
        strcpy(fcbptr->exname,openfile[fd].exname);
        fcbptr->attribute = openfile[fd].attribute;
        fcbptr->time = openfile[fd].time;
        fcbptr->date = openfile[fd].date;
        fcbptr->first = openfile[fd].first;
        fcbptr->length = openfile[fd].length;
        father = openfile[fd].father;

        //��ȡ��Ŀ¼�ļ�����
        openfile[father].count = 0;
        num = do_read(father, openfile[father].length, text);
        pos = (fcb*)text;
        //��λ���ļ���Ӧ��Ŀ¼��
        for(i = 0; i < (num / sizeof(fcb)); i ++)
        {
            if(strcmp(pos->filename, openfile[fd].filename) == 0 && strcmp(pos->exname, openfile[fd].exname) == 0)
                break;
            pos++;
        }
        openfile[father].count = i * sizeof(fcb);
        do_write(father, (char *)fcbptr, sizeof(fcb), 2);
        openfile[fd].fcbstate = 0;
    }

    //��ʼ���û��򿪱�
    strcpy(openfile[fd].filename, "");
    strcpy(openfile[fd].exname, "");
    openfile[fd].topenfile = 0;
    //printOpenFile();
}


//д�ļ�����
int my_write(int fd)
{
    fat *fat1,*fat2,*fatptr1,*fatptr2;
    int wstyle,num_cur,num = 0,len;
    char text[MAXTEXT];
    unsigned short blk_num;

    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat2 = (fat*)(myvhard + 3 * BLOCKSIZE);
    //���fd����Ч��
    if(fd < 0 || fd >= MAXOPENFILE)
    {
        printf("����fd������Χ��\n");
        return ERROR;
    }
    //ѡ��д�뷽ʽ
    while(1)
    {
        printf("��ѡ��Ҫд�붩���ļ�����ʽ���:\n1.�ض�д\t2.����д\t3.׷��д\n");
        scanf("%d",&wstyle);
        if(wstyle > 0 && wstyle < 4)
            break;
        printf("the wstyle must be in [1,3]!");
    }
    //�Ӽ�����������
    getchar();  //��Ҫ��֮ǰ�������еĻ��з�������������Ժ������text����Ӱ�졣
    switch(wstyle)
    {
        case 1:
            blk_num = openfile[fd].first;
            fatptr1 = fat1 + blk_num;
            fatptr2 = fat2 + blk_num;
            blk_num = fatptr1->id;
            fatptr1->id = END;
            fatptr2->id = END;
            while(blk_num != END)
            {
                fatptr1 = fat1 + blk_num;
                fatptr2 = fat2 + blk_num;
                blk_num = fatptr1->id;
                fatptr1->id = FREE;
                fatptr2->id = FREE;
            }
            openfile[fd].count = 0;
            openfile[fd].length = 0;
            break;
        case 2:
            openfile[fd].count = 0;
            //�ļ��Ķ�дָ��Ӧ�ò���Ҫ��
            break;
        case 3:
            openfile[fd].count = openfile[fd].length;
        default:
            break;
    }
    printf("������Ҫд����ı���\n");
    while(gets(text))
    {
        len = strlen(text);
        num_cur = do_write(fd,text,len,wstyle);
        if(num_cur != ERROR)
            num += num_cur;
        if(num_cur < len)
        {
            printf("д�����!\n");
            break;
        }
    }
    //printf("In my_write, the fd is %d, the filename is %s,the length is %d\n",fd, openfile[fd].filename,openfile[fd].length);
    return num;
}

//ʵ��д�ļ�����
int do_write(int fd,char *text,int len, char wstyle)
{
    fat *fat1,*fat2,*fatptr1,*fatptr2;
    unsigned short blk_num;
    int blk_off,i,num,cur_blk,father;
    unsigned char *pos;
    fcb *fcbptr;
    char text2[MAXTEXT];

    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat2 = (fat*)(myvhard + 3 * BLOCKSIZE);
    //�߼�����
    blk_num = openfile[fd].count / BLOCKSIZE;
    //����ƫ����
    blk_off = openfile[fd].count;
    fatptr1 = fat1 + openfile[fd].first;
    fatptr2 = fat2 + openfile[fd].first;
    cur_blk = openfile[fd].first;
     //����fat���ҵ�Ҫд�����ʼ�߼����λ��
    for(i = 0;i < blk_num; i++)
    {
        cur_blk = fatptr1->id;
        blk_off = blk_off - BLOCKSIZE;
        fatptr1 = fat1 + cur_blk;
    }
    //д��ͬʱ��Ҫ����д������
    num = 0;
    while(num < len)
    {
        pos = (unsigned char *)(myvhard + cur_blk * BLOCKSIZE);
        //��Ҫ����һ�����дҲҪ����һ��д
        for( i = 0; i < BLOCKSIZE; i++)
            buf[i] = pos[i];
        for(;blk_off < BLOCKSIZE; blk_off++)
        {
            buf[blk_off] = text[num];
            num++;
            openfile[fd].count++;
            //����д�볤��С�ڣ����̿��С - ��ʼ����ƫ��������ʱ��
            if(num == len)
                break;
        }
        for( i = 0; i< BLOCKSIZE; i++)
        {
            pos[i] = buf[i];
        }
        //���д�볤�ȴ���һ��(���̿��С - ��ʼ����ƫ����)��ʱ��
        if(num < len)
        {
            cur_blk = fatptr1->id;
            if(cur_blk == END)
            {
                cur_blk = findFreeBlock();
                if(cur_blk == ERROR)
                    break;
                fatptr1->id = cur_blk;
                fatptr2->id = cur_blk;
                fatptr1 = fatptr1 + cur_blk;
                fatptr2 = fatptr2 + cur_blk;
                fatptr1->id = END;
                fatptr2->id = END;
            }
            else
            {
                fatptr1 = fat1 + cur_blk;
                fatptr1 = fat1 + cur_blk;
            }
            blk_off = 0;
        }
    }
    if(openfile[fd].count > openfile[fd].length)
    {
        openfile[fd].length = openfile[fd].count;
    }

    //�ļ���fcb�Ƿ��޸�
    openfile[fd].fcbstate = 1;
    return num;
}

//���ļ�����
int my_read(int fd,int len)
{
    int num;
    char text[MAXTEXT];

    if(fd < 0 || fd >= MAXOPENFILE)
    {
        printf("����fd������Χ��\n");
        return ERROR;
    }
    openfile[fd].count = 0;
    num = do_read(fd,len,text);
    if(num == ERROR)
    {
        printf("��ȡʧ�ܣ�\n");
        return ERROR;
    }
    else
    {
        printf("%s\n",text);
    }
    return num;
}

//ʵ�ʶ��ļ�����
int do_read(int fd, int len, char *text)
{
    fat* fat1;
    fat* fat_ptr;
    int cur_blk,i;
    unsigned short blk_num;
    unsigned char* pos;
    int blk_off,num = 0; // num��¼��ȡ����

    //�ж϶�ȡ�����Ƿ񳬹��ļ�����
    if((openfile[fd].count + len) > openfile[fd].length)
    {
        printf("��ȡ���ȴ����ļ����ȣ�\n");
        return ERROR;
    }

    //�߼�����
    blk_num = openfile[fd].count / BLOCKSIZE;
    //����ƫ����
    blk_off = openfile[fd].count;
    fat1 = (fat*)(myvhard + BLOCKSIZE);
    fat_ptr = fat1 + openfile[fd].first;
    cur_blk = openfile[fd].first;
    //����fat���ҵ�Ҫ��ȡ����ʼ�߼����λ��
    for(i = 0;i < blk_num;i++)
    {
        cur_blk = fat_ptr->id;
        blk_off = blk_off - BLOCKSIZE;
        fat_ptr = fat1 + cur_blk;
    }
    while(num < len)
    {
        //pos��ǵ�ǰ��д���̿�ĳ�ʼλ��
        pos = (unsigned char*)(myvhard + cur_blk * BLOCKSIZE);
        for(i = 0;i < BLOCKSIZE;i ++)
        {
            buf[i] = pos[i];
        }
        for(;blk_off < BLOCKSIZE; blk_off++)
        {
            text[num] = buf[blk_off];
            num++;
            openfile[fd].count++;
            //Ҫ�ж��ǲ����Ѿ�����ָ��������
            if(num == len)
                break;
        }
        if(num < len)
        {
            cur_blk = fat_ptr->id;
            blk_off = 0;
            fat_ptr = fat1 + cur_blk;
        }
    }
    text[num] = '\0';
    return num;
}

//�˳��ļ�ϵͳ����
void my_exitsys()
{
    int father;
    FILE *fp;

    fp = fopen(filesys_name,"w");
    while(curdir)
    {
        father = openfile[curdir].father;
        my_close(curdir);
        curdir = father;
    }
    //������������д�����ָ���ļ���
    fwrite(myvhard, SIZE, 1, fp);
    fclose(fp);
    free(buf);
    free(myvhard);
}

//���û���������ȡ��·��
void extractDir(char *dirname, char * dir,char *filename)
{
    int len;
    char *tmp,*next;
    tmp = strtok(dirname,"\\");
    while(tmp)
    {
        if(!(next = strtok(NULL,"\\")))
        {
            if(((strcmp(tmp,".") == 0) || (strcmp(tmp,"..") == 0)))
            {
                break;
            }
            strcpy(filename,tmp);
            break;
        }
        strcat(dir,tmp);
        strcat(dir,"\\");
        tmp = next;
    }
    len = strlen(dir);
    if(dir[len - 1] == '\\')
    {
        dir[len - 1] = '\0';
    }
}

//���ҿ��п�
int findFreeBlock()
{
    unsigned char i;
    fat *fat1,*pos;
    fat1 = (fat*)(myvhard + BLOCKSIZE);
    for(i = 7;i < (SIZE / BLOCKSIZE); i++)
    {
        pos = fat1 + i;
        if(pos->id == FREE)
            return i;
    }
    printf("�Ҳ������п�");
    return ERROR;
}

void printOpenFile()
{
    int i,father;
    printf("fd\t\t�ļ���\t\t�ļ�����\t\t��Ŀ¼\t\t��Ŀ¼fd\n");
    for(i = 0;i < MAXOPENFILE; i++)
    {
        if(openfile[i].topenfile != 0)
        {
            father = openfile[i].father;
            printf("%d\t\t%s.%s\t\t%d\t\t%s\t\t%d\n",i,openfile[i].filename,openfile[i].exname,openfile[i].length,openfile[father].filename,father);
        }

    }
}

void printFcb(int fd)
{
    int i,num,tmp;
    fcb* fcbptr;
    char text[MAXTEXT];

    tmp = openfile[fd].count;
    openfile[fd].count = 0;
    num = do_read(fd, openfile[fd].length, text);
    printf("��Ŀ¼��%s �ж�ȡ�� %d �ֽ�.\n",openfile[fd].filename,num);
    fcbptr = (fcb*)text;
    //��λ���ļ���Ӧ��Ŀ¼��
    printf("�ļ���\t\t�ļ�����\t\t\n");
    for(i = 0; i < (num / sizeof(fcb)); i ++)
    {
        printf("%s\t\t%d\n",fcbptr->filename,fcbptr->length);
        fcbptr++;
    }
    openfile[fd].count = tmp;
}

int main()
{
    char cmd[15][10] = {"cd", "mkdir", "rmdir", "ls", "create", "rm", "open", "close", "write", "read", "format","exit","rm-r","popen"};
    char s[30], *sp;
	int cmdn, flag = 1, i, father;
	block0 *guide;

    //��ʼ��ȫ�ֱ���
    //����������̿ռ�
    myvhard = (unsigned char *)calloc(SIZE,1);
    //��ʼ���û��򿪱�
    for(i = 0;i < MAXOPENFILE;i ++)
    {
        openfile[i].topenfile = 0;
    }
    //����Ŀ¼����Ϊ��ǰĿ¼
    strcpy(currentdir,"\\root\\");
    //��ʼ���ļ����������ļ�����������һ���û��򿪱������ֵ��ָ��ǰ�򿪵��ļ�
    curdir = 0;
    //��ʼ�������������������ʼλ��
    guide = (block0*)myvhard;
    startp = guide->startblock;
    //������
    buf = (unsigned char*)malloc(BLOCKSIZE);
    if(!buf)
    {
        printf("malloc failed!\n");
        return ERROR;
    }
    startsys();
    //printf("In main,openfile[0].length is%d\n",openfile[0].length);
    printf("*********************��ӭ����FAT�ļ�ϵͳ*****************************\n\n");
    printf("������\t\t�������\t\t����˵��\n\n");
    printf("cd\t\tĿ¼��(·����)\t\t�л���ǰĿ¼��ָ��Ŀ¼\n");
    printf("mkdir\t\tĿ¼��\t\t\t�ڵ�ǰĿ¼������Ŀ¼\n");
    printf("rmdir\t\tĿ¼��\t\t\t�ڵ�ǰĿ¼ɾ��ָ��Ŀ¼\n");
    printf("ls\t\t��\t\t\t��ʾ��ǰĿ¼�µ�Ŀ¼���ļ�\n");
    printf("create\t\t�ļ���\t\t\t�ڵ�ǰĿ¼�´���ָ���ļ�\n");
    printf("rm\t\t�ļ���\t\t\t�ڵ�ǰĿ¼��ɾ��ָ���ļ�\n");
    printf("open\t\t�ļ���\t\t\t�ڵ�ǰĿ¼�´�ָ���ļ�\n");
    printf("write\t\t��\t\t\t�ڴ��ļ�״̬�£�д���ļ�\n");
    printf("read\t\t��\t\t\t�ڴ��ļ�״̬�£���ȡ���ļ�\n");
    printf("close\t\t��\t\t\t�ڴ��ļ�״̬�£��رո��ļ�\n");
    printf("format\t\t��\t\t\t��ʽ��\n");
    printf("exit\t\t��\t\t\t�˳�ϵͳ\n\n");
    printf("*********************************************************************\n\n");
    while(flag)
    {
        printf("%s>", openfile[curdir].dir);
        gets(s);
        cmdn = -1;
        if(strcmp(s, ""))//�����Ϊ�գ�ִ������
        {
            sp=strtok(s, " ");
            for(i = 0; i < 15; i++)
            {
                if(strcmp(sp, cmd[i]) == 0)
                {
                    cmdn = i;
                    break;
                }
            }
            switch(cmdn){
                case 0:
                    sp = strtok(NULL, " ");
                    if(sp && (!openfile[curdir].attribute))
                        my_cd(sp);
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 1:
                    sp = strtok(NULL, " ");
                    if(sp && (!openfile[curdir].attribute))
                        my_mkdir(sp);
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 2:
                    sp = strtok(NULL, " ");
                    if(sp && (!openfile[curdir].attribute))
                        my_rmdir(sp);
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 3:
                    if(!openfile[curdir].attribute)
                        my_ls();
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 4:
                    sp = strtok(NULL, " ");
                    if(sp && (!openfile[curdir].attribute))
                        my_create(sp);
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 5:
                    sp = strtok(NULL, " ");
                    if(sp && (!openfile[curdir].attribute))
                        my_rm(sp);
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 6:
                    sp = strtok(NULL, " ");
                    if(sp && (!openfile[curdir].attribute))
                    {
                        if(strchr(sp, '.'))//����sp��'.'�״γ��ֵ�λ��
                            curdir = my_open(sp);
                        else
                            printf("the openfile should have exname.\n");
                    }
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 7:
                    if(!(openfile[curdir].attribute == 0))
                    {
                        father = openfile[curdir].father;
                        my_close(curdir);
                        curdir = father;
                    }
                    else
                        printf("û�д��κ��ļ���\n");
                    break;
                case 8:
                    if(!(openfile[curdir].attribute == 0))
                        my_write(curdir);
                    else
                        printf("û�д��κ��ļ���\n");
                    break;
                case 9:
                    if(!(openfile[curdir].attribute == 0))
                        my_read(curdir, openfile[curdir].length);
                    else
                        printf("û�д��κ��ļ���\n");
                    break;
                case 10:
                     my_format();
                     startsys();
                     break;
                case 11:
                    if(openfile[curdir].attribute == 0)
                    {
                        my_exitsys();
                        flag = 0;
                    }
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 12:
                    sp = strtok(NULL, " ");
                    if(sp && (openfile[curdir].attribute == 0))
                        my_rmdir(sp);
                    else
                        printf("��������ȷ�����\n");
                    break;
                case 13:
                    printOpenFile();
                    break;
                //case 14:
                   // printFcb();
                    //break;
                default:
                    printf("��������ȷ�����\n");
                    break;
            }
        }
    }
    return 0;
}

