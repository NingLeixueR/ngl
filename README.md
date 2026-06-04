# NGL 框架客观分析报告

> 本文基于当前仓库代码、构建配置、测试用例、部署脚本和已有技术文档整理，用于在私有仓库不可公开的情况下，向面试官或新团队客观介绍 `ngl_server` / NGL 框架的设计思路、工程能力、技术边界和可改进方向。

## 1. 框架定位

`ngl_server` 是一个面向游戏服务端场景的 C++ Actor 模型服务器框架。它的核心目标不是做单一业务 Demo，而是提供一套可扩展的游戏后端运行时，包括：

- 多节点服务启动与节点类型装配
- Actor 驱动的业务模块组织方式
- TCP、WebSocket、KCP/UDP 等多传输协议接入
- Protobuf、自定义协议、XML、CSV 等配置与协议体系
- MySQL、PostgreSQL、Redis 等数据后端封装
- 网关转发、跨节点 Actor 通信、客户端消息路由
- GM/运营后台、Docker 发布、Windows 本地启动脚本
- GoogleTest 回归测试与性能测试入口

从代码结构看，NGL 更接近“中小型 MMO / 在线游戏服务端基础框架”，而不是普通 Web 服务框架。它关注的是长连接、低延迟消息投递、角色 Actor 生命周期、分服分区、网关转发、配置热更新、排行榜、邮件、聊天、活动、家族、背包、任务等游戏服务端常见问题。

## 2. 技术栈与工程基础

### 2.1 语言与构建

项目使用 C++23，构建系统为 CMake，依赖管理使用 Conan 2。根目录 `CMakeLists.txt` 中定义了若干关键构建选项：

- `NGL_ENABLE_STRONG_WARNINGS`：增强编译告警
- `NGL_ENABLE_SANITIZERS`：支持 AddressSanitizer / UndefinedBehaviorSanitizer
- `NGL_ENABLE_NATIVE_UNITY_BUILD`：支持 CMake 原生 unity build，加快大型目标构建
- `NGL_ENABLE_MIMALLOC`：可启用 mimalloc 作为可执行目标的内存分配器
- `NGLCORE_BUILD_SHARED`：支持将核心库构建为静态库或动态库
- `BUILD_TESTING`：控制测试目标构建
- `NGL_TEST_REGISTER_PERF`：控制性能测试是否注册到 CTest

依赖通过 `conanfile.py` 管理，主要包括：

| 依赖 | 作用 |
|------|------|
| Boost 1.86 | Asio、program_options、基础设施 |
| behaviortree.cpp 4.9 | 行为树 / AI 相关能力 |
| tinyxml2 | XML 配置解析 |
| Lua 5.4 | 脚本扩展 |
| Protobuf 3.21 | 网络协议与数据结构序列化 |
| libcurl | HTTP/外部接口能力 |
| libmysqlclient | MySQL 数据库接入 |
| hiredis | Redis 接入 |
| libpq | PostgreSQL 接入 |
| rapidjson | JSON 处理 |
| mimalloc | 内存分配优化 |
| GoogleTest | 单元测试与回归测试 |
| SDL / ImGui | Windows 本地 Demo / 工具侧能力 |

仓库中还内置了 KCP 和 utf8cpp 等第三方源码。

### 2.2 目标组织

项目主要目标分为：

- `nglcore`：核心运行时库，聚合 `server/libnglcore/core` 与 `public/cpp` 下的大量公共 C++ 源码。
- `node`：服务进程入口，命令行格式为 `<node_name> <area> <tcount> [extra args...]`。
- `ngl_test`：GoogleTest 测试目标。
- `tools/idl`、`tools/makeproto`、`tools/rebuild`、`tools/map_editor`：本地开发工具与生成链路。
- `demo`：Windows 本地 Demo 和 Cocos Creator 客户端示例。

这种组织方式的优点是核心运行时、进程入口、工具链、测试之间边界相对清楚。运行时逻辑集中在 `nglcore`，进程入口只负责参数校验、异常 dump 和调用 `ngl_main`。

## 3. 目录结构分析

当前仓库大致可以分为以下几层：

