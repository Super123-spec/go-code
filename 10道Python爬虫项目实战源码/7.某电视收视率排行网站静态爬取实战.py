#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 某电视收视率排行网站静态爬取实战
"""
re xpath bs4 pyquery
xpath
"""
import csv  # 用于数据存储
import requests  # 用于请求网页
import chardet  # 用于修改编码
import re  # 用于提取数据
from lxml import etree  # 解析数据的库
import time  # 可以粗糙模拟人为请求网页的速度
import warnings  # 忽略代码运行时候的警告信息

warnings.filterwarnings("ignore")


def get_data(url):
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/71.0.3578.98 Safari/537.36'}
    rqg = requests.get(url, headers=headers, verify=False)  # a
    rqg.encoding = chardet.detect(rqg.content)['encoding']  # b
    html = etree.HTML(rqg.text)

    # 1. 标题
    title = html.xpath('//header[@class="entry-header"]/table/tbody/tr/td[2]/font/h2/a/@title')
    # 2. 发布时间
    date = html.xpath('//header[@class="entry-header"]/table/tbody/tr/td[2]/div/time/text()')
    # 3. 链接
    link = html.xpath('//header[@class="entry-header"]/table/tbody/tr/td[2]/font/h2/a/@href')

    return title, date, link


def main():
    x = "http://www.tvtv.hk/archives/category/tv/page/"
    url_list = [x + str(i) for i in range(1, 11)]

    headers = ['标题', '发布时间', '链接']
    values = []
    titles = []
    dates = []
    links = []
    for url in url_list:
        print('>> 正获取： ', url)
        title, date, link = get_data(url)
        for t in title:
            titles.append(t)
        for d in date:
            dates.append(d)
        for l in link:
            links.append(l)

        time.sleep(3)  # 加时间延迟，减少访问频率

    for i in range(len(titles)):
        value = [titles[i], dates[i], links[i]]
        values.append(value)

    with open('电视台.csv', 'w', newline='') as fp:
        # 获取对象
        writer = csv.writer(fp)
        # 写入数据
        writer.writerow(headers)  # 写入表头
        writer.writerows(values)  # 写入数据


if __name__ == '__main__':
    main()