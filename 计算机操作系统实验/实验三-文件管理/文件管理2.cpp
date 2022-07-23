#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BLOCKSIZE 1024 //���̿��С
#define SIZE 1024000   //������̿ռ��С
#define END 65535      //FAT�е��ļ�������־
#define FREE 0         //FAT���̿���б�־
#define ROOTBLOCKNUM 2 //��Ŀ¼����ռ�̿���
#define MAXOPENFILE 10 //���ͬʱ���ļ�����t
#define MAXTEXT 10000

/*�ļ����ƿ�*/
typedef struct FCB
{
    char filename[8];        //�ļ���
    char exname[3];          //�ļ���չ��
    unsigned char attribute; //�ļ������ֶΣ�ֵΪ0ʱ��ʾĿ¼�ļ���ֵΪ1ʱ��ʾ�����ļ�
    unsigned short time;     //�ļ�����ʱ��
    unsigned short date;     //�ļ���������
    unsigned short first;    //�ļ���ʼ�̿��
    unsigned long length;    //�ļ�����
    char free;               //��ʾĿ¼���Ƿ�Ϊ�գ���ֵΪ0����ʾ�գ�ֵΪ1����ʾ�ѷ���
} fcb;

/*�ļ������*/
typedef struct FAT
{
    unsigned short id; //���̿��״̬�����еģ����ģ���һ����
} fat;

/*�û����ļ���*/
typedef struct USEROPEN
{
    char filename[8];        //�ļ���
    char exname[3];          //�ļ���չ��
    unsigned char attribute; //�ļ������ֶΣ�ֵΪ0ʱ��ʾĿ¼�ļ���ֵΪ1ʱ��ʾ�����ļ�
    unsigned short time;     //�ļ�����ʱ��
    unsigned short date;     //�ļ���������
    unsigned short first;    //�ļ���ʼ�̿��
    unsigned long length;    //�ļ����ȣ��������ļ����ֽ�������Ŀ¼�ļ�������Ŀ¼�������
    char free;               //��ʾĿ¼���Ƿ�Ϊ�գ���ֵΪ0����ʾ�գ�ֵΪ1����ʾ�ѷ���

    unsigned short dirno; //��Ӧ���ļ���Ŀ¼���ڸ�Ŀ¼�ļ��е��̿��
    int diroff;           //��Ӧ���ļ���Ŀ¼���ڸ�Ŀ¼�ļ���dirno�̿��е�Ŀ¼�����
    char dir[80];         //��Ӧ���ļ����ڵ�·����������������ټ���ָ���ļ��Ƿ��Ѿ���
    int father;           //��Ŀ¼�ڴ��ļ������λ��
    int count;            //��дָ�����ļ��е�λ��,�ļ������ַ���
    char fcbstate;        //�Ƿ��޸����ļ���FCB�����ݣ�����޸�����Ϊ1������Ϊ0
    char topenfile;       //��ʾ���û��򿪱����Ƿ�Ϊ�գ���ֵΪ0����ʾΪ�գ������ʾ�ѱ�ĳ���ļ�ռ��
} useropen;

/*������*/
typedef struct BLOCK0
{
    char magic[10];            //�ļ�ϵͳħ��
    char information[200];     //�洢һЩ������Ϣ������̿��С�����̿������������ļ�����
    unsigned short root;       //��Ŀ¼�ļ�����ʼ�̿��
    unsigned char *startblock; //�����������������ʼλ��
} block0;

unsigned char *myvhard;             //ָ��������̵���ʼ��ַ
useropen openfilelist[MAXOPENFILE]; //�û����ļ�������
int curdir;                         //�û����ļ����еĵ�ǰĿ¼���ڴ��ļ������λ��
char currentdir[80];                //��¼��ǰĿ¼��Ŀ¼��������Ŀ¼��·����
unsigned char *startp;              //��¼�����������������ʼλ��
char myfilename[] = "�ļ�ϵͳ";    //�ļ�ϵͳ���ļ���

