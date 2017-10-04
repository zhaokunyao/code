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
 service Sorter {
 
   /**
    * A method definition looks like C code. It has a return type, arguments,
    * and optionally a list of exceptions that it may throw. Note that argument
    * lists and exception lists are specified using the exact same syntax as
    * field lists in struct or exception definitions.
    */
 
    void ping(),
 
    i32 add(1:i32 num1, 2:i32 num2),
    list<double> sort_list(1:list<double> random_double_list)
 
 }
 
