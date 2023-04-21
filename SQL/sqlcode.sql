# Write your MySQL query statement below
# add all and as asc between by desc distance distinct from group if in join like limit left not null on or outer order select set to where
/* 
 表：Products
 
 +-------------+---------+
 | Column Name | Type    |
 +-------------+---------+
 | product_id  | int     |
 | low_fats    | enum    |
 | recyclable  | enum    |
 +-------------+---------+
 product_id 是这个表的主键。
 low_fats 是枚举类型，取值为以下两种 ('Y', 'N')，其中 'Y' 表示该产品是低脂产品，'N' 表示不是低脂产品。
 recyclable 是枚举类型，取值为以下两种 ('Y', 'N')，其中 'Y' 表示该产品可回收，而 'N' 表示不可回收。
 
 
 
 写出 SQL 语句，查找既是低脂又是可回收的产品编号。
 
 返回结果 无顺序要求 。
 
 查询结果格式如下例所示：
 
 Products 表：
 +-------------+----------+------------+
 | product_id  | low_fats | recyclable |
 +-------------+----------+------------+
 | 0           | Y        | N          |
 | 1           | Y        | Y          |
 | 2           | N        | Y          |
 | 3           | Y        | Y          |
 | 4           | N        | N          |
 +-------------+----------+------------+
 Result 表：
 +-------------+
 | product_id  |
 +-------------+
 | 1           |
 | 3           |
 +-------------+
 只有产品 id 为 1 和 3 的产品，既是低脂又是可回收的产品。
 T1757
 */
select
  product_id
from
  Products
where
  low_fats = 'Y'
  and recyclable = 'Y'
  /* 
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | name        | varchar |
   | continent   | varchar |
   | area        | int     |
   | population  | int     |
   | gdp         | bigint  |
   +-------------+---------+
   name 是这张表的主键。
   这张表的每一行提供：国家名称、所属大陆、面积、人口和 GDP 值。
   如果一个国家满足下述两个条件之一，则认为该国是 大国 ：
   
   面积至少为 300 万平方公里（即，3000000 km2），或者
   人口至少为 2500 万（即 25000000）
   
   编写一个 SQL 查询以报告 大国 的国家名称、人口和面积。
   
   按 任意顺序 返回结果表。
   
   查询结果格式如下例所示。
   输入：
   World 表：
   +-------------+-----------+---------+------------+--------------+
   | name        | continent | area    | population | gdp          |
   +-------------+-----------+---------+------------+--------------+
   | Afghanistan | Asia      | 652230  | 25500100   | 20343000000  |
   | Albania     | Europe    | 28748   | 2831741    | 12960000000  |
   | Algeria     | Africa    | 2381741 | 37100000   | 188681000000 |
   | Andorra     | Europe    | 468     | 78115      | 3712000000   |
   | Angola      | Africa    | 1246700 | 20609294   | 100990000000 |
   +-------------+-----------+---------+------------+--------------+
   输出：
   +-------------+------------+---------+
   | name        | population | area    |
   +-------------+------------+---------+
   | Afghanistan | 25500100   | 652230  |
   | Algeria     | 37100000   | 2381741 |
   +-------------+------------+---------+
   T595
   */
  # Write your MySQL query statement below
  /*
   or 如果是单列和union没有区别 多列如本题 area population，如果选择了area，则需要扫描population
   union 可以解决上述多列的问题，分别使用去找 但是union会对结果排序去重
   union all不会去重
   查询用没用到索引都不确定怎么能比较二者效率？
   简单点说union相当于就是分步查询，最后将多个结果集做并集运算；
   or是在一条SQL语句中根据多条过滤条件，
   如果or两边都用到索引的话，or的右边索引会失效，无论左右是不是多列索引：
   之所以是这样，是因为InnoDB索引的底层实现其实是一颗B+树，
   刷力扣的人数据结构应该都还不错，想一想在一颗多路查找树中是怎么进行查询的就知道，
   加入索引根据（a, b, c, d）进行排序，那么显然要在a取等的时候才会根据b进行排序，
   也就是要取等后续的属性才能进行排序，or当然不是相等，所以or后面的索引才会失效；
   */
select
  t.name,
  t.population,
  t.area
from
  World t
where
  t.area >= 3000000
  or t.population >= 25000000
select
  t.name,
  t.population,
  t.area
from
  World t
where
  t.area >= 3000000
union
select
  t.name,
  t.population,
  t.area
from
  World t
