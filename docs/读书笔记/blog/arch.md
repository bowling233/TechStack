# 系统架构类

## 可观测性

### [Unified Logging Layer: Turning Data into Action - Fluentd](https://www.fluentd.org/blog/unified-logging-layer)

- 传统日志基础设施并不是为机器设计的。十年前（2004 年）人是日志的主要消费者，而现在机器是。现存的日志格式结构性很弱，日志的生产者也很少对格式进行思考。
- 写复杂的正则表达式来解析日志是必备的能力。
- fluentd 提出 Unified Logging Layer，在日志的生产者和消费者之间定义统一的接口。
- 在定义接口时，fluentd 考虑了以下方面：
    - 灵活性。JSON 是灵活的，而 protobuf（来自谷歌）等是比较死板的。
    - 普遍性（数据库后端的支持）。JSON 被广泛支持，而二进制协议很少得到普遍支持。
    - 需要可伸缩性、可重试的数据传输，确保日志不会丢失。
- 统一日志层需要支持多种输入输出。设计时，统一日志层设计为可插拔架构。这样的架构将系统的复杂度从 $O(mn)$ 降低到 $O(m+n)$。