void startsys();                                        //�����ļ�ϵͳ
void my_format();                                       //���̸�ʽ��
void my_cd(char *dirname);                              //���ĵ�ǰĿ¼
void my_mkdir(char *dirname);                           //������Ŀ¼
void my_rmdir(char *dirname);                           //ɾ����Ŀ¼
void my_ls();                                           //��ʾĿ¼
void my_create(char *filename);                         //�����ļ�
void my_rm(char *filename);                             //ɾ���ļ�
int my_open(char *filename);                            //���ļ�
int my_close(int fd);                                   //�ر��ļ�
int my_write(int fd);                                   //д�ļ�
int do_write(int fd, char *text, int len, char wstyle); //ʵ��д�ļ�
int my_read(int fd, int len);                           //���ļ�
int do_read(int fd, int len, char *text);               //ʵ�ʶ��ļ�
void my_exitsys();                                      //�˳��ļ�ϵͳ
unsigned short findblock();                             //Ѱ�ҿ����̿�
int findopenfile();                                     //Ѱ�ҿ����ļ�����

int main()
{
    char cmd[15][10] = {"cd", "mkdir", "rmdir", "ls", "create", "rm", "open", "close", "write", "read", "exit"};
    char s[30], *sp;
    int cmdn, flag = 1, i;
    startsys();
    printf("*********************�ļ�ϵͳV1.0*******************************\n\n");
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
    printf("exit\t\t��\t\t\t�˳�ϵͳ\n\n");
    printf("*********************************************************************\n\n");
    while (flag)
    {
        printf("%s:", openfilelist[curdir].dir);
        gets(s);
        cmdn = -1;
        if (strcmp(s, ""))
        {
            sp = strtok(s, " ");
            for (i = 0; i < 15; i++)
            {
                if (strcmp(sp, cmd[i]) == 0)
                {
                    cmdn = i;
                    break;
                }
            }
            switch (cmdn)
            {
            case 0:
                sp = strtok(NULL, "");
                if (sp && (openfilelist[curdir].attribute & 0x20))
                    my_cd(sp);
                else
                    printf("��������ȷ�����\n");
                break;
            case 1:
                sp = strtok(NULL, "");
                if (sp && (openfilelist[curdir].attribute & 0x20))
                    my_mkdir(sp);
                else
                    printf("��������ȷ�����\n");
                break;
            case 2:
                sp = strtok(NULL, "");
                if (sp && (openfilelist[curdir].attribute & 0x20))
                    my_rmdir(sp);
                else
                    printf("��������ȷ�����\n");
                break;
            case 3:
                if (openfilelist[curdir].attribute & 0x20)
                    my_ls();
                else
                    printf("��������ȷ�����\n");
                break;
            case 4:
                sp = strtok(NULL, "");
                if (sp && (openfilelist[curdir].attribute & 0x20))
                    my_create(sp);
                else
                    printf("��������ȷ�����\n");
                break;
            case 5:
                sp = strtok(NULL, "");
                if (sp && (openfilelist[curdir].attribute & 0x20))
                    my_rm(sp);
                else
                    printf("��������ȷ�����\n");
                break;
            case 6:
                sp = strtok(NULL, "");
                if (sp && (openfilelist[curdir].attribute & 0x20))
                {
                    if (strchr(sp, '.')) //����sp��'.'�״γ��ֵ�λ��
                        curdir = my_open(sp);
                    else
                        printf("Ҫ�򿪵��ļ�Ӧ�������ⲿ���ơ�\n");
                }
                else
                    printf("��������ȷ�����\n");
                break;
            case 7:
                if (!(openfilelist[curdir].attribute & 0x20))
                    curdir = my_close(curdir);
                else
                    printf("û�д��κ��ļ���\n");
                break;
            case 8:
                if (!(openfilelist[curdir].attribute & 0x20))
                    my_write(curdir);
                else
                    printf("û�д��κ��ļ���\n");
                break;
            case 9:
                if (!(openfilelist[curdir].attribute & 0x20))
                    my_read(curdir, openfilelist[curdir].length);
                else
                    printf("û�д��κ��ļ���\n");
                break;
            case 10:
                if (openfilelist[curdir].attribute & 0x20)
                {
                    my_exitsys();
                    flag = 0;
                }
                else
                    printf("��������ȷ�����\n");
                break;
            default:
                printf("��������ȷ�����\n");
                break;
            }
        }
    }
    return 0;
}

