
import pygame, sys
import random




class Person():  # 人物
    def __init__(self, surf=None, y=None):
        self.surface = surf
        self.y = y  # y坐标
        self.w = (surf.get_width()) / 12  # 宽度
        self.h = surf.get_height() / 2  # 高度
        self.cur_frame = -1  # 当前的运动状态帧
        self.state = 0  # 0代表跑步状态，1代表跳跃状态,2代表连续跳跃
        self.gravity = 1 # 重力加速度
        self.velocity_y = 0  # y方向的速度
        self.vy_start = -20  # 起跳开始速度

    def getPos(self):   # 获取当前的位置信息，用于碰撞检测
        return (0, self.y + 12, self.w, self.h)


class Obstacle(object):  # 障碍物
    def __init__(self, surf, x=0, y=0):
        self.surface = surf
        self.x = x
        self.y = y
        self.w = surf.get_width()
        self.h = surf.get_height()
        self.cur_frame = random.randint(0, 6)  # 随机获取一种障碍物的类型
        self.w = 100
        self.h = 100

    def getPos(self):  # 当前的坐标信息
        return (self.x, self.y, self.w, self.h)

    def judgeCollision(self, rect1, rect2):  # 碰撞检测
        if (rect2[0] >= rect1[2] - 20) or (rect1[0] + 40 >= rect2[2]) or (rect1[1] + rect1[3] < rect2[1] + 20) or (
                rect2[1] + rect2[3] < rect1[1] + 20):
            return False
        return True


class BackGround(object):  # 背景
    def __init__(self, surf):
        self.surface = surf  # 初始化一个Surface 对象
        self.dx = -10
        self.w = surf.get_width()    # 返回 Surface 对象的宽度，以像素为单位。
        self.rect = surf.get_rect()  # 获取 Surface 对象的矩形区域


class PaoKu(object):
    def __init__(self):
        pygame.init()
        pygame.mixer.init()

        self.width = 1200  # 窗口宽度
        self.height = 500  # 窗口高度
        self.size = (self.width, self.height)
        self.screen = pygame.display.set_mode(self.size)
        pygame.display.set_caption('菜鸟学python')
        self.score = 0  # 分数
        self.font1 = pygame.font.Font("resource/simkai.ttf", 32)
        self.font2 = pygame.font.Font("resource/simkai.ttf", 64)  # 字体
        self.obstacle_pic = pygame.image.load("resource/obstacles.png").convert_alpha()  # 障碍物图片
        self.game_over = pygame.image.load("resource/gameover.bmp").convert_alpha()  # 游戏结束图片
        self.bg = BackGround(pygame.image.load("resource/bg.png").convert_alpha())  # 背景对象
        self.person = Person(pygame.image.load("resource/person.png").convert_alpha(), 500 - 85)  # 人物对象
        self.screen.blit(self.bg.surface, [0, 0])  # 初始化游戏背景

        self.obstacle_list = []  # 障碍物对象数组
        self.game_state = 0  # 游戏状态，0表示游戏中，1表示游戏结束# import os
