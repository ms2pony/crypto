## 一些操作说明

### 符号导出

导出`ecp_nistz256_mul_mont`等默认不对外开放的函数(符号)，动态库不开放这些函数，静态库开放，要使动态库开放，找到`openssl`根目录下的 makefile，大概 757 行这个样子，这行的关键词为：
`--version-script=libcrypto.map`
上面的关键词提到了文件`libcrypto.map`，我们需要修改这个内容，添加你需要导出的函数，然后重新`make`，即可使用那些默认不导出的函数了

## avx2 内联函数
