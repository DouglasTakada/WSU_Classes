const sqlite3 = require('sqlite3').verbose();
const db = new sqlite3.Database('./database/cmsdb.sqlite');

// let sql = `SELECT * FROM USER`;
// db.all(sql, [], (err, rows) => {
//   if (err) {
//     throw err;
//   }
//   rows.forEach((row) => {
//     console.log(row.username);
//   });
// });

let sql = `SELECT * FROM USER WHERE username=? AND password=?`;


function getRow(sql, values){
    return new Promise((resolve,reject) =>{
        db.get(sql, values, (err, row) => {
            if (err) {
              reject(err);
            }
            else{
                resolve(row);
            }
        });
    })
}

// function getRowTest() {
//     const row = getRow(sql,['subu','1234']).then((row)=>console.log(row))
// }

// getRowTest()

// async function getRowTest() {
//     let row = await getRow(sql,['subu','1234'])
//     console.log(row)
// }

// getRowTest().then(()=> console.log('query completed'))

// close the database connection
// db.close();

module.exports = { getRow }