# from PIL import Image
#
# def get_size(file):
#     # 获取文件大小:KB
#     size = os.path.getsize(file)
#     return int(size / 1024)
#
# def get_outfile(infile, outfile):
#     if outfile:
#         return outfile
#     dir, suffix = os.path.splitext(infile)
#     outfile = '{}-out{}'.format(dir, suffix)
#     return outfile
#
# def compress_image(infile, outfile='', mb=300, step=10, quality=10):
#     """不改变图片尺寸压缩到指定大小
#     :param infile: 压缩源文件
#     :param outfile: 压缩文件保存地址
#     :param mb: 压缩目标，KB
#     :param step: 每次调整的压缩比率
#     :param quality: 初始压缩比率
#     :return: 压缩文件地址，压缩文件大小
#     """
#     o_size = get_size(infile)
#     print(o_size)
#
#     if o_size <= mb:
#         return infile
#     outfile = get_outfile(infile, outfile)
#     while o_size > mb:
#         im = Image.open(infile)
#         im.save(outfile, quality=quality)
#         if quality - step < 0:
#             break
#         quality -= step
#         o_size = get_size(outfile)
#     return outfile, get_size(outfile)
#
# compress_image("微信图片.jpg")


        self.life = 100     # 初始的生命值
        self.clock = pygame.time.Clock()  # 时钟
        self.bg_music = pygame.mixer.Sound(r"resource\bgm.wav").play(-1, 0)  # 循环播放北京音乐

    def startGame(self, screen):   # 开始游戏界面
        gameStart = pygame.image.load("resource/start1new.png")
        screen.blit(gameStart, (0, 0))
        font = pygame.font.SysFont("resource/simkai.ttf", 70)
        tip = font.render("Press Any Key To Start!, Press Esc To Quit", True, (65, 105, 225))
        screen.blit(tip, (self.width / 2 - 550, self.height / 2 + 150))
        pygame.display.update()
        while True:
            for event in pygame.event.get():  # 关闭窗口
                if event.type == pygame.QUIT:
                    self.terminate()
                elif event.type == pygame.KEYDOWN:
                    if (event.key == pygame.K_ESCAPE):  # 按下ESC键
                        self.terminate()
                    else:
                        return
    def addObstacle(self):   # 添加障碍物
        rate = 4
        # 是否生成障碍物
        if not random.randint(0, 300) < rate:
            return
        y = random.choice([self.height - 100, self.height - 200, self.height - 300, self.height - 400])
        obstacle = Obstacle(self.obstacle_pic, self.width + 40, y)
        self.obstacle_list.append(obstacle)
    # 监听键盘事件，并做处理
    def ListenKeyBoard(self):  # 键盘事件处理

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                # 空格键跳跃
                if self.game_state == 0:
                    if event.key == pygame.K_SPACE:
                        pygame.mixer.Sound(r"resource\jump.wav").play()
                        if self.person.state == 0:
                            self.person.state = 1
                            self.person.velocity_y = self.person.vy_start
                        elif self.person.state == 1:
                            self.person.state = 2
                            self.person.velocity_y = self.person.vy_start
                elif self.game_state == 1:
                    if event.key == pygame.K_RETURN:   # 重新开始游戏
                        self.bg_music.stop()
                        self.__init__()

        if self.game_state == 0:
            # BackGorund的运动
            self.bg.dx += 10
            if self.bg.dx == 1200:
                self.bg.dx = 0

                # Person的移动
            if self.person.state == 0:
                self.person.cur_frame += 1
                if self.person.cur_frame == 12:
                    self.person.cur_frame = 0
            else:
                self.person.y += self.person.velocity_y
                self.person.velocity_y += self.person.gravity
                if self.person.y >= 500 - 85:
                    self.person.y = 500 - 85
                    self.person.state = 0
            # bstacle的操作
            self.addObstacle()

            for obstacle in self.obstacle_list:
                obstacle.x -= 10  # obstacle向左移动十个像素

                if obstacle.x + obstacle.w <= 0:  # 当obstacle离开界面时
                    self.obstacle_list.remove(obstacle)
                    self.score += 10000  # 避开obstacle，加10000分
                if obstacle.judgeCollision(self.person.getPos(), obstacle.getPos()):  # 碰撞检测
                    if obstacle.cur_frame == 6:
                        self.obstacle_list.remove(obstacle)
                        self.score += 10000  # 吃金币加100分
                        coin_sound = pygame.mixer.Sound(
                            r"resource/coin.wav")
                        coin_sound.play()
                    else:
                       self.life -= 1
                       self.obstacle_list.remove(obstacle)
                       if self.life <= 0:
                            self.game_state = 1  # 游戏失败
                       die_sound = pygame.mixer.Sound(
                           r"resource\die.wav")  # 添加碰撞之后产生的音效
                       die_sound.play()
    # 更新显示界面
    def updateScreen(self, screen):
            screen.blit(self.bg.surface, [-self.bg.dx, 0])  # 背景的贴图
            screen.blit(self.bg.surface, [1200 - self.bg.dx, 0])
            text = self.font1.render("score:%d" % self.score, True, (128, 128, 128))  # 分数的贴图
            screen.blit(text, (900, 20))
            del text
            rest_life = self.font1.render("life:%d" % self.life, True, (128, 128, 128))  # 剩余生命
            screen.blit(rest_life, (100, 20))
            del rest_life
            screen.blit(self.person.surface, [0, self.person.y], [int(self.person.cur_frame) * self.person.w, 0, self.person.w, self.person.h])  # 人物的贴图
            for obstacle in self.obstacle_list:  # 障碍物的贴图
                screen.blit(obstacle.surface, [obstacle.x, obstacle.y],
                            [int(obstacle.cur_frame) * obstacle.w, 0, obstacle.w, obstacle.h])
    # 判断游戏的状态
    def judgeState(self, screen):
        if self.game_state == 0:
            self.updateScreen(screen)
            return
        elif self.game_state == 1:
            screen.blit(self.game_over, [0, 0])
            text = self.font1.render("GameOver Score:%d  Press Enter to restart" % self.score, True, (255, 0, 0))
            screen.blit(text, (self.width / 2 - 350, self.height / 2 + 150))
    # 游戏结束
    def terminate(self):
        pygame.quit()
        sys.exit()

    # 游戏主入口函数
    def main(self):
        self.startGame(self.screen)
        while True:
            self.clock.tick(40)  # 设置时钟频率
            self.judgeState(self.screen)
            self.ListenKeyBoard()
            pygame.display.flip()

if __name__ == '__main__':
    paoku = PaoKu()
    paoku.main()
