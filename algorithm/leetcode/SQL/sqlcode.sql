# Write your MySQL query statement below #
add all
  and as asc between by desc distance distinct
from group if in
  join like
limit left not null on
  or outer order
select
set to
where
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
select product_id
from Products
where low_fats = 'Y'
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
select t.name,
  t.population,
  t.area
from World t
where t.area >= 3000000
  or t.population >= 25000000
select t.name,
  t.population,
  t.area
from World t
where t.area >= 3000000
union
select t.name,
  t.population,
  t.area
from World t
where t.population >= 25000000
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
select distinct(t.author_id) as 'id'
from Views t
where t.author_id = t.viewer_id
order by t.author_id
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
select t.tweet_id
from Tweets t
where char_length(t.content) > 15
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
select b.unique_id,
  a.name
from Employees a
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
select b.product_name,
  a.year,
  a.price
from Sales a,
  Product b
where a.product_id = b.product_id
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
select customer_id,
  count(visit_id) as count_no_trans
from Visits
where visit_id not in(
    select visit_id
    from Transactions
  )
group by customer_id
  /* 
   表： Weather
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | id            | int     |
   | recordDate    | date    |
   | temperature   | int     |
   +---------------+---------+
   id 是这个表的主键
   该表包含特定日期的温度信息
   编写一个 SQL 查询，来查找与之前（昨天的）日期相比温度更高的所有日期的 id 。
   返回结果 不要求顺序 。 
   查询结果格式如下例。
   示例 1：
   输入：
   Weather 表：
   +----+------------+-------------+
   | id | recordDate | Temperature |
   +----+------------+-------------+
   | 1  | 2015-01-01 | 10          |
   | 2  | 2015-01-02 | 25          |
   | 3  | 2015-01-03 | 20          |
   | 4  | 2015-01-04 | 30          |
   +----+------------+-------------+
   输出：
   +----+
   | id |
   +----+
   | 2  |
   | 4  |
   +----+
   解释：
   2015-01-02 的温度比前一天高（10 -> 25）
   2015-01-04 的温度比前一天高（20 -> 30）
   T197
   */
  /*
   datediff 计算两个date变量之间的天数差 
   timestampdiff 计算两个date变量之间的时间差，可以是天，小时等 小的放前面，大的放后面
   inner join 内连接 笛卡尔积
   */
select a.id
from Weather a,
  Weather b
where a.Temperature > b.Temperature
  and datediff(a.recordDate, b.recordDate) = 1
  and timestampdiff(day, b.recordDate, a.recordDate) = 1
select b.Id
from weather a
  inner join weather b on DATEDIFF(b.recordDate, a.recordDate) = 1
  and b.Temperature > a.Temperature;
/* 
 表: Activity
 
 +----------------+---------+
 | Column Name    | Type    |
 +----------------+---------+
 | machine_id     | int     |
 | process_id     | int     |
 | activity_type  | enum    |
 | timestamp      | float   |
 +----------------+---------+
 该表展示了一家工厂网站的用户活动.
 (machine_id, process_id, activity_type) 是当前表的主键.
 machine_id 是一台机器的ID号.
 process_id 是运行在各机器上的进程ID号.
 activity_type 是枚举类型 ('start', 'end').
 timestamp 是浮点类型,代表当前时间(以秒为单位).
 'start' 代表该进程在这台机器上的开始运行时间戳 , 'end' 代表该进程在这台机器上的终止运行时间戳.
 同一台机器，同一个进程都有一对开始时间戳和结束时间戳，而且开始时间戳永远在结束时间戳前面.
 
 
 
 现在有一个工厂网站由几台机器运行，每台机器上运行着相同数量的进程. 请写出一条SQL计算每台机器各自完成一个进程任务的平均耗时.
 
 完成一个进程任务的时间指进程的'end' 时间戳 减去 'start' 时间戳. 平均耗时通过计算每台机器上所有进程任务的总耗费时间除以机器上的总进程数量获得.
 
 结果表必须包含machine_id（机器ID） 和对应的 average time（平均耗时） 别名 processing_time, 且四舍五入保留3位小数.
 
 以 任意顺序 返回表。
 
 具体参考例子如下。
 
 
 
 示例 1:
 
 输入：
 Activity table:
 +------------+------------+---------------+-----------+
 | machine_id | process_id | activity_type | timestamp |
 +------------+------------+---------------+-----------+
 | 0          | 0          | start         | 0.712     |
 | 0          | 0          | end           | 1.520     |
 | 0          | 1          | start         | 3.140     |
 | 0          | 1          | end           | 4.120     |
 | 1          | 0          | start         | 0.550     |
 | 1          | 0          | end           | 1.550     |
 | 1          | 1          | start         | 0.430     |
 | 1          | 1          | end           | 1.420     |
 | 2          | 0          | start         | 4.100     |
 | 2          | 0          | end           | 4.512     |
 | 2          | 1          | start         | 2.500     |
 | 2          | 1          | end           | 5.000     |
 +------------+------------+---------------+-----------+
 输出：
 +------------+-----------------+
 | machine_id | processing_time |
 +------------+-----------------+
 | 0          | 0.894           |
 | 1          | 0.995           |
 | 2          | 1.456           |
 +------------+-----------------+
 解释：
 一共有3台机器,每台机器运行着两个进程.
 机器 0 的平均耗时: ((1.520 - 0.712) + (4.120 - 3.140)) / 2 = 0.894
 机器 1 的平均耗时: ((1.550 - 0.550) + (1.420 - 0.430)) / 2 = 0.995
 机器 2 的平均耗时: ((4.512 - 4.100) + (5.000 - 2.500)) / 2 = 1.456
 T1661
 */
/*
 round 取小数点后几位
 avg 求列的平均值
 if 判断
 *2 四条记录是除了4，但是按题意只需要除2
 */
select machine_id,
  round(
    avg(
      if(activity_type = 'start', - timestamp, timestamp)
    ) * 2,
    3
  ) as processing_time
from Activity
group by machine_id
  /* 
   选出所有 bonus < 1000 的员工的 name 及其 bonus。
   Employee 表单
   
   +-------+--------+-----------+--------+
   | empId |  name  | supervisor| salary |
   +-------+--------+-----------+--------+
   |   1   | John   |  3        | 1000   |
   |   2   | Dan    |  3        | 2000   |
   |   3   | Brad   |  null     | 4000   |
   |   4   | Thomas |  3        | 4000   |
   +-------+--------+-----------+--------+
   empId 是这张表单的主关键字
   
   Bonus 表单
   
   +-------+-------+
   | empId | bonus |
   +-------+-------+
   | 2     | 500   |
   | 4     | 2000  |
   +-------+-------+
   empId 是这张表单的主关键字
   
   输出示例：
   
   +-------+-------+
   | name  | bonus |
   +-------+-------+
   | John  | null  |
   | Dan   | 500   |
   | Brad  | null  |
   +-------+-------+
   T577
   */
select a.name,
  b.bonus
from Employee a
  left join Bonus b on a.empId = b.empId
where isnull(b.empId)
  /*b.empId is null */
  or b.bonus < 1000
  /* 
   学生表: Students
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | student_id    | int     |
   | student_name  | varchar |
   +---------------+---------+
   主键为 student_id（学生ID），该表内的每一行都记录有学校一名学生的信息。
   科目表: Subjects
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | subject_name | varchar |
   +--------------+---------+
   主键为 subject_name（科目名称），每一行记录学校的一门科目名称。
   考试表: Examinations
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | student_id   | int     |
   | subject_name | varchar |
   +--------------+---------+
   这张表压根没有主键，可能会有重复行。
   学生表里的一个学生修读科目表里的每一门科目，而这张考试表的每一行记录就表示学生表里的某个学生参加了一次科目表里某门科目的测试。
   要求写一段 SQL 语句，查询出每个学生参加每一门科目测试的次数，结果按 student_id 和 subject_name 排序。
   查询结构格式如下所示：
   Students table:
   +------------+--------------+
   | student_id | student_name |
   +------------+--------------+
   | 1          | Alice        |
   | 2          | Bob          |
   | 13         | John         |
   | 6          | Alex         |
   +------------+--------------+
   Subjects table:
   +--------------+
   | subject_name |
   +--------------+
   | Math         |
   | Physics      |
   | Programming  |
   +--------------+
   Examinations table:
   +------------+--------------+
   | student_id | subject_name |
   +------------+--------------+
   | 1          | Math         |
   | 1          | Physics      |
   | 1          | Programming  |
   | 2          | Programming  |
   | 1          | Physics      |
   | 1          | Math         |
   | 13         | Math         |
   | 13         | Programming  |
   | 13         | Physics      |
   | 2          | Math         |
   | 1          | Math         |
   +------------+--------------+
   Result table:
   +------------+--------------+--------------+----------------+
   | student_id | student_name | subject_name | attended_exams |
   +------------+--------------+--------------+----------------+
   | 1          | Alice        | Math         | 3              |
   | 1          | Alice        | Physics      | 2              |
   | 1          | Alice        | Programming  | 1              |
   | 2          | Bob          | Math         | 1              |
   | 2          | Bob          | Physics      | 0              |
   | 2          | Bob          | Programming  | 1              |
   | 6          | Alex         | Math         | 0              |
   | 6          | Alex         | Physics      | 0              |
   | 6          | Alex         | Programming  | 0              |
   | 13         | John         | Math         | 1              |
   | 13         | John         | Physics      | 1              |
   | 13         | John         | Programming  | 1              |
   +------------+--------------+--------------+----------------+
   结果表需包含所有学生和所有科目（即便测试次数为0）：
   Alice 参加了 3 次数学测试, 2 次物理测试，以及 1 次编程测试；
   Bob 参加了 1 次数学测试, 1 次编程测试，没有参加物理测试；
   Alex 啥测试都没参加；
   John  参加了数学、物理、编程测试各 1 次。
   T1280
   */
select a.student_id,
  a.student_name,
  b.subject_name,
  count(c.subject_name) as attended_exams
from (
    Students a
    inner join Subjects b
  )
  left join Examinations c on a.student_id = c.student_id
  and b.subject_name = c.subject_name
group by a.student_name,
  b.subject_name
order by a.student_id,
  a.student_name
  /* 
   表: Employee
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | id          | int     |
   | name        | varchar |
   | department  | varchar |
   | managerId   | int     |
   +-------------+---------+
   Id是该表的主键列。
   该表的每一行都表示雇员的名字、他们的部门和他们的经理的id。
   如果managerId为空，则该员工没有经理。
   没有员工会成为自己的管理者。
   
   编写一个SQL查询，查询至少有5名直接下属的经理 。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下所示。
   
   
   
   示例 1:
   
   输入: 
   Employee 表:
   +-----+-------+------------+-----------+
   | id  | name  | department | managerId |
   +-----+-------+------------+-----------+
   | 101 | John  | A          | None      |
   | 102 | Dan   | A          | 101       |
   | 103 | James | A          | 101       |
   | 104 | Amy   | A          | 101       |
   | 105 | Anne  | A          | 101       |
   | 106 | Ron   | B          | 101       |
   +-----+-------+------------+-----------+
   输出: 
   +------+
   | name |
   +------+
   | John |
   +------+
   T570
   */
