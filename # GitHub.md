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

- 查看仓库状态
    `git status`

- 查看文件差异
    `git diff readme.md`

- 查看提交日志
    `git log`


## 配合github使用远程仓库

