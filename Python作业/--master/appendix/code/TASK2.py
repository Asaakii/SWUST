'''TASK1,2,3：爬取好评、中评、及差评所对应的文件。
生成：“好评.xlsx”、“中评.xlsx”、“差评.xlsx”三个文件。'''
import re
import time
from urllib import request
import csv

info_result = []
for i in range(12):  # range(0,9)的话，输出i会发现i是0,1,2,3,4,5,6,7,8,如果是（7,9）的话，i是从7开始
    start_url = 'https://movie.douban.com/subject/26100958/comments?start='
    url = start_url + str(20 * i) + '&limit=20&sort=new_score&status=P&percent_type=m'  # 确定要爬取的入口链接，差评把最后m改l，好评改h
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36',
        'Cookie': 'bid=c4HcYpJ-ITQ; ll="118181"; __yadk_uid=g03Hrsyqt7kGA76PvFOXoZU0OkX5bE7o; push_noty_num=0; push_doumail_num=0; __gads=ID=de6d79c369b63f3c:T=1564017354:S=ALNI_Mb8h6rxfJBOinLgZGzkSnGfnYRb3g; _vwo_uuid_v2=D8AA0D38CA53E5BE4ED7ACC359B1504F3|3580c80d115689ec5d3ff9dc183d1131; ct=y; __utmc=30149280; ps=y; __utmv=30149280.19995; _pk_ref.100001.8cb4=%5B%22%22%2C%22%22%2C1564213575%2C%22https%3A%2F%2Faccounts.douban.com%2Fsafety%2Funlock_sms%2Fresetpassword%3Fconfirmation%3D4ca986011e34adcc%26alias%3D%22%5D; _pk_ses.100001.8cb4=*; __utma=30149280.2014977075.1563770428.1564201931.1564213577.13; __utmz=30149280.1564213577.13.8.utmcsr=accounts.douban.com|utmccn=(referral)|utmcmd=referral|utmcct=/safety/unlock_sms/resetpassword; __utmt=1; dbcl2="199955424:Qdm1dXOiqTA"; ck=vL3C; _pk_id.100001.8cb4=dada69f4c64a88f7.1563784878.8.1564213604.1564201941.; __utmb=30149280.3.10.1564213577'
    }
    data = request.Request(url=url, headers=headers)
    html1 = request.urlopen(data)
    data = html1.read().decode('utf-8')
    print(data)
    print("获取第" + str(i + 1) + "页")
    print(url)

    print("Start : %s" % time.ctime())
    time.sleep(15)  # 这么多秒之后再运行下面的程序
    print('End : %s' % time.ctime())

    # 下面就开始爬具体的内容了
    outtime_pattern = re.compile('<span class="comment-time " title="(.*?)">', re.S)
    outtime = re.findall(outtime_pattern, data)
    print(outtime)

    id_pattern = re.compile('<a href="https://www.douban.com/people/(.*?)/" class="">', re.S)
    id = re.findall(id_pattern, data)
    print(id)

    name_pattern = re.compile('/" class="">(.*?)</a>', re.S)
    name = re.findall(name_pattern, data)
    print(name)

    content_pattern = re.compile('<span class="short">(.*?)</span>', re.S)
    content = re.findall(content_pattern, data)

    votes_pattern = re.compile('<span class="votes">(.*?)</span>', re.S)
    votes = re.findall(votes_pattern, data)
    print(votes)

    scores_pattern = re.compile('<span class="allstar(.*?)rating" title="', re.S)
    scores = re.findall(scores_pattern, data)
    print(scores)

    degree_pattern = re.compile('0 rating" title="(.*?)"></span>', re.S)
    degree = re.findall(degree_pattern, data)
    print(degree)

    for j in range(len(outtime)):
        try:
            html = 'https://www.douban.com/people/' + str(id[j]) + '/'
            headers = {
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.142 Safari/537.36',
                'Cookie': 'bid=c4HcYpJ-ITQ; ll="118181"; __yadk_uid=g03Hrsyqt7kGA76PvFOXoZU0OkX5bE7o; push_noty_num=0; push_doumail_num=0; __gads=ID=de6d79c369b63f3c:T=1564017354:S=ALNI_Mb8h6rxfJBOinLgZGzkSnGfnYRb3g; _vwo_uuid_v2=D8AA0D38CA53E5BE4ED7ACC359B1504F3|3580c80d115689ec5d3ff9dc183d1131; ct=y; __utmc=30149280; ps=y; __utmv=30149280.19995; _pk_ref.100001.8cb4=%5B%22%22%2C%22%22%2C1564213575%2C%22https%3A%2F%2Faccounts.douban.com%2Fsafety%2Funlock_sms%2Fresetpassword%3Fconfirmation%3D4ca986011e34adcc%26alias%3D%22%5D; _pk_ses.100001.8cb4=*; __utma=30149280.2014977075.1563770428.1564201931.1564213577.13; __utmz=30149280.1564213577.13.8.utmcsr=accounts.douban.com|utmccn=(referral)|utmcmd=referral|utmcct=/safety/unlock_sms/resetpassword; __utmt=1; dbcl2="199955424:Qdm1dXOiqTA"; ck=vL3C; _pk_id.100001.8cb4=dada69f4c64a88f7.1563784878.8.1564213604.1564201941.; __utmb=30149280.3.10.1564213577'
            }
            data = request.Request(url=html, headers=headers)
            html = request.urlopen(data)
            a = html.read().decode('utf-8')

            city_pattern = re.compile('常居:&nbsp;<a href="https://(.*?)</a><br />', re.S)
            city1 = re.findall(city_pattern, a)
            if city1 == []:
                city = '未填'
            else:
                city = city1[0].split('>')[1]
            print(city)

            jointime1_pattern = re.compile('<div class="pl">(.*?)加入</div>', re.S)
            jointime1 = re.findall(jointime1_pattern, a)
            jointime = re.findall(r'\d{4}-\d{2}-\d{2}', str(jointime1))
            print(jointime)

            with open('中评.xlsx', 'a+', encoding='utf-8-sig', newline='') as datacsv:
                csvwriter = csv.writer(datacsv, dialect=("excel"))
                csvwriter.writerow(
                    [name[j], id[j], city, jointime[0], str(content[j]), outtime[j], scores[j], degree[j]])
        except:
            continue
        # 下面两行为了观察哪里出错了
        new2 = [name[j], id[j], jointime[0], city, outtime[j], scores[j], degree[j]]
        print(new2)
        print("Start : %s" % time.ctime())
        time.sleep(3)  # 这么多秒之后再运行下面的程序
        print('End : %s' % time.ctime())

        print('\n')
