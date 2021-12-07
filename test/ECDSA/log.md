# 生成ECDSA私钥文件，曲线为prime256v1
openssl ecparam -name prime256v1 -genkey -out ecdsa_priv.pem
# 显示私钥信息
openssl ec -in ecdsa_priv.pem -text -noout
# 生成私钥对应的公钥文件
openssl ec -in ecdsa_priv.pem -pubout -out ecdsa_pub.pem
# 查看公钥信息
openssl ec -in ecdsa_pub.pem -pubin -text -noout
# 将消息存入文件并用前面生成的公钥和私钥进行签名
echo "signed message" > plain.txt
# 进行签名，Hash 算法使用 sha256 算法
openssl dgst -sha256 -sign ecdsa_priv.pem -out signature.txt plain.txt
# 校验签名
openssl dgst -sha256 -verify ecdsa_pub.pem -signature signature.txt plain.txt
# 调试openssl命令行签名过程
使用本目录下的openssl命令`/home/tam/Desktop/bignum/openssl/apps/openssl dgst -sha256 -sign ecdsa_priv.pem -out signature.txt plain.txt`
1. 设置launch.json
```json
"program": "${workspaceFolder}/openssl/apps/openssl",	//修改
"args": [
				"dgst",
				"-sha256",
				"-sign",
				"test/ECDSA/ecdsa_priv.pem",
				"-out",
				"test/ECDSA/signature.txt",
				"test/ECDSA/plain.txt"
			],	//修改
"stopAtEntry": false,
"cwd": "${workspaceFolder}", //修改
```
2. 编写多次执行ECDSA签名脚本, `runECDSA.sh`，并赋予执行权限`chmod +x runECDSA.sh`
3. 使用`perf`工具追踪
   - 下载perf：`apt-get install linux-tools-$(uname -r) linux-tools-generic -y`
   - 开始追踪：`sudo perf record -g ./runECDSA.sh`
   - 查看追踪结果`sudo perf report -g`

# 调试openssl命令行验签过程
就在`# 调试openssl命令行签名过程`的基础上做一些改动，设置`launch.json`：
```json
"args": [
				"dgst",
				"-sha256",
				"-verify",
				"test/ECDSA/ecdsa_pub.pem",
				"-signature",
				"test/ECDSA/signature.txt",
				"test/ECDSA/plain.txt"
			],	//改动
```