| 目录 | 职责 |
|------|------|
| `public/cpp/actor` | Actor 基础设施、业务 Actor、协议注册、生成代码 |
| `public/cpp/net` | TCP、WebSocket、KCP、会话管理、统一网络门面 |
| `public/cpp/tools` | 序列化、日志、配置、CSV/XML、数据库、Lua、通用工具 |
| `public/cpp/third_party` | 内嵌 KCP、utf8cpp 等第三方代码 |
| `server/libnglcore` | 服务端启动、节点装配、运行时核心库 |
| `server/node` | 服务进程入口 |
| `server/tests` | GoogleTest 测试集合 |
| `server/tools` | IDL、协议生成、本地维护工具 |
| `server/demo` | Demo 与客户端样例 |
| `bin/configure` | 运行配置、CSV、XML、脚本和启动批处理 |
| `admin` | PHP GM/运营后台 |
| `deploy/docker` | Dockerfile、Compose、容器启动脚本 |
| `doc` | 架构文档、模块文档、部署与优化方案 |

从工程成熟度看，项目不是单纯代码堆积，已经具备文档化、测试化、构建选项、CI、Docker 发布和运维后台等配套。

## 4. 运行时启动与节点模型

### 4.1 统一入口

服务进程入口位于 `server/node/core/main.cpp`。它做了三件关键事情：

1. Windows 下设置控制台 UTF-8 输出。
2. 校验启动参数是否满足 `<node_name> <area> <tcount>`。
3. 设置 dump 处理器后进入 `ngl_main`。

真正的启动逻辑位于 `server/libnglcore/core/bootstrap/server_main.cpp`。该文件先构建 `start_ctx`，完成：

- 解析节点名称、区服 ID、线程编号
- 根据节点名称解析节点类型
- 加载 `./config/config.xml`
- 设置 CSV 路径为 `./config/csv`
- 从 `tab_servers.csv` 中查找当前节点对应的服务器配置
- 解析 TCP 监听端口
- 设置 `nconfig` 中的 node id、area、server name 等运行时信息

### 4.2 节点类型

启动时根据 `nconfig.nodetype()` 分发到不同节点装配函数：

| 节点类型 | 启动函数 | 典型职责 |
|----------|----------|----------|
| DB | `start_db` | 数据库 Actor 节点 |
| GAME | `start_game` | 游戏逻辑节点 |
| ACTOR | `start_actor` | Actor 服务节点 |
| LOG | `start_log` | 日志节点 |
| GATEWAY | `start_gateway` | 客户端网关节点 |
| LOGIN | `start_login` | 登录节点 |
| WORLD | `start_world` | 世界/全局管理节点 |
| RELOADCSV | `start_csvserver` | 配置热更新节点 |
| ROBOT | `start_robot` | 机器人/压测节点 |
| CROSS | `start_cross` | 跨服节点 |
| CROSSDB | `start_crossdb` | 跨服数据库节点 |
| PUSHSERVERCONFIG | `start_pushcfg` | 推送服务器配置节点 |

这种设计体现了游戏服务端常见的“多进程、多节点、多区服”模型。不同节点运行同一个 `node` 可执行文件，但通过启动参数和配置装配不同的 Actor 集合与网络端口。

### 4.3 评价

优点：

- 节点启动路径统一，新增节点类型有明确扩展点。
- 节点配置来自 XML + CSV，适合分服、多节点部署。
- 启动失败有结构化错误码和上下文日志，便于排查。
- Docker 中可以用同一个镜像启动不同节点。

不足：

- 当前主循环是无限 sleep，缺少完整优雅退出流程。
- 部分线程模型明确采用“进程生命周期内不销毁”的策略，适合游戏长驻进程，但对服务停止、热重启和资源释放的严谨性要求更高。
- 节点发现仍主要依赖静态配置表，动态服务发现和配置中心能力有限。

## 5. Actor 系统分析

Actor 模型是 NGL 的核心。项目中登录、聊天、邮件、排行榜、网关、角色、活动、家族、机器人、GM、KCP 等业务都被组织为 Actor。

### 5.1 Actor 标识

每个 Actor 使用 64 位 `nguid` 标识，结构大致为：

```text
| 16 bit type | 16 bit area | 32 bit dataid |
```

字段含义：

- `type`：Actor 类型，例如 Role、Chat、Gateway、Login 等。
- `area`：区服 / 分区 ID。
- `dataid`：实例 ID，例如角色 ID。

这种设计的好处是 Actor ID 本身携带路由信息，可以支持：

- 单例 Actor 寻址
- 动态 Actor 寻址
- 按 Actor 类型广播
- 按区服隔离
- 跨节点消息转发

