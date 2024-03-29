let add  = function (x,y) {
    x = y;
    return x + y;
}

let addO  = function (o) {
    o.x = o.y;
    return o.x + o.y;
}


let num = {
    x:1,
    y:2
}

let x= 1;
let y = 2;

console.log(add(x,y));
console.log(x,y)

console.log(addO(num));
console.log(num.x,num.y)

// If you pass a reference type through function, changes are saved whereas primitive types are not 

// primitive types
// int, bigint , string, bool null, symbol (), undefied guarrenteed to be uniqe
// object array function - reference types

// expression - something that can be put within a console.log()
// statement - the console.log(0)
// loosely typed language - not require a variable to be defined or classified by its data type - implicit datatype 
// Dynamically typed language - the type of variable is unknow at compile time
let i = -2;
while (i <0) {
    console.log("aaaa");
    i++;
}

function normal_unction() {
    console.log('salkfj');
}

// anonymus funciton
(function (a) {

})

// Arrow functions
()=>{
    
}

for (let step = 0; step< 5; step++){
    console.log("fkjls")
}
``

let where = function () {
    
}

function ifdsfs () {

}