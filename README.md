# Lexical Analyzer

## Usage

```shell
./lexical_analyzer.exe /path/to/target/file
```

## C Keywords

```C++
auto, break, case, char, const, continue, default, do, double, else, enum, extern, float, for, goto, if, int, long, register, return, short, signed, sizeof, static, struct, switch, typedef, union, unsigned, void, volatile, while
```

## Output format

| type       | type_id | e.g.             |
| ---------- | ------- | ---------------- |
| number     | 1       | 114514.123E-1133 |
| string     | 2       | "hello world"    |
| character  | 3       | 'c'              |
| keyword    | 4       | if               |
| comment    | 5       | // asdfasdf      |
| delimiter  | 6       | ;                |
| operator   | 7       | ++               |
| identifier | 8       | abc_test         |
| error      | -1      |                  |

## Result

![result](.\imgs\image-20221011230138285.png)

## P.S.

本实验采用VSCode进行编程，其中`launch.json`自动添加了运行时第二个argument，即文件的路径。其中`test.c`为被实验的文件对象。