select name
from Employee
where id in(
    select managerId
    from Employee
    group by managerId
    having count(managerId) >= 5
  )
  /* 
   表: Signups
   
   +----------------+----------+
   | Column Name    | Type     |
   +----------------+----------+
   | user_id        | int      |
   | time_stamp     | datetime |
   +----------------+----------+
   User_id是该表的主键。
   每一行都包含ID为user_id的用户的注册时间信息。
   
   
   
   表: Confirmations
   
   +----------------+----------+
   | Column Name    | Type     |
   +----------------+----------+
   | user_id        | int      |
   | time_stamp     | datetime |
   | action         | ENUM     |
   +----------------+----------+
   (user_id, time_stamp)是该表的主键。
   user_id是一个引用到注册表的外键。
   action是类型为('confirmed'， 'timeout')的ENUM
   该表的每一行都表示ID为user_id的用户在time_stamp请求了一条确认消息，该确认消息要么被确认('confirmed')，要么被过期('timeout')。
   用户的 确认率 是 'confirmed' 消息的数量除以请求的确认消息的总数。没有请求任何确认消息的用户的确认率为 0 。确认率四舍五入到 小数点后两位 。
   
   编写一个SQL查询来查找每个用户的 确认率 。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下所示。
   
   示例1:
   
   输入：
   Signups 表:
   +---------+---------------------+
   | user_id | time_stamp          |
   +---------+---------------------+
   | 3       | 2020-03-21 10:16:13 |
   | 7       | 2020-01-04 13:57:59 |
   | 2       | 2020-07-29 23:09:44 |
   | 6       | 2020-12-09 10:39:37 |
   +---------+---------------------+
   Confirmations 表:
   +---------+---------------------+-----------+
   | user_id | time_stamp          | action    |
   +---------+---------------------+-----------+
   | 3       | 2021-01-06 03:30:46 | timeout   |
   | 3       | 2021-07-14 14:00:00 | timeout   |
   | 7       | 2021-06-12 11:57:29 | confirmed |
   | 7       | 2021-06-13 12:58:28 | confirmed |
   | 7       | 2021-06-14 13:59:27 | confirmed |
   | 2       | 2021-01-22 00:00:00 | confirmed |
   | 2       | 2021-02-28 23:59:59 | timeout   |
   +---------+---------------------+-----------+
   输出: 
   +---------+-------------------+
   | user_id | confirmation_rate |
   +---------+-------------------+
   | 6       | 0.00              |
   | 3       | 0.00              |
   | 7       | 1.00              |
   | 2       | 0.50              |
   +---------+-------------------+
   解释:
   用户 6 没有请求任何确认消息。确认率为 0。
   用户 3 进行了 2 次请求，都超时了。确认率为 0。
   用户 7 提出了 3 个请求，所有请求都得到了确认。确认率为 1。
   用户 2 做了 2 个请求，其中一个被确认，另一个超时。确认率为 1 / 2 = 0.5。
   
   T1934
   */
select a.user_id,
  round(
    if(
      count(b.action) = 0,
      0,
      sum(b.action = 'confirmed') / count(b.action)
    ),
    2
  ) as confirmation_rate
from Signups a
  left join Confirmations b on a.user_id = b.user_id
group by a.user_id
select a.user_id,
  round(
    /* 如果不是null，返回第一个参数，否则返回第二个参数 */
    ifnull(avg(b.action = 'confirmed'), 0),
    2
  ) as confirmation_rate
from Signups a
  left join Confirmations b on a.user_id = b.user_id
group by a.user_id
  /* 
   某城市开了一家新的电影院，吸引了很多人过来看电影。该电影院特别注意用户体验，专门有个 LED显示板做电影推荐，上面公布着影评和相关电影描述。
   
   作为该电影院的信息部主管，您需要编写一个 SQL查询，找出所有影片描述为非 boring (不无聊) 的并且 id 为奇数 的影片，结果请按等级 rating 排列。
   
   
   
   例如，下表 cinema:
   
   +---------+-----------+--------------+-----------+
   |   id    | movie     |  description |  rating   |
   +---------+-----------+--------------+-----------+
   |   1     | War       |   great 3D   |   8.9     |
   |   2     | Science   |   fiction    |   8.5     |
   |   3     | irish     |   boring     |   6.2     |
   |   4     | Ice song  |   Fantacy    |   8.6     |
   |   5     | House card|   Interesting|   9.1     |
   +---------+-----------+--------------+-----------+
   
   对于上面的例子，则正确的输出是为：
   
   +---------+-----------+--------------+-----------+
   |   id    | movie     |  description |  rating   |
   +---------+-----------+--------------+-----------+
   |   5     | House card|   Interesting|   9.1     |
   |   1     | War       |   great 3D   |   8.9     |
   +---------+-----------+--------------+-----------+
   T620
   */
select *
from cinema
where description != 'boring'
  and id % 2 = 1
order by rating desc
  /* 
   Table: Prices
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | product_id    | int     |
   | start_date    | date    |
   | end_date      | date    |
   | price         | int     |
   +---------------+---------+
   (product_id，start_date，end_date) 是 Prices 表的主键。
   Prices 表的每一行表示的是某个产品在一段时期内的价格。
   每个产品的对应时间段是不会重叠的，这也意味着同一个产品的价格时段不会出现交叉。
   Table: UnitsSold
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | product_id    | int     |
   | purchase_date | date    |
   | units         | int     |
   +---------------+---------+
   UnitsSold 表没有主键，它可能包含重复项。
   UnitsSold 表的每一行表示的是每种产品的出售日期，单位和产品 id。
   编写SQL查询以查找每种产品的平均售价。
   average_price 应该四舍五入到小数点后两位。
   查询结果格式如下例所示：
   Prices table:
   +------------+------------+------------+--------+
   | product_id | start_date | end_date   | price  |
   +------------+------------+------------+--------+
   | 1          | 2019-02-17 | 2019-02-28 | 5      |
   | 1          | 2019-03-01 | 2019-03-22 | 20     |
   | 2          | 2019-02-01 | 2019-02-20 | 15     |
   | 2          | 2019-02-21 | 2019-03-31 | 30     |
   +------------+------------+------------+--------+
   UnitsSold table:
   +------------+---------------+-------+
   | product_id | purchase_date | units |
   +------------+---------------+-------+
   | 1          | 2019-02-25    | 100   |
   | 1          | 2019-03-01    | 15    |
   | 2          | 2019-02-10    | 200   |
   | 2          | 2019-03-22    | 30    |
   +------------+---------------+-------+
   
   Result table:
   +------------+---------------+
   | product_id | average_price |
   +------------+---------------+
   | 1          | 6.96          |
   | 2          | 16.96         |
   +------------+---------------+
   平均售价 = 产品总价 / 销售的产品数量。
   产品 1 的平均售价 = ((100 * 5)+(15 * 20) )/ 115 = 6.96
   产品 2 的平均售价 = ((200 * 15)+(30 * 30) )/ 230 = 16.96
   T1251
   */
select *
from Prices a
  left join UnitsSold b on a.product_id = b.product_id
  and b.purchase_date >= a.start_date
  and b.purchase_date <= a.end_date
  /* 
   | product_id | start_date | end_date   | price | product_id | purchase_date | units |
   | ---------- | ---------- | ---------- | ----- | ---------- | ------------- | ----- |
   | 1          | 2019-02-17 | 2019-02-28 | 5     | 1          | 2019-02-25    | 100   |
   | 1          | 2019-03-01 | 2019-03-22 | 20    | 1          | 2019-03-01    | 15    |
   | 2          | 2019-02-01 | 2019-02-20 | 15    | 2          | 2019-02-10    | 200   |
   | 2          | 2019-02-21 | 2019-03-31 | 30    | 2          | 2019-03-22    | 30    | 
   */
select a.product_id,
  round(sum(a.price * b.units) / sum(b.units), 2) as average_price
from Prices a
  left join UnitsSold b on a.product_id = b.product_id
  and b.purchase_date >= a.start_date
  and b.purchase_date <= a.end_date
group by a.product_id
  /* 
   项目表 Project： 
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | project_id  | int     |
   | employee_id | int     |
   +-------------+---------+
   主键为 (project_id, employee_id)。
   employee_id 是员工表 Employee 表的外键。
   
   员工表 Employee：
   
   +------------------+---------+
   | Column Name      | Type    |
   +------------------+---------+
   | employee_id      | int     |
   | name             | varchar |
   | experience_years | int     |
   +------------------+---------+
   主键是 employee_id。
   
   
   
   请写一个 SQL 语句，查询每一个项目中员工的 平均 工作年限，精确到小数点后两位。
   
   查询结果的格式如下：
   
   Project 表：
   +-------------+-------------+
   | project_id  | employee_id |
   +-------------+-------------+
   | 1           | 1           |
   | 1           | 2           |
   | 1           | 3           |
   | 2           | 1           |
   | 2           | 4           |
   +-------------+-------------+
   
   Employee 表：
   +-------------+--------+------------------+
   | employee_id | name   | experience_years |
   +-------------+--------+------------------+
   | 1           | Khaled | 3                |
   | 2           | Ali    | 2                |
   | 3           | John   | 1                |
   | 4           | Doe    | 2                |
   +-------------+--------+------------------+
   
   Result 表：
   +-------------+---------------+
   | project_id  | average_years |
   +-------------+---------------+
   | 1           | 2.00          |
   | 2           | 2.50          |
   +-------------+---------------+
   第一个项目中，员工的平均工作年限是 (3 + 2 + 1) / 3 = 2.00；第二个项目中，员工的平均工作年限是 (3 + 2) / 2 = 2.50
   T1075
   */
select *
from Project a
  left join Employee b on a.employee_id = b.employee_id
  /* 
   | project_id | employee_id | employee_id | name   | experience_years |
   | ---------- | ----------- | ----------- | ------ | ---------------- |
   | 1          | 1           | 1           | Khaled | 3                |
   | 1          | 2           | 2           | Ali    | 2                |
   | 1          | 3           | 3           | John   | 1                |
   | 2          | 1           | 1           | Khaled | 3                |
   | 2          | 4           | 4           | Doe    | 2                |
   */
select a.project_id,
  round(avg(experience_years), 2) as average_years
from Project a
  left join Employee b on a.employee_id = b.employee_id
group by project_id
  /* 
   用户表： Users
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | user_id     | int     |
   | user_name   | varchar |
   +-------------+---------+
   user_id 是该表的主键。
   该表中的每行包括用户 ID 和用户名。
   
   注册表： Register
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | contest_id  | int     |
   | user_id     | int     |
   +-------------+---------+
   (contest_id, user_id) 是该表的主键。
   该表中的每行包含用户的 ID 和他们注册的赛事。
   
   
   
   写一条 SQL 语句，查询各赛事的用户注册百分率，保留两位小数。
   
   返回的结果表按 percentage 的 降序 排序，若相同则按 contest_id 的 升序 排序。
   
   查询结果如下示例所示。
   
   
   
   示例 1：
   
   输入：
   Users 表：
   +---------+-----------+
   | user_id | user_name |
   +---------+-----------+
   | 6       | Alice     |
   | 2       | Bob       |
   | 7       | Alex      |
   +---------+-----------+
   
   Register 表：
   +------------+---------+
   | contest_id | user_id |
   +------------+---------+
   | 215        | 6       |
   | 209        | 2       |
   | 208        | 2       |
   | 210        | 6       |
   | 208        | 6       |
   | 209        | 7       |
   | 209        | 6       |
   | 215        | 7       |
   | 208        | 7       |
   | 210        | 2       |
   | 207        | 2       |
   | 210        | 7       |
   +------------+---------+
   输出：
   +------------+------------+
   | contest_id | percentage |
   +------------+------------+
   | 208        | 100.0      |
   | 209        | 100.0      |
   | 210        | 100.0      |
   | 215        | 66.67      |
   | 207        | 33.33      |
   +------------+------------+
   解释：
   所有用户都注册了 208、209 和 210 赛事，因此这些赛事的注册率为 100% ，我们按 contest_id 的降序排序加入结果表中。
   Alice 和 Alex 注册了 215 赛事，注册率为 ((2/3) * 100) = 66.67%
   Bob 注册了 207 赛事，注册率为 ((1/3) * 100) = 33.33%
   
   T1633
   */
select contest_id,
  round(
    count(user_id) /(
      select count(*)
      from Users
    ) * 100,
    2
  ) as percentage