//�����ļ�����startsys()
void startsys()
{
    FILE *fp; //�ļ����͵�ָ�����
    unsigned char buf[SIZE];
    fcb *root;
    int i;
    myvhard = (unsigned char *)malloc(SIZE); //����������̿ռ䣬���ڴ�ģ����̿ռ�
    memset(myvhard, 0, SIZE);                //��myvhard��ǰSIZE���ֽ���0�滻������myvhard
    if ((fp = fopen(myfilename, "r")) != NULL)
    {
        fread(buf, SIZE, 1, fp); //���������ļ���ȡ��������
        fclose(fp);
        if (strcmp(((block0 *)buf)->magic, "10101010"))
        {
            printf("�ļ�ϵͳ�����ڣ��������ļ�ϵͳ...\n");
            my_format();
        }
        else
        {
            printf("�ļ�ϵͳ�Ѵ��ڣ�����д��...\n");
            for (i = 0; i < SIZE; i++)
                myvhard[i] = buf[i];
        }
    }
    else
    {
        printf("�ļ�ϵͳ�����ڣ��������ļ�ϵͳ...\n");
        my_format();
    }
    root = (fcb *)(myvhard + 5 * BLOCKSIZE);
    strcpy(openfilelist[0].filename, root->filename);
    strcpy(openfilelist[0].exname, root->exname);
    openfilelist[0].attribute = root->attribute;
    openfilelist[0].time = root->time;
    openfilelist[0].date = root->date;
    openfilelist[0].first = root->first;
    openfilelist[0].length = root->length;
    openfilelist[0].free = root->free;
    openfilelist[0].dirno = 5;
    openfilelist[0].diroff = 0;
    strcpy(openfilelist[0].dir, "\\root\\");
    openfilelist[0].father = 0;
    openfilelist[0].count = 0;
    openfilelist[0].fcbstate = 0;
    openfilelist[0].topenfile = 1;
    for (i = 1; i < MAXOPENFILE; i++)
        openfilelist[i].topenfile = 0;
    curdir = 0;
    strcpy(currentdir, "\\root\\");
    startp = ((block0 *)myvhard)->startblock;
}

//���̸�ʽ������my_format()
void my_format()
{
    FILE *fp;
    fat *fat1, *fat2;
    block0 *blk0;
    time_t now;
    struct tm *nowtime;
    fcb *root;
    int i;
    blk0 = (block0 *)myvhard;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    root = (fcb *)(myvhard + 5 * BLOCKSIZE);
    strcpy(blk0->magic, "10101010");
    strcpy(blk0->information, "�ļ�ϵͳVer1.1\n���С=1KB ȫ��С=1000KB ����Ŀ=1000 ������=2\n");
    blk0->root = 5;
    blk0->startblock = (unsigned char *)root;
    for (i = 0; i < 5; i++)
    {
        fat1->id = END;
        fat2->id = END;
        fat1++;
        fat2++;
    }
    fat1->id = 6;
    fat2->id = 6;
    fat1++;
    fat2++;
    fat1->id = END;
    fat2->id = END;
    fat1++;
    fat2++;
    for (i = 7; i < SIZE / BLOCKSIZE; i++)
    {
        fat1->id = FREE;
        fat2->id = FREE;
        fat1++;
        fat2++;
    }
    now = time(NULL);
    nowtime = localtime(&now);
    strcpy(root->filename, ".");
    strcpy(root->exname, "");
    root->attribute = 0x28;
    root->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
    root->date = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
    root->first = 5;
    root->length = 2 * sizeof(fcb);
    root->free = 1;
    root++;
    now = time(NULL);
    nowtime = localtime(&now);
    strcpy(root->filename, "..");
    strcpy(root->exname, "");
    root->attribute = 0x28;
    root->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
    root->date = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
    root->first = 5;
    root->length = 2 * sizeof(fcb);
    root->free = 1;
    fp = fopen(myfilename, "w");
    fwrite(myvhard, SIZE, 1, fp);
    fclose(fp);
}

//���ĵ�ǰĿ¼����
void my_cd(char *dirname)
{
    char *dir;
    int fd;
    dir = strtok(dirname, "\\"); //�ֽ��ַ���Ϊһ���ַ�����dirnameΪҪ�ֽ���ַ�����"\\"Ϊ�ָ����ַ���
    if (strcmp(dir, ".") == 0)
        return;
    else if (strcmp(dir, "..") == 0)
    {
        if (curdir)
            curdir = my_close(curdir);
        return;
    }
    else if (strcmp(dir, "root") == 0)
    {
        while (curdir)
            curdir = my_close(curdir);
        dir = strtok(NULL, "\\");
    }
    while (dir)
    {
        fd = my_open(dir);
        if (fd != -1)
            curdir = fd;
        else
            return;
        dir = strtok(NULL, "\\");
    }
}

