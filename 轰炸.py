# coding: utf-8
__author__ = 'Mac'
__date__ = '19/10/31 15:05'

import time
from pynput.keyboard import Controller as key_cl
from pynput.mouse import Button, Controller

def keyboard_input(string):
    """
    模拟键盘输入字符串。

    :param string: 要输入的字符串。
    :return: None
    """
    keyboard = key_cl()  # 初始化键盘控制器
    keyboard.type(string)  # 模拟键盘输入字符串

def mouse_click():
    """
    模拟鼠标点击操作。

    :return: None
    """
    mouse = Controller()  # 初始化鼠标控制器
    mouse.press(Button.left)  # 模拟鼠标左键按下
    mouse.release(Button.left)  # 模拟鼠标左键释放

def main(number, string):
    """
    主函数，用于自动化发送消息。

    :param number: 要发送的消息数量。
    :param string: 要发送的消息内容。
    :return: None
    """
    time.sleep(10)  # 等待5秒，以便用户打开聊天窗口并将鼠标放置在发送按钮上
    for i in range(number):
        keyboard_input(string + str(i))  # 输入消息内容
        mouse_click()  # 点击发送按钮
        time.sleep(2)  # 等待0.2秒，避免发送过快

if __name__ == '__main__':
    main(99, "我要看梦泪诡偷移晶")
