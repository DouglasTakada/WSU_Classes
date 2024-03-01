// console.log("HEllo World!");
// JS does not have int and folat/double only number variable
//Prrimitive types
let a = 10;
let b= 10.6; // Type number
let c= "CPOTS"; //String
let d= false; // Boolean
let e = null; // object
let f; //Undefined
let g = Symbol("eecs");
let bi = 109878910n; // Type bigint
// End of Primitive types

//Complex types - reference types - always allocated in head 
let h = {
    name: "tim",
    dept: "eecs",
}; // Object

let i = [1,2,3]; // Array

let j = function (x,y){
    return x+ y;
} // Function

//End of Complex types

let nums = {// Objects are key-value pairs
    x:2,
    y:3,
    print: function () { //symblo: value
        console.log(this.x,this.y);
    }
}
nums.print()
function addObject(o){
    return o.x+o.y;
}

addObject(nums);

let n1= 2;
let n2 =3;

function addPrimitives(num1, num2){
    return num1 + num2;
}

addPrimitives(n1,n2)

let o = {
    name: "TIm",
    dept: "eecs",
    awards: null
};

// let s = new String('dougl');
// console.log(s.toUpperCase());
// console.log("EMMA".toLowerCase()); // This works because of wrapper classes

// Autoboxing boxes the type to the correct object to call the appropreate method

//expression always evaluates to value

//simpliest expression is literal

//statement is when an assignment is involved
//      stmt  true: false
//let n = n <5 ? 0 : 100;

//https://ecma-international.org/publications-and-standards/standards/ecma-262/

//Arrays are same as object - key value pairs

const o1 = {
    x:10,
    y:20,
    add: function () {
        return this.x + this.y;
    },
};

const o2 = {
    x: 15,
    y:25,
};

console.log(o1.add());
console.log(o1.add.call(o2)); //overwriting function to take in different object


//Method call vs function call
// function Student (name, major) {// Constructor
//     this.name = name;
//     this.major = major;
//     // this.print = function () {
//     //     console.log(this.name, ":", this.major);
//     // };
//     // return this;
// }

// function GradStud (name, major,thesis) { // Class student and gradstud has a lot of similarities
//     Student.call(this,name,major);
//     this.thesis = thesis;
// }

// const s1 = new Student("wish", "cs");
// const s2 = new Student("nowish", "cs");
// const s3 = new Student("emma", "cs");
// const s4 = new Student.call({},"Wish","cs");
// const s5 = new GradStud("Wi","cs","relational_patterns");

// console.log(s5);

// Student.prototype.C = function () { //Prototype object is a reference to the parent object
//     //Creating a property in the parent so there is not multiple copies of the prototype
//     console.log(this.name, ":", this.major);
// };

class Student {
    constructor(name, major){
        this.name = name;
        this.major = major;
    }
    print() {
        console.log(this.name, ":", this.major);
    };
}

class GradStud extends Student {
    constructor(name, major,thesis){
        super(name,major);
        this.thesis = thesis;
    }
    print() {
        console.log(this.name, ":", this.major,":",this.thesis);
    };
}

const s1 = new Student("wish", "cs");
const s2 = new GradStud("wish", "cs","nono");

s1.print();
s2.print();

// GradStud.prototype.C = Object.create(Student.prototype);

// s2.C();
// s5.C();


// console.log(s1.constructor);

let o3 = { v1: 56}

let o4 = [1,2,3]

// console.log(s1);


// New lecture

// function add(x:any, y:any): any
// function add(x,y){
//     return x + y

// }


function ho_function() {
    return function (x,y){
        return x + y;
    };
}
// lexical environment record is the parent record/ global record.
// closure: JS knows to keep which variables around in the global scope so you do not have a issue. This only applies when a function is returned
function inc() {
    const incVal = 1; // kept in lexical environment record if a function uses it
    return function (x){
        return x + incVal;
    };
}

const fun = ho_function();
console.log(fun(1,2))

const fun1 = inc();
console.log(fun1(10));

// const util = require_util();

// util.setVal(100);

// console.log(util.getVal());

// const util = require("./util")

// console.log(util)

// import valC from "./util.js";

// console.log(valC);

//Map filter reduce

let arr = [1,2,3,4,5,6,7,8,9]


function isEven(x) {
    return x%2 ==0;
}

let arr1 = arr.filter(isEven);// filter input must be a boolean returing function

function sq(x){
    return Math.pow(x,2);
}

let arr2 = arr1.map(sq);//Map input must take one input and return one value

console.log(arr1);

function add(x,y){//Reduce takes two elements
    return x + y;
}

console.log(arr2);

let result = arr2.reduce(add,0);

console.log(result);


