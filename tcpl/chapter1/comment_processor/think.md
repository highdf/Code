### test

#### test 目录与expect目录
命名以数字开始，逐个递增。方例进行循环遍历。
动作：open  "test/number"文件，作为main.c的输入，结束后对比expect/number文件是否一致。不一致 -> 记录error ++, 
