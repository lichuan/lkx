# Lkx language
**Lkx** is a new *strongly typed* scripting language, simpler and faster than lua. It can easily interact with ***c/c++***, the name **Lkx** comes from my daughter's name (***Li Kaixin***), so this language is also a gift for my daughter.

# Design Principles
- **simple and clear**
- **variable typed**
- **hot reloading**
- **garbage collection**
- **user defined structure**
- **shared function**
- **shared variable**
- **faster than Lua**
- **c-like syntax**
- **strictly consistent**
- **convention-based**

# Build Lkx
Lkx is written in standard C, so you can build it on any platform which support standard C. However, Lkx only supports 64-bit platform, please make sure that your platform can run 64-bit program. I personally like to work under the Linux operating system, so the **Lkx repo** on github is also the result of my work under Linux. If you also need to build Lkx on Linux, just run the **`./build.sh`** script directly.

# Lkx overview
- ## Variable Type
| supported type |  description|
|------   |    ------   |
|bool    | *boolean value, true or false* |
|double  | *double precision floating point* |
|string   | *sequence of characters* |
|int64    | *signed int of 64 bits*    |
|[int64]  | *array of int64* |
|[bool], [double], [string] | *array of bool, double, string* |
|{int64} | *unordered set of int64* |
|{m int64} | *unordered multi set of int64* |
|{o int64} | *orderded set of int64* |
|{mo int64} | *ordered multi set of int64* |
|{string}, {m string} | *unordered set of string, unordered multi set of string* |
|{o string}, {mo string} | *ordered set of string, ordered multi set of string* |
|{int64:string} | *unordered map, key type: int64, value type: string* |
|{string:string} | *unordered map, key type: string, value type: string* |
|{m string:int64} | *unordered multi map* |
|{o int64:int64} | *ordered map* |
|{mo string:[int64]} | *ordered multi map, value type: array of int64* |

- ## Module unit
In Lkx, each source file is a module, and each file has a consistent code layout, the source file is logically divided into several parts, each part must be separated by a blank line.  

The 1st part is the import statement, which imports shared variables and functions from other files:  
```go
import "family/lib/utils.lkx"
import "family/sister/info.lkx"
```
The 2nd part is the declaration and initialization of variables, the shared variable must be declared before the local variable:  
```c
shared string brother_name = "bob"
uint32 brother_height = 170
uint32 brother_weight = 55
uint32 brother_age = 31

```
The 3th part is the definition of the function, shared functions must be defined before local functions, and each function must be separated by a blank line:  
```c
shared bool brother_is_giant()
{
  return is_a_giant(brother_height, brother_weight)
}

shared void brother_grow_up()
{
  brother_height += 10
  brother_weight += 20
}

bool brother_older_than_sister()
{
  return brother_age >= sister_age
}
```
The 4th part is the hot reloading hook function, which is used to control whether the variables declared in the current module need to be reinitialized during hot reloading:  
```c
internal void _lkx_hot_reloading_()
{  
}

internal void _lkx_pre_hot_reloading_()
{
}

internal void _lkx_post_hot_reloading_()
{
}
```
The source code for this sample file *(`"family/brother/info.lkx"`)*:  
```go
import "family/lib/utils.lkx"
import "family/sister/info.lkx"

shared string brother_name = "bob"
uint32 brother_height = 170
uint32 brother_weight = 55
uint32 brother_age = 31

shared bool brother_is_tall()
{
  if(brother_height < TALL_CM)
  {
    return false
  }
  
  return true
}

shared bool is_older_brother()
{
  return brother_older_than_sister()
}

shared bool brother_is_giant()
{
  return is_a_giant(brother_height, brother_weight)
}

shared void brother_grow_up()
{
  brother_height += 10
  brother_weight += 20
}

bool brother_older_than_sister()
{
  return brother_age >= sister_age
}

internal void _lkx_hot_reloading_()
{  
}

internal void _lkx_pre_hot_reloading_()
{
}

internal void _lkx_post_hot_reloading_()
{
}
```