### 5.2 Actor 继承与职责

核心继承关系为：

```text
actor_base
  -> actor
      -> 具体业务 Actor
```

`actor_base` 主要负责：

- Actor 身份与配置
- 生命周期钩子
- `send_actor`、`send_server`、`send_client` 等消息发送接口
- 数据库组件管理
- Lua 脚本运行时绑定
- 定时器注册

`actor` 在此基础上增加：

- 普通消息队列
- 高优先级消息队列
- 每次调度的权重限制
- 单次调度的软时间预算
- 消息处理函数分发表
- 广播 tick 处理
- 队列积压告警

### 5.3 分层调度

Actor 调度由 `actor_manage` 和 `schedule_layer` 组成。`actor_manage` 是全局路由入口，内部固定包含 8 个 `schedule_layer`。

分层规则：

- 单例 Actor：按 Actor type 做位掩码分层。
- 动态 Actor：按 dataid 做位掩码分层。

这样做的目标是避免同一类动态 Actor 全部集中到一个调度层上，提升并行度。

每个 `schedule_layer` 有：

- 自己的 Actor 查找表
- 自己的就绪队列
- 自己的调度线程
- 自己的锁

工作线程池由 `actor_manage` 统一维护，调度层从共享池中获取空闲工作线程处理就绪 Actor。

### 5.4 消息处理流程

典型流程为：

```text
send_actor / 网络接收
  -> handle_pram 构造消息信封
  -> actor_manage::push_task_id
  -> 根据 nguid 路由到 schedule_layer
  -> 消息进入目标 Actor 队列
  -> Actor 从空闲状态进入就绪队列
  -> 调度线程获取工作线程
  -> 工作线程执行 actor_handle
  -> 先处理高优先级队列，再处理普通队列
  -> 未处理完则重新进入就绪队列
```

### 5.5 高优先级消息

框架在协议注册表中为消息维护 `m_highvalue` 字段。值越小优先级越高，0 表示普通消息。Actor 处理时会先排空高优先级队列，再按权重和时间预算处理普通队列。

这对游戏服务端有实际意义：

- 登录、断线、网关状态、关键控制类消息可以优先处理。
- 大量普通业务消息积压时，关键系统消息仍有机会更快被调度。
- 配合队列积压告警可以定位慢 Actor 或异常流量。

### 5.6 Actor 体系评价

优点：

- Actor 边界清晰，业务模块之间通过消息通信，减少共享状态。
- 通过 64 位 ID 把类型、区服、实例编码进路由标识，适合游戏分服模型。
- 分层调度降低单锁竞争，工作线程池共享能控制线程总量。
- 高优先级消息机制解决关键消息被普通消息淹没的问题。
- Actor 与 DB 组件、脚本、定时器、广播 tick 结合较完整。

不足：

- 调度模型较复杂，对维护者理解成本较高。
- 线程生命周期采用进程常驻策略，缺少完整 stop token / join / drain 机制。
- 高优先级消息如果使用不当，可能造成普通消息饥饿，需要有清晰的协议优先级规范。
- Actor 队列、调度耗时、延迟分布如果缺少持续监控，线上问题定位会比较依赖日志。

## 6. 协议与消息系统

### 6.1 协议注册

协议系统核心为 `tprotocol`，维护：

- C++ 类型 hash 到协议信息的映射
- 协议号到协议信息的映射
- 名称到协议信息的映射

协议来源包括：

- 自定义 C++ 协议
- Protobuf 协议
- XML 协议元数据
- 生成代码中的自动注册逻辑

每个协议不仅有 ID 和名称，还可以携带调度优先级、脚本桥接等信息。

### 6.2 消息信封

`handle_pram` 是类型擦除后的消息信封，承载：

- 协议 ID
- 类型化消息数据
- 原始网络包
- 目标 Actor
- 请求来源 Actor
- 批量投递目标集合
- 跨节点转发回调
- 按 Actor 类型广播标记

这种设计让本地 Actor 消息、跨节点消息、客户端转发消息都能走统一分发路径。

### 6.3 处理函数注册

Actor 的处理函数通过 `nrfun<T>` 进行类型化注册。常见注册方式包括：

- 普通网络可见消息处理
- 仅本地消息处理
- 客户端到网关 C2G 转发
- 网关到客户端 G2C 转发
- 二跳转发，例如客户端 -> 网关 -> 角色 Actor -> 聊天 Actor

