class Solution:
    def maximumXorProduct(self, a: int, b: int, n: int) -> int:
        c,d=a,b
        res = a*b
        for i in range(n):
            c,d=a^(1<<i),b^(1<<i)
            if c*d > a*b:
                a,b=c,d
        return a*b%1000000007