#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 图虫小姐姐照片爬取
import requests
import jsonpath
url="https://tuchong.com/rest/tags/%E7%BE%8E%E5%A5%B3/posts"
num=10
index=0
for page in range(1,num+1):
    parmes={'page':page,'count':20,'order':'weekly','before_timestamp':''}
    response=requests.get(url,params=parmes).json()
    print(response)
    img_urls=jsonpath.jsonpath(response,"$..cover_image_src")
    print(img_urls)
    for img_url in img_urls:
        img_content=requests.get(img_url).content
        index+=1
        with open(r"./{}/{}.jpg".format("图虫", index), "wb")as f:
            f.write(img_content)
            print(r"*****正在下载:{}.jpg".format(index))

