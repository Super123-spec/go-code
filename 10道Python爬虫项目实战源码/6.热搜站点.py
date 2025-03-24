#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    : 热搜站点
import requests

cookies = {
    '__51vcke__JfnM3vQtoqYTp8f8': '93f84f6a-27ab-5c41-88b0-ad8ecf590663',
    '__51vuft__JfnM3vQtoqYTp8f8': '1659512870774',
    'PHPSESSID': 'tt9ljn9nbui4bqvoltt9ts5b70',
    'Hm_lvt_1d9b8e4e110b54c48922093ef42f94fe': '1662368409,1663501922,1664182377',
    '__51uvsct__JfnM3vQtoqYTp8f8': '8',
    'Hm_lpvt_1d9b8e4e110b54c48922093ef42f94fe': '1664182384',
    '__vtins__JfnM3vQtoqYTp8f8': '%7B%22sid%22%3A%20%2244fc2d95-58b3-507c-b908-d72a6bcbfe57%22%2C%20%22vd%22%3A%202%2C%20%22stt%22%3A%206487%2C%20%22dr%22%3A%206487%2C%20%22expires%22%3A%201664184183702%2C%20%22ct%22%3A%201664182383702%7D',
}

headers = {
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
    'Accept-Language': 'zh-CN,zh;q=0.9,en;q=0.8',
    'Cache-Control': 'max-age=0',
    'Connection': 'keep-alive',
    # Requests sorts cookies= alphabetically
    # 'Cookie': '__51vcke__JfnM3vQtoqYTp8f8=93f84f6a-27ab-5c41-88b0-ad8ecf590663; __51vuft__JfnM3vQtoqYTp8f8=1659512870774; PHPSESSID=tt9ljn9nbui4bqvoltt9ts5b70; Hm_lvt_1d9b8e4e110b54c48922093ef42f94fe=1662368409,1663501922,1664182377; __51uvsct__JfnM3vQtoqYTp8f8=8; Hm_lpvt_1d9b8e4e110b54c48922093ef42f94fe=1664182384; __vtins__JfnM3vQtoqYTp8f8=%7B%22sid%22%3A%20%2244fc2d95-58b3-507c-b908-d72a6bcbfe57%22%2C%20%22vd%22%3A%202%2C%20%22stt%22%3A%206487%2C%20%22dr%22%3A%206487%2C%20%22expires%22%3A%201664184183702%2C%20%22ct%22%3A%201664182383702%7D',
    'Referer': 'https://hot.meibp.com/',
    'Sec-Fetch-Dest': 'document',
    'Sec-Fetch-Mode': 'navigate',
    'Sec-Fetch-Site': 'same-origin',
    'Sec-Fetch-User': '?1',
    'Upgrade-Insecure-Requests': '1',
    'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36',
    'sec-ch-ua': '"Chromium";v="104", " Not A;Brand";v="99", "Google Chrome";v="104"',
    'sec-ch-ua-mobile': '?0',
    'sec-ch-ua-platform': '"Windows"',
}

response = requests.get('https://hot.meibp.com/', cookies=cookies, headers=headers)
print(response)
from lxml import etree
html=etree.HTML(response.text)
divs=html.xpath('//div[@class="items"]/div[@class="row"]/div')
for div in divs:
    cat=div.xpath('./a/@title')
    for a in div.xpath('./div/div/a'):
        result={
            "热搜类别": "".join(cat),
            "标题": "".join(a.xpath('./@title')),
            "链接": "".join(a.xpath('./@href'))
        }
        print(result)
        import pandas as pd
        df=pd.DataFrame(result,index=range(0,4))
        print(df.to_excel('热搜数据.xlsx'))