这套机制减少了手写 switch-case 分发，也让协议到 Actor handler 的关系更加显式。

### 6.4 评价

优点：

- 协议 ID、类型、名称和优先级统一管理。
- 类型化 handler 降低反序列化后误用风险。
- 支持本地消息、跨节点消息、客户端转发消息复用同一套 Actor 分发框架。
- 二跳转发机制适合网关、角色、公共服务之间的业务路由。

不足：

- 类型擦除、模板注册、生成代码、协议 XML 同时存在，对新成员上手有门槛。
- 协议生成链路需要稳定文档和自动化，否则容易出现“改协议但漏生成/漏注册”的问题。
- 协议优先级应有治理规范，否则后期不同业务会争抢高优先级。

## 7. 网络层分析

网络层统一封装在 `nnet` 门面后，底层支持三类传输：

| 传输 | 类 | 使用场景 |
|------|----|----------|
| TCP | `ntcp` | 服务器间通信、传统客户端连接 |
| WebSocket / WSS | `nws` | 浏览器客户端、Cocos Web 环境 |
| KCP / UDP | `ukcp` / `nkcp` | 低延迟实时通信 |

### 7.1 TCP

TCP 传输基于 Boost.Asio，包含：

- acceptor 与 session 管理
- 出站连接与重连
- 服务器 ID 到 session 的映射
- 每 socket 工作线程对应的 `segpack`
- 出站 pack 的缓冲池

接收路径中，原始字节先经过 `segpack` 进行粘包/拆包处理，再进入协议分发系统。

### 7.2 WebSocket

WebSocket 复用 TCP 基础设施，但增加帧封装，适合浏览器环境。它提供与 TCP 类似的 send 接口，降低业务层感知。

### 7.3 KCP

KCP 通道用于 UDP 低延迟场景。会话创建通过网关消息协商：

```text
客户端请求 KCP session
  -> 网关生成会话信息
  -> 转发给 KCP Actor
  -> KCP 端点建立
  -> 返回 session key
  -> 客户端建立 UDP/KCP 通道
```

### 7.4 包格式与保护机制

网络包 `pack` 包含：

- 传输协议类型
- session id
- 包头
- 协议号
- Actor ID
- 包体长度
- 包体缓冲
- 缓冲池反向指针

框架还支持：

- 心跳包本地消费
- Telnet 命令检测
- XOR 简单混淆
- Varint 编码
- 每 socket 消息限速
- 断线清理

### 7.5 评价

优点：

- TCP、WebSocket、KCP 统一接入 Actor 分发系统。
- `nnet` 门面降低业务层对传输细节的依赖。
- `segpack` 和 pack 池体现了对长连接流式协议的实际处理。
- KCP 支持使框架能覆盖更实时的游戏流量。

不足：

- XOR 只能作为简单混淆，不能视为安全加密。
- 网络限速和异常连接治理需要和线上指标结合，否则只能被动关闭。
- WebSocket、TCP、KCP 三套路径需要长期保持协议一致性，测试覆盖必须持续跟进。

## 8. 数据库层分析

NGL 的数据库层采用“业务 Actor 不直接访问数据库，而是通过 DB Actor 通信”的方式。

### 8.1 组件模型

整体结构为：

```text
Actor
  -> nmanage_dbclient
      -> ndbclient<DBTYPE, TDBTAB, TACTOR>
          -> data_modified<T>
```

每个 Actor 可以管理多个 DB client，每个 DB client 对应一类表数据。

### 8.2 数据加载与保存

典型生命周期：

1. Actor 初始化 DB 组件。
2. DB client 向 DB Actor 发送加载请求。
3. DB Actor 返回数据，可能分块返回。
4. 加载完成后通知宿主 Actor。
5. 业务运行中修改数据，行级脏标记被记录。
6. 广播 tick 或 Actor 释放时批量保存脏数据、删除待删数据。

### 8.3 脏标记机制

`data_modified<T>` 和 `nmodified<T>` 用于行级变更跟踪。可变访问会标记脏数据，只读访问不会标记。这有利于减少无意义写库。

### 8.4 数据库后端

框架包含：

- MySQL 管理类与连接池
- PostgreSQL 管理类与连接池
- Redis 封装

这说明它不是只针对单一数据库实现，而是尝试抽象多种持久化后端。

### 8.5 评价

优点：