from Register
group by contest_id
order by percentage desc,
  contest_id asc
  /* 
   查询表 Queries： 
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | query_name  | varchar |
   | result      | varchar |
   | position    | int     |
   | rating      | int     |
   +-------------+---------+
   此表没有主键，并可能有重复的行。
   此表包含了一些从数据库中收集的查询信息。
   “位置”（position）列的值为 1 到 500 。
   “评分”（rating）列的值为 1 到 5 。评分小于 3 的查询被定义为质量很差的查询。
   
   将查询结果的质量 quality 定义为：
   
   各查询结果的评分与其位置之间比率的平均值。
   
   将劣质查询百分比 poor_query_percentage 为：
   
   评分小于 3 的查询结果占全部查询结果的百分比。
   
   编写一组 SQL 来查找每次查询的名称(query_name)、质量(quality) 和 劣质查询百分比(poor_query_percentage)。
   
   质量(quality) 和劣质查询百分比(poor_query_percentage) 都应四舍五入到小数点后两位。
   
   查询结果格式如下所示：
   
   Queries table:
   +------------+-------------------+----------+--------+
   | query_name | result            | position | rating |
   +------------+-------------------+----------+--------+
   | Dog        | Golden Retriever  | 1        | 5      |
   | Dog        | German Shepherd   | 2        | 5      |
   | Dog        | Mule              | 200      | 1      |
   | Cat        | Shirazi           | 5        | 2      |
   | Cat        | Siamese           | 3        | 3      |
   | Cat        | Sphynx            | 7        | 4      |
   +------------+-------------------+----------+--------+
   
   Result table:
   +------------+---------+-----------------------+
   | query_name | quality | poor_query_percentage |
   +------------+---------+-----------------------+
   | Dog        | 2.50    | 33.33                 |
   | Cat        | 0.66    | 33.33                 |
   +------------+---------+-----------------------+
   
   Dog 查询结果的质量为 ((5 / 1) + (5 / 2) + (1 / 200)) / 3 = 2.50
   Dog 查询结果的劣质查询百分比为 (1 / 3) * 100 = 33.33
   
   Cat 查询结果的质量为 ((2 / 5) + (3 / 3) + (4 / 7)) / 3 = 0.66
   Cat 查询结果的劣质查询百分比为 (1 / 3) * 100 = 33.33
   
   
   */
select query_name,
  round(avg(rating / position), 2) as quality,
  round(sum(rating < 3) / count(rating) * 100, 2) as poor_query_percentage
from Queries
group by query_name
  /* 
   Table: Transactions
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | id            | int     |
   | country       | varchar |
   | state         | enum    |
   | amount        | int     |
   | trans_date    | date    |
   +---------------+---------+
   id 是这个表的主键。
   该表包含有关传入事务的信息。
   state 列类型为 “[”批准“，”拒绝“] 之一。
   
   编写一个 sql 查询来查找每个月和每个国家/地区的事务数及其总金额、已批准的事务数及其总金额。
   以 任意顺序 返回结果表。
   查询结果格式如下所示。
   示例 1:
   输入：
   Transactions table:
   +------+---------+----------+--------+------------+
   | id   | country | state    | amount | trans_date |
   +------+---------+----------+--------+------------+
   | 121  | US      | approved | 1000   | 2018-12-18 |
   | 122  | US      | declined | 2000   | 2018-12-19 |
   | 123  | US      | approved | 2000   | 2019-01-01 |
   | 124  | DE      | approved | 2000   | 2019-01-07 |
   +------+---------+----------+--------+------------+
   输出：
   +----------+---------+-------------+----------------+--------------------+-----------------------+
   | month    | country | trans_count | approved_count | trans_total_amount | approved_total_amount |
   +----------+---------+-------------+----------------+--------------------+-----------------------+
   | 2018-12  | US      | 2           | 1              | 3000               | 1000                  |
   | 2019-01  | US      | 1           | 1              | 2000               | 2000                  |
   | 2019-01  | DE      | 1           | 1              | 2000               | 2000                  |
   +----------+---------+-------------+----------------+--------------------+-----------------------+
   T1193
   */
select date_format(trans_date, '%Y-%m') as month,
  country,
  count(date_format(trans_date, '%Y-%m')) as trans_count,
  sum(state = 'approved') as approved_count,
  sum(amount) as trans_total_amount,
  sum(if(state = 'approved', amount, 0)) as approved_total_amount
from Transactions
group by country,
  date_format(trans_date, '%Y-%m')
  /* 
   配送表: Delivery
   
   +-----------------------------+---------+
   | Column Name                 | Type    |
   +-----------------------------+---------+
   | delivery_id                 | int     |
   | customer_id                 | int     |
   | order_date                  | date    |
   | customer_pref_delivery_date | date    |
   +-----------------------------+---------+
   delivery_id 是表的主键。
   该表保存着顾客的食物配送信息，顾客在某个日期下了订单，并指定了一个期望的配送日期（和下单日期相同或者在那之后）。
   
   
   
   如果顾客期望的配送日期和下单日期相同，则该订单称为 「即时订单」，否则称为「计划订单」。
   
   「首次订单」是顾客最早创建的订单。我们保证一个顾客只会有一个「首次订单」。
   
   写一条 SQL 查询语句获取即时订单在所有用户的首次订单中的比例。保留两位小数。
   查询结果如下所示：
   
   Delivery 表：
   +-------------+-------------+------------+-----------------------------+
   | delivery_id | customer_id | order_date | customer_pref_delivery_date |
   +-------------+-------------+------------+-----------------------------+
   | 1           | 1           | 2019-08-01 | 2019-08-02                  |
   | 2           | 2           | 2019-08-02 | 2019-08-02                  |
   | 3           | 1           | 2019-08-11 | 2019-08-12                  |
   | 4           | 3           | 2019-08-24 | 2019-08-24                  |
   | 5           | 3           | 2019-08-21 | 2019-08-22                  |
   | 6           | 2           | 2019-08-11 | 2019-08-13                  |
   | 7           | 4           | 2019-08-09 | 2019-08-09                  |
   +-------------+-------------+------------+-----------------------------+
   
   Result 表：
   +----------------------+
   | immediate_percentage |
   +----------------------+
   | 50.00                |
   +----------------------+
   1 号顾客的 1 号订单是首次订单，并且是计划订单。
   2 号顾客的 2 号订单是首次订单，并且是即时订单。
   3 号顾客的 5 号订单是首次订单，并且是计划订单。
   4 号顾客的 7 号订单是首次订单，并且是即时订单。
   因此，一半顾客的首次订单是即时的。
   T1174
   */
  /*
   先求出首单的id对应date
   然后求出这些date和送到日期相等的数目比上总数目（首单） 
   */
select round (
    sum(
      order_date = customer_pref_delivery_date
    ) / count(*) * 100,
    2
  ) as immediate_percentage
from Delivery
where (customer_id, order_date) in (
    select customer_id,
      min(order_date)
    from delivery
    group by customer_id
  )
  /* 
   配送表: Delivery
   
   +-----------------------------+---------+
   | Column Name                 | Type    |
   +-----------------------------+---------+
   | delivery_id                 | int     |
   | customer_id                 | int     |
   | order_date                  | date    |
   | customer_pref_delivery_date | date    |
   +-----------------------------+---------+
   delivery_id 是表的主键。
   该表保存着顾客的食物配送信息，顾客在某个日期下了订单，并指定了一个期望的配送日期（和下单日期相同或者在那之后）。
   
   
   
   如果顾客期望的配送日期和下单日期相同，则该订单称为 「即时订单」，否则称为「计划订单」。
   
   写一条 SQL 查询语句获取即时订单所占的百分比， 保留两位小数。
   
   查询结果如下所示。
   
   
   
   示例 1:
   
   输入：
   Delivery 表:
   +-------------+-------------+------------+-----------------------------+
   | delivery_id | customer_id | order_date | customer_pref_delivery_date |
   +-------------+-------------+------------+-----------------------------+
   | 1           | 1           | 2019-08-01 | 2019-08-02                  |
   | 2           | 5           | 2019-08-02 | 2019-08-02                  |
   | 3           | 1           | 2019-08-11 | 2019-08-11                  |
   | 4           | 3           | 2019-08-24 | 2019-08-26                  |
   | 5           | 4           | 2019-08-21 | 2019-08-22                  |
   | 6           | 2           | 2019-08-11 | 2019-08-13                  |
   +-------------+-------------+------------+-----------------------------+
   输出：
   +----------------------+
   | immediate_percentage |
   +----------------------+
   | 33.33                |
   +----------------------+
   解释：2 和 3 号订单为即时订单，其他的为计划订单
   T1173
   */
select round (
    sum(order_date = customer_pref_delivery_date) / count(1) * 100,
    2
  ) as immediate_percentage
from Delivery
  /* 
   Table: Activity
   
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | player_id    | int     |
   | device_id    | int     |
   | event_date   | date    |
   | games_played | int     |
   +--------------+---------+
   （player_id，event_date）是此表的主键。
   这张表显示了某些游戏的玩家的活动情况。
   每一行是一个玩家的记录，他在某一天使用某个设备注销之前登录并玩了很多游戏（可能是 0）。
   
   
   
   编写一个 SQL 查询，报告在首次登录的第二天再次登录的玩家的比率，四舍五入到小数点后两位。
   换句话说，您需要计算从首次登录日期开始至少连续两天登录的玩家的数量，然后除以玩家总数。
   
   查询结果格式如下所示：
   
   Activity table:
   +-----------+-----------+------------+--------------+
   | player_id | device_id | event_date | games_played |
   +-----------+-----------+------------+--------------+
   | 1         | 2         | 2016-03-01 | 5            |
   | 1         | 2         | 2016-03-02 | 6            |
   | 2         | 3         | 2017-06-25 | 1            |
   | 3         | 1         | 2016-03-02 | 0            |
   | 3         | 4         | 2018-07-03 | 5            |
   +-----------+-----------+------------+--------------+
   
   Result table:
   +-----------+
   | fraction  |
   +-----------+
   | 0.33      |
   +-----------+
   只有 ID 为 1 的玩家在第一天登录后才重新登录，所以答案是 1/3 = 0.33
   
   T550
   */
select round(
    count(player_id) /(
      select count(distinct(player_id))
      from Activity
    ),
    2
  ) as fraction
from Activity
where (player_id, event_date) in (
    select player_id,
      date_add(min(event_date), interval 1 day)
    from Activity
    group by player_id
  )
  /* 
   表: Teacher
   
   +-------------+------+
   | Column Name | Type |
   +-------------+------+
   | teacher_id  | int  |
   | subject_id  | int  |
   | dept_id     | int  |
   +-------------+------+
   (subject_id, dept_id) 是该表的主键。
   该表中的每一行都表示带有 teacher_id 的教师在系 dept_id 中教授科目 subject_id。
   
   写一个 SQL 来查询每位老师在大学里教授的科目种类的数量。
   以 任意顺序 返回结果表。
   查询结果格式示例如下。
   示例 1:
   
   输入: 
   Teacher 表:
   +------------+------------+---------+
   | teacher_id | subject_id | dept_id |
   +------------+------------+---------+
   | 1          | 2          | 3       |
   | 1          | 2          | 4       |
   | 1          | 3          | 3       |
   | 2          | 1          | 1       |
   | 2          | 2          | 1       |
   | 2          | 3          | 1       |
   | 2          | 4          | 1       |
   +------------+------------+---------+
   输出:  
   +------------+-----+
   | teacher_id | cnt |
   +------------+-----+
   | 1          | 2   |
   | 2          | 4   |
   +------------+-----+
   解释: 
   教师 1:
   - 他在 3、4 系教科目 2。
   - 他在 3 系教科目 3。
   教师 2:
   - 他在 1 系教科目 1。
   - 他在 1 系教科目 2。
   - 他在 1 系教科目 3。
   - 他在 1 系教科目 4。
   2356
   */
