#-*- coding: utf-8 -*-

# Substitution-Permutation block cipher:  置换分组密码
#Rijndael S-box #模型
boxdata = [[99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118], [202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192], [183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21], [4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117], [9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132], [83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207], [208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168], [81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210], [205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115], [96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219], [224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121], [231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8], [186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138], [112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158], [225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223], [140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22]]
def S_box(t):
    # 掩码
    mask =  0b00001111
    print mask;
    # 与操作,  相当于只保留了t的最后4位
    valuey = mask & t
    # 对mask进行取反操作，-1 * (mask+1)， 然后是与操作, 
    # 以及 右移4位，相当于除以  2的4次方
    valuex = (~mask & t)>>4
    # 返回2维数组中的值
    return boxdata[valuex][valuey]

#Rijndael S-inv-box 模型
invboxdata = [[82, 9, 106, 213, 48, 54, 165, 56, 191, 64, 163, 158, 129, 243, 215, 251], [124, 227, 57, 130, 155, 47, 255, 135, 52, 142, 67, 68, 196, 222, 233, 203], [84, 123, 148, 50, 166, 194, 35, 61, 238, 76, 149, 11, 66, 250, 195, 78], [8, 46, 161, 102, 40, 217, 36, 178, 118, 91, 162, 73, 109, 139, 209, 37], [114, 248, 246, 100, 134, 104, 152, 22, 212, 164, 92, 204, 93, 101, 182, 146], [108, 112, 72, 80, 253, 237, 185, 218, 94, 21, 70, 87, 167, 141, 157, 132], [144, 216, 171, 0, 140, 188, 211, 10, 247, 228, 88, 5, 184, 179, 69, 6], [208, 44, 30, 143, 202, 63, 15, 2, 193, 175, 189, 3, 1, 19, 138, 107], [58, 145, 17, 65, 79, 103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115], [150, 172, 116, 34, 231, 173, 53, 133, 226, 249, 55, 232, 28, 117, 223, 110], [71, 241, 26, 113, 29, 41, 197, 137, 111, 183, 98, 14, 170, 24, 190, 27], [252, 86, 62, 75, 198, 210, 121, 32, 154, 219, 192, 254, 120, 205, 90, 244], [31, 221, 168, 51, 136, 7, 199, 49, 177, 18, 16, 89, 39, 128, 236, 95], [96, 81, 127, 169, 25, 181, 74, 13, 45, 229, 122, 159, 147, 201, 156, 239], [160, 224, 59, 77, 174, 42, 245, 176, 200, 235, 187, 60, 131, 83, 153, 97], [23, 43, 4, 126, 186, 119, 214, 38, 225, 105, 20, 99, 85, 33, 12, 125]]
def S_inv_box(t):
    mask =  0b00001111
    valuey = mask & t
    valuex = (~mask & t)>>4
    return invboxdata[valuex][valuey] 

#To get the next round key 计算下一个key的值
def next_key(key):
    # 初始化一个dict 字典
    b = {}
    # 掩码
    mask = 0b11111111
    # 循环8次 i =0,1,2,3,4,5,6,7
    for i in range(8):
        # 执行   与 操作
        b[7-i] = (key & mask)
        # key 右移8位，相当于除以2的8次方
        key = key >> 8
    # 初始化ans为0
    ans = 0
    # 循环8次 i =0,1,2,3,4,5,6,7
    for i in range(8):
        # 如果是偶数次的循环
        if i % 2==0:
            # ans 左移8位，相当于乘以2的8次方, 之后是异或操作、或操作
            ans = (ans << 8) | (b[i] ^ b[i+1])
        # 奇数次的循环
        else:
            # ans 左移8位， 再与S_box的结果进行 或 操作
            ans = (ans << 8) | S_box(b[i])
    # 返回ans
    return ans

#Byte sub function, call S_box 字节化处理
def Substitution(state):
    res = 0
    t = 0
    mask = 0b11111111
    #  循环8次 i=0,1,2,3,4,5,6,7
    for i in range(8):
        # S_box的结果以及mask做与操作， 然后左移 t 位， 再与res做或操作.
        res = (S_box(state & mask) << t) | res
        # state 右移8位
        state = state >> 8
        # t+=8
        t = t + 8
    return res

