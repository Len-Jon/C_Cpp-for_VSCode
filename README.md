# 使用说明

## 系统环境配置

> 在配置环境前，应先检查环境，因为Linux和Mac OS一般是不需要配置的

### Windows

- 检查环境

  - <kbd>Win</kbd>+<kbd>R</kbd> 打开运行

  - 输入`cmd`或者`powershell`

  - 依次输入

    ```powershell
    gcc -v
    g++ -v
    gdb -v
    ```

    如出现版本信息则环境配置完成

- 如上一步没有信息，需要配置

  - 下载MinGW
    
    - 如果是安装包格式可能不需要手动配置环境变量，可跳过下一步；如果是压缩包需要手动配置一下
  - 手动配置环境变量
    - <kbd>Win</kbd>+<kbd>E</kbd>打开资源管理器，右键左边的此电脑

    - 打开高级系统设置-环境变量-系统变量或用户变量

    - 双击 Path

    - 添加添加MinGW的bin文件夹添加进去，如

      ```
      D:\mingw64\bin
      ```
  - **一定要把原来的cmd或powershell关掉再打开**，回到上一步检查是否配置成功

### Linux

linux一般自带c / c++，gdb好像就不是自带的了，看情况吧

- 检查环境

  - 打开终端（Terminal）

  - 依次输入

    ```bash
    gcc -v
    g++ -v
    gdb -v
    ```

    如出现版本信息则配置完成

    若某一项没有版本信息，那么记住它，根据所使用的发行版的包管理工具安装对应的命令

- 补充安装
  - 包管理工具安装

    以apt为例，假设上一步中，gdb没有配置，则

  	```bash
  	sudo apt install gdb
  	```

	- 源码安装配置环境

  	相信使用Linux，又选择源码安装的你不需要我来说了
	
### Mac OS

- 检查环境

  - 打开启动台

  - 找到终端（Terminal）

  - 依次输入

    ```bash
    clang -v
    clang++ -v
    ```
    
    如果没有相应的环境，mac会提示安装

  

## 插件

都需要安装的插件：

- C/C++
- Code Runner

对于Mac，因为使用LLDB编译与调试，还需要安装：

- CodeLLDB

除此之外，推荐安装：

- Chinese (Simplified) Language Pack for Visual Studio Code （简体中文语言包）
- Bracket Pair Colorizer （彩色括号）

## 工作区环境配置

克隆本仓库，选择对应系统的文件夹复制出来，项目结构如下

- ${Env}
  - C
    - .vscode
      - launch.json
      - tasks.json
    - hello.c
  - C++
    - .vscode
      - launch.json
      - tasks.json
    - hello.cpp
  - c&c++.code-workspace

食用说明：

- 看的出来，两个文件夹分管两种语言，写源码的位置与对应的`hello.c/hello.cpp`同级。

- c&c++.code-workspace是工作区配置，本质是个json文件，里面有运行命令和一些优化命令，核心部分大概如下（不同系统不同）

  ```json
  {
  	//...
  	"settings": {
      //...
      	"code-runner.executorMap":
      	{
          	"c": "cd $dir && gcc '$fileName' -o '$fileNameWithoutExt.out' -Wall -O2 -std=c11 && './$fileNameWithoutExt.out' && rm -rf './$fileNameWithoutExt.out' './$fileNameWithoutExt.out.dSYM'",
          	"cpp": "cd $dir && g++ '$fileName' -o '$fileNameWithoutExt.out' -Wall -O2 -std=c++11 && './$fileNameWithoutExt.out' && rm -rf './$fileNameWithoutExt.out' './$fileNameWithoutExt.out.dSYM'",
      	},
      //...
  	}
  }
  ```

  如需更换c或c++的标准，更改std参数；

  如需保留生成的可执行文件，删除最后一个`&&`（包括）到`"`（不包括），用区间表示就是：[&&,")；

  有了这个文件即可搭配code runner插件运行。

- .vscode文件夹

  这个文件夹指的是当前文件夹下的环境配置，这里我们用来放调试的配置信息，有需求的自己修改

  launch.json是调试，里面调用tasks.json里的命令（先编译）



# 补充：关于Windows乱码问题

Windows系统的默认编码是GBK，所以在命令提示符或powershell中，编码都是GBK

```powershell
chcp
```

输入此命令可查看活动代码页

- 936为GBK
- 65001为UTF-8

因此，在编译运行的时候需要加上

> "-fexec-charset=GBK"

这个参数的作用是指定编译出来程序的编码

另一个隐藏参数`-finput-charset=UTF-8`是不必要的，因为VSCode默认编码就是UTF-8；

- 如果只是运行，那么这个在`c&c++.code-workspace`中已经配置，可以直接在内置终端中使用，无论是源码中的中文还是用户输入的中文都可以正常输出。

- 如果需要编译，那就比较麻烦

  tasks.json中需要指定 `"-fexec-charset=GBK"`，原因就是为了匹配系统编码。

  launch.json中的`"externalConsole": true,`

  如果此时在集成终端中显示，那么可能会产生乱码，因为VSCode似乎默认集成终端使用65001的活动代码页。

  如果不在集成终端显示，在调试查看变量时的中文显示会异常，但是黑框框里的中文正常

  | 源码  | 可执行文件 | 终端 | 源码里的中文 | 用户输入的中文 | 监视器里的中文 |
  | ----- | ---------- | ---- | ------------ | -------------- | -------------- |
  | UTF-8 | UTF-8      | 集成 | 正常         | 异常           | 异常           |
  | UTF-8 | UTF-8      | 外部 | 异常         | 正常           | 异常           |
| UTF-8 | GBK        | 集成 | 异常         | 异常           | 异常           |
  | UTF-8 | GBK        | 外部 | 正常         | 正常           | 异常           |
  

## 解决方法

### 方式1

可执行文件使用GBK，使用外部终端。但监视器里中文无法解决

### 方式2

修改系统编码，改成UTF-8，可执行文件使用UTF-8，使用内部终端，但可能导致其它应用的兼容性问题。



> 如果有其它方式请提issue