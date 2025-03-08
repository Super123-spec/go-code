from tkinter import *
import time
import tkinter.messagebox


window = Tk()
# 设置主窗口大小
window.geometry('500x450')
window.geometry("+700+300")
# 设置主窗口标题
window.title('你喜欢我吗?')
def closeWindow():
    tkinter.messagebox.showerror(title="警告",message = "不许关闭,好好回答!")
    return
# 定义用户使用窗口管理器明确关闭窗口时发生的情况
window.protocol('WM_DELETE_WINDOW', closeWindow)

# 设置文字
lable1 = Label(window, text="hey,小姐姐", font=("微软雅黑", 14))

lable2 = Label(window, text="喜欢我吗？", font=("微软雅黑", 34))
# 设置图片
photo = PhotoImage(file='./cc.png')
imgLabel = Label(window, imag=photo)
# 调用tkinter的布局管理模块
lable1.pack()
lable2.pack()
imgLabel.pack()

# 点击喜欢的操作
def Love():
    # oplevel组件是一个独立的顶级窗口
    love = Toplevel(window)
    love.geometry('300x200')
    love.geometry("+800+350")
    love.title("好巧,我也是")
    lable = Label(love,text="好巧,我也是", font=("微软雅黑", 24))
    btn = Button(love, text="确定")
    btn.config(command=lambda :closelove(love))
    lable.pack()
    love.protocol('WM_DELETE_WINDOW', closeall)
    btn.pack()
# 点击不喜欢的操作
def NoLove():
    no_love = Toplevel(window)
    no_love.geometry('300x200')
    no_love.geometry("+800+350")
    no_love.title("再考虑考虑呗")
    lable = Label(no_love,text="再考虑考虑呗", font=("微软雅黑", 24))
    btn = Button(no_love, text="确定")
    btn.config(command=lambda :closenolove(no_love))
    lable.pack()
    btn.pack()
# 子窗口关闭操作
def closeall():
    window.destroy()

def closelove(no_love):
    window.destroy()
    # love.destroy()

def closenolove(no_love):
    no_love.destroy()
# 设置按钮
btn1 = Button(window, text="喜欢")
# 配置按钮
btn1.config(command=Love)
btn2 = Button(window, text="不喜欢")
btn2.config(command=NoLove)
# 调用tkinter的布局管理模块
btn1.pack()
btn2.pack()

window.mainloop()
