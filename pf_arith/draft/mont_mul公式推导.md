$t=(T+mN)/R, 其中m=(T \bmod R)N^\prime \bmod R$



$R=r^n, N^\prime \bmod r=1$

求 $t=TR^{-1} \bmod N$



解：

$t=TR^{-1}\bmod N=Tr^{-n}\bmod N=Tr^{-1}\cdot r^{-1} \cdot ... \cdot r^{-1}\bmod N$

分析 $Tr^{-1}\bmod N$，有：

$m=(T \bmod r)N^\prime \bmod r=T \bmod r$

$\Rightarrow Tr^{-1}\bmod N=(T+mN)/r=(T+(T\bmod r)N) / r$

$定义 \phi_n(T,r)=Tr^{-n} \bmod N\; ,\phi_0=T$

$\Rightarrow \phi_n(T,r)=Tr^{-(n-1)}\bmod N \cdot r^{-1}\bmod N=\phi_{n-1}(T,r)\cdot r^{-1}\bmod N$

$\Rightarrow \phi_n(T,r)=(\phi_{n-1}+(\phi_{n-1}\bmod r)N) / r$

记 $T_n=\phi_{n}\bmod r=(\phi_{n-1}+T_{n-1}N)/r\bmod r=(\phi_{n-1}/r+T_{n-1}N/r)\bmod r$

记 $T_n^\prime=\phi_{n-1}/r\bmod r \;, T_n^{\prime\prime}=T_{n-1}N/r\bmod r$

记 $R_m^n=\frac{t}{r^{m}}\bmod r$

$\Rightarrow t=\phi_n=(\phi_{n-1}+T_{n-1}N) / r=(R_m,R_{m-1},...,R_0)_r$

$$
\Rightarrow R^n_m=\lfloor\frac{\phi_n}{r^m}\rfloor \bmod r
\\=\lfloor \frac{(\phi_{n-1}+(\phi_{n-1}\bmod r)N) / r}{r^m} \rfloor \bmod r 
\\ =\lfloor \frac{\phi_{n-1}+(\phi_{n-1}\bmod r)N}{r^{m+1}}\rfloor\bmod r
$$

求 $R0,...,Rn$

$R_n=$
