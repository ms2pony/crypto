## 部署openssl

`git clone --branch=OpenSSL_1_1_1-stable https://github.com/openssl/openssl.git`

`./config no-shared` `no-shared`选项，只生成静态库，避免链接静态库时链接成了动态库

## 下载 openssl 仓库

git clone <https://github.com/openssl/openssl.git>

### 有问题的分支，`./config`执行时会出错，OpenSSL_1_1_0g 等分支会有问题

### 切换到合适分支

git checkout -b 1.1.0stable origin/OpenSSL_1_1_0-stable

### 某些分支名会出现前面有`head`的问题，解决方法如下

git branch -m OpenSSL_1_1_0f openssl-1.1.0f # 改分支名，避免混淆

### 修改 makefile 中的 cflag，此处省略
