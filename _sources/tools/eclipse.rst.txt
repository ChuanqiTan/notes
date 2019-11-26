
.. note:: **工欲善其事，必先利其器。**

.. note:: | 我的 IDE 定为Eclipse+Vim，前者用于大规模的项目，后者用于除大规模项目外的所有情况。
          | 我选择IDE的标准为："开源、跨平台、近乎标准工具、好用"，Eclipse+Vim 足以满足我的需求。

       
Eclipse
=======================

- Eclipse CDT 常用的快捷键：

  - 基本
    
    :Ctrl+Shift+L:        显示所有的快捷键(万物之源啊，不记得的时候随手看一看)
    :Ctrl+3:              Quick Access，右上角的文本框，快速搜索所有的命令

  - 窗口导航

    :F12:                 Active Editor（非常重要，在如Ctrl+G等弹出其它窗口之后迅速的回到编辑窗口）
    :Ctrl+Alt+T:          排名第一的快捷键，快速打开类型，支持通配符
    :Ctrl+Alt+R:          排名第二的快捷键，快速寻找整个workspace里的所有资源，支持通配符
    :Ctrl+O:              Outline
    :Ctrl+E:              快速切换已打开的文件(类似的还有Ctrl+F6直接切换,和Ctrl+Shift+E)
    :Ctrl+M:              编辑器窗口最大最小化
    :Ctrl+T:              查看类继承关系图
    :Ctrl+Alt+H:          在Workspace范围内查找函数被调用的关系树
    :Ctrl+G:              查找一个符号的声明和定义，这个类似于工具栏的Mark Occurrences，但是可以显示在其它文件中定义的符号
    :Ctrl+Shift+G:        查找一个符号在当前workspace被引用的所有位置
    :Ctrl+W:              关闭当前窗口
    :Ctrl+Shift+W:        关闭所有窗口
    :Alt+Enter:           显示当前选择资源(工程,or 文件 or文件)的属性
    :Alt+Shift+Q:         再接一个字符选择打开一个窗口（按完Alt+Shift+Q后会弹出提示框）

  - 编辑

    :Alt+Shift+A:         进入块选择模式
    :Shift+Enter:         快速在下方创建一行并切换过去
    :Ctrl+Shift+Enter:    快速在上方创建一行并切换过去
    :Alt+上/下:           快速将当前行上下移一行
    :Alt+左/右:           移动到上次（下）光标所在的位置
    :Ctrl+,/.:            移动到上/下一个错误处
    :Ctrl+1:              Quick Fix
    :Ctrl+Q:              回到上一次编辑的位置(Vim: \`\`)
    :Ctrl+D:              删除一整行
    :Alt+/:               Code Assent!!!
    :Alt+?:               参数提示
    :Ctrl+Alt+/:          按文本补全
    :Ctrl+/:              切换注释
    :Ctrl+Shift+/:        添加块注释
    :Ctrl+Shift+\\:       删除块注释
    :Ctrl+Tab:            头文件和源文件切换
    :Ctrl+Shift+F:        根据Code Style格式化代码
    :Ctrl+H:              查找字段C/C++ Search
    :F2:                  显示Tooltip，相当于鼠标悬停     
    :F3:                  转到声明，相当于Ctrl+鼠标单击
    :Ctrl+F:              查找/替换窗口
    :Ctrl+J:              增量查找
    :Ctrl+K:              查找结果的下一个
    :Ctrl+Shift+K:        查找结果的上一个
    :Alt+Shift+方向:      根据语法进行整块选择
    :Ctrl+L:              定位在某行
    :Ctrl+ /:             打开/关闭折叠功能 ( **所有与折叠相关的都是小键盘上的键** )
    :Ctrl+ \*:            展开所有的块
    :Ctrl+Shift+/:        折叠所有的块
    :Ctrl+ -:             折叠当前元素
    :Ctrl+ +:             展开当前元素
    :Ctrl+Shift+P:        定位到对于的匹配符(譬如{})
    :Ctrl+Z:              撤销
    :Ctrl+Shift+Z:        重做
    :Ctrl+上/下:          保持光标位置不变的向上/下滚动
    :Ctrl+左/右:          按单词的移动（一定要多用）
    :Ctrl+Shift+N:        快速添加缺失的头文件
    :Ctrl+Shift+上:       转至当前文件的上一个成员
    :Ctrl+Shift+下:       转至当前文件的下一个成员

  - 重构

    :Alt+Shift+R:         重构 - 重命名
    :Alt+Shift+L:         重构 - 提取本地变量
    :Alt+Shift+M:         重构 - 提取本地方法
    :Alt+C:               重构 - 提取一个字面值为常量
    :Alt+Shift+T:         重构 - 把函数体在头文件和头文件之间进行切换

  - 构建、运行、调试：

    :Ctrl+B:              全部构建Build
    :Ctrl+Shift+B:        切换断点
    :F5:                  单步跳入
    :F6:                  单步跳过
    :F7:                  单步返回
    :F8:                  继续
    :F9:                  Make 最近的 Target
    :Shift+F9:            选择Make Target
    :F11:                 Debug
    :Ctrl+F11:            Run

  - 自定义

    :Alt+J:              下移一行
    :Alt+K:              上移一行
    :Alt+H:              左移一列
    :Alt+L:              右移一列

- 安装Eclipse汉化包

  - Eclipse的语言包是由Babel项目来提供的，首先到 http://www.eclipse.org/babel/downloads.php 找到当前Eclipse版本对应的中文包
  - 然后下载对应的组件的汉化包，一般来说我下载eclipse-zh和cdt-zh两个包就可以了
  - Eclipse的语言包也是用插件的形式安装，所以这2个语言包也使用links安装插件的方式安装

    - 在eclipse目录下创建languages目录，再把下载的2个语言包分别解压到language/eclipse-platform, language/cdt目录下
    - 再在eclipse目录下创建links目录，在其中创建任何名称的文本文件如languages.link，写入如下内容::

        path=languages/eclipse-platform
        path=languages/cdt

    - 如果还有部分内容没有更新成中文，那是因为以前的缓存，解决办法如下：

      - 把 configuration 目录中除了 config.ini 之外的目录全部删除，运行eclipse会重新建立
      - 以 -clean 参数启动eclipse

- 比较值得安装的插件:

  - `elt <http://code.google.com/p/elt/>`_ (Terminal plug-in for Eclipse) 给Eclipse添加一个命令行功能，这样就可以完全不用离开eclipse做所有的事情了.
  - `vrapper <http://vrapper.sourceforge.net/home/>`_ 模仿VIM编辑器的插件

- Eclipse CDT 常用设置

  - 编辑器选项：General > Editors > Text Editors
      选中Insert spaces for tabs, tab 宽度设置为2；
      选中Show print margin，并设置Print margin column = 100；
      选中Show line numbers
  - 工作空间设置 General > Workspace
      选中Save automatically before build、Always close unrelated projects without prompt、设置Workspace Name。
  - 重构前自动保存 C/C++  
      选中Save all modified resources automatically prior to refactoring
  - 群组归类显示 C/C++ > Appearance
      选中所有Group选项
  - 只构建有修改的项目 C/C++ > Build
      选中Build configurations only when there are Eclipse resource changes within the project and its references
  - 加快提示速度 C/C++ > Editor > Content Assist
      选中所有的自动激活，并把延时设置为1ms
  - 自动代码折叠：C/C++ > Editor > Folding
      | 选中Enable folding when opening a new editor
      | 选中Enable folding of preprocessor branches
      | 选中Enable folding of control flow statements
      | 只保留Initially fold these region types中的下列两项： Header Comments、Inactive Preprocessor Branches
  - 保存时删除所有行的末尾空格：C/C++ > Editor > Save Actions
      Remove trailing whitespace > 选中In all lines
  - 单文件最大解析数目：
      C/C++ > Editor > Scalability，从5000改成50000
  - 模板应用自定义代码风格：C/C++ > Editor > Templates
      选中Use code formatter
  - 解析器：C/C++ > Indexer
      选中Index unused headers；
      选中Index source and header files opened in editor；
      尽量加大Cache limits的值，例如：50%, 512MB, 256MB
  - 代码格式化
      C/C++ > Code Style > Formater 导入google-cpp-style-for-eclipse.xml
  - 设置豆沙色背景以保护眼睛
      常规 > 编辑器 > 文本编辑器 > 外观颜色选项 > 背景色 设置RGB为 ``R:204  G:232  B:207`` 就OK了。
  - 过滤不想要的文件：
      右键想要隐藏文件的project or folder->Properties->Resource->Resource Filters->Add "Exclude all"

- Windows下常见问题

  - windows下中文字体太小：因为默认使用的Consolas字体的原因，切换为Courier New字体，在Windows->Preferences->General->Appearance->Color and Font->Basic->Text Font->显示更多字体->右键显示激活