select teacher_id,
  count(distinct(subject_id)) as cnt
from Teacher
group by teacher_id
  /* 
   活动记录表：Activity
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | user_id       | int     |
   | session_id    | int     |
   | activity_date | date    |
   | activity_type | enum    |
   +---------------+---------+
   该表是用户在社交网站的活动记录。
   该表没有主键，可能包含重复数据。
   activity_type 字段为以下四种值 ('open_session', 'end_session', 'scroll_down', 'send_message')。
   每个 session_id 只属于一个用户。
   
   
   
   请写SQL查询出截至 2019-07-27（包含2019-07-27），近 30 天的每日活跃用户数（当天只要有一条活动记录，即为活跃用户）。
   以 任意顺序 返回结果表。
   查询结果示例如下。
   示例 1:
   
   输入：
   Activity table:
   +---------+------------+---------------+---------------+
   | user_id | session_id | activity_date | activity_type |
   +---------+------------+---------------+---------------+
   | 1       | 1          | 2019-07-20    | open_session  |
   | 1       | 1          | 2019-07-20    | scroll_down   |
   | 1       | 1          | 2019-07-20    | end_session   |
   | 2       | 4          | 2019-07-20    | open_session  |
   | 2       | 4          | 2019-07-21    | send_message  |
   | 2       | 4          | 2019-07-21    | end_session   |
   | 3       | 2          | 2019-07-21    | open_session  |
   | 3       | 2          | 2019-07-21    | send_message  |
   | 3       | 2          | 2019-07-21    | end_session   |
   | 4       | 3          | 2019-06-25    | open_session  |
   | 4       | 3          | 2019-06-25    | end_session   |
   +---------+------------+---------------+---------------+
   输出：
   +------------+--------------+ 
   | day        | active_users |
   +------------+--------------+ 
   | 2019-07-20 | 2            |
   | 2019-07-21 | 2            |
   +------------+--------------+ 
   解释：注意非活跃用户的记录不需要展示。
   T1141
   */
select activity_date as day,
  count(distinct(user_id)) as active_users
from Activity
where activity_date > '2019-06-27'
  and activity_date <= '2019-07-27'
group by activity_date
  /* 
   Table: Product
   
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | product_id   | int     |
   | product_name | varchar |
   | unit_price   | int     |
   +--------------+---------+
   Product_id是该表的主键。
   该表的每一行显示每个产品的名称和价格。
   
   Table: Sales
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | seller_id   | int     |
   | product_id  | int     |
   | buyer_id    | int     |
   | sale_date   | date    |
   | quantity    | int     |
   | price       | int     |
   +------ ------+---------+
   这个表没有主键，它可以有重复的行。
   product_id 是 Product 表的外键。
   该表的每一行包含关于一个销售的一些信息。
   
   
   
   编写一个SQL查询，报告2019年春季才售出的产品。即仅在2019-01-01至2019-03-31（含）之间出售的商品。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下所示。
   示例 1:
   
   输入：
   Product table:
   +------------+--------------+------------+
   | product_id | product_name | unit_price |
   +------------+--------------+------------+
   | 1          | S8           | 1000       |
   | 2          | G4           | 800        |
   | 3          | iPhone       | 1400       |
   +------------+--------------+------------+
   Sales table:
   +-----------+------------+----------+------------+----------+-------+
   | seller_id | product_id | buyer_id | sale_date  | quantity | price |
   +-----------+------------+----------+------------+----------+-------+
   | 1         | 1          | 1        | 2019-01-21 | 2        | 2000  |
   | 1         | 2          | 2        | 2019-02-17 | 1        | 800   |
   | 2         | 2          | 3        | 2019-06-02 | 1        | 800   |
   | 3         | 3          | 4        | 2019-05-13 | 2        | 2800  |
   +-----------+------------+----------+------------+----------+-------+
   输出：
   +-------------+--------------+
   | product_id  | product_name |
   +-------------+--------------+
   | 1           | S8           |
   +-------------+--------------+
   解释:
   id为1的产品仅在2019年春季销售。
   id为2的产品在2019年春季销售，但也在2019年春季之后销售。
   id 3的产品在2019年春季之后销售。
   我们只退回产品1，因为它是2019年春季才销售的产品。
   T1084
   */
  /*
   group by之前的where是消除不需要的行的
   之后的having是统计分组后的 
   */
select a.product_id,
  b.product_name
from Sales a
  left join Product b on a.product_id = b.product_id
group by a.product_id
having min(a.sale_date) >= '2019-01-01'
  and max(a.sale_date) <= '2019-03-31'
  /* 
   | seller_id | product_id | buyer_id | sale_date  | quantity | price | product_id | product_name | unit_price |
   | --------- | ---------- | -------- | ---------- | -------- | ----- | ---------- | ------------ | ---------- |
   | 1         | 1          | 1        | 2019-01-21 | 2        | 2000  | 1          | S8           | 1000       |
   | 1         | 2          | 2        | 2019-02-17 | 1        | 800   | 2          | G4           | 800        |
   | 2         | 2          | 3        | 2019-06-02 | 1        | 800   | 2          | G4           | 800        |
   | 3         | 3          | 4        | 2019-05-13 | 2        | 2800  | 3          | iPhone       | 1400       |
   */
  /* 
   表: Courses
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | student     | varchar |
   | class       | varchar |
   +-------------+---------+
   (student, class)是该表的主键列。
   该表的每一行表示学生的名字和他们注册的班级。
   编写一个SQL查询来报告 至少有5个学生 的所有班级。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下所示。
   
   示例 1:
   
   输入: 
   Courses table:
   +---------+----------+
   | student | class    |
   +---------+----------+
   | A       | Math     |
   | B       | English  |
   | C       | Math     |
   | D       | Biology  |
   | E       | Math     |
   | F       | Computer |
   | G       | Math     |
   | H       | Math     |
   | I       | Math     |
   +---------+----------+
   输出: 
   +---------+ 
   | class   | 
   +---------+ 
   | Math    | 
   +---------+
   解释: 
   -数学课有6个学生，所以我们包括它。
   -英语课有1名学生，所以我们不包括它。
   -生物课有1名学生，所以我们不包括它。
   -计算机课有1个学生，所以我们不包括它。
   T596
   */
select class
from Courses
group by class
having count(student) >= 5
  /* 
   表： Followers
   
   +-------------+------+
   | Column Name | Type |
   +-------------+------+
   | user_id     | int  |
   | follower_id | int  |
   +-------------+------+
   (user_id, follower_id) 是这个表的主键。
   该表包含一个关注关系中关注者和用户的编号，其中关注者关注用户。
   
   写出 SQL 语句，对于每一个用户，返回该用户的关注者数量。
   按 user_id 的顺序返回结果表。
   查询结果的格式如下示例所示。
   示例 1：
   
   输入：
   Followers 表：
   +---------+-------------+
   | user_id | follower_id |
   +---------+-------------+
   | 0       | 1           |
   | 1       | 0           |
   | 2       | 0           |
   | 2       | 1           |
   +---------+-------------+
   输出：
   +---------+----------------+
   | user_id | followers_count|
   +---------+----------------+
   | 0       | 1              |
   | 1       | 1              |
   | 2       | 2              |
   +---------+----------------+
   解释：
   0 的关注者有 {1}
   1 的关注者有 {0}
   2 的关注者有 {0,1}
   T1729
   */
select user_id,
  count(follower_id) as followers_count
from Followers
group by user_id
order by user_id asc
  /* 
   MyNumbers 表：
   +-------------+------+
   | Column Name | Type |
   +-------------+------+
   | num         | int  |
   +-------------+------+
   这张表没有主键。可能包含重复数字。
   这张表的每一行都含有一个整数。
   
   单一数字 是在 MyNumbers 表中只出现一次的数字。
   
   请你编写一个 SQL 查询来报告最大的 单一数字 。如果不存在 单一数字 ，查询需报告 null 。
   
   查询结果如下例所示。
   
   示例 1：
   
   输入：
   MyNumbers 表：
   +-----+
   | num |
   +-----+
   | 8   |
   | 8   |
   | 3   |
   | 3   |
   | 1   |
   | 4   |
   | 5   |
   | 6   |
   +-----+
   输出：
   +-----+
   | num |
   +-----+
   | 6   |
   +-----+
   解释：单一数字有 1、4、5 和 6 。
   6 是最大的单一数字，返回 6 。
   
   示例 2：
   
   输入：
   MyNumbers table:
   +-----+
   | num |
   +-----+
   | 8   |
   | 8   |
   | 7   |
   | 7   |
   | 3   |
   | 3   |
   | 3   |
   +-----+
   输出：
   +------+
   | num  |
   +------+
   | null |
   +------+
   解释：输入的表中不存在单一数字，所以返回 null 。
   T619
   */
select max(num) as num
from MyNumbers
where num in(
    select num
    from MyNumbers
    group by num
    having count(num) = 1
  )
  /* 
   Customer 表：
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | customer_id | int     |
   | product_key | int     |
   +-------------+---------+
   product_key 是 Customer 表的外键。
   
   Product 表：
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | product_key | int     |
   +-------------+---------+
   product_key 是这张表的主键。
   
   
   
   写一条 SQL 查询语句，从 Customer 表中查询购买了 Product 表中所有产品的客户的 id。
   
   示例：
   
   Customer 表：
   +-------------+-------------+
   | customer_id | product_key |
   +-------------+-------------+
   | 1           | 5           |
   | 2           | 6           |
   | 3           | 5           |
   | 3           | 6           |
   | 1           | 6           |
   +-------------+-------------+
   
   Product 表：
   +-------------+
   | product_key |
   +-------------+
   | 5           |
   | 6           |
   +-------------+
   
   Result 表：
   +-------------+
   | customer_id |
   +-------------+
   | 1           |
   | 3           |
   +-------------+
   购买了所有产品（5 和 6）的客户的 id 是 1 和 3 。
   
   T1045
   */
select customer_id
from Customer
group by customer_id
having count(distinct(product_key)) = (
    select count(product_key)
    from Product
  )
  /* 
   Table: Employees
   
   +-------------+----------+
   | Column Name | Type     |
   +-------------+----------+
   | employee_id | int      |
   | name        | varchar  |
   | reports_to  | int      |
   | age         | int      |
   +-------------+----------+
   employee_id 是这个表的主键.
   该表包含员工以及需要听取他们汇报的上级经理的ID的信息。 有些员工不需要向任何人汇报（reports_to 为空）。
   
   对于此问题，我们将至少有一个其他员工需要向他汇报的员工，视为一个经理。
   编写SQL查询需要听取汇报的所有经理的ID、名称、直接向该经理汇报的员工人数，以及这些员工的平均年龄，其中该平均年龄需要四舍五入到最接近的整数。
   返回的结果集需要按照 employee_id 进行排序。
   查询结果的格式如下：
   Employees table:
   +-------------+---------+------------+-----+
   | employee_id | name    | reports_to | age |
   +-------------+---------+------------+-----+
   | 9           | Hercy   | null       | 43  |
   | 6           | Alice   | 9          | 41  |
   | 4           | Bob     | 9          | 36  |
   | 2           | Winston | null       | 37  |
   +-------------+---------+------------+-----+
   
   Result table:
   +-------------+-------+---------------+-------------+
   | employee_id | name  | reports_count | average_age |
   +-------------+-------+---------------+-------------+
   | 9           | Hercy | 2             | 39          |
   +-------------+-------+---------------+-------------+
   Hercy 有两个需要向他汇报的员工, 他们是 Alice and Bob. 他们的平均年龄是 (41+36)/2 = 38.5, 四舍五入的结果是 39.
   
   T1731
   */
  /*
   这题使用join就够了，差别
   join只连接相等的行，左表可能只有几条
   leftjoin 还包含左表全部的表
   */
