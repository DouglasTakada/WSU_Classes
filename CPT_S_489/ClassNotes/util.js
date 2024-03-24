// function require_util(){
//     console.log("Loaded Util")

let val = 11;

export default class valClass {
    constructor(val){
        this.val = val;
    }
}

export function getVal(){
        return val;
    }

    console.log(module);

// module.exports = {
    
//     getVal:getVal,
// }

//     function setVal(new_val){
//         val = new_val;
//     }

//     return { // This allows 
//         // val: val,
//         //If you don't want anyone to change the value in outside of util js then don't export the function that can modify the values
//         getVal:getVal,
//         setVal:setVal,
//     }
// }


