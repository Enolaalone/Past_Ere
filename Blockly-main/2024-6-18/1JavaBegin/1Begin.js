console.log("Hello, World!");

//变量赋值
a = 5;
b = 6;
c = a + b;
console.log(c);


//JavaScript 使用关键字 let来定义变量， 使用等号来为变量赋值：
let x = 5;
let y = 6;
let z = x + y;

//赋值运算
x = 5
y = 6
z = (x + y) * 10
console.log(z)

//JavaScript 拥有动态类型
// JavaScript 拥有动态类型。这意味着相同的变量可用作不同的类型：
let k = 5
console.log(k)
k = 'hi'
console.log(k,k.length)//输出字符串长度
k = true //BOOL
console.log(k)

// JavaScript 数组
// 下面的代码创建名为 cars 的数组：

let car = new Array(1)
car[0] = 'a'
cars=["Saab","Volvo","BMW","Saab","Volvo","BMW"];
console.log(cars)

// JavaScript 对象  (字典)
let  person={
    firstname : "John",
    lastname  : "Doe",
    id        :  5566
};
console.log(person.firstname)
console.log(person['lastname'])

//字符串
let my_word = `${56+78}
                            我
                            爱
                            你` //${}  format 格式及其分行 使用 ` `  代替单双引号
console.log(my_word)

//函数
function myFunction(id)
{
    let x=id;  // x 区别与 全局变量
    return x;
}
y = myFunction(12345)
console.log(x,y)
x = 6
console.log(x)

//条件语句 符合C 语言语法
//if else
let time = 12;
if (time<20)
{
    x="Good day";
}
else
    x="Good evening";
//for
for (let i=0;i<cars.length;i++)
{
    console.log(i);
}
//while
let i=0
while (i<5)
{
    console.log(i);
    i++;
    if(i===2)
        continue //continue
    if (i===3)
        break //break
}

//面向对象
class Student {
    constructor(name, year) {//初始化
        this.name = name;
        this.year = year;
    }
    age(x) {
        return x - this.year;
    }
}

let s = new Student('jj',12)//新建立对象用new
console.log(s.year,s.name,s.age(16))
