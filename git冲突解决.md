 同事在使用git pull代码时，经常会碰到有冲突的情况，提示如下信息：

```
error: Your local changes to 'c/environ.c' would be overwritten by merge.  Aborting.
Please, commit your changes or stash them before you can merge.
```

这个意思是说更新下来的内容和本地修改的内容有冲突，先提交你的改变或者先将本地修改暂时存储起来。

下面就来分享一下处理冲突的方式，如果你是用的是TortoiseGit可以参考方案一，如果你更喜欢命令行，你就参考方案二：使用gitstash命令进行处理。

### 一、使用TORTOISEGIT处理代码冲突

#### 场景一：

```
user0 有新提交

user1 没有pull -> 写新代码 -> pull -> 提示有冲突
```

 解决办法一： 

```
-> stash save(把自己的代码隐藏存起来) -> 重新pull -> stash pop(把存起来的隐藏的代码取回来 ) -> 代码文件会显示冲突 -> 右键选择edit conficts，解决后点击编辑页面的 mark as resolved->  commit&push
```

 解决办法二： 

```
-> stash save(把自己的代码隐藏存起来) -> 重新pull -> stash pop(把存起来的隐藏的代码取回来 ) -> 代码文件会显示冲突 -> 右键选择resolve conflict -> 打开文件解决冲突 ->commit&push
```

#### 场景二：

```
user0 有新提交

user1 没有pull -> 写新代码 -> commit&push -> 提示有冲突
```

解决办法：

```
-> pull -> 代码文件会显示冲突 -> 右键选择edit conficts，解决后点击编辑页面的 mark as resolved -> commit&push
```

### 二、使用GIT命令处理代码冲突

1、先将本地修改存储起来

```
 $ git stash

 这样本地的所有修改就都被暂时存储起来 。是用git stash list可以看到保存的信息：

 git stash暂存修改

 git stash暂存修改

 其中stash@{0}就是刚才保存的标记。
```

 2、pull内容 

```
 暂存了本地修改之后，就可以pull了
```

 3、还原暂存的内容 

```
 $ git stash popstash@{0}

 系统提示如下类似的信息：   
 Auto-mergingc/environ.c
CONFLICT(content): Merge conflict in c/environ.c
意思就是系统自动合并修改的内容，但是其中有冲突，需要解决其中的冲突。
```

 4、解决文件中冲突的的部分 

```
 打开冲突的文件，会看到类似如下的内容：

 git冲突内容

 git冲突内容

 其中Updatedupstream 和=====之间的内容就是pull下来的内容，====和stashed changes之间的内容就是本地修改的内容。碰到这种情况，git也不知道哪行内容是需要的，所以要自行确定需要的内容。
```

 解决完成之后，就可以正常的提交了。 