- DB 访问通过 Actor 异步化，避免业务 Actor 直接阻塞在数据库 IO 上。
- 脏标记和批量刷盘适合游戏角色数据保存。
- DB 组件挂在 Actor 上，和角色、家族、排行榜等业务模型契合。
- 支持多数据库后端，扩展性较好。

不足：

- 批量刷盘策略需要关注崩溃时的数据丢失窗口。
- 强一致性事务、跨 Actor 事务、跨表原子性不是当前设计重点。
- DB Actor、连接池、业务 Actor 之间的失败重试、幂等和回滚策略需要进一步体系化。

## 9. 配置、CSV 与热更新

框架配置分为两大类：

- XML 系统配置：日志、网络、心跳、KCP、限速、加密、服务器参数等。
- CSV 游戏数据表：策划数据、服务器表、活动、道具、任务、地图、聊天、排行榜等。

### 9.1 XML 配置

`sysconfig` 提供静态访问器，启动时从 XML 加载运行时配置。典型配置项包括：

- 日志级别与刷盘
- XOR / Varint
- KCP ping 和 session 参数
- 网络心跳与超时
- 限速窗口
- 开服时间
- GM URL
- Lua 脚本路径
- 网关 ID 集合

### 9.2 CSV 表

CSV 基类 `csv_base` 和模板 `csv<T>` 提供：

- 加载
- 校验 hash
- 按 ID 查找
- 遍历
- 热更新回调注册

生成或手写的 `ttab_*` 包装器提供领域方法，例如 `ttab_servers`、`ttab_chat`、`ttab_activity` 等。

### 9.3 热更新

CSV 热更新通过 `reload_csv` 注册保存、重载、读文件回调。热更新时可使用 `actor_suspend` 暂停调度，保证重载过程中的一致性。

### 9.4 评价

优点：

- XML 管系统参数，CSV 管策划表，符合游戏项目常见生产方式。
- 表数据有类型化包装，避免业务层直接操作字符串表格。
- CSV MD5 校验与热更新机制具备实用价值。

不足：

- CSV 热更新对线程暂停和一致性要求较高，需要谨慎验证。
- 配置中心、灰度发布、回滚机制还不是完整平台化能力。
- 策划表校验规则如果缺少自动化，会影响线上变更质量。

## 10. 业务 Actor 覆盖范围

当前 `public/cpp/actor/actor_logic` 下包含 30 多类 Actor 目录，包括：

- 登录：`actor_login`
- 网关：`actor_gateway`、`actor_gateway_c2g`、`actor_gateway_g2c`
- 角色：`actor_role`、`actor_role_manage`
- 聊天：`actor_chat`
- 邮件：`actor_mail`
- 公告：`actor_notice`
- 排行榜：`actor_ranklist`
- 家族：`actor_family`
- 好友：`actor_friends`
- 活动：`actor_activity_manage`
- GM：`actor_gm`、`actor_gmclient`
- 日志：`actor_log`
- 机器人：`actor_robot`、`actor_robot_manage`
- KCP：`actor_kcp`
- CSV 服务：`actor_csvserver`、`actor_csvclient`
- KeyValue：`actor_keyvalue`
- Brief 数据：`actor_brief`
- 示例 Actor：猜数字、匹配、Demo 管理等

角色业务下还包含更细的模块：

- 背包
- 道具
- 合成
- 消耗
- 任务
- 属性
- 技能
- Buff / cooldown
- 地图与 AOI

这说明该框架已经从“基础网络 + Actor”扩展到“游戏业务骨架”，可以用来展示自己对游戏服务端完整链路的理解。

## 11. 代码生成与协议产物

项目包含两类开发工具：

- `server/tools/idl`：基于 IDL 定义生成相关代码和辅助产物。
- `server/tools/makeproto`：生成协议相关辅助文件和数据库配套文件。

同时仓库里存在：

- `.proto` 文件
- 生成的 C++ Protobuf 文件
- 生成的 TypeScript 协议文件
- XML 协议描述
- 自动生成的 Actor / 协议注册文件
- CSV 表对应的 C++ / TypeScript 包装

这条链路说明框架尝试解决服务端、客户端和配置之间的一致性问题。

客观评价：

- 对游戏项目来说，协议和表结构生成是必要能力，可以减少手写重复代码。
- 生成代码应尽量和手写业务代码隔离，当前目录上已有 `generated`、`tab`、`protocol` 等分层。
- 生成链路越复杂，越需要脚本化、CI 校验和清晰文档，否则会成为维护风险。

