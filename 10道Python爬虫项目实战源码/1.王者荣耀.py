#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 图灵木木老师
# @File    : 王者荣耀
"""
爬虫的基本步骤
1确定目标 菜市场位置
2发送请求 200 400
3解析数据
4保存数据
"""
import requests
from pyquery import PyQuery
url="https://pvp.qq.com/web201605/herolist.shtml"
html=requests.get(url).content
# print(html)
doc=PyQuery(html)
itmes=doc('.herolist>li').items()
print(itmes)
for item in itmes:
    url=item.find('img').attr('src')
    print(url)
    urls="https:"+url
    print(urls)
    name=item.find('a').text()
    print(name)
    url_content=requests.get(urls).content
    with open('./picture'+name+'.jpg','wb')as file:
        file.write(url_content)