//������Ŀ¼����
void my_mkdir(char *dirname)
{
    fcb *fcbptr;
    fat *fat1, *fat2;
    time_t now;
    struct tm *nowtime;
    char text[MAXTEXT];
    unsigned short blkno;
    int rbn, fd, i;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    openfilelist[curdir].count = 0;
    rbn = do_read(curdir, openfilelist[curdir].length, text);
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++) //�ڵ�ǰĿ¼���ң��Ƿ�������Ŀ¼
    {
        if (strcmp(fcbptr->filename, dirname) == 0 && strcmp(fcbptr->exname, "") == 0)
        {
            printf("Ҫ�������ļ����Ѵ��ڣ�\n");
            return;
        }
        fcbptr++;
    }
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++)
    {
        if (fcbptr->free == 0)
            break;
        fcbptr++;
    }
    blkno = findblock(); //Ѱ�ҿ����̿�
    if (blkno == -1)
        return;
    (fat1 + blkno)->id = END;
    (fat2 + blkno)->id = END;
    now = time(NULL);
    nowtime = localtime(&now);
    strcpy(fcbptr->filename, dirname);
    strcpy(fcbptr->exname, "");
    fcbptr->attribute = 0x30;
    fcbptr->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
    fcbptr->date = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
    fcbptr->first = blkno;
    fcbptr->length = 2 * sizeof(fcb);
    fcbptr->free = 1;
    openfilelist[curdir].count = i * sizeof(fcb);     //�ѵ�ǰĿ¼���ļ���дָ�붨λ���ļ�ĩβ
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2); //��ָ��fcbptr��ʼдһ��fcb��С�����ݵ���ǰĿ¼�ļ�ĩβ

    fd = my_open(dirname); //�����½�����Ŀ¼�ļ����û����ļ�������±�
    if (fd == -1)
        return;
    fcbptr = (fcb *)malloc(sizeof(fcb)); //������Ŀ¼��'.','..'Ŀ¼
    now = time(NULL);
    nowtime = localtime(&now);
    strcpy(fcbptr->filename, ".");
    strcpy(fcbptr->exname, "");
    fcbptr->attribute = 0x28;
    fcbptr->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
    fcbptr->date = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
    fcbptr->first = blkno;
    fcbptr->length = 2 * sizeof(fcb);
    fcbptr->free = 1;
    do_write(fd, (char *)fcbptr, sizeof(fcb), 2);
    now = time(NULL);
    nowtime = localtime(&now);
    strcpy(fcbptr->filename, "..");
    strcpy(fcbptr->exname, "");
    fcbptr->attribute = 0x28;
    fcbptr->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
    fcbptr->date = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
    fcbptr->first = blkno;
    fcbptr->length = 2 * sizeof(fcb);
    fcbptr->free = 1;
    do_write(fd, (char *)fcbptr, sizeof(fcb), 2);
    free(fcbptr);
    my_close(fd);

    fcbptr = (fcb *)text;
    fcbptr->length = openfilelist[curdir].length;
    openfilelist[curdir].count = 0;
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2); //���µ�ǰĿ¼�ļ�������
    openfilelist[curdir].fcbstate = 1;
}

//ɾ����Ŀ¼����
void my_rmdir(char *dirname)
{
    fcb *fcbptr, *fcbptr2;
    fat *fat1, *fat2, *fatptr1, *fatptr2;
    char text[MAXTEXT], text2[MAXTEXT];
    unsigned short blkno;
    int rbn, rbn2, fd, i, j;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    if (strcmp(dirname, ".") == 0 || strcmp(dirname, "..") == 0)
    {
        printf("�޷�ɾ����ǰĿ¼�͸�Ŀ¼��\n");
        return;
    }
    openfilelist[curdir].count = 0;
    rbn = do_read(curdir, openfilelist[curdir].length, text);
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++) //����Ҫɾ����Ŀ¼
    {
        if (strcmp(fcbptr->filename, dirname) == 0 && strcmp(fcbptr->exname, "") == 0)
            break;
        fcbptr++;
    }
    if (i == rbn / sizeof(fcb))
    {
        printf("Ҫɾ����Ŀ¼�����ڣ�\n");
        return;
    }
    fd = my_open(dirname);                              //Ŀ¼�ڵ�ǰ���ļ������е��±�
    rbn2 = do_read(fd, openfilelist[fd].length, text2); //��ȡҪɾ����Ŀ¼������
    fcbptr2 = (fcb *)text2;
    for (j = 0; j < rbn2 / sizeof(fcb); j++) //�ж�Ҫɾ��Ŀ¼�Ƿ�Ϊ��
    {
        if (strcmp(fcbptr2->filename, ".") && strcmp(fcbptr2->filename, "..") && strcmp(fcbptr2->filename, ""))
        {
            my_close(fd);
            printf("ɾ����Ŀ¼ʧ�ܡ�Ŀ¼��Ϊ�գ�\n");
            return;
        }
        fcbptr2++;
    }
    blkno = openfilelist[fd].first;
    while (blkno != END) //�޸�Ҫɾ��Ŀ¼��fat����ռ�õ�Ŀ¼�������
    {
        fatptr1 = fat1 + blkno;
        fatptr2 = fat2 + blkno;
        blkno = fatptr1->id;
        fatptr1->id = FREE;
        fatptr2->id = FREE;
    }
    my_close(fd);
    strcpy(fcbptr->filename, ""); //�޸���ɾ��Ŀ¼�ڵ�ǰĿ¼��fcb������
    fcbptr->free = 0;
    openfilelist[curdir].count = i * sizeof(fcb); //���µ�ǰĿ¼�ļ�������
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);
    openfilelist[curdir].fcbstate = 1;
}

