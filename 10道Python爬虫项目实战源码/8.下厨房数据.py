#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 下厨房数据
import requests
import time
import pandas
from bs4 import BeautifulSoup
start = time.time()
#用随机UA来访问
headers ={"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36"}
names = []
links = []
ellipsis_lists = []
authors = []
for page in range(0,2):
    url = 'https://www.xiachufang.com/explore/head/?page={}'.format(page)
    response = requests.get(url=url, headers=headers)
    html_data = response.text
    # print(html_data)
    bs = BeautifulSoup(html_data, 'html.parser')
    parent = bs.find('div', class_="normal-recipe-list").find_all('li')
    for item in parent:
        name = item.find('p', class_='name').find('a').text.strip()
        # print(name)
        names.append(name)

        link = 'https://www.xiachufang.com' + item.find('p', class_='name').find('a')['href']
        # print(link)
        links.append(link)

        ellipsis_list = item.find('p', class_='ing ellipsis').text.strip()
        # print(ellipsis_list)
        ellipsis_lists.append(ellipsis_list)

        author = item.find('p', class_='author').text.strip()
        # print(author)
        authors.append(author)

    time.sleep(2)
content = {'菜名':names,'链接':links,'配料表':ellipsis_lists,'作者':authors}
df = pandas.DataFrame(content)
print(df)