where
  t.population >= 25000000
  /* 
   Views 表：
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | article_id    | int     |
   | author_id     | int     |
   | viewer_id     | int     |
   | view_date     | date    |
   +---------------+---------+
   此表无主键，因此可能会存在重复行。
   此表的每一行都表示某人在某天浏览了某位作者的某篇文章。
   请注意，同一人的 author_id 和 viewer_id 是相同的。
   请编写一条 SQL 查询以找出所有浏览过自己文章的作者，结果按照 id 升序排列。
   查询结果的格式如下所示：
   Views 表：
   +------------+-----------+-----------+------------+
   | article_id | author_id | viewer_id | view_date  |
   +------------+-----------+-----------+------------+
   | 1          | 3         | 5         | 2019-08-01 |
   | 1          | 3         | 6         | 2019-08-02 |
   | 2          | 7         | 7         | 2019-08-01 |
   | 2          | 7         | 6         | 2019-08-02 |
   | 4          | 7         | 1         | 2019-07-22 |
   | 3          | 4         | 4         | 2019-07-21 |
   | 3          | 4         | 4         | 2019-07-21 |
   +------------+-----------+-----------+------------+
   
   结果表：
   +------+
   | id   |
   +------+
   | 4    |
   | 7    |
   +------+
   T1148
   */
select
  distinct(t.author_id) as 'id'
from
  Views t
where
  t.author_id = t.viewer_id
order by
  t.author_id
  /* 
   表：Tweets
   
   +----------------+---------+
   | Column Name    | Type    |
   +----------------+---------+
   | tweet_id       | int     |
   | content        | varchar |
   +----------------+---------+
   tweet_id 是这个表的主键。
   这个表包含某社交媒体 App 中所有的推文。
   写一条 SQL 语句，查询所有无效推文的编号（ID）。当推文内容中的字符数严格大于 15 时，该推文是无效的。
   以任意顺序返回结果表。
   查询结果格式如下示例所示：
   Tweets 表：
   +----------+----------------------------------+
   | tweet_id | content                          |
   +----------+----------------------------------+
   | 1        | Vote for Biden                   |
   | 2        | Let us make America great again! |
   +----------+----------------------------------+
   
   结果表：
   +----------+
   | tweet_id |
   +----------+
   | 2        |
   +----------+
   推文 1 的长度 length = 14。该推文是有效的。
   推文 2 的长度 length = 32。该推文是无效的。
   T1683
   */
  /*
   1、char_length(str) 
   （1）计算单位：字符 
   （2）不管汉字还是数字或者是字母都算是一个字符 
   2、length(str) 
   （1）计算单位：字节 
   （2）utf8编码：一个汉字三个字节，一个数字或字母一个字节。 
   （3）gbk编码：一个汉字两个字节，一个数字或字母一个字节。 
   */
select
  t.tweet_id
from
  Tweets t
where
  char_length(t.content) > 15
  /* 
   Employees 表：
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | id            | int     |
   | name          | varchar |
   +---------------+---------+
   id 是这张表的主键。
   这张表的每一行分别代表了某公司其中一位员工的名字和 ID 。
   EmployeeUNI 表：
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | id            | int     |
   | unique_id     | int     |
   +---------------+---------+
   (id, unique_id) 是这张表的主键。
   这张表的每一行包含了该公司某位员工的 ID 和他的唯一标识码（unique ID）。
   写一段SQL查询来展示每位用户的 唯一标识码（unique ID ）；如果某位员工没有唯一标识码，使用 null 填充即可。
   你可以以 任意 顺序返回结果表。
   查询结果的格式如下例所示。
   示例 1：
   输入：
   Employees 表:
   +----+----------+
   | id | name     |
   +----+----------+
   | 1  | Alice    |
   | 7  | Bob      |
   | 11 | Meir     |
   | 90 | Winston  |
   | 3  | Jonathan |
   +----+----------+
   EmployeeUNI 表:
   +----+-----------+
   | id | unique_id |
   +----+-----------+
   | 3  | 1         |
   | 11 | 2         |
   | 90 | 3         |
   +----+-----------+
   输出：
   +-----------+----------+
   | unique_id | name     |
   +-----------+----------+
   | null      | Alice    |
   | null      | Bob      |
   | 2         | Meir     |
   | 3         | Winston  |
   | 1         | Jonathan |
   +-----------+----------+
   解释：
   Alice and Bob 没有唯一标识码, 因此我们使用 null 替代。
   Meir 的唯一标识码是 2 。
   Winston 的唯一标识码是 3 。
   Jonathan 唯一标识码是 1 。
   T1378
   */
  /*
   t1 left join t2 on xxx
   把t2并到t1上，如果满足on的条件则是t2的数据，不然就是null
   */
select
  b.unique_id,
  a.name
