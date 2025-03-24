#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author  : 木木老师
# @File    :
"""
爬虫是什么？
采集数据  在互联网下采集数据得程序  电脑数据 手机数据
爬虫能做什么？
采集数据 就业 兼职 流量数据 爬虫 外包提供机会
爬虫怎么学习？
html
css
js
1确定目标 学校地址
2发送请求 200
3解析数据 火车 高铁 打包车
4保存数据 到教师 开始读书
兼职接单
就业转行
扣1
预定100 前三名同学低2400 最后7280 12 免息 一个月598
上课方式直播+录播，有视频 笔记，源码 课件
每个星期2，4，7 晚上8点到10点
6个月左右 3到4个月
零基础开始教学
保障学员学会才毕业




"""
import requests
import json
cookies = {
    'thw': 'cn',
    't': '3657a009343b2af328729fc66e2cf5d1',
    'cna': 'pzCIGaCyNwECAa8AOslfcGh7',
    'sgcookie': 'E100Bg2cIglbKXmchXgYntXWSwrr%2BGzVNxST4LzAMYB0mbxnZLWOEiTESfYwhCLAPhnXCmoDxYSDq7lglMyM%2Bu2hDQfLNUYf4kVVqtGmUEIFANc%3D',
    'uc3': 'vt3=F8dCv4CIM9ZzQUTYPQE%3D&lg2=WqG3DMC9VAQiUQ%3D%3D&nk2=F5RHoWPz1K4fOxyL&id2=UUpgRSoNhUCEvAigFA%3D%3D',
    'lgc': 'tb2029960110',
    'uc4': 'nk4=0%40FY4Ms466fuTumCvK3EmDSmgpB0lg5X8%3D&id4=0%40U2gqykLkvZ2PGePeeDMIOQh3IEiPE0IQ',
    'tracknick': 'tb2029960110',
    '_cc_': 'UtASsssmfA%3D%3D',
    'enc': 'oDihk%2BJbr7qLP35epH5bg%2FJavXCwI51jaq8lrC%2B%2FFpnfR3tcJ8jYGImnELPL2F17DoB3hZjb8BHtcFMmWy7HsgyZ8W3KeolMlyS%2FgB4IYQg%3D',
    '_m_h5_tk': '782e5e8ebb4bd554e0c3af870b52a4a2_1660723851250',
    '_m_h5_tk_enc': 'b8ae3a28bbe38bc8b7318e6c94331536',
    'cookie2': '136caac839e09f1181bec4019994060a',
    '_tb_token_': 'e01eb733a9678',
    'mt': 'ci=-1_0',
    'xlly_s': '1',
    '_samesite_flag_': 'true',
    'isg': 'BBUVQhcG26ibkvzlzrOuU1dWJBHPEskka5DEcpe9dQzb7jXgX2B_9ETvuPLYaeHc',
    'l': 'eBg2NxWngRs_tTgYBO5Churza779VBdb41PzaNbMiInca6dCtF9gPOCHJuE6SdtjgtCF_etPNKfZAdLHR3fRwxDDBbN014jZDxvO.',
    'tfstk': 'ckROBN2cVDmib2W5hFHh3Y3XS8glapmAAPs0MIrrsnk0PDVzZsbDZQLwUA_f4G3d.',
    'uc1': 'cookie14=UoeyDtjyS78wdw%3D%3D',
}

