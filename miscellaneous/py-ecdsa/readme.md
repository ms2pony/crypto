## 涉及算法

欧几里得算法(辗转相除法)、欧几里得扩展算法

## 欧几里得扩展算法和求逆

### 欧几里得和欧几里得扩展算法

参考：<https://blog.csdn.net/u014634338/article/details/40210435>

欧几里得算法:设a=bq+r，其中a,b,q,r都是整数，则gcd(a,b)=gcd(b,r)

欧几里得扩展算法就是求得给定a,b的gcd(a,b)以及x,y，使得gcd(a,b)=ax+by，

### 通过欧几里得算法求逆元

参考：<https://blog.csdn.net/sdz20172133/article/details/81291368>

如果gcd(a,b)=1，则ax+by=1，那么通过欧几里得算法就可以得到一个结论：
"如果a,b两个整数互质，则他们互有逆元"，因为$ax+by=1=>ax \equiv 1(\bmod b)$即a在模b下有逆元，逆元为x
