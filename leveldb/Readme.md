#util/logging.cc
`util/logging.h`

    `<endian.h>`
`port/atomic_pointer.h`
    std::atomic 并行编程
    explicit 只用于构造函数，禁止隐式转化:
        class A { explicit A(string a)};  A aa = "xxx"; 用来禁止这种行为

`fread_unlocked`
`fwrite_unlocked`
`fflush_unlocked`

Each  of  these functions has the same behaviour as its counterpart without the `_unlocked` suffix, 
except that they do not use locking 
(they do not set locks themselves, and do not test for the presence  of  locks  set  by others) 
and hence are thread-unsafe.  See flockfile(3).


`fdatasync`
flushes all data buffers of a file to disk (before the system call returns).  
It resembles fsync but is not required to update the metadata such as access time.

Applications that access databases or log files often write a tiny data fragment 
(e.g., one line in a log file)
and  then call fsync immediately in order to ensure that the written data is physically stored on the harddisk.
Unfortunately, fsync will always initiate two write operations: 
one for the newly written data and another  one in  order  to  update  the modification time stored in the inode. 
If the modification time is not a part of the transaction concept fdatasync can be used to avoid unnecessary inode disk write operations.


类的static property 初始化： 
(1)初始化在类体外进行(.cpp文件中)，而前面不加static，以免与一般静态变量或对象相混淆。
(2)初始化时不加该成员的访问权限控制符private，public等。
(3)初始化时使用作用域运算符来标明它所属类，因此，静态数据成员是类的成员，而不是对象的成员。
`City * City::_instance = NULL;`
`pthread_mutex_t City::_mutex;` 这句是否有必要？

类的const property 初始化：
`A::A(int a):bb(a) { //常成员的初始化` 通过列表进行


singleton:
`
typedef pthread_once_t OnceType;
extern void InitOnce(OnceType* once, void (*initializer)());

void InitOnce(OnceType* once, void (*initializer)()) {
  PthreadCall("once", pthread_once(once, initializer));
}
// 初始化
static pthread_once_t once = PTHREAD_ONCE_INIT; 
`



```
static void PthreadCall(const char* label, int result) {
    if (result != 0) {
        fprintf(stderr, "pthread %s: %s\n", label, strerror(result));
        abort();
    }
}

Mutex::Mutex() { PthreadCall("init mutex", pthread_mutex_init(&mu_, NULL)); }
```



