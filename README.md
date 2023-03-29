## KinokoBot

基于 Mirai 框架及 TextCompletion API 的高性能 QQ AI 对话机器人。

### 编译环境

- ubuntu 22.04

### 编译前的准备

- 需要在根目录中新建一个文件 `initKey.cpp` ，在其中使用自己的 OpenAI API key 定义 `API_KEY`。
- 安装vcpkg并导入如下的第三方库
  - HTTP 库： [C++ Requests](https://github.com/libcpr/cpr)
  - JSON 库：[JSON for Modern C++](https://github.com/nlohmann/json)



### 开发日志

- 2023/03/02

  对 OpenAI 的 API 进行基本的封装。统一调用返回时的格式。编写 TestBot 以测试封装库的正确性。

- 2023/03/04

  设计并优化了 ChatBot 的基本框架。

- 2023/03/05

  重构 ChatCache。

- 2023/03/06

  实现一个简单的 Logger 用以调试。实现 ChatBot 的第一个版本。

- 2023/03/07

  实现多人聊天。用 `string_view` 替换了 `const string&` 。

- 2023/03/24 - 2023/03/26

  开发 WebsocketServer ，准备使用 go-cqhttp 框架 + websocket 服务器部署 QQ 机器人。

- 2023/03/26

  尝试开发阻塞队列，失败，作罢。

  引入 WebsocketServer 及其依赖。

- 2023/03/27

  砍掉了所有当前不太可能实现的功能，从 Chat 模块中提取出 RoleplayModule 作为机器人的其中一个功能模块。

  微调RoleplayModule的prompt结构，prompt = scene + character info + talk。

  采用线程分离式的speak方法。

- 2023/03/28

  调整了目录结构。

  简单封装了消息到达的接口。
  
  修改机器人代号为 Kinoko。



