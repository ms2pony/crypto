## gnu向量指令解释
如果有个向量指令有三个操作数，那么gnu汇编的指令格式的3个操作数与intel文档描述的3个操作数是倒序关系：
比如 `op r1, r2, r3` (intel格式)，gnu汇编形式就是这样： `op %r3, %r2, %r1`
参考 https://github.com/kshitijl/avx2-examples.git (仓库地址)