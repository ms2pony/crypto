import matplotlib.pyplot as plt
import pandas as pd

# 获取数据
df = pd.read_csv('mpg_ggplot2.csv')

# 绘制简单散点图
plt.figure(figsize=(6, 6))
plt.scatter(df.cty  # 横坐标
            , df.hwy)  # 纵坐标
plt.show()
