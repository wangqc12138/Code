# KAFKA

## 数据结构
```c++
// kafka处理句柄结构，分为生产者和消费者，由rd_kafka_new第一参数决定，其中包含rk_brokers链表，rk_topics链表
typedef struct rd_kafka_s rd_kafka_t;
typedef struct rd_kafka_topic_s rd_kafka_topic_t;
// kafka全局配置，通过rd_kafka_conf_new创建，通过rd_kafka_conf_set配置，是rd_kafka_new函数创建处理句柄的第二个参数
typedef struct rd_kafka_conf_s rd_kafka_conf_t;
rd_kafka_conf_t *rd_kafka_conf_new(void);
// kafka主题配置，通过rd_kafka_topic_conf_new创建，通过rd_kafka_topic_conf_set设置参数
typedef struct rd_kafka_topic_conf_s rd_kafka_topic_conf_t;
typedef struct rd_kafka_queue_s rd_kafka_queue_t;
```

---
## 接口说明
```c++
// 创建一个kafka全局配置结构，并进行默认初始化设置，返回rd_kafka_conf_t引用指针
rd_kafka_conf_t *rd_kafka_conf_new(void)
// 设置全局配置结构
// conf全局配置结构
// name配置项名称
// value配置项值
// errstr错误提示
// errstr_size错误提示长度
// 调用这个函数后再调用rd_kafka_conf_set_default_topic_conf()会将之前设置的值全部用默认值覆盖掉
rd_kafka_conf_res_t rd_kafka_conf_set(rd_kafka_conf_t *conf, const char *name, const char *value, char *errstr, size_t errstr_size)
// 创建一个kafka主题配置结构，并进行默认初始化设置，返回rd_kafka_topic_conf_t引用指针
rd_kafka_topic_conf_t *rd_kafka_topic_conf_new (void)
// 设置主题配置
// 参数配置同上
rd_kafka_conf_res_t rd_kafka_topic_conf_set (rd_kafka_topic_conf_t *conf, const char *name, const char *value, char *errstr, size_t errstr_size)
// 创建一个生产者或者消费者
// type RD_KAFKA_PRODUCER生产者 RD_KAFKA_CONSUMER消费者
// app_conf 配置结构
// 成功返回rd_kafka_t* 操作句柄 失败返回NULL
rd_kafka_t *rd_kafka_new (rd_kafka_type_t type, rd_kafka_conf_t *app_conf, char *errstr, size_t errstr_size)
// 销毁操作句柄
// rk待释放的操作句柄
void rd_kafka_destroy (rd_kafka_t *rk)
// 创建一个主题操作句柄
// rk kafka操作句柄 topic主题内容？ conf主题配置
rd_kafka_topic_t *rd_kafka_topic_new (rd_kafka_t *rk, const char *topic,  rd_kafka_topic_conf_t *conf)
// 主题销毁句柄
// app_rkt 待释放的主题句柄
void rd_kafka_topic_destroy (rd_kafka_topic_t *app_rkt)
// 发送消息？rd_kafka_producev
// rkt kafka主题操作句柄
// partition 分区号
// msgflags 消息标志，使用RD_KAFKA_MSG_F_COPY标志？
// playload 消息体指针
// len 消息体长度
// key 消息选项key值，用作平衡分区，计算分区号的，填NULL
// keylen key长度 填0
// msg_opaque 是作为回调函数的参数，填NULL
int rd_kafka_produce (rd_kafka_topic_t *rkt, int32_t partition, int msgflags, void *payload, size_t len, const void *key, size_t keylen,  void *msg_opaque)
// Rk:kafka操作句柄
// timeout_ms：毫秒级时间
// 返回值：处理的事件数
// 发送完消息后调用此接口，timeout_ms是毫秒级的时间，函数会阻塞timeout_ms 毫秒等待事件处理，调用设置的回调函数。timeout_ms为0是非阻塞状态。
int rd_kafka_poll(rd_kafka_t *rk, int timeout_ms)
// Rk：kafka操作句柄
// timeout_ms：毫秒级时间
// 成功：RD_KAFKA_RESP_ERR_NO_ERROR
// 失败：RD_KAFKA_RESP_ERR_TIMED_OUT
// 在摧毁生产者之前调用此接口，确保正在排队和正在进行的消息被处理完成。此函数会调用rd_kafka_poll()并触发回调。
rd_kafka_resp_err_t rd_kafka_flush (rd_kafka_t *rk, int timeout_ms)
// Rk：kafka操作句柄
// Brokerlist：broker字符串 如:”172.20.51.38:9092” 不写端口，则采用默认端口9092 多个broker  brokerlist = "broker1:10000,broker2"
// 返回值：成功添加的broker个数
// 添加一个broker也可以通过 设置rd_kafka_conf_t结构中的 "bootstrap.servers" 配置项
// rd_kafka_conf_set(conf, "bootstrap.servers", brokers, errstr, sizeof(errstr))
int rd_kafka_brokers_add (rd_kafka_t *rk, const char *brokerlist) 
// Rk：kafka操作句柄
// 返回值：rd_kafka_resp_err_t 枚举
// 将消息重定向到了消费者队列，可以使用rd_kafka_consumer_poll()进行取消息。
rd_kafka_resp_err_t rd_kafka_poll_set_consumer (rd_kafka_t *rk)
```