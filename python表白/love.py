
from tkinter import *
from tkinter import messagebox

window = Tk()
# 设置主窗口大小
window.geometry('600x600')
# 设置窗口位置
window.geometry("+400+300")
# 设置主窗口标题
window.title('告白')


# 不允许关闭窗口
def closeWindow():
    messagebox.showinfo(title="警告", message="不许关闭,好好回答!")
    return


# 定义用户使用窗口管理器明确关闭窗口时发生的情况
window.protocol('WM_DELETE_WINDOW', closeWindow)

# 设置文字  标签控件
lable1 = Label(window, text="hey,小姐姐", font=("微软雅黑", 14))
# 你可以使用sticky选项去指定对齐方式 上下左右   N S W E
lable1.grid(row=0, column=0, sticky=W)
lable2 = Label(window, text="喜欢我吗？", font=("微软雅黑", 30))
lable2.grid(row=1, column=1, sticky=E)

# 设置图片
photo = PhotoImage(file='./cc.png')
imgLabel = Label(window, image=photo)
# columnspan 组件所跨越的列数
imgLabel.grid(row=2, columnspan=2)


# 点击喜欢的操作
def Love():
    # Toplevel组件是一个独立的顶级窗口
    love = Toplevel(window)
    love.geometry('300x150+450+350')
    love.title("我就知道你会同意的，那我现在来找你了哦  ")
    lable = Label(love, text="我就知道你会同意", font=("微软雅黑", 24))
    lable.pack()
    btn = Button(love, text="确定", width=10, height=2, command=closewindow)
    btn.pack()
    love.protocol('WM_DELETE_WINDOW', closelove)


def closelove():
    return


def closewindow():
    window.destroy()


# 点击不喜欢的操作
def NoLove():
    no_love = Toplevel(window)
    no_love.geometry('300x100+450+350')
    no_love.title("再考虑考虑呗")
    lable = Label(no_love, text="再考虑考虑呗", font=("微软雅黑", 24))
    lable.pack()
    btn = Button(no_love, text="好的", width=10, height=2, command=no_love.destroy)
    # btn = Button(no_love, text="好的", width=10, height=2, command=NoLove)
    btn.pack()
    # 关闭触发的方法
    no_love.protocol('WM_DELETE_WINDOW', closenolove)


def closenolove():
    NoLove()


# 设置按钮
btn1 = Button(window, text="喜欢", width=15, height=2, command=Love)
btn1.grid(row=3, column=0, sticky=W)
btn2 = Button(window, text="不喜欢", width=5, command=NoLove)
btn2.grid(row=3, column=1, sticky=E)
window.mainloop()
