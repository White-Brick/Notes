# Tmux

## 一、什么是tmux
Tmux是一个终端复用器（terminal multiplexer），使用tmux将会话与窗口进行分离解绑。

## 二、会话管理

1. 新建会话:  
`tmux new -s <session-name>`

2. 分离会话:  
`tmux detach`

3. 接入会话:  
`tmux attach -t 0`或者`tmux attach -t <session-name>`

4. 杀死会话:  
`tmux kill-session -t 0`或者`tmux kill-session -t <session-name>`

5. 切换会话:  
`tmux switch -t 0`或者`tmux switch -t <session-name>`

6. 重命名会话:  
`tmux rename-session -t 0 <new-name>` 

