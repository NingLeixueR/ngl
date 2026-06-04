# ngl_server 核心架构

`ngl_server` 是一个以 **Actor 模型** 为核心的 C++ 游戏服务器框架。项目主干不是传统的“单体服务 + 业务模块”结构，而是围绕 Actor 基础设施、服务端运行工程、配置/协议生成、运行脚本、管理后台和测试自动化分层组织。

## 核心分层

### 1. 公共 C++ 基础库：`public/cpp`

这是项目最核心的一层，知识图谱中这一层包含约 405 个文件，职责是公共 C++ 源码、网络、序列化、日志、配置和 Actor 基础设施。

关键路径集中在：

- `public/cpp/actor/actor_base/core/actor_base.cpp`
- `public/cpp/actor/actor_base/core/actor_base.h`
- `public/cpp/actor/actor_base/core/actor.cpp`
- `public/cpp/actor/actor_base/core/actor.h`
- `public/cpp/actor/actor_base/core/actor_manage.cpp`
- `public/cpp/actor/actor_base/core/actor_manage.h`
- `public/cpp/actor/actor_base/core/naddress.cpp`
- `public/cpp/actor/actor_base/core/naddress.h`
- `public/cpp/actor/actor_base/core/nactortype.h`
- `public/cpp/actor/actor_base/core/ndb_modular.*`
- `public/cpp/actor/actor_base/core/nmanage_dbclient.*`

这一层承担 Actor 抽象、Actor 管理、地址标识、数据库模块、消息参数和注册机制等基础能力。可以把它看作整个服务器框架的运行模型层。

### 2. Actor 业务逻辑层：`public/cpp/actor/actor_logic`

业务逻辑按 Actor 领域拆分在 `actor_logic` 下，而不是散落在服务端入口中。知识图谱里可以看到很多以 `actor_xxx` 组织的模块，例如：

- `public/cpp/actor/actor_logic/actor_activity_manage/`
- `public/cpp/actor/actor_logic/actor_brief/`
- `public/cpp/actor/actor_logic/actor_chat/`
- `public/cpp/actor/actor_logic/actor_client/`

典型文件包括：

- `actor_activity_manage.cpp/.h`
- `actor_chat.cpp/.h`
- `actor_brief.cpp/.h`
- 各模块下的 `message/*_handle.cpp`

项目的业务实现方式大致是：`Actor` 基类和管理器提供生命周期、地址、消息派发等能力；具体玩法或系统模块实现成独立 Actor 逻辑模块；再通过 message handler 处理协议或内部消息。

### 3. 服务端工程层：`server`

知识图谱中 `server` 层包含约 171 个文件，职责是承载服务端工程结构、运行目标和 CMake 集成。它更像是把 `public/cpp` 中的基础能力组织成可构建、可运行的服务端目标。

重点子目录包括：

- `server/runtime/libnglcore`
- `server/runtime/node`
- `server/tests`
- `server/tools/idl`
- `server/tools/makeproto`
- `server/tools/rebuild`

其中 `server/runtime` 是运行时入口相关区域，`server/tools` 是生成和维护工具，`server/tests` 是验证体系。

### 4. 协议、IDL 和代码生成工具：`server/tools` + `bin/compile_befor/idl`

知识图谱识别出独立的服务端工具层，代表路径包括：

- `server/tools/idl/core/idl.cpp`
- `server/tools/idl/core/idl.h`
- `server/tools/idl/core/idlcpp_protocol.h`
- `server/tools/idl/core/main.cpp`
- `server/tools/makeproto/core/main.cpp`
- `server/tools/makeproto/core/xml_protocol.cpp`
- `server/tools/makeproto/core/xml_protocol.h`
- `server/tools/rebuild/core/main.cpp`

图谱里的导入边显示：

- `server/tools/idl/core/idl.cpp` imports `server/tools/idl/core/idl.h`
- `server/tools/idl/core/main.cpp` imports `idl.h`
- `server/tools/idl/core/main.cpp` imports `idlcpp_protocol.h`
- `server/tools/makeproto/core/main.cpp` imports `xml_protocol.h`

这说明项目有一条明确的协议/IDL 生成链路：IDL、XML、Protobuf、CSV 等配置或协议定义通过工具生成 C++ 或协议相关代码，再被 Actor 逻辑和网络层消费。

相关配置和生成结果包括：

- `bin/compile_befor/idl/*.idl`
- `bin/configure/config/net_protocol.xml`
- `bin/configure/config/example_protocol.xml`
- `public/cpp/actor/generated/pb/net.pb.h`
- `public/cpp/actor/generated/pb/net.pb.cc`

