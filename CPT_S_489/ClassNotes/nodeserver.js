const http = require('http');

function handle(req,res){
    console.log(req,res);
}


http.createServer(handle) {
  res.writeHead(200, {'Content-Type': 'text/html'});
  res.end('Hello World!');
}

const server = http.createServer(handle);
server.listen(5000);