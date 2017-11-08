#-*- coding: utf-8 -*-
#从SingleBlock.py文件加载 SPblock方法和SPblock_de方法
from  SingleBlock import SPblock
from SingleBlock import SPblock_de
# 加载binascii，然而后面没用到它
import binascii

#convert string to hex 把字符串转成hex形式
def string_to_hex(s):
    ans = 0
    # 字符串长度
    # 由于每次读8字节，所以长度应该为8
    l = len(s)
    # 循环8次
    for i in range(len(s)):
        # ord(s[i]) 把第i位字符转成二进制, 也就是取得它的ascii码值
        # ans << 8 左移8位
        # | 操作 相当于把这二个数字拼在了一起， 前面是 ans左移8位的结果，后面是 ascii码值
        ans = (ans << 8) | ord(s[i])
    # 最终得到了64位长度的数字
    return ans

#convert hex to string 把hex形式转成字符串
def hex_to_string(h):
    ans = ""
    mask = 0b11111111
    #  循环8次
    for i in range(8):
        # & 操作相当于取h的最后8位
        # chr 操作把上面&的结果(ascii码)转成字符
        # + ans 就是字符串连接
        ans=chr(h & mask)+ans
        # 右移8位，相当于抛弃了最后8位。
        # 因为刚刚已经处理了最后8位，所以可以抛弃它。
        h = h >> 8
    return ans

#ECB model. the Electronic Codebook model divides the plaintext into blocks and uses same key to encrypt.
# ECB模型，把纯文本转成块的形式，用相同的密匙加密
def MultiSPblocks(input_file, key=0x008899a123ddeeff, output_file="output"):
    # 以2进制读取的形式打开input_file
    f = open(input_file,"rb")
    # 以2进制写入的形式打开output_file
    out = open(output_file,"wb")
    key =   0x8899a123ddeeff
    # 从输入文件中读取8个字节
    block = f.read(8)
    t = 0
    show = 1
    # 打印调试信息
    if show==1:
        print "Encryption:"
    # 如果读到的8个字节不为空，则一直循环
    while block:
        t = t + 1
        # 把这8个字节转成数字
        # 并调用SPblock方法进行加密
        output = SPblock(string_to_hex(block), key)
        # 把加密结果转成文本并写入到输出文件中
        out.write(hex_to_string(output))
        # 打印调试信息
        if show == 1:
            print "block",t
            print "key:",hex(key)
            print "input:",block
            print "ciphertext:",hex(output)
        # 继续从输入文件中读取8个字节
        block = f.read(8)
    f.close()
    out.close()


#ECB model. the Electronic Codebook model divides the plaintext into blocks and uses same key to decrypt.
# ECB模型，把纯文本转成块的形式，用相同的密匙解密
def MultiSPblocks_de(input_file="output", key=0x008899a123ddeeff, output_file="redata"):
    # 以2进制读取的形式打开input_file
    f = open(input_file,"rb")
    # 以2进制写入的形式打开output_file
    out = open(output_file,"wb")
    # 从输入文件中读取8个字节
    block = f.read(8)
    t = 0
    # 打印调试信息
    show = 1
    if show==1:
        print "Decryption:"
    # 如果读到的8个字节不为空，则一直循环
    while block:
        t = t + 1
        # 把这8个字节转成数字
        # 并调用SPblock_de方法进行解密
        output = SPblock_de(string_to_hex(block), key)
        # 把加密结果转成文本并写入到输出文件中
        out.write(hex_to_string(output))
        # 打印调试信息
        if show == 1:
            print "block",t
            print "key:",hex(key)
            print "ciphertext:",hex(string_to_hex(block))
            print "output:",hex_to_string(output)
        # 继续从输入文件中读取8个字节
        block = f.read(8)
    f.close()
    out.close()

# 程序入口
if __name__=="__main__":
    #MultiSPblocks(input_file="data")
    # 加密文件 "17COP514CW.pdf"文件，并保存到"output"文件中. 
    # output_file 参数没传， 所以用的是output_file的默认值。
    # key参数也没传，所以用的也是key的默认值。
    MultiSPblocks(input_file="17COP514CW.pdf")
    #MultiSPblocks_de(output_file="redata")
    # 解密文件"output"
    # input_file参数没传，所以用的是默认值
    # key参数同理。
    MultiSPblocks_de(output_file="redata.pdf")