- ## Hot reloading
Lkx code is usually called by a c/c++ host program. After we have developed a project and run it for some time, we may need to modify the variables and functions in the script to meet some new requirements. In this case, Lkx can reload the modified script code without restarting the c/c++ host program.  

Before the hot reloading of Lkx script, each variable in the script has been given the corresponding value by many executed functions. During hot reloading, we need to decide which variables should remain unchanged and which variables must be reinitialized based on business logic. Fortunately, Lkx provides an internal hot reloading hook function: **`_lkx_hot_reloading_()`**, In this function, you can specify which variables should remain unchanged during the hot reloading process, as follows *(`"family/lib/utils.lkx"`)*:
```c
shared uint32 TALL_CM = 190
shared uint32 FAT_KG = 90
uint32 GIANT_CM = 300
uint32 GIANT_KG = 500
uint32 call_giant_count = 0

shared bool is_a_giant(uint32 height, uint32 weight)
{
  if(height < GIANT_CM)
  {
    return false
  }

  if(weight < GIANT_KG)
  {
    return false
  }

  ++call_giant_count
  return true
}

internal void _lkx_hot_reloading_()
{
  _lkx_remain_unchanged_ = [call_giant_count]
}
```
The **`call_giant_count`** variable is added to an array called **`_lkx_remain_unchanged_`** to tell the interpreter that this variable needs to remain unchanged during hot reloading.

- ## User structure
In order to keep the simplicity of Lkx language, the syntax for defining a structure class with data and functions is not supported in script code, but you can define it in c/c++ code and then export it to the script.  

In Lkx's c/c++ api, there are two types of struct: inner struct and outer struct. There are two main differences between them:
1. **The inner struct is usually created by the Lkx script, and its attribute members can be directly accessed; the outer struct is usually created by the c/c++ host, and its members can only be accessed through member functions in the script.**

2. **The inner struct is created by the script, so its GC should also be processed by the Lkx interpreter, while the outer struct is created by the c/c++ host, so the interpreter usually does not need to process its GC.**

In addition, you can also assign an outer struct to a data member of an inner struct, the following example shows how to export the inner and outer struct to the Lkx script:
```c
typedef int (*lkx_Func)(lkx_Hub*);

typedef struct lkx_Reg_Func {
  const char *name;
  lkx_Func func;
} lkx_Reg_Func;

typedef struct lkx_Reg_Attr {
  const char *name;
  const char *type;
} lkx_Reg_Attr;

int main()
{
  lkx_Hub *lkx_hub = lkx_new_hub();
  lkx_init(lkx_hub, "./deploy/script/family/hub.lkx");
  lkx_load(lkx_hub);

  //outer struct CUser
  lkx_Reg_Func cuserfuncs[] =
  {
    {"get_id", lkx__CUser__get_id},
    {"get_name", lkx__CUser__get_name},
    {"send_msg", lkx__CUser__send_msg},
    {"save_data", lkx__CUser__save_data},
    {NULL, NULL}
  };

  //inner struct User
  lkx_Reg_Attr userattrs[] = {
    {"level", "uin32"},
    {"cuser", "CUser"},
    {"country", "string"},
    {"money", "uint32"},
    {"children", "[User]"},
    {NULL, NULL}
  };

  //outer struct CUser
  lkx_reg_outer_struct(lkx_hub, "CUser", cuserfuncs);
  lkx_reg_struct_metafunc(lkx_hub, "CUser", "__hash__", lkx__CUser____hash__, 1);
  lkx_reg_struct_metafunc(lkx_hub, "CUser", "__m_hash__", lkx__CUser____m_hash__, 2);
  lkx_reg_struct_metafunc(lkx_hub, "CUser", "__o_compare__", lkx__CUser____o_compare__, 0);
  lkx_reg_struct_metafunc(lkx_hub, "CUser", "__mo_compare__", lkx__CUser____mo_compare__, 0);

  //inner struct User
  lkx_reg_inner_struct(lkx_hub, "User", userattrs);
  lkx_reg_struct_metafunc(lkx_hub, "User", "__hash__", lkx__User____hash__, 1);
  lkx_reg_struct_metafunc(lkx_hub, "User", "__m_hash__", lkx__User____m_hash__, 2);
  lkx_reg_struct_metafunc(lkx_hub, "User", "__o_compare__", lkx__User____o_compare__, 0);
  lkx_reg_struct_metafunc(lkx_hub, "User", "__mo_compare__", lkx__User____mo_compare__, 0);

  //other code in main......
  ......
}
```

