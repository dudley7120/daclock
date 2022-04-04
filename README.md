# 3.0版本更新一下内容
### 1、采用SPIFFS存储老虎动图，支持通过网页上传新的图，文件需要以hlh1.bmp~hlh18.bmp命名，格式为bmp24位深文件。
### 2、优化服务器端配置，美化界面。
### 3、优化天气等刷新逻辑。
# 2.0版本更新以下内容
### 1、加入字库，支持常见文字显示，节日显示更完整。
### 2、加入注册服务功能，可在线配置纪念日，支持农历、阳历。
### 3、合并单屏、双屏版本代码，降低维护难度。
### 4、由于内置了2万多汉字区位码，空间占用较大，我编译的时候是99%
### 5、注册时钟时，昵称会成为网站的用户名，密码与用户名相同，修改密码功能暂未开发。
### 6、注册时钟时，会上传硬件地址作为时钟的ID。同时为了区分时钟，会记录时钟所在IP。
# daclock-p2.5
Use P2.5 led screen display
### 1、本时钟通过esp32驱动p2.5led单元板实现。
### 2、依托esp32强大的网络通信，实现了时间校准、天气显示、农历显示、节日显示。
### 3、时钟初次使用，采用Ap模式，网页访问IP进行配网。
### 4、网络连接后，时钟提供页面管理时钟部分参数。初始用户：admin 密码：000000
### 5、时钟功能还在完善中，由于平时工作，佛系更新。
### 6、时钟内置dht11模块，可同时显示室内外温度、适度。
### 7、后续将加入纪念日功能，通过网页进行配置。
### 8、后续持续加入多种界面。
### 9、提供源码，供有开发环境的朋友使用。bin文件可直接刷入使用
### 10、天气部分使用和风天气。key和城市id请访问https://id.qweather.com/获取。
### 11、DAOLEDCLOCK-BETA.ino.esp32.bin增加三天预报和老虎切换。
