def theoryOverhead(method,*args):
    m=len(bin(args[0])[2:])
    if method=="binary_mul1" or method=="binary_mul2":
        addCount=m//2
        doubleCount=m
        return addCount,doubleCount
    elif method=="binary_mulNAF":
        addCount=m//3
        doubleCount=m
        return addCount,doubleCount
    elif method=="window_mulNAFw":
        addCount=2**(args[2]-2)-1+m//(args[2]+1)
        doubleCount=1+m        
        return addCount,doubleCount
    else:
        ex = Exception("找不到该方法！")
        raise ex

def overhead(func):
    def wrapper(*args,**kwargs):
        _,addCount,doubleCount=func(*args)
        addCount2,doubleCount2=theoryOverhead(func.__name__,*args)
        print("实测值：")
        print("A的次数:",addCount)
        print("D的次数:",doubleCount)
        print("理论值：")
        print("A的次数:",addCount2)
        print("D的次数:",doubleCount2)
        return func(*args)[0]
        # return "over"
    return wrapper