//��ʾĿ¼����
void my_ls()
{
    fcb *fcbptr;
    char text[MAXTEXT];
    int rbn, i;
    openfilelist[curdir].count = 0;
    rbn = do_read(curdir, openfilelist[curdir].length, text);
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++)
    {
        if (fcbptr->free)
        {
            if (fcbptr->attribute & 0x20)
                printf("%s\\\t\t<DIR>\t\t\t%d/%d/%d\t%02d:%02d:%02d\n", fcbptr->filename, (fcbptr->date >> 9) + 1980, (fcbptr->date >> 5) & 0x000f, fcbptr->date & 0x001f, fcbptr->time >> 11, (fcbptr->time >> 5) & 0x003f, fcbptr->time & 0x001f * 2);
            else
                printf("%s.%s\t\t%dB\t\t%d/%d/%d\t%02d:%02d:%02d\t\n", fcbptr->filename, fcbptr->exname, (int)(fcbptr->length), (fcbptr->date >> 9) + 1980, (fcbptr->date >> 5) & 0x000f, fcbptr->date & 0x1f, fcbptr->time >> 11, (fcbptr->time >> 5) & 0x3f, fcbptr->time & 0x1f * 2);
        }
        fcbptr++;
    }
}

//�����ļ�����
void my_create(char *filename)
{
    fcb *fcbptr;
    fat *fat1, *fat2;
    char *fname, *exname, text[MAXTEXT];
    unsigned short blkno;
    int rbn, i;
    time_t now;
    struct tm *nowtime;

    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + BLOCKSIZE);
    fname = strtok(filename, ".");
    exname = strtok(NULL, ".");
    if (strcmp(fname, "") == 0)
    {
        printf("�ļ�������Ϊ�գ�\n");
        return;
    }
    if (!exname)
    {
        printf("�ļ��ⲿ���Ʋ���Ϊ�ա�\n");
        return;
    }
    openfilelist[curdir].count = 0;
    rbn = do_read(curdir, openfilelist[curdir].length, text);
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++)
    {
        if (strcmp(fcbptr->filename, fname) == 0 && strcmp(fcbptr->exname, exname) == 0)
        {
            printf("Ҫ�������ļ����Ѵ��ڣ�\n");
            return;
        }
        fcbptr++;
    }
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++)
    {
        if (fcbptr->free == 0)
            break;
        fcbptr++;
    }
    blkno = findblock();
    if (blkno == -1)
        return;
    (fat1 + blkno)->id = END;
    (fat2 + blkno)->id = END;

    now = time(NULL);
    nowtime = localtime(&now);
    strcpy(fcbptr->filename, fname);
    strcpy(fcbptr->exname, exname);
    fcbptr->attribute = 0x00;
    fcbptr->time = nowtime->tm_hour * 2048 + nowtime->tm_min * 32 + nowtime->tm_sec / 2;
    fcbptr->date = (nowtime->tm_year - 80) * 512 + (nowtime->tm_mon + 1) * 32 + nowtime->tm_mday;
    fcbptr->first = blkno;
    fcbptr->length = 0;
    fcbptr->free = 1;
    openfilelist[curdir].count = i * sizeof(fcb);
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);
    fcbptr = (fcb *)text;
    fcbptr->length = openfilelist[curdir].length;
    openfilelist[curdir].count = 0;
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);
    openfilelist[curdir].fcbstate = 1;
}

