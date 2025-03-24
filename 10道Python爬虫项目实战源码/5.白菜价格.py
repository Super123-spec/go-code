#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 白菜价格
import requests
url="https://m.smzdm.com/search/ajax_search_list?type=tag&channel=faxian&search_key=%E7%99%BD%E8%8F%9C%E5%85%9A&is_partner=0&timesort=1661820349&offset=4"
headers={"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36"}
parmes = {
        "type": "tag",
        "channel": "faxian",
        "search_key": "白菜党",
        "timesort": 1607519513
    }
response=requests.get(url=url,headers=headers).json()
# datas_list=response["data"]
import pandas as pd
df = pd.DataFrame(response['data'])
print(df)
df.to_excel('白菜价格数据.xlsx',index=False)
# print(datas_list)
