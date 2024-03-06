const http = require('http');
const fs = require('fs');
const path = require('path');

function handle(req,res){
    // console.log(req.url);
    let body  = ""
    if (req.url.endsWith('html')){
      body = fs.readFileSync(path.join(__dirname, req.url));
    } else if (req.url.endsWith("dy")){
      const ts = {new Date().toLocalTimeString,
      body = '<h2>$(ts)<h2>'
      }

    }
    res.writeHead(200,{
      "content-length": Buffer.byteLength(body),
      "content-type": "text/html",
    });
    res.write(body);
    res.end();

}


// http.createServer(handle) {
//   res.writeHead(200, {'Content-Type': 'text/html'});
//   res.end('Hello World!');
// }

const server = http.createServer(handle);
server.listen(5000);