//ɾ���ļ�����
void my_rm(char *filename)
{
    fcb *fcbptr;
    fat *fat1, *fat2, *fatptr1, *fatptr2;
    char *fname, *exname, text[MAXTEXT];
    unsigned short blkno;
    int rbn, i;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    fname = strtok(filename, ".");
    exname = strtok(NULL, ".");
    if (strcmp(fname, "") == 0)
    {
        printf("�ļ�������Ϊ�գ�\n");
        return;
    }
    if (!exname)
    {
        printf("�ļ��ⲿ���Ʋ���Ϊ�ա�\n");
        return;
    }
    openfilelist[curdir].count = 0;
    rbn = do_read(curdir, openfilelist[curdir].length, text);
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++)
    {
        if (strcmp(fcbptr->filename, fname) == 0 && strcmp(fcbptr->exname, exname) == 0)
            break;
        fcbptr++;
    }
    if (i == rbn / sizeof(fcb))
    {
        printf("�ļ������ڣ�\n");
        return;
    }
    blkno = fcbptr->first;
    while (blkno != END)
    {
        fatptr1 = fat1 + blkno;
        fatptr2 = fat2 + blkno;
        blkno = fatptr1->id;
        fatptr1->id = FREE;
        fatptr2->id = FREE;
    }
    strcpy(fcbptr->filename, "");
    fcbptr->free = 0;
    openfilelist[curdir].count = i * sizeof(fcb);
    do_write(curdir, (char *)fcbptr, sizeof(fcb), 2);
    openfilelist[curdir].fcbstate = 1;
}

//���ļ�����
int my_open(char *filename)
{
    fcb *fcbptr;
    char *fname, exname[3], *str, text[MAXTEXT];
    int rbn, fd, i;
    fname = strtok(filename, ".");
    str = strtok(NULL, ".");
    if (str)
        strcpy(exname, str);
    else
        strcpy(exname, "");
    for (i = 0; i < MAXOPENFILE; i++) //���û����ļ�������ҿ���ǰ�ļ��Ƿ��Ѿ���
    {
        if (strcmp(openfilelist[i].filename, fname) == 0 && strcmp(openfilelist[i].exname, exname) == 0 && i != curdir)
        {
            printf("�ļ��Ѿ��򿪣�\n");
            return -1;
        }
    }
    openfilelist[curdir].count = 0;
    rbn = do_read(curdir, openfilelist[curdir].length, text);
    fcbptr = (fcb *)text;
    for (i = 0; i < rbn / sizeof(fcb); i++) //�ڵ�ǰĿ¼����Ҫ�򿪵��ļ��Ƿ����
    {
        if (strcmp(fcbptr->filename, fname) == 0 && strcmp(fcbptr->exname, exname) == 0)
            break;
        fcbptr++;
    }
    if (i == rbn / sizeof(fcb))
    {
        printf("�ļ������ڣ�\n");
        return -1;
    }
    fd = findopenfile(); //Ѱ�ҿ����ļ�����
    if (fd == -1)
        return -1;
    strcpy(openfilelist[fd].filename, fcbptr->filename);
    strcpy(openfilelist[fd].exname, fcbptr->exname);
    openfilelist[fd].attribute = fcbptr->attribute;
    openfilelist[fd].time = fcbptr->time;
    openfilelist[fd].date = fcbptr->date;
    openfilelist[fd].first = fcbptr->first;
    openfilelist[fd].length = fcbptr->length;
    openfilelist[fd].free = fcbptr->free;
    openfilelist[fd].dirno = openfilelist[curdir].first;
    openfilelist[fd].diroff = i;
    strcpy(openfilelist[fd].dir, openfilelist[curdir].dir);
    strcat(openfilelist[fd].dir, filename);
    if (fcbptr->attribute & 0x20)
        strcat(openfilelist[fd].dir, "\\");
    openfilelist[fd].father = curdir;
    openfilelist[fd].count = 0;
    openfilelist[fd].fcbstate = 0;
    openfilelist[fd].topenfile = 1;
    return fd;
}