select a.employee_id,
  a.name,
  count(b.employee_id) as reports_count,
  round(avg(b.age), 0) as average_age
from Employees a
  left join Employees b on a.employee_id = b.reports_to
group by employee_id
having count(b.employee_id) >= 1
order by employee_id asc
  /* 
   | employee_id | name    | reports_to | age | employee_id | name  | reports_to | age  |
   | ----------- | ------- | ---------- | --- | ----------- | ----- | ---------- | ---- |
   | 9           | Hercy   | null       | 43  | 4           | Bob   | 9          | 36   |
   | 9           | Hercy   | null       | 43  | 6           | Alice | 9          | 41   |
   | 6           | Alice   | 9          | 41  | null        | null  | null       | null |
   | 4           | Bob     | 9          | 36  | null        | null  | null       | null |
   | 2           | Winston | null       | 37  | null        | null  | null       | null |
   */
  /* 
   Table: Employee
   
   +---------------+---------+
   | Column Name   |  Type   |
   +---------------+---------+
   | employee_id   | int     |
   | department_id | int     |
   | primary_flag  | varchar |
   +---------------+---------+
   这张表的主键为 employee_id, department_id
   employee_id 是员工的ID
   department_id 是部门的ID，表示员工与该部门有关系
   primary_flag 是一个枚举类型，值分别为('Y', 'N'). 如果值为'Y',表示该部门是员工的直属部门。 如果值是'N',则否
   
   一个员工可以属于多个部门。
   
   当一个员工加入超过一个部门的时候，他需要决定哪个部门是他的直属部门。
   
   请注意，当员工只加入一个部门的时候，那这个部门将默认为他的直属部门，虽然表记录的值为'N'.
   
   请编写一段SQL，查出员工所属的直属部门。
   
   返回结果没有顺序要求。
   
   
   
   示例：
   
   Employee table:
   +-------------+---------------+--------------+
   | employee_id | department_id | primary_flag |
   +-------------+---------------+--------------+
   | 1           | 1             | N            |
   | 2           | 1             | Y            |
   | 2           | 2             | N            |
   | 3           | 3             | N            |
   | 4           | 2             | N            |
   | 4           | 3             | Y            |
   | 4           | 4             | N            |
   +-------------+---------------+--------------+
   
   Result table:
   +-------------+---------------+
   | employee_id | department_id |
   +-------------+---------------+
   | 1           | 1             |
   | 2           | 1             |
   | 3           | 3             |
   | 4           | 3             |
   +-------------+---------------+
   - 员工1的直属部门是1
   - 员工2的直属部门是1
   - 员工3的直属部门是3
   - 员工4的直属部门是3
   */
  /* 
   group by以后，只有聚合函数会作用在组内所有的行上，非聚合函数的筛选条件（eg. primary_flag='Y'）只会作用在组内的第一行
   */
select ee.employee_id,
  if(cnt = 1, ee.department_id, ee.flag) department_id
from (
    select *,
      count(department_id) cnt,
      sum(if(primary_flag = 'Y', department_id, 0)) flag
    from employee
    group by employee_id
  ) as ee
  /* 方法二 */
select employee_id,
  department_id
from Employee
where primary_flag = 'Y'
union
select employee_id,
  department_id
from Employee
group by employee_id
having count(employee_id) = 1
  /* 
   表: Triangle
   
   +-------------+------+
   | Column Name | Type |
   +-------------+------+
   | x           | int  |
   | y           | int  |
   | z           | int  |
   +-------------+------+
   (x, y, z)是该表的主键列。
   该表的每一行包含三个线段的长度。
   
   
   
   写一个SQL查询，每三个线段报告它们是否可以形成一个三角形。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下所示。
   
   
   
   示例 1:
   
   输入: 
   Triangle 表:
   +----+----+----+
   | x  | y  | z  |
   +----+----+----+
   | 13 | 15 | 30 |
   | 10 | 20 | 15 |
   +----+----+----+
   输出: 
   +----+----+----+----------+
   | x  | y  | z  | triangle |
   +----+----+----+----------+
   | 13 | 15 | 30 | No       |
   | 10 | 20 | 15 | Yes      |
   +----+----+----+----------+
   T610
   */
select x,
  y,
  z,
  if(
    x + y > z
    and x + z > y
    and y + z > x,
    'Yes',
    'No'
  ) as triangle
from Triangle
select x,
  y,
  z,
  (
    case
      when x + y > z
      and x + z > y
      and y + z > x then 'Yes'
      else 'No'
    end
  ) as triangle
from Triangle
  /* 
   表：Logs
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | id          | int     |
   | num         | varchar |
   +-------------+---------+
   id 是这个表的主键。
   编写一个 SQL 查询，查找所有至少连续出现三次的数字。
   返回的结果表中的数据可以按 任意顺序 排列。
   
   查询结果格式如下面的例子所示：
   示例 1:
   
   输入：
   Logs 表：
   +----+-----+
   | Id | Num |
   +----+-----+
   | 1  | 1   |
   | 2  | 1   |
   | 3  | 1   |
   | 4  | 2   |
   | 5  | 1   |
   | 6  | 2   |
   | 7  | 2   |
   +----+-----+
   输出：
   Result 表：
   +-----------------+
   | ConsecutiveNums |
   +-----------------+
   | 1               |
   +-----------------+
   解释：1 是唯一连续出现至少三次的数字。
   T180
   */
select distinct(a.Num) as ConsecutiveNums
from logs a,
  logs b,
  logs c
where a.Id = b.Id + 1
  and a.Id = c.Id + 2
  and a.Num = b.Num
  and a.Num = c.Num
  /* 
   产品数据表: Products
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | product_id    | int     |
   | new_price     | int     |
   | change_date   | date    |
   +---------------+---------+
   这张表的主键是 (product_id, change_date)。
   这张表的每一行分别记录了 某产品 在某个日期 更改后 的新价格。
   
   写一段 SQL来查找在 2019-08-16 时全部产品的价格，假设所有产品在修改前的价格都是 10 。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下例所示。
   示例 1:
   
   输入：
   Products 表:
   +------------+-----------+-------------+
   | product_id | new_price | change_date |
   +------------+-----------+-------------+
   | 1          | 20        | 2019-08-14  |
   | 2          | 50        | 2019-08-14  |
   | 1          | 30        | 2019-08-15  |
   | 1          | 35        | 2019-08-16  |
   | 2          | 65        | 2019-08-17  |
   | 3          | 20        | 2019-08-18  |
   +------------+-----------+-------------+
   输出：
   +------------+-------+
   | product_id | price |
   +------------+-------+
   | 2          | 50    |
   | 1          | 35    |
   | 3          | 10    |
   +------------+-------+
   T1164
   */
select product_id,
  new_price as price
from Products
where (product_id, change_date) in(
    select product_id,
      max(change_date)
    from products
    where change_date <= '2019-08-16'
    group by product_id
  )
union
select product_id,
  10 as price
from Products
group by product_id
having min(change_date) > '2019-08-16'
  /*
   表: Queue
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | person_id   | int     |
   | person_name | varchar |
   | weight      | int     |
   | turn        | int     |
   +-------------+---------+
   person_id 是这个表的主键。
   该表展示了所有等待电梯的人的信息。
   表中 person_id 和 turn 列将包含从 1 到 n 的所有数字，其中 n 是表中的行数。
   有一群人在等着上公共汽车。然而，巴士有1000 公斤的重量限制，所以可能会有一些人不能上。
   写一条 SQL 查询语句查找 最后一个 能进入电梯且不超过重量限制的 person_name 。题目确保队列中第一位的人可以进入电梯，不会超重。
   查询结果如下所示。
   
   示例 1:
   
   输入：
   Queue 表
   +-----------+-------------------+--------+------+
   | person_id | person_name       | weight | turn |
   +-----------+-------------------+--------+------+
   | 5         | George Washington | 250    | 1    |
   | 3         | John Adams        | 350    | 2    |
   | 6         | Thomas Jefferson  | 400    | 3    |
   | 2         | Will Johnliams    | 200    | 4    |
   | 4         | Thomas Jefferson  | 175    | 5    |
   | 1         | James Elephant    | 500    | 6    |
   +-----------+-------------------+--------+------+
   输出：
   +-------------------+
   | person_name       |
   +-------------------+
   | Thomas Jefferson  |
   +-------------------+
   解释：
   为了简化，Queue 表按 turn 列由小到大排序。
   上例中 George Washington(id 5), John Adams(id 3) 和 Thomas Jefferson(id 6) 将可以进入电梯,因为他们的体重和为 250 + 350 + 400 = 1000。
   Thomas Jefferson(id 6) 是最后一个体重合适并进入电梯的人。
   T1204 
   */
select a.person_name
from Queue a
  inner join Queue b on a.turn >= b.turn
group by a.person_id
having sum(b.weight) <= 1000
order by a.turn desc
limit 1
  /* 
   表: Accounts
   
   +-------------+------+
   | 列名        | 类型  |
   +-------------+------+
   | account_id  | int  |
   | income      | int  |
   +-------------+------+
   account_id 是这个表的主键。
   每一行都包含一个银行帐户的月收入的信息。
   写出一个 SQL 查询，来报告每个工资类别的银行账户数量。 工资类别如下：
   
   "Low Salary"：所有工资 严格低于 20000 美元。
   "Average Salary"： 包含 范围内的所有工资 [$20000, $50000] 。
   
   "High Salary"：所有工资 严格大于 50000 美元。
   
   结果表 必须 包含所有三个类别。 如果某个类别中没有帐户，则报告 0 。
   
   按 任意顺序 返回结果表。
   
   查询结果格式如下示例。
   示例 1：
   
   输入：
   Accounts 表:
   +------------+--------+
   | account_id | income |
   +------------+--------+
   | 3          | 108939 |
   | 2          | 12747  |
   | 8          | 87709  |
   | 6          | 91796  |
   +------------+--------+
   输出：
   +----------------+----------------+
   | category       | accounts_count |
   +----------------+----------------+
   | Low Salary     | 1              |
   | Average Salary | 0              |
   | High Salary    | 3              |
   +----------------+----------------+
   解释：
   低薪: 数量为 2.
   中等薪水: 没有.
   高薪: 有三个账户，他们是 3, 6和 8.
   T1907
   */
select 'High Salary' as category,
  count(*) as accounts_count
from Accounts
where income > 50000
union
select 'Average Salary' as category,
  count(*) as accounts_count
from Accounts
where income <= 50000
  and income >= 20000
union
select 'Low Salary' as category,
  count(*) as accounts_count
from Accounts
where income < 20000
  /* 
   表: Employees
   
   +-------------+----------+
   | Column Name | Type     |
   +-------------+----------+
   | employee_id | int      |
   | name        | varchar  |
   | manager_id  | int      |
   | salary      | int      |
   +-------------+----------+
   employee_id 是这个表的主键。
   这个表包含了员工，他们的薪水和上级经理的id。
   有一些员工没有上级经理（其manager_id 是空值）。
   写一个查询语句，查询出，这些员工的id，他们的薪水严格少于$30000 并且他们的上级经理已离职。
   当一个经理离开公司时，他们的信息需要从员工表中删除掉，但是表中的员工的manager_id  这一列还是设置的离职经理的id 。
   
   返回的结果按照employee_id 从小到大排序。
   查询结果如下所示：
   示例：
   输入：
   Employees table:
   +-------------+-----------+------------+--------+
   | employee_id | name      | manager_id | salary |
   +-------------+-----------+------------+--------+
   | 3           | Mila      | 9          | 60301  |
   | 12          | Antonella | null       | 31000  |
   | 13          | Emery     | null       | 67084  |
   | 1           | Kalel     | 11         | 21241  |
   | 9           | Mikaela   | null       | 50937  |
   | 11          | Joziah    | 6          | 28485  |
   +-------------+-----------+------------+--------+
   输出：
   +-------------+
   | employee_id |
   +-------------+
   | 11          |
   +-------------+
   
   解释：
   薪水少于30000美元的员工有1号(Kalel) and 11号 (Joziah)。
   Kalel的上级经理是11号员工，他还在公司上班(他是Joziah)。
   Joziah的上级经理是6号员工，他已经离职，因为员工表里面已经没有6号员工的信息了，它被删除了。
   
   T1978
   */
