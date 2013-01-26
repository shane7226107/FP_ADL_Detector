/*Module for running system calls*/
var exec = require('child_process').exec;

/*Module for http server*/
var server,
    ip   = "127.0.0.1",
    port = 8888,
    http = require('http'),
    url = require('url'),
    path;

/*Module of file system*/
var page_file_index = require("fs"),
    encode = "utf8",
    filePath = "static/index.html";

/*Creating http server*/
server = http.createServer(function (req, res) {
  path = url.parse(req.url);

  switch (path.pathname) {
    case "/index":
      page_file_index.readFile(filePath, encode, function(err, file) {
        res.writeHead(200, {'Content-Type': 'text/html'});
        res.write(file);
        res.end();
      });
      break;
    case "/test":
      res.writeHead(200, {'Content-Type': 'text/plain'});
      run_ADL(res);
      break;
    default:
      res.writeHead(200, {'Content-Type': 'text/plain'});
      res.end('default page.\n');
      break;
  }
});

server.listen(port, ip);

console.log("Server running at http://" + ip + ":" + port);


/*Functions*/
function run_ADL(callback){
  var result = "nothing";

	console.log('running_ADL...');

	exec('./../DerivedData/FP_ADL_Detector/Build/Products/Debug/FP_ADL_Detector ~/Desktop/ADL_videos/by_hand/raw_video/beverage/1.mp4 show crf 550 650', 
  		function (error, stdout, stderr) {
	    	console.log('stdout: ' + stdout);
        callback.end(stdout);
	    	if (error !== null) {
	      		console.log('stderr: ' + stderr);
	      		console.log('exec error: ' + error);
            callback.end('stderr: ' + stderr);
	    	}
		});

  
}