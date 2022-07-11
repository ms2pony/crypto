## 20220625

### almMonInv实现时出现的问题

参考：`F:\iii\ii\i\workStudation\workStation\paper\nlog\note.md` k Almost Montgomery Inverse 算法

1. 用`//`而不是`/`,因为使用`/`会使结果低位上的数丢失(在计算大数情况下)
2. 参与计算的数的位数不大时并不遵循 $\left\lceil\log _{2}(a)\right\rceil \leq k \leq 2\left\lceil\log_{2}(a)\right\rceil$，k有时会小于 $\lceil\log _{2}(a)\rceil$