## 12. GM/运营后台

`admin/` 是一套 PHP 游戏运营后台，提供：

- GM 账号管理
- 权限控制
- 操作日志
- 封号 / 禁言
- 数据库查询与修改
- 家族管理
- GUID 查询
- 邮件
- 公告
- 开服管理
- 充值
- 协议查询
- 排行榜
- 服务器状态
- 关闭 Actor
- 时间管理

后台通过 TCP Socket 与游戏服务器通信，消息格式为 JSON，典型字段包括：

```json
{
  "actor_name": "ACTOR_XXX",
  "operator": "操作名",
  "data": {}
}
```

### 12.1 价值

GM 后台体现了框架不只是服务端运行时，也覆盖了部分运营支撑能力。对游戏项目来说，后台工具往往是上线后稳定运营的必要组成。

### 12.2 风险

已有文档中也明确列出了后台限制：

- 使用旧版 `mysql_*` 扩展，不兼容 PHP 7+
- 密码使用 MD5 哈希，安全性不足
- GM Socket 通信缺少鉴权握手
- `$_POST` 参数校验不充分
- 配置中存在硬编码数据库密码风险

这些问题不影响展示“具备运营后台设计经验”，但如果用于真实生产环境，应优先整改。

## 13. 测试与质量保障

`server/tests` 使用 GoogleTest，目前有 12 个 `*_gtest.cpp` 测试文件。测试目标 `ngl_test` 会自动收集测试源文件。

测试分层：

- 默认 fast 套件：`ngl_test_fast`，过滤掉 `*Perf*`
- 性能套件：需要开启 `NGL_TEST_REGISTER_PERF`

覆盖方向包括：

- 启动烟测
- 运行时
- Actor 管理
- 网络
- WebSocket / KCP 相关路径
- 序列化
- Socket pool
- XML 系统配置
- 工具函数
- 过滤词
- 性能基准

测试目标构建后会把 `bin/configure/config` 同步到测试运行目录，保证测试具备运行时配置。

### 13.1 评价

优点：

- 不是只依赖手工启动，有自动化测试入口。
- fast 测试和 perf 测试分离，适合 CI。
- 测试覆盖基础设施、运行时、网络、序列化等关键路径。
- CMake/CTest 集成清晰。

不足：

- 大型 Actor 系统更需要端到端集成测试和压力测试结果沉淀。
- 网络层和跨节点链路需要持续增加回归覆盖。
- 性能测试如果没有历史基线和趋势图，容易停留在本地参考层面。

## 14. 部署与运维

### 14.1 Windows 本地启动

`bin/configure/windows` 下提供多个批处理脚本，包括：

- 启动单节点
- 启动全套服务
- 启动客户端
- 启动机器人
- 初始化数据库
- 跨服启动
- 推送配置
- kill 脚本
- 节点重命名脚本

Windows 本地流程适合开发调试，尤其是 Visual Studio + CMake + Conan 的组合。

### 14.2 Linux 脚本

`bin/configure/linux` 下包含：

- 打包
- 解包
- 启动
- 关闭
- scp
- crontab
- nginx 配置样例
- 配置模板

说明项目已有一定部署经验，但 Linux 脚本仍偏传统手工运维。

### 14.3 Docker

`deploy/docker` 支持：

- 构建 Docker 镜像
- 单节点运行
- 通过环境变量指定默认节点
- 挂载本地配置
- Docker Compose 启动
- 一个容器内启动 Windows `start_server.bat` 对应的 7 个节点：
  - actor
  - game
  - db
  - login
  - log
  - gateway
  - world

Docker 文档也明确指出：当前 `tab_servers.csv` 使用 `127.0.0.1` 作为节点互联地址，因此“多节点同容器”是为了匹配现有配置。如果拆成一节点一容器，需要修改节点互联地址和服务发现方式。

### 14.4 评价

优点：

- 兼顾 Windows 本地开发、Linux 脚本和 Docker 发布。
- Dockerfile 与 Compose 说明比较明确。
- 统一 node 可执行文件配不同参数，适合镜像复用。

不足：

- 当前 Docker 方案更像“容器化本地多进程”，不是完整微服务化部署。
- 依赖静态 IP/端口配置，服务发现、健康检查、滚动发布能力有限。
- 生产级运维还需要日志采集、指标监控、告警、配置中心、灰度和回滚。