- ## Convention
Precedence of convention over complex syntax is a design principle of the Lkx language.
In Lkx, the file paths in the **`import`** statement are all prefixed with a unified project related name, which can reduce name conflicts throughout the entire project, as follows:
```go
import "family/father/info.lkx"
import "family/mother/info.lkx"
import "family/brother/info.lkx"
```
Because shared variables and functions can be accessed in all script files, it is best to add meaningful prefix characters when naming them. For example, in the following lkx script file *(`path: "family/brother/info.lkx"`)*, variables are prefixed with "*brother_*":
```go
import "family/lib/utils.lkx"
import "family/sister/info.lkx"

shared string brother_name = "bob"
uint32 brother_height = 170
uint32 brother_weight = 55
uint32 brother_age = 31
```
Lkx does not support the const keyword, if you want to define a constant, you can change the name of the variable to uppercase. In Lkx script, the uppercase variable name represents a constant. This is also the design philosophy of Lkx based on convention:
```c
shared uint32 TALL_CM = 190
shared uint32 FAT_KG = 90
uint32 GIANT_CM = 300
uint32 GIANT_KG = 500
uint32 call_giant_count = 0
```

- ## Variable initialization
  All variables declared in the Lkx file will be initialized to their corresponding values by the interpreter:
  - numeric variable is initialized to `0`
  - bool variable is initialized to `false`
  - array is initialized to `[]`
  - set is initialized to `{}`
  - map is initialized to `{:}`
  - struct variable is initialized to `null`

- ## Hub file
When the Lkx interpreter parses the import statement, it will find the corresponding source file according to the **`__lkx_import_path_from_c_workdir__`** set in the hub file. In addition, the hub file must import all other source files of the project, because the first file read by the interpreter is the hub file, and then parse other imported files in turn.
```go
[string] __lkx_import_path_from_c_workdir__ = 
[
  "./deploy/script/",
  "./deploy/script/3rdlib/",
  "./deploy/goolge/lkxlib/",
  "./deploy/tesla/lkxlib/",
  "./deploy/apple/lkxlib/"
]

import "family/father/info.lkx"
import "family/mother/info.lkx"
import "family/brother/info.lkx"
```

- ## Timer
As a scripting language, Lkx itself does not provide any timer functions, but you can easily implement it. As shown below, you can periodically call a script function in the main loop of c/c++to implement a timer:
```c
while(true)
{
  sleep(1);
  lkx_call(lkx_hub, "timer_func_per_second");
}
```

- ## Multithreading
lkx_Hub is the execution environment in Lkx, and each script function call runs inside a specific lkx_Hub. Each lkx_hub is an independent sandbox, so you can run different lkx_Hubs on different threads to get multithreading support. However, multithreaded programming is not easy and requires you to be more careful.

- ## Lkx vs Lua
  - simpler than Lua
  - more consistent than Lua
  - faster than Lua
  - better looking in Lkx than Lua
  - without Lua's ugly **`if end`** block
  - Lua is not strongly typed, so it is not suitable for large programs

# Implementation
- **cimpl**\
  *c impl of Lkx, main part of my work.*
  
- **csimpl**\
  *c# impl of Lkx, need your contribution.*
- **javaimpl**\
  *java impl of Lkx, need your contribution.*
- **pyimpl**\
  *python impl of Lkx, need your contribution.*
- **goimpl**\
  *go impl of Lkx, need your contribution.*

# Contact
If you're interested in Lkx language, join the telegram group: [*https://t.me/lkx_language*](https://t.me/lkx_language)