select employee_id
from Employees
where salary < 30000
  and manager_id not in(
    select employee_id
    from Employees
  )
order by employee_id asc
  /* 
   表: Seat
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | id          | int     |
   | name        | varchar |
   +-------------+---------+
   Id是该表的主键列。
   该表的每一行都表示学生的姓名和ID。
   Id是一个连续的增量。
   编写SQL查询来交换每两个连续的学生的座位号。如果学生的数量是奇数，则最后一个学生的id不交换。
   
   按 id 升序 返回结果表。
   
   查询结果格式如下所示。
   示例 1:
   
   输入: 
   Seat 表:
   +----+---------+
   | id | student |
   +----+---------+
   | 1  | Abbot   |
   | 2  | Doris   |
   | 3  | Emerson |
   | 4  | Green   |
   | 5  | Jeames  |
   +----+---------+
   输出: 
   +----+---------+
   | id | student |
   +----+---------+
   | 1  | Doris   |
   | 2  | Abbot   |
   | 3  | Green   |
   | 4  | Emerson |
   | 5  | Jeames  |
   +----+---------+
   解释:
   请注意，如果学生人数为奇数，则不需要更换最后一名学生的座位。
   
   T626
   */
select if(
    id % 2,
    if(
      id =(
        select max(id)
        from Seat
      ),
      id,
      id + 1
    ),
    id -1
  ) as id,
  student
from Seat
order by id asc
  /* 
   表：Movies
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | movie_id      | int     |
   | title         | varchar |
   +---------------+---------+
   movie_id 是这个表的主键。
   title 是电影的名字。
   
   表：Users
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | user_id       | int     |
   | name          | varchar |
   +---------------+---------+
   user_id 是表的主键。
   
   表：MovieRating
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | movie_id      | int     |
   | user_id       | int     |
   | rating        | int     |
   | created_at    | date    |
   +---------------+---------+
   (movie_id, user_id) 是这个表的主键。
   这个表包含用户在其评论中对电影的评分 rating 。
   created_at 是用户的点评日期。 
   
   
   
   请你编写一组 SQL 查询：
   
   查找评论电影数量最多的用户名。如果出现平局，返回字典序较小的用户名。
   查找在 February 2020 平均评分最高 的电影名称。如果出现平局，返回字典序较小的电影名称。
   字典序 ，即按字母在字典中出现顺序对字符串排序，字典序较小则意味着排序靠前。
   查询结果格式如下例所示。
   输入：
   Movies 表：
   +-------------+--------------+
   | movie_id    |  title       |
   +-------------+--------------+
   | 1           | Avengers     |
   | 2           | Frozen 2     |
   | 3           | Joker        |
   +-------------+--------------+
   Users 表：
   +-------------+--------------+
   | user_id     |  name        |
   +-------------+--------------+
   | 1           | Daniel       |
   | 2           | Monica       |
   | 3           | Maria        |
   | 4           | James        |
   +-------------+--------------+
   MovieRating 表：
   +-------------+--------------+--------------+-------------+
   | movie_id    | user_id      | rating       | created_at  |
   +-------------+--------------+--------------+-------------+
   | 1           | 1            | 3            | 2020-01-12  |
   | 1           | 2            | 4            | 2020-02-11  |
   | 1           | 3            | 2            | 2020-02-12  |
   | 1           | 4            | 1            | 2020-01-01  |
   | 2           | 1            | 5            | 2020-02-17  | 
   | 2           | 2            | 2            | 2020-02-01  | 
   | 2           | 3            | 2            | 2020-03-01  |
   | 3           | 1            | 3            | 2020-02-22  | 
   | 3           | 2            | 4            | 2020-02-25  | 
   +-------------+--------------+--------------+-------------+
   输出：
   Result 表：
   +--------------+
   | results      |
   +--------------+
   | Daniel       |
   | Frozen 2     |
   +--------------+
   解释：
   Daniel 和 Monica 都点评了 3 部电影（"Avengers", "Frozen 2" 和 "Joker"） 但是 Daniel 字典序比较小。
   Frozen 2 和 Joker 在 2 月的评分都是 3.5，但是 Frozen 2 的字典序比较小。
   T1341
   */
  (
    select a.name as results
    from Users a
      left join MovieRating b on a.user_id = b.user_id
    group by a.user_id
    order by count(a.user_id) desc,
      a.name asc
    limit 1
  )
union
(
  select b.title as results
  from MovieRating a
    join Movies b on a.movie_id = b.movie_id
  where created_at >= '2020-02-01'
    and created_at < '2020-03-01'
  group by a.movie_id
  order by avg(a.rating) desc,
    b.title asc
  limit 1
)
/* 
 表: Customer
 
 +---------------+---------+
 | Column Name   | Type    |
 +---------------+---------+
 | customer_id   | int     |
 | name          | varchar |
 | visited_on    | date    |
 | amount        | int     |
 +---------------+---------+
 (customer_id, visited_on) 是该表的主键。
 该表包含一家餐馆的顾客交易数据。
 visited_on 表示 (customer_id) 的顾客在 visited_on 那天访问了餐馆。
 amount 是一个顾客某一天的消费总额。
 
 
 
 你是餐馆的老板，现在你想分析一下可能的营业额变化增长（每天至少有一位顾客）。
 
 写一条 SQL 查询计算以 7 天（某日期 + 该日期前的 6 天）为一个时间段的顾客消费平均值。average_amount 要 保留两位小数。
 
 查询结果按 visited_on 排序。
 
 查询结果格式的例子如下。
 
 示例 1:
 
 输入：
 Customer 表:
 +-------------+--------------+--------------+-------------+
 | customer_id | name         | visited_on   | amount      |
 +-------------+--------------+--------------+-------------+
 | 1           | Jhon         | 2019-01-01   | 100         |
 | 2           | Daniel       | 2019-01-02   | 110         |
 | 3           | Jade         | 2019-01-03   | 120         |
 | 4           | Khaled       | 2019-01-04   | 130         |
 | 5           | Winston      | 2019-01-05   | 110         | 
 | 6           | Elvis        | 2019-01-06   | 140         | 
 | 7           | Anna         | 2019-01-07   | 150         |
 | 8           | Maria        | 2019-01-08   | 80          |
 | 9           | Jaze         | 2019-01-09   | 110         | 
 | 1           | Jhon         | 2019-01-10   | 130         | 
 | 3           | Jade         | 2019-01-10   | 150         | 
 +-------------+--------------+--------------+-------------+
 输出：
 +--------------+--------------+----------------+
 | visited_on   | amount       | average_amount |
 +--------------+--------------+----------------+
 | 2019-01-07   | 860          | 122.86         |
 | 2019-01-08   | 840          | 120            |
 | 2019-01-09   | 840          | 120            |
 | 2019-01-10   | 1000         | 142.86         |
 +--------------+--------------+----------------+
 解释：
 第一个七天消费平均值从 2019-01-01 到 2019-01-07 是restaurant-growth/restaurant-growth/ (100 + 110 + 120 + 130 + 110 + 140 + 150)/7 = 122.86
 第二个七天消费平均值从 2019-01-02 到 2019-01-08 是 (110 + 120 + 130 + 110 + 140 + 150 + 80)/7 = 120
 第三个七天消费平均值从 2019-01-03 到 2019-01-09 是 (120 + 130 + 110 + 140 + 150 + 80 + 110)/7 = 120
 第四个七天消费平均值从 2019-01-04 到 2019-01-10 是 (130 + 110 + 140 + 150 + 80 + 110 + 130 + 150)/7 = 142.86
 T1321
 */
select visited_on,
  sum(amount)
from Customer
group by visited_on
  /* 
   | visited_on | sum(amount) |
   | ---------- | ----------- |
   | 2019-01-01 | 100         |
   | 2019-01-02 | 110         |
   | 2019-01-03 | 120         |
   | 2019-01-04 | 130         |
   | 2019-01-05 | 110         |
   | 2019-01-06 | 140         |
   | 2019-01-07 | 150         |
   | 2019-01-08 | 80          |
   | 2019-01-09 | 110         |
   | 2019-01-10 | 280         |
   */
select visited_on,
  avg(t.amount) over (
    order by visited_on rows 6 preceding
  ) as amount
from (
    select visited_on,
      sum(amount) as amount
    from Customer
    group by visited_on
  ) as t
  /* 
   | visited_on | amount   |
   | ---------- | -------- |
   | 2019-01-01 | 100      |
   | 2019-01-02 | 105      |
   | 2019-01-03 | 110      |
   | 2019-01-04 | 115      |
   | 2019-01-05 | 114      |
   | 2019-01-06 | 118.3333 |
   | 2019-01-07 | 122.8571 |
   | 2019-01-08 | 120      |
   | 2019-01-09 | 120      |
   | 2019-01-10 | 142.8571 |
   */
select tt.visited_on,
  tt.sum_amout as amount,
  round(tt.sum_amout / 7, 2) as average_amount
from(
    select visited_on,
      sum(t.amount) over (
        order by visited_on rows 6 preceding
      ) as sum_amout
    from (
        select visited_on,
          sum(amount) as amount
        from Customer
        group by visited_on
      ) as t
  ) as tt
where datediff(
    visited_on,
    (
      select min(visited_on)
      from Customer
    )
  ) >= 6
select visited_on,
  amount,
  average_amount
from (
    select visited_on,
      row_number() over(
        order by visited_on
      ) as rk,
      sum(sum(amount)) over(
        order by visited_on rows 6 preceding
      ) as amount,
      round(
        avg(sum(amount)) over(
          order by visited_on rows 6 preceding
        ),
        2
      ) as average_amount
    from Customer
    group by visited_on
  ) as base
where rk >= 7
  /* 加数字就是列序号 */
order by 1
  /* 
   在 Facebook 或者 Twitter 这样的社交应用中，人们经常会发好友申请也会收到其他人的好友申请。
   
   RequestAccepted 表：
   
   +----------------+---------+
   | Column Name    | Type    |
   +----------------+---------+
   | requester_id   | int     |
   | accepter_id    | int     |
   | accept_date    | date    |
   +----------------+---------+
   (requester_id, accepter_id) 是这张表的主键。
   这张表包含发送好友请求的人的 ID ，接收好友请求的人的 ID ，以及好友请求通过的日期。
   
   
   
   写一个查询语句，找出拥有最多的好友的人和他拥有的好友数目。
   
   生成的测试用例保证拥有最多好友数目的只有 1 个人。
   
   查询结果格式如下例所示。
   
   
   
   示例：
   
   输入：
   RequestAccepted 表：
   +--------------+-------------+-------------+
   | requester_id | accepter_id | accept_date |
   +--------------+-------------+-------------+
   | 1            | 2           | 2016/06/03  |
   | 1            | 3           | 2016/06/08  |
   | 2            | 3           | 2016/06/08  |
   | 3            | 4           | 2016/06/09  |
   +--------------+-------------+-------------+
   输出：
   +----+-----+
   | id | num |
   +----+-----+
   | 3  | 3   |
   +----+-----+
   解释：
   编号为 3 的人是编号为 1 ，2 和 4 的人的好友，所以他总共有 3 个好友，比其他人都多。
   T602
   */
select t.id,
  count(t.id) as num
from(
    (
      select requester_id as id
      from RequestAccepted
    )
    union all
    (
      select accepter_id as id
      from RequestAccepted
    )
  ) as t
