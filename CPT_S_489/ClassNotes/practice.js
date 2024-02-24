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
function Student (name, major) {// Constructor
    this.name = name;
    this.major = major;
    // this.print = function () {
    //     console.log(this.name, ":", this.major);
    // };
    return this;
}

const s1 = new Student("wish", "cs");
const s2 = new Student("nowish", "cs");
const s3 = new Student("emma", "cs");

Student.prototype.printDetails = function () {
    console.log(this.name, ":", this.major);
};

s2.printDetails();


console.log(s1.constructor);

let o3 = { v1: 56}

let o4 = [1,2,3]

console.log(s1);
