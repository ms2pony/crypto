# title

## 签名与验签

使用 openssl cli，prime256v1 曲线，步骤如下：

1. 生成 ECDSA 私钥文件，曲线为 prime256v1
   openssl ecparam -name prime256v1 -genkey -out ecdsa_priv.pem
2. 显示私钥信息
   openssl ec -in ecdsa_priv.pem -text -noout
3. 生成私钥对应的公钥文件
   openssl ec -in ecdsa_priv.pem -pubout -out ecdsa_pub.pem
4. 查看公钥信息
   openssl ec -in ecdsa_pub.pem -pubin -text -noout
5. 将消息存入文件并用前面生成的公钥和私钥进行签名
   echo "signed message" > plain.txt
6. 进行签名，Hash 算法使用 sha256 算法
   openssl dgst -sha256 -sign ecdsa_priv.pem -out signature.txt plain.txt
7. 校验签名
   openssl dgst -sha256 -verify ecdsa_pub.pem -signature signature.txt plain.txt

## 调试签名与验签

requirement:vscode, openssl

### 调试签名

使用本目录下的 openssl 命令`/home/tam/Desktop/bignum/openssl/apps/openssl dgst -sha256 -sign ecdsa_priv.pem -out signature.txt plain.txt`

1. 设置 launch.json

    ```json
    "program": "${workspaceFolder}/openssl/apps/openssl", //修改
    "args": [
    "dgst",
    "-sha256",
    "-sign",
    "test/ECDSA/ecdsa_priv.pem",
    "-out",
    "test/ECDSA/signature.txt",
    "test/ECDSA/plain.txt"
    ], //修改
    "stopAtEntry": false,
    "cwd": "${workspaceFolder}", //修改
    ```

2. 编写多次执行 ECDSA 签名脚本, `runECDSA.sh`，并赋予执行权限`chmod +x runECDSA.sh`
3. 使用`perf`工具追踪
   - 下载 perf：`apt-get install linux-tools-$(uname -r) linux-tools-generic -y`
   - 开始追踪：`sudo perf record -g ./runECDSA.sh`
   - 查看追踪结果`sudo perf report -g`

### 调试验签

在 section`调试签名`的基础上做一些改动，设置`launch.json`：

```json
"args": [
    "dgst",
    "-sha256",
    "-verify",
    "test/ECDSA/ecdsa_pub.pem",
    "-out",
    "test/ECDSA/signature.txt",
    "test/ECDSA/plain.txt"
   ], //改动
```
