import random
 
# 设置最大值和最小值
min_val = 1
max_val = 6
 
# 是否继续
roll_again = "yes"
 
# 循环
while roll_again == "yes" or roll_again == "y":
    print("开始掷骰子")
    print("骰子数值是 :")
 
    # 第一轮
    print(random.randint(min_val, max_val))
 
    # 第二轮
    print(random.randint(min_val, max_val))
 
    # 是否继续
    roll_again = input("是否继续掷骰子?(是的话, 输入yes或者y)")