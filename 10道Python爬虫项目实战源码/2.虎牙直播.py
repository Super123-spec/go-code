#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 虎牙直播
"""
有基础同学 1
零基础同学 0
python计算机编程语言
python能做什么？
爬虫
在互联网下采集数据的程序
数据采集 流量数据 平台 15k 20万 兼职接单 就业
vip数据 300 300 600
数据分析，数据挖掘 自动化
数据可视化
web开发
知乎 豆瓣
flask django
人工智能

python怎么学？
爬虫程序基本步骤
1确定目标
2发送请求
3解析数据
4保存数据
项目实战能力
1
3个月-4个月每天花一个小时 兼职接单
100-800
2
就业转行能力
预定100 低2400优惠 7280 12期分期免息 598 3个月

上课直播上课
回访笔记 源码 课件
2 4 7晚上8点-10点
学习周期6个月 左右 3个月-4个月
学习有问题 兼职问题可以找木木老师
高清录播直播
保障学员学会才毕业
重修、





"""
# print("木木老师的课我是非常喜欢听")
import requests
import jsonpath
url="https://live.cdn.huya.com/livelist/game/tagLivelist?gameId=1663&tmpId=116&page=1"
data=requests.get(url).json()
print(data)
# $..解析数据 定位我们要的数据
img_url_list=jsonpath.jsonpath(data,'$..screenshot')
img_name_list=jsonpath.jsonpath(data,'$..nick')
print(img_name_list)
print(img_url_list)
for img_url,img_name in zip(img_url_list,img_name_list):
    img_data=requests.get(img_url).content
    file_name=img_name+'.jpg'
    print(file_name+"....正在下载")
    with open('img/'+file_name,'wb')as f:
        f.write(img_data)
