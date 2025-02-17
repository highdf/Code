### 算法
接口： result file(FILE *) comment_processor(FILE *source_file) 
第一步：检验argment是否非空 -> 空, 打印错误信息
                            -> 非空：执行P0
P0: 创建result_file result, 以字符流读入，更新当前模式，根椐当前模式执行动作

模式：char_mode, string_mode, comment_mode, normal_mode,  

comment_mode: 如何处理
获取第二字符：判断 switch '/' or '"" or other 
'/' -> processor line commnet
'"" -> processor block comment
other -> 向target_file写入'/' + other

line comment: 直到'\n'为止，向target_file写入'\n'
blick comment: 直到"*/"为止, 向target_file写入'\n'

current_mode = ESCAPE_MODE or PREFIX_COMMENT_MODE  || enbale_conn = 1
何时关闭？
enable_conn 何时关闭
comment_mdoe?何时更新
