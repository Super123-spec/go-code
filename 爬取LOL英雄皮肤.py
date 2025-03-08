import os
import requests
import time
from concurrent.futures import ThreadPoolExecutor

header = {
    'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36 Edg/111.0.1661.54'
}


# 获取LOL英雄的id
def ID():
    # 创建一个列表用于存放英雄的id
    id = []
    # 访问存放有英雄id的接口
    burl = 'https://game.gtimg.cn/images/lol/act/img/js/heroList/hero_list.js'
    breq = requests.get(burl).json()  # 拿接口的JSON文件可以更快的帮我们定位到想要的数据
    for i in breq['hero']:
        id.append(i['heroId'])  # 把获取到的id放入列表
    return id


# 获取LOL英雄的名字作为文件的命名
def name_spider(id, choose):
    names = []  # 存放英雄皮肤名字的列表
    surl = []  # 存放英雄皮肤链接的列表
    uname = 'https://game.gtimg.cn/images/lol/act/img/js/hero/' + str(id) + '.js'
    # 访问的链接，拿到每个英雄的详细信息的JSON文件
    ureq = requests.get(uname, headers=header).json()
    # 对访问到的JSON文件进行处理，获取到我们想要的数据
    for k in ureq['skins']:
        if k['chromas'] == '0':     # 当chromas标签 = 0时会是皮肤的原画（ = 1是皮肤的炫彩，不过我们不需要这个）
            names.append(k['name'])
            surl.append(k['mainImg'])
    # 爬取图片和保存函数（全写在一起就太多了点不好看，就分开写了）
    photo_spider(names, surl, choose)  # 爬到的皮肤名称和图片的链接作为参数传进函数


# 爬取具体图片函数，choose=0会把图片分门别类，放到对应的英雄的文件夹里面，其他数字就直接把图片存入指定文件夹
def photo_spider(names, surl, choose=1, path=r'./lol_skin'):
    # 判断选择的数据存储方式
    if choose == 0:
        # 下载的图片保存到的文件夹
        os.makedirs(path + r'/' + str(names[0]))  # 在指定文件夹下创建个英雄皮肤的文件夹
        os.chdir(path + r'/' + str(names[0]))  # 切换当前工作路径为指定路径
    else:
        os.chdir(path)  # 切换当前工作路径为指定路径
    # 对图片链接进行访问
    for i in range(len(surl)):
        photoreq = requests.get(surl[i]).content  # 因为是图片，所以这里我们拿二进制流返回
        # 保存到文件夹，按照皮肤的名字命名，保存的格式为png格式
        # 因为某些皮肤的名字中有"/"（例：K/DA这个系列的皮肤），会影响文件的保存，所以要替换掉
        with open(names[i].replace('/', '') + '.png', 'wb') as f:
            f.write(photoreq)


if __name__ == '__main__':
    # 程序开始时间
    if not os.path.exists('lol_skin'):
        os.makedirs('lol_skin')
    time_start = time.time()
    choose = input("输入需要存储的类型(0-把皮肤分类放到各个英雄的文件夹下):")
    print('开始下载了，耐心等待.........')
    # 调用函数爬取英雄的id
    id = ID()
    # 创建线程池，开启20个进程
    pool = ThreadPoolExecutor(max_workers=20)
    for pic_url in id:
        # 将耗时间的任务放到线程池中交给线程来执行
        pool.submit(name_spider, pic_url, choose)  # 执行的函数，函数所需的参数
    pool.shutdown()  # 让main函数在线程全部结束之后再结束
    # 程序结束时间
    time_end = time.time()
    print('下载完成')
    print('程序执行的时间:' + str(time_end - time_start))