headers = {
    'authority': 'h5api.m.taobao.com',
    'accept': '*/*',
    'accept-language': 'zh-CN,zh;q=0.9,en;q=0.8',
    # Requests sorts cookies= alphabetically
    # 'cookie': 'thw=cn; t=3657a009343b2af328729fc66e2cf5d1; cna=pzCIGaCyNwECAa8AOslfcGh7; sgcookie=E100Bg2cIglbKXmchXgYntXWSwrr%2BGzVNxST4LzAMYB0mbxnZLWOEiTESfYwhCLAPhnXCmoDxYSDq7lglMyM%2Bu2hDQfLNUYf4kVVqtGmUEIFANc%3D; uc3=vt3=F8dCv4CIM9ZzQUTYPQE%3D&lg2=WqG3DMC9VAQiUQ%3D%3D&nk2=F5RHoWPz1K4fOxyL&id2=UUpgRSoNhUCEvAigFA%3D%3D; lgc=tb2029960110; uc4=nk4=0%40FY4Ms466fuTumCvK3EmDSmgpB0lg5X8%3D&id4=0%40U2gqykLkvZ2PGePeeDMIOQh3IEiPE0IQ; tracknick=tb2029960110; _cc_=UtASsssmfA%3D%3D; enc=oDihk%2BJbr7qLP35epH5bg%2FJavXCwI51jaq8lrC%2B%2FFpnfR3tcJ8jYGImnELPL2F17DoB3hZjb8BHtcFMmWy7HsgyZ8W3KeolMlyS%2FgB4IYQg%3D; _m_h5_tk=782e5e8ebb4bd554e0c3af870b52a4a2_1660723851250; _m_h5_tk_enc=b8ae3a28bbe38bc8b7318e6c94331536; cookie2=136caac839e09f1181bec4019994060a; _tb_token_=e01eb733a9678; mt=ci=-1_0; xlly_s=1; _samesite_flag_=true; isg=BBUVQhcG26ibkvzlzrOuU1dWJBHPEskka5DEcpe9dQzb7jXgX2B_9ETvuPLYaeHc; l=eBg2NxWngRs_tTgYBO5Churza779VBdb41PzaNbMiInca6dCtF9gPOCHJuE6SdtjgtCF_etPNKfZAdLHR3fRwxDDBbN014jZDxvO.; tfstk=ckROBN2cVDmib2W5hFHh3Y3XS8glapmAAPs0MIrrsnk0PDVzZsbDZQLwUA_f4G3d.; uc1=cookie14=UoeyDtjyS78wdw%3D%3D',
    'referer': 'https://uland.taobao.com/',
    'sec-ch-ua': '"Chromium";v="104", " Not A;Brand";v="99", "Google Chrome";v="104"',
    'sec-ch-ua-mobile': '?0',
    'sec-ch-ua-platform': '"Windows"',
    'sec-fetch-dest': 'script',
    'sec-fetch-mode': 'no-cors',
    'sec-fetch-site': 'same-site',
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/104.0.0.0 Safari/537.36',
}

params = {
    'jsv': '2.5.1',
    'appKey': '12574478',
    't': '1660721380942',
    'sign': '775e45280c4be361d78ae61aa342f0bf',
    'api': 'mtop.alimama.union.xt.en.api.entry',
    'v': '1.0',
    'AntiCreep': 'true',
    'timeout': '20000',
    'AntiFlood': 'true',
    'type': 'jsonp',
    'dataType': 'jsonp',
    'callback': 'mtopjsonp2',
    'data': '{"pNum":0,"pSize":"60","refpid":"mm_26632258_3504122_32538762","variableMap":"{\\"q\\":\\"电脑\\",\\"navigator\\":false,\\"clk1\\":\\"266a8ebb978f7522787dada4211f79b9\\",\\"union_lens\\":\\"recoveryid:201_33.5.45.98_28206737_1660720582640;prepvid:201_33.5.45.98_28206737_1660720582640\\",\\"recoveryId\\":\\"201_33.44.59.40_5921570_1660721380571\\"}","qieId":"36308","spm":"a2e0b.20350158.31919782","app_pvid":"201_33.44.59.40_5921570_1660721380571","ctm":"spm-url:a2e0b.20350158.31919782.1;page_url:https%3A%2F%2Fuland.taobao.com%2Fsem%2Ftbsearch%3Frefpid%3Dmm_26632258_3504122_32538762%26keyword%3D%25E7%2594%25B5%25E8%2584%2591%26clk1%3D266a8ebb978f7522787dada4211f79b9%26upsId%3D266a8ebb978f7522787dada4211f79b9%26spm%3Da2e0b.20350158.31919782.1%26pid%3Dmm_26632258_3504122_32538762%26union_lens%3Drecoveryid%253A201_33.5.45.98_28206737_1660720582640%253Bprepvid%253A201_33.5.45.98_28206737_1660720582640%26pnum%3D0"}',
}

response = requests.get('https://h5api.m.taobao.com/h5/mtop.alimama.union.xt.en.api.entry/1.0/', params=params, cookies=cookies, headers=headers).content.decode()[12:-1]
# print(response)
data_dict=json.loads(response)
print(data_dict)
data_lists=data_dict["data"]["recommend"]["resultList"]
# print(data_lists)
results=[]
for data in data_lists:
    result={
    'shop_nam':data['itemName'],
    'shop_titie':data['shopTitle'],
    'shop_id':data['categoryId'],
    'shop_place':data["provcity"],
    'shop_url':data["url"],
    'shop_price':data["price"],
    'min_price':data["promotionPrice"]
    }
    results.append(result)
    print(results)
    import pandas as pd
    df=pd.DataFrame(results)
    df.to_excel("淘宝电脑02数据.xlsx",index=False)
