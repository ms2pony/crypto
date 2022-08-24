## wsl 下 windows 路径

- `/mnt/f/iii/ii/i/workStudation/code`

## 从某个项目(路径)下启动 jupyter

   `jupyter notebook --notebook-dir=/to/your/path`

## 使用环境变量来指定动态库的位置

设置LD_LIBRARY_PATH，设置其为openssl项目根目录，命令如下：

`export LD_LIBRARY_PATH="/home/tam/github/crypto/openssl"`

`sudo ldconfig`

直接运行该脚本没用，需要手动执行上面面两条指令