### 5. 运行配置与脚本层：`bin/configure`

知识图谱中“运行配置与脚本”层包含约 77 个文件，覆盖启动脚本、CSV/XML/Protobuf 配置和本地运行参数。

代表文件：

- `bin/configure/config/config/config.xml`
- `bin/configure/config/config/config.template.xml`
- `bin/configure/config/net_protocol.xml`
- `bin/configure/config/csv/tab_servers.csv`
- `bin/configure/linux/start.sh`
- `bin/configure/linux/close.sh`
- `bin/configure/windows/start_server.bat`
- `bin/configure/windows/start_demo01.bat`
- `bin/configure/script/lua/actor_testlua/actor_testlua.lua`

这一层说明项目运行时大量依赖外部配置：服务器列表、网络协议、AI 配置、Lua 脚本、CSV 表和启动参数等。架构上它承担数据驱动运行的角色。

### 6. 管理后台：`admin`

知识图谱识别出独立的管理后台层，约 84 个 PHP 文件。代表文件包括：

- `admin/auth.php`
- `admin/actionmanager.php`
- `admin/actor_type.php`
- `admin/get_serverlist.php`
- `admin/push_server_config.php`
- `admin/serverls.php`
- `admin/sys/close_actor.php`
- `admin/mail/*`
- `admin/notice/*`
- `admin/pay/*`

这说明项目不仅包含 C++ 服务端，还包含一个 PHP 运维/GM 管理后台。它很可能用于服务器列表、账号权限、公告、邮件、充值、封禁、开服和推送配置等运营管理操作。

### 7. 测试与 CI 层

测试体系代表路径：

- `server/tests/actor_manage_gtest.cpp`
- `server/tests/actor_role_gtest.cpp`
- `server/tests/bootstrap_gtest.cpp`
- `server/tests/net_gtest.cpp`
- `server/tests/runtime_gtest.cpp`
- `server/tests/perf_gtest.cpp`

CI 层包括：

- `.github/workflows/cmake-linux-conan.yml`
- `.github/workflows/cmake-windows-conan.yml`
- `.github/workflows/clang_format_check.yml`
- `.github/workflows/manual-test.yml`

构建体系包括：

- `CMakeLists.txt`
- `conanfile.py`
- `cmake/`
- `CMakeUserPresets.json`

项目采用 CMake + Conan + GoogleTest 的 C++ 工程体系，并覆盖 Windows/Linux 构建。

## 核心架构主线

```text
CMake/Conan 构建系统
        |
        v
公共 C++ 基础库 public/cpp
        |
        +--> Actor 基础设施：actor_base/core
        |       - actor
        |       - actor_base
        |       - actor_manage
        |       - naddress / nactortype / nguid
        |       - db modular / db client
        |
        +--> Actor 业务逻辑：actor_logic/*
        |       - chat
        |       - activity
        |       - client
        |       - brief
        |       - role 等业务 Actor
        |
        +--> generated/pb 协议代码
        |
        v
server 运行工程
        |
        +--> runtime / node / libnglcore
        +--> tests
        +--> tools
              - idl
              - makeproto
              - rebuild

外部支撑：
bin/configure 提供 XML/CSV/Lua/启动脚本
admin 提供 PHP 管理后台
.github/workflows 提供 CI
```

## 一句话总结

这个项目的核心架构是：以 `public/cpp/actor/actor_base/core` 为基础的 Actor 运行模型，向上通过 `actor_logic` 承载游戏业务模块，旁路通过 IDL/Protobuf/XML/CSV/Lua 配置实现协议和数据驱动，再由 `server` 工程、`bin/configure` 运行配置、`admin` 管理后台和 GoogleTest/CI 共同组成完整的游戏服务器框架。

## 推荐阅读顺序

如果要理解核心架构，建议按这个顺序阅读：

1. `README.md`
2. `CMakeLists.txt`
3. `public/cpp/actor/actor_base/core/actor.h`
4. `public/cpp/actor/actor_base/core/actor_base.h`
5. `public/cpp/actor/actor_base/core/actor_manage.h`
6. `public/cpp/actor/actor_base/core/naddress.h`
7. `public/cpp/actor/actor_logic/actor_chat/actor_chat.h`
8. `public/cpp/actor/actor_logic/actor_client/actor_client.cpp`
9. `server/tools/idl/core/main.cpp`
10. `bin/configure/config/net_protocol.xml`
11. `server/tests/actor_manage_gtest.cpp`
12. `server/tests/runtime_gtest.cpp`
