# GitHub
## 解决GitHub访问慢的问题
    1. 通过https://www.ipaddress.com/进行ip查询
    2. 获取github.com和github.global.ssl.fastly.net的ip地址
    3. 修改本地host文件
        sudo vim /private/etc/hosts
        140.82.112.3 github.com
        199.232.5.194 github.global.ssl.fastly.net
    4. 刷新DNS
        dscacheutil -flushcache

## Essentials
- repositories
- branches
- commits
- Pull Requests


## Step 1. Create a Repository
- 什么是仓库：  
repository can be a place where you store ideas, resources, or even share and discuss things with others.

- 仓库里可以存放什么：  
Repositories can contain folders and files, images, videos, spreadsheets, and data sets – anything your project needs.

## Step 2. Create a Branch
- 什么是分支：  
**Branching** is the way to work on different versions of a repository at one time.

- main分支：  
By default your repository has one branch named **main** which is considered to be the definitive branch. We use branches to experiment and make edits before committing them to main.  
仓库默认有一个最终的主线main分支，利用其他分支进行调试，最终提交合并至主线main分支

- 为什么使用分支：  
在GitHub，我们的开发人员、编写人员和设计人员使用分支将bug修复和特性工作与我们的主（生产）分支分开。当更改准备就绪时，它们会将分支合并到main中。

## Step 3. Make and commit changes

## Step 4. Open a Pull Request
 When you open a **pull request**, you’re proposing your changes and requesting that someone review and pull in your contribution and merge them into their branch. Pull requests show diffs, or differences, of the content from both branches. The changes, additions, and subtractions are shown in green and red.


 # Gits
## 常用命令
- 创建版本库repository  
    `git init`进行仓库初始化

- 提交文件  
    `git add readme.md`  
    `git commit -w 'create readme.md'`
    PS：add与commit区别，add把要提交的所有修改放到暂存区（Stage），commit一次性把暂存区的所有修改提交到分支

- 查看仓库状态
    `git status`

- 查看文件差异
    `git diff readme.md`

- 查看提交日志
    `git log`

## git差异比较
- git diff：  
    当工作区有改动，临时区为空，diff的对比是“工作区与最后一次commit提交的仓库的共同文件”；  
    当工作区有改动，临时区不为空，diff对比的是“工作区与暂存区的共同文件”

- git diff --cached或git diff --staged：  
    显示暂存区(已add但未commit文件)和最后一次commit(HEAD)之间的所有不相同文件的增删改(git diff --cached和git diff –staged相同作用)

- git diff HEAD：  
    显示工作目录(已track但未add文件)和暂存区(已add但未commit文件)与最后一次commit之间的的所有不相同文件的增删改。

- git diff HEAD^^^…(后面有X个^符号，X为正整数)：  
    可以查看最近一次提交的版本与往过去时间线前数X个的版本之间的所有同上`git diff HEAD`中定义文件之间的增删改。

- git diff <分支名1> <分支名2> ：  
    比较两个分支上最后 commit 的内容的差别


## 配合github使用远程仓库
- 终端命令创建ssh key  
    ssh-keygen -t rsa -C "xx@qq.com"
    ```
    Generating public/private rsa key pair.
    Enter file in which to save the key (/Users/geewinter/.ssh/id_rsa):
    Enter passphrase (empty for no passphrase):
    Enter same passphrase again:
    Your identification has been saved in /Users/geewinter/.ssh/id_rsa.
    Your public key has been saved in /Users/geewinter/.ssh/id_rsa.pub.
    
    The key fingerprint is:
    SHA256:nR6dkYbdfZFBiL/nRrbkXpY++lM+teTYpvzMDfXKiT8 815672122@qq.com
    The key's randomart image is:
    +---[RSA 3072]----+
    |            . o+o|
    |           + + o.|
    |          . * . o|
    |         . + +  .|
    |        S + o . .|
    |         . . . B=|
    |          .   &oO|
    |            .+E^+|
    |            .=&O=|
    +----[SHA256]-----+
    ```
- github中setting设置`New SSH Key`

- 链接验证  
    `ssh -T git@github.com`

- 查看绑定的仓库列表  
    `git remote -v`

- 删除远程仓库  
    `git remote remove origin`

- 添加新的远程仓库  
    
## 将本地已有项目push到github中
- git remote add origin git@github.com:White-Brick/hello-world.git  
- git push -u origin master