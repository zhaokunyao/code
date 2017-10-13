  /**
  * The first thing to know about are types. The available types in Thrift are:
  *
  *  bool        Boolean, one byte
  *  i8 (byte)   Signed 8-bit integer
  *  i16         Signed 16-bit integer
  *  i32         Signed 32-bit integer
  *  i64         Signed 64-bit integer
  *  double      64-bit floating point value
  *  string      String
  *  binary      Blob (byte array)
  *  map<t1,t2>  Map from one type to another
  *  list<t1>    Ordered list of one type
  *  set<t1>     Set of unique elements of one type
  *
  * Did you also notice that Thrift supports C style comments?
  */
 
 
 /**
  * Ahh, now onto the cool part, defining a service. Services just need a name
  * and can optionally inherit from another service using the extends keyword.
  */
  /**服务名称 Sorter 这个我理解可以随便写
  **/
 service Sorter {
 
   /**
    * A method definition looks like C code. It has a return type, arguments,
    * and optionally a list of exceptions that it may throw. Note that argument
    * lists and exception lists are specified using the exact same syntax as
    * field lists in struct or exception definitions.
    */

    /**
     * 下面约定接口格式
     * 所谓接口，就是服务端(server)提供哪些服务，以函数的形式来提供
     * 客户端(client)可以调用这些接口，也就是调用这些函数。
     * 函数的参数由客户端传入， 
     * 函数的返回值由服务端返回给客户端。
     **/
 
    /**
     * 第一个接口  ping  无参数， 无返回值所以是void
     * 这个接口是我搞来玩的
    **/
    void ping(),
 
    /**
     * 第二个接口，  add   参数是二个i32,就是2个整数。参数名分别是num1和num2
     * 返回值也是i32， 也是个整数。
     * 这个接口也是我搞来玩的
     */
    i32 add(1:i32 num1, 2:i32 num2),

    /**
     *第三个接口， 参数是一个 list<double> 就是由double构成的数组。 参数名是 random_double_list
     *它的返回值也是一个list<double> 就是由double构成的数组。
     */
    list<double> sort_list(1:list<double> random_double_list)
 
 }
 