## 15. 文档体系

`doc/` 下已有较完整文档，包括：

- 目录结构
- server 模块
- public/cpp 公共基础库
- libnglcore 运行时核心
- node 入口
- tests 测试模块
- idl 工具
- makeproto 工具
- client TypeScript 客户端
- Actor 系统架构
- 消息流与协议系统
- 网络层
- 网关架构
- 数据库层
- 配置系统
- 新增 Actor 指南
- Actor 就绪与高优先级调度
- 调用类图
- Socket 池优化
- WebSocket 路径简化
- GM 后台工具
- 运维和部署方案
- AI 项目评分记录

这对私有仓库尤其有价值，因为无法直接展示代码时，结构化文档可以帮助面试官理解复杂度和工程范围。

## 16. 框架优势总结

### 16.1 架构完整度较高

NGL 覆盖了游戏服务端从接入、路由、业务、存储、配置、工具、测试到部署的多个环节，不是单点技术实验。尤其是 Actor 系统、网关转发、DB Actor、CSV 热更新、GM 后台这些模块组合在一起，能体现完整游戏后端思维。

### 16.2 Actor 模型适合游戏业务

角色、聊天、邮件、排行榜、家族等模块天然适合 Actor 封装。通过 Actor ID 携带类型、区服和实例信息，也贴合分服游戏项目。

### 16.3 多传输协议能力

TCP、WebSocket、KCP 同时支持，说明框架考虑了不同客户端形态和低延迟场景。

### 16.4 工程化意识明显

CMake + Conan + GoogleTest + CTest + Docker + CI + SonarCloud badge + 文档体系，说明项目不是只关注“能跑”，也关注可构建、可测试、可发布和可维护。

### 16.5 生成链路减少重复劳动

协议、IDL、CSV、TypeScript 客户端协议等生成链路，有助于保证客户端、服务端、配置之间的一致性。

## 17. 客观不足与改进方向

### 17.1 优雅退出与生命周期治理

部分线程采用进程常驻、析构不回收的策略。对游戏长驻进程来说可以接受，但如果要达到更高工程标准，应补充：

- stop token
- 线程 join
- Actor 队列 drain
- DB 刷盘完成确认
- 网络连接关闭流程
- 进程退出前状态上报

### 17.2 线上可观测性不足

已有日志和部分统计，但一个生产级框架还需要：

- Actor 队列长度指标
- Actor 处理耗时分位数
- 消息延迟
- 网络收发包量
- DB 请求耗时
- DB 失败率
- KCP 丢包/重传指标
- CSV 热更新结果指标
- Prometheus / OpenTelemetry 等标准化接入

### 17.3 安全性需要加强

GM 后台和网络层存在一些明确风险：

- GM 后台 MD5 密码
- 旧 mysql 扩展
- GM Socket 缺少鉴权握手
- 参数校验不足
- XOR 不能替代加密

生产环境建议引入：

- HTTPS
- 密码 bcrypt / Argon2
- 后台 RBAC 细化
- GM 指令签名
- 服务端鉴权 token
- 操作审计不可篡改
- 输入校验和权限隔离

### 17.4 配置和部署仍偏静态

当前依赖 `tab_servers.csv` 静态定义节点互联关系。后续可以演进为：

- 配置中心
- 服务发现
- 健康检查
- 动态扩缩容
- 一节点一容器
- Kubernetes 部署
- 灰度和回滚

### 17.5 协议与代码生成链路需要强约束

生成链路越强大，也越需要规范：

- 生成脚本一键化
- 生成结果 CI 校验
- 协议兼容性检查
- 协议版本管理
- 客户端/服务端同步校验
- 生成代码和手写代码严格隔离

### 17.6 C++ 模板和宏复杂度

Actor、协议、DB 组件、生成代码大量使用模板和类型擦除。优点是灵活，缺点是：

- 编译错误可能复杂
- 新成员学习成本高
- 调试链路较长
- 文档和示例必须持续维护

## 18. 求职介绍建议

如果在面试中介绍这个框架，建议不要只说“我写了一个游戏服务器框架”，而是按问题域展开：

### 18.1 一句话介绍

可以这样表达：

> NGL 是我实现和持续维护的一个 C++23 游戏服务端框架，核心采用 Actor 模型，支持多节点分服、TCP/WebSocket/KCP 长连接、Protobuf 协议、CSV/XML 配置、异步 DB Actor、GM 后台、自动化测试和 Docker 部署。它主要用于验证和沉淀中小型在线游戏后端的完整技术链路。