from
  Employees a
  left join EmployeeUNI b on a.id = b.id
  /* 
   销售表 Sales：
   +-------------+-------+
   | Column Name | Type  |
   +-------------+-------+
   | sale_id     | int   |
   | product_id  | int   |
   | year        | int   |
   | quantity    | int   |
   | price       | int   |
   +-------------+-------+
   (sale_id, year) 是销售表 Sales 的主键.
   product_id 是关联到产品表 Product 的外键.
   注意: price 表示每单位价格
   产品表 Product：
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | product_id   | int     |
   | product_name | varchar |
   +--------------+---------+
   product_id 是表的主键.
   写一条SQL 查询语句获取 Sales 表中所有产品对应的 产品名称 product_name 以及该产品的所有 售卖年份 year 和 价格 price 。
   查询结果中的顺序无特定要求。
   查询结果格式示例如下
   Sales 表：
   +---------+------------+------+----------+-------+
   | sale_id | product_id | year | quantity | price |
   +---------+------------+------+----------+-------+ 
   | 1       | 100        | 2008 | 10       | 5000  |
   | 2       | 100        | 2009 | 12       | 5000  |
   | 7       | 200        | 2011 | 15       | 9000  |
   +---------+------------+------+----------+-------+
   Product 表：
   +------------+--------------+
   | product_id | product_name |
   +------------+--------------+
   | 100        | Nokia        |
   | 200        | Apple        |
   | 300        | Samsung      |
   +------------+--------------+
   Result 表：
   +--------------+-------+-------+
   | product_name | year  | price |
   +--------------+-------+-------+
   | Nokia        | 2008  | 5000  |
   | Nokia        | 2009  | 5000  |
   | Apple        | 2011  | 9000  |
   +--------------+-------+-------+
   T1068
   */
select
  b.product_name,
  a.year,
  a.price
from
  Sales a,
  Product b
where
  a.product_id = b.product_id
  /* 
   表：Visits
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | visit_id    | int     |
   | customer_id | int     |
   +-------------+---------+
   visit_id 是该表的主键。
   该表包含有关光临过购物中心的顾客的信息。
   
   
   
   表：Transactions
   
   +----------------+---------+
   | Column Name    | Type    |
   +----------------+---------+
   | transaction_id | int     |
   | visit_id       | int     |
   | amount         | int     |
   +----------------+---------+
   transaction_id 是此表的主键。
   此表包含 visit_id 期间进行的交易的信息。
   
   
   
   有一些顾客可能光顾了购物中心但没有进行交易。请你编写一个 SQL 查询，来查找这些顾客的 ID ，以及他们只光顾不交易的次数。
   
   返回以 任何顺序 排序的结果表。
   
   查询结果格式如下例所示。
   
   
   
   示例 1：
   
   输入:
   Visits
   +----------+-------------+
   | visit_id | customer_id |
   +----------+-------------+
   | 1        | 23          |
   | 2        | 9           |
   | 4        | 30          |
   | 5        | 54          |
   | 6        | 96          |
   | 7        | 54          |
   | 8        | 54          |
   +----------+-------------+
   Transactions
   +----------------+----------+--------+
   | transaction_id | visit_id | amount |
   +----------------+----------+--------+
   | 2              | 5        | 310    |
   | 3              | 5        | 300    |
   | 9              | 5        | 200    |
   | 12             | 1        | 910    |
   | 13             | 2        | 970    |
   +----------------+----------+--------+
   输出:
   +-------------+----------------+
   | customer_id | count_no_trans |
   +-------------+----------------+
   | 54          | 2              |
   | 30          | 1              |
   | 96          | 1              |
   +-------------+----------------+
   解释:
   ID = 23 的顾客曾经逛过一次购物中心，并在 ID = 12 的访问期间进行了一笔交易。
   ID = 9 的顾客曾经逛过一次购物中心，并在 ID = 13 的访问期间进行了一笔交易。
   ID = 30 的顾客曾经去过购物中心，并且没有进行任何交易。
   ID = 54 的顾客三度造访了购物中心。在 2 次访问中，他们没有进行任何交易，在 1 次访问中，他们进行了 3 次交易。
   ID = 96 的顾客曾经去过购物中心，并且没有进行任何交易。
   如我们所见，ID 为 30 和 96 的顾客一次没有进行任何交易就去了购物中心。顾客 54 也两次访问了购物中心并且没有进行任何交易。
   T1581
   */
  /* 
   group by 分组查询
   */
select
  customer_id,
  count(visit_id) as count_no_trans
from
  Visits
where
  visit_id not in(
    select
      visit_id
    from
      Transactions
  )
group by
  customer_id