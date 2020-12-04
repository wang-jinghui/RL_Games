## tic_tac_toe

1. python3 version
   - 更新了hash()
   - 升级state可视化效果(彩色)
   - hash_val <-> state 的互相转换
   
2. C++ version


#### stateType.h
变量:
1. data状态数组
2. winner玩家[1:0,-1:X]
3. hash_val状态哈希值
4. end结束标志

方法:
1. stateType(),默认构造函数,初始化变量data, winner, hash_val, end
2. hash(),计算返回状态的哈希值
3. ie_end(),判断游戏是否结束并返回状态标志
4. next_state(),接受新的动作,并返回新的状态
5. print_state(),格式化输出状态
6. get_state(),返回状态数组
7. get_winner(),返回当前赢家,如果返回0,则谁也不赢

#### playerType.h
变量:
1. map<int, double> estimations: $(s, value)$ table
2. step_size: ~ learning rate
3. epsilon: 随机探索概率
4. vector<stateType> states : 每个回合的状态列表
5. vector<int> greedy : 动作选择flag,1 greedy choice, 0 random choice
6. symbol : 1:O, -1:X

方法:
1. playerType():初始化step_size, epsilon, symbol
2. reset():清空states, greedy
3. set_symbol():初始化symbol, estimations
4. backup():回合结束后根据状态序列差值更新estimations
5. random_proba():生成一个0~1之间的随机小数
6. action():根据states中最后一个状态,产生下一步的动作
7. save_policy():把estimations写入文件
8. load_policy():加载保存的estimaions

#### judgerType.h

变量:
1. p1,p2 : playerType类的实例
2. states : vector类型记录一轮的状态

方法:
1. reset() : 重置p1, p2
2. play() : 互博
3. get_states() : 返回states

#### humanType.h

1. symbol : 符号
2. action_dict : 键盘按键到动作的映射,map<char, pair<int, int> >
3. action : 根据键盘的输入,返回对应的动作, pair<int, int>

#### main.c

1. 机机互搏
2. 人机互搏