### 18.2 展示重点

建议重点讲 5 个方向：

1. **Actor 调度**：为什么用 Actor，怎么做分层调度，如何避免共享状态，如何处理高优先级消息。
2. **网络与网关**：客户端消息如何从 TCP/WS/KCP 进入网关，再转发到游戏 Actor，服务端如何回包。
3. **数据持久化**：业务 Actor 如何通过 DB client 和 DB Actor 异步加载、脏标记、批量保存。
4. **配置与生成链路**：CSV/XML/Protobuf/IDL 如何支撑客户端、服务端和策划表一致。
5. **工程化**：CMake/Conan/GoogleTest/Docker/CI/文档/后台工具如何支撑长期维护。

### 18.3 可以主动承认的不足

主动承认不足会显得更可信：

> 这个框架目前更偏个人/小团队游戏服务端基础设施沉淀，已经覆盖 Actor、网络、协议、DB、配置、后台和部署，但距离生产级平台还需要加强优雅退出、可观测性、安全治理、动态服务发现和 Kubernetes 化部署。

### 18.4 面试官可能追问的问题

建议提前准备以下问题：

- Actor 调度为什么分 8 层？是否可以动态调整？
- Actor 消息积压怎么发现？怎么处理慢 Actor？
- 高优先级消息如何避免普通消息饥饿？
- 跨节点 Actor 消息如何寻址？远程 Actor 不存在怎么办？
- 网关如何绑定玩家 session 和角色 Actor？
- KCP session 如何创建？如何防止伪造？
- DB 脏标记什么时候刷盘？进程崩溃丢多少数据？
- CSV 热更新如何保证线程安全？
- 协议变更如何保持前后端兼容？
- 如果上 Kubernetes，现有架构要改哪些地方？

## 19. 可放在简历中的表述

以下表述可以根据实际贡献程度取舍：

```text
独立设计并实现 C++23 游戏服务端框架 NGL，核心基于 Actor 模型，支持多节点分服、TCP/WebSocket/KCP 长连接、Protobuf 协议路由、CSV/XML 配置加载与热更新、异步 DB Actor 持久化、GM 后台工具、GoogleTest 回归测试和 Docker 部署。
```

更偏技术细节版本：

```text
实现 Actor 分层调度与共享工作线程池，使用 64 位 Actor ID 编码类型、区服和实例信息，支持本地/跨节点消息路由、高优先级消息队列、批量 Actor 投递和网关 C2G/G2C 转发。
```

更偏工程化版本：

```text
为框架建设 CMake + Conan 构建体系、GoogleTest/CTest 测试链路、Docker 镜像发布、Windows/Linux 启动脚本和模块化技术文档，提升私有游戏服务端项目的可维护性和交付能力。
```

更偏业务完整性版本：

```text
基于框架实现登录、网关、角色、聊天、邮件、排行榜、家族、活动、机器人、GM 等 Actor 模块，并配套协议生成、配置表生成、运营后台和客户端 Demo，用于验证完整在线游戏后端链路。
```

## 20. 总体评价

NGL 是一个覆盖面较广、工程配套较完整的 C++ 游戏服务端框架。它的核心价值在于：

- 用 Actor 模型组织复杂游戏业务。
- 用统一消息系统连接本地 Actor、跨节点 Actor 和客户端网关。
- 用多传输协议覆盖 TCP、WebSocket、KCP 场景。
- 用 DB Actor、脏标记和批量刷盘处理游戏数据持久化。
- 用 CSV/XML/Protobuf/IDL/生成代码支撑协议和配置一致性。
- 用测试、文档、Docker、后台工具补齐工程化链路。

从求职角度看，这个项目可以很好地证明以下能力：

- C++ 服务端架构设计能力
- 游戏服务端领域理解
- 网络协议与长连接处理能力
- 多线程调度与并发模型设计能力
- 数据持久化和配置系统设计能力
- 工程化、测试、部署和文档意识

同时也应客观看待：它仍有个人框架常见的问题，例如生产级可观测性、安全治理、动态部署、优雅退出、协议治理和团队协作规范还需要继续加强。如果向新公司介绍，建议把它定位为“完整度较高的个人/小团队游戏服务端框架沉淀”，而不是声称已经等同于大规模商业化平台。