group by t.id
order by count(t.id) desc
limit 1
  /* 
   表: Student
   
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | student_id   | int     |
   | student_name | varchar |
   | gender       | varchar |
   | dept_id      | int     |
   +--------------+---------+
   Student_id是该表的主键。
   dept_id是Department表中dept_id的外键。
   该表的每一行都表示学生的姓名、性别和所属系的id。
   
   
   
   表: Department
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | dept_id     | int     |
   | dept_name   | varchar |
   +-------------+---------+
   Dept_id是该表的主键。
   该表的每一行包含一个部门的id和名称。
   
   编写一个SQL查询，为 Department 表中的所有部门(甚至是没有当前学生的部门)报告各自的部门名称和每个部门的学生人数。
   按 student_number 降序 返回结果表。如果是平局，则按 dept_name 的 字母顺序 排序。
   查询结果格式如下所示。
   示例 1:
   
   输入: 
   Student 表:
   +------------+--------------+--------+---------+
   | student_id | student_name | gender | dept_id |
   +------------+--------------+--------+---------+
   | 1          | Jack         | M      | 1       |
   | 2          | Jane         | F      | 1       |
   | 3          | Mark         | M      | 2       |
   +------------+--------------+--------+---------+
   Department 表:
   +---------+-------------+
   | dept_id | dept_name   |
   +---------+-------------+
   | 1       | Engineering |
   | 2       | Science     |
   | 3       | Law         |
   +---------+-------------+
   输出: 
   +-------------+----------------+
   | dept_name   | student_number |
   +-------------+----------------+
   | Engineering | 2              |
   | Science     | 1              |
   | Law         | 0              |
   +-------------+----------------+
   T585
   */
select a.dept_name,
  count(b.student_id) as student_number
from Department a
  left join Student b on a.dept_id = b.dept_id
group by a.dept_name
order by student_number desc,
  a.dept_name asc
  /* 
   写一个查询语句，将 2016 年 (TIV_2016) 所有成功投资的金额加起来，保留 2 位小数。
   
   对于一个投保人，他在 2016 年成功投资的条件是：
   
   他在 2015 年的投保额 (TIV_2015) 至少跟一个其他投保人在 2015 年的投保额相同。
   他所在的城市必须与其他投保人都不同（也就是说维度和经度不能跟其他任何一个投保人完全相同）。
   
   输入格式:
   表 insurance 格式如下：
   
   | Column Name | Type          |
   |-------------|---------------|
   | PID         | INTEGER(11)   |
   | TIV_2015    | NUMERIC(15,2) |
   | TIV_2016    | NUMERIC(15,2) |
   | LAT         | NUMERIC(5,2)  |
   | LON         | NUMERIC(5,2)  |
   
   PID 字段是投保人的投保编号， TIV_2015 是该投保人在2015年的总投保金额， TIV_2016 是该投保人在2016年的投保金额， LAT 是投保人所在城市的维度，
   LON 是投保人所在城市的经度。
   
   样例输入
   
   | PID | TIV_2015 | TIV_2016 | LAT | LON |
   |-----|----------|----------|-----|-----|
   | 1   | 10       | 5        | 10  | 10  |
   | 2   | 20       | 20       | 20  | 20  |
   | 3   | 10       | 30       | 20  | 20  |
   | 4   | 10       | 40       | 40  | 40  |
   
   样例输出
   
   | TIV_2016 |
   |----------|
   | 45.00    |
   
   解释
   
   就如最后一个投保人，第一个投保人同时满足两个条件：
   1. 他在 2015 年的投保金额 TIV_2015 为 '10' ，与第三个和第四个投保人在 2015 年的投保金额相同。
   2. 他所在城市的经纬度是独一无二的。
   
   第二个投保人两个条件都不满足。他在 2015 年的投资 TIV_2015 与其他任何投保人都不相同。
   且他所在城市的经纬度与第三个投保人相同。基于同样的原因，第三个投保人投资失败。
   
   所以返回的结果是第一个投保人和最后一个投保人的 TIV_2016 之和，结果是 45 。
   
   T585
   */
  /*
   两个条件是并列的，不是查重后再找@！
   */
select round(sum(tt.TIV_2016), 2) as TIV_2016
from (
    select round(sum(t.TIV_2016), 2) as TIV_2016
    from insurance t
    where (LAT, LON) in (
        select LAT,
          LON
        from insurance
        group by LAT,
          LON
        having count(*) = 1
      )
    group by TIV_2015
    having count(*) > 1
  ) as tt
select round(sum(t.TIV_2016), 2) as TIV_2016
from insurance t
where (LAT, LON) in (
    select LAT,
      LON
    from insurance
    group by LAT,
      LON
    having count(*) = 1
  )
  and TIV_2015 in (
    select TIV_2015
    from insurance
    group by TIV_2015
    having count(*) > 1
  )
  /*
   窗口 
   */
select round(sum(t.TIV_2016), 2) as TIV_2016
from (
    select TIV_2016,
      count(*) over (partition by TIV_2015) as c1,
      count(*) over (partition by LAT, LON) as c2
    from insurance
  ) as t
where t.c1 > 1
  and t.c2 = 1
  /*
   表: Employee
   
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | id           | int     |
   | name         | varchar |
   | salary       | int     |
   | departmentId | int     |
   +--------------+---------+
   Id是该表的主键列。
   departmentId是Department表中ID的外键。
   该表的每一行都表示员工的ID、姓名和工资。它还包含了他们部门的ID。
   
   
   
   表: Department
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | id          | int     |
   | name        | varchar |
   +-------------+---------+
   Id是该表的主键列。
   该表的每一行表示部门ID和部门名。
   
   
   
   公司的主管们感兴趣的是公司每个部门中谁赚的钱最多。一个部门的 高收入者 是指一个员工的工资在该部门的 不同 工资中 排名前三 。
   
   编写一个SQL查询，找出每个部门中 收入高的员工 。
   
   以 任意顺序 返回结果表。
   
   查询结果格式如下所示。
   
   
   
   示例 1:
   
   输入: 
   Employee 表:
   +----+-------+--------+--------------+
   | id | name  | salary | departmentId |
   +----+-------+--------+--------------+
   | 1  | Joe   | 85000  | 1            |
   | 2  | Henry | 80000  | 2            |
   | 3  | Sam   | 60000  | 2            |
   | 4  | Max   | 90000  | 1            |
   | 5  | Janet | 69000  | 1            |
   | 6  | Randy | 85000  | 1            |
   | 7  | Will  | 70000  | 1            |
   +----+-------+--------+--------------+
   Department  表:
   +----+-------+
   | id | name  |
   +----+-------+
   | 1  | IT    |
   | 2  | Sales |
   +----+-------+
   输出: 
   +------------+----------+--------+
   | Department | Employee | Salary |
   +------------+----------+--------+
   | IT         | Max      | 90000  |
   | IT         | Joe      | 85000  |
   | IT         | Randy    | 85000  |
   | IT         | Will     | 70000  |
   | Sales      | Henry    | 80000  |
   | Sales      | Sam      | 60000  |
   +------------+----------+--------+
   解释:
   在IT部门:
   - Max的工资最高
   - 兰迪和乔都赚取第二高的独特的薪水
   - 威尔的薪水是第三高的
   
   在销售部:
   - 亨利的工资最高
   - 山姆的薪水第二高
   - 没有第三高的工资，因为只有两名员工
   T185 
   */
select t.Department,
  t.Employee,
  t.Salary
from(
    select a.name as Department,
      b.name as Employee,
      dense_rank() over(
        partition by a.name
        order by b.Salary desc
      ) as p,
      b.Salary
    from Department a
      join Employee b on a.id = b.departmentId
  ) as t
where t.p <= 3
  /* 
   
   表： Users
   
   +----------------+---------+
   | Column Name    | Type    |
   +----------------+---------+
   | user_id        | int     |
   | name           | varchar |
   +----------------+---------+
   user_id 是该表的主键。
   该表包含用户的 ID 和名字。名字仅由小写和大写字符组成。
   
   
   
   编写一个 SQL 查询来修复名字，使得只有第一个字符是大写的，其余都是小写的。
   
   返回按 user_id 排序的结果表。
   
   查询结果格式示例如下。
   
   
   
   示例 1：
   
   输入：
   Users table:
   +---------+-------+
   | user_id | name  |
   +---------+-------+
   | 1       | aLice |
   | 2       | bOB   |
   +---------+-------+
   输出：
   +---------+-------+
   | user_id | name  |
   +---------+-------+
   | 1       | Alice |
   | 2       | Bob   |
   +---------+-------+
   T1667
   */
select user_id,
  concat(
    upper(substring(name, 1, 1)),
    lower(substring(name, 2))
  ) as name
from Users
order by user_id
  /* 
   用户表： Users
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | user_id       | int     |
   | name          | varchar |
   | mail          | varchar | 
   +---------------+---------+
   user_id （用户 ID）是该表的主键。
   这个表包含用户在某网站上注册的信息。有些邮箱是无效的。
   
   写一条 SQL 语句，查询拥有有效邮箱的用户。
   
   有效的邮箱包含符合下列条件的前缀名和域名：
   前缀名是包含字母（大写或小写）、数字、下划线 '_'、句点 '.' 和/或横杠 '-' 的字符串。前缀名必须以字母开头。
   域名是 '@leetcode.com' 。
   
   按任意顺序返回结果表。
   
   查询格式如下所示：
   
   Users
   +---------+-----------+-------------------------+
   | user_id | name      | mail                    |
   +---------+-----------+-------------------------+
   | 1       | Winston   | winston@leetcode.com    |
   | 2       | Jonathan  | jonathanisgreat         |
   | 3       | Annabelle | bella-@leetcode.com     |
   | 4       | Sally     | sally.come@leetcode.com |
   | 5       | Marwan    | quarz#2020@leetcode.com |
   | 6       | David     | david69@gmail.com       |
   | 7       | Shapiro   | .shapo@leetcode.com     |
   +---------+-----------+-------------------------+
   
   结果表：
   +---------+-----------+-------------------------+
   | user_id | name      | mail                    |
   +---------+-----------+-------------------------+
   | 1       | Winston   | winston@leetcode.com    |
   | 3       | Annabelle | bella-@leetcode.com     |
   | 4       | Sally     | sally.come@leetcode.com |
   +---------+-----------+-------------------------+
   2 号用户的邮箱没有域名。
   5 号用户的邮箱包含非法字符 #。
   6 号用户的邮箱的域名不是 leetcode。
   7 号用户的邮箱以句点（.）开头。
   */
  /*
   mysql 转义是 \\ 
   */