//�ر��ļ�����
int my_close(int fd)
{
    fcb *fcbptr;
    int father;
    if (fd < 0 || fd >= MAXOPENFILE)
    {
        printf("�ļ������ڣ�\n");
        return -1;
    }
    if (openfilelist[fd].fcbstate)
    {
        fcbptr = (fcb *)malloc(sizeof(fcb));
        strcpy(fcbptr->filename, openfilelist[fd].filename);
        strcpy(fcbptr->exname, openfilelist[fd].exname);
        fcbptr->attribute = openfilelist[fd].attribute;
        fcbptr->time = openfilelist[fd].time;
        fcbptr->date = openfilelist[fd].date;
        fcbptr->first = openfilelist[fd].first;
        fcbptr->length = openfilelist[fd].length;
        fcbptr->free = openfilelist[fd].free;
        father = openfilelist[fd].father;
        openfilelist[father].count = openfilelist[fd].diroff * sizeof(fcb);
        do_write(father, (char *)fcbptr, sizeof(fcb), 2);
        free(fcbptr);
        openfilelist[fd].fcbstate = 0;
    }
    strcpy(openfilelist[fd].filename, "");
    strcpy(openfilelist[fd].exname, "");
    openfilelist[fd].topenfile = 0;
    return father;
}

//д�ļ�����
int my_write(int fd)
{
    fat *fat1, *fat2, *fatptr1, *fatptr2;
    int wstyle, len, ll, tmp;
    char text[MAXTEXT];
    unsigned short blkno;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    if (fd < 0 || fd >= MAXOPENFILE)
    {
        printf("�ļ�������!\n");
        return -1;
    }
    while (1)
    {
        printf("��ѡ��Ҫд�붩���ļ���ʽ���:\n1.�ض�д\t2.����д\t3.׷��д\n");
        scanf("%d", &wstyle);
        if (wstyle > 0 && wstyle < 4)
            break;
        printf("�����Ŵ���!");
    }
    getchar();
    switch (wstyle)
    {
    case 1: //�ض�д��ԭ�ļ���ռ��������̿ռ�����Ϊ1
        blkno = openfilelist[fd].first;
        fatptr1 = fat1 + blkno;
        fatptr2 = fat2 + blkno;
        blkno = fatptr1->id;
        fatptr1->id = END;
        fatptr2->id = END;
        while (blkno != END)
        {
            fatptr1 = fat1 + blkno;
            fatptr2 = fat2 + blkno;
            blkno = fatptr1->id;
            fatptr1->id = FREE;
            fatptr2->id = FREE;
        }
        openfilelist[fd].count = 0;
        openfilelist[fd].length = 0;
        break;
    case 2:
        openfilelist[fd].count = 0;
        break;
    case 3:
        openfilelist[fd].count = openfilelist[fd].length;
        break;
    default:
        break;
    }
    ll = 0;
    printf("������Ҫд����ı�(��Ctrl+Z����):\n");
    while (gets(text))
    {
        len = strlen(text);
        text[len++] = '\n';
        text[len] = '\0';
        tmp = do_write(fd, text, len, wstyle);
        if (tmp != -1)
            ll += tmp;
        if (tmp < len)
        {
            printf("д�����!");
            break;
        }
    }
    return ll; //ʵ��д���ֽ���
}

//ʵ��д�ļ�����
int do_write(int fd, char *text, int len, char wstyle)
{
    fat *fat1, *fat2, *fatptr1, *fatptr2;
    unsigned char *buf, *blkptr;
    unsigned short blkno, blkoff;
    int i, ll;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    fat2 = (fat *)(myvhard + 3 * BLOCKSIZE);
    buf = (unsigned char *)malloc(BLOCKSIZE);
    if (buf == NULL)
    {
        printf("�ڴ�ռ����ʧ��!\n");
        return -1;
    }
    blkno = openfilelist[fd].first;
    blkoff = openfilelist[fd].count;
    fatptr1 = fat1 + blkno;
    fatptr2 = fat2 + blkno;
    while (blkoff >= BLOCKSIZE)
    {
        blkno = fatptr1->id;
        if (blkno == END)
        {
            blkno = findblock();
            if (blkno == -1)
            {
                free(buf);
                return -1;
            }
            fatptr1->id = blkno;
            fatptr2->id = blkno;
            fatptr1 = fat1 + blkno;
            fatptr2 = fat2 + blkno;
            fatptr1->id = END;
            fatptr2->id = END;
        }
        else
        {
            fatptr1 = fat1 + blkno;
            fatptr2 = fat2 + blkno;
        }
        blkoff = blkoff - BLOCKSIZE; //��blkoff��λ���ļ����һ�����̿�Ķ�дλ��
    }

    ll = 0;          //ʵ��д���ֽ���
    while (ll < len) //len���û�������ֽ���
    {
        blkptr = (unsigned char *)(myvhard + blkno * BLOCKSIZE);
        for (i = 0; i < BLOCKSIZE; i++)
            buf[i] = blkptr[i];
        for (; blkoff < BLOCKSIZE; blkoff++)
        {
            buf[blkoff] = text[ll++];
            openfilelist[fd].count++;
            if (ll == len)
                break;
        }
        for (i = 0; i < BLOCKSIZE; i++)
            blkptr[i] = buf[i];
        if (ll < len) //���һ�����̿�д���£����ٷ���һ�����̿�
        {
            blkno = fatptr1->id;
            if (blkno == END)
            {
                blkno = findblock();
                if (blkno == -1)
                    break;
                fatptr1->id = blkno;
                fatptr2->id = blkno;
                fatptr1 = fat1 + blkno;
                fatptr2 = fat2 + blkno;
                fatptr1->id = END;
                fatptr2->id = END;
            }
            else
            {
                fatptr1 = fat1 + blkno;
                fatptr2 = fat2 + blkno;
            }
            blkoff = 0;
        }
    }
    if (openfilelist[fd].count > openfilelist[fd].length)
        openfilelist[fd].length = openfilelist[fd].count;
    openfilelist[fd].fcbstate = 1;
    free(buf);
    return ll;
}

