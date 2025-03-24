#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 百度图片抓取

"""
爬虫的基本步骤
1确定目标
2发送请求
3解析数据
4保存数据
"""
import requests
import re
import os
number=10
keyword="周杰伦"
if not os.path.exists(keyword):
    os.makedirs(keyword)
url=r'http://image.baidu.com/search/flip?tn=baiduimage&ipn=r&ct=201326592&cl=2&lm=-1&st=-1&fm=result&fr=&sf=1&fmq' \
      r'=1497491098685_R&pv=&ic=0&nc=1&z=&se=1&showtab=0&fb=0&width=&height=&face=0&istype=2&ie=utf-8&ctd' \
      r'=1497491098685%5E00_1519X735&word='+ keyword
headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/102.0.5005.63 Safari/537.36'}
res=requests.get(url,headers=headers)
print(res)
picture_url=re.findall(r'objURL":"(.*?)",',res.text)
a=1
for i in picture_url:
    a+=1
    try:
        print(i)
        picture=requests.get(i,headers=headers,timeout=10)
        name=r"%s/%s_%d.jpg" %(keyword,keyword,a)
        with open(name,"wb")as f:
            f.write(picture.content)
        print("第%d张的图片在下载" %a)
    except:
        print("第%d张的图片在下载失败")
    if a>=number:
        break