select *
from Users
where mail regexp '^[a-z|A-Z][a-z|A-Z|0-9|_|\\.|-]*@leetcode\\.com$'
  /* 
   | user_id | name     | mail                         |
   | ------- | -------- | ---------------------------- |
   | 48      | Aharon   | AharonDWUbN@leetcode.com     |
   | 474     | Tamar    | TamarWQ@leetcode.com         |
   | 275     | Moshe    | Moshepk@leetcode.com         |
   | 414     | Tikvah   | Tikvah3jX3@leetcode.com      |
   | 857     | Aharon   | Aharon._x@leetcode.com       |
   | 696     | Yosef    | Yosef73@leetcode.com         |
   | 919     | Meir     | MeirVy@leetcode.com          |
   | 760     | Refael   | Refael_.jTx7@leetcode.com    |
   | 949     | Michael  | Michael.-y1ta@leetcode.com   |
   | 651     | Yosef    | Yosef_.IcOwJEM@leetcode.com  |
   | 94      | Yehudah  | Yehudah3I3EUx@leetcode.com   |
   | 650     | Yaakov   | Yaakov_-ruLe994@leetcode.com |
   | 674     | Gavriel  | Gavriel--8h2JAq@leetcode.com |
   | 246     | Benjamin | Benjamini2@leetcode.com      |
   | 843     | Zahava   | ZahavaOHfi@leetcode.com      |
   | 840     | Levi     | Levi9tiG@leetcode.com        |
   | 341     | Shimon   | ShimonFP@leetcode.com        |
   | 926     | Tamar    | Tamar-_Czy99@leetcode.com    |
   | 662     | Daniel   | DanielF@leetcode.com         |
   | 994     | Yehudah  | Yehudah4MuB@leetcode.com     |
   | 30      | Refael   | Refaeld@leetcode.com         |
   | 878     | Freida   | FreidaZlXf@leetcode.com      |
   | 637     | Levi     | Leviuo@leetcode.com          |
   */
  /* 
   | user_id | name     | mail                         |
   | ------- | -------- | ---------------------------- |
   | 48      | Aharon   | AharonDWUbN@leetcode.com     |
   | 474     | Tamar    | TamarWQ@leetcode.com         |
   | 275     | Moshe    | Moshepk@leetcode.com         |
   | 414     | Tikvah   | Tikvah3jX3@leetcode.com      |
   | 999     | Meir     | Meiry0@leetcode.com          |
   | 857     | Aharon   | Aharon._x@leetcode.com       |
   | 696     | Yosef    | Yosef73@leetcode.com         |
   | 317     | Moshe    | MoshehX0p@leetcode.com       |
   | 881     | Yosef    | YosefnSJtf0@leetcode.com     |
   | 919     | Meir     | MeirVy@leetcode.com          |
   | 760     | Refael   | Refael_.jTx7@leetcode.com    |
   | 949     | Michael  | Michael.-y1ta@leetcode.com   |
   | 651     | Yosef    | Yosef_.IcOwJEM@leetcode.com  |
   | 94      | Yehudah  | Yehudah3I3EUx@leetcode.com   |
   | 650     | Yaakov   | Yaakov_-ruLe994@leetcode.com |
   | 674     | Gavriel  | Gavriel--8h2JAq@leetcode.com |
   | 246     | Benjamin | Benjamini2@leetcode.com      |
   | 843     | Zahava   | ZahavaOHfi@leetcode.com      |
   | 840     | Levi     | Levi9tiG@leetcode.com        |
   | 341     | Shimon   | ShimonFP@leetcode.com        |
   | 926     | Tamar    | Tamar-_Czy99@leetcode.com    |
   | 662     | Daniel   | DanielF@leetcode.com         |
   | 994     | Yehudah  | Yehudah4MuB@leetcode.com     |
   | 30      | Refael   | Refaeld@leetcode.com         |
   | 878     | Freida   | FreidaZlXf@leetcode.com      |
   | 637     | Levi     | Leviuo@leetcode.com          |
   */
  /* 
   表: Products
   
   +------------------+---------+
   | Column Name      | Type    |
   +------------------+---------+
   | product_id       | int     |
   | product_name     | varchar |
   | product_category | varchar |
   +------------------+---------+
   product_id 是该表主键。
   该表包含该公司产品的数据。
   
   
   
   表: Orders
   
   +---------------+---------+
   | Column Name   | Type    |
   +---------------+---------+
   | product_id    | int     |
   | order_date    | date    |
   | unit          | int     |
   +---------------+---------+
   该表无主键，可能包含重复行。
   product_id 是表单 Products 的外键。
   unit 是在日期 order_date 内下单产品的数目。
   
   
   
   写一个 SQL 语句，要求获取在 2020 年 2 月份下单的数量不少于 100 的产品的名字和数目。
   
   返回结果表单的 顺序无要求 。
   
   查询结果的格式如下。
   
   
   
   示例 1:
   
   输入：
   Products 表:
   +-------------+-----------------------+------------------+
   | product_id  | product_name          | product_category |
   +-------------+-----------------------+------------------+
   | 1           | Leetcode Solutions    | Book             |
   | 2           | Jewels of Stringology | Book             |
   | 3           | HP                    | Laptop           |
   | 4           | Lenovo                | Laptop           |
   | 5           | Leetcode Kit          | T-shirt          |
   +-------------+-----------------------+------------------+
   Orders 表:
   +--------------+--------------+----------+
   | product_id   | order_date   | unit     |
   +--------------+--------------+----------+
   | 1            | 2020-02-05   | 60       |
   | 1            | 2020-02-10   | 70       |
   | 2            | 2020-01-18   | 30       |
   | 2            | 2020-02-11   | 80       |
   | 3            | 2020-02-17   | 2        |
   | 3            | 2020-02-24   | 3        |
   | 4            | 2020-03-01   | 20       |
   | 4            | 2020-03-04   | 30       |
   | 4            | 2020-03-04   | 60       |
   | 5            | 2020-02-25   | 50       |
   | 5            | 2020-02-27   | 50       |
   | 5            | 2020-03-01   | 50       |
   +--------------+--------------+----------+
   输出：
   +--------------------+---------+
   | product_name       | unit    |
   +--------------------+---------+
   | Leetcode Solutions | 130     |
   | Leetcode Kit       | 100     |
   +--------------------+---------+
   解释：
   2020 年 2 月份下单 product_id = 1 的产品的数目总和为 (60 + 70) = 130 。
   2020 年 2 月份下单 product_id = 2 的产品的数目总和为 80 。
   2020 年 2 月份下单 product_id = 3 的产品的数目总和为 (2 + 3) = 5 。
   2020 年 2 月份 product_id = 4 的产品并没有下单。
   2020 年 2 月份下单 product_id = 5 的产品的数目总和为 (50 + 50) = 100 。
   T1327
   */
select *
from (
    select product_name,
      sum(b.unit) as unit
    from Products a
      join Orders b on a.product_id = b.product_id
      and b.order_date >= '2020-02-01'
      and b.order_date < '2020-03-01'
    group by a.product_name
  ) t
where t.unit >= 100
  /* 
   表 Activities：
   
   +-------------+---------+
   | 列名         | 类型    |
   +-------------+---------+
   | sell_date   | date    |
   | product     | varchar |
   +-------------+---------+
   此表没有主键，它可能包含重复项。
   此表的每一行都包含产品名称和在市场上销售的日期。
   
   
   
   编写一个 SQL 查询来查找每个日期、销售的不同产品的数量及其名称。
   每个日期的销售产品名称应按词典序排列。
   返回按 sell_date 排序的结果表。
   查询结果格式如下例所示。
   
   
   
   示例 1:
   
   输入：
   Activities 表：
   +------------+-------------+
   | sell_date  | product     |
   +------------+-------------+
   | 2020-05-30 | Headphone   |
   | 2020-06-01 | Pencil      |
   | 2020-06-02 | Mask        |
   | 2020-05-30 | Basketball  |
   | 2020-06-01 | Bible       |
   | 2020-06-02 | Mask        |
   | 2020-05-30 | T-Shirt     |
   +------------+-------------+
   输出：
   +------------+----------+------------------------------+
   | sell_date  | num_sold | products                     |
   +------------+----------+------------------------------+
   | 2020-05-30 | 3        | Basketball,Headphone,T-shirt |
   | 2020-06-01 | 2        | Bible,Pencil                 |
   | 2020-06-02 | 1        | Mask                         |
   +------------+----------+------------------------------+
   解释：
   对于2020-05-30，出售的物品是 (Headphone, Basketball, T-shirt)，按词典序排列，并用逗号 ',' 分隔。
   对于2020-06-01，出售的物品是 (Pencil, Bible)，按词典序排列，并用逗号分隔。
   对于2020-06-02，出售的物品是 (Mask)，只需返回该物品名。
   T1484
   */
select sell_date,
  count(distinct(product)) as num_sold,
  group_concat(
    distinct product
    order by product separator ','
  ) as products
from Activities
group by sell_date
order by sell_date
  /* 
   Employee 表：
   
   +-------------+------+
   | Column Name | Type |
   +-------------+------+
   | id          | int  |
   | salary      | int  |
   +-------------+------+
   id 是这个表的主键。
   表的每一行包含员工的工资信息。
   
   
   
   编写一个 SQL 查询，获取并返回 Employee 表中第二高的薪水 。如果不存在第二高的薪水，查询应该返回 null 。
   
   查询结果如下例所示。
   
   
   
   示例 1：
   
   输入：
   Employee 表：
   +----+--------+
   | id | salary |
   +----+--------+
   | 1  | 100    |
   | 2  | 200    |
   | 3  | 300    |
   +----+--------+
   输出：
   +---------------------+
   | SecondHighestSalary |
   +---------------------+
   | 200                 |
   +---------------------+
   
   示例 2：
   
   输入：
   Employee 表：
   +----+--------+
   | id | salary |
   +----+--------+
   | 1  | 100    |
   +----+--------+
   输出：
   +---------------------+
   | SecondHighestSalary |
   +---------------------+
   | null                |
   +---------------------+
   
   T176
   */
select ifnull(
    (
      select t.salary
      from(
          select id,
            dense_rank() over(
              order by salary desc
            ) as a,
            salary
          from Employee
        ) as t
      where t.a = 2
      limit 1
    ), null
  ) as SecondHighestSalary
  /* 
   表: Person
   
   +-------------+---------+
   | Column Name | Type    |
   +-------------+---------+
   | id          | int     |
   | email       | varchar |
   +-------------+---------+
   id是该表的主键列。
   该表的每一行包含一封电子邮件。电子邮件将不包含大写字母。
   
   编写一个 SQL 删除语句来 删除 所有重复的电子邮件，只保留一个id最小的唯一电子邮件。
   以 任意顺序 返回结果表。 （注意： 仅需要写删除语句，将自动对剩余结果进行查询）
   
   查询结果格式如下所示。
   示例 1:
   
   输入: 
   Person 表:
   +----+------------------+
   | id | email            |
   +----+------------------+
   | 1  | john@example.com |
   | 2  | bob@example.com  |
   | 3  | john@example.com |
   +----+------------------+
   输出: 
   +----+------------------+
   | id | email            |
   +----+------------------+
   | 1  | john@example.com |
   | 2  | bob@example.com  |
   +----+------------------+
   解释: john@example.com重复两次。我们保留最小的Id = 1。
   
   T196
   */
delete from Person
where id not in(
    select id
    from (
        select min(id) as id
        from Person
        group by email
      ) t
  )
  /* 
   患者信息表： Patients
   
   +--------------+---------+
   | Column Name  | Type    |
   +--------------+---------+
   | patient_id   | int     |
   | patient_name | varchar |
   | conditions   | varchar |
   +--------------+---------+
   patient_id （患者 ID）是该表的主键。
   'conditions' （疾病）包含 0 个或以上的疾病代码，以空格分隔。
   这个表包含医院中患者的信息。
   写一条 SQL 语句，查询患有 I 类糖尿病的患者 ID （patient_id）、患者姓名（patient_name）以及其患有的所有疾病代码（conditions）。
   I 类糖尿病的代码总是包含前缀 DIAB1 。
   
   按 任意顺序 返回结果表。
   
   查询结果格式如下示例所示。
   示例 1:
   输入：
   Patients表：
   +------------+--------------+--------------+
   | patient_id | patient_name | conditions   |
   +------------+--------------+--------------+
   | 1          | Daniel       | YFEV COUGH   |
   | 2          | Alice        |              |
   | 3          | Bob          | DIAB100 MYOP |
   | 4          | George       | ACNE DIAB100 |
   | 5          | Alain        | DIAB201      |
   +------------+--------------+--------------+
   输出：
   +------------+--------------+--------------+
   | patient_id | patient_name | conditions   |
   +------------+--------------+--------------+
   | 3          | Bob          | DIAB100 MYOP |
   | 4          | George       | ACNE DIAB100 | 
   +------------+--------------+--------------+
   解释：Bob 和 George 都患有代码以 DIAB1 开头的疾病。
   
   T1527
   */
select *
from Patients
where conditions regexp '.* DIAB1.*|^DIAB1.*'