//���ļ�����
int my_read(int fd, int len)
{
    char text[MAXTEXT];
    int ll;
    if (fd < 0 || fd >= MAXOPENFILE)
    {
        printf("�ļ�������!\n");
        return -1;
    }
    openfilelist[fd].count = 0;
    ll = do_read(fd, len, text); //ll��ʵ�ʶ������ֽ���
    if (ll != -1)
        printf("%s", text);
    else
        printf("��ȡʧ��!\n");
    return ll;
}

//ʵ�ʶ��ļ�����
int do_read(int fd, int len, char *text)
{
    fat *fat1, *fatptr;
    unsigned char *buf, *blkptr;
    unsigned short blkno, blkoff;
    int i, ll;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    buf = (unsigned char *)malloc(BLOCKSIZE);
    if (buf == NULL)
    {
        printf("�ڴ�ռ����ʧ��!\n");
        return -1;
    }
    blkno = openfilelist[fd].first;
    blkoff = openfilelist[fd].count;
    if (blkoff >= openfilelist[fd].length)
    {
        puts("��ȡ���ȴ����ļ�����!");
        free(buf);
        return -1;
    }
    fatptr = fat1 + blkno;
    while (blkoff >= BLOCKSIZE) //blkoffΪ���һ���̿�ʣ�������
    {
        blkno = fatptr->id;
        blkoff = blkoff - BLOCKSIZE;
        fatptr = fat1 + blkno;
    }
    ll = 0;
    while (ll < len)
    {
        blkptr = (unsigned char *)(myvhard + blkno * BLOCKSIZE);
        for (i = 0; i < BLOCKSIZE; i++) //�����һ���̿�����ݶ�ȡ��buf��
            buf[i] = blkptr[i];
        for (; blkoff < BLOCKSIZE; blkoff++)
        {
            text[ll++] = buf[blkoff];
            openfilelist[fd].count++;
            if (ll == len || openfilelist[fd].count == openfilelist[fd].length)
                break;
        }
        if (ll < len && openfilelist[fd].count != openfilelist[fd].length)
        {
            blkno = fatptr->id;
            if (blkno == END)
                break;
            blkoff = 0;
            fatptr = fat1 + blkno;
        }
    }
    text[ll] = '\0';
    free(buf);
    return ll;
}

//�˳��ļ�ϵͳ����
void my_exitsys()
{
    FILE *fp;
    while (curdir)
        curdir = my_close(curdir);
    fp = fopen(myfilename, "w");
    fwrite(myvhard, SIZE, 1, fp);
    fclose(fp);
    free(myvhard);
}

unsigned short findblock()
{
    unsigned short i;
    fat *fat1, *fatptr;
    fat1 = (fat *)(myvhard + BLOCKSIZE);
    for (i = 7; i < SIZE / BLOCKSIZE; i++)
    {
        fatptr = fat1 + i;
        if (fatptr->id == FREE)
            return i;
    }
    printf("�Ҳ������п�!\n");
    return -1;
}

int findopenfile()
{
    int i;
    for (i = 0; i < MAXTEXT; i++)
    {
        if (openfilelist[i].topenfile == 0)
            return i;
    }
    printf("�򿪵��ļ�̫��!\n");
    return -1;
}