#Byte inv-sub function,  call S_inv_box 字节化处理
def Substitution_inv(state):
    res = 0
    t = 0
    mask = 0b11111111
    for i in range(8):
        res = (S_inv_box(state & mask) << t) | res
        state = state >> 8
        t = t + 8
    return res

#b0 b1 ...b63, get the t(th) binary, support function for transpose 得到第t个字节码
def get_t(state, t):
    return (state>>(63-t)) & 1

#b0 b1 ...b63, set the t(th) binary,support function for transpose  设置第t个字节码
def set_t(state, t, s):
    return state | (s<<(63-t))

#transpose the row and col in state 置换行和列
def transpose(state):
    res = 0
    for i in range(8):
        for j in range(8):
            res = set_t(res, i*8+j, get_t(state, j*8+i))
    return res

#shift n binary to right 二进制右移操作
def shift(col, n):
    return ((col & ((1<<n)-1))<<(8-n)) | col>>n 

#shift n binary to left 二进制左移操作
def shift_inv(col, n): 
    return shift(col, 8-n)

#the basic permutation operation, first transpose the "matrix" and do the row-shift. At last, we transpose the results of shift to get the final results
# 基本置换操作，先置换矩阵，完成行变化，最后再置换中间结果，得到最后答案
def Permutation(state):
    # 调用transpose方法
    state = transpose(state)
    res = 0
    t = 0
    mask = 0b11111111
    # 循环8次
    for i in range(8):
        # 调用shift方法并左移t位，然后 与 res做或操作
        res = (shift(state & mask, 7-i) << t) | res
        # state 右移8位
        state = state >> 8
        # t+=8
        t = t + 8
    # 调用transpose方法 
    return transpose(res)

#similar with Permutation, only change right shift to left shift. #与Permutationc相似
def Permutation_inv(state):
    state = transpose(state)
    res = 0
    t = 0
    mask = 0b11111111
    for i in range(8):
        res = (shift_inv(state & mask, 7-i) << t) | res
        state = state >> 8
        t = t + 8
    return transpose(res)

#Main function for encryption; do 5 rounds #加密主函数
def SPblock(input, key):
    #       异或 操作 
    state = input ^ key
    #  循环 5次  i = 0,1,2,3,4
    for i in range(5): 
        # 调用Substitution方法 
        state = Substitution(state)
        # 如果不是最后一次循环
        if i!=4:
            # 调用Permutation方法
            state = Permutation(state)
        # 调用next_key方法
        key = next_key(key)
        # 异或操作
        state = state ^ key
    #  返回state, 也就是加密之后的数字
    return state

#Main function for decryption. The decryption algorithm is the inverse process of the encryption. 
#The inverse S-box and permutation operation is applied in this process. 
#At the same time the order of operations in each round is reverse. And the round keys are used in reverse order too
#解密主函数，加密函数的反操作。
def SPblock_de(input, key):
    state = input
    keyd = {}

    # 循环 0，1，2，3，4，5
    for i in range(6):
        #  把保存到字典中
        keyd[i] = key
        # 调用next_key方法
        key = next_key(key)

    # 循环5次， i=4,3,2,1,0
    for i in range(0,5)[::-1]:
        # 异或操作
        state = state ^ keyd[i+1]
        # 如果不是第一次循环
        if i!=4:
            # 调用Permutation_inv方法
            state = Permutation_inv(state)
        # 调用Substitution_inv方法
        state = Substitution_inv(state)
    # 异或
    state = state ^ keyd[0]

    return state

# 程序入口
if __name__=="__main__":
    # 输入
    input = 0x1122334455667788
    # 密钥
    key =   0x008899a123ddeeff
    # 输出
    output = SPblock(input, key)
    # 1 6   进制输出 input
    print "input:",hex(input)
    # 1 6进制输 出      output
    print "ciphertext:",(hex(output))
    # 16进制输出解密的  结果    
    print "decryption output:",(hex(SPblock_de(output, key)))
