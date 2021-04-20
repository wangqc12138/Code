/*
实现 strStr() 函数。
给你两个字符串 haystack 和 needle ，请你在 haystack 字符串中找出 needle 字符串出现的第一个位置（下标从 0 开始）。如果不存在，则返回  -1 。
*/
// KMP算法
class Solution {
public:
    int strStr(string haystack, string needle) {

    }
};
// BM算法
class Solution {
public:
    int strStr(string haystack, string needle) {
    	int m=haystack.size(),n=needle.size(),i=0,j,b_m,g_m;
    	//坏字符表
    	for(;i<n;i++){
    		bc[needle[i]]=i;
    	}
    	i=0;
    	while(i<=m-n){
    		j=n-1;
    		while(haystack[i+j]==needle[j]){
    			j--;
    		}
    		if(j<0){
    			return i;
    		}
    		char badC=haystack[i+j];
    		if(bc.count(badC)){
    			b_m=i+j-bc[badC];
    		}else{
    			b_m=i+j+1;
    		}
    		if(j<n-1){
    			
    		}
    		i=max(b_m,g_m);
    	}
    }
    int goodSuffix(){
    	
    }

private:
	map<char,int> bc;
	vector<int> goodsuffix;
};
// Sunday算法
class Solution {
public:
    int strStr(string haystack, string needle) {

    }
};
class Solution {
    public int strStr(String haystack, String needle) {
        char[] hay = haystack.toCharArray();
        char[] need = needle.toCharArray();
        int haylen = haystack.length();
        int needlen = need.length;
        return bm(hay,haylen,need,needlen);
    }
    //用来求坏字符情况下移动位数
    private static void badChar(char[] b, int m, int[] bc) {
        //初始化
        for (int i = 0; i < 256; ++i) {
            bc[i] = -1;
        }
        //m 代表模式串的长度，如果有两个 a,则后面那个会覆盖前面那个
        for (int i = 0; i < m; ++i) {
            int ascii = (int)b[i];
            bc[ascii] = i;//下标
        }
    }
    //用来求好后缀条件下的移动位数
    private static void goodSuffix (char[] b, int m, int[] suffix,boolean[] prefix) {
        //初始化
        for (int i = 0; i < m; ++i) {
            suffix[i] = -1;
            prefix[i] = false;
        }
        for (int i = 0; i < m - 1; ++i) {
            int j = i;
            int k = 0;
            while (j >= 0 && b[j] == b[m-1-k]) {
                --j;
                ++k;
                suffix[k] = j + 1;
            }
            if (j == -1) prefix[k] = true;
        }
    }
    public static int bm (char[] a, int n, char[] b, int m) {

        int[] bc = new int[256];//创建一个数组用来保存最右边字符的下标
        badChar(b,m,bc);
        //用来保存各种长度好后缀的最右位置的数组
        int[] suffix_index = new int[m];
        //判断是否是头部，如果是头部则true
        boolean[] ispre = new boolean[m];
        goodSuffix(b,m,suffix_index,ispre);
        int i = 0;//第一个匹配字符
        //注意结束条件
        while (i <= n-m) {
            int j;
            //从后往前匹配，匹配失败，找到坏字符
            for (j = m - 1; j >= 0; --j) {
                if (a[i+j] != b[j]) break;
            }
            //模式串遍历完毕，匹配成功
            if (j < 0) {
                return i;
            }
            //下面为匹配失败时，如何处理
            //求出坏字符规则下移动的位数，就是我们坏字符下标减最右边的下标
            int x = j - bc[(int)a[i+j]];
            int y = 0;
            //好后缀情况，求出好后缀情况下的移动位数,如果不含有好后缀的话，则按照坏字符来
            if (y < m-1 && m - 1 - j > 0) {
                y = move(j, m, suffix_index,ispre);
            }
            //移动
            i = i + Math.max(x,y);

        }
        return -1;
    }
    // j代表坏字符的下标
    private static int move (int j, int m, int[] suffix_index, boolean[] ispre) {
        //好后缀长度
        int k = m - 1 - j;
        //如果含有长度为 k 的好后缀，返回移动位数，
        if (suffix_index[k] != -1) return j - suffix_index[k] + 1;
        //找头部为好后缀子串的最大长度，从长度最大的子串开始
        for (int r = j + 2; r <= m-1; ++r) {
            //如果是头部
            if (ispre[m-r] == true) {
                return r;
            }
        }
        //如果没有发现好后缀匹配的串，或者头部为好后缀子串，则移动到 m 位，也就是匹配串的长度
        return m;
    }
}
